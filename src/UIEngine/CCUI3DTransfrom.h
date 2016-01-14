#pragma once
#include "Include/Def/Require.h"
#include "Include/Util/Utiltpl.h"
#include "Include/UIEngine/IUI3DTransfrom.h"
#include "Include/UIEngine/IUICanvas.h"
#include "Include/UIEngine/TUICustomControl.h"

[
	default(IUI3DTransfrom) ,
	threading(free) ,
	uuid("16793B15-E911-416a-A46D-B78750F871D5") ,
	coclass
]
class ATL_NO_VTABLE CCUI3DTransfrom
	: public IDispatchImpl<IUI3DTransfrom>
{
public:
	DECLARE_PROTECT_FINAL_CONSTRUCT() ;
	CCUI3DTransfrom() ;
	virtual ~CCUI3DTransfrom() ;

public:
	HRESULT _call SetOffsetZ		(INT nOffsetZ) ;
	HRESULT _call GetOffsetZ		(INT* pnOffsetZ) ;
	HRESULT _call SetRotateX		(INT nRotateX) ;
	HRESULT _call GetRotateX		(INT* pnRotateX) ;
	HRESULT _call SetRotateY		(INT nRotateY) ;
	HRESULT _call GetRotateY		(INT* pnRotateY) ;
	HRESULT _call SetRotateZ		(INT nRotateZ) ;
	HRESULT _call GetRotateZ		(INT* pnRotateZ) ;
	HRESULT _call GetNeedTransfrom	(BOOL* pbNeedTransfrom) ;
	HRESULT _call CanvasTransfrom	(IUICanvas* pInCanvas, IUICanvas* pOutCanvas) ;

private:
	INT								m_nOffsetZ ;
	INT								m_nRotateX ;
	INT								m_nRotateY ;
	INT								m_nRotateZ ;
} ;
