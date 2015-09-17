

/* this ALWAYS GENERATED file contains the proxy stub code */


 /* File created by MIDL compiler version 7.00.0500 */
/* at Mon Aug 29 17:32:28 2011
 */
/* Compiler settings for .\IDL\HbgDebug.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#if !defined(_M_IA64) && !defined(_M_AMD64)


#pragma warning( disable: 4049 )  /* more than 64k source lines */
#if _MSC_VER >= 1200
#pragma warning(push)
#endif

#pragma warning( disable: 4211 )  /* redefine extern to static */
#pragma warning( disable: 4232 )  /* dllimport identity*/
#pragma warning( disable: 4024 )  /* array to pointer mapping*/
#pragma warning( disable: 4152 )  /* function/data pointer conversion in expression */
#pragma warning( disable: 4100 ) /* unreferenced arguments in x86 call */

#pragma optimize("", off ) 

#define USE_STUBLESS_PROXY


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 475
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif // __RPCPROXY_H_VERSION__


#include "HbgDebug_Win32_Release_h.h"

#define TYPE_FORMAT_STRING_SIZE   177                               
#define PROC_FORMAT_STRING_SIZE   595                               
#define EXPR_FORMAT_STRING_SIZE   1                                 
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   0            

typedef struct _HbgDebug_MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } HbgDebug_MIDL_TYPE_FORMAT_STRING;

typedef struct _HbgDebug_MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } HbgDebug_MIDL_PROC_FORMAT_STRING;

typedef struct _HbgDebug_MIDL_EXPR_FORMAT_STRING
    {
    long          Pad;
    unsigned char  Format[ EXPR_FORMAT_STRING_SIZE ];
    } HbgDebug_MIDL_EXPR_FORMAT_STRING;


static RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const HbgDebug_MIDL_TYPE_FORMAT_STRING HbgDebug__MIDL_TypeFormatString;
extern const HbgDebug_MIDL_PROC_FORMAT_STRING HbgDebug__MIDL_ProcFormatString;
extern const HbgDebug_MIDL_EXPR_FORMAT_STRING HbgDebug__MIDL_ExprFormatString;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IHbgCallback_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IHbgCallback_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IHbgDebug_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IHbgDebug_ProxyInfo;


extern const EXPR_EVAL ExprEvalRoutines[];

#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT50_OR_LATER)
#error You need a Windows 2000 or later to run this stub because it uses these features:
#error   /robust command line switch.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will fail with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const HbgDebug_MIDL_PROC_FORMAT_STRING HbgDebug__MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure Prompt */

			0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x3 ),	/* 3 */
/*  8 */	NdrFcShort( 0x28 ),	/* x86 Stack size/offset = 40 */
/* 10 */	NdrFcShort( 0x28 ),	/* 40 */
/* 12 */	NdrFcShort( 0x8 ),	/* 8 */
/* 14 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x9,		/* 9 */
/* 16 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 18 */	NdrFcShort( 0x0 ),	/* 0 */
/* 20 */	NdrFcShort( 0x3 ),	/* 3 */
/* 22 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter type */

/* 24 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 26 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 28 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter idThread */

/* 30 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 32 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 34 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter szContext */

/* 36 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 38 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 40 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pContext */

/* 42 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 44 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 46 */	NdrFcShort( 0x6 ),	/* Type Offset=6 */

	/* Parameter szMemoryStack */

/* 48 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 50 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 52 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pMemoryStack */

/* 54 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 56 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 58 */	NdrFcShort( 0x16 ),	/* Type Offset=22 */

	/* Parameter szHbgContexts */

/* 60 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 62 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 64 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pHbgContexts */

/* 66 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 68 */	NdrFcShort( 0x20 ),	/* x86 Stack size/offset = 32 */
/* 70 */	NdrFcShort( 0x26 ),	/* Type Offset=38 */

	/* Return value */

/* 72 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 74 */	NdrFcShort( 0x24 ),	/* x86 Stack size/offset = 36 */
/* 76 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Update */

/* 78 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 80 */	NdrFcLong( 0x0 ),	/* 0 */
/* 84 */	NdrFcShort( 0x4 ),	/* 4 */
/* 86 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 88 */	NdrFcShort( 0x10 ),	/* 16 */
/* 90 */	NdrFcShort( 0x8 ),	/* 8 */
/* 92 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 94 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 96 */	NdrFcShort( 0x0 ),	/* 0 */
/* 98 */	NdrFcShort( 0x1 ),	/* 1 */
/* 100 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter type */

/* 102 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 104 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 106 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter sizeData */

/* 108 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 110 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 112 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pData */

/* 114 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 116 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 118 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Return value */

/* 120 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 122 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 124 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Initialize */

/* 126 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 128 */	NdrFcLong( 0x0 ),	/* 0 */
/* 132 */	NdrFcShort( 0x3 ),	/* 3 */
/* 134 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 136 */	NdrFcShort( 0x44 ),	/* 68 */
/* 138 */	NdrFcShort( 0x8 ),	/* 8 */
/* 140 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 142 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 144 */	NdrFcShort( 0x0 ),	/* 0 */
/* 146 */	NdrFcShort( 0x1 ),	/* 1 */
/* 148 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pathDebuggee */

/* 150 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 152 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 154 */	NdrFcShort( 0x44 ),	/* Type Offset=68 */

	/* Parameter riid */

/* 156 */	NdrFcShort( 0x10a ),	/* Flags:  must free, in, simple ref, */
/* 158 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 160 */	NdrFcShort( 0x50 ),	/* Type Offset=80 */

	/* Parameter pIUnkClbk */

/* 162 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 164 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 166 */	NdrFcShort( 0x5c ),	/* Type Offset=92 */

	/* Return value */

/* 168 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 170 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 172 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure InitializeEx */

/* 174 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 176 */	NdrFcLong( 0x0 ),	/* 0 */
/* 180 */	NdrFcShort( 0x4 ),	/* 4 */
/* 182 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 184 */	NdrFcShort( 0x4c ),	/* 76 */
/* 186 */	NdrFcShort( 0x8 ),	/* 8 */
/* 188 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 190 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 192 */	NdrFcShort( 0x0 ),	/* 0 */
/* 194 */	NdrFcShort( 0x1 ),	/* 1 */
/* 196 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pidDebuggee */

/* 198 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 200 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 202 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter riid */

/* 204 */	NdrFcShort( 0x10a ),	/* Flags:  must free, in, simple ref, */
/* 206 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 208 */	NdrFcShort( 0x50 ),	/* Type Offset=80 */

	/* Parameter pIUnkClbk */

/* 210 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 212 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 214 */	NdrFcShort( 0x64 ),	/* Type Offset=100 */

	/* Return value */

/* 216 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 218 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 220 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Uninitialize */

/* 222 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 224 */	NdrFcLong( 0x0 ),	/* 0 */
/* 228 */	NdrFcShort( 0x5 ),	/* 5 */
/* 230 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 232 */	NdrFcShort( 0x8 ),	/* 8 */
/* 234 */	NdrFcShort( 0x8 ),	/* 8 */
/* 236 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 238 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 240 */	NdrFcShort( 0x0 ),	/* 0 */
/* 242 */	NdrFcShort( 0x0 ),	/* 0 */
/* 244 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bKillDebuggee */

/* 246 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 248 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 250 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 252 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 254 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 256 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Go */

/* 258 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 260 */	NdrFcLong( 0x0 ),	/* 0 */
/* 264 */	NdrFcShort( 0x6 ),	/* 6 */
/* 266 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 268 */	NdrFcShort( 0x8 ),	/* 8 */
/* 270 */	NdrFcShort( 0x8 ),	/* 8 */
/* 272 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 274 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 276 */	NdrFcShort( 0x0 ),	/* 0 */
/* 278 */	NdrFcShort( 0x0 ),	/* 0 */
/* 280 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter toAddr */

/* 282 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 284 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 286 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 288 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 290 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 292 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Step */

/* 294 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 296 */	NdrFcLong( 0x0 ),	/* 0 */
/* 300 */	NdrFcShort( 0x7 ),	/* 7 */
/* 302 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 304 */	NdrFcShort( 0x8 ),	/* 8 */
/* 306 */	NdrFcShort( 0x8 ),	/* 8 */
/* 308 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 310 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 312 */	NdrFcShort( 0x0 ),	/* 0 */
/* 314 */	NdrFcShort( 0x0 ),	/* 0 */
/* 316 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter idThread */

/* 318 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 320 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 322 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 324 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 326 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 328 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Break */

/* 330 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 332 */	NdrFcLong( 0x0 ),	/* 0 */
/* 336 */	NdrFcShort( 0x8 ),	/* 8 */
/* 338 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 340 */	NdrFcShort( 0x0 ),	/* 0 */
/* 342 */	NdrFcShort( 0x8 ),	/* 8 */
/* 344 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 346 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 348 */	NdrFcShort( 0x0 ),	/* 0 */
/* 350 */	NdrFcShort( 0x0 ),	/* 0 */
/* 352 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 354 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 356 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 358 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ToggleBreakpoint */

/* 360 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 362 */	NdrFcLong( 0x0 ),	/* 0 */
/* 366 */	NdrFcShort( 0x9 ),	/* 9 */
/* 368 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 370 */	NdrFcShort( 0x8 ),	/* 8 */
/* 372 */	NdrFcShort( 0x24 ),	/* 36 */
/* 374 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 376 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 378 */	NdrFcShort( 0x0 ),	/* 0 */
/* 380 */	NdrFcShort( 0x0 ),	/* 0 */
/* 382 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter addr */

/* 384 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 386 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 388 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter bSet */

/* 390 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 392 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 394 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 396 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 398 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 400 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ReadMemory */

/* 402 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 404 */	NdrFcLong( 0x0 ),	/* 0 */
/* 408 */	NdrFcShort( 0xa ),	/* 10 */
/* 410 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 412 */	NdrFcShort( 0x10 ),	/* 16 */
/* 414 */	NdrFcShort( 0x8 ),	/* 8 */
/* 416 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 418 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 420 */	NdrFcShort( 0x1 ),	/* 1 */
/* 422 */	NdrFcShort( 0x1 ),	/* 1 */
/* 424 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter addr */

/* 426 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 428 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 430 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter size */

/* 432 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 434 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 436 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pByte */

/* 438 */	NdrFcShort( 0x11b ),	/* Flags:  must size, must free, in, out, simple ref, */
/* 440 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 442 */	NdrFcShort( 0x74 ),	/* Type Offset=116 */

	/* Return value */

/* 444 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 446 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 448 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure WriteMemory */

/* 450 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 452 */	NdrFcLong( 0x0 ),	/* 0 */
/* 456 */	NdrFcShort( 0xb ),	/* 11 */
/* 458 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 460 */	NdrFcShort( 0x10 ),	/* 16 */
/* 462 */	NdrFcShort( 0x8 ),	/* 8 */
/* 464 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 466 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 468 */	NdrFcShort( 0x0 ),	/* 0 */
/* 470 */	NdrFcShort( 0x1 ),	/* 1 */
/* 472 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter addr */

/* 474 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 476 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 478 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter size */

/* 480 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 482 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 484 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pByte */

/* 486 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 488 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 490 */	NdrFcShort( 0x84 ),	/* Type Offset=132 */

	/* Return value */

/* 492 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 494 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 496 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ReadContext */

/* 498 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 500 */	NdrFcLong( 0x0 ),	/* 0 */
/* 504 */	NdrFcShort( 0xc ),	/* 12 */
/* 506 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 508 */	NdrFcShort( 0x10 ),	/* 16 */
/* 510 */	NdrFcShort( 0x8 ),	/* 8 */
/* 512 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 514 */	0x8,		/* 8 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 516 */	NdrFcShort( 0x1 ),	/* 1 */
/* 518 */	NdrFcShort( 0x1 ),	/* 1 */
/* 520 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter idThread */

/* 522 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 524 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 526 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter size */

/* 528 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 530 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 532 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pByte */

/* 534 */	NdrFcShort( 0x11b ),	/* Flags:  must size, must free, in, out, simple ref, */
/* 536 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 538 */	NdrFcShort( 0x94 ),	/* Type Offset=148 */

	/* Return value */

/* 540 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 542 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 544 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure WriteContext */

/* 546 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 548 */	NdrFcLong( 0x0 ),	/* 0 */
/* 552 */	NdrFcShort( 0xd ),	/* 13 */
/* 554 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 556 */	NdrFcShort( 0x10 ),	/* 16 */
/* 558 */	NdrFcShort( 0x8 ),	/* 8 */
/* 560 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 562 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 564 */	NdrFcShort( 0x0 ),	/* 0 */
/* 566 */	NdrFcShort( 0x1 ),	/* 1 */
/* 568 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter idThread */

/* 570 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 572 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 574 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter size */

/* 576 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 578 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 580 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pByte */

/* 582 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 584 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 586 */	NdrFcShort( 0xa4 ),	/* Type Offset=164 */

	/* Return value */

/* 588 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 590 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 592 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const HbgDebug_MIDL_TYPE_FORMAT_STRING HbgDebug__MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x11, 0x0,	/* FC_RP */
/*  4 */	NdrFcShort( 0x2 ),	/* Offset= 2 (6) */
/*  6 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/*  8 */	NdrFcShort( 0x1 ),	/* 1 */
/* 10 */	0x20,		/* Corr desc:  parameter,  */
			0x59,		/* FC_CALLBACK */
/* 12 */	NdrFcShort( 0x0 ),	/* 0 */
/* 14 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 16 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 18 */	
			0x11, 0x0,	/* FC_RP */
/* 20 */	NdrFcShort( 0x2 ),	/* Offset= 2 (22) */
/* 22 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 24 */	NdrFcShort( 0x1 ),	/* 1 */
/* 26 */	0x20,		/* Corr desc:  parameter,  */
			0x59,		/* FC_CALLBACK */
/* 28 */	NdrFcShort( 0x1 ),	/* 1 */
/* 30 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 32 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 34 */	
			0x11, 0x0,	/* FC_RP */
/* 36 */	NdrFcShort( 0x2 ),	/* Offset= 2 (38) */
/* 38 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 40 */	NdrFcShort( 0x1 ),	/* 1 */
/* 42 */	0x20,		/* Corr desc:  parameter,  */
			0x59,		/* FC_CALLBACK */
/* 44 */	NdrFcShort( 0x2 ),	/* 2 */
/* 46 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 48 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 50 */	
			0x11, 0x0,	/* FC_RP */
/* 52 */	NdrFcShort( 0x2 ),	/* Offset= 2 (54) */
/* 54 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 56 */	NdrFcShort( 0x1 ),	/* 1 */
/* 58 */	0x20,		/* Corr desc:  parameter,  */
			0x59,		/* FC_CALLBACK */
/* 60 */	NdrFcShort( 0x3 ),	/* 3 */
/* 62 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 64 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 66 */	
			0x11, 0x8,	/* FC_RP [simple_pointer] */
/* 68 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 70 */	
			0x11, 0x0,	/* FC_RP */
/* 72 */	NdrFcShort( 0x8 ),	/* Offset= 8 (80) */
/* 74 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/* 76 */	NdrFcShort( 0x8 ),	/* 8 */
/* 78 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 80 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 82 */	NdrFcShort( 0x10 ),	/* 16 */
/* 84 */	0x8,		/* FC_LONG */
			0x6,		/* FC_SHORT */
/* 86 */	0x6,		/* FC_SHORT */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 88 */	0x0,		/* 0 */
			NdrFcShort( 0xfff1 ),	/* Offset= -15 (74) */
			0x5b,		/* FC_END */
/* 92 */	
			0x2f,		/* FC_IP */
			0x5c,		/* FC_PAD */
/* 94 */	0x28,		/* Corr desc:  parameter, FC_LONG */
			0x0,		/*  */
/* 96 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 98 */	NdrFcShort( 0x5 ),	/* Corr flags:  early, iid_is, */
/* 100 */	
			0x2f,		/* FC_IP */
			0x5c,		/* FC_PAD */
/* 102 */	0x28,		/* Corr desc:  parameter, FC_LONG */
			0x0,		/*  */
/* 104 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 106 */	NdrFcShort( 0x5 ),	/* Corr flags:  early, iid_is, */
/* 108 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 110 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 112 */	
			0x11, 0x0,	/* FC_RP */
/* 114 */	NdrFcShort( 0x2 ),	/* Offset= 2 (116) */
/* 116 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 118 */	NdrFcShort( 0x1 ),	/* 1 */
/* 120 */	0x20,		/* Corr desc:  parameter,  */
			0x59,		/* FC_CALLBACK */
/* 122 */	NdrFcShort( 0x4 ),	/* 4 */
/* 124 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 126 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 128 */	
			0x11, 0x0,	/* FC_RP */
/* 130 */	NdrFcShort( 0x2 ),	/* Offset= 2 (132) */
/* 132 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 134 */	NdrFcShort( 0x1 ),	/* 1 */
/* 136 */	0x20,		/* Corr desc:  parameter,  */
			0x59,		/* FC_CALLBACK */
/* 138 */	NdrFcShort( 0x5 ),	/* 5 */
/* 140 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 142 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 144 */	
			0x11, 0x0,	/* FC_RP */
/* 146 */	NdrFcShort( 0x2 ),	/* Offset= 2 (148) */
/* 148 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 150 */	NdrFcShort( 0x1 ),	/* 1 */
/* 152 */	0x20,		/* Corr desc:  parameter,  */
			0x59,		/* FC_CALLBACK */
/* 154 */	NdrFcShort( 0x6 ),	/* 6 */
/* 156 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 158 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 160 */	
			0x11, 0x0,	/* FC_RP */
/* 162 */	NdrFcShort( 0x2 ),	/* Offset= 2 (164) */
/* 164 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 166 */	NdrFcShort( 0x1 ),	/* 1 */
/* 168 */	0x20,		/* Corr desc:  parameter,  */
			0x59,		/* FC_CALLBACK */
/* 170 */	NdrFcShort( 0x7 ),	/* 7 */
/* 172 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 174 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */

			0x0
        }
    };

static void __RPC_USER IHbgCallback_PromptExprEval_0000( PMIDL_STUB_MESSAGE pStubMsg )
{
    #pragma pack(4)
    struct _PARAM_STRUCT
        {
        IHbgDebug *This;
        DWORD type;
        DWORD idThread;
        SIZE_T szContext;
        BYTE *pContext;
        SIZE_T szMemoryStack;
        BYTE *pMemoryStack;
        SIZE_T szHbgContexts;
        BYTE *pHbgContexts;
        HRESULT _RetVal;
        };
    #pragma pack()
    struct _PARAM_STRUCT *pS	=	( struct _PARAM_STRUCT * )pStubMsg->StackTop;
    
    pStubMsg->Offset = 0;
    pStubMsg->MaxCount = ( unsigned long ) ( ( DWORD  )pS->szContext );
}

static void __RPC_USER IHbgCallback_PromptExprEval_0001( PMIDL_STUB_MESSAGE pStubMsg )
{
    #pragma pack(4)
    struct _PARAM_STRUCT
        {
        IHbgDebug *This;
        DWORD type;
        DWORD idThread;
        SIZE_T szContext;
        BYTE *pContext;
        SIZE_T szMemoryStack;
        BYTE *pMemoryStack;
        SIZE_T szHbgContexts;
        BYTE *pHbgContexts;
        HRESULT _RetVal;
        };
    #pragma pack()
    struct _PARAM_STRUCT *pS	=	( struct _PARAM_STRUCT * )pStubMsg->StackTop;
    
    pStubMsg->Offset = 0;
    pStubMsg->MaxCount = ( unsigned long ) ( ( DWORD  )pS->szMemoryStack );
}

static void __RPC_USER IHbgCallback_PromptExprEval_0002( PMIDL_STUB_MESSAGE pStubMsg )
{
    #pragma pack(4)
    struct _PARAM_STRUCT
        {
        IHbgDebug *This;
        DWORD type;
        DWORD idThread;
        SIZE_T szContext;
        BYTE *pContext;
        SIZE_T szMemoryStack;
        BYTE *pMemoryStack;
        SIZE_T szHbgContexts;
        BYTE *pHbgContexts;
        HRESULT _RetVal;
        };
    #pragma pack()
    struct _PARAM_STRUCT *pS	=	( struct _PARAM_STRUCT * )pStubMsg->StackTop;
    
    pStubMsg->Offset = 0;
    pStubMsg->MaxCount = ( unsigned long ) ( ( DWORD  )pS->szHbgContexts );
}

static void __RPC_USER IHbgCallback_UpdateExprEval_0003( PMIDL_STUB_MESSAGE pStubMsg )
{
    #pragma pack(4)
    struct _PARAM_STRUCT
        {
        IHbgDebug *This;
        DWORD type;
        SIZE_T sizeData;
        BYTE *pData;
        HRESULT _RetVal;
        };
    #pragma pack()
    struct _PARAM_STRUCT *pS	=	( struct _PARAM_STRUCT * )pStubMsg->StackTop;
    
    pStubMsg->Offset = 0;
    pStubMsg->MaxCount = ( unsigned long ) ( ( DWORD  )pS->sizeData );
}

static void __RPC_USER IHbgDebug_ReadMemoryExprEval_0004( PMIDL_STUB_MESSAGE pStubMsg )
{
    #pragma pack(4)
    struct _PARAM_STRUCT
        {
        IHbgDebug *This;
        DWORD_PTR addr;
        SIZE_T size;
        BYTE *pByte;
        HRESULT _RetVal;
        };
    #pragma pack()
    struct _PARAM_STRUCT *pS	=	( struct _PARAM_STRUCT * )pStubMsg->StackTop;
    
    pStubMsg->Offset = 0;
    pStubMsg->MaxCount = ( unsigned long ) ( ( DWORD  )pS->size );
}

static void __RPC_USER IHbgDebug_WriteMemoryExprEval_0005( PMIDL_STUB_MESSAGE pStubMsg )
{
    #pragma pack(4)
    struct _PARAM_STRUCT
        {
        IHbgDebug *This;
        DWORD_PTR addr;
        SIZE_T size;
        BYTE *pByte;
        HRESULT _RetVal;
        };
    #pragma pack()
    struct _PARAM_STRUCT *pS	=	( struct _PARAM_STRUCT * )pStubMsg->StackTop;
    
    pStubMsg->Offset = 0;
    pStubMsg->MaxCount = ( unsigned long ) ( ( DWORD  )pS->size );
}

static void __RPC_USER IHbgDebug_ReadContextExprEval_0006( PMIDL_STUB_MESSAGE pStubMsg )
{
    #pragma pack(4)
    struct _PARAM_STRUCT
        {
        IHbgDebug *This;
        DWORD idThread;
        SIZE_T size;
        BYTE *pByte;
        HRESULT _RetVal;
        };
    #pragma pack()
    struct _PARAM_STRUCT *pS	=	( struct _PARAM_STRUCT * )pStubMsg->StackTop;
    
    pStubMsg->Offset = 0;
    pStubMsg->MaxCount = ( unsigned long ) ( ( DWORD  )pS->size );
}

static void __RPC_USER IHbgDebug_WriteContextExprEval_0007( PMIDL_STUB_MESSAGE pStubMsg )
{
    #pragma pack(4)
    struct _PARAM_STRUCT
        {
        IHbgDebug *This;
        DWORD idThread;
        SIZE_T size;
        BYTE *pByte;
        HRESULT _RetVal;
        };
    #pragma pack()
    struct _PARAM_STRUCT *pS	=	( struct _PARAM_STRUCT * )pStubMsg->StackTop;
    
    pStubMsg->Offset = 0;
    pStubMsg->MaxCount = ( unsigned long ) ( ( DWORD  )pS->size );
}

static const EXPR_EVAL ExprEvalRoutines[] = 
    {
    IHbgCallback_PromptExprEval_0000
    ,IHbgCallback_PromptExprEval_0001
    ,IHbgCallback_PromptExprEval_0002
    ,IHbgCallback_UpdateExprEval_0003
    ,IHbgDebug_ReadMemoryExprEval_0004
    ,IHbgDebug_WriteMemoryExprEval_0005
    ,IHbgDebug_ReadContextExprEval_0006
    ,IHbgDebug_WriteContextExprEval_0007
    };



/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IHbgCallback, ver. 0.0,
   GUID={0x703CCF94,0x6517,0x43bb,{0xB1,0x6A,0xA2,0x7C,0xC9,0x67,0x55,0x86}} */

#pragma code_seg(".orpc")
static const unsigned short IHbgCallback_FormatStringOffsetTable[] =
    {
    0,
    78
    };

static const MIDL_STUBLESS_PROXY_INFO IHbgCallback_ProxyInfo =
    {
    &Object_StubDesc,
    HbgDebug__MIDL_ProcFormatString.Format,
    &IHbgCallback_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IHbgCallback_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    HbgDebug__MIDL_ProcFormatString.Format,
    &IHbgCallback_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(5) _IHbgCallbackProxyVtbl = 
{
    &IHbgCallback_ProxyInfo,
    &IID_IHbgCallback,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IHbgCallback::Prompt */ ,
    (void *) (INT_PTR) -1 /* IHbgCallback::Update */
};

const CInterfaceStubVtbl _IHbgCallbackStubVtbl =
{
    &IID_IHbgCallback,
    &IHbgCallback_ServerInfo,
    5,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IHbgDebug, ver. 0.0,
   GUID={0x481927C2,0x29B8,0x4c96,{0xB6,0x62,0x0C,0x24,0x40,0x99,0x45,0x86}} */

#pragma code_seg(".orpc")
static const unsigned short IHbgDebug_FormatStringOffsetTable[] =
    {
    126,
    174,
    222,
    258,
    294,
    330,
    360,
    402,
    450,
    498,
    546
    };

static const MIDL_STUBLESS_PROXY_INFO IHbgDebug_ProxyInfo =
    {
    &Object_StubDesc,
    HbgDebug__MIDL_ProcFormatString.Format,
    &IHbgDebug_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IHbgDebug_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    HbgDebug__MIDL_ProcFormatString.Format,
    &IHbgDebug_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(14) _IHbgDebugProxyVtbl = 
{
    &IHbgDebug_ProxyInfo,
    &IID_IHbgDebug,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IHbgDebug::Initialize */ ,
    (void *) (INT_PTR) -1 /* IHbgDebug::InitializeEx */ ,
    (void *) (INT_PTR) -1 /* IHbgDebug::Uninitialize */ ,
    (void *) (INT_PTR) -1 /* IHbgDebug::Go */ ,
    (void *) (INT_PTR) -1 /* IHbgDebug::Step */ ,
    (void *) (INT_PTR) -1 /* IHbgDebug::Break */ ,
    (void *) (INT_PTR) -1 /* IHbgDebug::ToggleBreakpoint */ ,
    (void *) (INT_PTR) -1 /* IHbgDebug::ReadMemory */ ,
    (void *) (INT_PTR) -1 /* IHbgDebug::WriteMemory */ ,
    (void *) (INT_PTR) -1 /* IHbgDebug::ReadContext */ ,
    (void *) (INT_PTR) -1 /* IHbgDebug::WriteContext */
};

const CInterfaceStubVtbl _IHbgDebugStubVtbl =
{
    &IID_IHbgDebug,
    &IHbgDebug_ServerInfo,
    14,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};

static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
    0,
    0,
    0,
    ExprEvalRoutines,
    0,
    HbgDebug__MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x50002, /* Ndr library version */
    0,
    0x70001f4, /* MIDL Version 7.0.500 */
    0,
    0,
    0,  /* notify & notify_flag routine table */
    0x1, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0
    };

const CInterfaceProxyVtbl * _HbgDebug_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IHbgCallbackProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IHbgDebugProxyVtbl,
    0
};

const CInterfaceStubVtbl * _HbgDebug_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IHbgCallbackStubVtbl,
    ( CInterfaceStubVtbl *) &_IHbgDebugStubVtbl,
    0
};

PCInterfaceName const _HbgDebug_InterfaceNamesList[] = 
{
    "IHbgCallback",
    "IHbgDebug",
    0
};


#define _HbgDebug_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _HbgDebug, pIID, n)

int __stdcall _HbgDebug_IID_Lookup( const IID * pIID, int * pIndex )
{
    IID_BS_LOOKUP_SETUP

    IID_BS_LOOKUP_INITIAL_TEST( _HbgDebug, 2, 1 )
    IID_BS_LOOKUP_RETURN_RESULT( _HbgDebug, 2, *pIndex )
    
}

const ExtendedProxyFileInfo HbgDebug_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _HbgDebug_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _HbgDebug_StubVtblList,
    (const PCInterfaceName * ) & _HbgDebug_InterfaceNamesList,
    0, // no delegation
    & _HbgDebug_IID_Lookup, 
    2,
    2,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};
#pragma optimize("", on )
#if _MSC_VER >= 1200
#pragma warning(pop)
#endif


#endif /* !defined(_M_IA64) && !defined(_M_AMD64)*/

