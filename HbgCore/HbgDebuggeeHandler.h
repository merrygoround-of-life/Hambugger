#pragma once

#include "HbgBreakPoint.h"


class CHbgDebuggee;


class CHbgDebuggeeHandler
{
public:
	CHbgDebuggeeHandler(CHbgDebuggee& dbggee);
	~CHbgDebuggeeHandler();

private:
	CHbgDebuggeeHandler& operator=(const CHbgDebuggeeHandler& /*hbgCriticalSection*/);

public:
	// Information
	BOOL GetDEPromptInfo(const DEBUG_EVENT& de, HbgPrompt_General& promptInfo);
	BOOL GetDEModuleInfo(const DEBUG_EVENT& de, HbgUpdate_Module& moduleInfo);
	BOOL GetDEThreadInfo(const DEBUG_EVENT& de, HbgUpdate_Thread& threadInfo, DWORD_PTR stackBase);

	// Dynamic Properties
	DWORD_PTR AddThread(DWORD idThread, HANDLE hThread, DWORD_PTR lpTLB);
	void RemoveThread(DWORD idThread);
	HANDLE FindThreadHandle(DWORD idThread) const;
	DWORD_PTR FindThreadStackBase(DWORD idThread) const;

	BOOL FindBreakpoint(DWORD_PTR address) const;
	void AddBreakpoint(DWORD_PTR address, BYTE bOp);
	BYTE RemoveBreakpoint(DWORD_PTR address);
	DWORD CheckBPs(DWORD_PTR addrStart, DWORD_PTR addrEnd, std::vector<CHbgBreakPoint>& listBPS) const;

	DWORD_PTR GetInstantBreakpoint(BYTE& bOP) const;
	void SetInstantBreakpoint(DWORD_PTR address);
	DWORD_PTR RemoveInstantBreakpoint();

	void _SetDelayedBreakpoint(DWORD_PTR address = 0);
	DWORD_PTR _GetDelayedBreakpoint() const;

	void _SetPromptNextTime(BOOL bPrompt);
	BOOL _GetPromptNextTime() const;

	// Utilities
	void GetCurrentContext(HANDLE hThread, DWORD flags, CONTEXT& context) const;
	void SetCurrentContext(HANDLE hThread, DWORD flags, CONTEXT& context) const;

	DWORD_PTR GetCurrentEIP(HANDLE hThread);
	void SetCurrentEIP(HANDLE hThread, DWORD_PTR eip);

	SIZE_T ReadMemory(DWORD_PTR address, BYTE* buf, SIZE_T bufSize);
	SIZE_T WriteMemory(DWORD_PTR address, const BYTE* buf, SIZE_T bufSize);

	BOOL ToggleBreakpoint(DWORD_PTR address);
	BOOL SetSingleStep(HANDLE hThread);

private:
	CHbgDebuggee& m_dbggee;
};
