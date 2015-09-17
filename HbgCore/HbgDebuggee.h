#pragma once

#include "HbgBreakPoint.h"


#define HBG_TFBIT		0x100
#define HBG_BPOPC		0xCC


class CHbgDebuggeeHandler;


class CHbgDebuggee
{
public:
	CHbgDebuggee(LPCWSTR path);
	CHbgDebuggee(DWORD pid);
	~CHbgDebuggee();

public:
	// Lock
	void Enter();
	void Leave();

public:
	LPCWSTR GetPath() const						{ if (!m_path.empty()) return m_path.c_str(); return NULL; }
	DWORD GetPid() const						{ return m_pid; }

	HANDLE GetProcessHandle() const				{ return m_hProcess; }
	void SetProcessHandle(HANDLE hProcess)		{ m_hProcess = hProcess; }
	
private:
	void Initialize();

private:
	std::wstring m_path;
	DWORD m_pid;

	HANDLE m_hProcess;

	CRITICAL_SECTION m_cs;

	// Threads
	std::map<DWORD, std::pair<HANDLE, DWORD_PTR> > m_mapThreads;

	// 영속 Breakpoint
	std::set<CHbgBreakPoint, CHbgBreakPoint> m_breakpoints;

	// 일회성 Breakpoint
	DWORD_PTR m_instantBreakpoint;
	BYTE m_bOpInstantBP;
	
	// 내부 참조용
	DWORD_PTR m_delayedBreakpoint;
	BOOL m_bPromptNextTime;

	friend class CHbgDebuggeeHandler;
};
