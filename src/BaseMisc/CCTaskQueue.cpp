#include "stdafx.h"
#include "CCTaskQueue.h"

CCTaskQueue::CCTaskQueue()
{
	this->m_pvecGetTask		= &m_vecFirstTask ;
	this->m_pvecPostTask	= &m_vecSecondTask ;
	this->m_nIndex			= 0 ;
	this->m_hTaskEvent		= ::CreateEvent(NULL, FALSE, FALSE, NULL) ;
	::InitializeCriticalSection(this) ;
}

CCTaskQueue::~CCTaskQueue()
{
	if (this->m_hTaskEvent)
	{
		::CloseHandle(this->m_hTaskEvent) ;
	}
	::DeleteCriticalSection(this) ;
}

HRESULT CCTaskQueue::GetTask(ITask** ppTask, INT bWaitTime)
{
	DEBUG_ASSERT(ppTask) ;
	IF_RETURN(NULL == ppTask, E_INVALIDARG) ;
	*ppTask = NULL ;

	IF_RETURN(NULL == m_pvecPostTask || NULL == m_pvecGetTask, E_FAIL) ;
	do 
	{
		if (this->m_nIndex < (INT)m_pvecGetTask->size())
		{
			*ppTask = (*m_pvecGetTask)[m_nIndex++] ;
			return S_OK ;
		}

		DWORD dwRet = WAIT_TIMEOUT ;
		if (bWaitTime < 0)
		{
			dwRet = ::WaitForSingleObject(this->m_hTaskEvent, INFINITE) ;
		}
		else
		{
			dwRet = ::WaitForSingleObject(this->m_hTaskEvent, bWaitTime) ;
		}
		IF_RETURN(WAIT_OBJECT_0  != dwRet, E_FAIL) ;

		this->m_pvecGetTask->clear() ;
		this->m_nIndex = 0 ;

		this->_lock() ;
		PVEC_TASK _temp = this->m_pvecGetTask ;
		this->m_pvecGetTask = this->m_pvecPostTask ;
		this->m_pvecPostTask = _temp ;
		this->_unlock() ;

	} while (1);
	return S_OK ;
}

HRESULT CCTaskQueue::PostTask(ITask* pTask)
{
	DEBUG_ASSERT(pTask) ;
	IF_RETURN(NULL == pTask, E_INVALIDARG) ;

	this->_lock() ;
	if (this->m_pvecPostTask)
	{
		this->m_pvecPostTask->push_back(pTask) ;
		::SetEvent(this->m_hTaskEvent) ;
	}
	this->_unlock() ;
	return S_OK ;
}

void CCTaskQueue::_lock()
{
	::EnterCriticalSection(this) ;
}

void CCTaskQueue::_unlock()
{
	::LeaveCriticalSection(this) ;
}