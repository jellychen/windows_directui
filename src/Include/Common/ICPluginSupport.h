#pragma once

#include "Include/Common/ICFactory.h"

[
	object ,
	uuid("A13EBE27-AADF-44af-BA3F-8915C6915F5D") ,
	pointer_default(unique)
]
__interface ICPluginSupport : IDispatch
{
	HRESULT OnPluginInit	(ICFactory* factory) ;
	HRESULT OnPluginUnInit	() ;
} ;

template<typename T>
class TCustomPluginSupportImpl 
	: public IDispatchImpl<ICPluginSupport>
{
public:
	HRESULT _call OnPluginInit(ICFactory* factory)
	{
		return S_OK ;
	}

	HRESULT _call OnPluginUnInit()
	{ 
		return S_OK ;
	}
} ;
