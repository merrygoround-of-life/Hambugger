// HbgServ.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "resource.h"
#include "HbgBase/HbgDebug_h.h"
#include "HbgBase/HbgProxyStub.h"
#include "HbgServFactory.h"


#if defined(_WIN64)
#	ifdef _DEBUG
		// {2498ECF3-1F5C-4bca-AE42-A951F868ED64}
		static const GUID CLSID_HbgServ = 
		{ 0x2498ecf3, 0x1f5c, 0x4bca, { 0xae, 0x42, 0xa9, 0x51, 0xf8, 0x68, 0xed, 0x64 } };
#	else
		// {2498ECF3-1F5C-4bca-AE42-A951F868E564}
		static const GUID CLSID_HbgServ = 
		{ 0x2498ecf3, 0x1f5c, 0x4bca, { 0xae, 0x42, 0xa9, 0x51, 0xf8, 0x68, 0xe5, 0x64 } };
#	endif // _DEBUG
#elif defined(_WIN32)
#	ifdef _DEBUG
		// {2498ECF3-1F5C-4bca-AE42-A951F868ED86}
		static const GUID CLSID_HbgServ = 
		{ 0x2498ecf3, 0x1f5c, 0x4bca, { 0xae, 0x42, 0xa9, 0x51, 0xf8, 0x68, 0xed, 0x86 } };
#	else
		// {2498ECF3-1F5C-4bca-AE42-A951F868E586}
		static const GUID CLSID_HbgServ = 
		{ 0x2498ecf3, 0x1f5c, 0x4bca, { 0xae, 0x42, 0xa9, 0x51, 0xf8, 0x68, 0xe5, 0x86 } };
#	endif // _DEBUG
#endif


static const GUID CLSID_HbgSvPS = IID_IHbgDebug;
DWORD g_dwCookieSvPS = 0;


#define MAX_LOADSTRING 100

// ���� ����:
HINSTANCE hInst;								// ���� �ν��Ͻ��Դϴ�.
TCHAR szTitle[MAX_LOADSTRING];					// ���� ǥ���� �ؽ�Ʈ�Դϴ�.

DWORD g_dwRegister = 0;
CHbgServFactory* g_pFactory = NULL;


extern DWORD g_idMainThread = 0;


void RegisterClassObject();
void RevokeClassObject();
void RegisterServer();
void UnregisterServer();
void _SetRegKeyValue(LPTSTR pszKey, LPTSTR pszSubkey, LPTSTR pszValueName, LPTSTR pszValue);


int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE /*hPrevInstance*/,
                     LPTSTR    lpCmdLine,
                     int       /*nCmdShow*/)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

 	// TODO: ���⿡ �ڵ带 �Է��մϴ�.
	g_idMainThread = ::GetCurrentThreadId();

	// ���� ���ڿ��� �ʱ�ȭ�մϴ�.
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);

	if (FAILED(::CoInitializeEx(NULL, COINIT_APARTMENTTHREADED))) {
		::MessageBox(NULL, L"COM �ʱ�ȭ ����.", NULL, MB_ICONERROR|MB_OK);
		return 0;
	}

	//HRESULT hr = ::CoInitializeSecurity(NULL, -1, NULL, NULL, RPC_C_AUTHN_LEVEL_CONNECT, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE, NULL);
	//_ASSERT(SUCCEEDED(hr));

	if (lpCmdLine && ((_wcsicmp(lpCmdLine, L"-Embedding") == 0) || (_wcsicmp(lpCmdLine, L"/Embedding") == 0)
		|| (_wcsicmp(lpCmdLine, L"- Embedding") == 0) || (_wcsicmp(lpCmdLine, L"/ Embedding") == 0))) {

		// ROT ���
		RegisterClassObject();
	} else {
		if (lpCmdLine && ((_wcsicmp(lpCmdLine, L"-RegServer") == 0) || (_wcsicmp(lpCmdLine, L"/RegServer") == 0)
				|| (_wcsicmp(lpCmdLine, L"- RegServer") == 0) || (_wcsicmp(lpCmdLine, L"/ RegServer") == 0))) {
			RegisterServer();
			return 0;
		} else if (lpCmdLine &&((_wcsicmp(lpCmdLine, L"-UnregServer") == 0) || (_wcsicmp(lpCmdLine, L"/UnregServer") == 0)
				|| (_wcsicmp(lpCmdLine, L"- UnregServer") == 0) || (_wcsicmp(lpCmdLine, L"/ UnregServer") == 0))) {
			UnregisterServer();
			return 0;
		} else {
			switch (::MessageBox(NULL, L"HbgServ ������Ʈ�� ����ұ��?\n\n- ��(���)\n- �ƴϿ�(��� ����)", NULL, MB_ICONQUESTION|MB_YESNOCANCEL)) {
				case IDYES:
					RegisterServer();
					return 0;
					break;
				case IDNO:
					UnregisterServer();
					return 0;
					break;
				case IDCANCEL:
					return 0;
					break;
			}
		}
	}

	// �⺻ �޽��� �����Դϴ�.
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// ROT ����
	RevokeClassObject();

	::CoUninitialize();

	return (int) msg.wParam;
}

void RegisterClassObject()
{
	g_pFactory = new CHbgServFactory;
	if (g_pFactory) {
		g_pFactory->AddRef();

		HRESULT hr = ::CoRegisterClassObject(CLSID_HbgServ, g_pFactory, CLSCTX_LOCAL_SERVER, REGCLS_MULTIPLEUSE, &g_dwRegister);
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

void RegisterServer()
{
	WCHAR szModulePath[_MAX_PATH];
	WCHAR wszCLSID[128];

	::GetModuleFileName(NULL, szModulePath, sizeof(szModulePath) / sizeof(WCHAR));
	::StringFromGUID2(CLSID_HbgServ, wszCLSID, sizeof(wszCLSID) / sizeof(WCHAR));

	WCHAR createCLSID[128];
	wcscpy_s(createCLSID, L"CLSID\\");
	wcscat_s(createCLSID, wszCLSID);

	_SetRegKeyValue(HBG_HBGSERV_PROGID, NULL, NULL, HBG_HBGSERV_PROGID L" Component");
	_SetRegKeyValue(HBG_HBGSERV_PROGID, L"CLSID", NULL, wszCLSID);
	_SetRegKeyValue(HBG_HBGSERV_PROGID, L"CurVer", NULL, HBG_HBGSERV_CUR_PROGID);
	_SetRegKeyValue(HBG_HBGSERV_CUR_PROGID, NULL, NULL, HBG_HBGSERV_PROGID L" Component");
	_SetRegKeyValue(HBG_HBGSERV_CUR_PROGID, L"CLSID", NULL, wszCLSID);
	_SetRegKeyValue(createCLSID, NULL, NULL, HBG_HBGSERV_PROGID L" Component");
	_SetRegKeyValue(createCLSID, L"ProgID", NULL, HBG_HBGSERV_CUR_PROGID);
	_SetRegKeyValue(createCLSID, L"LocalServer32", NULL, szModulePath);
}

void UnregisterServer()
{
	WCHAR wszCLSID[128];
	::StringFromGUID2(CLSID_HbgServ, wszCLSID, sizeof(wszCLSID) / sizeof(WCHAR));

	RegDeleteKey(HKEY_CLASSES_ROOT, HBG_HBGSERV_CUR_PROGID L"\\CLSID");
	RegDeleteKey(HKEY_CLASSES_ROOT, HBG_HBGSERV_CUR_PROGID);
	RegDeleteKey(HKEY_CLASSES_ROOT, HBG_HBGSERV_PROGID L"\\CurVer");
	RegDeleteKey(HKEY_CLASSES_ROOT, HBG_HBGSERV_PROGID L"\\CLSID");
	RegDeleteKey(HKEY_CLASSES_ROOT, HBG_HBGSERV_PROGID);

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
