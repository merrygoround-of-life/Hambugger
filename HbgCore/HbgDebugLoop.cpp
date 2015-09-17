#include "StdAfx.h"
#include <process.h>

#include "HbgCore.h"
#include "HbgBase/HbgDebug_h.h"
#include "HbgBase/HbgProxyStub.h"
#include "HbgBase/HbgPlatform.h"

#include "HbgDebuggeeHandler.h"
#include "HbgDebugLoop.h"


static const GUID CLSID_HbgSvPS = IID_IHbgDebug;
DWORD g_dwCookieSvPS = 0;


CHbgDebugLoop::CHbgDebugLoop(LPCWSTR path, IStream* pIClbkStream)
:	m_dbggee(path), m_pIClbkStream(pIClbkStream), m_bConnected(FALSE), m_hDebugLoopThread(INVALID_HANDLE_VALUE)
{
	_Create(pIClbkStream);
}

CHbgDebugLoop::CHbgDebugLoop(DWORD pid, IStream* pIClbkStream)
:	m_dbggee(pid), m_pIClbkStream(pIClbkStream), m_bConnected(FALSE), m_hDebugLoopThread(INVALID_HANDLE_VALUE)
{
	_Create(pIClbkStream);
}

CHbgDebugLoop::~CHbgDebugLoop(void)
{
	_Init();

	UINT nIdx = 0;
	while (nIdx < HbgEvent_Size) {
		::CloseHandle(m_hHbgEvent[nIdx]);
		++nIdx;
	}

	::CloseHandle(m_hHbgEventPrompt);
	::CloseHandle(m_hHbgEventInit);
}

BOOL CHbgDebugLoop::Start()
{
	_Init();

	UINT idDebugLoopThread = 0;
	m_hDebugLoopThread = reinterpret_cast<HANDLE>(::_beginthreadex(NULL, 0, &DebugLoopThread, reinterpret_cast<LPVOID>(this), CREATE_SUSPENDED, &idDebugLoopThread));

	if (m_hDebugLoopThread != INVALID_HANDLE_VALUE) {
		::ResumeThread(m_hDebugLoopThread);

		::WaitForSingleObject(m_hHbgEventInit, INFINITE);
		return m_bConnected;
	}

	return FALSE;
}

BOOL CHbgDebugLoop::Go()
{
	::SetEvent(m_hHbgEvent[HbgEvent_Go]);

	return TRUE;
}

BOOL CHbgDebugLoop::Break()
{
	::DebugBreakProcess(m_dbggee.GetProcessHandle());

	return TRUE;
}

BOOL CHbgDebugLoop::Detach()
{
	_Init(HbgEvent_Detach);
	
	return TRUE;
}

BOOL CHbgDebugLoop::AcquirePrompt() const
{
	return (WAIT_OBJECT_0 == ::WaitForSingleObject(m_hHbgEventPrompt, 0));
}

void CHbgDebugLoop::ReactivatePrompt()
{
	::SetEvent(m_hHbgEventPrompt);
}

CHbgDebugLoop::_PIMgr::_PIMgr(HbgPrompt_General& promptInfo)
:	m_promptInfo(promptInfo)
{
	m_promptInfo.idThread = 0;
	memset(&m_promptInfo.context, 0, sizeof(m_promptInfo.context));
	m_promptInfo.szMemoryStack = 0;
	m_promptInfo.pMemoryStack = NULL;
	m_promptInfo.szHbgContexts = 0;
	m_promptInfo.pHbgContexts = NULL;
}

CHbgDebugLoop::_PIMgr::~_PIMgr()
{
	m_promptInfo.idThread = 0;
	memset(&m_promptInfo.context, 0, sizeof(m_promptInfo.context));
	m_promptInfo.szMemoryStack = 0;
	if (m_promptInfo.pMemoryStack) {
		delete[] m_promptInfo.pMemoryStack;
		m_promptInfo.pMemoryStack = NULL;
	}
	m_promptInfo.szHbgContexts = 0;
	if (m_promptInfo.pHbgContexts) {
		delete[] m_promptInfo.pHbgContexts;
		m_promptInfo.pHbgContexts = NULL;
	}
}

void CHbgDebugLoop::_Create(IStream* pIClbkStream)
{
	m_pIClbkStream = pIClbkStream;

	UINT nIdx = 0;
	while (nIdx < HbgEvent_Size) {
		m_hHbgEvent[nIdx] = ::CreateEvent(NULL, TRUE, FALSE, NULL);		// manual, reset
		++nIdx;
	}

	m_hHbgEventPrompt = ::CreateEvent(NULL, FALSE, FALSE, NULL);		// auto, reset
	m_hHbgEventInit = ::CreateEvent(NULL, TRUE, FALSE, NULL);			// manual, reset
	
	m_bConnected = FALSE;
	m_hDebugLoopThread = INVALID_HANDLE_VALUE;
}

void CHbgDebugLoop::_Init(HbgEvent typeExit/*= HbgEvent_Exit*/)
{	
	if (m_hDebugLoopThread && (m_hDebugLoopThread != INVALID_HANDLE_VALUE)) {
		// 스레드 종료
		::SetEvent(m_hHbgEvent[typeExit]);

		// 위험할 수 있으므로 무한히 기다리지 않는다.
		::WaitForSingleObject(m_hDebugLoopThread, INFINITE/*1000*/);

		::CloseHandle(m_hDebugLoopThread);
		m_hDebugLoopThread = INVALID_HANDLE_VALUE;
	}

	UINT nIdx = 0;
	while (nIdx < HbgEvent_Size) {
		::ResetEvent(m_hHbgEvent[nIdx]);
		++nIdx;
	}

	::ResetEvent(m_hHbgEventPrompt);
	::ResetEvent(m_hHbgEventInit);

	m_bConnected = FALSE;
}

UINT WINAPI CHbgDebugLoop::DebugLoopThread(LPVOID lpParam)
{
#ifdef _DEBUG
	OutputDebugString(L"[HbgCore] DebugLoop::Thread Start.\n");
#endif //_DEBUG

	// 0) Initialize Apartment
	HRESULT hr = ::CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	_ASSERT(SUCCEEDED(hr));

	HbgRegisterProxyStub(IID_IHbgDebug, CLSID_HbgSvPS, &g_dwCookieSvPS);
	HbgRegisterProxyStub(IID_IHbgCallback, CLSID_HbgSvPS, &g_dwCookieSvPS);

	CHbgDebugLoop& me = *reinterpret_cast<CHbgDebugLoop*>(lpParam);
	CHbgDebuggee& dbggee = me.m_dbggee;

	IHbgCallback* pICallback = NULL;
	hr = ::CoGetInterfaceAndReleaseStream(me.m_pIClbkStream, IID_IHbgCallback, (LPVOID*)&pICallback);
	_ASSERT(SUCCEEDED(hr));

	// 1) Connect Debuggee
	if (dbggee.GetPath()) {
		STARTUPINFO si;
		PROCESS_INFORMATION pi;
		memset(&si, 0, sizeof(STARTUPINFO));
		memset(&pi, 0, sizeof(PROCESS_INFORMATION));
		si.cb = sizeof(STARTUPINFO);

		// - Debug New Process
		if (::CreateProcess(dbggee.GetPath(), NULL, NULL, NULL, FALSE, DEBUG_ONLY_THIS_PROCESS, NULL, NULL, &si, &pi)) {
			::CloseHandle(pi.hThread);
			::CloseHandle(pi.hProcess);
			::InterlockedExchange(&me.m_bConnected, TRUE);
		}
	} else if (dbggee.GetPid()) {

		// - Debug Exist Process
		if (::DebugActiveProcess(dbggee.GetPid())) {
			::InterlockedExchange(&me.m_bConnected, TRUE);
		}
	}
	::SetEvent(me.m_hHbgEventInit);

	// 2) Debug Loop
	if (me.m_bConnected)
		_thDebugLoop(me, dbggee, pICallback);
	::SetEvent(me.m_hHbgEventPrompt);

	// 3) Finalize Apartment
	HbgRevokeProxyStub(g_dwCookieSvPS);

	::CoUninitialize();

#ifdef _DEBUG
	OutputDebugString(L"[HbgCore] DebugLoop::Thread End.\n");
#endif //_DEBUG

	_endthreadex(0);
	return 0;
}

void CHbgDebugLoop::_thDebugLoop(CHbgDebugLoop& me, CHbgDebuggee& dbggee, IHbgCallback* pICallback)
{
	DWORD_PTR addrEntryPoint = 0;
	BOOL bFirstBP = TRUE;
	BOOL bExitLoop = FALSE;
	HbgPrompt_General promptInfo;

	do {
		// 1) Process Debug Event
		int typePrompt = -1;
		_PIMgr piMgr(promptInfo);

		DEBUG_EVENT de;
		DWORD dwContinueStatus = DBG_CONTINUE;
		BOOL bExistDE = ::WaitForDebugEvent(&de, 100);
		if (bExistDE) {
			CHbgDebuggeeHandler dbggeeHndlr(dbggee);

			switch (de.dwDebugEventCode) {
				case EXCEPTION_DEBUG_EVENT:
					{
						if (bFirstBP) {
							// loader breakpoint
							if (addrEntryPoint) {
								dbggeeHndlr.SetInstantBreakpoint(addrEntryPoint);
								addrEntryPoint = 0;
							}
							bFirstBP = FALSE;
						} else {
							DWORD_PTR prevInstantBP = dbggeeHndlr.RemoveInstantBreakpoint();

							// Restore delayed BP Insertion ///////////////////////
							DWORD_PTR restoreDelayedBP = dbggeeHndlr._GetDelayedBreakpoint();
							if (restoreDelayedBP) {
								if (!dbggeeHndlr.FindBreakpoint(restoreDelayedBP)) {
									dbggeeHndlr.ToggleBreakpoint(restoreDelayedBP);		// return value must be TRUE
									dbggeeHndlr._SetDelayedBreakpoint();				// erase delayedBP
								}
							}
							///////////////////////////////////////////////////////

							HANDLE hCurThread = dbggeeHndlr.FindThreadHandle(de.dwThreadId);
							DWORD_PTR addrException = dbggeeHndlr.GetCurrentEIP(hCurThread);

							switch (de.u.Exception.ExceptionRecord.ExceptionCode) {
								case EXCEPTION_BREAKPOINT:
									{
										typePrompt = HBG_PROMPT_TYPE_GENERAL;
										if ((prevInstantBP == (addrException - 1)) || (dbggeeHndlr.FindBreakpoint(addrException - 1)))
											dbggeeHndlr.SetCurrentEIP(hCurThread, addrException - 1);		// Rewind EIP
									}
									break;
								case EXCEPTION_SINGLE_STEP:
									{
										if (dbggeeHndlr._GetPromptNextTime() || dbggeeHndlr.FindBreakpoint(addrException))
											typePrompt = HBG_PROMPT_TYPE_GENERAL;
										
										dbggeeHndlr._SetPromptNextTime(TRUE);
									}
									break;
								default:
									{
										dwContinueStatus = DBG_EXCEPTION_NOT_HANDLED;
									}
									break;
							}
						}

						if (typePrompt != -1)
							dbggeeHndlr.GetDEPromptInfo(de, promptInfo);
					}
					break;
				case CREATE_THREAD_DEBUG_EVENT:
					{
						DWORD_PTR stackBase = dbggeeHndlr.AddThread(de.dwThreadId, de.u.CreateThread.hThread, (DWORD_PTR)de.u.CreateThread.lpThreadLocalBase);

						HbgUpdate_Thread updateThreadData;
						dbggeeHndlr.GetDEThreadInfo(de, updateThreadData, stackBase);
						pICallback->Update(HBG_UPDATE_TYPE_ADDTHREAD, sizeof(updateThreadData), (LPBYTE)&updateThreadData);
					}
					break;
				case CREATE_PROCESS_DEBUG_EVENT:
					{
						addrEntryPoint = (DWORD_PTR)de.u.CreateProcessInfo.lpStartAddress;
						dbggee.SetProcessHandle(de.u.CreateProcessInfo.hProcess);

						DWORD_PTR stackBase = dbggeeHndlr.AddThread(de.dwThreadId, de.u.CreateProcessInfo.hThread, (DWORD_PTR)de.u.CreateProcessInfo.lpThreadLocalBase);

						HbgUpdate_Module updateModuleData;
						dbggeeHndlr.GetDEModuleInfo(de, updateModuleData);
						pICallback->Update(HBG_UPDATE_TYPE_ADDMODULE, sizeof(updateModuleData), (LPBYTE)&updateModuleData);

						HbgUpdate_Thread updateThreadData;
						dbggeeHndlr.GetDEThreadInfo(de, updateThreadData, stackBase);
						pICallback->Update(HBG_UPDATE_TYPE_ADDTHREAD, sizeof(updateThreadData), (LPBYTE)&updateThreadData);

						::CloseHandle(de.u.CreateProcessInfo.hFile);
					}
					break;
				case EXIT_THREAD_DEBUG_EVENT:
					{
						HbgUpdate_RemoveThread_Id idThread =  (DWORD)de.dwThreadId;
						pICallback->Update(HBG_UPDATE_TYPE_REMOVETHREAD, sizeof(idThread), (LPBYTE)&idThread);

						dbggeeHndlr.RemoveThread(de.dwThreadId);
					}
					break;
				case EXIT_PROCESS_DEBUG_EVENT:
					{
						typePrompt = HBG_PROMPT_TYPE_TERMINATE;
						dbggeeHndlr.GetDEPromptInfo(de, promptInfo);

						// 종료 Prompt 순간에도 정보를 읽을 수 있도록
						//dbggeeHndlr.RemoveThread(de.dwThreadId);
						//dbggeeInfo.SetProcessHandle(NULL);
					}
					break;
				case LOAD_DLL_DEBUG_EVENT:
					{
						HbgUpdate_Module updateModuleData;
						dbggeeHndlr.GetDEModuleInfo(de, updateModuleData);
						pICallback->Update(HBG_UPDATE_TYPE_ADDMODULE, sizeof(updateModuleData), (LPBYTE)&updateModuleData);

						::CloseHandle(de.u.LoadDll.hFile);
					}
					break;
				case UNLOAD_DLL_DEBUG_EVENT:
					{
						HbgUpdate_RemovePage_AddrStart addr = (DWORD_PTR)de.u.UnloadDll.lpBaseOfDll;
						pICallback->Update(HBG_UPDATE_TYPE_REMOVEMODULE, sizeof(addr), (LPBYTE)&addr);

					}
					break;
				case OUTPUT_DEBUG_STRING_EVENT:
				case RIP_EVENT:
					break;
			}
		}
		
		// 2) Process Prompt
		if (typePrompt != -1)
			_thProcessPrompt(me, pICallback, (HBG_PROMPT_TYPE)typePrompt, promptInfo);

		// 3) Process 종료 처리
		bExitLoop = _thCheckCondition(me, dbggee, de, dwContinueStatus, bExistDE);
	} while (!bExitLoop);

	return;
}

void CHbgDebugLoop::_thProcessPrompt(CHbgDebugLoop& me, IHbgCallback* pICallback, HBG_PROMPT_TYPE typePrompt, HbgPrompt_General& promptInfo)
{
	// Prompt
	::SetEvent(me.m_hHbgEventPrompt);

	if (FAILED(pICallback->Prompt(typePrompt, promptInfo.idThread, sizeof(promptInfo.context), (LPBYTE)&promptInfo.context, promptInfo.szMemoryStack, (LPBYTE)promptInfo.pMemoryStack, promptInfo.szHbgContexts, (LPBYTE)promptInfo.pHbgContexts)))
		_ASSERT(FALSE);

	if (typePrompt == HBG_PROMPT_TYPE_TERMINATE)
		::WaitForSingleObject(me.m_hHbgEvent[HbgEvent_Exit], INFINITE);
	else
		::WaitForMultipleObjects(HbgEvent_Size, me.m_hHbgEvent, FALSE, INFINITE);

	// Unprompt
	::ResetEvent(me.m_hHbgEventPrompt);
}

BOOL CHbgDebugLoop::_thCheckCondition(CHbgDebugLoop& me, CHbgDebuggee& dbggee, DEBUG_EVENT& de, DWORD& dwContinueStatus, BOOL bExistDE)
{
	BOOL bExitLoop = FALSE;

	// 종료조건 확인
	switch (::WaitForMultipleObjects(HbgEvent_Size, me.m_hHbgEvent, FALSE, 0)) {
		case HbgEvent_Exit:
			if (bExistDE)
				::ContinueDebugEvent(de.dwProcessId, de.dwThreadId, dwContinueStatus);
			if (!dbggee.GetPath()) {
				// '프로세스 연결'로 시작했을 경우, 무조건 detach 처리
				::DebugActiveProcessStop(::GetProcessId(dbggee.GetProcessHandle()));
			}
			bExitLoop = TRUE;
			break;
		case HbgEvent_Detach:
			if (bExistDE)
				::ContinueDebugEvent(de.dwProcessId, de.dwThreadId, dwContinueStatus);
			::DebugActiveProcessStop(::GetProcessId(dbggee.GetProcessHandle()));
			bExitLoop = TRUE;
			break;
		default:
			::ResetEvent(me.m_hHbgEvent[HbgEvent_Go]);
			if (bExistDE) {
				// Create delayed BP Insertion ////////////////////////
				CHbgDebuggeeHandler dbggeeHndlr(dbggee);
				HANDLE hCurThread = dbggeeHndlr.FindThreadHandle(de.dwThreadId);
				CONTEXT context;
				dbggeeHndlr.GetCurrentContext(hCurThread, CONTEXT_CONTROL, context);
				if (dbggeeHndlr.FindBreakpoint(HbgGetContextIP(context))) {
					dbggeeHndlr.ToggleBreakpoint(HbgGetContextIP(context));			// return value must be FALSE
					dbggeeHndlr._SetDelayedBreakpoint(HbgGetContextIP(context));		// create delayedBP
					dbggeeHndlr.SetSingleStep(hCurThread);

					if (!(context.EFlags & HBG_TFBIT))
						dbggeeHndlr._SetPromptNextTime(FALSE);
				}
				///////////////////////////////////////////////////////

				::ContinueDebugEvent(de.dwProcessId, de.dwThreadId, dwContinueStatus);
			}
			break;
	}

	return bExitLoop;
}
