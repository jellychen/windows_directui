#include "stdafx.h"
#include "CCUIStatic.h"
#include "CCUIStackBlurAlgorithm.h"

CCUIStatic::CCUIStatic()
{
	this->m_bMutilLine  = FALSE ;
	this->m_clrText     = RGB(0, 0, 0) ;
}

CCUIStatic::~CCUIStatic()
{
}

HRESULT CCUIStatic::FinalConstruct()
{
	Common::Util::CreateObject(&m_pTextRender) ;
	DEBUG_ASSERT(m_pTextRender) ;

	Common::Util::CreateObject(&m_pTextFont) ;
	DEBUG_ASSERT(m_pTextFont) ;

	if (this->m_pTextRender)
	{
		this->m_pTextRender->SetLineLimit(TRUE) ;
		this->m_pTextRender->SetTrimming(TEXT::TRIM_CHAR) ;
		this->m_pTextRender->SetFont(m_pTextFont) ;
		this->m_pTextRender->SetAlignment(TEXT::ALI_NEAR) ;
		this->m_pTextRender->SetLineAlignment(TEXT::ALI_NEAR) ;
	}
	__self->SetAutoCapture(FALSE) ;

	return S_OK ;
}

HRESULT CCUIStatic::SetText(BSTR bstrText)
{
	IF_RETURN(CString(bstrText) == this->m_cstrText, S_OK) ;
	this->m_cstrText = CString(bstrText) ;
	GetEntity<IUIFrameInternal>()->MarkReCalcsize() ;
	__self->Invalidate() ;
	return S_OK ;
}

HRESULT CCUIStatic::GetText(BSTR* pbstrText)
{
	DEBUG_ASSERT(pbstrText) ;
	IF_RETURN(NULL == pbstrText, E_INVALIDARG) ;

	CComBSTR bstrText(this->m_cstrText) ;
	return bstrText.CopyTo(pbstrText) ;
}

HRESULT CCUIStatic::SetFont(IUIFont* pFont)
{
	DEBUG_ASSERT(pFont) ;
	IF_RETURN(NULL == pFont || NULL == this->m_pTextFont, E_INVALIDARG) ;

	this->m_pTextFont->CloneFont(pFont) ;
	if (this->m_pTextRender)
	{
		this->m_pTextRender->SetFont(pFont) ;
		GetEntity<IUIFrameInternal>()->MarkReCalcsize() ;
		__self->Invalidate() ;
	}

	return S_OK ;
}

HRESULT CCUIStatic::GetFont(IUIFont** ppFont)
{
	DEBUG_ASSERT(ppFont) ;
	IF_RETURN(NULL == ppFont, E_INVALIDARG) ;
	*ppFont = NULL ;

	if (this->m_pTextFont)
	{
		return this->m_pTextFont->QueryInterface(__uuidof(IUIFont), (VOID**)ppFont) ;
	}
	return S_OK ;
}

HRESULT CCUIStatic::SetMutiLine(BOOL bMutiLine)
{
	this->m_bMutilLine = bMutiLine ;
	if (this->m_pTextRender)
	{
		this->m_pTextRender->SetLineLimit(!m_bMutilLine) ;
	}
	return S_OK ;
}

HRESULT CCUIStatic::GetMutiLine(BOOL* pbMutiLine)
{
	DEBUG_ASSERT(pbMutiLine) ;
	IF_RETURN(NULL == pbMutiLine, E_INVALIDARG) ;
	*pbMutiLine = this->m_bMutilLine ;
	return S_OK ;
}

HRESULT CCUIStatic::SetTextColor(COLORREF clr)
{
	this->m_clrText = clr ;
	return S_OK ;
}

HRESULT CCUIStatic::GetTextColor(COLORREF* pclr)
{
	DEBUG_ASSERT(pclr) ;
	IF_RETURN(NULL == pclr, E_INVALIDARG) ;

	*pclr = this->m_clrText ;
	return S_OK ;
}

HRESULT CCUIStatic::CalcSize(SIZE szOld, SIZE* pszCalcOut)
{
	DEBUG_ASSERT(pszCalcOut) ;
	IF_RETURN(NULL == pszCalcOut, E_INVALIDARG) ;
	*pszCalcOut = szOld ;

	BOOL bAutoWidth = FALSE ;
	__self->GetAutoWidth(&bAutoWidth) ;
	if (bAutoWidth)
	{
		szOld.cx = -1 ;
	}

	BOOL bAutoHight = FALSE ;
	__self->GetAutoHeight(&bAutoHight) ;
	if (bAutoHight)
	{
		szOld.cy = -1 ;
	}

	CRect rcPadding ;
	__self->GetPadding(&rcPadding) ;

	if (FALSE == this->m_bMutilLine)
	{
		szOld.cx = INT_MAX ;
	}

	CSize szCalcSize(0, 0) ;
	if (this->m_pTextRender)
	{
		this->m_pTextRender->CalcTextSize(CComBSTR(m_cstrText), szOld, &szCalcSize) ;
	}

	if (bAutoWidth)
	{
		pszCalcOut->cx = szCalcSize.cx + rcPadding.left + rcPadding.right ;
	}

	if (bAutoHight)
	{
		pszCalcOut->cy = szCalcSize.cy + rcPadding.top + rcPadding.bottom ;
	}
	return E_FAIL ;
}

HRESULT CCUIStatic::Render(IUICanvas* pCanvas, RECT rcRender, INT nState)
{
	HRESULT hRet = __super::Render(pCanvas, rcRender, nState) ;

	CRect rcPadding ;
	__self->GetPadding(&rcPadding) ;

	CRect rcTarget  = rcRender ;
	rcTarget.left   = rcRender.left + rcPadding.left ;
	rcTarget.top    = rcRender.top + rcPadding.top ;
	rcTarget.right  = rcRender.right - rcPadding.right ;
	rcTarget.bottom = rcRender.bottom - rcPadding.bottom ;

	if (this->m_pTextRender)
	{
		BYTE cShowAlpha = 255 ;
		__self->GetShowAlpha(&cShowAlpha) ;
		this->m_pTextRender->DrawOnCanvas(pCanvas, CComBSTR(m_cstrText), rcTarget, m_clrText, cShowAlpha) ;
	}
	return hRet ;
}

HRESULT CCUIStatic::SetAttribute(ICVarData* pAttrData)
{
	HRESULT hRet = __super::SetAttribute(pAttrData) ;
	SET_ATTR_INTERFACE_BEGIN(pAttrData, IUIStatic)
	SET_ATTR_BSTR           (Text)
	SET_ATTR_INTERFACE      (IUIFont, Font)
	SET_ATTR_BOOL           (MutiLine)
	SET_ATTR_COLORREF       (TextColor)
	SET_ATTR_END            ()
	return hRet ;
}