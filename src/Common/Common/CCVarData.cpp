
#include "stdafx.h"
#include "CCVarData.h"

CCVarData::CCVarData()
{

}

CCVarData::~CCVarData()
{

}

HRESULT CCVarData::GetBool(BSTR bsKey, BOOL* pVal)
{
	DEBUG_ASSERT(pVal) ;
	IF_RETURN(NULL == pVal, E_INVALIDARG) ;

	HASH_POOL::iterator _it = this->m_hashPool.find(bsKey) ;
	if (this->m_hashPool.end() != _it && _it->second)
	{
		return _it->second->GetBool(pVal) ;
	}
	return E_FAIL ;
}

HRESULT CCVarData::GetChar(BSTR bsKey, CHAR* pVal)
{
	DEBUG_ASSERT(pVal) ;
	IF_RETURN(NULL == pVal, E_INVALIDARG) ;

	HASH_POOL::iterator _it = this->m_hashPool.find(bsKey) ;
	if (this->m_hashPool.end() != _it && _it->second)
	{
		return _it->second->GetChar(pVal) ;
	}
	return E_FAIL ;
}

HRESULT CCVarData::GetWChar(BSTR bsKey, WCHAR* pVal)
{
	DEBUG_ASSERT(pVal) ;
	IF_RETURN(NULL == pVal, E_INVALIDARG) ;

	HASH_POOL::iterator _it = this->m_hashPool.find(bsKey) ;
	if (this->m_hashPool.end() != _it && _it->second)
	{
		return _it->second->GetWChar(pVal) ;
	}
	return E_FAIL ;
}

HRESULT CCVarData::GetWord(BSTR bsKey, WORD* pVal)
{
	DEBUG_ASSERT(pVal) ;
	IF_RETURN(NULL == pVal, E_INVALIDARG) ;

	HASH_POOL::iterator _it = this->m_hashPool.find(bsKey) ;
	if (this->m_hashPool.end() != _it && _it->second)
	{
		return _it->second->GetWord(pVal) ;
	}
	return E_FAIL ;
}

HRESULT CCVarData::GetDWord(BSTR bsKey, DWORD* pVal)
{
	DEBUG_ASSERT(pVal) ;
	IF_RETURN(NULL == pVal, E_INVALIDARG) ;

	HASH_POOL::iterator _it = this->m_hashPool.find(bsKey) ;
	if (this->m_hashPool.end() != _it && _it->second)
	{
		return _it->second->GetDWord(pVal) ;
	}
	return E_FAIL ;
}

HRESULT CCVarData::GetShort(BSTR bsKey, SHORT* pVal)
{
	DEBUG_ASSERT(pVal) ;
	IF_RETURN(NULL == pVal, E_INVALIDARG) ;

	HASH_POOL::iterator _it = this->m_hashPool.find(bsKey) ;
	if (this->m_hashPool.end() != _it && _it->second)
	{
		return _it->second->GetShort(pVal) ;
	}
	return E_FAIL ;
}

HRESULT CCVarData::GetUInt(BSTR bsKey, UINT* pVal)
{
	DEBUG_ASSERT(pVal) ;
	IF_RETURN(NULL == pVal, E_INVALIDARG) ;

	HASH_POOL::iterator _it = this->m_hashPool.find(bsKey) ;
	if (this->m_hashPool.end() != _it && _it->second)
	{
		return _it->second->GetUInt(pVal) ;
	}
	return E_FAIL ;
}

HRESULT CCVarData::GetUInt32(BSTR bsKey, UINT32* pVal)
{
	DEBUG_ASSERT(pVal) ;
	IF_RETURN(NULL == pVal, E_INVALIDARG) ;

	HASH_POOL::iterator _it = this->m_hashPool.find(bsKey) ;
	if (this->m_hashPool.end() != _it && _it->second)
	{
		return _it->second->GetUInt32(pVal) ;
	}
	return E_FAIL ;
}

HRESULT CCVarData::GetUInt64(BSTR bsKey, UINT64* pVal)
{
	DEBUG_ASSERT(pVal) ;
	IF_RETURN(NULL == pVal, E_INVALIDARG) ;

	HASH_POOL::iterator _it = this->m_hashPool.find(bsKey) ;
	if (this->m_hashPool.end() != _it && _it->second)
	{
		return _it->second->GetUInt64(pVal) ;
	}
	return E_FAIL ;
}

HRESULT CCVarData::GetInt(BSTR bsKey, INT* pVal)
{
	DEBUG_ASSERT(pVal) ;
	IF_RETURN(NULL == pVal, E_INVALIDARG) ;

	HASH_POOL::iterator _it = this->m_hashPool.find(bsKey) ;
	if (this->m_hashPool.end() != _it && _it->second)
	{
		return _it->second->GetInt(pVal) ;
	}
	return E_FAIL ;
}

HRESULT CCVarData::GetInt32(BSTR bsKey, INT32* pVal)
{
	DEBUG_ASSERT(pVal) ;
	IF_RETURN(NULL == pVal, E_INVALIDARG) ;

	HASH_POOL::iterator _it = this->m_hashPool.find(bsKey) ;
	if (this->m_hashPool.end() != _it && _it->second)
	{
		return _it->second->GetInt32(pVal) ;
	}
	return E_FAIL ;
}

HRESULT CCVarData::GetInt64(BSTR bsKey, INT64* pVal)
{
	DEBUG_ASSERT(pVal) ;
	IF_RETURN(NULL == pVal, E_INVALIDARG) ;

	HASH_POOL::iterator _it = this->m_hashPool.find(bsKey) ;
	if (this->m_hashPool.end() != _it && _it->second)
	{
		return _it->second->GetInt64(pVal) ;
	}
	return E_FAIL ;
}

HRESULT CCVarData::GetFloat(BSTR bsKey, FLOAT* pVal)
{
	DEBUG_ASSERT(pVal) ;
	IF_RETURN(NULL == pVal, E_INVALIDARG) ;

	HASH_POOL::iterator _it = this->m_hashPool.find(bsKey) ;
	if (this->m_hashPool.end() != _it && _it->second)
	{
		return _it->second->GetFloat(pVal) ;
	}
	return E_FAIL ;
}

HRESULT CCVarData::GetDouble(BSTR bsKey, DOUBLE* pVal)
{
	DEBUG_ASSERT(pVal) ;
	IF_RETURN(NULL == pVal, E_INVALIDARG) ;

	HASH_POOL::iterator _it = this->m_hashPool.find(bsKey) ;
	if (this->m_hashPool.end() != _it && _it->second)
	{
		return _it->second->GetDouble(pVal) ;
	}
	return E_FAIL ;
}

HRESULT CCVarData::GetString(BSTR bsKey, BSTR* pVal)
{
	DEBUG_ASSERT(pVal) ;
	IF_RETURN(NULL == pVal, E_INVALIDARG) ;

	HASH_POOL::iterator _it = this->m_hashPool.find(bsKey) ;
	if (this->m_hashPool.end() != _it && _it->second)
	{
		return _it->second->GetString(pVal) ;
	}
	return E_FAIL ;
}

HRESULT CCVarData::GetGuid(BSTR bsKey, GUID* pVal)
{
	DEBUG_ASSERT(pVal) ;
	IF_RETURN(NULL == pVal, E_INVALIDARG) ;

	HASH_POOL::iterator _it = this->m_hashPool.find(bsKey) ;
	if (this->m_hashPool.end() != _it && _it->second)
	{
		return _it->second->GetGuid(pVal) ;
	}
	return E_FAIL ;
}

HRESULT CCVarData::GetRect(BSTR bsKey, RECT* pVal)
{
	DEBUG_ASSERT(pVal) ;
	IF_RETURN(NULL == pVal, E_INVALIDARG) ;

	HASH_POOL::iterator _it = this->m_hashPool.find(bsKey) ;
	if (this->m_hashPool.end() != _it && _it->second)
	{
		return _it->second->GetRect(pVal) ;
	}
	return E_FAIL ;
}

HRESULT CCVarData::GetPoint(BSTR bsKey, POINT* pVal)
{
	DEBUG_ASSERT(pVal) ;
	IF_RETURN(NULL == pVal, E_INVALIDARG) ;

	HASH_POOL::iterator _it = this->m_hashPool.find(bsKey) ;
	if (this->m_hashPool.end() != _it && _it->second)
	{
		return _it->second->GetPoint(pVal) ;
	}
	return E_FAIL ;
}

HRESULT CCVarData::GetSize(BSTR bsKey, SIZE* pVal)
{
	DEBUG_ASSERT(pVal) ;
	IF_RETURN(NULL == pVal, E_INVALIDARG) ;

	HASH_POOL::iterator _it = this->m_hashPool.find(bsKey) ;
	if (this->m_hashPool.end() != _it && _it->second)
	{
		return _it->second->GetSize(pVal) ;
	}
	return E_FAIL ;
}

HRESULT CCVarData::GetInterface(BSTR bsKey, REFIID iid, VOID** ppVal)
{
	DEBUG_ASSERT(ppVal) ;
	IF_RETURN(NULL == ppVal, E_INVALIDARG) ;

	HASH_POOL::iterator _it = this->m_hashPool.find(bsKey) ;
	if (this->m_hashPool.end() != _it && _it->second)
	{
		return _it->second->GetInterface(iid, ppVal) ;
	}
	return E_FAIL ;
}

HRESULT CCVarData::GetVarData(BSTR bsKey, ICVarData** ppVal)
{
	DEBUG_ASSERT(ppVal) ;
	IF_RETURN(NULL == ppVal, E_INVALIDARG) ;

	return this->GetInterface(bsKey, __uuidof(ICVarData), (VOID**)ppVal) ;
}

HRESULT CCVarData::GetVarArray(BSTR bskey, ICVarArray** ppVal)
{
	DEBUG_ASSERT(ppVal) ;
	IF_RETURN(NULL == ppVal, E_INVALIDARG) ;

	return this->GetInterface(bskey, __uuidof(ICVarArray), (VOID**)ppVal) ;
}

HRESULT CCVarData::GetVarBuffer(BSTR bskey, ICVarBuffer** ppVal)
{
	DEBUG_ASSERT(ppVal) ;
	IF_RETURN(NULL == ppVal, E_INVALIDARG) ;

	return this->GetInterface(bskey, __uuidof(ICVarBuffer), (VOID**)ppVal) ;
}

HRESULT CCVarData::Clear()
{
	this->m_hashPool.clear() ;
	return E_FAIL ;
}

HRESULT CCVarData::EraseItem(BSTR bsKey)
{
	HASH_POOL::iterator _it = this->m_hashPool.find(bsKey) ;
	if (this->m_hashPool.end() != _it)
	{
		this->m_hashPool.erase(_it) ;
	}
	return S_OK ;
}

HRESULT CCVarData::SetBool(BSTR bsKey, BOOL val)
{
	CComPtr<ICVariant> _pVariant ;
	Common::Util::CreateObject(&_pVariant) ;
	DEBUG_ASSERT(_pVariant) ;
	IF_RETURN(NULL == _pVariant, E_FAIL) ;

	_pVariant->SetBool(val) ;
	this->m_hashPool[bsKey] = _pVariant ;
	return S_OK ;
}

HRESULT CCVarData::SetChar(BSTR bsKey, CHAR val)
{
	CComPtr<ICVariant> _pVariant ;
	Common::Util::CreateObject(&_pVariant) ;
	DEBUG_ASSERT(_pVariant) ;
	IF_RETURN(NULL == _pVariant, E_FAIL) ;

	_pVariant->SetChar(val) ;
	this->m_hashPool[bsKey] = _pVariant ;
	return S_OK ;
}

HRESULT CCVarData::SetWChar(BSTR bsKey, WCHAR val)
{
	CComPtr<ICVariant> _pVariant ;
	Common::Util::CreateObject(&_pVariant) ;
	DEBUG_ASSERT(_pVariant) ;
	IF_RETURN(NULL == _pVariant, E_FAIL) ;

	_pVariant->SetWChar(val) ;
	this->m_hashPool[bsKey] = _pVariant ;
	return S_OK ;
}

HRESULT CCVarData::SetWord(BSTR bsKey, WORD val)
{
	CComPtr<ICVariant> _pVariant ;
	Common::Util::CreateObject(&_pVariant) ;
	DEBUG_ASSERT(_pVariant) ;
	IF_RETURN(NULL == _pVariant, E_FAIL) ;

	_pVariant->SetWord(val) ;
	this->m_hashPool[bsKey] = _pVariant ;
	return S_OK ;
}

HRESULT CCVarData::SetDWord(BSTR bsKey, DWORD val)
{
	CComPtr<ICVariant> _pVariant ;
	Common::Util::CreateObject(&_pVariant) ;
	DEBUG_ASSERT(_pVariant) ;
	IF_RETURN(NULL == _pVariant, E_FAIL) ;

	_pVariant->SetDWord(val) ;
	this->m_hashPool[bsKey] = _pVariant ;
	return S_OK ;
}

HRESULT CCVarData::SetShort(BSTR bsKey, SHORT val)
{
	CComPtr<ICVariant> _pVariant ;
	Common::Util::CreateObject(&_pVariant) ;
	DEBUG_ASSERT(_pVariant) ;
	IF_RETURN(NULL == _pVariant, E_FAIL) ;

	_pVariant->SetShort(val) ;
	this->m_hashPool[bsKey] = _pVariant ;
	return S_OK ;
}

HRESULT CCVarData::SetUInt(BSTR bsKey, UINT val)
{
	CComPtr<ICVariant> _pVariant ;
	Common::Util::CreateObject(&_pVariant) ;
	DEBUG_ASSERT(_pVariant) ;
	IF_RETURN(NULL == _pVariant, E_FAIL) ;

	_pVariant->SetUInt(val) ;
	this->m_hashPool[bsKey] = _pVariant ;
	return S_OK ;
}

HRESULT CCVarData::SetUInt32(BSTR bsKey, UINT32 val)
{
	CComPtr<ICVariant> _pVariant ;
	Common::Util::CreateObject(&_pVariant) ;
	DEBUG_ASSERT(_pVariant) ;
	IF_RETURN(NULL == _pVariant, E_FAIL) ;

	_pVariant->SetUInt32(val) ;
	this->m_hashPool[bsKey] = _pVariant ;
	return S_OK ;
}

HRESULT CCVarData::SetUInt64(BSTR bsKey, UINT64 val)
{
	CComPtr<ICVariant> _pVariant ;
	Common::Util::CreateObject(&_pVariant) ;
	DEBUG_ASSERT(_pVariant) ;
	IF_RETURN(NULL == _pVariant, E_FAIL) ;

	_pVariant->SetUInt64(val) ;
	this->m_hashPool[bsKey] = _pVariant ;
	return S_OK ;
}

HRESULT CCVarData::SetInt(BSTR bsKey, INT val)
{
	CComPtr<ICVariant> _pVariant ;
	Common::Util::CreateObject(&_pVariant) ;
	DEBUG_ASSERT(_pVariant) ;
	IF_RETURN(NULL == _pVariant, E_FAIL) ;

	_pVariant->SetInt(val) ;
	this->m_hashPool[bsKey] = _pVariant ;
	return S_OK ;
}

HRESULT CCVarData::SetInt32(BSTR bsKey, INT32 val)
{
	CComPtr<ICVariant> _pVariant ;
	Common::Util::CreateObject(&_pVariant) ;
	DEBUG_ASSERT(_pVariant) ;
	IF_RETURN(NULL == _pVariant, E_FAIL) ;

	_pVariant->SetInt32(val) ;
	this->m_hashPool[bsKey] = _pVariant ;
	return S_OK ;
}

HRESULT CCVarData::SetInt64(BSTR bsKey, INT64 val)
{
	CComPtr<ICVariant> _pVariant ;
	Common::Util::CreateObject(&_pVariant) ;
	DEBUG_ASSERT(_pVariant) ;
	IF_RETURN(NULL == _pVariant, E_FAIL) ;

	_pVariant->SetInt64(val) ;
	this->m_hashPool[bsKey] = _pVariant ;
	return S_OK ;
}

HRESULT CCVarData::SetFloat(BSTR bsKey, FLOAT val)
{
	CComPtr<ICVariant> _pVariant ;
	Common::Util::CreateObject(&_pVariant) ;
	DEBUG_ASSERT(_pVariant) ;
	IF_RETURN(NULL == _pVariant, E_FAIL) ;

	_pVariant->SetFloat(val) ;
	this->m_hashPool[bsKey] = _pVariant ;
	return S_OK ;
}

HRESULT CCVarData::SetDouble(BSTR bsKey, DOUBLE val)
{
	CComPtr<ICVariant> _pVariant ;
	Common::Util::CreateObject(&_pVariant) ;
	DEBUG_ASSERT(_pVariant) ;
	IF_RETURN(NULL == _pVariant, E_FAIL) ;

	_pVariant->SetDouble(val) ;
	this->m_hashPool[bsKey] = _pVariant ;
	return S_OK ;
}

HRESULT CCVarData::SetString(BSTR bsKey, BSTR val)
{
	CComPtr<ICVariant> _pVariant ;
	Common::Util::CreateObject(&_pVariant) ;
	DEBUG_ASSERT(_pVariant) ;
	IF_RETURN(NULL == _pVariant, E_FAIL) ;

	_pVariant->SetString(val) ;
	this->m_hashPool[bsKey] = _pVariant ;
	return S_OK ;
}

HRESULT CCVarData::SetGuid(BSTR bsKey, GUID val)
{
	CComPtr<ICVariant> _pVariant ;
	Common::Util::CreateObject(&_pVariant) ;
	DEBUG_ASSERT(_pVariant) ;
	IF_RETURN(NULL == _pVariant, E_FAIL) ;

	_pVariant->SetGuid(val) ;
	this->m_hashPool[bsKey] = _pVariant ;
	return S_OK ;
}

HRESULT CCVarData::SetRect(BSTR bsKey, RECT val)
{
	CComPtr<ICVariant> _pVariant ;
	Common::Util::CreateObject(&_pVariant) ;
	DEBUG_ASSERT(_pVariant) ;
	IF_RETURN(NULL == _pVariant, E_FAIL) ;

	_pVariant->SetRect(val) ;
	this->m_hashPool[bsKey] = _pVariant ;
	return S_OK ;
}

HRESULT CCVarData::SetPoint(BSTR bsKey, POINT val)
{
	CComPtr<ICVariant> _pVariant ;
	Common::Util::CreateObject(&_pVariant) ;
	DEBUG_ASSERT(_pVariant) ;
	IF_RETURN(NULL == _pVariant, E_FAIL) ;

	_pVariant->SetPoint(val) ;
	this->m_hashPool[bsKey] = _pVariant ;
	return S_OK ;
}

HRESULT CCVarData::SetSize(BSTR bsKey, SIZE val)
{
	CComPtr<ICVariant> _pVariant ;
	Common::Util::CreateObject(&_pVariant) ;
	DEBUG_ASSERT(_pVariant) ;
	IF_RETURN(NULL == _pVariant, E_FAIL) ;

	_pVariant->SetSize(val) ;
	this->m_hashPool[bsKey] = _pVariant ;
	return S_OK ;
}

HRESULT CCVarData::SetInterface(BSTR bsKey, IUnknown* val)
{
	CComPtr<ICVariant> _pVariant ;
	Common::Util::CreateObject(&_pVariant) ;
	DEBUG_ASSERT(_pVariant) ;
	IF_RETURN(NULL == _pVariant, E_FAIL) ;

	_pVariant->SetInterface(val) ;
	this->m_hashPool[bsKey] = _pVariant ;
	return S_OK ;
}

HRESULT CCVarData::SetVarData(BSTR bskey, ICVarData* pVal)
{
	return this->SetInterface(bskey, pVal) ;
}

HRESULT CCVarData::SetVarArray(BSTR bskey, ICVarArray* pVal)
{
	return this->SetInterface(bskey, pVal) ;
}

HRESULT CCVarData::SetVarBuffer(BSTR bskey, ICVarBuffer* pVal)
{
	return this->SetInterface(bskey, pVal) ;
}

HRESULT CCVarData::SetNewVarData(BSTR bskey, ICVarData** ppVal)
{
	DEBUG_ASSERT(ppVal) ;
	IF_RETURN(NULL == ppVal, E_INVALIDARG) ;
	*ppVal = NULL ;

	CComPtr<ICVarData> _pVarData ;
	Common::Util::CreateObject(&_pVarData) ;
	IF_RETURN(NULL == _pVarData, E_FAIL) ;
	_pVarData->QueryInterface(__uuidof(ICVarData), (VOID**)ppVal) ;

	return this->SetInterface(bskey, _pVarData) ;
}

HRESULT CCVarData::SetNewVarArray(BSTR bskey, ICVarArray** ppVal)
{
	DEBUG_ASSERT(ppVal) ;
	IF_RETURN(NULL == ppVal, E_INVALIDARG) ;
	*ppVal = NULL ;

	CComPtr<ICVarArray> _pVarArray ;
	Common::Util::CreateObject(&_pVarArray) ;
	IF_RETURN(NULL == _pVarArray, E_FAIL) ;
	_pVarArray->QueryInterface(__uuidof(ICVarArray), (VOID**)ppVal) ;

	return this->SetInterface(bskey, _pVarArray) ;
}

HRESULT CCVarData::SetNewVarBuffer(BSTR bskey, ICVarBuffer** ppVal)
{
	DEBUG_ASSERT(ppVal) ;
	IF_RETURN(NULL == ppVal, E_INVALIDARG) ;
	*ppVal = NULL ;

	CComPtr<ICVarBuffer> _pVarBuffer ;
	Common::Util::CreateObject(&_pVarBuffer) ;
	IF_RETURN(NULL == _pVarBuffer, E_FAIL) ;
	
	return this->SetInterface(bskey, _pVarBuffer) ;
}