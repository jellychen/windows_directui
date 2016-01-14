#include "stdafx.h" 
#include "CCBaseTest.h"

HRESULT CCBaseTest::Test()
{
	::MessageBox(NULL , _T("11"), _T("34"), MB_OK) ;
	return S_OK ;
}

HRESULT CCBaseTest::Test2()
{
	::MessageBox(NULL , _T("111111111111"), _T("341111111111"), MB_OK) ;
	return S_OK ;
}