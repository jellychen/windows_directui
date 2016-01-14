#pragma once
#include "Include/UIEngine/IUIControl.h"
#include "Include/UIEngine/IUIScroll.h"
#include "Include/UIEngine/IUIListItem.h"

[
	object ,
	uuid("C76E86E6-3534-41f4-BBAB-54DFCF6A0FB8") ,
	pointer_default(unique)
]
__interface IUIList : IUIControl
{
	HRESULT SetVScroll			(IUIScroll* pScroll) ;
	HRESULT GetVScroll			(IUIScroll** ppScroll) ;
	HRESULT SetItemFixHeight	(BOOL bFixHeight) ;
	HRESULT GetItemFixHeight	(BOOL* pbFixHeight) ;
	HRESULT SetItemHeight		(INT nHeight) ;
	HRESULT GetItemHeight		(INT* pnHeight) ;

	HRESULT AddItem				(IUIListItem* pListItem) ;
	HRESULT InsertItem			(IUIListItem* pListItem) ;
	HRESULT DelItem				(INT nIndex) ;
	HRESULT GetItemCount		(INT* pCount) ;
	HRESULT GetItemByIndex		(INT nIndex, IUIListItem** ppListItem) ;
} ;