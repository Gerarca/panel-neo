//---------------------------------------------------------------------------
//
//	TArray.hpp
//
//	Immutable array implementation for one-dimensional arrays.
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "TMemPtr.hpp"
#include "TComparer.hpp"

#ifndef _TARRAY_HPP_
#define _TARRAY_HPP_

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

template <class T> 
class TArray : private TMemPtr<T>	//hide the underlying TMemPtr
{
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
	TArray(size_t numCount = 0) : TMemPtr<T>()
	{
		//create the array
		if (FALSE == Create(numCount))
		{
			DEBUG_ASSERT(FALSE);	//break into debugger
			RELEASE_CHECK(FALSE);	//log during runtime
			throw CException(ExceptionCodes::Memory_Alloc_Failed,
				"[TArray<T>::TArray<T>()::1] Failed to allocate memory!");
		}
	}

	//**************************************************************//
	//	This constructor simply initializes internal variables.		//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	refTArray	-	reference to the source array				//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The function initializes the object to its default state.	//
	//	After that, it makes a copy of the source array.			//
	//																//
	//**************************************************************//
	TArray(TArray<T> const& refTArray) : TMemPtr<T>()
	{ 
		//create the array
		if (FALSE == Create(refTArray.Count()))
		{
			DEBUG_ASSERT(FALSE);	//break into debugger
			RELEASE_CHECK(FALSE);	//log during runtime
			throw CException(ExceptionCodes::Memory_Alloc_Failed,
				"[TArray<T>::TArray<T>()::2] Failed to allocate memory!");
		}

		//copy the content of the source array
		operator =(refTArray); 
	}

	//**************************************************************//
	//	This constructor simply initializes internal variables.		//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	refTArray	-	reference to the source array				//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The function initializes the object to its default state.	//
	//	After that, it takes over the source array.					//
	//																//
	//**************************************************************//
	TArray(TArray<T>& refTArray) : TMemPtr<T>()
	{ 
		//take over the management of the source array
		operator =(refTArray); 
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
	virtual ~TArray(VOID)
	{
		//delete the array and free the memory
		TMemPtr<T>::Delete();
	}

//public methods
public:

	//**************************************************************//
	//	This function creates the array.							//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	numCount	-	the required capacity of the array			//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The function returns TRUE if array has been created or		//
	//	FALSE otherwise.											//
	//																//
	//**************************************************************//
	BOOL Create(size_t numCount)
	{
		//delete the existing array
		Delete();

		//allocate memory
		if (FALSE != TMemPtr<T>::Create(numCount))
		{
			//default empty slots
			Clear();
			return TRUE;
		}
		//failed to allocate memory
		return FALSE;
	}

	//**************************************************************//
	//	This function allows deleting the array.					//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The function frees currently allocated memory.				//
	//																//
	//**************************************************************//
	VOID Delete(VOID)
	{
		//delete the existing array
		TMemPtr<T>::Delete();
	}

	//**************************************************************//
	//	This function returns the size of the array.				//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The function returns the maximum capacity of this array.	//
	//																//
	//**************************************************************//
	size_t Count(VOID) const
	{ return TMemPtr<T>::Count(); }

	//**************************************************************//
	//	This function is used to delete the contents of the array.	//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The function returns the reference to this object.			//
	//	The function clears all objects contained within but		//
	//	doesn't free the allocated memory.							//
	//																//
	//**************************************************************//
	TArray<T>& Clear(VOID)
	{
		//perform cleanup but do not free the memory
		size_t count = TMemPtr<T>::Count();
		for (size_t i = 0; i < count; ++i)
		{
			//set entry to the default value
			TMemPtr<T>::operator [](i) = T();
		}

		//return reference to this object
		return *this;
	}

	//**************************************************************//
	//	This function is used to copy items from the source array.	//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	refTArray	-	the reference to the source array			//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The function returns the reference to this object.			//
	//																//
	//**************************************************************//
	TArray<T>& Copy(TArray<T> const& refTArray)
	{
		//get the new number of items to copy
		size_t room = Count();	//the size of this array 
		size_t count = MIN_VALUE(room, refTArray.Count());

		//copy as many entries as possible
		for (size_t i = 0; i < count; ++i)
		{
			//copy entry (requires "operator =(T const&)")
			operator [](i) = refTArray[i];
		}

		//default the the rest of the array's entries
		while (count < room)
		{
			//set entry to the default value
			operator [](count++) = T();
		}

		//return reference to this object
		return *this;
	}

	//**************************************************************//
	//	This function is used to sort the contents of the array.	//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	flgDescending	-	the 'descending' direction of sorting	//
	//																//
	//	ptrComparer	-	the optional comparer that can be used to	//
	//					perform more complex item comparisons that	//
	//					affect the order of sorting					//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The function returns the reference to this object.			//
	//	The result is the list of items sorted according to the		//
	//	input parameters.											//
	//																//
	//**************************************************************//
	TArray<T>& Sort(BOOL flgDescending = FALSE, 
		TComparer<T>* ptrComparer = NULL)
	{
		//sort all items in the list
		SubSort(0, Count(), flgDescending, ptrComparer);

		//return reference to this object
		return *this;
	}

	//**************************************************************//
	//	This function is used to find an index of a single object	//
	//	within this array.											//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	refT	-	the reference to an(other) object containing	//
	//				searching paramaters							//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The function returns value >= 0 if the new object has been	//
	//	found or value < 0 otherwise.								//
	//																//
	//**************************************************************//
	int IndexOf(T const& refTObj) const
	{
		//search the array (the underlying memory block 
		//contains items that can be accessed sequentially)
		T const* items = TMemPtr<T>::operator T const*();
		size_t count = TMemPtr<T>::Count();
		for (size_t i = 0; i < count; ++i)
		{
			//check if the data matches using 
			//the T's "operator ==(T const&)"
			if (refTObj == items[i])
			{
				//return the index
				return static_cast<int>(i);
			}
		}

		//object not found
		return NEGATIVE_VALUE;
	}

//operators
public:

	//**************************************************************//
	//	This operator is used to make copy of the managed source	//
	//	memory block containg the source array.						//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	refTArray	-	reference to the source array				//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The operator returns the reference to this array.			//
	//																//
	//**************************************************************//
	TArray<T>& operator =(TArray<T> const& refTArray)
	{
		//copy items from the source array
		return Copy(refTArray);
	}

	//**************************************************************//
	//	This operator is used to take over the managed memory block	//
	//	containg the source array's elements.						//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	refTArray	-	reference to the source array				//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The operator returns the reference to this array.			//
	//																//
	//**************************************************************//
	TArray<T>& operator =(TArray<T>& refTArray)
	{
		//take over the management of the memory block used by the source array
		TMemPtr<T>::operator =(static_cast<TMemPtr<T>&>(refTArray));
		return *this;
	}

	//**************************************************************//
	//	This operator is used to obtain the pointer to memory block	//
	//	containing the array.										//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The operator returns the pointer to the memory block		//
	//	containing the array.										//
	//																//
	//**************************************************************//
	operator T const*(VOID) const	//direct access to the buffer - careful!
	{ return TMemPtr<T>::operator T const*(); }

	//**************************************************************//
	//	This operator is used to obtain the pointer to memory block	//
	//	containing the array.										//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The operator returns the pointer to the memory block		//
	//	containing the array.										//
	//																//
	//**************************************************************//
	operator T*(VOID)	//direct access to the buffer - careful!
	{ return TMemPtr<T>::operator T*(); }

	//**************************************************************//
	//	This operator is used to obtain the pointer to memory block	//
	//	containing the array.										//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The operator returns the pointer to the memory block		//
	//	containing the array.										//
	//																//
	//**************************************************************//
	operator VOID const*(VOID) const	//direct access to the buffer - careful!
	{ return TMemPtr<T>::operator const VOID*(); }

	//**************************************************************//
	//	This operator is used to obtain the pointer to memory block	//
	//	containing the array.										//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The operator returns the pointer to the memory block		//
	//	containing the array.										//
	//																//
	//**************************************************************//
	operator VOID*(VOID)	//direct access to the buffer - careful!
	{ return TMemPtr<T>::operator VOID*(); }

	//**************************************************************//
	//	This operator is used to get the reference to an object		//
	//	within the array.											//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	index		-	0-based index to an object within the		//
	//					array.										//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The operator returns the reference to the object selected	//
	//	within the array.											//
	//																//
	//**************************************************************//
	T const& operator [](size_t index) const
	{ 
		return TMemPtr<T>::operator [](index); 
	}

	//**************************************************************//
	//	This operator is used to get the reference to an object		//
	//	within the array.											//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	index		-	0-based index to an object within the		//
	//					array.										//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The operator returns the reference to the object selected	//
	//	within the array.											//
	//																//
	//**************************************************************//
	T& operator [](size_t index)
	{ 
		return TMemPtr<T>::operator [](index); 
	}

	//**************************************************************//
	//	This operator is used to get the reference to an object		//
	//	within the array.											//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	index		-	0-based index to an object within the		//
	//					array.										//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The operator returns the reference to the object selected	//
	//	within the array.											//
	//																//
	//**************************************************************//
	T const& operator [](int index) const
	{ 
		return TMemPtr<T>::operator [](index);
	}

	//**************************************************************//
	//	This operator is used to get the reference to an object		//
	//	within the array.											//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	index		-	0-based index to an object within the		//
	//					array.										//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The operator returns the reference to the object selected	//
	//	within the array.											//
	//																//
	//**************************************************************//
	T& operator [](int index)
	{ 
		return TMemPtr<T>::operator [](index);
	}

//private methods
private:

	//sort the partial content of the array 
	VOID SubSort(size_t numIndex, size_t numCount,
		BOOL flgDescending, TComparer<T>* ptrComparer)
	{
		//check if sorting is required
		if (1 < numCount)
		{
			//get the split point
			size_t final = numIndex + numCount - 1;	//last index
			size_t pivot = Split(numIndex, numCount, flgDescending, ptrComparer);

			//check if the partition before the split point needs to be sorted
			if (numIndex < pivot)
			{
				//sort the 'before' partition
				SubSort(numIndex, pivot - numIndex, flgDescending, ptrComparer);
			}

			//check if the partition after the split point needs to be sorted
			if (final > pivot)
			{
				//sort the 'after' partition
				SubSort(pivot + 1, final - pivot, flgDescending, ptrComparer);
			}
		}
	}

	//split data into two chunks for further sorting
	//and return the 'split' index
	size_t Split(size_t numIndex, size_t numCount,
		BOOL flgDescending, TComparer<T>* ptrComparer)
	{
		//select new, arbitrary pivot index somewhere in the middle
		size_t pivot = numIndex + (numCount >> 1);
		size_t final = numIndex + numCount - 1;	//the index of the last item

		//swap the pivot item with the last one
		Swap(pivot, final);

		//sort the items
		pivot = numIndex;	//new pivot candidate
		for (size_t index = numIndex; index < final; ++index)    //skip the last element
		{
			//compare selected item with the last item
			if (IS_EQUAL > Compare(operator[](index), 
				operator[](final), flgDescending, ptrComparer))
			{
				//this item goes before the pivot item
				Swap(index, pivot++);	//increment the pivot index
			}
		}

		//swap the pivot item back - into the right place
		Swap(pivot, final);

		//return the pivot index
		return pivot;
	}

	//compare 2 objects
	int Compare(T const& refA, T const& refB, 
		BOOL flgDescending, TComparer<T>* ptrComparer) const
	{
		//check if the custom comparer is available
		if (NULL != ptrComparer)
		{
			//use the provided comparer
			return (FALSE != flgDescending)?
				-1 * ptrComparer->Compare(refA, refB) : 
				ptrComparer->Compare(refA, refB);
		}

		//by default, use the compare operators of class type T
		//(BOOL operator >(T const& refA, T const& refB) const;)
		if (refA > refB)
		{
			return (FALSE != flgDescending)? IS_LESSER : IS_GREATER;
		}
		else if (refA < refB)
		{
			return (FALSE != flgDescending)? IS_GREATER : IS_LESSER;
		}

		//both objects are equal
		return IS_EQUAL;
	}

	//swap 2 objects in the array
	VOID Swap(size_t numIndexA, size_t numIndexB)
	{
		//is the swap necessary?
		if (numIndexA != numIndexB)
		{
			//swap objects (relies on the 'operator =()' 
			//being implemented in the class type T)
			T objT = operator[](numIndexA);
			operator[](numIndexA) = operator[](numIndexB);
			operator[](numIndexB) = objT;
		}
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

#endif	//_TARRAY_HPP_
