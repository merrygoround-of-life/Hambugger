#pragma once


#include "HbgWndBase.h"


struct HbgUpdate_Thread;


class CHbgThreadList : public CListCtrl
{
	DECLARE_DYNAMIC(CHbgThreadList)

public:
	CHbgThreadList();
	virtual ~CHbgThreadList();

private:
	class CHbgThreadInfo
	{
	public:
		CHbgThreadInfo(const HbgUpdate_Thread& threadInfo);

	public:
		HbgContext curContext;
		DWORD_PTR startAddress;
	};

protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLvnGetdispinfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);

public:
	void AddItem(const HbgUpdate_Thread& threadInfo);
	void RemoveItem(SIZE_T id);
	SIZE_T FindItem(SIZE_T id) const;

protected:
	DECLARE_MESSAGE_MAP()

public:
	std::vector<CHbgThreadInfo> m_threads;
	SIZE_T m_curIdx;
	BOOL m_bEnable;

	HWND m_hMainView;
};


// CHbgThreadWnd

class CHbgThreadWnd : public CDockablePane, public IHbgWndBase
{
	DECLARE_DYNAMIC(CHbgThreadWnd)

public:
	CHbgThreadWnd();
	virtual ~CHbgThreadWnd();

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
	CHbgThreadList m_wndThreadList;
	CFont m_fontThreadWnd;
};


