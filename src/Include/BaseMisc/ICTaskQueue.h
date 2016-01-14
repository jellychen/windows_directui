#pragma once

#include "Include/BaseMisc/ITask.h"

[
	object ,
	uuid("5B439914-C444-4d15-9441-8375AB653E49") ,
	pointer_default(unique)
]
__interface ICTaskQueue : IDispatch
{
	HRESULT GetTask		(ITask** ppTask, INT bWaitTime) ;
	HRESULT PostTask	(ITask* pTask) ;
} ;