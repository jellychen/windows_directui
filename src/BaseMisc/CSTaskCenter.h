#pragma once

#include "Include/Def/Require.h"
#include "Include/Common/ISService.h"
#include "Include/BaseMisc/ISTaskCenter.h"
#include "CTaskRunnable.h"
#include <map>

[
	default(ISTaskCenter) ,
	threading(free) ,
	uuid("6489FA4B-31EC-48c0-8112-9021EFA35EF4") ,
	coclass
]
class ATL_NO_VTABLE CSTaskCenter 
	: public TCustomServiceImpl<ISTaskCenter>
	, public CRITICAL_SECTION
{
public:
	DECLARE_PROTECT_FINAL_CONSTRUCT() ;
	CSTaskCenter() ;
	virtual ~CSTaskCenter() ;

public:
	HRESULT _call PostTask		(BSTR bstrId, ITask* pTask) ;
	HRESULT _call StartThread	(BSTR bstrId) ;
	HRESULT _call StopThread	(BSTR bstrId) ;
	HRESULT _call AttachThread	(BSTR bstrId, ICTaskQueue* pTaskQueue) ;
	HRESULT _call DetachThread	(BSTR bstrId) ;

public:
	VOID	_lock	() ;
	VOID	_unlock	() ;

private:
	typedef struct _thread_node
	{
		CComPtr<ICTaskQueue>	_pTaskQueue ;
		CTaskRunnable*			_pTaskRunnable ;
	} ;
	typedef std::map<CString, _thread_node> MAP_RUNNABLE ;
	MAP_RUNNABLE							m_mapRunnable ;
} ;