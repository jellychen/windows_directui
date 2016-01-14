#pragma once

[
	object ,
	uuid("814325CB-000D-445e-9EAB-21190A5E4472") ,
	pointer_default(unique)
]
__interface IUIBase : IDispatch
{
	HRESULT SetEntity	(IUnknown* pEntity) ;
	HRESULT GetEntity	(IUnknown** ppEntity) ;
} ;