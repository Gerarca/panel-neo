//---------------------------------------------------------------------------
//
//	TKeyValue.hpp
//
//	The generic key-value storage implementation.
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _TKEYVALUE_HPP_
#define _TKEYVALUE_HPP_

//---------------------------------------------------------------------------

//disable some well-understood warnings
#if defined(MS_VS_COMPILER)
#pragma warning(push)
#pragma warning(disable: 4521 4522)
#elif defined(GCC_COMPILER)
#else
#error "Undefined compiler information!"
#endif	//MS_VS_COMPILER

//---------------------------------------------------------------------------

template<class TKey, class TValue>
class TKeyValue
{
//friends
private:
	//befriending TDictionary allows that class to
	//direcly access key and value stored within this
	//class (and not through the properties) for the 
	//increased performance
	template<class, class> friend class TDictionary;

//private members
private:
	TKey	m_objKey;		//the key object
	TValue	m_objValue;		//the value object

//constructors & destructor
public:

	TKeyValue(VOID)
	{
	}

	TKeyValue(TKeyValue<TKey, TValue> const& refTKeyValue)
	{
		operator =(refTKeyValue);
	}

	TKeyValue(TKeyValue<TKey, TValue>& refTKeyValue)
	{
		operator =(refTKeyValue);
	}

	TKeyValue(TKey const& refKey, TValue const& refValue) :
		m_objKey(refKey), m_objValue(refValue)
	{
	}

	TKeyValue(TKey const& refKey, TValue& refValue) :
		m_objKey(refKey), m_objValue(refValue)
	{
	}

	virtual ~TKeyValue(VOID)
	{
	}

//properties
public:

	TKey get_Key(VOID) const
	{
		//the TKey must have copy constructor
		return m_objKey;
	}

	TValue get_Value(VOID) const
	{
		//the TValue must have copy constructor
		return m_objValue;
	}

//operators
public:

	TKeyValue<TKey, TValue>& operator =(TKeyValue<TKey, TValue> const& refTKeyValue)
	{
		m_objKey = refTKeyValue.m_objKey;
		m_objValue = refTKeyValue.m_objValue;
		return *this;
	}

	TKeyValue<TKey, TValue>& operator =(TKeyValue<TKey, TValue>& refTKeyValue)
	{
		m_objKey = refTKeyValue.m_objKey;
		m_objValue = refTKeyValue.m_objValue;
		return *this;
	}

	operator TValue const*(VOID) const
	{ return static_cast<TValue const*>(&m_objValue); }

	operator TValue*(VOID)
	{ return &m_objValue; }

	operator TValue const&(VOID) const
	{ return m_objValue; }

	operator TValue&(VOID)
	{ return m_objValue; }

	BOOL operator ==(TKeyValue<TKey, TValue> const& refTKeyValue) const
	{
		//the Tkey must support 'operator =='
		return (m_objKey == refTKeyValue.m_objKey)? TRUE : FALSE;
	}

	BOOL operator !=(TKeyValue<TKey, TValue> const& refTKeyValue) const
	{
		return (FALSE == operator ==(refTKeyValue))? TRUE : FALSE;
	}

	BOOL operator >(TKeyValue<TKey, TValue> const& refTKeyValue) const
	{
		//the Tkey must support 'operator >'
		return (m_objKey > refTKeyValue.m_objKey)? TRUE : FALSE;
	}

	BOOL operator >=(TKeyValue<TKey, TValue> const& refTKeyValue) const
	{
		//the Tkey must support 'operator >='
		return (m_objKey >= refTKeyValue.m_objKey)? TRUE : FALSE;
	}

	BOOL operator <(TKeyValue<TKey, TValue> const& refTKeyValue) const
	{
		//the Tkey must support 'operator <'
		return (m_objKey < refTKeyValue.m_objKey)? TRUE : FALSE;
	}

	BOOL operator <=(TKeyValue<TKey, TValue> const& refTKeyValue) const
	{
		//the Tkey must support 'operator <='
		return (m_objKey <= refTKeyValue.m_objKey)? TRUE : FALSE;
	}
};

//---------------------------------------------------------------------------

#if defined(MS_VS_COMPILER)
#pragma warning(pop)
#elif defined(GCC_COMPILER)
#else
#error "Undefined compiler information!"
#endif	//MS_VS_COMPILER

//---------------------------------------------------------------------------

#endif	//_TKEYVALUE_HPP_
