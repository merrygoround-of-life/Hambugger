#include "StdAfx.h"
#include "HbgDebuggee.h"


// CHbgDebuggee
CHbgDebuggee::CHbgDebuggee(LPCWSTR path)
:	m_hProcess(NULL), m_instantBreakpoint(0), m_bOpInstantBP(HBG_BPOPC), m_delayedBreakpoint(0), m_bPromptNextTime(TRUE)
{
	Initialize();

	m_pid = 0;
	if (path)
		m_path = path;
}

CHbgDebuggee::CHbgDebuggee(DWORD pid)
:	m_hProcess(NULL), m_instantBreakpoint(0), m_bOpInstantBP(HBG_BPOPC), m_delayedBreakpoint(0), m_bPromptNextTime(TRUE)
{
	Initialize();
	
	if (pid)
		m_pid = pid;	
	m_path.clear();
}

CHbgDebuggee::~CHbgDebuggee()
{
	::DeleteCriticalSection(&m_cs);
}

void CHbgDebuggee::Enter()
{
	::EnterCriticalSection(&m_cs);
}

void CHbgDebuggee::Leave()
{
	::LeaveCriticalSection(&m_cs);
}

void CHbgDebuggee::Initialize()
{
	if (0 == ::InitializeCriticalSectionAndSpinCount(&m_cs, 4000)) {
		// error
		_ASSERT(FALSE);
	}
}
