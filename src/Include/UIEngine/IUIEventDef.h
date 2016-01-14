#pragma once

namespace EVENT
{
	enum
	{
		BASE_EVENT_START                = 0x0000 ,      //基础事件开始
		MOUSEENTER                      ,               //鼠标进入
		MOUSELEAVE                      ,               //鼠标移出
		MOUSEMOVE                       ,               //鼠标移动
		MOUSELBTNDOWN                   ,               //鼠标左键按下
		MOUSELBTNUP                     ,               //鼠标左键抬起
		MOUSELBTNCLICK                  ,               //鼠标左键点击
		MOUSELBTNDBCLICK                ,               //鼠标双击
		MOUSERBTNDOWN                   ,               //鼠标右按下
		MOUSERBTNUP                     ,               //鼠标右键弹起
		MOUSERBCLICK                    ,               //鼠标右击点击

		DRAGBEGIN                       ,               //开始拖动
		DRAGGING                        ,               //拖动中
		DRAGEND                         ,               //拖动结束

		DRAWBEGIN                       ,               //绘制开始
		DRAWEND                         ,               //绘制结束

		LAYOUTBEGIN                     ,               //开始布局
		LAYOUTEND                       ,               //布局结束
		BASE_EVENT_END                  = 0x00ff ,      //基础时间结束
	} ;
}

struct tEventArg
{
	INT                     nEventId ;
} ;

struct tEventArgPoint : public tEventArg
{
	POINT                   pt ;
} ;

struct tEventArgInt : public tEventArg
{
	INT                     nValue ;
};

struct tEventArgBool : public tEventArg
{
	BOOL                    bValue ;
} ;