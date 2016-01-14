#include "Include/Def/Require.h"
#include "Include/BaseMisc/ICTest.h"

[
	default(ICBaseTest) ,
	threading(free) ,
	uuid("2994642D-F858-4d77-9B8D-59A03641BA15") ,
	coclass
]
class ATL_NO_VTABLE CCBaseTest 
	: public TCustomWeakAgentSupport<ICBaseTest>
	, public IDispatchImpl<ICBaseTestB>
{
public:
	CCBaseTest()
	{
	}

	~CCBaseTest()
	{

	}
	HRESULT _call Test	() ;
	HRESULT _call Test2	() ;
} ;