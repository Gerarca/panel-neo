//---------------------------------------------------------------------------
//
//	Exception.hpp
//
//	The exception class type.
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"
#include <string>

using namespace std;

#ifndef _EXCEPTION_HPP_
#define _EXCEPTION_HPP_

//---------------------------------------------------------------------------

namespace ExceptionCodes {
enum value {
	Unknown		= 0,	//unknown exception

	Memory_Alloc_Failed,
	Memory_Free_Failed,
	Index_Out_Of_Range,
	Unknown_Index_Key,
	Invalid_Data_Size,
	Null_Value_Reference,

	Create_Critical_Section,
	Destroy_Critical_Section,
	Lock_Critical_Section,
	Unlock_Critical_Section,

	Constructor_Failed,
	Destructor_Failed,

	Component_Acquire_Error,
	Component_Release_Error,

	Missing_Getter_Accessor,
	Missing_Setter_Accessor,
	Missing_Pointer_Accessor
}; }
typedef DSC_ENUM_T ExceptionCode;

//---------------------------------------------------------------------------

class CException
{
//private members
private:
	ExceptionCode	m_flgCode;
	string			m_strText;

//constructor & destructor
public:
	CException(ExceptionCode flgCode, string const& strText);
	virtual ~CException(VOID);

//public methods
public:
	ExceptionCode Code(VOID) const;
	string Text(VOID) const;

//operators
public:
	CException& operator=(CException const& refException);
};

//---------------------------------------------------------------------------

#endif	//_EXCEPTION_HPP_
