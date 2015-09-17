#pragma once


#include "HbgWndBase.h"


class CHbgCurrentAddressComboBox : public CComboBox
{
	DECLARE_DYNAMIC(CHbgCurrentAddressComboBox)

public:
	CHbgCurrentAddressComboBox();
	virtual ~CHbgCurrentAddressComboBox();

public:
	void SetCurrent(DWORD_PTR addr);

protected:
	DECLARE_MESSAGE_MAP()

private:
	CString m_strTemplete;
};


class CHbgMemoryEdit : public CEdit
{
	DECLARE_DYNAMIC(CHbgMemoryEdit)

public:
	CHbgMemoryEdit();
	virtual ~CHbgMemoryEdit();

public:
	void SetCurrent(DWORD_PTR addr);

protected:
	DECLARE_MESSAGE_MAP()

private:
	CString m_strAddrTemplete;
	CString m_strByteTemplete;
	CString m_strAsciiTemplete;
};


// CHbgMemoryWnd

class CHbgMemoryWnd : public CDockablePane, public IHbgWndBase
{
	DECLARE_DYNAMIC(CHbgMemoryWnd)

public:
	CHbgMemoryWnd();
	virtual ~CHbgMemoryWnd();

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);

protected:
	DECLARE_MESSAGE_MAP()
	
	void AdjustLayout();

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClickedButton();
	afx_msg void OnUpdateButton(CCmdUI *pCmdUI);
	
public:
	// IHbgWndBase	
	virtual void LinkMain(CHbgMainView* pHbgView, CHbgMainDoc* pHbgDoc);
	virtual void Reset();
	virtual void Enable(BOOL bEnable);
	virtual void Prompt(HBG_PROMPT_TYPE type, LPCVOID pData);
	virtual void Update(HBG_UPDATE_TYPE type, LPCVOID pData);

private:
	BOOL _FixedAddress(DWORD_PTR& addr);

protected:
	CStatic m_wndStatic;
	CHbgCurrentAddressComboBox m_wndCurrentAddress;
	CButton m_wndButton;
	CHbgMemoryEdit m_wndMemoryEdit;
	CFont m_fontMemoryWnd;

private:
	BOOL m_bEnable;
};


