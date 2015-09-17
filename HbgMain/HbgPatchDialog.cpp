// HbgPatchDialog.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "HbgMain.h"
#include "HbgEngine/HbgEngine.h"
#include "HbgDasm/include/HbgDasmInc.h"
#include "HbgBase/HbgMemPtr.h"
#include "HbgPatchDialog.h"



IMPLEMENT_DYNAMIC(CHbgPatchEdit1, CEdit)

CHbgPatchEdit1::CHbgPatchEdit1(BOOL bCode)
:	m_bCode(bCode)
{
}

CHbgPatchEdit1::~CHbgPatchEdit1()
{
}


BEGIN_MESSAGE_MAP(CHbgPatchEdit1, CEdit)
END_MESSAGE_MAP()


// CHbgPatchDialog 대화 상자입니다.

IMPLEMENT_DYNAMIC(CHbgPatchDialog, CDialog)

CHbgPatchDialog::CHbgPatchDialog(CWnd* pParent, DWORD_PTR address, BOOL bCode/*= TRUE*/)
	: CDialog(CHbgPatchDialog::IDD, pParent), m_editPatch(bCode), m_editInfo(bCode), m_address(address), m_bCode(bCode)
{

}

CHbgPatchDialog::~CHbgPatchDialog()
{
}

void CHbgPatchDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PATCH_EDIT, m_editPatch);
	DDX_Control(pDX, IDC_INFO_EDIT, m_editInfo);
}

BOOL CHbgPatchDialog::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN) {
		// 실수를 막기 위해..
		if (pMsg->wParam >= L'G' && pMsg->wParam <= L'Z')
			return TRUE;
	}

	return CDialog::PreTranslateMessage(pMsg);;
}

void CHbgPatchDialog::OnOK()
{
	CString strPatch;
	m_editPatch.GetWindowText(strPatch);
	DWORD lenPatch = strPatch.GetLength() / 2;

	CHbgMemPtr bufData(lenPatch);
	_Convert(strPatch, bufData);

	static_cast<CHbgMainApp*>(AfxGetApp())->HbgGetEngine()->WriteMemory(m_address, lenPatch, bufData);

	CDialog::OnOK();
}


BEGIN_MESSAGE_MAP(CHbgPatchDialog, CDialog)
	ON_EN_CHANGE(IDC_PATCH_EDIT, &CHbgPatchDialog::OnEnChangeEditPatch)
END_MESSAGE_MAP()


// CHbgPatchDialog 메시지 처리기입니다.

BOOL CHbgPatchDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 1) title
	CString title;
	GetWindowText(title);
	CString tmpAddr;
	CString templateStr(L" [");
	templateStr.Append(HBGDEFFMT_ADDRSTR);
	templateStr.Append(L"]");
	tmpAddr.Format(templateStr, m_address);
	title.Append(tmpAddr);	
	SetWindowText(title);

	// 2) Static
	if (m_bCode)
		GetDlgItem(IDC_PATCH_STATIC2)->SetWindowText(L"Disassemble:");
	else
		GetDlgItem(IDC_PATCH_STATIC2)->SetWindowText(L"ASCII:");

	// 3) font
	m_fontPatchEdit.CreatePointFont(80, L"Verdana Bold");
	m_editPatch.SetFont(&m_fontPatchEdit);
	m_editPatch.SetLimitText(HBGDASM_BUFLEN);
	m_editInfo.SetFont(&m_fontPatchEdit);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CHbgPatchDialog::OnEnChangeEditPatch()
{
	CString strInput, strOnput;
	m_editPatch.GetWindowText(strInput);
	SIZE_T lenInput = strInput.GetLength();

	if (!lenInput) {
		m_editInfo.SetWindowText(NULL);
		return;
	}

	if (!(lenInput % 2)) {
		SIZE_T lenBuf = lenInput / 2;
		CHbgMemPtr bufData(lenBuf);
		_Convert(strInput, bufData);

		SIZE_T nRead = 0;
		if (m_bCode) {
			HbgDasmInfo dasmInfo;
			SIZE_T sz = 0;

			while (nRead < lenBuf) {
				HbgDasmInit(dasmInfo, HBGDASM_OPT_RETLENGTH | HBGDASM_OPT_GETDASM/* | HBGDASM_OPT_GETOPCODE*/, bufData + nRead, lenBuf - nRead, m_address);

				sz = HbgDasmParse(dasmInfo);
				if (!sz)
					break;

				if (nRead)
					strOnput.Append(L"\r\n");

				nRead += sz;
				strOnput.Append(dasmInfo.dasm);
			}
		} else {
			while (nRead < lenBuf) {
				WCHAR tmpChar[2] = {0, 0};
				*tmpChar = *(bufData + nRead);

				++nRead;

				if (*tmpChar < 0x0080) {
					if ((*tmpChar >= 0x0021) && (*tmpChar <= 0x007E))
						strOnput.Append(tmpChar);
					else
						strOnput.Append(L".");
				} else {
					strOnput.Append(L"?");
				}

			}
		}

		m_editInfo.SetWindowText(strOnput);
	}
}

void CHbgPatchDialog::_Convert(const CString& src, CHbgMemPtr& buf)
{
	LPBYTE pBuf = buf;
	LPCWSTR pStart = src;
	LPWSTR pEnd = NULL;
	DWORD lenInput = src.GetLength();

	DWORD curPos = 0;
	while (curPos < lenInput) {
		CString partStr(pStart + curPos, 2);
		*pBuf = (BYTE)wcstoul(partStr, &pEnd, 16);

		curPos += 2;
		++pBuf;
	}
}
