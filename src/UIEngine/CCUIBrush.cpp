#include "stdafx.h"
#include "CCUIBrush.h"

CCUIBrush::CCUIBrush()
{
	this->m_dwBrushType = BRUSH::RECT_BORDER ;
	this->m_clrColor    = RGB(0, 0, 0) ;
}

CCUIBrush::~CCUIBrush()
{
}

HRESULT CCUIBrush::SetColor(COLORREF clrColor)
{
	this->m_clrColor = clrColor ;
	return S_OK ;
}

HRESULT CCUIBrush::GetColor(COLORREF* pclrColor)
{
	DEBUG_ASSERT(pclrColor) ;
	IF_RETURN(NULL == pclrColor, E_INVALIDARG) ;

	*pclrColor = this->m_clrColor ;
	return S_OK ;
}

HRESULT CCUIBrush::SetBrushType(DWORD dwType)
{
	this->m_dwBrushType = dwType ;
	return S_OK ;
}

HRESULT CCUIBrush::SetBrushType(BSTR bstrType)
{
	CString cstrType = bstrType ;
	if (0 == cstrType.CompareNoCase(_T("RECT_FILL")))
	{
		return this->SetBrushType(BRUSH::RECT_FILL) ;
	}
	else if (0 == cstrType.CompareNoCase(_T("RECT_BORDER")))
	{
		return this->SetBrushType(BRUSH::RECT_BORDER) ;
	}
	else if (0 == cstrType.CompareNoCase(_T("DOTE_RECT_BORDER")))
	{
		return this->SetBrushType(BRUSH::DOTE_RECT_BORDER) ;
	}
	return E_FAIL ;
}

HRESULT CCUIBrush::GetBrushType(DWORD* pdwType)
{
	DEBUG_ASSERT(pdwType) ;
	IF_RETURN(NULL == pdwType, E_INVALIDARG) ;

	*pdwType = this->m_dwBrushType ;
	return S_OK ;
}

HRESULT CCUIBrush::GetSize(SIZE* pszDraw)
{
	DEBUG_ASSERT(pszDraw) ;
	IF_RETURN(NULL == pszDraw, E_INVALIDARG) ;

	pszDraw->cx = 0 ;
	pszDraw->cy = 0 ;
	return S_OK ;
}

HRESULT CCUIBrush::DrawOnDC(HDC hDC, RECT rcDraw, BYTE cAlpha)
{
	DEBUG_ASSERT(hDC) ;
	IF_RETURN(NULL == hDC, E_INVALIDARG) ;

	Gdiplus::Graphics _graphic(hDC) ;
	_graphic.SetSmoothingMode(Gdiplus::SmoothingModeDefault) ;

	if (BRUSH::DOTE_RECT_BORDER == this->m_dwBrushType
		|| BRUSH::RECT_BORDER == this->m_dwBrushType)
	{
		Gdiplus::Pen _pen(Gdiplus::Color(cAlpha, 
			GetRValue(this->m_clrColor), GetGValue(this->m_clrColor), GetBValue(this->m_clrColor))) ;

		if (BRUSH::DOTE_RECT_BORDER == this->m_dwBrushType)
		{
			Gdiplus::REAL dashVals[2] = {2.0f, 2.0f} ;
			_pen.SetDashPattern(dashVals, 2) ;
		}
		_graphic.DrawLine(&_pen, rcDraw.left + 1, rcDraw.top + 1, rcDraw.right - 1, rcDraw.top + 1) ;
		_graphic.DrawLine(&_pen, rcDraw.left + 1, rcDraw.top + 2, rcDraw.left + 1, rcDraw.bottom - 2) ;
		_graphic.DrawLine(&_pen, rcDraw.right -1 , rcDraw.bottom - 2, rcDraw.right - 1, rcDraw.top + 2) ;
		_graphic.DrawLine(&_pen, rcDraw.right - 1, rcDraw.bottom - 1, rcDraw.left + 1, rcDraw.bottom - 1) ;
	}
	else if (BRUSH::RECT_FILL == this->m_dwBrushType)
	{
		Gdiplus::SolidBrush _bursh(Gdiplus::Color(cAlpha, 
			GetRValue(this->m_clrColor), GetGValue(this->m_clrColor), GetBValue(this->m_clrColor))) ;
		_graphic.FillRectangle(&_bursh, rcDraw.left, rcDraw.top, rcDraw.right, rcDraw.bottom) ;
	}
	return S_OK ;
}


HRESULT CCUIBrush::DrawOnCanvas(IUICanvas* pCanvas, RECT rcDraw, BYTE cAlpha)
{
	DEBUG_ASSERT(pCanvas) ;
	IF_RETURN(NULL == pCanvas, E_INVALIDARG) ;

	HDC hDC = NULL ;
	pCanvas->GetCanvasDC(&hDC) ;
	return this->DrawOnDC(hDC, rcDraw, cAlpha) ;
}

HRESULT CCUIBrush::SetAttribute(ICVarData* pAttrData)
{
	SET_ATTR_CLASS_BEGIN    (pAttrData, CCUIBrush)
	SET_ATTR_COLORREF       (Color)
	SET_ATTR_BSTR           (BrushType)
	SET_ATTR_END            ()
	return S_OK ;
}