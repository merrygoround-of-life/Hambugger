

/* this ALWAYS GENERATED file contains the proxy stub code */


 /* File created by MIDL compiler version 7.00.0500 */
/* at Mon Aug 29 17:32:23 2011
 */
/* Compiler settings for .\IDL\HbgDebug.idl:
    Oicf, W1, Zp8, env=Win64 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#if defined(_M_AMD64)


#pragma warning( disable: 4049 )  /* more than 64k source lines */
#if _MSC_VER >= 1200
#pragma warning(push)
#endif

#pragma warning( disable: 4211 )  /* redefine extern to static */
#pragma warning( disable: 4232 )  /* dllimport identity*/
#pragma warning( disable: 4024 )  /* array to pointer mapping*/
#pragma warning( disable: 4152 )  /* function/data pointer conversion in expression */

#define USE_STUBLESS_PROXY


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 475
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif // __RPCPROXY_H_VERSION__


#include "HbgDebug_x64_Release_h.h"

#define TYPE_FORMAT_STRING_SIZE   177                               
#define PROC_FORMAT_STRING_SIZE   621                               
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

#if !defined(__RPC_WIN64__)
#error  Invalid build platform for this stub.
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
/*  8 */	NdrFcShort( 0x50 ),	/* X64 Stack size/offset = 80 */
/* 10 */	NdrFcShort( 0x28 ),	/* 40 */
/* 12 */	NdrFcShort( 0x8 ),	/* 8 */
/* 14 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x9,		/* 9 */
/* 16 */	0xa,		/* 10 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 18 */	NdrFcShort( 0x0 ),	/* 0 */
/* 20 */	NdrFcShort( 0x3 ),	/* 3 */
/* 22 */	NdrFcShort( 0x0 ),	/* 0 */
/* 24 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter type */

/* 26 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 28 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 30 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter idThread */

/* 32 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 34 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 36 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter szContext */

/* 38 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 40 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 42 */	0xb9,		/* FC_UINT3264 */
			0x0,		/* 0 */

	/* Parameter pContext */

/* 44 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 46 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 48 */	NdrFcShort( 0x6 ),	/* Type Offset=6 */

	/* Parameter szMemoryStack */

/* 50 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 52 */	NdrFcShort( 0x28 ),	/* X64 Stack size/offset = 40 */
/* 54 */	0xb9,		/* FC_UINT3264 */
			0x0,		/* 0 */

	/* Parameter pMemoryStack */

/* 56 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 58 */	NdrFcShort( 0x30 ),	/* X64 Stack size/offset = 48 */
/* 60 */	NdrFcShort( 0x16 ),	/* Type Offset=22 */

	/* Parameter szHbgContexts */

/* 62 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 64 */	NdrFcShort( 0x38 ),	/* X64 Stack size/offset = 56 */
/* 66 */	0xb9,		/* FC_UINT3264 */
			0x0,		/* 0 */

	/* Parameter pHbgContexts */

/* 68 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 70 */	NdrFcShort( 0x40 ),	/* X64 Stack size/offset = 64 */
/* 72 */	NdrFcShort( 0x26 ),	/* Type Offset=38 */

	/* Return value */

/* 74 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 76 */	NdrFcShort( 0x48 ),	/* X64 Stack size/offset = 72 */
/* 78 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Update */

/* 80 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 82 */	NdrFcLong( 0x0 ),	/* 0 */
/* 86 */	NdrFcShort( 0x4 ),	/* 4 */
/* 88 */	NdrFcShort( 0x28 ),	/* X64 Stack size/offset = 40 */
/* 90 */	NdrFcShort( 0x10 ),	/* 16 */
/* 92 */	NdrFcShort( 0x8 ),	/* 8 */
/* 94 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 96 */	0xa,		/* 10 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 98 */	NdrFcShort( 0x0 ),	/* 0 */
/* 100 */	NdrFcShort( 0x1 ),	/* 1 */
/* 102 */	NdrFcShort( 0x0 ),	/* 0 */
/* 104 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter type */

/* 106 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 108 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 110 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter sizeData */

/* 112 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 114 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 116 */	0xb9,		/* FC_UINT3264 */
			0x0,		/* 0 */

	/* Parameter pData */

/* 118 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 120 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 122 */	NdrFcShort( 0x36 ),	/* Type Offset=54 */

	/* Return value */

/* 124 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 126 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 128 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Initialize */

/* 130 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 132 */	NdrFcLong( 0x0 ),	/* 0 */
/* 136 */	NdrFcShort( 0x3 ),	/* 3 */
/* 138 */	NdrFcShort( 0x28 ),	/* X64 Stack size/offset = 40 */
/* 140 */	NdrFcShort( 0x44 ),	/* 68 */
/* 142 */	NdrFcShort( 0x8 ),	/* 8 */
/* 144 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 146 */	0xa,		/* 10 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 148 */	NdrFcShort( 0x0 ),	/* 0 */
/* 150 */	NdrFcShort( 0x1 ),	/* 1 */
/* 152 */	NdrFcShort( 0x0 ),	/* 0 */
/* 154 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pathDebuggee */

/* 156 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 158 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 160 */	NdrFcShort( 0x44 ),	/* Type Offset=68 */

	/* Parameter riid */

/* 162 */	NdrFcShort( 0x10a ),	/* Flags:  must free, in, simple ref, */
/* 164 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 166 */	NdrFcShort( 0x50 ),	/* Type Offset=80 */

	/* Parameter pIUnkClbk */

/* 168 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 170 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 172 */	NdrFcShort( 0x5c ),	/* Type Offset=92 */

	/* Return value */

/* 174 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 176 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 178 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure InitializeEx */

/* 180 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 182 */	NdrFcLong( 0x0 ),	/* 0 */
/* 186 */	NdrFcShort( 0x4 ),	/* 4 */
/* 188 */	NdrFcShort( 0x28 ),	/* X64 Stack size/offset = 40 */
/* 190 */	NdrFcShort( 0x4c ),	/* 76 */
/* 192 */	NdrFcShort( 0x8 ),	/* 8 */
/* 194 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 196 */	0xa,		/* 10 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 198 */	NdrFcShort( 0x0 ),	/* 0 */
/* 200 */	NdrFcShort( 0x1 ),	/* 1 */
/* 202 */	NdrFcShort( 0x0 ),	/* 0 */
/* 204 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pidDebuggee */

/* 206 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 208 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 210 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter riid */

/* 212 */	NdrFcShort( 0x10a ),	/* Flags:  must free, in, simple ref, */
/* 214 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 216 */	NdrFcShort( 0x50 ),	/* Type Offset=80 */

	/* Parameter pIUnkClbk */

/* 218 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 220 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 222 */	NdrFcShort( 0x64 ),	/* Type Offset=100 */

	/* Return value */

/* 224 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 226 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 228 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Uninitialize */

/* 230 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 232 */	NdrFcLong( 0x0 ),	/* 0 */
/* 236 */	NdrFcShort( 0x5 ),	/* 5 */
/* 238 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 240 */	NdrFcShort( 0x8 ),	/* 8 */
/* 242 */	NdrFcShort( 0x8 ),	/* 8 */
/* 244 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 246 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 248 */	NdrFcShort( 0x0 ),	/* 0 */
/* 250 */	NdrFcShort( 0x0 ),	/* 0 */
/* 252 */	NdrFcShort( 0x0 ),	/* 0 */
/* 254 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter bKillDebuggee */

/* 256 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 258 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 260 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 262 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 264 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 266 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Go */

/* 268 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 270 */	NdrFcLong( 0x0 ),	/* 0 */
/* 274 */	NdrFcShort( 0x6 ),	/* 6 */
/* 276 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 278 */	NdrFcShort( 0x10 ),	/* 16 */
/* 280 */	NdrFcShort( 0x8 ),	/* 8 */
/* 282 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 284 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 286 */	NdrFcShort( 0x0 ),	/* 0 */
/* 288 */	NdrFcShort( 0x0 ),	/* 0 */
/* 290 */	NdrFcShort( 0x0 ),	/* 0 */
/* 292 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter toAddr */

/* 294 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 296 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 298 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Return value */

/* 300 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 302 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 304 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Step */

/* 306 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 308 */	NdrFcLong( 0x0 ),	/* 0 */
/* 312 */	NdrFcShort( 0x7 ),	/* 7 */
/* 314 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 316 */	NdrFcShort( 0x8 ),	/* 8 */
/* 318 */	NdrFcShort( 0x8 ),	/* 8 */
/* 320 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 322 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 324 */	NdrFcShort( 0x0 ),	/* 0 */
/* 326 */	NdrFcShort( 0x0 ),	/* 0 */
/* 328 */	NdrFcShort( 0x0 ),	/* 0 */
/* 330 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter idThread */

/* 332 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 334 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 336 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 338 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 340 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 342 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Break */

/* 344 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 346 */	NdrFcLong( 0x0 ),	/* 0 */
/* 350 */	NdrFcShort( 0x8 ),	/* 8 */
/* 352 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 354 */	NdrFcShort( 0x0 ),	/* 0 */
/* 356 */	NdrFcShort( 0x8 ),	/* 8 */
/* 358 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 360 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 362 */	NdrFcShort( 0x0 ),	/* 0 */
/* 364 */	NdrFcShort( 0x0 ),	/* 0 */
/* 366 */	NdrFcShort( 0x0 ),	/* 0 */
/* 368 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 370 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 372 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 374 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ToggleBreakpoint */

/* 376 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 378 */	NdrFcLong( 0x0 ),	/* 0 */
/* 382 */	NdrFcShort( 0x9 ),	/* 9 */
/* 384 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 386 */	NdrFcShort( 0x10 ),	/* 16 */
/* 388 */	NdrFcShort( 0x24 ),	/* 36 */
/* 390 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x3,		/* 3 */
/* 392 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 394 */	NdrFcShort( 0x0 ),	/* 0 */
/* 396 */	NdrFcShort( 0x0 ),	/* 0 */
/* 398 */	NdrFcShort( 0x0 ),	/* 0 */
/* 400 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter addr */

/* 402 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 404 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 406 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Parameter bSet */

/* 408 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 410 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 412 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 414 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 416 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 418 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ReadMemory */

/* 420 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 422 */	NdrFcLong( 0x0 ),	/* 0 */
/* 426 */	NdrFcShort( 0xa ),	/* 10 */
/* 428 */	NdrFcShort( 0x28 ),	/* X64 Stack size/offset = 40 */
/* 430 */	NdrFcShort( 0x18 ),	/* 24 */
/* 432 */	NdrFcShort( 0x8 ),	/* 8 */
/* 434 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 436 */	0xa,		/* 10 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 438 */	NdrFcShort( 0x1 ),	/* 1 */
/* 440 */	NdrFcShort( 0x1 ),	/* 1 */
/* 442 */	NdrFcShort( 0x0 ),	/* 0 */
/* 444 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter addr */

/* 446 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 448 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 450 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Parameter size */

/* 452 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 454 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 456 */	0xb9,		/* FC_UINT3264 */
			0x0,		/* 0 */

	/* Parameter pByte */

/* 458 */	NdrFcShort( 0x11b ),	/* Flags:  must size, must free, in, out, simple ref, */
/* 460 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 462 */	NdrFcShort( 0x74 ),	/* Type Offset=116 */

	/* Return value */

/* 464 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 466 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 468 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure WriteMemory */

/* 470 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 472 */	NdrFcLong( 0x0 ),	/* 0 */
/* 476 */	NdrFcShort( 0xb ),	/* 11 */
/* 478 */	NdrFcShort( 0x28 ),	/* X64 Stack size/offset = 40 */
/* 480 */	NdrFcShort( 0x18 ),	/* 24 */
/* 482 */	NdrFcShort( 0x8 ),	/* 8 */
/* 484 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 486 */	0xa,		/* 10 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 488 */	NdrFcShort( 0x0 ),	/* 0 */
/* 490 */	NdrFcShort( 0x1 ),	/* 1 */
/* 492 */	NdrFcShort( 0x0 ),	/* 0 */
/* 494 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter addr */

/* 496 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 498 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 500 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Parameter size */

/* 502 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 504 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 506 */	0xb9,		/* FC_UINT3264 */
			0x0,		/* 0 */

	/* Parameter pByte */

/* 508 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 510 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 512 */	NdrFcShort( 0x84 ),	/* Type Offset=132 */

	/* Return value */

/* 514 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 516 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 518 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure ReadContext */

/* 520 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 522 */	NdrFcLong( 0x0 ),	/* 0 */
/* 526 */	NdrFcShort( 0xc ),	/* 12 */
/* 528 */	NdrFcShort( 0x28 ),	/* X64 Stack size/offset = 40 */
/* 530 */	NdrFcShort( 0x10 ),	/* 16 */
/* 532 */	NdrFcShort( 0x8 ),	/* 8 */
/* 534 */	0x47,		/* Oi2 Flags:  srv must size, clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 536 */	0xa,		/* 10 */
			0x7,		/* Ext Flags:  new corr desc, clt corr check, srv corr check, */
/* 538 */	NdrFcShort( 0x1 ),	/* 1 */
/* 540 */	NdrFcShort( 0x1 ),	/* 1 */
/* 542 */	NdrFcShort( 0x0 ),	/* 0 */
/* 544 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter idThread */

/* 546 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 548 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 550 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter size */

/* 552 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 554 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 556 */	0xb9,		/* FC_UINT3264 */
			0x0,		/* 0 */

	/* Parameter pByte */

/* 558 */	NdrFcShort( 0x11b ),	/* Flags:  must size, must free, in, out, simple ref, */
/* 560 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 562 */	NdrFcShort( 0x94 ),	/* Type Offset=148 */

	/* Return value */

/* 564 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 566 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 568 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure WriteContext */

/* 570 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 572 */	NdrFcLong( 0x0 ),	/* 0 */
/* 576 */	NdrFcShort( 0xd ),	/* 13 */
/* 578 */	NdrFcShort( 0x28 ),	/* X64 Stack size/offset = 40 */
/* 580 */	NdrFcShort( 0x10 ),	/* 16 */
/* 582 */	NdrFcShort( 0x8 ),	/* 8 */
/* 584 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 586 */	0xa,		/* 10 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 588 */	NdrFcShort( 0x0 ),	/* 0 */
/* 590 */	NdrFcShort( 0x1 ),	/* 1 */
/* 592 */	NdrFcShort( 0x0 ),	/* 0 */
/* 594 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter idThread */

/* 596 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 598 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 600 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter size */

/* 602 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 604 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 606 */	0xb9,		/* FC_UINT3264 */
			0x0,		/* 0 */

	/* Parameter pByte */

/* 608 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 610 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 612 */	NdrFcShort( 0xa4 ),	/* Type Offset=164 */

	/* Return value */

/* 614 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 616 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 618 */	0x8,		/* FC_LONG */
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
/* 94 */	0x2b,		/* Corr desc:  parameter, FC_HYPER */
			0x0,		/*  */
/* 96 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 98 */	NdrFcShort( 0x5 ),	/* Corr flags:  early, iid_is, */
/* 100 */	
			0x2f,		/* FC_IP */
			0x5c,		/* FC_PAD */
/* 102 */	0x2b,		/* Corr desc:  parameter, FC_HYPER */
			0x0,		/*  */
/* 104 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
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
    #pragma pack(8)
    struct _PARAM_STRUCT
        {
        IHbgDebug *This;
        DWORD type;
        char Pad0[4];
        DWORD idThread;
        char Pad1[4];
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
    pStubMsg->MaxCount = (ULONG_PTR) ( ( DWORD  )pS->szContext );
}

static void __RPC_USER IHbgCallback_PromptExprEval_0001( PMIDL_STUB_MESSAGE pStubMsg )
{
    #pragma pack(8)
    struct _PARAM_STRUCT
        {
        IHbgDebug *This;
        DWORD type;
        char Pad0[4];
        DWORD idThread;
        char Pad1[4];
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
    pStubMsg->MaxCount = (ULONG_PTR) ( ( DWORD  )pS->szMemoryStack );
}

static void __RPC_USER IHbgCallback_PromptExprEval_0002( PMIDL_STUB_MESSAGE pStubMsg )
{
    #pragma pack(8)
    struct _PARAM_STRUCT
        {
        IHbgDebug *This;
        DWORD type;
        char Pad0[4];
        DWORD idThread;
        char Pad1[4];
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
    pStubMsg->MaxCount = (ULONG_PTR) ( ( DWORD  )pS->szHbgContexts );
}

static void __RPC_USER IHbgCallback_UpdateExprEval_0003( PMIDL_STUB_MESSAGE pStubMsg )
{
    #pragma pack(8)
    struct _PARAM_STRUCT
        {
        IHbgDebug *This;
        DWORD type;
        char Pad0[4];
        SIZE_T sizeData;
        BYTE *pData;
        HRESULT _RetVal;
        };
    #pragma pack()
    struct _PARAM_STRUCT *pS	=	( struct _PARAM_STRUCT * )pStubMsg->StackTop;
    
    pStubMsg->Offset = 0;
    pStubMsg->MaxCount = (ULONG_PTR) ( ( DWORD  )pS->sizeData );
}

static void __RPC_USER IHbgDebug_ReadMemoryExprEval_0004( PMIDL_STUB_MESSAGE pStubMsg )
{
    #pragma pack(8)
    struct _PARAM_STRUCT
        {
        IHbgDebug *This;
        unsigned __int64 addr;
        SIZE_T size;
        BYTE *pByte;
        HRESULT _RetVal;
        };
    #pragma pack()
    struct _PARAM_STRUCT *pS	=	( struct _PARAM_STRUCT * )pStubMsg->StackTop;
    
    pStubMsg->Offset = 0;
    pStubMsg->MaxCount = (ULONG_PTR) ( ( DWORD  )pS->size );
}

static void __RPC_USER IHbgDebug_WriteMemoryExprEval_0005( PMIDL_STUB_MESSAGE pStubMsg )
{
    #pragma pack(8)
    struct _PARAM_STRUCT
        {
        IHbgDebug *This;
        unsigned __int64 addr;
        SIZE_T size;
        BYTE *pByte;
        HRESULT _RetVal;
        };
    #pragma pack()
    struct _PARAM_STRUCT *pS	=	( struct _PARAM_STRUCT * )pStubMsg->StackTop;
    
    pStubMsg->Offset = 0;
    pStubMsg->MaxCount = (ULONG_PTR) ( ( DWORD  )pS->size );
}

static void __RPC_USER IHbgDebug_ReadContextExprEval_0006( PMIDL_STUB_MESSAGE pStubMsg )
{
    #pragma pack(8)
    struct _PARAM_STRUCT
        {
        IHbgDebug *This;
        DWORD idThread;
        char Pad0[4];
        SIZE_T size;
        BYTE *pByte;
        HRESULT _RetVal;
        };
    #pragma pack()
    struct _PARAM_STRUCT *pS	=	( struct _PARAM_STRUCT * )pStubMsg->StackTop;
    
    pStubMsg->Offset = 0;
    pStubMsg->MaxCount = (ULONG_PTR) ( ( DWORD  )pS->size );
}

static void __RPC_USER IHbgDebug_WriteContextExprEval_0007( PMIDL_STUB_MESSAGE pStubMsg )
{
    #pragma pack(8)
    struct _PARAM_STRUCT
        {
        IHbgDebug *This;
        DWORD idThread;
        char Pad0[4];
        SIZE_T size;
        BYTE *pByte;
        HRESULT _RetVal;
        };
    #pragma pack()
    struct _PARAM_STRUCT *pS	=	( struct _PARAM_STRUCT * )pStubMsg->StackTop;
    
    pStubMsg->Offset = 0;
    pStubMsg->MaxCount = (ULONG_PTR) ( ( DWORD  )pS->size );
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
   GUID={0x703CCF94,0x6517,0x43bb,{0xB1,0x6A,0xA2,0x7C,0xC9,0x67,0x55,0x64}} */

#pragma code_seg(".orpc")
static const unsigned short IHbgCallback_FormatStringOffsetTable[] =
    {
    0,
    80
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
   GUID={0x481927C2,0x29B8,0x4c96,{0xB6,0x62,0x0C,0x24,0x40,0x99,0x45,0x64}} */

#pragma code_seg(".orpc")
static const unsigned short IHbgDebug_FormatStringOffsetTable[] =
    {
    130,
    180,
    230,
    268,
    306,
    344,
    376,
    420,
    470,
    520,
    570
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
#if _MSC_VER >= 1200
#pragma warning(pop)
#endif


#endif /* defined(_M_AMD64)*/

