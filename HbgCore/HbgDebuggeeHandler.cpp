#include "StdAfx.h"
#include "Psapi.h"
#include "HbgBase/HbgPlatform.h"
#include "HbgDebuggee.h"
#include "HbgDebuggeeHandler.h"


CHbgDebuggeeHandler::CHbgDebuggeeHandler(CHbgDebuggee& dbggee)
:	m_dbggee(dbggee)
{
	m_dbggee.Enter();
}

CHbgDebuggeeHandler::~CHbgDebuggeeHandler()
{
	m_dbggee.Leave();
}

BOOL CHbgDebuggeeHandler::GetDEPromptInfo(const DEBUG_EVENT& de, HbgPrompt_General& promptInfo)
{
	// 1) idThread
	promptInfo.idThread = de.dwThreadId;

	// 2) context
	HANDLE hCurHandle = FindThreadHandle(de.dwThreadId);
	if (!hCurHandle)
		return FALSE;

	GetCurrentContext(hCurHandle, CONTEXT_ALL, promptInfo.context);

	// 3) szMemoryStack
	DWORD_PTR stackBase = FindThreadStackBase(de.dwThreadId);
	if (!stackBase)
		return FALSE;

	promptInfo.szMemoryStack = stackBase - HbgGetContextSP(promptInfo.context);

	// 4) pMemoryStack
	promptInfo.pMemoryStack = new DWORD_PTR[promptInfo.szMemoryStack / sizeof(DWORD_PTR)];
	ReadMemory(HbgGetContextSP(promptInfo.context), (LPBYTE)promptInfo.pMemoryStack, promptInfo.szMemoryStack);

	if (m_dbggee.m_mapThreads.empty())
		return FALSE;

	// 5) szHbgContexts
	promptInfo.szHbgContexts = (DWORD_PTR)(m_dbggee.m_mapThreads.size() * sizeof(HbgContext));

	// 6) pHbgContexts
	promptInfo.pHbgContexts = new HbgContext[promptInfo.szHbgContexts / sizeof(HbgContext)];
	HbgContext* pCurHbgContext = promptInfo.pHbgContexts;

	std::map<DWORD, std::pair<HANDLE, DWORD_PTR> >::const_iterator iter = m_dbggee.m_mapThreads.begin();
	while (iter != m_dbggee.m_mapThreads.end()) {
		if (promptInfo.idThread == iter->first) {
			pCurHbgContext->idThread = promptInfo.idThread;
			pCurHbgContext->eipCurrent = HbgGetContextIP(promptInfo.context);
		} else {			
			CONTEXT context;
			GetCurrentContext(iter->second.first, CONTEXT_FULL, context);

			pCurHbgContext->idThread = iter->first;
			pCurHbgContext->eipCurrent = HbgGetContextIP(context);
		}

		++pCurHbgContext;
		++iter;
	}

	return TRUE;
}

BOOL CHbgDebuggeeHandler::GetDEModuleInfo(const DEBUG_EVENT& de, HbgUpdate_Module& moduleInfo)
{
	DWORD_PTR addrEntryPoint = 0;
	moduleInfo.addressStart = 0;
	moduleInfo.addressEnd = 0;
	moduleInfo.addressCodeStart = 0;
	moduleInfo.addressCodeEnd = 0;

	// 1) address
	switch (de.dwDebugEventCode) {
	case CREATE_PROCESS_DEBUG_EVENT:
		moduleInfo.addressStart = (DWORD_PTR)de.u.CreateProcessInfo.lpBaseOfImage;
		addrEntryPoint = (DWORD_PTR)de.u.CreateProcessInfo.lpStartAddress;
		break;
	case LOAD_DLL_DEBUG_EVENT:
		moduleInfo.addressStart = (DWORD_PTR)de.u.LoadDll.lpBaseOfDll;
		break;
	}

	// PE 내용을 통해 code 영역 가져옴.
	BYTE buf1[sizeof(IMAGE_DOS_HEADER)];
	ReadMemory(moduleInfo.addressStart, buf1, sizeof(buf1));

	BYTE buf2[sizeof(IMAGE_NT_HEADERS)];
	ReadMemory((moduleInfo.addressStart + ((PIMAGE_DOS_HEADER)buf1)->e_lfanew), buf2, sizeof(buf2));

	PIMAGE_NT_HEADERS pINH = (PIMAGE_NT_HEADERS)buf2;

	// 2) size
	moduleInfo.addressEnd = moduleInfo.addressStart + pINH->OptionalHeader.SizeOfImage - 1;

	// 3) code Segment
	moduleInfo.addressCodeStart = moduleInfo.addressStart + pINH->OptionalHeader.BaseOfCode;
	moduleInfo.addressCodeEnd = (pINH->OptionalHeader.SizeOfCode) ? (moduleInfo.addressCodeStart + pINH->OptionalHeader.SizeOfCode - 1) : moduleInfo.addressEnd;

	if (addrEntryPoint) {
		BYTE buf3[sizeof(IMAGE_SECTION_HEADER)];
		DWORD_PTR addrEntryPointDelta = addrEntryPoint - moduleInfo.addressStart;
		DWORD cntSection = pINH->FileHeader.NumberOfSections;
		DWORD idxSection = 0;
		while (idxSection < cntSection) {
			ReadMemory((moduleInfo.addressStart + ((PIMAGE_DOS_HEADER)buf1)->e_lfanew) + sizeof(IMAGE_NT_HEADERS) + (sizeof(IMAGE_SECTION_HEADER) * idxSection), buf3, sizeof(buf3));
			PIMAGE_SECTION_HEADER pISH = (PIMAGE_SECTION_HEADER)buf3;

			if ((pISH->VirtualAddress <= addrEntryPointDelta) && ((pISH->VirtualAddress + pISH->SizeOfRawData) >= addrEntryPointDelta)) {
				moduleInfo.addressCodeStart = moduleInfo.addressStart + pISH->VirtualAddress;
				moduleInfo.addressCodeEnd = moduleInfo.addressCodeStart + pISH->SizeOfRawData - 1;
				break;
			}

			++idxSection;
		}
	}

	_ASSERT(moduleInfo.addressCodeStart < moduleInfo.addressCodeEnd);

	// 4) path
	*moduleInfo.path = L'\0';
	switch (de.dwDebugEventCode) {
	case CREATE_PROCESS_DEBUG_EVENT:
		{
			if (m_dbggee.GetPath())
				wcscpy_s(moduleInfo.path, m_dbggee.GetPath());

			if (*moduleInfo.path == L'\0')
				::GetModuleFileNameEx(m_dbggee.GetProcessHandle(), (HMODULE)de.u.CreateProcessInfo.lpBaseOfImage, moduleInfo.path, sizeof(moduleInfo.path) / sizeof(WCHAR));
		}
		break;
	case LOAD_DLL_DEBUG_EVENT:
		{
			DWORD_PTR lpModuleName = NULL;
			ReadMemory((DWORD_PTR)de.u.LoadDll.lpImageName, (LPBYTE)&lpModuleName, sizeof(lpModuleName));
			if (lpModuleName)
				ReadMemory(lpModuleName, (LPBYTE)moduleInfo.path, sizeof(moduleInfo.path));

			if (*moduleInfo.path == L'\0')
				::GetModuleFileNameEx(m_dbggee.GetProcessHandle(), (HMODULE)de.u.LoadDll.lpBaseOfDll, moduleInfo.path, sizeof(moduleInfo.path) / sizeof(WCHAR));

		}
		break;
	}

	return TRUE;
}

BOOL CHbgDebuggeeHandler::GetDEThreadInfo(const DEBUG_EVENT& de, HbgUpdate_Thread& threadInfo, DWORD_PTR stackBase)
{
	// 1) threadId / threadStartAddress
	threadInfo.threadId = 0;
	threadInfo.threadStartAddress = 0;
	threadInfo.threadStackBase = stackBase;

	switch (de.dwDebugEventCode) {
	case CREATE_PROCESS_DEBUG_EVENT:
		threadInfo.threadId = de.dwThreadId;
		threadInfo.threadStartAddress = (DWORD_PTR)de.u.CreateProcessInfo.lpStartAddress;
		break;
	case CREATE_THREAD_DEBUG_EVENT:
		threadInfo.threadId = de.dwThreadId;
		threadInfo.threadStartAddress = (DWORD_PTR)de.u.CreateThread.lpStartAddress;
		break;
	}

	// 2) strFuncStartAddr
	*threadInfo.strFuncStartAddr = L'\0';

	return TRUE;
}

DWORD_PTR CHbgDebuggeeHandler::AddThread(DWORD idThread, HANDLE hThread, DWORD_PTR lpTLB)
{
	_ASSERT(!FindThreadHandle(idThread));
	
	// TEB구조체의 offset
	// 32bit: 0x04=stackBase / 0x08=stackLimit
	// 64bit: 0x08=stackBase / 0x10=stackLimit
	DWORD_PTR stackBase = 0;
	ReadMemory(lpTLB + sizeof(DWORD_PTR), (LPBYTE)&stackBase, sizeof(stackBase));

	m_dbggee.m_mapThreads.insert(std::pair<DWORD, std::pair<HANDLE, DWORD_PTR> >(idThread, std::pair<HANDLE, DWORD_PTR>(hThread, stackBase)));

	return stackBase;
}

void CHbgDebuggeeHandler::RemoveThread(DWORD idThread)
{
	_ASSERT(FindThreadHandle(idThread));
	std::map<DWORD, std::pair<HANDLE, DWORD_PTR> >::iterator iter = m_dbggee.m_mapThreads.find(idThread);
	if (iter != m_dbggee.m_mapThreads.end())
		m_dbggee.m_mapThreads.erase(iter);
}

HANDLE CHbgDebuggeeHandler::FindThreadHandle(DWORD idThread) const
{
	std::map<DWORD, std::pair<HANDLE, DWORD_PTR> >::const_iterator iter = m_dbggee.m_mapThreads.find(idThread);
	if (iter != m_dbggee.m_mapThreads.end())
		return iter->second.first;

	return NULL;
}

DWORD_PTR CHbgDebuggeeHandler::FindThreadStackBase(DWORD idThread) const
{
	std::map<DWORD, std::pair<HANDLE, DWORD_PTR> >::const_iterator iter = m_dbggee.m_mapThreads.find(idThread);
	if (iter != m_dbggee.m_mapThreads.end())
		return iter->second.second;

	return 0;
}

BOOL CHbgDebuggeeHandler::FindBreakpoint(DWORD_PTR address) const
{
	CHbgBreakPoint tmpBP(address, 0);
	std::set<CHbgBreakPoint, CHbgBreakPoint>::const_iterator iter = m_dbggee.m_breakpoints.find(tmpBP);
	if (iter != m_dbggee.m_breakpoints.end())
		return TRUE;

	return FALSE;
}

void CHbgDebuggeeHandler::AddBreakpoint(DWORD_PTR address, BYTE bOp)
{
	_ASSERT(!FindBreakpoint(address));
	m_dbggee.m_breakpoints.insert(CHbgBreakPoint(address, bOp));
}

BYTE CHbgDebuggeeHandler::RemoveBreakpoint(DWORD_PTR address)
{
	_ASSERT(FindBreakpoint(address));
	BYTE bOp = HBG_BPOPC;

	CHbgBreakPoint tmpBP(address, 0);
	std::set<CHbgBreakPoint, CHbgBreakPoint>::iterator iter = m_dbggee.m_breakpoints.find(tmpBP);
	if (iter != m_dbggee.m_breakpoints.end()) {
		bOp = iter->m_bOp;
		m_dbggee.m_breakpoints.erase(iter);
	}

	return bOp;
}

DWORD CHbgDebuggeeHandler::CheckBPs(DWORD_PTR addrStart, DWORD_PTR addrEnd, std::vector<CHbgBreakPoint>& listBPS) const
{
	UINT count = 0;
	std::set<CHbgBreakPoint, CHbgBreakPoint>::const_iterator iter = m_dbggee.m_breakpoints.begin();
	while (iter != m_dbggee.m_breakpoints.end()) {
		if ((addrStart <= iter->m_address) && (addrEnd >= iter->m_address)) {
			listBPS.push_back(*iter);
			++count;
		}

		++iter;
	}

	return count;
}

DWORD_PTR CHbgDebuggeeHandler::GetInstantBreakpoint(BYTE& bOP) const
{
	bOP = m_dbggee.m_bOpInstantBP;
	return m_dbggee.m_instantBreakpoint;
}

void CHbgDebuggeeHandler::SetInstantBreakpoint(DWORD_PTR address)
{
	if (!FindBreakpoint(address)) {		// 주어진 주소에 영속 BP가 있으면 일회성 BP는 만들 필요가 없다.
		m_dbggee.m_instantBreakpoint = address;
		/*size_t nRead = */ReadMemory(address, &m_dbggee.m_bOpInstantBP, sizeof(m_dbggee.m_bOpInstantBP));
		BYTE bOp = HBG_BPOPC;
		/*size_t nWritten = */WriteMemory(address, &bOp, sizeof(bOp));
	}
}

DWORD_PTR CHbgDebuggeeHandler::RemoveInstantBreakpoint()
{
	DWORD_PTR prevInstantBP = 0;
	if (m_dbggee.m_instantBreakpoint && (m_dbggee.m_bOpInstantBP != HBG_BPOPC)) {		
#ifdef _DEBUG
		BYTE bOp = HBG_BPOPC;
		/*size_t nRead = */ReadMemory(m_dbggee.m_instantBreakpoint, &bOp, sizeof(bOp));		// bOp must be HBG_BPOPC
		_ASSERT(bOp == HBG_BPOPC);
#endif // _DEBUG

		/*size_t nWritten = */WriteMemory(m_dbggee.m_instantBreakpoint, &m_dbggee.m_bOpInstantBP, sizeof(m_dbggee.m_bOpInstantBP));

		prevInstantBP = m_dbggee.m_instantBreakpoint;
		m_dbggee.m_instantBreakpoint = 0;
		m_dbggee.m_bOpInstantBP = HBG_BPOPC;
	}

	return prevInstantBP;
}

void CHbgDebuggeeHandler::_SetDelayedBreakpoint(DWORD_PTR address/*= 0*/)
{
	m_dbggee.m_delayedBreakpoint = address;
}

DWORD_PTR CHbgDebuggeeHandler::_GetDelayedBreakpoint() const
{
	return m_dbggee.m_delayedBreakpoint;
}

void CHbgDebuggeeHandler::_SetPromptNextTime(BOOL bPrompt)
{
	m_dbggee.m_bPromptNextTime = bPrompt;
}

BOOL CHbgDebuggeeHandler::_GetPromptNextTime() const
{
	return m_dbggee.m_bPromptNextTime;
}

void CHbgDebuggeeHandler::GetCurrentContext(HANDLE hThread, DWORD flags, CONTEXT& context) const
{
	context.ContextFlags = flags;
	::GetThreadContext(hThread, &context);
}

void CHbgDebuggeeHandler::SetCurrentContext(HANDLE hThread, DWORD flags, CONTEXT& context) const
{
	context.ContextFlags = flags;
	::SetThreadContext(hThread, &context);
}

DWORD_PTR CHbgDebuggeeHandler::GetCurrentEIP(HANDLE hThread)
{
	CONTEXT context;
	GetCurrentContext(hThread, CONTEXT_CONTROL, context);

	return HbgGetContextIP(context);
}

void CHbgDebuggeeHandler::SetCurrentEIP(HANDLE hThread, DWORD_PTR eip)
{
	CONTEXT context;
	GetCurrentContext(hThread, CONTEXT_CONTROL, context);

	HbgGetContextIP(context) = (DWORD_PTR)eip;
	SetCurrentContext(hThread, CONTEXT_CONTROL, context);
}

SIZE_T CHbgDebuggeeHandler::ReadMemory(DWORD_PTR address, BYTE* buf, SIZE_T bufSize)
{
	HANDLE hProcess = m_dbggee.GetProcessHandle();
	SIZE_T nRead = 0;
	BOOL bSucceeded = FALSE;

	if (ReadProcessMemory(hProcess, (LPCVOID)address, buf, bufSize, &nRead))
		bSucceeded = TRUE;

	return bSucceeded ? nRead : 0;
}

SIZE_T CHbgDebuggeeHandler::WriteMemory(DWORD_PTR address, const BYTE* buf, SIZE_T bufSize)
{
	HANDLE hProcess = m_dbggee.GetProcessHandle();
	SIZE_T nWritten = 0;
	BOOL bSucceeded = FALSE;

	MEMORY_BASIC_INFORMATION mbi;
	if (VirtualQueryEx(hProcess, (LPCVOID)address, &mbi, sizeof (MEMORY_BASIC_INFORMATION))) {

		DWORD oldProtect;
		if (VirtualProtectEx(hProcess, mbi.BaseAddress, mbi.RegionSize, PAGE_EXECUTE_READWRITE, &oldProtect)) {

			if (WriteProcessMemory(hProcess, (LPVOID)address, (LPCVOID)buf, bufSize, &nWritten)) {

				if (VirtualProtectEx(hProcess, mbi.BaseAddress, mbi.RegionSize, mbi.Protect, &oldProtect)) {

					if (FlushInstructionCache (hProcess, (LPCVOID)address, bufSize))
						bSucceeded = TRUE;
				}
			}
		}
	}

	if (!bSucceeded)
		nWritten = 0;

	return nWritten;
}

BOOL CHbgDebuggeeHandler::ToggleBreakpoint(DWORD_PTR address)
{
	BOOL bSet;
	if (!FindBreakpoint(address)) {
		// Set Breakpoint
		BYTE bOldOp = HBG_BPOPC;
		/*size_t nRead = */ReadMemory(address, &bOldOp, sizeof(bOldOp));
		BYTE bOp = HBG_BPOPC;
		/*size_t nWritten = */WriteMemory(address, &bOp, sizeof(bOp));
		AddBreakpoint(address, bOldOp);

		bSet = TRUE;
	} else {
		// Remove Breakpoint
		BYTE bOp = RemoveBreakpoint(address);
		/*size_t nWritten = */WriteMemory(address, &bOp, sizeof(bOp));

		bSet = FALSE;
	}

	return bSet;
}

BOOL CHbgDebuggeeHandler::SetSingleStep(HANDLE hThread)
{
	if (!hThread)
		return FALSE;

	CONTEXT context;
	GetCurrentContext(hThread, CONTEXT_CONTROL, context);

	context.EFlags |= HBG_TFBIT;
	SetCurrentContext(hThread, CONTEXT_CONTROL, context);

	return TRUE;
}
