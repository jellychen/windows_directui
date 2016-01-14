#pragma once

[
	object ,
	uuid("4D38BD7B-4835-4855-BF49-1DF718CC630C") ,
	pointer_default(unique)
]
__interface ISPlugin : IDispatch
{
	HRESULT LoadPlugin		() ;
	HRESULT UnLoadPlugin	() ;
} ;