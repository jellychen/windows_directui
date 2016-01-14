
#include "stdafx.h"
#include "CSModule.h"

HRESULT CSModule::LoadModule(BSTR bsModulePath)
{
	HINSTANCE _hInst = ::GetModuleHandle(bsModulePath) ;
	if (NULL == _hInst)
	{
		_hInst = ::LoadLibrary(bsModulePath) ;
	}
	IF_RETURN(NULL == _hInst, E_FAIL) ;

	typedef int (__stdcall* ModuleMain)(VOID) ;
	ModuleMain _proc = (ModuleMain)::GetProcAddress(_hInst, "ModuleMain") ;
	DEBUG_ASSERT_MSG(_proc, _T("Get dll %s ModuleMain function failed ..."), bsModulePath) ;
	IF_RETURN(NULL == _proc, E_FAIL) ;

	_proc() ;
	return S_OK ;
}