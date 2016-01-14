#pragma once
#include "Include/BaseMisc/ICTaskQueue.h"

[
	object ,
	uuid("3FE0B669-1737-4281-84DC-EB6834E1A538") ,
	pointer_default(unique)
]
__interface ISTaskCenter : IDispatch
{
	HRESULT PostTask		(BSTR bstrId, ITask* pTask) ;
	HRESULT StartThread		(BSTR bstrId) ;
	HRESULT StopThread		(BSTR bstrId) ;
	HRESULT AttachThread	(BSTR bstrId, ICTaskQueue* pTaskQueue) ;
	HRESULT DetachThread	(BSTR bstrId) ;
} ;