#pragma once

namespace V2V
{
	template<typename T> BYTE BSTR2BYTE(BSTR bstrVal)
	{
		return (BYTE)_wtoi(bstrVal) ;
	}

	template<typename T> INT BSTR2INT(BSTR bstrVal)
	{
		return _wtoi(bstrVal) ;
	}

	template<typename T> UINT BSTR2UINT(BSTR bstrVal)
	{
		return (UINT)_wtoi(bstrVal) ;
	}

	template<typename T> LONG BSTR2LONG(BSTR bstrVal)
	{
		return (LONG)_wtol(bstrVal) ;
	}

	template<typename T> DWORD BSTR2DWORD(BSTR bstrVal)
	{
		return (DWORD)_wtol(bstrVal) ;
	}

	template<typename T> INT64 BSTR2INT64(BSTR bstrVal)
	{
		return _wtoi64(bstrVal) ;
	}

	template<typename T> FLOAT BSTR2FLOAT(BSTR bstrVal)
	{
		return (FLOAT)_wtof(bstrVal) ;
	}

	template<typename T> DOUBLE BSTR2DOUBLE(BSTR bstrVal)
	{
		return (DOUBLE)_wtof(bstrVal) ;
	}

	template<typename T> BOOL BSTR2BOOL(BSTR bstrVal)
	{
		CString cstrVal(bstrVal) ;
		return cstrVal.CompareNoCase(_T("True")) == 0 ;
	}

	template<typename T> COLORREF BSTR2COLORREF(BSTR bstrVal)
	{
		INT r, g, b;
		swscanf_s(bstrVal, _T("%d,%d,%d"), &r, &g, &b) ;
		return RGB(r, g, b) ;
	}

	template<typename T> POINT BSTR2POINT(BSTR bstrVal)
	{
		POINT pt ;
		swscanf_s(bstrVal, _T("%d,%d"), &pt.x, &pt.y) ;
		return pt ;
	}

	template<typename T> SIZE BSTR2SIZE(BSTR bstrVal)
	{
		SIZE sz ;
		swscanf_s(bstrVal, _T("%d,%d"), &sz.cx, &sz.cy) ;
		return sz ;
	}

	template<typename T> RECT BSTR2RECT(BSTR bstrVal)
	{
		RECT rc ;
		swscanf_s(bstrVal, _T("%d,%d,%d,%d"), 
			&rc.left, &rc.top, &rc.right, &rc.bottom) ;
		return rc ;
	}
}

#define SET_ATTR_INTERFACE_BEGIN(_attr, _interface)								\
{                                                                               \
	IF_RETURN(NULL == _attr, E_INVALIDARG) ;                                    \
	CComPtr<ICVarData> _pAttr = _attr ;                                         \
	CComQIPtr<_interface> _ptr = GetEntity<_interface>() ;                      \
	IF_RETURN(NULL == _ptr, E_FAIL) ;                                           \

#define SET_ATTR_CLASS_BEGIN(_attr, _class)										\
{                                                                               \
	IF_RETURN(NULL == _attr, E_INVALIDARG) ;                                    \
	CComPtr<ICVarData> _pAttr = _attr ;											\
	_class* _ptr = this ;                                                       \

#define SET_ATTR_END()															\
}

#define SET_ATTR(type, field)                                                       \
    SET_ATTR_##TYPE(field) ;

#define SET_ATTR_BOOL(field)                                                        \
    {                                                                               \
        CComBSTR field ;                                                            \
        if (SUCCEEDED(_pAttr->GetString(CComBSTR(L#field), &field)))                \
        {                                                                           \
            _ptr->Set##field(V2V::BSTR2BOOL<VOID>(field)) ;                         \
        }                                                                           \
    }

#define SET_ATTR_BSTR(field)                                                        \
    {                                                                               \
        CComBSTR field ;                                                            \
        if (SUCCEEDED(_pAttr->GetString(CComBSTR(L#field), &field)))                \
        {                                                                           \
            _ptr->Set##field(field) ;                                               \
        }                                                                           \
    }

#define SET_ATTR_BYTE(field)                                                        \
    {                                                                               \
        CComBSTR field ;                                                            \
        if (SUCCEEDED(_pAttr->GetString(CComBSTR(L#field), &field)))                \
        {                                                                           \
            _ptr->Set##field(V2V::BSTR2BYTE<VOID>(field)) ;                         \
        }                                                                           \
    }

#define SET_ATTR_INT(field)                                                         \
    {                                                                               \
        CComBSTR field ;                                                            \
        if (SUCCEEDED(_pAttr->GetString(CComBSTR(L#field), &field)))                \
        {                                                                           \
            _ptr->Set##field(V2V::BSTR2INT<VOID>(field)) ;                          \
        }                                                                           \
    }

#define SET_ATTR_DWORD(field)                                                       \
    {                                                                               \
        CComBSTR field ;                                                            \
        if (SUCCEEDED(_pAttr->GetString(CComBSTR(L#field), &field)))                \
        {                                                                           \
            _ptr->Set##field(V2V::BSTR2DWORD<VOID>(field)) ;                        \
        }                                                                           \
    }

#define SET_ATTR_UINT(field)                                                        \
    {                                                                               \
        CComBSTR field ;                                                            \
        if (SUCCEEDED(_pAttr->GetString(CComBSTR(L#field), &field)))                \
        {                                                                           \
            _ptr->Set##field(V2V::BSTR2UINT<VOID>(field)) ;                         \
        }                                                                           \
    }

#define SET_ATTR_LONG(field)                                                        \
    {                                                                               \
        CComBSTR field ;                                                            \
        if (SUCCEEDED(_pAttr->GetString(CComBSTR(L#field), &field)))                \
        {                                                                           \
            _ptr->Set##field(V2V::BSTR2LONG<VOID>(field)) ;                         \
        }                                                                           \
    }

#define SET_ATTR_FLOAT(field)                                                       \
    {                                                                               \
        CComBSTR field ;                                                            \
        if (SUCCEEDED(_pAttr->GetString(CComBSTR(L#field), &field)))                \
        {                                                                           \
            _ptr->Set##field(V2V::BSTR2FLOAT<VOID>(field)) ;                        \
        }                                                                           \
    }

#define SET_ATTR_DOUBLE(field)                                                      \
    {                                                                               \
        CComBSTR field ;                                                            \
        if (SUCCEEDED(_pAttr->GetString(CComBSTR(L#field), &field)))                \
        {                                                                           \
            _ptr->Set##field(V2V::BSTR2DOUBLE<VOID>(field)) ;                       \
        }                                                                           \
    }

#define SET_ATTR_POINT(field)                                                       \
    {                                                                               \
        CComBSTR field ;                                                            \
        if (SUCCEEDED(_pAttr->GetString(CComBSTR(L#field), &field)))                \
        {                                                                           \
            _ptr->Set##field(V2V::BSTR2POINT<VOID>(field)) ;                        \
        }                                                                           \
    }

#define SET_ATTR_SIZE(field)                                                        \
    {                                                                               \
        CComBSTR field ;                                                            \
        if (SUCCEEDED(_pAttr->GetString(CComBSTR(L#field), &field)))                \
        {                                                                           \
            _ptr->Set##field(V2V::BSTR2SIZE<VOID>(field)) ;                         \
        }                                                                           \
    }

#define SET_ATTR_RECT(field)                                                        \
    {                                                                               \
        CComBSTR field ;                                                            \
        if (SUCCEEDED(_pAttr->GetString(CComBSTR(L#field), &field)))                \
        {                                                                           \
            _ptr->Set##field(V2V::BSTR2RECT<VOID>(field)) ;                         \
        }                                                                           \
    }

#define SET_ATTR_COLORREF(field)                                                    \
    {                                                                               \
        CComBSTR field ;                                                            \
        if (SUCCEEDED(_pAttr->GetString(CComBSTR(L#field), &field)))                \
        {                                                                           \
            _ptr->Set##field(V2V::BSTR2COLORREF<VOID>(field)) ;                     \
        }                                                                           \
    }

#define SET_ATTR_INTERFACE(_interface, field)                                       \
    {                                                                               \
        CComPtr<_interface> pInterface ;                                            \
        if (SUCCEEDED(_pAttr->GetInterface(CComBSTR(L#field),                       \
         __uuidof(_interface), (VOID**)&pInterface)))                               \
        {                                                                           \
            _ptr->Set##field(pInterface) ;                                          \
        }                                                                           \
    }
