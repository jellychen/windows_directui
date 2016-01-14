#pragma once
#include "Include/UIEngine/IUIElement.h"
#include "Include/UIEngine/IUIAttribute.h"
#include "Include/UIEngine/TUICustomBase.h"

template<typename IActual, typename IBase>
class TUICustomElement
	: public TUICustomBase<IActual, IBase>
	, public IDispatchImpl<IUIAttribute>
{
public:
	HRESULT _call SetName(BSTR bstrName)
	{
		return this->m_pRawObject->SetName(bstrName) ;
	}

	HRESULT _call GetName(BSTR* pbstrName)
	{
		return this->m_pRawObject->GetName(pbstrName) ;
	}

	HRESULT _call SetData(ICVarData* pVarData)
	{
		return this->m_pRawObject->SetData(pVarData) ;
	}

	HRESULT _call GetData(ICVarData** ppVarData)
	{
		return this->m_pRawObject->GetData(ppVarData) ;
	}

	HRESULT _call SetIndex(INT nIndex)
	{
		return this->m_pRawObject->SetIndex(nIndex) ;
	}

	HRESULT _call GetIndex(INT* pnIndex)
	{
		return this->m_pRawObject->GetIndex(pnIndex) ;
	}

	HRESULT _call GetRoot(IUIElement** ppRoot)
	{
		return this->m_pRawObject->GetRoot(ppRoot) ;
	}

	HRESULT _call SetParent(IUIElement* pParent)
	{
		return this->m_pRawObject->SetParent(pParent) ;
	}

	HRESULT _call GetParent(IUIElement** pParent)
	{
		return this->m_pRawObject->GetParent(pParent) ;
	}

	HRESULT _call GetSiblingCount(LONG* plCount)
	{
		return this->m_pRawObject->GetSiblingCount(plCount) ;
	}

	HRESULT _call GetSiblingByIndex(INT nIndex, IUIElement** ppSibling)
	{
		return this->m_pRawObject->GetSiblingByIndex(nIndex, ppSibling) ;
	}

	HRESULT _call GetSiblingByName(BSTR bstrName, IUIElement** ppSibling)
	{
		return this->m_pRawObject->GetSiblingByName(bstrName, ppSibling) ;
	}

	HRESULT _call GetNextSibling(IUIElement** ppNextSibling)
	{
		return this->m_pRawObject->GetNextSibling(ppNextSibling) ;
	}

	HRESULT _call GetLastSibling(IUIElement** ppLastSibling)
	{
		return this->m_pRawObject->GetLastSibling(ppLastSibling) ;
	}

	HRESULT _call GetChildrenCount(LONG* plCount)
	{
		return this->m_pRawObject->GetChildrenCount(plCount) ;
	}

	HRESULT _call GetChildByIndex(INT nIndex, IUIElement** ppChild)
	{
		return this->m_pRawObject->GetChildByIndex(nIndex, ppChild) ;
	}

	HRESULT _call GetChildByName(BSTR bstrName, IUIElement** ppChild)
	{
		return this->m_pRawObject->GetChildByName(bstrName, ppChild) ;
	}

	HRESULT _call GetChildAgentByName(BSTR bstrName, IWeakAgent** ppAgent)
	{
		return this->m_pRawObject->GetChildAgentByName(bstrName, ppAgent) ;
	}

	HRESULT _call GetChildByNameDeeply(BSTR bstrName, IUIElement** ppChild)
	{
		return this->m_pRawObject->GetChildByNameDeeply(bstrName, ppChild) ;
	}

	HRESULT _call GetChildAgentByNameDeeply(BSTR bstrName, IWeakAgent** ppAgent)
	{
		return this->m_pRawObject->GetChildAgentByNameDeeply(bstrName, ppAgent) ;
	}

	HRESULT _call AddChildFront(IUIElement* pChild)
	{
		return this->m_pRawObject->AddChildFront(pChild) ;
	}

	HRESULT _call AddChildBack(IUIElement* pChild)
	{
		return this->m_pRawObject->AddChildBack(pChild) ;
	}

	HRESULT _call InsertChild(INT nIndex, IUIElement* pChild)
	{
		return this->m_pRawObject->InsertChild(nIndex, pChild) ;
	}

	HRESULT _call RemoveChild(IUIElement* pChild)
	{
		return this->m_pRawObject->RemoveChild(pChild) ;
	}

	HRESULT _call RemoveChildByIndex(INT nIndex)
	{
		return this->m_pRawObject->RemoveChildByIndex(nIndex) ;
	}

	HRESULT _call RemoveChildByName(BSTR bstrName)
	{
		return this->m_pRawObject->RemoveChildByName(bstrName) ;
	}

	HRESULT _call SetAttribute(ICVarData* pAttrData)
	{
		return GetInterfaceEntity<IUIAttribute>(m_pRawObject)->SetAttribute(pAttrData) ;
	}
} ;