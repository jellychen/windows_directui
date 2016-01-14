#pragma once
#include "Include/UIEngine/IUIFrame.h"

[
	object ,
	uuid("F432F0A9-96F2-43fa-9EE6-8395B1D9102E") ,
	pointer_default(unique)
]
__interface IUIControl : IUIFrame
{
	HRESULT SetFocus			(BOOL bFocus) ;
	HRESULT GetFocus			(BOOL* pbFocus) ;
	HRESULT SetAutoCapture		(BOOL bAutoCapture) ;
	HRESULT GetAutoCapture		(BOOL* pbAutoCapture) ;
	HRESULT SetControlFoucs		(IUIControl* pControl) ;
	HRESULT GetControlFoucs		(IUIControl** ppControl) ;
	HRESULT ControlFocusChange	(BOOL bFoucs) ;
	HRESULT SetToolTips			(BSTR bstrToolTips) ;
	HRESULT GetToolTips			(BSTR* pbstrToolTips) ;
} ;