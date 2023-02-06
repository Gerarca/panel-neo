//---------------------------------------------------------------------------
//
//	DSC_TroubleTypes.hpp
//  Copyright 2021 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_TROUBLE_TYPES_HPP_
#define _DSC_TROUBLE_TYPES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_TroubleTypes {
/*!
	The SDK provides access to Trouble Types as described below.
*/
enum DSC_TroubleType_Tag {

	//Default for all enums
	Not_Available	= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	Unknown			= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	

	No_Troubles								= 0x01, /**< No Troubles. */
	Device_Tamper							= 0x02, /**< Device Tamper. */
	Device_Fault							= 0x03, /**< Device Fault. */
	Device_Low_Battery						= 0x04, /**< Device Low Battery. */
	Device_Delinquency						= 0x05, /**< Device Delinquency. */
	Failure_To_Communicate					= 0x06, /**< Failure To Communicate. */
	GSIP_Receiver_Trouble					= 0x07, /**< GSIP Receiver Trouble. */
	All_Receiver_Not_Available_Status		= 0x08, /**< All Receiver Not Available Status. */
	All_Receiver_Supervision_Trouble		= 0x09, /**< All Receiver Supervision Trouble. */
	Device_AC_Trouble						= 0x0A, /**< Device AC Trouble. */
	Device_Low_Sensitivity					= 0x0B, /**< Device Low Sensitivity. */
	Device_Internal_Fault					= 0x0C, /**< Device Internal Fault. */
	RF_Device_Not_Networked					= 0x0D, /**< RF Device Not Networked. */
	Device_Mask_Trouble						= 0x0E, /**< Device Mask Trouble. */
	Power_Unit_Failure						= 0x0F, /**< Power Unit Failure. */
	Overcurrent_Trouble						= 0x10, /**< Overcurrent Trouble. */
	Overview_Of_System_Troubles_Level_1		= 0x21, /**< Overview Of System Troubles Level 1. */
	Service_Request_Troubles				= 0x22, /**< Service Request Troubles. */
	Communications_Troubles					= 0x23, /**< Communications Troubles. */
	Bell_Trouble							= 0x31, /**< Bell Trouble. */
	RF_Jam_Trouble							= 0x36, /**< RF Jam Trouble. */
	Fire_Trouble							= 0x37, /**< Fire Trouble. */
	CO_Trouble								= 0x38, /**< CO Trouble. */
	Ground_Fault							= 0x3A, /**< Ground Fault. */
	Output_Fault							= 0x3B, /**< Output Fault. */
	TLM_Trouble								= 0x3C, /**< TLM Trouble. */
	Printer_Offline							= 0x3D, /**< Printer Offline. */
	Time_Date_Trouble						= 0x40, /**< Time Date Trouble. */
	Configuration_Trouble					= 0x41, /**< Configuration Trouble. */
	Warm_Start_Trouble						= 0x42, /**< Warm Start Trouble. */
	USB_WIFI_Trouble						= 0x43, /**< USB WIFI Trouble. */
	Critical_Shutdown_Trouble				= 0x44, /**< Critical Shutdown Trouble. */
	SIM_Lock_Trouble						= 0x51, /**< SIM Lock Trouble. */
	GSM_Trouble								= 0x56, /**< GSM Trouble. */
	Ethernet_Trouble						= 0x61, /**< Ethernet Trouble. */
	Module_Supervisory_Trouble				= 0x81, /**< Module Supervisory Trouble. */
	Module_Tamper							= 0x82, /**< Module Tamper. */
	Module_AC_Trouble						= 0x85, /**< Module AC Trouble. */
	Module_Low_Battery_Trouble				= 0x87, /**< Module Low Battery Trouble. */
	Module_Battery_Missing_Trouble			= 0x88, /**< Module Battery Missing Trouble. */
	Module_Battery_Charger_Trouble			= 0x89, /**< Module Battery Charger Trouble. */
	Module_Bus_Low_Voltage_Trouble			= 0x8B, /**< Module Bus Low Voltage Trouble. */
	Module_Bus_Fault						= 0x8C, /**< Module Bus Fault. */
	Module_AUX_Trouble						= 0x8D, /**< Module AUX Trouble. */
	Firmware_Upgrade_Fault					= 0x8E, /**< Firmware Upgrade Fault. */
	Default_Code							= 0x8F, /**< Default Code. */
	Duplicated_Code							= 0x90, /**< Duplicated Code. */
	Gas_Trouble								= 0x91, /**< Gas Trouble. */
	Heat_Trouble							= 0x92, /**< Heat Trouble. */
	Freeze_Trouble							= 0x93, /**< Freeze Trouble. */
	Probe_Trouble							= 0x94, /**< Prob Trouble. */
	Smoke_Trouble							= 0x95, /**< Smoke Trouble. */
	Radio_SIM_Failure						= 0x96, /**< Radio SIM Failure. */
	Module_Battery_Disconnected				= 0x97, /**< Module Battery Disconnected. */
	Radio_Low_Signal_Trouble				= 0x98, /**< Radio Low Signal Trouble. */
	GSM_Network								= 0x99, /**< GSM Network. */
	IP_Remote_Server						= 0x9A, /**< IP Remote Server. */
	Low_Input_Voltage						= 0x9B, /**< Low Input Voltage. */
	Output_Low								= 0x9C, /**< Output Low. */
	Module_Battery_2_Low_Voltage_Trouble	= 0x9D, /**< Module Battery 2 Low Voltage Trouble. */
	Module_Battery_2_Missing_Trouble		= 0x9E, /**< Module Battery 2 Missing Trouble. */
	Module_AUX_2_Trouble					= 0x9F, /**< Module AUX 2 Trouble. */
	Limit_Exceed_Troubles					= 0xA0, /**< Limit Exceed Troubles. */
	Zone_Limit_Exceed_Trouble				= 0xA1, /**< Zone Limit Exceed Trouble. */
	Partition_Limit_Exceed_Trouble			= 0xA2  /**< Partition Limit Exceed Trouble. */
}; }

#else

#define DSC_TroubleTypes(value)	(DSC_E82_##value)
enum DSC_TroubleType_Tag {

	//Default for all enums
	DSC_E82_Not_Available	= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	DSC_E82_Unknown			= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	

	DSC_E82_No_Troubles								= 0x01, /**< No Troubles. */
	DSC_E82_Device_Tamper							= 0x02, /**< Device Tamper. */
	DSC_E82_Device_Fault							= 0x03, /**< Device Fault. */
	DSC_E82_Device_Low_Battery						= 0x04, /**< Device Low Battery. */
	DSC_E82_Device_Delinquency						= 0x05, /**< Device Delinquency. */
	DSC_E82_Failure_To_Communicate					= 0x06, /**< Failure To Communicate. */
	DSC_E82_GSIP_Receiver_Trouble					= 0x07, /**< GSIP Receiver Trouble. */
	DSC_E82_All_Receiver_Not_Available_Status		= 0x08, /**< All Receiver Not Available Status. */
	DSC_E82_All_Receiver_Supervision_Trouble		= 0x09, /**< All Receiver Supervision Trouble. */
	DSC_E82_Device_AC_Trouble						= 0x0A, /**< Device AC Trouble. */
	DSC_E82_Device_Low_Sensitivity					= 0x0B, /**< Device Low Sensitivity. */
	DSC_E82_Device_Internal_Fault					= 0x0C, /**< Device Internal Fault. */
	DSC_E82_RF_Device_Not_Networked					= 0x0D, /**< RF Device Not Networked. */
	DSC_E82_Device_Mask_Trouble						= 0x0E, /**< Device Mask Trouble. */
	DSC_E82_Power_Unit_Failure						= 0x0F, /**< Power Unit Failure. */
	DSC_E82_Overcurrent_Trouble						= 0x10, /**< Overcurrent Trouble. */
	DSC_E82_Overview_Of_System_Troubles_Level_1		= 0x21, /**< Overview Of System Troubles Level 1. */
	DSC_E82_Service_Request_Troubles				= 0x22, /**< Service Request Troubles. */
	DSC_E82_Communications_Troubles					= 0x23, /**< Communications Troubles. */
	DSC_E82_Bell_Trouble							= 0x31, /**< Bell Trouble. */
	DSC_E82_RF_Jam_Trouble							= 0x36, /**< RF Jam Trouble. */
	DSC_E82_Fire_Trouble							= 0x37, /**< Fire Trouble. */
	DSC_E82_CO_Trouble								= 0x38, /**< CO Trouble. */
	DSC_E82_Ground_Fault							= 0x3A, /**< Ground Fault. */
	DSC_E82_Output_Fault							= 0x3B, /**< Output Fault. */
	DSC_E82_TLM_Trouble								= 0x3C, /**< TLM Trouble. */
	DSC_E82_Printer_Offline							= 0x3D, /**< Printer Offline. */
	DSC_E82_Time_Date_Trouble						= 0x40, /**< Time Date Trouble. */
	DSC_E82_Configuration_Trouble					= 0x41, /**< Configuration Trouble. */
	DSC_E82_Warm_Start_Trouble						= 0x42, /**< Warm Start Trouble. */
	DSC_E82_USB_WIFI_Trouble						= 0x43, /**< USB WIFI Trouble. */
	DSC_E82_Critical_Shutdown_Trouble				= 0x44, /**< Critical Shutdown Trouble. */
	DSC_E82_SIM_Lock_Trouble						= 0x51, /**< SIM Lock Trouble. */
	DSC_E82_GSM_Trouble								= 0x56, /**< GSM Trouble. */
	DSC_E82_Ethernet_Trouble						= 0x61, /**< Ethernet Trouble. */
	DSC_E82_Module_Supervisory_Trouble				= 0x81, /**< Module Supervisory Trouble. */
	DSC_E82_Module_Tamper							= 0x82, /**< Module Tamper. */
	DSC_E82_Module_AC_Trouble						= 0x85, /**< Module AC Trouble. */
	DSC_E82_Module_Low_Battery_Trouble				= 0x87, /**< Module Low Battery Trouble. */
	DSC_E82_Module_Battery_Missing_Trouble			= 0x88, /**< Module Battery Missing Trouble. */
	DSC_E82_Module_Battery_Charger_Trouble			= 0x89, /**< Module Battery Charger Trouble. */
	DSC_E82_Module_Bus_Low_Voltage_Trouble			= 0x8B, /**< Module Bus Low Voltage Trouble. */
	DSC_E82_Module_Bus_Fault						= 0x8C, /**< Module Bus Fault. */
	DSC_E82_Module_AUX_Trouble						= 0x8D, /**< Module AUX Trouble. */
	DSC_E82_Firmware_Upgrade_Fault					= 0x8E, /**< Firmware Upgrade Fault. */
	DSC_E82_Default_Code							= 0x8F, /**< Default Code. */
	DSC_E82_Duplicated_Code							= 0x90, /**< Duplicated Code. */
	DSC_E82_Gas_Trouble								= 0x91, /**< Gas Trouble. */
	DSC_E82_Heat_Trouble							= 0x92, /**< Heat Trouble. */
	DSC_E82_Freeze_Trouble							= 0x93, /**< Freeze Trouble. */
	DSC_E82_Probe_Trouble							= 0x94, /**< Prob Trouble. */
	DSC_E82_Smoke_Trouble							= 0x95, /**< Smoke Trouble. */
	DSC_E82_Radio_SIM_Failure						= 0x96, /**< Radio SIM Failure. */
	DSC_E82_Module_Battery_Disconnected				= 0x97, /**< Module Battery Disconnected. */
	DSC_E82_Radio_Low_Signal_Trouble				= 0x98, /**< Radio Low Signal Trouble. */
	DSC_E82_GSM_Network								= 0x99, /**< GSM Network. */
	DSC_E82_IP_Remote_Server						= 0x9A, /**< IP Remote Server. */
	DSC_E82_Low_Input_Voltage						= 0x9B, /**< Low Input Voltage. */
	DSC_E82_Output_Low								= 0x9C, /**< Output Low. */
	DSC_E82_Module_Battery_2_Low_Voltage_Trouble	= 0x9D, /**< Module Battery 2 Low Voltage Trouble. */
	DSC_E82_Module_Battery_2_Missing_Trouble		= 0x9E, /**< Module Battery 2 Missing Trouble. */
	DSC_E82_Module_AUX_2_Trouble					= 0x9F, /**< Module AUX 2 Trouble. */
	DSC_E82_Limit_Exceed_Troubles					= 0xA0, /**< Limit Exceed Troubles. */
	DSC_E82_Zone_Limit_Exceed_Trouble				= 0xA1, /**< Zone Limit Exceed Trouble. */
	DSC_E82_Partition_Limit_Exceed_Trouble			= 0xA2  /**< Partition Limit Exceed Trouble. */
};

#endif

/*!
	The DSC_TroubleType data type corresponds with the enum DSC_TroubleType_Tag.

	\sa enum DSC_TroubleType_Tag
*/
typedef DSC_ENUM_T DSC_TroubleType;

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_TROUBLE_TYPES_HPP_
