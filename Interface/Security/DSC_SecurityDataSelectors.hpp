//---------------------------------------------------------------------------
//
//	DSC_SecurityDataSelectors.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_SECURITY_DATA_SELECTORS_HPP_
#define _DSC_SECURITY_DATA_SELECTORS_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_SecurityDataSelectors {
/*!
	The SDK provides access to real time data/state change events 
	by the “OnDataUpdateNotificationHandler” in DSC_ISecurityBase:

	Specifies the type of data that has been updated/changed.
*/
enum DSC_SecurityDataSelector_Tag {

	Unknown				= 0,	/**< Reserved value. */

	//common properties
	SystemIndex			= 1,	/**< The "SystemIndex" property of an access code, a partition, a zone, a virtual zone or a virtual keypad. */
	Label				= 2,	/**< The "Label" property of an access code, a partition or a zone. */
	Value				= 3,	/**< The "Value" property of an access code. */
	Length				= 4,	/**< The "AccessCodeLength" property of an access code (number of digits). */
	Attributes			= 5,	/**< The "Attributes" property of an access code or a zone. */
	AlarmTypes			= 303,	/**< The "AlarmTypes" property of the system manager, a partition or a zone. */
	Enabled				= 6,	/**< The "Enabled" property of a partition. */

	//data arrays
	NumberOfAccessCodes				= 80,	/**< The "NumberOfAccessCodes" property of an access code manager. */
	NumberOfPartitions				= 81,	/**< The "NumberOfPartitions" property of a partition manager. */
	NumberOfZones					= 82,	/**< The "NumberOfZones" property of a zone manager. */
	NumberOfVirtualZones			= 83,	/**< The "NumberOfVirtualZones" property of a virtual manager. */
	NumberOfVirtualKeypads			= 84,	/**< The "NumberOfVirtualKeypads" property of a virtual keypad manager. */
	NumberOfSupportedVirtualKeypads	= 85,	/**< The "NumberOfSupportedVirtualKeypads" property of a virtual keypad manager. */

	//zone properties
	OpenClose			= 100,	/**< The "OpenCloseState" property of a zone. */
	Bypass				= 101,	/**< The "BypassState" property of a zone. */
	Tamper				= 102,	/**< The "TamperState" property of a zone. */
	LowBattery			= 103,	/**< The "LowBatteryState" property of a zone. */
	//Trouble				= 104,	/**< The "Trouble" property of a zone - currently not implemented. */
	//ChimeEnabled		= 105,	/**< The "ChimeEnabled" property of a zone - currently not implemented. */
	Masked 				= 106,	/**< The "Masked" property of a zone. */
	LowSensitivity		= 107,	/**< The "LowSensitivityState" property of a zone. */
	Alarm				= 108,	/**< The "AlarmState" property of a zone. */
	Fault   			= 109,	/**< The "FaultState" property of a zone. */
	Delinquency			= 110,	/**< The "DelinquencyState" property of a zone. */
	AlarmInMemory		= 300,	/**< The "AlarmInMemoryState" property of a zone. */

	Zone_ChimeFunction	= 160,	/**< The "ChimeFunction" property of a zone attributes. */
	Zone_BypassEnable	= 161,	/**< The "BypassEnable" property of a zone attributes. */

	//partition properties
	PartitionArmingLevelStatus		= 200,	/**< The "PartitionArmedState" property of a partition state. */
	PartitionAudibleBellStatus		= 201,	/**< The "PartitionAudibleBellState" property of a partition state. */
	PartitionAlarmInMemoryStatus	= 202,	/**< The "PartitionAlarmMemoryState" property of a partition state. */
	PartitionQuickExitStatus		= 203,	/**< The "PartitionQuickExitState" property of a partition state. */
	PartitionReadyStatus			= 204,	/**< The "PartitionReadyState" property of a partition state. */
	PartitionExitDelayStatus		= 205,	/**< The "PartitionExitDelayState" property of a partition state. */
	PartitionEntryDelayStatus		= 206,	/**< The "PartitionEntryDelayState" property of a partition state. */
	PartitionBusyStatus				= 207,	/**< The "PartitionBusyState" property of a partition state. */
	PartitionBypassStatus			= 208,	/**< The "PartitionBypassState" property of a partition state. */
	PartitionBlankStatus			= 209,	/**< The "PartitionBlankState" property of a partition state. */
	PartitionTroubleStatus			= 210,	/**< The "PartitionTroubleState" property of a partition state. */
	PartitionDoorChimeStatus		= 211,	/**< The "DoorChimeEnabledState" property of a partition. */	
	PartitionAlarmStatus			= 212,	/**< The "PartitionAlarmState" iproperty of a partition state. */
	PartitionBuzzerStatus			= 213,	/**< The "PartitionBuzzerState" property of a partition state. */
	PartitionAudibleBellType		= 214,	/**< The "PartitionAudibleBellType" property of a partition state. */
	PartitionStateData				= 215,	/**< The state data of a partition. */

	//*******************
	//	All 'enum' numbers between 300 and 399 are reserved for backward compatibility!
	//*******************

	//access code properties
	AccessCode_CanBypassZone		= 400,	/**< The "CanBypassZone" property of an access code attributes. */
	AccessCode_RemoteAccessEnabled	= 401,	/**< The "RemoteAccessEnabled" property of an access code attributes. */
	AccessCode_OneTimeUse			= 402,	/**< The "OneTimeUse" property of an access code attributes. */
	AccessCode_BellSquawk			= 403,	/**< The "BellSquawk" property of an access code attributes. */
	AccessCode_Supervisor			= 404,	/**< The "Supervisor" property of an access code attributes. */
	AccessCode_DuressCode			= 405,	/**< The "DuressCode" property of an access code attributes. */

	//virtual zone properties
	VirtualZone_Open			= 500,	/**< The "Open" property of a virtual zone status. */
	VirtualZone_Tamper			= 501,	/**< The "Tamper" property of a virtual zone status. */
	VirtualZone_Fault			= 502,	/**< The "Fault" property of a virtual zone status. */
	VirtualZone_LowBattery		= 503,	/**< The "LowBattery" property of a virtual zone status. */
	VirtualZone_ACTrouble		= 504,	/**< The "ACTrouble" property of a virtual zone status. */
	VirtualZone_Masked			= 505,	/**< The "Masked" property of a virtual zone status. */

	ZoneNumber					= 301,	/**< The "ZoneNumber" property of a virtual zone. */
	VirtualZoneStatus			= 302,	/**< The information on the status of a virtual zone. */

	//virtual keypad properties
	VirtualKeypad_Partition			= 600,	/**< The "Partition" property of a virtual keypad. */
	VirtualKeypad_Mode				= 601,	/**< The "Mode" property of a virtual keypad. */
	VirtualKeypad_Type				= 602,	/**< The "Type" property of a virtual keypad. */
	VirtualKeypad_Width				= 603,	/**< The "Width" property of a virtual keypad. */
	VirtualKeypad_Height			= 604,	/**< The "Height" property of a virtual keypad. */

	//miscellaneous properties
	SystemManager_TroublePresent	= 700,	/**< The "TroublePresent" property of the system manager. */

	//event buffer entry
	EventBufferEntry                = 800   /**< Event Buffer Entry. */
}; }

#else

#define DSC_SecurityDataSelectors(value)	(DSC_E51_##value)
enum DSC_SecurityDataSelector_Tag {

	DSC_E51_Unknown				= 0,	/**< Reserved value. */

	//common properties
	DSC_E51_SystemIndex			= 1,	/**< The "SystemIndex" property of an access code, a partition, a zone, a virtual zone or a virtual keypad. */
	DSC_E51_Label				= 2,	/**< The "Label" property of an access code, a partition or a zone. */
	DSC_E51_Value				= 3,	/**< The "Value" property of an access code. */
	DSC_E51_Length				= 4,	/**< The "AccessCodeLength" property of an access code (number of digits). */
	DSC_E51_Attributes			= 5,	/**< The "Attributes" property of an access code or a zone. */
	DSC_E51_AlarmTypes			= 303,	/**< The "AlarmTypes" property of the system manager, a partition or a zone. */
	DSC_E51_Enabled				= 6,	/**< The "Enabled" property of a partition. */

	//data arrays
	DSC_E51_NumberOfAccessCodes				= 80,	/**< The "NumberOfAccessCodes" property of an access code manager. */
	DSC_E51_NumberOfPartitions				= 81,	/**< The "NumberOfPartitions" property of a partition manager. */
	DSC_E51_NumberOfZones					= 82,	/**< The "NumberOfZones" property of a zone manager. */
	DSC_E51_NumberOfVirtualZones			= 83,	/**< The "NumberOfVirtualZones" property of a virtual manager. */
	DSC_E51_NumberOfVirtualKeypads			= 84,	/**< The "NumberOfVirtualKeypads" property of a virtual keypad manager. */
	DSC_E51_NumberOfSupportedVirtualKeypads	= 85,	/**< The "NumberOfSupportedVirtualKeypads" property of a virtual keypad manager. */

	//zone properties
	DSC_E51_OpenClose			= 100,	/**< The "OpenCloseState" property of a zone. */
	DSC_E51_Bypass				= 101,	/**< The "BypassState" property of a zone. */
	DSC_E51_Tamper				= 102,	/**< The "TamperState" property of a zone. */
	DSC_E51_LowBattery			= 103,	/**< The "LowBatteryState" property of a zone. */
	//DSC_E51_Trouble				= 104,	/**< The "Trouble" property of a zone - currently not implemented. */
	//DSC_E51_ChimeEnabled		= 105,	/**< The "ChimeEnabled" property of a zone - currently not implemented. */
	DSC_E51_Masked 				= 106,	/**< The "Masked" property of a zone. */
	DSC_E51_LowSensitivity		= 107,	/**< The "LowSensitivityState" property of a zone. */
	DSC_E51_Alarm				= 108,	/**< The "AlarmState" property of a zone. */
	DSC_E51_Fault   			= 109,	/**< The "FaultState" property of a zone. */
	DSC_E51_Delinquency			= 110,	/**< The "DelinquencyState" property of a zone. */
	DSC_E51_AlarmInMemory		= 300,	/**< The "AlarmInMemoryState" property of a zone. */

	DSC_E51_Zone_ChimeFunction	= 160,	/**< The "ChimeFunction" property of a zone attributes. */
	DSC_E51_Zone_BypassEnable	= 161,	/**< The "BypassEnable" property of a zone attributes. */

	//partition properties
	DSC_E51_PartitionArmingLevelStatus		= 200,	/**< The "PartitionArmedState" property of a partition state. */
	DSC_E51_PartitionAudibleBellStatus		= 201,	/**< The "PartitionAudibleBellState" property of a partition state. */
	DSC_E51_PartitionAlarmInMemoryStatus	= 202,	/**< The "PartitionAlarmMemoryState" property of a partition state. */
	DSC_E51_PartitionQuickExitStatus		= 203,	/**< The "PartitionQuickExitState" property of a partition state. */
	DSC_E51_PartitionReadyStatus			= 204,	/**< The "PartitionReadyState" property of a partition state. */
	DSC_E51_PartitionExitDelayStatus		= 205,	/**< The "PartitionExitDelayState" property of a partition state. */
	DSC_E51_PartitionEntryDelayStatus		= 206,	/**< The "PartitionEntryDelayState" property of a partition state. */
	DSC_E51_PartitionBusyStatus				= 207,	/**< The "PartitionBusyState" property of a partition state. */
	DSC_E51_PartitionBypassStatus			= 208,	/**< The "PartitionBypassState" property of a partition state. */
	DSC_E51_PartitionBlankStatus			= 209,	/**< The "PartitionBlankState" property of a partition state. */
	DSC_E51_PartitionTroubleStatus			= 210,	/**< The "PartitionTroubleState" property of a partition state. */
	DSC_E51_PartitionDoorChimeStatus		= 211,	/**< The "DoorChimeEnabledState" property of a partition. */	
	DSC_E51_PartitionAlarmStatus			= 212,	/**< The "PartitionAlarmState" iproperty of a partition state. */
	DSC_E51_PartitionBuzzerStatus			= 213,	/**< The "PartitionBuzzerState" property of a partition state. */
	DSC_E51_PartitionAudibleBellType		= 214,	/**< The "PartitionAudibleBellType" property of a partition state. */
	DSC_E51_PartitionStateData				= 215,	/**< The state data of a partition. */

	//*******************
	//	All 'enum' numbers between 300 and 399 are reserved for backward compatibility!
	//*******************

	//access code properties
	DSC_E51_AccessCode_CanBypassZone		= 400,	/**< The "CanBypassZone" property of an access code attributes. */
	DSC_E51_AccessCode_RemoteAccessEnabled	= 401,	/**< The "RemoteAccessEnabled" property of an access code attributes. */
	DSC_E51_AccessCode_OneTimeUse			= 402,	/**< The "OneTimeUse" property of an access code attributes. */
	DSC_E51_AccessCode_BellSquawk			= 403,	/**< The "BellSquawk" property of an access code attributes. */
	DSC_E51_AccessCode_Supervisor			= 404,	/**< The "Supervisor" property of an access code attributes. */
	DSC_E51_AccessCode_DuressCode			= 405,	/**< The "DuressCode" property of an access code attributes. */

	//virtual zone properties
	DSC_E51_VirtualZone_Open		= 500,	/**< The "Open" property of a virtual zone status. */
	DSC_E51_VirtualZone_Tamper		= 501,	/**< The "Tamper" property of a virtual zone status. */
	DSC_E51_VirtualZone_Fault		= 502,	/**< The "Fault" property of a virtual zone status. */
	DSC_E51_VirtualZone_LowBattery	= 503,	/**< The "LowBattery" property of a virtual zone status. */
	DSC_E51_VirtualZone_ACTrouble	= 504,	/**< The "ACTrouble" property of a virtual zone status. */
	DSC_E51_VirtualZone_Masked		= 505,	/**< The "Masked" property of a virtual zone status. */

	DSC_E51_ZoneNumber				= 301,	/**< The "ZoneNumber" property of a virtual zone. */
	DSC_E51_VirtualZoneStatus		= 302,	/**< The information on the status of a virtual zone. */

	//virtual keypad properties
	DSC_E51_VirtualKeypad_Partition			= 600,	/**< The "Partition" property of a virtual keypad. */
	DSC_E51_VirtualKeypad_Mode				= 601,	/**< The "Mode" property of a virtual keypad. */
	DSC_E51_VirtualKeypad_Type				= 602,	/**< The "Type" property of a virtual keypad. */
	DSC_E51_VirtualKeypad_Width				= 603,	/**< The "Width" property of a virtual keypad. */
	DSC_E51_VirtualKeypad_Height			= 604,	/**< The "Height" property of a virtual keypad. */

	//miscellaneous properties
	DSC_E51_SystemManager_TroublePresent	= 700,	/**< The "TroublePresent" property of the system manager. */

	DSC_E51_EventBufferEntry                = 800   /**< Event Buffer Entry. */
};

#endif

/*!
	The DSC_SecurityDataSelector data type corresponds with the enum DSC_SecurityDataSelector_Tag.

	\sa enum DSC_SecurityDataSelector_Tag
*/
typedef DSC_ENUM_T DSC_SecurityDataSelector;

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_SECURITY_DATA_SELECTORS_HPP_
