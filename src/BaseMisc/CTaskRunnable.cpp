#include "stdafx.h"
#include "CTaskRunnable.h"

DWORD WINAPI _ThreadCallback(LPVOID lpParam)
{
	IF_RETURN(NULL == lpParam, 0) ;
	CTaskRunnable* _ptr = (CTaskRunnable*)lpParam ;
	_ptr->RunnableFunction() ;
	return 0 ;
}

CTaskRunnable::CTaskRunnable()
{
	this->m_hThreadHandle	= NULL ;
	this->m_hThreadExit		= ::CreateEvent(NULL, TRUE, FALSE, NULL) ;
}

CTaskRunnable::~CTaskRunnable()
{
	if (this->m_hThreadExit)
	{
		::CloseHandle(this->m_hThreadExit) ;
	}

	if (this->m_hThreadHandle)
	{
		::CloseHandle(this->m_hThreadHandle) ;
	}
}

BOOL CTaskRunnable::Start(BSTR bstrId)
{
	if (this->m_hThreadHandle)
	{
		DWORD dwExitCode = 0 ;
		::GetExitCodeThread(this->m_hThreadHandle, &dwExitCode) ;
		IF_RETURN(STILL_ACTIVE == dwExitCode, FALSE) ;
		::CloseHandle(this->m_hThreadHandle) ;
		this->m_hThreadHandle = NULL ;
	}

	::ResetEvent(this->m_hThreadExit) ;
	this->m_hThreadHandle = ::CreateThread(NULL, 0, _ThreadCallback, (VOID*)this, CREATE_SUSPENDED, NULL) ;
	
	::ResumeThread(this->m_hThreadHandle) ;
	return TRUE ;
}

BOOL CTaskRunnable::Stop()
{
	IF_RETURN(NULL == this->m_hThreadHandle, FALSE) ;
	::SetEvent(this->m_hThreadExit) ;
	return TRUE ;
}

BOOL CTaskRunnable::WaitThreadExit(INT nTime)
{
	if (this->m_hThreadHandle)
	{
		if (nTime < 0)
		{
			nTime = INFINITE ;
		}

		DWORD dwRet = ::WaitForSingleObject(this->m_hThreadHandle, nTime) ;
		if (WAIT_OBJECT_0 != dwRet)
		{
			::TerminateThread(this->m_hThreadHandle, 0) ;
		}

		::CloseHandle(this->m_hThreadHandle) ;
		this->m_hThreadHandle = NULL ;
	}
	return TRUE ;
}

BOOL CTaskRunnable::PostTask(ITask* pTask)
{
	if (this->m_pThreadTaskQueue)
	{
		return SUCCEEDED(this->m_pThreadTaskQueue->PostTask(pTask)) ;
	}
	return FALSE ;
}

VOID CTaskRunnable::RunnableFunction()
{
	if (this->m_pThreadTaskQueue)
	{
		while (TRUE)
		{
			DWORD dwRet = ::WaitForSingleObject(m_hThreadExit, 0) ;
			IF_BREAK(WAIT_OBJECT_0 == dwRet) ;

			ITask* _pTask = NULL ;
			//this->m_pThreadTaskQueue->GetTask(&_pTask) ;
			IF_CONTINUE(NULL == _pTask) ;

			_pTask->TaskRun() ;
		}
	}
	return ;
}