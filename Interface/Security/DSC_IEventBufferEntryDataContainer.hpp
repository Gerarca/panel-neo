//---------------------------------------------------------------------------
//
//	DSC_IEventBufferEntryDataContainer.hpp
//
// Data container for "Event Buffer Notification (CMD110)" update.
//
//---------------------------------------------------------------------------
//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

//includes
#include "DSC_IComponent.hpp"
#include "DSC_IDataBuffer.hpp"

#ifndef _DSC_I_EVENT_BUFFER_ENTRY_DATA_CONTAINER
#define _DSC_I_EVENT_BUFFER_ENTRY_DATA_CONTAINER

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#define NAME_DSC_IEventBufferEntryDataContainer	"DSC_IEventBufferEntryDataContainer"

//---------------------------------------------------------------------------

#ifndef DSC_IEventBufferEntryDataContainer_FWD_DEFINED
#define DSC_IEventBufferEntryDataContainer_FWD_DEFINED
typedef DSC_INTERFACE DSC_IEventBufferEntryDataContainer DSC_IEventBufferEntryDataContainer;
#endif

//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

/*!
	This interface is used for providing information on event buffer entries
	in the system.
*/
DSC_INTERFACE DSC_IEventBufferEntryDataContainer : public DSC_IComponent
{
public:	

    //! Get the Partition number to which the buffer message is for.
    /*! Gets the partition the buffer message is for. 
	*/
    /*!	
    	\param ptrPartition Pointer to storage for the partition number.
    */	
	virtual IRESULT ICALL get_Partition(OUT DSC_SYSTEM_INDEX* ptrPartition) const = 0;

	//! Returns the event type received
	/*! Returns the event type received. */
	/*!
		\param ptrEventCode Pointer to storage for event type.
	*/
	virtual IRESULT ICALL get_EventType(OUT BYTE* ptrEventType) const = 0;

	//! Returns the event code received
	/*! Returns the event code received. */
	/*!
		\param ptrEventCode Pointer to storage for event code.
	*/
	virtual IRESULT ICALL get_EventCode(OUT UINT16* ptrEventCode) const = 0;
};

#else

typedef struct DSC_IEventBufferEntryDataContainer_Vtbl
{
	BEGIN_INTERFACE

	IRESULT (ICALL *Query)(IN DSC_IEventBufferEntryDataContainer *This, IN char const* pszInterface, OUT VOID** ptrInterface);
	IRESULT (ICALL *Acquire)(IN DSC_IEventBufferEntryDataContainer *This, OUT ICOUNT* ptrCount);
	IRESULT (ICALL *Release)(IN DSC_IEventBufferEntryDataContainer *This, OUT ICOUNT* ptrCount);

	IRESULT (ICALL *get_Partition)(IN DSC_IEventBufferEntryDataContainer *This, OUT DSC_SYSTEM_INDEX* ptrPartition);
    IRESULT (ICALL *get_EventType)(IN DSC_IEventBufferEntryDataContainer *This, OUT BYTE* ptrEventType);
    IRESULT (ICALL *get_EventCode)(IN DSC_IEventBufferEntryDataContainer *This, OUT UINT16* ptrEventCode);

	END_INTERFACE
} DSC_IEventBufferEntryDataContainer_Vtbl;

DSC_INTERFACE DSC_IEventBufferEntryDataContainer
{
	//the assumption: the compiler places pointer to VTABLE first in the class layout
 	struct DSC_IEventBufferEntryDataContainer_Vtbl *ptrVtbl;
};

#endif

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_I_EVENT_BUFFER_ENTRY_DATA_CONTAINER
