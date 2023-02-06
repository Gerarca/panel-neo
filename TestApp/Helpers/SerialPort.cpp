//	SerialPort.cpp
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//

#include "SerialPort.h"
#include <ctime>
#include <limits>

#if defined(WINDOWS)
#include <tchar.h>
#elif defined(LINUX)
#else
#error "Undefined platform information!"
#endif

using namespace std;

//---------------------------------------------------------------------------

CSerialPort::CSerialPort(VOID) :  
	m_numReadIdleTimeout(0), m_numSendIdleTimeout(0),
	m_ptrOwner(NULL), m_ptrTag(NULL)
{
	DEBUG_PRINTF("[CSerialPort::CSerialPort] %p\n", this);

	//initialize member variables
	m_ptrSerial.Create();

	//reset timeouts
	ResetReadIdleTimeout();
	ResetSendIdleTimeout();
}

//---------------------------------------------------------------------------

CSerialPort::~CSerialPort(VOID)
{
	DEBUG_PRINTF("[CSerialPort::~CSerialPort] %p\n", this);

	//shutdown
	Shutdown(THREAD_STOP_COUNT);
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

CSerial* CSerialPort::GetSerial(VOID)
{
	return static_cast<CSerial*>(m_ptrSerial);
}

VOID CSerialPort::SetSerial(CSerial* value)
{
	m_ptrSerial.Attach(value, 1);
}

//---------------------------------------------------------------------------

BOOL CSerialPort::IsActive(VOID)
{
	ThreadState state = CThread::GetState();
	return ((ThreadStates::Unknown != state) &&
		(ThreadStates::Stopped != state))? TRUE : FALSE;
}

//---------------------------------------------------------------------------

BOOL CSerialPort::Activate(char const* pszSerial)
{
	//check the socket
	if (FALSE == m_ptrSerial.IsNull())
	{
		//failure
		return FALSE;
	}

	try
	{
		//try opening the serial
		if (FALSE == m_ptrSerial->Open(pszSerial))
		{
			//failed to open the serial
			goto Activate_Failure;
		}

		//start the therad
		if (FALSE != CThread::Start())
		{
			//success
			return TRUE;
		} 
	}
	catch (...) {}

Activate_Failure:

	//make sure everything is shutdown
	Shutdown(THREAD_STOP_COUNT);
	return FALSE;
}

//---------------------------------------------------------------------------

BOOL CSerialPort::Shutdown(int numTimeout)
{
	//stop the thread
	if (FALSE == CThread::Stop(numTimeout))
	{
		//the thread hasn't stopped yet
		return FALSE;
	}

	//check the socket
	if (FALSE == m_ptrSerial.IsNull())
	{
		//shutdown and close the serial
		try { m_ptrSerial->Close(); }
		catch (...) {}
	}

	//done
	return TRUE;
}

//---------------------------------------------------------------------------

size_t CSerialPort::Send(BYTE const* bufData, size_t numSize)
{
	//sanity check
	CSerial* pserial = GetSerial();
	if (NULL == pserial)
	{
		//failure
		return 0;
	}

	//send data
	int sent = pserial->Send(bufData, numSize);
	if (0 <= sent)
	{
		//reset tx idle timeout
		ResetSendIdleTimeout();

		//allow thread switching
		Platform::THREAD_SLEEP(SERIAL_SEND_WAIT);

		//return the number of bytes sent
		return sent;
	}
	else
	{
		//error while sending data
		DEBUG_CHECK(FALSE);
		RELEASE_CHECK(FALSE);
	}

	//failure
	return 0;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

string CSerialPort::GetPortInfo(VOID)
{
	//check the serial
	if (FALSE == m_ptrSerial.IsNull())
	{
		return m_ptrSerial->GetPortInfo();
	}
	//failure
	return "";
}

//---------------------------------------------------------------------------

BaudRate CSerialPort::GetBaudRate(VOID)
{
	//check the serial
	if (FALSE == m_ptrSerial.IsNull())
	{
		return m_ptrSerial->GetBaudRate();
	}
	//failure
	return static_cast<BaudRate>(SERIAL_ERROR);
}

VOID CSerialPort::SetBaudRate(BaudRate flgBaud)
{
	//check the serial
	if (FALSE == m_ptrSerial.IsNull())
	{
		return m_ptrSerial->SetBaudRate(flgBaud);
	}
}

//---------------------------------------------------------------------------

DataSize CSerialPort::GetDataBits(VOID)
{
	//check the serial
	if (FALSE == m_ptrSerial.IsNull())
	{
		return m_ptrSerial->GetDataBits();
	}
	//failure
	return static_cast<DataSize>(SERIAL_ERROR);
}

VOID CSerialPort::SetDataBits(DataSize flgBits)
{
	//check the serial
	if (FALSE == m_ptrSerial.IsNull())
	{
		return m_ptrSerial->SetDataBits(flgBits);
	}
}

//---------------------------------------------------------------------------

ParityFlag CSerialPort::GetParity(VOID)
{
	//check the serial
	if (FALSE == m_ptrSerial.IsNull())
	{
		return m_ptrSerial->GetParity();
	}
	//failure
	return static_cast<ParityFlag>(SERIAL_ERROR);
}

VOID CSerialPort::SetParity(ParityFlag flgParity)
{
	//check the serial
	if (FALSE == m_ptrSerial.IsNull())
	{
		return m_ptrSerial->SetParity(flgParity);
	}
}

//---------------------------------------------------------------------------

StopSize CSerialPort::GetStopBits(VOID)
{
	//check the serial
	if (FALSE == m_ptrSerial.IsNull())
	{
		return m_ptrSerial->GetStopBits();
	}
	//failure
	return static_cast<StopSize>(SERIAL_ERROR);
}

VOID CSerialPort::SetStopBits(StopSize flgStop)
{
	//check the serial
	if (FALSE == m_ptrSerial.IsNull())
	{
		return m_ptrSerial->SetStopBits(flgStop);
	}
}

//---------------------------------------------------------------------------

int CSerialPort::GetReadIdleTimeout(VOID)
{
	CLock lock = m_objTimeoutLock;
	return m_numReadIdleTimeout;
}

VOID CSerialPort::SetReadIdleTimeout(int value)
{
	CLock lock = m_objTimeoutLock;
	m_numReadIdleTimeout = (value > 0)? value : 0;
}

//---------------------------------------------------------------------------

int CSerialPort::GetSendIdleTimeout(VOID)
{
	CLock lock = m_objTimeoutLock;
	return m_numSendIdleTimeout;
}

VOID CSerialPort::SetSendIdleTimeout(int value)
{
	CLock lock = m_objTimeoutLock;
	m_numSendIdleTimeout = (value > 0)? value : 0;
}

//---------------------------------------------------------------------------

VOID* CSerialPort::GetOwner(VOID)
{
	return m_ptrOwner;
}

VOID CSerialPort::SetOwner(VOID* value)
{
	m_ptrOwner = value;
}

//---------------------------------------------------------------------------

VOID* CSerialPort::GetTag(VOID)
{
	return m_ptrTag;
}

VOID CSerialPort::SetTag(VOID* value)
{
	m_ptrTag = value;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

BOOL CSerialPort::ThreadStart(VOID* ptrParam)
{
	//sanity check
	CSerial* pserial = GetSerial();
	if (NULL == pserial)
	{
		//failure
		return FALSE;
	}

	//reset timeouts
	ResetReadIdleTimeout();
	ResetSendIdleTimeout();

	//prepare event args
	CSerialEventArgs args;
	args.m_strPortInfo = pserial->GetPortInfo();
	args.m_bufDataBuffer.Delete();

    //fire event
    try { ActivateEvent(this, &args); } catch (...) {}
	return TRUE;
}

//---------------------------------------------------------------------------

BOOL CSerialPort::ThreadStop(VOID* ptrParam)
{
	//prepare event args
	CSerialEventArgs args;
	CSerial* pserial = GetSerial();
	args.m_strPortInfo = (NULL != pserial)? pserial->GetPortInfo() : "";
	args.m_bufDataBuffer.Delete();

	//close the serial
	if (NULL != pserial)
	{
		try { pserial->Close(); }
		catch (...) {}
	}

    //fire event
    try { ShutdownEvent(this, &args); } catch (...) {}
	return TRUE;
}

//---------------------------------------------------------------------------

BOOL CSerialPort::ThreadProc(VOID* ptrParam)
{
	//sanity check
	CSerial* pserial = GetSerial();
	if (NULL == pserial)
	{
		//failure
		return FALSE;
	}

	//prepare event args
	CSerialEventArgs args;
	args.m_strPortInfo = pserial->GetPortInfo();

	//check if the serial is open
	if (FALSE != pserial->IsOpen())
	{
		//read all available data
		int read = pserial->Read(m_bufRxData, SERIAL_MAX_BUFSIZE);
		if (0 < read)
		{
			//reset read idle timeout
			ResetReadIdleTimeout();

			//allocate data buffer
			if (FALSE == args.m_bufDataBuffer.Create(read))
			{
				//failed to allocate required memory
				DEBUG_CHECK(FALSE);
				RELEASE_CHECK(FALSE);
				return FALSE;
			}

			//copy the data
			memcpy(args.m_bufDataBuffer, m_bufRxData, read);

			//fire event
			try { ReceivedEvent(this, &args); } catch (...) {}
		}
		else if (0 == read)
		{
			//check read idle timeout
			TestReadIdleTimeout();
		
			//check send idle timeout
			TestSendIdleTimeout();

			//switch threads - take your time because there was no new data
			Platform::THREAD_SLEEP(SERIAL_READ_WAIT);
		}
		else
		{
			//error while reading serial data
			DEBUG_CHECK(FALSE);
			RELEASE_CHECK(FALSE);
			return FALSE;	//end the thread
		}
	}
	else
	{
		//the serial is no longer open
		return FALSE;	//end the thread
	}

	//fire event
	try { MainLoopEvent(this, &args); } catch (...) {}
	return TRUE;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

VOID CSerialPort::ResetReadIdleTimeout(VOID)
{
	//reset rx idle timeout
	CLock lock = m_objTimeoutLock;
	int timeout = m_numReadIdleTimeout;
	m_objReadIdleTimeout = (0 < timeout)? 
		time(NULL) + timeout : (numeric_limits<time_t>::max)();
}

//---------------------------------------------------------------------------

VOID CSerialPort::ResetSendIdleTimeout(VOID)
{
	//reset tx idle timeout
	CLock lock = m_objTimeoutLock;
	int timeout = m_numSendIdleTimeout;
	m_objSendIdleTimeout = (0 < timeout)? 
		time(NULL) + timeout : (numeric_limits<time_t>::max)();
}

//---------------------------------------------------------------------------

VOID CSerialPort::TestReadIdleTimeout(VOID)
{
	//check idle timeout
	CLock lock = m_objTimeoutLock;
	if (0 >= difftime(m_objReadIdleTimeout, time(NULL)))
	{
		//reset rx idle timeout
		int timeout = m_numReadIdleTimeout;
		m_objReadIdleTimeout = (0 < timeout)? 
			time(NULL) + timeout : (numeric_limits<time_t>::max)();

		//prepare event args
		CSerialEventArgs args;
		CSerial* pserial = GetSerial();
		args.m_strPortInfo = (NULL != pserial)? pserial->GetPortInfo() : "";
		args.m_bufDataBuffer.Delete();

		//signal idle
		try { ReadIdleEvent(this, &args); } catch (...) {}
	}
}

//---------------------------------------------------------------------------

VOID CSerialPort::TestSendIdleTimeout(VOID)
{
	//check idle timeout
	CLock lock = m_objTimeoutLock;
	if (0 >= difftime(m_objSendIdleTimeout, time(NULL)))
	{
		//reset tx idle timeout
		int timeout = m_numSendIdleTimeout;
		m_objSendIdleTimeout = (0 < timeout)? 
			time(NULL) + timeout : (numeric_limits<time_t>::max)();
		
		//prepare event args
		CSerialEventArgs args;
		CSerial* pserial = GetSerial();
		args.m_strPortInfo = (NULL != pserial)? pserial->GetPortInfo() : "";
		args.m_bufDataBuffer.Delete();

		//signal idle
		try { SendIdleEvent(this, &args); } catch (...) {}
	}
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
