#ifndef INCLUDE_UITL_UTILTPL_H
#define INCLUDE_UITL_UTILTPL_H
#include "Include/Util/Util.h"

#define CServicePtr CWeakPtr

namespace Common
{
	namespace Util
	{
		template<typename I_T, typename _class>
		HRESULT CreateComObject(I_T** ppObject)
		{
			if (NULL == ppObject) return E_INVALIDARG ;
			*ppObject = NULL ;
			CComObject<_class>* _p_object ;
			CComObject<_class>::CreateInstance(&_p_object) ;
			if (_p_object)
			{
				HRESULT hRet = _p_object->QueryInterface(__uuidof(I_T), (VOID**)ppObject) ;
				_p_object->Release() ;
				return hRet ;
			}
			return E_FAIL ;
		}

		template<typename T>
		HRESULT CreateObject(T** ppObject)
		{
			DEBUG_ASSERT(ppObject) ;
			IF_RETURN(NULL == ppObject, E_INVALIDARG) ;
			HRESULT _hRet = CreateObjectByIidWidthKey(__uuidof(T), (VOID**)ppObject, NULL, (LONG)::GetModuleHandle(0)) ;
			IF_RETURN(SUCCEEDED(_hRet), _hRet) ;
			return CreateObjectByIid(__uuidof(T), (VOID**)ppObject, NULL) ;
		}

		template<typename T>
		HRESULT GetService(CWeakPtr<T>* pServiceWeakPtr)
		{
			DEBUG_ASSERT(pServiceWeakPtr) ;
			IF_RETURN(NULL == pServiceWeakPtr, E_INVALIDARG) ;
			HRESULT _hRet = GetServiceByIidWidthKey( (*pServiceWeakPtr).GetSupportGuid(), 
				(*pServiceWeakPtr).GetAgentPtr(), NULL, (LONG)::GetModuleHandle(0)) ;
			IF_RETURN(SUCCEEDED(_hRet), _hRet) ;
			return GetServiceByIid((*pServiceWeakPtr).GetSupportGuid(), (*pServiceWeakPtr).GetAgentPtr(), NULL) ;
		}
	}
}
#endif//INCLUDE_UITL_UTILTPL_H