#include "stdafx.h"
#include "HbgServ.h"
#include "HbgServFactory.h"


CHbgServFactory::CHbgServFactory()
:	m_cRef(0)
{
}

CHbgServFactory::~CHbgServFactory()
{
}

HRESULT CHbgServFactory::QueryInterface(REFIID riid, LPVOID* ppv)
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

ULONG CHbgServFactory::AddRef(void)
{
	++m_cRef;
	return m_cRef;
}

ULONG CHbgServFactory::Release(void)
{
	--m_cRef;
	if (m_cRef == 0)
		delete this;

	return m_cRef;
}

HRESULT CHbgServFactory::CreateInstance(IUnknown *pUnkOuter, REFIID riid, LPVOID* ppv)
{
	HRESULT hr = E_FAIL;

	if (pUnkOuter/* && riid != IID_IUnknown*/) {
		hr = CLASS_E_NOAGGREGATION;					// 우선 aggregation 미지원.
	} else {
		CHbgServ* pServer = new CHbgServ(pUnkOuter);
		if (pServer) {
			++g_cHbgServObjects;
			hr = pServer->InternalQueryInterface(riid, ppv);
			if (FAILED(hr)) {
				--g_cHbgServObjects;
				delete pServer;

				HbgEndProcess();
			}
		} else {
			hr = E_OUTOFMEMORY;
		}
	}

	return hr;
}

HRESULT CHbgServFactory::LockServer(BOOL fLock)
{
	if (fLock)
		++g_cHbgServLocks;
	else
		--g_cHbgServLocks;

	return S_OK;
}
