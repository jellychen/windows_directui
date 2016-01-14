#pragma once
#include "Include/Def/Require.h"
#include "Include/UIEngine/IUIHittest.h"
#include "Include/UIEngine/IUIFrame.h"
#include "Include/UIEngine/IUIFrameInternal.h"
#include <vector>

typedef const IUIFrame* CPFRAME ;
bool _frame_compare(CPFRAME _left, CPFRAME _right) ;

[
	default(IUIHittest) ,
	threading(free) ,
	uuid("E093B174-92B0-4eff-BA5F-062F552778B4") ,
	coclass
]
class ATL_NO_VTABLE CCUIHittest
	: public IDispatchImpl<IUIHittest>
	, public IDispatchImpl<IUIAddFrame>
{
public:
	DECLARE_PROTECT_FINAL_CONSTRUCT() ;
	CCUIHittest() ;
	virtual ~CCUIHittest() ;

public:
	HRESULT _call GetHitFrame   (IUIFrame** ppFrame, BOOL bSolid) ;
	HRESULT _call AddFrameBegin () ;
	HRESULT _call AddFrame      (IUIFrame* pFrame) ;
	HRESULT _call AddFrameEnd   () ;

private:
	CComPtr<IUIFrame>           m_pFrameTemp ;
	CWeakPtr<IUIFrame>			m_pFrameAgent ;
	CComPtr<IUIFrame>           m_pSolidFrameTemp ;
	CWeakPtr<IUIFrame>			m_pSolidFrameAgent ;
} ;