//---------------------------------------------------------------------------
//
//	DSC_ISecurityEventSink.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_IComponent.hpp"
#include "DSC_IChannel.hpp"
#include "DSC_SecurityEventCategories.hpp"
#include "DSC_SecurityEventTypes.hpp"
#include "DSC_SecurityDataSelectors.hpp"
#include "DSC_DataContainers.hpp"

#ifndef _DSC_I_SECURITY_EVENT_SINK_HPP_
#define _DSC_I_SECURITY_EVENT_SINK_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

//The event sink interface is used for receiving event notifications.
#define NAME_DSC_ISecurityEventSink	"DSC_ISecurityEventSink"

//The updated event sink interface used for receiving event notifications.
#define NAME_DSC_ISecurityEventSink2	"DSC_ISecurityEventSink2"

//---------------------------------------------------------------------------

#ifndef DSC_ISecurityEventSink_FWD_DEFINED
#define DSC_ISecurityEventSink_FWD_DEFINED
typedef DSC_INTERFACE DSC_ISecurityEventSink DSC_ISecurityEventSink;
#endif

#ifndef DSC_ISecurityEventSink2_FWD_DEFINED
#define DSC_ISecurityEventSink2_FWD_DEFINED
typedef DSC_INTERFACE DSC_ISecurityEventSink2 DSC_ISecurityEventSink2;
#endif

#ifndef DSC_ISecurityBase_FWD_DEFINED
#define DSC_ISecurityBase_FWD_DEFINED
typedef DSC_INTERFACE DSC_ISecurityBase DSC_ISecurityBase;
#endif

//---------------------------------------------------------------------------
#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)
//---------------------------------------------------------------------------

/*!
	This interface is used to receive event notifications from the DSC_ISecurityBase.
*/
DSC_INTERFACE DSC_ISecurityEventSink : public DSC_IComponent
{
public:

    //! General Notification Event event
    /*! This event is fired whenever something of particular importance needs to be raised to the user.
        This primarily includes notifying the user whenever the target system has entered or exit any programming modes, 
		likely necessitating a refresh of the SDK / any cached data.      */
    /*!
		\sa DSC_IComponent
		\sa DSC_ISecurityBase
		\sa DSC_DataContainer
		\sa DSC_SecurityEventCategory
		\sa DSC_SecurityEventType
      	\param ptrSender The interface of the sender of the event (the Security Base).
		\param flgEventCategory The category of the event as listed in the DSC_SecurityEventCategorys enum (for example "SystemState").
		\param flgEventType The type of the event as listed in the DSC_SecurityEventTypes enum (for example "Assignment").
		\param flgDataContainer The type of the data container argument that follows. All container types are listed in the DSC_DataContainers enum.
		\param ptrDataContainer The interface of the data container that contains properties relevant for the event.
    */
	virtual IRESULT ICALL OnGeneralNotificationHandler(IN DSC_ISecurityBase* ptrSender, 
		IN DSC_SecurityEventCategory flgEventCategory, IN DSC_SecurityEventType flgEventType,
		IN DSC_DataContainer flgDataContainer, IN DSC_IComponent* ptrDataContainer) = 0;


    //! Security Data / State Change event
    /*! This event is fired whenever the SDK detects a change in the system data or state. 
		For example if a Partition's "State" (arming level) changes.     */
    /*!	
		\sa DSC_IComponent
		\sa DSC_ISecurityBase
		\sa DSC_DataContainer
		\sa DSC_SecurityDataSelector
      	\param ptrSender The interface of the sender of the event (the Security Base).
		\param flgDataContainer The type of the data container argument that follows. All container types are listed in the DSC_DataContainers enum.
		\param ptrDataContainer The interface of the data container that contains properties listed in the list of selectors.
		\param tblDataSelectors The list of data selectors providing information on which properties of the container have been updated.
		\param numDataSelectors The number of the selectors in the list (the size of the list).
    */
	virtual IRESULT ICALL OnDataUpdateNotificationHandler(IN DSC_ISecurityBase* ptrSender, 
		IN DSC_DataContainer flgDataContainer, IN DSC_IComponent* ptrDataContainer, 
		IN DSC_SecurityDataSelector const* tblDataSelectors, IN DSC_SIZE_T numDataSelectors) = 0;
};

//---------------------------------------------------------------------------

/*!
	This is interface is used to receive event notifications from the DSC_ISecurityBase.
	This interface suprsedes the DSC_ISecurityEventSink interface that is now obsolete.	
	It must be implemented by the 3rd party software.
*/
DSC_INTERFACE DSC_ISecurityEventSink2 : public DSC_ISecurityEventSink
{
public:

    //! Security Data / State Change event
    /*! This event is fired whenever the SDK detects a change in the system data or state. 
		For example if a Partition's "State" (arming level) changes.     */
    /*!	
		\sa DSC_IComponent
		\sa DSC_ISecurityBase
		\sa DSC_DataContainer
		\sa DSC_SecurityDataSelector
      	\param ptrSender The interface of the sender of the event (the Security Base).
		\param flgDataContainer The type of the data container argument that follows. All container types are listed in the DSC_DataContainers enum.
		\param ptrDataContainer The interface of the data container that contains properties listed in the list of selectors.
		\param tblDataSelectors The list of data selectors providing information on which properties of the container have been updated.
		\param numDataSelectors The number of the selectors in the list (the size of the list).
		\param flgAuxDataContainer The 'type' of the auxiliary data container argument that follows.
		\param ptrAuxDataContainer The interface of the auxiliary data container that contains additional properties relevant for the event.
    */
	virtual IRESULT ICALL OnDataUpdateNotificationExtHandler(IN DSC_ISecurityBase* ptrSender, 
		IN DSC_DataContainer flgDataContainer, IN DSC_IComponent* ptrDataContainer, 
		IN DSC_SecurityDataSelector const* tblDataSelectors, IN DSC_SIZE_T numDataSelectors,
		IN DSC_DataContainer flgAuxDataContainer, IN DSC_IComponent* ptrAuxDataContainer) = 0;
};

//---------------------------------------------------------------------------
#else
//---------------------------------------------------------------------------

typedef struct DSC_ISecurityEventSink_Vtbl
{
	BEGIN_INTERFACE

	IRESULT (ICALL *Query)(IN DSC_ISecurityEventSink *This, IN char const* pszInterface, OUT VOID** ptrInterface);
	IRESULT (ICALL *Acquire)(IN DSC_ISecurityEventSink *This, OUT ICOUNT* ptrCount);
	IRESULT (ICALL *Release)(IN DSC_ISecurityEventSink *This, OUT ICOUNT* ptrCount);

	IRESULT (ICALL *OnGeneralNotificationHandler)(IN DSC_ISecurityEventSink *This, 
		IN DSC_ISecurityBase* ptrSender, 
		IN DSC_SecurityEventCategory flgEventCategory, IN DSC_SecurityEventType flgEventType,
		IN DSC_DataContainer flgDataContainer, IN DSC_IComponent* ptrDataContainer);
	IRESULT (ICALL *OnDataUpdateNotificationHandler)(IN DSC_ISecurityEventSink *This, 
		IN DSC_ISecurityBase* ptrSender, 
		IN DSC_DataContainer flgDataContainer, IN DSC_IComponent* ptrDataContainer, 
		IN DSC_SecurityDataSelector const* tblDataSelectors, IN DSC_SIZE_T numDataSelectors);

	END_INTERFACE
} DSC_ISecurityEventSink_Vtbl;

DSC_INTERFACE DSC_ISecurityEventSink
{
	//the assumption: the compiler places pointer to VTABLE first in the class layout
 	struct DSC_ISecurityEventSink_Vtbl *ptrVtbl;
};

//---------------------------------------------------------------------------

typedef struct DSC_ISecurityEventSink2_Vtbl
{
	BEGIN_INTERFACE

	IRESULT (ICALL *Query)(IN DSC_ISecurityEventSink2 *This, IN char const* pszInterface, OUT VOID** ptrInterface);
	IRESULT (ICALL *Acquire)(IN DSC_ISecurityEventSink2 *This, OUT ICOUNT* ptrCount);
	IRESULT (ICALL *Release)(IN DSC_ISecurityEventSink2 *This, OUT ICOUNT* ptrCount);

	IRESULT (ICALL *OnGeneralNotificationHandler)(IN DSC_ISecurityEventSink2 *This, 
		IN DSC_ISecurityBase* ptrSender, 
		IN DSC_SecurityEventCategory flgEventCategory, IN DSC_SecurityEventType flgEventType,
		IN DSC_DataContainer flgDataContainer, IN DSC_IComponent* ptrDataContainer);
	IRESULT (ICALL *OnDataUpdateNotificationHandler)(IN DSC_ISecurityEventSink2 *This, 
		IN DSC_ISecurityBase* ptrSender, 
		IN DSC_DataContainer flgDataContainer, IN DSC_IComponent* ptrDataContainer, 
		IN DSC_SecurityDataSelector const* tblDataSelectors, IN DSC_SIZE_T numDataSelectors);
	IRESULT (ICALL *OnDataUpdateNotificationExtHandler)(IN DSC_ISecurityEventSink2 *This, 
		IN DSC_ISecurityBase* ptrSender, 
		IN DSC_DataContainer flgDataContainer, IN DSC_IComponent* ptrDataContainer, 
		IN DSC_SecurityDataSelector const* tblDataSelectors, IN DSC_SIZE_T numDataSelectors,
		IN DSC_DataContainer flgAuxDataContainer, IN DSC_IComponent* ptrAuxDataContainer);

	END_INTERFACE
} DSC_ISecurityEventSink2_Vtbl;

DSC_INTERFACE DSC_ISecurityEventSink2
{
	//the assumption: the compiler places pointer to VTABLE first in the class layout
 	struct DSC_ISecurityEventSink2_Vtbl *ptrVtbl;
};

//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_I_SECURITY_EVENT_SINK_HPP_
