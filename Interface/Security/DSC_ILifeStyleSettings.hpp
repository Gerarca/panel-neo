//---------------------------------------------------------------------------
//
//	DSC_ILifeStyleSettings.hpp
//  Copyright 2021 Johnson Controls. All rights reserved.
//
//	The interface for implementing an array of LifeStyleNotifications.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_IComponent.hpp"
#include "DSC_LifeStyleNotifications.hpp"
#include "DSC_ITextString.hpp"
#include "DSC_IDataBuffer.hpp"

#ifndef _DSC_I_LIFESTYLE_SETTINGS_HPP_
#define _DSC_I_LIFESTYLE_SETTINGS_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

//The implementation must be thread safe.
#define NAME_DSC_ILifeStyleSettings	"DSC_ILifeStyleSettings"

//---------------------------------------------------------------------------

#ifndef DSC_ILifeStyleSettings_FWD_DEFINED
#define DSC_ILifeStyleSettings_FWD_DEFINED
typedef DSC_INTERFACE DSC_ILifeStyleSettings DSC_ILifeStyleSettings;
#endif

//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

/*!
	This interface is used to access and manipulate an array of LifeStyle Notification settings
*/
DSC_INTERFACE DSC_ILifeStyleSettings : public DSC_IComponent
{
public:

	//! Gets the number of settings stored in the list
    /*!	
     	\param ptrCount Pointer to DSC_SIZE_T that contains the number of settings stored.
    */
	virtual IRESULT ICALL get_Size(OUT DSC_SIZE_T* ptrCount) const = 0;

	//! Gets the pointer to the selected setting
    /*!	
		\param numIndex The 0 based array index of the setting you wish to get from the list.
     	\param ptrSetting Pointer to storage for the requested LifeStyle Notification setting.
    */
	virtual IRESULT ICALL get_Setting(IN DSC_SIZE_T numIndex, 
		OUT DSC_LifeStyleNotification* ptrSetting) const = 0;

	//! Clears all the settings stored in the list
    /*!	
    */
	virtual IRESULT ICALL Clear(VOID) = 0;

	//! Adds new settings to the list
    /*!	
     	\param flgSetting Provided LifeStyle Notification setting to be added to the list.
    */
	virtual IRESULT ICALL Add(
		IN DSC_LifeStyleNotification flgSetting) = 0;

	//! Inserts new setting in to the list at a given position
    /*!	
		\param numIndex The 0 based list index to insert the new setting.
     	\param flgSetting Provided LifeStyle Notification setting to be inserted in list.
    */
	virtual IRESULT ICALL InsertAt(IN DSC_SIZE_T numIndex, 
		IN DSC_LifeStyleNotification flgSetting) = 0;

	//! Removes the setting from the list at given position.
    /*!	
		\param numIndex The 0 based list index of the LifeStyle Notification setting to remove.
    */
	virtual IRESULT ICALL RemoveAt(IN DSC_SIZE_T numIndex) = 0;

	//! Checks if the list contains a given LifeStyle Notification setting
    /*!	
		\param flgSetting Provided LifeStyle Notification setting to look for in the list.
		\param result Pointer to storage for the result of the check.
    */
	virtual IRESULT ICALL Contains(IN DSC_LifeStyleNotification flgSetting, OUT BOOL* result) = 0;
};

#else

typedef struct DSC_ISystemIndices_Vtbl
{
	BEGIN_INTERFACE

	IRESULT (ICALL *Query)(IN DSC_ILifeStyleSettings *This, IN char const* pszInterface, OUT VOID** ptrInterface);
	IRESULT (ICALL *Acquire)(IN DSC_ILifeStyleSettings *This, OUT ICOUNT* ptrCount);
	IRESULT (ICALL *Release)(IN DSC_ILifeStyleSettings *This, OUT ICOUNT* ptrCount);

	IRESULT (ICALL *get_Size)(IN DSC_ILifeStyleSettings *This, OUT DSC_SIZE_T* ptrCount);
	IRESULT (ICALL *get_Setting)(IN DSC_ILifeStyleSettings *This, 
		IN DSC_SIZE_T numIndex, OUT DSC_LifeStyleNotification* ptrSetting);
	IRESULT (ICALL *Clear)(IN DSC_ILifeStyleSettings *This);
	IRESULT (ICALL *Add)(IN DSC_ILifeStyleSettings *This, 
		IN DSC_LifeStyleNotification flgSetting);
	IRESULT (ICALL *InsertAt)(IN DSC_ILifeStyleSettings *This, 
		IN DSC_SIZE_T numIndex, IN DSC_LifeStyleNotification flgSetting);
	IRESULT (ICALL *RemoveAt)(IN DSC_ILifeStyleSettings *This, IN DSC_SIZE_T numIndex);
	IRESULT (ICALL *Contains)(IN DSC_ILifeStyleSettings *This, 
		IN DSC_LifeStyleNotification flgSetting, OUT BOOL* result);

	END_INTERFACE
} DSC_ILifeStyleSettings_Vtbl;

DSC_INTERFACE DSC_ILifeStyleSettings
{
	//the assumption: the compiler places pointer to VTABLE first in the class layout
 	struct DSC_ILifeStyleSettings_Vtbl *ptrVtbl;
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

#endif	//_DSC_I_LIFESTYLE_SETTINGS_HPP_
