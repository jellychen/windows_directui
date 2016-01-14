#pragma once

[
	object ,
	uuid("9FBD03DD-6622-4025-A805-DF3887156D12") ,
	pointer_default(unique)
]
__interface ISTaskHostAgent : IDispatch
{
	HRESULT AddHostAgent	(INT nHostId, IUnknown* pHost) ;
	HRESULT DelHostAgent	(INT nHostId) ;
	HRESULT AddHostProtect	(INT nHostId) ;
	HRESULT DelHostProtect	(INT nHostId) ;
} ;