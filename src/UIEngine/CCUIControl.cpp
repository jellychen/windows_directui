#include "stdafx.h"
#include "CCUIControl.h"

CCUIControl::CCUIControl()
{
	this->m_bAutoCapture = TRUE ;
}

CCUIControl::~CCUIControl()
{
}

HRESULT CCUIControl::FinalConstruct()
{
	return S_OK ;
}

HRESULT CCUIControl::SetFocus(BOOL bFocus)
{
	CComPtr<IUIControl> pControl = GetEntity<IUIControl>() ;

	if (bFocus)
	{
		return __self->SetControlFoucs(GetEntity<IUIControl>()) ;
	}
	else
	{
		CComPtr<IUIControl> pOldFocus ;
		__self->GetControlFoucs(&pOldFocus) ;
		if (pControl == pOldFocus)
		{
			return __self->SetControlFoucs(NULL) ;
		}
	}
	return E_FAIL ;
}

HRESULT CCUIControl::GetFocus(BOOL* pbFocus)
{
	DEBUG_ASSERT(pbFocus) ;
	IF_RETURN(NULL == pbFocus, E_INVALIDARG) ;

	CComPtr<IUIControl> pControl ;
	__self->GetControlFoucs(&pControl) ;
	if (pControl == GetEntity<IUIControl>())
	{
		*pbFocus = TRUE ;
	}
	else
	{
		*pbFocus = FALSE ;
	}
	return S_OK ;
}

HRESULT CCUIControl::SetAutoCapture(BOOL bAutoCapture)
{
	this->m_bAutoCapture = bAutoCapture ;
	return S_OK ;
}
HRESULT CCUIControl::GetAutoCapture(BOOL* pbAutoCapture)
{
	DEBUG_ASSERT(pbAutoCapture) ;
	IF_RETURN(NULL == pbAutoCapture, E_INVALIDARG) ;

	*pbAutoCapture = this->m_bAutoCapture ;
	return S_OK ; 
}

HRESULT CCUIControl::SetControlFoucs(IUIControl* pControl)
{
	CComPtr<IUIElement> pElementRoot ;
	__self->GetRoot(&pElementRoot) ;
	IF_RETURN(GetEntity<IUIElement>() == pElementRoot, E_FAIL) ;

	CComQIPtr<IUIControl> pContrlRoot = pElementRoot ;
	if (pContrlRoot)
	{
		return pContrlRoot->SetControlFoucs(pControl) ;
	}
	return E_FAIL ;
}

HRESULT CCUIControl::GetControlFoucs(IUIControl** ppControl)
{
	DEBUG_ASSERT(ppControl) ;
	IF_RETURN(NULL == ppControl, E_INVALIDARG) ;
	*ppControl = NULL ;

	CComPtr<IUIElement> pElementRoot ;
	__self->GetRoot(&pElementRoot) ;
	IF_RETURN(GetEntity<IUIElement>() == pElementRoot, E_FAIL) ;

	CComQIPtr<IUIControl> pContrlRoot = pElementRoot ;
	if (pContrlRoot)
	{
		return pContrlRoot->GetControlFoucs(ppControl) ;
	}
	return E_FAIL ;
}

HRESULT CCUIControl::ControlFocusChange(BOOL bFoucs)
{
	return S_OK ;
}

HRESULT CCUIControl::SetToolTips(BSTR bstrToolTips)
{
	this->m_cstrTooltips = bstrToolTips ;
	return S_OK ;
}

HRESULT CCUIControl::GetToolTips(BSTR* pbstrToolTips)
{
	DEBUG_ASSERT(pbstrToolTips) ;
	IF_RETURN(NULL == pbstrToolTips, E_INVALIDARG) ;

	CComBSTR bstrToolTips(this->m_cstrTooltips) ;
	return bstrToolTips.CopyTo(pbstrToolTips) ;
}

//HRESULT CCUIControl::CalcSize(SIZE szOld, SIZE* pszCalcOut)
//{
//	//DEBUG_ASSERT_MSG(FALSE, _T("not support auto size!!")) ;
//	return E_FAIL ;
//}

HRESULT CCUIControl::OnMessage(IUIFrame* pTarget, tMsgArg* pArg)
{
	__super::OnMessage(pTarget, pArg) ;

	DEBUG_ASSERT(pArg) ;
	IF_RETURN(NULL == pArg, E_INVALIDARG) ;
	if (this->m_cstrTooltips.GetLength() > 0)
	{
		CWeakPtr<IUIExtensionCenter> _pExtensionCenter ;
		Common::Util::GetService(&_pExtensionCenter) ;
		DEBUG_ASSERT(_pExtensionCenter) ;

		if (_pExtensionCenter && MESSAGE::UI_MOUSEENTER == pArg->dwMsgId)
		{
			_pExtensionCenter->CallExtension(
				__uuidof(IUIExtensionToolTips), GetEntity<IUIFrame>(), NULL) ;
		}
		else if (_pExtensionCenter && MESSAGE::UI_MOUSELEAVE == pArg->dwMsgId)
		{
			_pExtensionCenter->CallExtension(
				__uuidof(IUIExtensionToolTipsDismiss), GetEntity<IUIFrame>(), NULL) ;
		}
	}

	if (MESSAGE::UI_MOUSEENTER == pArg->dwMsgId)
	{
		if (this->m_cstrTooltips.GetLength() > 0)
		{
			CWeakPtr<IUIExtensionCenter> _pExtensionCenter ;
			Common::Util::GetService(&_pExtensionCenter) ;
			DEBUG_ASSERT(_pExtensionCenter) ;
			if (_pExtensionCenter)
			{
				_pExtensionCenter->CallExtension(
					__uuidof(IUIExtensionToolTips), GetEntity<IUIFrame>(), NULL) ;
			}
		}
	}
	else if (MESSAGE::UI_MOUSELEAVE == pArg->dwMsgId)
	{
		if (this->m_cstrTooltips.GetLength() > 0)
		{
			CWeakPtr<IUIExtensionCenter> _pExtensionCenter ;
			Common::Util::GetService(&_pExtensionCenter) ;
			DEBUG_ASSERT(_pExtensionCenter) ;
			if (_pExtensionCenter)
			{
				_pExtensionCenter->CallExtension(
					__uuidof(IUIExtensionToolTipsDismiss), GetEntity<IUIFrame>(), NULL) ;
			}
		}
	}
	else if (MESSAGE::UI_LBTNDOWN == pArg->dwMsgId && this->m_bAutoCapture)
	{
		__self->SetCapture(TRUE) ;
	}
	else if (MESSAGE::UI_LBTNUP == pArg->dwMsgId && this->m_bAutoCapture)
	{
		__self->SetCapture(FALSE) ;
	}
	return S_OK ;
}

HRESULT CCUIControl::SetAttribute(ICVarData* pAttrData)
{
	 __super::SetAttribute(pAttrData) ;
	SET_ATTR_INTERFACE_BEGIN(pAttrData, IUIControl)
    SET_ATTR_BSTR           (ToolTips)
	SET_ATTR_BOOL			(AutoCapture)
	SET_ATTR_END            ()
	return S_OK ;
}