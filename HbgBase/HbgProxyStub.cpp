#include "stdafx.h"
#include "HbgProxyStub.h"


void HbgRegisterProxyStub(REFIID iid, CLSID clsid, LPDWORD pCookie)
{
	// Register ProxyStub
	IUnknown* pIUnkProxyStub = NULL;
	if (SUCCEEDED(DllGetClassObject(clsid, IID_IUnknown, (LPVOID*)&pIUnkProxyStub))) {

		if (SUCCEEDED(::CoRegisterClassObject(clsid, pIUnkProxyStub, CLSCTX_INPROC_SERVER, REGCLS_MULTIPLEUSE, pCookie)))
			::CoRegisterPSClsid(iid, clsid);

		pIUnkProxyStub->Release();
	}
}

void HbgRevokeProxyStub(DWORD cookie)
{
	// Revoke ProxyStub
	if (cookie)
		::CoRevokeClassObject(cookie);
}
