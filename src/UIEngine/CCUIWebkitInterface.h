#pragma once
#include "CCUIWebkitDef.h"

#ifdef __cplusplus

namespace wke
{
	class IWebView
	{
	public:
		virtual void destroy() = 0;

		virtual const char* name() const = 0;
		virtual void setName(const char* name) = 0;

		virtual bool transparent() const = 0;
		virtual void setTransparent(bool transparent) = 0;

		virtual void loadURL(const utf8* url) = 0;
		virtual void loadURL(const wchar_t* url) = 0;

		virtual void loadHTML(const utf8* html) = 0;
		virtual void loadHTML(const wchar_t* html) = 0;

		virtual void loadFile(const utf8* filename) = 0;
		virtual void loadFile(const wchar_t* filename) = 0;

		virtual bool isLoaded() const = 0;        /*document load sucessed*/
		virtual bool isLoadFailed() const = 0;    /*document load failed*/
		virtual bool isLoadComplete() const = 0;  /*document load complete*/
		virtual bool isDocumentReady() const = 0; /*document ready*/
		virtual void stopLoading() = 0;
		virtual void reload() = 0;

		virtual const utf8* title() = 0;
		virtual const wchar_t* titleW() = 0;

		virtual void resize(int w, int h) = 0;
		virtual int width() const = 0;   /*viewport width*/
		virtual int height() const = 0;  /*viewport height*/

		virtual int contentsWidth() const = 0;  /*contents width*/
		virtual int contentsHeight() const = 0; /*contents height*/

		virtual void setDirty(bool dirty) = 0;
		virtual bool isDirty() const = 0;
		virtual void addDirtyArea(int x, int y, int w, int h) = 0;

		virtual void layoutIfNeeded() = 0;
		virtual void paint(void* bits, int pitch) = 0;
		virtual void tick() = 0;
		virtual void paint(HDC hdc,int x,int y,int cx,int cy,int xSrc,int ySrc,bool fKeepAlpha) = 0;

		virtual bool canGoBack() const = 0;
		virtual bool goBack() = 0;
		virtual bool canGoForward() const = 0;
		virtual bool goForward() = 0;

		virtual void selectAll() = 0;
		virtual void copy() = 0;
		virtual void cut() = 0;
		virtual void paste() = 0;
		virtual void delete_() = 0;

		virtual void setCookieEnabled(bool enable) = 0;
		virtual bool cookieEnabled() const = 0;

		virtual void setMediaVolume(float volume) = 0;
		virtual float mediaVolume() const = 0;

		virtual bool mouseEvent(unsigned int message, int x, int y, unsigned int flags) = 0;
		virtual bool contextMenuEvent(int x, int y, unsigned int flags) = 0;
		virtual bool mouseWheel(int x, int y, int delta, unsigned int flags) = 0;
		virtual bool keyUp(unsigned int virtualKeyCode, unsigned int flags, bool systemKey) = 0;
		virtual bool keyDown(unsigned int virtualKeyCode, unsigned int flags, bool systemKey) = 0;
		virtual bool keyPress(unsigned int virtualKeyCode, unsigned int flags, bool systemKey) = 0;

		virtual void focus() = 0;
		virtual void unfocus() = 0;

		virtual wkeRect getCaret() = 0;

		virtual jsValue runJS(const utf8* script) = 0;
		virtual jsValue runJS(const wchar_t* script) = 0;
		virtual jsExecState globalExec() = 0;

		virtual void sleep() = 0; //moveOffscreen
		virtual void awaken() = 0; //moveOnscreen
		virtual bool isAwake() const = 0;

		virtual void setZoomFactor(float factor) = 0;
		virtual float zoomFactor() const = 0;

		virtual void setEditable(bool editable) = 0;

		virtual void setClientHandler(const wkeClientHandler* handler) = 0;
		virtual const wkeClientHandler* getClientHandler() const = 0;

		virtual void setBufHandler(wkeBufHandler *handler) = 0;
		virtual const wkeBufHandler * getBufHandler() const  = 0;
	};
}

typedef wke::IWebView* wkeWebView;

#else

typedef void* wkeWebView;

#ifndef HAVE_WCHAR_T
typedef unsigned short wchar_t;
#endif

#ifndef HAVE_BOOL
typedef unsigned char bool;
#define true 1
#define false 0
#endif

#endif /*__cplusplus*/