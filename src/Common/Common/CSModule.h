#pragma once

#include "Include/Def/Require.h"
#include "Include/Common/ISService.h"
#include "Include/Common/ISModule.h"

[
	default(ISModule) ,
	threading(free) ,
	uuid("E5A244E0-CD1F-4809-A519-44992FE64870") ,
	coclass
]
class ATL_NO_VTABLE CSModule
	: public TCustomServiceImpl<ISModule>
{
public:
	DECLARE_PROTECT_FINAL_CONSTRUCT() ;

public:
	HRESULT _call LoadModule(BSTR bsModulePath) ;
} ;