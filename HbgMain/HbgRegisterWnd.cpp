// HbgRegisterWnd.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "HbgMain.h"
#include "HbgMainView.h"
#include "HbgEngine/HbgEngine.h"
#include "HbgRegisterWnd.h"


IMPLEMENT_DYNAMIC(CHbgRegisterItemList, CListCtrl)

CHbgRegisterItemList::CHbgRegisterItemList()
{
	memset(&m_context, 0, sizeof(m_context));
}

CHbgRegisterItemList::~CHbgRegisterItemList()
{
}

CHbgRegisterItemList::CHbgRegisterItem::CHbgRegisterItem(const IHbgRegProc* pRegObj)
:	m_pRegObj(pRegObj)
{
}

BOOL CHbgRegisterItemList::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	return CListCtrl::PreCreateWindow(cs);
}

int CHbgRegisterItemList::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	InsertColumn(0, L"종류", LVCFMT_LEFT, 50, 0);
	InsertColumn(1, L"값", LVCFMT_LEFT, 200, 0);

	Initialize();

	return 0;
}

void CHbgRegisterItemList::OnLvnGetdispinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	
	LVITEM& item = pDispInfo->item;
	if (item.mask & LVIF_TEXT) {
		if (item.iItem < (int)m_regItems.size()) {

			CHbgRegisterItem& curItem = m_regItems.at(item.iItem);

			static std::wstring tmpStrBuf;

			switch (item.iSubItem) {
				case 0:
					{
						item.pszText = (LPWSTR)curItem.m_pRegObj->GetName();
					}
					break;
				case 1:
					{
						if (curItem.m_pRegObj->Read(tmpStrBuf, m_context))
							item.pszText = (LPWSTR)tmpStrBuf.c_str();
					}
					break;
			}
		}
	}

	*pResult = 0;
}

void CHbgRegisterItemList::OnLvnBeginlabeledit(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (!m_bEnable) {
		*pResult = 1;
		return;
	}

	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);	
	LVITEM& item = pDispInfo->item;
	if (item.iItem < (int)m_regItems.size()) {

		CHbgRegisterItem& curItem = m_regItems.at(item.iItem);
		
		std::wstring tmpStrBuf;
		if (curItem.m_pRegObj->Read(tmpStrBuf, m_context))
			GetEditControl()->SetWindowText(tmpStrBuf.c_str());
	}

	*pResult = 0;
}

void CHbgRegisterItemList::OnLvnEndlabeledit(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	LVITEM& item = pDispInfo->item;
	
	if (item.pszText) {
		CHbgRegisterItem& curItem = m_regItems.at(item.iItem);

		CONTEXT context;
		if (static_cast<CHbgMainApp*>(AfxGetApp())->HbgGetEngine()->ReadContext(m_idThread, sizeof(context), (LPBYTE)&context)) {

			std::wstring tmpStrBuf(item.pszText);
			if (curItem.m_pRegObj->Write(tmpStrBuf, context)) {
				if (static_cast<CHbgMainApp*>(AfxGetApp())->HbgGetEngine()->WriteContext(m_idThread, sizeof(context), (LPBYTE)&context)) {
					m_context = context;

					HbgContext hbgContext = { m_idThread, HbgGetContextIP(context) };
					::SendMessage(m_hMainView, HBG_WM_CHANGECONTEXT, (WPARAM)&hbgContext, NULL);
				}
			}
		}
	}

	*pResult = 0;
}

void CHbgRegisterItemList::Initialize()
{
	DWORD idx = 0;
	while (idx < _HbgReg_COUNT) {
		_HbgRegItem* pCurItem = HbgGetRegItem(idx);
		_ASSERT(pCurItem);
		if (pCurItem) {
			CHbgRegisterItem curItem(pCurItem->pObj);
			m_regItems.push_back(curItem);
		}
		
		++idx;
	}

	SetRedraw(FALSE);
	SetItemCount((int)m_regItems.size());
	SetRedraw();
}

BEGIN_MESSAGE_MAP(CHbgRegisterItemList, CListCtrl)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(LVN_GETDISPINFO, &CHbgRegisterItemList::OnLvnGetdispinfo)
	ON_NOTIFY_REFLECT(LVN_BEGINLABELEDIT, &CHbgRegisterItemList::OnLvnBeginlabeledit)
	ON_NOTIFY_REFLECT(LVN_ENDLABELEDIT, &CHbgRegisterItemList::OnLvnEndlabeledit)
END_MESSAGE_MAP()


// CHbgRegisterWnd

IMPLEMENT_DYNAMIC(CHbgRegisterWnd, CDockablePane)

CHbgRegisterWnd::CHbgRegisterWnd()
{
}

CHbgRegisterWnd::~CHbgRegisterWnd()
{
}


BEGIN_MESSAGE_MAP(CHbgRegisterWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CHbgRegisterWnd 메시지 처리기입니다.


int CHbgRegisterWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	const DWORD dwStyle = LVS_REPORT | LVS_OWNERDATA | LVS_SHOWSELALWAYS | LVS_NOSORTHEADER | LVS_SINGLESEL | LVS_EDITLABELS | WS_CHILD | WS_VISIBLE | WS_VSCROLL;

	m_wndRegItemList.Create(dwStyle, rectDummy, this, 1);
	m_wndRegItemList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	m_fontRegisterWnd.CreatePointFont(80, L"돋움체");
	m_wndRegItemList.SetFont(&m_fontRegisterWnd);

	return 0;
}

void CHbgRegisterWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	
	m_wndRegItemList.SetWindowPos (NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}

void CHbgRegisterWnd::LinkMain(CHbgMainView* pHbgView, CHbgMainDoc* /*pHbgDoc*/)
{
	m_wndRegItemList.m_hMainView = pHbgView->GetSafeHwnd();
}

void CHbgRegisterWnd::Reset()
{
	CONTEXT context;
	memset(&context, 0, sizeof(context));

	SetRegisters(0, context);
}

void CHbgRegisterWnd::Enable(BOOL bEnable)
{
	m_wndRegItemList.m_bEnable = bEnable;
}

void CHbgRegisterWnd::Prompt(HBG_PROMPT_TYPE /*type*/, LPCVOID pData)
{
	HbgPrompt_General* pPromptInfo = (HbgPrompt_General*)pData;
	SetRegisters(pPromptInfo->idThread, pPromptInfo->context);
}

void CHbgRegisterWnd::Update(HBG_UPDATE_TYPE /*type*/, LPCVOID /*pData*/)
{
}

void CHbgRegisterWnd::SetRegisters(const DWORD id, const CONTEXT& context)
{
	m_wndRegItemList.m_idThread = id;
	m_wndRegItemList.m_context = context;

	m_wndRegItemList.RedrawItems(0, (int)m_wndRegItemList.m_regItems.size());
}
