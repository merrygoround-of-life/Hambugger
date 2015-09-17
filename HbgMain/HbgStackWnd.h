#pragma once


#include "HbgWndBase.h"


struct HbgUpdate_Thread;


class CHbgStackList : public CListCtrl
{
	DECLARE_DYNAMIC(CHbgStackList)

public:
	CHbgStackList();
	virtual ~CHbgStackList();

public:
	class CHbgStackInfo
	{
	public:
		CHbgStackInfo();
		CHbgStackInfo(DWORD id);
		CHbgStackInfo(const HbgUpdate_Thread& threadInfo);
		bool operator() (const CHbgStackInfo& val1, const CHbgStackInfo& val2) const { return (val1.id < val2.id) ? TRUE : FALSE; }

	public:
		DWORD id;
		DWORD_PTR baseAddress;
	};

protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLvnGetdispinfo(NMHDR *pNMHDR, LRESULT *pResult);

public:
	void AddStackPage(const HbgUpdate_Thread& threadInfo);
	void RemoveStackPage(DWORD id);
	CHbgStackInfo* SetStackPage(DWORD id);

protected:
	DECLARE_MESSAGE_MAP()

public:
	std::set<CHbgStackInfo, CHbgStackInfo> m_stacks;

	DWORD m_curThread;
	DWORD_PTR m_curAddress;
	PDWORD_PTR m_pData;
	SIZE_T m_sizeData;
};


// CHbgStackWnd

class CHbgStackWnd : public CDockablePane, public IHbgWndBase
{
	DECLARE_DYNAMIC(CHbgStackWnd)

public:
	CHbgStackWnd();
	virtual ~CHbgStackWnd();

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

public:
	// IHbgWndBase	
	virtual void LinkMain(CHbgMainView* pHbgView, CHbgMainDoc* pHbgDoc);
	virtual void Reset();
	virtual void Enable(BOOL bEnable);
	virtual void Prompt(HBG_PROMPT_TYPE type, LPCVOID pData);
	virtual void Update(HBG_UPDATE_TYPE type, LPCVOID pData);

protected:
	CHbgStackList m_wndStackList;
	CFont m_fontStackWnd;
};


