#include "stdafx.h"
#include "CCUICanvas.h"

CUICanvas::CUICanvas()
{
	this->m_hClipRgn = NULL ;
}

CUICanvas::~CUICanvas()
{
	if (NULL != this->m_hClipRgn)
	{
		::DeleteObject(this->m_hClipRgn) ;
	}
}

HRESULT CUICanvas::InitFromWnd(HWND hWnd, SIZE szCanvas)
{
	DEBUG_ASSERT(hWnd) ;
	IF_RETURN(NULL == hWnd, E_INVALIDARG) ;

	HDC hDC = ::GetWindowDC(hWnd) ;
	HRESULT hRet = this->InitFromDC(hDC, szCanvas) ;
	::ReleaseDC(hWnd, hDC) ;
	return S_OK ;
}

HRESULT CUICanvas::InitFromDC(HDC hDC, SIZE szCanvas)
{
	DEBUG_ASSERT(hDC) ;
	IF_RETURN(NULL == hDC, E_INVALIDARG) ;

	this->m_memDC.Destory() ;
	this->m_memDC.Create(hDC, szCanvas) ;
	::SetBkMode(this->m_memDC, TRANSPARENT) ;
	if (NULL != this->m_hClipRgn)
	{
		::DeleteObject(this->m_hClipRgn) ;
	}
	this->m_hClipRgn = ::CreateRectRgn(0, 0, szCanvas.cx, szCanvas.cy) ;
	return S_OK ;
}

HRESULT CUICanvas::InitFromCanvas(IUICanvas* pCanvas, SIZE szCanvas)
{
	DEBUG_ASSERT(pCanvas) ;
	IF_RETURN(NULL == pCanvas, E_INVALIDARG) ;

	HDC hDC = NULL ;
	pCanvas->GetCanvasDC(&hDC) ;
	return this->InitFromDC(hDC, szCanvas) ;
}

HRESULT CUICanvas::IsVaild(BOOL* pbValid)
{
	DEBUG_ASSERT(pbValid) ;
	IF_RETURN(NULL == pbValid, E_INVALIDARG) ;

	*pbValid = this->m_memDC.IsVaild() ;
	return S_OK ;
}

HRESULT CUICanvas::GetSize(SIZE* pszCavnas)
{
	DEBUG_ASSERT(pszCavnas) ;
	IF_RETURN(NULL == pszCavnas, E_INVALIDARG) ;

	*pszCavnas = this->m_memDC.GetSize() ;
	return S_OK ;
}

HRESULT CUICanvas::GetCanvasDC(HDC* pCanvasDC)
{
	DEBUG_ASSERT(pCanvasDC) ;
	IF_RETURN(NULL == pCanvasDC, E_INVALIDARG) ;

	*pCanvasDC = this->m_memDC ;
	return S_OK ;
}

HRESULT CUICanvas::BitbltOnDC(HDC hDC, RECT rcDraw, BOOL bStretch)
{
	CRect rc(rcDraw) ;
	if ((rc.Width() == this->m_memDC.GetSize().cx 
		&& rc.Height() == this->m_memDC.GetSize().cy) || FALSE == bStretch )
	{
		::BitBlt(hDC, rc.left, rc.top, this->m_memDC.GetSize().cx,
			this->m_memDC.GetSize().cy,this->m_memDC, 0, 0, SRCCOPY) ;
	}
	else
	{
		::StretchBlt(hDC, rc.left, rc.top, rc.Width(), rc.Height(), 
			this->m_memDC, 0, 0, this->m_memDC.GetSize().cx, this->m_memDC.GetSize().cy, SRCCOPY) ;
	}
	return S_OK ;
}

HRESULT CUICanvas::BitbltOnCanvas(IUICanvas* pCanvas, RECT rcDraw, BOOL bStretch)
{
	DEBUG_ASSERT(pCanvas) ;
	IF_RETURN(NULL == pCanvas, E_INVALIDARG) ;

	HDC  hDC = NULL ;
	pCanvas->GetCanvasDC(&hDC) ;
	return this->BitbltOnDC(hDC, rcDraw, bStretch) ;
}

HRESULT CUICanvas::DrawOnDC(HDC hDC, RECT rcDraw, BYTE cAlpha)
{
	IF_RETURN(0 == cAlpha, S_OK) ;
	CRect rc(rcDraw) ;

	BLENDFUNCTION bf = {AC_SRC_OVER, 0, cAlpha, AC_SRC_ALPHA} ;
	::AlphaBlend(hDC, rc.left, rc.top, rc.Width(), rc.Height()
		, this->m_memDC, 0, 0, rc.Width(), rc.Height(), bf) ;

	return S_OK ;
}

HRESULT CUICanvas::DrawOnCanvas(IUICanvas* pCanvas, RECT rcDraw, BYTE cAlpha)
{
	DEBUG_ASSERT(pCanvas) ;
	IF_RETURN(NULL == pCanvas, E_INVALIDARG) ;

	HDC  hDC = NULL ;
	pCanvas->GetCanvasDC(&hDC) ;
	return this->DrawOnDC(hDC, rcDraw, cAlpha) ;
}

HRESULT CUICanvas::SetViewport(POINT ptViewport, POINT* pptOldViewport)
{
	if (this->m_memDC)
	{
		::SetViewportOrgEx(this->m_memDC, ptViewport.x, ptViewport.y, (LPPOINT)pptOldViewport) ;
		return S_OK ;
	}
	return E_FAIL ;
}

HRESULT CUICanvas::OffsetViewport(POINT ptOffset, POINT* pptOldViewport)
{
	if (this->m_memDC)
	{
		::OffsetViewportOrgEx(this->m_memDC, ptOffset.x, ptOffset.y, (LPPOINT)pptOldViewport) ;
	}
	return E_FAIL ;
}

HRESULT CUICanvas::GetClipBox(RECT* prcClipBox)
{
	DEBUG_ASSERT(prcClipBox) ;
	IF_RETURN(NULL == prcClipBox, E_INVALIDARG) ;
	return ::GetClipBox(this->m_memDC, prcClipBox)? S_OK: E_FAIL ;
}

HRESULT CUICanvas::GetClipRgn(HRGN* phClipRgn)
{
	DEBUG_ASSERT(phClipRgn) ;
	IF_RETURN(NULL == phClipRgn, E_INVALIDARG) ;
	return ::CombineRgn(*phClipRgn, this->m_hClipRgn, NULL, RGN_COPY)? S_OK: E_FAIL ;
}

HRESULT CUICanvas::SetClipRgn(HRGN hClipRgn)
{
	if (this->m_hClipRgn)
	{
		::DeleteObject(this->m_hClipRgn) ;
	}
	this->m_hClipRgn = ::CreateRectRgn(0, 0, 0, 0) ;
	::CombineRgn(this->m_hClipRgn, hClipRgn, NULL, RGN_COPY) ;
	::SelectClipRgn(this->m_memDC, this->m_hClipRgn) ;
	return S_OK ;
}

HRESULT CUICanvas::SetClipRect(RECT rcClip)
{
	if (this->m_hClipRgn)
	{
		::DeleteObject(this->m_hClipRgn) ;
	}
	this->m_hClipRgn = ::CreateRectRgnIndirect(&rcClip) ;
	::SelectClipRgn(this->m_memDC, this->m_hClipRgn) ;
	return S_OK ;
}

HRESULT CUICanvas::SetCombineRect(RECT rcClipRect, INT nCombineMode)
{
	if (this->m_hClipRgn)
	{
		HRGN hRgn = ::CreateRectRgnIndirect(&rcClipRect) ;
		::CombineRgn(this->m_hClipRgn, this->m_hClipRgn, hRgn, nCombineMode) ;
		::DeleteObject(hRgn) ;
	}
	else
	{
		this->m_hClipRgn = ::CreateRectRgnIndirect(&rcClipRect) ;
	}
	::SelectClipRgn(this->m_memDC, this->m_hClipRgn) ;

	CRect rc ;
	::GetClipBox(this->m_memDC, &rc) ;

	return S_OK ;
}

HRESULT CUICanvas::ClearClipRgn()
{
	if (this->m_hClipRgn)
	{
		::DeleteObject(this->m_hClipRgn) ;
		this->m_hClipRgn = NULL ;
	}

	HRGN hRgn = ::CreateRectRgn(0, 0, 0, 0) ;
	::SelectClipRgn(this->m_memDC, hRgn) ;
	::DeleteObject(hRgn) ;
	return S_OK ;
}

HRESULT CUICanvas::GetMemImageSize(SIZE* pszBuffer)
{
	DEBUG_ASSERT(pszBuffer) ;
	IF_RETURN(NULL == pszBuffer, E_INVALIDARG) ;

	*pszBuffer = this->m_memDC.GetSize() ;
	return S_OK ;
}

HRESULT CUICanvas::GetMemBuffer(BYTE** ppBuffer)
{
	DEBUG_ASSERT(ppBuffer) ;
	IF_RETURN(NULL == ppBuffer, E_INVALIDARG) ;

	*ppBuffer = this->m_memDC.GetMemBuffer() ;
	return S_OK ;
}

HRESULT CUICanvas::GetColorByPoint(POINT pt, COLORREF* pclr)
{
	DEBUG_ASSERT(pclr) ;
	IF_RETURN(NULL == pclr, E_INVALIDARG) ;

	CSize szMemDC = this->m_memDC.GetSize() ;
	IF_RETURN(pt.x < 0 || pt.y < 0 , E_FAIL) ;
	IF_RETURN(pt.x >= szMemDC.cx || pt.y >= szMemDC.cy, E_FAIL) ;

	INT nOffset = pt.y * szMemDC.cx + pt.x ;
	*pclr = *((COLORREF*)this->m_memDC.GetMemBuffer() + nOffset) ;
	return S_OK ;
}

HRESULT CUICanvas::SetColorByPoint(POINT pt, COLORREF clr)
{
	CSize szMemDC = this->m_memDC.GetSize() ;
	IF_RETURN(pt.x < 0 || pt.y < 0 , E_FAIL) ;
	IF_RETURN(pt.x >= szMemDC.cx || pt.y >= szMemDC.cy, E_FAIL) ;

	INT nOffset = pt.y * szMemDC.cx + pt.x ;
	*((COLORREF*)this->m_memDC.GetMemBuffer() + nOffset) = clr ;
	return S_OK ;
}

HRESULT CUICanvas::OffsetCanvasAlpha(INT nOffset)
{
	BOOL bRet = this->m_memDC.AlphaOffset(nOffset) ;
	return bRet ? S_OK : E_FAIL ;
}

HRESULT CUICanvas::ClearCanvas()
{
	CRect rcClipRect(0, 0, 0, 0) ;
	::GetClipBox(this->m_memDC, &rcClipRect) ;
	if (FALSE == rcClipRect.IsRectNull() && this->m_hClipRgn)
	{
		::FillRect(this->m_memDC, &rcClipRect, (HBRUSH)::GetStockObject(BLACK_BRUSH)) ;
	}
	return S_OK ;
}

HRESULT CUICanvas::DestoryCanvas()
{
	this->m_memDC.Destory() ;
	if (this->m_hClipRgn)
	{
		::DeleteObject(this->m_hClipRgn) ;
		this->m_hClipRgn = NULL ;
	}
	return S_OK ;
}