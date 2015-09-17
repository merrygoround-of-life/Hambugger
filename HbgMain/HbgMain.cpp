
// HbgMain.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "HbgMain.h"
#include "MainFrm.h"

#include "HbgEngine/HbgEngine.h"
#include "HbgBase/HbgDebug_h.h"
#include "HbgBase/HbgProxyStub.h"
#include "HbgBase/HbgMessageFilter.h"
#include "HbgMainDoc.h"
#include "HbgMainView.h"
#include "HbgOLE/HbgMainOleFactory.h"


#if defined(_WIN64)
#	ifdef _DEBUG
		// {35803C60-E010-45a9-B13F-F30BE72ABD64}
		static const GUID CLSID_HbgMain = 
		{ 0x35803c60, 0xe010, 0x45a9, { 0xb1, 0x3f, 0xf3, 0xb, 0xe7, 0x2a, 0xbd, 0x64 } };
#	else
		// {35803C60-E010-45a9-B13F-F30BE72AB564}
		static const GUID CLSID_HbgMain = 
		{ 0x35803c60, 0xe010, 0x45a9, { 0xb1, 0x3f, 0xf3, 0xb, 0xe7, 0x2a, 0xb5, 0x64 } };
#	endif // _DEBUG
#elif defined(_WIN32)
#	ifdef _DEBUG
		// {35803C60-E010-45a9-B13F-F30BE72ABD86}
		static const GUID CLSID_HbgMain = 
		{ 0x35803c60, 0xe010, 0x45a9, { 0xb1, 0x3f, 0xf3, 0xb, 0xe7, 0x2a, 0xbd, 0x86 } };
#	else
		// {35803C60-E010-45a9-B13F-F30BE72AB586}
		static const GUID CLSID_HbgMain = 
		{ 0x35803c60, 0xe010, 0x45a9, { 0xb1, 0x3f, 0xf3, 0xb, 0xe7, 0x2a, 0xb5, 0x86 } };
#	endif // _DEBUG
#endif


static const GUID CLSID_HbgSvPS = IID_IHbgDebug;
DWORD g_dwCookieSvPS = 0;


static const LPCWSTR s_regFrameVerSection = L"FrameVersion";


void RegisterClassObject();
void RevokeClassObject();
void _SetRegKeyValue(LPTSTR pszKey, LPTSTR pszSubkey, LPTSTR pszValueName, LPTSTR pszValue);


DWORD g_dwRegister = 0;
CHbgMainFactory* g_pFactory = NULL;
//LPMESSAGEFILTER pOldMsgFilter = NULL;


// CHbgMainApp

BEGIN_MESSAGE_MAP(CHbgMainApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CHbgMainApp::OnAppAbout)
	// ǥ�� ������ ���ʷ� �ϴ� ���� ����Դϴ�.
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
END_MESSAGE_MAP()

// CHbgMainApp ����

CHbgMainApp::CHbgMainApp()
{
	m_bHiColorIcons = TRUE;

	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}

// ������ CHbgMainApp ��ü�Դϴ�.

CHbgMainApp theApp;

//CHbgMessageFilter hbgMsgFilter;


// CHbgMainApp �ʱ�ȭ
BOOL CHbgMainApp::InitInstance()
{
	// ���� ���α׷� �Ŵ��佺Ʈ�� ComCtl32.dll ���� 6 �̻��� ����Ͽ� ���־� ��Ÿ����
	// ����ϵ��� �����ϴ� ���, Windows XP �󿡼� �ݵ�� InitCommonControlsEx()�� �ʿ��մϴ�. 
	// InitCommonControlsEx()�� ������� ������ â�� ���� �� �����ϴ�.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ���� ���α׷����� ����� ��� ���� ��Ʈ�� Ŭ������ �����ϵ���
	// �� �׸��� �����Ͻʽÿ�.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	// ǥ�� �ʱ�ȭ
	// �̵� ����� ������� �ʰ� ���� ���� ������ ũ�⸦ ���̷���
	// �Ʒ����� �ʿ� ���� Ư�� �ʱ�ȭ
	// ��ƾ�� �����ؾ� �մϴ�.
	// �ش� ������ ����� ������Ʈ�� Ű�� �����Ͻʽÿ�.
	// TODO: �� ���ڿ��� ȸ�� �Ǵ� ������ �̸��� ����
	// ������ �������� �����ؾ� �մϴ�.

#if defined(_DEBUG)
	SetRegistryKey(_T(HBG_COMPANYNAME) _T("\\") _T("Dev\\") _T(HBG_PRODUCTNAME) _T("\\") _T(HBG_PLATFORM));
#else
	SetRegistryKey(_T(HBG_COMPANYNAME) _T("\\") _T(HBG_PRODUCTNAME) _T("\\") _T(HBG_PLATFORM));
#endif // _DEBUG

	LoadStdProfileSettings(4);  // MRU�� �����Ͽ� ǥ�� INI ���� �ɼ��� �ε��մϴ�.

	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// ���� ���α׷��� ���� ���ø��� ����մϴ�. ���� ���ø���
	//  ����, ������ â �� �� ������ ���� ������ �մϴ�.
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CHbgMainDoc),
		RUNTIME_CLASS(CMainFrame),       // �� SDI ������ â�Դϴ�.
		RUNTIME_CLASS(CHbgMainView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// DDE Execute ���⸦ Ȱ��ȭ�մϴ�.
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// ǥ�� �� ���, DDE, ���� ���⿡ ���� ������� ���� �м��մϴ�.
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);


	// ����ٿ� ������ ����� ����ġ�մϴ�.
	// ���� ���α׷��� /RegServer, /Register, /Unregserver �Ǵ� /Unregister�� ���۵� ��� FALSE�� ��ȯ�մϴ�.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// â �ϳ��� �ʱ�ȭ�Ǿ����Ƿ� �̸� ǥ���ϰ� ������Ʈ�մϴ�.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// ���̻簡 ���� ��쿡�� DragAcceptFiles�� ȣ���մϴ�.
	//  SDI ���� ���α׷������� ProcessShellCommand �Ŀ� �̷��� ȣ���� �߻��ؾ� �մϴ�.
	// ��� ���⿡ ���� ���⸦ Ȱ��ȭ�մϴ�.
	m_pMainWnd->DragAcceptFiles();
	
	::CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

	//HRESULT hr = ::CoInitializeSecurity(NULL, -1, NULL, NULL, RPC_C_AUTHN_LEVEL_CONNECT, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE, NULL);
	//_ASSERT(SUCCEEDED(hr));

	//// COM STA Reentrancy Mechanism�� ���� ���� �޽������� ó��
	//::CoRegisterMessageFilter(&hbgMsgFilter, &pOldMsgFilter);

	// ROT ���
	RegisterClassObject();

	return TRUE;
}

int CHbgMainApp::ExitInstance()
{
	// ROT ����
	RevokeClassObject();

	//if (pOldMsgFilter) {
	//	// �޽��� ���� ����
	//	::CoRegisterMessageFilter(pOldMsgFilter, NULL);
	//}

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	::CoUninitialize();

	return CWinAppEx::ExitInstance();
}

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// ��ȭ ���ڸ� �����ϱ� ���� ���� ���α׷� ����Դϴ�.
void CHbgMainApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CHbgMainApp ����� ���� �ε�/���� �޼���

void CHbgMainApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
	
	// Check Frame Version
	int verFrame = GetInt(s_regFrameVerSection, -1);
	if (verFrame != HBG_FRAME_VERSION) {
		if (verFrame != -1)
			::AfxMessageBox(L"������ ������ ������Ʈ �Ǿ����Ƿ�,\n�������� �ʱ�ȭ�մϴ�.", MB_ICONINFORMATION|MB_OK);
		DelRegTree(GetAppRegistryKey(), L"Workspace");
	}
}

void CHbgMainApp::LoadCustomState()
{
}

void CHbgMainApp::SaveCustomState()
{
	// Save Frame Version
	WriteInt(s_regFrameVerSection, HBG_FRAME_VERSION);
}

// CHbgMainApp �޽��� ó����




CDocument* CHbgMainApp::OpenDocumentFile(LPCTSTR lpszFileName)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	return CWinAppEx::OpenDocumentFile(lpszFileName);
}

BOOL CHbgMainApp::Register()
{
	WCHAR szModulePath[_MAX_PATH];
	WCHAR wszCLSID[128];

	::GetModuleFileName(NULL, szModulePath, sizeof(szModulePath) / sizeof(WCHAR));
	::StringFromGUID2(CLSID_HbgMain, wszCLSID, sizeof(wszCLSID) / sizeof(WCHAR));

	WCHAR createCLSID[128];
	wcscpy_s(createCLSID, L"CLSID\\");
	wcscat_s(createCLSID, wszCLSID);

	_SetRegKeyValue(HBG_HBGMAIN_PROGID, NULL, NULL, HBG_HBGMAIN_PROGID L" Component");
	_SetRegKeyValue(HBG_HBGMAIN_PROGID, L"CLSID", NULL, wszCLSID);
	_SetRegKeyValue(HBG_HBGMAIN_PROGID, L"CurVer", NULL, HBG_HBGMAIN_CUR_PROGID);
	_SetRegKeyValue(HBG_HBGMAIN_CUR_PROGID, NULL, NULL, HBG_HBGMAIN_PROGID L" Component");
	_SetRegKeyValue(HBG_HBGMAIN_CUR_PROGID, L"CLSID", NULL, wszCLSID);
	_SetRegKeyValue(createCLSID, NULL, NULL, HBG_HBGMAIN_PROGID L" Component");
	_SetRegKeyValue(createCLSID, L"ProgID", NULL, HBG_HBGMAIN_CUR_PROGID);
	_SetRegKeyValue(createCLSID, L"LocalServer32", NULL, szModulePath);

	return CWinAppEx::Register();
}

BOOL CHbgMainApp::Unregister()
{
	WCHAR wszCLSID[128];
	::StringFromGUID2(CLSID_HbgMain, wszCLSID, sizeof(wszCLSID) / sizeof(WCHAR));

	RegDeleteKey(HKEY_CLASSES_ROOT, HBG_HBGMAIN_CUR_PROGID L"\\CLSID");
	RegDeleteKey(HKEY_CLASSES_ROOT, HBG_HBGMAIN_CUR_PROGID);
	RegDeleteKey(HKEY_CLASSES_ROOT, HBG_HBGMAIN_PROGID L"\\CurVer");
	RegDeleteKey(HKEY_CLASSES_ROOT, HBG_HBGMAIN_PROGID L"\\CLSID");
	RegDeleteKey(HKEY_CLASSES_ROOT, HBG_HBGMAIN_PROGID);

	WCHAR createCLSID[128];
	wcscpy_s(createCLSID, L"CLSID\\");
	wcscat_s(createCLSID, wszCLSID);

	WCHAR createCLSID2[128];
	wcscpy_s(createCLSID2, createCLSID);
	wcscat_s(createCLSID2, L"\\LocalServer32");

	RegDeleteKey(HKEY_CLASSES_ROOT, createCLSID2);
	
	wcscpy_s(createCLSID2, createCLSID);
	wcscat_s(createCLSID2, L"\\ProgID");
	RegDeleteKey(HKEY_CLASSES_ROOT, createCLSID2);

	RegDeleteKey(HKEY_CLASSES_ROOT, createCLSID);
	
	return CWinAppEx::Unregister();
}

CHbgEngine* CHbgMainApp::HbgGetEngine()
{
	static CHbgEngine s_hbgEngine;
	return &s_hbgEngine;
}

HWND CHbgMainApp::_ClbkHWnd(HWND pHWND/*= NULL*/)
{
	static HWND s_hWndClbk(pHWND);
	if (pHWND)
		return NULL;

	return s_hWndClbk;
}

void RegisterClassObject()
{
	g_pFactory = new CHbgMainFactory;
	if (g_pFactory) {
		g_pFactory->AddRef();

		HRESULT hr = ::CoRegisterClassObject(CLSID_HbgMain, g_pFactory, CLSCTX_LOCAL_SERVER, REGCLS_MULTIPLEUSE, &g_dwRegister);
		if (!SUCCEEDED(hr)) {
			g_pFactory->Release();
			delete g_pFactory;
		}
	}

	HbgRegisterProxyStub(IID_IHbgDebug, CLSID_HbgSvPS, &g_dwCookieSvPS);
	HbgRegisterProxyStub(IID_IHbgCallback, CLSID_HbgSvPS, &g_dwCookieSvPS);
}

void RevokeClassObject()
{
	if (g_dwRegister) {
		::CoRevokeClassObject(g_dwRegister);

		if (g_pFactory)
			g_pFactory->Release();
	}

	HbgRevokeProxyStub(g_dwCookieSvPS);
}

void _SetRegKeyValue(LPTSTR pszKey, LPTSTR pszSubkey, LPTSTR pszValueName, LPTSTR pszValue)
{
	WCHAR szKey[256];
	wcscpy_s(szKey, pszKey);
	HKEY hKey;

	if (pszSubkey) {
		wcscat_s(szKey, L"\\");
		wcscat_s(szKey, pszSubkey);
	}

	LSTATUS ec = RegCreateKeyEx(HKEY_CLASSES_ROOT, szKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);
	if (ERROR_SUCCESS == ec) {
		if (pszValue) {
			ec = RegSetValueEx(hKey, pszValueName, 0, REG_SZ, (BYTE*)pszValue, (DWORD)((wcslen(pszValue) + 1) * sizeof(WCHAR)));
		}

		RegCloseKey(hKey);
	}
}
