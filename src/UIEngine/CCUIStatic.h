#pragma once
#include "Include/Util/Utiltpl.h"
#include "Include/Common/ICVarData.h"
#include "Include/UIEngine/IUIStatic.h"
#include "Include/UIEngine/TUICustomControl.h"
#include "Include/UIEngine/IUIText.h"
#include "Include/UIEngine/TUIV2v.h"

[
	default(IUIStatic) ,
	threading(free) ,
	uuid("6A536450-119D-4ED2-9697-AEEC2D3D4EEB") ,
	coclass
]
class ATL_NO_VTABLE CCUIStatic
	: public TUICustomControl<IUIStatic, IUIControl>
{
public:
	DECLARE_PROTECT_FINAL_CONSTRUCT() ;
	CCUIStatic() ;
	virtual ~CCUIStatic() ;
	HRESULT FinalConstruct() ;

public:
	HRESULT _call SetText           (BSTR bstrText) ;
	HRESULT _call GetText           (BSTR* pbstrText) ;
	HRESULT _call SetFont           (IUIFont* pFont) ;
	HRESULT _call GetFont           (IUIFont** ppFont) ;
	HRESULT _call SetMutiLine       (BOOL bMutiLine) ;
	HRESULT _call GetMutiLine       (BOOL* pbMutiLine) ;
	HRESULT _call SetTextColor      (COLORREF clr) ;
	HRESULT _call GetTextColor      (COLORREF* pclr) ;

private:
	HRESULT _call CalcSize          (SIZE szOld, SIZE* pszCalcOut) ;
	HRESULT _call Render            (IUICanvas* pCanvas, RECT rcRender, INT nState) ;
	HRESULT _call SetAttribute      (ICVarData* pAttrData) ;

private:
	CString                         m_cstrText ;
	BOOL                            m_bMutilLine ;
	COLORREF                        m_clrText ;
	CComPtr<IUIFont>                m_pTextFont ;
	CComPtr<IUIText>                m_pTextRender ;
	CComPtr<IUICanvas>				m_pBlurCanvas ;
} ;