#pragma once

#include "Include/Def/Require.h"
#include "Include/Util/UtilTpl.h"
#include "Include/Common/ICStruct.h"
#include <vector>

[
	default(ICVarArray) ,
	threading(free) ,
	uuid("F9C9D572-9291-4cae-B99F-064CC3883270") ,
	coclass
]
class ATL_NO_VTABLE CCVarArray : public IDispatchImpl<ICVarArray>
{
public:
	DECLARE_PROTECT_FINAL_CONSTRUCT() ;
	CCVarArray() ;
	virtual ~CCVarArray() ;

public:
	HRESULT _call GetArrayCount		(LONG* plCount) ;
	HRESULT _call GetBool			(LONG lIndex, BOOL*		pVal) ;
	HRESULT _call GetChar			(LONG lIndex, CHAR*		pVal) ;
	HRESULT _call GetWChar			(LONG lIndex, WCHAR*	pVal) ;
	HRESULT _call GetWord			(LONG lIndex, WORD*		pVal) ;
	HRESULT _call GetDWord			(LONG lIndex, DWORD*	pVal) ;
	HRESULT _call GetShort			(LONG lIndex, SHORT*	pVal) ;
	HRESULT _call GetUInt			(LONG lIndex, UINT*		pVal) ;
	HRESULT _call GetUInt32			(LONG lIndex, UINT32*	pVal) ;
	HRESULT _call GetUInt64			(LONG lIndex, UINT64*	pVal) ;
	HRESULT _call GetInt			(LONG lIndex, INT*		pVal) ;
	HRESULT _call GetInt32			(LONG lIndex, INT32*	pVal) ;
	HRESULT _call GetInt64			(LONG lIndex, INT64*	pVal) ;
	HRESULT _call GetFloat			(LONG lIndex, FLOAT*	pVal) ;
	HRESULT _call GetDouble			(LONG lIndex, DOUBLE*	pVal) ;
	HRESULT _call GetString			(LONG lIndex, BSTR*		pVal) ;
	HRESULT _call GetGuid			(LONG lIndex, GUID*		pVal) ;
	HRESULT _call GetRect			(LONG lIndex, RECT*		pVal) ;
	HRESULT _call GetPoint			(LONG lIndex, POINT*	pVal) ;
	HRESULT _call GetSize			(LONG lIndex, SIZE*		pVal) ;

	HRESULT _call GetInterface		(LONG lIndex, REFIID iid, VOID** ppVal) ;
	HRESULT _call GetVarData		(LONG lIndex, ICVarData** ppVal)		;
	HRESULT _call GetVarArray		(LONG lIndex, ICVarArray** ppVal)		;
	HRESULT _call GetVarBuffer		(LONG lIndex, ICVarBuffer** ppVal)		;

	HRESULT _call EraseAll			() ;
	HRESULT _call EraseOne			(LONG lIndex) ;

	HRESULT _call AddBool			(BOOL val) ;
	HRESULT _call InsertBool		(LONG lIndex, BOOL val) ;
	HRESULT _call SetBool			(LONG lIndex, BOOL val) ;
	HRESULT _call AddChar			(CHAR val) ;
	HRESULT _call InsertChar		(LONG lIndex, CHAR val) ;
	HRESULT _call SetChar			(LONG lIndex, CHAR val) ;
	HRESULT _call AddWChar			(WCHAR val) ;
	HRESULT _call InsertWChar		(LONG lIndex, WCHAR val) ;
	HRESULT _call SetWChar			(LONG lIndex, WCHAR val) ;
	HRESULT _call AddWord			(WORD val) ;
	HRESULT _call InsertWord		(LONG lIndex, WORD val) ;
	HRESULT _call SetWord			(LONG lIndex, WORD val) ;
	HRESULT _call AddDWord			(DWORD val) ;
	HRESULT _call InsertDWord		(LONG lIndex, DWORD val) ;
	HRESULT _call SetDWord			(LONG lIndex, DWORD val) ;
	HRESULT _call AddShort			(SHORT val) ;
	HRESULT _call InsertShort		(LONG lIndex, SHORT val) ;
	HRESULT _call SetShort			(LONG lIndex, SHORT val) ;
	HRESULT _call AddUInt			(UINT val) ;
	HRESULT _call InsertUInt		(LONG lIndex, UINT val) ;
	HRESULT _call SetUInt			(LONG lIndex, UINT val) ;
	HRESULT _call AddUInt32			(UINT32 val) ;
	HRESULT _call InsertUInt32		(LONG lIndex, UINT32 val) ;
	HRESULT _call SetUInt32			(LONG lIndex, UINT32 val) ;
	HRESULT _call AddUInt64			(UINT64 val) ;
	HRESULT _call InsertUInt64		(LONG lIndex, UINT64 val) ;
	HRESULT _call SetUInt64			(LONG lIndex, UINT64 val) ;
	HRESULT _call AddInt			(INT val) ;
	HRESULT _call InsertInt			(LONG lIndex, INT val) ;
	HRESULT _call SetInt			(LONG lIndex, INT val) ;
	HRESULT _call AddInt32			(INT32 val) ;
	HRESULT _call InsertInt32		(LONG lIndex, INT32 val) ;
	HRESULT _call SetInt32			(LONG lIndex, INT32 val) ;
	HRESULT _call AddInt64			(INT64 val) ;
	HRESULT _call InsertInt64		(LONG lIndex, INT64 val) ;
	HRESULT _call SetInt64			(LONG lIndex, INT64 val) ;
	HRESULT _call AddFloat			(FLOAT val) ;
	HRESULT _call InsertFloat		(LONG lIndex, FLOAT val) ;
	HRESULT _call SetFloat			(LONG lIndex, FLOAT val) ;
	HRESULT _call AddDouble			(DOUBLE val) ;
	HRESULT _call InsertDouble		(LONG lIndex, DOUBLE val) ;
	HRESULT _call SetDouble			(LONG lIndex, DOUBLE val) ;
	HRESULT _call AddString			(BSTR val) ;
	HRESULT _call InsertString		(LONG lIndex, BSTR val) ;
	HRESULT _call SetString			(LONG lIndex, BSTR val) ;
	HRESULT _call AddGuid			(GUID val) ;
	HRESULT _call InsertGuid		(LONG lIndex, GUID val) ;
	HRESULT _call SetGuid			(LONG lIndex, GUID val) ;
	HRESULT _call AddRect			(RECT val) ;
	HRESULT _call InsertRect		(LONG lIndex, RECT val) ;
	HRESULT _call SetRect			(LONG lIndex, RECT val) ;
	HRESULT _call AddPoint			(POINT val) ;
	HRESULT _call InsertPoint		(LONG lIndex, POINT val) ;
	HRESULT _call SetPoint			(LONG lIndex, POINT val) ;
	HRESULT _call AddSize			(SIZE val) ;
	HRESULT _call InsertSize		(LONG lIndex, SIZE val) ;
	HRESULT _call SetSize			(LONG lIndex, SIZE val) ;
	HRESULT _call AddInterface		(IUnknown* pVal) ;
	HRESULT _call InsertInterface	(LONG lIndex, IUnknown* pVal) ;
	HRESULT _call SetInterface		(LONG lIndex, IUnknown* pVal) ;

	HRESULT _call AddVarData		(ICVarData* pVal) ;
	HRESULT _call AddNewVarData		(ICVarData** ppVal) ;
	HRESULT _call InsertVarData		(LONG lIndex, ICVarData* pVal) ;
	HRESULT _call InsertNewVarData	(LONG lIndex, ICVarData** pVal) ;
	HRESULT _call SetVarData		(LONG lIndex, ICVarData* pVal) ;
	HRESULT _call SetNewVarData		(LONG lIndex, ICVarData** ppVal) ;

	HRESULT _call AddVarArray		(ICVarArray* pVal) ;
	HRESULT _call AddNewVarArray	(ICVarArray** ppVal) ;
	HRESULT _call InsertVarArray	(LONG lIndex, ICVarArray* pVal) ;
	HRESULT _call InsertNewVarArray	(LONG lIndex, ICVarArray** ppVal) ;
	HRESULT _call SetVarArray		(LONG lIndex, ICVarArray* pVal) ;
	HRESULT _call SetNewVarArray	(LONG lIndex, ICVarArray** ppVal) ;

	HRESULT _call AddVarBuffer		(ICVarBuffer* pVal) ;
	HRESULT _call AddNewVarBuffer	(ICVarBuffer** ppVal) ;
	HRESULT _call InsertVarBuffer	(LONG lIndex, ICVarBuffer* pVal) ;
	HRESULT _call InsertNewVarBuffer(LONG lIndex, ICVarBuffer** ppVal) ;
	HRESULT _call SetVarBuffer		(LONG lIndex, ICVarBuffer* pVal) ;
	HRESULT _call SetNewVarBuffer	(LONG lIndex, ICVarBuffer** ppVal) ;
private:
	typedef std::vector<CComPtr<ICVariant>>	VEC_ARRAY ;
	VEC_ARRAY						m_vecArray ;
} ;