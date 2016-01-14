#pragma once
#include "Include/UIEngine/IUIFont.h"
#include "Include/UIEngine/IUICanvas.h"

namespace TEXT
{
	enum
	{
		ALI_NEAR            = 0X0001 ,
		ALI_CENTER          = 0X0002 ,
		ALI_FAR             = 0X0003 ,
	} ;

	enum
	{
		TRIM_NONE           = 0X0000 ,
		TRIM_CHAR           = 0X0001 ,
		TRIM_WORD           = 0X0002 ,
		TRIM_ELLIPSIS_WORD  = 0X0003 ,
	} ;
}

[
	object ,
	uuid("01595DF1-DA93-4AE2-B8E9-728CA7C46A4C") ,
	pointer_default(unique)
]
__interface IUIText : IDispatch
{
	HRESULT SetFont             (IUIFont* pFont) ;
	HRESULT GetFont             (IUIFont** ppFont) ;
	HRESULT SetAlignment        (DWORD dwAligment) ;
	HRESULT GetAlignment        (DWORD* pdwAligment) ;
	HRESULT SetLineAlignment    (DWORD dwAligment) ;
	HRESULT GetLineAlignment    (DWORD* pdwAligment) ;
	HRESULT SetRightToLeft      (BOOL bRightToLeft) ;
	HRESULT GetRightTopLeft     (BOOL* pbRightToLeft) ;
	HRESULT SetVertical         (BOOL bVertical) ;
	HRESULT GetVertical         (BOOL* pbVertical) ;
	HRESULT SetNoWarp           (BOOL bNoWarp) ;
	HRESULT GetNoWarp           (BOOL* pbNoWarp) ;
	HRESULT SetLineLimit        (BOOL bLimitLine) ;
	HRESULT GetLineLimit        (BOOL* pbLimitLine) ;
	HRESULT SetTrimming         (DWORD dwTrimType) ;
	HRESULT GetTrimming         (DWORD* pdwTrimType) ;

	HRESULT CalcTextSize        (BSTR bstrText, SIZE szLayout, SIZE* pszCalcOut) ;
	HRESULT CalcCharSize		(TCHAR tcChar,  SIZE* pszCalcOut) ;
	HRESULT DrawOnDC            (HDC hDC, BSTR bstrText, RECT rcRender, COLORREF clr, BYTE cAlpha) ;
	HRESULT DrawOnCanvas        (IUICanvas* pCanvas, BSTR bstrText, RECT rcRender, COLORREF clr, BYTE cAlpha) ;
} ;