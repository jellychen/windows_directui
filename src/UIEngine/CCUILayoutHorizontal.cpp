#include "stdafx.h"
#include "CCUILayoutHorizontal.h"
#include <vector>
typedef std::vector<CComPtr<IUIFrame>> VEC_FRAME ;

CCUILayoutHorizontal::CCUILayoutHorizontal()
{
	this->m_nFillItem		= 0 ;
	this->m_nOrientation	= LAYOUT::ORIENTATION_NEAR ;
}

CCUILayoutHorizontal::~CCUILayoutHorizontal()
{
}

HRESULT CCUILayoutHorizontal::SetOrientation(INT nOrientation)
{
	this->m_nOrientation = nOrientation ;
	return S_OK ;
}

HRESULT CCUILayoutHorizontal::GetOrientation(INT* pnOrientation)
{
	DEBUG_ASSERT(pnOrientation) ;
	IF_RETURN(NULL == pnOrientation, E_INVALIDARG) ;

	*pnOrientation = this->m_nOrientation ;
	return S_OK ;
}

HRESULT CCUILayoutHorizontal::SetFillItemIndex(INT nItemIndex)
{
	this->m_nFillItem = nItemIndex ;
	return S_OK ;
}

HRESULT CCUILayoutHorizontal::GetFillItemIndex(INT* pnItemIndex)
{
	DEBUG_ASSERT(pnItemIndex) ;
	IF_RETURN(NULL == pnItemIndex, E_INVALIDARG) ;

	*pnItemIndex = this->m_nFillItem ;
	return S_OK ;
}

HRESULT CCUILayoutHorizontal::Layout(IUIFrame* pHostFrame)
{
	DEBUG_ASSERT(pHostFrame) ;
	IF_RETURN(NULL == pHostFrame, E_INVALIDARG) ;

	CSize szContainer(0, 0) ;
	pHostFrame->GetSize(&szContainer) ;
	CRect rcPadding(0, 0, 0, 0) ;
	pHostFrame->GetPadding(&rcPadding) ;
	CRect rcExtPadding(0, 0, 0, 0) ;
	CComQIPtr<IUIFrameInternal> pFrameInternal = pHostFrame ;
	if (pFrameInternal)
	{
		pFrameInternal->GetExtPadding(&rcExtPadding) ;
	}

	CRect rcContainer(0, 0, 0, 0) ;
	rcContainer.left    = rcPadding.left + rcExtPadding.left ;
	rcContainer.top     = rcPadding.top + rcExtPadding.top ;
	rcContainer.right   = szContainer.cx - rcPadding.right - rcExtPadding.right ;
	rcContainer.bottom  = szContainer.cy - rcPadding.bottom - rcExtPadding.bottom ;

	INT nCurrentLayout = 0, nUsedSpace = 0 ;
	if (LAYOUT::ORIENTATION_NEAR == this->m_nOrientation)
	{
		nCurrentLayout = rcPadding.left + rcExtPadding.left ;
	}
	else if (LAYOUT::ORIENTATION_FAR == this->m_nOrientation)
	{
		nCurrentLayout = szContainer.cx - rcPadding.right - rcExtPadding.right ;
	}

	LONG lChildrenCount = 0 ;
	pHostFrame->GetChildrenCount(&lChildrenCount) ;
	for (INT i = 0; i < lChildrenCount; ++i)
	{
		CComPtr<IUIElement> pElement ;
		pHostFrame->GetChildByIndex(i, &pElement) ;
		CComQIPtr<IUIFrame> pFrameChild = pElement ;
		CComQIPtr<IUIFrameInternal> pFrameInternal = pElement ;
		IF_CONTINUE(NULL == pFrameChild || NULL == pFrameInternal) ;

		BOOL bHidden = FALSE ;
		pFrameChild->GetHidden(&bHidden) ;
		IF_CONTINUE(bHidden) ;

		BOOL bFloat = FALSE ;
		pFrameChild->GetFloat(&bFloat) ;
		IF_CONTINUE(bFloat) ;

		CRect rcChildMargin(0, 0, 0, 0) ;
		pFrameChild->GetMargin(&rcChildMargin) ;

		BOOL bChildHeightAsParent = FALSE ;
		pFrameChild->GetHeightAsParent(&bChildHeightAsParent) ;
		if (bChildHeightAsParent)
		{
			CSize szEstimateSize(0, 0) ;
			szEstimateSize.cx   = -1 ;
			szEstimateSize.cy   = rcContainer.Height() - rcChildMargin.top - rcChildMargin.bottom ;
			pFrameInternal->SetEstimateSize(szEstimateSize) ;
		}

		BOOL bChildWidthAsParent = FALSE ;
		pFrameChild->GetWidthAsParent(&bChildWidthAsParent) ;
		if (i == this->m_nFillItem -1  || -1 * lChildrenCount + i == this->m_nFillItem)
		{
			INT nFillSize = this->CalcFillSize(pHostFrame, rcContainer, nUsedSpace, i) ;
			CSize szEstimateSize(0, 0) ;
			szEstimateSize.cx   = nFillSize - rcChildMargin.left - rcChildMargin.right ;
			szEstimateSize.cy   = -1 ;
			pFrameInternal->SetEstimateSize(szEstimateSize) ;
		}
		else if (bChildWidthAsParent)
		{
			pFrameInternal->SetEstimateSize(CSize(0, -1)) ;
		}

		CRect rcTarget(0, 0, 0, 0) ;
		CSize szChildChild(0, 0) ;
		pFrameChild->GetSize(&szChildChild) ;

		nUsedSpace += szChildChild.cx + rcChildMargin.left + rcChildMargin.right ;

		INT nDrift = DRIFT::DRIFT_NEAR ;
		pFrameChild->GetDrift(&nDrift) ;

		if (LAYOUT::ORIENTATION_NEAR == this->m_nOrientation)
		{
			if (DRIFT::DRIFT_NEAR == nDrift)
			{
				rcTarget.top    = rcContainer.top + rcChildMargin.top ;
			}
			else if (DRIFT::DRIFT_FAR == nDrift)
			{
				rcTarget.top	= rcContainer.bottom - rcChildMargin.bottom - szChildChild.cy ;
			}
			else if (DRIFT::DRIFT_MIDDLE == nDrift)
			{
				rcTarget.top	= (rcContainer.Height() - szChildChild.cy)/2 + rcContainer.top ;
			}
			rcTarget.left   = nCurrentLayout + rcChildMargin.left ;
			rcTarget.right  = rcTarget.left + szChildChild.cx ;
			rcTarget.bottom = rcTarget.top + szChildChild.cy ;
			nCurrentLayout += szChildChild.cx + rcChildMargin.left + rcChildMargin.right ;
		}
		else if (LAYOUT::ORIENTATION_FAR == this->m_nOrientation)
		{
			if (DRIFT::DRIFT_NEAR == nDrift)
			{
				rcTarget.top    = rcContainer.top + rcChildMargin.top ;
			}
			else if (DRIFT::DRIFT_FAR == nDrift)
			{
				rcTarget.top	= rcContainer.bottom - rcChildMargin.bottom - szChildChild.cy ;
			}
			else if (DRIFT::DRIFT_MIDDLE == nDrift)
			{
				rcTarget.top	= (rcContainer.Height() - szChildChild.cy)/2 + rcContainer.top ;
			}
			rcTarget.right  = nCurrentLayout - rcChildMargin.right ;
			rcTarget.left   = rcTarget.right - szChildChild.cx ;
			rcTarget.bottom = rcTarget.top + szChildChild.cy ;
			nCurrentLayout -= szChildChild.cx + rcChildMargin.left + rcChildMargin.right ;
		}
		pFrameInternal->SetLayoutRect(rcTarget) ;
	}
	return S_OK ;
}

HRESULT CCUILayoutHorizontal::CalcSize(IUIFrame* pHostFrame, SIZE szOld, SIZE* pOutSize)
{
	DEBUG_ASSERT(pHostFrame) ;
	IF_RETURN(NULL == pHostFrame, E_INVALIDARG) ;
	DEBUG_ASSERT(pOutSize) ;
	IF_RETURN(NULL == pOutSize, E_INVALIDARG) ;

	BOOL bAutoWidth = FALSE, bAutoHeight = FALSE ;
	pHostFrame->GetAutoWidth(&bAutoWidth) ;
	pHostFrame->GetAutoHeight(&bAutoHeight) ;

	if (!bAutoWidth && !bAutoHeight)
	{
		*pOutSize = szOld ;
		return S_OK ;
	}

	CRect _rcPadding(0, 0, 0, 0) ;
	pHostFrame->GetPadding(_rcPadding) ;
	CRect _rcExtPadding(0, 0, 0, 0) ;
	CComQIPtr<IUIFrameInternal> pFrameInternal = pHostFrame ;
	if (pFrameInternal)
	{
		pFrameInternal->GetExtPadding(&_rcExtPadding) ;
	}

	CSize szMinBoundSize = szOld ;
	if (bAutoHeight)
	{
		szMinBoundSize.cy = 0 ;
	}

	if (bAutoWidth)
	{
		szMinBoundSize.cx = 0 ;
	}

	VEC_FRAME _vec_frame ;
	LONG lChildrenCount = 0 ;
	pHostFrame->GetChildrenCount(&lChildrenCount) ;
	for (INT i = 0; i < lChildrenCount; ++i)
	{
		//IF_CONTINUE(i == this->m_nFillItem - 1) ;

		CComPtr<IUIElement> pElement ;
		pHostFrame->GetChildByIndex(i, &pElement) ;
		CComQIPtr<IUIFrame> pFrame = pElement ;
		IF_CONTINUE(NULL == pFrame) ;

		CComQIPtr<IUIFrameInternal> pFrameInternal = pFrame ;
		IF_CONTINUE(NULL == pFrameInternal) ;

		BOOL bHidden = FALSE ;
		pFrame->GetHidden(&bHidden) ;
		IF_CONTINUE(TRUE == bHidden) ;

		BOOL bFloat = TRUE ;
		pFrame->GetFloat(&bFloat) ;
		IF_CONTINUE(TRUE == bFloat) ;

		BOOL bChildHeightAsParent = FALSE ;
		pFrame->GetHeightAsParent(&bChildHeightAsParent) ;
		BOOL bChildWidthAsParent = FALSE ;
		pFrame->GetWidthAsParent(&bChildWidthAsParent) ;
		BOOL bChildAutoHeight = FALSE ;
		pFrame->GetAutoHeight(&bChildAutoHeight) ;
		BOOL bChildAutoWidth = FALSE ;
		pFrame->GetAutoWidth(&bChildAutoWidth) ;

		if (bChildHeightAsParent && bChildAutoWidth && bAutoHeight)
		{
			_vec_frame.push_back(pFrame) ;
		}
		else
		{
			CRect rcFrameMargin(0, 0, 0, 0) ;
			pFrame->GetMargin(&rcFrameMargin) ;
			
			CSize szEstimateSize(-1, -1) ;
			if (bChildWidthAsParent)
			{
				szEstimateSize.cx = 0 ;
			}
			if (bChildHeightAsParent && !bAutoHeight)
			{
				szEstimateSize.cy = szOld.cy - _rcPadding.top - _rcPadding.bottom - _rcExtPadding.top - _rcExtPadding.bottom ;		
			}
			pFrameInternal->SetEstimateSize(szEstimateSize) ;

			CSize szFrame(0, 0) ;
			pFrame->GetSize(&szFrame) ;
			if (i == this->m_nFillItem -1  || -1 * lChildrenCount + i == this->m_nFillItem)
			{
				szFrame.cx = 0 ;
			}

			if (bAutoHeight)
			{
				INT nHeight = szFrame.cy + rcFrameMargin.top + rcFrameMargin.bottom ;
				if (nHeight > szMinBoundSize.cy)
				{
					szMinBoundSize.cy = nHeight ;
				}
			}

			if (bAutoWidth)
			{
				szMinBoundSize.cx += (szFrame.cx + rcFrameMargin.left + rcFrameMargin.right) ;
			}
		}
	}

	if (bAutoWidth)
	{
		for (INT i = 0; i < (INT)_vec_frame.size(); ++i)
		{
			CComPtr<IUIFrame> pFrame = _vec_frame[i] ;
			CComQIPtr<IUIFrameInternal> pFrameInternal = _vec_frame[i] ;
			IF_CONTINUE(NULL == pFrame || NULL == pFrameInternal) ;

			CRect rcMargin(0, 0, 0, 0) ;
			pFrame->GetMargin(&rcMargin) ;

			CSize szEstimateSize(0, 0) ;
			szEstimateSize.cx = -1 ;
			szEstimateSize.cy = szMinBoundSize.cy - rcMargin.top - rcMargin.bottom ;
			pFrameInternal->SetEstimateSize(szEstimateSize) ;

			CSize szFrame(0, 0) ;
			pFrame->GetSize(&szFrame) ;
			szMinBoundSize.cx = szFrame.cx + rcMargin.left + rcMargin.right ;
		}
	}


	if (bAutoWidth)
	{
		szMinBoundSize.cx += _rcPadding.left + _rcPadding.right + _rcExtPadding.left + _rcExtPadding.right ;
	}

	if (bAutoHeight)
	{
		szMinBoundSize.cy += _rcPadding.top + _rcPadding.bottom + _rcExtPadding.top + _rcExtPadding.bottom ;
	}

	*pOutSize = szMinBoundSize ;
	return S_OK ;
}

HRESULT CCUILayoutHorizontal::SetAttribute(ICVarData* pAttrData)
{
	SET_ATTR_CLASS_BEGIN	(pAttrData, IUILayoutHorizontal)
	SET_ATTR_INT			(Orientation)
	SET_ATTR_INT			(FillItemIndex)
	SET_ATTR_END            ()

	return S_OK ;
}

INT CCUILayoutHorizontal::CalcFillSize(IUIFrame* pHostFrame, RECT rc, INT nCurrent, INT nIndex)
{
	DEBUG_ASSERT(pHostFrame) ;
	IF_RETURN(NULL == pHostFrame, 0) ;

	LONG lChildrenCount = 0 ;
	pHostFrame->GetChildrenCount(&lChildrenCount) ;
	IF_RETURN(nIndex >= lChildrenCount, 0) ;

	CRect rcContainer(rc) ;
	INT nFillSize = rcContainer.Width() - nCurrent ;
	for (INT i = nIndex + 1; i < lChildrenCount; ++i)
	{
		CComPtr<IUIElement> pElement ;
		pHostFrame->GetChildByIndex(i, &pElement) ;
		CComQIPtr<IUIFrame> pFrameChild = pElement ;
		CComQIPtr<IUIFrameInternal> pFrameInternal = pElement ;
		IF_CONTINUE(NULL == pFrameChild || NULL == pFrameInternal) ;

		BOOL bHidden = FALSE ;
		pFrameChild->GetHidden(&bHidden) ;
		IF_CONTINUE(TRUE == bHidden) ;

		BOOL bFloat = TRUE ;
		pFrameChild->GetFloat(&bFloat) ;
		IF_CONTINUE(TRUE == bFloat) ;

		CRect rcChildMargin(0, 0, 0, 0) ;
		pFrameChild->GetMargin(&rcChildMargin) ;

		BOOL bCanbeCalcSize = TRUE ;
		BOOL bChildHeightAsParent = FALSE ;
		pFrameChild->GetHeightAsParent(&bChildHeightAsParent) ;
		if (bChildHeightAsParent)
		{
			CSize szEstimateSize(0, 0) ;
			szEstimateSize.cx   = -1 ;
			szEstimateSize.cy   = rcContainer.Height() - rcChildMargin.top - rcChildMargin.bottom ;
			pFrameInternal->SetEstimateSize(szEstimateSize) ;
		}

		BOOL bChildWidthAsParent = FALSE ;
		pFrameChild->GetWidthAsParent(&bChildWidthAsParent) ;
		if (bChildWidthAsParent)
		{
			bCanbeCalcSize = FALSE ;
			pFrameInternal->SetEstimateSize(CSize(0, -1)) ;
		}

		CSize szChild(0, 0) ;
		if (bCanbeCalcSize)
		{
			pFrameChild->GetSize(&szChild) ;
		}

		nFillSize -= (szChild.cx + rcChildMargin.left + rcChildMargin.right) ;
	}
	return nFillSize >= 0 ? nFillSize : 0 ;
}
