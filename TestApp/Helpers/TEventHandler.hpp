//---------------------------------------------------------------------------
//
//	TEventHandler.hpp
//
//	An ipmplementation of the event handler class type.
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "IEventHandler.hpp"

#ifndef _T_EVENT_HANDLER_HPP_
#define _T_EVENT_HANDLER_HPP_

//---------------------------------------------------------------------------

template <class TSender, class TEventArgs, class TReceiver>
class TEventHandler : public IEventHandler<TSender, TEventArgs>
{
//public types
public:
	typedef VOID (TReceiver::*HANDLER)(TSender* ptrSender, TEventArgs const* ptrArgs);

//private members
private:
	TReceiver*	const	m_ptrReceiver;
	HANDLER		const	m_ptrFunction;

//construction and destruction
public:

	TEventHandler(TReceiver* const ptrReceiver, HANDLER const ptrFunction) : 
		m_ptrReceiver(ptrReceiver), m_ptrFunction(ptrFunction)
	{}

	virtual ~TEventHandler(VOID)
	{}

//public methods
public:

	//destroy this object and free memory
	VOID ICALL Free(VOID)
	{
		//delete this object
		delete this;
	}

	//clone this object
	IEventHandler<TSender, TEventArgs>* ICALL Clone(VOID) const
	{
		return new TEventHandler<TSender, TEventArgs, TReceiver>(m_ptrReceiver, m_ptrFunction);
	}

	//check if this object matches the argument
	BOOL ICALL Equals(IEventHandler<TSender, TEventArgs> const* ptrHandler) const
	{
		//try casting the handler pointer onto this type
		TEventHandler<TSender, TEventArgs, TReceiver> const* ptrThisHandler = 
			static_cast<TEventHandler<TSender, TEventArgs, TReceiver> const*>(ptrHandler);
		if (NULL != ptrThisHandler)
		{
			//compare corresponding class type and function pointers
			if ((m_ptrReceiver == ptrThisHandler->m_ptrReceiver) &&
				(m_ptrFunction == ptrThisHandler->m_ptrFunction))
			{
				//the same delegate
				return TRUE;
			}
		}
		//different delegates
		return FALSE;
	}

	//execute the event handler
	VOID ICALL operator()(TSender* ptrSender, TEventArgs const* ptrArgs) const
	{
		//check if the event handler info is present
		if ((NULL != m_ptrReceiver) && (NULL != m_ptrFunction))
		{
			try
			{
				//call the event handler
				(m_ptrReceiver->*m_ptrFunction)(ptrSender, ptrArgs);
			}
			catch (...)
			{
				//swallow exceptions
			}
		}
	}
};

//---------------------------------------------------------------------------

#endif	//_T_EVENT_HANDLER_HPP_
