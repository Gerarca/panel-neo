//---------------------------------------------------------------------------
//
//	DSC_ITroubleData.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_IComponent.hpp"
#include "DSC_DeviceModuleTypes.hpp"
#include "DSC_TroubleTypes.hpp"
#include "DSC_TroubleStates.hpp"

#ifndef _DSC_I_TROUBLE_DATA_HPP_
#define _DSC_I_TROUBLE_DATA_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#define NAME_DSC_ITroubleData	"DSC_ITroubleData"

//---------------------------------------------------------------------------

#ifndef DSC_ITroubleData_FWD_DEFINED
#define DSC_ITroubleData_FWD_DEFINED
typedef DSC_INTERFACE DSC_ITroubleData DSC_ITroubleData;
#endif

//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

/*!
	This interface is used with the general event notification for
	providing trouble information.
*/
DSC_INTERFACE DSC_ITroubleData : public DSC_IComponent
{
public:

    //! Get the value indicating the type of the device or module that is in trouble state. 
    /*! Returns the device or module type that is in the trouble state. */
    /*!	
		\sa enum DSC_DeviceModuleType_Tag
      	\param ptrType Pointer to storage for the DSC_DeviceModuleType value.
    */
	virtual IRESULT ICALL get_DeviceModuleType(OUT DSC_DeviceModuleType* ptrDeviceModuleType) const = 0;

    //! Get the Device or Module system index.
    /*! Get the system index for the device or module. */
    /*!	
      	\param ptrNumber Pointer to storage for the Device or Module system index.
    */
	virtual IRESULT ICALL get_DeviceModuleNumber(OUT DSC_SYSTEM_INDEX* ptrNumber) const = 0;

    //! Get the value indicating the type of the trouble. 
    /*! This property returns one of the DSC_TroubleType enum values to indicate the type of the trouble. */
    /*!	
		\sa enum DSC_TroubleType_Tag
      	\param ptrTroubleType Pointer to storage for the DSC_TroubleType value.
    */
	virtual IRESULT ICALL get_TroubleType(OUT DSC_TroubleType* ptrTroubleType) const = 0;

    //! Get the value indicating the trouble state. 
    /*! This property returns one of the DSC_TroubleState enum values to indicate the trouble state. */  
    /*!	
		\sa enum DSC_TroubleState_Tag
      	\param ptrTroubleState Pointer to storage for the DSC_TroubleState value.
    */
	virtual IRESULT ICALL get_TroubleStatus(OUT DSC_TroubleState* ptrTroubleState) const = 0;
};

#else

typedef struct DSC_ITroubleData_Vtbl
{
	BEGIN_INTERFACE

	IRESULT (ICALL *Query)(IN DSC_ITroubleData *This, IN char const* pszInterface, OUT VOID** ptrInterface);
	IRESULT (ICALL *Acquire)(IN DSC_ITroubleData *This, OUT ICOUNT* ptrCount);
	IRESULT (ICALL *Release)(IN DSC_ITroubleData *This, OUT ICOUNT* ptrCount);

	IRESULT (ICALL *get_DeviceModuleType)(IN DSC_ITroubleData *This, 
		OUT DSC_DeviceModuleType* ptrDeviceModuleType);
	IRESULT (ICALL *get_DeviceModuleNumber)(IN DSC_ITroubleData *This, 
		OUT DSC_SYSTEM_INDEX* ptrNumber);
	IRESULT (ICALL *get_TroubleType)(IN DSC_ITroubleData *This, 
		OUT DSC_TroubleType* ptrTroubleType);
	IRESULT (ICALL *get_TroubleStatus)(IN DSC_ITroubleData *This, 
		OUT DSC_TroubleState* ptrTroubleState);

	END_INTERFACE
} DSC_ITroubleData_Vtbl;

DSC_INTERFACE DSC_ITroubleData
{
	//the assumption: the compiler places pointer to VTABLE first in the class layout
 	struct DSC_ITroubleData_Vtbl *ptrVtbl;
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

#endif	//_DSC_I_TROUBLE_DATA_HPP_
