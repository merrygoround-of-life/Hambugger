// HbgStackWnd.cpp : 구현 파일입니다.
//

#include "stdafx.h"

#include "HbgMain.h"
#include "HbgEngine/HbgEngine.h"
#include "HbgStackWnd.h"


static const SIZE_T s_dwSizeDefStruct = sizeof(SIZE_T);


IMPLEMENT_DYNAMIC(CHbgStackList, CListCtrl)

CHbgStackList::CHbgStackList()
:	m_curThread(0), m_curAddress(0), m_pData(NULL), m_sizeData(0)
{
}

CHbgStackList::~CHbgStackList()
{
	if (m_pData) {
		delete[] m_pData;
		m_pData = NULL;
	}
}

CHbgStackList::CHbgStackInfo::CHbgStackInfo()
:	id(0), baseAddress(0)
{
}

CHbgStackList::CHbgStackInfo::CHbgStackInfo(DWORD id)
:	id(id), baseAddress(0)
{
}

CHbgStackList::CHbgStackInfo::CHbgStackInfo(const HbgUpdate_Thread& threadInfo)
:	id(0), baseAddress(0)
{
	id = threadInfo.threadId;
	baseAddress = threadInfo.threadStackBase;
}

BOOL CHbgStackList::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	return CListCtrl::PreCreateWindow(cs);
}

int CHbgStackList::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	InsertColumn(0, L"주소", LVCFMT_LEFT, 100, 0);
	InsertColumn(1, L"값", LVCFMT_LEFT, 80, 0);

	return 0;
}

void CHbgStackList::OnLvnGetdispinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	
	LVITEM& item = pDispInfo->item;
	if (item.mask & LVIF_TEXT) {
		if (m_pData) {
			static CString tmpStrAddr;

			switch (item.iSubItem) {
				case 0:
					{
						tmpStrAddr.Format(HBGDEFFMT_ADDRSTR, m_curAddress + (item.iItem * s_dwSizeDefStruct));
						item.pszText = (LPWSTR)(LPCWSTR)tmpStrAddr;
					}
					break;
				case 1:
					{
						tmpStrAddr.Format(HBGDEFFMT_VALSTR, *(m_pData + item.iItem));
						item.pszText = (LPWSTR)(LPCWSTR)tmpStrAddr;
					}
					break;
			}
		}
	}

	*pResult = 0;
}

void CHbgStackList::AddStackPage(const HbgUpdate_Thread& threadInfo)
{
	m_stacks.insert(CHbgStackInfo(threadInfo));
}

void CHbgStackList::RemoveStackPage(DWORD id)
{
	CHbgStackInfo tmp(id);
	std::set<CHbgStackInfo, CHbgStackInfo>::iterator iter = m_stacks.find(tmp);
	if (iter != m_stacks.end()) {
		if ((*iter).id == id) {
			if (m_curThread == id) {
				m_curThread = 0;
				m_curAddress = 0;
			}
			m_stacks.erase(iter);
		}
	}
}

CHbgStackList::CHbgStackInfo* CHbgStackList::SetStackPage(DWORD id)
{
	std::set<CHbgStackInfo, CHbgStackInfo>::iterator iter = m_stacks.find(CHbgStackInfo(id));
	if (iter != m_stacks.end() && ((*iter).id == id)) {
		m_curThread = id;
		return &*iter;
	}

	return NULL;
}

BEGIN_MESSAGE_MAP(CHbgStackList, CListCtrl)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(LVN_GETDISPINFO, &CHbgStackList::OnLvnGetdispinfo)
END_MESSAGE_MAP()


// CHbgStackWnd

IMPLEMENT_DYNAMIC(CHbgStackWnd, CDockablePane)

CHbgStackWnd::CHbgStackWnd()
{

}

CHbgStackWnd::~CHbgStackWnd()
{
}


BEGIN_MESSAGE_MAP(CHbgStackWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// CHbgStackWnd 메시지 처리기입니다.



int CHbgStackWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	const DWORD dwStyle = LVS_REPORT | LVS_OWNERDATA | LVS_SHOWSELALWAYS | LVS_NOSORTHEADER | LVS_SINGLESEL | WS_CHILD | WS_VISIBLE | WS_VSCROLL;
	m_wndStackList.Create(dwStyle, rectDummy, this, 1);
	m_wndStackList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	m_fontStackWnd.CreatePointFont(80, L"돋움체");
	m_wndStackList.SetFont(&m_fontStackWnd);

	return 0;
}

void CHbgStackWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	m_wndStackList.SetWindowPos (NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}

void CHbgStackWnd::LinkMain(CHbgMainView* /*pHbgView*/, CHbgMainDoc* /*pHbgDoc*/)
{
}

void CHbgStackWnd::Reset()
{
	m_wndStackList.SetRedraw(FALSE);
	m_wndStackList.SetItemCount(0);
	m_wndStackList.SetRedraw();
	
	m_wndStackList.m_curThread = 0;
	m_wndStackList.m_curAddress = 0;

	if (m_wndStackList.m_pData) {
		delete[] m_wndStackList.m_pData;
		m_wndStackList.m_pData = NULL;
		m_wndStackList.m_sizeData = 0;
	}
}

void CHbgStackWnd::Enable(BOOL bEnable)
{
	if (!bEnable) {
		m_wndStackList.SetRedraw(FALSE);
		m_wndStackList.SetItemCount(0);
		m_wndStackList.SetRedraw();
	}

	//m_wndStackList.EnableWindow(bEnable);
}

void CHbgStackWnd::Prompt(HBG_PROMPT_TYPE /*type*/, LPCVOID pData)
{	
	HbgPrompt_General* pPromptInfo = (HbgPrompt_General*)pData;

	CHbgStackList::CHbgStackInfo* pCurStackInfo = NULL;
	if (m_wndStackList.m_curThread != pPromptInfo->idThread)
		pCurStackInfo = m_wndStackList.SetStackPage(pPromptInfo->idThread);

	if (pPromptInfo->pMemoryStack) {
		// Call From Server
		if (m_wndStackList.m_sizeData < pPromptInfo->szMemoryStack / sizeof(DWORD_PTR)) {
			m_wndStackList.m_sizeData = pPromptInfo->szMemoryStack / sizeof(DWORD_PTR);

			if (m_wndStackList.m_pData) {
				delete[] m_wndStackList.m_pData;
			}
			m_wndStackList.m_pData = new DWORD_PTR[pPromptInfo->szMemoryStack / sizeof(DWORD_PTR)];
		}
		m_wndStackList.m_sizeData = pPromptInfo->szMemoryStack / sizeof(DWORD_PTR);

		memcpy_s(m_wndStackList.m_pData, pPromptInfo->szMemoryStack, pPromptInfo->pMemoryStack, pPromptInfo->szMemoryStack);
		m_wndStackList.m_curAddress = HbgGetContextSP(pPromptInfo->context);

	} else if (pCurStackInfo) {
		// Call From User
		SIZE_T szMemoryStack = pCurStackInfo->baseAddress - HbgGetContextSP(pPromptInfo->context);

		if (m_wndStackList.m_sizeData < szMemoryStack / sizeof(DWORD_PTR)) {
			m_wndStackList.m_sizeData = szMemoryStack / sizeof(DWORD_PTR);

			if (m_wndStackList.m_pData) {
				delete[] m_wndStackList.m_pData;
			}
			m_wndStackList.m_pData = new DWORD_PTR[szMemoryStack / sizeof(DWORD_PTR)];
		}
		m_wndStackList.m_sizeData = szMemoryStack / sizeof(DWORD_PTR);

		static_cast<CHbgMainApp*>(AfxGetApp())->HbgGetEngine()->ReadMemory(HbgGetContextSP(pPromptInfo->context), m_wndStackList.m_sizeData * sizeof(DWORD_PTR), (LPBYTE)m_wndStackList.m_pData);
		m_wndStackList.m_curAddress = HbgGetContextSP(pPromptInfo->context);
	}

	m_wndStackList.SetRedraw(FALSE);
	m_wndStackList.SetItemCount((int)m_wndStackList.m_sizeData);
	m_wndStackList.SetRedraw();

	m_wndStackList.EnsureVisible(0, FALSE);
	m_wndStackList.SetItemState(0, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
}

void CHbgStackWnd::Update(HBG_UPDATE_TYPE type, LPCVOID pData)
{
	switch (type) {
		case HBG_UPDATE_TYPE_ADDTHREAD:
			m_wndStackList.AddStackPage(*(HbgUpdate_Thread*)pData);
			break;
		case HBG_UPDATE_TYPE_REMOVETHREAD:
			m_wndStackList.RemoveStackPage((HbgUpdate_RemoveThread_Id)pData);
			break;
	}
}
