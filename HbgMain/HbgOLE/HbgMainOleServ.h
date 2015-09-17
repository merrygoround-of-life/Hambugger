#ifndef _HbgMainOleServ_H_
#define _HbgMainOleServ_H_


class CHbgCallback;


class CHbgMainOleServ : public IUnknown
{
public:
	CHbgMainOleServ();
	~CHbgMainOleServ();

public:
	// IUnknown
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, LPVOID* ppv);
	virtual ULONG STDMETHODCALLTYPE AddRef();
	virtual ULONG STDMETHODCALLTYPE Release();

private:
	CHbgCallback* m_pImplClbk;
	DWORD m_cRef;
};


extern LONG g_cHbgClbkObjects;
extern LONG g_cHbgClbkLocks;


#endif // _HbgMainOleServ_H_

