#pragma once

#include <vector>
#include <map>

#define MIN_PACKAGE_FILE_SIZE           20020
#define PACKAGE_FILE_HEAD               20020
#define PACKAGE_FILE_HASH_SIZE          5000
#define PACKAGE_FILE_SIGN               16
#define PACKAGE_FILE_VERSION            4
#define PACKAGE_FILE_NAME_SIZE          128
#define PACKAGE_FILE_LIST_SIZE          4

#pragma pack(push, 1)

struct FILE_INFO_PAKAGE
{
	TCHAR                               _str_file_name[PACKAGE_FILE_NAME_SIZE] ;
	UINT32                              _un32_start_address ;
	UINT32                              _un32_file_length ;
} ;

struct FILE_INFO
{
	UINT32                              _un32_start_address ;
	UINT32                              _un32_file_length ;
}  ;

#pragma  pack(pop)

typedef std::vector<UINT32>             VEC_FILE_HASHTABLE ;
typedef std::vector<BOOL>               VEC_FILE_LIST_LOADED ;
typedef std::map<CString, FILE_INFO>    MAP_FILE_TABLE_INFO ;

struct FileListInfo
{
	CString                             _file_pack ;
	VEC_FILE_HASHTABLE                  _file_info ;
	MAP_FILE_TABLE_INFO                 _file_list_info ;
	VEC_FILE_LIST_LOADED                _file_list_load ;
} ;

typedef std::map<CString, FileListInfo> MAP_PACKAGE_POOL ;