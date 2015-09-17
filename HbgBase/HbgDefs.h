#ifndef _HbgDefs_H_
#define _HbgDefs_H_


#include "HbgBase/HbgVersions.h"


#define HBG_HBGMAIN_PROGID		_T(HBG_PRODUCTNAME) L"." HBG_HBGMAIN L"." _T(HBG_PLATFORM)
#define HBG_HBGMAIN_CUR_PROGID	HBG_HBGMAIN_PROGID L"." _T(HBG_COMPONENT_VERSION_STR)
#define HBG_HBGSERV_PROGID		_T(HBG_PRODUCTNAME) L"." HBG_HBGSERV L"." _T(HBG_PLATFORM)
#define HBG_HBGSERV_CUR_PROGID	HBG_HBGSERV_PROGID L"." _T(HBG_COMPONENT_VERSION_STR)


#define HBG_WM_PROMPT			WM_USER + 1
#define HBG_WM_UPDATE			WM_USER + 2


enum HBG_PROMPT_TYPE {
	HBG_PROMPT_TYPE_GENERAL = 0,
	HBG_PROMPT_TYPE_TERMINATE,
};


enum HBG_UPDATE_TYPE {
	HBG_UPDATE_TYPE_ADDMODULE = 0,
	HBG_UPDATE_TYPE_REMOVEMODULE,
	HBG_UPDATE_TYPE_ADDTHREAD,
	HBG_UPDATE_TYPE_REMOVETHREAD,
};


struct HbgContext
{
	DWORD idThread;
	DWORD_PTR eipCurrent;
};


struct HbgPrompt_General
{
	DWORD idThread;
	CONTEXT context;

	SIZE_T szMemoryStack;
	PDWORD_PTR pMemoryStack;

	SIZE_T szHbgContexts;
	HbgContext* pHbgContexts;
};


struct HbgUpdate_Module
{
	DWORD_PTR addressStart;
	DWORD_PTR addressEnd;
	DWORD_PTR addressCodeStart;
	DWORD_PTR addressCodeEnd;
	
	WCHAR path[_MAX_PATH];
};


struct HbgUpdate_Thread
{
	DWORD threadId;
	DWORD_PTR threadStartAddress;
	DWORD_PTR threadStackBase;
	
	WCHAR strFuncStartAddr[_MAX_PATH];
};


typedef	DWORD_PTR				HbgUpdate_RemovePage_AddrStart;
typedef	DWORD					HbgUpdate_RemoveThread_Id;


#endif // _HbgDefs_H_
