//---------------------------------------------------------------------------
//
//	DSC_ObjectTypes.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//	The list of all object types used by the SDK.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_OBJECT_TYPES_HPP_
#define _DSC_OBJECT_TYPES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_ObjectTypes {
/*!
	The list of various interface types used by the SDK.
*/
enum DSC_ObjectType_Tag {

	Unknown			= 0,	/**< Unknown - must be 0! */

	Interactive						= 1,

	BlockCipher						= 10,
	Channel							= 11,
	ChannelEventSink				= 12,
	Component						= 13,
	DataBuffer						= 14,
	DataStore						= 15,
	Diagnostics						= 16,
	LicenseManager					= 17,
	ProtocolData					= 18,
	SystemIndices					= 19,
	TextString						= 20,

	AccessCode						= 100,
	AccessCodeAttributes			= 101,
	AccessCodeManager				= 102,
	AccessCredentials				= 103,
	AlarmTypeContainer				= 104,
	AssignmentData					= 105,
	AssignmentList					= 106,
	BuzzerDataContainer				= 107,
	CommandOutputDataContainer		= 108,
	EventBufferEntryDataContainer	= 109,

	KeyPressedDataContainer			= 110,
	LCDCursorDataContainer			= 111,
	LCDUpdateDataContainer			= 112,
	LEDStatusDataContainer			= 113,
	LifeStyleSettings				= 114,
	Partition						= 115,
	PartitionManager				= 116,
	PartitionStateData				= 117,
	ProgrammingDataContainer		= 118,
	Repository						= 119,

	RequestResult					= 120,
	SecurityBase					= 121,
	SecurityEventSink				= 122,
	SpecificFunctions				= 123,
	SystemCapabilities				= 124,
	SystemInformation				= 125,
	SystemManager					= 126,
	TroubleData						= 127,
	TroubleList						= 128,
	VirtualKeypad					= 129,

	VirtualKeypadManager			= 130,
	VirtualZone						= 131,
	VirtualZoneManager				= 132,
	VirtualZoneStatus				= 133,
	Zone							= 134,
	ZoneAttributes					= 135,
	ZoneManager						= 136
}; }

#else

#define DSC_ObjectTypes(value)	(DSC_E84_##value)
enum DSC_ObjectType_Tag {

	DSC_E84_Unknown			= 0,	/**< Unknown - must be 0! */

	DSC_E84_Interactive						= 1,

	DSC_E84_BlockCipher						= 10,
	DSC_E84_Channel							= 11,
	DSC_E84_ChannelEventSink				= 12,
	DSC_E84_Component						= 13,
	DSC_E84_DataBuffer						= 14,
	DSC_E84_DataStore						= 15,
	DSC_E84_Diagnostics						= 16,
	DSC_E84_LicenseManager					= 17,
	DSC_E84_ProtocolData					= 18,
	DSC_E84_SystemIndices					= 19,
	DSC_E84_TextString						= 20,

	DSC_E84_AccessCode						= 100,
	DSC_E84_AccessCodeAttributes			= 101,
	DSC_E84_AccessCodeManager				= 102,
	DSC_E84_AccessCredentials				= 103,
	DSC_E84_AlarmTypeContainer				= 104,
	DSC_E84_AssignmentData					= 105,
	DSC_E84_AssignmentList					= 106,
	DSC_E84_BuzzerDataContainer				= 107,
	DSC_E84_CommandOutputDataContainer		= 108,
	DSC_E84_EventBufferEntryDataContainer	= 109,

	DSC_E84_KeyPressedDataContainer			= 110,
	DSC_E84_LCDCursorDataContainer			= 111,
	DSC_E84_LCDUpdateDataContainer			= 112,
	DSC_E84_LEDStatusDataContainer			= 113,
	DSC_E84_LifeStyleSettings				= 114,
	DSC_E84_Partition						= 115,
	DSC_E84_PartitionManager				= 116,
	DSC_E84_PartitionStateData				= 117,
	DSC_E84_ProgrammingDataContainer		= 118,
	DSC_E84_Repository						= 119,

	DSC_E84_RequestResult					= 120,
	DSC_E84_SecurityBase					= 121,
	DSC_E84_SecurityEventSink				= 122,
	DSC_E84_SpecificFunctions				= 123,
	DSC_E84_SystemCapabilities				= 124,
	DSC_E84_SystemInformation				= 125,
	DSC_E84_SystemManager					= 126,
	DSC_E84_TroubleData						= 127,
	DSC_E84_TroubleList						= 128,
	DSC_E84_VirtualKeypad					= 129,

	DSC_E84_VirtualKeypadManager			= 130,
	DSC_E84_VirtualZone						= 131,
	DSC_E84_VirtualZoneManager				= 132,
	DSC_E84_VirtualZoneStatus				= 133,
	DSC_E84_Zone							= 134,
	DSC_E84_ZoneAttributes					= 135,
	DSC_E84_ZoneManager						= 136
};

#endif

/*!
	The DSC_ObjectType data type corresponds with the enum DSC_ObjectType_Tag.

	\sa enum DSC_ObjectType_Tag
*/
typedef DSC_ENUM_T DSC_ObjectType;

//---------------------------------------------------------------------------
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_OBJECT_TYPES_HPP_
