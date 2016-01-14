#include "stdafx.h"
#include "CCUIElement.h"

CUIElement::CUIElement()
{
	this->m_nIndex = -1 ;
}

CUIElement::~CUIElement()
{
}

HRESULT CUIElement::SetName(BSTR bstrName)
{
	this->m_cstrElementName = bstrName ;
	return S_OK ;
}

HRESULT CUIElement::GetName(BSTR* pbstrName)
{
	DEBUG_ASSERT(pbstrName) ;
	IF_RETURN(NULL == pbstrName, E_INVALIDARG) ;
	CComBSTR bstrName(this->m_cstrElementName) ;
	return bstrName.CopyTo(pbstrName) ;
}

HRESULT CUIElement::SetData(ICVarData* pVarData)
{
	this->m_pElementData = pVarData ;
	return S_OK ;
}

HRESULT CUIElement::GetData(ICVarData** ppVarData)
{
	DEBUG_ASSERT(ppVarData) ;
	IF_RETURN(NULL == ppVarData, E_INVALIDARG) ;
	if (this->m_pElementData)
	{
		return this->m_pElementData->QueryInterface(__uuidof(ICVarData), (VOID**)ppVarData) ;
	}
	return E_FAIL ;
}

HRESULT CUIElement::SetIndex(INT nIndex)
{
	this->m_nIndex = nIndex ;
	return S_OK ;
}

HRESULT CUIElement::GetIndex(INT* pnIndex)
{
	DEBUG_ASSERT(pnIndex) ;
	IF_RETURN(NULL == pnIndex, E_INVALIDARG) ;
	*pnIndex = this->m_nIndex ;
	return S_OK ;
}

HRESULT CUIElement::GetRoot(IUIElement** ppRoot)
{
	DEBUG_ASSERT(ppRoot) ;
	IF_RETURN(NULL == ppRoot, E_INVALIDARG) ;
	*ppRoot = NULL ;

	CComPtr<IUIElement> pParentTemp = GetEntity<IUIElement>() ;
	while (pParentTemp)
	{
		CComPtr<IUIElement> pElement ;
		pParentTemp->GetParent(&pElement) ;
		IF_BREAK(NULL == pElement) ;
		pParentTemp = pElement ;
	}

	if (pParentTemp)
	{
		return pParentTemp->QueryInterface(__uuidof(IUIElement), (VOID**)ppRoot) ;
	}
	return E_FAIL ;
}

HRESULT CUIElement::SetParent(IUIElement* pParent)
{
	this->m_wpParentPtr = NULL ;
	this->m_wpParentPtr = pParent ;
	return S_OK ;
}

HRESULT CUIElement::GetParent(IUIElement** pParent)
{
	DEBUG_ASSERT(pParent) ;
	IF_RETURN(NULL == pParent, E_INVALIDARG) ;
	*pParent = NULL ;
	IF_RETURN(NULL == this->m_wpParentPtr, E_FAIL) ;

	CComPtr<IWeakAgent> pComAgent = this->m_wpParentPtr.GetAgent() ;
	if (pComAgent)
	{
		return pComAgent->QueryOrigin(__uuidof(IUIElement), (VOID**)pParent) ;
	}
	return E_FAIL ;
}

HRESULT CUIElement::GetSiblingCount(LONG* plCount)
{
	DEBUG_ASSERT(plCount) ;
	IF_RETURN(NULL == plCount, E_INVALIDARG) ;
	*plCount = 1 ;

	CComPtr<IUIElement> pParent ;
	__self->GetParent(&pParent) ;
	if (pParent)
	{
		return pParent->GetChildrenCount(plCount) ;
	}
	return S_OK ;
}

HRESULT CUIElement::GetSiblingByIndex(INT nIndex, IUIElement** ppSibling)
{
	DEBUG_ASSERT(ppSibling) ;
	IF_RETURN(NULL == ppSibling, E_INVALIDARG) ;
	*ppSibling = NULL ;

	CComPtr<IUIElement> pParent ;
	__self->GetParent(&pParent) ;
	if (pParent)
	{
		return pParent->GetChildByIndex(nIndex, ppSibling) ;
	}
	return E_FAIL ;
}

HRESULT CUIElement::GetSiblingByName(BSTR bstrName, IUIElement** ppSibling)
{
	DEBUG_ASSERT(ppSibling) ;
	IF_RETURN(NULL == ppSibling, E_INVALIDARG) ;
	*ppSibling = NULL ;

	CComPtr<IUIElement> pParent ;
	__self->GetParent(&pParent) ;
	if (pParent)
	{
		return pParent->GetChildByName(bstrName, ppSibling) ;
	}
	return E_FAIL ;
}

HRESULT CUIElement::GetNextSibling(IUIElement** ppNextSibling)
{
	DEBUG_ASSERT(ppNextSibling) ;
	IF_RETURN(NULL == ppNextSibling, E_INVALIDARG) ;
	*ppNextSibling = NULL ;

	if (this->m_wpParentPtr)
	{
		return this->m_wpParentPtr->GetChildByIndex(m_nIndex+1, ppNextSibling) ;
	}
	return E_FAIL ;
}

HRESULT CUIElement::GetLastSibling(IUIElement** pLastSibling)
{
	DEBUG_ASSERT(pLastSibling) ;
	IF_RETURN(NULL == pLastSibling, E_INVALIDARG) ;
	*pLastSibling = NULL ;

	if (this->m_wpParentPtr)
	{
		return this->m_wpParentPtr->GetChildByIndex(m_nIndex-1, pLastSibling) ;
	}
	return E_FAIL ;
}

HRESULT CUIElement::GetChildrenCount(LONG* plCount)
{
	DEBUG_ASSERT(plCount) ;
	IF_RETURN(NULL == plCount, E_INVALIDARG) ;
	*plCount = (LONG)this->m_vecChildrenPool.size() ;
	return S_OK ;
}

HRESULT CUIElement::GetChildByIndex(INT nIndex, IUIElement** ppChild)
{
	DEBUG_ASSERT(ppChild) ;
	IF_RETURN(NULL == ppChild, E_INVALIDARG) ;
	*ppChild = NULL ;
	DEBUG_ASSERT(nIndex >= 0 && nIndex < (INT)m_vecChildrenPool.size()) ;
	IF_RETURN(!(nIndex >= 0 && nIndex < (INT)m_vecChildrenPool.size()), E_INVALIDARG) ;
	if (this->m_vecChildrenPool[nIndex])
	{
		return this->m_vecChildrenPool[nIndex]
		->QueryInterface(__uuidof(IUIElement), (VOID**)ppChild) ;
	}
	return E_FAIL ;
}

HRESULT CUIElement::GetChildByName(BSTR bstrName, IUIElement** ppChild)
{
	DEBUG_ASSERT(ppChild) ;
	IF_RETURN(NULL == ppChild, E_INVALIDARG) ;
	*ppChild = NULL ;

	for (size_t i = 0; i < this->m_vecChildrenPool.size(); ++i)
	{
		IF_CONTINUE(NULL == this->m_vecChildrenPool[i]) ;
		CComBSTR _bstrName ;
		this->m_vecChildrenPool[i]->GetName(&_bstrName) ;
		if (CString(_bstrName) == CString(bstrName))
		{
			return this->m_vecChildrenPool[i]->QueryInterface(__uuidof(IUIElement), (VOID**)ppChild) ;
		}
	}
	return E_FAIL ;
}

HRESULT CUIElement::GetChildAgentByName(BSTR bstrName, IWeakAgent** ppAgent)
{
	DEBUG_ASSERT(ppAgent) ;
	IF_RETURN(NULL == ppAgent, E_INVALIDARG) ;
	*ppAgent = NULL ;

	CComPtr<IUIElement> pElement ;
	__self->GetChildByName(bstrName, &pElement) ;
	CComQIPtr<IWeakAgentSupport> pAgentSupport = pElement ;
	if (pAgentSupport && pElement)
	{
		return pAgentSupport->QueryAgent(ppAgent) ;
	}
	return E_FAIL ;
}

HRESULT CUIElement::GetChildByNameDeeply(BSTR bstrName, IUIElement** ppChild)
{
	DEBUG_ASSERT(ppChild) ;
	IF_RETURN(NULL == ppChild, E_INVALIDARG) ;
	*ppChild = NULL ;

	std::vector<CComPtr<IUIElement>> vecElem ;
	for (size_t i = 0; i < this->m_vecChildrenPool.size(); ++i)
	{
		vecElem.push_back(this->m_vecChildrenPool[i]) ;
	}

	for (size_t i = 0; i < vecElem.size(); ++i)
	{
		CComPtr<IUIElement> pElement = vecElem[i] ;
		IF_CONTINUE(NULL == pElement) ;

		CComBSTR _bstrName ;
		pElement->GetName(&_bstrName) ;
		if (CString(_bstrName) == CString(bstrName))
		{
			return pElement->QueryInterface(__uuidof(IUIElement), (VOID**)ppChild) ;
		}
		else
		{
			LONG lChildrenCount = 0 ;
			pElement->GetChildrenCount(&lChildrenCount) ;
			for (INT i = 0; i < lChildrenCount; ++i)
			{
				CComPtr<IUIElement> pElementTemp ;
				pElement->GetChildByIndex(i, &pElementTemp) ;
				IF_CONTINUE(NULL == pElementTemp) ;
				vecElem.push_back(pElementTemp) ;
			}
		}
	}
	return S_OK ;
}

HRESULT CUIElement::GetChildAgentByNameDeeply(BSTR bstrName, IWeakAgent** ppAgent)
{
	DEBUG_ASSERT(ppAgent) ;
	IF_RETURN(NULL == ppAgent, E_INVALIDARG) ;
	*ppAgent = NULL ;

	CComPtr<IUIElement> pElement ;
	__self->GetChildByNameDeeply(bstrName, &pElement) ;
	CComQIPtr<IWeakAgentSupport> pAgentSupport = pElement ;
	if (pAgentSupport && pElement)
	{
		return pAgentSupport->QueryAgent(ppAgent) ;
	}
	return E_FAIL ;
}

HRESULT CUIElement::AddChildFront(IUIElement* pChild)
{
	DEBUG_ASSERT(pChild) ;
	IF_RETURN(NULL == pChild, E_INVALIDARG) ;
	pChild->SetIndex(0) ;
	this->m_vecChildrenPool.insert(this->m_vecChildrenPool.begin(), pChild) ;
	for (size_t i = 1; i < this->m_vecChildrenPool.size(); ++i)
	{
		IF_CONTINUE(NULL == this->m_vecChildrenPool[i]) ;
		this->m_vecChildrenPool[i]->SetIndex((INT)i) ;
	}
	pChild->SetParent(GetEntity<IUIElement>()) ;
	return S_OK ;
}

HRESULT CUIElement::AddChildBack(IUIElement* pChild)
{
	DEBUG_ASSERT(pChild) ;
	IF_RETURN(NULL == pChild, E_INVALIDARG) ;
	pChild->SetIndex((INT)this->m_vecChildrenPool.size()) ;
	this->m_vecChildrenPool.push_back(pChild) ;
	pChild->SetParent(GetEntity<IUIElement>()) ;
	return S_OK ;
}

HRESULT CUIElement::InsertChild(INT nIndex, IUIElement* pChild)
{
	DEBUG_ASSERT(pChild) ;
	IF_RETURN(NULL == pChild, E_INVALIDARG) ;
	DEBUG_ASSERT(nIndex >= 0 && nIndex < (INT)m_vecChildrenPool.size()) ;
	IF_RETURN(!(nIndex >= 0 && nIndex < (INT)m_vecChildrenPool.size()), E_INVALIDARG) ;

	VEC_CHILDREN_POOL::iterator it = this->m_vecChildrenPool.begin() + nIndex ;
	this->m_vecChildrenPool.insert(it, pChild) ;
	for (size_t i = nIndex+1; i < this->m_vecChildrenPool.size(); ++i)
	{
		IF_CONTINUE(NULL == this->m_vecChildrenPool[i]) ;
		this->m_vecChildrenPool[i]->SetIndex((INT)i) ;
	}
	pChild->SetParent(GetEntity<IUIElement>()) ;
	return S_OK ;
}

HRESULT CUIElement::RemoveChild(IUIElement* pChild)
{
	DEBUG_ASSERT(pChild) ;
	IF_RETURN(NULL == pChild, E_INVALIDARG) ;

	for (size_t i = 0; i < this->m_vecChildrenPool.size(); ++i)
	{
		if (this->m_vecChildrenPool[i] == pChild)
		{
			return __self->RemoveChildByIndex((INT)i) ;
		}
	}
	return E_FAIL ;
}

HRESULT CUIElement::RemoveChildByIndex(INT nIndex)
{
	DEBUG_ASSERT(nIndex >= 0 && nIndex < (INT)m_vecChildrenPool.size()) ;
	IF_RETURN(!(nIndex >= 0 && nIndex < (INT)m_vecChildrenPool.size()), E_INVALIDARG) ;

	VEC_CHILDREN_POOL::iterator it = this->m_vecChildrenPool.begin() + nIndex ;
	this->m_vecChildrenPool.erase(it) ;
	for (size_t i = (size_t)nIndex; i < this->m_vecChildrenPool.size(); ++i)
	{
		this->m_vecChildrenPool[i]->SetIndex((INT)(i)) ;
	}
	return S_OK ;
}

HRESULT CUIElement::RemoveChildByName(BSTR bstrName)
{
	for (size_t i = 0; i < this->m_vecChildrenPool.size(); ++i)
	{
		IF_CONTINUE(NULL == this->m_vecChildrenPool[i]) ;
		CComBSTR _bstrName ;
		this->m_vecChildrenPool[i]->GetName(&_bstrName) ;
		if (CString(_bstrName) == CString(bstrName))
		{
			return __self->RemoveChildByIndex((INT)i) ;
		}
	}
	return E_FAIL ;
}

HRESULT CUIElement::SetAttribute(ICVarData* pAttrData)
{
	SET_ATTR_INTERFACE_BEGIN(pAttrData, IUIElement)
	SET_ATTR_BSTR(Name)
	SET_ATTR_END()
	return S_OK ;
}