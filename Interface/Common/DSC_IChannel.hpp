//---------------------------------------------------------------------------
//
//	DSC_IChannel.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//	The interface for implementing communication channels.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_IComponent.hpp"
#include "DSC_IChannelEventSink.hpp"
#include "DSC_IDataStore.hpp"
#include "DSC_IBlockCipher.hpp"
#include "DSC_ProtocolTypes.hpp"
#include "DSC_CipherTypes.hpp"

#ifndef _DSC_I_CHANNEL_HPP_
#define _DSC_I_CHANNEL_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
//---------------------------------------------------------------------------

//The channel component implementation must be thread safe. Only a single
//protocol is supported by a channel at any given time (1:1 correspondence).
#define NAME_DSC_IChannel	"DSC_IChannel"

//---------------------------------------------------------------------------

#ifndef DSC_IChannelEventSink_FWD_DEFINED
#define DSC_IChannelEventSink_FWD_DEFINED
typedef DSC_INTERFACE DSC_IChannelEventSink DSC_IChannelEventSink;
#endif

#ifndef DSC_IChannel_FWD_DEFINED
#define DSC_IChannel_FWD_DEFINED
typedef DSC_INTERFACE DSC_IChannel DSC_IChannel;
#endif

//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

/*!
	This is the main interface used to stream data bytes between the SDK
	and the external world. (The channel component implementation must be thread safe.
	Only a single protocol is supported by a channel at any given time.) 
*/
DSC_INTERFACE DSC_IChannel : public DSC_IDataStore
{
public:

	//***************************************************
	//
	//	Events
	//
	//***************************************************

	//! This function is used to attach the event handlers interface for communicating channel events.
    /*!	
		\sa DSC_IChannelEventSink
     	\param ptrEventSink Pointer to the DSC_IChannelEventSink interface 
    */
	virtual IRESULT ICALL add_EventSink(IN DSC_IChannelEventSink* ptrEventSink) = 0;

	//! This function is used to dettach the event handlers interface for communicating channel events.
    /*!	
		\sa DSC_IChannelEventSink
     	\param ptrEventSink Pointer to the DSC_IChannelEventSink interface 
    */
	virtual IRESULT ICALL remove_EventSink(IN DSC_IChannelEventSink* ptrEventSink) = 0;

	//***************************************************
	//
	//	Properties
	//
	//***************************************************

	//! This property is used to obtain the information on the communication protocol used by the channel.
    /*!	
		\sa enum DSC_ProtocolType_Tag
     	\param result Pointer to DSC_ProtocolType member.
    */
	virtual IRESULT ICALL get_Protocol(OUT DSC_ProtocolType* result) const = 0;

	//! This property is used to obtain the peer device identification information.
    /*! 
		The channel can sometimes obtain the Peer Identifier from the received data packets depending on the protocol. 
		However, if that information is not available, the Peer Identifier has to be preset using the set_PeerIdentifier. 

		\sa DSC_ITextString
     	\param ptrTextString Pointer to DSC_ITextString member.
    */
	virtual IRESULT ICALL get_PeerIdentifier(OUT DSC_ITextString** ptrTextString) const = 0;

	//! This property is used to preset the peer device identification information.
    /*! 
		It is used in cases where the peer device does not identify itself throught the protocol.

     	\param pszTextString Pointer to UTF8 text string containing the peer identifier.
    */
	virtual IRESULT ICALL set_PeerIdentifier(IN char const* pszTextString) = 0;

	//! This property is used to obtain additional connection information stored by the DSC_IChannel.
    /*!	
     	\param ptrTextString Pointer to DSC_ITextString member.
    */
	virtual IRESULT ICALL get_ConnectionInfo(OUT DSC_ITextString** ptrTextString) const = 0;

	//! This property is used to store additional connection information in the DSC_IChannel.
    /*!	
     	\param pszTextString Pointer to UTF8 text string containing the connection information.
    */
	virtual IRESULT ICALL set_ConnectionInfo(IN char const* pszTextString) = 0;

	//! This property is used to obtain the DSC_IChannel's status flags.
    /*!      */
    /*!	
     	\param result Pointer to DSC_CHANNEL_STATE_FLAGS member. The status flags are defined in DSC_ChannelStates enum
    */
	virtual IRESULT ICALL get_StatusFlags(OUT DSC_CHANNEL_STATE_FLAGS* result) const = 0;

	//! This property is used to get the interface to the DataStore.
    /*! 
		The DataStore keeps all the information that a channel may need in order to 
		process the incoming data. This includes any applicable encryption keys, account information, etc.

		\sa DSC_IDataStore
     	\param ptrDataStore Pointer to DSC_IDataStore.
    */
	virtual IRESULT ICALL get_DataStore(OUT DSC_IDataStore** ptrDataStore) = 0;

	//! This property is used to set the interface to the DataStore.
    /*! 
		The DataStore keeps all the information that a channel may need in order to p
		rocess the incoming data. This includes any applicable encryption keys, account information, etc.

		\sa DSC_IDataStore
     	\param ptrDataStore Pointer to DSC_IDataStore.
    */
	virtual IRESULT ICALL set_DataStore(IN DSC_IDataStore* ptrDataStore) = 0;

	//! This property is used to get the Receive Timeout value in seconds.
    /*! 
		This timeout is used for detecting and notifying the user that there is no incoming traffic.

     	\param result Pointer to UINT16.
    */
	virtual IRESULT ICALL get_RxIdleTimeout(OUT UINT16* result) const = 0;

	//! This property is used to set the Receive Timeout value in seconds.
    /*! 
		This timeout is used for detecting and notifying the user that there is no incoming traffic.

     	\param value Pointer to UINT16.
    */
	virtual IRESULT ICALL set_RxIdleTimeout(IN UINT16 value) = 0;

	//! This property is used to get the Transmit Timeout value in seconds.
    /*! 
		This timeout is used for detecting and notifying the user that there is no outgoing traffic.

     	\param result Pointer to UINT16.
    */
	virtual IRESULT ICALL get_TxIdleTimeout(OUT UINT16* result) const = 0;

	//! This property is used to set the Transmit Timeout value in seconds.
    /*! 
		This timeout is used for detecting and notifying the user that there is no outgoing traffic.

     	\param value Pointer to UINT16.
    */
	virtual IRESULT ICALL set_TxIdleTimeout(IN UINT16 value) = 0;

	//! This property is used to get the Transmit Retry Delay value in seconds.
    /*! 
		The delay time before any transmission is repeated, if no "ACK" was received.

     	\param result Pointer to UINT16.
    */
	virtual IRESULT ICALL get_TxRetryDelay(OUT UINT16* result) const = 0;

	//! This property is used to set the Transmit Retry Delay value in seconds.
    /*! 
		The delay time before any transmission is repeated, if no "ACK" was received.

     	\param value Pointer to UINT16.
    */
	virtual IRESULT ICALL set_TxRetryDelay(IN UINT16 value) = 0;

	//! This property is used to get the Transmit Retry Count.
    /*! 
		Used to specify the maximum tansmission retry count. The value 0 means that there will be no retries.

     	\param result Pointer to UINT16.
    */
	virtual IRESULT ICALL get_TxRetryCount(OUT UINT16* result) const = 0;

	//! This property is used to set the Transmit Retry Count.
    /*! 
		Used to specify the maximum transmission retry count. The value 0 means that there will be no retries.

     	\param value Pointer to UINT16.
    */
	virtual IRESULT ICALL set_TxRetryCount(IN UINT16 value) = 0;

	//! This property is used to get the "Tag" data.
    /*! 
		Used to "tag" / store any 3rd party custom data to the channel so it can be linked with other components.

     	\param ptrTag Pointer to the tagged data.
    */
	virtual IRESULT ICALL get_Tag(OUT VOID** ptrTag) const = 0;

	//! This property is used to set the "Tag" data.
    /*! 
		Used to "tag" / store any 3rd party custom data to the channel so it can be linked with other components.

     	\param ptrTag Pointer to the tagged data.
    */
	virtual IRESULT ICALL set_Tag(IN VOID* ptrTag) = 0;

	//***************************************************
	//
	//	Methods
	//
	//***************************************************

	//! This function is used to register a block cipher needed for encrypting and decrypting the data traffic.
    /*! 
		An attempt to register a block cipher of the type that has already been registered results in 
		replacing the currently registered cipher with the new one. 
		If the ptrCipher value is NULL, any currently registered cipher of given flgType will be unregistered. 
		Note: More than one block cipher can be registered with	the channel.

		\sa enum DSC_CipherType_Tag
		\sa DSC_IBlockCipher
     	\param flgType The cipher type identificator.
     	\param ptrCipher Pointer to the cipher component (may be NULL).
    */
	virtual IRESULT ICALL SetBlockCipher(
		IN DSC_CipherType flgType, IN DSC_IBlockCipher* ptrCipher) = 0;

	//! This function is used to open the channel.
    /*!	
     	\param pszArguments Pointer to the list of arguments required to open the channel, the format depends on the given type of channel.
    */
	virtual IRESULT ICALL OpenChannel(char const* pszArguments) = 0;

	//! This function is used to close the channel.
    /*! 
		A channel must be closed before the component is released, otherwise memory leaks or other unpredictable behavior may occur.
    */
	virtual IRESULT ICALL CloseChannel(VOID) = 0;

	//! This function is used to reset the channel.
    /*! 
		Used to reset the channel state without closing and re-opening it.
    */
	virtual IRESULT ICALL ResetChannel(VOID) = 0;

	//! This function must be called periodically to allow the SDK to perform internal data processing.
    /*! 
		The SDK avoids creating any threads internally allowing the 3rd party developer full control of resources.
		As a result, 3rd party code MUST! call ProcessState on a regular basis. This can be used as a throtteling option
		to balance CPU load vs end user experiance. 
		Calling ProcessState between 10mS and 100mS typically provides a smooth and responsive user experiance.
    */
	virtual IRESULT ICALL ProcessState(VOID) = 0;

	//! This function is used to process the incoming data.
    /*! 
		When new data is received by 3rd party developers it must be passed into the SDK using this function.

     	\param bufData Pointer to the buffer containing the incoming data.
     	\param numSize The number of bytes available in the buffer.
     	\param ptrCount Pointer to the variable that will receive the number of bytes written into the channel for processing
    */
	virtual IRESULT ICALL ReceiveRawData(
		IN BYTE const* bufData, IN DSC_SIZE_T numSize, OUT DSC_SIZE_T* ptrCount) = 0;

	//! This function is used internally by the SDK to send data packets.
    /*! 
		It is recommended that this function not NOT used by 3rd party software, 
		unless in some isolated cases of very intensive debugging.

		\sa DSC_IProtocolData
     	\param ptrPacket Pointer to the data packet interface.
     	\param numTimeout Command expiration timeout in seconds.
    */
	virtual IRESULT ICALL SendDataPacket(
		IN DSC_IProtocolData* ptrPacket, IN BYTE numTimeout) = 0;

	//! This function is used the SDK to send raw payload.
    /*! 
		The payload to be sent will be wrapped in proper protocol frame.
		The payload must conform to the given data exchange protocol.

     	\param bufData Pointer to the buffer containing the payload data.
     	\param numSize The number of bytes available in the buffer.
     	\param numTimeout Command expiration timeout in seconds.
		\param ptrPacket Optional pointer to the data packet interface storage (the DSC_IProtocolData interface must be relased when no longer needed).
    */
	virtual IRESULT ICALL SendRawPayload(
		IN BYTE const* bufData, IN DSC_SIZE_T numSize, IN BYTE numTimeout, 
		OUT DSC_IProtocolData** ptrPacket) = 0;
};

#else

typedef struct DSC_IChannel_Vtbl
{
	BEGIN_INTERFACE

	IRESULT (ICALL *Query)(IN DSC_IChannel *This, IN char const* pszInterface, OUT VOID** ptrInterface);
	IRESULT (ICALL *Acquire)(IN DSC_IChannel *This, OUT ICOUNT* ptrCount);
	IRESULT (ICALL *Release)(IN DSC_IChannel *This, OUT ICOUNT* ptrCount);

	IRESULT (ICALL *SelectData)(IN DSC_IChannel *This,  
		IN char const* pszParams, OUT DSC_ITextString** ptrResult);
	IRESULT (ICALL *InsertData)(IN DSC_IChannel *This,  
		IN char const* pszParams, OUT DSC_SIZE_T* ptrResult);
	IRESULT (ICALL *UpdateData)(IN DSC_IChannel *This,  
		IN char const* pszParams, OUT DSC_SIZE_T* ptrResult);
	IRESULT (ICALL *DeleteData)(IN DSC_IChannel *This, 
		IN char const* pszParams, OUT DSC_SIZE_T* ptrResult);

	IRESULT (ICALL *add_EventSink)(IN DSC_IChannel *This, IN DSC_IChannelEventSink* ptrEventSink);
	IRESULT (ICALL *remove_EventSink)(IN DSC_IChannel *This, IN DSC_IChannelEventSink* ptrEventSink);

	IRESULT (ICALL *get_Protocol)(IN DSC_IChannel *This, OUT DSC_ProtocolType* result);
	IRESULT (ICALL *get_PeerIdentifier)(IN DSC_IChannel *This, OUT DSC_ITextString** ptrTextString);
	IRESULT (ICALL *set_PeerIdentifier)(IN DSC_IChannel *This, IN char const* pszTextString);
	IRESULT (ICALL *get_ConnectionInfo)(IN DSC_IChannel *This, OUT DSC_ITextString** ptrTextString);
	IRESULT (ICALL *set_ConnectionInfo)(IN DSC_IChannel *This, IN char const* pszTextString);
	IRESULT (ICALL *get_StatusFlags)(IN DSC_IChannel *This, OUT DSC_CHANNEL_STATE_FLAGS* result);
	IRESULT (ICALL *get_DataStore)(IN DSC_IChannel *This, OUT DSC_IDataStore** ptrDataStore);
	IRESULT (ICALL *set_DataStore)(IN DSC_IChannel *This, IN DSC_IDataStore* ptrDataStore);
	IRESULT (ICALL *get_RxIdleTimeout)(IN DSC_IChannel *This, OUT UINT16* result);
	IRESULT (ICALL *set_RxIdleTimeout)(IN DSC_IChannel *This, IN UINT16 value);
	IRESULT (ICALL *get_TxIdleTimeout)(IN DSC_IChannel *This, OUT UINT16* result);
	IRESULT (ICALL *set_TxIdleTimeout)(IN DSC_IChannel *This, IN UINT16 value);
	IRESULT (ICALL *get_TxRetryDelay)(IN DSC_IChannel *This, OUT UINT16* result);
	IRESULT (ICALL *set_TxRetryDelay)(IN DSC_IChannel *This, IN UINT16 value);
	IRESULT (ICALL *get_TxRetryCount)(IN DSC_IChannel *This, OUT UINT16* result);
	IRESULT (ICALL *set_TxRetryCount)(IN DSC_IChannel *This, IN UINT16 value);
	IRESULT (ICALL *get_Tag)(IN DSC_IChannel *This, OUT VOID** ptrTag);
	IRESULT (ICALL *set_Tag)(IN DSC_IChannel *This, IN VOID* ptrTag);

	IRESULT (ICALL *SetBlockCipher)(IN DSC_IChannel *This, 
		IN DSC_CipherType flgType, IN DSC_IBlockCipher* ptrCipher);
	IRESULT (ICALL *OpenChannel)(IN DSC_IChannel *This, char const* pszArguments);
	IRESULT (ICALL *CloseChannel)(IN DSC_IChannel *This);
	IRESULT (ICALL *ResetChannel)(IN DSC_IChannel *This);
	IRESULT (ICALL *ProcessState)(IN DSC_IChannel *This);
	IRESULT (ICALL *ReceiveRawData)(IN DSC_IChannel *This, 
		IN BYTE const* bufData, IN DSC_SIZE_T numSize, OUT DSC_SIZE_T* ptrCount);
	IRESULT (ICALL *SendDataPacket)(IN DSC_IChannel *This, 
		IN DSC_IProtocolData* ptrPacket, IN BYTE numTimeout);
	IRESULT (ICALL *SendRawPayload)(IN DSC_IChannel *This, 
		IN BYTE const* bufData, IN DSC_SIZE_T numSize, IN BYTE numTimeout, 
		OUT DSC_IProtocolData** ptrPacket);

	END_INTERFACE
} DSC_IChannel_Vtbl;

DSC_INTERFACE DSC_IChannel
{
	//the assumption: the compiler places pointer to VTABLE first in the class layout
 	struct DSC_IChannel_Vtbl *ptrVtbl;
};

#endif

//---------------------------------------------------------------------------
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_I_CHANNEL_HPP_
