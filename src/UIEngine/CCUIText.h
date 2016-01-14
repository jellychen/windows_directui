#pragma once
#include "Include/UIEngine/IUIText.h"
#include "Include/UIEngine/IUIAttribute.h"
#include "Include/UIEngine/TUIV2v.h"
#include <math.h>
#include <GdiPlus.h>

[
	default(IUIText) ,
	threading(free) ,
	uuid("ABE0840E-3497-4E7A-AC5F-15D53D6AFD70") ,
	coclass
]
class ATL_NO_VTABLE CCUIText 
	: public IDispatchImpl<IUIText>
	, public IDispatchImpl<IUIAttribute>
{
public:
	DECLARE_PROTECT_FINAL_CONSTRUCT() ;
	CCUIText() ;
	virtual ~CCUIText() ;
	HRESULT FinalConstruct() ;

public:
	HRESULT _call SetFont           (IUIFont* pFont) ;
	HRESULT _call GetFont           (IUIFont** ppFont) ;
	HRESULT _call SetAlignment      (DWORD dwAlignment) ;
	HRESULT _call SetAlignment      (BSTR bstrAlignment) ;
	HRESULT _call GetAlignment      (DWORD* pdwAlignment) ;
	HRESULT _call SetLineAlignment  (DWORD dwAlignment) ;
	HRESULT _call SetLineAlignment  (BSTR bstrAlignment) ;
	HRESULT _call GetLineAlignment  (DWORD* pdwAlignment) ;
	HRESULT _call SetRightToLeft    (BOOL bRightToLeft) ;
	HRESULT _call GetRightTopLeft   (BOOL* pbRightToLeft) ;
	HRESULT _call SetVertical       (BOOL bVertical) ;
	HRESULT _call GetVertical       (BOOL* pbVertical) ;
	HRESULT _call SetNoWarp         (BOOL bNoWarp) ;
	HRESULT _call GetNoWarp         (BOOL* pbNoWarp) ;
	HRESULT _call SetLineLimit      (BOOL bLimitLine) ;
	HRESULT _call GetLineLimit      (BOOL* pbLimitLine) ;
	HRESULT _call SetTrimming       (DWORD dwTrimType) ;
	HRESULT _call SetTrimming       (BSTR bstrTrimType) ;
	HRESULT _call GetTrimming       (DWORD* pdwTrimType) ;
	HRESULT _call CalcTextSize      (BSTR bstrText, SIZE szLayout, SIZE* pszCalcOut) ;
	HRESULT _call CalcCharSize		(TCHAR tcChar,  SIZE* pszCalcOut) ;
	HRESULT _call DrawOnDC          (HDC hDC, BSTR bstrText, RECT rcRender, COLORREF clr, BYTE cAlpha) ;
	HRESULT _call DrawOnCanvas      (IUICanvas* pCanvas, BSTR bstrText, RECT rcRender, COLORREF clr, BYTE cAlpha) ;
	HRESULT _call SetAttribute      (ICVarData* pAttrData) ;

private:
	CComPtr<IUIFont>                m_pFont ;
	Gdiplus::StringAlignment        m_eStringAlignment ;
	Gdiplus::StringAlignment        m_eStringLineAlignment ;
	Gdiplus::StringTrimming         m_eStringTrimming ;
	BOOL                            m_bRightToLeft ;
	BOOL                            m_bVertical ;
	BOOL                            m_bNoWarp ;
	BOOL                            m_bLineLimit ;
} ;