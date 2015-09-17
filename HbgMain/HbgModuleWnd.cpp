// HbgModuleWnd.cpp : 구현 파일입니다.
//

#include "stdafx.h"

#include "HbgMain.h"
#include "HbgMainView.h"
#include "HbgModuleWnd.h"


IMPLEMENT_DYNAMIC(CHbgModuleList, CListCtrl)

CHbgModuleList::CHbgModuleList()
:	m_curIdx((SIZE_T)-1), m_newIdx(0), m_bEnable(FALSE), m_hMainView(NULL), m_pHbgDoc(NULL)
{
}

CHbgModuleList::~CHbgModuleList()
{
}

CHbgModuleList::CHbgModuleInfo::CHbgModuleInfo(SIZE_T order, const HbgUpdate_Module& moduleInfo)
:	idx(0), addressStart(0), addressEnd(0), addressCodeStart(0), addressCodeEnd(0)
{
	idx = order;
	addressStart = moduleInfo.addressStart;
	addressEnd = moduleInfo.addressEnd;
	addressCodeStart = moduleInfo.addressCodeStart;
	addressCodeEnd = moduleInfo.addressCodeEnd;
	if (moduleInfo.path) {
		path = moduleInfo.path;

		WCHAR fName[_MAX_FNAME] = {0, };
		WCHAR fExt[_MAX_EXT] = {0, };

		_wsplitpath_s(moduleInfo.path, NULL, NULL, NULL, NULL, fName, _MAX_FNAME, fExt, _MAX_EXT);
		name.append(fName);
		name.append(fExt);
	}
}

BOOL CHbgModuleList::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	return CListCtrl::PreCreateWindow(cs);
}

int CHbgModuleList::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	InsertColumn(0, L"순서", LVCFMT_LEFT, 40, 0);
	InsertColumn(1, L"이름", LVCFMT_LEFT, 90, 0);
	InsertColumn(2, L"주소", LVCFMT_LEFT, 160, 0);
	InsertColumn(3, L"경로", LVCFMT_LEFT, 210, 0);

	return 0;
}

void CHbgModuleList::OnLvnGetdispinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	
	LVITEM& item = pDispInfo->item;
	if (item.mask & LVIF_TEXT) {
		if (item.iItem < (int)m_modules.size()) {

			CHbgModuleInfo& curItem = m_modules.at(item.iItem);

			static CString tmpStrAddr;

			switch (item.iSubItem) {
				case 0:
					{
						tmpStrAddr.Format(L"%d", curItem.idx);
						item.pszText = (LPWSTR)(LPCWSTR)tmpStrAddr;
					}
					break;
				case 1:
					{
						item.pszText = (LPWSTR)curItem.name.c_str();
					}
					break;
				case 2:
					{
						CString templateStr(HBGDEFFMT_ADDRSTR);
						templateStr.Append(L" - ");
						templateStr.Append(HBGDEFFMT_ADDRSTR);
						tmpStrAddr.Format(templateStr, curItem.addressStart, curItem.addressEnd);
						item.pszText = (LPWSTR)(LPCWSTR)tmpStrAddr;
					}
					break;
				case 3:
					{
						item.pszText = (LPWSTR)curItem.path.c_str();
					}
					break;
			}
		}
	}

	*pResult = 0;
}

void CHbgModuleList::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)
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
					if (pNMCD->nmcd.dwItemSpec == m_curIdx) {
						pNMCD->clrText = RGB(255, 127, 0);
					}
					*pResult = CDRF_NEWFONT;
				}
				break;
		}
	}
}

void CHbgModuleList::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (m_bEnable) {
		LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

		CHbgModuleInfo& selModule = m_modules.at(pNMItemActivate->iItem);
		::SendMessage(m_hMainView, HBG_WM_CHANGEPAGE, (WPARAM)selModule.addressCodeStart, NULL);
	}

	*pResult = 0;
}

void CHbgModuleList::AddItem(const HbgUpdate_Module& moduleInfo)
{
	++m_newIdx;
	CHbgModuleInfo curItem(m_newIdx, moduleInfo);
	m_modules.push_back(curItem);
}

void CHbgModuleList::RemoveItem(DWORD_PTR baseAddr)
{
	std::vector<CHbgModuleInfo>::iterator iter = m_modules.begin();
	while (iter != m_modules.end()) {
		if ((*iter).addressStart == baseAddr) {
			m_modules.erase(iter);
			break;
		}

		++iter;
	}
}

SIZE_T CHbgModuleList::FindItem(DWORD_PTR addr) const
{
	SIZE_T idx = 0;
	for (idx = 0; idx < m_modules.size(); ++idx) {
		if (m_modules.at(idx).addressCodeStart <= addr && m_modules.at(idx).addressCodeEnd >= addr)
			return idx;
	}

	return (SIZE_T)-1;
}


BEGIN_MESSAGE_MAP(CHbgModuleList, CListCtrl)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(LVN_GETDISPINFO, &CHbgModuleList::OnLvnGetdispinfo)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &CHbgModuleList::OnNMCustomdraw)
	ON_NOTIFY_REFLECT(NM_DBLCLK, &CHbgModuleList::OnNMDblclk)
END_MESSAGE_MAP()


// CHbgModuleWnd

IMPLEMENT_DYNAMIC(CHbgModuleWnd, CDockablePane)

CHbgModuleWnd::CHbgModuleWnd()
{

}

CHbgModuleWnd::~CHbgModuleWnd()
{
}


BEGIN_MESSAGE_MAP(CHbgModuleWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// CHbgModuleWnd 메시지 처리기입니다.



int CHbgModuleWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	const DWORD dwStyle = LVS_REPORT | LVS_OWNERDATA | LVS_SHOWSELALWAYS | LVS_NOSORTHEADER | LVS_SINGLESEL | WS_CHILD | WS_VISIBLE | WS_VSCROLL;
	m_wndModuleList.Create(dwStyle, rectDummy, this, 1);
	m_wndModuleList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	m_fontModuleWnd.CreatePointFont(80, L"돋움체");
	m_wndModuleList.SetFont(&m_fontModuleWnd);


	return 0;
}

void CHbgModuleWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	m_wndModuleList.SetWindowPos (NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}

void CHbgModuleWnd::LinkMain(CHbgMainView* pHbgView, CHbgMainDoc* /*pHbgDoc*/)
{
	m_wndModuleList.m_hMainView = pHbgView->GetSafeHwnd();
}

void CHbgModuleWnd::Reset()
{
	m_wndModuleList.SetRedraw(FALSE);
	m_wndModuleList.SetItemCount(0);
	m_wndModuleList.SetRedraw();
	m_wndModuleList.m_modules.clear();
	m_wndModuleList.m_curIdx = (SIZE_T)-1;
	m_wndModuleList.m_newIdx = 0;
}

void CHbgModuleWnd::Enable(BOOL bEnable)
{
	//m_wndModuleList.EnableWindow(bEnable);
	m_wndModuleList.m_bEnable = bEnable;
}

void CHbgModuleWnd::Prompt(HBG_PROMPT_TYPE /*type*/, LPCVOID pData)
{
	HbgPrompt_General* pPromptInfo = (HbgPrompt_General*)pData;

	m_wndModuleList.m_curIdx = m_wndModuleList.FindItem(HbgGetContextIP(pPromptInfo->context));
	if (m_wndModuleList.m_curIdx != (SIZE_T)-1) {
		m_wndModuleList.SetItemState((int)m_wndModuleList.m_curIdx, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
		m_wndModuleList.EnsureVisible((int)m_wndModuleList.m_curIdx, FALSE);
	}
}

void CHbgModuleWnd::Update(HBG_UPDATE_TYPE type, LPCVOID pData)
{
	switch (type) {
		case HBG_UPDATE_TYPE_ADDMODULE:
			m_wndModuleList.SetRedraw(FALSE);
			m_wndModuleList.AddItem(*((HbgUpdate_Module*)pData));
			m_wndModuleList.SetItemCount((int)m_wndModuleList.m_modules.size());
			m_wndModuleList.SetRedraw();
			break;
		case HBG_UPDATE_TYPE_REMOVEMODULE:
			m_wndModuleList.SetRedraw(FALSE);
			m_wndModuleList.RemoveItem((HbgUpdate_RemovePage_AddrStart)pData);
			m_wndModuleList.SetItemCount((int)m_wndModuleList.m_modules.size());
			m_wndModuleList.SetRedraw();
			break;
	}
}
