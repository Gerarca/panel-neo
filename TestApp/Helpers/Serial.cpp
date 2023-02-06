#include "Serial.h"

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

CSerial::CSerial(VOID) : m_hSerialPort(INVALID_SERIAL)
{
	//setup defaults
	ResetSerial();
}

//---------------------------------------------------------------------------

CSerial::~CSerial(VOID)
{
	//close the port
	Close();
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

BaudRate CSerial::GetBaudRate(VOID)
{
	return m_flgBaudRate;
}

VOID CSerial::SetBaudRate(BaudRate flgBaud)
{
	m_flgBaudRate = flgBaud;
}

//---------------------------------------------------------------------------

DataSize CSerial::GetDataBits(VOID)
{
	return m_flgDataBits;
}

VOID CSerial::SetDataBits(DataSize flgBits)
{
	m_flgDataBits = flgBits;
}

//---------------------------------------------------------------------------

ParityFlag CSerial::GetParity(VOID)
{
	return m_flgParity;
}

VOID CSerial::SetParity(ParityFlag flgParity)
{
	m_flgParity = flgParity;
}

//---------------------------------------------------------------------------

StopSize CSerial::GetStopBits(VOID)
{
	return m_flgStopBits;
}

VOID CSerial::SetStopBits(StopSize flgStop)
{
	m_flgStopBits = flgStop;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

#if defined(WINDOWS)

//---------------------------------------------------------------------------

int CSerial::GetByteReadTimeout(VOID)
{
	return m_numByteReadTimeout;
}

VOID CSerial::SetByteReadTimeout(int numTimeout)
{
	m_numByteReadTimeout = ((numTimeout > 0) || 
		(numTimeout == MAXDWORD))? numTimeout : 0;
}

//---------------------------------------------------------------------------

string CSerial::GetPortInfo(VOID)
{
	return m_strPortInfo;
}

//---------------------------------------------------------------------------

int CSerial::GetTailReadTimeout(VOID)
{
	return m_numTailReadTimeout;
}

VOID CSerial::SetTailReadTimeout(int numTimeout)
{
	m_numTailReadTimeout = ((numTimeout > 0) || 
		(numTimeout == MAXDWORD))? numTimeout : 0;
}

//---------------------------------------------------------------------------

int CSerial::GetByteSendTimeout(VOID)
{
	return m_numByteSendTimeout;
}

VOID CSerial::SetByteSendTimeout(int numTimeout)
{
	m_numByteSendTimeout = ((numTimeout > 0) || 
		(numTimeout == MAXDWORD))? numTimeout : 0;
}

//---------------------------------------------------------------------------

int CSerial::GetTailSendTimeout(VOID)
{
	return m_numTailSendTimeout;
}

VOID CSerial::SetTailSendTimeout(int numTimeout)
{
	m_numTailSendTimeout = ((numTimeout > 0) || 
		(numTimeout == MAXDWORD))? numTimeout : 0;
}

//---------------------------------------------------------------------------

int CSerial::GetIdleReadTimeout(VOID)
{
	return m_numIdleReadTimeout;
}

VOID CSerial::SetIdleReadTimeout(int numTimeout)
{
	m_numIdleReadTimeout = ((numTimeout > 0) || 
		(numTimeout == MAXDWORD))? numTimeout : 0;
}

//---------------------------------------------------------------------------

#elif defined(LINUX)
//linux does not support this functionality
#else
#error "Undefined platform information!"
#endif

//---------------------------------------------------------------------------

BOOL CSerial::IsOpen(VOID)
{
	return (INVALID_SERIAL != m_hSerialPort)? TRUE : FALSE;
}

//---------------------------------------------------------------------------

BOOL CSerial::Open(char const* pszSerial)
{
	//check if the serial is already open
	if (INVALID_SERIAL != m_hSerialPort)
	{
		//the serial is already open
		return FALSE;
	}

#if defined(WINDOWS)
	//open the serial port
	m_hSerialPort = CreateFile(pszSerial, GENERIC_READ | GENERIC_WRITE,
		0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_SERIAL != m_hSerialPort)
	{
		//store port info
		m_strPortInfo = pszSerial;

		//setup the control data block
		DCB ctrl;
		memset(&ctrl, 0, sizeof(DCB));
		ctrl.DCBlength = sizeof(DCB);

#if defined(SERIAL_ABORT_ON_ERROR)
		ctrl.fAbortOnError = TRUE;
#endif
		ctrl.fBinary = TRUE; //only binary mode is supported
		ctrl.fParity = (ParityFlags::PF_NONE != m_flgParity) ? TRUE : FALSE; //enable parity checking
		ctrl.BaudRate = m_flgBaudRate;
		ctrl.ByteSize = m_flgDataBits;
		ctrl.Parity = m_flgParity;
		ctrl.StopBits = m_flgStopBits;

		ctrl.fDtrControl = DTR_CONTROL_ENABLE; //enable DTR
		ctrl.fRtsControl = RTS_CONTROL_ENABLE; //enable RTS

		//setup comm port
		if (SetCommState(m_hSerialPort, &ctrl))
		{
			//save currently used timeouts (so 
			//they can be restored upon closing)
			if (GetCommTimeouts(m_hSerialPort, &m_bufTimeouts))
			{
				//make a copy of current timeouts
				COMMTIMEOUTS timeouts;
				memcpy(&timeouts, &m_bufTimeouts, sizeof(COMMTIMEOUTS));

				//setup new timeouts
				timeouts.ReadTotalTimeoutMultiplier =  m_numByteReadTimeout;
				timeouts.ReadTotalTimeoutConstant = m_numTailReadTimeout;
				timeouts.ReadIntervalTimeout = m_numIdleReadTimeout;
				timeouts.WriteTotalTimeoutMultiplier = m_numByteSendTimeout;
				timeouts.WriteTotalTimeoutConstant = m_numTailSendTimeout;

				//set new timeouts
				if (SetCommTimeouts(m_hSerialPort, &timeouts))
				{
					//success
					return TRUE;
				}
			}
		}
	}
#elif defined(LINUX)
	//open the serial port
	m_hSerialPort = open(pszSerial, O_RDWR | O_NOCTTY);
	if (INVALID_SERIAL != m_hSerialPort)
	{
		//store port info
		m_strPortInfo = pszSerial;

		//get attributes
		termios tty;
		memset(&tty, 0, sizeof(termios));
		if (0 == tcgetattr(m_hSerialPort, &tty))
		{
			//translate baud rates
			int baud = 0;
			switch (m_flgBaudRate)
			{
				case BaudRates::BR_110:
					baud = B110;
					break;
				case BaudRates::BR_300:
					baud = B300;
					break;
				case BaudRates::BR_600:
					baud = B600;
					break;
				case BaudRates::BR_1200:
					baud = B1200;
					break;
				case BaudRates::BR_2400:
					baud = B2400;
					break;
				case BaudRates::BR_4800:
					baud = B4800;
					break;
				case BaudRates::BR_9600:
					baud = B9600;
					break;
				//case BaudRates::BR_14400:
				//	break;
				case BaudRates::BR_19200:
					baud = B19200;
					break;
				case BaudRates::BR_38400:
					baud = B38400;
					break;
				//case BaudRates::BR_56000:
				//	break;
				case BaudRates::BR_57600:
					baud = B57600;
					break;
				case BaudRates::BR_115200:
					baud = B115200;
					break;
				default:
					baud = 0;	//unsupported baud rate!
					break;
			}

			//set input and output baud rates
			cfsetispeed(&tty, baud);
			cfsetospeed(&tty, baud);

			//set data size flags
			tty.c_cflag &= ~CSIZE;
			switch (m_flgDataBits)
			{
				case DataSizes::DB_5:
					tty.c_cflag |= CS5;
					break;
				case DataSizes::DB_6:
					tty.c_cflag |= CS6;
					break;
				case DataSizes::DB_7:
					tty.c_cflag |= CS7;
					break;
				case DataSizes::DB_8:
					tty.c_cflag |= CS8;
					break;
				default:
					tty.c_cflag |= CS8;
					break;
			}

			//set parity flags
			switch (m_flgParity)
			{
				case ParityFlags::PF_NONE:
					tty.c_cflag &= ~PARENB;
					break;
				case ParityFlags::PF_ODD:
					tty.c_cflag |= PARENB;
					tty.c_cflag |= PARODD;
					break;
				case ParityFlags::PF_EVEN:
					tty.c_cflag |= PARENB;
					tty.c_cflag &= ~PARODD;
					break;
				//case ParityFlags::PF_MARK:
				//	tty.c_cflag |= PARENB;
				//	break;
				//case ParityFlags::PF_SPACE:
				//	tty.c_cflag |= PARENB;
				//	break;
				default:
					tty.c_cflag &= ~PARENB;
					break;
			}

			//set stop bits flag
			switch (m_flgStopBits)
			{
				case StopSizes::SB_ONE:
					tty.c_flag &= ~CSTOPB;
					break;
				case StopSizes::SB_ONE_HALF:
				case StopSizes::SB_TWO:
					tty.c_cflag |= CSTOPB;
					break;
				default:
					tty.c_flag &= ~CSTOPB;
					break;
			}

			//setup other control flags
			tty.c_cflags |= CLOCAL | CREAD;	//ignore modem control lines, enable receiver

			//setup the remaining flags
			tty.c_iflag = 0;
			tty.c_oflag = 0;	//no remaping, no delays
			tty.c_lflag = 0;	//no signaling chars, no echo, no canonical processing
			tty.c_cc[VMIN] = 0;		//read doesn't wait for any number of chars
			tty.c_cc[VTIME] = 0;	//read doesn't wait for any period of time

			//check if the baud is supported
			if (0 != baud)
			{
				//set the attributes
				if (0 == tcsetattr(m_hSerialPort, TCSANOW, &tty))
				{
					//flush the buffers now
					tcflush(m_hSerialPort, TCIOFLUSH);

					//success
					return TRUE;
				}
			}
		}
	}
#else
#error "Undefined platform information!"
#endif

	//close the serial port
	Close();

	//failure
	return FALSE;
}

//---------------------------------------------------------------------------

VOID CSerial::Close(VOID)
{
	//check if the port is open
	if (INVALID_SERIAL != m_hSerialPort)
	{
#if defined(WINDOWS)
		//restore default timeouts
		if (FALSE == SetCommTimeouts(m_hSerialPort, &m_bufTimeouts))
		{
			//handle error
		}

		//close handle
		if (FALSE != CloseHandle(m_hSerialPort))
		{
			//port closed
			m_hSerialPort = INVALID_SERIAL;
		}
#elif defined(LINUX)
		//restore default timeouts
		//...?

		//close serial port
		if (0 <= close(m_hSerialPort))
		{
			//port closed
			m_hSerialPort = INVALID_SERIAL;
		}
		else
		{
			//handle error
		}
#else
#error "Undefined platform information!"
#endif
	}
	
	//reset to defaults
	ResetSerial();
}

//---------------------------------------------------------------------------

int CSerial::Send(BYTE const* bufData, size_t numSize)
{
	//is the port open?
	if (INVALID_SERIAL != m_hSerialPort)
	{
		//is data present?
		if ((NULL != bufData) && (0 < numSize))
		{
#if defined(WINDOWS)
			DWORD sent = 0;
			if (FALSE != WriteFile(
				m_hSerialPort, static_cast<VOID const*>(bufData), 
				static_cast<DWORD>(numSize), &sent, NULL))
			{
				//return the number of bytes sent
				return static_cast<int>(sent);
			}
#elif defined(LINUX)
			return write(m_hSerialPort, 
				static_cast<VOID const*>(bufData), numSize);
#else
#error "Undefined platform information!"
#endif
		}
	}
	
	//error
	return SERIAL_ERROR;
}

//---------------------------------------------------------------------------

int CSerial::Read(BYTE* bufData, size_t numSize)
{
	//is the port open?
	if (INVALID_SERIAL != m_hSerialPort)
	{
		//is data buffer present?
		if ((NULL != bufData) && (0 < numSize))
		{
#if defined(WINDOWS)
			DWORD read = 0;
			if (FALSE != ReadFile(
				m_hSerialPort, static_cast<VOID*>(bufData), 
				static_cast<DWORD>(numSize), &read, NULL))
			{
				  //return the number of bytes read
				  return static_cast<int>(read);
			}
			else
			{
				//get error code (re-use the 'read' local variable)
				read = GetLastError();
				switch (read)
				{
					case ERROR_IO_PENDING:
						//this is technically not an error
						return 0;
					default:
						//does the error code value fit within the 32-bit 'int'?
						if (INT32_MAX >= read)
						{
							//convert the error code to a negative value
							return (-1) * static_cast<int>(read);
						}
						//the error code does not fit within the 32-bit 'int'
						return static_cast<int>(INT32_MIN);	//generic error code
				}
			}
#elif defined(LINUX)
			return read(m_hSerialPort, 
				static_cast<VOID*>(bufData), numSize);
#else
#error "Undefined platform information!"
#endif
		}
	}

	//error
	return SERIAL_ERROR;
}

//---------------------------------------------------------------------------

#if defined(WINDOWS) && defined(SERIAL_ABORT_ON_ERROR)
ErrorFlag CSerial::Clear(int* ptrBytesToRead)
{
	//check if the serial port is open
	if (INVALID_SERIAL != m_hSerialPort)
	{
		DWORD flags = 0;
		if (NULL != ptrBytesToRead)
		{
			//get and clear the communication error
			COMSTAT state;
			memset(&state, 0, sizeof(COMSTAT));
			if (FALSE != ClearCommError(m_hSerialPort, &flags, &state))
			{
				//return the number of bytes currently available to read
				*ptrBytesToRead = state.cbInQue;

				//return communication errors flags
				return static_cast<ErrorFlag>(flags);
			}
		}
		else
		{
			//get and clear the communication error
			if (FALSE != ClearCommError(m_hSerialPort, &flags, NULL))
			{
				//return communication errors flags
				return static_cast<ErrorFlag>(flags);
			}
		}
	}
	//return unknown error
	return ErrorFlags::ERR_UNKNOWN;
}
#endif

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void CSerial::ResetSerial()
{
  //default serial port data: 9600, 8, N, 1
  m_flgBaudRate = BaudRates::BR_9600;
  m_flgDataBits = DataSizes::DB_8;
  m_flgParity = ParityFlags::PF_NONE;
  m_flgStopBits = StopSizes::SB_ONE;

#if defined(WINDOWS)
  //setup default timeouts
  m_numByteReadTimeout = SERIAL_DEFAULT_BYTE_READ_TIMEOUT;
  m_numTailReadTimeout = SERIAL_DEFAULT_TAIL_READ_TIMEOUT;
  m_numByteSendTimeout = SERIAL_DEFAULT_BYTE_SEND_TIMEOUT;
  m_numTailSendTimeout = SERIAL_DEFAULT_TAIL_SEND_TIMEOUT;
  m_numIdleReadTimeout = SERIAL_DEFAULT_IDLE_READ_TIMEOUT;
#elif defined(LINUX)
//linux does not support this functionality
#else
#error "Undefined platform information!"
#endif

  //reset port data
  m_strPortInfo.clear();
  m_hSerialPort = INVALID_SERIAL;

#if defined(WINDOWS)
  //reset timeouts info
  memset(&m_bufTimeouts, 0, sizeof(COMMTIMEOUTS));
#elif defined(LINUX)
//linux does not support this functionality
#else
#error "Undefined platform information!"
#endif
}

//---------------------------------------------------------------------------
