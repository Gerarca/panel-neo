//---------------------------------------------------------------------------
//
//	DSC_PartitionAudibleBellTypes.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_PARTITION_AUDIBLE_BELL_TYPES_HPP_
#define _DSC_PARTITION_AUDIBLE_BELL_TYPES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_PartitionAudibleBellTypes {
/*!
	The SDK provides access to the following audible bell types as described below.

	When the bell is audible it can produce various cadences to indicate what condition caused it to turn on.
*/
enum DSC_PartitionAudibleBellType_Tag {
	
	//Default for all enums
	Not_Available			= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	Unknown					= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values. 
    OFF						= 1,	/**< The bell is presently off / silent. */	
	ON_Steady				= 2,	/**< The bell is on using a constant output. */	
    Pulse_Slow				= 3,	/**< The bell is on giving a short burst every 10 seconds. An example of this is during entry/exit delay. */	
    Pulse_Fast				= 4,	/**< The bell is on giving a short burst every second. An example of this is during the last 10 seconds of entry/exit delay indecating an "urgent state". */	
    Temporal_Fire			= 5,	/**< The bell is on indicating a fire condition. Fire bells sound in a pattern that are governed by regulatory requirements.
										Two typical patterns are Standard: 1 second ON / 1 second OFF and Temporal Three: 500ms ON, 500ms OFF, 500ms ON, 500ms OFF, 500ms ON, 1.5 sec. OFF). */
    Temporal_CO				= 6,	/**< The bell is on indicating a carbon monoxide alarm condition. Carbon monoxide bells sound in a pattern that are governed by regulatory requirements. */	
    Temporal_CO_Timeout		= 7		/**< The bell is on indicating a carbon monoxide alarm timeout condition. Carbon monoxide bells sound in a pattern that are governed by regulatory requirements. */	

}; }

#else

#define DSC_PartitionAudibleBellTypes(value)	(DSC_E37_##value)
enum DSC_PartitionAudibleBellType_Tag {
	
	//Default for all enums
	DSC_E37_Not_Available			= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	DSC_E37_Unknown					= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	
	
	//Valid product values. 
    DSC_E37_OFF						= 1,	/**< The bell is presently off / silent. */	
	DSC_E37_ON_Steady				= 2,	/**< The bell is on using a constant output. */	
    DSC_E37_Pulse_Slow				= 3,	/**< The bell is on giving a short burst every 10 seconds. An example of this is during entry/exit delay. */	
    DSC_E37_Pulse_Fast				= 4,	/**< The bell is on giving a short burst every second. An example of this is during the last 10 seconds of entry/exit delay indecating an "urgent state". */	
    DSC_E37_Temporal_Fire			= 5,	/**< The bell is on indicating a fire condition. Fire bells sound in a pattern that are governed by regulatory requirements.
											Two typical patterns are Standard: 1 second ON / 1 second OFF and Temporal Three: 500ms ON, 500ms OFF, 500ms ON, 500ms OFF, 500ms ON, 1.5 sec. OFF). */
    DSC_E37_Temporal_CO				= 6,	/**< The bell is on indicating a carbon monoxide alarm condition. Carbon monoxide bells sound in a pattern that are governed by regulatory requirements. */	
    DSC_E37_Temporal_CO_Timeout		= 7		/**< The bell is on indicating a carbon monoxide alarm timeout condition. Carbon monoxide bells sound in a pattern that are governed by regulatory requirements. */	

};

#endif

/*!
	The DSC_PartitionAudibleBellType data type corresponds with the enum DSC_PartitionAudibleBellType_Tag.

	\sa enum DSC_PartitionAudibleBellType_Tag
*/
typedef DSC_ENUM_T DSC_PartitionAudibleBellType;

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_PARTITION_AUDIBLE_BELL_TYPES_HPP_
