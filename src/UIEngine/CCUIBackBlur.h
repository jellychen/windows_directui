#pragma once
#include "Include/UIEngine/IUIBackBlur.h"
#include "Include/UIEngine/IUICanvas.h"
#include "Include/UIEngine/TUICustomControl.h"
#include "Include/UIEngine/TUIUtil.h"

[
	default(IUIBackBlur) ,
	threading(free) ,
	uuid("A2F55359-A080-435b-8A8C-649D7B75C8E8") ,
	coclass
]
class ATL_NO_VTABLE CCUIBackBlur
	: public TUICustomControl<IUIBackBlur, IUIControl>
{
public:
	CCUIBackBlur() ;
	virtual ~CCUIBackBlur() ;
	HRESULT FinalConstruct() ;

public:
	HRESULT _call SetRadius		(INT nRadius) ;
	HRESULT _call GetRadius		(INT* pnRadius) ;
	HRESULT _call Draw			(IUICanvas* pCanvas) ;
	HRESULT _call Render		(IUICanvas* pCanvas, RECT rcRender, INT nState) ;
	HRESULT _call SetAttribute	(ICVarData* pAttrData) ;
	HRESULT _call OnMessage		(IUIFrame* pTarget, tMsgArg* pArg) ;
private:
	BOOL	_blur				(IUICanvas* pCanvas) ;

private:
	BOOL						m_bLBtnDown ;
	CPoint						m_ptLBtnDownPoint ;
	INT							m_nRadius ;
	CComPtr<IUICanvas>			m_pCanvas ;
} ;