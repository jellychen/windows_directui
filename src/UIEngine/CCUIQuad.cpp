#include "stdafx.h"
#include "CCUIQuad.h"

CCUIQuad::CCUIQuad()
{
	this->m_pQuadRoot = NULL ;
}

CCUIQuad::~CCUIQuad()
{
	this->_free_quad_tree(this->m_pQuadRoot) ;
}

HRESULT CCUIQuad::FinalConstruct()
{
	CRect rcQuad(0, 0, QUAD_MAX_SIZE, QUAD_MAX_SIZE) ;
	this->m_pQuadRoot = _build_quad_tree(QUAD_DEPTH, rcQuad) ;
	return S_OK ;
}

HRESULT CCUIQuad::SynchFrame(RECT rcFrame, IUIFrame* pFrame)
{
	CRect _rcTarget(rcFrame) ;
	if (_rcTarget.IsRectEmpty())
	{
		return this->EraseFrame(pFrame) ;
	}

	BOOL bRet = this->_synch_frame(m_pQuadRoot, _rcTarget, pFrame) ;
	return bRet ? S_OK : E_FAIL ;
}

HRESULT CCUIQuad::GetFrameRect(IUIFrame* pFrame, RECT* prcRect)
{
	DEBUG_ASSERT(pFrame && prcRect) ;
	IF_RETURN(!(pFrame && prcRect), E_INVALIDARG) ;
	MAP_FRAME_RECR_POOL::iterator it = this->m_mapFrameRectPool.find((LONG)(pFrame)) ;
	IF_RETURN(this->m_mapFrameRectPool.end() == it, E_FAIL) ;

	*prcRect   = it->second ;
	return S_OK ;
}

HRESULT CCUIQuad::FrameFromPoint(POINT ptTarget, ICVarArray* pFrameArray)
{
	BOOL bRet = this->_find_frame_point(m_pQuadRoot, ptTarget, pFrameArray) ;
	return bRet ? S_OK : E_FAIL ;
}

HRESULT CCUIQuad::FrameFromPoint2(POINT ptTarget, IUIAddFrame* pAddFrame)
{
	DEBUG_ASSERT(pAddFrame) ;
	IF_RETURN(NULL == pAddFrame, E_INVALIDARG) ;

	pAddFrame->AddFrameBegin() ;
	this->_find_frame_point2(m_pQuadRoot, ptTarget, pAddFrame) ;
	pAddFrame->AddFrameEnd() ;
	return S_OK ;
}

HRESULT CCUIQuad::FrameFromRect(RECT rcTarget, ICVarArray* pFrameArray)
{
	BOOL bRet =  this->_find_frame_rect(m_pQuadRoot, CRect(rcTarget), pFrameArray) ;
	return bRet ? S_OK : E_FAIL ;
}

HRESULT CCUIQuad::FrameFromRect2(RECT rcTarget, IUIAddFrame* pAddFrame)
{
	DEBUG_ASSERT(pAddFrame) ;
	IF_RETURN(NULL == pAddFrame, E_INVALIDARG) ;

	pAddFrame->AddFrameBegin() ;
	this->_find_frame_rect2(m_pQuadRoot, CRect(rcTarget), pAddFrame) ;
	pAddFrame->AddFrameEnd() ;
	return S_OK ;
}

HRESULT CCUIQuad::EraseFrame(IUIFrame* pFrame)
{
	DEBUG_ASSERT(pFrame) ;
	IF_RETURN(NULL == pFrame, E_INVALIDARG) ;

	MAP_FRAME_POOL::iterator it = this->m_mapFramePool.find((LONG)(pFrame)) ;
	if (this->m_mapFramePool.end() != it)
	{
		CWeakPtr<IUIFrame> pFrameAgent = pFrame ;
		QUAD_NODE* pNode = it->second ;
		DEBUG_ASSERT(pNode) ;
		if (pNode)
		{
			VEC_QUAD_FRAME_POOL::iterator it_info = pNode->vecFramePool.begin() ;
			for (; it_info != pNode->vecFramePool.end(); ++it_info)
			{
				if (it_info->pFrameAgent == pFrameAgent)
				{
					pNode->vecFramePool.erase(it_info) ;
					break ;
				}
			}
		}

		this->m_mapFramePool.erase(it) ;
	}

	MAP_FRAME_RECR_POOL::iterator it_rect = this->m_mapFrameRectPool.find((LONG)(pFrame)) ;
	if (this->m_mapFrameRectPool.end() != it_rect)
	{
		this->m_mapFrameRectPool.erase(it_rect) ;
	}
	return S_OK ;
}

HRESULT CCUIQuad::Clear()
{
	BOOL bRet = this->_clear_quad_tree(m_pQuadRoot) ;
	this->m_mapFramePool.clear() ;
	this->m_mapFrameRectPool.clear() ;
	return bRet ? S_OK : E_FAIL ;
}

QUAD_NODE* CCUIQuad::_build_quad_tree(INT nDepth, CRect rcArea)
{
	IF_RETURN(1 > nDepth, NULL) ;

	QUAD_NODE* pNode = new QUAD_NODE() ;
	pNode->rcQuadNodeRect = rcArea ;

	if (nDepth > 1)
	{
		pNode->bHaveChildren = TRUE ;

		CRect rcLeftTop ;
		rcLeftTop.left      = rcArea.left ;
		rcLeftTop.top       = rcArea.top ;
		rcLeftTop.right     = rcArea.left + rcArea.Width()/2 ;
		rcLeftTop.bottom    = rcArea.top + rcArea.Height()/2 ;
		pNode->pQuadChildren[QUAD::LEFT_UP] = _build_quad_tree(nDepth-1, rcLeftTop) ;

		CRect rcRightTop ;
		rcRightTop.left    = rcArea.left + rcArea.Width()/2 + 1 ;
		rcRightTop.top     = rcArea.top ;
		rcRightTop.right   = rcArea.right ;
		rcRightTop.bottom  = rcArea.top + rcArea.Height()/2 + 1 ;
		pNode->pQuadChildren[QUAD::RIGHT_UP] = _build_quad_tree(nDepth-1, rcRightTop) ;

		CRect rcLeftBottom ;
		rcLeftBottom.left   = rcArea.left ;
		rcLeftBottom.top    = rcArea.top + rcArea.Height()/2 + 1 ;
		rcLeftBottom.right  = rcArea.left + rcArea.Width()/2 ;
		rcLeftBottom.bottom = rcArea.bottom ;
		pNode->pQuadChildren[QUAD::LEFT_BOTTOM] = _build_quad_tree(nDepth-1, rcLeftBottom) ;

		CRect rcRightBottom ;
		rcRightBottom.left  = rcArea.left + rcArea.Width()/2 + 1 ;
		rcRightBottom.right = rcArea.right ;
		rcRightBottom.top   = rcArea.top + rcArea.Height()/2 + 1 ;
		rcRightBottom.bottom= rcArea.bottom ;
		pNode->pQuadChildren[QUAD::RIGHT_BOTTOM] = _build_quad_tree(nDepth-1, rcRightBottom) ;

	}
	else
	{
		pNode->bHaveChildren = FALSE ;
		pNode->pQuadChildren[QUAD::LEFT_UP]         = NULL ;
		pNode->pQuadChildren[QUAD::RIGHT_UP]        = NULL ;
		pNode->pQuadChildren[QUAD::LEFT_BOTTOM]     = NULL ;
		pNode->pQuadChildren[QUAD::RIGHT_BOTTOM]    = NULL ;
	}

	return pNode ;
}

BOOL CCUIQuad::_free_quad_tree(QUAD_NODE* pQuadNode)
{
	IF_RETURN(NULL == pQuadNode, TRUE) ;
	for (INT i = 0; i < 4; ++i)
	{
		_free_quad_tree(pQuadNode->pQuadChildren[i]) ;
	}
	delete pQuadNode ;
	return TRUE ;
}

BOOL CCUIQuad::_clear_quad_tree(QUAD_NODE* pQuadNode)
{
	IF_RETURN(NULL == pQuadNode, TRUE) ;
	pQuadNode->vecFramePool.clear() ;
	pQuadNode->vecFramePool.swap(VEC_QUAD_FRAME_POOL()) ;
	for (INT i = 0; i < 4; ++i)
	{
		_clear_quad_tree(pQuadNode->pQuadChildren[i]) ;
	}
	return TRUE ;
}

BOOL CCUIQuad::_synch_frame(QUAD_NODE* pQuadNode, CRect& rcFrame, IUIFrame* pFrame)
{
	IF_RETURN(NULL == pQuadNode || NULL == pFrame, FALSE) ;
	if (pQuadNode->bHaveChildren)
	{
		for (INT i = 0; i < 4; ++i)
		{
			if (rcFrame.left > pQuadNode->pQuadChildren[i]->rcQuadNodeRect.left
				&& rcFrame.top > pQuadNode->pQuadChildren[i]->rcQuadNodeRect.top
				&& rcFrame.right < pQuadNode->pQuadChildren[i]->rcQuadNodeRect.right
				&& rcFrame.bottom < pQuadNode->pQuadChildren[i]->rcQuadNodeRect.bottom)
			{
				return _synch_frame(pQuadNode->pQuadChildren[i], rcFrame, pFrame) ;
			}
		}
	}

	this->EraseFrame(pFrame) ;
	this->m_mapFrameRectPool[(LONG)(pFrame)] = rcFrame ;

	CWeakPtr<IUIFrame> _frame_agent  = pFrame ;

	QUAD_FRAME_INFO _frame_info ;
	_frame_info.rcFrameRect = rcFrame ;
	_frame_info.pFrameAgent = _frame_agent ;

	pQuadNode->vecFramePool.push_back(_frame_info) ;
	this->m_mapFramePool[(LONG)(pFrame)] = pQuadNode ;

	return TRUE ;
}

BOOL CCUIQuad::_find_frame_point(QUAD_NODE* pQuadNode, POINT& ptTarget, ICVarArray* pFrameArray)
{
	IF_RETURN(NULL == pQuadNode || NULL == pFrameArray, FALSE) ;

	for (size_t i = 0; i < pQuadNode->vecFramePool.size(); ++i)
	{
		if (pQuadNode->vecFramePool[i].rcFrameRect.PtInRect(ptTarget))
		{
			CComPtr<IUIFrame> pFrame ;
			pQuadNode->vecFramePool[i].pFrameAgent.Promote(__uuidof(IUIFrame), (VOID**)&pFrame) ;
			DEBUG_ASSERT(pFrame) ;
			pFrameArray->AddInterface(pFrame) ;
		}
	}

	if (pQuadNode->bHaveChildren)
	{
		for (INT i = 0; i < 4; ++i)
		{
			if (pQuadNode->pQuadChildren[i]->rcQuadNodeRect.PtInRect(ptTarget))
			{
				return this->_find_frame_point(pQuadNode->pQuadChildren[i], ptTarget, pFrameArray) ;
			}
		}
	}

	return TRUE ;
}

BOOL CCUIQuad::_find_frame_point2(QUAD_NODE* pQuadNode, POINT& ptTarget, IUIAddFrame* pAddFrame)
{
	IF_RETURN(NULL == pQuadNode || NULL == pAddFrame, FALSE) ;

	for (size_t i = 0; i < pQuadNode->vecFramePool.size(); ++i)
	{
		if (pQuadNode->vecFramePool[i].rcFrameRect.PtInRect(ptTarget))
		{
			CComPtr<IUIFrame> pFrame ;
			pQuadNode->vecFramePool[i].pFrameAgent.Promote(__uuidof(IUIFrame), (VOID**)&pFrame) ;
			DEBUG_ASSERT(pFrame) ;
			pAddFrame->AddFrame(pFrame) ;
		}
	}

	if (pQuadNode->bHaveChildren)
	{
		for (INT i = 0; i < 4; ++i)
		{
			if (pQuadNode->pQuadChildren[i]->rcQuadNodeRect.PtInRect(ptTarget))
			{
				return this->_find_frame_point2(pQuadNode->pQuadChildren[i], ptTarget, pAddFrame) ;
			}
		}
	}
	return TRUE ;
}

BOOL CCUIQuad::_find_frame_rect(QUAD_NODE* pQuadNode, CRect& rcFrame, ICVarArray* pFrameArray)
{
	IF_RETURN(NULL == pQuadNode || NULL == pFrameArray, FALSE) ;

	for (size_t i = 0; i < pQuadNode->vecFramePool.size(); ++i)
	{
		CRect rcFrameTemp = pQuadNode->vecFramePool[i].rcFrameRect ;
		if (::IntersectRect(&rcFrameTemp, &rcFrameTemp, &rcFrame))
		{
			CComPtr<IUIFrame> pFrame ;
			pQuadNode->vecFramePool[i].pFrameAgent.Promote(__uuidof(IUIFrame), (VOID**)&pFrame) ;
			DEBUG_ASSERT(pFrame) ;
			pFrameArray->AddInterface(pFrame) ;
		}
	}

	if (pQuadNode->bHaveChildren)
	{
		for (INT i = 0; i < 4; ++i)
		{
			CRect rcFrameTemp = pQuadNode->pQuadChildren[i]->rcQuadNodeRect ;
			if (::IntersectRect(&rcFrameTemp, &rcFrameTemp, &rcFrame))
			{
				this->_find_frame_rect(pQuadNode->pQuadChildren[i], rcFrame, pFrameArray) ;
			}
		}
	}
	return TRUE ;
}

BOOL CCUIQuad::_find_frame_rect2(QUAD_NODE* pQuadNode, CRect& rcFrame, IUIAddFrame* pAddFrame)
{
	IF_RETURN(NULL == pQuadNode || NULL == pAddFrame, FALSE) ;

	for (size_t i = 0; i < pQuadNode->vecFramePool.size(); ++i)
	{
		CRect rcFrameTemp = pQuadNode->vecFramePool[i].rcFrameRect ;
		if (::IntersectRect(&rcFrameTemp, &rcFrameTemp, &rcFrame))
		{
			CComPtr<IUIFrame> pFrame ;
			pQuadNode->vecFramePool[i].pFrameAgent.Promote(__uuidof(IUIFrame), (VOID**)&pFrame) ;
			DEBUG_ASSERT(pFrame) ;
			pAddFrame->AddFrame(pFrame) ;
		}
	}

	if (pQuadNode->bHaveChildren)
	{
		for (INT i = 0; i < 4; ++i)
		{
			CRect rcFrameTemp = pQuadNode->pQuadChildren[i]->rcQuadNodeRect ;
			if (::IntersectRect(&rcFrameTemp, &rcFrameTemp, &rcFrame))
			{
				this->_find_frame_rect2(pQuadNode->pQuadChildren[i], rcFrame, pAddFrame) ;
			}
		}
	}
	return TRUE ;
}