//---------------------------------------------------------------------------
//
//	TDictionary.hpp
//
//	The generic dictionary implementation based on a sorted list.
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "TList.hpp"
#include "TKeyValue.hpp"
#include "TComparer.hpp"

#ifndef _TDICTIONARY_HPP_
#define _TDICTIONARY_HPP_

//---------------------------------------------------------------------------

//disable some well-understood warnings
#if defined(MS_VS_COMPILER)
#pragma warning(push)
#pragma warning(disable: 4355 4522)
#elif defined(GCC_COMPILER)
#else
#error "Undefined compiler information!"
#endif	//MS_VS_COMPILER

//---------------------------------------------------------------------------

template<class TKey, class TValue>
class TDictionary
{
//private members
private:

	//The list contains key/value pairs. Each key must be
	//unique within the list or otherwise it wouldn't be
	//a dictionary.
	TList<TKeyValue<TKey, TValue> >	m_lstDictionary;
	TComparer<TKey>*				m_ptrKeyComparer;	//optional key comparer

//constructors & destructor
public:

	TDictionary(TComparer<TKey>* ptrComparer = NULL) : 
		m_ptrKeyComparer(ptrComparer)
	{
	}

	virtual ~TDictionary(VOID)
	{
		//free the comparer
		SetComparer(NULL);
	}

//public methods
public:

	//Get the count of elements currently stored in the dictionary.
	size_t Count(VOID) const
	{
		return m_lstDictionary.Count();
	}

	//Clear the contents of the dictionary.
	VOID Clear(VOID)
	{
		m_lstDictionary.Clear();
	}

	//The sorting of the entries is required in order to enable
	//efficient binary tree search algorithm to be used for
	//indexing of the dictionary content.
	TValue* Add(TKey const& refTKey, 
		TValue const& refTValue, BOOL flgOverwrite = FALSE)
	{
		//check if the dictionary already contains the key
		size_t insert = 0;
		int index = Search(refTKey, 0, m_lstDictionary.Count(), insert);
		if (0 > index)
		{
			//add new key/value pair to the list
			TKeyValue<TKey, TValue> pair(refTKey, refTValue);
			TKeyValue<TKey, TValue>* added = 
				m_lstDictionary.InsertAt(insert, pair);
			if (NULL != added)
			{
				//return pointer to the newly added value
				return &(added->m_objValue);
			}
		}
		else
		{
			//check if the existing value should be replaced
			if (FALSE != flgOverwrite)
			{
				//modify existing entry
				TKeyValue<TKey, TValue>* present = &m_lstDictionary[index];
				present->m_objValue = refTValue;

				//return pointer to the modified value
				return &(present->m_objValue);
			}
		}
		//failure
		return NULL;
	}

	//The sorting of the entries is required in order to enable
	//efficient binary tree search algorithm to be used for
	//indexing of the dictionary content.
	TValue* Add(TKey const& refTKey, 
		TValue& refTValue, BOOL flgOverwrite = FALSE)
	{
		//check if the dictionary already contains the key
		size_t insert = 0;
		int index = Search(refTKey, 0, m_lstDictionary.Count(), insert);
		if (0 > index)
		{
			//add new key/value pair to the list
			TKeyValue<TKey, TValue> pair(refTKey, refTValue);
			TKeyValue<TKey, TValue>* added = 
				m_lstDictionary.InsertAt(insert, pair);
			if (NULL != added)
			{
				//return pointer to the newly added value
				return &(added->m_objValue);
			}
		}
		else
		{
			//check if the existing value should be replaced
			if (FALSE != flgOverwrite)
			{
				//modify existing entry
				TKeyValue<TKey, TValue>* present = &m_lstDictionary[index];
				present->m_objValue = refTValue;

				//return pointer to the modified value
				return &(present->m_objValue);
			}
		}
		//failure
		return NULL;
	}

	//Remove an entry with the given key from the dictionary.
	VOID Remove(TKey const& refTKey)
	{
		//search for entry
		size_t insert = 0;
		int index = Search(refTKey, 0, m_lstDictionary.Count(), insert);
		if (0 <= index)
		{
			//remove existing entry
			m_lstDictionary.RemoveAt(static_cast<size_t>(index));
		}
	}

	//Find the index of an entry within the dictionary.
	//Function returns value < 0 if entry not found.
	int IndexOf(TKey const& refTKey) const
	{
		//search for the key
		size_t temp = 0;
		return Search(refTKey, 0, m_lstDictionary.Count(), temp);
	}

	//Check if the dictionary contains certain entry.
	BOOL Contains(TKey const& refTKey) const
	{
		int index = IndexOf(refTKey);
		return (0 <= index)? TRUE : FALSE;
	}

	//Get all unique keys of entries currently stored in the dictionary.
	TList<TKey> GetKeys(VOID) const
	{
		//get the number of entries in the dictionary
		size_t count = m_lstDictionary.Count();

		//fetch the keys from the dictionary (each key/entry is unique)
		TList<TKey> keys;
		for (size_t i = 0; i < count; ++i)
		{
			//copy the key into the list
			if (NULL == keys.Add(
				const_cast<TKey const&>(m_lstDictionary[i].m_objKey)))
			{
				//not enough memeory
				DEBUG_CHECK(FALSE);
				RELEASE_CHECK(FALSE);
			}
		}

		//return the list of keys
		return keys;
	}

	//the alternative method of accessing the value to
	//"TValue const& operator [](TKey const& refTKey) const"
	TValue const& GetValue(TKey const& refTKey) const
	{
		int index = IndexOf(refTKey);
		if (0 <= index)
		{
			return  m_lstDictionary[index].m_objValue;
		}

		//failed to access an item
		DEBUG_ASSERT(FALSE);	//break into debugger
		RELEASE_CHECK(FALSE);	//log during runtime
		throw CException(ExceptionCodes::Unknown_Index_Key,
			"[TDictionary<TKey, TValue>::GetValue(TKey const& key)] No value with the given key found!");
	}

	//the alternative method of accessing the value to
	//"TValue& operator [](TKey const& refTKey)"
	TValue& GetValue(TKey const& refTKey)
	{
		int index = IndexOf(refTKey);
		if (0 <= index)
		{
			return  m_lstDictionary[index].m_objValue;
		}

		//failed to access an item
		DEBUG_ASSERT(FALSE);	//break into debugger
		RELEASE_CHECK(FALSE);	//log during runtime
		throw CException(ExceptionCodes::Unknown_Index_Key,
			"[TDictionary<TKey, TValue>::GetValue(TKey const& key)] No value with the given key found!");
	}

	//the alternative method of accessing key/value data to 
	//"TKeyValue<TKey, TValue> const& operator[](size_t index) const"
	TKeyValue<TKey, TValue> const& GetAt(size_t numIndex) const
	{
		return m_lstDictionary[numIndex];
	}

	//Remove the entry at the given index position (carefull!).
	VOID RemoveAt(size_t numIndex)
	{
		m_lstDictionary.RemoveAt(numIndex);
	}

//operators
public:

	//copy the contents of the source dictionary
	TDictionary<TKey, TValue>& operator =(TDictionary<TKey, TValue> const& refTDictionary)
	{
		//make copy of existing list
		m_lstDictionary = refTDictionary.m_lstDictionary;

		//clone the comparer if required
		if (NULL != refTDictionary.m_ptrKeyComparer)
		{
			SetComparer(refTDictionary.m_ptrKeyComparer->Clone());
		}
		else
		{
			SetComparer(NULL);
		}

		//return reference to the dictionary
		return *this;
	}

	//move (take ownership) of the contents of the source dictionary
	TDictionary<TKey, TValue>& operator =(TDictionary<TKey, TValue>& refTDictionary)
	{
		//take over an existing list
		m_lstDictionary = refTDictionary.m_lstDictionary;

		//clone the comparer if required
		if (NULL != refTDictionary.m_ptrKeyComparer)
		{
			SetComparer(refTDictionary.m_ptrKeyComparer->Clone());
		}
		else
		{
			SetComparer(NULL);
		}

		//return reference to the dictionary
		return *this;
	}

	//return value based on the given key; it may throw
	//an exception if there is no entry in the dictionary
	//with the given key
	TValue const& operator [](TKey const& refTKey) const
	{
		int index = IndexOf(refTKey);
		if (0 <= index)
		{
			return  m_lstDictionary[index].m_objValue;
		}

		//failed to access an item
		DEBUG_ASSERT(FALSE);	//break into debugger
		RELEASE_CHECK(FALSE);	//log during runtime
		throw CException(ExceptionCodes::Unknown_Index_Key,
			"[TDictionary<TKey, TValue>::operator [](TKey const& key)] No value with the given key found!");
	}

	//return value based on the given key; it may throw
	//an exception if there is no entry in the dictionary
	//with the given key
	TValue& operator [](TKey const& refTKey)
	{
		int index = IndexOf(refTKey);
		if (0 <= index)
		{
			return  m_lstDictionary[index].m_objValue;
		}

		//failed to access an item
		DEBUG_ASSERT(FALSE);	//break into debugger
		RELEASE_CHECK(FALSE);	//log during runtime
		throw CException(ExceptionCodes::Unknown_Index_Key,
			"[TDictionary<TKey, TValue>::operator [](TKey const& key)] No value with the given key found!");
	}

	//do not allow r/w access to TKeyValue<TKey, TValue> to
	//prevent modifying the key that governs the sorting
	TKeyValue<TKey, TValue> const& operator[](size_t index) const
	{
		return m_lstDictionary[index];
	}

	//do not allow r/w access to TKeyValue<TKey, TValue> to
	//prevent modifying the key that governs the sorting
	TKeyValue<TKey, TValue> const& operator[](int index) const
	{
		return m_lstDictionary[index];
	}

//private methods
private:

	//Allow setting/changing the comparer.
	VOID SetComparer(TComparer<TKey>* ptrComparer)
	{
		//check if comparer was assigned
		if (NULL != m_ptrKeyComparer)
		{
			//delet the comparer
			delete m_ptrKeyComparer;
		}
		m_ptrKeyComparer = ptrComparer;
	}

	//This class uses binary tree search algorithm
	//to search for keys within the dictionary.
	//This function serves 2 purposes: 1) to find an index of
	//an entry with given key, and 2) failing that, provide
	//the insertion point into the dictionary - this takes
	//care about proper sorting of the dictionary entries.
	int Search(TKey const& refTKey, 
		size_t numIndex, size_t numCount, size_t& numInsert) const
	{
		//check if further descent is required
		if (1 < numCount)
		{
			//select the mid-point index
			size_t split = numIndex + (numCount >> 1);

			//compare keys at the split point
			int compare = Compare(refTKey, 
				m_lstDictionary[split].m_objKey);
			if (IS_EQUAL > compare)
			{
				//search entries before the 'split' index
				//(skip the entry at the 'split' index)
				return Search(refTKey, 
					numIndex, split - numIndex, numInsert);
			}
			else if (IS_EQUAL < compare)
			{
				//search entries after the 'split' index
				//(skip the entry at the 'split' index)
				return Search(refTKey, 
					split + 1, numCount - (split + 1 - numIndex), numInsert);
			}

			//key found - return valid index
			numInsert = static_cast<size_t>(-1);	//max size_t value
			return int(split);	//the split index - not numIndex!
		}
		else if (1 == numCount)
		{
			//compare keys of the last item in the descent path
			int compare = Compare(refTKey, 
				m_lstDictionary[numIndex].m_objKey);
			if (0 > compare)
			{
				//assign the insert index to the index of the last item 
				//from the list so the new item can be inserted before it
				numInsert = numIndex;
				return NEGATIVE_VALUE;	//key not found
			}
			else if (0 < compare)
			{
				//assign the insert index to the index of the next item 
				//from the list so the new item can be inserted after it
				numInsert = numIndex + 1;
				return NEGATIVE_VALUE;	//key not found
			}

			//key found - return the index
			numInsert = static_cast<size_t>(-1);	//max size_t value
			return int(numIndex);	//the numIndex!
		}

		//key not found - insert new item at the numIndex position
		numInsert = numIndex;
		return NEGATIVE_VALUE;	//key not found
	}

	//Compare 2 keys.
	int Compare(TKey const& refA, TKey const& refB) const
	{
		//check if comparer is available
		if (NULL != m_ptrKeyComparer)
		{
			//use the provided comparer
			return m_ptrKeyComparer->Compare(refA, refB);
		}

		//by default, use the compare operators of TKey
		if (refA > refB)
		{
			return IS_GREATER;
		}
		else if (refA < refB)
		{
			return IS_LESSER;
		}

		//both keys are equal
		return IS_EQUAL;
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

#endif	//_TDICTIONARY_HPP_
