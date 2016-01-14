#pragma once

template<typename IActual, typename CHost>
class TUISmartPtr
{
public:
	TUISmartPtr(CHost* pHost)
	{
		this->m_pEntity = NULL ;
		this->m_pSmartPtr = NULL ;
		this->m_pHost = pHost ;
	}

	bool SetEntity(IUnknown* pEntity)
	{
		this->m_pEntity = pEntity ;
		return true ;
	}

	operator bool()
	{
		if (NULL == this->m_pSmartPtr && this->m_pEntity)
		{
			CComPtr<IActual> _ptr ;
			this->m_pEntity->QueryInterface(__uuidof(IActual), (VOID**)&_ptr) ;
			this->m_pSmartPtr = _ptr ;
		}
		return NULL != this->m_pSmartPtr ;
	}

	IActual* operator->()
	{
		/*
		if (NULL == this->m_pSmartPtr && this->m_pEntity)
		{
			CComPtr<IActual> _ptr ;
			this->m_pEntity->QueryInterface(__uuidof(IActual), (VOID**)&_ptr) ;
			this->m_pSmartPtr = _ptr ;
		}
		return this->m_pSmartPtr ;
		*/

		CComPtr<IUnknown> _pUnknow ;
		m_pHost->GetEntity(&_pUnknow) ;
		CComPtr<IActual> _ptr ;
		_pUnknow->QueryInterface(__uuidof(IActual), (VOID**)&_ptr) ;
		return _ptr ;
	}

private:
	IActual*    m_pSmartPtr ;
	IUnknown*   m_pEntity ;
	CHost*		m_pHost ;
} ;