

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


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

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __HbgDebug_x64_Release_h_h__
#define __HbgDebug_x64_Release_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IHbgCallback_FWD_DEFINED__
#define __IHbgCallback_FWD_DEFINED__
typedef interface IHbgCallback IHbgCallback;
#endif 	/* __IHbgCallback_FWD_DEFINED__ */


#ifndef __IHbgDebug_FWD_DEFINED__
#define __IHbgDebug_FWD_DEFINED__
typedef interface IHbgDebug IHbgDebug;
#endif 	/* __IHbgDebug_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IHbgCallback_INTERFACE_DEFINED__
#define __IHbgCallback_INTERFACE_DEFINED__

/* interface IHbgCallback */
/* [uuid][object] */ 


EXTERN_C const IID IID_IHbgCallback;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("703CCF94-6517-43bb-B16A-A27CC9675564")
    IHbgCallback : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Prompt( 
            /* [in] */ DWORD type,
            /* [in] */ DWORD idThread,
            /* [in] */ SIZE_T szContext,
            /* [size_is][in] */ BYTE *pContext,
            /* [in] */ SIZE_T szMemoryStack,
            /* [size_is][in] */ BYTE *pMemoryStack,
            /* [in] */ SIZE_T szHbgContexts,
            /* [size_is][in] */ BYTE *pHbgContexts) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Update( 
            /* [in] */ DWORD type,
            /* [in] */ SIZE_T sizeData,
            /* [size_is][in] */ BYTE *pData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IHbgCallbackVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IHbgCallback * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IHbgCallback * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IHbgCallback * This);
        
        HRESULT ( STDMETHODCALLTYPE *Prompt )( 
            IHbgCallback * This,
            /* [in] */ DWORD type,
            /* [in] */ DWORD idThread,
            /* [in] */ SIZE_T szContext,
            /* [size_is][in] */ BYTE *pContext,
            /* [in] */ SIZE_T szMemoryStack,
            /* [size_is][in] */ BYTE *pMemoryStack,
            /* [in] */ SIZE_T szHbgContexts,
            /* [size_is][in] */ BYTE *pHbgContexts);
        
        HRESULT ( STDMETHODCALLTYPE *Update )( 
            IHbgCallback * This,
            /* [in] */ DWORD type,
            /* [in] */ SIZE_T sizeData,
            /* [size_is][in] */ BYTE *pData);
        
        END_INTERFACE
    } IHbgCallbackVtbl;

    interface IHbgCallback
    {
        CONST_VTBL struct IHbgCallbackVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IHbgCallback_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IHbgCallback_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IHbgCallback_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IHbgCallback_Prompt(This,type,idThread,szContext,pContext,szMemoryStack,pMemoryStack,szHbgContexts,pHbgContexts)	\
    ( (This)->lpVtbl -> Prompt(This,type,idThread,szContext,pContext,szMemoryStack,pMemoryStack,szHbgContexts,pHbgContexts) ) 

#define IHbgCallback_Update(This,type,sizeData,pData)	\
    ( (This)->lpVtbl -> Update(This,type,sizeData,pData) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IHbgCallback_INTERFACE_DEFINED__ */


#ifndef __IHbgDebug_INTERFACE_DEFINED__
#define __IHbgDebug_INTERFACE_DEFINED__

/* interface IHbgDebug */
/* [uuid][object] */ 


EXTERN_C const IID IID_IHbgDebug;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("481927C2-29B8-4c96-B662-0C2440994564")
    IHbgDebug : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Initialize( 
            /* [string][in] */ LPCWSTR pathDebuggee,
            /* [in] */ REFIID riid,
            /* [iid_is][in] */ IUnknown *pIUnkClbk) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE InitializeEx( 
            /* [in] */ DWORD pidDebuggee,
            /* [in] */ REFIID riid,
            /* [iid_is][in] */ IUnknown *pIUnkClbk) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Uninitialize( 
            /* [in] */ BOOL bKillDebuggee) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Go( 
            /* [in] */ unsigned __int64 toAddr) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Step( 
            /* [in] */ DWORD idThread) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Break( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ToggleBreakpoint( 
            /* [in] */ unsigned __int64 addr,
            /* [out] */ BOOL *bSet) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ReadMemory( 
            /* [in] */ unsigned __int64 addr,
            /* [in] */ SIZE_T size,
            /* [size_is][out][in] */ BYTE *pByte) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE WriteMemory( 
            /* [in] */ unsigned __int64 addr,
            /* [in] */ SIZE_T size,
            /* [size_is][in] */ BYTE *pByte) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ReadContext( 
            /* [in] */ DWORD idThread,
            /* [in] */ SIZE_T size,
            /* [size_is][out][in] */ BYTE *pByte) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE WriteContext( 
            /* [in] */ DWORD idThread,
            /* [in] */ SIZE_T size,
            /* [size_is][in] */ BYTE *pByte) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IHbgDebugVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IHbgDebug * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IHbgDebug * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IHbgDebug * This);
        
        HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            IHbgDebug * This,
            /* [string][in] */ LPCWSTR pathDebuggee,
            /* [in] */ REFIID riid,
            /* [iid_is][in] */ IUnknown *pIUnkClbk);
        
        HRESULT ( STDMETHODCALLTYPE *InitializeEx )( 
            IHbgDebug * This,
            /* [in] */ DWORD pidDebuggee,
            /* [in] */ REFIID riid,
            /* [iid_is][in] */ IUnknown *pIUnkClbk);
        
        HRESULT ( STDMETHODCALLTYPE *Uninitialize )( 
            IHbgDebug * This,
            /* [in] */ BOOL bKillDebuggee);
        
        HRESULT ( STDMETHODCALLTYPE *Go )( 
            IHbgDebug * This,
            /* [in] */ unsigned __int64 toAddr);
        
        HRESULT ( STDMETHODCALLTYPE *Step )( 
            IHbgDebug * This,
            /* [in] */ DWORD idThread);
        
        HRESULT ( STDMETHODCALLTYPE *Break )( 
            IHbgDebug * This);
        
        HRESULT ( STDMETHODCALLTYPE *ToggleBreakpoint )( 
            IHbgDebug * This,
            /* [in] */ unsigned __int64 addr,
            /* [out] */ BOOL *bSet);
        
        HRESULT ( STDMETHODCALLTYPE *ReadMemory )( 
            IHbgDebug * This,
            /* [in] */ unsigned __int64 addr,
            /* [in] */ SIZE_T size,
            /* [size_is][out][in] */ BYTE *pByte);
        
        HRESULT ( STDMETHODCALLTYPE *WriteMemory )( 
            IHbgDebug * This,
            /* [in] */ unsigned __int64 addr,
            /* [in] */ SIZE_T size,
            /* [size_is][in] */ BYTE *pByte);
        
        HRESULT ( STDMETHODCALLTYPE *ReadContext )( 
            IHbgDebug * This,
            /* [in] */ DWORD idThread,
            /* [in] */ SIZE_T size,
            /* [size_is][out][in] */ BYTE *pByte);
        
        HRESULT ( STDMETHODCALLTYPE *WriteContext )( 
            IHbgDebug * This,
            /* [in] */ DWORD idThread,
            /* [in] */ SIZE_T size,
            /* [size_is][in] */ BYTE *pByte);
        
        END_INTERFACE
    } IHbgDebugVtbl;

    interface IHbgDebug
    {
        CONST_VTBL struct IHbgDebugVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IHbgDebug_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IHbgDebug_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IHbgDebug_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IHbgDebug_Initialize(This,pathDebuggee,riid,pIUnkClbk)	\
    ( (This)->lpVtbl -> Initialize(This,pathDebuggee,riid,pIUnkClbk) ) 

#define IHbgDebug_InitializeEx(This,pidDebuggee,riid,pIUnkClbk)	\
    ( (This)->lpVtbl -> InitializeEx(This,pidDebuggee,riid,pIUnkClbk) ) 

#define IHbgDebug_Uninitialize(This,bKillDebuggee)	\
    ( (This)->lpVtbl -> Uninitialize(This,bKillDebuggee) ) 

#define IHbgDebug_Go(This,toAddr)	\
    ( (This)->lpVtbl -> Go(This,toAddr) ) 

#define IHbgDebug_Step(This,idThread)	\
    ( (This)->lpVtbl -> Step(This,idThread) ) 

#define IHbgDebug_Break(This)	\
    ( (This)->lpVtbl -> Break(This) ) 

#define IHbgDebug_ToggleBreakpoint(This,addr,bSet)	\
    ( (This)->lpVtbl -> ToggleBreakpoint(This,addr,bSet) ) 

#define IHbgDebug_ReadMemory(This,addr,size,pByte)	\
    ( (This)->lpVtbl -> ReadMemory(This,addr,size,pByte) ) 

#define IHbgDebug_WriteMemory(This,addr,size,pByte)	\
    ( (This)->lpVtbl -> WriteMemory(This,addr,size,pByte) ) 

#define IHbgDebug_ReadContext(This,idThread,size,pByte)	\
    ( (This)->lpVtbl -> ReadContext(This,idThread,size,pByte) ) 

#define IHbgDebug_WriteContext(This,idThread,size,pByte)	\
    ( (This)->lpVtbl -> WriteContext(This,idThread,size,pByte) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IHbgDebug_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


