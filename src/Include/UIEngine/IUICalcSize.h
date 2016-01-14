#pragma once

[
	object ,
	uuid("E963BBB6-B663-47b8-BFD1-E75A47D68C6B") ,
	pointer_default(unique)
]
__interface IUICalcSize : IDispatch
{
	HRESULT CalcSize    (SIZE szOld, SIZE* pszCalcOut) ;
} ;