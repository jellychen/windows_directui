
#include "stdafx.h"
#include "CCVarArray.h"

CCVarArray::CCVarArray()
{
}

CCVarArray::~CCVarArray()
{
}

HRESULT CCVarArray::GetArrayCount(LONG* plCount)
{
	IF_RETURN(NULL == plCount, E_INVALIDARG) ;
	*plCount = (LONG)this->m_vecArray.size() ;
	return S_OK ;
}

HRESULT CCVarArray::GetBool(LONG lIndex, BOOL* pVal)
{
	DEBUG_ASSERT_MSG(pVal, _T("args pVal == null")) ;
	IF_RETURN(NULL == pVal, E_INVALIDARG) ;
	DEBUG_ASSERT_MSG(lIndex < (LONG)m_vecArray.size(), _T("index > size")) ;
	IF_RETURN(lIndex >= (LONG)m_vecArray.size(), E_INVALIDARG) ;

	CComPtr<ICVariant> _ptr = this->m_vecArray[lIndex] ;
	DEBUG_ASSERT(_ptr) ;
	IF_RETURN(NULL == _ptr, E_FAIL) ;

	return _ptr->GetBool(pVal) ;
}

HRESULT CCVarArray::GetChar(LONG lIndex, CHAR* pVal)
{
	DEBUG_ASSERT_MSG(pVal, _T("args pVal == null")) ;
	IF_RETURN(NULL == pVal, E_INVALIDARG) ;
	DEBUG_ASSERT_MSG(lIndex < (LONG)m_vecArray.size(), _T("index > size")) ;
	IF_RETURN(lIndex >= (LONG)m_vecArray.size(), E_INVALIDARG) ;

	CComPtr<ICVariant> _ptr = this->m_vecArray[lIndex] ;
	DEBUG_ASSERT(_ptr) ;
	IF_RETURN(NULL == _ptr, E_FAIL) ;

	return _ptr->GetChar(pVal) ;
}

HRESULT CCVarArray::GetWChar(LONG lIndex, WCHAR* pVal)
{
	DEBUG_ASSERT_MSG(pVal, _T("args pVal == null")) ;
	IF_RETURN(NULL == pVal, E_INVALIDARG) ;
	DEBUG_ASSERT_MSG(lIndex < (LONG)m_vecArray.size(), _T("index > size")) ;
	IF_RETURN(lIndex >= (LONG)m_vecArray.size(), E_INVALIDARG) ;

	CComPtr<ICVariant> _ptr = this->m_vecArray[lIndex] ;
	DEBUG_ASSERT(_ptr) ;
	IF_RETURN(NULL == _ptr, E_FAIL) ;

	return _ptr->GetWChar(pVal) ;
}

HRESULT CCVarArray::GetWord(LONG lIndex, WORD* pVal)
{
	DEBUG_ASSERT_MSG(pVal, _T("args pVal == null")) ;
	IF_RETURN(NULL == pVal, E_INVALIDARG) ;
	DEBUG_ASSERT_MSG(lIndex < (LONG)m_vecArray.size(), _T("index > size")) ;
	IF_RETURN(lIndex >= (LONG)m_vecArray.size(), E_INVALIDARG) ;

	CComPtr<ICVariant> _ptr = this->m_vecArray[lIndex] ;
	DEBUG_ASSERT(_ptr) ;
	IF_RETURN(NULL == _ptr, E_FAIL) ;

	return _ptr->GetWord(pVal) ;
}

HRESULT CCVarArray::GetDWord(LONG lIndex, DWORD* pVal)
{
	DEBUG_ASSERT_MSG(pVal, _T("args pVal == null")) ;
	IF_RETURN(NULL == pVal, E_INVALIDARG) ;
	DEBUG_ASSERT_MSG(lIndex < (LONG)m_vecArray.size(), _T("index > size")) ;
	IF_RETURN(lIndex >= (LONG)m_vecArray.size(), E_INVALIDARG) ;

	CComPtr<ICVariant> _ptr = this->m_vecArray[lIndex] ;
	DEBUG_ASSERT(_ptr) ;
	IF_RETURN(NULL == _ptr, E_FAIL) ;

	return _ptr->GetDWord(pVal) ;
}

HRESULT CCVarArray::GetShort(LONG lIndex, SHORT* pVal)
{
	DEBUG_ASSERT_MSG(pVal, _T("args pVal == null")) ;
	IF_RETURN(NULL == pVal, E_INVALIDARG) ;
	DEBUG_ASSERT_MSG(lIndex < (LONG)m_vecArray.size(), _T("index > size")) ;
	IF_RETURN(lIndex >= (LONG)m_vecArray.size(), E_INVALIDARG) ;

	CComPtr<ICVariant> _ptr = this->m_vecArray[lIndex] ;
	DEBUG_ASSERT(_ptr) ;
	IF_RETURN(NULL == _ptr, E_FAIL) ;

	return _ptr->GetShort(pVal) ;
}

HRESULT CCVarArray::GetUInt(LONG lIndex, UINT* pVal)
{
	DEBUG_ASSERT_MSG(pVal, _T("args pVal == null")) ;
	IF_RETURN(NULL == pVal, E_INVALIDARG) ;
	DEBUG_ASSERT_MSG(lIndex < (LONG)m_vecArray.size(), _T("index > size")) ;
	IF_RETURN(lIndex >= (LONG)m_vecArray.size(), E_INVALIDARG) ;

	CComPtr<ICVariant> _ptr = this->m_vecArray[lIndex] ;
	DEBUG_ASSERT(_ptr) ;
	IF_RETURN(NULL == _ptr, E_FAIL) ;

	return _ptr->GetUInt(pVal) ;
}

HRESULT CCVarArray::GetUInt32(LONG lIndex, UINT32* pVal)
{
	DEBUG_ASSERT_MSG(pVal, _T("args pVal == null")) ;
	IF_RETURN(NULL == pVal, E_INVALIDARG) ;
	DEBUG_ASSERT_MSG(lIndex < (LONG)m_vecArray.size(), _T("index > size")) ;
	IF_RETURN(lIndex >= (LONG)m_vecArray.size(), E_INVALIDARG) ;

	CComPtr<ICVariant> _ptr = this->m_vecArray[lIndex] ;
	DEBUG_ASSERT(_ptr) ;
	IF_RETURN(NULL == _ptr, E_FAIL) ;

	return _ptr->GetUInt32(pVal) ;
}

HRESULT CCVarArray::GetUInt64(LONG lIndex, UINT64* pVal)
{
	DEBUG_ASSERT_MSG(pVal, _T("args pVal == null")) ;
	IF_RETURN(NULL == pVal, E_INVALIDARG) ;
	DEBUG_ASSERT_MSG(lIndex < (LONG)m_vecArray.size(), _T("index > size")) ;
	IF_RETURN(lIndex >= (LONG)m_vecArray.size(), E_INVALIDARG) ;

	CComPtr<ICVariant> _ptr = this->m_vecArray[lIndex] ;
	DEBUG_ASSERT(_ptr) ;
	IF_RETURN(NULL == _ptr, E_FAIL) ;

	return _ptr->GetUInt64(pVal) ;
}

HRESULT CCVarArray::GetInt(LONG lIndex, INT* pVal)
{
	DEBUG_ASSERT_MSG(pVal, _T("args pVal == null")) ;
	IF_RETURN(NULL == pVal, E_INVALIDARG) ;
	DEBUG_ASSERT_MSG(lIndex < (LONG)m_vecArray.size(), _T("index > size")) ;
	IF_RETURN(lIndex >= (LONG)m_vecArray.size(), E_INVALIDARG) ;

	CComPtr<ICVariant> _ptr = this->m_vecArray[lIndex] ;
	DEBUG_ASSERT(_ptr) ;
	IF_RETURN(NULL == _ptr, E_FAIL) ;

	return _ptr->GetInt(pVal) ;
}

HRESULT CCVarArray::GetInt32(LONG lIndex, INT32* pVal)
{
	DEBUG_ASSERT_MSG(pVal, _T("args pVal == null")) ;
	IF_RETURN(NULL == pVal, E_INVALIDARG) ;
	DEBUG_ASSERT_MSG(lIndex < (LONG)m_vecArray.size(), _T("index > size")) ;
	IF_RETURN(lIndex >= (LONG)m_vecArray.size(), E_INVALIDARG) ;

	CComPtr<ICVariant> _ptr = this->m_vecArray[lIndex] ;
	DEBUG_ASSERT(_ptr) ;
	IF_RETURN(NULL == _ptr, E_FAIL) ;

	return _ptr->GetInt32(pVal) ;
}

HRESULT CCVarArray::GetInt64(LONG lIndex, INT64* pVal)
{
	DEBUG_ASSERT_MSG(pVal, _T("args pVal == null")) ;
	IF_RETURN(NULL == pVal, E_INVALIDARG) ;
	DEBUG_ASSERT_MSG(lIndex < (LONG)m_vecArray.size(), _T("index > size")) ;
	IF_RETURN(lIndex >= (LONG)m_vecArray.size(), E_INVALIDARG) ;

	CComPtr<ICVariant> _ptr = this->m_vecArray[lIndex] ;
	DEBUG_ASSERT(_ptr) ;
	IF_RETURN(NULL == _ptr, E_FAIL) ;

	return _ptr->GetInt64(pVal) ;
}

HRESULT CCVarArray::GetFloat(LONG lIndex, FLOAT* pVal)
{
	DEBUG_ASSERT_MSG(pVal, _T("args pVal == null")) ;
	IF_RETURN(NULL == pVal, E_INVALIDARG) ;
	DEBUG_ASSERT_MSG(lIndex < (LONG)m_vecArray.size(), _T("index > size")) ;
	IF_RETURN(lIndex >= (LONG)m_vecArray.size(), E_INVALIDARG) ;

	CComPtr<ICVariant> _ptr = this->m_vecArray[lIndex] ;
	DEBUG_ASSERT(_ptr) ;
	IF_RETURN(NULL == _ptr, E_FAIL) ;

	return _ptr->GetFloat(pVal) ;
}

HRESULT CCVarArray::GetDouble(LONG lIndex, DOUBLE* pVal)
{
	DEBUG_ASSERT_MSG(pVal, _T("args pVal == null")) ;
	IF_RETURN(NULL == pVal, E_INVALIDARG) ;
	DEBUG_ASSERT_MSG(lIndex < (LONG)m_vecArray.size(), _T("index > size")) ;
	IF_RETURN(lIndex >= (LONG)m_vecArray.size(), E_INVALIDARG) ;

	CComPtr<ICVariant> _ptr = this->m_vecArray[lIndex] ;
	DEBUG_ASSERT(_ptr) ;
	IF_RETURN(NULL == _ptr, E_FAIL) ;

	return _ptr->GetDouble(pVal) ;
}

HRESULT CCVarArray::GetString(LONG lIndex, BSTR* pVal)
{
	DEBUG_ASSERT_MSG(pVal, _T("args pVal == null")) ;
	IF_RETURN(NULL == pVal, E_INVALIDARG) ;
	DEBUG_ASSERT_MSG(lIndex < (LONG)m_vecArray.size(), _T("index > size")) ;
	IF_RETURN(lIndex >= (LONG)m_vecArray.size(), E_INVALIDARG) ;

	CComPtr<ICVariant> _ptr = this->m_vecArray[lIndex] ;
	DEBUG_ASSERT(_ptr) ;
	IF_RETURN(NULL == _ptr, E_FAIL) ;

	return _ptr->GetString(pVal) ;
}

HRESULT CCVarArray::GetGuid(LONG lIndex, GUID* pVal)
{
	DEBUG_ASSERT_MSG(pVal, _T("args pVal == null")) ;
	IF_RETURN(NULL == pVal, E_INVALIDARG) ;
	DEBUG_ASSERT_MSG(lIndex < (LONG)m_vecArray.size(), _T("index > size")) ;
	IF_RETURN(lIndex >= (LONG)m_vecArray.size(), E_INVALIDARG) ;

	CComPtr<ICVariant> _ptr = this->m_vecArray[lIndex] ;
	DEBUG_ASSERT(_ptr) ;
	IF_RETURN(NULL == _ptr, E_FAIL) ;

	return _ptr->GetGuid(pVal) ;
}

HRESULT CCVarArray::GetRect(LONG lIndex, RECT* pVal)
{
	DEBUG_ASSERT_MSG(pVal, _T("args pVal == null")) ;
	IF_RETURN(NULL == pVal, E_INVALIDARG) ;
	DEBUG_ASSERT_MSG(lIndex < (LONG)m_vecArray.size(), _T("index > size")) ;
	IF_RETURN(lIndex >= (LONG)m_vecArray.size(), E_INVALIDARG) ;

	CComPtr<ICVariant> _ptr = this->m_vecArray[lIndex] ;
	DEBUG_ASSERT(_ptr) ;
	IF_RETURN(NULL == _ptr, E_FAIL) ;

	return _ptr->GetRect(pVal) ;
}

HRESULT CCVarArray::GetPoint(LONG lIndex, POINT* pVal)
{
	DEBUG_ASSERT_MSG(pVal, _T("args pVal == null")) ;
	IF_RETURN(NULL == pVal, E_INVALIDARG) ;
	DEBUG_ASSERT_MSG(lIndex < (LONG)m_vecArray.size(), _T("index > size")) ;
	IF_RETURN(lIndex >= (LONG)m_vecArray.size(), E_INVALIDARG) ;

	CComPtr<ICVariant> _ptr = this->m_vecArray[lIndex] ;
	DEBUG_ASSERT(_ptr) ;
	IF_RETURN(NULL == _ptr, E_FAIL) ;

	return _ptr->GetPoint(pVal) ;
}

HRESULT CCVarArray::GetSize(LONG lIndex, SIZE* pVal)
{
	DEBUG_ASSERT_MSG(pVal, _T("args pVal == null")) ;
	IF_RETURN(NULL == pVal, E_INVALIDARG) ;
	DEBUG_ASSERT_MSG(lIndex < (LONG)m_vecArray.size(), _T("index > size")) ;
	IF_RETURN(lIndex >= (LONG)m_vecArray.size(), E_INVALIDARG) ;

	CComPtr<ICVariant> _ptr = this->m_vecArray[lIndex] ;
	DEBUG_ASSERT(_ptr) ;
	IF_RETURN(NULL == _ptr, E_FAIL) ;

	return _ptr->GetSize(pVal) ;
}

HRESULT CCVarArray::GetInterface(LONG lIndex, REFIID iid, VOID** ppVal)
{
	DEBUG_ASSERT_MSG(ppVal, _T("args pVal == null")) ;
	IF_RETURN(NULL == ppVal, E_INVALIDARG) ;
	DEBUG_ASSERT_MSG(lIndex < (LONG)m_vecArray.size(), _T("index > size")) ;
	IF_RETURN(lIndex >= (LONG)m_vecArray.size(), E_INVALIDARG) ;

	CComPtr<ICVariant> _ptr = this->m_vecArray[lIndex] ;
	DEBUG_ASSERT(_ptr) ;
	IF_RETURN(NULL == _ptr, E_FAIL) ;

	return _ptr->GetInterface(iid, ppVal) ;
}

HRESULT CCVarArray::GetVarData(LONG lIndex, ICVarData** ppVal)
{
	return this->GetInterface(lIndex, __uuidof(ICVarData), (VOID**)ppVal) ;
}

HRESULT CCVarArray::GetVarArray(LONG lIndex, ICVarArray** ppVal)
{
	return this->GetInterface(lIndex, __uuidof(ICVarArray), (VOID**)ppVal) ;
}

HRESULT CCVarArray::GetVarBuffer(LONG lIndex, ICVarBuffer** ppVal)
{
	return this->GetInterface(lIndex, __uuidof(ICVarBuffer), (VOID**)ppVal) ;
}

HRESULT CCVarArray::EraseAll()
{
	this->m_vecArray.clear() ;
	return S_OK ;
}

HRESULT CCVarArray::EraseOne(LONG lIndex)
{
	if (lIndex >= 0 && lIndex < (LONG)this->m_vecArray.size())
	{
		VEC_ARRAY::iterator _it = this->m_vecArray.begin() + lIndex ;
		this->m_vecArray.erase(_it) ;
	}
	return S_OK ;
}

HRESULT CCVarArray::AddBool(BOOL val)
{
	CComPtr<ICVariant> _var ;
	Common::Util::CreateObject(&_var) ;
	DEBUG_ASSERT(_var) ;
	IF_RETURN(NULL == _var, E_FAIL) ;

	_var->SetBool(val) ;
	this->m_vecArray.push_back(_var) ;
	return S_OK ;
}

HRESULT CCVarArray::InsertBool(LONG lIndex, BOOL val)
{
	DEBUG_ASSERT_MSG(lIndex < (LONG)m_vecArray.size(), _T("index > size")) ;
	IF_RETURN(lIndex >= (LONG)m_vecArray.size(), E_INVALIDARG) ;

	CComPtr<ICVariant> _var ;
	Common::Util::CreateObject(&_var) ;
	DEBUG_ASSERT(_var) ;
	IF_RETURN(NULL == _var, E_FAIL) ;
	
	_var->SetBool(val) ;
	VEC_ARRAY::iterator _it = this->m_vecArray.begin() + lIndex ;
	this->m_vecArray.insert(_it, _var) ;
	return S_OK ;
}

HRESULT CCVarArray::SetBool(LONG lIndex, BOOL val)
{
	DEBUG_ASSERT_MSG(lIndex < (LONG)m_vecArray.size(), _T("index > size")) ;
	IF_RETURN(lIndex >= (LONG)m_vecArray.size(), E_INVALIDARG) ;

	CComPtr<ICVariant> _var ;
	Common::Util::CreateObject(&_var) ;
	DEBUG_ASSERT(_var) ;
	IF_RETURN(NULL == _var, E_FAIL) ;

	_var->SetBool(val) ;
	this->m_vecArray[lIndex] = _var ;
	return S_OK ;
}

HRESULT CCVarArray::AddChar(CHAR val)
{
	CComPtr<ICVariant> _var ;
	Common::Util::CreateObject(&_var) ;
	DEBUG_ASSERT(_var) ;
	IF_RETURN(NULL == _var, E_FAIL) ;

	_var->SetChar(val) ;
	this->m_vecArray.push_back(_var) ;
	return S_OK ;
}

HRESULT CCVarArray::InsertChar(LONG lIndex, CHAR val)
{
	DEBUG_ASSERT_MSG(lIndex < (LONG)m_vecArray.size(), _T("index > size")) ;
	IF_RETURN(lIndex >= (LONG)m_vecArray.size(), E_INVALIDARG) ;

	CComPtr<ICVariant> _var ;
	Common::Util::CreateObject(&_var) ;
	DEBUG_ASSERT(_var) ;
	IF_RETURN(NULL == _var, E_FAIL) ;

	_var->SetChar(val) ;
	VEC_ARRAY::iterator _it = this->m_vecArray.begin() + lIndex ;
	this->m_vecArray.insert(_it, _var) ;
	return S_OK ;
}

HRESULT CCVarArray::SetChar(LONG lIndex, CHAR val)
{
	DEBUG_ASSERT_MSG(lIndex < (LONG)m_vecArray.size(), _T("index > size")) ;
	IF_RETURN(lIndex >= (LONG)m_vecArray.size(), E_INVALIDARG) ;

	CComPtr<ICVariant> _var ;
	Common::Util::CreateObject(&_var) ;
	DEBUG_ASSERT(_var) ;
	IF_RETURN(NULL == _var, E_FAIL) ;

	_var->SetChar(val) ;
	this->m_vecArray[lIndex] = _var ;
	return S_OK ;
}

HRESULT CCVarArray::AddWChar(WCHAR val)
{
	CComPtr<ICVariant> _var ;
	Common::Util::CreateObject(&_var) ;
	DEBUG_ASSERT(_var) ;
	IF_RETURN(NULL == _var, E_FAIL) ;

	_var->SetWChar(val) ;
	this->m_vecArray.push_back(_var) ;
	return S_OK ;
}

HRESULT CCVarArray::InsertWChar(LONG lIndex, WCHAR val)
{
	DEBUG_ASSERT_MSG(lIndex < (LONG)m_vecArray.size(), _T("index > size")) ;
	IF_RETURN(lIndex >= (LONG)m_vecArray.size(), E_INVALIDARG) ;

	CComPtr<ICVariant> _var ;
	Common::Util::CreateObject(&_var) ;
	DEBUG_ASSERT(_var) ;
	IF_RETURN(NULL == _var, E_FAIL) ;

	_var->SetWChar(val) ;
	VEC_ARRAY::iterator _it = this->m_vecArray.begin() + lIndex ;
	this->m_vecArray.insert(_it, _var) ;
	return S_OK ;
}

HRESULT CCVarArray::SetWChar(LONG lIndex, WCHAR val)
{
	DEBUG_ASSERT_MSG(lIndex < (LONG)m_vecArray.size(), _T("index > size")) ;
	IF_RETURN(lIndex >= (LONG)m_vecArray.size(), E_INVALIDARG) ;

	CComPtr<ICVariant> _var ;
	Common::Util::CreateObject(&_var) ;
	DEBUG_ASSERT(_var) ;
	IF_RETURN(NULL == _var, E_FAIL) ;

	_var->SetWChar(val) ;
	this->m_vecArray[lIndex] = _var ;
	return S_OK ;
}

HRESULT CCVarArray::AddWord(WORD val)
{
	CComPtr<ICVariant> _var ;
	Common::Util::CreateObject(&_var) ;
	DEBUG_ASSERT(_var) ;
	IF_RETURN(NULL == _var, E_FAIL) ;

	_var->SetWord(val) ;
	this->m_vecArray.push_back(_var) ;
	return S_OK ;
}

HRESULT CCVarArray::InsertWord(LONG lIndex, WORD val)
{
	DEBUG_ASSERT_MSG(lIndex < (LONG)m_vecArray.size(), _T("index > size")) ;
	IF_RETURN(lIndex >= (LONG)m_vecArray.size(), E_INVALIDARG) ;

	CComPtr<ICVariant> _var ;
	Common::Util::CreateObject(&_var) ;
	DEBUG_ASSERT(_var) ;
	IF_RETURN(NULL == _var, E_FAIL) ;

	_var->SetWord(val) ;
	VEC_ARRAY::iterator _it = this->m_vecArray.begin() + lIndex ;
	this->m_vecArray.insert(_it, _var) ;
	return S_OK ;
}

HRESULT CCVarArray::SetWord(LONG lIndex, WORD val)
{
	DEBUG_ASSERT_MSG(lIndex < (LONG)m_vecArray.size(), _T("index > size")) ;
	IF_RETURN(lIndex >= (LONG)m_vecArray.size(), E_INVALIDARG) ;

	CComPtr<ICVariant> _var ;
	Common::Util::CreateObject(&_var) ;
	DEBUG_ASSERT(_var) ;
	IF_RETURN(NULL == _var, E_FAIL) ;

	_var->SetWord(val) ;
	this->m_vecArray[lIndex] = _var ;
	return S_OK ;
}

HRESULT CCVarArray::AddDWord(DWORD val)
{
	CComPtr<ICVariant> _var ;
	Common::Util::CreateObject(&_var) ;
	DEBUG_ASSERT(_var) ;
	IF_RETURN(NULL == _var, E_FAIL) ;

	_var->SetDWord(val) ;
	this->m_vecArray.push_back(_var) ;
	return S_OK ;
}

HRESULT CCVarArray::InsertDWord(LONG lIndex, DWORD val)
{
	DEBUG_ASSERT_MSG(lIndex < (LONG)m_vecArray.size(), _T("index > size")) ;
	IF_RETURN(lIndex >= (LONG)m_vecArray.size(), E_INVALIDARG) ;

	CComPtr<ICVariant> _var ;
	Common::Util::CreateObject(&_var) ;
	DEBUG_ASSERT(_var) ;
	IF_RETURN(NULL == _var, E_FAIL) ;

	_var->SetDWord(val) ;
	VEC_ARRAY::iterator _it = this->m_vecArray.begin() + lIndex ;
	this->m_vecArray.insert(_it, _var) ;
	return S_OK ;
}

HRESULT CCVarArray::SetDWord(LONG lIndex, DWORD val)
{
	DEBUG_ASSERT_MSG(lIndex < (LONG)m_vecArray.size(), _T("index > size")) ;
	IF_RETURN(lIndex >= (LONG)m_vecArray.size(), E_INVALIDARG) ;

	CComPtr<ICVariant> _var ;
	Common::Util::CreateObject(&_var) ;
	DEBUG_ASSERT(_var) ;
	IF_RETURN(NULL == _var, E_FAIL) ;

	_var->SetDWord(val) ;
	this->m_vecArray[lIndex] = _var ;
	return S_OK ;
}

HRESULT CCVarArray::AddShort(SHORT val)
{
	CComPtr<ICVariant> _var ;
	Common::Util::CreateObject(&_var) ;
	DEBUG_ASSERT(_var) ;
	IF_RETURN(NULL == _var, E_FAIL) ;

	_var->SetShort(val) ;
	this->m_vecArray.push_back(_var) ;
	return S_OK ;
}

HRESULT CCVarArray::InsertShort(LONG lIndex, SHORT val)
{
	DEBUG_ASSERT_MSG(lIndex < (LONG)m_vecArray.size(), _T("index > size")) ;
	IF_RETURN(lIndex >= (LONG)m_vecArray.size(), E_INVALIDARG) ;

	CComPtr<ICVariant> _var ;
	Common::Util::CreateObject(&_var) ;
	DEBUG_ASSERT(_var) ;
	IF_RETURN(NULL == _var, E_FAIL) ;

	_var->SetShort(val) ;
	VEC_ARRAY::iterator _it = this->m_vecArray.begin() + lIndex ;
	this->m_vecArray.insert(_it, _var) ;
	return S_OK ;
}

HRESULT CCVarArray::SetShort(LONG lIndex, SHORT val)
{
	DEBUG_ASSERT_MSG(lIndex < (LONG)m_vecArray.size(), _T("index > size")) ;
	IF_RETURN(lIndex >= (LONG)m_vecArray.size(), E_INVALIDARG) ;

	CComPtr<ICVariant> _var ;
	Common::Util::CreateObject(&_var) ;
	DEBUG_ASSERT(_var) ;
	IF_RETURN(NULL == _var, E_FAIL) ;

	_var->SetShort(val) ;
	this->m_vecArray[lIndex] = _var ;
	return S_OK ;
}

HRESULT CCVarArray::AddUInt(UINT val)
{
	CComPtr<ICVariant> _var ;
	Common::Util::CreateObject(&_var) ;
	DEBUG_ASSERT(_var) ;
	IF_RETURN(NULL == _var, E_FAIL) ;

	_var->SetInt(val) ;
	this->m_vecArray.push_back(_var) ;
	return S_OK ;
}

HRESULT CCVarArray::InsertUInt(LONG lIndex, UINT val)
{
	DEBUG_ASSERT_MSG(lIndex < (LONG)m_vecArray.size(), _T("index > size")) ;
	IF_RETURN(lIndex >= (LONG)m_vecArray.size(), E_INVALIDARG) ;

	CComPtr<ICVariant> _var ;
	Common::Util::CreateObject(&_var) ;
	DEBUG_ASSERT(_var) ;
	IF_RETURN(NULL == _var, E_FAIL) ;

	_var->SetUInt(val) ;
	VEC_ARRAY::iterator _it = this->m_vecArray.begin() + lIndex ;
	this->m_vecArray.insert(_it, _var) ;
	return S_OK ;
}

HRESULT CCVarArray::SetUInt(LONG lIndex, UINT val)
{
	DEBUG_ASSERT_MSG(lIndex < (LONG)m_vecArray.size(), _T("index > size")) ;
	IF_RETURN(lIndex >= (LONG)m_vecArray.size(), E_INVALIDARG) ;

	CComPtr<ICVariant> _var ;
	Common::Util::CreateObject(&_var) ;
	DEBUG_ASSERT(_var) ;
	IF_RETURN(NULL == _var, E_FAIL) ;

	_var->SetUInt(val) ;
	this->m_vecArray[lIndex] = _var ;
	return S_OK ;
}

HRESULT CCVarArray::AddUInt32(UINT32 val)
{
	CComPtr<ICVariant> _var ;
	Common::Util::CreateObject(&_var) ;
	DEBUG_ASSERT(_var) ;
	IF_RETURN(NULL == _var, E_FAIL) ;

	_var->SetUInt32(val) ;
	this->m_vecArray.push_back(_var) ;
	return S_OK ;
}

HRESULT CCVarArray::InsertUInt32(LONG lIndex, UINT32 val)
{
	DEBUG_ASSERT_MSG(lIndex < (LONG)m_vecArray.size(), _T("index > size")) ;
	IF_RETURN(lIndex >= (LONG)m_vecArray.size(), E_INVALIDARG) ;

	CComPtr<ICVariant> _var ;
	Common::Util::CreateObject(&_var) ;
	DEBUG_ASSERT(_var) ;
	IF_RETURN(NULL == _var, E_FAIL) ;

	_var->SetUInt32(val) ;
	VEC_ARRAY::iterator _it = this->m_vecArray.begin() + lIndex ;
	this->m_vecArray.insert(_it, _var) ;
	return S_OK ;
}

HRESULT CCVarArray::SetUInt32(LONG lIndex, UINT32 val)
{
	DEBUG_ASSERT_MSG(lIndex < (LONG)m_vecArray.size(), _T("index > size")) ;
	IF_RETURN(lIndex >= (LONG)m_vecArray.size(), E_INVALIDARG) ;

	CComPtr<ICVariant> _var ;
	Common::Util::CreateObject(&_var) ;
	DEBUG_ASSERT(_var) ;
	IF_RETURN(NULL == _var, E_FAIL) ;

	_var->SetUInt32(val) ;
	this->m_vecArray[lIndex] = _var ;
	return S_OK ;
}

HRESULT CCVarArray::AddUInt64(UINT64 val)
{
	CComPtr<ICVariant> _var ;
	Common::Util::CreateObject(&_var) ;
	DEBUG_ASSERT(_var) ;
	IF_RETURN(NULL == _var, E_FAIL) ;

	_var->SetUInt64(val) ;
	this->m_vecArray.push_back(_var) ;
	return S_OK ;
}

HRESULT CCVarArray::InsertUInt64(LONG lIndex, UINT64 val)
{
	DEBUG_ASSERT_MSG(lIndex < (LONG)m_vecArray.size(), _T("index > size")) ;
	IF_RETURN(lIndex >= (LONG)m_vecArray.size(), E_INVALIDARG) ;

	CComPtr<ICVariant> _var ;
	Common::Util::CreateObject(&_var) ;
	DEBUG_ASSERT(_var) ;
	IF_RETURN(NULL == _var, E_FAIL) ;

	_var->SetUInt64(val) ;
	VEC_ARRAY::iterator _it = this->m_vecArray.begin() + lIndex ;
	this->m_vecArray.insert(_it, _var) ;
	return S_OK ;
}

HRESULT CCVarArray::SetUInt64(LONG lIndex, UINT64 val)
{
	DEBUG_ASSERT_MSG(lIndex < (LONG)m_vecArray.size(), _T("index > size")) ;
	IF_RETURN(lIndex >= (LONG)m_vecArray.size(), E_INVALIDARG) ;

	CComPtr<ICVariant> _var ;
	Common::Util::CreateObject(&_var) ;
	DEBUG_ASSERT(_var) ;
	IF_RETURN(NULL == _var, E_FAIL) ;

	_var->SetUInt64(val) ;
	this->m_vecArray[lIndex] = _var ;
	return S_OK ;
}

HRESULT CCVarArray::AddInt(INT val)
{
	CComPtr<ICVariant> _var ;
	Common::Util::CreateObject(&_var) ;
	DEBUG_ASSERT(_var) ;
	IF_RETURN(NULL == _var, E_FAIL) ;

	_var->SetInt(val) ;
	this->m_vecArray.push_back(_var) ;
	return S_OK ;
}

HRESULT CCVarArray::InsertInt(LONG lIndex, INT val)
{
	DEBUG_ASSERT_MSG(lIndex < (LONG)m_vecArray.size(), _T("index > size")) ;
	IF_RETURN(lIndex >= (LONG)m_vecArray.size(), E_INVALIDARG) ;

	CComPtr<ICVariant> _var ;
	Common::Util::CreateObject(&_var) ;
	DEBUG_ASSERT(_var) ;
	IF_RETURN(NULL == _var, E_FAIL) ;

	_var->SetInt(val) ;
	VEC_ARRAY::iterator _it = this->m_vecArray.begin() + lIndex ;
	this->m_vecArray.insert(_it, _var) ;
	return S_OK ;
}

HRESULT CCVarArray::SetInt(LONG lIndex, INT val)
{
	DEBUG_ASSERT_MSG(lIndex < (LONG)m_vecArray.size(), _T("index > size")) ;
	IF_RETURN(lIndex >= (LONG)m_vecArray.size(), E_INVALIDARG) ;

	CComPtr<ICVariant> _var ;
	Common::Util::CreateObject(&_var) ;
	DEBUG_ASSERT(_var) ;
	IF_RETURN(NULL == _var, E_FAIL) ;

	_var->SetInt(val) ;
	this->m_vecArray[lIndex] = _var ;
	return S_OK ;
}

HRESULT CCVarArray::AddInt32(INT32 val)
{
	CComPtr<ICVariant> _var ;
	Common::Util::CreateObject(&_var) ;
	DEBUG_ASSERT(_var) ;
	IF_RETURN(NULL == _var, E_FAIL) ;

	_var->SetInt32(val) ;
	this->m_vecArray.push_back(_var) ;
	return S_OK ;
}

HRESULT CCVarArray::InsertInt32(LONG lIndex, INT32 val)
{
	DEBUG_ASSERT_MSG(lIndex < (LONG)m_vecArray.size(), _T("index > size")) ;
	IF_RETURN(lIndex >= (LONG)m_vecArray.size(), E_INVALIDARG) ;

	CComPtr<ICVariant> _var ;
	Common::Util::CreateObject(&_var) ;
	DEBUG_ASSERT(_var) ;
	IF_RETURN(NULL == _var, E_FAIL) ;

	_var->SetInt32(val) ;
	VEC_ARRAY::iterator _it = this->m_vecArray.begin() + lIndex ;
	this->m_vecArray.insert(_it, _var) ;
	return S_OK ;
}

HRESULT CCVarArray::SetInt32(LONG lIndex, INT32 val)
{
	DEBUG_ASSERT_MSG(lIndex < (LONG)m_vecArray.size(), _T("index > size")) ;
	IF_RETURN(lIndex >= (LONG)m_vecArray.size(), E_INVALIDARG) ;

	CComPtr<ICVariant> _var ;
	Common::Util::CreateObject(&_var) ;
	DEBUG_ASSERT(_var) ;
	IF_RETURN(NULL == _var, E_FAIL) ;

	_var->SetInt32(val) ;
	this->m_vecArray[lIndex] = _var ;
	return S_OK ;
}

HRESULT CCVarArray::AddInt64(INT64 val)
{
	CComPtr<ICVariant> _var ;
	Common::Util::CreateObject(&_var) ;
	DEBUG_ASSERT(_var) ;
	IF_RETURN(NULL == _var, E_FAIL) ;

	_var->SetInt64(val) ;
	this->m_vecArray.push_back(_var) ;
	return S_OK ;
}

HRESULT CCVarArray::InsertInt64(LONG lIndex, INT64 val)
{
	DEBUG_ASSERT_MSG(lIndex < (LONG)m_vecArray.size(), _T("index > size")) ;
	IF_RETURN(lIndex >= (LONG)m_vecArray.size(), E_INVALIDARG) ;

	CComPtr<ICVariant> _var ;
	Common::Util::CreateObject(&_var) ;
	DEBUG_ASSERT(_var) ;
	IF_RETURN(NULL == _var, E_FAIL) ;

	_var->SetInt64(val) ;
	VEC_ARRAY::iterator _it = this->m_vecArray.begin() + lIndex ;
	this->m_vecArray.insert(_it, _var) ;
	return S_OK ;
}

HRESULT CCVarArray::SetInt64(LONG lIndex, INT64 val)
{
	DEBUG_ASSERT_MSG(lIndex < (LONG)m_vecArray.size(), _T("index > size")) ;
	IF_RETURN(lIndex >= (LONG)m_vecArray.size(), E_INVALIDARG) ;

	CComPtr<ICVariant> _var ;
	Common::Util::CreateObject(&_var) ;
	DEBUG_ASSERT(_var) ;
	IF_RETURN(NULL == _var, E_FAIL) ;

	_var->SetInt64(val) ;
	this->m_vecArray[lIndex] = _var ;
	return S_OK ;
}

HRESULT CCVarArray::AddFloat(FLOAT val)
{
	CComPtr<ICVariant> _var ;
	Common::Util::CreateObject(&_var) ;
	DEBUG_ASSERT(_var) ;
	IF_RETURN(NULL == _var, E_FAIL) ;

	_var->SetFloat(val) ;
	this->m_vecArray.push_back(_var) ;
	return S_OK ;
}

HRESULT CCVarArray::InsertFloat(LONG lIndex, FLOAT val)
{
	DEBUG_ASSERT_MSG(lIndex < (LONG)m_vecArray.size(), _T("index > size")) ;
	IF_RETURN(lIndex >= (LONG)m_vecArray.size(), E_INVALIDARG) ;

	CComPtr<ICVariant> _var ;
	Common::Util::CreateObject(&_var) ;
	DEBUG_ASSERT(_var) ;
	IF_RETURN(NULL == _var, E_FAIL) ;

	_var->SetFloat(val) ;
	VEC_ARRAY::iterator _it = this->m_vecArray.begin() + lIndex ;
	this->m_vecArray.insert(_it, _var) ;
	return S_OK ;
}

HRESULT CCVarArray::SetFloat(LONG lIndex, FLOAT val)
{
	DEBUG_ASSERT_MSG(lIndex < (LONG)m_vecArray.size(), _T("index > size")) ;
	IF_RETURN(lIndex >= (LONG)m_vecArray.size(), E_INVALIDARG) ;

	CComPtr<ICVariant> _var ;
	Common::Util::CreateObject(&_var) ;
	DEBUG_ASSERT(_var) ;
	IF_RETURN(NULL == _var, E_FAIL) ;

	_var->SetFloat(val) ;
	this->m_vecArray[lIndex] = _var ;
	return S_OK ;
}

HRESULT CCVarArray::AddDouble(DOUBLE val)
{
	CComPtr<ICVariant> _var ;
	Common::Util::CreateObject(&_var) ;
	DEBUG_ASSERT(_var) ;
	IF_RETURN(NULL == _var, E_FAIL) ;

	_var->SetDouble(val) ;
	this->m_vecArray.push_back(_var) ;
	return S_OK ;
}

HRESULT CCVarArray::InsertDouble(LONG lIndex, DOUBLE val)
{
	DEBUG_ASSERT_MSG(lIndex < (LONG)m_vecArray.size(), _T("index > size")) ;
	IF_RETURN(lIndex >= (LONG)m_vecArray.size(), E_INVALIDARG) ;

	CComPtr<ICVariant> _var ;
	Common::Util::CreateObject(&_var) ;
	DEBUG_ASSERT(_var) ;
	IF_RETURN(NULL == _var, E_FAIL) ;

	_var->SetDouble(val) ;
	VEC_ARRAY::iterator _it = this->m_vecArray.begin() + lIndex ;
	this->m_vecArray.insert(_it, _var) ;
	return S_OK ;
}

HRESULT CCVarArray::SetDouble(LONG lIndex, DOUBLE val)
{
	DEBUG_ASSERT_MSG(lIndex < (LONG)m_vecArray.size(), _T("index > size")) ;
	IF_RETURN(lIndex >= (LONG)m_vecArray.size(), E_INVALIDARG) ;

	CComPtr<ICVariant> _var ;
	Common::Util::CreateObject(&_var) ;
	DEBUG_ASSERT(_var) ;
	IF_RETURN(NULL == _var, E_FAIL) ;

	_var->SetDouble(val) ;
	this->m_vecArray[lIndex] = _var ;
	return S_OK ;
}

HRESULT CCVarArray::AddString(BSTR val)
{
	CComPtr<ICVariant> _var ;
	Common::Util::CreateObject(&_var) ;
	DEBUG_ASSERT(_var) ;
	IF_RETURN(NULL == _var, E_FAIL) ;

	_var->SetString(val) ;
	this->m_vecArray.push_back(_var) ;
	return S_OK ;
}

HRESULT CCVarArray::InsertString(LONG lIndex, BSTR val)
{
	DEBUG_ASSERT_MSG(lIndex < (LONG)m_vecArray.size(), _T("index > size")) ;
	IF_RETURN(lIndex >= (LONG)m_vecArray.size(), E_INVALIDARG) ;

	CComPtr<ICVariant> _var ;
	Common::Util::CreateObject(&_var) ;
	DEBUG_ASSERT(_var) ;
	IF_RETURN(NULL == _var, E_FAIL) ;

	_var->SetString(val) ;
	VEC_ARRAY::iterator _it = this->m_vecArray.begin() + lIndex ;
	this->m_vecArray.insert(_it, _var) ;
	return S_OK ;
}

HRESULT CCVarArray::SetString(LONG lIndex, BSTR val)
{
	DEBUG_ASSERT_MSG(lIndex < (LONG)m_vecArray.size(), _T("index > size")) ;
	IF_RETURN(lIndex >= (LONG)m_vecArray.size(), E_INVALIDARG) ;

	CComPtr<ICVariant> _var ;
	Common::Util::CreateObject(&_var) ;
	DEBUG_ASSERT(_var) ;
	IF_RETURN(NULL == _var, E_FAIL) ;

	_var->SetString(val) ;
	this->m_vecArray[lIndex] = _var ;
	return S_OK ;
}

HRESULT CCVarArray::AddGuid(GUID val)
{
	CComPtr<ICVariant> _var ;
	Common::Util::CreateObject(&_var) ;
	DEBUG_ASSERT(_var) ;
	IF_RETURN(NULL == _var, E_FAIL) ;

	_var->SetGuid(val) ;
	this->m_vecArray.push_back(_var) ;
	return S_OK ;
}

HRESULT CCVarArray::InsertGuid(LONG lIndex, GUID val)
{
	DEBUG_ASSERT_MSG(lIndex < (LONG)m_vecArray.size(), _T("index > size")) ;
	IF_RETURN(lIndex >= (LONG)m_vecArray.size(), E_INVALIDARG) ;

	CComPtr<ICVariant> _var ;
	Common::Util::CreateObject(&_var) ;
	DEBUG_ASSERT(_var) ;
	IF_RETURN(NULL == _var, E_FAIL) ;

	_var->SetGuid(val) ;
	VEC_ARRAY::iterator _it = this->m_vecArray.begin() + lIndex ;
	this->m_vecArray.insert(_it, _var) ;
	return S_OK ;
}

HRESULT CCVarArray::SetGuid(LONG lIndex, GUID val)
{
	DEBUG_ASSERT_MSG(lIndex < (LONG)m_vecArray.size(), _T("index > size")) ;
	IF_RETURN(lIndex >= (LONG)m_vecArray.size(), E_INVALIDARG) ;

	CComPtr<ICVariant> _var ;
	Common::Util::CreateObject(&_var) ;
	DEBUG_ASSERT(_var) ;
	IF_RETURN(NULL == _var, E_FAIL) ;

	_var->SetGuid(val) ;
	this->m_vecArray[lIndex] = _var ;
	return S_OK ;
}

HRESULT CCVarArray::AddRect(RECT val)
{
	CComPtr<ICVariant> _var ;
	Common::Util::CreateObject(&_var) ;
	DEBUG_ASSERT(_var) ;
	IF_RETURN(NULL == _var, E_FAIL) ;

	_var->SetRect(val) ;
	this->m_vecArray.push_back(_var) ;
	return S_OK ;
}

HRESULT CCVarArray::InsertRect(LONG lIndex, RECT val)
{
	DEBUG_ASSERT_MSG(lIndex < (LONG)m_vecArray.size(), _T("index > size")) ;
	IF_RETURN(lIndex >= (LONG)m_vecArray.size(), E_INVALIDARG) ;

	CComPtr<ICVariant> _var ;
	Common::Util::CreateObject(&_var) ;
	DEBUG_ASSERT(_var) ;
	IF_RETURN(NULL == _var, E_FAIL) ;

	_var->SetRect(val) ;
	VEC_ARRAY::iterator _it = this->m_vecArray.begin() + lIndex ;
	this->m_vecArray.insert(_it, _var) ;
	return S_OK ;
}

HRESULT CCVarArray::SetRect(LONG lIndex, RECT val)
{
	DEBUG_ASSERT_MSG(lIndex < (LONG)m_vecArray.size(), _T("index > size")) ;
	IF_RETURN(lIndex >= (LONG)m_vecArray.size(), E_INVALIDARG) ;

	CComPtr<ICVariant> _var ;
	Common::Util::CreateObject(&_var) ;
	DEBUG_ASSERT(_var) ;
	IF_RETURN(NULL == _var, E_FAIL) ;

	_var->SetRect(val) ;
	this->m_vecArray[lIndex] = _var ;
	return S_OK ;
}

HRESULT CCVarArray::AddPoint(POINT val)
{
	CComPtr<ICVariant> _var ;
	Common::Util::CreateObject(&_var) ;
	DEBUG_ASSERT(_var) ;
	IF_RETURN(NULL == _var, E_FAIL) ;

	_var->SetPoint(val) ;
	this->m_vecArray.push_back(_var) ;
	return S_OK ;
}

HRESULT CCVarArray::InsertPoint(LONG lIndex, POINT val)
{
	DEBUG_ASSERT_MSG(lIndex < (LONG)m_vecArray.size(), _T("index > size")) ;
	IF_RETURN(lIndex >= (LONG)m_vecArray.size(), E_INVALIDARG) ;

	CComPtr<ICVariant> _var ;
	Common::Util::CreateObject(&_var) ;
	DEBUG_ASSERT(_var) ;
	IF_RETURN(NULL == _var, E_FAIL) ;

	_var->SetPoint(val) ;
	VEC_ARRAY::iterator _it = this->m_vecArray.begin() + lIndex ;
	this->m_vecArray.insert(_it, _var) ;
	return S_OK ;
}

HRESULT CCVarArray::SetPoint(LONG lIndex, POINT val)
{
	DEBUG_ASSERT_MSG(lIndex < (LONG)m_vecArray.size(), _T("index > size")) ;
	IF_RETURN(lIndex >= (LONG)m_vecArray.size(), E_INVALIDARG) ;

	CComPtr<ICVariant> _var ;
	Common::Util::CreateObject(&_var) ;
	DEBUG_ASSERT(_var) ;
	IF_RETURN(NULL == _var, E_FAIL) ;

	_var->SetPoint(val) ;
	this->m_vecArray[lIndex] = _var ;
	return S_OK ;
}

HRESULT CCVarArray::AddSize(SIZE val)
{
	CComPtr<ICVariant> _var ;
	Common::Util::CreateObject(&_var) ;
	DEBUG_ASSERT(_var) ;
	IF_RETURN(NULL == _var, E_FAIL) ;

	_var->SetSize(val) ;
	this->m_vecArray.push_back(_var) ;
	return S_OK ;
}

HRESULT CCVarArray::InsertSize(LONG lIndex, SIZE val)
{
	DEBUG_ASSERT_MSG(lIndex < (LONG)m_vecArray.size(), _T("index > size")) ;
	IF_RETURN(lIndex >= (LONG)m_vecArray.size(), E_INVALIDARG) ;

	CComPtr<ICVariant> _var ;
	Common::Util::CreateObject(&_var) ;
	DEBUG_ASSERT(_var) ;
	IF_RETURN(NULL == _var, E_FAIL) ;

	_var->SetSize(val) ;
	VEC_ARRAY::iterator _it = this->m_vecArray.begin() + lIndex ;
	this->m_vecArray.insert(_it, _var) ;
	return S_OK ;
}

HRESULT CCVarArray::SetSize(LONG lIndex, SIZE val)
{
	DEBUG_ASSERT_MSG(lIndex < (LONG)m_vecArray.size(), _T("index > size")) ;
	IF_RETURN(lIndex >= (LONG)m_vecArray.size(), E_INVALIDARG) ;

	CComPtr<ICVariant> _var ;
	Common::Util::CreateObject(&_var) ;
	DEBUG_ASSERT(_var) ;
	IF_RETURN(NULL == _var, E_FAIL) ;

	_var->SetSize(val) ;
	this->m_vecArray[lIndex] = _var ;
	return S_OK ;
}

HRESULT CCVarArray::AddInterface(IUnknown* pVal)
{
	CComPtr<ICVariant> _var ;
	Common::Util::CreateObject(&_var) ;
	DEBUG_ASSERT(_var) ;
	IF_RETURN(NULL == _var, E_FAIL) ;

	_var->SetInterface(pVal) ;
	this->m_vecArray.push_back(_var) ;
	return S_OK ;
}

HRESULT CCVarArray::InsertInterface(LONG lIndex, IUnknown* pVal)
{
	DEBUG_ASSERT_MSG(lIndex < (LONG)m_vecArray.size(), _T("index > size")) ;
	IF_RETURN(lIndex >= (LONG)m_vecArray.size(), E_INVALIDARG) ;

	CComPtr<ICVariant> _var ;
	Common::Util::CreateObject(&_var) ;
	DEBUG_ASSERT(_var) ;
	IF_RETURN(NULL == _var, E_FAIL) ;

	_var->SetInterface(pVal) ;
	VEC_ARRAY::iterator _it = this->m_vecArray.begin() + lIndex ;
	this->m_vecArray.insert(_it, _var) ;
	return S_OK ;
}

HRESULT CCVarArray::SetInterface(LONG lIndex, IUnknown* pVal)
{
	DEBUG_ASSERT_MSG(lIndex < (LONG)m_vecArray.size(), _T("index > size")) ;
	IF_RETURN(lIndex >= (LONG)m_vecArray.size(), E_INVALIDARG) ;

	CComPtr<ICVariant> _var ;
	Common::Util::CreateObject(&_var) ;
	DEBUG_ASSERT(_var) ;
	IF_RETURN(NULL == _var, E_FAIL) ;

	_var->SetInterface(pVal) ;
	this->m_vecArray[lIndex] = _var ;
	return S_OK ;
}

HRESULT CCVarArray::AddVarData(ICVarData* pVal)
{
	return this->AddInterface(pVal) ;
}

HRESULT CCVarArray::AddNewVarData(ICVarData** ppVal)
{
	DEBUG_ASSERT(ppVal) ;
	IF_RETURN(NULL == ppVal, E_INVALIDARG) ;
	*ppVal = NULL ;

	CComPtr<ICVarData> _pVarData ;
	Common::Util::CreateObject(&_pVarData) ;
	IF_RETURN(NULL == _pVarData, E_FAIL) ;

	_pVarData->QueryInterface(__uuidof(ICVarData), (VOID**)ppVal) ;
	return this->AddInterface(_pVarData) ;
}

HRESULT CCVarArray::InsertVarData(LONG lIndex, ICVarData* pVal)
{
	return this->InsertInterface(lIndex, pVal) ;
}

HRESULT CCVarArray::InsertNewVarData(LONG lIndex, ICVarData** ppVal)
{
	DEBUG_ASSERT(ppVal) ;
	IF_RETURN(NULL == ppVal, E_INVALIDARG) ;
	*ppVal = NULL ;

	CComPtr<ICVarData> _pVarData ;
	Common::Util::CreateObject(&_pVarData) ;
	IF_RETURN(NULL == _pVarData, E_FAIL) ;

	_pVarData->QueryInterface(__uuidof(ICVarData), (VOID**)ppVal) ;
	return this->InsertInterface(lIndex, _pVarData) ;
}

HRESULT CCVarArray::SetVarData(LONG lIndex, ICVarData* pVal)
{
	return this->SetInterface(lIndex, pVal) ;
}

HRESULT CCVarArray::SetNewVarData(LONG lIndex, ICVarData** ppVal)
{
	DEBUG_ASSERT(ppVal) ;
	IF_RETURN(NULL == ppVal, E_INVALIDARG) ;
	*ppVal = NULL ;

	CComPtr<ICVarData> _pVarData ;
	Common::Util::CreateObject(&_pVarData) ;
	IF_RETURN(NULL == _pVarData, E_FAIL) ;
	_pVarData->QueryInterface(__uuidof(ICVarData), (VOID**)ppVal) ;

	return this->SetInterface(lIndex, _pVarData) ;
}

HRESULT CCVarArray::AddVarArray(ICVarArray* pVal)
{
	return this->AddInterface(pVal) ;
}

HRESULT CCVarArray::AddNewVarArray(ICVarArray** ppVal)
{
	DEBUG_ASSERT(ppVal) ;
	IF_RETURN(NULL == ppVal, E_INVALIDARG) ;
	*ppVal = NULL ;

	CComPtr<ICVarArray> _pVarArray ;
	Common::Util::CreateObject(&_pVarArray) ;
	IF_RETURN(NULL == _pVarArray, E_FAIL) ;
	_pVarArray->QueryInterface(__uuidof(ICVarArray), (VOID**)ppVal) ;

	return this->AddInterface(_pVarArray) ;
}

HRESULT CCVarArray::InsertVarArray(LONG lIndex, ICVarArray* pVal)
{
	return this->InsertInterface(lIndex, pVal) ;
}

HRESULT CCVarArray::InsertNewVarArray(LONG lIndex, ICVarArray** ppVal)
{
	DEBUG_ASSERT(ppVal) ;
	IF_RETURN(NULL == ppVal, E_INVALIDARG) ;
	*ppVal = NULL ;

	CComPtr<ICVarArray> _pVarArray ;
	Common::Util::CreateObject(&_pVarArray) ;
	IF_RETURN(NULL == _pVarArray, E_FAIL) ;
	_pVarArray->QueryInterface(__uuidof(ICVarArray), (VOID**)ppVal) ;

	return this->InsertInterface(lIndex, _pVarArray) ;
}

HRESULT CCVarArray::SetVarArray(LONG lIndex, ICVarArray* pVal)
{
	return this->SetInterface(lIndex, pVal) ;
}

HRESULT CCVarArray::SetNewVarArray(LONG lIndex, ICVarArray** ppVal)
{
	DEBUG_ASSERT(ppVal) ;
	IF_RETURN(NULL == ppVal, E_INVALIDARG) ;
	*ppVal = NULL ;

	CComPtr<ICVarArray> _pVarArray ;
	Common::Util::CreateObject(&_pVarArray) ;
	IF_RETURN(NULL == _pVarArray, E_FAIL) ;
	_pVarArray->QueryInterface(__uuidof(ICVarArray), (VOID**)ppVal) ;

	return this->SetInterface(lIndex, _pVarArray) ;
}

HRESULT CCVarArray::AddVarBuffer(ICVarBuffer* pVal)
{
	return this->AddInterface(pVal) ;
}

HRESULT CCVarArray::AddNewVarBuffer(ICVarBuffer** ppVal)
{
	DEBUG_ASSERT(ppVal) ;
	IF_RETURN(NULL == ppVal, E_INVALIDARG) ;
	*ppVal = NULL ;

	CComPtr<ICVarBuffer> _pVarBuffer ;
	Common::Util::CreateObject(&_pVarBuffer) ;
	IF_RETURN(NULL == _pVarBuffer, E_FAIL) ;
	_pVarBuffer->QueryInterface(__uuidof(ICVarBuffer), (VOID**)ppVal) ;

	return this->AddInterface(_pVarBuffer) ;
}

HRESULT CCVarArray::InsertVarBuffer(LONG lIndex, ICVarBuffer* pVal)
{
	return this->InsertInterface(lIndex, pVal) ;
}

HRESULT CCVarArray::InsertNewVarBuffer(LONG lIndex, ICVarBuffer** ppVal)
{
	DEBUG_ASSERT(ppVal) ;
	IF_RETURN(NULL == ppVal, E_INVALIDARG) ;
	*ppVal = NULL ;

	CComPtr<ICVarBuffer> _pVarBuffer ;
	Common::Util::CreateObject(&_pVarBuffer) ;
	IF_RETURN(NULL == _pVarBuffer, E_FAIL) ;
	_pVarBuffer->QueryInterface(__uuidof(ICVarBuffer), (VOID**)ppVal) ;

	return this->InsertInterface(lIndex, _pVarBuffer) ;
}

HRESULT CCVarArray::SetVarBuffer(LONG lIndex, ICVarBuffer* pVal)
{
	return this->SetInterface(lIndex, pVal) ;
}

HRESULT CCVarArray::SetNewVarBuffer(LONG lIndex, ICVarBuffer** ppVal)
{
	DEBUG_ASSERT(ppVal) ;
	IF_RETURN(NULL == ppVal, E_INVALIDARG) ;
	*ppVal = NULL ;

	CComPtr<ICVarBuffer> _pVarBuffer ;
	Common::Util::CreateObject(&_pVarBuffer) ;
	IF_RETURN(NULL == _pVarBuffer, E_FAIL) ;
	_pVarBuffer->QueryInterface(__uuidof(ICVarBuffer), (VOID**)ppVal) ;

	return this->SetInterface(lIndex, _pVarBuffer) ;
}