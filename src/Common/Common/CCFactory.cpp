
#include "stdafx.h"
#include "CCFactory.h"

CCFactory::CCFactory()
{
}

CCFactory::~CCFactory()
{
}

HRESULT CCFactory::Init()
{
	return this->m_common.Init() ;
}

HRESULT CCFactory::UnInit()
{
	return this->m_common.UnInit() ;
}

HRESULT CCFactory::SetProjectBaseDir(BSTR bstrDir)
{
	return this->m_common.SetProjectBaseDir(bstrDir) ;
}

HRESULT CCFactory::RegisterComponent(REFIID iid, REFCLSID clsid, BSTR bstrFile)
{
	return this->m_common.RegisterComponent(iid, clsid, bstrFile) ;
}

HRESULT CCFactory::RegisterComponentString(BSTR bsiid, BSTR bsclsid, BSTR bstrFile)
{
	return this->m_common.RegisterComponentString(bsiid, bsclsid, bstrFile) ;
}

HRESULT CCFactory::RegisterService(REFIID iid, REFCLSID clsid, BSTR bstrFile)
{
	return this->m_common.RegisterService(iid, clsid, bstrFile) ;
}

HRESULT CCFactory::RegisterServiceString(BSTR bsiid, BSTR bsclsid, BSTR bstrFile)
{
	return this->m_common.RegisterServiceString(bsiid, bsclsid, bstrFile) ;
}

HRESULT CCFactory::CreateObjectByIid(REFIID iid, VOID** ppOut, IUnknown* pOutUnknow)
{
	return this->m_common.CreateObjectByIid(iid, ppOut, pOutUnknow) ;
}

HRESULT CCFactory::CreateObjectByClsid(REFIID iid, REFCLSID clsid, VOID** ppOut, IUnknown* pOutUnknow)
{
	return this->m_common.CreateObjectByClsid(iid, clsid, ppOut, pOutUnknow) ;
}

HRESULT CCFactory::GetServiceByIid(REFIID iid, IWeakAgent** ppOutAgent, IUnknown* pOutUnknow)
{
	return this->m_common.GetServiceByIid(iid, ppOutAgent, pOutUnknow) ;
}

HRESULT CCFactory::GetServiceByClsid(REFIID iid, REFCLSID clsid, IWeakAgent** ppOutAgent, IUnknown* pOutUnknow)
{
	return this->m_common.GetServiceByClsid(iid, clsid, ppOutAgent, pOutUnknow) ;
}

HRESULT CCFactory::ClearServicePool()
{
	return this->m_common.ClearServicePool() ;
}