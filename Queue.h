#pragma once
#include "AuroraDefine.h"

namespace Aurora
{
	// push pop initialize reset
	template <typename T>
	class CQueue
	{
	protected:
		CQueue( void ) : _initialized( false )
		{

		}
	public:
		CQueue( const size_t QueueSize ) :
		count( 0 )
		{
			size = QueueSize;
			pData = new T[size];
			if( !pData )
			{
				_initialized = false;
				return;
			}

			memset( pData, 0, size );
			_initialized = true;
		}
		virtual ~CQueue( void )
		{
			SAFE_DELETE_ARRAY_POINTER( pData );
		}

		bool Recycle( int Position )
		{
			if( 0 > Position || GetSize() < Position )
			{
				return false;
			}

			memset( pData, 0, sizeof( T ) );
		}

		void SetData( T value )
		{
			if( pData && true == _initialized )
			{
				memcpy( &pData[count], (const void *)T, sizeof( T ) );
				++count;
			}
		}

		T GetFrontData( void )
		{
			if( pData && true == _initialized )
			{
				return &pData[count++];
			}
		}

		bool GetData( int Position, T* value )
		{
			if( 0 > Position || GetSize() < Position )
			{
				return false;
			}

			value = &pData[Position];
			return true;
		}

		bool Enqueue( const T value )
		{
			if( size <= count )
			{
				// already Maximum size.
				return false;
			}

			pData[count] = value;
			++count;
			return true;
		}

		T Dequeue( void )
		{
			if( 0 >= count )
			{
				return nullptr;
			}

			--count;
			return pData[count];
		}

		inline size_t ItemCount( void ) const { return count; }
		inline size_t GetSize( void ) const { return size; }

	private:
		bool _initialized;
		T *pData;
		size_t size;
		size_t count;
	};
}