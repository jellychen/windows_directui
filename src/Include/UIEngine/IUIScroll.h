#pragma once
#include "Include/UIEngine/IUIDraw.h"
#include "Include/UIEngine/IUIControl.h"
#include "Include/UIEngine/IUIScrollDef.h"


[
	object ,
	uuid("E386D85B-BF83-4bdc-9CFA-0916C4002F29") ,
	pointer_default(unique)
]
__interface IUIScroll : IUIControl
{
	HRESULT SetOrientation                  (INT nOrientation) ;
	HRESULT GetOrientation                  (INT* pnOrientation) ;
	HRESULT SetEnableWheel                  (BOOL bEnableWheel) ;
	HRESULT GetEnableWheel                  (BOOL* pbEnableWheel) ;
	HRESULT SetPercentage                   (INT nPercetage) ;
	HRESULT GetPercentage                   (INT* pnPercetage) ;
	HRESULT SetScrollScale                  (INT nScale) ;
	HRESULT GetScrollScale                  (INT* pnScale) ;
	HRESULT SetScrollBarSize                (SIZE szScrollBar) ;
	HRESULT GetScrollBarSize                (SIZE* pszScrollBar) ;
	HRESULT SetScrollBarMinSize             (SIZE szScrollBar) ;
	HRESULT GetScrollBarMinSize             (SIZE* pszScrollBar) ;
	HRESULT SetScrollBarNormalDraw          (IUIDraw* pNormalDraw) ;
	HRESULT GetScrollBarNormalDraw          (IUIDraw** ppNormalDraw) ;
	HRESULT SetScrollBarHighlightDraw       (IUIDraw* pHighlightDraw) ;
	HRESULT GetScrollBarHighlightDraw       (IUIDraw** ppHighlightDraw) ;
	HRESULT SetScrollBarPushedDraw          (IUIDraw* pPushedDraw) ;
	HRESULT GetScrollBarPushedDraw          (IUIDraw** ppPushedraw) ;
} ;