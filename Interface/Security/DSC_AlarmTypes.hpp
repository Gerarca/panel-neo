//---------------------------------------------------------------------------
//
//	DSC_AlarmTypes.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_ALARM_TYPES_HPP_
#define _DSC_ALARM_TYPES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

//helper macros for processing alarm information
#define DSC_ALARM_TYPE_RESTORAL_FLAG		0x8000
#define DSC_ALARM_TYPE_IS_RESTORAL(alarm)	((0 != ((DSC_ALARM_TYPE_RESTORAL_FLAG) & alarm))? TRUE : FALSE)
#define DSC_ALARM_TYPE_ROOT_VALUE(alarm)	((~(DSC_ALARM_TYPE_RESTORAL_FLAG)) & alarm)

//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

namespace DSC_AlarmTypes {	
/*!
	The SDK provides access to Alarm Types as described below.

	Used to interact with the present state of a Alarm Type 
*/
enum DSC_AlarmType_Tag {
	
	//Default for all enums
	Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	

    Unknown_Alarm				= 0x0001,	/**< Unknown alarm. */
    Burglary_Alarm				= 0x0002,	/**< Burglary alarm. */
    Alarm_24HR_Supervisory		= 0x0003,	/**< 24H Supervisory alarm. */
    Fire_Alarm					= 0x0004,	/**< Fire alarm. */
    Fire_Supervisory_Alarm		= 0x0005,	/**< Fire Supervisory alarm. */
    CO_Alarm					= 0x0006,	/**< CO (carbon monoxide) alarm. */
    Gas_Alarm					= 0x0007,	/**< Gas alarm. */
    High_Temperature_Alarm		= 0x0008,	/**< High Temperature alarm. */
    Low_Temperature_Alarm		= 0x0009,	/**< Low Temperature alarm. */
    Medical_Alarm				= 0x000A,	/**< Medical emergency alarm. */
    Panic_Alarm					= 0x000B,	/**< Panic alarm. */
    Waterflow_Alarm				= 0x000C,	/**< Waterflow alarm. */
    Water_Leakage_Alarm			= 0x000D,	/**< Water Leakage alarm. */
    Pendant_Alarm				= 0x000E,	/**< Pendant alarm. */
    Tamper_Alarm				= 0x000F,	/**< Tamper alarm. */
    RF_Jam_Alarm				= 0x0010,	/**< RF (radio) Jam alarm. */
    Hardware_Fault_Alarm		= 0x0011,	/**< Hardware Fault alarm. */
    Duress_Alarm				= 0x0012,	/**< Duress alarm. */
    Personal_Emergency_Alarm	= 0x0013,	/**< Personal Emergency alarm. */
    Holdup_Alarm				= 0x0014,	/**< Holdup alarm. */
    Sprinkler_Alarm				= 0x0015,	/**< Sprinkler alarm. */
    Quick_Bypass_Alarm			= 0x0016,	/**< Quick Bypass alarm. */
    Burglary_Alarm_Not_Verified	= 0x0017,	/**< Unverfied Burglary alarm. */
    Holdup_Alarm_Not_Verified	= 0x0018,	/**< Unverfied Holdup alarm. */
    High_Temperature_Warning	= 0x0019,	/**< High Temperature Warning alarm. */
    Low_Temperature_Warning		= 0x001A,	/**< Low Temperature Warning alarm. */

    General_Alarm				= 0x0100,	/**< General alarm. */

    Unknown_Alarm_Restore				= 0x8001,	/**< Unknown alarm restore. */
    Burglary_Alarm_Restore				= 0x8002,	/**< Burglary alarm restore. */
    Alarm_24HR_Supervisory_Restore		= 0x8003,	/**< 24H Supervisory alarm restore. */
    Fire_Alarm_Restore					= 0x8004,	/**< Fire alarm restore. */
    Fire_Supervisory_Alarm_Restore		= 0x8005,	/**< Fire Supervisory alarm restore. */
    CO_Alarm_Restore					= 0x8006,	/**< CO (carbon monoxide) alarm restore. */
    Gas_Alarm_Restore					= 0x8007,	/**< Gas alarm restore. */
    High_Temperature_Alarm_Restore		= 0x8008,	/**< High Temperature alarm restore. */
    Low_Temperature_Alarm_Restore		= 0x8009,	/**< Low Temperature alarm restore. */
    Medical_Alarm_Restore				= 0x800A,	/**< Medical emergency alarm restore. */
    Panic_Alarm_Restore					= 0x800B,	/**< Panic alarm restore. */
    Waterflow_Alarm_Restore				= 0x800C,	/**< Waterflow alarm restore. */
    Water_Leakage_Alarm_Restore			= 0x800D,	/**< Water Leakage alarm restore. */
    Pendant_Alarm_Restore				= 0x800E,	/**< Pendant alarm restore. */
    Tamper_Alarm_Restore				= 0x800F,	/**< Tamper alarm restore. */
    RF_Jam_Alarm_Restore				= 0x8010,	/**< RF (radio) Jam alarm restore. */
    Hardware_Fault_Alarm_Restore		= 0x8011,	/**< Hardware Fault alarm restore. */
    Duress_Alarm_Restore				= 0x8012,	/**< Duress alarm restore. */
    Personal_Emergency_Alarm_Restore	= 0x8013,	/**< Personal Emergency alarm restore. */
    Holdup_Alarm_Restore				= 0x8014,	/**< Holdup alarm restore. */
    Sprinkler_Alarm_Restore				= 0x8015,	/**< Sprinkler alarm restore. */
    Quick_Bypass_Alarm_Restore			= 0x8016,	/**< Quick Bypass alarm restore. */
    Burglary_Alarm_Not_Verified_Restore	= 0x8017,	/**< Unverfied Burglary alarm restore. */
    Holdup_Alarm_Not_Verified_Restore	= 0x8018,	/**< Unverfied Holdup alarm restore. */
    High_Temperature_Warning_Restore	= 0x8019,	/**< High Temperature Warning alarm restore. */
    Low_Temperature_Warning_Restore		= 0x801A,	/**< Low Temperature Warning alarm restore. */

    General_Alarm_Restore				= 0x8100	/**< General alarm restore. */
}; }

#else

#define DSC_AlarmTypes(value)	(DSC_E74_##value)
enum DSC_AlarmType_Tag {
	
	//Default for all enums
	DSC_E74_Not_Available		= -1,	/**< Reserved value. It indicates that this value is not available on the product. */	
	DSC_E74_Unknown				= 0,	/**< Reserved value. It indicates that the value has not yet been retrieved from the product. */	

    DSC_E74_Unknown_Alarm				= 0x0001,
    DSC_E74_Burglary_Alarm				= 0x0002,
    DSC_E74_Alarm_24HR_Supervisory		= 0x0003,
    DSC_E74_Fire_Alarm					= 0x0004,
    DSC_E74_Fire_Supervisory_Alarm		= 0x0005,
    DSC_E74_CO_Alarm					= 0x0006,
    DSC_E74_Gas_Alarm					= 0x0007,
    DSC_E74_High_Temperature_Alarm		= 0x0008,
    DSC_E74_Low_Temperature_Alarm		= 0x0009,
    DSC_E74_Medical_Alarm				= 0x000A,
    DSC_E74_Panic_Alarm					= 0x000B,
    DSC_E74_Waterflow_Alarm				= 0x000C,
    DSC_E74_Water_Leakage_Alarm			= 0x000D,
    DSC_E74_Pendant_Alarm				= 0x000E,
    DSC_E74_Tamper_Alarm				= 0x000F,
    DSC_E74_RF_Jam_Alarm				= 0x0010,
    DSC_E74_Hardware_Fault_Alarm		= 0x0011,
    DSC_E74_Duress_Alarm				= 0x0012,
    DSC_E74_Personal_Emergency_Alarm	= 0x0013,
    DSC_E74_Holdup_Alarm				= 0x0014,
    DSC_E74_Sprinkler_Alarm				= 0x0015,
    DSC_E74_Quick_Bypass_Alarm			= 0x0016,
    DSC_E74_Burglary_Alarm_Not_Verified	= 0x0017,
    DSC_E74_Holdup_Alarm_Not_Verified	= 0x0018,
    DSC_E74_High_Temperature_Warning	= 0x0019,
    DSC_E74_Low_Temperature_Warning		= 0x001A,

    DSC_E74_General_Alarm				= 0x0100,

    DSC_E74_Unknown_Alarm_Restore				= 0x8001,
    DSC_E74_Burglary_Alarm_Restore				= 0x8002,
    DSC_E74_Alarm_24HR_Supervisory_Restore		= 0x8003,
    DSC_E74_Fire_Alarm_Restore					= 0x8004,
    DSC_E74_Fire_Supervisory_Alarm_Restore		= 0x8005,
    DSC_E74_CO_Alarm_Restore					= 0x8006,
    DSC_E74_Gas_Alarm_Restore					= 0x8007,
    DSC_E74_High_Temperature_Alarm_Restore		= 0x8008,
    DSC_E74_Low_Temperature_Alarm_Restore		= 0x8009,
    DSC_E74_Medical_Alarm_Restore				= 0x800A,
    DSC_E74_Panic_Alarm_Restore					= 0x800B,
    DSC_E74_Waterflow_Alarm_Restore				= 0x800C,
    DSC_E74_Water_Leakage_Alarm_Restore			= 0x800D,
    DSC_E74_Pendant_Alarm_Restore				= 0x800E,
    DSC_E74_Tamper_Alarm_Restore				= 0x800F,
    DSC_E74_RF_Jam_Alarm_Restore				= 0x8010,
    DSC_E74_Hardware_Fault_Alarm_Restore		= 0x8011,
    DSC_E74_Duress_Alarm_Restore				= 0x8012,
    DSC_E74_Personal_Emergency_Alarm_Restore	= 0x8013,
    DSC_E74_Holdup_Alarm_Restore				= 0x8014,
    DSC_E74_Sprinkler_Alarm_Restore				= 0x8015,
    DSC_E74_Quick_Bypass_Alarm_Restore			= 0x8016,
    DSC_E74_Burglary_Alarm_Not_Verified_Restore	= 0x8017,
    DSC_E74_Holdup_Alarm_Not_Verified_Restore	= 0x8018,
    DSC_E74_High_Temperature_Warning_Restore	= 0x8019,
    DSC_E74_Low_Temperature_Warning_Restore		= 0x801A,

    DSC_E74_General_Alarm_Restore				= 0x8100
};

#endif

/*!
	The DSC_AlarmType data type corresponds with the enum DSC_AlarmType_Tag.

	\sa enum DSC_AlarmType_Tag
*/
typedef DSC_ENUM_T DSC_AlarmType;

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_ALARM_TYPES_HPP_
