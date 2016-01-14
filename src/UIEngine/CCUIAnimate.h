#pragma once
#include "Include/Util/Utiltpl.h"
#include "Include/Common/ICVarData.h"
#include "Include/UIEngine/IUIAnimate.h"
#include "Include/UIEngine/TUICustomControl.h"
#include "Include/UIEngine/TUIV2v.h"
#include "Include/UIEngine/IUITimer.h"
#include <vector>


[
	default(IUIAnimate) ,
	threading(free) ,
	uuid("33B87A71-8EDD-45cc-9622-88CCA6D72E0B") ,
	coclass
]
class ATL_NO_VTABLE CCUIAnimate
	: public TUICustomControl<IUIAnimate, IUIControl>
{
public:
	DECLARE_PROTECT_FINAL_CONSTRUCT() ;
	CCUIAnimate() ;
	virtual ~CCUIAnimate() ;
	HRESULT FinalConstruct() ;

	typedef std::vector<CComPtr<IUIDraw>>	VEC_DRAW ;
	
public:
	HRESULT _call AddFrame		(IUIDraw* pDraw) ;
	HRESULT _call SetInterval	(INT nInterval) ;
	HRESULT _call GetInterval	(INT* pnInterval) ;
	HRESULT	_call DoForward		(BOOL bForward) ;

public:
	HRESULT _call Render					(IUICanvas* pCanvas, RECT rcRender, INT nState) ;
	HRESULT _call OnMessage					(IUIFrame* pTarget, tMsgArg* pArg) ;
	
private:
	HRESULT OnTimer							(INT nTimerId) ;

private:
	VEC_DRAW								m_vecDraw ;
	INT										m_nInterval ;
	INT										m_nCurrent ;
	BOOL									m_bForward ;
	CWeakPtr<IUITimer>						m_pTimer ;
	CComSinkTimerCallbackPtr<CCUIAnimate>	m_pTimerCallback ;
} ;
