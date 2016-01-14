#pragma once

#include "CCVariantType.h"
#include "CCVariantObject.h"
#include "Include/Def/Require.h"
#include "Include/Common/ICVariant.h"

[
	default(ICVariant) ,
	threading(free) ,
	uuid("3FC74D6B-FF79-47f5-AC4D-7C90352AA4FF") ,
	coclass
]
class ATL_NO_VTABLE CCVariant : public IDispatchImpl<ICVariant>
{
public:
	DECLARE_PROTECT_FINAL_CONSTRUCT() ;
	CCVariant() ;
	virtual ~CCVariant() ;

public:
	HRESULT _call GetBool		(BOOL*		pVal)	;
	HRESULT _call GetChar		(CHAR*		pVal)	;
	HRESULT _call GetWChar		(WCHAR*		pVal)	;
	HRESULT _call GetWord		(WORD*		pVal)	;
	HRESULT _call GetDWord		(DWORD*		pVal)	;
	HRESULT _call GetShort		(SHORT*		pVal)	;
	HRESULT _call GetUInt		(UINT*		pVal)	;
	HRESULT _call GetUInt32		(UINT32*	pVal)	;
	HRESULT _call GetUInt64		(UINT64*	pVal)	;
	HRESULT _call GetInt		(INT*		pVal)	;
	HRESULT _call GetInt32		(INT32*		pVal)	;
	HRESULT _call GetInt64		(INT64*		pVal)	;
	HRESULT _call GetFloat		(FLOAT*		pVal)	;
	HRESULT _call GetDouble		(DOUBLE*	pVal)	;
	HRESULT _call GetString		(BSTR*		pVal)	;
	HRESULT _call GetGuid		(GUID*		pVal)	;
	HRESULT _call GetRect		(RECT*		pVal)	;
	HRESULT _call GetPoint		(POINT*		pVal)	;
	HRESULT _call GetSize		(SIZE*		pVal)	;
	HRESULT _call SetBool		(BOOL		val)	;
	HRESULT _call SetChar		(CHAR		val)	;
	HRESULT _call SetWChar		(WCHAR		val)	;
	HRESULT _call SetWord		(WORD		val)	;
	HRESULT _call SetDWord		(DWORD		val)	;
	HRESULT _call SetShort		(SHORT		val)	;
	HRESULT _call SetUInt		(UINT		val)	;
	HRESULT _call SetUInt32		(UINT32		val)	;
	HRESULT _call SetUInt64		(UINT64		val)	;
	HRESULT _call SetInt		(INT		val)	;
	HRESULT _call SetInt32		(INT32		val)	;
	HRESULT _call SetInt64		(INT64		val)	;
	HRESULT _call SetFloat		(FLOAT		val)	;
	HRESULT _call SetDouble		(DOUBLE		val)	;
	HRESULT _call SetString		(BSTR		val)	;
	HRESULT _call SetGuid		(GUID		val)	;
	HRESULT _call SetRect		(RECT		val)	;
	HRESULT _call SetPoint		(POINT		val)	;
	HRESULT _call SetSize		(SIZE		val)	;

	HRESULT _call GetInterface	(REFIID iid, VOID** ppVal)	;
	HRESULT _call SetInterface	(IUnknown*	val)			;

private:
	VOID	ReleseVariant		()				;

private:
	VARIANT_TYPE				m_eValueType	;
	VOID*						m_pValueData	;
} ;