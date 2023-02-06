//	TCPClient.h
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//

#pragma once

//---------------------------------------------------------------------------

#include "TCPProxy.h"

//---------------------------------------------------------------------------

#ifndef _TCP_CLIENT_H_
#define _TCP_CLIENT_H_

//---------------------------------------------------------------------------

#define CLIENT_CONNECT_WAIT		10		//[ms]

//---------------------------------------------------------------------------

class CTCPClient : public CTCPProxy
{
//private members
private:

	AddressFamily	m_flgFamily;

//constructor and destructor
public:

	CTCPClient(AddressFamily flgFamily = AddressFamilies::ADDR_IP4);
	virtual ~CTCPClient(VOID);

//properties
public:

//public methods
public:

	BOOL Connect(LPCTSTR pszAddr, int numPort, size_t numTimeout);
};

//---------------------------------------------------------------------------
#endif	//_TCP_CLIENT_H_
