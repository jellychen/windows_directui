#pragma once
#include "Include/Def/Require.h"
#include "Include/Util/Utiltpl.h"
#include "Include/UIEngine/IUIText.h"
#include "Include/UIEngine/IUIFrameDef.h"
#include "Include/UIEngine/IUIButton.h"
#include "Include/UIEngine/TUICustomControl.h"

[
    default(IUIButton) ,
    threading(free) ,
    uuid("EDF3CBEE-93A6-44f1-AF06-5B8E882C3BD9") ,
    coclass
]
class ATL_NO_VTABLE CCUIButton
	: public TUICustomControl<IUIButton, IUIControl>
{
public:
	DECLARE_PROTECT_FINAL_CONSTRUCT() ;
	CCUIButton() ;
	virtual ~CCUIButton() ;
	HRESULT FinalConstruct() ;

public:
	HRESULT _call SetFont				(IUIFont* pFont) ;
    HRESULT _call GetFont				(IUIFont** ppFont) ;
    HRESULT _call SetText				(BSTR bstrText) ;
    HRESULT _call GetText				(BSTR* pbstrText) ;
	HRESULT _call SetTextNormalColor	(COLORREF clr) ;
    HRESULT _call GetTextNormalColor	(COLORREF* pclr) ;
    HRESULT _call SetTextHighlightColor	(COLORREF clr) ;
    HRESULT _call GetTextHighlightColor	(COLORREF* pclr) ;
    HRESULT _call SetTextPushedColor	(COLORREF clr) ;
    HRESULT _call GetTextPushedColor	(COLORREF* pclr) ;
    HRESULT _call SetTextDisableColor	(COLORREF clr) ;
    HRESULT _call GetTextDisableColor	(COLORREF* pclr) ;
    HRESULT _call SetNormalBkgDraw		(IUIDraw* pNormalDraw) ;
    HRESULT _call GetNormalBkgDraw		(IUIDraw** ppNormalDraw) ;
    HRESULT _call SetHighlightBkgDraw	(IUIDraw* pHighlightDraw) ;
    HRESULT _call GetHighlightBkgDraw	(IUIDraw** ppHighlightDraw) ;
    HRESULT _call SetPushedBkgDraw		(IUIDraw* pPushedDraw) ;
    HRESULT _call GetPushedBkgDraw		(IUIDraw** ppPushedDraw) ;
    HRESULT _call SetDisableBkgDraw		(IUIDraw* pDisableDraw) ;
    HRESULT _call GetDisableBkgDraw		(IUIDraw** ppDisableDraw) ;

private:
	HRESULT _call OnMessage				(IUIFrame* pTarget, tMsgArg* pArg) ;
	HRESULT _call CalcSize              (SIZE szOld, SIZE* pszCalcOut) ;
	HRESULT _call Render                (IUICanvas* pCanvas, RECT rcRender, INT nState) ;
	HRESULT _call SetAttribute			(ICVarData* pAttrData) ;

private:
	CString								m_strText ;
	CComPtr<IUIText>                    m_pTextRender ;
    CComPtr<IUIFont>                    m_pTextFont ;
	COLORREF                            m_clrNormalColor ;
    COLORREF                            m_clrHighlightColor ;
    COLORREF                            m_clrPushedColor ;
    COLORREF                            m_clrDisableColor ;
    CComPtr<IUIDraw>                    m_pNormalDraw ;
    CComPtr<IUIDraw>                    m_pHighlightDraw ;
    CComPtr<IUIDraw>                    m_pPushedDraw ;
    CComPtr<IUIDraw>                    m_pDisableDraw ;
} ;