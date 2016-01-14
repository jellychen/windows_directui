#pragma once
#include "Include/Def/Require.h"
#include "Include/Util/UtilTpl.h"
#include "Include/Common/ISService.h"
#include "Include/UIEngine/IUIControl.h"
#include "Include/UIEngine/IUIExtension.h"
#include "Include/UIEngine/IUIExtensionDef.h"
#include "Include/UIEngine/IUITooltips.h"
#include "Include/UIEngine/IUIWin.h"
#include "Include/UIEngine/IUIStatic.h"
#include "Include/UIEngine/TUIUtil.h"
#include "Include/UIEngine/IUILayoutDefault.h"

[
	default(IUITooltips) ,
	threading(free) ,
	uuid("DAE19002-027F-4960-9FDB-B06136BC517A") ,
	coclass
]
class ATL_NO_VTABLE CSUIIUITooltips
	: public TCustomServiceImpl<IUITooltips>
{
public:
	DECLARE_PROTECT_FINAL_CONSTRUCT() ;
	CSUIIUITooltips() ;
	virtual ~CSUIIUITooltips() ;
	HRESULT FinalConstruct() ;

public:
	HRESULT _call OnInit				() ;
	HRESULT _call SetTooltipsDraw		(IUIDraw* pDraw) ;
	HRESULT _call GetTooltipsDraw		(IUIDraw** ppDraw) ;
	HRESULT _call SetTooltipsPadding	(RECT rcPadding) ;
	HRESULT _call GetTooltipsPadding	(RECT* prcPadding) ;
	HRESULT _call SetTooltipsOffset		(POINT ptOffset) ;
	HRESULT _call GetTooltipsOffset		(POINT* pptOffset) ;

private:
	HRESULT OnToolTipsExtension			(REFIID iid, IUIFrame* pFrame, ICVarData* pData) ;
	HRESULT OnToolTipsDismissExtension	(REFIID iid, IUIFrame* pFrame, ICVarData* pData) ;

private:
	BOOL											m_bCreate ;
	CPoint											m_ptOffset ;
	CComPtr<IUIWin>									m_pWindow ;
	CComPtr<IUIStatic>								m_pStatic ;
	CComSinkExtensionCallbackPtr<CSUIIUITooltips>	m_pExtensionCallback ;
	CComSinkExtensionCallbackPtr<CSUIIUITooltips>	m_pToolTipsDismissExtensionCallback ;
	CWeakPtr<IUIExtensionCenter>					m_pExtensionCenter ;
} ;