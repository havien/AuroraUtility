#pragma once
#include "ThreadManager.h"
#include "LogManager.h"

using namespace Aurora;

ThreadManager::ThreadManager( void )
{

}
	
ThreadManager::~ThreadManager( void )
{
	/*for( auto iter = _threads.begin(); iter != _threads.end(); ++iter )
	{
		SafeDelete( (*iter) );
	}*/
}

Thread* ThreadManager::CreateThread( void )
{
	return new Thread();
}

HANDLE ThreadManager::BeginThread( UInt32( __stdcall *StartAddress )(void *), void* pArgs, const WCHAR* pName )
{
	auto pThread = CreateThread();
	if( pThread )
	{
		pThread->_handle = reinterpret_cast<HANDLE>(_beginthreadex( nullptr, 0,
													 StartAddress, pArgs,
													 0, &pThread->_id ));
		if( 0 == pThread->_handle )
		{
			if( pName )
			{
				AuroraLogManager->Critical( L"Failed to Create Thread! [%s]", pName );
			}
			else
			{
				AuroraLogManager->Critical( L"Failed to Create Thread!" );
			}
			
			return false;
		}

		if( nullptr != pName )
		{
			pThread->SetName( pName );
		}

		//AuroraLogManager->Trace( L"Success to Begin Thread! [id:%d, name: %s]", pThread->_id, pThread->_name );
		//_threads.push_back( pThread );
		return pThread->_handle;
	}

	return INVALID_HANDLE_VALUE;
}

bool ThreadManager::StopThread( const HANDLE* pHandle )
{
	if( pHandle )
	{
		//auto ThreadIter = FindThread( pHandle );
		//if( _threads.end() != ThreadIter )
		//{
		//	// find!
		//	CloseHandle( (*pHandle) );
		//	//_endthreadex( 0 );
		//		
		//	return true;
		//}
			
		return false;
	}
		
	return false;
}

void ThreadManager::FindThread( const HANDLE* pHandle )
{
	pHandle;
	/*if( pHandle )
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

	return _threads.end();*/
}

void ThreadManager::SetThreadName( const WCHAR* pThreadName )
{
	pThreadName;
}