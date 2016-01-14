#include "stdafx.h"
#include "CCUIRender.h"

bool frame_less(const FRAME_RENDER_NODE& left, const FRAME_RENDER_NODE& right)
{
	INT nLeftDepth  = (INT)left._vec_info.size() -1 ;
	INT nRightDepth = (INT)right._vec_info.size() -1 ;

	do 
	{
		IF_RETURN(0 > nLeftDepth, true) ;
		IF_RETURN(0 > nRightDepth, false) ;

		if (left._vec_info[nLeftDepth]._nZOrder 
			< right._vec_info[nRightDepth]._nZOrder) 
		{
			return true ;
		}
		else if (left._vec_info[nLeftDepth]._nZOrder 
			> right._vec_info[nRightDepth]._nZOrder)
		{
			return false ;
		}

		if (left._vec_info[nLeftDepth]._nIndex 
			< right._vec_info[nRightDepth]._nIndex) 
		{
			return true ;
		}
		else if (left._vec_info[nLeftDepth]._nIndex 
			> right._vec_info[nRightDepth]._nIndex)
		{
			return false ;
		}

		--nLeftDepth ;
		--nRightDepth ;

	} while (TRUE) ;

	return false ;
}

CCUIRender::CCUIRender()
{
}

CCUIRender::~CCUIRender()
{
}

HRESULT CCUIRender::Render(IUICanvas* pCanvas)
{
	DEBUG_ASSERT(pCanvas) ;
	IF_RETURN(NULL == pCanvas, E_INVALIDARG) ;
	std::sort(m_vecFramePool.begin(), m_vecFramePool.end(), frame_less) ;

	CComPtr<IUICanvas> _pCurrentCanvas =  pCanvas ;
	for (size_t i = 0; i < this->m_vecFramePool.size(); ++i)
	{
		IF_CONTINUE(NULL == this->m_vecFramePool[i]._pFrame) ;
		this->m_vecFramePool[i]._pFrame->Draw(_pCurrentCanvas) ;
	}
	return S_OK ;
}

HRESULT CCUIRender::Clear()
{
	this->m_vecFramePool.clear() ;
	this->m_setFramePool.clear() ;
	return S_OK ;
}

HRESULT CCUIRender::AddFrameBegin()
{
	return S_OK ;
}

HRESULT CCUIRender::AddFrame(IUIFrame* pFrame)
{
	DEBUG_ASSERT(pFrame) ;
	IF_RETURN(NULL == pFrame, E_INVALIDARG) ;

	SET_LONG::iterator it = this->m_setFramePool.find((LONG)(pFrame)) ;
	IF_RETURN(this->m_setFramePool.end() != it, S_OK) ;

	this->m_setFramePool.insert((LONG)(pFrame)) ;

	FRAME_RENDER_NODE _node ;
	_node._pFrame = pFrame ;

	CComQIPtr<IUIFrame> pTempFrame = pFrame ;
	while (pTempFrame)
	{
		RENDER_INFO _info ;
		pTempFrame->GetIndex(&_info._nIndex) ;
		pTempFrame->GetZOrder(&_info._nZOrder) ;
		_node._vec_info.push_back(_info) ;

		CComPtr<IUIElement> pElement ;
		pTempFrame->GetParent(&pElement) ;
		pTempFrame = pElement ;
	}
	this->m_vecFramePool.push_back(_node) ;

	return S_OK ;
}

HRESULT CCUIRender::AddFrameEnd()
{
	return S_OK ;
}