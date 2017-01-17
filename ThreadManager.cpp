#pragma once
#include "ThreadManager.h"

using namespace Aurora;

ThreadManager::ThreadManager( void )
{

}
	
ThreadManager::~ThreadManager( void )
{
	for( auto iter = _threads.begin(); iter != _threads.end(); ++iter )
	{
		if( nullptr != (*iter) )
		{
			SAFE_DELETE( (*iter) );
		}
	}
}

AuroraThread* ThreadManager::CreateNewThread( void )
{
	return new AuroraThread();
	//return pNewThread;
	//_threads.push_back( pNewThread );
}

HANDLE ThreadManager::BeginThread( UInt32( __stdcall *StartAddress )(void *), void* pArgList, const char* pName )
{
	AuroraThread* pThread = CreateNewThread();
	if( pThread )
	{
		pThread->handle = (HANDLE)_beginthreadex( nullptr, 0, StartAddress, pArgList, 0, &pThread->identifier );
		if( 0 == pThread->handle )
		{
			return false;
		}

		if( nullptr != pName )
		{
			pThread->SetThreadName( pName );
		}

		_threads.push_back( pThread );
		return pThread->handle;
	}

	return INVALID_HANDLE_VALUE;
}

bool ThreadManager::StopThread( const HANDLE* pHandle )
{
	if( pHandle )
	{
		auto ThreadIter = FindThread( pHandle );
		if( _threads.end() != ThreadIter )
		{
			// find!
			CloseHandle( (*pHandle) );
			//_endthreadex( 0 );
				
			return true;
		}
			
		return false;
	}
		
	return false;
}

ThreadIter ThreadManager::FindThread( const HANDLE* pHandle )
{
	if( pHandle )
	{
		for ( auto iter = _threads.begin(); iter != _threads.end(); ++iter )
		{
			if( (*iter)->handle == (*pHandle) )
			{
				return iter;
			}
		}

		return _threads.end();
	}

	return _threads.end();
}

void ThreadManager::SetThreadName( const WCHAR* pThreadName )
{
	pThreadName;
}