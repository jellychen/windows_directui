#pragma once
#include "Include/UIEngine/IUIFrameDef.h"
#include "Include/UIEngine/IUIFrame.h"
#include "Include/UIEngine/IUIFrameInternal.h"
#include "Include/UIEngine/IUILayoutDefault.h"

[
	default(IUILayoutHorizontal) ,
	threading(free) ,
	uuid("62316E13-2B60-464f-9877-ED343344F7F4") ,
	coclass
]
class ATL_NO_VTABLE CCUILayoutHorizontal
	: public IDispatchImpl<IUILayoutHorizontal>
	, public IDispatchImpl<IUIAttribute>
{
public:
	CCUILayoutHorizontal() ;
	virtual ~CCUILayoutHorizontal() ;

public:
	HRESULT _call SetOrientation	(INT nOrientation) ;
	HRESULT _call GetOrientation	(INT* pnOrientation) ;
	HRESULT _call SetFillItemIndex	(INT nItemIndex) ;
	HRESULT _call GetFillItemIndex	(INT* pnItemIndex) ;
	HRESULT _call Layout			(IUIFrame* pFrame) ;
	HRESULT _call CalcSize			(IUIFrame* pFrame, SIZE szOld, SIZE* pOutSize) ;
	HRESULT _call SetAttribute		(ICVarData* pAttrData) ;

private:
	INT CalcFillSize				(IUIFrame* pHostFrame, RECT rcContainer, INT nCurrent, INT nIndex) ;

private:
	INT								m_nOrientation ;
	INT								m_nFillItem ;
} ;