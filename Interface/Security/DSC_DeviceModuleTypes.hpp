//---------------------------------------------------------------------------
//
//	DSC_DeviceModuleTypes.hpp
//  Copyright 2021 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_DEVICE_MODULE_TYPES_HPP_
#define _DSC_DEVICE_MODULE_TYPES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_DeviceModuleTypes {
/*!
	The SDK provides access to Device/Module Types as described below.
*/
enum DSC_DeviceModuleType_Tag {

	//Default for all enums
	Not_Available	= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	Unknown			= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	

	System								= 0x01, /**< System. */
	Zone_Device							= 0x02, /**< Zone Device. */
	Keypad_Device						= 0x03, /**< Keypad Device. */
	Siren_Device_Or_Indoor_Siren_Device	= 0x04, /**< Siren or InDoor Siren Device. */
	FOB_Device							= 0x05, /**< FOB Device. */
	Proximity_Tag_Device				= 0x06, /**< Proximity Tag Device. */
	Repeater_Device						= 0x07, /**< Repeater Device. */
	Audio_Station_Device				= 0x08, /**< Audio Station Device. */
	AML_Module							= 0x11, /**< AML Module. */
	IO_Expander_Module					= 0x12, /**< IO Expander Module. */
	Zone_Expander_Module				= 0x13, /**< Zone Expander Module. */
	Wireless_Transreceiver_Module		= 0x14, /**< Wireless Transreceiver Module. */
	Power_Supply_Module					= 0x15, /**< Power Supply Module. */
	High_Current_Output_Module			= 0x16, /**< High Current Output Module. */
	Output_Expander_Module				= 0x17, /**< Output Expander Module. */
	Printer_Module						= 0x18, /**< Printer Module. */
	Hardwired_Keypad_Module				= 0x19, /**< Hardwired Keypad Module. */
	Audio_Alarm_Verification_Module		= 0x1A, /**< Audio Alarm Verification Module. */
	Voice_Dialer_Module					= 0x1B, /**< Voice Dialer Module. */
	Modem_Module						= 0x1C, /**< Modem Module. */
	Alternate_Communicator_Module		= 0x1D, /**< Alternate Communicator Module. */
	CorBus_Repeater_Module				= 0x1E, /**< Corbus Repeater Module. */
	Power_Supply_3A_Module				= 0x1F, /**< Power Supply 3A Module. */
	MX_Module							= 0x20, /**< MX Module. */
	Wireless_Keypad						= 0x21, /**< Wireless Keypad. */
	Wireless_Handheld_Keypad			= 0x22, /**< Wireless Handheld Keypad. */
	Wireless_PGM						= 0x23, /**< Wireless PGM. */
	Indoor_Wireless_Siren				= 0x24, /**< Indoor Wireless Siren. */
	Outdoor_Wireless_Siren				= 0x25, /**< Outdoor Wireless Siren. */
	Wireless_Key_FOB					= 0x26, /**< Wireless Key FOB. */
	Proximity_Tag						= 0x27, /**< Proximity Tag. */
	Wired_Keypad						= 0x28, /**< Wired Keypad. */
	Outdoor_Siren_Device				= 0x29, /**< Outdoor Siren Device. */
	All_Modules_Including_Panel			= 0xF1, /**< All Modules Including Panel. */
	Interface_Module					= 0xF2, /**< Interface Module. */
	IP_Communicator_Module				= 0xF3  /**< IP Communicator Module. */
}; }

#else

#define DSC_DeviceModuleTypes(value)	(DSC_E79_##value)
enum DSC_DeviceModuleType_Tag {

	//Default for all enums
	DSC_E79_Not_Available	= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	DSC_E79_Unknown			= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	

	DSC_E79_System								= 0x01, /**< System. */
	DSC_E79_Zone_Device							= 0x02, /**< Zone Device. */
	DSC_E79_Keypad_Device						= 0x03, /**< Keypad Device. */
	DSC_E79_Siren_Device_Or_Indoor_Siren_Device	= 0x04, /**< Siren or InDoor Siren Device. */
	DSC_E79_FOB_Device							= 0x05, /**< FOB Device. */
	DSC_E79_Proximity_Tag_Device				= 0x06, /**< Proximity Tag Device. */
	DSC_E79_Repeater_Device						= 0x07, /**< Repeater Device. */
	DSC_E79_Audio_Station_Device				= 0x08, /**< Audio Station Device. */
	DSC_E79_AML_Module							= 0x11, /**< AML Module. */
	DSC_E79_IO_Expander_Module					= 0x12, /**< IO Expander Module. */
	DSC_E79_Zone_Expander_Module				= 0x13, /**< Zone Expander Module. */
	DSC_E79_Wireless_Transreceiver_Module		= 0x14, /**< Wireless Transreceiver Module. */
	DSC_E79_Power_Supply_Module					= 0x15, /**< Power Supply Module. */
	DSC_E79_High_Current_Output_Module			= 0x16, /**< High Current Output Module. */
	DSC_E79_Output_Expander_Module				= 0x17, /**< Output Expander Module. */
	DSC_E79_Printer_Module						= 0x18, /**< Printer Module. */
	DSC_E79_Hardwired_Keypad_Module				= 0x19, /**< Hardwired Keypad Module. */
	DSC_E79_Audio_Alarm_Verification_Module		= 0x1A, /**< Audio Alarm Verification Module. */
	DSC_E79_Voice_Dialer_Module					= 0x1B, /**< Voice Dialer Module. */
	DSC_E79_Modem_Module						= 0x1C, /**< Modem Module. */
	DSC_E79_Alternate_Communicator_Module		= 0x1D, /**< Alternate Communicator Module. */
	DSC_E79_CorBus_Repeater_Module				= 0x1E, /**< Corbus Repeater Module. */
	DSC_E79_Power_Supply_3A_Module				= 0x1F, /**< Power Supply 3A Module. */
	DSC_E79_MX_Module							= 0x20, /**< MX Module. */
	DSC_E79_Wireless_Keypad						= 0x21, /**< Wireless Keypad. */
	DSC_E79_Wireless_Handheld_Keypad			= 0x22, /**< Wireless Handheld Keypad. */
	DSC_E79_Wireless_PGM						= 0x23, /**< Wireless PGM. */
	DSC_E79_Indoor_Wireless_Siren				= 0x24, /**< Indoor Wireless Siren. */
	DSC_E79_Outdoor_Wireless_Siren				= 0x25, /**< Outdoor Wireless Siren. */
	DSC_E79_Wireless_Key_FOB					= 0x26, /**< Wireless Key FOB. */
	DSC_E79_Proximity_Tag						= 0x27, /**< Proximity Tag. */
	DSC_E79_Wired_Keypad						= 0x28, /**< Wired Keypad. */
	DSC_E79_Outdoor_Siren_Device				= 0x29, /**< Outdoor Siren Device. */
	DSC_E79_All_Modules_Including_Panel			= 0xF1, /**< All Modules Including Panel. */
	DSC_E79_Interface_Module					= 0xF2, /**< Interface Module. */
	DSC_E79_IP_Communicator_Module				= 0xF3  /**< IP Communicator Module. */
};

#endif

/*!
	The DSC_DeviceModuleType data type corresponds with the enum DSC_DeviceModuleType_Tag.

	\sa enum DSC_DeviceModuleType_Tag
*/
typedef DSC_ENUM_T DSC_DeviceModuleType;

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_DEVICE_MODULE_TYPES_HPP_
