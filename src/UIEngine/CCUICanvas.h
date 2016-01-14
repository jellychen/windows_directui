#pragma once
#include "CUIMemDC.h"
#include "Include/UIEngine/IUICanvas.h"

[
	default(IUICanvas) ,
	threading(free) ,
	uuid("73717462-7951-4d02-9EA9-322F5182D1CA") ,
	coclass
]
class ATL_NO_VTABLE CUICanvas
	: public IDispatchImpl<IUICanvas>
{
public:
	DECLARE_PROTECT_FINAL_CONSTRUCT() ;
	CUICanvas() ;
	virtual ~CUICanvas() ;

public:
	HRESULT _call InitFromWnd       (HWND hWnd, SIZE szCanvas) ;
	HRESULT _call InitFromDC        (HDC hDC, SIZE szCanvas) ;
	HRESULT _call InitFromCanvas    (IUICanvas* pCanvas, SIZE szCanvas) ;
	HRESULT _call IsVaild           (BOOL* pbValid) ;
	HRESULT _call GetSize           (SIZE* pszCavnas) ;
	HRESULT _call GetCanvasDC       (HDC* pCanvasDC) ;
	HRESULT _call BitbltOnDC		(HDC hDC, RECT rcDraw, BOOL bStretch) ;
	HRESULT _call BitbltOnCanvas	(IUICanvas* pCanvas, RECT rcDraw, BOOL bStretch) ;
	HRESULT _call DrawOnDC          (HDC hDC, RECT rcDraw, BYTE cAlpha) ;
	HRESULT _call DrawOnCanvas      (IUICanvas* pCanvas, RECT rcDraw, BYTE cAlpha) ;
	HRESULT _call SetViewport       (POINT ptViewport, POINT* pptOldViewport) ;
	HRESULT _call OffsetViewport    (POINT ptOffset, POINT* pptOldViewport) ;
	HRESULT _call GetClipBox        (RECT* prcClipBox) ;
	HRESULT _call GetClipRgn        (HRGN* phClipRgn) ;
	HRESULT _call SetClipRgn        (HRGN hClipRgn) ;
	HRESULT _call SetClipRect       (RECT rcClip) ;
	HRESULT _call SetCombineRect    (RECT rcClipRect, INT nCombineMode) ;
	HRESULT _call ClearClipRgn      () ;
	HRESULT _call GetMemImageSize   (SIZE* pszBuffer) ;
	HRESULT _call GetMemBuffer      (BYTE** ppBuffer) ;
	HRESULT _call GetColorByPoint   (POINT pt, COLORREF* pclr) ;
	HRESULT _call SetColorByPoint   (POINT pt, COLORREF clr) ;
	HRESULT _call OffsetCanvasAlpha (INT nOffset) ;
	HRESULT _call ClearCanvas       () ;
	HRESULT _call DestoryCanvas     () ;

private:
	CUIMemDC                        m_memDC ;
	HRGN                            m_hClipRgn ;
} ;