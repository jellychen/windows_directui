#pragma once

namespace ANCHOR
{
	enum 
	{
		NONE                    = 0x0   ,
		TOP_LEFT                        ,
		TOP_RIGHT                       ,
		TOP_CENTER                      ,
		BOTTOM_LEFT                     ,
		BOTTOM_RIGHT                    ,
		BOTTOM_CENTER                   ,
		CENTER                          ,
		LEFT_CENTER                     ,
		RIGHT_CENTER                    ,
	} ;

	enum
	{
		LEFT                    = 0xA   ,
		RIGHT                           ,
		TOP                             ,
		BOTTOM                          ,
		FILL                            ,
	} ;
}

namespace DRIFT
{
	enum 
	{
		DRIFT_NEAR				= 0x0	,
		DRIFT_FAR						,
		DRIFT_MIDDLE					,
	} ;
}

namespace STATE
{
	enum
	{
		NORMAL                  = 0x0   ,
		HIGHLIGHT               = 0x1   ,
		PUSHED                  = 0x2   ,
		DISABLE                 = 0x3   ,
	} ;
}

namespace LAYOUT_INFO_CHANGE
{
	enum
	{
		CHANGE_UNKNOWN          = 0x0000 ,
		CHANGE_SIZE             = 0x0001 ,
		CHANGE_LOCATION         = 0x0002 ,
		CHANGE_ANCHOR           = 0x0004 ,
		CHANGE_MARGIN           = 0x0008 ,
		CHANGE_PADDING          = 0x0010 ,
		CHANGE_ALPHA            = 0x0020 ,
		CHANGE_DISABLE          = 0x0040 ,
		CHANGE_HIDDEN           = 0x0080 ,
	} ;
}

namespace UI
{
	namespace EVENT
	{
		enum
		{
			CONTROL_EVENT_START = 0xFF	,
		} ;
	}
}