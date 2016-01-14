#include "stdafx.h"
#include "CCUIBase.h"

HRESULT CCUIBase::QueryAgent(IWeakAgent** ppOut)
{
	DEBUG_ASSERT(ppOut) ;
	IF_RETURN(NULL == ppOut, E_INVALIDARG) ;
	CComPtr<IWeakAgent> pWeakAgent = this->m_pAgentHost ;
	if (pWeakAgent)
	{
		return pWeakAgent->QueryInterface(__uuidof(IWeakAgent), (VOID**)ppOut) ;
	}
	return E_FAIL ;
}

HRESULT CCUIBase::SetEntity(IUnknown* pEntity)
{
	this->m_pEntity = pEntity ;
	this->m_pAgentHost.SetOrigin(pEntity) ;
	return S_OK ;
}

HRESULT CCUIBase::GetEntity(IUnknown** ppEntity)
{
	IF_RETURN(NULL == ppEntity, E_INVALIDARG) ;
	*ppEntity = NULL ;
	if (this->m_pEntity)
	{
		return this->m_pEntity->QueryInterface(__uuidof(IUnknown), (VOID**)ppEntity) ;
	}
	return E_FAIL ;
}