//	SerialPort.h
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//

#pragma once

//---------------------------------------------------------------------------

#include "Serial.h"
#include "TMemPtr.hpp"
#include "Lock.hpp"
#include "Thread.hpp"
#include "TEvent.hpp"
#include "SerialEventArgs.h"

using namespace SDK_MAJOR_NAMESPACE::SDK_MINOR_NAMESPACE;

//---------------------------------------------------------------------------

#ifndef _SERIAL_PORT_H_
#define _SERIAL_PORT_H_

//---------------------------------------------------------------------------

#define SERIAL_MS_PER_SEC		1000
#define SERIAL_STOP_WAIT		50
#define SERIAL_SEND_WAIT		1
#define SERIAL_READ_WAIT		1
#define SERIAL_MAX_BUFSIZE		8200
#define SERIAL_SEPARATOR		","

//---------------------------------------------------------------------------

class CSerialPort : protected CThread
{
//private members
private:

	TMemPtr<CSerial>	m_ptrSerial;
	BYTE				m_bufRxData[SERIAL_MAX_BUFSIZE];

    int					m_numReadIdleTimeout;	//[s]
	int					m_numSendIdleTimeout;	//[s]
	time_t				m_objReadIdleTimeout;
	time_t				m_objSendIdleTimeout;
	CCriticalSection	m_objTimeoutLock;

	VOID*				m_ptrOwner;
	VOID*				m_ptrTag;

//constructor and destructor
public:

	CSerialPort(VOID);
	virtual ~CSerialPort(VOID);

//events
public:

	TEvent<CSerialPort, CSerialEventArgs>	ActivateEvent;
	TEvent<CSerialPort, CSerialEventArgs>	ShutdownEvent;
	TEvent<CSerialPort, CSerialEventArgs>	MainLoopEvent;
	TEvent<CSerialPort, CSerialEventArgs>	ReadIdleEvent;	//receiver idle timeout
	TEvent<CSerialPort, CSerialEventArgs>	SendIdleEvent;	//transmitter idle timeout
	TEvent<CSerialPort, CSerialEventArgs>	ReceivedEvent;	//data received

//properties
public:

	CSerial* GetSerial(VOID);
	VOID SetSerial(CSerial* value);

	string GetPortInfo(VOID);

	BaudRate GetBaudRate(VOID);
	VOID SetBaudRate(BaudRate flgBaud);

	DataSize GetDataBits(VOID);
	VOID SetDataBits(DataSize flgBits);

	ParityFlag GetParity(VOID);
	VOID SetParity(ParityFlag flgParity);

	StopSize GetStopBits(VOID);
	VOID SetStopBits(StopSize flgStop);

	int GetReadIdleTimeout(VOID);
	VOID SetReadIdleTimeout(int value);

	int GetSendIdleTimeout(VOID);
	VOID SetSendIdleTimeout(int value);

	VOID* GetOwner(VOID);
	VOID SetOwner(VOID* value);

	VOID* GetTag(VOID);
	VOID SetTag(VOID* value);

//public methods
public:

	virtual BOOL IsActive(VOID);
    virtual BOOL Activate(char const* pszSerial);
    virtual BOOL Shutdown(int numTimeout);

	size_t Send(BYTE const* bufData, size_t numSize);

//protected methods
protected:

//private methods
private:

	virtual BOOL ThreadStart(VOID* ptrParam);	//called from ThreadMain before main loop
	virtual BOOL ThreadStop(VOID* ptrParam);	//called from ThreadMain after main loop
	virtual BOOL ThreadProc(VOID* ptrParam);	//called from ThreadMain main loop

	VOID ResetReadIdleTimeout(VOID);
	VOID ResetSendIdleTimeout(VOID);
	VOID TestReadIdleTimeout(VOID);
	VOID TestSendIdleTimeout(VOID);
};

//---------------------------------------------------------------------------
#endif	//_SERIAL_PORT_H_
