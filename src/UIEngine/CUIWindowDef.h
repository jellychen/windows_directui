#pragma once
#define WINDOW_MESSAGE_BEGIN(_MESSAGE, _RET)                                    \
	do {                                                                        \
	LRESULT* _pResult = _RET ;                                                  \
	switch(_MESSAGE)                                                            \
	{

#define WINDOW_ACTIVATE(_FUNC, _WPARAM, _LPARAM, _HANDLE)                       \
	case WM_ACTIVATE:                                                           \
	*_pResult = this->_FUNC((UINT)LOWORD(_WPARAM),                              \
	(BOOL)HIWORD(wParam), _HANDLE) ; break ;

#define WINDOW_ERASEBKGND(_FUNC, _WPARAM, _LPARAM, _HANDLE)                     \
	case WM_ERASEBKGND:                                                         \
	*_pResult = this->_FUNC((HDC)(_WPARAM), _HANDLE) ; break ;

#define WINDOW_NCCALCSIZE(_FUNC, _WPARAM, _LPARAM, _HANDLE)                     \
	case WM_NCCALCSIZE:                                                         \
	*_pResult = this->_FUNC((BOOL)(_WPARAM), _LPARAM, _HANDLE) ; break ;

#define WINDOW_GETMINMAXINFO(_FUNC, _WPARAM, _LPARAM, _HANDLE)                  \
	case WM_GETMINMAXINFO:                                                      \
	*_pResult = this->_FUNC(LPMINMAXINFO(_LPARAM), _HANDLE) ; break ;           \

#define WINDOW_NCHITTEST(_FUNC, _WPARAM, _LPARAM, _HANDLE)                      \
	case WM_NCHITTEST:                                                          \
	*_pResult = this->_FUNC(_WPARAM, _LPARAM,                                   \
	CPoint(GET_X_LPARAM(_LPARAM), GET_Y_LPARAM(_LPARAM)), _HANDLE) ; break ;

#define WINDOW_NCPAINT(_FUNC, _WPARAM, _LPARAM, _HANDLE)                        \
	case WM_NCPAINT:                                                            \
	*_pResult = this->_FUNC((LONG)(_WPARAM), _HANDLE) ; break ;

#define WINDOW_NCLBUTTONDOWN(_FUNC, _WPARAM, _LPARAM, _HANDLE)                  \
	case WM_NCLBUTTONDOWN:                                                      \
	*_pResult = this->_FUNC((UINT)(_WPARAM),                                    \
	CPoint(GET_X_LPARAM(_LPARAM), GET_Y_LPARAM(_LPARAM)), _HANDLE) ; break ;

#define WINDOW_SIZE(_FUNC, _WPARAM, _LPARAM, _HANDLE)                           \
	case WM_SIZE:                                                               \
	*_pResult = this->_FUNC((UINT)_WPARAM,                                      \
	CSize(GET_X_LPARAM(_LPARAM), GET_Y_LPARAM(_LPARAM)), _HANDLE) ; break ;

#define WINDOW_MOVING(_FUNC, _WPARAM, _LPARAM, _HANDLE)                         \
	case WM_MOVING:                                                             \
	*_pResult = this->_FUNC((LPRECT)_LPARAM, _HANDLE) ; break ;

#define WINDOW_PAINT(_FUNC, _WPARAM, _LPARAM, _HANDLE)                          \
	case WM_PAINT:                                                              \
	*_pResult = this->_FUNC((HDC)(_WPARAM), _HANDLE) ; break ;

#define WINDOW_MOUSEMOVE(_FUNC, _WPARAM, _LPARAM, _HANDLE)                      \
	case WM_MOUSEMOVE:                                                          \
	*_pResult = this->_FUNC((UINT)_WPARAM,                                      \
	CPoint(GET_X_LPARAM(_LPARAM), GET_Y_LPARAM(_LPARAM)), _HANDLE) ; break ;

#define WINDOW_MOUSELEAVE(_FUNC, _WPARAM, _LPARAM, _HANDLE)                     \
	case WM_MOUSELEAVE:                                                         \
	*_pResult = this->_FUNC(_HANDLE) ;

#define WINDOW_KEYDOWN(_FUNC, _WPARAM, _LPARAM, _HANDLE)                        \
	case WM_KEYDOWN:                                                            \
	*_pResult = this->_FUNC((TCHAR)_WPARAM,                                     \
	(UINT)_LPARAM & 0xFFFF, (UINT)((_LPARAM & 0xFFFF0000) >> 16),               \
	_HANDLE) ; break ;

#define WINDOW_DESTROY(_FUNC, _WPARAM, _LPARAM, _HANDLE)                        \
	case WM_DESTROY:                                                            \
	*_pResult = this->_FUNC(_HANDLE) ; break ;

#define WINDOW_MESSAGE_END()                                                    \
	}} while(FALSE) ;