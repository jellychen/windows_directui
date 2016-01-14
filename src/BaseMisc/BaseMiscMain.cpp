
#include "stdafx.h"
#include "Include/Def/Require.h"
#include "Include/Util/Utiltpl.h"

FUNC_API int ModuleMain()
{
	Common::Util::RegisterComponentString(
		_T("724F8B49-B765-4c60-8D40-98CD246EC1A5"), 
		_T("2994642D-F858-4d77-9B8D-59A03641BA15"), 
		_T("BaseMisc.dll")) ;

	// ICXml
	Common::Util::RegisterComponentString(_T("5894C945-9FAC-44a6-9D2D-23777CB7F94D"), _T("766ADD9A-002C-4e51-9756-75ABEECD855B"), _T("BaseMisc.dll")) ;

	// ISFileroute
	Common::Util::RegisterServiceString(_T("1E2A247A-3BE1-4fcb-87D7-31C740C08BD3"), _T("500070EA-5470-461a-B589-64BB5235ECCD"), _T("BaseMisc.dll")) ;
	// ISPackage
	Common::Util::RegisterServiceString(_T("E0278C42-DB7A-47f3-87B7-86CC5E0070DF"), _T("2C2DBD63-62DC-4ecd-B221-2D4374D8066A"), _T("BaseMisc.dll")) ;
	// ISConfig
	Common::Util::RegisterServiceString(_T("C0CDE877-F263-4a13-B51A-C79844A99355"), _T("D9CF0CF0-11C4-400c-8D74-F4E2B0A1831A"), _T("BaseMisc.dll")) ;
	return 0 ;
}