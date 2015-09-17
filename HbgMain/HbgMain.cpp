
// HbgMain.cpp : 응용 프로그램에 대한 클래스 동작을 정의합니다.
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
	// 표준 파일을 기초로 하는 문서 명령입니다.
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
END_MESSAGE_MAP()

// CHbgMainApp 생성

CHbgMainApp::CHbgMainApp()
{
	m_bHiColorIcons = TRUE;

	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}

// 유일한 CHbgMainApp 개체입니다.

CHbgMainApp theApp;

//CHbgMessageFilter hbgMsgFilter;


// CHbgMainApp 초기화
BOOL CHbgMainApp::InitInstance()
{
	// 응용 프로그램 매니페스트가 ComCtl32.dll 버전 6 이상을 사용하여 비주얼 스타일을
	// 사용하도록 지정하는 경우, Windows XP 상에서 반드시 InitCommonControlsEx()가 필요합니다. 
	// InitCommonControlsEx()를 사용하지 않으면 창을 만들 수 없습니다.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 응용 프로그램에서 사용할 모든 공용 컨트롤 클래스를 포함하도록
	// 이 항목을 설정하십시오.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	// 표준 초기화
	// 이들 기능을 사용하지 않고 최종 실행 파일의 크기를 줄이려면
	// 아래에서 필요 없는 특정 초기화
	// 루틴을 제거해야 합니다.
	// 해당 설정이 저장된 레지스트리 키를 변경하십시오.
	// TODO: 이 문자열을 회사 또는 조직의 이름과 같은
	// 적절한 내용으로 수정해야 합니다.

#if defined(_DEBUG)
	SetRegistryKey(_T(HBG_COMPANYNAME) _T("\\") _T("Dev\\") _T(HBG_PRODUCTNAME) _T("\\") _T(HBG_PLATFORM));
#else
	SetRegistryKey(_T(HBG_COMPANYNAME) _T("\\") _T(HBG_PRODUCTNAME) _T("\\") _T(HBG_PLATFORM));
#endif // _DEBUG

	LoadStdProfileSettings(4);  // MRU를 포함하여 표준 INI 파일 옵션을 로드합니다.

	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// 응용 프로그램의 문서 템플릿을 등록합니다. 문서 템플릿은
	//  문서, 프레임 창 및 뷰 사이의 연결 역할을 합니다.
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CHbgMainDoc),
		RUNTIME_CLASS(CMainFrame),       // 주 SDI 프레임 창입니다.
		RUNTIME_CLASS(CHbgMainView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// DDE Execute 열기를 활성화합니다.
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// 표준 셸 명령, DDE, 파일 열기에 대한 명령줄을 구문 분석합니다.
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);


	// 명령줄에 지정된 명령을 디스패치합니다.
	// 응용 프로그램이 /RegServer, /Register, /Unregserver 또는 /Unregister로 시작된 경우 FALSE를 반환합니다.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// 창 하나만 초기화되었으므로 이를 표시하고 업데이트합니다.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// 접미사가 있을 경우에만 DragAcceptFiles를 호출합니다.
	//  SDI 응용 프로그램에서는 ProcessShellCommand 후에 이러한 호출이 발생해야 합니다.
	// 끌어서 놓기에 대한 열기를 활성화합니다.
	m_pMainWnd->DragAcceptFiles();
	
	::CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

	//HRESULT hr = ::CoInitializeSecurity(NULL, -1, NULL, NULL, RPC_C_AUTHN_LEVEL_CONNECT, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE, NULL);
	//_ASSERT(SUCCEEDED(hr));

	//// COM STA Reentrancy Mechanism을 막기 위해 메시지필터 처리
	//::CoRegisterMessageFilter(&hbgMsgFilter, &pOldMsgFilter);

	// ROT 등록
	RegisterClassObject();

	return TRUE;
}

int CHbgMainApp::ExitInstance()
{
	// ROT 해제
	RevokeClassObject();

	//if (pOldMsgFilter) {
	//	// 메시지 필터 복구
	//	::CoRegisterMessageFilter(pOldMsgFilter, NULL);
	//}

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	::CoUninitialize();

	return CWinAppEx::ExitInstance();
}

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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

// 대화 상자를 실행하기 위한 응용 프로그램 명령입니다.
void CHbgMainApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CHbgMainApp 사용자 지정 로드/저장 메서드

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
			::AfxMessageBox(L"프레임 버전이 업데이트 되었으므로,\n설정값을 초기화합니다.", MB_ICONINFORMATION|MB_OK);
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

// CHbgMainApp 메시지 처리기




CDocument* CHbgMainApp::OpenDocumentFile(LPCTSTR lpszFileName)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

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
