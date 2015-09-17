#ifndef _HbgMessageFilter_inl_
#define _HbgMessageFilter_inl_


class CHbgMessageFilter : public IMessageFilter
{
public:
	CHbgMessageFilter();
	~CHbgMessageFilter();

public:
	// IUnknown
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID, LPVOID*);
	virtual ULONG STDMETHODCALLTYPE AddRef();
	virtual ULONG STDMETHODCALLTYPE Release();
	
	// IHbgMessageFilter
	virtual DWORD STDMETHODCALLTYPE HandleInComingCall( 
		/* [in] */ DWORD dwCallType,
		/* [in] */ HTASK /*htaskCaller*/,
		/* [in] */ DWORD /*dwTickCount*/,
		/* [in] */ LPINTERFACEINFO /*lpInterfaceInfo*/);

	virtual DWORD STDMETHODCALLTYPE RetryRejectedCall( 
		/* [in] */ HTASK /*htaskCallee*/,
		/* [in] */ DWORD /*dwTickCount*/,
		/* [in] */ DWORD dwRejectType);

	virtual DWORD STDMETHODCALLTYPE MessagePending( 
		/* [in] */ HTASK /*htaskCallee*/,
		/* [in] */ DWORD /*dwTickCount*/,
		/* [in] */ DWORD /*dwPendingType*/);
};


#endif // _HbgMessageFilter_inl_
