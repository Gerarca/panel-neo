// TestApp.cpp : Defines the entry point for the console application.
//

#include "DSC_Types.hpp"
#include "Application.h"
#include "Debug.hpp"

#if defined(WINDOWS)
#include <stdio.h>
#include <conio.h>
#elif defined(LINUX)
#include <cctype>
#include "LinuxIO.h"
#include <cstdio>
#else
#error "Undefined platform information!"
#endif

using namespace std;
using namespace SDK_MAJOR_NAMESPACE::SDK_MINOR_NAMESPACE;

#define APPLICATION_CHAR	'A'
#define TESTRUNNER_CHAR     'T'
 
//---------------------------------------------------------------------------

int main(int argc, char* argv[])
{  
#if defined(LINUX) 
	CLinuxIO::setup();
#endif

	printf("TestApp Start!\n");

	//init sockets
	if (FALSE == CSocket::Initialize())
	{
		printf("TestApp: Couldn't initialize Windows sockets!\n");
	}
	else
	{ 
		//execute the application
		CApplication application;
		application.Execute();
	} // if
	
	//cleanup
	CSocket::CleanupAll();

	printf("TestApp Stop!\n");
	printf("Press ENTER Key To Continue!\n");
	_getch();

#if defined(LINUX)
	CLinuxIO::restore();
#endif

	return 0;
}

//---------------------------------------------------------------------------
