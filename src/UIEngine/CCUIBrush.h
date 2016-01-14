#pragma once
#include "Include/Common/ICStruct.h"
#include "Include/UIEngine/IUIBrush.h"
#include "Include/UIEngine/IUIAttribute.h"
#include "Include/UIEngine/TUIV2v.h"
#include <GdiPlus.h>

[
	default(IUIBrush) ,
	threading(free) ,
	uuid("9C4B9085-E329-496f-9484-1A5FC221ABB1") ,
	coclass
]
class ATL_NO_VTABLE CCUIBrush
	: public IDispatchImpl<IUIBrush>
	, public IDispatchImpl<IUIAttribute>
{
public:
	DECLARE_PROTECT_FINAL_CONSTRUCT() ;
	CCUIBrush() ;
	virtual ~CCUIBrush() ;

public:
	HRESULT _call SetColor      (COLORREF clrColor) ;
	HRESULT _call GetColor      (COLORREF* pclrColor) ;
	HRESULT _call SetBrushType  (DWORD dwType) ;
	HRESULT _call SetBrushType  (BSTR bstrType) ;
	HRESULT _call GetBrushType  (DWORD* pdwType) ;
	HRESULT _call GetSize       (SIZE* pszDraw) ;
	HRESULT _call DrawOnDC      (HDC hDC, RECT rcDraw, BYTE cAlpha) ;
	HRESULT _call DrawOnCanvas  (IUICanvas* pCanvas, RECT rcDraw, BYTE cAlpha) ;
	HRESULT _call SetAttribute  (ICVarData* pAttrData) ;

private:
	COLORREF                    m_clrColor ;
	DWORD                       m_dwBrushType ;
} ;