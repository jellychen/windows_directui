#include "stdafx.h"
#include "CCUIAnimate.h"

CCUIAnimate::CCUIAnimate():m_pTimerCallback(this)
{
	this->m_nInterval	= 30 ;
	this->m_nCurrent	= 0 ;
	this->m_bForward	= TRUE ;
	this->m_pTimerCallback->Hook_OnTimer(&CCUIAnimate::OnTimer) ;
}

CCUIAnimate::~CCUIAnimate()
{
	if (this->m_pTimer)
	{
		this->m_pTimer->Erase(m_pTimerCallback, 1) ;
	}
}

HRESULT CCUIAnimate::FinalConstruct()
{
	Common::Util::GetService(&m_pTimer) ;
	DEBUG_ASSERT(m_pTimer) ;
	return S_OK ;
}

HRESULT CCUIAnimate::AddFrame(IUIDraw* pDraw)
{
	DEBUG_ASSERT(pDraw) ;
	IF_RETURN(NULL == pDraw, E_FAIL) ;

	this->m_vecDraw.push_back(pDraw) ;
	return S_OK ;
}

HRESULT CCUIAnimate::SetInterval(INT nInterval)
{
	this->m_nInterval = nInterval ;
	return S_OK ;
}

HRESULT CCUIAnimate::GetInterval(INT* pnInterval)
{
	DEBUG_ASSERT(pnInterval) ;
	IF_RETURN(NULL == pnInterval, E_INVALIDARG) ;

	*pnInterval = this->m_nInterval ;
	return S_OK ;
}

HRESULT	CCUIAnimate::DoForward(BOOL bForward)
{
	this->m_bForward = bForward ;
	if (this->m_pTimer)
	{
		this->m_pTimer->SetInterval(this->m_pTimerCallback, this->m_nInterval, 1) ;
	}
	return S_OK ;
}

HRESULT CCUIAnimate::Render(IUICanvas* pCanvas, RECT rcRender, INT nState)
{
	DEBUG_ASSERT(pCanvas) ;
	IF_RETURN(NULL == pCanvas, E_INVALIDARG) ;
	IF_RETURN(this->m_nCurrent < 0, E_FAIL) ;
	IF_RETURN(this->m_nCurrent >= (INT)this->m_vecDraw.size(), E_FAIL) ;

	if (this->m_vecDraw[this->m_nCurrent])
	{
		this->m_vecDraw[m_nCurrent]->DrawOnCanvas(pCanvas, rcRender, 255) ;
	}
	return S_OK ;
}

HRESULT CCUIAnimate::OnMessage(IUIFrame* pTarget, tMsgArg* pArg)
{
	__super::OnMessage(pTarget, pArg) ;
	IF_RETURN(NULL == pArg, E_INVALIDARG) ;
	if (MESSAGE::UI_MOUSEENTER == pArg->dwMsgId)
	{
		__self->DoForward(TRUE) ;
	}
	else if (MESSAGE::UI_MOUSELEAVE == pArg->dwMsgId)
	{
		__self->DoForward(FALSE) ;
	}
	return S_OK ;
}

HRESULT CCUIAnimate::OnTimer(INT nTimerId)
{
	DEBUG_ASSERT(this->m_pTimer) ;
	IF_RETURN(NULL == this->m_pTimer, E_FAIL) ;

	if (this->m_bForward)
	{
		this->m_nCurrent++ ;
		if (this->m_nCurrent >= (INT)this->m_vecDraw.size() - 1)
		{
			this->m_pTimer->Erase(m_pTimerCallback, 1) ;
			this->m_nCurrent = (INT)this->m_vecDraw.size() - 1 ;
		}
	}
	else
	{
		this->m_nCurrent-- ;
		if (0 >= this->m_nCurrent)
		{
			this->m_nCurrent = 0 ;
			this->m_pTimer->Erase(m_pTimerCallback, 1) ;
		}
	}
	__self->Invalidate() ;
	return S_OK ;
}