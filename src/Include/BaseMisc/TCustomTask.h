#pragma once
#include "Include/Def/Require.h"
#include "Include/BaseMisc/ITask.h"
#include "Include/BaseMisc/ICTaskQueue.h"

namespace Task
{
	template<typename T>
	class TCustomTaskMark ;
	template<typename T>
	class TCustomTaskAddProtect ;
	template<typename T>
	class TCustomTaskAddProtectResponse ;
	template<typename T>
	class TCustomTaskComplete ;

	template<typename T>
	class TCustomTaskMark : public ITask
	{
	public:
		typedef void (T::*PTaskCallback)() ;
		
		TCustomTaskMark()
		{
			this->m_pHostPtr		= NULL ;
			this->m_nHostClassId	= -1 ;
			this->m_pCallback		= NULL ;
			this->m_pTaskComplete	= NULL ;
		}

	public:
		T*					m_pHostPtr ;
		INT					m_nHostClassId ;
		PTaskCallback		m_pCallback ;
		PTaskCallback		m_pTaskComplete ;

		DWORD				m_dwHostThreadId ;
	public:
		void TaskRun()
		{
			// post to host thread id
			
			// del task
			this->TaskDel() ;
		}
		void TaskDel()		{ delete this ;	}
	} ;

	template<typename T>
	class TCustomTaskAddProtect : public ITask
	{
	public:
		typedef void (T::*PTaskCallback)() ;

	public:
		T*					m_pHostPtr ;
		INT					m_nHostClassId ;
		PTaskCallback		m_pCallback ;

		DWORD				m_dwTaskThreadId ;
	public:
		void TaskRun()
		{
			// promote protect
			
			// post tp task thread id

			// del task
		}
		void TaskDel()		{ delete this ; }
	} ;

	template<typename T>
	class TCustomTaskAddProtectResponse : public ITask
	{

	} ;

	template<typename T>
	class TCustomTaskComplete : public ITask
	{

	} ;
}