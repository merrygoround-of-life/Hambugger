#ifndef _HbgMainFactory_h_
#define _HbgMainFactory_h_


class CHbgMainFactory : public IClassFactory
{
public:
	CHbgMainFactory();
	~CHbgMainFactory();

public:
	// IUnknown
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, LPVOID* ppv);
	virtual ULONG STDMETHODCALLTYPE AddRef();
	virtual ULONG STDMETHODCALLTYPE Release();
	
	// IClassFactory
	virtual HRESULT STDMETHODCALLTYPE CreateInstance(IUnknown* pUnkOuter, REFIID riid, LPVOID* ppv);
	virtual HRESULT STDMETHODCALLTYPE LockServer(BOOL fLock);

private:
	DWORD m_cRef;
};


#endif // _HbgMainFactory_h_
