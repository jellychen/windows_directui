#pragma once
#include "Include/Def/Require.h"
#include "Include/Util/Utiltpl.h"
#include "Include/UIEngine/IUIList.h"
#include "Include/UIEngine/IUIFrameDef.h"
#include "Include/UIEngine/TUICustomControl.h"
#include <vector>

[
	default(IUIList) ,
	threading(free) ,
	uuid("F6FF79EA-C81B-4877-A0DA-4A8CBE713EF4") ,
	coclass
]
class ATL_NO_VTABLE CCUIList
	: public TUICustomControl<IUIList, IUIControl>
{
public:
	DECLARE_PROTECT_FINAL_CONSTRUCT() ;
	CCUIList() ;
	virtual ~CCUIList() ;
	HRESULT FinalConstruct() ;

	typedef std::vector<CComPtr<IUIListItem>> VEC_ITEMS ;
public:
	HRESULT _call SetVScroll		(IUIScroll* pScroll) ;
	HRESULT _call GetVScroll		(IUIScroll** ppScroll) ;
	HRESULT _call SetItemFixHeight	(BOOL bFixHeight) ;
	HRESULT _call GetItemFixHeight	(BOOL* pbFixHeight) ;
	HRESULT _call SetItemHeight		(INT nHeight) ;
	HRESULT _call GetItemHeight		(INT* pnHeight) ;
	HRESULT _call AddItem			(IUIListItem* pListItem) ;
	HRESULT _call InsertItem		(IUIListItem* pListItem) ;
	HRESULT _call DelItem			(INT nIndex) ;
	HRESULT _call GetItemCount		(INT* pCount) ;
	HRESULT _call GetItemByIndex	(INT nIndex, IUIListItem** ppListItem) ;

private:
	INT		_calc_content_height	() ;

private:
	INT								m_nOffset ;
	BOOL							m_bFixHeight ;
	INT								m_nFixHeight ;
	VEC_ITEMS						m_vecItems ;
	CComPtr<IUIScroll>				m_pScrollView ;
} ;