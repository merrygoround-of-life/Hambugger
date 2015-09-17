#include "stdafx.h"
#include "../HbgMain.h"
#include "HbgClBkImpl.h"


CHbgCallback::CHbgCallback(IUnknown* pCallback)
:	m_pCallback(pCallback), m_hWnd(NULL)
{
	m_hWnd = static_cast<CHbgMainApp*>(AfxGetApp())->_ClbkHWnd();
}

CHbgCallback::~CHbgCallback()
{
}

HRESULT CHbgCallback::QueryInterface(REFIID riid, LPVOID* ppv)
{
	return m_pCallback->QueryInterface(riid, ppv);
}

ULONG CHbgCallback::AddRef()
{
	return m_pCallback->Release();
}

ULONG CHbgCallback::Release()
{
	return m_pCallback->Release();
}

HRESULT CHbgCallback::Prompt(/*[in]*/DWORD type, /*[in]*/DWORD idThread, /*[in]*/SIZE_T szContext, /*[in, size_is(szContext)]*/BYTE* pContext, /*[in]*/SIZE_T szMemoryStack, /*[in, size_is(szMemoryStack)]*/BYTE* pMemoryStack, /*[in]*/SIZE_T szHbgContexts, /*[in, size_is(szHbgContexts)]*/BYTE* pHbgContexts)
{
	_ASSERT(szContext == sizeof(CONTEXT) && !(szMemoryStack % sizeof(SIZE_T)) && !(szHbgContexts % sizeof(HbgContext)));
	HbgPrompt_General tmpInfo = { idThread, *((CONTEXT*)pContext), szMemoryStack, (PDWORD_PTR)pMemoryStack, szHbgContexts, (HbgContext*)pHbgContexts };
	::SendMessage(m_hWnd, HBG_WM_PROMPT, (WPARAM)type, (LPARAM)&tmpInfo);

	return S_OK;
}

HRESULT CHbgCallback::Update(/*[in]*/DWORD type, /*[in]*/SIZE_T sizeData, /*[in, size_is(sizeData)]*/BYTE* pData)
{
	switch (type) {
		case HBG_UPDATE_TYPE_ADDMODULE:
			{
				_ASSERT(sizeData == sizeof(HbgUpdate_Module));
				HbgUpdate_Module* pAddPage = (HbgUpdate_Module*)pData;
				::SendMessage(m_hWnd, HBG_WM_UPDATE, (WPARAM)type, (LPARAM)pAddPage);
			}
			break;
		case HBG_UPDATE_TYPE_REMOVEMODULE:
			{
				_ASSERT(sizeData == sizeof(HbgUpdate_RemovePage_AddrStart));
				HbgUpdate_RemovePage_AddrStart addr = *((HbgUpdate_RemovePage_AddrStart*)(pData));
				::SendMessage(m_hWnd, HBG_WM_UPDATE, (WPARAM)type, (LPARAM)addr);
			}
			break;
		case HBG_UPDATE_TYPE_ADDTHREAD:
			{
				_ASSERT(sizeData == sizeof(HbgUpdate_Thread));
				HbgUpdate_Thread* pThreadInfo = (HbgUpdate_Thread*)pData;
				::SendMessage(m_hWnd, HBG_WM_UPDATE, (WPARAM)type, (LPARAM)pThreadInfo);
			}
			break;
		case HBG_UPDATE_TYPE_REMOVETHREAD:
			{
				_ASSERT(sizeData == sizeof(HbgUpdate_RemoveThread_Id));
				HbgUpdate_RemoveThread_Id id = *((HbgUpdate_RemoveThread_Id*)(pData));
				::SendMessage(m_hWnd, HBG_WM_UPDATE, (WPARAM)type, (LPARAM)id);
			}
			break;
	}

	return S_OK;
}
