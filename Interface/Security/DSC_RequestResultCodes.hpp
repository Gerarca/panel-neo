//---------------------------------------------------------------------------
//
//	DSC_RequestResultCodes.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_REQUEST_RESULT_CODES_HPP_
#define _DSC_REQUEST_RESULT_CODES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_RequestResultCodes {
/*!
	The SDK provides access to Read and Write result values as described below.

	Result codes for SDK options requests.
	Most values are self-explanatory based on the requested SDK operation.
*/
enum DSC_RequestResultCode_Tag {

	// 0-4095
	Common_NotAvailable							= -1,		/**< Reserved value. It indicates that this value is not available on the product. */
	Common_Unknown								= 0,		/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */

	Common_Success								= 1,		/**< The requested operation succeeded. */
	Common_InvalidUserCredentials				= 2,		/**< The provided user credentials was invalid. */
	Common_InvalidInstallerCredentials			= 3,		/**< The provided installer credentials was invalid. */
	Common_UserCredentialsRequired              = 4,		/**< The operation requested requires user credentials to be provided. */
	Common_FunctionNotAvailable					= 5,		/**< The operation requested is not supported. */
	Common_UnrecognizedResultCode               = 6,        /**< The operation requested yielded an unrecognized response code. */
	Common_InvalidInstance						= 7,		/**< The current instance of the interface is no longer valid. Please re-request the interface again. */

	// 4096-5119
	Target_SystemIsLockedOut					= 4096,		/**< The system is locked out and not available at this time. */
	Target_PowerUpShuntInEffect					= 4097,		/**< The system is powering up / initializing. */
	Target_PanelIsNotResponsive					= 4098,		/**< The system is not responding to requests. */
	Target_SystemIsBusy							= 4099,		/**< The system is busy performing other operations. */
	Target_NoActiveSession						= 4100,		/**< There system is not connected or is connecting. */
	Target_WrongSessionId						= 4101,		/**< The session ID does not match the target system. */
	Target_InternalError						= 4102,		/**< The system encountered an internal error, retry the requested operation. */
	Target_Timeout								= 4103,		/**< The system is not responding and a timeout failure has occurred. */
	Target_RequestMissing						= 4104,		/**< The request is missing / not supported. */
	Target_RequestError							= 4105,		/**< The requested operation failed. */
	Target_ResponseMissing						= 4106,		/**< The requested data was not received. */
	Target_ResponseError						= 4107,		/**< The requested data was not valid. */

	// 5120-6143
	SDK_InternalError							= 5120,		/**< The SDK had an internal error processing the operation. */

	// 6144-7167
	AccessCode_InvalidAccessCodeBeingProgrammed = 6144,		/**< The provided access code value was not valid. */
	AccessCode_CodeDuplicated					= 6145,		/**< The provided access code value is already in use. */

	// 7168-8191
	Partition_PartitionFailedToArm				= 7168,		/**< The partition did not arm, i.e. Zones open. */
	Partition_InvalidArmingMode					= 7169,		/**< The requested arming mode is not available. */
	Partition_WalkTestActive					= 7170,		/**< The partition is in walk test mode. */
	Partition_SomeOrAllPartitionsFailedToArm	= 7171,		/**< One or more partitions did not arm. */
	Partition_PartitionIsBusy					= 7172,		/**< The requested partition is busy performing other operations. */
	Partition_PartitionFailedToDisarm			= 7173,		/**< The requested partition failed to disarm, probable cause is wrong access code. */
	Partition_SomeOrAllPartitionsFailedToDisarm = 7174,		/**< One or more requested partitions failed to disarm, probable cause is wrong access code. */
	Partition_InvalidFAPType					= 7175,		/**< The requested [F], [A], [P] key is not available. */
	Partition_FAPRequestDenied					= 7176,		/**< The requested [F], [A], [P] operation failed. */
	Partition_CannotChangeDoorChimeStatus		= 7177,		/**< The requested door chime operation failed. */
	Partition_InvalidDoorChimeEnabledState		= 7178,		/**< The requested door chime state is not available. */
	Partition_CommandOutputNotDefined			= 7179,		/**< The requested command output [*7] is not available. */
	Partition_InvalidCommandOutputNumber		= 7180,		/**< The requested command output "index" is not available. */
	Partition_InvalidCommandOutputState			= 7181,		/**< The requested command output state is not available. */

	// 8192-9215
	System_IncorrectTime						= 8192,		/**< The time/date data or format was invalid. */

	// 9216-10239
	VirtualZoneStatus_SystemIsBusy				= 9216,		/**< The system is busy performing other operations. */

	// 10240 -  11263
	Zone_ZoneCannotBeBypassed					= 10240,	/**< The system rejected the bypass request. */
	Zone_InvalidBypassState						= 10241,	/**< The requested bypass state is invalid. */

	// 11264 - 12287
	VirtualKeypad_NotSupported					= 11264,	/**< The Virtual Keypad is not supported on the system. */
	VirtualKeypad_InvalidKeypadNumber			= 11265,	/**< The Virtual Keypad is invalid. */
	VirtualKeypad_InvalidKeypadMode				= 11266,	/**< The Virtual Keypad mode is invalid. */
	VirtualKeypad_AlreadyActiveOnAnotherSession = 11267,	/**< The Virtual Keypad is already being used on another session. */
	VirtualKeypad_MaximumSupportedKeypadsActive = 11268		/**< The maximum number of Virtual Keypads on the system has been reached. */

}; }

#else

#define DSC_RequestResultCodes(value)	(DSC_E50_##value)
enum DSC_RequestResultCode_Tag {

	// 0-4095
	DSC_E50_Common_NotAvailable							= -1,		/**< Reserved value. It indicates that this value is not available on the product. */
	DSC_E50_Common_Unknown								= 0,		/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */

	DSC_E50_Common_Success								= 1,		/**< The requested operation succeeded. */
	DSC_E50_Common_InvalidUserCredentials				= 2,		/**< The provided user credentials was invalid. */
	DSC_E50_Common_InvalidInstallerCredentials			= 3,		/**< The provided installer credentials was invalid. */
	DSC_E50_Common_UserCredentialsRequired              = 4,		/**< The operation requested requires user credentials to be provided. */
	DSC_E50_Common_FunctionNotAvailable					= 5,		/**< The operation requested is not supported. */
	DSC_E50_Common_UnrecognizedResultCode               = 6,        /**< The operation requested yielded an unrecognized response code. */


	// 4096-5119
	DSC_E50_Target_SystemIsLockedOut					= 4096,		/**< The system is locked out and not available at this time. */
	DSC_E50_Target_PowerUpShuntInEffect					= 4097,		/**< The system is powering up / initializing. */
	DSC_E50_Target_PanelIsNotResponsive					= 4098,		/**< The system is not responding to requests. */
	DSC_E50_Target_SystemIsBusy							= 4099,		/**< The system is busy performing other operations. */
	DSC_E50_Target_NoActiveSession						= 4100,		/**< There system is not connected or is connecting. */
	DSC_E50_Target_WrongSessionId						= 4101,		/**< The session ID does not match the target system. */
	DSC_E50_Target_InternalError						= 4102,		/**< The system encountered an internal error, retry the requested operation. */
	DSC_E50_Target_Timeout								= 4103,		/**< The system is not responding and a timeout failure has occurred. */
	DSC_E50_Target_RequestMissing						= 4104,		/**< The request is missing / not supported. */
	DSC_E50_Target_RequestError							= 4105,		/**< The requested operation failed. */
	DSC_E50_Target_ResponseMissing						= 4106,		/**< The requested data was not received. */
	DSC_E50_Target_ResponseError						= 4107,		/**< The requested data was not valid. */

	// 5120-6143
	DSC_E50_SDK_InternalError							= 5120,		/**< The SDK had an internal error processing the operation. */
	DSC_E50_SDK_CurrentlyBusy							= 5121,		/**< The SDK cannot perform requested operation at this time. */

	// 6144-7167
	DSC_E50_AccessCode_InvalidAccessCodeBeingProgrammed = 6144,		/**< The provided access code value was not valid. */
	DSC_E50_AccessCode_CodeDuplicated					= 6145,		/**< The provided access code value is already in use. */

	// 7168-8191
	DSC_E50_Partition_PartitionFailedToArm				= 7168,		/**< The partition did not arm, i.e. Zones open. */
	DSC_E50_Partition_InvalidArmingMode					= 7169,		/**< The requested arming mode is not available. */
	DSC_E50_Partition_WalkTestActive					= 7170,		/**< The partition is in walk test mode. */
	DSC_E50_Partition_SomeOrAllPartitionsFailedToArm	= 7171,		/**< One or more partitions did not arm. */
	DSC_E50_Partition_PartitionIsBusy					= 7172,		/**< The requested partition is busy performing other operations. */
	DSC_E50_Partition_PartitionFailedToDisarm			= 7173,		/**< The requested partition failed to disarm, probable cause is wrong access code. */
	DSC_E50_Partition_SomeOrAllPartitionsFailedToDisarm = 7174,		/**< One or more requested partitions failed to disarm, probable cause is wrong access code. */
	DSC_E50_Partition_InvalidFAPType					= 7175,		/**< The requested [F], [A], [P] key is not available. */
	DSC_E50_Partition_FAPRequestDenied					= 7176,		/**< The requested [F], [A], [P] operation failed. */
	DSC_E50_Partition_CannotChangeDoorChimeStatus		= 7177,		/**< The requested door chime operation failed. */
	DSC_E50_Partition_InvalidDoorChimeEnabledState		= 7178,		/**< The requested door chime state is not available. */
	DSC_E50_Partition_CommandOutputNotDefined			= 7179,		/**< The requested command output [*7] is not available. */
	DSC_E50_Partition_InvalidCommandOutputNumber		= 7180,		/**< The requested command output "index" is not available. */
	DSC_E50_Partition_InvalidCommandOutputState			= 7181,		/**< The requested command output state is not available. */

	// 8192-9215
	DSC_E50_System_IncorrectTime						= 8192,		/**< The time/date data or format was invalid. */

	// 9216-10239
	DSC_E50_VirtualZoneStatus_SystemIsBusy				= 9216,		/**< The system is busy performing other operations. */

	// 10240 -  11263
	DSC_E50_Zone_ZoneCannotBeBypassed					= 10240,	/**< The system rejected the bypass request. */
	DSC_E50_Zone_InvalidBypassState						= 10241,	/**< The requested bypass state is invalid. */

	// 11264 - 12287
	DSC_E50_VirtualKeypad_NotSupported					= 11264,	/**< The Virtual Keypad is not supported on the system. */
	DSC_E50_VirtualKeypad_InvalidKeypadNumber			= 11265,	/**< The Virtual Keypad is invalid. */
	DSC_E50_VirtualKeypad_InvalidKeypadMode				= 11266,	/**< The Virtual Keypad mode is invalid. */
	DSC_E50_VirtualKeypad_AlreadyActiveOnAnotherSession = 11267,	/**< The Virtual Keypad is already being used on another session. */
	DSC_E50_VirtualKeypad_MaximumSupportedKeypadsActive = 11268		/**< The maximum number of Virtual Keypads on the system has been reached. */

};

#endif

/*!
	The DSC_RequestResultCode data type corresponds with the enum DSC_RequestResultCode_Tag.

	\sa enum DSC_RequestResultCode_Tag
*/
typedef DSC_ENUM_T DSC_RequestResultCode;

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_REQUEST_RESULT_CODES_HPP_
