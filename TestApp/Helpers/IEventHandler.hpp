//---------------------------------------------------------------------------
//
//	IEventHandler.hpp
//
//	The event handler class type interface.
//
//	Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_IBase.hpp"

#ifndef _IEVENT_HANDLER_HPP_
#define _IEVENT_HANDLER_HPP_

//---------------------------------------------------------------------------

template <class TSender, class TEventArgs>
DSC_INTERFACE IEventHandler
{
public:

	//destroy the event handler object and free the memory
	virtual VOID ICALL Free(VOID) = 0;

	//clone the event handler object
	virtual IEventHandler<TSender, TEventArgs>* ICALL Clone(VOID) const = 0;

	//check if event handlers are equivalent
	virtual BOOL ICALL Equals(IEventHandler<TSender, TEventArgs> const* ptrHandler) const = 0;

	//call/execute the event handler
    virtual VOID ICALL operator ()(TSender* ptrSender, TEventArgs const* ptrArgs) const = 0;
};

//---------------------------------------------------------------------------

#endif	//_IEVENT_HANDLER_HPP_
