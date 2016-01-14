#ifndef INCLUDE_DEF_WEAKPTR_H
#define INCLUDE_DEF_WEAKPTR_H

/********IWeakAgent********/
[
	object ,
	uuid("93E95132-D41A-492d-8A0B-C6A27C57D1AA") ,
	pointer_default(unique)
]
__interface IWeakAgent : IDispatch
{
	HRESULT IsAgentVaild	(const _GUID& iid, BOOL* pbVaild) ;
	HRESULT QueryOrigin		(const _GUID& iid, VOID** ppOut) ;
} ;

/********CWeakAgent********/
class CWeakAgent
	: public CComObjectRootEx<CComMultiThreadModel>
	, public IDispatchImpl<IWeakAgent>
{
	BEGIN_COM_MAP(CWeakAgent)
		COM_INTERFACE_ENTRY(IWeakAgent)
	END_COM_MAP()
public:
	CWeakAgent(){ this->m_ptr = NULL ; }
	virtual ~CWeakAgent(){ this->m_ptr = NULL ; }

	HRESULT IsAgentVaild(const _GUID& iid, BOOL* pbVaild)
	{
		IF_RETURN(NULL == pbVaild, E_INVALIDARG) ;
		*pbVaild = FALSE ;
		IF_RETURN(NULL == this->m_ptr, S_OK) ;
		
		CComPtr<IUnknown> _ptr ;
		HRESULT _hRet = this->m_ptr->QueryInterface(iid, (VOID**)&_ptr) ;
		if (SUCCEEDED(_hRet) && _ptr)
		{
			*pbVaild = TRUE ;
		}
		return S_OK ;
	}

	HRESULT QueryOrigin(const _GUID& iid, VOID** ppOut)
	{
		IF_RETURN(NULL == ppOut, E_INVALIDARG) ;
		*ppOut = NULL ;
		IF_RETURN(NULL == this->m_ptr, S_OK) ;

		return this->m_ptr->QueryInterface(iid, ppOut) ;
	}

public:
	IUnknown* m_ptr ;
} ;


/********CWeakAgentHost********/
class CWeakAgentHost
	: public CComPtr<CWeakAgent>
{
public:
	CWeakAgentHost()
	{
		CComObject<CWeakAgent>* _object = NULL ;
		CComObject<CWeakAgent>::CreateInstance(&_object) ;
		if (NULL != _object)
		{
			p = _object ;
			p->AddRef() ;
		}
	}

	virtual ~CWeakAgentHost()
	{
		p->m_ptr = NULL ;
	}

	HRESULT SetOrigin(IUnknown* pOrigin)
	{
		IF_RETURN(NULL == pOrigin, E_INVALIDARG) ;
		p->m_ptr = pOrigin ;
		return S_OK ;
	}
} ;

/********CWeakAgentHost********/
[
	object ,
	uuid("38F03DF8-AE0B-4D6C-8072-6FEF4CD51A58") ,
	pointer_default(unique)
]
__interface IWeakAgentSupport : IDispatch
{
	HRESULT QueryAgent(IWeakAgent** ppOut) ;
} ;

/********TCustomWeakAgentSupport********/
template<typename T>
class TCustomWeakAgentSupport
	: public IDispatchImpl<IWeakAgentSupport>
	, public IDispatchImpl<T>
{
public:
	TCustomWeakAgentSupport()
	{
		this->m_selfWeakAgent.SetOrigin((IUnknown*)(T*)this) ;
	}

	HRESULT QueryAgent(IWeakAgent** ppOut)
	{
		IF_RETURN(NULL == ppOut, E_INVALIDARG) ;
		*ppOut = NULL ;
		CComPtr<IWeakAgent> pWeakAgent = this->m_selfWeakAgent ;
		if (pWeakAgent)
		{
			return pWeakAgent->QueryInterface(__uuidof(IWeakAgent), (VOID**)ppOut) ;	
		}
		return S_OK ;
	}

private:
	CWeakAgentHost m_selfWeakAgent ;
} ;

/********CBaseWeakPtr********/
template<typename T>
class CWeakPtr
{
public:
	CWeakPtr(){}

	template<typename _T1>
	CWeakPtr(const CWeakPtr<_T1>& ptr)
	{
		if (ptr.m_pWeakAgent)
		{
			CComPtr<T> _ptr ;
			CComPtr<IWeakAgent> _pAgent = ptr.m_pWeakAgent ;
			HRESULT _hRet = _pAgent->QueryOrigin(__uuidof(T), (VOID**)&_ptr) ;
			if (_ptr && SUCCEEDED(_hRet))
			{
				this->m_pWeakAgent = _pAgent ;
			}
		}
	}

	CWeakPtr(const CComPtr<IWeakAgent> ptr)
	{
		IF_RETURN_VOID(NULL == ptr) ;

		CComPtr<T> _ptr ;
		HRESULT _hRet = ptr->QueryOrigin(__uuidof(T), (VOID**)&_ptr) ;
		IF_RETURN_VOID(NULL == _ptr || !SUCCEEDED(_hRet)) ;

		this->m_pWeakAgent = ptr ;
	}

	CWeakPtr(IUnknown* ptr)
	{
		this->Free() ;
		CComQIPtr<IWeakAgentSupport> _wpSupport = ptr ;
		if (NULL != ptr && _wpSupport)
		{
			_wpSupport->QueryAgent(&m_pWeakAgent) ;
		}
	}

	GUID GetSupportGuid()
	{
		return __uuidof(T) ;
	}

	IWeakAgent** GetAgentPtr()
	{
		return &m_pWeakAgent ;
	}

	IWeakAgent* GetAgent()
	{
		return this->m_pWeakAgent ;
	}
	
	operator bool ()
	{
		BOOL bIsValid = FALSE ;
		if (this->m_pWeakAgent)
		{
			this->m_pWeakAgent->IsAgentVaild(__uuidof(T), &bIsValid) ;
		}
		return TRUE == bIsValid ;
	}

	operator T* ()
	{
		CComPtr<T> _ptr ;
		if (this->m_pWeakAgent)
		{
			this->m_pWeakAgent->QueryOrigin(__uuidof(T), (VOID**)&_ptr) ;
		}
		return _ptr ;
	}

	operator IWeakAgent* ()
	{
		return this->m_pWeakAgent ;
	}

	void operator = (const int _null)
	{
		if (0 == _null)
		{
			this->Free() ;
		}
	}

	void operator = (IUnknown* _ptr)
	{
		this->Free() ;
		CComQIPtr<IWeakAgentSupport> _wpSupport = _ptr ;
		if (NULL != _ptr && _wpSupport)
		{
			_wpSupport->QueryAgent(&m_pWeakAgent) ;
		}
	}

	template<typename _T1>
	void operator = (const CWeakPtr<_T1> ptr)
	{
		this->Free() ;
		
		if (ptr.m_pWeakAgent)
		{
			CComPtr<T> _ptr ;
			CComPtr<IWeakAgent> _pAgent = ptr.m_pWeakAgent ;
			HRESULT _hRet = _pAgent->QueryOrigin(__uuidof(T), (VOID**)&_ptr) ;
			if (_ptr && SUCCEEDED(_hRet))
			{
				this->m_pWeakAgent = _pAgent ;
			}
		}
	}

	bool operator == (IWeakAgent* ptr)
	{
		return ptr == this->m_pWeakAgent ;
	}

	T* operator -> ()
	{
		DEBUG_ASSERT_MSG(m_pWeakAgent, _T("Error: Agent Crash...! Please check...")) ;
		IF_RETURN(NULL == this->m_pWeakAgent, NULL) ;

		CComPtr<T> _ptr ;
		this->m_pWeakAgent->QueryOrigin(__uuidof(T), (VOID**)&_ptr) ;
		DEBUG_ASSERT_MSG(_ptr, _T("Error: Agent Crash...! Please check...")) ;
		return _ptr ;
	}

	BOOL Promote(const GUID& _guid, VOID** pptr)
	{
		DEBUG_ASSERT(pptr) ;
		IF_RETURN(NULL == pptr, E_INVALIDARG) ;
		*pptr = NULL ;
		IF_RETURN(NULL == this->m_pWeakAgent, FALSE) ;

		return S_OK == this->m_pWeakAgent->QueryOrigin(_guid, (VOID**)pptr) ;
	}

	template<typename _T1>
	BOOL TPromote(_T1** pptr)
	{
		DEBUG_ASSERT(pptr) ;
		IF_RETURN(NULL == pptr, E_INVALIDARG) ;

		return S_OK == this->Promote(__uuidof(_T1), (VOID**)pptr) ;
	}

	VOID Free()
	{
		this->m_pWeakAgent = NULL ;
	}

public:
	CComPtr<IWeakAgent> m_pWeakAgent ;
} ;

#endif//INCLUDE_DEF_WEAKPTR_H