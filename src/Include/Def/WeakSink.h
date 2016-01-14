#ifndef INCLUDE_DEF_WEAKSINK_H
#define INCLUDE_DEF_WEAKSINK_H

#define COMMON_SINK_BEGIN(SINK_NAME)                                        \
	template<typename CHost, typename ISink>                                \
	class SINK_NAME                                                         \
		: public CComObjectRootEx<CComMultiThreadModel>                     \
		, public IDispatchImpl<ISink>                                       \
	{                                                                       \
		BEGIN_COM_MAP(SINK_NAME)                                            \
			COM_INTERFACE_ENTRY(ISink)                                      \
		END_COM_MAP()                                                       \
	public:                                                                 \
		SINK_NAME()                                                         \
		{                                                                   \
			memset((BYTE*)&m_pHost, 0,                                      \
				sizeof(*this) - ((BYTE*)&m_pHost - (BYTE*)this)) ;          \
		}                                                                   \
		virtual ~SINK_NAME()                                                \
		{                                                                   \
		}                                                                   \
		HRESULT UnHookAll()                                                 \
		{                                                                   \
			BYTE* start = (BYTE*)(&m_pHost + 1) ;                           \
			BYTE* end = (BYTE*)this + sizeof(*this) ;                       \
			for (BYTE* pb = start; pb != end; ++pb)                         \
			{                                                               \
				*pb = NULL ;                                                \
			}                                                               \
			return S_OK ;                                                   \
		}                                                                   \
	public:                                                                 \
		CHost* m_pHost ;

#define COMMON_SINK_END()                                                   \
	} ;

#define COMMON_SINK_FUNC_RET(RET, NAME, PARAM, ARG)                         \
	public:                                                                 \
		typedef RET (CHost::*F##NAME) PARAM ;                               \
		HRESULT Hook_##NAME(F##NAME pf##NAME)                               \
		{                                                                   \
			this->m_pf##NAME = pf##NAME ;                                   \
			return S_OK ;                                                   \
		}                                                                   \
		HRESULT UnHook_##NAME()                                             \
		{                                                                   \
			this->m_pf##NAME = NULL ;                                       \
			return S_OK ;                                                   \
		}                                                                   \
		virtual RET __stdcall NAME PARAM                                    \
		{                                                                   \
			if (this->m_pHost && this->m_pf##NAME)                          \
			{                                                               \
				return ((this->m_pHost)->*(m_pf##NAME))ARG ;                \
			}                                                               \
			return RET(-1) ;                                                \
		}                                                                   \
	private:                                                                \
		F##NAME m_pf##NAME ;

#define COMMON_SINK_FUNC(NAME, PARAM, ARG)                                  \
	COMMON_SINK_FUNC_RET(HRESULT, NAME, PARAM, ARG)

#define DECLARE_COMMON_SINK_PTR(SINK_NAME, ISink)                           \
	template<class CHost>                                                   \
	class SINK_NAME##Ptr : public CComPtr<SINK_NAME<CHost, ISink>>          \
	{                                                                       \
		typedef SINK_NAME<CHost, ISink> SinkType ;                          \
	public:                                                                 \
		SINK_NAME##Ptr(CHost *pHost)                                        \
		{                                                                   \
			CComObject<SINK_NAME<CHost, ISink>>*pObject = NULL ;            \
			CComObject<SINK_NAME<CHost, ISink>>::CreateInstance(&pObject) ; \
			if (pObject)                                                    \
			{                                                               \
				p = pObject ;                                               \
				p->AddRef() ;                                               \
				p->m_pHost = pHost ;                                        \
			}                                                               \
		}                                                                   \
		SinkType* operator= (SinkType* lp) throw()                          \
		{                                                                   \
			if (p && *this != lp)                                           \
			{                                                               \
				p->m_pHost = NULL ;                                         \
				p->UnHookAll() ;                                            \
			}                                                               \
			return CComPtr<SinkType>::operator = (lp) ;                     \
		}                                                                   \
		virtual ~SINK_NAME##Ptr()                                           \
		{                                                                   \
			if (p)                                                          \
			{                                                               \
				p->m_pHost = NULL ;                                         \
			}                                                               \
		}                                                                   \
	} ;
#endif//INCLUDE_DEF_WEAKSINK_H