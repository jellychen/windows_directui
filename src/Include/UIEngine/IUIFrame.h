#pragma once

#include "Include/UIEngine/IUIDraw.h"
#include "Include/UIEngine/IUIElement.h"
#include "Include/UIEngine/IUICanvas.h"
#include "Include/UIEngine/IUIEventDef.h"
#include "Include/UIEngine/IUICalcSize.h"
#include "Include/UIEngine/IUILayout.h"
#include "Include/UIEngine/IUIFrameCursor.h"
#include "Include/UIEngine/IUIFrameCallback.h"

[
	object ,
	uuid("051D90C7-E7AB-4ee1-A171-826CA957518A") ,
	pointer_default(unique)
]
__interface IUIFrame : IUIElement
{
	HRESULT SetSize                 (SIZE szSize) ;
	HRESULT GetSize                 (SIZE* pszSize) ;
	HRESULT SetLocation             (POINT ptLocation) ;
	HRESULT GetLocation             (POINT* pptLocation) ;
	HRESULT SetRect                 (RECT rcRect) ;
	HRESULT GetRect                 (RECT* prcRect) ;
	HRESULT SetMargin               (RECT rcMargin) ;
	HRESULT GetMargin               (RECT* prcMargin) ;
	HRESULT SetPadding              (RECT rcPadding) ;
	HRESULT GetPadding              (RECT* prcPadding) ;
	HRESULT SetZOrder               (INT nZOrder) ;
	HRESULT GetZOrder               (INT* pnZOrder) ;
	HRESULT SetHidden               (BOOL bHidden) ;
	HRESULT GetHidden               (BOOL* pbHidden) ;
	HRESULT GetVisible              (BOOL* pbVisible) ;
	HRESULT SetFloat                (BOOL bFloat) ;
	HRESULT GetFloat                (BOOL* pbFloat) ;
	HRESULT SetEnable               (BOOL bEnable) ;
	HRESULT GetEnable               (BOOL* pbEnable) ;
	HRESULT SetCapture              (BOOL bCapture) ;
	HRESULT GetCapture              (BOOL* pbCapture) ;
	HRESULT SetState                (INT nState) ;
	HRESULT GetState                (INT* pnState) ;
	HRESULT SetEnableState          (BOOL bEnableState) ;
	HRESULT GetEnableState          (BOOL* pbEnableState) ;
	HRESULT SetHittest              (INT nHittest) ;
	HRESULT GetHittest              (INT* pnHittest) ;
	HRESULT SetHoverCursor			(INT nHoverCursor) ;
	HRESULT GetHoverCursor			(INT* pnHoverCursor) ;
	HRESULT GetAbsolutDepth         (INT* pnDepth) ;
	HRESULT GetAbsolutLocation      (POINT* pptLocation) ;
	HRESULT GetScreenLocation       (POINT* pptLocation) ;
	HRESULT GetAbsolutRect          (RECT* prcRect) ;
	HRESULT GetScreenRect           (RECT* prcRect) ;
	HRESULT GetAbsolutVisibleRect   (RECT* prcRect) ;

	HRESULT SetLayouter				(IUILayout* pLayouter) ;
	HRESULT GetLayouter				(IUILayout** ppLayouter) ;

	HRESULT Draw                    (IUICanvas* pCanvas) ;
	HRESULT Render                  (IUICanvas* pCanvas, RECT rcRender, INT nState) ;
	HRESULT SetDoubleBuffer         (BOOL bDoubleBuffer) ;
	HRESULT GetDoubleBuffer         (BOOL* pbDoubleBuffer) ;
	HRESULT SetAlpha                (BYTE cAlpha) ;
	HRESULT GetAlpha                (BYTE* pcAlpha) ;
	HRESULT GetShowAlpha            (BYTE* pcAlpha) ;
	HRESULT SetBkgDraw              (IUIDraw* pBkgDraw) ;
	HRESULT GetBkgDraw              (IUIDraw** ppBkgDraw) ;
	HRESULT SetBkgDrawAlpha         (BYTE cBkgAlpha) ;
	HRESULT GetBkgDrawAlpha         (BYTE* pcBkgAlpha) ;
	HRESULT SetBkgMaskDraw          (IUIDraw* pBkgMaskDraw) ;
	HRESULT GetBkgMaskDraw          (IUIDraw** ppBkgMaskDraw) ;
	HRESULT SetBkgMaskDrawAlpha     (BYTE cBkgMaskAlpha) ;
	HRESULT GetBkgMaskDrawAlpha     (BYTE* pcBkgMaskAlpha) ;

	HRESULT Update                  (BOOL bFoceLayout, BOOL bFoceSync) ;

	HRESULT SetAnchor               (INT nAnchor) ;
	HRESULT GetAnchor               (INT* pAnchor) ;
	HRESULT SetDrift				(INT nDrift) ;
	HRESULT GetDrift				(INT* pnDrift) ;
	HRESULT SetAutoWidth            (BOOL bAutoWidth) ;
	HRESULT GetAutoWidth            (BOOL* pbAutoWidth) ;
	HRESULT SetAutoHeight           (BOOL bAutoHeight) ;
	HRESULT GetAutoHeight           (BOOL* pbAutoHeight) ;
	HRESULT SetAutoSize             (BOOL bAutoSize) ;
	HRESULT GetAutoSize             (BOOL* pbAutoSize) ;
	HRESULT SetMaxAutoSize          (SIZE szMaxAutoSize) ;
	HRESULT GetMaxAutoSize          (SIZE* pszMaxAutoSize) ;
	HRESULT SetMinAutoSize          (SIZE szMinAutoSize) ;
	HRESULT GetMinAutoSize          (SIZE* pszMinAutoSize) ;
	HRESULT SetWidthAsParent        (BOOL bWidthAsParent) ;
	HRESULT GetWidthAsParent        (BOOL* pbWidthAsParent) ;
	HRESULT SetHeightAsParent       (BOOL bHeightAsParent) ;
	HRESULT GetHeightAsParent       (BOOL* pbHeightAsParent) ;
	HRESULT SetSizeAsParent         (BOOL bSizeAsParent) ;
	HRESULT GetSizeAsParent         (BOOL* pbSizeAsParent) ;

	HRESULT SetEnableDrag           (BOOL bEnable) ;
	HRESULT GetEnableDrag           (BOOL* pbEnable) ;
	HRESULT SetDragRange            (RECT rcRange) ;
	HRESULT GetDragRange            (RECT* prcRange) ;
	HRESULT SetEnableVerticalDrag   (BOOL bEnable) ;
	HRESULT GetEnableVerticalDrag   (BOOL* pbEnable) ;
	HRESULT SetEnableHorizontalDrag (BOOL bEnable) ;
	HRESULT GetEnableHorizontalDrag (BOOL* pbEnable) ;

	HRESULT SetEnableDBClick        (BOOL bEnable) ;
	HRESULT GetEnableDBClick        (BOOL* pbEnable) ;
	HRESULT SetIntercepMouse        (BOOL bIntercept) ;
	HRESULT GetIntercepMouse        (BOOL* pbIntercept) ;
	HRESULT SetTransparentMouse     (BOOL bTransparent) ;
	HRESULT GetTransparentMouse     (BOOL* pbTransparent) ;
	HRESULT SetIntercepKeyboard     (BOOL bIntercept) ;
	HRESULT GetIntercepKeyboard		(BOOL* pbIntercept) ;
	HRESULT SetTransparentKeyboard  (BOOL bTransparent) ;
	HRESULT GetTransparentKeyboard	(BOOL* pbTransparent) ;

	HRESULT Invalidate              () ;
	HRESULT InvalidateRect          (RECT rcInvalidate) ;

	HRESULT RaiseEvent              (INT nEventId, tEventArg* pArgs) ;
	HRESULT AddEventListener        (INT nEventId, IUIEventCallback* pListener) ;
	HRESULT DelEventListener        (INT nEventId, IUIEventCallback* pListener) ;
	HRESULT AddDestoryListener      (IUIDestoryCallback* pListener) ;
	HRESULT DelDestoryListener      (IUIDestoryCallback* pListener) ;
} ;