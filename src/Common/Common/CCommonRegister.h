#pragma once

namespace Common
{
	namespace Reg
	{
		BSTR _object_table[][3] = 
		{
			{   // ICVariant
				_T("8419047E-547C-4bbb-84C3-4C3F5EEEB6C2") ,
				_T("3FC74D6B-FF79-47f5-AC4D-7C90352AA4FF") ,
				_T("Common.dll")
			} ,

			{   // ICVarData
				_T("606F5434-9A03-4243-952A-8960D7005E04") ,
				_T("6349F25A-ED1A-4bd1-BA96-ED56C879532E") ,
				_T("Common.dll")
			} ,

			{   // ICVarDataReader
				_T("C1E41389-958D-4853-84A3-2859616ADBB8") ,
				_T("6349F25A-ED1A-4bd1-BA96-ED56C879532E") ,
				_T("Common.dll")
			} ,

			{   // ICVarArrayReader
				_T("3DE31929-A92D-4e4b-9CB5-BA4FC5CD9DD8") ,
				_T("F9C9D572-9291-4cae-B99F-064CC3883270") ,
				_T("Common.dll")
			} ,

			{   // ICVarArray
				_T("247F6AAA-D0DB-4218-8CE5-422D29220D13") ,
				_T("F9C9D572-9291-4cae-B99F-064CC3883270") ,
				_T("Common.dll")
			} ,

			{   // ICVarBufferReader
				_T("40FCDBD4-2A5D-46cd-97E7-0E5F27AD3432") ,
				_T("6901067E-2592-45ae-92C8-ACE41E0F4C51") ,
				_T("Common.dll")
			} ,

			{   // ICVarBuffer
				_T("0C420062-4108-495d-A93F-EDBB57350DE5") ,
				_T("6901067E-2592-45ae-92C8-ACE41E0F4C51") ,
				_T("Common.dll")
			} ,
		} ;

		BSTR _service_table[][3] = 
		{
			{   // ISModule
				_T("D9E92111-265D-4801-A65C-9FE43EAF0EF2") ,
				_T("E5A244E0-CD1F-4809-A519-44992FE64870") ,
				_T("Common.dll")
			} ,

			{   // ISPlugin
				_T("4D38BD7B-4835-4855-BF49-1DF718CC630C") ,
				_T("33E53EE3-D8BA-415f-B8EB-532E1391F820") ,
				_T("Common.dll")
			} ,
		} ;
	}
}