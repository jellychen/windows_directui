#pragma once

#include "Include/Def/Require.h"
#include "Include/Util/UtilTpl.h"
#include "Include/UIEngine/IUIBase.h"
#include "Include/UIEngine/TUISmartPtr.h"
#include "TUIV2v.h"

template<typename IActual, typename IBase>
class TUICustomBase
	: public IDispatchImpl<IActual>
	, public IDispatchImpl<IWeakAgentSupport>
{
public:
	TUICustomBase():__self(this)
	{
		Common::Util::CreateObject(&m_pRawObject) ;
		DEBUG_ASSERT(m_pRawObject) ;
		__self.SetEntity((IActual*)this) ;
		this->m_pRawObject->SetEntity((IActual*)this) ;
	}

	HRESULT _call SetEntity(IUnknown* pEntity)
	{
		__self.SetEntity((IActual*)this) ;
		return this->m_pRawObject->SetEntity(pEntity) ;
	}

	HRESULT _call GetEntity(IUnknown** ppEntity)
	{
		return this->m_pRawObject->GetEntity(ppEntity) ;
	}

	HRESULT _call QueryAgent(IWeakAgent** ppOut)
	{
		CComQIPtr<IWeakAgentSupport> _wpSupport = m_pRawObject ;
		if (_wpSupport)
		{
			return _wpSupport->QueryAgent(ppOut) ;
		}
		return E_FAIL ;
	}

protected:
	template<typename T>T* GetEntity()
	{
		CComPtr<IUnknown> pEntity ;
		this->GetEntity(&pEntity) ;
		CComQIPtr<T> _ptr = pEntity ;
		return _ptr ;
	}

	template<typename T>T* GetInterfaceEntity(IUnknown* pUnknown)
	{
		CComQIPtr<T> _ptr = pUnknown ;
		return _ptr ;
	}
	
protected:
	TUISmartPtr<IActual, TUICustomBase>		__self ;
	CComPtr<IBase>							m_pRawObject ;
} ;