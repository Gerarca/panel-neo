#include "LinuxIO.h"
#include <sys/select.h>
#include <iostream>
#include <unistd.h>
#include <termios.h>
#include <cstdio>

//disable some well-understood warnings
#if defined(MS_VS_COMPILER)
#elif defined(GCC_COMPILER)
#else
#error "Undefined compiler information!"
#endif	//MS_VS_COMPILER

//---------------------------------------------------------------------------

struct termios CLinuxIO::original_terminal;

//---------------------------------------------------------------------------

CLinuxIO::CLinuxIO(VOID)
{
}

//---------------------------------------------------------------------------

CLinuxIO::~CLinuxIO(VOID)
{
}

//---------------------------------------------------------------------------

int CLinuxIO::getch(VOID)
{
	return(std::cin.get());
}

//---------------------------------------------------------------------------

int CLinuxIO::kbhit(VOID)
{
	fd_set rfds;
	struct timeval tv;

	// immediate return
	tv.tv_sec = 0;
	tv.tv_usec = 0;

	FD_ZERO(&rfds);
	FD_SET(STDIN_FILENO, &rfds);

	switch (select(STDIN_FILENO + 1, &rfds, NULL, NULL, &tv))
	{
		case -1:
			// error
			break;
		case 0:
			// nothing available
			break;
		default:
			if (FD_ISSET(STDIN_FILENO, &rfds))
			{
				return(1);
			}
			break;
	}
	return(0);
}

//---------------------------------------------------------------------------

VOID CLinuxIO::getline(char* line, size_t max)
{
	std::cin.getline(line, max);
}

//---------------------------------------------------------------------------

VOID CLinuxIO::setup(VOID)
{
	// save current terminal so we can go back to it
	struct termios terminal;
	tcgetattr(STDIN_FILENO, &terminal);
	original_terminal = terminal;

	// Set terminal to single character mode initially
	setCharacterMode();
}

//---------------------------------------------------------------------------

VOID CLinuxIO::restore(VOID)
{
	// Restore terminal mode.
	if (tcsetattr(STDIN_FILENO, TCSANOW, &original_terminal) < 0) {
		DEBUG_PRINT("Unable to restore original terminal mode\n");
	}
}

//---------------------------------------------------------------------------

VOID CLinuxIO::setCharacterMode(VOID)
{
	struct termios terminal;
	tcgetattr(STDIN_FILENO, &terminal);

	terminal.c_lflag &= (~ICANON & ~ECHO);
	terminal.c_cc[VTIME] = 0;
	terminal.c_cc[VMIN] = 1;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &terminal) < 0)
	{
		DEBUG_PRINT("Unable to set terminal to character mode\n");
	}
}

//---------------------------------------------------------------------------

VOID CLinuxIO::setLineMode(VOID)
{
	struct termios terminal;
	tcgetattr(STDIN_FILENO, &terminal);

	terminal.c_lflag &= (~ECHO);
	terminal.c_lflag |= (ICANON);
	terminal.c_cc[VTIME] = 0;
	terminal.c_cc[VMIN] = 0;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &terminal) < 0)
	{
		DEBUG_PRINT("Unable to set terminal to line mode\n");
	}
}

//---------------------------------------------------------------------------

#if defined(MS_VS_COMPILER)
#elif defined(GCC_COMPILER)
#else
#error "Undefined compiler information!"
#endif	//MS_VS_COMPILER

//---------------------------------------------------------------------------
