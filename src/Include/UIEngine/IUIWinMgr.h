#pragma once
#include "Include/Common/ICStruct.h"
#include "Include/UIEngine/IUIWin.h"

[
	object ,
	uuid("5C250BB4-957F-48dc-9052-0DEB61C3B020") ,
	pointer_default(unique)
]
__interface IUIWinMgr : IDispatch
{
	HRESULT AddWindow           (IUIWin* pWin) ;
	HRESULT DelWindow           (IUIWin* pWin) ;
	HRESULT GetWindowByHWnd     (HWND hWnd, IUIWin** pWin) ;
	HRESULT GetAllWindows       (ICVarArray* pWinArray) ;
	HRESULT GetAllWindowsCount  (INT* pnCount) ;
} ;