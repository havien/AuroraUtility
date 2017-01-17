#pragma once

#include "Includes.h"
#include "AuroraDefine.h"
#include "AuroraSingleton.h"

namespace Aurora
{
	enum class EThreadState
	{
		None = 0,
		Waiting,
		Suspend,
		Running,
	};

	class AuroraThread
	{
	public:
		AuroraThread( void ) : 
		handle( INVALID_HANDLE_VALUE ),
		state( EThreadState::None ),
		identifier( 0 )
		{
			memset( ThreadName, 0, MAX_THREAD_NAME_LEN );
		}

		~AuroraThread( void ) {}

		void SetThreadName( const char* pThreadName ) const
		{
			if( pThreadName )
			{
				strcpy_s( (char*)&ThreadName, MAX_THREAD_NAME_LEN, pThreadName );
			}
		}

		//private:
		HANDLE handle;
		unsigned int identifier;
		EThreadState state;
		char ThreadName[MAX_THREAD_NAME_LEN];
	};

	typedef std::vector<AuroraThread *> ThreadList;
	typedef std::vector<AuroraThread *>::iterator ThreadIter;

	class ThreadManager : public Singleton<ThreadManager>
	{
		friend class Singleton<ThreadManager>;
	private:
		ThreadManager( void );
		AuroraThread* CreateNewThread( void );
		ThreadList _threads;
	public:
		virtual ~ThreadManager( void );

		HANDLE BeginThread( UInt32( __stdcall* StartAddress )(void *), void* pArgList, const char* pName );
		bool StopThread( const HANDLE* pHandle );
		
		ThreadIter FindThread( const HANDLE* pHandle );
		void SetThreadName( const WCHAR* pName );
	};

	#define AuroraThreadManager ThreadManager::Instance()
}