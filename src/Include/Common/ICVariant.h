#pragma once

[
	object ,
	uuid("8419047E-547C-4bbb-84C3-4C3F5EEEB6C2") ,
	pointer_default(unique)
]
__interface ICVariant : IDispatch
{
	HRESULT GetBool		(BOOL*			pVal)	;
	HRESULT GetChar		(CHAR*			pVal)	;
	HRESULT GetWChar	(WCHAR*			pVal)	;
	HRESULT GetWord		(WORD*			pVal)	;
	HRESULT GetDWord	(DWORD*			pVal)	;
	HRESULT GetShort	(SHORT*			pVal)	;
	HRESULT GetUInt		(UINT*			pVal)	;
	HRESULT GetUInt32	(UINT32*		pVal)	;
	HRESULT GetUInt64	(UINT64*		pVal)	;
	HRESULT GetInt		(INT*			pVal)	;
	HRESULT GetInt32	(INT32*			pVal)	;
	HRESULT GetInt64	(INT64*			pVal)	;
	HRESULT GetFloat	(FLOAT*			pVal)	;
	HRESULT GetDouble	(DOUBLE*		pVal)	;
	HRESULT GetString	(BSTR*			pVal)	;
	HRESULT GetGuid		(GUID*			pVal)	;
	HRESULT GetRect		(RECT*			pVal)	;
	HRESULT GetPoint	(POINT*			pVal)	;
	HRESULT GetSize		(SIZE*			pVal)	;

	HRESULT SetBool		(BOOL			val)	;
	HRESULT SetChar		(CHAR			val)	;
	HRESULT SetWChar	(WCHAR			val)	;
	HRESULT SetWord		(WORD			val)	;
	HRESULT SetDWord	(DWORD			val)	;
	HRESULT SetShort	(SHORT			val)	;
	HRESULT SetUInt		(UINT			val)	;
	HRESULT SetUInt32	(UINT32			val)	;
	HRESULT SetUInt64	(UINT64			val)	;
	HRESULT SetInt		(INT			val)	;
	HRESULT SetInt32	(INT32			val)	;
	HRESULT SetInt64	(INT64			val)	;
	HRESULT SetFloat	(FLOAT			val)	;
	HRESULT SetDouble	(DOUBLE			val)	;
	HRESULT SetString	(BSTR			val)	;
	HRESULT SetGuid		(GUID			val)	;
	HRESULT SetRect		(RECT			val)	;
	HRESULT SetPoint	(POINT			val)	;
	HRESULT SetSize		(SIZE			val)	;

	HRESULT GetInterface(REFIID iid, VOID** ppVal)	;
	HRESULT SetInterface(IUnknown*	val)			;
} ;
