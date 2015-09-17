
// HbgMain.h : HbgMain ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


class CHbgEngine;


// CHbgMainApp:
// �� Ŭ������ ������ ���ؼ��� HbgMain.cpp�� �����Ͻʽÿ�.
//

class CHbgMainApp : public CWinAppEx
{
public:
	CHbgMainApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual CDocument* OpenDocumentFile(LPCTSTR lpszFileName);
	
	virtual BOOL Register();
	virtual BOOL Unregister();

public:
	CHbgEngine* HbgGetEngine();
	HWND _ClbkHWnd(HWND pHWND = NULL);
};

extern CHbgMainApp theApp;
