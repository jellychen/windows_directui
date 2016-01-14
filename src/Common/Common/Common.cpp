// Common.cpp : DLL 导出的实现。


#include "stdafx.h"
#include "resource.h"

// 模块属性使 DllMain、DllRegisterServer 和 DllUnregisterServer 为您自动实现
[ module(dll, uuid = "{2768AE11-1B35-48AE-BA6B-E3AB172F2AAC}", 
		 name = "Common", 
		 helpstring = "Common 1.0 类型库",
		 resource_name = "IDR_COMMON") ]
class CCommonModule
{
public:
	CCommonModule()
	{
	}
};
		 
