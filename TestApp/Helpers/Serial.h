//	Serial.h
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//

#pragma once

#ifndef _SERIAL_H_
#define _SERIAL_H_

#include "DSC_Types.hpp"
#include <string>

using namespace std;

//---------------------------------------------------------------------------

#if defined(WINDOWS)

#define INVALID_SERIAL	INVALID_HANDLE_VALUE
//enable this if terminating IO on error is required
//#define SERIAL_ABORT_ON_ERROR

#elif defined(LINUX)

#define INVALID_SERIAL	(-1)

#else
#error "Undefined platform information!"
#endif

//---------------------------------------------------------------------------

#define SERIAL_ERROR	(-1)

//---------------------------------------------------------------------------

namespace BaudRates {
enum value {
    BR_110 = CBR_110,
    BR_300 = CBR_300,
    BR_600 = CBR_600,
    BR_1200 = CBR_1200,
    BR_2400 = CBR_2400,
    BR_4800 = CBR_4800,
    BR_9600 = CBR_9600,
    BR_14400 = CBR_14400,
    BR_19200 = CBR_19200,
    BR_38400 = CBR_38400,
    BR_56000 = CBR_56000,
    BR_57600 = CBR_57600,
    BR_115200 = CBR_115200
    //BR_128000 = CBR_128000,
    //BR_256000 = CBR_256000
}; }
typedef BaudRates::value BaudRate;

namespace DataSizes {
enum value {
    DB_5 = 5,
    DB_6 = 6,
    DB_7 = 7,
    DB_8 = 8
}; }
typedef DataSizes::value DataSize;

namespace ParityFlags {
enum value {
    PF_NONE = NOPARITY,
    PF_ODD = ODDPARITY,
    PF_EVEN = EVENPARITY,
    PF_MARK = MARKPARITY,
    PF_SPACE = SPACEPARITY
}; }
typedef ParityFlags::value ParityFlag;

namespace StopSizes {
enum value {
    SB_ONE = ONESTOPBIT,
    SB_ONE_HALF = ONE5STOPBITS,
    SB_TWO = TWOSTOPBITS
}; }
typedef StopSizes::value StopSize;

namespace ErrorFlags {
enum value {
	ERR_UNKNOWN	= 0,	//unknown error

    ERR_RXOVER = CE_RXOVER, //receive buffer overrun
    ERR_OVERRUN = CE_OVERRUN, //receive buffer overflow / data lost
    ERR_PARITY = CE_RXPARITY,  //receive parity error
    ERR_FRAME = CE_FRAME, //receive framing error detected
    ERR_BREAK = CE_BREAK, //break condition detected
    ERR_TXFULL = CE_TXFULL  //transmitter queue is full
}; }
typedef ErrorFlags::value ErrorFlag;

//---------------------------------------------------------------------------

class CSerial
{
private:  //constants
#if defined(WINDOWS)
	static const int SERIAL_DEFAULT_BYTE_READ_TIMEOUT = 15; //[ms]
	static const int SERIAL_DEFAULT_TAIL_READ_TIMEOUT = 45; //[ms]
	static const int SERIAL_DEFAULT_BYTE_SEND_TIMEOUT = 15; //[ms]
	static const int SERIAL_DEFAULT_TAIL_SEND_TIMEOUT = 45; //[ms]
	static const int SERIAL_DEFAULT_IDLE_READ_TIMEOUT = MAXDWORD;  //[ms]
#elif defined(LINUX)
//linux does not support this functionality
#else
#error "Undefined platform information!"
#endif

private:  //member variables
	string		m_strPortInfo;
	BaudRate	m_flgBaudRate;
	DataSize	m_flgDataBits;
	ParityFlag	m_flgParity;
	StopSize	m_flgStopBits;

#if defined(WINDOWS)
	int			m_numByteReadTimeout;  //timeout in [ms] to receive one byte
	int			m_numTailReadTimeout;  //additional timeout in [ms] to receive bytes
	int			m_numByteSendTimeout;  //timeout in [ms] to send one byte
	int			m_numTailSendTimeout;  //additional timeout in [ms] to send bytes
	int			m_numIdleReadTimeout;  //timeout in [ms] to wait for next byte (max gap)
#elif defined(LINUX)
//linux does not support this functionality
#else
#error "Undefined platform information!"
#endif


#if defined(WINDOWS)
  HANDLE		m_hSerialPort;
  COMMTIMEOUTS	m_bufTimeouts;
#elif defined(LINUX)
  int			m_hSerialPort;
#else
#error "Undefined platform information!"
#endif

private:  //private methods
  VOID ResetSerial(VOID);

public:   //constructor and destructor
	CSerial(VOID);
	virtual ~CSerial(VOID);

public:	//properties
	string GetPortInfo(VOID);

	BaudRate GetBaudRate(VOID);
	VOID SetBaudRate(BaudRate flgBaud);

	DataSize GetDataBits(VOID);
	VOID SetDataBits(DataSize flgBits);

	ParityFlag GetParity(VOID);
	VOID SetParity(ParityFlag flgParity);

	StopSize GetStopBits(VOID);
	VOID SetStopBits(StopSize flgStop);

#if defined(WINDOWS)
	int GetByteReadTimeout(VOID);
	VOID SetByteReadTimeout(int numTimeout);

	int GetTailReadTimeout(VOID);
	VOID SetTailReadTimeout(int numTimeout);

	int GetByteSendTimeout(VOID);
	VOID SetByteSendTimeout(int numTimeout);

	int GetTailSendTimeout(VOID);
	VOID SetTailSendTimeout(int numTimeout);

	int GetIdleReadTimeout(VOID);
	VOID SetIdleReadTimeout(int numTimeout);
#elif defined(LINUX)
//linux does not support this functionality
#else
#error "Undefined platform information!"
#endif

public:   //public methods
	BOOL IsOpen(VOID);  //check if the port has been open
	BOOL Open(char const* pszSerial); //open serial port and setup timeouts
	VOID Close(VOID); //close the serial port

	int Send(BYTE const* bufData, size_t numSize);	//send data
	int Read(BYTE* bufData, size_t numSize);		//read data

#if defined(WINDOWS) && defined(SERIAL_ABORT_ON_ERROR)
	//the function checks and clears communication errors
	//it may pass back the number of bytes waiting to be read
	ErrorFlag Clear(int* ptrBytesToRead = NULL);
#endif
};

//---------------------------------------------------------------------------
#endif  //_SERIAL_H_
