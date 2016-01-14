#pragma once
#include "Include/Def/Require.h"
#include "Include/UIEngine/IUIElement.h"
#include "Include/UIEngine/IUIWin.h"

namespace UI
{
	//----------------------------------
	template<typename T> HWND GetHostWnd(IUIElement* pElement)
	{
		IF_RETURN(NULL == pElement, NULL) ;

		HWND _hWnd = NULL ;
		CComPtr<IUIElement> _pRoot ;
		pElement->GetRoot(&_pRoot) ;
		CComQIPtr<IUIWin> _pRootWindow = _pRoot ;
		IF_RETURN(NULL == _pRootWindow, NULL) ;

		_pRootWindow->GetHWnd(&_hWnd) ;
		return _hWnd ;
	}
}