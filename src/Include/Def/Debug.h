#ifndef INCLUDE_DEF_DEBUG_H
#define INCLUDE_DEF_DEBUG_H
#include <crtdbg.h>

#ifdef _UNICODE
#define stprintf            swprintf
#define _tCrtDbgReport      _CrtDbgReportW
#else
#define stprinf             sprintf
#define _tCrtDbgReport      _CrtDbgReport
#endif//_UNICODE

#ifdef _DEBUG
#define DEBUG_ASSERT(OP)                                                                    \
	do{                                                                                     \
	if (!(OP))                                                                              \
			{                                                                               \
			TCHAR buf[MAX_PATH] = _T("\0") ;                                                \
			stprintf(buf, _T(#OP)) ;                                                        \
			if (1 == _tCrtDbgReport(_CRT_ASSERT, _T(__FILE__), __LINE__, NULL, buf))        \
				{                                                                           \
				::_CrtDbgBreak() ;                                                          \
				}                                                                           \
			}                                                                               \
	}while(FALSE) ;

#define DEBUG_ASSERT_MSG(OP, FT, ...)                                                       \
	do{                                                                                     \
	if (!(OP))                                                                              \
			{                                                                               \
			TCHAR buf[MAX_PATH] = _T("\0") ;                                                \
			stprintf(buf, FT, __VA_ARGS__) ;                                                \
			if (1 == _tCrtDbgReport(_CRT_ASSERT, _T(__FILE__), __LINE__, NULL, buf))        \
				{                                                                           \
				::_CrtDbgBreak() ;                                                          \
				}                                                                           \
			}                                                                               \
	}while(FALSE) ;

#define DEBUG_TRACE(FT, ...)                                                                \
	do{                                                                                     \
	TCHAR buf[MAX_PATH] = _T("\0") ;                                                        \
	stprintf(buf, FT, __VA_ARGS__) ;                                                        \
	::OutputDebugString(buf) ;                                                              \
	} while(FALSE) ;
#else
#define DEBUG_ASSERT(OP)
#define DEBUG_ASSERT_MSG(OP, FT, ...)
#define DEBUG_TRACE(FT, ...)

#endif//_DEBUG
#endif//INCLUDE_DEF_DEBUG_H