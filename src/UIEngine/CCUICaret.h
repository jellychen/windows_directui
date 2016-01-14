#pragma once
#include "Include/Def/Require.h"
#include "Include/Util/Utiltpl.h"
#include "Include/UIEngine/IUITimer.h"
#include "Include/UIEngine/IUIBrush.h"
#include "Include/UIEngine/TUICustomControl.h"
#include "Include/UIEngine/IUICaret.h"

[
	default(IUICaret) ,
	threading(free) ,
	uuid("F22D285D-6636-466c-873B-DE8B743CD351") ,
	coclass
]
class ATL_NO_VTABLE CCUICaret
	: public TUICustomControl<IUICaret, IUIControl>
{
public:
	DECLARE_PROTECT_FINAL_CONSTRUCT() ;
	CCUICaret() ;
	virtual ~CCUICaret() ;
	HRESULT FinalConstruct() ;

public:
	HRESULT _call SetBlinkTime          (DWORD dwBlink) ;
	HRESULT _call GetBlinkTime          (DWORD* pdwBlink) ;
	HRESULT _call SetCaretDraw          (IUIDraw* pDraw) ;
	HRESULT _call GetCaretDraw          (IUIDraw** ppDraw) ;
	HRESULT _call SetBlink				(BOOL bBlink) ;
	HRESULT _call GetBlink				(BOOL* bBlink) ;
	HRESULT _call ShowCaret             () ;
	HRESULT _call HideCaret             () ;
	HRESULT _call Render                (IUICanvas* pCanvas, RECT rcRender, INT nState) ;
private:
	HRESULT OnTimer                     (INT nTimerID) ;

private:
	BOOL                                m_bBlink ;
	DWORD                               m_dwBlinkTime ;
	CComPtr<IUIDraw>                    m_pCaretDraw ;
	CWeakPtr<IUITimer>					m_pTimerService ;
	CComSinkTimerCallbackPtr<CCUICaret> m_pTimerCallbackPtr ;
} ;