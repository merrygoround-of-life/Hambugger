#pragma once


#include "HbgWndBase.h"


struct IHbgRegProc;


class CHbgRegisterItemList : public CListCtrl
{
	DECLARE_DYNAMIC(CHbgRegisterItemList)

public:
	CHbgRegisterItemList();
	virtual ~CHbgRegisterItemList();

public:
	class CHbgRegisterItem
	{
	public:
		CHbgRegisterItem(const IHbgRegProc* pRegObj);

	public:
		const IHbgRegProc* m_pRegObj;
	};

protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLvnGetdispinfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnBeginlabeledit(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnEndlabeledit(NMHDR *pNMHDR, LRESULT *pResult);

protected:
	DECLARE_MESSAGE_MAP()

private:
	void Initialize();

public:
	std::vector<CHbgRegisterItem> m_regItems;
	DWORD m_idThread;
	CONTEXT m_context;

	BOOL m_bEnable;
	HWND m_hMainView;
};

// CHbgRegisterWnd

class CHbgRegisterWnd : public CDockablePane, public IHbgWndBase
{
	DECLARE_DYNAMIC(CHbgRegisterWnd)

public:
	CHbgRegisterWnd();
	virtual ~CHbgRegisterWnd();

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
	void SetRegisters(const DWORD id, const CONTEXT& context);

protected:
	CHbgRegisterItemList m_wndRegItemList;
	CFont m_fontRegisterWnd;
};


