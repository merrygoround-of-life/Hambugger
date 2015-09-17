
// MainFrm.h : CMainFrame 클래스의 인터페이스
//

#pragma once

#include "HbgRegisterWnd.h"
#include "HbgMemoryWnd.h"
#include "HbgBreakpointWnd.h"
#include "HbgStackWnd.h"
#include "HbgModuleWnd.h"
#include "HbgThreadWnd.h"

class CMainFrame : public CFrameWndEx
{
	
protected: // serialization에서만 만들어집니다.
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

// 구현입니다.
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 컨트롤 모음이 포함된 멤버입니다.
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;
	CMFCToolBar       m_wndDebugToolBar;
	CMFCStatusBar     m_wndStatusBar;
	CMFCToolBarImages m_UserImages;

	CHbgRegisterWnd m_wndRegisters;
	CHbgMemoryWnd m_wndMemory;
	CHbgBreakpointWnd m_wndBreakpoints;
	CHbgStackWnd m_wndStack;
	CHbgModuleWnd m_wndModules;
	CHbgThreadWnd m_wndThreads;

// 생성된 메시지 맵 함수
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	afx_msg void OnUpdateConnected(CCmdUI *pCmdUI);
	DECLARE_MESSAGE_MAP()

	BOOL CreateDockingWindows();
	void SetDockingWindowIcons(BOOL bHiColorIcons);

public:
	CMFCStatusBar* GetStatusBar();

	CHbgRegisterWnd* GetRegisterWnd();
	CHbgMemoryWnd* GetMemoryWnd();
	CHbgBreakpointWnd* GetBreakpointWnd();
	CHbgStackWnd* GetStackWnd();
	CHbgModuleWnd* GetModuleWnd();
	CHbgThreadWnd* GetThreadWnd();
};


