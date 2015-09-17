#ifndef _HbgDebug_h_
#define _HbgDebug_h_


#include "HbgBase/HbgDebug_h.h"
#include "HbgCore/include/HbgCoreInc.h"


class CHbgCore;
struct IHbgCallback;


class CHbgDebug : public IHbgDebug
{
public:
	CHbgDebug(IUnknown* pServ);
	~CHbgDebug();

public:
	// IUnknown
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, LPVOID* ppv);
	virtual ULONG STDMETHODCALLTYPE AddRef();
	virtual ULONG STDMETHODCALLTYPE Release();
	
	// IHbgDebug
	virtual HRESULT STDMETHODCALLTYPE Initialize(/*[in, string]*/LPCWSTR pathDebuggee, /*[in]*/REFIID riid, /*[iid_is(riid)]*/IUnknown* pIUnkClbk);
	virtual HRESULT STDMETHODCALLTYPE InitializeEx(/*[in]*/DWORD pidDebuggee, /*[in]*/REFIID riid, /*[iid_is(riid)]*/IUnknown* pIUnkClbk);
	virtual HRESULT STDMETHODCALLTYPE Uninitialize(/*[in]*/BOOL bKillDebuggee);
	virtual HRESULT STDMETHODCALLTYPE Go(/*[in]*/DWORD_PTR toAddr);
	virtual HRESULT STDMETHODCALLTYPE Step(/*[in]*/DWORD idThread);
	virtual HRESULT STDMETHODCALLTYPE Break();
	virtual HRESULT STDMETHODCALLTYPE ToggleBreakpoint(/*[in]*/DWORD_PTR addr, /*[out]*/BOOL* bSet);
	virtual HRESULT STDMETHODCALLTYPE ReadMemory(/*[in]*/DWORD_PTR addr, /*[in]*/SIZE_T size, /*[in, out, size_is(size)]*/BYTE* pByte);
	virtual HRESULT STDMETHODCALLTYPE WriteMemory(/*[in]*/DWORD_PTR addr, /*[in]*/SIZE_T size, /*[in, size_is(size)]*/BYTE* pByte);
	virtual HRESULT STDMETHODCALLTYPE ReadContext(/*[in]*/DWORD idThread, /*[in]*/SIZE_T size, /*[in, out, size_is(size)]*/BYTE* pByte);
	virtual HRESULT STDMETHODCALLTYPE WriteContext(/*[in]*/DWORD idThread, /*[in]*/SIZE_T size, /*[in, size_is(size)]*/BYTE* pByte);

private:
	CHbgCore m_core;

private:
	IUnknown* m_pServ;
};


#endif // _HbgDebug_h_
