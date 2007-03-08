/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Mar 08 17:46:15 2007
 */
/* Compiler settings for E:\sourceforge\tpl\codemodel\codemodel.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __codemodel_i_h__
#define __codemodel_i_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __CodeModel_FWD_DEFINED__
#define __CodeModel_FWD_DEFINED__
typedef interface CodeModel CodeModel;
#endif 	/* __CodeModel_FWD_DEFINED__ */


#ifndef __CodeElements_FWD_DEFINED__
#define __CodeElements_FWD_DEFINED__
typedef interface CodeElements CodeElements;
#endif 	/* __CodeElements_FWD_DEFINED__ */


#ifndef __CodeElement_FWD_DEFINED__
#define __CodeElement_FWD_DEFINED__
typedef interface CodeElement CodeElement;
#endif 	/* __CodeElement_FWD_DEFINED__ */


#ifndef __CodeNamespace_FWD_DEFINED__
#define __CodeNamespace_FWD_DEFINED__
typedef interface CodeNamespace CodeNamespace;
#endif 	/* __CodeNamespace_FWD_DEFINED__ */


#ifndef __CodeClass_FWD_DEFINED__
#define __CodeClass_FWD_DEFINED__
typedef interface CodeClass CodeClass;
#endif 	/* __CodeClass_FWD_DEFINED__ */


#ifndef __CodeFunction_FWD_DEFINED__
#define __CodeFunction_FWD_DEFINED__
typedef interface CodeFunction CodeFunction;
#endif 	/* __CodeFunction_FWD_DEFINED__ */


#ifndef __CodeVariable_FWD_DEFINED__
#define __CodeVariable_FWD_DEFINED__
typedef interface CodeVariable CodeVariable;
#endif 	/* __CodeVariable_FWD_DEFINED__ */


#ifndef __CodeParameter_FWD_DEFINED__
#define __CodeParameter_FWD_DEFINED__
typedef interface CodeParameter CodeParameter;
#endif 	/* __CodeParameter_FWD_DEFINED__ */


#ifndef __CodeTypeRef_FWD_DEFINED__
#define __CodeTypeRef_FWD_DEFINED__
typedef interface CodeTypeRef CodeTypeRef;
#endif 	/* __CodeTypeRef_FWD_DEFINED__ */


#ifndef __CodeType_FWD_DEFINED__
#define __CodeType_FWD_DEFINED__
typedef interface CodeType CodeType;
#endif 	/* __CodeType_FWD_DEFINED__ */


#ifndef __TextPoint_FWD_DEFINED__
#define __TextPoint_FWD_DEFINED__
typedef interface TextPoint TextPoint;
#endif 	/* __TextPoint_FWD_DEFINED__ */


#ifndef __CCodeModel_FWD_DEFINED__
#define __CCodeModel_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCodeModel CCodeModel;
#else
typedef struct CCodeModel CCodeModel;
#endif /* __cplusplus */

#endif 	/* __CCodeModel_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __CODEMODELLib_LIBRARY_DEFINED__
#define __CODEMODELLib_LIBRARY_DEFINED__

/* library CODEMODELLib */
/* [helpstring][version][uuid] */ 













enum vsCMPart
    {	vsCMPartName	= 1,
	vsCMPartAttributes	= 2,
	vsCMPartHeader	= 4,
	vsCMPartWhole	= 8,
	vsCMPartBody	= 16,
	vsCMPartNavigate	= 32,
	vsCMPartAttributesWithDelimiter	= 68,
	vsCMPartBodyWithDelimiter	= 80,
	vsCMPartHeaderWithAttributes	= 6,
	vsCMPartWholeWithAttributes	= 10
    };

enum vsCMTypeRef
    {	vsCMTypeRefOther	= 0,
	vsCMTypeRefCodeType	= 1,
	vsCMTypeRefArray	= 2,
	vsCMTypeRefVoid	= 3,
	vsCMTypeRefPointer	= 4,
	vsCMTypeRefString	= 5,
	vsCMTypeRefObject	= 6,
	vsCMTypeRefByte	= 7,
	vsCMTypeRefChar	= 8,
	vsCMTypeRefShort	= 9,
	vsCMTypeRefInt	= 10,
	vsCMTypeRefLong	= 11,
	vsCMTypeRefFloat	= 12,
	vsCMTypeRefDouble	= 13,
	vsCMTypeRefDecimal	= 14,
	vsCMTypeRefBool	= 15,
	vsCMTypeRefVariant	= 16
    };

enum vsCMAccess
    {	vsCMAccessPublic	= 1,
	vsCMAccessPrivate	= 2,
	vsCMAccessProject	= 4,
	vsCMAccessProtected	= 8,
	vsCMAccessDefault	= 32,
	vsCMAccessAssemblyOrFamily	= 64,
	vsCMAccessWithEvents	= 128,
	vsCMAccessProjectOrProtected	= 12
    };

enum vsCMElement
    {	vsCMElementOther	= 0,
	vsCMElementClass	= 1,
	vsCMElementFunction	= 2,
	vsCMElementVariable	= 3,
	vsCMElementProperty	= 4,
	vsCMElementNamespace	= 5,
	vsCMElementParameter	= 6,
	vsCMElementAttribute	= 7,
	vsCMElementInterface	= 8,
	vsCMElementDelegate	= 9,
	vsCMElementEnum	= 10,
	vsCMElementStruct	= 11,
	vsCMElementUnion	= 12,
	vsCMElementLocalDeclStmt	= 13,
	vsCMElementFunctionInvokeStmt	= 14,
	vsCMElementPropertySetStmt	= 15,
	vsCMElementAssignmentStmt	= 16,
	vsCMElementInheritsStmt	= 17,
	vsCMElementImplementsStmt	= 18,
	vsCMElementOptionStmt	= 19,
	vsCMElementVBAttributeStmt	= 20,
	vsCMElementVBAttributeGroup	= 21,
	vsCMElementEventsDeclaration	= 22,
	vsCMElementUDTDecl	= 23,
	vsCMElementDeclareDecl	= 24,
	vsCMElementDefineStmt	= 25,
	vsCMElementTypeDef	= 26,
	vsCMElementIncludeStmt	= 27,
	vsCMElementUsingStmt	= 28,
	vsCMElementMacro	= 29,
	vsCMElementMap	= 30,
	vsCMElementIDLImport	= 31,
	vsCMElementIDLImportLib	= 32,
	vsCMElementIDLCoClass	= 33,
	vsCMElementIDLLibrary	= 34,
	vsCMElementImportStmt	= 35,
	vsCMElementMapEntry	= 36,
	vsCMElementVCBase	= 37,
	vsCMElementEvent	= 38,
	vsCMElementModule	= 39
    };

enum vsCMInfoLocation
    {	vsCMInfoLocationProject	= 1,
	vsCMInfoLocationExternal	= 2,
	vsCMInfoLocationNone	= 4,
	vsCMInfoLocationVirtual	= 8
    };

enum vsCMFunction
    {	vsCMFunctionOther	= 0,
	vsCMFunctionConstructor	= 1,
	vsCMFunctionPropertyGet	= 2,
	vsCMFunctionPropertyLet	= 4,
	vsCMFunctionPropertySet	= 8,
	vsCMFunctionPutRef	= 16,
	vsCMFunctionPropertyAssign	= 32,
	vsCMFunctionSub	= 64,
	vsCMFunctionFunction	= 128,
	vsCMFunctionTopLevel	= 256,
	vsCMFunctionDestructor	= 512,
	vsCMFunctionOperator	= 1024,
	vsCMFunctionVirtual	= 2048,
	vsCMFunctionPure	= 4096,
	vsCMFunctionConstant	= 8192,
	vsCMFunctionShared	= 16384,
	vsCMFunctionInline	= 32768,
	vsCMFunctionComMethod	= 65536
    };

EXTERN_C const IID LIBID_CODEMODELLib;

#ifndef __CodeModel_INTERFACE_DEFINED__
#define __CodeModel_INTERFACE_DEFINED__

/* interface CodeModel */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_CodeModel;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A35694B3-DACB-4772-B8C9-E4357E7BEE0E")
    CodeModel : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CodeElements( 
            /* [retval][out] */ CodeElements __RPC_FAR *__RPC_FAR *ppCodeElements) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsCaseSensitive( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pSensitive) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ VARIANT Element) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddNamespace( 
            /* [in] */ BSTR Name,
            /* [in] */ VARIANT Location,
            /* [in] */ VARIANT Position,
            /* [retval][out] */ CodeNamespace __RPC_FAR *__RPC_FAR *ppCodeNamespace) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddClass( 
            /* [in] */ BSTR Name,
            /* [in] */ VARIANT Location,
            /* [in] */ VARIANT Position,
            /* [in] */ VARIANT Bases,
            /* [in] */ VARIANT ImplementedInterfaces,
            /* [retval][out] */ CodeClass __RPC_FAR *__RPC_FAR *ppCodeClass) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddFunction( 
            /* [in] */ BSTR Name,
            /* [in] */ VARIANT Location,
            /* [in] */ enum vsCMFunction Kind,
            /* [in] */ VARIANT Type,
            /* [in] */ VARIANT Position,
            /* [in] */ enum vsCMAccess Access,
            /* [retval][out] */ CodeFunction __RPC_FAR *__RPC_FAR *ppCodeFunction) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddVariable( 
            /* [in] */ BSTR Name,
            /* [in] */ VARIANT Location,
            /* [in] */ VARIANT Type,
            /* [in] */ VARIANT Position,
            /* [in] */ enum vsCMAccess Access,
            /* [retval][out] */ CodeVariable __RPC_FAR *__RPC_FAR *ppCodeVariable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IsValidID( 
            /* [in] */ BSTR Name,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pValid) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct CodeModelVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            CodeModel __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            CodeModel __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            CodeModel __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            CodeModel __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            CodeModel __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            CodeModel __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            CodeModel __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CodeElements )( 
            CodeModel __RPC_FAR * This,
            /* [retval][out] */ CodeElements __RPC_FAR *__RPC_FAR *ppCodeElements);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsCaseSensitive )( 
            CodeModel __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pSensitive);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            CodeModel __RPC_FAR * This,
            /* [in] */ VARIANT Element);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddNamespace )( 
            CodeModel __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [in] */ VARIANT Location,
            /* [in] */ VARIANT Position,
            /* [retval][out] */ CodeNamespace __RPC_FAR *__RPC_FAR *ppCodeNamespace);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddClass )( 
            CodeModel __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [in] */ VARIANT Location,
            /* [in] */ VARIANT Position,
            /* [in] */ VARIANT Bases,
            /* [in] */ VARIANT ImplementedInterfaces,
            /* [retval][out] */ CodeClass __RPC_FAR *__RPC_FAR *ppCodeClass);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddFunction )( 
            CodeModel __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [in] */ VARIANT Location,
            /* [in] */ enum vsCMFunction Kind,
            /* [in] */ VARIANT Type,
            /* [in] */ VARIANT Position,
            /* [in] */ enum vsCMAccess Access,
            /* [retval][out] */ CodeFunction __RPC_FAR *__RPC_FAR *ppCodeFunction);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddVariable )( 
            CodeModel __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [in] */ VARIANT Location,
            /* [in] */ VARIANT Type,
            /* [in] */ VARIANT Position,
            /* [in] */ enum vsCMAccess Access,
            /* [retval][out] */ CodeVariable __RPC_FAR *__RPC_FAR *ppCodeVariable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsValidID )( 
            CodeModel __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pValid);
        
        END_INTERFACE
    } CodeModelVtbl;

    interface CodeModel
    {
        CONST_VTBL struct CodeModelVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define CodeModel_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define CodeModel_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define CodeModel_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define CodeModel_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define CodeModel_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define CodeModel_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define CodeModel_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define CodeModel_get_CodeElements(This,ppCodeElements)	\
    (This)->lpVtbl -> get_CodeElements(This,ppCodeElements)

#define CodeModel_get_IsCaseSensitive(This,pSensitive)	\
    (This)->lpVtbl -> get_IsCaseSensitive(This,pSensitive)

#define CodeModel_Remove(This,Element)	\
    (This)->lpVtbl -> Remove(This,Element)

#define CodeModel_AddNamespace(This,Name,Location,Position,ppCodeNamespace)	\
    (This)->lpVtbl -> AddNamespace(This,Name,Location,Position,ppCodeNamespace)

#define CodeModel_AddClass(This,Name,Location,Position,Bases,ImplementedInterfaces,ppCodeClass)	\
    (This)->lpVtbl -> AddClass(This,Name,Location,Position,Bases,ImplementedInterfaces,ppCodeClass)

#define CodeModel_AddFunction(This,Name,Location,Kind,Type,Position,Access,ppCodeFunction)	\
    (This)->lpVtbl -> AddFunction(This,Name,Location,Kind,Type,Position,Access,ppCodeFunction)

#define CodeModel_AddVariable(This,Name,Location,Type,Position,Access,ppCodeVariable)	\
    (This)->lpVtbl -> AddVariable(This,Name,Location,Type,Position,Access,ppCodeVariable)

#define CodeModel_IsValidID(This,Name,pValid)	\
    (This)->lpVtbl -> IsValidID(This,Name,pValid)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE CodeModel_get_CodeElements_Proxy( 
    CodeModel __RPC_FAR * This,
    /* [retval][out] */ CodeElements __RPC_FAR *__RPC_FAR *ppCodeElements);


void __RPC_STUB CodeModel_get_CodeElements_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE CodeModel_get_IsCaseSensitive_Proxy( 
    CodeModel __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pSensitive);


void __RPC_STUB CodeModel_get_IsCaseSensitive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CodeModel_Remove_Proxy( 
    CodeModel __RPC_FAR * This,
    /* [in] */ VARIANT Element);


void __RPC_STUB CodeModel_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CodeModel_AddNamespace_Proxy( 
    CodeModel __RPC_FAR * This,
    /* [in] */ BSTR Name,
    /* [in] */ VARIANT Location,
    /* [in] */ VARIANT Position,
    /* [retval][out] */ CodeNamespace __RPC_FAR *__RPC_FAR *ppCodeNamespace);


void __RPC_STUB CodeModel_AddNamespace_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CodeModel_AddClass_Proxy( 
    CodeModel __RPC_FAR * This,
    /* [in] */ BSTR Name,
    /* [in] */ VARIANT Location,
    /* [in] */ VARIANT Position,
    /* [in] */ VARIANT Bases,
    /* [in] */ VARIANT ImplementedInterfaces,
    /* [retval][out] */ CodeClass __RPC_FAR *__RPC_FAR *ppCodeClass);


void __RPC_STUB CodeModel_AddClass_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CodeModel_AddFunction_Proxy( 
    CodeModel __RPC_FAR * This,
    /* [in] */ BSTR Name,
    /* [in] */ VARIANT Location,
    /* [in] */ enum vsCMFunction Kind,
    /* [in] */ VARIANT Type,
    /* [in] */ VARIANT Position,
    /* [in] */ enum vsCMAccess Access,
    /* [retval][out] */ CodeFunction __RPC_FAR *__RPC_FAR *ppCodeFunction);


void __RPC_STUB CodeModel_AddFunction_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CodeModel_AddVariable_Proxy( 
    CodeModel __RPC_FAR * This,
    /* [in] */ BSTR Name,
    /* [in] */ VARIANT Location,
    /* [in] */ VARIANT Type,
    /* [in] */ VARIANT Position,
    /* [in] */ enum vsCMAccess Access,
    /* [retval][out] */ CodeVariable __RPC_FAR *__RPC_FAR *ppCodeVariable);


void __RPC_STUB CodeModel_AddVariable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CodeModel_IsValidID_Proxy( 
    CodeModel __RPC_FAR * This,
    /* [in] */ BSTR Name,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pValid);


void __RPC_STUB CodeModel_IsValidID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __CodeModel_INTERFACE_DEFINED__ */


#ifndef __CodeElements_INTERFACE_DEFINED__
#define __CodeElements_INTERFACE_DEFINED__

/* interface CodeElements */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_CodeElements;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4D77AA14-DFB6-4ACD-A17E-D5406EDF8234")
    CodeElements : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE _NewEnum( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *lppiuReturn) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ VARIANT index,
            /* [retval][out] */ CodeElement __RPC_FAR *__RPC_FAR *ppCodeElement) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct CodeElementsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            CodeElements __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            CodeElements __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            CodeElements __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            CodeElements __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            CodeElements __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            CodeElements __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            CodeElements __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_NewEnum )( 
            CodeElements __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *lppiuReturn);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Item )( 
            CodeElements __RPC_FAR * This,
            /* [in] */ VARIANT index,
            /* [retval][out] */ CodeElement __RPC_FAR *__RPC_FAR *ppCodeElement);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            CodeElements __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        END_INTERFACE
    } CodeElementsVtbl;

    interface CodeElements
    {
        CONST_VTBL struct CodeElementsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define CodeElements_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define CodeElements_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define CodeElements_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define CodeElements_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define CodeElements_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define CodeElements_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define CodeElements_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define CodeElements__NewEnum(This,lppiuReturn)	\
    (This)->lpVtbl -> _NewEnum(This,lppiuReturn)

#define CodeElements_Item(This,index,ppCodeElement)	\
    (This)->lpVtbl -> Item(This,index,ppCodeElement)

#define CodeElements_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CodeElements__NewEnum_Proxy( 
    CodeElements __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *lppiuReturn);


void __RPC_STUB CodeElements__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CodeElements_Item_Proxy( 
    CodeElements __RPC_FAR * This,
    /* [in] */ VARIANT index,
    /* [retval][out] */ CodeElement __RPC_FAR *__RPC_FAR *ppCodeElement);


void __RPC_STUB CodeElements_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE CodeElements_get_Count_Proxy( 
    CodeElements __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB CodeElements_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __CodeElements_INTERFACE_DEFINED__ */


#ifndef __CodeElement_INTERFACE_DEFINED__
#define __CodeElement_INTERFACE_DEFINED__

/* interface CodeElement */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_CodeElement;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E25A22E8-3508-4A0F-A37E-A92B849E27E6")
    CodeElement : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FullName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Kind( 
            /* [retval][out] */ enum vsCMElement __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsCodeType( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_InfoLocation( 
            /* [retval][out] */ enum vsCMInfoLocation __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Children( 
            /* [retval][out] */ CodeElements __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StartPoint( 
            /* [retval][out] */ TextPoint __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EndPoint( 
            /* [retval][out] */ TextPoint __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetStartPoint( 
            /* [in] */ enum vsCMPart Part,
            /* [retval][out] */ TextPoint __RPC_FAR *__RPC_FAR *ppTextPoint) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetEndPoint( 
            /* [in] */ enum vsCMPart Part,
            /* [retval][out] */ TextPoint __RPC_FAR *__RPC_FAR *ppTextPoint) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct CodeElementVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            CodeElement __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            CodeElement __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            CodeElement __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            CodeElement __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            CodeElement __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            CodeElement __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            CodeElement __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            CodeElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Name )( 
            CodeElement __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FullName )( 
            CodeElement __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Kind )( 
            CodeElement __RPC_FAR * This,
            /* [retval][out] */ enum vsCMElement __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsCodeType )( 
            CodeElement __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InfoLocation )( 
            CodeElement __RPC_FAR * This,
            /* [retval][out] */ enum vsCMInfoLocation __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Children )( 
            CodeElement __RPC_FAR * This,
            /* [retval][out] */ CodeElements __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StartPoint )( 
            CodeElement __RPC_FAR * This,
            /* [retval][out] */ TextPoint __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EndPoint )( 
            CodeElement __RPC_FAR * This,
            /* [retval][out] */ TextPoint __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetStartPoint )( 
            CodeElement __RPC_FAR * This,
            /* [in] */ enum vsCMPart Part,
            /* [retval][out] */ TextPoint __RPC_FAR *__RPC_FAR *ppTextPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEndPoint )( 
            CodeElement __RPC_FAR * This,
            /* [in] */ enum vsCMPart Part,
            /* [retval][out] */ TextPoint __RPC_FAR *__RPC_FAR *ppTextPoint);
        
        END_INTERFACE
    } CodeElementVtbl;

    interface CodeElement
    {
        CONST_VTBL struct CodeElementVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define CodeElement_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define CodeElement_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define CodeElement_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define CodeElement_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define CodeElement_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define CodeElement_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define CodeElement_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define CodeElement_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define CodeElement_put_Name(This,newVal)	\
    (This)->lpVtbl -> put_Name(This,newVal)

#define CodeElement_get_FullName(This,pVal)	\
    (This)->lpVtbl -> get_FullName(This,pVal)

#define CodeElement_get_Kind(This,pVal)	\
    (This)->lpVtbl -> get_Kind(This,pVal)

#define CodeElement_get_IsCodeType(This,pVal)	\
    (This)->lpVtbl -> get_IsCodeType(This,pVal)

#define CodeElement_get_InfoLocation(This,pVal)	\
    (This)->lpVtbl -> get_InfoLocation(This,pVal)

#define CodeElement_get_Children(This,pVal)	\
    (This)->lpVtbl -> get_Children(This,pVal)

#define CodeElement_get_StartPoint(This,pVal)	\
    (This)->lpVtbl -> get_StartPoint(This,pVal)

#define CodeElement_get_EndPoint(This,pVal)	\
    (This)->lpVtbl -> get_EndPoint(This,pVal)

#define CodeElement_GetStartPoint(This,Part,ppTextPoint)	\
    (This)->lpVtbl -> GetStartPoint(This,Part,ppTextPoint)

#define CodeElement_GetEndPoint(This,Part,ppTextPoint)	\
    (This)->lpVtbl -> GetEndPoint(This,Part,ppTextPoint)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE CodeElement_get_Name_Proxy( 
    CodeElement __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB CodeElement_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE CodeElement_put_Name_Proxy( 
    CodeElement __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB CodeElement_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE CodeElement_get_FullName_Proxy( 
    CodeElement __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB CodeElement_get_FullName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE CodeElement_get_Kind_Proxy( 
    CodeElement __RPC_FAR * This,
    /* [retval][out] */ enum vsCMElement __RPC_FAR *pVal);


void __RPC_STUB CodeElement_get_Kind_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE CodeElement_get_IsCodeType_Proxy( 
    CodeElement __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB CodeElement_get_IsCodeType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE CodeElement_get_InfoLocation_Proxy( 
    CodeElement __RPC_FAR * This,
    /* [retval][out] */ enum vsCMInfoLocation __RPC_FAR *pVal);


void __RPC_STUB CodeElement_get_InfoLocation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE CodeElement_get_Children_Proxy( 
    CodeElement __RPC_FAR * This,
    /* [retval][out] */ CodeElements __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB CodeElement_get_Children_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE CodeElement_get_StartPoint_Proxy( 
    CodeElement __RPC_FAR * This,
    /* [retval][out] */ TextPoint __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB CodeElement_get_StartPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE CodeElement_get_EndPoint_Proxy( 
    CodeElement __RPC_FAR * This,
    /* [retval][out] */ TextPoint __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB CodeElement_get_EndPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CodeElement_GetStartPoint_Proxy( 
    CodeElement __RPC_FAR * This,
    /* [in] */ enum vsCMPart Part,
    /* [retval][out] */ TextPoint __RPC_FAR *__RPC_FAR *ppTextPoint);


void __RPC_STUB CodeElement_GetStartPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CodeElement_GetEndPoint_Proxy( 
    CodeElement __RPC_FAR * This,
    /* [in] */ enum vsCMPart Part,
    /* [retval][out] */ TextPoint __RPC_FAR *__RPC_FAR *ppTextPoint);


void __RPC_STUB CodeElement_GetEndPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __CodeElement_INTERFACE_DEFINED__ */


#ifndef __CodeNamespace_INTERFACE_DEFINED__
#define __CodeNamespace_INTERFACE_DEFINED__

/* interface CodeNamespace */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_CodeNamespace;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("49695717-2D36-4806-B13D-1AFDC6C5D2C5")
    CodeNamespace : public CodeElement
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ VARIANT Element) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddNamespace( 
            /* [in] */ BSTR Name,
            /* [in] */ VARIANT Location,
            /* [in] */ VARIANT Position,
            /* [retval][out] */ CodeNamespace __RPC_FAR *__RPC_FAR *ppCodeNamespace) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddClass( 
            /* [in] */ BSTR Name,
            /* [in] */ VARIANT Location,
            /* [in] */ VARIANT Position,
            VARIANT Bases,
            VARIANT ImplementedInterfaces,
            /* [retval][out] */ CodeClass __RPC_FAR *__RPC_FAR *ppCodeClass) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddFunction( 
            /* [in] */ BSTR Name,
            /* [in] */ VARIANT Location,
            /* [in] */ enum vsCMFunction Kind,
            /* [in] */ VARIANT Type,
            /* [in] */ VARIANT Position,
            /* [in] */ enum vsCMAccess Access,
            /* [retval][out] */ CodeFunction __RPC_FAR *__RPC_FAR *ppCodeFunction) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddVariable( 
            /* [in] */ BSTR Name,
            /* [in] */ VARIANT Location,
            /* [in] */ VARIANT Type,
            /* [in] */ VARIANT Position,
            /* [in] */ enum vsCMAccess Access,
            /* [retval][out] */ CodeVariable __RPC_FAR *__RPC_FAR *ppCodeVariable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IsValidID( 
            /* [in] */ BSTR Name,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pValid) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Members( 
            /* [retval][out] */ CodeElements __RPC_FAR *__RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct CodeNamespaceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            CodeNamespace __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            CodeNamespace __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            CodeNamespace __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            CodeNamespace __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            CodeNamespace __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            CodeNamespace __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            CodeNamespace __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            CodeNamespace __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Name )( 
            CodeNamespace __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FullName )( 
            CodeNamespace __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Kind )( 
            CodeNamespace __RPC_FAR * This,
            /* [retval][out] */ enum vsCMElement __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsCodeType )( 
            CodeNamespace __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InfoLocation )( 
            CodeNamespace __RPC_FAR * This,
            /* [retval][out] */ enum vsCMInfoLocation __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Children )( 
            CodeNamespace __RPC_FAR * This,
            /* [retval][out] */ CodeElements __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StartPoint )( 
            CodeNamespace __RPC_FAR * This,
            /* [retval][out] */ TextPoint __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EndPoint )( 
            CodeNamespace __RPC_FAR * This,
            /* [retval][out] */ TextPoint __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetStartPoint )( 
            CodeNamespace __RPC_FAR * This,
            /* [in] */ enum vsCMPart Part,
            /* [retval][out] */ TextPoint __RPC_FAR *__RPC_FAR *ppTextPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEndPoint )( 
            CodeNamespace __RPC_FAR * This,
            /* [in] */ enum vsCMPart Part,
            /* [retval][out] */ TextPoint __RPC_FAR *__RPC_FAR *ppTextPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            CodeNamespace __RPC_FAR * This,
            /* [in] */ VARIANT Element);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddNamespace )( 
            CodeNamespace __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [in] */ VARIANT Location,
            /* [in] */ VARIANT Position,
            /* [retval][out] */ CodeNamespace __RPC_FAR *__RPC_FAR *ppCodeNamespace);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddClass )( 
            CodeNamespace __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [in] */ VARIANT Location,
            /* [in] */ VARIANT Position,
            VARIANT Bases,
            VARIANT ImplementedInterfaces,
            /* [retval][out] */ CodeClass __RPC_FAR *__RPC_FAR *ppCodeClass);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddFunction )( 
            CodeNamespace __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [in] */ VARIANT Location,
            /* [in] */ enum vsCMFunction Kind,
            /* [in] */ VARIANT Type,
            /* [in] */ VARIANT Position,
            /* [in] */ enum vsCMAccess Access,
            /* [retval][out] */ CodeFunction __RPC_FAR *__RPC_FAR *ppCodeFunction);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddVariable )( 
            CodeNamespace __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [in] */ VARIANT Location,
            /* [in] */ VARIANT Type,
            /* [in] */ VARIANT Position,
            /* [in] */ enum vsCMAccess Access,
            /* [retval][out] */ CodeVariable __RPC_FAR *__RPC_FAR *ppCodeVariable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsValidID )( 
            CodeNamespace __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pValid);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Members )( 
            CodeNamespace __RPC_FAR * This,
            /* [retval][out] */ CodeElements __RPC_FAR *__RPC_FAR *pVal);
        
        END_INTERFACE
    } CodeNamespaceVtbl;

    interface CodeNamespace
    {
        CONST_VTBL struct CodeNamespaceVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define CodeNamespace_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define CodeNamespace_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define CodeNamespace_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define CodeNamespace_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define CodeNamespace_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define CodeNamespace_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define CodeNamespace_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define CodeNamespace_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define CodeNamespace_put_Name(This,newVal)	\
    (This)->lpVtbl -> put_Name(This,newVal)

#define CodeNamespace_get_FullName(This,pVal)	\
    (This)->lpVtbl -> get_FullName(This,pVal)

#define CodeNamespace_get_Kind(This,pVal)	\
    (This)->lpVtbl -> get_Kind(This,pVal)

#define CodeNamespace_get_IsCodeType(This,pVal)	\
    (This)->lpVtbl -> get_IsCodeType(This,pVal)

#define CodeNamespace_get_InfoLocation(This,pVal)	\
    (This)->lpVtbl -> get_InfoLocation(This,pVal)

#define CodeNamespace_get_Children(This,pVal)	\
    (This)->lpVtbl -> get_Children(This,pVal)

#define CodeNamespace_get_StartPoint(This,pVal)	\
    (This)->lpVtbl -> get_StartPoint(This,pVal)

#define CodeNamespace_get_EndPoint(This,pVal)	\
    (This)->lpVtbl -> get_EndPoint(This,pVal)

#define CodeNamespace_GetStartPoint(This,Part,ppTextPoint)	\
    (This)->lpVtbl -> GetStartPoint(This,Part,ppTextPoint)

#define CodeNamespace_GetEndPoint(This,Part,ppTextPoint)	\
    (This)->lpVtbl -> GetEndPoint(This,Part,ppTextPoint)


#define CodeNamespace_Remove(This,Element)	\
    (This)->lpVtbl -> Remove(This,Element)

#define CodeNamespace_AddNamespace(This,Name,Location,Position,ppCodeNamespace)	\
    (This)->lpVtbl -> AddNamespace(This,Name,Location,Position,ppCodeNamespace)

#define CodeNamespace_AddClass(This,Name,Location,Position,Bases,ImplementedInterfaces,ppCodeClass)	\
    (This)->lpVtbl -> AddClass(This,Name,Location,Position,Bases,ImplementedInterfaces,ppCodeClass)

#define CodeNamespace_AddFunction(This,Name,Location,Kind,Type,Position,Access,ppCodeFunction)	\
    (This)->lpVtbl -> AddFunction(This,Name,Location,Kind,Type,Position,Access,ppCodeFunction)

#define CodeNamespace_AddVariable(This,Name,Location,Type,Position,Access,ppCodeVariable)	\
    (This)->lpVtbl -> AddVariable(This,Name,Location,Type,Position,Access,ppCodeVariable)

#define CodeNamespace_IsValidID(This,Name,pValid)	\
    (This)->lpVtbl -> IsValidID(This,Name,pValid)

#define CodeNamespace_get_Members(This,pVal)	\
    (This)->lpVtbl -> get_Members(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CodeNamespace_Remove_Proxy( 
    CodeNamespace __RPC_FAR * This,
    /* [in] */ VARIANT Element);


void __RPC_STUB CodeNamespace_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CodeNamespace_AddNamespace_Proxy( 
    CodeNamespace __RPC_FAR * This,
    /* [in] */ BSTR Name,
    /* [in] */ VARIANT Location,
    /* [in] */ VARIANT Position,
    /* [retval][out] */ CodeNamespace __RPC_FAR *__RPC_FAR *ppCodeNamespace);


void __RPC_STUB CodeNamespace_AddNamespace_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CodeNamespace_AddClass_Proxy( 
    CodeNamespace __RPC_FAR * This,
    /* [in] */ BSTR Name,
    /* [in] */ VARIANT Location,
    /* [in] */ VARIANT Position,
    VARIANT Bases,
    VARIANT ImplementedInterfaces,
    /* [retval][out] */ CodeClass __RPC_FAR *__RPC_FAR *ppCodeClass);


void __RPC_STUB CodeNamespace_AddClass_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CodeNamespace_AddFunction_Proxy( 
    CodeNamespace __RPC_FAR * This,
    /* [in] */ BSTR Name,
    /* [in] */ VARIANT Location,
    /* [in] */ enum vsCMFunction Kind,
    /* [in] */ VARIANT Type,
    /* [in] */ VARIANT Position,
    /* [in] */ enum vsCMAccess Access,
    /* [retval][out] */ CodeFunction __RPC_FAR *__RPC_FAR *ppCodeFunction);


void __RPC_STUB CodeNamespace_AddFunction_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CodeNamespace_AddVariable_Proxy( 
    CodeNamespace __RPC_FAR * This,
    /* [in] */ BSTR Name,
    /* [in] */ VARIANT Location,
    /* [in] */ VARIANT Type,
    /* [in] */ VARIANT Position,
    /* [in] */ enum vsCMAccess Access,
    /* [retval][out] */ CodeVariable __RPC_FAR *__RPC_FAR *ppCodeVariable);


void __RPC_STUB CodeNamespace_AddVariable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CodeNamespace_IsValidID_Proxy( 
    CodeNamespace __RPC_FAR * This,
    /* [in] */ BSTR Name,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pValid);


void __RPC_STUB CodeNamespace_IsValidID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE CodeNamespace_get_Members_Proxy( 
    CodeNamespace __RPC_FAR * This,
    /* [retval][out] */ CodeElements __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB CodeNamespace_get_Members_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __CodeNamespace_INTERFACE_DEFINED__ */


#ifndef __CodeClass_INTERFACE_DEFINED__
#define __CodeClass_INTERFACE_DEFINED__

/* interface CodeClass */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_CodeClass;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C5D1B2C7-CCDB-49B9-80B7-D18169612145")
    CodeClass : public CodeElement
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddClass( 
            /* [in] */ BSTR Name,
            /* [in] */ VARIANT Location,
            /* [in] */ VARIANT Position,
            VARIANT Bases,
            VARIANT ImplementedInterfaces,
            /* [retval][out] */ CodeClass __RPC_FAR *__RPC_FAR *ppCodeClass) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddFunction( 
            /* [in] */ BSTR Name,
            /* [in] */ VARIANT Location,
            /* [in] */ enum vsCMFunction Kind,
            /* [in] */ VARIANT Type,
            /* [in] */ VARIANT Position,
            /* [in] */ enum vsCMAccess Access,
            /* [retval][out] */ CodeFunction __RPC_FAR *__RPC_FAR *ppCodeFunction) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddVariable( 
            /* [in] */ BSTR Name,
            /* [in] */ VARIANT Location,
            /* [in] */ VARIANT Type,
            /* [in] */ VARIANT Position,
            /* [in] */ enum vsCMAccess Access,
            /* [retval][out] */ CodeVariable __RPC_FAR *__RPC_FAR *ppCodeVariable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IsValidID( 
            /* [in] */ BSTR Name,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pValid) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Members( 
            /* [retval][out] */ CodeElements __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Namespace( 
            /* [retval][out] */ CodeNamespace __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Bases( 
            /* [retval][out] */ CodeElements __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddBase( 
            /* [in] */ VARIANT Base,
            /* [in] */ VARIANT Position,
            /* [retval][out] */ CodeElement __RPC_FAR *__RPC_FAR *ppOut) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveBase( 
            /* [in] */ VARIANT Element) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveMember( 
            /* [in] */ VARIANT Element) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsDerivedFrom( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct CodeClassVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            CodeClass __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            CodeClass __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            CodeClass __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            CodeClass __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            CodeClass __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            CodeClass __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            CodeClass __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            CodeClass __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Name )( 
            CodeClass __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FullName )( 
            CodeClass __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Kind )( 
            CodeClass __RPC_FAR * This,
            /* [retval][out] */ enum vsCMElement __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsCodeType )( 
            CodeClass __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InfoLocation )( 
            CodeClass __RPC_FAR * This,
            /* [retval][out] */ enum vsCMInfoLocation __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Children )( 
            CodeClass __RPC_FAR * This,
            /* [retval][out] */ CodeElements __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StartPoint )( 
            CodeClass __RPC_FAR * This,
            /* [retval][out] */ TextPoint __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EndPoint )( 
            CodeClass __RPC_FAR * This,
            /* [retval][out] */ TextPoint __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetStartPoint )( 
            CodeClass __RPC_FAR * This,
            /* [in] */ enum vsCMPart Part,
            /* [retval][out] */ TextPoint __RPC_FAR *__RPC_FAR *ppTextPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEndPoint )( 
            CodeClass __RPC_FAR * This,
            /* [in] */ enum vsCMPart Part,
            /* [retval][out] */ TextPoint __RPC_FAR *__RPC_FAR *ppTextPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddClass )( 
            CodeClass __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [in] */ VARIANT Location,
            /* [in] */ VARIANT Position,
            VARIANT Bases,
            VARIANT ImplementedInterfaces,
            /* [retval][out] */ CodeClass __RPC_FAR *__RPC_FAR *ppCodeClass);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddFunction )( 
            CodeClass __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [in] */ VARIANT Location,
            /* [in] */ enum vsCMFunction Kind,
            /* [in] */ VARIANT Type,
            /* [in] */ VARIANT Position,
            /* [in] */ enum vsCMAccess Access,
            /* [retval][out] */ CodeFunction __RPC_FAR *__RPC_FAR *ppCodeFunction);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddVariable )( 
            CodeClass __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [in] */ VARIANT Location,
            /* [in] */ VARIANT Type,
            /* [in] */ VARIANT Position,
            /* [in] */ enum vsCMAccess Access,
            /* [retval][out] */ CodeVariable __RPC_FAR *__RPC_FAR *ppCodeVariable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsValidID )( 
            CodeClass __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pValid);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Members )( 
            CodeClass __RPC_FAR * This,
            /* [retval][out] */ CodeElements __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Namespace )( 
            CodeClass __RPC_FAR * This,
            /* [retval][out] */ CodeNamespace __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Bases )( 
            CodeClass __RPC_FAR * This,
            /* [retval][out] */ CodeElements __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddBase )( 
            CodeClass __RPC_FAR * This,
            /* [in] */ VARIANT Base,
            /* [in] */ VARIANT Position,
            /* [retval][out] */ CodeElement __RPC_FAR *__RPC_FAR *ppOut);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveBase )( 
            CodeClass __RPC_FAR * This,
            /* [in] */ VARIANT Element);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveMember )( 
            CodeClass __RPC_FAR * This,
            /* [in] */ VARIANT Element);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsDerivedFrom )( 
            CodeClass __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        END_INTERFACE
    } CodeClassVtbl;

    interface CodeClass
    {
        CONST_VTBL struct CodeClassVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define CodeClass_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define CodeClass_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define CodeClass_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define CodeClass_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define CodeClass_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define CodeClass_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define CodeClass_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define CodeClass_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define CodeClass_put_Name(This,newVal)	\
    (This)->lpVtbl -> put_Name(This,newVal)

#define CodeClass_get_FullName(This,pVal)	\
    (This)->lpVtbl -> get_FullName(This,pVal)

#define CodeClass_get_Kind(This,pVal)	\
    (This)->lpVtbl -> get_Kind(This,pVal)

#define CodeClass_get_IsCodeType(This,pVal)	\
    (This)->lpVtbl -> get_IsCodeType(This,pVal)

#define CodeClass_get_InfoLocation(This,pVal)	\
    (This)->lpVtbl -> get_InfoLocation(This,pVal)

#define CodeClass_get_Children(This,pVal)	\
    (This)->lpVtbl -> get_Children(This,pVal)

#define CodeClass_get_StartPoint(This,pVal)	\
    (This)->lpVtbl -> get_StartPoint(This,pVal)

#define CodeClass_get_EndPoint(This,pVal)	\
    (This)->lpVtbl -> get_EndPoint(This,pVal)

#define CodeClass_GetStartPoint(This,Part,ppTextPoint)	\
    (This)->lpVtbl -> GetStartPoint(This,Part,ppTextPoint)

#define CodeClass_GetEndPoint(This,Part,ppTextPoint)	\
    (This)->lpVtbl -> GetEndPoint(This,Part,ppTextPoint)


#define CodeClass_AddClass(This,Name,Location,Position,Bases,ImplementedInterfaces,ppCodeClass)	\
    (This)->lpVtbl -> AddClass(This,Name,Location,Position,Bases,ImplementedInterfaces,ppCodeClass)

#define CodeClass_AddFunction(This,Name,Location,Kind,Type,Position,Access,ppCodeFunction)	\
    (This)->lpVtbl -> AddFunction(This,Name,Location,Kind,Type,Position,Access,ppCodeFunction)

#define CodeClass_AddVariable(This,Name,Location,Type,Position,Access,ppCodeVariable)	\
    (This)->lpVtbl -> AddVariable(This,Name,Location,Type,Position,Access,ppCodeVariable)

#define CodeClass_IsValidID(This,Name,pValid)	\
    (This)->lpVtbl -> IsValidID(This,Name,pValid)

#define CodeClass_get_Members(This,pVal)	\
    (This)->lpVtbl -> get_Members(This,pVal)

#define CodeClass_get_Namespace(This,pVal)	\
    (This)->lpVtbl -> get_Namespace(This,pVal)

#define CodeClass_get_Bases(This,pVal)	\
    (This)->lpVtbl -> get_Bases(This,pVal)

#define CodeClass_AddBase(This,Base,Position,ppOut)	\
    (This)->lpVtbl -> AddBase(This,Base,Position,ppOut)

#define CodeClass_RemoveBase(This,Element)	\
    (This)->lpVtbl -> RemoveBase(This,Element)

#define CodeClass_RemoveMember(This,Element)	\
    (This)->lpVtbl -> RemoveMember(This,Element)

#define CodeClass_get_IsDerivedFrom(This,pVal)	\
    (This)->lpVtbl -> get_IsDerivedFrom(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CodeClass_AddClass_Proxy( 
    CodeClass __RPC_FAR * This,
    /* [in] */ BSTR Name,
    /* [in] */ VARIANT Location,
    /* [in] */ VARIANT Position,
    VARIANT Bases,
    VARIANT ImplementedInterfaces,
    /* [retval][out] */ CodeClass __RPC_FAR *__RPC_FAR *ppCodeClass);


void __RPC_STUB CodeClass_AddClass_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CodeClass_AddFunction_Proxy( 
    CodeClass __RPC_FAR * This,
    /* [in] */ BSTR Name,
    /* [in] */ VARIANT Location,
    /* [in] */ enum vsCMFunction Kind,
    /* [in] */ VARIANT Type,
    /* [in] */ VARIANT Position,
    /* [in] */ enum vsCMAccess Access,
    /* [retval][out] */ CodeFunction __RPC_FAR *__RPC_FAR *ppCodeFunction);


void __RPC_STUB CodeClass_AddFunction_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CodeClass_AddVariable_Proxy( 
    CodeClass __RPC_FAR * This,
    /* [in] */ BSTR Name,
    /* [in] */ VARIANT Location,
    /* [in] */ VARIANT Type,
    /* [in] */ VARIANT Position,
    /* [in] */ enum vsCMAccess Access,
    /* [retval][out] */ CodeVariable __RPC_FAR *__RPC_FAR *ppCodeVariable);


void __RPC_STUB CodeClass_AddVariable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CodeClass_IsValidID_Proxy( 
    CodeClass __RPC_FAR * This,
    /* [in] */ BSTR Name,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pValid);


void __RPC_STUB CodeClass_IsValidID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE CodeClass_get_Members_Proxy( 
    CodeClass __RPC_FAR * This,
    /* [retval][out] */ CodeElements __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB CodeClass_get_Members_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE CodeClass_get_Namespace_Proxy( 
    CodeClass __RPC_FAR * This,
    /* [retval][out] */ CodeNamespace __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB CodeClass_get_Namespace_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE CodeClass_get_Bases_Proxy( 
    CodeClass __RPC_FAR * This,
    /* [retval][out] */ CodeElements __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB CodeClass_get_Bases_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CodeClass_AddBase_Proxy( 
    CodeClass __RPC_FAR * This,
    /* [in] */ VARIANT Base,
    /* [in] */ VARIANT Position,
    /* [retval][out] */ CodeElement __RPC_FAR *__RPC_FAR *ppOut);


void __RPC_STUB CodeClass_AddBase_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CodeClass_RemoveBase_Proxy( 
    CodeClass __RPC_FAR * This,
    /* [in] */ VARIANT Element);


void __RPC_STUB CodeClass_RemoveBase_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CodeClass_RemoveMember_Proxy( 
    CodeClass __RPC_FAR * This,
    /* [in] */ VARIANT Element);


void __RPC_STUB CodeClass_RemoveMember_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE CodeClass_get_IsDerivedFrom_Proxy( 
    CodeClass __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB CodeClass_get_IsDerivedFrom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __CodeClass_INTERFACE_DEFINED__ */


#ifndef __CodeFunction_INTERFACE_DEFINED__
#define __CodeFunction_INTERFACE_DEFINED__

/* interface CodeFunction */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_CodeFunction;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7D2E83DD-588D-4B5A-B95C-6BB18FBF4E6C")
    CodeFunction : public CodeElement
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FunctionKind( 
            /* [retval][out] */ enum vsCMFunction __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Type( 
            /* [retval][out] */ CodeTypeRef __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Type( 
            /* [in] */ CodeTypeRef __RPC_FAR *newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Parameters( 
            /* [retval][out] */ CodeElements __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Access( 
            /* [retval][out] */ enum vsCMAccess __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Access( 
            /* [in] */ enum vsCMAccess newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddParameter( 
            /* [in] */ BSTR Name,
            /* [in] */ VARIANT Type,
            /* [in] */ VARIANT Position,
            /* [retval][out] */ CodeParameter __RPC_FAR *__RPC_FAR *ppCodeParameter) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveParameter( 
            /* [in] */ VARIANT Element) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct CodeFunctionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            CodeFunction __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            CodeFunction __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            CodeFunction __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            CodeFunction __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            CodeFunction __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            CodeFunction __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            CodeFunction __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            CodeFunction __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Name )( 
            CodeFunction __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FullName )( 
            CodeFunction __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Kind )( 
            CodeFunction __RPC_FAR * This,
            /* [retval][out] */ enum vsCMElement __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsCodeType )( 
            CodeFunction __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InfoLocation )( 
            CodeFunction __RPC_FAR * This,
            /* [retval][out] */ enum vsCMInfoLocation __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Children )( 
            CodeFunction __RPC_FAR * This,
            /* [retval][out] */ CodeElements __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StartPoint )( 
            CodeFunction __RPC_FAR * This,
            /* [retval][out] */ TextPoint __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EndPoint )( 
            CodeFunction __RPC_FAR * This,
            /* [retval][out] */ TextPoint __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetStartPoint )( 
            CodeFunction __RPC_FAR * This,
            /* [in] */ enum vsCMPart Part,
            /* [retval][out] */ TextPoint __RPC_FAR *__RPC_FAR *ppTextPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEndPoint )( 
            CodeFunction __RPC_FAR * This,
            /* [in] */ enum vsCMPart Part,
            /* [retval][out] */ TextPoint __RPC_FAR *__RPC_FAR *ppTextPoint);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FunctionKind )( 
            CodeFunction __RPC_FAR * This,
            /* [retval][out] */ enum vsCMFunction __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Type )( 
            CodeFunction __RPC_FAR * This,
            /* [retval][out] */ CodeTypeRef __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Type )( 
            CodeFunction __RPC_FAR * This,
            /* [in] */ CodeTypeRef __RPC_FAR *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parameters )( 
            CodeFunction __RPC_FAR * This,
            /* [retval][out] */ CodeElements __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Access )( 
            CodeFunction __RPC_FAR * This,
            /* [retval][out] */ enum vsCMAccess __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Access )( 
            CodeFunction __RPC_FAR * This,
            /* [in] */ enum vsCMAccess newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddParameter )( 
            CodeFunction __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [in] */ VARIANT Type,
            /* [in] */ VARIANT Position,
            /* [retval][out] */ CodeParameter __RPC_FAR *__RPC_FAR *ppCodeParameter);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveParameter )( 
            CodeFunction __RPC_FAR * This,
            /* [in] */ VARIANT Element);
        
        END_INTERFACE
    } CodeFunctionVtbl;

    interface CodeFunction
    {
        CONST_VTBL struct CodeFunctionVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define CodeFunction_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define CodeFunction_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define CodeFunction_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define CodeFunction_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define CodeFunction_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define CodeFunction_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define CodeFunction_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define CodeFunction_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define CodeFunction_put_Name(This,newVal)	\
    (This)->lpVtbl -> put_Name(This,newVal)

#define CodeFunction_get_FullName(This,pVal)	\
    (This)->lpVtbl -> get_FullName(This,pVal)

#define CodeFunction_get_Kind(This,pVal)	\
    (This)->lpVtbl -> get_Kind(This,pVal)

#define CodeFunction_get_IsCodeType(This,pVal)	\
    (This)->lpVtbl -> get_IsCodeType(This,pVal)

#define CodeFunction_get_InfoLocation(This,pVal)	\
    (This)->lpVtbl -> get_InfoLocation(This,pVal)

#define CodeFunction_get_Children(This,pVal)	\
    (This)->lpVtbl -> get_Children(This,pVal)

#define CodeFunction_get_StartPoint(This,pVal)	\
    (This)->lpVtbl -> get_StartPoint(This,pVal)

#define CodeFunction_get_EndPoint(This,pVal)	\
    (This)->lpVtbl -> get_EndPoint(This,pVal)

#define CodeFunction_GetStartPoint(This,Part,ppTextPoint)	\
    (This)->lpVtbl -> GetStartPoint(This,Part,ppTextPoint)

#define CodeFunction_GetEndPoint(This,Part,ppTextPoint)	\
    (This)->lpVtbl -> GetEndPoint(This,Part,ppTextPoint)


#define CodeFunction_get_FunctionKind(This,pVal)	\
    (This)->lpVtbl -> get_FunctionKind(This,pVal)

#define CodeFunction_get_Type(This,pVal)	\
    (This)->lpVtbl -> get_Type(This,pVal)

#define CodeFunction_put_Type(This,newVal)	\
    (This)->lpVtbl -> put_Type(This,newVal)

#define CodeFunction_get_Parameters(This,pVal)	\
    (This)->lpVtbl -> get_Parameters(This,pVal)

#define CodeFunction_get_Access(This,pVal)	\
    (This)->lpVtbl -> get_Access(This,pVal)

#define CodeFunction_put_Access(This,newVal)	\
    (This)->lpVtbl -> put_Access(This,newVal)

#define CodeFunction_AddParameter(This,Name,Type,Position,ppCodeParameter)	\
    (This)->lpVtbl -> AddParameter(This,Name,Type,Position,ppCodeParameter)

#define CodeFunction_RemoveParameter(This,Element)	\
    (This)->lpVtbl -> RemoveParameter(This,Element)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE CodeFunction_get_FunctionKind_Proxy( 
    CodeFunction __RPC_FAR * This,
    /* [retval][out] */ enum vsCMFunction __RPC_FAR *pVal);


void __RPC_STUB CodeFunction_get_FunctionKind_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE CodeFunction_get_Type_Proxy( 
    CodeFunction __RPC_FAR * This,
    /* [retval][out] */ CodeTypeRef __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB CodeFunction_get_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE CodeFunction_put_Type_Proxy( 
    CodeFunction __RPC_FAR * This,
    /* [in] */ CodeTypeRef __RPC_FAR *newVal);


void __RPC_STUB CodeFunction_put_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE CodeFunction_get_Parameters_Proxy( 
    CodeFunction __RPC_FAR * This,
    /* [retval][out] */ CodeElements __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB CodeFunction_get_Parameters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE CodeFunction_get_Access_Proxy( 
    CodeFunction __RPC_FAR * This,
    /* [retval][out] */ enum vsCMAccess __RPC_FAR *pVal);


void __RPC_STUB CodeFunction_get_Access_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE CodeFunction_put_Access_Proxy( 
    CodeFunction __RPC_FAR * This,
    /* [in] */ enum vsCMAccess newVal);


void __RPC_STUB CodeFunction_put_Access_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CodeFunction_AddParameter_Proxy( 
    CodeFunction __RPC_FAR * This,
    /* [in] */ BSTR Name,
    /* [in] */ VARIANT Type,
    /* [in] */ VARIANT Position,
    /* [retval][out] */ CodeParameter __RPC_FAR *__RPC_FAR *ppCodeParameter);


void __RPC_STUB CodeFunction_AddParameter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CodeFunction_RemoveParameter_Proxy( 
    CodeFunction __RPC_FAR * This,
    /* [in] */ VARIANT Element);


void __RPC_STUB CodeFunction_RemoveParameter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __CodeFunction_INTERFACE_DEFINED__ */


#ifndef __CodeVariable_INTERFACE_DEFINED__
#define __CodeVariable_INTERFACE_DEFINED__

/* interface CodeVariable */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_CodeVariable;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0D0C13FA-B397-4E0C-9695-C6C0D3B5FC99")
    CodeVariable : public CodeElement
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Type( 
            /* [retval][out] */ CodeTypeRef __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Type( 
            /* [in] */ CodeTypeRef __RPC_FAR *newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Access( 
            /* [retval][out] */ enum vsCMAccess __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Access( 
            /* [in] */ enum vsCMAccess newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsConstant( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_IsConstant( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct CodeVariableVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            CodeVariable __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            CodeVariable __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            CodeVariable __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            CodeVariable __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            CodeVariable __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            CodeVariable __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            CodeVariable __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            CodeVariable __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Name )( 
            CodeVariable __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FullName )( 
            CodeVariable __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Kind )( 
            CodeVariable __RPC_FAR * This,
            /* [retval][out] */ enum vsCMElement __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsCodeType )( 
            CodeVariable __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InfoLocation )( 
            CodeVariable __RPC_FAR * This,
            /* [retval][out] */ enum vsCMInfoLocation __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Children )( 
            CodeVariable __RPC_FAR * This,
            /* [retval][out] */ CodeElements __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StartPoint )( 
            CodeVariable __RPC_FAR * This,
            /* [retval][out] */ TextPoint __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EndPoint )( 
            CodeVariable __RPC_FAR * This,
            /* [retval][out] */ TextPoint __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetStartPoint )( 
            CodeVariable __RPC_FAR * This,
            /* [in] */ enum vsCMPart Part,
            /* [retval][out] */ TextPoint __RPC_FAR *__RPC_FAR *ppTextPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEndPoint )( 
            CodeVariable __RPC_FAR * This,
            /* [in] */ enum vsCMPart Part,
            /* [retval][out] */ TextPoint __RPC_FAR *__RPC_FAR *ppTextPoint);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Type )( 
            CodeVariable __RPC_FAR * This,
            /* [retval][out] */ CodeTypeRef __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Type )( 
            CodeVariable __RPC_FAR * This,
            /* [in] */ CodeTypeRef __RPC_FAR *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Access )( 
            CodeVariable __RPC_FAR * This,
            /* [retval][out] */ enum vsCMAccess __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Access )( 
            CodeVariable __RPC_FAR * This,
            /* [in] */ enum vsCMAccess newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsConstant )( 
            CodeVariable __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_IsConstant )( 
            CodeVariable __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        END_INTERFACE
    } CodeVariableVtbl;

    interface CodeVariable
    {
        CONST_VTBL struct CodeVariableVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define CodeVariable_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define CodeVariable_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define CodeVariable_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define CodeVariable_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define CodeVariable_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define CodeVariable_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define CodeVariable_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define CodeVariable_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define CodeVariable_put_Name(This,newVal)	\
    (This)->lpVtbl -> put_Name(This,newVal)

#define CodeVariable_get_FullName(This,pVal)	\
    (This)->lpVtbl -> get_FullName(This,pVal)

#define CodeVariable_get_Kind(This,pVal)	\
    (This)->lpVtbl -> get_Kind(This,pVal)

#define CodeVariable_get_IsCodeType(This,pVal)	\
    (This)->lpVtbl -> get_IsCodeType(This,pVal)

#define CodeVariable_get_InfoLocation(This,pVal)	\
    (This)->lpVtbl -> get_InfoLocation(This,pVal)

#define CodeVariable_get_Children(This,pVal)	\
    (This)->lpVtbl -> get_Children(This,pVal)

#define CodeVariable_get_StartPoint(This,pVal)	\
    (This)->lpVtbl -> get_StartPoint(This,pVal)

#define CodeVariable_get_EndPoint(This,pVal)	\
    (This)->lpVtbl -> get_EndPoint(This,pVal)

#define CodeVariable_GetStartPoint(This,Part,ppTextPoint)	\
    (This)->lpVtbl -> GetStartPoint(This,Part,ppTextPoint)

#define CodeVariable_GetEndPoint(This,Part,ppTextPoint)	\
    (This)->lpVtbl -> GetEndPoint(This,Part,ppTextPoint)


#define CodeVariable_get_Type(This,pVal)	\
    (This)->lpVtbl -> get_Type(This,pVal)

#define CodeVariable_put_Type(This,newVal)	\
    (This)->lpVtbl -> put_Type(This,newVal)

#define CodeVariable_get_Access(This,pVal)	\
    (This)->lpVtbl -> get_Access(This,pVal)

#define CodeVariable_put_Access(This,newVal)	\
    (This)->lpVtbl -> put_Access(This,newVal)

#define CodeVariable_get_IsConstant(This,pVal)	\
    (This)->lpVtbl -> get_IsConstant(This,pVal)

#define CodeVariable_put_IsConstant(This,newVal)	\
    (This)->lpVtbl -> put_IsConstant(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE CodeVariable_get_Type_Proxy( 
    CodeVariable __RPC_FAR * This,
    /* [retval][out] */ CodeTypeRef __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB CodeVariable_get_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE CodeVariable_put_Type_Proxy( 
    CodeVariable __RPC_FAR * This,
    /* [in] */ CodeTypeRef __RPC_FAR *newVal);


void __RPC_STUB CodeVariable_put_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE CodeVariable_get_Access_Proxy( 
    CodeVariable __RPC_FAR * This,
    /* [retval][out] */ enum vsCMAccess __RPC_FAR *pVal);


void __RPC_STUB CodeVariable_get_Access_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE CodeVariable_put_Access_Proxy( 
    CodeVariable __RPC_FAR * This,
    /* [in] */ enum vsCMAccess newVal);


void __RPC_STUB CodeVariable_put_Access_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE CodeVariable_get_IsConstant_Proxy( 
    CodeVariable __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB CodeVariable_get_IsConstant_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE CodeVariable_put_IsConstant_Proxy( 
    CodeVariable __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB CodeVariable_put_IsConstant_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __CodeVariable_INTERFACE_DEFINED__ */


#ifndef __CodeParameter_INTERFACE_DEFINED__
#define __CodeParameter_INTERFACE_DEFINED__

/* interface CodeParameter */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_CodeParameter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8AB948E0-759A-4616-B12F-CBDDF76B9FDF")
    CodeParameter : public CodeElement
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Type( 
            /* [retval][out] */ CodeTypeRef __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Type( 
            /* [in] */ CodeTypeRef __RPC_FAR *newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct CodeParameterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            CodeParameter __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            CodeParameter __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            CodeParameter __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            CodeParameter __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            CodeParameter __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            CodeParameter __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            CodeParameter __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            CodeParameter __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Name )( 
            CodeParameter __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FullName )( 
            CodeParameter __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Kind )( 
            CodeParameter __RPC_FAR * This,
            /* [retval][out] */ enum vsCMElement __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsCodeType )( 
            CodeParameter __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InfoLocation )( 
            CodeParameter __RPC_FAR * This,
            /* [retval][out] */ enum vsCMInfoLocation __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Children )( 
            CodeParameter __RPC_FAR * This,
            /* [retval][out] */ CodeElements __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StartPoint )( 
            CodeParameter __RPC_FAR * This,
            /* [retval][out] */ TextPoint __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EndPoint )( 
            CodeParameter __RPC_FAR * This,
            /* [retval][out] */ TextPoint __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetStartPoint )( 
            CodeParameter __RPC_FAR * This,
            /* [in] */ enum vsCMPart Part,
            /* [retval][out] */ TextPoint __RPC_FAR *__RPC_FAR *ppTextPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEndPoint )( 
            CodeParameter __RPC_FAR * This,
            /* [in] */ enum vsCMPart Part,
            /* [retval][out] */ TextPoint __RPC_FAR *__RPC_FAR *ppTextPoint);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Type )( 
            CodeParameter __RPC_FAR * This,
            /* [retval][out] */ CodeTypeRef __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Type )( 
            CodeParameter __RPC_FAR * This,
            /* [in] */ CodeTypeRef __RPC_FAR *newVal);
        
        END_INTERFACE
    } CodeParameterVtbl;

    interface CodeParameter
    {
        CONST_VTBL struct CodeParameterVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define CodeParameter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define CodeParameter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define CodeParameter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define CodeParameter_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define CodeParameter_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define CodeParameter_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define CodeParameter_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define CodeParameter_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define CodeParameter_put_Name(This,newVal)	\
    (This)->lpVtbl -> put_Name(This,newVal)

#define CodeParameter_get_FullName(This,pVal)	\
    (This)->lpVtbl -> get_FullName(This,pVal)

#define CodeParameter_get_Kind(This,pVal)	\
    (This)->lpVtbl -> get_Kind(This,pVal)

#define CodeParameter_get_IsCodeType(This,pVal)	\
    (This)->lpVtbl -> get_IsCodeType(This,pVal)

#define CodeParameter_get_InfoLocation(This,pVal)	\
    (This)->lpVtbl -> get_InfoLocation(This,pVal)

#define CodeParameter_get_Children(This,pVal)	\
    (This)->lpVtbl -> get_Children(This,pVal)

#define CodeParameter_get_StartPoint(This,pVal)	\
    (This)->lpVtbl -> get_StartPoint(This,pVal)

#define CodeParameter_get_EndPoint(This,pVal)	\
    (This)->lpVtbl -> get_EndPoint(This,pVal)

#define CodeParameter_GetStartPoint(This,Part,ppTextPoint)	\
    (This)->lpVtbl -> GetStartPoint(This,Part,ppTextPoint)

#define CodeParameter_GetEndPoint(This,Part,ppTextPoint)	\
    (This)->lpVtbl -> GetEndPoint(This,Part,ppTextPoint)


#define CodeParameter_get_Type(This,pVal)	\
    (This)->lpVtbl -> get_Type(This,pVal)

#define CodeParameter_put_Type(This,newVal)	\
    (This)->lpVtbl -> put_Type(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE CodeParameter_get_Type_Proxy( 
    CodeParameter __RPC_FAR * This,
    /* [retval][out] */ CodeTypeRef __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB CodeParameter_get_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE CodeParameter_put_Type_Proxy( 
    CodeParameter __RPC_FAR * This,
    /* [in] */ CodeTypeRef __RPC_FAR *newVal);


void __RPC_STUB CodeParameter_put_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __CodeParameter_INTERFACE_DEFINED__ */


#ifndef __CodeTypeRef_INTERFACE_DEFINED__
#define __CodeTypeRef_INTERFACE_DEFINED__

/* interface CodeTypeRef */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_CodeTypeRef;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F172B96C-7426-4D76-8CE3-A8019B5D8AA1")
    CodeTypeRef : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TypeKind( 
            /* [retval][out] */ enum vsCMTypeRef __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CodeType( 
            /* [retval][out] */ CodeType __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CodeType( 
            /* [in] */ CodeType __RPC_FAR *newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ElementType( 
            /* [retval][out] */ CodeTypeRef __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ElementType( 
            /* [in] */ CodeTypeRef __RPC_FAR *newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Rank( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Rank( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AsString( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateArrayType( 
            /* [in] */ long Rank,
            /* [retval][out] */ CodeTypeRef __RPC_FAR *__RPC_FAR *ppTypeRef) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct CodeTypeRefVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            CodeTypeRef __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            CodeTypeRef __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            CodeTypeRef __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            CodeTypeRef __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            CodeTypeRef __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            CodeTypeRef __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            CodeTypeRef __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TypeKind )( 
            CodeTypeRef __RPC_FAR * This,
            /* [retval][out] */ enum vsCMTypeRef __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CodeType )( 
            CodeTypeRef __RPC_FAR * This,
            /* [retval][out] */ CodeType __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CodeType )( 
            CodeTypeRef __RPC_FAR * This,
            /* [in] */ CodeType __RPC_FAR *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ElementType )( 
            CodeTypeRef __RPC_FAR * This,
            /* [retval][out] */ CodeTypeRef __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ElementType )( 
            CodeTypeRef __RPC_FAR * This,
            /* [in] */ CodeTypeRef __RPC_FAR *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Rank )( 
            CodeTypeRef __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Rank )( 
            CodeTypeRef __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AsString )( 
            CodeTypeRef __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateArrayType )( 
            CodeTypeRef __RPC_FAR * This,
            /* [in] */ long Rank,
            /* [retval][out] */ CodeTypeRef __RPC_FAR *__RPC_FAR *ppTypeRef);
        
        END_INTERFACE
    } CodeTypeRefVtbl;

    interface CodeTypeRef
    {
        CONST_VTBL struct CodeTypeRefVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define CodeTypeRef_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define CodeTypeRef_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define CodeTypeRef_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define CodeTypeRef_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define CodeTypeRef_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define CodeTypeRef_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define CodeTypeRef_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define CodeTypeRef_get_TypeKind(This,pVal)	\
    (This)->lpVtbl -> get_TypeKind(This,pVal)

#define CodeTypeRef_get_CodeType(This,pVal)	\
    (This)->lpVtbl -> get_CodeType(This,pVal)

#define CodeTypeRef_put_CodeType(This,newVal)	\
    (This)->lpVtbl -> put_CodeType(This,newVal)

#define CodeTypeRef_get_ElementType(This,pVal)	\
    (This)->lpVtbl -> get_ElementType(This,pVal)

#define CodeTypeRef_put_ElementType(This,newVal)	\
    (This)->lpVtbl -> put_ElementType(This,newVal)

#define CodeTypeRef_get_Rank(This,pVal)	\
    (This)->lpVtbl -> get_Rank(This,pVal)

#define CodeTypeRef_put_Rank(This,newVal)	\
    (This)->lpVtbl -> put_Rank(This,newVal)

#define CodeTypeRef_get_AsString(This,pVal)	\
    (This)->lpVtbl -> get_AsString(This,pVal)

#define CodeTypeRef_CreateArrayType(This,Rank,ppTypeRef)	\
    (This)->lpVtbl -> CreateArrayType(This,Rank,ppTypeRef)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE CodeTypeRef_get_TypeKind_Proxy( 
    CodeTypeRef __RPC_FAR * This,
    /* [retval][out] */ enum vsCMTypeRef __RPC_FAR *pVal);


void __RPC_STUB CodeTypeRef_get_TypeKind_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE CodeTypeRef_get_CodeType_Proxy( 
    CodeTypeRef __RPC_FAR * This,
    /* [retval][out] */ CodeType __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB CodeTypeRef_get_CodeType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE CodeTypeRef_put_CodeType_Proxy( 
    CodeTypeRef __RPC_FAR * This,
    /* [in] */ CodeType __RPC_FAR *newVal);


void __RPC_STUB CodeTypeRef_put_CodeType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE CodeTypeRef_get_ElementType_Proxy( 
    CodeTypeRef __RPC_FAR * This,
    /* [retval][out] */ CodeTypeRef __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB CodeTypeRef_get_ElementType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE CodeTypeRef_put_ElementType_Proxy( 
    CodeTypeRef __RPC_FAR * This,
    /* [in] */ CodeTypeRef __RPC_FAR *newVal);


void __RPC_STUB CodeTypeRef_put_ElementType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE CodeTypeRef_get_Rank_Proxy( 
    CodeTypeRef __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB CodeTypeRef_get_Rank_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE CodeTypeRef_put_Rank_Proxy( 
    CodeTypeRef __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB CodeTypeRef_put_Rank_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE CodeTypeRef_get_AsString_Proxy( 
    CodeTypeRef __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB CodeTypeRef_get_AsString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CodeTypeRef_CreateArrayType_Proxy( 
    CodeTypeRef __RPC_FAR * This,
    /* [in] */ long Rank,
    /* [retval][out] */ CodeTypeRef __RPC_FAR *__RPC_FAR *ppTypeRef);


void __RPC_STUB CodeTypeRef_CreateArrayType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __CodeTypeRef_INTERFACE_DEFINED__ */


#ifndef __CodeType_INTERFACE_DEFINED__
#define __CodeType_INTERFACE_DEFINED__

/* interface CodeType */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_CodeType;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("29113FC9-37E7-4506-9DAF-1E2241D343CF")
    CodeType : public CodeElement
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Members( 
            /* [retval][out] */ CodeElements __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Namespace( 
            /* [retval][out] */ CodeNamespace __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Bases( 
            /* [retval][out] */ CodeElements __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddBase( 
            /* [in] */ VARIANT Base,
            /* [in] */ VARIANT Position,
            /* [retval][out] */ CodeElement __RPC_FAR *__RPC_FAR *ppOut) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveBase( 
            /* [in] */ VARIANT Element) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveMember( 
            /* [in] */ VARIANT Element) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsDerivedFrom( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct CodeTypeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            CodeType __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            CodeType __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            CodeType __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            CodeType __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            CodeType __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            CodeType __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            CodeType __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            CodeType __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Name )( 
            CodeType __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FullName )( 
            CodeType __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Kind )( 
            CodeType __RPC_FAR * This,
            /* [retval][out] */ enum vsCMElement __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsCodeType )( 
            CodeType __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InfoLocation )( 
            CodeType __RPC_FAR * This,
            /* [retval][out] */ enum vsCMInfoLocation __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Children )( 
            CodeType __RPC_FAR * This,
            /* [retval][out] */ CodeElements __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StartPoint )( 
            CodeType __RPC_FAR * This,
            /* [retval][out] */ TextPoint __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EndPoint )( 
            CodeType __RPC_FAR * This,
            /* [retval][out] */ TextPoint __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetStartPoint )( 
            CodeType __RPC_FAR * This,
            /* [in] */ enum vsCMPart Part,
            /* [retval][out] */ TextPoint __RPC_FAR *__RPC_FAR *ppTextPoint);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEndPoint )( 
            CodeType __RPC_FAR * This,
            /* [in] */ enum vsCMPart Part,
            /* [retval][out] */ TextPoint __RPC_FAR *__RPC_FAR *ppTextPoint);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Members )( 
            CodeType __RPC_FAR * This,
            /* [retval][out] */ CodeElements __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Namespace )( 
            CodeType __RPC_FAR * This,
            /* [retval][out] */ CodeNamespace __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Bases )( 
            CodeType __RPC_FAR * This,
            /* [retval][out] */ CodeElements __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddBase )( 
            CodeType __RPC_FAR * This,
            /* [in] */ VARIANT Base,
            /* [in] */ VARIANT Position,
            /* [retval][out] */ CodeElement __RPC_FAR *__RPC_FAR *ppOut);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveBase )( 
            CodeType __RPC_FAR * This,
            /* [in] */ VARIANT Element);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveMember )( 
            CodeType __RPC_FAR * This,
            /* [in] */ VARIANT Element);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsDerivedFrom )( 
            CodeType __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        END_INTERFACE
    } CodeTypeVtbl;

    interface CodeType
    {
        CONST_VTBL struct CodeTypeVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define CodeType_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define CodeType_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define CodeType_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define CodeType_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define CodeType_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define CodeType_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define CodeType_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define CodeType_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define CodeType_put_Name(This,newVal)	\
    (This)->lpVtbl -> put_Name(This,newVal)

#define CodeType_get_FullName(This,pVal)	\
    (This)->lpVtbl -> get_FullName(This,pVal)

#define CodeType_get_Kind(This,pVal)	\
    (This)->lpVtbl -> get_Kind(This,pVal)

#define CodeType_get_IsCodeType(This,pVal)	\
    (This)->lpVtbl -> get_IsCodeType(This,pVal)

#define CodeType_get_InfoLocation(This,pVal)	\
    (This)->lpVtbl -> get_InfoLocation(This,pVal)

#define CodeType_get_Children(This,pVal)	\
    (This)->lpVtbl -> get_Children(This,pVal)

#define CodeType_get_StartPoint(This,pVal)	\
    (This)->lpVtbl -> get_StartPoint(This,pVal)

#define CodeType_get_EndPoint(This,pVal)	\
    (This)->lpVtbl -> get_EndPoint(This,pVal)

#define CodeType_GetStartPoint(This,Part,ppTextPoint)	\
    (This)->lpVtbl -> GetStartPoint(This,Part,ppTextPoint)

#define CodeType_GetEndPoint(This,Part,ppTextPoint)	\
    (This)->lpVtbl -> GetEndPoint(This,Part,ppTextPoint)


#define CodeType_get_Members(This,pVal)	\
    (This)->lpVtbl -> get_Members(This,pVal)

#define CodeType_get_Namespace(This,pVal)	\
    (This)->lpVtbl -> get_Namespace(This,pVal)

#define CodeType_get_Bases(This,pVal)	\
    (This)->lpVtbl -> get_Bases(This,pVal)

#define CodeType_AddBase(This,Base,Position,ppOut)	\
    (This)->lpVtbl -> AddBase(This,Base,Position,ppOut)

#define CodeType_RemoveBase(This,Element)	\
    (This)->lpVtbl -> RemoveBase(This,Element)

#define CodeType_RemoveMember(This,Element)	\
    (This)->lpVtbl -> RemoveMember(This,Element)

#define CodeType_get_IsDerivedFrom(This,pVal)	\
    (This)->lpVtbl -> get_IsDerivedFrom(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE CodeType_get_Members_Proxy( 
    CodeType __RPC_FAR * This,
    /* [retval][out] */ CodeElements __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB CodeType_get_Members_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE CodeType_get_Namespace_Proxy( 
    CodeType __RPC_FAR * This,
    /* [retval][out] */ CodeNamespace __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB CodeType_get_Namespace_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE CodeType_get_Bases_Proxy( 
    CodeType __RPC_FAR * This,
    /* [retval][out] */ CodeElements __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB CodeType_get_Bases_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CodeType_AddBase_Proxy( 
    CodeType __RPC_FAR * This,
    /* [in] */ VARIANT Base,
    /* [in] */ VARIANT Position,
    /* [retval][out] */ CodeElement __RPC_FAR *__RPC_FAR *ppOut);


void __RPC_STUB CodeType_AddBase_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CodeType_RemoveBase_Proxy( 
    CodeType __RPC_FAR * This,
    /* [in] */ VARIANT Element);


void __RPC_STUB CodeType_RemoveBase_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CodeType_RemoveMember_Proxy( 
    CodeType __RPC_FAR * This,
    /* [in] */ VARIANT Element);


void __RPC_STUB CodeType_RemoveMember_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE CodeType_get_IsDerivedFrom_Proxy( 
    CodeType __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB CodeType_get_IsDerivedFrom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __CodeType_INTERFACE_DEFINED__ */


#ifndef __TextPoint_INTERFACE_DEFINED__
#define __TextPoint_INTERFACE_DEFINED__

/* interface TextPoint */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_TextPoint;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2518BB7D-580C-4D46-9BFE-6F224D2BEF99")
    TextPoint : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct TextPointVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            TextPoint __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            TextPoint __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            TextPoint __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            TextPoint __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            TextPoint __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            TextPoint __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            TextPoint __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } TextPointVtbl;

    interface TextPoint
    {
        CONST_VTBL struct TextPointVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define TextPoint_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define TextPoint_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define TextPoint_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define TextPoint_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define TextPoint_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define TextPoint_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define TextPoint_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __TextPoint_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_CCodeModel;

#ifdef __cplusplus

class DECLSPEC_UUID("EA93371C-5D30-449B-8087-77AE11AE6BBA")
CCodeModel;
#endif
#endif /* __CODEMODELLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
