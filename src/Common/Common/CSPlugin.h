#pragma once

#include "Include/Def/Require.h"
#include "Include/Common/ISService.h"
#include "Include/Common/ISPlugin.h"

[
	default(ISPlugin) ,
	threading(free) ,
	uuid("33E53EE3-D8BA-415f-B8EB-532E1391F820") ,
	coclass
]
class ATL_NO_VTABLE CSPlugin 
	: public TCustomServiceImpl<ISPlugin>
{
public:
	DECLARE_PROTECT_FINAL_CONSTRUCT() ;
	CSPlugin() ;
	virtual ~CSPlugin() ;


	HRESULT _call LoadPlugin()
	{
		::MessageBox(NULL, _T("11"), _T("22"), MB_OK) ;
		return S_OK ;
	}

	HRESULT _call UnLoadPlugin()
	{
		return S_OK ;
	}
} ;