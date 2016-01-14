#pragma once
#include "Include/UIEngine/IUICanvas.h"

[
	object ,
	uuid("4E2F9608-834B-4210-9EDE-AB5708E90121") ,
	pointer_default(unique)
]
__interface IUIDraw : IDispatch
{
	HRESULT GetSize         (SIZE* pszDraw) ;
	HRESULT DrawOnDC        (HDC hDC, RECT rcDraw, BYTE cAlpha) ;
	HRESULT DrawOnCanvas    (IUICanvas* pCanvas, RECT rcDraw, BYTE cAlpha) ;
} ;