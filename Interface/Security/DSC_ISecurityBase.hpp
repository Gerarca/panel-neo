//---------------------------------------------------------------------------
//
//	DSC_ISecurityBase.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_IComponent.hpp"
#include "DSC_ISecurityEventSink.hpp"
#include "DSC_IChannel.hpp"
#include "DSC_IPartitionManager.hpp"
#include "DSC_ISystemManager.hpp"
#include "DSC_IAccessCredentials.hpp"
#include "DSC_ISpecificFunctions.hpp"
#include "DSC_ISystemInformation.hpp"
#include "DSC_ISystemCapabilities.hpp"
#include "DSC_IRepository.hpp"
#include "DSC_IRequestResult.hpp"
#include "DSC_ProtocolTypes.hpp"
#include "DSC_ITroubleList.hpp"

#ifndef _DSC_I_SECURITY_BASE_HPP_
#define _DSC_I_SECURITY_BASE_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#define NAME_DSC_ISecurityBase	"DSC_ISecurityBase"

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

/*!
	The SecurityBase is the virtual representation of the panel and the main interface used for interacting with it.
*/
DSC_INTERFACE DSC_ISecurityBase : public DSC_IComponent
{
public:
	
	//! Get the Protocol
    /*! Retrieves the protocol used to communicate with the panel. */
    /*!	
		\sa enum DSC_ProtocolType_Tag
     	\param result Pointer to storage for the Protocol Type.
    */
	virtual IRESULT ICALL get_Protocol(OUT DSC_ProtocolType* result) const = 0;

	//! Add Events
    /*! Adds the event handlers to the security base, allowing it to provide realtime notifications. */
    /*!	
		\sa DSC_ISecurityEventSink
     	\param ptrEventSink Provided DSC_ISecurityBaseEventSink interface containing the list of event handlers to connect.
    */
	virtual IRESULT ICALL add_EventSink(IN DSC_ISecurityEventSink* ptrEventSink) = 0;

	//! Remove Events
    /*! Removes the event handlers from the security base.     */
    /*!	
     	\param ptrEventSink Provided DSC_ISecurityBaseEventSink interface containing the list of event handlers to disconnect.
    */
	virtual IRESULT ICALL remove_EventSink(IN DSC_ISecurityEventSink* ptrEventSink) = 0;

    //! Add Communication Channel						  
    /*! Adds the communications interface to the securitybase, allowing the securitybase to communicate with the panel.     */
    /*!	
		\sa DSC_IChannel
      	\param ptrChannel Provided DSC_IChannel interface to assign to the securitybase.
    */
	virtual IRESULT ICALL add_Channel(IN DSC_IChannel* ptrChannel) = 0;

    //! Remove Communication Channel
    /*! Removes the communications interface from the securitybase, preventing the securitybase from communicating with the panel. */
    /*!	
		\sa DSC_IChannel
      	\param ptrChannel Provided DSC_IChannel interface to remove from the securitybase
    */
	virtual IRESULT ICALL remove_Channel(IN DSC_IChannel* ptrChannel) = 0;

    //! Get the Partition Manager
    /*! Retrieves the Partition Manager interface which allows access to the Partitions.    */
    /*!	
      	\param ptrManager Pointer to storage for the requested PartitionManager interface.
    */
	virtual IRESULT ICALL get_PartitionManager(OUT DSC_IPartitionManager** ptrManager) = 0;

    //! Get the SystemManager
    /*! Retrieves the System Manager interface which allows access to non-partitionable features and functions.     */
    /*!	
      	\param ptrManager Pointer to storage for the requested SystemManager interface.
    */
	virtual IRESULT ICALL get_SystemManager(OUT DSC_ISystemManager** ptrManager) = 0;

    //! Get InstallerCredentials
    /*! Retrieves the InstallerCredentials which is used for various SDK function calls.     */
    /*!	
		\sa DSC_IAccessCredentials
      	\param ptrCredentials Pointer to storage for the requested Installer AccessCredentials interface.
    */
	virtual IRESULT ICALL get_InstallerCredentials(OUT DSC_IAccessCredentials** ptrCredentials) = 0;

    //! Set InstallerCredentials
    /*! Sets the InstallerCredentials for use with various SDK function calls. */
    /*!	
		\sa DSC_IAccessCredentials
      	\param ptrCredentials Provided DSC_IAccessCredentials interface containing the InstallerCredentials to set.
    */
	virtual IRESULT ICALL set_InstallerCredentials(IN DSC_IAccessCredentials* ptrCredentials) = 0;

    //! Get General Purpose Tag
    /*! Retrieves the value of the Tag set by the user (provided for the user to store whatever they want).    */
    /*!	
      	\param ptrTag Pointer to storage for Tag
    */
	virtual IRESULT ICALL get_Tag(OUT VOID** ptrTag) const = 0;

    //! Set General Purpose Tag
    /*! Sets the Tag property. (provided for the user to store whatever they want).     */
    /*!	
      	\param ptrTag Provided value to store in the Tag
    */
	virtual IRESULT ICALL set_Tag(IN VOID* ptrTag) = 0;

    //! Process the internal state of the SecurityBase
    /*! External periodic call required by the SecruityBase to perform necessary internal processing.     */
    /*!	
    */
	virtual IRESULT ICALL ProcessState(VOID) = 0;

    //! Get the number of channels currently assigned to the Security Base
    /*! Retrieves the number of communication channels currently assigned to the Security Base.   */
    /*!	
      	\param ptrCount Pointer to storage for the number of assigned channels.
    */
	virtual IRESULT ICALL get_NumberOfChannels(OUT DSC_SIZE_T* ptrCount)  const = 0;

    //! Get a Channel interface
    /*! Retrieves a Channel interface. This is a 0 based list index, NOT a system index.      */
    /*!	
		\sa DSC_IChannel
      	\param numIndex Requested 0 based list index of the channel interface to get.
		\param ptrChannel Pointer to storage for the requested channel interface.
    */
	virtual IRESULT ICALL get_Channel(IN DSC_SIZE_T numIndex, OUT DSC_IChannel** ptrChannel) = 0;

	//! Get SpecificFunctions interface
    /*! Retrieves a SpecificFunctions interface, which provides product specific functionality.      */
    /*!	
		\sa DSC_ISpecificFunctions
		\param ptrSpecificFunctions Pointer to storage for the specific functions interface.
    */
	virtual IRESULT ICALL get_SpecificFunctions(OUT DSC_ISpecificFunctions** ptrSpecificFunctions) = 0;

	//! Get the PeerIdentifier
    /*!	Depending on the data exchange protocol the peer device can provide its Peer Identifier information. 
		(eg. for ITV2 the PeerIdentifier is the Integration ID)	*/
    /*! 
		\sa DSC_ITextString
     	\param ptrTextString Pointer to the storage for the returned DSC_ITextString interface.
    */
	virtual IRESULT ICALL get_PeerIdentifier(OUT DSC_ITextString** ptrTextString) const = 0;

	//! Get ReadyToUse
    /*! Retrieves the status indicating whether or not the SecurityBase is ready to communicate with the panel. */
    /*!	
		\param ptrIsReady Pointer to storage for the IsReady status.
    */
	virtual IRESULT ICALL get_ReadyToUse(OUT BOOL* ptrIsReady) const = 0;

	//! Read System Information
    /*! Queries the panel for information. The system information includes 
		things like the product ID, software version, protocol version, etc.      */
    /*!	
		\sa DSC_ISystemInformation
		\param ptrSystemInformation Pointer to storage for the system information interface.
		\param ptrRequestResult Pointer to storage for the result of the operation.
    */
	virtual IRESULT ICALL ReadSystemInformation(
		OUT DSC_ISystemInformation** ptrSystemInformation, 
		OUT DSC_IRequestResult** ptrRequestResult) = 0;

	//! Read System Capabilities
    /*! Queries the panel for its capabilities. The system capabilities of the panel includes things like 
		the maximum number of supported partitions, zones, users, etc.      */
    /*!	
		\sa DSC_ISystemCapabilities
		\param ptrSystemCapabilities Pointer to storage for the system capabilities interface.
		\param ptrRequestResult Pointer to storage for the result of the operation.
    */
	virtual IRESULT ICALL ReadSystemCapabilities(
		OUT DSC_ISystemCapabilities** ptrSystemCapabilities, 
		OUT DSC_IRequestResult** ptrRequestResult) = 0;

	//! Get Repository
    /*! Retrieves the interface containing functions for accessing data stored in the SDK's internal repository.      */
    /*!	
		\sa DSC_IRepository
		\param ptrRepository Pointer to storage for the Repository interface.
    */
	virtual IRESULT ICALL get_Repository(OUT DSC_IRepository** ptrRepository) = 0;

	//! Get Trouble Information
    /*! Queries the panel for its trouble information. The troubles include things such as low battery,
		zone fault, module tamper,  etc. */
    /*!	
		\sa DSC_ITroubleList
		\param ptrTroubleList Pointer to storage for the TroubleList interface.
		\param ptrRequestResult Pointer to storage for the result of the operation.
    */
	virtual IRESULT ICALL ReadTroubleInformation(
		OUT DSC_ITroubleList** ptrTroubleList, 
		OUT DSC_IRequestResult** ptrRequestResult) = 0;
};

#else

typedef struct DSC_ISecurityBase_Vtbl
{
	BEGIN_INTERFACE

	IRESULT (ICALL *Query)(IN DSC_ISecurityBase *This, IN char const* pszInterface, OUT VOID** ptrInterface);
	IRESULT (ICALL *Acquire)(IN DSC_ISecurityBase *This, OUT ICOUNT* ptrCount);
	IRESULT (ICALL *Release)(IN DSC_ISecurityBase *This, OUT ICOUNT* ptrCount);

	IRESULT (ICALL *get_Protocol)(IN DSC_ISecurityBase *This, OUT DSC_ProtocolType* result);
	IRESULT (ICALL *add_EventSink)(IN DSC_ISecurityBase *This, IN DSC_ISecurityEventSink* ptrEventSink);
	IRESULT (ICALL *remove_EventSink)(IN DSC_ISecurityBase *This, IN DSC_ISecurityEventSink* ptrEventSink);
	IRESULT (ICALL *add_Channel)(IN DSC_ISecurityBase *This, IN DSC_IChannel* ptrChannel);
	IRESULT (ICALL *remove_Channel)(IN DSC_ISecurityBase *This, IN DSC_IChannel* ptrChannel);
	IRESULT (ICALL *get_PartitionManager)(IN DSC_ISecurityBase *This, OUT DSC_IPartitionManager** ptrManager);
	IRESULT (ICALL *get_SystemManager)(IN DSC_ISecurityBase *This, OUT DSC_ISystemManager** ptrManager);
	IRESULT (ICALL *get_InstallerCredentials)(IN DSC_ISecurityBase *This, OUT DSC_IAccessCredentials** ptrCredentials);
	IRESULT (ICALL *set_InstallerCredentials)(IN DSC_ISecurityBase *This, IN DSC_IAccessCredentials* ptrCredentials);
	IRESULT (ICALL *get_Tag)(IN DSC_ISecurityBase *This, OUT VOID** ptrTag);
	IRESULT (ICALL *set_Tag)(IN DSC_ISecurityBase *This, IN VOID* ptrTag);
	IRESULT (ICALL *ProcessState)(IN DSC_ISecurityBase *This);
	IRESULT (ICALL *get_NumberOfChannels)(IN DSC_ISecurityBase *This, OUT DSC_SIZE_T* ptrCount);
	IRESULT (ICALL *get_Channel)(IN DSC_ISecurityBase *This, IN DSC_SIZE_T numIndex, OUT DSC_IChannel** ptrChannel);
	IRESULT (ICALL *get_SpecificFunctions)(IN DSC_ISecurityBase *This, OUT DSC_ISpecificFunctions** ptrSpecificFunctions);
	IRESULT (ICALL *get_PeerIdentifier)(IN DSC_ISecurityBase *This, OUT DSC_ITextString** ptrTextString);
	IRESULT (ICALL *get_ReadyToUse)(IN DSC_ISecurityBase *This, OUT BOOL* ptrIsReady);
	IRESULT (ICALL *ReadSystemInformation)(IN DSC_ISecurityBase *This, 
		OUT DSC_ISystemInformation** ptrSystemInformation, OUT DSC_IRequestResult** ptrRequestResult);
	IRESULT (ICALL *ReadSystemCapabilities)(IN DSC_ISecurityBase *This, 
		OUT DSC_ISystemCapabilities** ptrSystemCapabilities, OUT DSC_IRequestResult** ptrRequestResult);
	IRESULT (ICALL *get_Repository)(IN DSC_ISecurityBase *This, OUT DSC_IRepository** ptrRepository);
	IRESULT (ICALL *ReadTroubleInformation)(IN DSC_ISecurityBase *This, 
		OUT DSC_ITroubleList** ptrTroubleList, OUT DSC_IRequestResult** ptrRequestResult);

	END_INTERFACE
} DSC_ISecurityBase_Vtbl;

DSC_INTERFACE DSC_ISecurityBase
{
	//the assumption: the compiler places pointer to VTABLE first in the class layout
 	struct DSC_ISecurityBase_Vtbl *ptrVtbl;
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

#endif	//_DSC_I_SECURITY_BASE_HPP_
