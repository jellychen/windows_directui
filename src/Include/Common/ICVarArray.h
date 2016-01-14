#pragma once

[
	object ,
	uuid("3DE31929-A92D-4e4b-9CB5-BA4FC5CD9DD8") ,
	pointer_default(unique)
]
__interface ICVarArrayReader : IDispatch
{
	HRESULT GetArrayCount	(LONG* plCount) ;
	HRESULT GetBool			(LONG lIndex, BOOL*		pVal) ;
	HRESULT GetChar			(LONG lIndex, CHAR*		pVal) ;
	HRESULT GetWChar		(LONG lIndex, WCHAR*	pVal) ;
	HRESULT GetWord			(LONG lIndex, WORD*		pVal) ;
	HRESULT GetDWord		(LONG lIndex, DWORD*	pVal) ;
	HRESULT GetShort		(LONG lIndex, SHORT*	pVal) ;
	HRESULT GetUInt			(LONG lIndex, UINT*		pVal) ;
	HRESULT GetUInt32		(LONG lIndex, UINT32*	pVal) ;
	HRESULT GetUInt64		(LONG lIndex, UINT64*	pVal) ;
	HRESULT GetInt			(LONG lIndex, INT*		pVal) ;
	HRESULT GetInt32		(LONG lIndex, INT32*	pVal) ;
	HRESULT GetInt64		(LONG lIndex, INT64*	pVal) ;
	HRESULT GetFloat		(LONG lIndex, FLOAT*	pVal) ;
	HRESULT GetDouble		(LONG lIndex, DOUBLE*	pVal) ;
	HRESULT GetString		(LONG lIndex, BSTR*		pVal) ;
	HRESULT GetGuid			(LONG lIndex, GUID*		pVal) ;
	HRESULT GetRect			(LONG lIndex, RECT*		pVal) ;
	HRESULT GetPoint		(LONG lIndex, POINT*	pVal) ;
	HRESULT GetSize			(LONG lIndex, SIZE*		pVal) ;

	HRESULT GetInterface	(LONG lIndex, REFIID iid, VOID** ppVal) ;
	HRESULT GetVarData		(LONG lIndex, ICVarData** ppVal)		;
	HRESULT GetVarArray		(LONG lIndex, ICVarArray** ppVal)		;
	HRESULT GetVarBuffer	(LONG lIndex, ICVarBuffer** ppVal)		;
} ;

[
	object ,
	uuid("247F6AAA-D0DB-4218-8CE5-422D29220D13") ,
	pointer_default(unique)
]
__interface ICVarArray : ICVarArrayReader
{
	HRESULT EraseAll		() ;
	HRESULT EraseOne		(LONG lIndex) ;
	HRESULT AddBool			(BOOL val) ;
	HRESULT InsertBool		(LONG lIndex, BOOL val) ;
	HRESULT SetBool			(LONG lIndex, BOOL val) ;
	HRESULT AddChar			(CHAR val) ;
	HRESULT InsertChar		(LONG lIndex, CHAR val) ;
	HRESULT SetChar			(LONG lIndex, CHAR val) ;
	HRESULT AddWChar		(WCHAR val) ;
	HRESULT InsertWChar		(LONG lIndex, WCHAR val) ;
	HRESULT SetWChar		(LONG lIndex, WCHAR val) ;
	HRESULT AddWord			(WORD val) ;
	HRESULT InsertWord		(LONG lIndex, WORD val) ;
	HRESULT SetWord			(LONG lIndex, WORD val) ;
	HRESULT AddDWord		(DWORD val) ;
	HRESULT InsertDWord		(LONG lIndex, DWORD val) ;
	HRESULT SetDWord		(LONG lIndex, DWORD val) ;
	HRESULT AddShort		(SHORT val) ;
	HRESULT InsertShort		(LONG lIndex, SHORT val) ;
	HRESULT SetShort		(LONG lIndex, SHORT val) ;
	HRESULT AddUInt			(UINT val) ;
	HRESULT InsertUInt		(LONG lIndex, UINT val) ;
	HRESULT SetUInt			(LONG lIndex, UINT val) ;
	HRESULT AddUInt32		(UINT32 val) ;
	HRESULT InsertUInt32	(LONG lIndex, UINT32 val) ;
	HRESULT SetUInt32		(LONG lIndex, UINT32 val) ;
	HRESULT AddUInt64		(UINT64 val) ;
	HRESULT InsertUInt64	(LONG lIndex, UINT64 val) ;
	HRESULT SetUInt64		(LONG lIndex, UINT64 val) ;
	HRESULT AddInt			(INT val) ;
	HRESULT InsertInt		(LONG lIndex, INT val) ;
	HRESULT SetInt			(LONG lIndex, INT val) ;
	HRESULT AddInt32		(INT32 val) ;
	HRESULT InsertInt32		(LONG lIndex, INT32 val) ;
	HRESULT SetInt32		(LONG lIndex, INT32 val) ;
	HRESULT AddInt64		(INT64 val) ;
	HRESULT InsertInt64		(LONG lIndex, INT64 val) ;
	HRESULT SetInt64		(LONG lIndex, INT64 val) ;
	HRESULT AddFloat		(FLOAT val) ;
	HRESULT InsertFloat		(LONG lIndex, FLOAT val) ;
	HRESULT SetFloat		(LONG lIndex, FLOAT val) ;
	HRESULT AddDouble		(DOUBLE val) ;
	HRESULT InsertDouble	(LONG lIndex, DOUBLE val) ;
	HRESULT SetDouble		(LONG lIndex, DOUBLE val) ;
	HRESULT AddString		(BSTR val) ;
	HRESULT InsertString	(LONG lIndex, BSTR val) ;
	HRESULT SetString		(LONG lIndex, BSTR val) ;
	HRESULT AddGuid			(GUID val) ;
	HRESULT InsertGuid		(LONG lIndex, GUID val) ;
	HRESULT SetGuid			(LONG lIndex, GUID val) ;
	HRESULT AddRect			(RECT val) ;
	HRESULT InsertRect		(LONG lIndex, RECT val) ;
	HRESULT SetRect			(LONG lIndex, RECT val) ;
	HRESULT AddPoint		(POINT val) ;
	HRESULT InsertPoint		(LONG lIndex, POINT val) ;
	HRESULT SetPoint		(LONG lIndex, POINT val) ;
	HRESULT AddSize			(SIZE val) ;
	HRESULT InsertSize		(LONG lIndex, SIZE val) ;
	HRESULT SetSize			(LONG lIndex, SIZE val) ;
	HRESULT AddInterface	(IUnknown* pVal) ;
	HRESULT InsertInterface	(LONG lIndex, IUnknown* pVal) ;
	HRESULT SetInterface	(LONG lIndex, IUnknown* pVal) ;

	HRESULT AddVarData			(ICVarData* pVal) ;
	HRESULT AddNewVarData		(ICVarData** ppVal) ;
	HRESULT InsertVarData		(LONG lIndex, ICVarData* pVal) ;
	HRESULT InsertNewVarData	(LONG lIndex, ICVarData** pVal) ;
	HRESULT SetVarData			(LONG lIndex, ICVarData* pVal) ;
	HRESULT SetNewVarData		(LONG lIndex, ICVarData** ppVal) ;
	HRESULT AddVarArray			(ICVarArray* pVal) ;
	HRESULT AddNewVarArray		(ICVarArray** ppVal) ;
	HRESULT InsertVarArray		(LONG lIndex, ICVarArray* pVal) ;
	HRESULT InsertNewVarArray	(LONG lIndex, ICVarArray** pVal) ;
	HRESULT SetVarArray			(LONG lIndex, ICVarArray* pVal) ;
	HRESULT SetNewVarArray		(LONG lIndex, ICVarArray** ppVal) ;
	HRESULT AddVarBuffer		(ICVarBuffer* pVal) ;
	HRESULT AddNewVarBuffer		(ICVarBuffer** ppVal) ;
	HRESULT InsertVarBuffer		(LONG lIndex, ICVarBuffer* pVal) ;
	HRESULT InsertNewVarBuffer	(LONG lIndex, ICVarBuffer** pVal) ;
	HRESULT SetVarBuffer		(LONG lIndex, ICVarBuffer* pVal) ;
	HRESULT SetNewVarBuffer		(LONG lIndex, ICVarBuffer** ppVal) ;
} ;
