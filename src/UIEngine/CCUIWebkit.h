#pragma once
#include "Include/UIEngine/IUIWebkit.h"
#include "Include/UIEngine/TUICustomControl.h"
#include "Include/UIEngine/IUITimer.h"
#include "Include/UIEngine/IUIWin.h"
#include "Include/UIEngine/TUIUtil.h"
#include "Include/UIEngine/TUIV2v.h"
#include "CCUIWebkitDef.h"
#include "CCUIWebkitInterface.h"
#include "CCUIWebkitHost.h"

[
	default(IUIWebkit) ,
	threading(free) ,
	uuid("9D21F203-B88A-49ec-829F-5C521537DB60") ,
	coclass
]
class ATL_NO_VTABLE CCUIWebkit 
	: public TUICustomControl<IUIWebkit, IUIControl>
	, public _wkeBufHandler 
{
public:
	CCUIWebkit() ;
	virtual ~CCUIWebkit() ;
	HRESULT FinalConstruct() ;

public:
	HRESULT _call SetUrl		(BSTR bstrUrl) ;

public:
	HRESULT _call GetSize		(SIZE* pszSize) ;
	HRESULT _call SetLayoutRect	(RECT rcLayout) ;
	HRESULT _call Render		(IUICanvas* pCanvas, RECT rcRender, INT nState) ;
	HRESULT _call OnMessage		(IUIFrame* pTarget, tMsgArg* pArg) ;

public:
	HRESULT _call SetAttribute	(ICVarData* pAttrData) ;

public:
	void	onBufUpdated		(const HDC hdc,int x, int y, int cx, int cy) ;
	HRESULT OnTimer				(INT nTimerId) ;

private:
	wkeWebView								m_pWebkit ;
	CWeakPtr<IUITimer>						m_pTimer ;
	CComSinkTimerCallbackPtr<CCUIWebkit>	m_pTimeCallbackPtr ;
} ;