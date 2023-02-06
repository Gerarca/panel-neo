//---------------------------------------------------------------------------
//
//	TProperty.hpp
//
//	The implementation of property mechanism for use inside class types.
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"
#include "Debug.hpp"

#ifndef _TPROPERTY_HPP_
#define _TPROPERTY_HPP_

//---------------------------------------------------------------------------

//enable access to property values by reference
//#define ENABLE_TPROPERTY_ACCESS_BYREF

//---------------------------------------------------------------------------

//This class is intended to be used within other class types to introduce
//property-like behaviour.
template <class TOwner, class TData>
class TProperty
{
//private members
private:

	//getter and setter functions prototypes
	typedef TData (TOwner::*GETTER)(VOID) const;
	typedef VOID (TOwner::*SETTER)(TData const&);
#if defined(ENABLE_TPROPERTY_ACCESS_BYREF)
	typedef TData& (TOwner::*POINTER)(VOID);
#endif

	//pointer to the property owner
	TOwner*		m_ptrOwner;

	//getter & setter
	GETTER		m_ptrGetter;
	SETTER		m_ptrSetter;
#if defined(ENABLE_TPROPERTY_ACCESS_BYREF)
	POINTER		m_ptrPointer;	//used to obtain data reference
#endif

	//property value may be NULL/empty
	BOOL		m_flgIsNull;

//constructors and destructor
public:

	//**************************************************************//
	//	This constructor initializes this property object.			//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	ptrOwner	-	address of the container object				//
	//																//
	//	ptrGetter	-	address of the getter function within		//
	//					the container object						//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//**************************************************************//
	TProperty(TOwner* ptrOwner, GETTER ptrGetter) : 
		m_ptrOwner(ptrOwner),
#if defined(ENABLE_TPROPERTY_ACCESS_BYREF)
		m_ptrGetter(ptrGetter), m_ptrSetter(NULL), 
		m_ptrPointer(NULL),
#else
		m_ptrGetter(ptrGetter), m_ptrSetter(NULL),
#endif
		m_flgIsNull(FALSE)
	{
	}

	//**************************************************************//
	//	This constructor initializes this property object.			//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	ptrOwner	-	address of the container object				//
	//																//
	//	ptrSetter	-	address of the setter function within		//
	//					the container object						//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//**************************************************************//
	TProperty(TOwner* ptrOwner, SETTER ptrSetter) : 
		m_ptrOwner(ptrOwner),
#if defined(ENABLE_TPROPERTY_ACCESS_BYREF)
		m_ptrGetter(NULL), m_ptrSetter(ptrSetter), 
		m_ptrPointer(NULL),
#else
		m_ptrGetter(NULL), m_ptrSetter(ptrSetter),
#endif
		m_flgIsNull(FALSE)
	{
	}

	//**************************************************************//
	//	This constructor initializes this property object.			//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	ptrOwner	-	address of the container object				//
	//																//
	//	ptrPointer	-	address of the pointer function within		//
	//					the container object						//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//**************************************************************//
#if defined(ENABLE_TPROPERTY_ACCESS_BYREF)
	TProperty(TOwner* ptrOwner, POINTER ptrPointer) : 
		m_ptrOwner(ptrOwner),
		m_ptrGetter(NULL), m_ptrSetter(NULL), 
		m_ptrPointer(ptrPointer),
		m_flgIsNull(FALSE)
	{
	}
#endif

	//**************************************************************//
	//	This constructor initializes this property object.			//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	ptrOwner	-	address of the container object				//
	//																//
	//	ptrGetter	-	address of the getter function within		//
	//					the container object						//
	//	ptrSetter	-	address of the setter function within		//
	//					the container object						//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//**************************************************************//
	TProperty(TOwner* ptrOwner, GETTER ptrGetter, SETTER ptrSetter) : 
		m_ptrOwner(ptrOwner),
#if defined(ENABLE_TPROPERTY_ACCESS_BYREF)
		m_ptrGetter(ptrGetter), m_ptrSetter(ptrSetter), 
		m_ptrPointer(NULL),
#else
		m_ptrGetter(ptrGetter), m_ptrSetter(ptrSetter),
#endif
		m_flgIsNull(FALSE)
	{
	}

	//**************************************************************//
	//	This constructor initializes this property object.			//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	ptrOwner	-	address of the container object				//
	//																//
	//	ptrGetter	-	address of the getter function within		//
	//					the container object						//
	//	ptrSetter	-	address of the setter function within		//
	//					the container object						//
	//	ptrPointer	-	address of the pointer function within		//
	//					the container object						//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//**************************************************************//
#if defined(ENABLE_TPROPERTY_ACCESS_BYREF)
	TProperty(TOwner* ptrOwner, GETTER ptrGetter, SETTER ptrSetter, POINTER ptrPointer) : 
		m_ptrOwner(ptrOwner),
		m_ptrGetter(ptrGetter), m_ptrSetter(ptrSetter), 
		m_ptrPointer(ptrPointer),
		m_flgIsNull(FALSE)
	{
	}
#endif

	//**************************************************************//
	//	This constructor initializes this property object.			//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	ptrOwner	-	address of the container object				//
	//																//
	//	ptrGetter	-	address of the getter function within		//
	//					the container object						//
	//	ptrPointer	-	address of the pointer function within		//
	//					the container object						//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//**************************************************************//
#if defined(ENABLE_TPROPERTY_ACCESS_BYREF)
	TProperty(TOwner* ptrOwner, GETTER ptrGetter, POINTER ptrPointer) : 
		m_ptrOwner(ptrOwner),
		m_ptrGetter(ptrGetter), m_ptrSetter(NULL), 
		m_ptrPointer(ptrPointer),
		m_flgIsNull(FALSE)
	{
	}
#endif

	//**************************************************************//
	//	This constructor initializes this property object.			//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	ptrOwner	-	address of the container object				//
	//																//
	//	ptrSetter	-	address of the setter function within		//
	//					the container object						//
	//	ptrPointer	-	address of the pointer function within		//
	//					the container object						//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//**************************************************************//
#if defined(ENABLE_TPROPERTY_ACCESS_BYREF)
	TProperty(TOwner* ptrOwner, SETTER ptrSetter, POINTER ptrPointer) : 
		m_ptrOwner(ptrOwner),
		m_ptrGetter(NULL), m_ptrSetter(ptrSetter), 
		m_ptrPointer(ptrPointer),
		m_flgIsNull(FALSE)
	{
	}
#endif

	//**************************************************************//
	//	This destructor destroys this property object.				//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//**************************************************************//
	virtual ~TProperty(VOID)
	{
	}

//public methods
public:

	//**************************************************************//
	//	This function is used to determine whether the property		//
	//	value is NULL/empty.										//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The function returns TRUE if the property value is NULL.	//
	//																//
	//**************************************************************//
	BOOL IsNull(VOID) const
	{ return m_flgIsNull; }

	//**************************************************************//
	//	This function is used to mark the property value as NULL.	//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//**************************************************************//
	VOID SetNull(BOOL flgIsNull)
	{ m_flgIsNull = flgIsNull; }

//operators
public:

	//**************************************************************//
	//	This operator is used to get data value using the getter	//
	//	function declared in the container class type.				//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The operator returns data value obtained by calling the		//
	//	getter function.											//
	//	If the function is not available, an exception is thrown.	//
	//																//
	//**************************************************************//
	operator TData(VOID) const
	{
		//validate the container
		DEBUG_ASSERT(NULL != m_ptrOwner);
		if (NULL != m_ptrOwner)
		{
			//check if the value is NULL
			if (FALSE != m_flgIsNull)
			{
				//warn about the problem
				DEBUG_ASSERT(FALSE);
				RELEASE_CHECK(FALSE);
				throw CException(ExceptionCodes::Null_Value_Reference,
					"[TProperty<T>::operator TData(VOID) const] Inaccessible NULL property!");
			}

			//validate the getter
			DEBUG_ASSERT(NULL != m_ptrGetter);
			if (NULL != m_ptrGetter)
			{
				//get the data value
				return (m_ptrOwner->*m_ptrGetter)();
			}
		}

		//this is generally a bad thing
		DEBUG_ASSERT(FALSE);	//break into debugger
		RELEASE_CHECK(FALSE);	//log during runtime
		throw CException(ExceptionCodes::Missing_Getter_Accessor,
			"[TProperty<T>::operator TData(VOID) const] No 'getter' function is available!");
	}

	//**************************************************************//
	//	This operator is used to set data value using the setter	//
	//	function declared in the container class type.				//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	valData		-	data value to be set using the setter		//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The operator returns a reference to this object.			//
	//																//
	//**************************************************************//
	TProperty<TOwner, TData>& operator =(TData const& value)
	{
		//validate the container
		DEBUG_ASSERT(NULL != m_ptrOwner);
		if (NULL != m_ptrOwner)
		{
			//check if the value is NULL
			if (FALSE != m_flgIsNull)
			{
				//warn about the problem
				DEBUG_ASSERT(FALSE);
				RELEASE_CHECK(FALSE);
				throw CException(ExceptionCodes::Null_Value_Reference,
					"[TProperty<T>::operator =(TData const& value))] Inaccessible NULL property!");
			}

			//validate the setter
			DEBUG_ASSERT(NULL != m_ptrSetter);
			if (NULL != m_ptrSetter)
			{
				//set the data value
				(m_ptrOwner->*m_ptrSetter)(value);
				return *this;
			}
		}

		//this is generally a bad thing
		DEBUG_ASSERT(FALSE);	//break into debugger
		RELEASE_CHECK(FALSE);	//log during runtime
		throw CException(ExceptionCodes::Missing_Setter_Accessor,
			"[TProperty<T>::operator =(TData const& value)] No 'setter' function is available!");
	}

	//**************************************************************//
	//	This operator is used to get the data reference using the	//
	//	accessor function declared in the container class type.		//
	//	(Use this operator with extreme caution!)					//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The operator returns the data reference by calling the		//
	//	appropriate accessor function.								//
	//	If the function is not available, an exception is thrown.	//
	//																//
	//**************************************************************//
#if defined(ENABLE_TPROPERTY_ACCESS_BYREF)
	TData const& operator *(VOID) const
	{
		//validate the container
		DEBUG_ASSERT(NULL != m_ptrOwner);
		if (NULL != m_ptrOwner)
		{
			//check if the value is NULL
			if (FALSE != m_flgIsNull)
			{
				//warn about the problem
				DEBUG_ASSERT(FALSE);
				RELEASE_CHECK(FALSE);
				throw CException(ExceptionCodes::Null_Value_Reference,
					"[TProperty<T>::operator *(VOID)] NULL value reference!");
			}

			//validate the getter
			DEBUG_ASSERT(NULL != m_ptrPointer);
			if (NULL != m_ptrPointer)
			{
				//get the data value
				return (m_ptrOwner->*m_ptrPointer)();
			}
		}

		//this is generally a bad thing
		DEBUG_ASSERT(FALSE);	//break into debugger
		RELEASE_CHECK(FALSE);	//log during runtime
		throw CException(ExceptionCodes::Missing_Pointer_Accessor,
			"[TProperty<T>::operator *(VOID) const] No 'pointer' function is available!");
	}
#endif

	//**************************************************************//
	//	This operator is used to get the data reference using the	//
	//	accessor function declared in the container class type.		//
	//	(Use this operator with extreme caution!)					//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The operator returns the data reference by calling the		//
	//	appropriate accessor function.								//
	//	If the function is not available, an exception is thrown.	//
	//																//
	//**************************************************************//
#if defined(ENABLE_TPROPERTY_ACCESS_BYREF)
	TData& operator *(VOID)
	{
		//validate the container
		DEBUG_ASSERT(NULL != m_ptrOwner);
		if (NULL != m_ptrOwner)
		{
			//check if the value is NULL
			if (FALSE != m_flgIsNull)
			{
				//warn about the problem
				DEBUG_ASSERT(FALSE);
				RELEASE_CHECK(FALSE);
				throw CException(ExceptionCodes::Null_Value_Reference,
					"[TProperty<T>::operator *(VOID)] NULL value reference!");
			}

			//validate the getter
			DEBUG_ASSERT(NULL != m_ptrPointer);
			if (NULL != m_ptrPointer)
			{
				//get the data value
				return (m_ptrOwner->*m_ptrPointer)();
			}
		}

		//this is generally a bad thing
		DEBUG_ASSERT(FALSE);	//break into debugger
		RELEASE_CHECK(FALSE);	//log during runtime
		throw CException(ExceptionCodes::Missing_Pointer_Accessor,
			"[TProperty<T>::operator *(VOID)] No 'pointer' function is available!");
	}
#endif
};

//---------------------------------------------------------------------------

#endif	//_TPROPERTY_HPP_
