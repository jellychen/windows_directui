#pragma once
#include "Include/UIEngine/IUIDraw.h"
#include "Include/UIEngine/IUIFont.h"
#include "Include/UIEngine/IUIControl.h"
#include "Include/UIEngine/IUIButtonEvent.h"

[
    object ,
    uuid("42FB084C-7535-43B5-87DE-E6533C323A0B") ,
    pointer_default(unique)
]
__interface IUIButton : IUIControl
{
	HRESULT SetFont                 (IUIFont* pFont) ;
    HRESULT GetFont                 (IUIFont** ppFont) ;
    HRESULT SetText                 (BSTR bstrText) ;
    HRESULT GetText                 (BSTR* pbstrText) ;
	HRESULT SetTextNormalColor      (COLORREF clr) ;
    HRESULT GetTextNormalColor      (COLORREF* pclr) ;
    HRESULT SetTextHighlightColor	(COLORREF clr) ;
    HRESULT GetTextHighlightColor   (COLORREF* pclr) ;
    HRESULT SetTextPushedColor      (COLORREF clr) ;
    HRESULT GetTextPushedColor      (COLORREF* pclr) ;
    HRESULT SetTextDisableColor     (COLORREF clr) ;
    HRESULT GetTextDisableColor     (COLORREF* pclr) ;
    HRESULT SetNormalBkgDraw        (IUIDraw* pNormalDraw) ;
    HRESULT GetNormalBkgDraw        (IUIDraw** ppNormalDraw) ;
    HRESULT SetHighlightBkgDraw     (IUIDraw* pHighlightDraw) ;
    HRESULT GetHighlightBkgDraw     (IUIDraw** ppHighlightDraw) ;
    HRESULT SetPushedBkgDraw        (IUIDraw* pPushedDraw) ;
    HRESULT GetPushedBkgDraw        (IUIDraw** ppPushedDraw) ;
    HRESULT SetDisableBkgDraw       (IUIDraw* pDisableDraw) ;
    HRESULT GetDisableBkgDraw       (IUIDraw** ppDisableDraw) ;
} ;