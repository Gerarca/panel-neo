//---------------------------------------------------------------------------
//
//	TEvent.hpp
//
//	An ipmplementation of the event class type.
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "IEventHandler.hpp"
#include "TList.hpp"
#include "Lock.hpp"

using namespace SDK_MAJOR_NAMESPACE::SDK_MINOR_NAMESPACE;

#ifndef _TEVENT_HPP_
#define _TEVENT_HPP_

//---------------------------------------------------------------------------

template <class TSender, class TEventArgs> 
class TEvent
{
//private members
private:

	//the list of pointers to event handlers
	TList<IEventHandler<TSender, TEventArgs>*>	m_lstHandlers;
	CCriticalSection							m_clsListLock;

//constructors & destructor
public:

	TEvent(VOID)
	{
#ifdef TRACK_EVENT_LIFETIME
		DEBUG_PRINTF("[TEvent::TEvent] %p\n", this);
#endif
	}

	virtual ~TEvent(VOID)
	{
#ifdef TRACK_EVENT_LIFETIME
		DEBUG_PRINTF("[TEvent::~TEvent] %p\n", this);
#endif
		//delete all handlers
		CLock lock = m_clsListLock;
		while (0 < m_lstHandlers.Count())
		{
			//destroy the event handler
			Destroy(m_lstHandlers[0]);

			//remove the event handler from the list
			m_lstHandlers.RemoveAt(0);
		}
	}

//public methods
public:

	//check if there are no subscribes to the event
	BOOL IsNull(VOID)
	{
		CLock lock = m_clsListLock;
		return (0 == m_lstHandlers.GetCount())? TRUE : FALSE;
	}

	//add the event handler to the list
	//
	//the lifetime of the object pointed to by ptrHandler 
	//must be controlled externally
	VOID operator +=(IEventHandler<TSender, TEventArgs> const* ptrHandler)
	{
		//sanity check
		if (NULL != ptrHandler)
		{
			//check if the handler is already in the list
			CLock lock = m_clsListLock;
			int index = IndexOf(ptrHandler);
			if (0 > index)
			{
				//make a copy of the event handler
				IEventHandler<TSender, TEventArgs>* handler = ptrHandler->Clone();

				//add new handler to the list
				if (NULL == m_lstHandlers.Add(handler))
				{
					//couldn't add the handler to the list
					DEBUG_ASSERT(FALSE);	//break into debugger
					RELEASE_CHECK(FALSE);	//log during runtime
					throw CException(ExceptionCodes::Memory_Alloc_Failed,
						"[TEvent<TSender>::operator +=(IEventHandler<TSender> const* ptrHandler)] Failed to add handler to the list!");
				}
			}
		}
	}

	//take the ownership of the event handler and add it to the list
	//
	//the lifetime of the object pointed to by ptrHandler is
	//controlled internally after taking ownership of the object
	VOID operator +=(IEventHandler<TSender, TEventArgs>* ptrHandler)
	{
		//sanity check
		if (NULL != ptrHandler)
		{
			//check if the handler is already in the list
			CLock lock = m_clsListLock;
			int index = IndexOf(ptrHandler);
			if (0 > index)
			{
				//add new handler to the list
				if (NULL == m_lstHandlers.Add(ptrHandler))
				{
					//destroy the event handler to avoid memory leaks
					Destroy(ptrHandler);

					//couldn't add the handler to the list
					DEBUG_ASSERT(FALSE);	//break into debugger
					RELEASE_CHECK(FALSE);	//log during runtime
					throw CException(ExceptionCodes::Memory_Alloc_Failed,
						"[TEvent<TSender>::operator +=(IEventHandler<TSender>* ptrHandler)] Failed to add handler to the list!");
				}
			}
			else
			{
				//destroy the event handler to avoid memory leaks
				Destroy(ptrHandler);
			}
		}
	}

	//remove the event handler from the list
	//
	//the lifetime of the object pointed to by ptrHandler 
	//must be controlled externally
	VOID operator -=(IEventHandler<TSender, TEventArgs> const* ptrHandler)
	{
		//sanity check
		if (NULL != ptrHandler)
		{
			//check if the handler is already in the list
			CLock lock = m_clsListLock;
			int index = IndexOf(ptrHandler);
			if (0 <= index)
			{
				//destroy the event handler
				Destroy(m_lstHandlers[index]);

				//remove existing handler from the list
				m_lstHandlers.RemoveAt(index);
			}
		}
	}

	//remove the event handler from the list
	//
	//the lifetime of the object pointed to by ptrHandler is
	//controlled internally after taking ownership of the object
	VOID operator -=(IEventHandler<TSender, TEventArgs>* ptrHandler)
	{
		//sanity check
		if (NULL != ptrHandler)
		{
			//check if the handler is already in the list
			CLock lock = m_clsListLock;
			int index = IndexOf(ptrHandler);
			if (0 <= index)
			{
				//destroy the event handler
				Destroy(m_lstHandlers[index]);

				//remove existing handler from the list
				m_lstHandlers.RemoveAt(index);
			}

			//destroy the event handler to avoid memory leaks
			Destroy(ptrHandler);
		}
	}

	//call the event handler
	VOID operator()(TSender* ptrSender, TEventArgs const* ptrArgs)
	{
		//call all event handlers
		CLock lock = m_clsListLock;
		size_t count = m_lstHandlers.Count();
		for (size_t index = 0; index < count; ++index)
		{
			//get handler from the list
			IEventHandler<TSender, TEventArgs> const* handler = m_lstHandlers[index];
			if (NULL != handler)
			{
				//call the event handler
				(*handler)(ptrSender, ptrArgs);
			}
		}
	}

//private methods
private:

	//get index of the handler within the list
	int IndexOf(IEventHandler<TSender, TEventArgs> const* ptrHandler) const
	{
		//validate the pointer to event handler
		if (NULL != ptrHandler)
		{
			//search the list of handlers
			size_t count = m_lstHandlers.Count();
			for (size_t index = 0; index < count; ++index)
			{
				//get handler from the list
				IEventHandler<TSender, TEventArgs> const* handler = m_lstHandlers[index];
				if (NULL != handler)
				{
					//compare the handler
					if (FALSE != handler->Equals(ptrHandler))
					{
						//return the index of the existing handler
						return static_cast<int>(index);
					}
				}
			}
		}
		//delegate not found
		return NEGATIVE_VALUE;
	}

	//destroy the event handler
	VOID Destroy(IEventHandler<TSender, TEventArgs>* ptrHandler)
	{
		//validate the pointer to event handler
		if (NULL != ptrHandler)
		{
			//destroy the event handler and free the memory
			ptrHandler->Free();
		}
	}
};

//---------------------------------------------------------------------------

#endif	//_TEVENT_HPP_
