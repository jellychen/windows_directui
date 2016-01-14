#include "stdafx.h"
#include "CCUIFont.h"

CCUIFont::CCUIFont()
{
	this->m_nFontHeight         = -16 ;
	this->m_nFontWidth          = 0 ;
	this->m_nEscapement         = 0 ;
	this->m_nWeight             = FW_NORMAL ;
	this->m_bItatic             = FALSE ;
	this->m_bStrikeout          = FALSE ;
	this->m_bUnderline          = FALSE ;
	this->m_cOutPrecision       = OUT_STRING_PRECIS ;
	this->m_cClipPrecision      = CLIP_STROKE_PRECIS ;
	this->m_cQuality            = PROOF_QUALITY ;
	this->m_nOrientation        = 0 ;
	this->m_cstrFacename        = _T("Î¢ÈíÑÅºÚ") ;
	this->m_cCharset            = GB2312_CHARSET ;
	this->m_cPitchAndFamily     = DEFAULT_PITCH ;
	this->m_dwDrawType          = FONT_DRAW::DRAW_ANTIALIAS ;//::DRAW_ANTIALIASGRIDFIT ;
	this->m_bFontAttrChange     = TRUE ;
	this->m_hFont               = NULL ;
}

CCUIFont::~CCUIFont()
{
	if (this->m_hFont)
	{
		::DeleteObject(this->m_hFont) ;
	}
}

HRESULT CCUIFont::SetWidth(INT nWidth)
{
	IF_RETURN(this->m_nFontWidth == nWidth, E_FAIL) ;
	this->m_nFontWidth = nWidth ;
	this->m_bFontAttrChange = TRUE ;
	return S_OK ;
}

HRESULT CCUIFont::GetWidth(INT* pnWidth)
{
	DEBUG_ASSERT(pnWidth) ;
	IF_RETURN(NULL == pnWidth, E_INVALIDARG) ;
	*pnWidth = this->m_nFontWidth ;
	return S_OK ;
}

HRESULT CCUIFont::SetHeight(INT nHeight)
{
	IF_RETURN(this->m_nFontHeight == nHeight, E_FAIL) ;
	this->m_nFontHeight = nHeight ;
	this->m_bFontAttrChange = TRUE ;
	return S_OK ;
}

HRESULT CCUIFont::GetHeight(INT* pnHeight)
{
	DEBUG_ASSERT(pnHeight) ;
	IF_RETURN(NULL == pnHeight, E_INVALIDARG) ;
	*pnHeight = this->m_nFontHeight ;
	return S_OK ;
}

HRESULT CCUIFont::SetEscapement(INT nEscapement)
{
	IF_RETURN(this->m_nEscapement == nEscapement, E_FAIL) ;
	this->m_nEscapement = nEscapement ;
	this->m_bFontAttrChange = TRUE ;
	return S_OK ;
}

HRESULT CCUIFont::GetEscapement(INT* pnEscapement)
{
	DEBUG_ASSERT(pnEscapement) ;
	IF_RETURN(NULL == pnEscapement, E_INVALIDARG) ;
	*pnEscapement = this->m_nEscapement ;
	return S_OK ;
}

HRESULT CCUIFont::SetWeight(INT nWeight)
{
	IF_RETURN(this->m_nWeight == nWeight, E_FAIL) ;
	this->m_nWeight = nWeight ;
	this->m_bFontAttrChange = TRUE ;
	return S_OK ;
}

HRESULT CCUIFont::GetWeight(INT* pnWeight)
{
	DEBUG_ASSERT(pnWeight) ;
	IF_RETURN(NULL == pnWeight, E_INVALIDARG) ;
	*pnWeight = this->m_nWeight ;
	return S_OK ;
}

HRESULT CCUIFont::SetItalic(BOOL bItatic)
{
	IF_RETURN(this->m_bItatic == bItatic, E_FAIL) ;
	this->m_bItatic = bItatic ;
	this->m_bFontAttrChange = TRUE ;
	return S_OK ;
}

HRESULT CCUIFont::GetItalic(BOOL* pbItatic)
{
	DEBUG_ASSERT(pbItatic) ;
	IF_RETURN(NULL == pbItatic, E_INVALIDARG) ;
	*pbItatic = this->m_bItatic ;
	return S_OK ;
}

HRESULT CCUIFont::SetStrikout(BOOL bStrikeout)
{
	IF_RETURN(this->m_bStrikeout == bStrikeout, E_FAIL) ;
	this->m_bStrikeout = bStrikeout ;
	this->m_bFontAttrChange = TRUE ;
	return S_OK ;
}

HRESULT CCUIFont::GetStrikeout(BOOL* pbStrikeout)
{
	DEBUG_ASSERT(pbStrikeout) ;
	IF_RETURN(NULL == pbStrikeout, E_INVALIDARG) ;
	*pbStrikeout = this->m_bStrikeout ;
	return S_OK ;
}

HRESULT CCUIFont::SetUnderline(BOOL bUnderline)
{
	IF_RETURN(this->m_bUnderline == bUnderline, E_FAIL) ;
	this->m_bUnderline = bUnderline ;
	this->m_bFontAttrChange = TRUE ;
	return S_OK ;
}

HRESULT CCUIFont::GetUnderline(BOOL* pbUnderline)
{
	DEBUG_ASSERT(pbUnderline) ;
	IF_RETURN(NULL == pbUnderline, E_INVALIDARG) ;
	*pbUnderline = this->m_bUnderline ;
	return S_OK ;
}

HRESULT CCUIFont::SetOutPrecision(BYTE cOutPrecision)
{
	IF_RETURN(this->m_cOutPrecision == cOutPrecision, E_FAIL) ;
	this->m_cOutPrecision = cOutPrecision ;
	this->m_bFontAttrChange = TRUE ;
	return S_OK ;
}

HRESULT CCUIFont::GetOutPrecision(BYTE* pcOutPrecision)
{
	DEBUG_ASSERT(pcOutPrecision) ;
	IF_RETURN(NULL == pcOutPrecision, E_INVALIDARG) ;
	*pcOutPrecision = this->m_cOutPrecision ;
	return S_OK ;
}

HRESULT CCUIFont::SetClipPrecision(BYTE cClipPrecision)
{
	IF_RETURN(this->m_cClipPrecision == cClipPrecision, E_FAIL) ;
	this->m_cClipPrecision = cClipPrecision ;
	this->m_bFontAttrChange = TRUE ;
	return S_OK ;
}

HRESULT CCUIFont::GetClipPrecision(BYTE* pcClipPrecision)
{
	DEBUG_ASSERT(pcClipPrecision) ;
	IF_RETURN(NULL == pcClipPrecision, E_INVALIDARG) ;
	*pcClipPrecision = this->m_cClipPrecision ;
	return S_OK ;
}

HRESULT CCUIFont::SetQuality(BYTE cQuality)
{
	IF_RETURN(this->m_cQuality == cQuality, E_FAIL) ;
	this->m_cQuality = cQuality ;
	this->m_bFontAttrChange = TRUE ;
	return S_OK ;
}

HRESULT CCUIFont::GetQuality(BYTE* pcQuality)
{
	DEBUG_ASSERT(pcQuality) ;
	IF_RETURN(NULL == pcQuality, E_INVALIDARG) ;
	*pcQuality = this->m_cQuality ;
	return S_OK ;
}

HRESULT CCUIFont::SetOrientation(INT nOrientation)
{
	IF_RETURN(this->m_nOrientation == nOrientation, E_FAIL) ;
	this->m_nOrientation = nOrientation ;
	this->m_bFontAttrChange = TRUE ;
	return S_OK ;
}

HRESULT CCUIFont::GetOrientation(INT* pnOrientation)
{
	DEBUG_ASSERT(pnOrientation) ;
	IF_RETURN(NULL == pnOrientation, E_INVALIDARG) ;
	*pnOrientation = this->m_nOrientation ;
	return S_OK ;
}

HRESULT CCUIFont::SetFacename(BSTR bstrFacename)
{
	IF_RETURN(this->m_cstrFacename == CString(bstrFacename), E_FAIL) ;
	this->m_cstrFacename = bstrFacename ;
	this->m_bFontAttrChange = TRUE ;
	return S_OK ;
}

HRESULT CCUIFont::GetFacename(BSTR* pbstrFacename)
{
	DEBUG_ASSERT(pbstrFacename) ;
	IF_RETURN(NULL == pbstrFacename, E_INVALIDARG) ;
	CComBSTR bstrStr(this->m_cstrFacename) ;
	bstrStr.CopyTo(pbstrFacename) ;
	return S_OK ;
}

HRESULT CCUIFont::SetCharset(BYTE cCharset)
{
	IF_RETURN(this->m_cCharset == cCharset, E_FAIL) ;
	this->m_cCharset = cCharset ;
	this->m_bFontAttrChange = TRUE ;
	return S_OK ;
}

HRESULT CCUIFont::GetCharset(BYTE* pcCharset)
{
	DEBUG_ASSERT(pcCharset) ;
	IF_RETURN(NULL == pcCharset, E_INVALIDARG) ;
	*pcCharset = this->m_cCharset ;
	return S_OK ;
}

HRESULT CCUIFont::SetPitchAndFamily(BYTE cPitchAndFamily)
{
	IF_RETURN(this->m_cPitchAndFamily == cPitchAndFamily, E_FAIL) ;
	this->m_cPitchAndFamily = cPitchAndFamily ;
	this->m_bFontAttrChange = TRUE ;
	return S_OK ;
}

HRESULT CCUIFont::GetPitchAndFamily(BYTE* pcPitchAndFamily)
{
	DEBUG_ASSERT(pcPitchAndFamily) ;
	IF_RETURN(NULL == pcPitchAndFamily, E_INVALIDARG) ;
	*pcPitchAndFamily = this->m_cPitchAndFamily ;
	return S_OK ;
}

HRESULT CCUIFont::SetDrawType(DWORD dwDrawType)
{
	this->m_dwDrawType = dwDrawType ;
	return S_OK ;
}

HRESULT CCUIFont::SetDrawType(BSTR bstrDrawType)
{
	CString cstrDrawType(bstrDrawType) ;
	if (0 == cstrDrawType.CompareNoCase(_T("DRAW_DEFAULT")))
	{
		return this->SetDrawType(FONT_DRAW::DRAW_DEFAULT) ;
	}
	else if (0 == cstrDrawType.CompareNoCase(_T("DRAW_SINGLEBITPERPIXELGRIDFIT")))
	{
		return this->SetDrawType(FONT_DRAW::DRAW_SINGLEBITPERPIXELGRIDFIT) ;
	}
	else if (0 == cstrDrawType.CompareNoCase(_T("DRAW_SINGLEBITPERPIXEL")))
	{
		return this->SetDrawType(FONT_DRAW::DRAW_SINGLEBITPERPIXEL) ;
	}
	else if (0 == cstrDrawType.CompareNoCase(_T("DRAW_ANTIALIASGRIDFIT")))
	{
		return this->SetDrawType(FONT_DRAW::DRAW_ANTIALIASGRIDFIT) ;
	}
	else if (0 == cstrDrawType.CompareNoCase(_T("DRAW_ANTIALIAS")))
	{
		return this->SetDrawType(FONT_DRAW::DRAW_ANTIALIAS) ;
	}
	else if (0 == cstrDrawType.CompareNoCase(_T("DRAW_CLEARTYPEGRIDFIT")))
	{
		return this->SetDrawType(FONT_DRAW::DRAW_CLEARTYPEGRIDFIT) ;
	}
	return E_FAIL ;
}

HRESULT CCUIFont::GetDrawType(DWORD* pdwDrawType)
{
	DEBUG_ASSERT(pdwDrawType) ;
	IF_RETURN(NULL == pdwDrawType, E_INVALIDARG) ;

	*pdwDrawType = this->m_dwDrawType ;
	return S_OK ;
}

HRESULT CCUIFont::GetLogFont(LOGFONT* pLogFont)
{
	DEBUG_ASSERT(pLogFont) ;
	IF_RETURN(NULL == pLogFont, E_INVALIDARG) ;
	pLogFont->lfHeight          = this->m_nFontHeight ;
	pLogFont->lfWidth           = this->m_nFontWidth ;
	pLogFont->lfEscapement      = this->m_nEscapement ;
	pLogFont->lfOrientation     = this->m_nOrientation ;
	pLogFont->lfWeight          = this->m_nWeight ;
	pLogFont->lfItalic          = this->m_bItatic ;
	pLogFont->lfUnderline       = this->m_bUnderline ;
	pLogFont->lfStrikeOut       = this->m_bStrikeout ;
	pLogFont->lfCharSet         = this->m_cCharset ;
	pLogFont->lfOutPrecision    = this->m_cOutPrecision ;
	pLogFont->lfClipPrecision   = this->m_cClipPrecision ;
	pLogFont->lfQuality         = this->m_cQuality ;
	pLogFont->lfPitchAndFamily  = this->m_cPitchAndFamily ;

	memset(pLogFont->lfFaceName, 0, sizeof(WCHAR) * LF_FACESIZE) ;
	wcsncpy_s(pLogFont->lfFaceName, this->m_cstrFacename, this->m_cstrFacename.GetLength()) ; 

	return S_OK ;
}


HRESULT CCUIFont::GetHFont(HFONT* phFont)
{
	DEBUG_ASSERT_MSG(phFont, _T("phFont == NULL")) ;
	IF_RETURN(NULL == phFont, E_INVALIDARG) ;
	if (this->m_bFontAttrChange)
	{
		if (this->m_hFont)
		{
			::DeleteObject(this->m_hFont) ;
			this->m_hFont = NULL ;
		}

		this->m_hFont = ::CreateFont(this->m_nFontHeight,
			this->m_nFontWidth, this->m_nEscapement, this->m_nOrientation,
			this->m_nWeight, this->m_bItatic, this->m_bUnderline, this->m_bStrikeout,
			this->m_cCharset, this->m_cOutPrecision, this->m_cClipPrecision,
			this->m_cQuality, this->m_cPitchAndFamily, this->m_cstrFacename) ;
		this->m_bFontAttrChange = FALSE ;
	}

	*phFont = this->m_hFont ;
	return S_OK ;
}

HRESULT CCUIFont::CloneFont(IUIFont* pFont)
{
	DEBUG_ASSERT(pFont) ;
	IF_RETURN(NULL == pFont, E_INVALIDARG) ;

	LOGFONT _log_font ;
	pFont->GetLogFont(&_log_font) ;

	this->m_nFontHeight     = (INT)_log_font.lfHeight ;
	this->m_nFontWidth      = (INT)_log_font.lfWidth ;
	this->m_nEscapement     = (INT)_log_font.lfEscapement ;
	this->m_nOrientation    = (INT)_log_font.lfOrientation ;
	this->m_nWeight         = (INT)_log_font.lfWeight ;
	this->m_bItatic         = (BOOL)_log_font.lfItalic ;
	this->m_bUnderline      = (BOOL)_log_font.lfUnderline ;
	this->m_bStrikeout      = (BOOL)_log_font.lfStrikeOut ;
	this->m_cCharset        = (BYTE)_log_font.lfCharSet ;
	this->m_cOutPrecision   = (BYTE)_log_font.lfOutPrecision ;
	this->m_cClipPrecision  = (BYTE)_log_font.lfClipPrecision ;
	this->m_cQuality        = (BYTE)_log_font.lfQuality ;
	this->m_cPitchAndFamily = (BYTE)_log_font.lfPitchAndFamily ;
	this->m_bFontAttrChange = TRUE ;

	pFont->GetDrawType(&m_dwDrawType) ;
	return S_OK ;
}

HRESULT CCUIFont::SetAttribute(ICVarData* pAttrData)
{
	SET_ATTR_CLASS_BEGIN    (pAttrData, CCUIFont)
	SET_ATTR_INT            (Width)
	SET_ATTR_INT            (Height)
	SET_ATTR_INT            (Escapement)
	SET_ATTR_INT            (Weight)
	SET_ATTR_BOOL           (Italic)
	SET_ATTR_BOOL           (Strikout)
	SET_ATTR_BOOL           (Underline)
	SET_ATTR_BYTE           (OutPrecision)
	SET_ATTR_BYTE           (ClipPrecision)
	SET_ATTR_BYTE           (Quality)
	SET_ATTR_INT            (Orientation)
	SET_ATTR_BSTR           (Facename)
	SET_ATTR_BYTE           (Charset)
	SET_ATTR_BYTE           (PitchAndFamily)
	SET_ATTR_DWORD          (DrawType)
	SET_ATTR_END            ()
	return S_OK ;
}