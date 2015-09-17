#include "stdafx.h"
#include "HbgBase/HbgMessageFilter.h"
#include "HbgDebug.h"
#include "HbgServ.h"


///////////////////////////////////////////////////////////
// CHbgServInterUnk
class CHbgServInterUnk : public IUnknown
{
public:
	CHbgServInterUnk(CHbgServ* pServ)	:	m_pServ(pServ)	{}
	~CHbgServInterUnk()										{}

public:
	// IUnknown
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, LPVOID* ppv)
	{
		return m_pServ->InternalQueryInterface(riid, ppv);
	}

	virtual ULONG STDMETHODCALLTYPE AddRef()
	{
		return m_pServ->InternalAddRef();
	}

	virtual ULONG STDMETHODCALLTYPE Release()
	{
		return m_pServ->InternalRelease();
	}

private:
	CHbgServ* m_pServ;
};
	

//CHbgMessageFilter hbgMsgFilter;


///////////////////////////////////////////////////////////
// CHbgServ
CHbgServ::CHbgServ(IUnknown* pUnkOuter)
:	m_pImpl(NULL), m_cRef(0), m_pUnknown(pUnkOuter), m_pServInterUnk(NULL)
{
	m_pImpl = new CHbgDebug(this);
	m_pServInterUnk = new CHbgServInterUnk(this);

	if (!m_pUnknown)
		m_pUnknown = m_pServInterUnk;

	//// COM STA Reentrancy Mechanism을 막기 위해 메시지필터 처리
	//::CoRegisterMessageFilter(&hbgMsgFilter, NULL);
}

CHbgServ::~CHbgServ()
{	
	//// 메시지 필터 복구
	//::CoRegisterMessageFilter(NULL, NULL);

	if (m_pImpl) {
		delete m_pImpl;
		m_pImpl = NULL;
	}

	if (m_pServInterUnk) {
		delete m_pServInterUnk;
		m_pServInterUnk = NULL;
	}

	m_pUnknown = NULL;
}

HRESULT CHbgServ::QueryInterface(REFIID riid, LPVOID* ppv)
{
	return m_pUnknown->QueryInterface(riid, ppv);
}

ULONG CHbgServ::AddRef()
{
	return m_pUnknown->AddRef();
}

ULONG CHbgServ::Release()
{
	return m_pUnknown->Release();
}

HRESULT CHbgServ::InternalQueryInterface(REFIID riid, LPVOID* ppv)
{
	HRESULT hr = E_NOINTERFACE;
	BOOL bOk = FALSE;

	if (riid == IID_IUnknown) {
		*ppv = m_pUnknown;
		bOk = TRUE;
	} else if (riid == IID_IHbgDebug) {
		*ppv = m_pImpl;
		bOk = TRUE;
	}

	if (bOk) {
		InternalAddRef();
		hr = S_OK;
	}

	return hr;
}

ULONG CHbgServ::InternalAddRef()
{
	++m_cRef;
	return m_cRef;
}

ULONG CHbgServ::InternalRelease()
{
	--m_cRef;
	if (m_cRef == 0) {
		--g_cHbgServObjects;
		delete this;

		HbgEndProcess();
	}

	return m_cRef;
}


LONG g_cHbgServObjects = 0;
LONG g_cHbgServLocks = 0;

extern DWORD g_idMainThread;

void HbgEndProcess()
{
	if (!g_cHbgServObjects && !g_cHbgServLocks)
		::PostThreadMessage(g_idMainThread, WM_QUIT, 0, 0);
}
