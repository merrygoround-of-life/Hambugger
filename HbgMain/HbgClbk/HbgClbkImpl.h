#ifndef _HbgCallback_H_
#define _HbgCallback_H_


#include "HbgBase/HbgDebug_h.h"


class CHbgCallback : public IHbgCallback
{
public:
	CHbgCallback(IUnknown* pCallback);
	~CHbgCallback();

public:
	// IUnknown
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, LPVOID* ppv);
	virtual ULONG STDMETHODCALLTYPE AddRef();
	virtual ULONG STDMETHODCALLTYPE Release();
	
	// IHbgCallback
	virtual HRESULT STDMETHODCALLTYPE Prompt(/*[in]*/DWORD type, /*[in]*/DWORD idThread, /*[in]*/SIZE_T szContext, /*[in, size_is(szContext)]*/BYTE* pContext, /*[in]*/SIZE_T szMemoryStack, /*[in, size_is(szMemoryStack)]*/BYTE* pMemoryStack, /*[in]*/SIZE_T szHbgContexts, /*[in, size_is(szHbgContexts)]*/BYTE* pHbgContexts);
	virtual HRESULT STDMETHODCALLTYPE Update(/*[in]*/DWORD type, /*[in]*/SIZE_T sizeData, /*[in, size_is(sizeData)]*/BYTE* pData);

private:
	IUnknown* m_pCallback;
	HWND m_hWnd;
};


#endif // _HbgCallback_H_

