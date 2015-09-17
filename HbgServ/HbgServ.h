#ifndef _HbgServ_h_
#define _HbgServ_h_


class CHbgDebug;
class CHbgServInterUnk;


class CHbgServ : public IUnknown
{
public:
	CHbgServ(IUnknown* pUnkOuter);
	~CHbgServ();

public:
	// IUnknown
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, LPVOID* ppv);
	virtual ULONG STDMETHODCALLTYPE AddRef();
	virtual ULONG STDMETHODCALLTYPE Release();
	
	// (Internal)IUnknown
	virtual HRESULT STDMETHODCALLTYPE InternalQueryInterface(REFIID riid, LPVOID* ppv);
	virtual ULONG STDMETHODCALLTYPE InternalAddRef();
	virtual ULONG STDMETHODCALLTYPE InternalRelease();
	
private:
	CHbgDebug* m_pImpl;
	DWORD m_cRef;

	IUnknown* m_pUnknown;
	CHbgServInterUnk* m_pServInterUnk;
};


extern LONG g_cHbgServObjects;
extern LONG g_cHbgServLocks;

void HbgEndProcess();


#endif // _HbgServ_h_
