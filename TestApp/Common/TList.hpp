//---------------------------------------------------------------------------
//
//	TList.hpp
//
//	Dynamic list implementation. The list can grow or shrink depending on 
//	the amount of data stored in it.
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "TMemPtr.hpp"
#include "TArray.hpp"
#include "TComparer.hpp"

#ifndef _TLIST_HPP_
#define _TLIST_HPP_

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
class TList
{
//private types
private:
	struct TLink
	{
		T		m_objItem;
		TLink*	m_ptrPrev;
		TLink*	m_ptrNext;
	};

//private members
private:
	TLink*			m_ptrHead;
	TLink*			m_ptrTail;
	size_t			m_numCount;	//the number of objects in the list
	TArray<TLink*>	m_lstLinks;	//list indexing helper

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
	TList(VOID) : 
		m_ptrHead(NULL), m_ptrTail(NULL), m_numCount(0)
	{}

	//**************************************************************//
	//	This constructor simply initializes internal variables and	//
	//	copies the contsnt of the source list.						//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	refTList	-	reference to the source TList				//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The function initializes the object to its default state.	//
	//	After that, it makes a copy of the source list.				//
	//																//
	//**************************************************************//
	TList(TList<T> const& refTList) : 
		m_ptrHead(NULL), m_ptrTail(NULL), m_numCount(0)
	{ operator =(refTList); }

	//**************************************************************//
	//	This constructor simply initializes internal variables.		//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	refTList	-	reference to the source TList				//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The function initializes the object to its default state.	//
	//	After that, it takes over managing the content of the		//
	//	source list.												//
	//																//
	//**************************************************************//
	TList(TList<T>& refTList) :
		m_ptrHead(NULL), m_ptrTail(NULL), m_numCount(0)
	{ operator =(refTList); }

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
	virtual ~TList(VOID)
	{ 
		Clear();
	}

//public methods
public:

	//**************************************************************//
	//	This function returns the number of olbjects stored in the	//
	//	list.														//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The function returns the number of objects stored in this	//
	//	list.														//
	//																//
	//**************************************************************//
	size_t Count(VOID) const
	{
		//Often the call to this method is followed by
		//some kind of a loop to iterate through all
		//items. For this reason, it may be beneficial
		//to re-build the indexing information here if 
		//it is invalid (but not force this - that would
		//simply kill the performance). This kludge has
		//been added here to help with the legacy code 
		//that is unaware of the 'IndexOn' function.
		const_cast<TList<T>*>(this)->IndexOn();

		//return the number of items on the list
		return m_numCount; 
	}

	//**************************************************************//
	//	This function is used to delete the contents of the list.	//
	//	The objects within the list are destroyed and the memory	//
	//	is freed.													//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The function returns the reference to this object.			//
	//	The function destroys all objects contained within and		//
	//	frees all allocated memory.									//
	//																//
	//**************************************************************//
	TList<T>& Clear(VOID)
	{
		//start the search at the head
		for (TLink *link = m_ptrHead, 
			*next = NULL; NULL != link; link = next)
		{
			//save the next link pointer
			next = link->m_ptrNext;

			//unlink from the list
			RemoveLink(link);

			//delete the link and the contained T object
			delete link;
		}

		//return reference to this object
		return *this;
	}

	//**************************************************************//
	//	This function is used to copy multiple objects from the		//
	//	source list. It allocates all necessary memory.				//
	//	It is strongly recommended to re-index the source array		//
	//	before copying it to improve the performance.				//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	refTList	-	the reference to the source list			//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The function returns the reference to this object.			//
	//																//
	//**************************************************************//
	TList<T>& Copy(TList<T> const& refTList)
	{
		//clear the current list
		Clear();

		//copy all items from the source list
		size_t count = refTList.Count();
		for (size_t i = 0; i < count; ++i)
		{
			//add a copy of the source item to this list
			if (NULL == Add(refTList[i]))
			{
				//failed to add an item
				DEBUG_ASSERT(FALSE);	//break into debugger
				RELEASE_CHECK(FALSE);	//log during runtime
			}
		}

		//rebuild the index information
		IndexOn(TRUE);

		//return reference to this object
		return *this;
	}

	//**************************************************************//
	//	This function is used to sort the contents of the list.	//
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
	TList<T>& Sort(BOOL flgDescending = FALSE, 
		TComparer<T>* ptrComparer = NULL)
	{
		//rebuild the indexing information
		IndexOn();

		//sort all items in the list
		SubSort(0, Count(), flgDescending, ptrComparer);

		//return reference to this object
		return *this;
	}

	//**************************************************************//
	//	This function is used to perform internal indexing of the	//
	//	list in order to improve performance when accessing list	//
	//	items by their indexes.										//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	flgForced	-	TRUE forces rebuilding of the indexing		//
	//					information from scrach. FALSE keeps the	//
	//					existing indexing information if present	//
	//					or rebuilds it if missing or invalid.		//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The function returns the reference to this object.			//
	//	The function creates internal indexing information.			//
	//																//
	//**************************************************************//
	TList<T>& IndexOn(BOOL flgForced = FALSE)
	{
		//rebuild the indexing information?
		if ((FALSE != flgForced) ||				//forced rebuild?
			(m_numCount != m_lstLinks.Count()))	//invalid indexing?
		{
			//delete old indexing information
			m_lstLinks.Delete();

			//create the indexing array
			if (FALSE != m_lstLinks.Create(m_numCount))
			{
				//iterate through the list
				size_t index = 0;
				for (TLink* link = m_ptrHead; 
					NULL != link; link = link->m_ptrNext)
				{
					//save the link pointer
					m_lstLinks[index++] = link;
				}
			}
			else
			{
				//failed to create the required array
				DEBUG_ASSERT(FALSE);	//break into debugger
				RELEASE_CHECK(FALSE);	//log during runtime

				//The failure to build the indexing information
				//is not fatal - the items stored in the list
				//are still accessible but it will take much
				//more time.
			}
		}
		//return reference to this object
		return *this;
	}

	//**************************************************************//
	//	This function is used to find an index of a single object	//
	//	within this list.											//
	//	Notice: this function relies on the proper comparator		//
	//	operator "operator ==(T const&)" to be implemented in the	//
	//	class type <T> or otherwise it may not work correctly.		//
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
		//search the array
		size_t index = 0;
		for (TLink* link = m_ptrHead; 
			NULL != link; link = link->m_ptrNext)
		{
			//check if the data matches using 
			//the T's "operator ==(T const&)"
			if (refTObj == link->m_objItem)
			{
				//return the index
				return static_cast<int>(index);
			}
			else
			{
				//increment the index
				++index;
			}
		}
		//object not found
		return NEGATIVE_VALUE;
	}

	//**************************************************************//
	//	This function is used to convert the list to an array.		//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The function returns an array containing copies of the list	//
	//	items.														//
	//																//
	//**************************************************************//
	TArray<T> ToArray(VOID) const
	{
		//create an empty array
		TArray<T> data(m_numCount);

		//copy all list items
		size_t index = 0;
		for (TLink* link = m_ptrHead; 
			NULL != link; link = link->m_ptrNext)
		{
			//copy the data using T's "operator =(T const&)"
			data[index++] = const_cast<T const&>(link->m_objItem);
		}

		//return the array
		return data;
	}

	//**************************************************************//
	//	This function is used to append single object at the very	//
	//	end ofthis list. The function reallocates the memory if		//
	//	necessary.													//
	//	Notice: this function will be called when the argument is	//
	//	a value type or a temporary object.							//
	//	Notice: this function relies on the proper assignment		//
	//	operator "operator =(T const&)" to be implemented in the	//
	//	class type <T> or otherwise it may not work correctly		//
	//	(value data types don't need to implement this operator).	//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	refTObj	-	the reference to the object being added to the	//
	//				list											//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The function returns valid pointer to the new object added	//
	//	successfully or NULL otherwise.								//
	//																//
	//**************************************************************//
	T* Add(T const& refTObj)
	{
		//append the copy of the object at the end of the arrray
		return InsertAt(m_numCount, refTObj);
	}

	//**************************************************************//
	//	This function is used to append single object at the very	//
	//	end ofthis list. The function reallocates the memory if		//
	//	necessary.													//
	//	Notice: this function relies on the proper assignment		//
	//	operator "operator =(T&)" to be implemented in the class	//
	//	type <T> or otherwise it may not work correctly.			//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	refTObj	-	the reference to the object being added to the	//
	//				list											//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The function returns valid pointer to the new object added	//
	//	successfully or NULL otherwise.								//
	//																//
	//**************************************************************//
	T* Add(T& refTObj)
	{
		//append the object at the end of the arrray
		return InsertAt(m_numCount, refTObj);
	}

	//**************************************************************//
	//	This function is used to remove the first or all matching	//
	//	objects from the list.										//
	//	Notice: this function relies on the proper comaprator		//
	//	operator "operator ==(T const&)" to be implemented in the	//
	//	class type <T> or otherwise it may not work correctly.		//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	refTObj	-	the object being removed from the list			//
	//	flgAll	-	the flag indicating whether all matching		//
	//				objects should be removed or only the first one	//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The function removes matching object from the list.			//
	//																//
	//**************************************************************//
	VOID Remove(T const& refTObj, BOOL flgAll)
	{
		//start the search at the head
		for (TLink *link = m_ptrHead, 
			*next = NULL; NULL != link; link = next)
		{
			//save the next link pointer
			next = link->m_ptrNext;

			//check if the data matches using 
			//the T's "operator ==(T const&)"
			if (refTObj == link->m_objItem)
			{
				//unlink from the list
				RemoveLink(link);

				//delete the link and the contained T object
				delete link;

				//remove only the first matching object?
				if (FALSE == flgAll)
				{
					//done
					return;
				}
			}
		}
	}

	//**************************************************************//
	//	This function is used to insert single object into the		//
	//	list. The function (re)allocates the memory if necessary.	//
	//	Notice: this function will be called when the argument is	//
	//	a value type or a temporary object.							//
	//	Notice: this function will be called when the argument is	//
	//	a value type or a temporary object.							//
	//	Notice: this function relies on the proper assignment		//
	//	operator "operator =(T const&)" to be implemented in the	//
	//	class type <T> or otherwise it may not work correctly		//
	//	(value data types don't need to implement this operator).	//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	index	-	0-based index at which the new object is to be	//
	//				inserted; if the index is beyond the boundaries	//
	//				of the list, it will be added at the end		//
	//																//
	//	refTObj	-	the reference to the object being added to the	//
	//				list											//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The function returns valid pointer to the new object added	//
	//	successfully or NULL otherwise.								//
	//																//
	//**************************************************************//
	T* InsertAt(size_t numIndex, T const& refTObj)
	{
		//create new link and copy the object 
		//using the "operator =(T const&)"
		TLink* link = new TLink;
		link->m_objItem = refTObj;
		link->m_ptrPrev = NULL;
		link->m_ptrNext = NULL;

		//insert the link into the list
		if (FALSE != InsertLink(numIndex, link))
		{
			//return the pointer to the inserted item
			return &link->m_objItem;
		}
		else
		{
			//delete the link and the contained T object
			delete link;
		}

		//failed to insert the new object
		return NULL;
	}

	//**************************************************************//
	//	This function is used to insert single object into the		//
	//	list. The function (re)allocates the memory if necessary.	//
	//	Notice: this function relies on the proper assignment		//
	//	operator "operator =(T&)" to be implemented in the class	//
	//	type <T> or otherwise it may not work correctly.			//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	index	-	0-based index at which the new object is to be	//
	//				inserted; if the index is beyond the boundaries	//
	//				of the list, it will be added at the end		//
	//																//
	//	refTObj	-	the reference to the object being added to the	//
	//				list											//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The function returns valid pointer to the new object added	//
	//	successfully or NULL otherwise.								//
	//																//
	//**************************************************************//
	T* InsertAt(size_t numIndex, T& refTObj)
	{
		//create new link and copy the object 
		//using the "operator =(T&)"
		TLink* link = new TLink;
		link->m_objItem = refTObj;
		link->m_ptrPrev = NULL;
		link->m_ptrNext = NULL;

		//insert the link into the list
		if (FALSE != InsertLink(numIndex, link))
		{
			//return the pointer to the inserted item
			return &link->m_objItem;
		}
		else
		{
			//delete the link and the contained T object
			delete link;
		}

		//failed to insert the new object
		return NULL;
	}

	//**************************************************************//
	//	This function is used to remove (destroy) single object		//
	//	stored in the list.											//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	index		-	0-based index to an object within the		//
	//					list										//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The function removes single object from the list.			//
	//																//
	//**************************************************************//
	VOID RemoveAt(size_t numIndex)
	{
		//find the link to remove
		TLink* link = SelectLink(numIndex);
		if (NULL != link)
		{
			//unlink from the list
			RemoveLink(link);

			//delete the link and the contained T object
			delete link;
		}
	}

//operators
public:

	//**************************************************************//
	//	This operator is used to make copy of the source list.		//
	//	It is strongly recommended to re-index the source array		//
	//	before copying it to improve the performance.				//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	refTList	-	reference to the source list				//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The operator returns the reference to this list.			//
	//																//
	//**************************************************************//
	TList<T>& operator =(TList<T> const& refTList)
	{
		//make copy of existing list
		return Copy(refTList);
	}

	//**************************************************************//
	//	This operator is used to take over the ownership of managed	//
	//	memory block containg the source list.						//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	refTList	-	reference to the source list				//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The operator returns the reference to this list.			//
	//																//
	//**************************************************************//
	TList<T>& operator =(TList<T>& refTList)
	{
		//clear this list
		Clear();

		//take over an existing list
		m_ptrHead = refTList.m_ptrHead;
		m_ptrTail = refTList.m_ptrTail;
		m_numCount = refTList.m_numCount;

		refTList.m_ptrHead = NULL;
		refTList.m_ptrTail = NULL;
		refTList.m_numCount = 0;
		refTList.m_lstLinks.Delete();

		//rebuild the index information
		IndexOn(TRUE);

		//return the reference to this object
		return *this;
	}

	//**************************************************************//
	//	This operator is used to get the reference to an object		//
	//	within the list.											//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	index		-	0-based index to an object within the		//
	//					list										//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The operator returns the reference to the object selected	//
	//	within the list.											//
	//																//
	//**************************************************************//
	T const& operator [](size_t index) const
	{ 
		//validate the index
		TLink const* link = SelectLink(index);
		if (NULL != link)
		{
			//return the list item
			return link->m_objItem;
		}

		//failed to access an item
		DEBUG_ASSERT(FALSE);	//break into debugger
		RELEASE_CHECK(FALSE);	//log during runtime
		throw CException(ExceptionCodes::Index_Out_Of_Range,
			"[TList<T>::operator [](size_t index) const] Index out of range!");
	}

	//**************************************************************//
	//	This operator is used to get the reference to an object		//
	//	within the list.											//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	index		-	0-based index to an object within the		//
	//					list										//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The operator returns the reference to the object selected	//
	//	within the list.											//
	//																//
	//**************************************************************//
	T& operator [](size_t index)
	{ 
		//validate the index
		TLink* link = SelectLink(index);
		if (NULL != link)
		{
			//return the list item
			return link->m_objItem;
		}

		//failed to access an item
		DEBUG_ASSERT(FALSE);	//break into debugger
		RELEASE_CHECK(FALSE);	//log during runtime
		throw CException(ExceptionCodes::Index_Out_Of_Range,
			"[TList<T>::operator [](size_t index)] Index out of range!");
	}

	//**************************************************************//
	//	This operator is used to get the reference to an object		//
	//	within the list.											//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	index		-	0-based index to an object within the		//
	//					list										//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The operator returns the reference to the object selected	//
	//	within the list.											//
	//																//
	//**************************************************************//
	T const& operator [](int index) const
	{ 
		//redirect the call
		return operator [](static_cast<size_t>(index));
	}

	//**************************************************************//
	//	This operator is used to get the reference to an object		//
	//	within the list.											//
	//**************************************************************//
	//	Arguments:													//
	//**************************************************************//
	//																//
	//	index		-	0-based index to an object within the		//
	//					list										//
	//																//
	//**************************************************************//
	//	Result(s):													//
	//**************************************************************//
	//																//
	//	The operator returns the reference to the object selected	//
	//	within the list.											//
	//																//
	//**************************************************************//
	T& operator [](int index)
	{ 
		//redirect the call
		return operator [](static_cast<size_t>(index));
	}

//private methods
private:

	//sort the partial content of the list 
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
		for (size_t i = numIndex; i < final; ++i)    //skip the last element
		{
			//compare selected item with the last item
			if (IS_EQUAL > Compare(operator[](i), 
				operator[](final), flgDescending, ptrComparer))
			{
				//this item goes before the pivot item
				Swap(i, pivot++);	//increment the pivot index
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

	//swap 2 objects in the list
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

	TLink const* SelectLink(size_t numIndex) const
	{
		//indexing available?
		if (m_numCount == m_lstLinks.Count())
		{
			//The indexing information is available and
			//can be used to speed up fetching of the 
			//required link.

			//index within range?
			if (numIndex < m_numCount)
			{
				//return link using the indexing information
				return m_lstLinks[numIndex];
			}
		}
		else
		{
			//The indexing information is not available so
			//search for the required link the hard way.

			//start the search at the head
			for (TLink* link = m_ptrHead; 
				NULL != link; link = link->m_ptrNext, --numIndex)
			{
				//arrived at the required position?
				if (0 == numIndex)
				{
					//return the link
					return link;
				}
			}
		}

		//there is nothing at the given position
		return NULL;
	}

	TLink* SelectLink(size_t numIndex)
	{
		//indexing available?
		if (m_numCount == m_lstLinks.Count())
		{
			//The indexing information is available and
			//can be used to speed up fetching of the 
			//required link.

			//index within range?
			if (numIndex < m_numCount)
			{
				//return link using the indexing information
				return m_lstLinks[numIndex];
			}
		}
		else
		{
			//The indexing information is not available so
			//search for the required link the hard way.

			//start the search at the head
			for (TLink* link = m_ptrHead; 
				NULL != link; link = link->m_ptrNext, --numIndex)
			{
				//arrived at the required position?
				if (0 == numIndex)
				{
					//return the link
					return link;
				}
			}
		}

		//there is nothing at the given position
		return NULL;
	}

	BOOL InsertLink(size_t numIndex, TLink* ptrLink)
	{
		//is the link valid?
		if (NULL != ptrLink)
		{
			//find the insertion point (it will become the next link)
			TLink* curr = SelectLink(numIndex);
			if (NULL != curr)
			{
				//The current link is not NULL so the new link 
				//should be inserted right before it.

				//link-in
				ptrLink->m_ptrPrev = curr->m_ptrPrev;
				ptrLink->m_ptrNext = curr;

				//update linking of the current item
				if (NULL != curr->m_ptrPrev)
				{
					curr->m_ptrPrev->m_ptrNext = ptrLink;
				}
				curr->m_ptrPrev = ptrLink;

				//update the list head pointer if necessary
				if (m_ptrHead == curr)
				{
					m_ptrHead = ptrLink;
				}
			}
			else
			{
				//There is no current link persent so the new link 
				//should be added at the end of the list. 

				//link-in
				ptrLink->m_ptrPrev = m_ptrTail;
				ptrLink->m_ptrNext = NULL;

				//update the list tail pointer
				if (NULL != m_ptrTail)
				{
					m_ptrTail->m_ptrNext = ptrLink;
				}
				m_ptrTail = ptrLink;

				//update the list head pointer if necessary
				if (NULL == m_ptrHead)
				{
					m_ptrHead = ptrLink;
				}
			}

			//update the list size
			++m_numCount;

			//invalidate current indexing
			m_lstLinks.Delete();

			//new link added
			return TRUE;
		}

		//failed to insert the new link
		return FALSE;
	}

	VOID RemoveLink(TLink* ptrLink)
	{
		//is the link valid?
		if (NULL != ptrLink)
		{
			//unlink
			if (NULL != ptrLink->m_ptrPrev)
			{
				ptrLink->m_ptrPrev->m_ptrNext = ptrLink->m_ptrNext;
			}
			if (NULL != ptrLink->m_ptrNext)
			{
				ptrLink->m_ptrNext->m_ptrPrev = ptrLink->m_ptrPrev;
			}

			//update the list head pointer if necessary
			if (m_ptrHead == ptrLink)
			{
				m_ptrHead = ptrLink->m_ptrNext;
			}

			//update the list tail pointer if necessary
			if (m_ptrTail == ptrLink)
			{
				m_ptrTail = ptrLink->m_ptrPrev;
			}

			//update the list size
			--m_numCount;

			//invalidate current indexing
			m_lstLinks.Delete();
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

typedef TList<BYTE_MEMPTR> BYTE_MEMPTR_LIST;

//---------------------------------------------------------------------------

#endif	//_TLIST_HPP_
