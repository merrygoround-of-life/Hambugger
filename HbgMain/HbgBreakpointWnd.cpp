// HbgBreakpointWnd.cpp : 구현 파일입니다.
//

#include "stdafx.h"

#include "HbgMain.h"
#include "HbgMainView.h"
#include "HbgMainDoc.h"
#include "HbgDoc/HbgDocument.h"
#include "HbgBreakpointWnd.h"


IMPLEMENT_DYNAMIC(CHbgBreakpointList, CListCtrl)

CHbgBreakpointList::CHbgBreakpointList()
:	m_bEnable(FALSE), m_hMainView(NULL), m_pHbgDoc(NULL)
{
}

CHbgBreakpointList::~CHbgBreakpointList()
{
}

BOOL CHbgBreakpointList::PreCreateWindow(CREATESTRUCT& cs)
{
	return CListCtrl::PreCreateWindow(cs);
}

int CHbgBreakpointList::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	InsertColumn(0, L"주소", LVCFMT_LEFT, 200, 0);

	return 0;
}

void CHbgBreakpointList::OnLvnGetdispinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	
	LVITEM& item = pDispInfo->item;

	CHbgDocument* pHbgDocImpl = NULL;
	if (m_pHbgDoc)
		pHbgDocImpl = m_pHbgDoc->GetImpl();
	
	if (pHbgDocImpl) {
		const std::vector<DWORD_PTR> &listBPs = pHbgDocImpl->_GetListBPs();
		if (pHbgDocImpl && (item.iItem < (int)listBPs.size())) {
			static CString tmpStrAddr;
			tmpStrAddr.Format(HBGDEFFMT_ADDRSTR, listBPs.at(item.iItem));
			item.pszText = (LPWSTR)(LPCWSTR)tmpStrAddr;
		}
	}

	*pResult = 0;
}

void CHbgBreakpointList::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (m_bEnable) {
		LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

		if (m_pHbgDoc && m_pHbgDoc->GetImpl()) {
			const std::vector<DWORD_PTR> &listBPs = m_pHbgDoc->GetImpl()->_GetListBPs();
			if ((pNMItemActivate->iItem < (int)listBPs.size()))
				::SendMessage(m_hMainView, HBG_WM_CHANGEPAGE, (WPARAM)listBPs.at(pNMItemActivate->iItem), NULL);
		}
	}

	*pResult = 0;
}


BEGIN_MESSAGE_MAP(CHbgBreakpointList, CListCtrl)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(LVN_GETDISPINFO, &CHbgBreakpointList::OnLvnGetdispinfo)
	ON_NOTIFY_REFLECT(NM_DBLCLK, &CHbgBreakpointList::OnNMDblclk)
END_MESSAGE_MAP()


// CHbgBreakpointWnd

IMPLEMENT_DYNAMIC(CHbgBreakpointWnd, CDockablePane)

CHbgBreakpointWnd::CHbgBreakpointWnd()
{

}

CHbgBreakpointWnd::~CHbgBreakpointWnd()
{
}


BEGIN_MESSAGE_MAP(CHbgBreakpointWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// CHbgBreakpointWnd 메시지 처리기입니다.



int CHbgBreakpointWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	const DWORD dwStyle = LVS_REPORT | LVS_OWNERDATA | LVS_NOCOLUMNHEADER | LVS_SINGLESEL | WS_CHILD | WS_VISIBLE | WS_VSCROLL;
	m_wndBreakpointList.Create(dwStyle, rectDummy, this, 1);
	m_wndBreakpointList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	m_fontBreakpointWnd.CreatePointFont(80, L"돋움체");
	m_wndBreakpointList.SetFont(&m_fontBreakpointWnd);
	m_wndBreakpointList.SetItemCount(0);

	return 0;
}

void CHbgBreakpointWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	m_wndBreakpointList.SetWindowPos (NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}

void CHbgBreakpointWnd::LinkMain(CHbgMainView* pHbgView, CHbgMainDoc* pHbgDoc)
{
	m_wndBreakpointList.m_hMainView = pHbgView->GetSafeHwnd();
	m_wndBreakpointList.m_pHbgDoc = pHbgDoc;
}

void CHbgBreakpointWnd::Reset()
{
	m_wndBreakpointList.SetRedraw(FALSE);
	m_wndBreakpointList.SetItemCount(0);
	m_wndBreakpointList.SetRedraw();
}

void CHbgBreakpointWnd::Enable(BOOL bEnable)
{
	//m_wndBreakpointList.EnableWindow(bEnable);
	m_wndBreakpointList.m_bEnable = bEnable;
}

void CHbgBreakpointWnd::Prompt(HBG_PROMPT_TYPE /*type*/, LPCVOID /*pData*/)
{
	CHbgDocument* pHbgDocImpl = NULL;
	if (m_wndBreakpointList.m_pHbgDoc)
		pHbgDocImpl= m_wndBreakpointList.m_pHbgDoc->GetImpl();

	if (pHbgDocImpl) {
		int countBPs = (int)pHbgDocImpl->_GetListBPs().size();
		if (m_wndBreakpointList.GetItemCount() != countBPs) {
			m_wndBreakpointList.SetRedraw(FALSE);
			m_wndBreakpointList.SetItemCount(countBPs);
			m_wndBreakpointList.SetRedraw();
		}
	}
}

void CHbgBreakpointWnd::Update(HBG_UPDATE_TYPE /*type*/, LPCVOID /*pData*/)
{
	CHbgDocument* pHbgDocImpl = NULL;
	if (m_wndBreakpointList.m_pHbgDoc)
		pHbgDocImpl= m_wndBreakpointList.m_pHbgDoc->GetImpl();

	if (pHbgDocImpl) {
		int countBPs = (int)pHbgDocImpl->_GetListBPs().size();
		if (m_wndBreakpointList.GetItemCount() != countBPs) {
			m_wndBreakpointList.SetRedraw(FALSE);
			m_wndBreakpointList.SetItemCount(countBPs);
			m_wndBreakpointList.SetRedraw();
		}
	}
}
