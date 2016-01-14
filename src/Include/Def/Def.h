#ifndef INCLUDE_DEF_DEF_H
#define INCLUDE_DEF_DEF_H

#ifndef IF_RETURN
#define IF_RETURN(x, ret)                                           \
	if (!!(x))                                                      \
	{                                                               \
		return ret ;                                                \
	}
#endif//IF_RETURN

#ifndef IF_RETURN_VOID
#define IF_RETURN_VOID(x)                                           \
	if (!!(x))                                                      \
	{                                                               \
		return ;                                                    \
	}
#endif//IF_RETURN

#ifndef IF_BREAK
#define IF_BREAK(x)                                                 \
	if ((x))                                                        \
	{                                                               \
		break ;                                                     \
	}
#endif//IF_BREAK

#ifndef IF_CONTINUE
#define IF_CONTINUE(x)                                              \
	if (!!(x))                                                      \
	{                                                               \
		continue ;                                                  \
	}
#endif//IF_CONTINUE

#ifndef SAFE_DELETE
#define SAFE_DELETE(ptr)                                            \
	if (NULL != ptr)                                                \
	{                                                               \
		delete ptr ;                                                \
		ptr = NULL ;                                                \
	}
#endif//SAFE_DELETE

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(ptr)                                      \
	if (NULL != ptr)                                                \
	{                                                               \
		delete[] ptr ;                                              \
	}
#endif//SAFE_DELETE_ARRAY

#ifndef FUNCTION_EXPORT
#define FUNC_API extern "C" __declspec(dllimport)
#else
#define FUNC_API extern "C" __declspec(dllexport)
#endif//FUNCTION_EXPORT

#define _call   STDMETHODCALLTYPE

#endif//INCLUDE_DEF_DEF_H