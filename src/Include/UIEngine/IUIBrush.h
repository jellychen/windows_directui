#pragma once
#include "Include/UIEngine/IUIDraw.h"

namespace BRUSH
{
	enum
	{
		RECT_FILL               = 0x0000 ,
		RECT_BORDER             = 0x0001 ,
		DOTE_RECT_BORDER        = 0x0002 ,
	} ;
}

[
	object ,
	uuid("0A8F6858-743D-433B-AE72-D08ED19271A6") ,
	pointer_default(unique)
]
__interface IUIBrush : IUIDraw
{
	HRESULT SetColor        (COLORREF clrColor) ;
	HRESULT GetColor        (COLORREF* pclrColor) ;
	HRESULT SetBrushType    (DWORD dwType) ;
	HRESULT GetBrushType    (DWORD* pdwType) ;
} ;