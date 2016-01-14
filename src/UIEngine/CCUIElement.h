#pragma once
#include "Include/UIEngine/IUIElement.h"
#include "Include/UIEngine/IUIAttribute.h"
#include "Include/UIEngine/TUICustomBase.h"
#include <vector>

[
	default(IUIElement) ,
	threading(free) ,
	uuid("AF8CD66A-3C32-4d46-B395-5AFA2D1DAFA3") ,
	coclass
]
class ATL_NO_VTABLE CUIElement 
	: public TUICustomBase<IUIElement, IUIBase>
	, public IDispatchImpl<IUIAttribute>
{
public:
	DECLARE_PROTECT_FINAL_CONSTRUCT() ;
	CUIElement() ;
	virtual ~CUIElement() ;

public:
	HRESULT _call SetName                   (BSTR bstrName) ;
	HRESULT _call GetName                   (BSTR* pbstrName) ;
	HRESULT _call SetData                   (ICVarData* pVarData) ;
	HRESULT _call GetData                   (ICVarData** ppVarData) ;
	HRESULT _call SetIndex                  (INT nIndex) ;
	HRESULT _call GetIndex                  (INT* pnIndex) ;
	HRESULT _call GetRoot                   (IUIElement** ppRoot) ;
	HRESULT _call SetParent                 (IUIElement* pParent) ;
	HRESULT _call GetParent                 (IUIElement** pParent) ;
	HRESULT _call GetSiblingCount           (LONG* plCount) ;
	HRESULT _call GetSiblingByIndex         (INT nIndex, IUIElement** ppSibling) ;
	HRESULT _call GetSiblingByName          (BSTR bstrName, IUIElement** ppSibling) ;
	HRESULT _call GetNextSibling            (IUIElement** ppNextSibling) ;
	HRESULT _call GetLastSibling            (IUIElement** pLastSibling) ;
	HRESULT _call GetChildrenCount          (LONG* plCount) ;
	HRESULT _call GetChildByIndex           (INT nIndex, IUIElement** ppChild) ;
	HRESULT _call GetChildByName            (BSTR bstrName, IUIElement** ppChild) ;
	HRESULT _call GetChildAgentByName       (BSTR bstrName, IWeakAgent** ppAgent) ;
	HRESULT _call GetChildByNameDeeply      (BSTR bstrName, IUIElement** ppChild) ;
	HRESULT _call GetChildAgentByNameDeeply (BSTR bstrName, IWeakAgent** ppAgent) ;
	HRESULT _call AddChildFront             (IUIElement* pChild) ;
	HRESULT _call AddChildBack              (IUIElement* pChild) ;
	HRESULT _call InsertChild               (INT nIndex, IUIElement* pChild) ;
	HRESULT _call RemoveChild               (IUIElement* pChild) ;
	HRESULT _call RemoveChildByIndex        (INT nIndex) ;
	HRESULT _call RemoveChildByName         (BSTR bstrName) ;

	// interface IUIAttribute
	HRESULT _call SetAttribute              (ICVarData* pAttrData) ;

private:
	INT                                     m_nIndex ;
	CString                                 m_cstrElementName ;
	CComPtr<ICVarData>						m_pElementData ;
	CWeakPtr<IUIElement>					m_wpParentPtr ;

	typedef std::vector<CComPtr<IUIElement>>VEC_CHILDREN_POOL ;
	VEC_CHILDREN_POOL                       m_vecChildrenPool ;
} ; 