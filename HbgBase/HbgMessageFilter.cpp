#include "stdafx.h"
#include "HbgMessageFilter.h"


CHbgMessageFilter::CHbgMessageFilter()
{}

CHbgMessageFilter::~CHbgMessageFilter()
{}

HRESULT STDMETHODCALLTYPE CHbgMessageFilter::QueryInterface(REFIID, LPVOID*)
{ return E_NOINTERFACE; }

ULONG STDMETHODCALLTYPE CHbgMessageFilter::AddRef()
{ return 0; }

ULONG STDMETHODCALLTYPE CHbgMessageFilter::Release()
{ return 0; }
	

DWORD STDMETHODCALLTYPE CHbgMessageFilter::HandleInComingCall( 
	/* [in] */ DWORD dwCallType,
	/* [in] */ HTASK /*htaskCaller*/,
	/* [in] */ DWORD /*dwTickCount*/,
	/* [in] */ LPINTERFACEINFO /*lpInterfaceInfo*/)
{
	if (dwCallType != CALLTYPE_NESTED && dwCallType != CALLTYPE_TOPLEVEL_CALLPENDING)
		return SERVERCALL_ISHANDLED;

	return SERVERCALL_REJECTED;
}

DWORD STDMETHODCALLTYPE CHbgMessageFilter::RetryRejectedCall( 
	/* [in] */ HTASK /*htaskCallee*/,
	/* [in] */ DWORD /*dwTickCount*/,
	/* [in] */ DWORD dwRejectType)
{
	if (dwRejectType == SERVERCALL_REJECTED)
		return (DWORD)-1;

	return 100;
}

DWORD STDMETHODCALLTYPE CHbgMessageFilter::MessagePending( 
	/* [in] */ HTASK /*htaskCallee*/,
	/* [in] */ DWORD /*dwTickCount*/,
	/* [in] */ DWORD /*dwPendingType*/)
{
	return PENDINGMSG_WAITNOPROCESS;
}
