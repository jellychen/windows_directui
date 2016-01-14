#pragma once
#include "Include/Common/ICStruct.h"

[
	object ,
	uuid("C1E41389-958D-4853-84A3-2859616ADBB8") ,
	pointer_default(unique)
]
__interface ICVarDataReader : IDispatch
{
	HRESULT GetBool		(BSTR bsKey, BOOL*		pVal) ;
	HRESULT GetChar		(BSTR bsKey, CHAR*		pVal) ;
	HRESULT GetWChar	(BSTR bsKey, WCHAR*		pVal) ;
	HRESULT GetWord		(BSTR bsKey, WORD*		pVal) ;
	HRESULT GetDWord	(BSTR bsKey, DWORD*		pVal) ;
	HRESULT GetShort	(BSTR bsKey, SHORT*		pVal) ;
	HRESULT GetUInt		(BSTR bsKey, UINT*		pVal) ;
	HRESULT GetUInt32	(BSTR bsKey, UINT32*	pVal) ;
	HRESULT GetUInt64	(BSTR bsKey, UINT64*	pVal) ;
	HRESULT GetInt		(BSTR bsKey, INT*		pVal) ;
	HRESULT GetInt32	(BSTR bsKey, INT32*		pVal) ;
	HRESULT GetInt64	(BSTR bsKey, INT64*		pVal) ;
	HRESULT GetFloat	(BSTR bsKey, FLOAT*		pVal) ;
	HRESULT GetDouble	(BSTR bsKey, DOUBLE*	pVal) ;
	HRESULT GetString	(BSTR bsKey, BSTR*		pVal) ;
	HRESULT GetGuid		(BSTR bsKey, GUID*		pVal) ;
	HRESULT GetRect		(BSTR bsKey, RECT*		pVal) ;
	HRESULT GetPoint	(BSTR bsKey, POINT*		pVal) ;
	HRESULT GetSize		(BSTR bsKey, SIZE*		pVal) ;

	HRESULT GetInterface(BSTR bsKey, REFIID iid, VOID** ppVal)	;
	HRESULT GetVarData	(BSTR bsKey, ICVarData** ppVal)			;
	HRESULT GetVarArray	(BSTR bskey, ICVarArray** ppVal)		;
	HRESULT GetVarBuffer(BSTR bskey, ICVarBuffer** ppVal)		;
} ;

[
	object ,
	uuid("606F5434-9A03-4243-952A-8960D7005E04") ,
	pointer_default(unique)
]
__interface ICVarData : ICVarDataReader
{
	HRESULT Clear		()				;
	HRESULT EraseItem	(BSTR bsKey)	;

	HRESULT SetBool		(BSTR bsKey, BOOL		val) ;
	HRESULT SetChar		(BSTR bsKey, CHAR		val) ;
	HRESULT SetWChar	(BSTR bsKey, WCHAR		val) ;
	HRESULT SetWord		(BSTR bsKey, WORD		val) ;
	HRESULT SetDWord	(BSTR bsKey, DWORD		val) ;
	HRESULT SetShort	(BSTR bsKey, SHORT		val) ;
	HRESULT SetUInt		(BSTR bsKey, UINT		val) ;
	HRESULT SetUInt32	(BSTR bsKey, UINT32		val) ;
	HRESULT SetUInt64	(BSTR bsKey, UINT64		val) ;
	HRESULT SetInt		(BSTR bsKey, INT		val) ;
	HRESULT SetInt32	(BSTR bsKey, INT32		val) ;
	HRESULT SetInt64	(BSTR bsKey, INT64		val) ;
	HRESULT SetFloat	(BSTR bsKey, FLOAT		val) ;
	HRESULT SetDouble	(BSTR bsKey, DOUBLE		val) ;
	HRESULT SetString	(BSTR bsKey, BSTR		val) ;
	HRESULT SetGuid		(BSTR bsKey, GUID		val) ;
	HRESULT SetRect		(BSTR bsKey, RECT		val) ;
	HRESULT SetPoint	(BSTR bsKey, POINT		val) ;
	HRESULT SetSize		(BSTR bsKey, SIZE		val) ;

	HRESULT SetInterface	(BSTR bsKey, IUnknown*	pVal)		;
	HRESULT SetVarData		(BSTR bskey, ICVarData* pVal)		;
	HRESULT SetVarArray		(BSTR bskey, ICVarArray* pVal)		;
	HRESULT SetVarBuffer	(BSTR bskey, ICVarBuffer* pVal)		;
	HRESULT SetNewVarData	(BSTR bskey, ICVarData** ppVal)		;
	HRESULT SetNewVarArray	(BSTR bskey, ICVarArray** ppVal)	;
	HRESULT SetNewVarBuffer	(BSTR bskey, ICVarBuffer** ppVal)	;
} ;
