#include "stdafx.h"
#include "CCUIText.h"

CCUIText::CCUIText()
{
	this->m_eStringAlignment    = Gdiplus::StringAlignmentCenter ;
	this->m_eStringLineAlignment= Gdiplus::StringAlignmentCenter ;
	this->m_bNoWarp             = FALSE ;
	this->m_bVertical           = FALSE ;
	this->m_bRightToLeft        = FALSE ;
	this->m_bLineLimit          = FALSE ;
}

CCUIText::~CCUIText()
{
}

HRESULT CCUIText::FinalConstruct()
{
	return S_OK ;
}

HRESULT CCUIText::SetFont(IUIFont* pFont)
{
	this->m_pFont = pFont ;
	return S_OK ;
}

HRESULT CCUIText::GetFont(IUIFont** ppFont)
{
	DEBUG_ASSERT(ppFont) ;
	IF_RETURN(NULL == ppFont, E_INVALIDARG) ;
	*ppFont = NULL ;
	if (this->m_pFont)
	{
		return this->m_pFont->QueryInterface(__uuidof(IUIFont), (VOID**)ppFont) ;
	}
	return E_FAIL ;
}

HRESULT CCUIText::SetAlignment(DWORD dwAligment)
{
	if (TEXT::ALI_CENTER == dwAligment)
	{
		this->m_eStringAlignment = Gdiplus::StringAlignmentCenter ;
	}
	else if (TEXT::ALI_NEAR == dwAligment)
	{
		this->m_eStringAlignment = Gdiplus::StringAlignmentNear ;
	}
	else if (TEXT::ALI_FAR == dwAligment)
	{
		this->m_eStringAlignment = Gdiplus::StringAlignmentFar ;
	}
	else
	{
		return E_FAIL ;
	}
	return S_OK ;
}

HRESULT CCUIText::SetAlignment(BSTR bstrAlignment)
{
	CString strAlignment(bstrAlignment) ;
	if (0 == strAlignment.CompareNoCase(_T("ALI_CENTER")))
	{
		return this->SetAlignment(TEXT::ALI_CENTER) ;
	}
	else if (0 == strAlignment.CompareNoCase(_T("ALI_NEAR")))
	{
		return this->SetAlignment(TEXT::ALI_NEAR) ;
	}
	else if (0 == strAlignment.CompareNoCase(_T("ALI_FAR")))
	{
		return this->SetAlignment(TEXT::ALI_FAR) ;
	}
	return E_FAIL ;
}

HRESULT CCUIText::GetAlignment(DWORD* pdwAligment)
{
	DEBUG_ASSERT(pdwAligment) ;
	IF_RETURN(NULL == pdwAligment, E_INVALIDARG) ;
	if (this->m_eStringAlignment == Gdiplus::StringAlignmentCenter)
	{
		*pdwAligment = TEXT::ALI_CENTER ;
	}
	else if (this->m_eStringAlignment == Gdiplus::StringAlignmentNear)
	{
		*pdwAligment = TEXT::ALI_NEAR ;
	}
	else if (this->m_eStringAlignment == Gdiplus::StringAlignmentFar)
	{
		*pdwAligment = TEXT::ALI_FAR ;
	}
	else
	{
		return E_FAIL ;
	}
	return S_OK ;
}

HRESULT CCUIText::SetLineAlignment(DWORD dwAligment)
{
	if (TEXT::ALI_CENTER == dwAligment)
	{
		this->m_eStringLineAlignment = Gdiplus::StringAlignmentCenter ;
	}
	else if (TEXT::ALI_NEAR == dwAligment)
	{
		this->m_eStringLineAlignment = Gdiplus::StringAlignmentNear ;
	}
	else if (TEXT::ALI_FAR == dwAligment)
	{
		this->m_eStringLineAlignment = Gdiplus::StringAlignmentFar ;
	}
	else
	{
		return E_FAIL ;
	}
	return S_OK ;
}

HRESULT CCUIText::SetLineAlignment(BSTR bstrAlignment)
{
	CString strAlignment(bstrAlignment) ;
	if (0 == strAlignment.CompareNoCase(_T("ALI_CENTER")))
	{
		return this->SetLineAlignment(TEXT::ALI_CENTER) ;
	}
	else if (0 == strAlignment.CompareNoCase(_T("ALI_NEAR")))
	{
		return this->SetLineAlignment(TEXT::ALI_NEAR) ;
	}
	else if (0 == strAlignment.CompareNoCase(_T("ALI_FAR")))
	{
		return this->SetLineAlignment(TEXT::ALI_FAR) ;
	}
	return E_FAIL ;
}

HRESULT CCUIText::GetLineAlignment(DWORD* pdwAligment)
{
	DEBUG_ASSERT(pdwAligment) ;
	IF_RETURN(NULL == pdwAligment, E_INVALIDARG) ;
	if (this->m_eStringLineAlignment == Gdiplus::StringAlignmentCenter)
	{
		*pdwAligment = TEXT::ALI_CENTER ;
	}
	else if (this->m_eStringLineAlignment == Gdiplus::StringAlignmentNear)
	{
		*pdwAligment = TEXT::ALI_NEAR ;
	}
	else if (this->m_eStringLineAlignment == Gdiplus::StringAlignmentFar)
	{
		*pdwAligment = TEXT::ALI_FAR ;
	}
	else
	{
		return E_FAIL ;
	}
	return S_OK ;
}

HRESULT CCUIText::SetRightToLeft(BOOL bRightToLeft)
{
	this->m_bRightToLeft = TRUE ;
	return S_OK ;
}

HRESULT CCUIText::GetRightTopLeft(BOOL* pbRightToLeft)
{
	DEBUG_ASSERT(pbRightToLeft) ;
	IF_RETURN(NULL == pbRightToLeft, E_INVALIDARG) ;
	*pbRightToLeft = this->m_bRightToLeft ;
	return S_OK ;
}

HRESULT CCUIText::SetVertical(BOOL bVertical)
{
	this->m_bVertical = bVertical ;
	return S_OK ;
}

HRESULT CCUIText::GetVertical(BOOL* pbVertical)
{
	DEBUG_ASSERT(pbVertical) ;
	IF_RETURN(NULL == pbVertical, E_INVALIDARG) ;
	*pbVertical = this->m_bVertical ;
	return S_OK ;
}

HRESULT CCUIText::SetNoWarp(BOOL bNoWarp)
{
	this->m_bNoWarp = bNoWarp ;
	return S_OK ;
}

HRESULT CCUIText::GetNoWarp(BOOL* pbNoWarp)
{
	DEBUG_ASSERT(pbNoWarp) ;
	IF_RETURN(NULL == pbNoWarp, E_INVALIDARG) ;
	*pbNoWarp = this->m_bNoWarp ;
	return S_OK ;
}

HRESULT CCUIText::SetLineLimit(BOOL bLimitLine)
{
	this->m_bLineLimit = bLimitLine ;
	return S_OK ;
}

HRESULT CCUIText::GetLineLimit(BOOL* pbLimitLine)
{
	DEBUG_ASSERT(pbLimitLine) ;
	IF_RETURN(NULL == pbLimitLine, E_INVALIDARG) ;
	*pbLimitLine = this->m_bLineLimit ;
	return S_OK ;
}

HRESULT CCUIText::SetTrimming(DWORD dwTrimType)
{
	if (TEXT::TRIM_NONE == dwTrimType)
	{
		this->m_eStringTrimming = Gdiplus::StringTrimmingNone ;
	}
	else if (TEXT::TRIM_CHAR == dwTrimType)
	{
		this->m_eStringTrimming = Gdiplus::StringTrimmingCharacter ;
	}
	else if (TEXT::TRIM_WORD == dwTrimType)
	{
		this->m_eStringTrimming = Gdiplus::StringTrimmingWord ;
	}
	else
	{
		return E_INVALIDARG ;
	}
	return S_OK ;
}

HRESULT CCUIText::SetTrimming(BSTR bstrTrimType)
{
	CString strTrimType(bstrTrimType) ;
	if (0 == strTrimType.CompareNoCase(_T("TRIM_NONE")))
	{
		return this->SetTrimming(TEXT::TRIM_NONE) ;
	}
	else if (0 == strTrimType.CompareNoCase(_T("TRIM_CHAR")))
	{
		return this->SetTrimming(TEXT::TRIM_CHAR) ;
	}
	else if (0 == strTrimType.CompareNoCase(_T("TRIM_WORD")))
	{
		return this->SetTrimming(TEXT::TRIM_WORD) ;
	}
	return E_FAIL ;
}

HRESULT CCUIText::GetTrimming(DWORD* pdwTrimType)
{
	DEBUG_ASSERT(pdwTrimType) ;
	IF_RETURN(NULL == pdwTrimType, E_INVALIDARG) ;
	if (Gdiplus::StringTrimmingNone == this->m_eStringTrimming)
	{
		*pdwTrimType = TEXT::TRIM_NONE ;
	}
	else if (Gdiplus::StringTrimmingCharacter == this->m_eStringTrimming)
	{
		*pdwTrimType = TEXT::TRIM_CHAR ;
	}
	else if (Gdiplus::StringTrimmingWord == this->m_eStringTrimming)
	{
		*pdwTrimType = TEXT::TRIM_WORD ;
	}
	else
	{
		return E_FAIL ;
	}
	return S_OK ;
}

HRESULT CCUIText::CalcTextSize(BSTR bstrText, SIZE szLayout, SIZE* pszCalcOut)
{
	DEBUG_ASSERT(pszCalcOut) ;
	IF_RETURN(NULL == pszCalcOut, E_INVALIDARG) ;

	HDC hDC = ::GetDC(NULL) ;
	Gdiplus::Graphics _graphics(hDC) ;
	CString strText(bstrText) ;

	LOGFONT _log_font ;
	this->m_pFont->GetLogFont(&_log_font) ;
	Gdiplus::Font _font(hDC, &_log_font) ;

	INT nStringFlag = 0 ;
	if (this->m_bRightToLeft)
	{
		nStringFlag |= Gdiplus::StringFormatFlagsDirectionRightToLeft ;
	}

	if (this->m_bVertical)
	{
		nStringFlag |= Gdiplus::StringFormatFlagsDirectionVertical ;
	}

	if (this->m_bNoWarp)
	{
		nStringFlag |= Gdiplus::StringFormatFlagsNoWrap ;
	}

	if (this->m_bLineLimit)
	{
		nStringFlag |= Gdiplus::StringFormatFlagsLineLimit ;
	}

	Gdiplus::StringFormat _string_format ;
	_string_format.SetAlignment(this->m_eStringAlignment) ;
	_string_format.SetLineAlignment(this->m_eStringLineAlignment) ;
	_string_format.SetTrimming(this->m_eStringTrimming) ;
	_string_format.SetFormatFlags(nStringFlag) ;

	if (szLayout.cx < 0)
	{
		szLayout.cx = INT_MAX ;
	}

	if (szLayout.cy < 0)
	{
		szLayout.cy = INT_MAX ;
	}
	Gdiplus::RectF _rect_layout(0.0f, 0.0f, szLayout.cx, szLayout.cy) ;
	INT nColdepointsFitted = 0 , nLinesFilled = 0 ;
	Gdiplus::RectF _rect_calcout ;
	_graphics.MeasureString(strText.GetBuffer(), -1, &_font,
		_rect_layout, &_string_format, &_rect_calcout, &nColdepointsFitted, &nLinesFilled) ;
	strText.ReleaseBuffer() ;
	pszCalcOut->cx = (INT)ceil(_rect_calcout.Width) ;
	pszCalcOut->cy = (INT)ceil(_rect_calcout.Height) ;

	::DeleteDC(hDC) ;
	return S_OK ;
}

HRESULT CCUIText::CalcCharSize(TCHAR tcChar,  SIZE* pszCalcOut)
{
	DEBUG_ASSERT(pszCalcOut) ;
	IF_RETURN(NULL == pszCalcOut, E_INVALIDARG) ;

	pszCalcOut->cx = 0 ; pszCalcOut->cy = 0 ;
	IF_RETURN(NULL == this->m_pFont, E_FAIL) ;

	HFONT _hFont = NULL ;
	this->m_pFont->GetHFont(&_hFont) ;
	HDC hDC = ::GetDC(NULL) ;
	HFONT hOldObject = (HFONT)::SelectObject(hDC, _hFont) ;
	TCHAR _str[2] ; _str[0] = tcChar, _str[1] = _T('\0') ;
	::GetTextExtentPoint32(hDC, _str, 1, pszCalcOut) ;
	::SelectObject(hDC, hOldObject) ;
	::DeleteDC(hDC) ;
	return S_OK ;
}

HRESULT CCUIText::DrawOnDC(HDC hDC, BSTR bstrText, RECT rcRender, COLORREF clr, BYTE cAlpha)
{
	DEBUG_ASSERT(hDC) ;
	IF_RETURN(NULL == hDC, E_INVALIDARG) ;
	IF_RETURN(NULL == this->m_pFont, E_FAIL) ;
	::SetBkMode(hDC, TRANSPARENT) ;
	Gdiplus::Graphics _graphics(hDC) ;
	CString     strText(bstrText) ;
	CRect       rcTextRender(rcRender) ;

	LOGFONT _log_font ;
	this->m_pFont->GetLogFont(&_log_font) ;
	Gdiplus::FontFamily     _font_family(_log_font.lfFaceName);
	Gdiplus::Font           _font(hDC, &_log_font) ;

	INT nStringFlag = Gdiplus::StringFormatFlagsMeasureTrailingSpaces ;
	if (this->m_bRightToLeft)
	{
		nStringFlag |= Gdiplus::StringFormatFlagsDirectionRightToLeft ;
	}

	if (this->m_bVertical)
	{
		nStringFlag |= Gdiplus::StringFormatFlagsDirectionVertical ;
	}

	if (this->m_bNoWarp)
	{
		nStringFlag |= Gdiplus::StringFormatFlagsNoWrap ;
	}

	if (this->m_bLineLimit)
	{
		nStringFlag |= Gdiplus::StringFormatFlagsLineLimit ;
	}


	Gdiplus::StringFormat _string_format ;
	_string_format.SetAlignment(this->m_eStringAlignment) ;
	_string_format.SetLineAlignment(this->m_eStringLineAlignment) ;
	_string_format.SetTrimming(this->m_eStringTrimming) ;
	_string_format.SetFormatFlags(nStringFlag) ;

	Gdiplus::SolidBrush _brush(Gdiplus::Color(cAlpha, GetRValue(clr), GetGValue(clr), GetBValue(clr))) ;
	Gdiplus::RectF _rect_layout ;
	_rect_layout.X      = rcRender.left ;
	_rect_layout.Y      = rcRender.top ;
	_rect_layout.Width  = rcRender.right - rcRender.left ;
	_rect_layout.Height = rcRender.bottom - rcRender.top ;

	_graphics.SetSmoothingMode(Gdiplus::SmoothingModeHighQuality) ;

	DWORD dwFontDrawType = Gdiplus::TextRenderingHintAntiAlias  ;
	this->m_pFont->GetDrawType(&dwFontDrawType) ;
	_graphics.SetTextRenderingHint((Gdiplus::TextRenderingHint)dwFontDrawType) ;
	_graphics.DrawString(LPCTSTR(strText), strText.GetLength(), &_font, _rect_layout, &_string_format, &_brush) ;

	return S_OK ;
}

HRESULT CCUIText::DrawOnCanvas(IUICanvas* pCanvas, BSTR bstrText, RECT rcRender, COLORREF clr, BYTE cAlpha)
{
	DEBUG_ASSERT(pCanvas) ;
	IF_RETURN(NULL == pCanvas, E_INVALIDARG) ;
	HDC hDC = NULL ;
	if (SUCCEEDED(pCanvas->GetCanvasDC(&hDC)) && NULL != hDC)
	{
		return this->DrawOnDC(hDC, bstrText, rcRender, clr, cAlpha) ;
	}
	return E_FAIL ;
}

HRESULT CCUIText::SetAttribute(ICVarData* pAttrData)
{
	SET_ATTR_CLASS_BEGIN    (pAttrData, CCUIText)
	SET_ATTR_INTERFACE      (IUIFont, Font)
	SET_ATTR_BSTR           (Alignment)
	SET_ATTR_BSTR           (LineAlignment)
	SET_ATTR_BOOL           (RightToLeft)
	SET_ATTR_BOOL           (Vertical)
	SET_ATTR_BOOL           (NoWarp)
	SET_ATTR_BOOL           (LineLimit)
	SET_ATTR_BOOL           (Vertical)
	SET_ATTR_BSTR           (Trimming)
	SET_ATTR_END            ()

	return S_OK ;
}