#pragma once

#include "Includes.h"
#include "AuroraDefine.h"
#include "AuroraSingleton.h"

namespace Aurora
{
#if defined(WIN32) || defined(_WIN32) || defined(_WIN64)
	typedef CRITICAL_SECTION LockObject;
#elif defined(__linux__)
	typedef pthread_mutex_t LockObject;
#endif

	class ILock
	{
	public:
		ILock(){ }

		virtual ~ILock(){ }
		virtual void Lock()= 0;
		virtual void UnLock()= 0;
	protected:
		bool locked;
	};

	class CAutoLockW : public ILock
	{
	public:
		CAutoLockW( LockObject* pObject )
		{
			if( nullptr == pObject )
			{
				return;
			}

			pMonitorObject = pObject;
			if( false == initialized )
			{
				//InitLockObject();
			}

			if( false == IsLocked() )
			{
				Lock();
			}
		}

		CAutoLockW & operator=( const CAutoLockW & ) {}
	public:
		virtual ~CAutoLockW( void )
		{ 
			if( true == IsLocked() )
			{
				UnLock();
			}

			//DeleteCriticalSection( &_monitorObject );
		}
		
		virtual void Lock( void )
		{
			if( false == IsLocked() )
			{
				locked = true;
				EnterCriticalSection( pMonitorObject );
			}
		}

		virtual void UnLock( void )
		{
			if( true == IsLocked() )
			{
				LeaveCriticalSection( pMonitorObject );
				locked = false;
			}
		}

		const inline bool IsLocked() const { return locked; }

		bool initialized;
		CRITICAL_SECTION* pMonitorObject;
	};
};