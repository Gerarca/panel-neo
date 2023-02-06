//---------------------------------------------------------------------------
//
//	TComPtr.hpp
//
//	Smart pointer implementation for component data types. All the components
//	must implement DSC_IComponent interface.
//	Smart pointers are used to automatically manage dynamic memory allocations.
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"
#include "TTypeHelp.hpp"

#ifndef _TCOMPTR_HPP_
#define _TCOMPTR_HPP_

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

//This class is intended for managing the lifespan of software components
//(objects implmenting the DSC_IComponent interface).
template <class T> 
class TComPtr
{
private:
	T*	m_ptrT;

//constructors & destructor
public:

	//**************************************************************//
	//	This constructor simply initializes internal variables.		//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The function initializes the object to its default state.	//
	//																//
	//**************************************************************//
	TComPtr(VOID) : m_ptrT(NULL) 
	{
#if !defined(NDEBUG)
		//constrain the T to be a component
		IsComponent<T>();
#endif
	}

	//**************************************************************//
	//	This constructor simply initializes internal variables.		//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	refTComPtr	-	reference to the source object				//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The function initializes the object to its default state.	//
	//																//
	//**************************************************************//
	TComPtr(TComPtr<T> const& refTComPtr) : m_ptrT(NULL) 
	{
#if !defined(NDEBUG)
		//constrain the T to be a component
		IsComponent<T>();
#endif
		operator =(refTComPtr);
	}

	//**************************************************************//
	//	This constructor simply initializes internal variables.		//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	ptrT		-	pointer to the component to be managed		//
	//	flgAcquire	-	increment ref count if TRUE					//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The function initializes the object to its default state.	//
	//																//
	//**************************************************************//
	TComPtr(T* ptrT, BOOL flgAcquire) : m_ptrT(NULL)
	{
#if !defined(NDEBUG)
		//constrain the T to be a component
		IsComponent<T>();
#endif
		Store(ptrT, flgAcquire);
	}

	//**************************************************************//
	//	This virtual destructor is responsible for releasing the	//
	//	component being managed by this object.						//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The function decrements the ref count of the component		//
	//	being managed by this objecty. Once the ref count drops		//
	//	to 0, the component will self-delete.						//
	//																//
	//**************************************************************//
	virtual ~TComPtr(VOID)
	{ Release(); }

//public methods
public:

	//**************************************************************//
	//	This function checks if this object is currently free to	//
	//	to start managing another component.						//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The function returns TRUE if this object currently does not	//
	//	manage any component, or FALSE otherwise.					//
	//																//
	//**************************************************************//
	BOOL IsNull(VOID) const
	{
		return (NULL == m_ptrT)? TRUE : FALSE;
	}

	//**************************************************************//
	//	This function decrements the ref count of the managed		//
	//	component.													//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The function clears the pointer to the managed component.	//
	//																//
	//**************************************************************//
	VOID Clear(VOID)
	{
		//clear the currently hosted component
		Release();
	}

	//**************************************************************//
	//	This function stores the pointer to the managed component	//
	//	and increments the ref count if required.					//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	ptrT		-	pointer to the component to be managed		//
	//	flgAcquire	-	increment ref count if TRUE					//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The function stores the pointer to managed object.			//
	//																//
	//**************************************************************//
	TComPtr<T>& Store(T* ptrT, BOOL flgAcquire)
	{
		//release the current component
		Release();

		//increment the ref count?
		if (FALSE != flgAcquire)
		{
			//attach the new component and
			//increment its ref counter
			Acquire(ptrT);
		}
		else
		{
			//store the pointer without incrementing 
			//the object's ref count
			m_ptrT = ptrT;
		}

		//return ref to this object
		return *this;
	}

	//**************************************************************//
	//	This function increments the ref count of the managed		//
	//	component and returns the pointer to it.													//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The function returns the pointer to the managed component.	//
	//																//
	//**************************************************************//
	T* Fetch(VOID)
	{
		//return the pointer to the component
		//after incrementing the ref counter
		Acquire(m_ptrT);
		return m_ptrT;
	}

	////**************************************************************//
	////	This function increments the ref count of the managed		//
	////	component and returns the DSC_IComponent.					//
	////**************************************************************//
	////	Arguments:													//
	////**************************************************************//
	////																//
	////**************************************************************//
	////	Result(s):													//
	////**************************************************************//
	////																//
	////	The function returns the pointer to the managed component.	//
	////																//
	////**************************************************************//
	//TComPtr<DSC_IComponent> Component(VOID)
	//{
	//	return Query();
	//}

//operators
public:

	//**************************************************************//
	//	This operator allows assigning a component to manage.		//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	refTComPtr	-	reference to another object managing the	//
	//					same component								//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The operator takes over the management of the life of a		//
	//	component. The original object retains the management.		//
	//																//
	//**************************************************************//
	TComPtr<T>& operator =(TComPtr<T> const& refTComPtr)
	{
		//release the current component
		Release();

		//attach the component from the source object 
		//and increment the ref counter
		Acquire(refTComPtr.m_ptrT);

		//return ref to this object
		return *this;
	}

	//**************************************************************//
	//	This operator allows dereferencing the managed component.	//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The operator returns a reference to the managed component.	//
	//																//
	//**************************************************************//
	T const& operator *(VOID) const
	{ return *m_ptrT; }

	//**************************************************************//
	//	This operator allows dereferencing the managed component.	//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The operator returns a reference to the managed component.	//
	//																//
	//**************************************************************//
	T& operator *(VOID)
	{ return *m_ptrT; }

	//**************************************************************//
	//	This operator allows dereferencing the managed component.	//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The operator returns a pointer to the managed component.	//
	//																//
	//**************************************************************//
	T const* operator ->(VOID) const
	{ return m_ptrT; }

	//**************************************************************//
	//	This operator allows dereferencing the managed component.	//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The operator returns a pointer to the managed component.	//
	//																//
	//**************************************************************//
	T* operator ->(VOID)
	{ return m_ptrT; }

	//**************************************************************//
	//	This operator allows dereferencing the managed component.	//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The operator returns a pointer to the constant managed		//
	//	component. This function is of vary limited use.			//
	//																//
	//**************************************************************//
	operator T const*(VOID) const
	{ 
		//return the pointer to the component
		//without incrementing the ref counter
		return const_cast<T const*>(m_ptrT); 
	}

	//**************************************************************//
	//	This operator allows dereferencing the managed component.	//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The operator returns a pointer to the managed component and	//
	//	splits the management by incrementing the reference count.	//
	//																//
	//**************************************************************//
	operator T*(VOID)
	{
		//return the pointer to the component
		//without incrementing the ref counter
		return m_ptrT;
	}

	//**************************************************************//
	//	This operator allows accessing the internal component		//
	//	pointer directly. Use it with extreme caution!				//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The operator returns a pointer to the pointer to the		//
	//	managed component. The Acquire must be called prior to		//
	//	using this operator to assign new pointer.					//
	//																//
	//**************************************************************//
	operator T**(VOID)
	{
		//release the current component
		Release();

		//return the pointer to the component pointer (it is assumed
		//that the Acquire has already been called on the component)
		return &m_ptrT;
	}

	//**************************************************************//
	//	This operator allows accessing the internal component		//
	//	pointer directly. Use it with extreme caution!				//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The operator returns a pointer to the pointer to the		//
	//	managed component. The Acquire must be called prior to		//
	//	using this operator to assign new pointer.					//
	//																//
	//**************************************************************//
	operator VOID**(VOID)
	{
		//release the current component
		Release();

		//return the pointer to the component pointer (it is assumed
		//that the Acquire has already been called on the component)
		return reinterpret_cast<VOID**>(&m_ptrT);
	}

	//**************************************************************//
	//	This operator allows checking component equivalence.		//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	refTComPtr	-	reference to another object managing the	//
	//					same component								//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The operator returns TRUE if this object and the refTComPtr	//
	//	object point to the same component.							//
	//																//
	//**************************************************************//
	BOOL operator ==(TComPtr<T> const& refTComPtr)
	{
		//return TRUE if both TComPtr ptrs point
		//to the same object
		return (m_ptrT == refTComPtr.m_ptrT)? TRUE : FALSE;
	}

	//**************************************************************//
	//	This operator allows checking component not equivalence.	//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	refTComPtr	-	reference to another object managing the	//
	//					same component								//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The operator returns TRUE if this object and the refTComPtr	//
	//	object point to different components.						//
	//																//
	//**************************************************************//
	BOOL operator !=(TComPtr<T> const& refTComPtr)
	{
		//return TRUE if both TComPtr ptrs point
		//to different objects
		return (m_ptrT != refTComPtr.m_ptrT)? TRUE : FALSE;
	}

	//**************************************************************//
	//	This operator allows checking component not equivalence.	//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	ptrT		-	pointer to a component						//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The operator returns TRUE if this object points to the		//
	//	specified component.										//
	//																//
	//**************************************************************//
	BOOL operator ==(T const* ptrT) const
	{ return (m_ptrT == ptrT)? TRUE : FALSE; }

	//**************************************************************//
	//	This operator allows checking component not equivalence.	//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	ptrT		-	pointer to a component						//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The operator returns TRUE if this object doesn't point to	//
	//	the specified component.									//
	//																//
	//**************************************************************//
	BOOL operator !=(T const* ptrT) const
	{ return (m_ptrT != ptrT)? TRUE : FALSE; }

//private methods
private:

	////**************************************************************//
	////	This function queries the managed component.				//
	////**************************************************************//
	////	Arguments:													//
	////**************************************************************//
	////																//
	////**************************************************************//
	////	Result(s):													//
	////**************************************************************//
	////																//
	////	The function returns the pointer to the underlying			//
	////	DSC_IComponent interface.									//
	////																//
	////**************************************************************//
	//TComPtr<DSC_IComponent> Query(VOID)
	//{
	//	//create wrapper for the component interface
	//	TComPtr<DSC_IComponent> comp;

	//	//the try/catch block is necessary because the component
	//	//could be destroyed before the Query is called here
	//	try
	//	{
	//		//check if the component is present
	//		if (NULL != m_ptrT)
	//		{
	//			//query for the required interface
	//			if (IS_FAILURE(m_ptrT->Query(NAME_DSC_IComponent, comp)))
	//			{
	//				//failed to obtain "DSC_IComponent*" interface
	//				DEBUG_ASSERT(FALSE);	//break into debugger
	//				RELEASE_CHECK(FALSE);	//log during runtime
	//			}
	//		}
	//	}
	//	catch (...) {}

	//	//return the wrapped component interface (it may be NULL)
	//	return comp;
	//}

	//**************************************************************//
	//	This function increments the ref count of the managed		//
	//	component.													//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The function returns the current ref count.					//
	//																//
	//**************************************************************//
	ICOUNT Acquire(T* ptrT)
	{
		//the try/catch block is necessary because the component
		//could be destroyed before the Acquire is called here
		try
		{
			//check if the component is present
			if (NULL != ptrT)
			{
				//increment the ref counter
				ICOUNT count;
				if (IS_SUCCESS(ptrT->Acquire(&count)))
				{
					//check count
					if (0 < count)
					{
						//store the pointer
						m_ptrT = ptrT;
						return count;
					}
				}
			}
		}
		catch (...) {}

		//component is missing
		m_ptrT = NULL;
		return 0;
	}

	//**************************************************************//
	//	This function decrements the ref count of the managed		//
	//	component.													//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The function clears the pointer to the managed component.	//
	//																//
	//**************************************************************//
	ICOUNT Release(VOID)
	{
		//the try/catch block is necessary because the component
		//could be destroyed before the Release is called here
		//(although that would mean that there is an error in some
		//other place of the source code)
		try
		{
			//check if the component is present
			if (NULL != m_ptrT) 
			{
				//decrease the ref counter
				ICOUNT count = 0;
				if (IS_SUCCESS(m_ptrT->Release(&count)))
				{
					//forget the component
					m_ptrT = NULL;
					return count;
				}
			}
		}
		catch (...) {}

		//component is missing
		m_ptrT = NULL;
		return 0;
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

#endif	//_TCOMPTR_HPP_
