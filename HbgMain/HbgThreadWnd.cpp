// HbgThreadWnd.cpp : 구현 파일입니다.
//

#include "stdafx.h"

#include "HbgMain.h"
#include "HbgMainView.h"
#include "HbgEngine/HbgEngine.h"
#include "HbgThreadWnd.h"


IMPLEMENT_DYNAMIC(CHbgThreadList, CListCtrl)

CHbgThreadList::CHbgThreadList()
:	m_curIdx((SIZE_T)-1), m_bEnable(FALSE), m_hMainView(NULL)
{
}

CHbgThreadList::~CHbgThreadList()
{
}

CHbgThreadList::CHbgThreadInfo::CHbgThreadInfo(const HbgUpdate_Thread& threadInfo)
:	startAddress(0)
{
	startAddress = threadInfo.threadStartAddress;

	curContext.idThread = threadInfo.threadId;
	curContext.eipCurrent = 0;
}

BOOL CHbgThreadList::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	return CListCtrl::PreCreateWindow(cs);
}

int CHbgThreadList::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	InsertColumn(0, L"ID", LVCFMT_LEFT, 50, 0);
	InsertColumn(1, L"현재 위치", LVCFMT_LEFT, 100, 0);
	InsertColumn(2, L"시작 위치", LVCFMT_LEFT, 100, 0);

	return 0;
}

void CHbgThreadList::OnLvnGetdispinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	
	LVITEM& item = pDispInfo->item;
	if (item.mask & LVIF_TEXT) {
		if (item.iItem < (int)m_threads.size()) {
			CHbgThreadInfo& curItem = m_threads.at(item.iItem);
			if (curItem.curContext.idThread) {
				static CString tmpStrAddr;

				switch (item.iSubItem) {
					case 0:
						{
							tmpStrAddr.Format(L"%d", curItem.curContext.idThread);
							item.pszText = (LPWSTR)(LPCWSTR)tmpStrAddr;
						}
						break;
					case 1:
						{
							if (curItem.curContext.eipCurrent) {
								tmpStrAddr.Format(HBGDEFFMT_ADDRSTR, curItem.curContext.eipCurrent);
								item.pszText = (LPWSTR)(LPCWSTR)tmpStrAddr;
							} else {
								item.pszText = L"";
							}
						}
						break;
					case 2:
						{
							tmpStrAddr.Format(HBGDEFFMT_ADDRSTR, curItem.startAddress);
							item.pszText = (LPWSTR)(LPCWSTR)tmpStrAddr;
						}
						break;
				}
			}
		}
	}

	*pResult = 0;
}

void CHbgThreadList::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLVCUSTOMDRAW pNMCD = reinterpret_cast<LPNMLVCUSTOMDRAW>(pNMHDR);
	
	*pResult = CDRF_DODEFAULT;

	if (m_bEnable && m_curIdx != -1) {
		switch (pNMCD->nmcd.dwDrawStage) {
			case CDDS_PREPAINT:
				{
					*pResult = CDRF_NOTIFYITEMDRAW;
				}
				break;
			case CDDS_ITEMPREPAINT:
				{
					if (pNMCD->nmcd.dwItemSpec == (DWORD_PTR)m_curIdx) {
						pNMCD->clrText = RGB(255, 127, 0);
					}
					*pResult = CDRF_NEWFONT;
				}
				break;
		}
	}
}

void CHbgThreadList::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (m_bEnable) {
		LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

		CHbgThreadInfo& selThread = m_threads.at(pNMItemActivate->iItem);
		::SendMessage(m_hMainView, HBG_WM_CHANGECONTEXT, (WPARAM)&selThread.curContext, NULL);
	}

	*pResult = 0;
}

void CHbgThreadList::AddItem(const HbgUpdate_Thread& threadInfo)
{
	m_threads.push_back(CHbgThreadInfo(threadInfo));
}

void CHbgThreadList::RemoveItem(SIZE_T id)
{
	DWORD idx = 0;
	std::vector<CHbgThreadInfo>::iterator iter = m_threads.begin();
	while (iter != m_threads.end()) {
		if ((*iter).curContext.idThread == id) {
			m_threads.erase(iter);
			break;
		}

		++iter;
		++idx;
	}
}

SIZE_T CHbgThreadList::FindItem(SIZE_T id) const
{
	SIZE_T idx = 0;
	for (idx = 0; idx < m_threads.size(); ++idx) {
		if (m_threads.at(idx).curContext.idThread == id)
			return idx;
	}

	return (SIZE_T)-1;
}

BEGIN_MESSAGE_MAP(CHbgThreadList, CListCtrl)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(LVN_GETDISPINFO, &CHbgThreadList::OnLvnGetdispinfo)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &CHbgThreadList::OnNMCustomdraw)
	ON_NOTIFY_REFLECT(NM_DBLCLK, &CHbgThreadList::OnNMDblclk)
END_MESSAGE_MAP()


// CHbgThreadWnd

IMPLEMENT_DYNAMIC(CHbgThreadWnd, CDockablePane)

CHbgThreadWnd::CHbgThreadWnd()
{

}

CHbgThreadWnd::~CHbgThreadWnd()
{
}


BEGIN_MESSAGE_MAP(CHbgThreadWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// CHbgThreadWnd 메시지 처리기입니다.



int CHbgThreadWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	const DWORD dwStyle = LVS_REPORT | LVS_OWNERDATA | LVS_SHOWSELALWAYS | LVS_NOSORTHEADER | LVS_SINGLESEL | WS_CHILD | WS_VISIBLE | WS_VSCROLL;
	m_wndThreadList.Create(dwStyle, rectDummy, this, 1);
	m_wndThreadList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	m_fontThreadWnd.CreatePointFont(80, L"돋움체");
	m_wndThreadList.SetFont(&m_fontThreadWnd);


	return 0;
}

void CHbgThreadWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	m_wndThreadList.SetWindowPos (NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}

void CHbgThreadWnd::LinkMain(CHbgMainView* pHbgView, CHbgMainDoc* /*pHbgDoc*/)
{
	m_wndThreadList.m_hMainView = pHbgView->GetSafeHwnd();
}

void CHbgThreadWnd::Reset()
{
	m_wndThreadList.SetRedraw(FALSE);
	m_wndThreadList.SetItemCount(0);
	m_wndThreadList.SetRedraw();
	m_wndThreadList.m_threads.clear();
	m_wndThreadList.m_curIdx = (SIZE_T)-1;
}

void CHbgThreadWnd::Enable(BOOL bEnable)
{
	if (!bEnable) {
		m_wndThreadList.SetRedraw(FALSE);
		m_wndThreadList.SetItemCount(0);
		m_wndThreadList.SetRedraw();
	}

	//m_wndThreadList.EnableWindow(bEnable);
	m_wndThreadList.m_bEnable = bEnable;
}

void CHbgThreadWnd::Prompt(HBG_PROMPT_TYPE /*type*/, LPCVOID pData)
{
	m_wndThreadList.SetRedraw(FALSE);
	m_wndThreadList.SetItemCount((DWORD)m_wndThreadList.m_threads.size());
	m_wndThreadList.SetRedraw();

	HbgPrompt_General* pPromptInfo = (HbgPrompt_General*)pData;

	SIZE_T nIdx = 0;
	SIZE_T nTotal = pPromptInfo->szHbgContexts / sizeof(HbgContext);
	while (nIdx < nTotal) {
		HbgContext& curContext = pPromptInfo->pHbgContexts[nIdx];

		SIZE_T nCurIdx = m_wndThreadList.FindItem(curContext.idThread);
		if (nCurIdx != ((SIZE_T)-1)) {
			m_wndThreadList.m_threads.at(nCurIdx).curContext = curContext;

			if (curContext.idThread == pPromptInfo->idThread) {
				SIZE_T nOldIdx = m_wndThreadList.m_curIdx;
				m_wndThreadList.m_curIdx = nCurIdx;
				m_wndThreadList.SetItemState((int)nCurIdx, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
				m_wndThreadList.EnsureVisible((int)nCurIdx, FALSE);
				m_wndThreadList.Update((int)nOldIdx);
				m_wndThreadList.Update((int)nCurIdx);
			}
		}

		++nIdx;
	}	
}

void CHbgThreadWnd::Update(HBG_UPDATE_TYPE type, LPCVOID pData)
{
	switch (type) {
		case HBG_UPDATE_TYPE_ADDTHREAD:
			m_wndThreadList.AddItem(*((HbgUpdate_Thread*)pData));
			break;
		case HBG_UPDATE_TYPE_REMOVETHREAD:
			m_wndThreadList.RemoveItem((HbgUpdate_RemoveThread_Id)pData);
			break;
	}
}
