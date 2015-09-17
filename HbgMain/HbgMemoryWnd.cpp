// HbgMemoryWnd.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "HbgMain.h"
#include "HbgEngine/HbgEngine.h"
#include "HbgPatchDialog.h"
#include "HbgMemoryWnd.h"


IMPLEMENT_DYNAMIC(CHbgCurrentAddressComboBox, CComboBox)

CHbgCurrentAddressComboBox::CHbgCurrentAddressComboBox()
{
	m_strTemplete = HBGDEFFMT_ADDRSTR;
}

CHbgCurrentAddressComboBox::~CHbgCurrentAddressComboBox()
{
}

void CHbgCurrentAddressComboBox::SetCurrent(DWORD_PTR addr)
{
	CString tmp;
	tmp.Format(m_strTemplete, addr);
	SetWindowText(tmp);
	SetEditSel(0, -1);

	if (GetCount() > 10)
		DeleteString(9);
	InsertString(0, tmp);
}

BEGIN_MESSAGE_MAP(CHbgCurrentAddressComboBox, CComboBox)
END_MESSAGE_MAP()


IMPLEMENT_DYNAMIC(CHbgMemoryEdit, CEdit)

CHbgMemoryEdit::CHbgMemoryEdit()
{
	m_strAddrTemplete = HBGDEFFMT_ADDRSTR;
	m_strByteTemplete = HbgFmtValStr_1byte;
	m_strAsciiTemplete = L"%s";
}

CHbgMemoryEdit::~CHbgMemoryEdit()
{
}

void CHbgMemoryEdit::SetCurrent(DWORD_PTR addr)
{
	const UINT totalByte = 0x1000;
	BYTE buf[totalByte];
	memset(buf, 0, totalByte);

	const UINT defSize = 0x10;

	static CString templateStr(L"");
	if (templateStr.IsEmpty()) {
		templateStr = HBGDEFFMT_ADDRSTR;
		templateStr.Append(L"\t");
		DWORD sz = defSize;
		while (sz--) {
			templateStr.Append(L" ");
			templateStr.Append(HbgFmtValStr_1byte);
		}
		templateStr.Append(L"\t%s\r\n");
	}

	if (static_cast<CHbgMainApp*>(AfxGetApp())->HbgGetEngine()->ReadMemory(addr, totalByte, buf)) {

		CString tmp;
		
		CString final;
		UINT nPtr = 0;
		while (nPtr < totalByte) {
			UINT nCUrPtr = nPtr;
			if (nPtr + defSize > totalByte)
				break;

			CString tmp2;
			WCHAR tmpChar[2] = {0, 0};
			BYTE lp = 0;
			while (lp < defSize) {
				*tmpChar = buf[nCUrPtr + lp];
				if (*tmpChar < 0x80) {
					if ((*tmpChar >= 0x0021) && (*tmpChar <= 0x007E))
						tmp2.Append(tmpChar);
					else
						tmp2.Append(L".");
				} else {
					tmp2.Append(L"?");
				}

				++lp;
			}

			tmp.Format(templateStr, addr + nPtr,
				buf[nCUrPtr], buf[nCUrPtr + 1], buf[nCUrPtr + 2], buf[nCUrPtr + 3], buf[nCUrPtr + 4], buf[nCUrPtr + 5], buf[nCUrPtr + 6], buf[nCUrPtr + 7],
				buf[nCUrPtr + 8], buf[nCUrPtr + 9], buf[nCUrPtr + 10], buf[nCUrPtr + 11], buf[nCUrPtr + 12], buf[nCUrPtr + 13], buf[nCUrPtr + 14], buf[nCUrPtr + 15], tmp2);

			final.Append(tmp);
			nPtr += defSize;
		}

		SetWindowText(final);
	}
}


BEGIN_MESSAGE_MAP(CHbgMemoryEdit, CEdit)
END_MESSAGE_MAP()


// CHbgMemoryWnd

IMPLEMENT_DYNAMIC(CHbgMemoryWnd, CDockablePane)

CHbgMemoryWnd::CHbgMemoryWnd()
:	m_bEnable(FALSE)
{
}

CHbgMemoryWnd::~CHbgMemoryWnd()
{
}

BOOL CHbgMemoryWnd::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN) {
		if (pMsg->wParam == VK_RETURN) {
			DWORD_PTR curAddr = 0;
			if (_FixedAddress(curAddr)) {
				m_wndCurrentAddress.SetCurrent(curAddr);
				m_wndMemoryEdit.SetCurrent(curAddr);
			} else {
				m_wndCurrentAddress.SetCurrent(NULL);
			}
		}
	}

	return __super::PreTranslateMessage(pMsg);
}


BEGIN_MESSAGE_MAP(CHbgMemoryWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_BN_CLICKED(3, &CHbgMemoryWnd::OnClickedButton)
	ON_UPDATE_COMMAND_UI(3, &CHbgMemoryWnd::OnUpdateButton)
END_MESSAGE_MAP()

void CHbgMemoryWnd::AdjustLayout()
{
	CRect rectClient, rectCombo;
	GetClientRect(rectClient);

	int cxStaticButton = 40;

	m_wndCurrentAddress.GetWindowRect(&rectCombo);
	int cyCmb = rectCombo.Size().cy;

	m_wndStatic.SetWindowPos(NULL, rectClient.left, rectClient.top, cxStaticButton, cyCmb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndCurrentAddress.SetWindowPos(NULL, rectClient.left + cxStaticButton, rectClient.top, rectClient.Width() - cxStaticButton * 2, 200, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndButton.SetWindowPos(NULL, rectClient.Width() - cxStaticButton, rectClient.top, cxStaticButton, cyCmb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndMemoryEdit.SetWindowPos (NULL, rectClient.left, rectClient.top + cyCmb, rectClient.Width(), rectClient.Height() - cyCmb, SWP_NOACTIVATE | SWP_NOZORDER);
}


// CHbgMemoryWnd 메시지 처리기입니다.



int CHbgMemoryWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	m_fontMemoryWnd.CreatePointFont(80, L"돋움체");

	// 1) static
	const DWORD dwTmpStyle = SS_CENTER | SS_CENTERIMAGE | WS_CHILD | WS_VISIBLE;
	m_wndStatic.Create(L"주소", dwTmpStyle, rectDummy, this, 1);
	m_wndStatic.SetFont(&m_fontMemoryWnd);

	// 2) combo
	const DWORD dwComboStyle = CBS_DROPDOWN | WS_CHILD | WS_VISIBLE | WS_BORDER;
	m_wndCurrentAddress.Create(dwComboStyle, rectDummy, this, 2);
	m_wndCurrentAddress.SetFont(&m_fontMemoryWnd);

	// 3) button
	const DWORD dwButonStyle = BS_PUSHBUTTON | BS_CENTER | BS_VCENTER | WS_CHILD | WS_VISIBLE;
	m_wndButton.Create(L"패치", dwButonStyle, rectDummy, this, 3);
	m_wndButton.SetFont(&m_fontMemoryWnd);

	// 4) edit
	const DWORD dwEditStyle = ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL;
	m_wndMemoryEdit.Create(dwEditStyle, rectDummy, this, 4);
	m_wndMemoryEdit.SetFont(&m_fontMemoryWnd);

	AdjustLayout();

	return 0;
}

void CHbgMemoryWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	AdjustLayout();
}

void CHbgMemoryWnd::OnClickedButton()
{
	DWORD_PTR curAddr = 0;
	_FixedAddress(curAddr);
	CHbgPatchDialog dlg(this, curAddr, FALSE);

	if (dlg.DoModal() == IDOK) {
		m_wndMemoryEdit.SetCurrent(curAddr);
	}
}

void CHbgMemoryWnd::OnUpdateButton(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_bEnable);
}

void CHbgMemoryWnd::LinkMain(CHbgMainView* /*pHbgView*/, CHbgMainDoc* /*pHbgDoc*/)
{
}

void CHbgMemoryWnd::Reset()
{
	m_wndCurrentAddress.SetWindowText(NULL);
	m_wndMemoryEdit.SetWindowText(NULL);
}

void CHbgMemoryWnd::Enable(BOOL bEnable)
{
	m_bEnable = bEnable;
	if (!bEnable)
		m_wndMemoryEdit.SetWindowText(NULL);

	m_wndCurrentAddress.EnableWindow(bEnable);
	//m_wndMemoryEdit.EnableWindow(bEnable);
}

void CHbgMemoryWnd::Prompt(HBG_PROMPT_TYPE /*type*/, LPCVOID /*pData*/)
{
}

void CHbgMemoryWnd::Update(HBG_UPDATE_TYPE /*type*/, LPCVOID /*pData*/)
{
}

BOOL CHbgMemoryWnd::_FixedAddress(DWORD_PTR& addr)
{
	CString tmp;
	m_wndCurrentAddress.GetWindowText(tmp);
	if (!_wcsnicmp(tmp, L"0x", 2))
		tmp = tmp.Mid(2);

	int len = tmp.GetLength();
	if (len >= 0 && len <= (sizeof(DWORD_PTR) * 2)) {
		if (swscanf_s(tmp, HBGDEFFMT_VALSTR, &addr))
			return TRUE;
	}

	return FALSE;
}
