// HbgCore.cpp : DLL 응용 프로그램을 위해 내보낸 함수를 정의합니다.
//

#include "stdafx.h"
#include "HbgCoreInternal.h"
#include "HbgCore.h"


CHbgCore::CHbgCore(void)
: m_coreInternal(NULL)
{
}

CHbgCore::~CHbgCore(void)
{
	if (m_coreInternal) {
		delete m_coreInternal;
		m_coreInternal = NULL;
	}
}

HRESULT CHbgCore::Initialize(LPCWSTR pathDebuggee, IUnknown* pIUnkClbk)
{
	if (m_coreInternal || !pathDebuggee)
		return E_FAIL;
	
	m_coreInternal = new CHbgCoreInternal;
	if (!m_coreInternal->Initialize(pathDebuggee, pIUnkClbk)) {
		if (m_coreInternal) {
			delete m_coreInternal;
			m_coreInternal = NULL;
		}

		return E_FAIL;
	}

	return S_OK;
}

HRESULT CHbgCore::InitializeEx(DWORD pidDebuggee, IUnknown* pIUnkClbk)
{
	if (m_coreInternal || !pidDebuggee)
		return E_FAIL;
	
	m_coreInternal = new CHbgCoreInternal;
	if (!m_coreInternal->InitializeEx(pidDebuggee, pIUnkClbk)) {
		if (m_coreInternal) {
			delete m_coreInternal;
			m_coreInternal = NULL;
		}

		return E_FAIL;
	}

	return S_OK;
}

HRESULT CHbgCore::Uninitialize(BOOL bKillDebuggee)
{
	if (!m_coreInternal)
		return E_FAIL;
	
	if (!bKillDebuggee)
		m_coreInternal->Detach();

	delete m_coreInternal;
	m_coreInternal = NULL;

	return S_OK;
}

HRESULT CHbgCore::Go(DWORD_PTR toAddr)
{
	if (!m_coreInternal)
		return E_FAIL;

	if (!m_coreInternal->Go(toAddr))
		return E_FAIL;;

	return S_OK;
}

HRESULT CHbgCore::Step(DWORD idThread)
{
	if (!m_coreInternal)
		return E_FAIL;

	if (!m_coreInternal->Step(idThread))
		return E_FAIL;;

	return S_OK;
}

HRESULT CHbgCore::Break()
{
	if (!m_coreInternal)
		return E_FAIL;

	if (!m_coreInternal->Break())
		return E_FAIL;

	return S_OK;
}

HRESULT CHbgCore::ToggleBreakpoint(DWORD_PTR addr, BOOL* bSet)
{
	if (!m_coreInternal)
		return E_FAIL;

	if (!m_coreInternal->ToggleBreakpoint(addr, bSet))
		return E_FAIL;

	return S_OK;
}

HRESULT CHbgCore::ReadMemory(DWORD_PTR addr, SIZE_T size, BYTE* pByte)
{
	if (!m_coreInternal)
		return E_FAIL;

	if (!m_coreInternal->ReadMemory(addr, size, pByte))
		return E_FAIL;

	return S_OK;
}

HRESULT CHbgCore::WriteMemory(DWORD_PTR addr, SIZE_T size, BYTE* pByte)
{
	if (!m_coreInternal)
		return E_FAIL;

	if (!m_coreInternal->WriteMemory(addr, size, pByte))
		return E_FAIL;

	return S_OK;
}

HRESULT CHbgCore::ReadContext(DWORD idThread, SIZE_T size, BYTE* pByte)
{
	if (!m_coreInternal)
		return E_FAIL;

	if (!m_coreInternal->ReadContext(idThread, size, pByte))
		return E_FAIL;

	return S_OK;
}

HRESULT CHbgCore::WriteContext(DWORD idThread, SIZE_T size, BYTE* pByte)
{
	if (!m_coreInternal)
		return E_FAIL;

	if (!m_coreInternal->WriteContext(idThread, size, pByte))
		return E_FAIL;

	return S_OK;
}
