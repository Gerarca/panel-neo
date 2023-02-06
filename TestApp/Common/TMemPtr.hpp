//---------------------------------------------------------------------------
//
//	TMemPtr.hpp
//
//	Smart pointer implementation. Smart pointers are used to automatically 
//	manage dynamic memory allocations.
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"
#include "Debug.hpp"
#include "Exception.hpp"

#ifndef _TMEMPTR_HPP_
#define _TMEMPTR_HPP_

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

//This class is intended to be used as a base class for implementing value
//and/or object smart pointer classes.
template <class T>
class TMemPtr
{
//private members
private:
	T*		m_ptrT;		//the pointer to allocated memory block
	size_t	m_numN;		//the number of objects within the memory block
						//(notice that it isn't a size the memory block)
//protected methods
protected:

	//**************************************************************//
	//	This virtual function can be overwritten in a derived class	//
	//	to allow memory allocation.									//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	ptrT		-	pointer to currently allocated memory block	//
	//																//
	//	numN		-	reference to variable containing the number	//
	//					of objects within the currently allocated	//
	//					memory block								//
	//																//
	//	numNew		-	requested new number of objects (may		//
	//					require re-allocation of the memory block)	//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The function returns pointer to a new (re-allocated) memory	//
	//	block, and updates the numN to the number of objects within	//
	//	the memory block.											//
	//																//
	//**************************************************************//
	virtual T* Alloc(T* ptrT, size_t numN, size_t numNew)
	{
		//allocate memory
		if (0 < numNew)
		{
			try
			{
				//try allocating new memory
				T* ptrNew = new T[numNew];
				if (NULL != ptrNew)	//some non-standard C++ compilers may return NULL
				{
					//copy existing data to the new array
					size_t count = MIN_VALUE(numN, numNew);
					for (size_t i = 0; i < count; ++i)
					{
						//copy object data using the operator =(T&)
						ptrNew[i] = ptrT[i];
					}

					//delete the entire array
					Free(ptrT, numN);

					//set the result
					ptrT = ptrNew;
				}
				else
				{
					//set the result
					ptrT = NULL;
				}
			}
			catch (...)
			{
				DEBUG_ASSERT(FALSE);	//break into debugger
				RELEASE_CHECK(FALSE);	//log during runtime
				//throw CException(ExceptionCodes::Memory_Alloc_Failed, 
				//	"[TMemPtr<T>::Free] Memory Alloc() failed!");

				//set the result
				ptrT = NULL;
			}
		}
		else
		{
			//free the memory
			Free(ptrT, numN);

			//set the result
			ptrT = NULL;
		}

		//return pointer to (re)allocated memory
		return ptrT;
	}

	//**************************************************************//
	//	This virtual function can be overwritten in a derived class	//
	//	to allow memory freeing.									//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	ptrT		-	reference to pointer to currently allocated //
	//					memory block								//
	//																//
	//	numN		-	reference to variable containing the number	//
	//					of objects within the currently allocated	//
	//					memory block								//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The function frees the currently allocated memory and may	//
	//	perform additional tasks to ensure proper management of		//
	//	the resources. After that, the function sets the ptrT		//
	//	to NULL as well as sets the numN value to 0.				//
	//																//
	//**************************************************************//
	virtual VOID Free(T* ptrT, size_t numN)
	{
		//check if memory block is present
		if (NULL != ptrT)
		{
			//free the memory block
			try 
			{
				delete[] ptrT;
			}
			catch (...)
			{
				DEBUG_ASSERT(FALSE);	//break into debugger
				RELEASE_CHECK(FALSE);	//log during runtime
				//throw CException(ExceptionCodes::Memory_Free_Failed, 
				//	"[TMemPtr<T>::Free] Memory Free() failed!");
			}
			numN = 0;	//just to get rid of compiler warning
		}
	}

//constructor and destructor
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
	TMemPtr(VOID) : m_ptrT(NULL), m_numN(0)
	{
		//Warning: do not perform any actions inside the constructor
		//that would require calling virtual functions because object
		//has not been yet created so the virtual functions have not
		//been overwritten and this may yield unpredictable results.
	}

	//**************************************************************//
	//	This constructor initializes internal variables and copies	//
	//	the content of another memory block.						//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	refTMemPtr	-	the reference to another TMemPtr object		//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The function initializes the object to its default state.	//
	//																//
	//**************************************************************//
	TMemPtr(TMemPtr<T> const& refTMemPtr) : m_ptrT(NULL), m_numN(0)
	{
		//Warning: do not use this constructor in derived classes! 
		//If this constructor is called in a derived class, its code
		//will execute _before_ the constructor of the derived class
		//has a chance to execute. As the result, if the derived class 
		//overwrites the virtual functions of this class, very bad 
		//things may happen!
		operator =(refTMemPtr); 
	}

	//**************************************************************//
	//	This constructor initializes internal variables and takes	//
	//	over another memory block.									//
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
	TMemPtr(TMemPtr<T>& refTMemPtr) : m_ptrT(NULL), m_numN(0)
	{ 
		//Warning: do not use this constructor in derived classes! 
		//If this constructor is called in a derived class, its code
		//will execute _before_ the constructor of the derived class
		//has a chance to execute. As the result, if the derived class 
		//overwrites the virtual functions of this class, very bad 
		//things may happen!
		operator =(refTMemPtr); 
	}

	//**************************************************************//
	//	This constructor initializes internal variables and copies	//
	//	the content of another memory block.						//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	refTMemPtr	-	the reference to another TMemPtr object		//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The function initializes the object to its default state.	//
	//																//
	//**************************************************************//
	TMemPtr(T const* ptrT, size_t numN) : m_ptrT(NULL), m_numN(0)
	{ 
		//Warning: do not use this constructor in derived classes! 
		//If this constructor is called in a derived class, its code
		//will execute _before_ the constructor of the derived class
		//has a chance to execute. As the result, if the derived class 
		//overwrites the virtual functions of this class, very bad 
		//things may happen!
		Copy(ptrT, numN); 
	}

	//**************************************************************//
	//	This virtual destructor is responsible for ensuring that	//
	//	the managed memory block is always released when no longer	//
	//	needed.														//
	//	The destructor of any derived class _must_ call "Delete()"	//
	//	to ensure the correct release of the allocated memory.		//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The function releases the currently allocated memory being	//
	//	managed by this object. And then destroys this object.		//
	//																//
	//**************************************************************//
	virtual ~TMemPtr(VOID)
	{
		//Destructors in derived class(es) _MUST_ call the 
		//function 'Delete()' function to perform the proper 
		//cleanup and free the memory.
		Delete();
	}

//public methods
public:

	//**************************************************************//
	//	This function checks if this object is currently free to	//
	//	to start managing a memory block.							//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The function returns TRUE if this object currently does not	//
	//	have the ownership of any allocated memory blocks, or FALSE	//
	//	otherwise.													//
	//																//
	//**************************************************************//
	BOOL IsNull(VOID) const
	{ 
		return (NULL == m_ptrT)? TRUE : FALSE;
	}

	//**************************************************************//
	//	This function returns the number of objects stored in the	//
	//	managed memory block.										//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The function returns the number of objects stored in memory	//
	//	block.														//
	//																//
	//**************************************************************//
	size_t Count(VOID) const
	{
		return (NULL != m_ptrT)? m_numN : 0;
	}

	//**************************************************************//
	//	This function allows allocating memory and initilizing		//
	//	objects within it.											//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	numNew		-	requested number of objects in memory (may	//
	//					require re-allocation of the memory block)	//
	//					(the default value is 1)					//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The function returns a pointer to a new (the same or		//
	//	re-allocated) memory block, and updates the numN to the		//
	//	adjusted count of objects within the memory	block.			//
	//																//
	//**************************************************************//
	BOOL Create(size_t numNew = 1)
	{
		//(re)allocate memory and create new objects if required
		T* ptrT = Alloc(m_ptrT, m_numN, numNew);
		if ((NULL != ptrT) || ((NULL == ptrT) && (0 == numNew)))
		{
			//success
			m_ptrT = ptrT;		//update m_ptrT
			m_numN = numNew;	//update m_numN
			return TRUE;
		} 
		//failure
		return FALSE;
	}

	//**************************************************************//
	//	This function allows freeing currently allocated memory.	//											//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The function frees currently allocated memory and re-inits	//
	//	the m_ptrT and the m_numN to their default values.			//
	//																//
	//**************************************************************//
	VOID Delete(VOID)
	{
		//free the memory and re-init member variables
		Free(m_ptrT, m_numN);
		m_ptrT = NULL;	//update m_ptrT
		m_numN = 0;		//update m_numN
	}

	//**************************************************************//
	//	This function is used to adopt and start managing a memory	//
	//	block allocated externally (independently).					//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	ptrT		-	pointer to an allocated memory block		//
	//																//
	//	numN		-	number of objects within the allocated		//
	//					memory block								//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The function attaches memory block to this object so the	//
	//	the memory can be automatically managed from now on.		//
	//																//
	//**************************************************************//
	VOID Attach(T* ptrT, size_t numN)
	{
		Delete();
		m_ptrT = ptrT;
		m_numN = (NULL != ptrT)? numN : 0;
	}

	//**************************************************************//
	//	This function is used to give up the ownership of managed	//
	//	memory block without freeing the memory.					//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	ptrN	-	pointer to a variable that will receive the		//
	//				number of objects stored withing the memory		//
	//				block being detached							//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The function detaches memory block from this object so the	//
	//	the memory is no longer managed automatically (however the	//
	//	memory block is not freed). The functions returns the		//
	//	pointer to the detached memory block.						//
	//																//
	//**************************************************************//
	T* Detach(size_t* ptrN = NULL)
	{
		T* ptrT = m_ptrT;
		if (NULL != ptrN)
		{
			*ptrN = m_numN;
		}
		m_ptrT = NULL;	//clear the memory pointer
		m_numN = 0;		//clear the block size
		return ptrT;
	}

	//**************************************************************//
	//	This function is used to copy multiple objects from the		//
	//	source memory block. It allocates all necessary memory.		//
	//	Notice: this function relies on the proper assignment		//
	//	operator "operator =(T const&)" to be implemented in the	//
	//	class type <T> or otherwise it may not work correctly		//
	//	(value data types don't need to implement this operator).	//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	refTMemPtr	-	the reference to the object managing source		//
	//				memory block									//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The function returns the reference to this object.			//
	//																//
	//**************************************************************//
	TMemPtr<T>& Copy(TMemPtr<T> const& refTMemPtr)
	{
		return Copy(static_cast<T const*>(refTMemPtr), refTMemPtr.Count());
	}

	//**************************************************************//
	//	This function is used to copy the contents of the source	//
	//	memory block. It allocates all necessary memory.			//
	//	Notice: this function relies on the proper assignment		//
	//	operator "operator =(T const*)" to be implemented in the	//
	//	class type <T> or otherwise it may not work correctly		//
	//	(value data types don't need to implement this operator).	//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	ptrT	-	pointer to the source memory block				//
	//																//
	//	numN	-	number of objects within the allocated			//
	//				memory block									//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The function returns the reference to this object.			//
	//																//
	//**************************************************************//
	TMemPtr<T>& Copy(T const* ptrT, size_t numN)
	{
		//free currently managed memory block
		Delete();

		//update the number of elements if necessary
		if ((NULL != ptrT) && (0 < numN))
		{
			//allocate new memory block
			if (FALSE == Create(numN))
			{
				//failed to allocate memory
				DEBUG_ASSERT(FALSE);	//break into debugger
				RELEASE_CHECK(FALSE);	//log during runtime
				throw CException(ExceptionCodes::Memory_Alloc_Failed,
					"[TMemPtr<T>::Copy(T const* ptrT, size_t numN)] Failed to allocate memory!");
			}

			//copy objects from the source
			for (size_t i = 0; i < m_numN; ++i)
			{
				//use the copy operator '=' to copy objects
				//(copy operator '=' must be supported by the
				//class type of objects being copied)
				m_ptrT[i] = ptrT[i];
			}
		}

		//return the reference to this object
		return *this;
	}

//operators
public:

	//**************************************************************//
	//	This function is used to make a copy of the managed	source	//
	//	memory block.												//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	refTMemPtr		-	reference to a TMemPtr object managing memory	//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The function returns the reference to this object.			//
	//																//
	//**************************************************************//
	TMemPtr<T>& operator =(TMemPtr<T> const& refTMemPtr)
	{
		//copy memory block
		return Copy(refTMemPtr);
	}

	//**************************************************************//
	//	This function is used to take over the ownership of managed	//
	//	source memory block (the source TMemPtr gives up the ownership	//
	//	of the memory block being taken over).						//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	refTMemPtr		-	reference to a TMemPtr object managing memory	//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The function returns the reference to this object.			//
	//																//
	//**************************************************************//
	TMemPtr<T>& operator =(TMemPtr<T>& refTMemPtr)
	{
		//take over the management of a memory block
		size_t numN = 0;
		T* ptrT = refTMemPtr.Detach(&numN);
		Attach(ptrT, numN);
		return *this;
	}

	//**************************************************************//
	//	This operator is used to get the reference to the memory	//
	//	block being managed by this	object.							//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The operator returns the reference to memory block being	//
	//	managed by this object.										//
	//																//
	//**************************************************************//
	T const& operator *(VOID) const
	{ return const_cast<T const&>(*m_ptrT); }

	//**************************************************************//
	//	This operator is used to get the reference to the memory	//
	//	block being managed by this	object.							//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The operator returns the reference to memory block being	//
	//	managed by this object.										//
	//																//
	//**************************************************************//
	T& operator *(VOID)
	{ return *m_ptrT; }

	//**************************************************************//
	//	This operator is used to obtain the pointer to memory being	//
	//	managed by this	object.										//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The operator returns the pointer to the memory block being	//
	//	managed by this object.										//
	//																//
	//**************************************************************//
	T const* operator ->(VOID) const
	{ return const_cast<T const*>(m_ptrT); }

	//**************************************************************//
	//	This operator is used to obtain the pointer to memory being	//
	//	managed by this	object.										//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The operator returns the pointer to the memory block being	//
	//	managed by this object.										//
	//																//
	//**************************************************************//
	T* operator ->(VOID)
	{ return m_ptrT; }

	//**************************************************************//
	//	This operator is used to obtain the pointer to memory being	//
	//	managed by this	object.										//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The operator returns the pointer to the memory block being	//
	//	managed by this object.										//
	//																//
	//**************************************************************//
	operator T const*(VOID) const
	{ return static_cast<T const*>(m_ptrT); }

	//**************************************************************//
	//	This operator is used to obtain the pointer to memory being	//
	//	managed by this	object.										//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The operator returns the pointer to the memory block being	//
	//	managed by this object.										//
	//																//
	//**************************************************************//
	operator T*(VOID)
	{ return m_ptrT; }

	//**************************************************************//
	//	This operator is used to obtain the pointer to memory being	//
	//	managed by this	object.										//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The operator returns the pointer to the memory block being	//
	//	managed by this object.										//
	//																//
	//**************************************************************//
	operator VOID const*(VOID) const
	{ return static_cast<VOID const*>(m_ptrT); }

	//**************************************************************//
	//	This operator is used to obtain the pointer to memory being	//
	//	managed by this	object.										//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The operator returns the pointer to the memory block being	//
	//	managed by this object.										//
	//																//
	//**************************************************************//
	operator VOID*(VOID)
	{ return static_cast<VOID*>(m_ptrT); }

	//**************************************************************//
	//	This operator is used to get the reference to an object		//
	//	within the memory block being managed by this TMemPtr object.	//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	numN		-	0-based index to an object within the		//
	//					memory block being managed by this object	//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The operator returns the reference to the object selected	//
	//	within the memory block being managed by this object.		//
	//																//
	//**************************************************************//
	T const& operator [](size_t index) const
	{ 
		//validate the index
		if (index < m_numN)
		{
			return m_ptrT[index]; 
		}

		//failed to access an item
		DEBUG_ASSERT(FALSE);	//break into debugger
		RELEASE_CHECK(FALSE);	//log during runtime
		throw CException(ExceptionCodes::Index_Out_Of_Range, 
			"[TMemPtr<T>::operator [](size_t index) const] Index out of range!");
	}

	//**************************************************************//
	//	This operator is used to get the reference to an object		//
	//	within the memory block being managed by this TMemPtr object.	//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	numN		-	0-based index to an object within the		//
	//					memory block being managed by this object	//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The operator returns the reference to the object selected	//
	//	within the memory block being managed by this object.		//
	//																//
	//**************************************************************//
	T& operator [](size_t index)
	{ 
		//validate the index
		if (index < m_numN)
		{
			return m_ptrT[index]; 
		}

		//failed to access an item
		DEBUG_ASSERT(FALSE);	//break into debugger
		RELEASE_CHECK(FALSE);	//log during runtime
		throw CException(ExceptionCodes::Index_Out_Of_Range, 
			"[TMemPtr<T>::operator [](size_t index)] Index out of range!");
	}

	//**************************************************************//
	//	This operator is used to get the reference to an object		//
	//	within the memory block being managed by this TMemPtr object.//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	numN		-	0-based index to an object within the		//
	//					memory block being managed by this object	//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The operator returns the reference to the object selected	//
	//	within the memory block being managed by this object.		//
	//																//
	//**************************************************************//
	T const& operator [](int index) const
	{
		//redirect the call
		return operator [](static_cast<size_t>(index));
	}

	//**************************************************************//
	//	This operator is used to get the reference to an object		//
	//	within the memory block being managed by this TMemPtr object.//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	numN		-	0-based index to an object within the		//
	//					memory block being managed by this object	//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The operator returns the reference to the object selected	//
	//	within the memory block being managed by this object.		//
	//																//
	//**************************************************************//
	T& operator [](int index)
	{
		//redirect the call
		return operator [](static_cast<size_t>(index));
	}

	//**************************************************************//
	//	This operator is used to compare pointers to an allocated	//
	//	memory block and pointer to memory being managed by this	//
	//	TMemPtr object.												//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	refTMemPtr		-	reference to a TMemPtr object managing memory//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The result is TRUE if the source TMemPtr object manages the	//
	//	same memory block as the memory block being managed by		//
	//	this object.												//
	//																//
	//**************************************************************//
	BOOL operator ==(TMemPtr<T> const& refTMemPtr) const
	{ return (m_ptrT == refTMemPtr.m_ptrT)? TRUE : FALSE; }

	//**************************************************************//
	//	This operator is used to compare pointers to an allocated	//
	//	memory block and pointer to memory being managed by this	//
	//	TMemPtr object.												//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	refTMemPtr		-	reference to a TMemPtr object managing memory//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The result is TRUE if the source TMemPtr object doesn't manage	//
	//	the same memory block as the memory block being managed by	//
	//	this object.												//
	//																//
	//**************************************************************//
	BOOL operator !=(TMemPtr<T> const& refTMemPtr) const
	{ return (m_ptrT != refTMemPtr.m_ptrT)? TRUE : FALSE; }

	//**************************************************************//
	//	This operator is used to compare pointers to an allocated	//
	//	memory block and pointer to memory being managed by this	//
	//	TMemPtr object.												//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	ptrT		-	pointer to an allocated memory block		//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The result is TRUE if the pointer to memory block is the	//
	//	same as the pointer to the memory block being managed by	//
	//	this object.												//
	//																//
	//**************************************************************//
	BOOL operator ==(T const* ptrT) const
	{ return (m_ptrT == ptrT)? TRUE : FALSE; }

	//**************************************************************//
	//	This operator is used to compare pointers to an allocated	//
	//	memory block and pointer to memory being managed by this	//
	//	TMemPtr object.												//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	ptrT		-	pointer to an allocated memory block		//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The result is TRUE if the pointer to memory block is not	//
	//	the	same as the pointer to the memory block being managed	//
	//	by this object.												//
	//																//
	//**************************************************************//
	BOOL operator !=(T const* ptrT) const
	{ return (m_ptrT != ptrT)? TRUE : FALSE; }
};

//---------------------------------------------------------------------------

#if defined(MS_VS_COMPILER)
#pragma warning(pop)
#elif defined(GCC_COMPILER)
#else
#error "Undefined compiler information!"
#endif	//MS_VS_COMPILER

//---------------------------------------------------------------------------

typedef TMemPtr<BYTE> BYTE_MEMPTR;

//---------------------------------------------------------------------------

//Note: Never copy one TMemPtr to another TMemPtr of different <T>ype.
//In such a situation operator =(TMemPtr<T>&) will not be used and 
//the same pointer T* will be stored in both TMemPtr classes. When 
//TMemPtr destructors are called, memory space violation error will 
//happen.

//Note: m_numN is not guaranteed to keep correct count of objects
//stored in memory pointed by m_ptrT. This is because TMemPtr can be used
//to store pointers allocated externally (with external 'new' operator).
//Use second parameter of the method Attach() to pass the correct
//size in terms of the count of allocated objects.

//---------------------------------------------------------------------------

#endif	//_TMEMPTR_HPP_
