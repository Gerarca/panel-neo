//---------------------------------------------------------------------------
//
//	TextString.hpp
//
//	The DSC_ITextString implmentations.
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_ITextString.hpp"
#include "Component.hpp"
#include "TComPtr.hpp"
#include "Lock.hpp"

using namespace SDK_MAJOR_NAMESPACE::SDK_MINOR_NAMESPACE;

#ifndef _TEXT_STRING_HPP_
#define _TEXT_STRING_HPP_

//---------------------------------------------------------------------------

class CTextString : public CComponent, public virtual DSC_ITextString
{
//private members
private:
	CCriticalSection	m_clsPropLock;	//protection
	string				m_strTextString;

//constructors and destructor
public:
	CTextString(VOID);
	virtual ~CTextString(VOID);

//public methods
public:

	//DSC_IComponent
	virtual IRESULT ICALL Query(IN char const* pszInterface, OUT VOID** ptrInterface);
	virtual IRESULT ICALL Acquire(OUT ICOUNT* ptrCount);
	virtual IRESULT ICALL Release(OUT ICOUNT* ptrCount);

	//DSC_ITextString
	virtual IRESULT ICALL get_Length(OUT DSC_SIZE_T* ptrLength) const;
	virtual IRESULT ICALL get_String(OUT char const** ptrString) const;
	virtual IRESULT ICALL set_String(IN char const* pszString);

//sttaic methods
public:

	static IRESULT ICALL CreateTextString(
		IN char const* pszText, OUT DSC_ITextString** ptrText);
};

//---------------------------------------------------------------------------

#endif	//_TEXT_STRING_HPP_
