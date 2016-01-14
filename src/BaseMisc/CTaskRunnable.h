#pragma once
#include "Include/Def/Require.h"
#include "Include/Util/UtilTpl.h"
#include "Include/BaseMisc/ITask.h"
#include "Include/BaseMisc/ICTaskQueue.h"

class CTaskRunnable
{
public:
	CTaskRunnable() ;
	virtual ~CTaskRunnable() ;

public:
	static CTaskRunnable* _get_new_instance() 
	{
		return new CTaskRunnable() ;
	}

	static void _release_instance(CTaskRunnable* _instance)
	{
		if (_instance)
		{
			delete _instance ;	
		}
	}

public:
	BOOL Start				(BSTR bstrId) ;
	BOOL Stop				() ;
	BOOL WaitThreadExit		(INT nTime) ;
	BOOL PostTask			(ITask* pTask) ;

public:
	VOID RunnableFunction	();

public:
	HANDLE					m_hThreadHandle ;
	HANDLE					m_hThreadExit ;
	CComPtr<ICTaskQueue>	m_pThreadTaskQueue ;
} ;