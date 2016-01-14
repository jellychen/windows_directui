#pragma once

#ifdef BUILDING_WEK
#   define WKE_API __declspec(dllexport)
#else
#   define WKE_API __declspec(dllimport)
#endif

typedef char utf8 ;

typedef struct 
{
	int x ;
	int y ;
	int w ;
	int h ;
} wkeRect ;

enum wkeMouseFlags
{
	WKE_LBUTTON				= 0x01	,
	WKE_RBUTTON				= 0x02	,
	WKE_SHIFT				= 0x04	,
	WKE_CONTROL				= 0x08	,
	WKE_MBUTTON				= 0x10	,
} ;

enum wkeKeyFlags
{
	WKE_EXTENDED			= 0x0100	,
	WKE_REPEAT				= 0x4000	,
} ;

enum wkeMouseMsg
{
	WKE_MSG_MOUSEMOVE       =  0x0200	,
	WKE_MSG_LBUTTONDOWN     =  0x0201	,
	WKE_MSG_LBUTTONUP       =  0x0202	,
	WKE_MSG_LBUTTONDBLCLK   =  0x0203	,
	WKE_MSG_RBUTTONDOWN     =  0x0204	,
	WKE_MSG_RBUTTONUP       =  0x0205	,
	WKE_MSG_RBUTTONDBLCLK   =  0x0206	,
	WKE_MSG_MBUTTONDOWN     =  0x0207	,
	WKE_MSG_MBUTTONUP       =  0x0208	,
	WKE_MSG_MBUTTONDBLCLK   =  0x0209	,
	WKE_MSG_MOUSEWHEEL      =  0x020A	,
} ;

typedef		void*		jsExecState	;
typedef		__int64		jsValue		;
typedef		void*		wkeString	;
typedef		void (*ON_TITLE_CHANGED)	(const struct _wkeClientHandler* clientHandler, const wkeString title)	;
typedef		void (*ON_URL_CHANGED)		(const struct _wkeClientHandler* clientHandler, const wkeString url)	;

typedef struct _wkeClientHandler 
{
	ON_TITLE_CHANGED	onTitleChanged	;
	ON_URL_CHANGED		onURLChanged	;
} wkeClientHandler ;

typedef struct _wkeBufHandler
{
	virtual void onBufUpdated (const HDC hdc,int x, int y, int cx, int cy) = 0 ;
} wkeBufHandler ;