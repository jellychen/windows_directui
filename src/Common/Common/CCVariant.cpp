
#include "stdafx.h"
#include "CCVariant.h"

CCVariant::CCVariant()
{
	this->m_pValueData = NULL ;
	this->m_eValueType = VARIANT_TYPE_NONE ;
}

CCVariant::~CCVariant()
{
	this->ReleseVariant() ;
}

HRESULT CCVariant::GetBool(BOOL* pVal)
{
	IF_RETURN(NULL == pVal, E_INVALIDARG) ;
	IF_RETURN(NULL == this->m_pValueData, E_FAIL) ;
	IF_RETURN(VARIANT_TYPE_BOOL != this->m_eValueType, E_FAIL) ;

	*pVal = *((BOOL*)this->m_pValueData) ;
	return S_OK ;
}

HRESULT CCVariant::GetChar(CHAR* pVal)
{
	IF_RETURN(NULL == pVal, E_INVALIDARG) ;
	IF_RETURN(NULL == this->m_pValueData, E_FAIL) ;
	IF_RETURN(VARIANT_TYPE_CHAR != this->m_eValueType, E_FAIL) ;

	*pVal = *((CHAR*)this->m_pValueData) ;
	return S_OK ;
}

HRESULT CCVariant::GetWChar(WCHAR* pVal)
{	
	IF_RETURN(NULL == pVal, E_INVALIDARG) ;
	IF_RETURN(NULL == this->m_pValueData, E_FAIL) ;
	IF_RETURN(VARIANT_TYPE_WCHAR != this->m_eValueType, E_FAIL) ;

	*pVal = *((WCHAR*)this->m_pValueData) ;
	return S_OK ;
}

HRESULT CCVariant::GetWord(WORD* pVal)
{
	IF_RETURN(NULL == pVal, E_INVALIDARG) ;
	IF_RETURN(NULL == this->m_pValueData, E_FAIL) ;
	IF_RETURN(VARIANT_TYPE_WORD != this->m_eValueType, E_FAIL) ;

	*pVal = *((WORD*)this->m_pValueData) ;
	return S_OK ;
}

HRESULT CCVariant::GetDWord(DWORD* pVal)
{
	IF_RETURN(NULL == pVal, E_INVALIDARG) ;
	IF_RETURN(NULL == this->m_pValueData, E_FAIL) ;
	IF_RETURN(VARIANT_TYPE_DWORD != this->m_eValueType, E_FAIL) ;

	*pVal = *((DWORD*)this->m_pValueData) ;
	return S_OK ;
}

HRESULT CCVariant::GetShort(SHORT* pVal)
{
	IF_RETURN(NULL == pVal, E_INVALIDARG) ;
	IF_RETURN(NULL == this->m_pValueData, E_FAIL) ;
	IF_RETURN(VARIANT_TYPE_SHORT != this->m_eValueType, E_FAIL) ;

	*pVal = *((SHORT*)this->m_pValueData) ;
	return S_OK ;
}

HRESULT CCVariant::GetUInt(UINT* pVal)
{
	IF_RETURN(NULL == pVal, E_INVALIDARG) ;
	IF_RETURN(NULL == this->m_pValueData, E_FAIL) ;
	IF_RETURN(VARIANT_TYPE_UINT != this->m_eValueType, E_FAIL) ;

	*pVal = *((UINT*)this->m_pValueData) ;
	return S_OK ;
}

HRESULT CCVariant::GetUInt32(UINT32* pVal)
{
	IF_RETURN(NULL == pVal, E_INVALIDARG) ;
	IF_RETURN(NULL == this->m_pValueData, E_FAIL) ;
	IF_RETURN(VARIANT_TYPE_UINT32 != this->m_eValueType, E_FAIL) ;

	*pVal = *((UINT32*)this->m_pValueData) ;
	return S_OK ;
}

HRESULT CCVariant::GetUInt64(UINT64* pVal)
{
	IF_RETURN(NULL == pVal, E_INVALIDARG) ;
	IF_RETURN(NULL == this->m_pValueData, E_FAIL) ;
	IF_RETURN(VARIANT_TYPE_UINT64 != this->m_eValueType, E_FAIL) ;

	*pVal = *((UINT64*)this->m_pValueData) ;
	return S_OK ;
}

HRESULT CCVariant::GetInt(INT* pVal)
{
	IF_RETURN(NULL == pVal, E_INVALIDARG) ;
	IF_RETURN(NULL == this->m_pValueData, E_FAIL) ;
	IF_RETURN(VARIANT_TYPE_INT != this->m_eValueType, E_FAIL) ;

	*pVal = *((INT*)this->m_pValueData) ;
	return S_OK ;
}

HRESULT CCVariant::GetInt32(INT32* pVal)
{
	IF_RETURN(NULL == pVal, E_INVALIDARG) ;
	IF_RETURN(NULL == this->m_pValueData, E_FAIL) ;
	IF_RETURN(VARIANT_TYPE_INT32 != this->m_eValueType, E_FAIL) ;

	*pVal = *((INT32*)this->m_pValueData) ;
	return S_OK ;
}

HRESULT CCVariant::GetInt64(INT64* pVal)
{
	IF_RETURN(NULL == pVal, E_INVALIDARG) ;
	IF_RETURN(NULL == this->m_pValueData, E_FAIL) ;
	IF_RETURN(VARIANT_TYPE_INT64 != this->m_eValueType, E_FAIL) ;

	*pVal = *((INT64*)this->m_pValueData) ;
	return S_OK ;
}

HRESULT CCVariant::GetFloat(FLOAT* pVal)
{
	IF_RETURN(NULL == pVal, E_INVALIDARG) ;
	IF_RETURN(NULL == this->m_pValueData, E_FAIL) ;
	IF_RETURN(VARIANT_TYPE_FLOAT != this->m_eValueType, E_FAIL) ;

	*pVal = *((FLOAT*)this->m_pValueData) ;
	return S_OK ;
}

HRESULT CCVariant::GetDouble(DOUBLE* pVal)
{
	IF_RETURN(NULL == pVal, E_INVALIDARG) ;
	IF_RETURN(NULL == this->m_pValueData, E_FAIL) ;
	IF_RETURN(VARIANT_TYPE_DOUBLE != this->m_eValueType, E_FAIL) ;

	*pVal = *((DOUBLE*)this->m_pValueData) ;
	return S_OK ;
}

HRESULT CCVariant::GetString(BSTR* pVal)
{
	IF_RETURN(NULL == pVal, E_INVALIDARG) ;
	IF_RETURN(NULL == this->m_pValueData, E_FAIL) ;
	IF_RETURN(VARIANT_TYPE_STRING != this->m_eValueType, E_FAIL) ;
	
	CComBSTR _bstr(((CCVariantString*)this->m_pValueData)->_str) ;
	return _bstr.CopyTo(pVal);
}

HRESULT CCVariant::GetGuid(GUID* pVal)
{
	IF_RETURN(NULL == pVal, E_INVALIDARG) ;
	IF_RETURN(NULL == this->m_pValueData, E_FAIL) ;
	IF_RETURN(VARIANT_TYPE_GUID != this->m_eValueType, E_FAIL) ;

	*pVal = *((GUID*)this->m_pValueData) ;
	return S_OK ;
}

HRESULT CCVariant::GetRect(RECT* pVal)
{
	IF_RETURN(NULL == pVal, E_INVALIDARG) ;
	IF_RETURN(NULL == this->m_pValueData, E_FAIL) ;
	IF_RETURN(VARIANT_TYPE_RECT != this->m_eValueType, E_FAIL) ;

	*pVal = *((RECT*)this->m_pValueData) ;
	return S_OK ;
}

HRESULT CCVariant::GetPoint(POINT* pVal)
{
	IF_RETURN(NULL == pVal, E_INVALIDARG) ;
	IF_RETURN(NULL == this->m_pValueData, E_FAIL) ;
	IF_RETURN(VARIANT_TYPE_POINT != this->m_eValueType, E_FAIL) ;

	*pVal = *((POINT*)this->m_pValueData) ;
	return S_OK ;
}

HRESULT CCVariant::GetSize(SIZE* pVal)
{
	IF_RETURN(NULL == pVal, E_INVALIDARG) ;
	IF_RETURN(NULL == this->m_pValueData, E_FAIL) ;
	IF_RETURN(VARIANT_TYPE_SIZE != this->m_eValueType, E_FAIL) ;

	*pVal = *((SIZE*)this->m_pValueData) ;
	return S_OK ;
}

HRESULT CCVariant::SetBool(BOOL val)
{
	this->ReleseVariant() ;
	this->m_eValueType = VARIANT_TYPE_BOOL ;
	this->m_pValueData = new BOOL(val) ;
	return S_OK ;
}

HRESULT CCVariant::SetChar(CHAR val)
{
	this->ReleseVariant() ;
	this->m_eValueType = VARIANT_TYPE_CHAR ;
	this->m_pValueData = new CHAR(val) ;
	return S_OK ;
}

HRESULT CCVariant::SetWChar(WCHAR val)
{
	this->ReleseVariant() ;
	this->m_eValueType = VARIANT_TYPE_WCHAR ;
	this->m_pValueData = new WCHAR(val) ;
	return S_OK ;
}

HRESULT CCVariant::SetWord(WORD val)
{
	this->ReleseVariant() ;
	this->m_eValueType = VARIANT_TYPE_WORD ;
	this->m_pValueData = new WORD(val) ;
	return S_OK ;
}

HRESULT CCVariant::SetDWord(DWORD val)
{
	this->ReleseVariant() ;
	this->m_eValueType = VARIANT_TYPE_DWORD ;
	this->m_pValueData = new DWORD(val) ;
	return S_OK ;
}

HRESULT CCVariant::SetShort(SHORT val)
{
	this->ReleseVariant() ;
	this->m_eValueType = VARIANT_TYPE_SHORT ;
	this->m_pValueData = new SHORT(val) ;
	return S_OK ;
}

HRESULT CCVariant::SetUInt(UINT val)
{
	this->ReleseVariant() ;
	this->m_eValueType = VARIANT_TYPE_UINT ;
	this->m_pValueData = new UINT(val) ;
	return S_OK ;
}

HRESULT CCVariant::SetUInt32(UINT32 val)
{
	this->ReleseVariant() ;
	this->m_eValueType = VARIANT_TYPE_UINT32 ;
	this->m_pValueData = new UINT32(val) ;
	return S_OK ;
}

HRESULT CCVariant::SetUInt64(UINT64 val)
{
	this->ReleseVariant() ;
	this->m_eValueType = VARIANT_TYPE_UINT64 ;
	this->m_pValueData = new UINT64(val) ;
	return S_OK ;
}

HRESULT CCVariant::SetInt(INT val)
{
	this->ReleseVariant() ;
	this->m_eValueType = VARIANT_TYPE_INT ;
	this->m_pValueData = new INT(val) ;
	return S_OK ;
}

HRESULT CCVariant::SetInt32(INT32 val)
{
	this->ReleseVariant() ;
	this->m_eValueType = VARIANT_TYPE_INT32 ;
	this->m_pValueData = new INT32(val) ;
	return S_OK ;
}

HRESULT CCVariant::SetInt64(INT64 val)
{
	this->ReleseVariant() ;
	this->m_eValueType = VARIANT_TYPE_INT64 ;
	this->m_pValueData = new INT64(val) ;
	return S_OK ;
}

HRESULT CCVariant::SetFloat(FLOAT val)
{
	this->ReleseVariant() ;
	this->m_eValueType = VARIANT_TYPE_FLOAT ;
	this->m_pValueData = new FLOAT(val) ;
	return S_OK ;
}

HRESULT CCVariant::SetDouble(DOUBLE val)
{
	this->ReleseVariant() ;
	this->m_eValueType = VARIANT_TYPE_DOUBLE ;
	this->m_pValueData = new DOUBLE(val) ;
	return S_OK ;
}

HRESULT CCVariant::SetString(BSTR val)
{
	this->ReleseVariant() ;
	this->m_eValueType = VARIANT_TYPE_STRING ;
	this->m_pValueData = new CCVariantString(val) ;
	return S_OK ;
}

HRESULT CCVariant::SetGuid(GUID val)
{
	this->ReleseVariant() ;
	this->m_eValueType = VARIANT_TYPE_GUID ;
	this->m_pValueData = new GUID(val) ;
	return S_OK ;
}

HRESULT CCVariant::SetRect(RECT val)
{
	this->ReleseVariant() ;
	this->m_eValueType = VARIANT_TYPE_RECT ;
	this->m_pValueData = new RECT(val) ;
	return S_OK ;
}

HRESULT CCVariant::SetPoint(POINT val)
{
	this->ReleseVariant() ;
	this->m_eValueType = VARIANT_TYPE_POINT ;
	this->m_pValueData = new POINT(val) ;
	return S_OK ;
}

HRESULT CCVariant::SetSize(SIZE	val)
{
	this->ReleseVariant() ;
	this->m_eValueType = VARIANT_TYPE_SIZE ;
	this->m_pValueData = new SIZE(val) ;
	return S_OK ;
}

HRESULT CCVariant::GetInterface(REFIID iid, VOID** ppVal)
{
	IF_RETURN(NULL == ppVal, E_INVALIDARG) ;
	IF_RETURN(NULL == this->m_pValueData, E_FAIL) ;
	IF_RETURN(VARIANT_TYPE_OBJECT != this->m_eValueType, E_FAIL) ;

	*ppVal = NULL ;
	CCVariantComObject* _object = ((CCVariantComObject*)this->m_pValueData) ;
	if (_object->_ptr)
	{
		return _object->_ptr->QueryInterface(iid, ppVal) ;
	}
	return E_FAIL ;
}

HRESULT CCVariant::SetInterface(IUnknown* val)
{
	this->ReleseVariant() ;
	this->m_eValueType = VARIANT_TYPE_OBJECT ;
	this->m_pValueData = new CCVariantComObject(val) ;
	return S_OK ;
}

VOID CCVariant::ReleseVariant()
{
	IF_RETURN_VOID(NULL == this->m_pValueData) ;
	IF_RETURN_VOID(VARIANT_TYPE_NONE == this->m_eValueType) ;

	switch(this->m_eValueType)
	{
	case VARIANT_TYPE_NONE:
		break ;
	case VARIANT_TYPE_BOOL:
		delete (BOOL*)this->m_pValueData ;
		break ;
	case VARIANT_TYPE_BYTE:
		delete (BYTE*)this->m_pValueData ;
		break ;
	case VARIANT_TYPE_CHAR:
		delete (CHAR*)this->m_pValueData ;
		break ;
	case VARIANT_TYPE_WCHAR:
		delete (WCHAR*)this->m_pValueData ;
		break ;
	case VARIANT_TYPE_WORD:
		delete (WORD*)this->m_pValueData ;
		break ;
	case VARIANT_TYPE_DWORD:
		delete (DWORD*)this->m_pValueData ;
		break ;
	case VARIANT_TYPE_SHORT:
		delete (SHORT*)this->m_pValueData ;
		break ;
	case VARIANT_TYPE_UINT:
		delete (UINT*)this->m_pValueData ;
		break ;
	case VARIANT_TYPE_UINT32:
		delete (UINT32*)this->m_pValueData ;
		break ;
	case VARIANT_TYPE_UINT64:
		delete (UINT64*)this->m_pValueData ;
		break ;
	case VARIANT_TYPE_INT:
		delete (INT*)this->m_pValueData ;
		break ;
	case VARIANT_TYPE_INT32:
		delete (INT32*)this->m_pValueData ;
		break ;
	case VARIANT_TYPE_INT64:
		delete (INT64*)this->m_pValueData ;
		break ;
	case VARIANT_TYPE_FLOAT:
		delete (FLOAT*)this->m_pValueData ;
		break ;
	case VARIANT_TYPE_DOUBLE:
		delete (DOUBLE*)this->m_pValueData ;
		break ;
	case VARIANT_TYPE_STRING:
		delete (CCVariantString*)this->m_pValueData ;
		break ;
	case VARIANT_TYPE_GUID:
		delete (GUID*)this->m_pValueData ;
		break ;
	case VARIANT_TYPE_RECT:
		delete (RECT*)this->m_pValueData ;
		break ;
	case VARIANT_TYPE_POINT:
		delete (POINT*)this->m_pValueData ;
		break ;
	case VARIANT_TYPE_SIZE:
		delete (BOOL*)this->m_pValueData ;
		break ;
	case VARIANT_TYPE_OBJECT:
		delete (CCVariantComObject*)this->m_pValueData ;
		break ;
	}
	this->m_eValueType = VARIANT_TYPE_NONE ;
	this->m_pValueData = NULL ;
}