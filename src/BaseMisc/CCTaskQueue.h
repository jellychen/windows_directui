#pragma once
#include "Include/Def/Require.h"
#include "Include/BaseMisc/ITask.h"
#include "Include/BaseMisc/ICTaskQueue.h"
#include <vector>

[
	default(ICTaskQueue) ,
	threading(free) ,
	uuid("7F211A57-5C7F-48a1-9E98-269F633564CF") ,
	coclass
]
class ATL_NO_VTABLE CCTaskQueue 
	: public IDispatchImpl<ICTaskQueue>
	, public CRITICAL_SECTION
{
public:
	DECLARE_PROTECT_FINAL_CONSTRUCT() ;
	CCTaskQueue() ;
	virtual ~CCTaskQueue() ;

public:
	HRESULT _call GetTask	(ITask** ppTask, INT bWaitTime) ;
	HRESULT _call PostTask	(ITask* pTask) ;

private:
	void	_lock	() ;
	void	_unlock	() ;

private:
	typedef std::vector<ITask*>	VEC_TASK ;
	typedef VEC_TASK*			PVEC_TASK ;
	VEC_TASK					m_vecFirstTask ;
	VEC_TASK					m_vecSecondTask ;
	PVEC_TASK					m_pvecGetTask ;
	PVEC_TASK					m_pvecPostTask ;

	INT							m_nIndex ;
	HANDLE						m_hTaskEvent ;
} ;