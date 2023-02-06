//---------------------------------------------------------------------------
//
//	SocketEventArgs.hpp
//
//	The generic socket event argument class type.
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"
#include "AddressInfo.h"
#include "TMemPtr.hpp"

#ifndef _SOCKET_EVENTARGS_HPP_
#define _SOCKET_EVENTARGS_HPP_

//---------------------------------------------------------------------------

struct CSocketEventArgs
{
	CAddressInfo	m_clsLocalAddress;
	CAddressInfo	m_clsRemoteAddress;
	TMemPtr<BYTE>	m_bufDataBuffer;
};

//---------------------------------------------------------------------------

#endif	//_SOCKET_EVENTARGS_HPP_
