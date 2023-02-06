//	Account.cpp
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//

#include "Account.h"
#include "Tokenizer.hpp"

//---------------------------------------------------------------------------

//disable some well-understood warnings
#if defined(MS_VS_COMPILER)
#pragma warning(push)
#pragma warning(disable: 4355)
#elif defined(GCC_COMPILER)
#else
#error "Undefined compiler information!"
#endif	//MS_VS_COMPILER

//---------------------------------------------------------------------------

	CAccountKey::CAccountKey(VOID) :		
		Identifier(this, &CAccountKey::get_Identifier, &CAccountKey::set_Identifier)
	{
		DEBUG_PRINTF("[CAccountKey::CAccountKey] %p\n", this);
	}

//---------------------------------------------------------------------------

	CAccountKey::CAccountKey(string const& strIdentifier) :
		Identifier(this, &CAccountKey::get_Identifier, &CAccountKey::set_Identifier)
	{
		DEBUG_PRINTF("[CAccountKey::CAccountKey::2] %p\n", this);
		set_Identifier(strIdentifier);
	}

//---------------------------------------------------------------------------

	CAccountKey::CAccountKey(CAccountKey const& refAccountKey) :
		Identifier(this, &CAccountKey::get_Identifier, &CAccountKey::set_Identifier)
	{
		DEBUG_PRINTF("[CAccountKey::CAccountKey::3] %p\n", this);
		operator =(refAccountKey);
	}

//---------------------------------------------------------------------------

	CAccountKey::~CAccountKey(VOID)
	{
		DEBUG_PRINTF("[CAccountKey::~CAccountKey] %p\n", this);
	}

//---------------------------------------------------------------------------

	string CAccountKey::get_Identifier(VOID) const
	{
		CLock lock = const_cast<CCriticalSection&>(m_clsPropLock);
		return m_strIdentifier;
	}

	VOID CAccountKey::set_Identifier(string const& value)
	{
		CLock lock = m_clsPropLock;
		m_strIdentifier = CTokenizer::Trim(value);
	}

//---------------------------------------------------------------------------

	CAccountKey& CAccountKey::operator =(CAccountKey const& refAccountKey)
	{
		set_Identifier(refAccountKey.get_Identifier());
		return *this;
	}

//---------------------------------------------------------------------------

	BOOL CAccountKey::operator ==(CAccountKey const& refAccountKey) const
	{
		string identifier = get_Identifier();
		return (identifier == refAccountKey.get_Identifier())? TRUE : FALSE;
	}

	BOOL CAccountKey::operator !=(CAccountKey const& refAccountKey) const
	{
		string identifier = get_Identifier();
		return (identifier != refAccountKey.get_Identifier())? TRUE : FALSE;
	}

	BOOL CAccountKey::operator >(CAccountKey const& refAccountKey) const
	{
		//compare 'identifier'
		string src = get_Identifier();
		string ref = refAccountKey.get_Identifier();
		if (src > ref)
		{
			return TRUE;
		}
		else if (src < ref)
		{
			return FALSE;
		}
		return FALSE;
	}

	BOOL CAccountKey::operator <(CAccountKey const& refAccountKey) const
	{
		//compare 'identifier'
		string src = get_Identifier();
		string ref = refAccountKey.get_Identifier();
		if (src < ref)
		{
			return TRUE;
		}
		else if (src > ref)
		{
			return FALSE;
		}
		return FALSE;
	}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

	CAccount::CAccount(VOID) :
		Identifier(this, &CAccount::get_Identifier, &CAccount::set_Identifier),
		IntegrationID(this, &CAccount::get_IntegrationID, &CAccount::set_IntegrationID),
		AccessCode(this, &CAccount::get_AccessCode, &CAccount::set_AccessCode),
		UdpChannelFunction(this, &CAccount::get_UdpChannelFunction, &CAccount::set_UdpChannelFunction),
		TcpChannelFunction(this, &CAccount::get_TcpChannelFunction, &CAccount::set_TcpChannelFunction),
		KeyChangeTime(this, &CAccount::get_KeyChangeTime, &CAccount::set_KeyChangeTime)
	{
		DEBUG_PRINTF("[CAccount::CAccount] %p\n", this);
	}

//---------------------------------------------------------------------------

	CAccount::CAccount(CAccount const& refAccount) :
		Identifier(this, &CAccount::get_Identifier, &CAccount::set_Identifier),
		IntegrationID(this, &CAccount::get_IntegrationID, &CAccount::set_IntegrationID),
		AccessCode(this, &CAccount::get_AccessCode, &CAccount::set_AccessCode),
		UdpChannelFunction(this, &CAccount::get_UdpChannelFunction, &CAccount::set_UdpChannelFunction),
		TcpChannelFunction(this, &CAccount::get_TcpChannelFunction, &CAccount::set_TcpChannelFunction),
		KeyChangeTime(this, &CAccount::get_KeyChangeTime, &CAccount::set_KeyChangeTime)
	{
		DEBUG_PRINTF("[CAccount::CAccount::2] %p\n", this);
		operator =(refAccount);
	}

//---------------------------------------------------------------------------

	CAccount::~CAccount(VOID)
	{
		DEBUG_PRINTF("[CAccount::~CAccount] %p\n", this);
	}

//---------------------------------------------------------------------------

	string CAccount::get_Identifier(VOID) const
	{
		CLock lock = const_cast<CCriticalSection&>(m_clsPropLock);
		return m_strIdentifier;
	}

	VOID CAccount::set_Identifier(string const& value)
	{
		CLock lock = m_clsPropLock;
		m_strIdentifier = CTokenizer::Trim(value);
	}

//---------------------------------------------------------------------------

	string CAccount::get_IntegrationID(VOID) const
	{
		CLock lock = const_cast<CCriticalSection&>(m_clsPropLock);
		return m_strIntegrationID;
	}

	VOID CAccount::set_IntegrationID(string const& value)
	{
		CLock lock = m_clsPropLock;
		m_strIntegrationID = value;
	}

//---------------------------------------------------------------------------

	string CAccount::get_AccessCode(VOID) const
	{
		CLock lock = const_cast<CCriticalSection&>(m_clsPropLock);
		return m_strAccessCode;
	}

	VOID CAccount::set_AccessCode(string const& value)
	{
		CLock lock = m_clsPropLock;
		m_strAccessCode = value;
	}

//---------------------------------------------------------------------------

	string CAccount::get_UdpChannelFunction(VOID) const
	{
		CLock lock = const_cast<CCriticalSection&>(m_clsPropLock);
		return m_strUdpChannelFunction;
	}

	VOID CAccount::set_UdpChannelFunction(string const& value)
	{
		CLock lock = m_clsPropLock;
		m_strUdpChannelFunction = value;
	}

//---------------------------------------------------------------------------

	string CAccount::get_TcpChannelFunction(VOID) const
	{
		CLock lock = const_cast<CCriticalSection&>(m_clsPropLock);
		return m_strTcpChannelFunction;
	}

	VOID CAccount::set_TcpChannelFunction(string const& value)
	{
		CLock lock = m_clsPropLock;
		m_strTcpChannelFunction = value;
	}

//---------------------------------------------------------------------------

	UINT32 CAccount::get_KeyChangeTime(VOID) const
	{
		CLock lock = const_cast<CCriticalSection&>(m_clsPropLock);
		return m_numKeyChangeTime;
	}

	VOID CAccount::set_KeyChangeTime(UINT32 const& value)
	{
		CLock lock = m_clsPropLock;
		m_numKeyChangeTime = value;
	}

//---------------------------------------------------------------------------

	CAccount& CAccount::operator =(CAccount const& refAccount)
	{
		set_Identifier(refAccount.get_Identifier());
		set_IntegrationID(refAccount.get_IntegrationID());
		set_AccessCode(refAccount.get_AccessCode());
		set_UdpChannelFunction(refAccount.get_UdpChannelFunction());
		set_TcpChannelFunction(refAccount.get_TcpChannelFunction());
		set_KeyChangeTime(refAccount.get_KeyChangeTime());
		return *this;
	}

//---------------------------------------------------------------------------

#if defined(MS_VS_COMPILER)
#pragma warning(pop)
#elif defined(GCC_COMPILER)
#else
#error "Undefined compiler information!"
#endif	//MS_VS_COMPILER

//---------------------------------------------------------------------------
