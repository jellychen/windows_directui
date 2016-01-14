#pragma once

[
	object ,
	uuid("5DF1D3F2-2067-4cd2-9455-20DC5CE3B189") ,
	pointer_default(unique)
]
__interface ISServiceDependent : IDispatch
{
	HRESULT BaseOn			(REFIID iid, REFIID riid) ;
} ;

[
	object ,
	uuid("E8824A4B-C454-43c5-95ED-0734258B8029") ,
	pointer_default(unique)
]
__interface ISServiceBase : IDispatch
{
	HRESULT OnInit			() ;
	HRESULT OnUnInit		() ;
	HRESULT OnDependent		(ISServiceDependent* pServiceDependent) ;
} ;

template<typename _T>
class TCustomServiceImpl
	: public IDispatchImpl<ISServiceBase>
	, public TCustomWeakAgentSupport<_T>
{
public:
	HRESULT _call OnInit		(){ return S_OK ;}
	HRESULT _call OnUnInit		(){ return S_OK ;}
	HRESULT _call OnDependent	(ISServiceDependent* pServiceDependent){ return S_OK ;}
} ;

template<typename _T>
class CSServicePtr : public CWeakPtr<_T>
{
} ;