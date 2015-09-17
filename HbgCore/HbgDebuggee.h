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

	// ���� Breakpoint
	std::set<CHbgBreakPoint, CHbgBreakPoint> m_breakpoints;

	// ��ȸ�� Breakpoint
	DWORD_PTR m_instantBreakpoint;
	BYTE m_bOpInstantBP;
	
	// ���� ������
	DWORD_PTR m_delayedBreakpoint;
	BOOL m_bPromptNextTime;

	friend class CHbgDebuggeeHandler;
};
