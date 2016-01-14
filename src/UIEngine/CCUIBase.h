#pragma once

#include "Include/Def/Require.h"
#include "Include/UIEngine/IUIBase.h"

[
	default(IUIBase) ,
	threading(free) ,
	uuid("49F5DE2D-90CE-4301-9196-27BA33CC8D0D") ,
	coclass
]
class ATL_NO_VTABLE CCUIBase
	: public IDispatchImpl<IUIBase>
	, public IDispatchImpl<IWeakAgentSupport>
{
public:
	HRESULT _call QueryAgent	(IWeakAgent** ppOut) ;
	HRESULT _call SetEntity		(IUnknown* pEntity) ;
	HRESULT _call GetEntity		(IUnknown** ppEntity) ;

private:
	IUnknown*					m_pEntity ;
	CWeakAgentHost				m_pAgentHost ;
} ;