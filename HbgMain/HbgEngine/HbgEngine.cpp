#include "StdAfx.h"
#include "HbgBase/HbgDebug_h.h"

#include "HbgEngine.h"


CHbgEngine::CHbgEngine(void)
:	m_pIHbgDebug(NULL), m_pIUnkCallback(NULL), m_bRun(FALSE)
{
}

CHbgEngine::~CHbgEngine(void)
{
	Finalize();
}

BOOL CHbgEngine::Running() const
{
	return m_bRun;
}

void CHbgEngine::Finalize()
{
	if (m_pIUnkCallback) {
		m_pIUnkCallback->Release();
		m_pIUnkCallback = NULL;
	}

	if (m_pIHbgDebug) {
		m_pIHbgDebug->Release();
		m_pIHbgDebug = NULL;
	}
}

BOOL CHbgEngine::Initialize(LPCWSTR pathDebuggee, DWORD pidDebuggee)
{
	HRESULT hr = E_FAIL;
	std::wstring strErr;
	m_bRun = TRUE;

	// 기존에 동작하고 있었다면 종료
	if (m_pIHbgDebug && m_pIUnkCallback)
		m_pIHbgDebug->Uninitialize(TRUE);

	if (!m_pIUnkCallback) {
		// 1) HbgMain 컴포넌트 생성
		CLSID clsid_hbgmain;
		hr = ::CLSIDFromProgID(HBG_HBGMAIN_PROGID, &clsid_hbgmain);
		if (SUCCEEDED(hr))
			hr = ::CoCreateInstance(clsid_hbgmain, NULL, CLSCTX_INPROC_SERVER, IID_IUnknown, (LPVOID*)&m_pIUnkCallback);
		else
			strErr = L"등록 필요";
	} else {
		// IHbgCallback 인터페이스가 이미 존재
		hr = S_OK;
	}

	if (SUCCEEDED(hr) && m_pIUnkCallback) {
		if (!m_pIHbgDebug) {
			// 2) HbgServ 컴포넌트 생성
			CLSID clsid_hbgserv;
			hr = ::CLSIDFromProgID(HBG_HBGSERV_PROGID, &clsid_hbgserv);
			if (SUCCEEDED(hr)) {
				MULTI_QI mqi[] = { { &IID_IUnknown, NULL, S_OK }, };
				COSERVERINFO csi = { 0, NULL, NULL, 0 };
				hr = ::CoCreateInstanceEx(clsid_hbgserv, NULL, CLSCTX_ALL, &csi, sizeof(mqi) / sizeof(mqi[0]), mqi);
				if (SUCCEEDED(hr)) {
					IUnknown* pIUnkServ = mqi[0].pItf;
					hr = pIUnkServ->QueryInterface(IID_IHbgDebug, (LPVOID*)&m_pIHbgDebug);
					pIUnkServ->Release();
				}
			} else {
				strErr = L"등록 필요";
			}
		} else {
			// IHbgDebug 인터페이스가 이미 존재
			hr = S_OK;
		}

		if (SUCCEEDED(hr) && m_pIHbgDebug) {

#ifdef _DEBUG
			::AfxMessageBox(L"디버거 연결", MB_ICONINFORMATION|MB_OK);
#endif _DEBUG

			// 3) 컴포넌트 초기화
			if (pathDebuggee)
				hr = m_pIHbgDebug->Initialize(pathDebuggee, IID_IUnknown, m_pIUnkCallback);
			else if (pidDebuggee)
				hr = m_pIHbgDebug->InitializeEx(pidDebuggee, IID_IUnknown, m_pIUnkCallback);
			else
				hr = E_FAIL;
		}
	}

	BOOL bSucceeded = SUCCEEDED(hr);
	if (!bSucceeded) {
		if (strErr.empty())
			strErr = L"연결 실패";
		::AfxMessageBox(strErr.c_str(), MB_ICONEXCLAMATION|MB_OK);
	}

	return bSucceeded;
}

BOOL CHbgEngine::Uninitialize(BOOL bKillDebuggee, BOOL bUserAct/*= TRUE*/)
{
	HRESULT hr = S_OK;
	m_bRun = FALSE;

	if (bUserAct && m_pIHbgDebug && m_pIUnkCallback)
		hr = m_pIHbgDebug->Uninitialize(bKillDebuggee);

	return SUCCEEDED(hr);
}

BOOL CHbgEngine::Go(DWORD_PTR toAddr)
{
	HRESULT hr = E_FAIL;

	if (m_pIHbgDebug && m_pIUnkCallback)
		hr = m_pIHbgDebug->Go(toAddr);

	return SUCCEEDED(hr);
}

BOOL CHbgEngine::Step(DWORD idThread)
{
	HRESULT hr = E_FAIL;

	if (m_pIHbgDebug && m_pIUnkCallback)
		hr = m_pIHbgDebug->Step(idThread);

	return SUCCEEDED(hr);
}

BOOL CHbgEngine::Break()
{
	HRESULT hr = E_FAIL;

	if (m_pIHbgDebug && m_pIUnkCallback)
		hr = m_pIHbgDebug->Break();

	return SUCCEEDED(hr);
}

BOOL CHbgEngine::ToggleBreakpoint(DWORD_PTR addr, BOOL* bSet)
{
	HRESULT hr = E_FAIL;

	if (m_pIHbgDebug && m_pIUnkCallback)
		hr = m_pIHbgDebug->ToggleBreakpoint(addr, bSet);

	return SUCCEEDED(hr);
}

BOOL CHbgEngine::ReadMemory(DWORD_PTR addr, SIZE_T size, BYTE* pByte)
{
	HRESULT hr = E_FAIL;

	if (m_pIHbgDebug && m_pIUnkCallback)
		hr = m_pIHbgDebug->ReadMemory(addr, size, pByte);

	return SUCCEEDED(hr);
}

BOOL CHbgEngine::WriteMemory(DWORD_PTR addr, SIZE_T size, BYTE* pByte)
{
	HRESULT hr = E_FAIL;

	if (m_pIHbgDebug && m_pIUnkCallback)
		hr = m_pIHbgDebug->WriteMemory(addr, size, pByte);

	return SUCCEEDED(hr);
}

BOOL CHbgEngine::ReadContext(DWORD idThread, SIZE_T size, BYTE* pByte)
{
	HRESULT hr = E_FAIL;

	if (m_pIHbgDebug && m_pIUnkCallback)
		hr = m_pIHbgDebug->ReadContext(idThread, size, pByte);

	return SUCCEEDED(hr);
}

BOOL CHbgEngine::WriteContext(DWORD idThread, SIZE_T size, BYTE* pByte)
{
	HRESULT hr = E_FAIL;

	if (m_pIHbgDebug && m_pIUnkCallback)
		hr = m_pIHbgDebug->WriteContext(idThread, size, pByte);

	return SUCCEEDED(hr);
}
