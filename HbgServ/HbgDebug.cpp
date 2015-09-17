#include "stdafx.h"
#include "HbgDebug.h"


CHbgDebug::CHbgDebug(IUnknown* pServ)
:	m_pServ(pServ)
{
}

CHbgDebug::~CHbgDebug()
{}

HRESULT CHbgDebug::QueryInterface(REFIID riid, LPVOID* ppv)
{
	return m_pServ->QueryInterface(riid, ppv);
}

ULONG CHbgDebug::AddRef()
{
	return m_pServ->AddRef();
}

ULONG CHbgDebug::Release()
{
	return m_pServ->Release();
}

HRESULT CHbgDebug::Initialize(/*[in, string]*/LPCWSTR pathDebuggee, /*[in]*/REFIID /*riid*/, /*[iid_is(riid)]*/IUnknown* pIUnkClbk)
{
	return m_core.Initialize(pathDebuggee, pIUnkClbk);
}

HRESULT CHbgDebug::InitializeEx(/*[in]*/DWORD pidDebuggee, /*[in]*/REFIID /*riid*/, /*[iid_is(riid)]*/IUnknown* pIUnkClbk)
{
	return m_core.InitializeEx(pidDebuggee, pIUnkClbk);
}

HRESULT CHbgDebug::Uninitialize(/*[in]*/BOOL bKillDebuggee)
{
	return m_core.Uninitialize(bKillDebuggee);
}

HRESULT CHbgDebug::Go(/*[in]*/DWORD_PTR toAddr)
{
	return m_core.Go(toAddr);
}

HRESULT CHbgDebug::Step(/*[in]*/DWORD idThread)
{
	return m_core.Step(idThread);
}

HRESULT CHbgDebug::Break()
{
	return m_core.Break();
}

HRESULT CHbgDebug::ToggleBreakpoint(/*[in]*/DWORD_PTR addr, /*[out]*/BOOL* bSet)
{
	return m_core.ToggleBreakpoint(addr, bSet);
}

HRESULT CHbgDebug::ReadMemory(/*[in]*/DWORD_PTR addr, /*[in]*/SIZE_T size, /*[in, out, size_is(size)]*/BYTE* pByte)
{
	return m_core.ReadMemory(addr, size, pByte);
}

HRESULT CHbgDebug::WriteMemory(/*[in]*/DWORD_PTR addr, /*[in]*/SIZE_T size, /*[in, size_is(size)]*/BYTE* pByte)
{
	return m_core.WriteMemory(addr, size, pByte);
}

HRESULT CHbgDebug::ReadContext(/*[in]*/DWORD idThread, /*[in]*/SIZE_T size, /*[in, out, size_is(size)]*/BYTE* pByte)
{
	return m_core.ReadContext(idThread, size, pByte);
}

HRESULT CHbgDebug::WriteContext(/*[in]*/DWORD idThread, /*[in]*/SIZE_T size, /*[in, size_is(size)]*/BYTE* pByte)
{
	return m_core.WriteContext(idThread, size, pByte);
}
