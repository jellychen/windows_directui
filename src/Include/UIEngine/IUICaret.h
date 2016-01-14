#pragma once
#include "Include/UIEngine/IUIControl.h"
#include "Include/UIEngine/IUIDraw.h"

[
	object ,
	uuid("82B0BE5C-1AA9-4ac1-8085-8B89AFD2439D") ,
	pointer_default(unique)
]
__interface IUICaret : IUIControl
{
	HRESULT SetBlinkTime    (DWORD dwBlink) ;
	HRESULT GetBlinkTime    (DWORD* pdwBlink) ;
	HRESULT SetCaretDraw    (IUIDraw* pDraw) ;
	HRESULT GetCaretDraw    (IUIDraw** ppDraw) ;
	HRESULT SetBlink		(BOOL bBlink) ;
	HRESULT GetBlink		(BOOL* bBlink) ;
	HRESULT ShowCaret       () ;
	HRESULT HideCaret       () ;
} ;