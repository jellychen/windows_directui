#pragma once

namespace MESSAGE
{
	enum
	{
		UI_MSG_BEGIN        = 0X00  ,
		UI_ACTIVE                   ,
		UI_MOUSEMSG_BEGIN			,
		UI_LBTNDOWN                 ,
		UI_LBTNUP                   ,
		UI_LBTNCLICK                ,
		UI_LBTNDBCLICK              ,
		UI_RBTNDOWN                 ,
		UI_RBTNUP                   ,
		UI_RBTNCLICK                ,
		UI_MOUSEMOVE                ,
		UI_MOUSEENTER               ,
		UI_MOUSELEAVE               ,
		UI_MOUSEWHEEL               ,
		UI_MOUSEMSG_END				,
		UI_KEYDOWN                  ,
		UI_KEYUP                    ,
		UI_CHAR                     ,
		UI_FOCUS                    ,
		UI_CURSOR                   ,
		UI_IME                      ,
		UI_IME_STARTCOMPOSITION		,
		UI_IME_CHAR					,
		UI_MSG_END                  ,
	} ;
}

struct tMsgArg
{
	HWND        hWnd ;
	DWORD       dwMsgId ;
	DWORD       dwSysmteMsgId ;
	WPARAM      wParam ;
	LPARAM      lParam ;
} ;

struct tMsgArgPoint : public tMsgArg
{
	POINT       pt ;
} ;

struct tMsgArgMouseWheel : public tMsgArgPoint
{
	INT         nZDelta ;
	UINT        uKeyFlags ;
} ;

struct tMsgArgKey : public tMsgArg
{
	UINT        unChar ;
	UINT        unRepCnt ;
	UINT        unFlags ;
} ;

struct tMsgArgBool : public tMsgArg
{
	BOOL        bValue ;
} ;