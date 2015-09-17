#pragma once
#include "afxwin.h"


class CHbgMemPtr;


class CHbgPatchEdit1 : public CEdit
{
	DECLARE_DYNAMIC(CHbgPatchEdit1)

public:
	CHbgPatchEdit1(BOOL bCode);
	virtual ~CHbgPatchEdit1();

protected:
	DECLARE_MESSAGE_MAP()

private:
	BOOL m_bCode;
};


// CHbgPatchDialog 대화 상자입니다.

class CHbgPatchDialog : public CDialog
{
	DECLARE_DYNAMIC(CHbgPatchDialog)

public:
	CHbgPatchDialog(CWnd* pParent, DWORD_PTR address, BOOL bCode = TRUE);   // 표준 생성자입니다.
	virtual ~CHbgPatchDialog();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_PATCH_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnOK();

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();

public:
	afx_msg void OnEnChangeEditPatch();

private:
	void _Convert(const CString& src, CHbgMemPtr& buf);

private:
	CHbgPatchEdit1 m_editPatch;
	CHbgPatchEdit1 m_editInfo;

	CFont m_fontPatchEdit;

private:
	DWORD_PTR m_address;
	BOOL m_bCode;
};
