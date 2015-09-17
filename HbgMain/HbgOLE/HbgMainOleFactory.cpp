#include "stdafx.h"
#include "HbgMainOleServ.h"
#include "HbgMainOleFactory.h"


LONG g_cHbgMainObjects = 0;
LONG g_cHbgMainLocks = 0;


CHbgMainFactory::CHbgMainFactory()
:	m_cRef(0)
{
}

CHbgMainFactory::~CHbgMainFactory()
{
}

HRESULT CHbgMainFactory::QueryInterface(REFIID riid, LPVOID* ppv)
{
	HRESULT hr = E_NOINTERFACE;
	BOOL bOK = FALSE;

	if (riid == IID_IUnknown || riid == IID_IClassFactory) {
		*ppv = this;
		bOK = TRUE;
	}

	if (bOK) {
		AddRef();
		hr = S_OK;
	}

	return hr;
}

ULONG CHbgMainFactory::AddRef(void)
{
	++m_cRef;
	return m_cRef;
}

ULONG CHbgMainFactory::Release(void)
{
	--m_cRef;
	if (m_cRef == 0)
		delete this;

	return m_cRef;
}

HRESULT CHbgMainFactory::CreateInstance(IUnknown *pUnkOuter, REFIID riid, LPVOID* ppv)
{
	HRESULT hr = E_FAIL;

	if (pUnkOuter) {
		hr = CLASS_E_NOAGGREGATION;
	} else {
		CHbgMainOleServ* pClbkServer = new CHbgMainOleServ;
		if (pClbkServer) {
			++g_cHbgMainObjects;
			hr = pClbkServer->QueryInterface(riid, ppv);
			if (FAILED(hr)) {
				--g_cHbgMainObjects;
				delete pClbkServer;
			}
		} else {
			hr = E_OUTOFMEMORY;
		}
	}

	return hr;
}

HRESULT CHbgMainFactory::LockServer(BOOL fLock)
{
	if (fLock)
		++g_cHbgMainLocks;
	else
		--g_cHbgMainLocks;

	return S_OK;
}
