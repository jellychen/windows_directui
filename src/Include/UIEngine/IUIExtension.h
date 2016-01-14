#pragma once
#include "Include/Common/ICStruct.h"
#include "Include/UIEngine/IUIFrame.h"

[
	object ,
	uuid("40AE7BA3-227D-4d0b-BBD5-6A0562BD496F") ,
	pointer_default(unique)
]
__interface IUIExtensionCallback : IDispatch
{
	HRESULT OnExtension (REFIID iid, IUIFrame* pFrame, ICVarData* pData) ;
} ;

COMMON_SINK_BEGIN(CComSinkExtensionCallback)
COMMON_SINK_FUNC(OnExtension, (REFIID iid, IUIFrame* pFrame, ICVarData* pData), (iid, pFrame, pData))
COMMON_SINK_END()
DECLARE_COMMON_SINK_PTR(CComSinkExtensionCallback, IUIExtensionCallback) ;

[
	object ,
	uuid("725F55E6-8BD3-4a30-98C3-E5D210D06790") ,
	pointer_default(unique)
]
__interface IUIExtensionCenter : IDispatch
{
	HRESULT CallExtension				(REFIID iid, IUIFrame* pFrame, ICVarData* pArg) ;
	HRESULT AddExtensionListener		(REFIID iid, IUIExtensionCallback* pCallback) ;
	HRESULT DelExtensionListener		(REFIID iid, IUIExtensionCallback* pCallback) ;
	HRESULT AddGlobalExtensionListener	(IUIExtensionCallback* pCallback) ;
	HRESULT DelGlobalExtensionListener	(IUIExtensionCallback* pCallback) ;
} ;
