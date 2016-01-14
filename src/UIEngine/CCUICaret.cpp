#include "stdafx.h"
#include "CCUICaret.h"

CCUICaret::CCUICaret():m_pTimerCallbackPtr(this)
{
	this->m_bBlink = FALSE ;
	this->m_dwBlinkTime = 500 ;
	this->m_pTimerCallbackPtr->Hook_OnTimer(&CCUICaret::OnTimer) ;
}

CCUICaret::~CCUICaret()
{
	if (this->m_pTimerService)
	{
		this->m_pTimerService->Erase(this->m_pTimerCallbackPtr, 1) ;
	}
}

HRESULT CCUICaret::FinalConstruct()
{
	Common::Util::GetService(&m_pTimerService) ;
	DEBUG_ASSERT(m_pTimerService) ;
	CComPtr<IUIBrush> pBrush ;
	Common::Util::CreateObject(&pBrush) ;
	__self->SetHidden(TRUE) ;

	if (pBrush)
	{
		pBrush->SetColor(RGB(230, 230, 230)) ;
		pBrush->SetBrushType(BRUSH::RECT_FILL) ;
		this->m_pCaretDraw = pBrush ;
	}

	return S_OK ;
}

HRESULT CCUICaret::SetBlinkTime(DWORD dwBlink)
{
	IF_RETURN(this->m_dwBlinkTime == dwBlink, S_OK) ;

	this->m_dwBlinkTime = dwBlink ;
	if (this->m_bBlink)
	{
		__self->HideCaret() ;
		__self->ShowCaret() ;
	}
	return S_OK ;
}

HRESULT CCUICaret::GetBlinkTime(DWORD* pdwBlink)
{
	DEBUG_ASSERT(pdwBlink) ;
	IF_RETURN(NULL == pdwBlink, E_INVALIDARG) ;

	*pdwBlink = this->m_dwBlinkTime ;
	return S_OK ;
}

HRESULT CCUICaret::SetCaretDraw(IUIDraw* pDraw)
{
	IF_RETURN(this->m_pCaretDraw == pDraw, S_OK) ;

	this->m_pCaretDraw = pDraw ;
	return S_OK ;
}

HRESULT CCUICaret::GetCaretDraw(IUIDraw** ppDraw)
{
	DEBUG_ASSERT(ppDraw) ;
	IF_RETURN(NULL == ppDraw, E_INVALIDARG) ;
	*ppDraw = NULL ;

	if (this->m_pCaretDraw)
	{
		return this->m_pCaretDraw->QueryInterface(__uuidof(IUIDraw), (VOID**)ppDraw) ;
	}
	return S_OK ;
}

HRESULT CCUICaret::SetBlink(BOOL bBlink)
{
	IF_RETURN(this->m_bBlink == bBlink, S_OK) ;
	if (FALSE == bBlink)
	{
		this->m_pTimerService->Erase(m_pTimerCallbackPtr, 1) ;
	}
	else
	{
		this->m_pTimerService->SetInterval(m_pTimerCallbackPtr,m_dwBlinkTime, 1) ;
	}
	return S_OK ;
}

HRESULT CCUICaret::GetBlink(BOOL* bBlink)
{
	DEBUG_ASSERT(bBlink) ;
	IF_RETURN(NULL == bBlink, E_INVALIDARG) ;

	*bBlink = this->m_bBlink ;
	return S_OK ;
}

HRESULT CCUICaret::ShowCaret()
{
	IF_RETURN(this->m_bBlink, S_OK) ;
	this->m_bBlink = TRUE ;
	if (this->m_pTimerService)
	{
		return this->m_pTimerService->SetInterval(m_pTimerCallbackPtr,m_dwBlinkTime, 1) ;
	}
	return E_FAIL ;
}

HRESULT CCUICaret::HideCaret()
{
	IF_RETURN(FALSE == this->m_bBlink, S_OK) ;
	this->m_bBlink = FALSE ;
	if (this->m_pTimerService)
	{
		this->m_pTimerService->Erase(m_pTimerCallbackPtr, 1) ;
	}
	__self->SetHidden(TRUE) ;
	return S_OK ;
}

HRESULT CCUICaret::Render(IUICanvas* pCanvas, RECT rcRender, INT nState)
{
	HRESULT hRet = __super::Render(pCanvas, rcRender, nState) ;
	if (this->m_pCaretDraw)
	{
		BYTE cAlpha = 255 ;
		__self->GetShowAlpha(&cAlpha) ;

		this->m_pCaretDraw->DrawOnCanvas(pCanvas, rcRender, cAlpha) ;
	}
	return hRet ;
}

HRESULT CCUICaret::OnTimer(INT nTimerID)
{
	BOOL bHidden = FALSE ;
	__self->GetHidden(&bHidden) ;
	__self->SetHidden(!bHidden) ;
	return S_OK ;
}