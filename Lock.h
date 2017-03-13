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
		ILock( void ) { }

		virtual ~ILock( void ) { }
		virtual void Lock( void ) = 0;
		virtual void UnLock( void ) = 0;
	protected:
		bool locked;
	};

	class CAutoLockWindows : public ILock
	{
	public:
		CAutoLockWindows( LockObject* pObject )
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

		CAutoLockWindows & operator=( const CAutoLockWindows & ) {}
	public:
		virtual ~CAutoLockWindows( void )
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

		const inline bool IsLocked( void ) const { return locked; }

		bool initialized;
		CRITICAL_SECTION* pMonitorObject;
	};
};