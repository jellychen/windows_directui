#pragma once
#include "Include/Def/Require.h"
#include "Include/Util/Utiltpl.h"
#include "Include/UIEngine/IUIList.h"
#include "Include/UIEngine/IUIFrameDef.h"
#include "Include/UIEngine/IUIListItem.h"
#include "Include/UIEngine/TUICustomControl.h"

[
	default(IUIListItem) ,
	threading(free) ,
	uuid("27346A6F-A002-468e-BC70-3313384A3CC6") ,
	coclass
]
class ATL_NO_VTABLE CCUIListItem
	: public TUICustomControl<IUIListItem, IUIControl>
{
public:
	DECLARE_PROTECT_FINAL_CONSTRUCT() ;
	CCUIListItem() ;
	virtual ~CCUIListItem() ;

public:
	HRESULT _call SetHostList		(IUIElement* pHostList) ;
	HRESULT _call SetSelected		(BOOL bSelected) ;
	HRESULT _call GetSelected		(BOOL* pbSelected) ;
	HRESULT _call SetNormalDraw		(IUIDraw* pNormalDraw) ;
	HRESULT _call GetNormalDraw		(IUIDraw** ppNormalDraw) ;
	HRESULT _call SetHighlightDraw	(IUIDraw* pHighlightDraw) ;
	HRESULT _call GetHighlightDraw	(IUIDraw** ppHighlightDraw) ;
	HRESULT _call SetDisableDraw	(IUIDraw* pDisableDraw) ;
	HRESULT _call GetDisableDraw	(IUIDraw** ppDisableDraw) ;
	HRESULT _call SetSelectedDraw	(IUIDraw* pSelectedDraw) ;
	HRESULT _call GetSelectedDraw	(IUIDraw** ppSelectedDraw) ;

public:
	BOOL							m_bSelected ;								
	HRESULT _call Render			(IUICanvas* pCanvas, RECT rcRender, INT nState) ;
	HRESULT _call OnMessageRiase	(IUIFrame* pTarget, tMsgArg* pArg, BOOL* pbIntercept) ;

private:
	CComPtr<IUIDraw>				m_pNormalDraw ;
	CComPtr<IUIDraw>				m_pHighlightDraw ;
	CComPtr<IUIDraw>				m_pDisableDraw ;
	CComPtr<IUIDraw>				m_pSelectedDraw ;
	CWeakPtr<IUIList>				m_pHostList ;
} ;