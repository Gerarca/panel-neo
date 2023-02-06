#pragma once

//---------------------------------------------------------------------------

#include "DSC_Config.hpp"
#include "DSC_Types.hpp"
#include "Debug.hpp"
#include <termios.h>

//---------------------------------------------------------------------------

#ifndef _LINUX_IO_H_
#define _LINUX_IO_H_

#define _kbhit CLinuxIO::kbhit
#define _getch CLinuxIO::getch

//---------------------------------------------------------------------------

class CLinuxIO
{
	//private members
private:
	static struct termios original_terminal;

	// constructor
private:
	CLinuxIO(VOID);

	// destructor
public:
	virtual ~CLinuxIO(VOID);

	//properties
public:

	//public methods
public:
	static int  kbhit(VOID);
	static int  getch(VOID);
	static VOID getline(char* line, size_t max);
	static VOID setup(VOID);
	static VOID restore(VOID);
	static VOID setCharacterMode(VOID);
	static VOID setLineMode(VOID);

	//private methods
private:
};

//---------------------------------------------------------------------------
#endif	//_LINUX_IO_H_
