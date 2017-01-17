#include "AuroraDefine.h"
#include "AuroraSingleton.h"

namespace AuroraUtility
{
	class CMemoryManager : public Singleton<CMemoryManager>
	{
		friend class Singleton<CMemoryManager>;
	private:
		CMemoryManager( void )
		{

		}
	public:
		virtual ~CMemoryManager( void )
		{

		}

		bool CopyMemory( void* pSrc, void* pDesc, size_t CopyLength )
		{
			if( 0 >= CopyLength )
			{
				return false;
			}

			if( pSrc && pDesc )
			{
				return false;
			}

			memcpy( pSrc, pDesc, CopyLength );
		}
	}
}