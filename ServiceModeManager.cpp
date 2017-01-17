#pragma once
#include "Includes.h"
#include "ServiceModeManager.h"

using namespace Aurora;

WindowsServiceManager::WindowsServiceManager( void )
{
}


WindowsServiceManager::~WindowsServiceManager( void )
{
}


void WindowsServiceManager::Install( void )
{
	SC_HANDLE schSCManager;
	SC_HANDLE schService;
	TCHAR szPath[MAX_PATH];

	if( !GetModuleFileName( NULL, szPath, MAX_PATH ) )
	{
		printf( "Cannot install service (%d)\n", GetLastError() );
		return;
	}

	// Get a handle to the SCM database. 

	schSCManager = OpenSCManager(
								NULL,                    // local computer
								NULL,                    // ServicesActive database 
								SC_MANAGER_ALL_ACCESS );  // full access rights 

	if( NULL == schSCManager )
	{
		printf( "OpenSCManager failed (%d)\n", GetLastError() );
		return;
	}

	// Create the service

	schService = CreateService(
		schSCManager,								// SCM database 
		L"Service Mode Test",                   // name of service 
		L"Service Mode Test Version",               // service name to display 
		SERVICE_ALL_ACCESS,        // desired access 
		SERVICE_WIN32_OWN_PROCESS, // service type 
		SERVICE_DEMAND_START,      // start type 
		SERVICE_ERROR_NORMAL,      // error control type 
		szPath,                    // path to service's binary 
		NULL,                      // no load ordering group 
		NULL,                      // no tag identifier 
		NULL,                      // no dependencies 
		NULL,                      // LocalSystem account 
		NULL );                     // no password 

	if( schService == NULL )
	{
		printf( "CreateService failed (%d)\n", GetLastError() );
		CloseServiceHandle( schSCManager );
		return;
	}
	else
	{
		printf( "Service installed successfully\n" );
	}

	CloseServiceHandle( schService );
	CloseServiceHandle( schSCManager );
}

void WindowsServiceManager::Delete( void )
{
	SC_HANDLE schSCManager;
	SC_HANDLE schService;
	//SERVICE_STATUS ssStatus;

	// Get a handle to the SCM database. 

	schSCManager = OpenSCManager(
		NULL,                    // local computer
		NULL,                    // ServicesActive database 
		SC_MANAGER_ALL_ACCESS );  // full access rights 

	if( NULL == schSCManager )
	{
		printf( "OpenSCManager failed (%d)\n", GetLastError() );
		return;
	}

	// Get a handle to the service.

	schService = OpenService(
		schSCManager,       // SCM database 
		L"Service Mode Test",          // name of service 
		DELETE );            // need delete access 

	if( schService == NULL )
	{
		printf( "OpenService failed (%d)\n", GetLastError() );
		CloseServiceHandle( schSCManager );
		return;
	}

	// Delete the service.

	if( !DeleteService( schService ) )
	{
		printf( "DeleteService failed (%d)\n", GetLastError() );
	}
	else printf( "Service deleted successfully\n" );

	CloseServiceHandle( schService );
	CloseServiceHandle( schSCManager );
}

void WindowsServiceManager::UpdateDesc( void )
{
	SC_HANDLE schSCManager;
	SC_HANDLE schService;
	SERVICE_DESCRIPTION sd;
	LPTSTR szDesc = TEXT( "Test SERVER?" );

	// Get a handle to the SCM database. 

	schSCManager = OpenSCManager(
		NULL,                    // local computer
		NULL,                    // ServicesActive database 
		SC_MANAGER_ALL_ACCESS );  // full access rights 

	if( NULL == schSCManager )
	{
		printf( "OpenSCManager failed (%d)\n", GetLastError() );
		return;
	}

	// Get a handle to the service.

	schService = OpenService(
		schSCManager,				// SCM database 
		L"Service Mode Test",  // name of service 
		SERVICE_CHANGE_CONFIG );		// need change config access 

	if( schService == NULL )
	{
		printf( "OpenService failed (%d)\n", GetLastError() );
		CloseServiceHandle( schSCManager );
		return;
	}

	// Change the service description.

	sd.lpDescription = szDesc;

	if( !ChangeServiceConfig2(
		schService,                 // handle to service
		SERVICE_CONFIG_DESCRIPTION, // change: description
		&sd ) )                      // new description
	{
		printf( "ChangeServiceConfig2 failed\n" );
	}
	else printf( "Service description updated successfully.\n" );

	CloseServiceHandle( schService );
	CloseServiceHandle( schSCManager );
}

// test code.
//WindowsServiceManager test;
//
//test.Install( );
//test.UpdateDesc( );
//Sleep( 10000 );
//test.Delete( );
//return 0;