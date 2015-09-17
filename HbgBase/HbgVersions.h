#ifndef _HbgVersions_H_
#define _HbgVersions_H_


// Common
#define HBG_VERSION						0,2,0,10
#define HBG_VERSION_STR					"0,2,0,10"
#define HBG_FRAME_VERSION				0x00000004
#define HBG_COMPONENT_VERSION_STR		"1"

#if defined(_WIN64)
#	define HBG_PLATFORM					"x64"
#	define HBG_PLATFORMPRODUCTNAME		"Hambugger (x64)"
#elif defined(_WIN32)
#	define HBG_PLATFORM					"x86"
#	define HBG_PLATFORMPRODUCTNAME		"Hambugger (x86)"
#endif

#define HBG_PRODUCTNAME					"Hambugger"
#define HBG_COMPANYNAME					"Plantrue"
#define HBG_COPYRIGHT					"Copyright (C) 2010-2011 Plantrue"


// Modules
#if defined(_DEBUG)
#	define HBG_HBGMAIN					L"HbgMainD"
#	define HBG_HBGSERV					L"HbgServD"
#	define HBG_HBGCORE					L"HbgCoreD"
#	define HBG_HBGDASM					L"HbgDasmD"
#else
#	define HBG_HBGMAIN					L"HbgMain"
#	define HBG_HBGSERV					L"HbgServ"
#	define HBG_HBGCORE					L"HbgCore"
#	define HBG_HBGDASM					L"HbgDasm"
#endif // _DEBUG


#endif // _HbgVersions_H_
