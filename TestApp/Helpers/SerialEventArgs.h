//---------------------------------------------------------------------------
//
//	SerialEventArgs.hpp
//
//	The generic serial event argument class type.
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"
#include "TMemPtr.hpp"

using namespace SDK_MAJOR_NAMESPACE::SDK_MINOR_NAMESPACE;

#ifndef _SERIAL_EVENTARGS_HPP_
#define _SERIAL_EVENTARGS_HPP_

//---------------------------------------------------------------------------

struct CSerialEventArgs
{
	string			m_strPortInfo;
	TMemPtr<BYTE>	m_bufDataBuffer;
};

//---------------------------------------------------------------------------

#endif	//_SERIAL_EVENTARGS_HPP_
