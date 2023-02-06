//---------------------------------------------------------------------------
//
//	DSC_DataContainers.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_DATA_CONTAINERS_HPP_
#define _DSC_DATA_CONTAINERS_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_DataContainers {
/*!
	The list of various data containers used by the SDK.
*/
enum DSC_DataContainer_Tag {

	Unknown						= 0,	/**< reserved - must be 0! */

	Partition					= 1,	/**< DSC_IPartition data container */
	Zone						= 2,	/**< DSC_IZone data Container */
	VirtualZone					= 3,	/**< DSC_IVirtualZone data container */
	ProgrammingInformation		= 4,	/**< DSC_IProgrammingDataContainer data container */
	KeyPressedInformation		= 5,	/**< DSC_IKeyPressedDataContainer data container */
	LCDUpdateInformation		= 6,	/**< DSC_ILCDUpdateDataContainer data container */
	LCDCursorInformation		= 7,	/**< DSC_ILCDCursorDataContainer data container */
	LEDStatusInformation		= 8,	/**< DSC_ILCDStatusDataContainer data container */
	BuzzerInformation			= 9,	/**< DSC_IBuzzerDataContainer data container */
	AccessCode					= 10,	/**< DSC_IAccessCode data container */
	SystemManager				= 11,	/**< DSC_ISystemManager data container */
	PartitionStateData			= 12,	/**< DSC_IPartitionStateData data container */
	AccessCodeAttributes		= 13,	/**< DSC_IAccessCodeAttributes data container */
	ZoneAttributes				= 14,	/**< DSC_IZoneAttributes data container */
	VirtualZoneStatus			= 15,	/**< DSC_IVirtualZoneStatus data container */
	TextString					= 16,	/**< DSC_ITextString data container */
	DataBuffer					= 17,	/**< DSC_IDataBuffer data container */
	CommandOutput               = 18,   /**< DSC_ICommandOutputDataContainer data container */
	AssignmentData				= 19,	/**< DSC_IAssignmentData data container */
	AssignmentList				= 20,	/**< DSC_IAssignmentList data container */
	TroubleData					= 21,	/**< DSC_ITroubleData data container */
	TroubleList					= 22,	/**< DSC_ITroubleList data container */
	EventBufferEntry            = 23    /**< DSC_IEventBufferEntry data container */
}; }

#else

#define DSC_DataContainers(value)	(DSC_E05_##value)
enum DSC_DataContainer_Tag {

	DSC_E05_Unknown						= 0,	/**< reserved - must be 0! */

	DSC_E05_Partition					= 1,
	DSC_E05_Zone						= 2,
	DSC_E05_VirtualZone					= 3,
	DSC_E05_ProgrammingInformation		= 4,
	DSC_E05_KeyPressedInformation		= 5,
	DSC_E05_LCDUpdateInformation		= 6,
	DSC_E05_LCDCursorInformation		= 7,
	DSC_E05_LEDStatusInformation		= 8,
	DSC_E05_BuzzerInformation			= 9,
	DSC_E05_AccessCode					= 10,
	DSC_E05_SystemManager				= 11,
	DSC_E05_PartitionStateData			= 12,
	DSC_E05_AccessCodeAttributes		= 13,
	DSC_E05_ZoneAttributes				= 14,
	DSC_E05_VirtualZoneStatus			= 15,
	DSC_E05_TextString					= 16,
	DSC_E05_DataBuffer					= 17,
	DSC_E05_CommandOutput				= 18,
	DSC_E05_AssignmentData				= 19,
	DSC_E05_AssignmentList				= 20,
	DSC_E05_TroubleData					= 21,
	DSC_E05_TroubleList					= 22,
	DSC_E05_EventBufferEntry            = 23
};

#endif

/*!
	The DSC_DataContainer data type corresponds with the enum DSC_DataContainer_Tag.

	\sa enum DSC_DataContainer_Tag
*/
typedef DSC_ENUM_T DSC_DataContainer;

//---------------------------------------------------------------------------
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_DATA_CONTAINERS_HPP_
