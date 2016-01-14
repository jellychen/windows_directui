#pragma once
#include "Include/UIEngine/IUIFont.h"
#include "Include/UIEngine/IUIControl.h"

[
	object ,
	uuid("C0CCC861-A94C-498f-95C4-4ECA8C16F2EF") ,
	pointer_default(unique)
]
__interface IUIStatic : IUIControl
{
	HRESULT SetText			(BSTR bstrText) ;
	HRESULT GetText			(BSTR* pbstrText) ;
	HRESULT SetFont			(IUIFont* pFont) ;
	HRESULT GetFont			(IUIFont** ppFont) ;
	HRESULT SetMutiLine		(BOOL bMutiLine) ;
	HRESULT GetMutiLine		(BOOL* pnMutiLine) ;
	HRESULT SetTextColor	(COLORREF clr) ;
	HRESULT GetTextColor	(COLORREF* pclr) ;
} ;