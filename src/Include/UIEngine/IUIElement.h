#pragma once
#include "Include/Def/Require.h"
#include "Include/Common/ICStruct.h"
#include "Include/UIEngine/IUIBase.h"

[
	object ,
	uuid("0BC76408-37B0-45bf-80A6-E22BD66B602F") ,
	pointer_default(unique)
]
__interface IUIElement : IUIBase
{
	HRESULT SetName                     (BSTR bstrName) ;
	HRESULT GetName                     (BSTR* pbstrName) ;
	HRESULT SetData                     (ICVarData* pVarData) ;
	HRESULT GetData                     (ICVarData** ppVarData) ;
	HRESULT SetIndex                    (INT nIndex) ;
	HRESULT GetIndex                    (INT* pnIndex) ;
	HRESULT GetRoot                     (IUIElement** ppRoot) ;
	HRESULT SetParent                   (IUIElement* pParent) ;
	HRESULT GetParent                   (IUIElement** pParent) ;
	HRESULT GetSiblingCount             (LONG* plCount) ;
	HRESULT GetSiblingByIndex           (INT nIndex, IUIElement** ppSibling) ;
	HRESULT GetSiblingByName            (BSTR bstrName, IUIElement** ppSibling) ;
	HRESULT GetNextSibling              (IUIElement** ppNextSibling) ;
	HRESULT GetLastSibling              (IUIElement** pLastSibling) ;
	HRESULT GetChildrenCount            (LONG* plCount) ;
	HRESULT GetChildByIndex             (INT nIndex, IUIElement** ppChild) ;
	HRESULT GetChildByName              (BSTR bstrName, IUIElement** ppChild) ;
	HRESULT GetChildAgentByName         (BSTR bstrName, IWeakAgent** ppAgent) ;
	HRESULT GetChildByNameDeeply        (BSTR bstrName, IUIElement** ppChild) ;
	HRESULT GetChildAgentByNameDeeply   (BSTR bstrName, IWeakAgent** ppAgent) ;
	HRESULT AddChildFront               (IUIElement* pChild) ;
	HRESULT AddChildBack                (IUIElement* pChild) ;
	HRESULT InsertChild                 (INT nIndex, IUIElement* pChild) ;
	HRESULT RemoveChild                 (IUIElement* pChild) ;
	HRESULT RemoveChildByIndex          (INT nIndex) ;
	HRESULT RemoveChildByName           (BSTR bstrName) ;
} ;