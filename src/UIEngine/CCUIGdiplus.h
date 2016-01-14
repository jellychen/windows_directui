#pragma once

#include <GdiPlus.h>
#pragma comment(lib,"GdiPlus.lib")

class CCUIGdiplus
{
public:
	CCUIGdiplus() ;
	virtual ~CCUIGdiplus() ;

private:
	ULONG_PTR   m_gdiplus_token ; 
} ;