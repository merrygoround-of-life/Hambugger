#pragma once


#include "HbgWndBase.h"


struct HbgUpdate_Module;


class CHbgModuleList : public CListCtrl
{
	DECLARE_DYNAMIC(CHbgModuleList)

public:
	CHbgModuleList();
	virtual ~CHbgModuleList();

private:
	class CHbgModuleInfo
	{
	public:
		CHbgModuleInfo(SIZE_T order, const HbgUpdate_Module& moduleInfo);

	public:
		SIZE_T idx;
		DWORD_PTR addressStart;
		DWORD_PTR addressEnd;
		DWORD_PTR addressCodeStart;
		DWORD_PTR addressCodeEnd;
		std::wstring name;
		std::wstring path;
	};

protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLvnGetdispinfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);

public:
	void AddItem(const HbgUpdate_Module& moduleInfo);
	void RemoveItem(DWORD_PTR baseAddr);
	SIZE_T FindItem(DWORD_PTR addr) const;

protected:
	DECLARE_MESSAGE_MAP()

public:
	std::vector<CHbgModuleInfo> m_modules;
	SIZE_T m_curIdx;
	SIZE_T m_newIdx;
	BOOL m_bEnable;

	HWND m_hMainView;
	CHbgMainDoc* m_pHbgDoc;
};


// CHbgModuleWnd

class CHbgModuleWnd : public CDockablePane, public IHbgWndBase
{
	DECLARE_DYNAMIC(CHbgModuleWnd)

public:
	CHbgModuleWnd();
	virtual ~CHbgModuleWnd();

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
	CHbgModuleList m_wndModuleList;
	CFont m_fontModuleWnd;
};


