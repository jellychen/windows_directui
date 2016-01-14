#include "stdafx.h"
#include "CCUIListItem.h"

CCUIListItem::CCUIListItem()
{
	this->m_bSelected = FALSE ;
}

CCUIListItem::~CCUIListItem()
{

}

HRESULT CCUIListItem::SetHostList(IUIElement* pHostList)
{
	this->m_pHostList = pHostList ;
	return S_OK ;
}

HRESULT CCUIListItem::SetSelected(BOOL bSelected)
{
	if (this->m_bSelected != bSelected)
	{
		__self->Invalidate() ;
	}
	this->m_bSelected = bSelected ;
	return S_OK ;
}

HRESULT CCUIListItem::GetSelected(BOOL* pbSelected)
{
	DEBUG_ASSERT(pbSelected) ;
	IF_RETURN(NULL == pbSelected, E_INVALIDARG) ;

	*pbSelected = this->m_bSelected ;
	return S_OK ;
}

HRESULT CCUIListItem::SetNormalDraw(IUIDraw* pNormalDraw)
{
	INT nState = STATE::NORMAL ;
	__self->GetState(&nState) ;

	if (!this->m_bSelected && nState == STATE::NORMAL && this->m_pNormalDraw != pNormalDraw)
	{
		__self->Invalidate() ;
	}
	this->m_pNormalDraw = pNormalDraw ;
	return S_OK ;
}

HRESULT CCUIListItem::GetNormalDraw(IUIDraw** ppNormalDraw)
{
	DEBUG_ASSERT(ppNormalDraw) ;
	IF_RETURN(NULL == ppNormalDraw, E_INVALIDARG) ;
	*ppNormalDraw = NULL ;

	if (this->m_pNormalDraw)
	{
		this->m_pNormalDraw->QueryInterface(__uuidof(IUIDraw), (void**)ppNormalDraw) ;
	}
	return S_OK ;
}

HRESULT CCUIListItem::SetHighlightDraw(IUIDraw* pHighlightDraw)
{
	INT nState = STATE::NORMAL ;
	__self->GetState(&nState) ;
	if (!this->m_bSelected && nState == STATE::HIGHLIGHT && this->m_pNormalDraw != pHighlightDraw)
	{
		__self->Invalidate() ;
	}
	this->m_pHighlightDraw = pHighlightDraw ;
	return S_OK ;
}

HRESULT CCUIListItem::GetHighlightDraw(IUIDraw** ppHighlightDraw)
{
	DEBUG_ASSERT(ppHighlightDraw) ;
	IF_RETURN(NULL == ppHighlightDraw, E_INVALIDARG) ;
	*ppHighlightDraw = NULL ;

	if (this->m_pHighlightDraw)
	{
		this->m_pHighlightDraw->QueryInterface(__uuidof(IUIDraw), (void**)ppHighlightDraw) ;
	}
	return S_OK ;
}

HRESULT CCUIListItem::SetDisableDraw(IUIDraw* pDisableDraw)
{
	INT nState = STATE::NORMAL ;
	__self->GetState(&nState) ;

	if (nState == STATE::DISABLE && this->m_pDisableDraw != pDisableDraw)
	{
		__self->Invalidate() ;
	}
	this->m_pDisableDraw = pDisableDraw ;
	return S_OK ;
}

HRESULT CCUIListItem::GetDisableDraw(IUIDraw** ppDisableDraw)
{
	DEBUG_ASSERT(ppDisableDraw) ;
	IF_RETURN(NULL == ppDisableDraw, E_INVALIDARG) ;
	*ppDisableDraw = NULL ;

	if (this->m_pDisableDraw)
	{
		this->m_pDisableDraw->QueryInterface(__uuidof(IUIDraw), (void**)ppDisableDraw) ;
	}
	return S_OK ;
}

HRESULT CCUIListItem::SetSelectedDraw(IUIDraw* pSelectedDraw)
{
	if (this->m_bSelected && this->m_pSelectedDraw != pSelectedDraw)
	{
		__self->Invalidate() ;
	}
	this->m_pSelectedDraw = pSelectedDraw ;
	return S_OK ;
}

HRESULT CCUIListItem::GetSelectedDraw(IUIDraw** ppSelectedDraw)
{
	DEBUG_ASSERT(ppSelectedDraw) ;
	IF_RETURN(NULL == ppSelectedDraw, E_INVALIDARG) ;
	*ppSelectedDraw = NULL ;

	if (this->m_pSelectedDraw)
	{
		this->m_pSelectedDraw->QueryInterface(__uuidof(IUIDraw), (void**)ppSelectedDraw) ;
	}
	return S_OK ;
}

HRESULT CCUIListItem::Render(IUICanvas* pCanvas, RECT rcRender, INT nState)
{
	return S_OK ;
}

HRESULT CCUIListItem::OnMessageRiase(IUIFrame* pTarget, tMsgArg* pArg, BOOL* pbIntercept)
{
	IF_RETURN(pArg == NULL, E_INVALIDARG) ;
	if (pArg->dwMsgId == MESSAGE::UI_LBTNCLICK && !this->m_bSelected)
	{
		__self->Invalidate() ;
		this->m_bSelected = TRUE ;
	}
	return S_OK ;
}