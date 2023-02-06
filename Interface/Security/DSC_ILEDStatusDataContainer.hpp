//---------------------------------------------------------------------------
//
//	DSC_ILEDStatusDataContainer.hpp
//
// Data container for "VirtualKeypad_LEDStatus" General System message update.
//
//---------------------------------------------------------------------------
//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

//includes
#include "DSC_IComponent.hpp"
#include "DSC_LEDTypes.hpp"
#include "DSC_LEDCadences.hpp"

#ifndef _DSC_I_LED_STATUS_DATA_CONTAINER
#define _DSC_I_LED_STATUS_DATA_CONTAINER

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#define NAME_DSC_ILEDStatusDataContainer	"DSC_ILEDStatusDataContainer"

//---------------------------------------------------------------------------

#ifndef DSC_ILEDStatusDataContainer_FWD_DEFINED
#define DSC_ILEDStatusDataContainer_FWD_DEFINED
typedef DSC_INTERFACE DSC_ILEDStatusDataContainer DSC_ILEDStatusDataContainer;
#endif

//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

/*!
	This interface is used for providing information on the LED statuses.
*/
DSC_INTERFACE DSC_ILEDStatusDataContainer : public DSC_IComponent
{
public:		

    //! Get the Virtual Keypad number of the keypad.
    /*! Gets the SystemIndex assigned to the Virtual Kaypad by the system.	*/ 
    /*!	
    	\param ptrSystemIndex Pointer to storage for the system index.
    */	
	virtual IRESULT ICALL get_SystemIndex(OUT DSC_SYSTEM_INDEX* ptrSystemIndex) const = 0;

    //! Get the Partition number for the partition to which the Virtual Keypad is assigned.
    /*! Gets the SystemIndex for the partition the Virtual Keypad is assigned to. 
		Accordingly, partition = 0 indicates partition for global user interface, for example global keypad.	*/
    /*!	
    	\param ptrPartition Pointer to storage for the partition's system index.
    */	
	virtual IRESULT ICALL get_Partition(OUT DSC_SYSTEM_INDEX* ptrPartition) const = 0;

    //! Get the LED Type code.
    /*! 	*/ 
    /*!	
		\sa DSC_LEDType_Tag
    	\param ptrType Pointer to storage for the LED type.
    */	
	virtual IRESULT ICALL get_Type(OUT DSC_LEDType* ptrType) const = 0;

    //! Get the LED Cadence information.
    /*! 	*/ 
    /*!	
		\sa DSC_LEDCadence_Tag
    	\param ptrCadence Pointer to storage for the LED cadence information.
    */	
	virtual IRESULT ICALL get_Cadence(OUT DSC_LEDCadence* ptrCadence) const = 0;
};

#else

typedef struct DSC_ILEDStatusDataContainer_Vtbl
{
	BEGIN_INTERFACE

	IRESULT (ICALL *Query)(IN DSC_ILEDStatusDataContainer *This, IN char const* pszInterface, OUT VOID** ptrInterface);
	IRESULT (ICALL *Acquire)(IN DSC_ILEDStatusDataContainer *This, OUT ICOUNT* ptrCount);
	IRESULT (ICALL *Release)(IN DSC_ILEDStatusDataContainer *This, OUT ICOUNT* ptrCount);

	IRESULT (ICALL *get_SystemIndex)(IN DSC_ILEDStatusDataContainer *This, OUT DSC_SYSTEM_INDEX* ptrSystemIndex);
	IRESULT (ICALL *get_Partition)(IN DSC_ILEDStatusDataContainer *This, OUT DSC_SYSTEM_INDEX* ptrPartition);
	IRESULT (ICALL *get_Type)(IN DSC_ILEDStatusDataContainer *This, OUT DSC_LEDType* ptrType);
	IRESULT (ICALL *get_Cadence)(IN DSC_ILEDStatusDataContainer *This, OUT DSC_LEDCadence* ptrCadence);

	END_INTERFACE
} DSC_ILEDStatusDataContainer_Vtbl;

DSC_INTERFACE DSC_ILEDStatusDataContainer
{
	//the assumption: the compiler places pointer to VTABLE first in the class layout
 	struct DSC_ILEDStatusDataContainer_Vtbl *ptrVtbl;
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

#endif	//_DSC_I_LED_STATUS_DATA_CONTAINER
