
// HbgMainView.cpp : CHbgMainView 클래스의 구현
//

#include "stdafx.h"
#include <tlhelp32.h>
#include "afxcmn.h"
#include "HbgMain.h"

#include "HbgMainDoc.h"
#include "MainFrm.h"

#include "HbgEngine/HbgEngine.h"

#include "HbgDasm/include/HbgDasmInc.h"
#include "HbgDoc/HbgDocument.h"
#include "HbgPatchDialog.h"
#include "HbgWndBase.h"
#include "HbgMainView.h"


// CHbgInputPIDDlg
class CHbgInputPIDDlg : public CDialog
{
public:
	CHbgInputPIDDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_PID_DIALOG };

public:
	virtual BOOL OnInitDialog();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

public:
	afx_msg void OnBnClickedPidRefresh();
	afx_msg void OnLvnItemchangedPidList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkPidList(NMHDR *pNMHDR, LRESULT *pResult);

private:
	BOOL UpdateProcessList();

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()

public:
	DWORD m_pid;

private:
	CListCtrl m_listPid;
	CFont m_pidFont;
};

CHbgInputPIDDlg::CHbgInputPIDDlg() : CDialog(CHbgInputPIDDlg::IDD), m_pid(1)
{
}

BOOL CHbgInputPIDDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_pidFont.CreatePointFont(80, L"돋움체");

	m_listPid.SetFont(&m_pidFont);
	m_listPid.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	m_listPid.InsertColumn(0, L"PID", LVCFMT_LEFT, 50, 0);
	m_listPid.InsertColumn(1, L"프로그램", LVCFMT_LEFT, 150, 0);

	UpdateProcessList();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CHbgInputPIDDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PID_EDIT, m_pid);
	DDV_MinMaxUInt(pDX, m_pid, 1, 65535);
	DDX_Control(pDX, IDC_PID_LIST, m_listPid);
}

BEGIN_MESSAGE_MAP(CHbgInputPIDDlg, CDialog)
	ON_BN_CLICKED(IDC_PID_REFRESH, &CHbgInputPIDDlg::OnBnClickedPidRefresh)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_PID_LIST, &CHbgInputPIDDlg::OnLvnItemchangedPidList)
	ON_NOTIFY(NM_DBLCLK, IDC_PID_LIST, &CHbgInputPIDDlg::OnNMDblclkPidList)
END_MESSAGE_MAP()

void CHbgInputPIDDlg::OnBnClickedPidRefresh()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateProcessList();
}

void CHbgInputPIDDlg::OnLvnItemchangedPidList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString curItem = m_listPid.GetItemText( pNMLV->iItem, 0 );
	swscanf_s( curItem, L"%d", &m_pid );

	UpdateData( FALSE );
	*pResult = 0;
}

void CHbgInputPIDDlg::OnNMDblclkPidList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString curItem = m_listPid.GetItemText( pNMItemActivate->iItem, 0 );
	swscanf_s( curItem, L"%d", &m_pid );

	UpdateData( FALSE );
	*pResult = 0;

	OnOK();
}

BOOL CHbgInputPIDDlg::UpdateProcessList()
{
	BOOL bRtn = FALSE;
	m_listPid.DeleteAllItems();

	HANDLE hProcessSnap = ::CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
	if( INVALID_HANDLE_VALUE != hProcessSnap )
	{
		PROCESSENTRY32 pe32;
		pe32.dwSize = sizeof( PROCESSENTRY32 );

		if( FALSE != ::Process32First( hProcessSnap, &pe32 ) )
		{
			DWORD nIdx = 0;
			WCHAR pidBuf[10] = {0, };
			do
			{
				swprintf_s( pidBuf, L"%d", pe32.th32ProcessID );
				m_listPid.InsertItem( nIdx, pidBuf );
				m_listPid.SetItemText ( nIdx, 1, pe32.szExeFile );
				++nIdx;
			}
			while( FALSE != ::Process32Next( hProcessSnap, &pe32 ) );

			bRtn = TRUE;
		}

		CloseHandle( hProcessSnap );
		hProcessSnap = NULL;
	}

	return bRtn;
}


// CHbgInputAddrDlg
class CHbgInputAddrDlg : public CDialog
{
public:
	CHbgInputAddrDlg(DWORD_PTR eip);

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ADDRESS_DIALOG };

public:
	virtual BOOL OnInitDialog();

protected:
	virtual void OnOK();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()

private:
	CEdit m_addressEdit;

public:
	DWORD_PTR m_address;
};

CHbgInputAddrDlg::CHbgInputAddrDlg(DWORD_PTR eip)
:	CDialog(CHbgInputAddrDlg::IDD), m_address(eip)
{
}

BOOL CHbgInputAddrDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CString tmp;
	tmp.Format(HBGDEFFMT_ADDRSTR, m_address);
	m_addressEdit.SetWindowText(tmp);
	m_addressEdit.SetLimitText(sizeof(DWORD_PTR) * 2 + 2);
	//m_addressEdit.SetSel(2, -1);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CHbgInputAddrDlg::OnOK()
{
	CString tmp;
	m_addressEdit.GetWindowText(tmp);
	if (!_wcsnicmp(tmp, L"0x", 2))
		tmp = tmp.Mid(2);

	if (tmp.GetLength() > (sizeof(DWORD_PTR) * 2)) {
		m_addressEdit.SetWindowText(NULL);
	} else {
		DWORD_PTR tmpAddr = 0;
		if (swscanf_s(tmp, HBGDEFFMT_VALSTR, &tmpAddr))
			m_address = tmpAddr;
	}

	CDialog::OnOK();
}

void CHbgInputAddrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ADDRESS_EDIT, m_addressEdit);
}

BEGIN_MESSAGE_MAP(CHbgInputAddrDlg, CDialog)
END_MESSAGE_MAP()


// CHbgMainView

IMPLEMENT_DYNCREATE(CHbgMainView, CListView)

BEGIN_MESSAGE_MAP(CHbgMainView, CListView)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_NOTIFY_REFLECT(LVN_GETDISPINFO, &CHbgMainView::OnLvnGetdispinfo)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &CHbgMainView::OnNMCustomdraw)
	ON_COMMAND(ID_DEBUG_OPEN, &CHbgMainView::OnDebugOpen)
	ON_UPDATE_COMMAND_UI(ID_DEBUG_OPEN, &CHbgMainView::OnUpdateDebugOpen)
	ON_COMMAND(ID_DEBUG_ATTACH, &CHbgMainView::OnDebugAttach)
	ON_UPDATE_COMMAND_UI(ID_DEBUG_ATTACH, &CHbgMainView::OnUpdateDebugAttach)
	ON_COMMAND(ID_DEBUG_EXIT, &CHbgMainView::OnDebugExit)
	ON_UPDATE_COMMAND_UI(ID_DEBUG_EXIT, &CHbgMainView::OnUpdateDebugExit)
	ON_COMMAND(ID_DEBUG_DETACH, &CHbgMainView::OnDebugDetach)
	ON_UPDATE_COMMAND_UI(ID_DEBUG_DETACH, &CHbgMainView::OnUpdateDebugDetach)
	ON_COMMAND(ID_DEBUG_RESTART, &CHbgMainView::OnDebugRestart)
	ON_UPDATE_COMMAND_UI(ID_DEBUG_RESTART, &CHbgMainView::OnUpdateDebugRestart)
	ON_COMMAND(ID_DEBUG_PAUSE, &CHbgMainView::OnDebugPause)
	ON_UPDATE_COMMAND_UI(ID_DEBUG_PAUSE, &CHbgMainView::OnUpdateDebugPause)
	ON_COMMAND(ID_DEBUG_GO, &CHbgMainView::OnDebugGo)
	ON_UPDATE_COMMAND_UI(ID_DEBUG_GO, &CHbgMainView::OnUpdateDebugGo)
	ON_COMMAND(ID_DEBUG_STEPIN, &CHbgMainView::OnDebugStepIn)
	ON_UPDATE_COMMAND_UI(ID_DEBUG_STEPIN, &CHbgMainView::OnUpdateDebugStepIn)
	ON_COMMAND(ID_DEBUG_STEPOUT, &CHbgMainView::OnDebugStepOut)
	ON_UPDATE_COMMAND_UI(ID_DEBUG_STEPOUT, &CHbgMainView::OnUpdateDebugStepOut)
	ON_COMMAND(ID_DEBUG_RUN_TILL_CUR, &CHbgMainView::OnDebugRunTillCursor)
	ON_UPDATE_COMMAND_UI(ID_DEBUG_RUN_TILL_CUR, &CHbgMainView::OnUpdateDebugRunTillCursor)
	ON_COMMAND(ID_DEBUG_ORIGIN, &CHbgMainView::OnDebugOrigin)
	ON_UPDATE_COMMAND_UI(ID_DEBUG_ORIGIN, &CHbgMainView::OnUpdateDebugOrigin)
	ON_COMMAND(ID_DEBUG_MOVE, &CHbgMainView::OnDebugMove)
	ON_UPDATE_COMMAND_UI(ID_DEBUG_MOVE, &CHbgMainView::OnUpdateDebugMove)
	ON_COMMAND(ID_DEBUG_TOGGLE_BP, &CHbgMainView::OnDebugToggleBreakpoint)
	ON_UPDATE_COMMAND_UI(ID_DEBUG_TOGGLE_BP, &CHbgMainView::OnUpdateToggleBreakpoint)
	ON_COMMAND(ID_HBG_REGISTER, &CHbgMainView::OnHbgRegister)
	ON_UPDATE_COMMAND_UI(ID_HBG_REGISTER, &CHbgMainView::OnUpdateHbgRegister)
	ON_COMMAND(ID_HBG_UNREGISTER, &CHbgMainView::OnHbgUnregister)
	ON_UPDATE_COMMAND_UI(ID_HBG_UNREGISTER, &CHbgMainView::OnUpdateHbgUnregister)
	ON_MESSAGE(HBG_WM_PROMPT, &CHbgMainView::OnCallbackPrompt)
	ON_MESSAGE(HBG_WM_UPDATE, &CHbgMainView::OnCallbackUpdate)
	ON_MESSAGE(HBG_WM_CHANGEPAGE, &CHbgMainView::OnMsgChangePage)
	ON_MESSAGE(HBG_WM_CHANGECONTEXT, &CHbgMainView::OnMsgChangeContext)
	ON_NOTIFY_REFLECT(NM_DBLCLK, &CHbgMainView::OnNMDblclk)
END_MESSAGE_MAP()

// CHbgMainView 생성/소멸

CHbgMainView::CHbgMainView()
:	m_bPrompt(FALSE), m_pVisiblePage(NULL), m_curThreadID(0), m_pCurPage(NULL), m_curIdx(HbgNullIdx)
{
	// TODO: 여기에 생성 코드를 추가합니다.
}

CHbgMainView::~CHbgMainView()
{
}

BOOL CHbgMainView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.
	cs.style &= ~LVS_TYPEMASK;
	cs.style |= (LVS_REPORT | LVS_OWNERDATA | LVS_SHOWSELALWAYS | LVS_NOSORTHEADER | LVS_SINGLESEL);

	return CListView::PreCreateWindow(cs);
}

void CHbgMainView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	GetDocument()->SetMainView(this);
	static_cast<CHbgMainApp*>(AfxGetApp())->_ClbkHWnd(GetSafeHwnd());

	// Wnds
	RegisterWnds(static_cast<CMainFrame*>(AfxGetMainWnd())->GetRegisterWnd());
	RegisterWnds(static_cast<CMainFrame*>(AfxGetMainWnd())->GetMemoryWnd());
	RegisterWnds(static_cast<CMainFrame*>(AfxGetMainWnd())->GetBreakpointWnd());
	RegisterWnds(static_cast<CMainFrame*>(AfxGetMainWnd())->GetStackWnd());
	RegisterWnds(static_cast<CMainFrame*>(AfxGetMainWnd())->GetModuleWnd());
	RegisterWnds(static_cast<CMainFrame*>(AfxGetMainWnd())->GetThreadWnd());

	_Unprompt();
}

void CHbgMainView::OnRButtonUp(UINT /*nFlags*/, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CHbgMainView::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}

int CHbgMainView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CListView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CListCtrl& listctrl = GetListCtrl();

	m_defFont.CreatePointFont(80, L"돋움체");

	listctrl.SetFont(&m_defFont);
	listctrl.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	listctrl.InsertColumn(0, L"*", LVCFMT_LEFT, 20, 0);
	listctrl.InsertColumn(1, L"주소", LVCFMT_LEFT, 100, 0);
	listctrl.InsertColumn(2, L"명령어", LVCFMT_LEFT, 200, 0);
	listctrl.InsertColumn(3, L"디스어셈블리", LVCFMT_LEFT, 300, 0);
	
	return 0;
}

void CHbgMainView::OnClose()
{
	_Init();

	CListView::OnClose();
}

void CHbgMainView::OnLvnGetdispinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	
	LVITEM& item = pDispInfo->item;
	if (item.mask & LVIF_TEXT) {
		if (m_pVisiblePage) {
			const CHbgInstruction* pCurItem = m_pVisiblePage->GetOpItem(item.iItem);
			if (pCurItem) {
				switch (item.iSubItem) {
					case 0:
						{
							m_pVisiblePage->LoadRegion(item.iItem);

							if (m_pVisiblePage == m_pCurPage && m_curIdx == (SIZE_T)item.iItem && m_bPrompt)
								item.pszText = L"★";
							else
								item.pszText = L"";
						}
						break;
					case 1:
						{
							static CString tmpStrAddr;
							tmpStrAddr.Format(HBGDEFFMT_ADDRSTR, pCurItem->GetAddress());
							item.pszText = (LPWSTR)(LPCWSTR)tmpStrAddr;
						}
						break;
					case 2:
						{
							CHbgInstructionData* pCurData = pCurItem->GetData();
							_ASSERT(pCurData);
							item.pszText = (pCurData) ? (pCurData->GetOpcode()) : L"";
						}
						break;
					case 3:
						{
							CHbgInstructionData* pCurData = pCurItem->GetData();
							_ASSERT(pCurData);
							item.pszText = (pCurData) ? (pCurData->GetDisasm()) : L"";
						}
						break;
				}
			}
		}
	}

	*pResult = 0;
}

void CHbgMainView::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLVCUSTOMDRAW pNMCD = reinterpret_cast<LPNMLVCUSTOMDRAW>(pNMHDR);
	
	*pResult = CDRF_DODEFAULT;
	switch (pNMCD->nmcd.dwDrawStage) {
		case CDDS_PREPAINT:
			{
				*pResult = CDRF_NOTIFYITEMDRAW;
			}
			break;
		case CDDS_ITEMPREPAINT:
			{
				if (m_pVisiblePage) {
					const CHbgInstruction* pCurItem = m_pVisiblePage->GetOpItem(pNMCD->nmcd.dwItemSpec);
					if (pCurItem && GetDocument()->GetImpl()->FindBP(pCurItem->GetAddress())) {
						pNMCD->clrText = RGB(255, 255, 255);
						pNMCD->clrTextBk = RGB(255, 0, 0);
					}
				}
				*pResult = CDRF_NOTIFYSUBITEMDRAW;
			}
			break;
		case CDDS_SUBITEM | CDDS_ITEMPREPAINT:
			{
				if (m_pVisiblePage && m_pVisiblePage == m_pCurPage) {
					if (pNMCD->nmcd.dwItemSpec == m_curIdx && m_bPrompt) 
						pNMCD->clrText = RGB(255, 127, 0);
				}
				*pResult = CDRF_NEWFONT;
			}
			break;
	}
}

void CHbgMainView::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (m_bPrompt) {
		LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

		if (pNMItemActivate && m_pVisiblePage) {
			const CHbgInstruction* pCurItem = m_pVisiblePage->GetOpItem(pNMItemActivate->iItem);
			if (pCurItem) {
				CHbgPatchDialog dlg(this, pCurItem->GetAddress());

				if (dlg.DoModal() == IDOK) {
					CListCtrl& listctrl = GetListCtrl();
					listctrl.SetRedraw(FALSE);

					m_pVisiblePage->Clear();
					m_pVisiblePage->LoadInit();
					listctrl.SetItemCount((int)m_pVisiblePage->GetItemCount());

					listctrl.SetRedraw();
				}
			}
		}
	}

	*pResult = 0;
}


// CHbgMainView 진단

#ifdef _DEBUG
void CHbgMainView::AssertValid() const
{
	CListView::AssertValid();
}

void CHbgMainView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CHbgMainDoc* CHbgMainView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHbgMainDoc)));
	return (CHbgMainDoc*)m_pDocument;
}
#endif //_DEBUG


// CHbgMainView 메시지 처리기

void CHbgMainView::OnDebugOpen()
{
	CFileDialog dlg(TRUE, NULL, 0, 4|2, L"실행파일 (*.exe)|*.exe|", this);
	if (dlg.DoModal() == IDOK) {
		CWaitCursor wait;
		_Init();

		CString newFilePath = dlg.GetPathName();
		GetDocument()->NewDocument(newFilePath);
		if (!static_cast<CHbgMainApp*>(AfxGetApp())->HbgGetEngine()->Initialize(newFilePath, 0))
			OnDebugExit();
	}
	
	_Unprompt();
}

void CHbgMainView::OnUpdateDebugOpen(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(!static_cast<CHbgMainApp*>(AfxGetApp())->HbgGetEngine()->Running());
}

void CHbgMainView::OnDebugAttach()
{
	CHbgInputPIDDlg pidDlg;
	if (pidDlg.DoModal() == IDOK && pidDlg.m_pid) {
		CWaitCursor wait;
		_Init();

		GetDocument()->NewDocument(NULL, pidDlg.m_pid);
		if (!static_cast<CHbgMainApp*>(AfxGetApp())->HbgGetEngine()->Initialize(NULL, pidDlg.m_pid))
			OnDebugExit();
	}

	_Unprompt();
}

void CHbgMainView::OnUpdateDebugAttach(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(!static_cast<CHbgMainApp*>(AfxGetApp())->HbgGetEngine()->Running());
}

void CHbgMainView::OnDebugExit()
{
	CWaitCursor wait;

	static_cast<CHbgMainApp*>(AfxGetApp())->HbgGetEngine()->Uninitialize(TRUE);
	_Init();
	GetDocument()->NewDocument();
}

void CHbgMainView::OnUpdateDebugExit(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(static_cast<CHbgMainApp*>(AfxGetApp())->HbgGetEngine()->Running());
}

void CHbgMainView::OnDebugDetach()
{
	CWaitCursor wait;

	static_cast<CHbgMainApp*>(AfxGetApp())->HbgGetEngine()->Uninitialize(FALSE);
	_Init();
	GetDocument()->NewDocument();
}

void CHbgMainView::OnUpdateDebugDetach(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(static_cast<CHbgMainApp*>(AfxGetApp())->HbgGetEngine()->Running());
}

void CHbgMainView::OnDebugRestart()
{
	CString curFilePath = GetDocument()->GetFilePath();
	DWORD curProcessID = GetDocument()->GetProcessID();

	// 1) 기존 동작 종료
	OnDebugExit();

	// 2) 기존 파일로 시작
	if (!curFilePath.IsEmpty()) {
		GetDocument()->NewDocument(curFilePath);
		if (!static_cast<CHbgMainApp*>(AfxGetApp())->HbgGetEngine()->Initialize(curFilePath, 0))
			OnDebugExit();
	} else if (curProcessID) {
		GetDocument()->NewDocument(NULL, curProcessID);
		if (!static_cast<CHbgMainApp*>(AfxGetApp())->HbgGetEngine()->Initialize(NULL, curProcessID))
			OnDebugExit();
	}

	_Unprompt();
}

void CHbgMainView::OnUpdateDebugRestart(CCmdUI *pCmdUI)
{
	BOOL bEnable = (static_cast<CHbgMainApp*>(AfxGetApp())->HbgGetEngine()->Running()) || (GetDocument()->GetFilePath());
	pCmdUI->Enable(bEnable);
}

void CHbgMainView::OnDebugPause()
{
	CWaitCursor wait;

	_Unprompt();
	static_cast<CHbgMainApp*>(AfxGetApp())->HbgGetEngine()->Break();
}

void CHbgMainView::OnUpdateDebugPause(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(static_cast<CHbgMainApp*>(AfxGetApp())->HbgGetEngine()->Running() && !m_bPrompt);
}

void CHbgMainView::OnDebugGo()
{
	CWaitCursor wait;

	_Unprompt();
	static_cast<CHbgMainApp*>(AfxGetApp())->HbgGetEngine()->Go(0);
}

void CHbgMainView::OnUpdateDebugGo(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_bPrompt);
}

void CHbgMainView::OnDebugStepIn()
{
	CWaitCursor wait;

	_Unprompt();
	static_cast<CHbgMainApp*>(AfxGetApp())->HbgGetEngine()->Step(m_curThreadID);
}

void CHbgMainView::OnUpdateDebugStepIn(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_bPrompt);
}

void CHbgMainView::OnDebugStepOut()
{
	CWaitCursor wait;

	_Unprompt();
	BOOL bCall = FALSE;
	if (m_pCurPage && (m_curIdx != HbgNullIdx) && (m_curIdx < m_pCurPage->GetItemCount())) {
		const CHbgInstruction* pCurItem = m_pCurPage->GetOpItem(m_curIdx);
		if (pCurItem) {
			CHbgInstructionData* pCurData = pCurItem->GetData();
			if (pCurData && pCurData->GetCharacters() & HBGDASM_CHAR_CALL) {
				DWORD_PTR nextAddr = 0;
				if (m_pCurPage && ((m_curIdx + 1) < m_pCurPage->GetItemCount())) {
					const CHbgInstruction* pNextItem = m_pCurPage->GetOpItem(m_curIdx + 1);
					if (pNextItem) {
						nextAddr = pNextItem->GetAddress();
						static_cast<CHbgMainApp*>(AfxGetApp())->HbgGetEngine()->Go(nextAddr);
						bCall = TRUE;
					}
				}
			}
		}
	}
	
	if (!bCall)
		OnDebugStepIn();
}

void CHbgMainView::OnUpdateDebugStepOut(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_bPrompt);
}

void CHbgMainView::OnDebugRunTillCursor()
{
	CWaitCursor wait;

	_Unprompt();
	
	SIZE_T curIdx = GetListCtrl().GetNextItem(0, LVIS_SELECTED);
	if (m_pVisiblePage && (curIdx != (SIZE_T)-1)) {
		DWORD_PTR nextAddr = 0;

		const CHbgInstruction* pCurItem = m_pVisiblePage->GetOpItem(curIdx);
		if (pCurItem) {
			nextAddr = pCurItem->GetAddress();
			static_cast<CHbgMainApp*>(AfxGetApp())->HbgGetEngine()->Go(nextAddr);
		}
	}
}

void CHbgMainView::OnUpdateDebugRunTillCursor(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_bPrompt);
}

void CHbgMainView::OnDebugOrigin()
{
	CWaitCursor wait;

	_SetVisiblePage(m_pCurPage);
	SetFocus();
}

void CHbgMainView::OnUpdateDebugOrigin(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_bPrompt);
}

void CHbgMainView::OnDebugMove()
{
	DWORD_PTR eip = 0;
	SIZE_T curIdx = GetListCtrl().GetNextItem(0, LVIS_SELECTED);
	if (m_pVisiblePage && (curIdx != (SIZE_T)-1)) {
		const CHbgInstruction* pCurItem = m_pVisiblePage->GetOpItem(curIdx);
		if (pCurItem)
			eip = pCurItem->GetAddress();
	}

	CHbgInputAddrDlg dlg(eip);
	if (dlg.DoModal() == IDOK)
		::SendMessage(GetSafeHwnd(), HBG_WM_CHANGEPAGE, (WPARAM)dlg.m_address, NULL);
}

void CHbgMainView::OnUpdateDebugMove(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_bPrompt);
}

void CHbgMainView::OnDebugToggleBreakpoint()
{
	CWaitCursor wait;

	DWORD_PTR bpAddr = 0;
	CListCtrl& listctrl = GetListCtrl();

	SIZE_T curIdx = listctrl.GetNextItem(0, LVIS_SELECTED);
	if (m_pVisiblePage && (curIdx != (SIZE_T)-1)) {
		const CHbgInstruction* pCurItem = m_pVisiblePage->GetOpItem(curIdx);
		if (pCurItem) {
			bpAddr = pCurItem->GetAddress();
			BOOL bSet;
			static_cast<CHbgMainApp*>(AfxGetApp())->HbgGetEngine()->ToggleBreakpoint(bpAddr, &bSet);

			if (bSet)
				GetDocument()->GetImpl()->AddBP(bpAddr);
			else
				GetDocument()->GetImpl()->RemoveBP(bpAddr);

			// 중단점 창만 Update
			static_cast<CMainFrame*>(AfxGetMainWnd())->GetBreakpointWnd()->Update((HBG_UPDATE_TYPE)NULL, NULL);
		}
	}
}

void CHbgMainView::OnUpdateToggleBreakpoint(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(static_cast<CHbgMainApp*>(AfxGetApp())->HbgGetEngine()->Running());
}

void CHbgMainView::OnHbgRegister()
{
	BOOL bSucceeded = FALSE;

	SHELLEXECUTEINFO sei = { sizeof(SHELLEXECUTEINFO) };
	sei.lpVerb = L"runas";
	sei.nShow = SW_SHOWNORMAL;

	WCHAR szModulePath[_MAX_PATH] = {0, };	
	::GetModuleFileName(NULL, szModulePath, _MAX_PATH );
	LPWSTR pLastDept = wcsrchr(szModulePath, L'\\');
	if(NULL == pLastDept)
	{
		// undefined error
		::GetCurrentDirectory(_MAX_PATH, szModulePath);
		pLastDept = wcsrchr(szModulePath, L'\\');
	}

	// 1) HbgServ
	*(pLastDept + 1) = L'\0';
	wcscat_s(szModulePath, HBG_HBGSERV L".exe");
	sei.lpFile = szModulePath;
	sei.lpParameters = L"-regserver";
	if (ShellExecuteEx(&sei)) {

		// 2) HbgMain
		*(pLastDept + 1) = L'\0';
		wcscat_s(szModulePath, HBG_HBGMAIN L".exe");
		sei.lpFile = szModulePath;
		sei.lpParameters = L"-regserver";
		if (ShellExecuteEx(&sei))
			bSucceeded = TRUE;
	}

	_ASSERT(bSucceeded);
}

void CHbgMainView::OnUpdateHbgRegister(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(!static_cast<CHbgMainApp*>(AfxGetApp())->HbgGetEngine()->Running());
}

void CHbgMainView::OnHbgUnregister()
{
	BOOL bSucceeded = FALSE;

	SHELLEXECUTEINFO sei = { sizeof(SHELLEXECUTEINFO) };
	sei.lpVerb = L"runas";
	sei.nShow = SW_SHOWNORMAL;

	// 1) HbgServ
	sei.lpFile = HBG_HBGSERV L".exe";
	sei.lpParameters = L"-unregserver";
	if (ShellExecuteEx(&sei)) {

		// 2) HbgMain
		sei.lpFile = HBG_HBGMAIN L".exe";
		sei.lpParameters = L"-unregserver";
		if (ShellExecuteEx(&sei))
			bSucceeded = TRUE;
	}

	_ASSERT(bSucceeded);
}

void CHbgMainView::OnUpdateHbgUnregister(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(!static_cast<CHbgMainApp*>(AfxGetApp())->HbgGetEngine()->Running());
}

LRESULT CHbgMainView::OnCallbackPrompt(WPARAM wParam, LPARAM lParam)
{
	HBG_PROMPT_TYPE typePrompt = (HBG_PROMPT_TYPE)wParam;
	HbgPrompt_General* pPromptInfo = (HbgPrompt_General*)lParam;

	m_bPrompt = (typePrompt == HBG_PROMPT_TYPE_TERMINATE) ? FALSE : TRUE;

	// 1) NainView 처리
	SIZE_T oldIdx = m_curIdx;
	if (GetDocument()->SetCurEIP(HbgGetContextIP(pPromptInfo->context), m_pCurPage, m_curIdx)) {
		m_curThreadID = pPromptInfo->idThread;
		if (oldIdx != m_curIdx)
			GetListCtrl().RedrawItems((int)oldIdx, (int)oldIdx);
	
		_SetVisiblePage(m_pCurPage);
	}

	// 2) Wnds 처리
	PromptWnds(typePrompt, (LPCVOID)pPromptInfo);
	EnableWnds(TRUE);

	if (typePrompt == HBG_PROMPT_TYPE_TERMINATE)
		static_cast<CHbgMainApp*>(AfxGetApp())->HbgGetEngine()->Uninitialize(TRUE, FALSE);

	_SetStatus(TRUE, m_curThreadID, HbgGetContextIP(pPromptInfo->context));

	SetFocus();

	return 0;
}

LRESULT CHbgMainView::OnCallbackUpdate(WPARAM wParam, LPARAM lParam)
{
	// 1) NainView 처리
	HBG_UPDATE_TYPE typeUpdate = (HBG_UPDATE_TYPE)wParam;
	switch (typeUpdate) {
		case HBG_UPDATE_TYPE_ADDMODULE:
			GetDocument()->AddPage((HbgUpdate_Module*)lParam);
			break;
		case HBG_UPDATE_TYPE_REMOVEMODULE:
			GetDocument()->RemovePage(lParam);
			break;
	}

	// 2) Wnds 처리
	UpdateWnds((HBG_UPDATE_TYPE)wParam, (LPCVOID)lParam);

	return 0;
}

LRESULT CHbgMainView::OnMsgChangePage(WPARAM wParam, LPARAM /*lParam*/)
{
	SIZE_T addr = wParam;

	CHbgPage* pSelPage = NULL;
	SIZE_T selIdx = 0;
	if (GetDocument()->SetCurEIP(addr, pSelPage, selIdx)) {
		_SetVisiblePage(pSelPage);

		CListCtrl& listctrl = GetListCtrl();
		listctrl.SetItemState((int)selIdx, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
		listctrl.EnsureVisible((int)selIdx, FALSE);

		SetFocus();
	}

	return 0;
}

LRESULT CHbgMainView::OnMsgChangeContext(WPARAM wParam, LPARAM /*lParam*/)
{
	HbgContext* pCurContext = (HbgContext*)wParam;

	SIZE_T oldIdx = m_curIdx;
	if (GetDocument()->SetCurEIP(pCurContext->eipCurrent, m_pCurPage, m_curIdx)) {

		m_curThreadID = pCurContext->idThread;
		if (oldIdx != m_curIdx)
			GetListCtrl().RedrawItems((int)oldIdx, (int)oldIdx);

		_SetVisiblePage(m_pCurPage);

		CONTEXT curContext;
		static_cast<CHbgMainApp*>(AfxGetApp())->HbgGetEngine()->ReadContext(m_curThreadID, sizeof(curContext), (LPBYTE)&curContext);

		HbgPrompt_General tmpPromptInfo = { pCurContext->idThread, curContext, 0, NULL, sizeof(HbgContext), pCurContext };
		PromptWnds(HBG_PROMPT_TYPE_GENERAL, (LPCVOID)&tmpPromptInfo);
		EnableWnds(TRUE);

		_SetStatus(TRUE, m_curThreadID, pCurContext->eipCurrent);

		SetFocus();
	}

	return 0;
}

void CHbgMainView::RegisterWnds(IHbgWndBase* pWnd)
{
	if (pWnd) {
		pWnd->LinkMain(this, GetDocument());
		m_wnds.push_back(pWnd);
	}
}

void CHbgMainView::ResetWnds()
{
	std::vector<IHbgWndBase*>::iterator iter = m_wnds.begin();
	while (iter != m_wnds.end()) {
		(*iter)->Reset();

		++iter;
	}
}

void CHbgMainView::EnableWnds(BOOL bEnable)
{
	std::vector<IHbgWndBase*>::iterator iter = m_wnds.begin();
	while (iter != m_wnds.end()) {
		(*iter)->Enable(bEnable);

		++iter;
	}
}

void CHbgMainView::PromptWnds(HBG_PROMPT_TYPE type, LPCVOID pData)
{
	std::vector<IHbgWndBase*>::iterator iter = m_wnds.begin();
	while (iter != m_wnds.end()) {
		(*iter)->Prompt(type, pData);

		++iter;
	}
}

void CHbgMainView::UpdateWnds(HBG_UPDATE_TYPE type, LPCVOID pData)
{
	std::vector<IHbgWndBase*>::iterator iter = m_wnds.begin();
	while (iter != m_wnds.end()) {
		(*iter)->Update(type, pData);

		++iter;
	}
}

void CHbgMainView::_Init()
{
	m_pVisiblePage = NULL;
	m_curThreadID = 0;
	m_pCurPage = NULL;
	m_curIdx = HbgNullIdx;

	_Unprompt();
	
	CListCtrl& listctrl = GetListCtrl();

	//listctrl.DeleteAllItems();
	listctrl.SetRedraw(FALSE);
	listctrl.SetItemCount(0);
	listctrl.SetRedraw();
	
	ResetWnds();
}

void CHbgMainView::_Unprompt()
{
	m_bPrompt = FALSE;
	EnableWnds(FALSE);

	_SetStatus(FALSE);
}

void CHbgMainView::_SetVisiblePage(CHbgPage* pPage)
{
	if (pPage) {
		CListCtrl& listctrl = GetListCtrl();

		// Page 처리
		if (m_pVisiblePage != pPage) {
			m_pVisiblePage = pPage;
			m_pVisiblePage->LoadInit();

			listctrl.SetRedraw(FALSE);
			listctrl.SetItemCount((int)m_pVisiblePage->GetItemCount());
			listctrl.SetRedraw();
		}

		// Selection/CurEIP 처리
		if (m_pVisiblePage != m_pCurPage) {
			if (m_curIdx != HbgNullIdx)
				listctrl.RedrawItems((int)m_curIdx, (int)m_curIdx);

			listctrl.RedrawItems(0, 0);
			listctrl.SetItemState(0, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
			listctrl.EnsureVisible(0, FALSE);
		} else {
			SIZE_T oldSelIdx = listctrl.GetNextItem(0, LVIS_SELECTED);
			if (oldSelIdx != (SIZE_T)-1)
				listctrl.RedrawItems((int)oldSelIdx, (int)oldSelIdx);

			SIZE_T idxSel = (m_curIdx != HbgNullIdx) ? m_curIdx : 0;
			listctrl.RedrawItems((int)idxSel, (int)idxSel);
			listctrl.SetItemState((int)idxSel, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
			listctrl.EnsureVisible((int)idxSel, FALSE);
		}
	}
}

void CHbgMainView::_SetStatus(BOOL bPrompt, DWORD idThread/*= 0*/, DWORD_PTR curEip/*= 0*/)
{
	if (static_cast<CHbgMainApp*>(AfxGetApp())->HbgGetEngine()->Running()) {
		if (bPrompt) {
			CString templateStr(L"대기중 [스레드:%04d] ");
			templateStr.Append(HBGDEFFMT_ADDRSTR);
			CString tmpStr;
			tmpStr.Format(templateStr, idThread, curEip);
			static_cast<CMainFrame*>(AfxGetMainWnd())->GetStatusBar()->SetPaneText(1, tmpStr);
		} else {
			static_cast<CMainFrame*>(AfxGetMainWnd())->GetStatusBar()->SetPaneText(1, L"실행중");
		}
	} else {
		static_cast<CMainFrame*>(AfxGetMainWnd())->GetStatusBar()->SetPaneText(1, L"중단");
	}
}
