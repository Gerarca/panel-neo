//---------------------------------------------------------------------------
//
//	DSC_Parameters.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//	The list of parameter/data names and values used with the 
//	DSC_IDataStore interface.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_PARAMETERS_HPP_
#define _DSC_PARAMETERS_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
//---------------------------------------------------------------------------

//generic parameter names used by DSC_IDataStore
#define QUERY_CATEGORY			"Category"
#define QUERY_SELECTOR			"Selector"

//---------------------------------------------------------------------------

//query categories
#define QUERY_CATEGORY_ITV2					"ITV2"			//Protocol ID, will add for WSA etc.

//---------------------------------------------------------------------------

//generic query selectors
#define QUERY_SELECTOR_ACCOUNT_INFO			"AccountInfo"
#define QUERY_SELECTOR_DEVICE_INFO			"DeviceInfo"
#define QUERY_SELECTOR_CHANNEL_FUNCTION		"ChannelFunction"

//---------------------------------------------------------------------------

//ITV2 parameter names (must be single words)
//Strings needed for DSC_IDataStore.hpp "Keys for Data store"

#define ITV2_PARAM_CONNECTION			"ITV2_Connection"	//connection info (port number/name)
#define ITV2_PARAM_IDENTIFIER			"ITV2_Identifier"	//string before 7E/7F
#define ITV2_PARAM_INTEGRATION_ID		"ITV2_IntegrationID"//see ITV2 opensession
#define ITV2_PARAM_ACCESS_CODE			"ITV2_AccessCode"
#define ITV2_PARAM_KEY_CHANGE_TIME		"ITV2_KeyChangeTime"	//time in [s] for rotating session keys
#define ITV2_PARAM_STRICT_PROTOCOL		"ITV2_StrictProtocol"	//if 'TRUE' the strict ITV2 protocol is enforced

#define ITV2_PARAM_CHANNEL_FUNCTION		"ITV2_ChannelFunction"
#define ITV2_PARAM_FUNCTION_NO_FUNCTION		"ITV2_No_Function"		//the function has not been assigned
#define ITV2_PARAM_FUNCTION_POLLING_ONLY	"ITV2_Polling_Only"		//integration polling
#define ITV2_PARAM_FUNCTION_NOTIFICATIONS	"ITV2_Notifications"	//integration notifications
#define ITV2_PARAM_FUNCTION_POLL_AND_NOTIFY	"ITV2_Poll_Notify"		//integration "notifications follow poll"

#define ITV2_PARAM_DEVICE_TYPE			"ITV2_DeviceType"
#define ITV2_PARAM_DEVICE_ID			"ITV2_DeviceID"
#define ITV2_PARAM_SOFTWARE_VERSION		"ITV2_SoftwareVersion"
#define ITV2_PARAM_PROTOCOL_VERSION		"ITV2_ProtocolVersion"
#define ITV2_PARAM_TX_BUFFER_SIZE		"ITV2_TxBufferSize"
#define ITV2_PARAM_RX_BUFFER_SIZE		"ITV2_RxBufferSize"
#define ITV2_PARAM_FUTURE_USE			"ITV2_FutureUse"
#define ITV2_PARAM_ENCRYPTION_TYPE		"ITV2_EncryptionType"

//---------------------------------------------------------------------------
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_PARAMETERS_HPP_
