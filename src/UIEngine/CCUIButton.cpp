#include "stdafx.h"
#include "CCUIButton.h"

CCUIButton::CCUIButton()
{
	this->m_clrNormalColor = RGB(0, 0, 0) ;
	this->m_clrHighlightColor = RGB(0, 0, 0) ;
	this->m_clrPushedColor = RGB(0, 0, 0) ;
	this->m_clrDisableColor = RGB(0, 0, 0) ;
}

CCUIButton::~CCUIButton()
{

}

HRESULT CCUIButton::FinalConstruct()
{
	Common::Util::CreateObject(&m_pTextFont) ;
	DEBUG_ASSERT(m_pTextFont) ;
	Common::Util::CreateObject(&m_pTextRender) ;
	DEBUG_ASSERT(m_pTextRender) ;
	__self->SetEnableState(TRUE) ;

	if (this->m_pTextRender)
	{
		this->m_pTextRender->SetFont(m_pTextFont) ;
	}
	return S_OK ;
}

HRESULT CCUIButton::SetFont(IUIFont* pFont)
{
	DEBUG_ASSERT(pFont) ;
	IF_RETURN(NULL == pFont, E_INVALIDARG) ;
	
	this->m_pTextFont = pFont ;
	if (this->m_pTextRender)
	{
		this->m_pTextRender->SetFont(pFont) ;
		GetEntity<IUIFrameInternal>()->MarkReCalcsize() ;
		__self->Invalidate() ;
	}
	return S_OK ;
}

HRESULT CCUIButton::GetFont(IUIFont** ppFont)
{
	DEBUG_ASSERT(ppFont) ;
	IF_RETURN(NULL == ppFont, E_INVALIDARG) ;
	*ppFont = NULL ;

	if (this->m_pTextFont)
	{
		return this->m_pTextFont->QueryInterface(__uuidof(IUIFont), (VOID**)ppFont) ;
	}
	return E_FAIL ;
}

HRESULT CCUIButton::SetText(BSTR bstrText)
{
	this->m_strText = bstrText ;
	GetEntity<IUIFrameInternal>()->MarkReCalcsize() ;
	__self->Invalidate() ;
	return S_OK ;
}

HRESULT CCUIButton::GetText(BSTR* pbstrText)
{
	DEBUG_ASSERT(pbstrText) ;
	IF_RETURN(NULL == pbstrText, E_INVALIDARG) ;

	CComBSTR _bstrText(m_strText) ;
	_bstrText.CopyTo(pbstrText) ;
	return S_OK ;
}

HRESULT CCUIButton::SetTextNormalColor(COLORREF clr)
{
	IF_RETURN(this->m_clrNormalColor == clr, S_OK) ;
	this->m_clrNormalColor = clr ;
	__self->Invalidate() ;
	return S_OK ;
}

HRESULT CCUIButton::GetTextNormalColor(COLORREF* pclr)
{
	DEBUG_ASSERT(pclr) ;
	IF_RETURN(NULL == pclr, E_INVALIDARG) ;

	*pclr = this->m_clrNormalColor ;
	return S_OK ;
}

HRESULT CCUIButton::SetTextHighlightColor(COLORREF clr)
{
	IF_RETURN(this->m_clrHighlightColor == clr, S_OK) ;
	this->m_clrHighlightColor = clr ;
	__self->Invalidate() ;
	return S_OK ;
}

HRESULT CCUIButton::GetTextHighlightColor(COLORREF* pclr)
{
	DEBUG_ASSERT(pclr) ;
	IF_RETURN(NULL == pclr, E_INVALIDARG) ;

	*pclr = this->m_clrHighlightColor ;
	return S_OK ;
}

HRESULT CCUIButton::SetTextPushedColor(COLORREF clr)
{
	IF_RETURN(this->m_clrPushedColor == clr, S_OK) ;
	this->m_clrPushedColor = clr ;
	__self->Invalidate() ;
	return S_OK ;
}

HRESULT CCUIButton::GetTextPushedColor(COLORREF* pclr)
{
	DEBUG_ASSERT(pclr) ;
	IF_RETURN(NULL == pclr, E_INVALIDARG) ;

	*pclr = this->m_clrPushedColor ;
	return S_OK ;
}

HRESULT CCUIButton::SetTextDisableColor(COLORREF clr)
{
	IF_RETURN(this->m_clrDisableColor == clr, S_OK) ;
	this->m_clrDisableColor = clr ;
	__self->Invalidate() ;
	return S_OK ;
}

HRESULT CCUIButton::GetTextDisableColor(COLORREF* pclr)
{
	DEBUG_ASSERT(pclr) ;
	IF_RETURN(NULL == pclr, E_INVALIDARG) ;

	*pclr = this->m_clrDisableColor ;
	return S_OK ;
}

HRESULT CCUIButton::SetNormalBkgDraw(IUIDraw* pNormalDraw)
{
	IF_RETURN(this->m_pNormalDraw == pNormalDraw, S_OK) ;

	this->m_pNormalDraw = pNormalDraw ;
	INT _nState = STATE::NORMAL ;
	__self->GetState(&_nState) ;
	if (STATE::NORMAL == _nState)
	{
		__self->Invalidate() ;
	}
	return S_OK ;
}

HRESULT CCUIButton::GetNormalBkgDraw(IUIDraw** ppNormalDraw)
{
	DEBUG_ASSERT(ppNormalDraw) ;
	IF_RETURN(NULL == ppNormalDraw, E_INVALIDARG) ;

	*ppNormalDraw = NULL ;
	if (this->m_pNormalDraw)
	{
		return this->m_pNormalDraw->QueryInterface(__uuidof(IUIDraw), (VOID**)ppNormalDraw) ;
	}
	return E_FAIL ;
}

HRESULT CCUIButton::SetHighlightBkgDraw(IUIDraw* pHighlightDraw)
{
	IF_RETURN(this->m_pHighlightDraw == pHighlightDraw, S_OK) ;

	this->m_pHighlightDraw = pHighlightDraw ;
	INT _nState = STATE::NORMAL ;
	__self->GetState(&_nState) ;
	if (STATE::HIGHLIGHT == _nState)
	{
		__self->Invalidate() ;
	}
	return S_OK ;
}

HRESULT CCUIButton::GetHighlightBkgDraw(IUIDraw** ppHighlightDraw)
{
	DEBUG_ASSERT(ppHighlightDraw) ;
	IF_RETURN(NULL == ppHighlightDraw, E_INVALIDARG) ;

	*ppHighlightDraw = NULL ;
	if (this->m_pHighlightDraw)
	{
		return this->m_pHighlightDraw->QueryInterface(__uuidof(IUIDraw), (VOID**)ppHighlightDraw) ;
	}
	return E_FAIL ;
}

HRESULT CCUIButton::SetPushedBkgDraw(IUIDraw* pPushedDraw)
{
	IF_RETURN(this->m_pPushedDraw == pPushedDraw, S_OK) ;

	this->m_pPushedDraw = pPushedDraw ;
	INT _nState = STATE::NORMAL ;
	__self->GetState(&_nState) ;
	if (STATE::PUSHED == _nState)
	{
		__self->Invalidate() ;
	}
	return S_OK ;
}

HRESULT CCUIButton::GetPushedBkgDraw(IUIDraw** ppPushedDraw)
{
	DEBUG_ASSERT(ppPushedDraw) ;
	IF_RETURN(NULL == ppPushedDraw, E_INVALIDARG) ;

	*ppPushedDraw = NULL ;
	if (this->m_pPushedDraw)
	{
		return this->m_pPushedDraw->QueryInterface(__uuidof(IUIDraw), (VOID**)ppPushedDraw) ;
	}
	return E_FAIL ;
}

HRESULT CCUIButton::SetDisableBkgDraw(IUIDraw* pDisableDraw)
{
	IF_RETURN(this->m_pDisableDraw == pDisableDraw, S_OK) ;

	this->m_pDisableDraw = pDisableDraw ;
	INT _nState = STATE::NORMAL ;
	__self->GetState(&_nState) ;
	if (STATE::DISABLE == _nState)
	{
		__self->Invalidate() ;
	}
	return S_OK ;
}

HRESULT CCUIButton::GetDisableBkgDraw(IUIDraw** ppDisableDraw)
{
	DEBUG_ASSERT(ppDisableDraw) ;
	IF_RETURN(NULL == ppDisableDraw, E_INVALIDARG) ;

	*ppDisableDraw = NULL ;
	if (this->m_pDisableDraw)
	{
		return this->m_pPushedDraw->QueryInterface(__uuidof(IUIDraw), (VOID**)ppDisableDraw) ;
	}
	return E_FAIL ;
}

HRESULT CCUIButton::OnMessage(IUIFrame* pTarget, tMsgArg* pArg)
{
	__super::OnMessage(pTarget, pArg) ;
	if (pArg && MESSAGE::UI_LBTNCLICK == pArg->dwMsgId)
	{
		__self->RaiseEvent(UI::EVENT::BUTTON_CLICK, NULL) ;
	}
	return S_OK ;
}

HRESULT CCUIButton::CalcSize(SIZE szOld, SIZE* pszCalcOut)
{
	DEBUG_ASSERT(pszCalcOut) ;
	IF_RETURN(NULL == pszCalcOut, E_INVALIDARG) ;

	CRect _rcPadding(0, 0, 0, 0) ;
	__self->GetPadding(&_rcPadding) ;

	CSize _szButtonSize(0, 0) ;
	_szButtonSize.cx = _rcPadding.left + _rcPadding.right ;
	_szButtonSize.cy = _rcPadding.top + _rcPadding.bottom ;

	CSize _szStringSize(0, 0) ;
	if (this->m_pTextRender)
	{
		this->m_pTextRender->CalcTextSize(CComBSTR(m_strText), CSize(0, 0), &_szStringSize) ;
	}
	_szButtonSize.cx += _szStringSize.cx ;
	_szButtonSize.cy += _szStringSize.cy ;
	*pszCalcOut = _szButtonSize ;

	return S_OK ;

}
HRESULT CCUIButton::Render(IUICanvas* pCanvas, RECT rcRender, INT nState)
{
	DEBUG_ASSERT(pCanvas) ;
	IF_RETURN(NULL == pCanvas, E_INVALIDARG) ;
	__super::Render(pCanvas, rcRender, nState) ;

	CRect _rcTargetRender = rcRender ;
	CRect _rcPadding(0, 0, 0, 0) ;
	__self->GetPadding(&_rcPadding) ;

	_rcTargetRender.left	+= _rcPadding.left ;
	_rcTargetRender.top		+= _rcPadding.top ;
	_rcTargetRender.right	-= _rcPadding.right ;
	_rcTargetRender.bottom	-= _rcPadding.bottom ;

	BYTE _cShowAlpha = 255 ;
	__self->GetShowAlpha(&_cShowAlpha) ;
	switch(nState)
	{
	case STATE::NORMAL:
		if (this->m_pNormalDraw)
		{
			this->m_pNormalDraw->DrawOnCanvas(pCanvas, rcRender, _cShowAlpha) ;
		}

		if (this->m_pTextRender)
		{
			this->m_pTextRender->DrawOnCanvas(pCanvas, CComBSTR(m_strText), _rcTargetRender, this->m_clrNormalColor, _cShowAlpha) ;
		}
		break ;

	case STATE::HIGHLIGHT:
		if (this->m_pHighlightDraw)
		{
			this->m_pHighlightDraw->DrawOnCanvas(pCanvas, rcRender, _cShowAlpha) ;
		}

		if (this->m_pTextRender)
		{
			this->m_pTextRender->DrawOnCanvas(pCanvas, CComBSTR(m_strText), _rcTargetRender, this->m_clrHighlightColor, _cShowAlpha) ;
		}
		break ;

	case STATE::PUSHED:
		if (this->m_pPushedDraw)
		{
			this->m_pPushedDraw->DrawOnCanvas(pCanvas, rcRender, _cShowAlpha) ;
		}

		if (this->m_pTextRender)
		{
			this->m_pTextRender->DrawOnCanvas(pCanvas, CComBSTR(m_strText), _rcTargetRender, this->m_clrPushedColor, _cShowAlpha) ;
		}

		break ;

	case STATE::DISABLE:
		if (this->m_pDisableDraw)
		{
			this->m_pDisableDraw->DrawOnCanvas(pCanvas, rcRender, _cShowAlpha) ;
		}

		if (this->m_pTextRender)
		{
			this->m_pTextRender->DrawOnCanvas(pCanvas, CComBSTR(m_strText), _rcTargetRender, this->m_clrDisableColor, _cShowAlpha) ;
		}
		break ;
	}

	return S_OK ;
}

HRESULT CCUIButton::SetAttribute(ICVarData* pAttrData)
{
	__super::SetAttribute(pAttrData) ;

	SET_ATTR_CLASS_BEGIN    (pAttrData, IUIButton)
	SET_ATTR_INTERFACE      (IUIFont, Font)
	SET_ATTR_BSTR			(Text)
	SET_ATTR_COLORREF		(TextNormalColor)
	SET_ATTR_COLORREF		(TextHighlightColor)
	SET_ATTR_COLORREF		(TextPushedColor)
	SET_ATTR_COLORREF		(TextDisableColor)
	SET_ATTR_INTERFACE      (IUIDraw, NormalBkgDraw)
	SET_ATTR_INTERFACE      (IUIDraw, HighlightBkgDraw)
	SET_ATTR_INTERFACE      (IUIDraw, PushedBkgDraw)
	SET_ATTR_INTERFACE      (IUIDraw, DisableBkgDraw)
	SET_ATTR_END            ()

	return S_OK ;
}