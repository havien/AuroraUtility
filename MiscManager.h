#pragma once

#include "Includes.h"
#include "AuroraDefine.h"
#include "AuroraSingleton.h"

namespace Aurora
{
	class MiscManager : public Singleton<MiscManager>
	{
		friend class Singleton<MiscManager>;
	private:
		MiscManager( void );

		NON_COPYABLE( MiscManager );
	public:
		virtual ~MiscManager( void );

		void SetLogFile( WCHAR* pLogFileName );

		DWORD GetProcessorCount( void );
		UInt16 GetProcessorCountUInt16( void );

		void PrintDebugTextToOutputWindow( ELogPrintType type, WCHAR* szFormat, ... );

		const bool SupportQPF( Int64 &QPFTick );
		
		Int64 GetQPCTick( void );
		Int64 GetQPCElapsedMicroSecond( const Int64 &qptTick, const Int64 &startTick, const Int64 &endTick );
		Int64 GetQPCElapsedSecond( const Int64 &qptTick, const Int64 &startTick, const Int64 &endTick );

		bool ExecuteProcess( const WCHAR* pProcessName, const WCHAR* pParameters, 
							 const bool minimized = true, const UInt32 executeCount = 1, 
							 DWORD sleepTime = 0 );

		inline const bool SupportQFC( void ) const
		{
			return supportQFC;
		}

		bool supportQFC;
		WCHAR logFileName[MAX_NORMAL_STRING_LEN];
		CRITICAL_SECTION _monitorObject;
	};

	#define AuroraMiscManager MiscManager::Instance()

	#define PRINT_NORMAL_LOG( str, ... ) AuroraMiscManager->PrintDebugTextToOutputWindow( ELogPrintType::Normal, str, __VA_ARGS__ )
	#define PRINT_FILE_LOG( str, ... ) AuroraMiscManager->PrintDebugTextToOutputWindow( ELogPrintType::WriteLog, str, __VA_ARGS__ )
}