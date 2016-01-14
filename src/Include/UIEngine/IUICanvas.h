#pragma once

[
	object ,
	uuid("661BAF54-ECCC-4A6F-9D71-27E4EA61B342") ,
	pointer_default(unique)
]
__interface IUICanvas : IDispatch
{
	HRESULT InitFromWnd         (HWND hWnd, SIZE szCanvas) ;
	HRESULT InitFromDC          (HDC hDC, SIZE szCanvas) ;
	HRESULT InitFromCanvas      (IUICanvas* pCanvas, SIZE szCanvas) ;
	HRESULT IsVaild             (BOOL* pbValid) ;
	HRESULT GetSize             (SIZE* pszCavnas) ;
	HRESULT GetCanvasDC         (HDC* pCanvasDC) ;
	HRESULT BitbltOnDC			(HDC hDC, RECT rcDraw, BOOL bStretch) ;
	HRESULT BitbltOnCanvas		(IUICanvas* pCanvas, RECT rcDraw, BOOL bStretch) ;
	HRESULT DrawOnDC            (HDC hDC, RECT rcDraw, BYTE cAlpha) ;
	HRESULT DrawOnCanvas        (IUICanvas* pCanvas, RECT rcDraw, BYTE cAlpha) ;
	HRESULT SetViewport         (POINT ptViewport, POINT* pptOldViewport) ;
	HRESULT OffsetViewport      (POINT ptOffset, POINT* pptOldViewport) ;
	HRESULT GetClipBox          (RECT* prcClipBox) ;
	HRESULT GetClipRgn          (HRGN* phClipRgn) ;
	HRESULT SetClipRgn          (HRGN hClipRgn) ;
	HRESULT SetCombineRect      (RECT rcClipRect, INT nCombineMode) ;
	HRESULT ClearClipRgn        () ;
	HRESULT GetMemImageSize     (SIZE* pszBuffer) ;
	HRESULT GetMemBuffer        (BYTE** ppBuffer) ;
	HRESULT GetColorByPoint     (POINT pt, COLORREF* pclr) ;
	HRESULT SetColorByPoint     (POINT pt, COLORREF clr) ;
	HRESULT OffsetCanvasAlpha   (INT nOffset) ;
	HRESULT ClearCanvas         () ;
	HRESULT DestoryCanvas       () ;
} ;