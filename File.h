#pragma once

#include "Includes.h"
#include <fstream>

#include "AuroraDefine.h"
#include "BaseObject.h"

namespace Aurora
{
	class File : public AuroraBase 
	{
	public:
		explicit File( const WCHAR* pFileName, const EFile type, const EFileOpenMode mode );
		virtual ~File();

		void SetName( const WCHAR* pFileName );
		bool OpenBinary( const EFileOpenMode mode );
		bool OpenBinary( const WCHAR* pFileName, const EFileOpenMode mode );
	private:
		WCHAR _name[MAX_PATH + 1];
		std::wfstream _stream;
	};
}