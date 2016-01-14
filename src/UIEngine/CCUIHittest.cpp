#include "stdafx.h"
#include "CCUIHittest.h"

bool _frame_compare(CPFRAME _left, CPFRAME _right)
{
	DEBUG_ASSERT(_left && _right) ;
	IF_RETURN(NULL == _left || NULL == _right, false) ;
	CComPtr<IUIFrame> pleft     = (IUIFrame*) _left ;
	CComPtr<IUIFrame> pRight    = (IUIFrame*)_right ;

	typedef std::vector<CComPtr<IUIFrame>> VEC_FRAMS ;
	VEC_FRAMS _left_ancestors, _right_ancestors ;

	CComQIPtr<IUIFrame> pTempFrame = pleft ;
	while (pTempFrame)
	{
		_left_ancestors.push_back(pTempFrame) ;
		CComPtr<IUIElement> pElement ;
		pTempFrame->GetParent(&pElement) ;
		pTempFrame = pElement ;
	}

	pTempFrame = pRight ;
	while (pTempFrame)
	{
		_right_ancestors.push_back(pTempFrame) ;
		CComPtr<IUIElement> pElement ;
		pTempFrame->GetParent(&pElement) ;
		pTempFrame = pElement ;
	}

	INT nLeftDepth  = (INT)_left_ancestors.size() - 1 ;
	INT nRightDepth = (INT)_right_ancestors.size() - 1 ;

	do 
	{
		if (0 > nLeftDepth) return true ;
		if (0 > nRightDepth) return false ;

		INT nLeftZOrder     = INT_MIN ;
		INT nRightZOrder    = INT_MIN ;
		_left_ancestors[nLeftDepth]->GetZOrder(&nLeftZOrder) ;
		_right_ancestors[nRightDepth]->GetZOrder(&nRightZOrder) ;

		if (nLeftZOrder < nRightZOrder)
		{
			return true ;
		}
		else if (nLeftZOrder > nRightZOrder)
		{
			return false ;
		}

		INT nLeftIndex  = INT_MIN ;
		INT nRightIndex = INT_MIN ;
		_left_ancestors[nLeftDepth]->GetIndex(&nLeftIndex) ;
		_right_ancestors[nRightDepth]->GetIndex(&nRightIndex) ;

		if (nLeftIndex < nRightIndex)
		{
			return true ;
		}
		else if (nLeftIndex > nRightIndex)
		{
			return false ;
		}

		nLeftDepth-- ;
		nRightDepth-- ;

	} while (TRUE) ;

	return false ;
}

CCUIHittest::CCUIHittest()
{
}

CCUIHittest::~CCUIHittest()
{
}

HRESULT CCUIHittest::GetHitFrame(IUIFrame** ppFrame, BOOL bSolid)
{
	DEBUG_ASSERT(ppFrame) ;
	IF_RETURN(NULL == ppFrame, E_INVALIDARG) ;
	*ppFrame = NULL ;

	if (FALSE == bSolid)
	{
		IF_RETURN(!m_pFrameAgent, E_FAIL) ;
		return this->m_pFrameAgent.Promote(__uuidof(IUIFrame), (VOID**)ppFrame) ;
	}
	else
	{
		IF_RETURN(!m_pSolidFrameAgent, E_FAIL) ;
		return this->m_pSolidFrameAgent.Promote(__uuidof(IUIFrame), (VOID**)ppFrame) ;
	}
	return E_FAIL ;
}

HRESULT CCUIHittest::AddFrameBegin()
{
	this->m_pFrameAgent = NULL ;
	this->m_pFrameTemp = NULL ;

	this->m_pSolidFrameAgent = NULL ;
	this->m_pSolidFrameTemp = NULL ;
	return S_OK ;
}

HRESULT CCUIHittest::AddFrame(IUIFrame* pFrame)
{
	DEBUG_ASSERT(pFrame) ;
	IF_RETURN(NULL == pFrame, E_INVALIDARG) ;

	if (NULL == this->m_pFrameTemp
		|| _frame_compare(this->m_pFrameTemp, pFrame))
	{
		this->m_pFrameTemp = pFrame ;

		BOOL bIsTransparetMouse = FALSE ;
		pFrame->GetTransparentMouse(&bIsTransparetMouse) ;
		if (FALSE == bIsTransparetMouse)
		{
			this->m_pSolidFrameTemp = pFrame ;
		}
	}

	return S_OK ;
}

HRESULT CCUIHittest::AddFrameEnd()
{
	this->m_pFrameAgent = this->m_pFrameTemp ;
	this->m_pFrameTemp = NULL ;
	this->m_pSolidFrameAgent = this->m_pSolidFrameTemp ;
	this->m_pSolidFrameTemp = NULL ;

	return S_OK ;
}