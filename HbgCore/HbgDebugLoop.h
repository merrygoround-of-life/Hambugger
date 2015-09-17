#pragma once

#include "HbgDebuggee.h"


struct IHbgCallback;


class CHbgDebugLoop
{
public:
	CHbgDebugLoop(LPCWSTR path, IStream* pIClbkStream);
	CHbgDebugLoop(DWORD pid, IStream* pIClbkStream);
	~CHbgDebugLoop(void);

public:
	CHbgDebuggee& GetDebuggee()	{ return m_dbggee; }

public:
	BOOL Start();
	BOOL Go();
	BOOL Break();
	BOOL Detach();

	BOOL AcquirePrompt() const;
	void ReactivatePrompt();

private:
	// PromptInfo Mgr
	class _PIMgr
	{
	public:
		_PIMgr(HbgPrompt_General& promptInfo);
		~_PIMgr();

	private:
		_PIMgr& operator=(const _PIMgr& /*piMgr*/);

	private:
		HbgPrompt_General& m_promptInfo;
	};

	enum HbgEvent {
		HbgEvent_Go = 0,
		HbgEvent_Exit,
		HbgEvent_Detach,

		HbgEvent_Size,
	};

	void _Create(IStream* pIClbkStream);
	void _Init(HbgEvent typeExit = HbgEvent_Exit);

private:
	CHbgDebuggee m_dbggee;

	IStream* m_pIClbkStream;

	HANDLE m_hHbgEvent[HbgEvent_Size];
	HANDLE m_hHbgEventPrompt;
	HANDLE m_hHbgEventInit;
	volatile LONG m_bConnected;

	// DebugLoop Thread
	HANDLE m_hDebugLoopThread;
	static UINT WINAPI DebugLoopThread(LPVOID lpParam);

	static void _thDebugLoop(CHbgDebugLoop& me, CHbgDebuggee& dbggee, IHbgCallback* pICallback);
	static void _thProcessPrompt(CHbgDebugLoop& me, IHbgCallback* pICallback, HBG_PROMPT_TYPE typePrompt, HbgPrompt_General& promptInfo);
	static BOOL _thCheckCondition(CHbgDebugLoop& me, CHbgDebuggee& dbggee, DEBUG_EVENT& de, DWORD& dwContinueStatus, BOOL bExistDE);
};
