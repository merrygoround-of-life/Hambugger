
// HbgMainView.h : CHbgMainView 클래스의 인터페이스
//


#pragma once


#define HBG_WM_CHANGEPAGE		WM_USER + 11
#define HBG_WM_CHANGECONTEXT	WM_USER + 12


class CHbgPage;
class CHbgMainDoc;
interface IHbgWndBase;


class CHbgMainView : public CListView
{
protected: // serialization에서만 만들어집니다.
	CHbgMainView();
	DECLARE_DYNCREATE(CHbgMainView)

// 특성입니다.
public:
	CHbgMainDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();

// 구현입니다.
public:
	virtual ~CHbgMainView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnLvnGetdispinfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);

	DECLARE_MESSAGE_MAP()
	
public:
	afx_msg void OnDebugOpen();
	afx_msg void OnUpdateDebugOpen(CCmdUI *pCmdUI);
	afx_msg void OnDebugAttach();
	afx_msg void OnUpdateDebugAttach(CCmdUI *pCmdUI);
	afx_msg void OnDebugExit();
	afx_msg void OnUpdateDebugExit(CCmdUI *pCmdUI);
	afx_msg void OnDebugDetach();
	afx_msg void OnUpdateDebugDetach(CCmdUI *pCmdUI);
	afx_msg void OnDebugRestart();
	afx_msg void OnUpdateDebugRestart(CCmdUI *pCmdUI);
	afx_msg void OnDebugPause();
	afx_msg void OnUpdateDebugPause(CCmdUI *pCmdUI);
	afx_msg void OnDebugGo();
	afx_msg void OnUpdateDebugGo(CCmdUI *pCmdUI);
	afx_msg void OnDebugStepIn();
	afx_msg void OnUpdateDebugStepIn(CCmdUI *pCmdUI);
	afx_msg void OnDebugStepOut();
	afx_msg void OnUpdateDebugStepOut(CCmdUI *pCmdUI);
	afx_msg void OnDebugRunTillCursor();
	afx_msg void OnUpdateDebugRunTillCursor(CCmdUI *pCmdUI);
	afx_msg void OnDebugOrigin();
	afx_msg void OnUpdateDebugOrigin(CCmdUI *pCmdUI);
	afx_msg void OnDebugMove();
	afx_msg void OnUpdateDebugMove(CCmdUI *pCmdUI);
	afx_msg void OnDebugToggleBreakpoint();
	afx_msg void OnUpdateToggleBreakpoint(CCmdUI *pCmdUI);
	afx_msg void OnHbgRegister();
	afx_msg void OnUpdateHbgRegister(CCmdUI *pCmdUI);
	afx_msg void OnHbgUnregister();
	afx_msg void OnUpdateHbgUnregister(CCmdUI *pCmdUI);

	LRESULT OnCallbackPrompt(WPARAM wParam, LPARAM lParam);
	LRESULT OnCallbackUpdate(WPARAM wParam, LPARAM lParam);
	LRESULT OnMsgChangePage(WPARAM wParam, LPARAM lParam);
	LRESULT OnMsgChangeContext(WPARAM wParam, LPARAM lParam);

private:
	// IHbgBase 관련
	void RegisterWnds(IHbgWndBase* pWnd);
	void ResetWnds();
	void EnableWnds(BOOL bEnable);
	void PromptWnds(HBG_PROMPT_TYPE type, LPCVOID pData);
	void UpdateWnds(HBG_UPDATE_TYPE type, LPCVOID pData);

private:
	void _Init();
	void _Unprompt();
	void _SetVisiblePage(CHbgPage* pPage);
	void _SetStatus(BOOL bPrompt, DWORD idThread = 0, DWORD_PTR curEip = 0);

private:
	CFont m_defFont;
	BOOL m_bPrompt;

	CHbgPage* m_pVisiblePage;

	DWORD m_curThreadID;
	CHbgPage* m_pCurPage;
	SIZE_T m_curIdx;

	std::vector<IHbgWndBase*> m_wnds;
};

#ifndef _DEBUG  // HbgMainView.cpp의 디버그 버전
inline CHbgMainDoc* CHbgMainView::GetDocument() const
   { return reinterpret_cast<CHbgMainDoc*>(m_pDocument); }
#endif

