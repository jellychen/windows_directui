#pragma once
#include "Include/Util/Utiltpl.h"
#include "Include/UIEngine/IUIButton.h"
#include "Include/UIEngine/IUIScroll.h"
#include "Include/UIEngine/IUIBrush.h"
#include "Include/UIEngine/TUICustomControl.h"

[
	default(IUIScroll) ,
	threading(free) ,
	uuid("4CD999BB-1384-460f-8252-38C3B82A8CBA") ,
	coclass
]
class ATL_NO_VTABLE CCUIScroll
	: public TUICustomControl<IUIScroll, IUIControl>
{
public:
	DECLARE_PROTECT_FINAL_CONSTRUCT() ;
	CCUIScroll() ;
	virtual ~CCUIScroll() ;
	HRESULT FinalConstruct() ;

public:
	HRESULT _call SetOrientation			(INT nOrientation) ;
	HRESULT _call SetOrientation			(BSTR bstrOrientation) ;
	HRESULT _call GetOrientation			(INT* pnOrientation) ;
	HRESULT _call SetEnableWheel			(BOOL bEnableWheel) ;
	HRESULT _call GetEnableWheel			(BOOL* pbEnableWheel) ;
	HRESULT _call SetPercentage				(INT nPercetage) ;
	HRESULT _call GetPercentage				(INT* pnPercetage) ;
	HRESULT _call SetScrollScale			(INT nScale) ;
	HRESULT _call GetScrollScale			(INT* pnScale) ;
	HRESULT _call SetScrollBarSize			(SIZE szScrollBar) ;
	HRESULT _call GetScrollBarSize			(SIZE* pszScrollBar) ;
	HRESULT _call SetScrollBarMinSize		(SIZE szScrollBar) ;
	HRESULT _call GetScrollBarMinSize		(SIZE* pszScrollBar) ;
	HRESULT _call SetScrollBarNormalDraw	(IUIDraw* pNormalDraw) ;
	HRESULT _call GetScrollBarNormalDraw	(IUIDraw** ppNormalDraw) ;
	HRESULT _call SetScrollBarHighlightDraw	(IUIDraw* pHighlightDraw) ;
	HRESULT _call GetScrollBarHighlightDraw	(IUIDraw** ppHighlightDraw) ;
	HRESULT _call SetScrollBarPushedDraw	(IUIDraw* pPushedDraw) ;
	HRESULT _call GetScrollBarPushedDraw	(IUIDraw** ppPushedraw) ;

public:
	HRESULT _call CalcSize                  (SIZE szOld, SIZE* pszCalcOut) ;
	HRESULT _call Layout                    () ;
	HRESULT _call SetAttribute              (ICVarData* pAttrData) ;

private:
	INT										m_nOrientation ;
	INT										m_nScale ;
	BOOL									m_bEnableWheel ;
	DOUBLE                                  m_fPercentage ;
	CSize                                   m_szScrollBarMinSize ;
	CComPtr<IUIButton>                      m_pScrollBar ;
} ;