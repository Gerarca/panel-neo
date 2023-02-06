//---------------------------------------------------------------------------
//
//	DSC_ISpecificFunctions.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_IComponent.hpp"
#include "DSC_ILifeStyleSettings.hpp"
#include "DSC_IRequestResult.hpp"
#include "DSC_ProtocolTypes.hpp"
#include "DSC_ISystemIndices.hpp"

#ifndef _DSC_I_SPECIFIC_FUNCTIONS_HPP_
#define _DSC_I_SPECIFIC_FUNCTIONS_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#define NAME_DSC_ISpecificFunctions	"DSC_ISpecificFunctions"

//---------------------------------------------------------------------------

#ifndef DSC_ISpecificFunctions_FWD_DEFINED
#define DSC_ISpecificFunctions_FWD_DEFINED
typedef DSC_INTERFACE DSC_ISpecificFunctions DSC_ISpecificFunctions;
#endif

//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

/*!
	This interface is used to provide product-specific functionality that
	is not covered by any of the other, regular interfaces.
*/
DSC_INTERFACE DSC_ISpecificFunctions : public DSC_IComponent
{
public:

	//! Get the Protocol
    /*! Retrieves the protocol used to communicate with the panel.     */
    /*!	
		\sa enum DSC_ProtocolType_Tag
		\param result Pointer to storage for the Protocol Type.
    */
	virtual IRESULT ICALL get_Protocol(OUT DSC_ProtocolType* result) const = 0;

	//! Changes the integration access code for the system
	/*! This function will issue the requisite commands to change the Integration Access Code on the panel. */
	/*!
		\param pszCurrentAccessCode Pointer to UTF8 string containing the current Integration Access Code.
		\param pszNewAccessCode Pointer to UTF8 string containing the new Integration Access Code.
		\param pszNewSessionLabel Pointer to UTF8 string containing the new Session Label.
		\param ptrRequestResult Pointer to storage for the result of the operation.
	*/
	virtual IRESULT ICALL ITV2_ChangeIntegrationAccessCode(
		IN char const* pszCurrentAccessCode, IN char const* pszNewAccessCode, 
		IN char const* pszNewSessionLabel, OUT DSC_IRequestResult** ptrRequestResult) = 0;

	//! Read the LifeStyle Notification Settings
	/*! This function will issue the requisite commands to read the LifeStyle Notification Settings from the panel.   */
	/*!
		\sa DSC_ILifeStyleSettings
		\param ptrLifeStyleSettings Pointer to storage for the LifeStyleSettings interface containing the LifeStyle Notifications that are turned ON.
		\param ptrRequestResult Pointer to storage for the result of the operation.
	*/
	virtual IRESULT ICALL ITV2_ReadLifeStyleNotificationSettings(
		OUT DSC_ILifeStyleSettings** ptrLifeStyleSettings, 
		OUT DSC_IRequestResult** ptrRequestResult) = 0;

	//! Write the LifeStyle Notification Settings
	/*! This function will issue the requisite commands to write the LifeStyle Notification Settings to the panel.  */
	/*!
		\sa enum DSC_LifeStyleNotification_Tag
		\param ptrLifeStyleOnData Provided list of LifeStyle Notifications to turn on.
		\param numLifeStyleOnSize Provided number of LifeStyle Notifications contained in the on list.
		\param ptrLifeStyleOffData Provided list of LifeStyle Notifications to turn off.
		\param numLifeStyleOffSize Provided number of LifeStyle NOtifications in the off list.
		\param ptrRequestResult Pointer to storage for the result of the operation.
	*/
	virtual IRESULT ICALL ITV2_WriteLifeStyleNotificationSettings(
		IN DSC_LifeStyleNotification const* ptrLifeStyleOnData, IN DSC_SIZE_T numLifeStyleOnSize,
		IN DSC_LifeStyleNotification const* ptrLifeStyleOffData, IN DSC_SIZE_T numLifeStyleOffSize,
		OUT DSC_IRequestResult** ptrRequestResult) = 0;

	//! Default the LifeStyle Notification Settings
	/*! This function will issue the requisite commands to default the LifeStyle Notification Settings on the panel.  */
	/*!
		\param ptrRequestResult Pointer to storage for the result of the operation.
	*/
	virtual IRESULT ICALL ITV2_DefaultLifeStyleNotificationSettings(
		OUT DSC_IRequestResult** ptrRequestResult) = 0;

	//! Read the Zone Notification Settings
	/*! This function will issue the requisite commands to read the Zone Notification Settings from the panel.    */
	/*!
		\param ptrZoneNumbers Pointer to storage for the System Indices interface containing the Zone System Indexes of Zone Notifications that are turned ON.
		\param ptrRequestResult Pointer to storage for the result of the operation.
	*/
	virtual IRESULT ICALL ITV2_ReadZoneNotificationSettings(
		OUT DSC_ISystemIndices** ptrZoneNumbers, 
		OUT DSC_IRequestResult** ptrRequestResult) = 0;

	//! Write the Zone Notification Settings
	/*! This function will issue the requisite commands to write the Zone Notification Settings to the panel.   */
	/*!
		\param ptrZoneOnData Provided list of System Indexes of Zone Notifications to turn on.
		\param numZoneOnSize Provided number of System Indexes contained in the on list.
		\param ptrZoneOffData Provided list of System Indexes of Zone Notifications to turn off.
		\param numZoneOffSize Provided number of System Indexes contained in the off list.
		\param ptrRequestResult Pointer to storage for the result of the operation.
	*/
	virtual IRESULT ICALL ITV2_WriteZoneNotificationSettings(
		IN DSC_SYSTEM_INDEX const* ptrZoneOnData, IN DSC_SIZE_T numZoneOnSize,
		IN DSC_SYSTEM_INDEX const* ptrZoneOffData, IN DSC_SIZE_T numZoneOffSize, 
		OUT DSC_IRequestResult** ptrRequestResult) = 0;

	//! Default the Zone Notification Settings
	/*! This function will issue the requisite commands to default the Zone Notification Settings on the panel.  */
	/*!
		\param ptrRequestResult Pointer to storage for the result of the operation.
	*/
	virtual IRESULT ICALL ITV2_DefaultZoneNotificationSettings(
		OUT DSC_IRequestResult** ptrRequestResult) = 0;
};

#else

typedef struct DSC_ISpecificFunctions_Vtbl
{
	BEGIN_INTERFACE

	IRESULT (ICALL *Query)(IN DSC_ISpecificFunctions *This, IN char const* pszInterface, OUT VOID** ptrInterface);
	IRESULT (ICALL *Acquire)(IN DSC_ISpecificFunctions *This, OUT ICOUNT* ptrCount);
	IRESULT (ICALL *Release)(IN DSC_ISpecificFunctions *This, OUT ICOUNT* ptrCount);

	IRESULT (ICALL *get_Protocol)(IN DSC_ISpecificFunctions *This, OUT DSC_ProtocolType* result);

	IRESULT (ICALL *ITV2_ChangeIntegrationAccessCode)(IN DSC_ISpecificFunctions *This, 
		IN char const* pszCurrentAccessCode, IN char const* pszNewAccessCode, 
		IN char const* pszNewSessionLabel, OUT DSC_IRequestResult** ptrRequestResult);

	IRESULT (ICALL *ITV2_ReadLifeStyleNotificationSettings)(IN DSC_ISpecificFunctions *This, 
		OUT DSC_ILifeStyleSettings** ptrLifeStyleSettings, 
		OUT DSC_IRequestResult** ptrRequestResult);
	IRESULT (ICALL *ITV2_WriteLifeStyleNotificationSettings)(IN DSC_ISpecificFunctions *This, 
		IN DSC_LifeStyleNotification const* ptrLifeStyleOnData, IN DSC_SIZE_T numLifeStyleOnSize,
		IN DSC_LifeStyleNotification const* ptrLifeStyleOffData, IN DSC_SIZE_T numLifeStyleOffSize,
		OUT DSC_IRequestResult** ptrRequestResult);
	IRESULT (ICALL *ITV2_DefaultLifeStyleNotificationSettings)(IN DSC_ISpecificFunctions *This,
		OUT DSC_IRequestResult** ptrRequestResult);

	IRESULT (ICALL *ITV2_ReadZoneNotificationSettings)(IN DSC_ISpecificFunctions *This, 
		OUT DSC_ISystemIndices** ptrZoneNumbers, 
		OUT DSC_IRequestResult** ptrRequestResult);
	IRESULT (ICALL *ITV2_WriteZoneNotificationSettings)(IN DSC_ISpecificFunctions *This, 
		IN DSC_SYSTEM_INDEX const* ptrZoneOnData, IN DSC_SIZE_T numZoneOnSize,
		IN DSC_SYSTEM_INDEX const* ptrZoneOffData, IN DSC_SIZE_T numZoneOffSize, 
		OUT DSC_IRequestResult** ptrRequestResult);
	IRESULT (ICALL *ITV2_DefaultZoneNotificationSettings)(IN DSC_ISpecificFunctions *This,
		OUT DSC_IRequestResult** ptrRequestResult);

	END_INTERFACE
} DSC_ISpecificFunctions_Vtbl;

DSC_INTERFACE DSC_ISpecificFunctions
{
	//the assumption: the compiler places pointer to VTABLE first in the class layout
 	struct DSC_ISpecificFunctions_Vtbl *ptrVtbl;
};

#endif

//---------------------------------------------------------------------------
} //SECURITY_NAMESPACE
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_I_SPECIFIC_FUNCTIONS_HPP_
