#pragma once


#include "HbgWndBase.h"


class CHbgMainDoc;


class CHbgBreakpointList : public CListCtrl
{
	DECLARE_DYNAMIC(CHbgBreakpointList)

public:
	CHbgBreakpointList();
	virtual ~CHbgBreakpointList();


protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLvnGetdispinfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);

protected:
	DECLARE_MESSAGE_MAP()

public:
	BOOL m_bEnable;

	HWND m_hMainView;
	CHbgMainDoc* m_pHbgDoc;
};


// CHbgBreakpointWnd

class CHbgBreakpointWnd : public CDockablePane, public IHbgWndBase
{
	DECLARE_DYNAMIC(CHbgBreakpointWnd)

public:
	CHbgBreakpointWnd();
	virtual ~CHbgBreakpointWnd();

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
	CHbgBreakpointList m_wndBreakpointList;
	CFont m_fontBreakpointWnd;
};


