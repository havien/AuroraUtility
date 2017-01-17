/*

// for linux o/s common functions.
#ifdef __linux__
class CLinuxUtilityManager : public CAuroraSingleton<CLinuxUtilityManager>
{
friend class CAuroraSingleton<CLinuxUtilityManager>;
private:
CLinuxUtilityManager() { }
CLinuxUtilityManager( const CLinuxUtilityManager& CopyArg );
public:
virtual ~CLinuxUtilityManager( void ) { }

//for linux calc elapsed time.
/*
#include <iostream>
#include <sys/time.h>                // for gettimeofday()
using namespace std;

int main()
{
timeval t1, t2;
double elapsedTime;

// start timer
gettimeofday(&t1, NULL);

// do something
...

// stop timer
gettimeofday(&t2, NULL);

// compute and print the elapsed time in millisec
elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms
cout << elapsedTime << " ms.\n";

return 0;
}
	};
#endif
#ifdef _WIN32 /* || _WIN64
	template <typename T>
	class AuroraWrapList
	{
	public:
		AuroraWrapList( void ) {}
		AuroraWrapList( bool HasPointer ) : m_HasPointer( HasPointer )
		{

		}
		~AuroraWrapList( void ) {}
		const inline bool HasPointer( void ) { return m_HasPointer; }
	private:
		bool m_HasPointer;

		std::list<T> m_List;
		std::list<T *> m_ListWithPointer;
	};

	//template <typename T>
	//class CWrapVector
	//{
	//private:		
	//	std::vector<T *> m_Vec;
	//	size_t m_ReserveSize;

	//	CWrapVector( void ) 
	//	{ m_Vec.reserve( DefaultVectorReserveSize ); }
	//	
	//	// Constructor with ReserveSize.
	//	CWrapVector( size_t ReserveSize ) : m_ReserveSize( ReserveSize )
	//	{
	//		m_Vec.reserve( ReserveSize );
	//	}

	//	inline void push_back( const T * Val ) { m_Vec.push_back(Val); }
	//	inline void pop_back() { m_Vec.pop_back(); }
	//	inline reference front() { m_Vec.front(); }

	//	CWrapVector( const CWrapVector& CopyArg );
	//public:
	//	static const size_t DefaultVectorReserveSize = 1024;
	//	virtual ~CWrapVector( void )
	//	{
	//		for( auto Iter = m_Vec.begin(); Iter != m_Vec.end(); ++Iter )
	//		{
	//			delete (*Iter);
	//		}

	//		m_Vec.clear();
	//	}
	//};

	/*class CVectorManager : public CAuroraSingleton<CVectorManager>
	{
	friend class CAuroraSingleton<CVectorManager>;
	private:
	CVectorManager( void )
	{

	}

	CVectorManager( const CVectorManager& CopyArg );
	public:
	virtual ~CVectorManager( void ) { }

	template<typename T>
	void Find( )
	};

	class CListManager : public CAuroraSingleton<CListManager>
	{
		friend class CAuroraSingleton<CListManager>;
	private:
		CListManager( void )
		{

		}

		CListManager( const CListManager& CopyArg );
	public:
		virtual ~CListManager( void ) {}

		template<typename T>
		void ReleaseList( std::list<T *> &TargetList, bool ClearList = false )
		{
			auto CurList = TargetList.begin( );
			auto EndList = TargetList.end( );

			while ( Curlist != Endlist )
			{
				SAFE_DELETE( (*Curlist) );
				listTarget.erase( Curlist++ );
			}

			if( true == ClearList )
			{
				TargetList.clear( );
			}
		}

		template<typename T>
		void ReleaseList( std::list<T> &TargetList, bool ClearList = false )
		{
			auto CurList = TargetList.begin( );
			auto EndList = TargetList.end( );

			while ( Curlist != Endlist )
			{
				listTarget.erase( Curlist++ );
			}

			if( true == ClearList )
			{
				TargetList.clear( );
			}
		}
	};
	Int64 QPFTick;
	pWinUtilManager->SupportQPF( QPFTick );

	Int64 StartTick = pWinUtilManager->GetQPCTick( );
	for ( Counter Cur = 0; Cur < 65555; ++Cur )
	{
		int bbb = Cur + 4 * 3 / 2;
		int ccc = (Cur * 2) + 1 / 1 * 4 * 42;
		printf( "%d\n", Cur );
	}

	Int64 EndTick = pWinUtilManager->GetQPCTick( );

	Int64 ElapsedTick = pWinUtilManager->GetQPCElapsedSecond( QPFTick, StartTick, EndTick );
	PRINT_NORMAL_LOG( L"Elapsed Second : %ld\n", ElapsedTick );

	ElapsedTick = pWinUtilManager->GetQPCElapsedMicroSecond( QPFTick, StartTick, EndTick );
	PRINT_NORMAL_LOG( L"Elapsed MicroSecond : %ld\n", ElapsedTick );
	
	//	CSQLiteManager *pSQLiteManager = CSQLiteManager::Instance();
	//	bool TryLoadDB =  pSQLiteManager->ConnectToDB( "test.db" );
	//	if( true == TryLoadDB )
	//	{
	//		bool TryEverything = false;
	//		//TryEverything = pSQLiteManager->Prepare( eDBWork_Select, "SELECT * FROM GT_Account WHERE UniqueID = ?" );
	//		pSQLiteManager->ExecuteSelect( "SELECT * FROM GT_Account WHERE UniqueID = 1" );
	//
	//
	//		//bool TryEverything = pSQLiteManager->ExecuteQuery( "INSERT INTO GT_Account( AccountID, Password ) VALUES( '김연수', '청춘의 문장들' )" );
	//		/*TryEverything = pSQLiteManager->Prepare( eDBWork_Insert, "INSERT INTO GT_Account( AccountID, Password ) VALUES( ?, ? )" );
	//
	//		char AccountID[17] = {0};
	//		char Password[50] = {0};
	//
	//		StringManager::Instance()->MemsetAndCopyStringA( AccountID, AccountIDLength, "김연수" );
	//		StringManager::Instance()->MemsetAndCopyStringA( Password, PasswordLength, "청춘의 문장들" );
	//
	//		TryEverything = pSQLiteManager->BindParameter( eSQLiteBind_NVARCHAR, (void *)AccountID, AccountIDLength-1 );
	//		TryEverything = pSQLiteManager->BindParameter( eSQLiteBind_NVARCHAR, (void *)Password, PasswordLength-1 );
	//		pSQLiteManager->step();
	//*/
//		int d = 0;
//	}

/*bool Exet = pSQLiteManager->ExecuteQuery( "INSERT INTO GT_Account( AccountID, Password ) VALUES( 'test2', '1234' )", NonSelect );
if( true == Exet )
{
Int64 AccountUniqueID = pSQLiteManager->GetLastInsertID();
char*pSecQuery2 = pWinUtilManager->MakeString( "INSERT INTO GT_Player( AccountID, NickName ) VALUES( %d, '%s' )", AccountUniqueID, "Nikunemu" );
Exet = pSQLiteManager->ExecuteQuery( pSecQuery2, NonSelect );
}*/

//pSQLiteManager->ExecuteQuery( "INSERT INTO GT_Player( AccountID, Password ) VALUES( 'test2', '1234' )" );

/*printf( "try Connect to DB(Microsoft SQL) Server...\n" );
bool TryConnectDB = pODBCManager->ConnectToDB( L"39.115.133.32", L"fmo_gm", L"ofmg", L"ofmg", EDBConnect_DriverDirect );
if( false == TryConnectDB )
{
PRINT_NORMAL_LOG( L"Failed to Connect DB Server..!\n" );
return 0;
}

SQLRETURN SQLRet = pODBCManager->Prepare( EWorkType_Query,
L"INSERT GameMasterLevels (id, name) VALUES(?, ?)" );
if( SQL_SUCCESS == SQLRet )
{
int id = 6;
WCHAR test[256] ={0};
wcscpy_s( test, 7, L"GMTest" );
SQLRet = pODBCManager->BindInteger( id );
SQLRet = pODBCManager->BindWVarCHAR( test );

SQLRet = pODBCManager->Execute();
}
else
{
pODBCManager->FailedExecuteMessages();
}
// 결과값을 돌려받기 위한 변수들
SQLCHAR Name[21];
int Price;
BOOL Korean;
SQLINTEGER lName,lPrice,lKorean;
// 화면 출력을 위한 변수들
int y=1;
HDC hdc;
int arTab[2]={200,400};
TCHAR str[255];

// 결과를 돌려받기 위해 바인딩한다.
SQLBindCol(hStmt,1,SQL_C_CHAR,Name,sizeof(Name),&lName);
SQLBindCol(hStmt,2,SQL_C_ULONG,&Price,0,&lPrice);
SQLBindCol(hStmt,3,SQL_C_ULONG,&Korean,0,&lKorean);

// SQL문을 실행한다.
if( SQL_SUCCESS != SQLExecDirect( hStmt, (SQLWCHAR* )L"select name,price,korean from tblCigar", SQL_NTS ) )
{
return false;
}

// 읽어온 데이터 출력
/*while(SQLFetch(hStmt)!=SQL_NO_DATA) {
wsprintf(str,"이름:%s\t가격:%d\t국산:%s",Name,Price,(Korean ? "예":"아니오"));
TabbedTextOut(hdc,10,y*20,str,lstrlen(str),2,arTab,0);
y++;
};

if( hStmt ) SQLCloseCursor( hStmt );
*/


//char SendBuffer[NormalNetworkBufferLen] = {0};
//char RecvBuffer[NormalNetworkBufferLen] ={0};

//bool TrySend = false;
//WCHAR RecvInput[ChatTextLength] ={0};
//while( true )
//{
//	bool RecvPacket = false;
//	
//	memset(SendBuffer, 0, NormalNetworkBufferLen - 1);
//	memset( RecvInput, 0, ChatTextLength - 1 );

//	printf( "Input> " );
//	//gets_s( SendBuffer );
//	_getws_s( RecvInput );

//	if( 0 >= wcslen( RecvInput ) )
//	{
//		continue;
//	}
//	
//	//char*pExit = strstr( SendBuffer, "exit" );
//	WCHAR* pExit = wcsstr( RecvInput, L"exit" );
//	if( nullptr != pExit )
//	{
//		printf( "exit Event, exit program.\n" );
//		return;
//	}

//	//char*pRegister = strstr( SendBuffer, "signup" );
//	WCHAR* pRegister = wcsstr( RecvInput, L"signup" );
//	if( nullptr != pRegister )
//	{
//		AuroraNetwork::CPacketRegisterReq tempPacket;
//		AuroraUtility::StringManager::Instance()->MemsetAndCopyStringW( tempPacket.AccountID, AuroraNetwork::AccountIDLength-1, L"havien" );
//		AuroraUtility::StringManager::Instance()->MemsetAndCopyStringW( tempPacket.Password, AuroraNetwork::PasswordLength-1, L"1234" );
//		AuroraUtility::StringManager::Instance()->MemsetAndCopyStringW( tempPacket.NickName, AuroraNetwork::NickNameLength-1, L"neivah" );

//		int SendResult = 0;
//		TrySend = pNetworkManager->SendToServer( (const char*)&tempPacket, tempPacket.GetSize(), SendResult );
//		if( false == TrySend )
//		{
//			if( SOCKET_ERROR == SendResult )
//			{
//				break;
//			}
//			else if( 10054 == SendResult )
//			{
//				break;
//			}
//			else if( 10038 == SendResult )
//			{
//				break;
//			}
//			break;
//		}

//		if( 0 < SendResult )
//		{
//			RecvPacket = true;
//			PRINT_NORMAL_LOG( L"Success to Send %ld Bytes, [%S]\n", SendResult, SendBuffer );
//		}
//		continue;
//	}

//	// send normal chat packet.
//	//AuroraNetwork::CPacketNormalChatReq ChatReqPacket;
//	//ChatReqPacket.SetChatText( RecvInput );
//	////ChatReqPacket.CalculateSize();

//	char Buffer[NormalNetworkBufferLen] = {0};
//	StringManager::Instance()->WCHARToCHAR( RecvInput, Buffer );

//	int SendResult = 0;
//	TrySend = pNetworkManager->SendToServer( Buffer, strlen(Buffer), SendResult );
//	if( false==TrySend )
//	{
//		return;
//	}

//	if( 0 < SendResult )
//	{
//		RecvPacket = true;
//		PRINT_NORMAL_LOG( L"Success to Send %ld Bytes, [%S]\n", SendResult, SendBuffer );
//	}

//	//if( 0 >= strlen( SendBuffer ) )
//	//{
//	//	continue;
//	//}
//	
//	//if( true == RecvPacket )
//	//{
//	//	int RecvResult = 0;
//	//	memset( RecvBuffer, 0, NormalNetworkBufferLen - 1 );
//	//	bool bTryReceive = pNetworkManager->ReceiveFromServer( &RecvBuffer[0], NormalNetworkBufferLen, RecvResult, NormalReceive );
//	//	if( false == bTryReceive )
//	//	{
//	//		if( SOCKET_ERROR == RecvResult )
//	//		{
//	//			break;
//	//		}

//	//		if( 10054 == RecvResult )
//	//		{
//	//			break;
//	//		}

//	//		if( 10038 == RecvResult )
//	//		{
//	//			break;
//	//		}
//	//		break;
//	//	}

//	//	if( true == bTryReceive && 0 < RecvResult )
//	//	{
//	//		CBasePacket *pPacket = reinterpret_cast<CBasePacket *>(RecvBuffer);
//	//		if( pPacket )
//	//		{
//	//			ENormalPacketOperation Operation = static_cast<ENormalPacketOperation>(pPacket->GetOperation());
//	//			switch ( Operation )
//	//			{
//	//				case RegisterAck:
//	//				{
//	//					CPacketRegisterAck *tempPacket = (CPacketRegisterAck *)pPacket;
//	//					if( true == tempPacket->CheckSize() )
//	//					{
//	//						PRINT_NORMAL_LOG( L"New UniqueID is [%d]\n", tempPacket->GetUniqueID( ) );
//	//					}
//	//					
//	//					break;
//	//				}
//	//				case LoginAck:
//	//				{
//	//					break;
//	//				}
//	//			}
//	//		}

//	//		//PRINT_NORMAL_LOG( L"Received DATA [%S]\n", RecvBuffer );
//	//		/*Sleep( 2 * SECOND );*/
//	//		//printf( "[TCP/%s:%d] %s\n", inet_ntoa( clientaddr.sin_addr ), ntohs( clientaddr.sin_port ), buf );
//	//	}
//	//}

/*else
{
PRINT_NORMAL_LOG( L"Failed to Connect Server![IP : %S, Port : %d]\n", ServerIP, AuroraNetwork::g_NetworkPort );

bool Reconnect = false;
while ( true )
{
Reconnect = pNetworkManager->InitClientNetwork( ServerIP, AuroraNetwork::g_NetworkPort );
Reconnect = pWinsockManager->StartEventSelectClient( pNetworkManager->GetClientSocket() );
Reconnect = pNetworkManager->ConnectToServer();
if( false == Reconnect )
{
PRINT_NORMAL_LOG( L"Failed to Connect Server![IP : %S, Port : %d]\n", ServerIP, AuroraNetwork::g_NetworkPort );
}
else
{
break;
}

Sleep( 1000 );
}

UserInput( pNetworkManager, pWinUtilManager );
return 0;
}*/
*/