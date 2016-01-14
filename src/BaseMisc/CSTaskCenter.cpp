#include "stdafx.h"
#include "CSTaskCenter.h"

CSTaskCenter::CSTaskCenter()
{
	::InitializeCriticalSection(this) ;
}

CSTaskCenter::~CSTaskCenter()
{
	::DeleteCriticalSection(this) ;
}

HRESULT CSTaskCenter::PostTask(BSTR bstrId, ITask* pTask)
{
	if (NULL == bstrId)
	{
	}
	else
	{

	}
	return S_OK ;
}

HRESULT CSTaskCenter::StartThread(BSTR bstrId)
{
	return S_OK ;
}

HRESULT CSTaskCenter::StopThread(BSTR bstrId)
{
	return S_OK ;
}

HRESULT CSTaskCenter::AttachThread(BSTR bstrId, ICTaskQueue* pTaskQueue)
{
	return S_OK ;
}

HRESULT CSTaskCenter::DetachThread(BSTR bstrId)
{
	return S_OK ;
}

VOID CSTaskCenter::_lock()
{
	::EnterCriticalSection(this) ;
}

VOID CSTaskCenter::_unlock()
{
	::LeaveCriticalSection(this) ;
}