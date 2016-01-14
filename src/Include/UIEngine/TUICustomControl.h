#pragma once
#include "Include/UIEngine/IUIControl.h"
#include "Include/UIEngine/TUICustomFrame.h"

template<typename IActual, typename IBase>
class TUICustomControl
	: public TUICustomFrame<IActual, IBase>
{
public:
	HRESULT _call SetFocus(BOOL bFocus)
	{
		return this->m_pRawObject->SetFocus(bFocus) ;
	}

	HRESULT _call GetFocus(BOOL* pbFocus)
	{
		return this->m_pRawObject->GetFocus(pbFocus) ;
	}

	HRESULT _call SetAutoCapture(BOOL bAutoCapture)
	{
		return this->m_pRawObject->SetAutoCapture(bAutoCapture) ;
	}
	
	HRESULT _call GetAutoCapture(BOOL* pbAutoCapture)
	{
		return this->m_pRawObject->GetAutoCapture(pbAutoCapture) ;
	}

	HRESULT _call SetControlFoucs(IUIControl* pControl)
	{
		return this->m_pRawObject->SetControlFoucs(pControl) ;
	}

	HRESULT _call GetControlFoucs(IUIControl** ppControl)
	{
		return this->m_pRawObject->GetControlFoucs(ppControl) ;
	}

	HRESULT _call ControlFocusChange(BOOL bFoucs)
	{
		return this->m_pRawObject->ControlFocusChange(bFoucs) ;
	}
	
	HRESULT _call SetToolTips(BSTR bstrToolTips)
	{
		return this->m_pRawObject->SetToolTips(bstrToolTips) ;
	}

	HRESULT _call GetToolTips(BSTR* pbstrToolTips)
	{
		return this->m_pRawObject->GetToolTips(pbstrToolTips) ;
	}
} ;