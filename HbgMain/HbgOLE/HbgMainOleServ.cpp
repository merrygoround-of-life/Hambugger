#include "stdafx.h"
#include "HbgClbk/HbgClBkImpl.h"
#include "HbgMainOleServ.h"


CHbgMainOleServ::CHbgMainOleServ()
:	m_cRef(0)
{
	m_pImplClbk = new CHbgCallback(this);
}

CHbgMainOleServ::~CHbgMainOleServ()
{
	if (m_pImplClbk) {
		delete m_pImplClbk;
		m_pImplClbk = NULL;
	}
}

HRESULT CHbgMainOleServ::QueryInterface(REFIID riid, LPVOID* ppv)
{
	HRESULT hr = E_NOINTERFACE;
	BOOL bOk = FALSE;

	if (riid == IID_IUnknown) {
		*ppv = this;
		bOk = TRUE;
	} else if (riid == IID_IHbgCallback) {
		*ppv = m_pImplClbk;
		bOk = TRUE;
	}

	if (bOk) {
		AddRef();
		hr = S_OK;
	}

	return hr;
}

ULONG CHbgMainOleServ::AddRef()
{
	++m_cRef;
	return m_cRef;
}

ULONG CHbgMainOleServ::Release()
{
	--m_cRef;
	if (m_cRef == 0) {
		--g_cHbgClbkObjects;
		delete this;
	}

	return m_cRef;
}


LONG g_cHbgClbkObjects = 0;
LONG g_cHbgClbkLocks = 0;
