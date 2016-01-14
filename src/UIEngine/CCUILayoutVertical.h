#pragma once
#include "Include/UIEngine/IUIFrameDef.h"
#include "Include/UIEngine/IUIFrame.h"
#include "Include/UIEngine/IUIFrameInternal.h"
#include "Include/UIEngine/IUILayoutDefault.h"

[
	default(IUILayoutVertical) ,
	threading(free) ,
	uuid("51430FE6-17A7-4053-BC04-077E5BF86F52") ,
	coclass
]
class ATL_NO_VTABLE CCUILayoutVertical
	: public IDispatchImpl<IUILayoutVertical>
	, public IDispatchImpl<IUIAttribute>
{
public:
	CCUILayoutVertical() ;
	virtual ~CCUILayoutVertical() ;

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