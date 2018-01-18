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
		MiscManager();
	public:
		virtual ~MiscManager();

		int ConsoleTest();

		DWORD GetProcessorCount() const;
		UInt16 GetProcessorCountU16() const;

		const bool SupportQPF( Int64 &QPFTick );
		
		Int64 GetQPCTick() const;
		Int64 GetQPCElapsedMicroSecond( const Int64 &qptTick, const Int64 &startTick, const Int64 &endTick );
		Int64 GetQPCElapsedSecond( const Int64 &qptTick, const Int64 &startTick, const Int64 &endTick ) const;

		bool ExecuteProcess( const WCHAR* pProcessName, const WCHAR* pParameters, 
							 const bool minimized = true, const Int32 executeCount = 1, 
							 DWORD sleepTime = 0 ) const;

		inline const bool SupportQFC() const
		{
			return supportQFC;
		}

		bool supportQFC;
	};
}

#define AuroraMiscManager Aurora::MiscManager::Instance()