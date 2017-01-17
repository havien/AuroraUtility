#pragma once

#include "Includes.h"
#include "UtilityDefine.h"
#include "MiscManager.h"
#include "AuroraSingleton.h"

namespace AuroraUtility
{
#if defined(WIN32) || defined(_WIN32) || defined(_WIN64)
	typedef CRITICAL_SECTION LockObject;
#elif defined(__linux__)
	typedef pthread_mutex_t LockObject;
#endif

	class ILock
	{
	public:
		ILock( LockObject *pobject ) : m_MonitorObject( pobject ), m_InitializedObject( false ), m_LockedObject( false )
		{

		}

		virtual ~ILock( void ) { }
		virtual void Lock( void ) = PURE_VIRTUAL;
		virtual void UnLock( void ) = PURE_VIRTUAL;
	protected:
		bool m_InitializedObject;
		bool m_LockedObject;
		LockObject *m_MonitorObject;
	};

	class CAutoLockWindows : public ILock
	{
	public:
		CAutoLockWindows( LockObject *pobject ) : ILock( pobject )
		{
			if( false == m_InitializedObject )
			{
				//InitLockObject();
			}

			if( false == Locked() )
			{
				Lock();
			}
		}

		CAutoLockWindows & operator=( const CAutoLockWindows & ) {}
	public:
		virtual ~CAutoLockWindows( void )
		{ 
			if( true == Locked() )
			{
				UnLock();
			}

			//DeleteCriticalSection( &_monitorObject );
		}
		
		virtual void Lock( void )
		{
			if( false == Locked() )
			{
				m_LockedObject = true;
				EnterCriticalSection( m_MonitorObject );
			}
		}

		virtual void UnLock( void )
		{
			if ( true == Locked() )
			{
				LeaveCriticalSection( m_MonitorObject );
				m_LockedObject = false;
			}
		}

		const inline bool Locked( void ) const { return m_LockedObject; }
	};
};