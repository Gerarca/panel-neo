//---------------------------------------------------------------------------
//
//	DSC_IKeyPressedDataContainer.hpp
//
// Data container for "VirtualKeypad_KeyPress" General System message update.
//
//---------------------------------------------------------------------------
//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

//includes
#include "DSC_IComponent.hpp"
#include "DSC_VirtualKeypadKeys.hpp"

#ifndef _DSC_I_KEY_PRESSED_DATA_CONTAINER
#define _DSC_I_KEY_PRESSED_DATA_CONTAINER

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#define NAME_DSC_IKeyPressedDataContainer	"DSC_IKeyPressedDataContainer"

//---------------------------------------------------------------------------

#ifndef DSC_IKeyPressedDataContainer_FWD_DEFINED
#define DSC_IKeyPressedDataContainer_FWD_DEFINED
typedef DSC_INTERFACE DSC_IKeyPressedDataContainer DSC_IKeyPressedDataContainer;
#endif

//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

/*!
	This interface is used for providing information on key presses
	in the system.
*/
DSC_INTERFACE DSC_IKeyPressedDataContainer : public DSC_IComponent
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

    //! Get the code of the key that was pressed on the keypad.
    /*! 	*/ 
    /*!	
		\sa DSC_VirtualKeypadKey_Tag
    	\param ptrKey Pointer to storage for the key code.
    */	
	virtual IRESULT ICALL get_KeyPressed(OUT DSC_VirtualKeypadKey* ptrKey) const = 0;
};

#else

typedef struct DSC_IKeyPressedDataContainer_Vtbl
{
	BEGIN_INTERFACE

	IRESULT (ICALL *Query)(IN DSC_IKeyPressedDataContainer *This, IN char const* pszInterface, OUT VOID** ptrInterface);
	IRESULT (ICALL *Acquire)(IN DSC_IKeyPressedDataContainer *This, OUT ICOUNT* ptrCount);
	IRESULT (ICALL *Release)(IN DSC_IKeyPressedDataContainer *This, OUT ICOUNT* ptrCount);

	IRESULT (ICALL *get_SystemIndex)(IN DSC_IKeyPressedDataContainer *This, OUT DSC_SYSTEM_INDEX* ptrSystemIndex);
	IRESULT (ICALL *get_Partition)(IN DSC_IKeyPressedDataContainer *This, OUT DSC_SYSTEM_INDEX* ptrPartition);
	IRESULT (ICALL *get_KeyPressed)(IN DSC_IKeyPressedDataContainer *This, OUT DSC_VirtualKeypadKey* ptrKey);

	END_INTERFACE
} DSC_IKeyPressedDataContainer_Vtbl;

DSC_INTERFACE DSC_IKeyPressedDataContainer
{
	//the assumption: the compiler places pointer to VTABLE first in the class layout
 	struct DSC_IKeyPressedDataContainer_Vtbl *ptrVtbl;
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

#endif	//_DSC_I_KEY_PRESSED_DATA_CONTAINER
