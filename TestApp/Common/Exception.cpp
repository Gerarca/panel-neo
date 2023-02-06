//---------------------------------------------------------------------------
//
//	Exception.cpp
//
//	The exception class type.
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

#include "Exception.hpp"

//---------------------------------------------------------------------------

	CException::CException(ExceptionCode flgCode, string const& strText) :
		m_flgCode(flgCode), m_strText(strText)
	{
	}

//---------------------------------------------------------------------------

	CException::~CException(VOID)
	{
	}

//---------------------------------------------------------------------------

	ExceptionCode CException::Code(VOID) const
	{
		return m_flgCode;
	}

//---------------------------------------------------------------------------

	string CException::Text(VOID) const
	{
		return m_strText;
	}

//---------------------------------------------------------------------------

	CException& CException::operator=(CException const& refException)
	{
		m_flgCode = refException.m_flgCode;
		m_strText = refException.m_strText;
		return *this;
	}

//---------------------------------------------------------------------------
