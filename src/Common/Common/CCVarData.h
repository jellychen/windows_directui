#pragma once

#include "Include/Def/Require.h"
#include "Include/Util/UtilTpl.h"
#include "Include/Common/ICStruct.h"
#include "CCVarDataKey.h"
#include <hash_map>

[
	default(ICVarData) ,
	threading(free) ,
	uuid("6349F25A-ED1A-4bd1-BA96-ED56C879532E") ,
	coclass
]
class ATL_NO_VTABLE CCVarData : public IDispatchImpl<ICVarData>
{
public:
	DECLARE_PROTECT_FINAL_CONSTRUCT() ;
	CCVarData() ;
	virtual ~CCVarData() ;

public:
	HRESULT _call GetBool		(BSTR bsKey, BOOL*		pVal) ;
	HRESULT _call GetChar		(BSTR bsKey, CHAR*		pVal) ;
	HRESULT _call GetWChar		(BSTR bsKey, WCHAR*		pVal) ;
	HRESULT _call GetWord		(BSTR bsKey, WORD*		pVal) ;
	HRESULT _call GetDWord		(BSTR bsKey, DWORD*		pVal) ;
	HRESULT _call GetShort		(BSTR bsKey, SHORT*		pVal) ;
	HRESULT _call GetUInt		(BSTR bsKey, UINT*		pVal) ;
	HRESULT _call GetUInt32		(BSTR bsKey, UINT32*	pVal) ;
	HRESULT _call GetUInt64		(BSTR bsKey, UINT64*	pVal) ;
	HRESULT _call GetInt		(BSTR bsKey, INT*		pVal) ;
	HRESULT _call GetInt32		(BSTR bsKey, INT32*		pVal) ;
	HRESULT _call GetInt64		(BSTR bsKey, INT64*		pVal) ;
	HRESULT _call GetFloat		(BSTR bsKey, FLOAT*		pVal) ;
	HRESULT _call GetDouble		(BSTR bsKey, DOUBLE*	pVal) ;
	HRESULT _call GetString		(BSTR bsKey, BSTR*		pVal) ;
	HRESULT _call GetGuid		(BSTR bsKey, GUID*		pVal) ;
	HRESULT _call GetRect		(BSTR bsKey, RECT*		pVal) ;
	HRESULT _call GetPoint		(BSTR bsKey, POINT*		pVal) ;
	HRESULT _call GetSize		(BSTR bsKey, SIZE*		pVal) ;

	HRESULT _call GetInterface	(BSTR bsKey, REFIID iid, VOID** ppVal) ;
	HRESULT _call GetVarData	(BSTR bsKey, ICVarData** ppVal) ;
	HRESULT _call GetVarArray	(BSTR bskey, ICVarArray** ppVal) ;
	HRESULT _call GetVarBuffer(BSTR bskey, ICVarBuffer** ppVal) ;

	HRESULT _call Clear			()				;
	HRESULT _call EraseItem		(BSTR bsKey)	;

	HRESULT _call SetBool		(BSTR bsKey, BOOL		val) ;
	HRESULT _call SetByte		(BSTR bsKey, BYTE		val) ;
	HRESULT _call SetChar		(BSTR bsKey, CHAR		val) ;
	HRESULT _call SetWChar		(BSTR bsKey, WCHAR		val) ;
	HRESULT _call SetWord		(BSTR bsKey, WORD		val) ;
	HRESULT _call SetDWord		(BSTR bsKey, DWORD		val) ;
	HRESULT _call SetShort		(BSTR bsKey, SHORT		val) ;
	HRESULT _call SetUInt		(BSTR bsKey, UINT		val) ;
	HRESULT _call SetUInt32		(BSTR bsKey, UINT32		val) ;
	HRESULT _call SetUInt64		(BSTR bsKey, UINT64		val) ;
	HRESULT _call SetInt		(BSTR bsKey, INT		val) ;
	HRESULT _call SetInt32		(BSTR bsKey, INT32		val) ;
	HRESULT _call SetInt64		(BSTR bsKey, INT64		val) ;
	HRESULT _call SetFloat		(BSTR bsKey, FLOAT		val) ;
	HRESULT _call SetDouble		(BSTR bsKey, DOUBLE		val) ;
	HRESULT _call SetString		(BSTR bsKey, BSTR		val) ;
	HRESULT _call SetGuid		(BSTR bsKey, GUID		val) ;
	HRESULT _call SetRect		(BSTR bsKey, RECT		val) ;
	HRESULT _call SetPoint		(BSTR bsKey, POINT		val) ;
	HRESULT _call SetSize		(BSTR bsKey, SIZE		val) ;
	HRESULT _call SetInterface	(BSTR bsKey, IUnknown*	val) ;

	HRESULT _call SetVarData		(BSTR bskey, ICVarData* pVal) ;
	HRESULT _call SetVarArray		(BSTR bskey, ICVarArray* pVal) ;
	HRESULT _call SetVarBuffer		(BSTR bskey, ICVarBuffer* pVal) ;
	HRESULT _call SetNewVarData		(BSTR bskey, ICVarData** ppVal) ;
	HRESULT _call SetNewVarArray	(BSTR bskey, ICVarArray** ppVal) ;
	HRESULT _call SetNewVarBuffer	(BSTR bskey, ICVarBuffer** ppVal) ;

private:
	typedef stdext::hash_map<CCVarDataKeyString, 
		CComPtr<ICVariant>, CCVarDataKeyStringHash> HASH_POOL ;
	HASH_POOL					m_hashPool ;
} ;
