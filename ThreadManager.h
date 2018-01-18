#pragma once

#include "Includes.h"
#include "AuroraDefine.h"
#include "AuroraSingleton.h"

namespace Aurora
{
	class Thread
	{
		friend class ThreadManager;
	public:
		Thread() : 
		_handle( INVALID_HANDLE_VALUE ), _id( 0 )
		{
			memset( _name, 0, sizeof( WCHAR ) * MAX_THREAD_NAME_LEN );
		}

		~Thread(){}

		void SetName( const WCHAR* pName ) const
		{
			if( pName )
			{
				wcsncpy_s( (WCHAR*)_name, (MAX_THREAD_NAME_LEN - 1), 
						   pName, (MAX_THREAD_NAME_LEN - 1) );
			}
		}

	private:
		HANDLE _handle;
		UInt32 _id;
		WCHAR _name[MAX_THREAD_NAME_LEN];
	};

	class ThreadManager : public Singleton<ThreadManager>
	{
		friend class Singleton<ThreadManager>;
	private:
		ThreadManager();
		Thread* CreateThread();
	public:
		virtual ~ThreadManager();

		HANDLE BeginThread( UInt32( __stdcall* StartAddress )(void *), void* pArgs, const WCHAR* pName );
		bool StopThread( const HANDLE* pHandle );
		
		void FindThread( const HANDLE* pHandle );
		void SetThreadName( const WCHAR* pName );
	};
}

#define AuroraThreadManager Aurora::ThreadManager::Instance()