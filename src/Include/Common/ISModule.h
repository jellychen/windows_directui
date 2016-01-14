#pragma once

[
	object ,
	uuid("D9E92111-265D-4801-A65C-9FE43EAF0EF2") ,
	pointer_default(unique)
]
__interface ISModule : IDispatch
{
	HRESULT LoadModule	(BSTR bsModulePath) ;
} ;