//---------------------------------------------------------------------------
//
//	DSC_ChannelErrors.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//	The list of various error codes reported by the channel.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_CHANNEL_ERRORS_HPP_
#define _DSC_CHANNEL_ERRORS_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_ChannelErrors {
/*! 
	The list of various error codes reported by the DSC_IChannel. 
*/
enum DSC_ChannelError_Tag {

	No_Errors						= 0,	/**< no errors - must be 0! */

	Missing_Data_Store				= 10,	/**< required data store reference is missing */
	Cant_Build_Request				= 11,	/**< cannot build the data store request */
	Cant_Execute_Query				= 12,	/**< cannot execute the data store query */
	Missing_Query_Data				= 13,	/**< missing query data (request and/or response) */
	Invalid_Query_Data				= 14,	/**< invalid query data (unknown or wrong data value) */

	Unknown_Peer_Identifier			= 20,	/**< the peer info is not available (has not been found) */
	Invalid_Peer_Identifier			= 21,	/**< the received identifier doesn't match the peer info assigned to the channel */
	Peer_Info_Query_Failure			= 22,	/**< querrying for the peer info failed */
	Encryption_Key_Too_Short		= 23,	/**< the encryption key or the seed used to generate the encryption key is too short */
	Encryption_Key_Too_Long			= 24,	/**< the encryption key or the seed used to generate the encryption key is too long */

	Invalid_Packet_Received			= 30,	/**< the received packet is invalid (corrupted or unknown format) */
	Invalid_Packet_Sequence			= 31,	/**< the packet was received out of the expected sequence */
	Invalid_Packet_Contents			= 33,	/**< the packet contents is wrong or invalid */
	Unknown_Packet_Contents			= 34,	/**< the packet contents appears to be valid but is unknown */
	Invalid_Packet_Size				= 35,	/**< the packet size is invalid - the packet cannot be processed */
	Unknown_Packet_Type				= 36,	/**< the packet type is unknown - the packet cannot be processed */

	Data_Container_Failure			= 40,	/**< cannot create appropriate data container for the packet data */
	Property_Getter_Failed			= 41,	/**< cannot get data container's property value */
	Property_Setter_Failed			= 42,	/**< cannot set data container's property value */

	Unknown_Encryption_Type			= 50,	/**< encryption type (scheme) is unknown */
	Encryption_Failure				= 51,	/**< encryption failed (not enough memory, bad key or IV, etc.) */
	Decryption_Failure				= 52,	/**< decryption failed (not enough memory, bad key or IV, etc.) */
	Serialization_Failure			= 53,	/**< cannot serialize the packet data */
	Deserialization_Failure			= 54,	/**< cannot deserialize the packet data */

	Cant_Parse_Packet_Contents		= 60,	/**< cannot parse the data packet (i.e. not enough memory or bad formatting) */
	Cant_Build_Packet_Contents		= 61,	/**< cannot build/assemble the data packet (i.e. not enough memory) */
	Cant_Frame_Packet_Contents		= 62,	/**< cannot build the packet frame (i.e. not enough memory) */

	Cant_Prepare_Data_Request		= 70,	/**< cannot prepare arguments for the data request packet to be sent */
	Cant_Process_Data_Request		= 71,	/**< cannot process arguments of the received data request packet */
	Cant_Send_Data_Request			= 72,	/**< cannot send data request packet */
	Data_Request_Was_Rejected		= 73,	/**< previously sent data request was rejected */
	Cant_Save_Data_Request			= 74,	/**< previously sent data request cannot be saved locally */
	Data_Request_Timed_Out			= 75,	/**< previously sent data request received no response */
	Missing_Data_Request			= 76,	/**< previously sent data request is not longer available */

	Sender_Buffer_Is_Full			= 80,	/**< data packet cannot be added to the sender's buffer */
	Cant_Schedule_Sending			= 81,	/**< data packet was not added to the sender's buffer */
	Packet_Sending_Failed			= 82,	/**< couldn't send the data packet or its reception was not acknowledged */

	Unsupported_Peer_Device			= 90,	/**< the peer deveice is not supported */
	Unsupported_Protocol_Version	= 91,	/**< the protocol version is not supported */
	Unsupported_Software_Version	= 92,	/**< the product software version is not supported */
	Unsupported_Encryption_Type		= 93,	/**< the encryption type is not supported */

	OpenSession_Rejected			= 100,	/**< the OpenSession command was rejected by the peer */
	RequestAccess_Rejected			= 101	/**< the RequestAccess command was rejected by the peer */

}; }

#else

#define DSC_ChannelErrors(value)	(DSC_E01_##value)
enum DSC_ChannelError_Tag {

	DSC_E01_No_Errors						= 0,	/**< no errors - must be 0! */

	DSC_E01_Missing_Data_Store				= 10,	/**< required data store reference is missing */
	DSC_E01_Cant_Build_Request				= 11,	/**< cannot build the data store request */
	DSC_E01_Cant_Execute_Query				= 12,	/**< cannot execute the data store query */
	DSC_E01_Missing_Query_Data				= 13,	/**< missing query data (request and/or response) */
	DSC_E01_Invalid_Query_Data				= 14,	/**< invalid query data (unknown or wrong data value) */

	DSC_E01_Unknown_Peer_Identifier			= 20,	/**< the peer info is not available (has not been found) */
	DSC_E01_Invalid_Peer_Identifier			= 21,	/**< the received identifier doesn't match the peer info assigned to the channel */
	DSC_E01_Peer_Info_Query_Failure			= 22,	/**< querrying for the peer info failed */
	DSC_E01_Encryption_Key_Too_Short		= 23,	/**< the encryption key or the seed used to generate the encryption key is too short */
	DSC_E01_Encryption_Key_Too_Long			= 24,	/**< the encryption key or the seed used to generate the encryption key is too long */

	DSC_E01_Invalid_Packet_Received			= 30,	/**< the received packet is invalid (corrupted or unknown format) */
	DSC_E01_Invalid_Packet_Sequence			= 31,	/**< the packet was received out of the expected sequence */
	DSC_E01_Invalid_Packet_Contents			= 33,	/**< the packet contents is wrong or invalid */
	DSC_E01_Unknown_Packet_Contents			= 34,	/**< the packet contents appears to be valid but is unknown */
	DSC_E01_Invalid_Packet_Size				= 35,	/**< the packet size is invalid - the packet cannot be processed */
	DSC_E01_Unknown_Packet_Type				= 36,	/**< the packet type is unknown - the packet cannot be processed */

	DSC_E01_Data_Container_Failure			= 40,	/**< cannot create appropriate data container for the packet data */
	DSC_E01_Property_Getter_Failed			= 41,	/**< cannot get data container's property value */
	DSC_E01_Property_Setter_Failed			= 42,	/**< cannot set data container's property value */

	DSC_E01_Unknown_Encryption_Type			= 50,	/**< encryption type (scheme) is unknown */
	DSC_E01_Encryption_Failure				= 51,	/**< encryption failed (not enough memory, bad key or IV, etc.) */
	DSC_E01_Decryption_Failure				= 52,	/**< decryption failed (not enough memory, bad key or IV, etc.) */
	DSC_E01_Serialization_Failure			= 53,	/**< cannot serialize the packet data */
	DSC_E01_Deserialization_Failure			= 54,	/**< cannot deserialize the packet data */

	DSC_E01_Cant_Parse_Packet_Contents		= 60,	/**< cannot parse the data packet (i.e. not enough memory or bad formatting) */
	DSC_E01_Cant_Build_Packet_Contents		= 61,	/**< cannot build/assemble the data packet (i.e. not enough memory) */
	DSC_E01_Cant_Frame_Packet_Contents		= 62,	/**< cannot build the packet frame (i.e. not enough memory) */

	DSC_E01_Cant_Prepare_Data_Request		= 70,	/**< cannot prepare arguments for the data request packet to be sent */
	DSC_E01_Cant_Process_Data_Request		= 71,	/**< cannot process arguments of the received data request packet */
	DSC_E01_Cant_Send_Data_Request			= 72,	/**< cannot send data request packet */
	DSC_E01_Data_Request_Was_Rejected		= 73,	/**< previously sent data request was rejected */
	DSC_E01_Cant_Save_Data_Request			= 74,	/**< previously sent data request cannot be saved locally */
	DSC_E01_Data_Request_Timed_Out			= 75,	/**< previously sent data request received no response */
	DSC_E01_Missing_Data_Request			= 76,	/**< previously sent data request is not longer available */

	DSC_E01_Sender_Buffer_Is_Full			= 80,	/**< data packet cannot be added to the sender's buffer */
	DSC_E01_Cant_Schedule_Sending			= 81,	/**< data packet was not added to the sender's buffer */
	DSC_E01_Packet_Sending_Failed			= 82,	/**< couldn't send the data packet or its reception was not acknowledged */

	DSC_E01_Unsupported_Peer_Device			= 90,	/**< the peer deveice is not supported */
	DSC_E01_Unsupported_Protocol_Version	= 91,	/**< the protocol version is not supported */
	DSC_E01_Unsupported_Software_Version	= 92,	/**< the product software version is not supported */
	DSC_E01_Unsupported_Encryption_Type		= 93,	/**< the encryption type is not supported */

	DSC_E01_OpenSession_Rejected			= 100,	/**< the OpenSession command was rejected by the peer */
	DSC_E01_RequestAccess_Rejected			= 101	/**< the RequestAccess command was rejected by the peer */

};

#endif

/*! 
	The DSC_ChannelError data type corresponds with the enum DSC_ChannelError_Tag.

	\sa enum DSC_ChannelError_Tag
*/
typedef DSC_ENUM_T DSC_ChannelError;

//---------------------------------------------------------------------------
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_CHANNEL_ERRORS_HPP_
