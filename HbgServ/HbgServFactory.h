#ifndef _HbgServFactory_h_
#define _HbgServFactory_h_


class CHbgServFactory : public IClassFactory
{
public:
	CHbgServFactory();
	~CHbgServFactory();

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


#endif // _HbgServFactory_h_
