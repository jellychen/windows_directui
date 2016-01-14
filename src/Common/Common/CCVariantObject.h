#pragma once

class CCVariantString
{
public:
	CString	_str ;
public:
	CCVariantString(BSTR str) 
	{
		this->_str = str ;
	}
};

class CCVariantComObject
{
public:
	CComPtr<IUnknown> _ptr ;

public:
	CCVariantComObject(IUnknown* ptr)
	{
		this->_ptr = ptr ;
	}
};