#include "StdAfx.h"
#include "HbgBase/HbgDebug_h.h"
#include "HbgBreakPoint.h"
#include "HbgDebugLoop.h"
#include "HbgDebuggeeHandler.h"
#include "HbgCoreInternal.h"


CHbgCoreInternal::CHbgCoreInternal(void)
:	m_pDebugLoop(NULL), m_pICallback(NULL)
{
}

CHbgCoreInternal::~CHbgCoreInternal(void)
{
	_Init();
}

BOOL CHbgCoreInternal::Initialize(LPCWSTR pathDebuggee, IUnknown* pIUnkClbk)
{
	_Init();

	if (pathDebuggee && *pathDebuggee) {
		HRESULT hr = pIUnkClbk->QueryInterface(IID_IHbgCallback, (LPVOID*)&m_pICallback);
		if (SUCCEEDED(hr)) {
			pIUnkClbk->Release();
			IStream* pICallbackStream = NULL;
			hr = ::CoMarshalInterThreadInterfaceInStream(IID_IHbgCallback, m_pICallback, &pICallbackStream);

			m_pDebugLoop = new CHbgDebugLoop(pathDebuggee, pICallbackStream);

			return m_pDebugLoop->Start();
		}
	}

	return FALSE;
}

BOOL CHbgCoreInternal::InitializeEx(DWORD pidDebuggee, IUnknown* pIUnkClbk)
{
	_Init();

	if (pidDebuggee) {
		HRESULT hr = pIUnkClbk->QueryInterface(IID_IHbgCallback, (LPVOID*)&m_pICallback);
		if (SUCCEEDED(hr)) {
			pIUnkClbk->Release();
			IStream* pICallbackStream = NULL;
			hr = ::CoMarshalInterThreadInterfaceInStream(IID_IHbgCallback, m_pICallback, &pICallbackStream);

			m_pDebugLoop = new CHbgDebugLoop(pidDebuggee, pICallbackStream);

			return m_pDebugLoop->Start();
		}
	}

	return FALSE;
}

BOOL CHbgCoreInternal::Detach()
{
	if (!m_pDebugLoop)
		return FALSE;

	return m_pDebugLoop->Detach();
}

BOOL CHbgCoreInternal::Go(DWORD_PTR toAddr)
{
	if (!m_pDebugLoop || !m_pDebugLoop->AcquirePrompt())
		return FALSE;

	CHbgDebuggeeHandler dbggeeHndlr(m_pDebugLoop->GetDebuggee());

	if (toAddr)
		dbggeeHndlr.SetInstantBreakpoint(toAddr);

	return m_pDebugLoop->Go();
}

BOOL CHbgCoreInternal::Step(DWORD idThread)
{
	if (!m_pDebugLoop || !m_pDebugLoop->AcquirePrompt())
		return FALSE;

	CHbgDebuggeeHandler dbggeeHndlr(m_pDebugLoop->GetDebuggee());

	HANDLE hCurThread = dbggeeHndlr.FindThreadHandle(idThread);
	if (!hCurThread)
		return FALSE;

	dbggeeHndlr.SetSingleStep(hCurThread);
	dbggeeHndlr._SetPromptNextTime(TRUE);

	return m_pDebugLoop->Go();
}

BOOL CHbgCoreInternal::Break()
{
	if (!m_pDebugLoop)
		return FALSE;

	CHbgDebuggeeHandler dbggeeHndlr(m_pDebugLoop->GetDebuggee());

	return m_pDebugLoop->Break();
}

BOOL CHbgCoreInternal::ToggleBreakpoint(DWORD_PTR addr, BOOL* bSet)
{
	if (!m_pDebugLoop)
		return FALSE;

	CHbgDebuggeeHandler dbggeeHndlr(m_pDebugLoop->GetDebuggee());
	*bSet = dbggeeHndlr.ToggleBreakpoint(addr);

	return TRUE;
}

BOOL CHbgCoreInternal::ReadMemory(DWORD_PTR addr, SIZE_T size, BYTE* pByte)
{
	if (!m_pDebugLoop || !size || !m_pDebugLoop->AcquirePrompt())
		return FALSE;

	CHbgDebuggeeHandler dbggeeHndlr(m_pDebugLoop->GetDebuggee());

	SIZE_T nRead = dbggeeHndlr.ReadMemory(addr, pByte, size);
	_ASSERT(nRead);

	_FixBP(addr, size, pByte, TRUE);

	m_pDebugLoop->ReactivatePrompt();
	return nRead ? TRUE : FALSE;
}

BOOL CHbgCoreInternal::WriteMemory(DWORD_PTR addr, SIZE_T size, BYTE* pByte)
{
	if (!m_pDebugLoop || !size || !m_pDebugLoop->AcquirePrompt())
		return FALSE;

	CHbgDebuggeeHandler dbggeeHndlr(m_pDebugLoop->GetDebuggee());

	_FixBP(addr, size, pByte, FALSE);
	SIZE_T nWritten = dbggeeHndlr.WriteMemory(addr, pByte, size);
	_ASSERT(nWritten);

	m_pDebugLoop->ReactivatePrompt();
	return nWritten ? TRUE : FALSE;
}

BOOL CHbgCoreInternal::ReadContext(DWORD idThread, SIZE_T size, BYTE* pByte)
{
	if (!m_pDebugLoop || (size != sizeof(CONTEXT)) || !m_pDebugLoop->AcquirePrompt())
		return FALSE;

	CHbgDebuggeeHandler dbggeeHndlr(m_pDebugLoop->GetDebuggee());

	CONTEXT* pCurContext = (CONTEXT*)pByte;
	HANDLE curThread = dbggeeHndlr.FindThreadHandle(idThread);

	if (curThread)
		dbggeeHndlr.GetCurrentContext(curThread, CONTEXT_ALL, *pCurContext);
	else
		_ASSERT(FALSE);

	m_pDebugLoop->ReactivatePrompt();
	return TRUE;
}

BOOL CHbgCoreInternal::WriteContext(DWORD idThread, SIZE_T size, BYTE* pByte)
{
	if (!m_pDebugLoop || (size != sizeof(CONTEXT)) || !m_pDebugLoop->AcquirePrompt())
		return FALSE;

	CHbgDebuggeeHandler dbggeeHndlr(m_pDebugLoop->GetDebuggee());

	CONTEXT* pCurContext = (CONTEXT*)pByte;
	HANDLE curThread = dbggeeHndlr.FindThreadHandle(idThread);

	if (curThread)
		dbggeeHndlr.SetCurrentContext(curThread, CONTEXT_ALL, *pCurContext);
	else
		_ASSERT(FALSE);

	m_pDebugLoop->ReactivatePrompt();
	return TRUE;
}

void CHbgCoreInternal::_Init()
{	
	if (m_pDebugLoop) {
		delete m_pDebugLoop;
		m_pDebugLoop = NULL;
	}
}

void CHbgCoreInternal::_FixBP(DWORD_PTR addr, SIZE_T size, BYTE* pByte, BOOL bRead)
{
	CHbgDebuggeeHandler dbggeeHndlr(m_pDebugLoop->GetDebuggee());

	DWORD_PTR addrStart = addr;
	DWORD_PTR addrEnd = addr + size - 1;

	// 1) General BP
	std::vector<CHbgBreakPoint> listBPs;
	if (dbggeeHndlr.CheckBPs(addrStart, addrEnd, listBPs)) {
		std::vector<CHbgBreakPoint>::iterator iter = listBPs.begin();
		while (iter != listBPs.end()) {
			BYTE bOldOp = *(pByte + (*iter).m_address - addrStart);
			*(pByte + (*iter).m_address - addrStart) = (*iter).m_bOp;
			if (!bRead)
				(*iter).m_bOp = bOldOp;

			++iter;
		}
	}
	
	// 2) Instant BP
	BYTE instantOP = 0;
	DWORD_PTR instantBP = dbggeeHndlr.GetInstantBreakpoint(instantOP);
	if (instantBP) {
		if ((addrStart <= instantBP) && (addrEnd >= instantBP)) {
			BYTE bOldOp = *(pByte + instantBP - addrStart);
			*(pByte + instantBP - addrStart) = instantOP;
			if (!bRead)
				dbggeeHndlr.SetInstantBreakpoint(bOldOp);
		}
	}
}
