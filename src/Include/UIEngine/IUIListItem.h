#pragma once
#include "Include/UIEngine/IUIDraw.h"
#include "Include/UIEngine/IUIControl.h"

[
	object ,
	uuid("31B0E4FF-BAA3-4268-93C1-05EE8CB54EEA") ,
	pointer_default(unique)
]
__interface IUIListItem : IUIControl
{
	HRESULT SetHostList			(IUIElement* pHostList) ;
	HRESULT SetSelected			(BOOL bSelected) ;
	HRESULT GetSelected			(BOOL* pbSelected) ;
	HRESULT SetNormalDraw		(IUIDraw* pNormalDraw) ;
	HRESULT GetNormalDraw		(IUIDraw** ppNormalDraw) ;
	HRESULT SetHighlightDraw	(IUIDraw* pHighlightDraw) ;
	HRESULT GetHighlightDraw	(IUIDraw** ppHighlightDraw) ;
	HRESULT SetDisableDraw		(IUIDraw* pDisableDraw) ;
	HRESULT GetDisableDraw		(IUIDraw** ppDisableDraw) ;
	HRESULT SetSelectedDraw		(IUIDraw* pSelectedDraw) ;
	HRESULT GetSelectedDraw		(IUIDraw** ppSelectedDraw) ;
} ;