//---------------------------------------------------------------------------
//
//	DSC_IVirtualKeypad.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_IComponent.hpp"
#include "DSC_VirtualKeypadModes.hpp"
#include "DSC_VirtualKeypadTypes.hpp"
#include "DSC_IRequestResult.hpp"
#include "DSC_VirtualKeypadKeys.hpp"

#ifndef _DSC_I_VIRTUAL_KEYPAD_HPP_
#define _DSC_I_VIRTUAL_KEYPAD_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#define NAME_DSC_IVirtualKeypad	"DSC_IVirtualKeypad"

//---------------------------------------------------------------------------

#ifndef DSC_IVirtualKeypad_FWD_DEFINED
#define DSC_IVirtualKeypad_FWD_DEFINED
typedef DSC_INTERFACE DSC_IVirtualKeypad DSC_IVirtualKeypad;
#endif

//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

/*!
	This interface is used to provide virtual keypad capability.
*/
DSC_INTERFACE DSC_IVirtualKeypad : public DSC_IComponent
{
public:

    //! Get the Virtual Keypad System Index
    /*! Gets the SystemIndex for the Virtual Keypad as assigned by the panel.	
	    For example, Virtual Keypad 1 would return system index 1.     */ 
    /*!	
    	\param ptrSystemIndex Pointer to storage for the Virtual Keypad System Index
    */	
	virtual IRESULT ICALL get_SystemIndex(OUT DSC_SYSTEM_INDEX* ptrSystemIndex) const = 0;

    //! Get the Partition
    /*! Gets the SystemIndex for the partition the Virtual Keypad is assigned to. */
    /*!	
    	\param ptrPartition Pointer to storage for the Partition System Index.
    */	
	virtual IRESULT ICALL get_Partition(OUT DSC_SYSTEM_INDEX* ptrPartition) const = 0;

    //! Get the Mode
    /*! Gets the mode of operation for the Virtual Keypad.	*/ 
    /*!	
		\sa enum DSC_VirtualKeypadMode_Tag
    	\param ptrMode Pointer to storage for the mode information.
    */	
	virtual IRESULT ICALL get_Mode(OUT DSC_VirtualKeypadMode* ptrMode) const = 0;

    //! Get the Type
    /*! Gets the type of Virtual Keypad.	*/ 
    /*!	
		\sa enum DSC_VirtualKeypadType_Tag
    	\param ptrType Pointer to storage for the type information.
    */	
	virtual IRESULT ICALL get_Type(OUT DSC_VirtualKeypadType* ptrType) const = 0;

    //! Get the Width
    /*! Gets the width information of the Virtual Keypad.	*/ 
    /*!	
    	\param ptrCount Pointer to storage for the width information.
    */	
	virtual IRESULT ICALL get_Width(OUT DSC_SIZE_T* ptrCount) const = 0;

    //! Get the Height
    /*! Gets the height information of the Virtual Keypad.	*/ 
    /*!	
    	\param ptrCount Pointer to storage for the height information.
    */	
	virtual IRESULT ICALL get_Height(OUT DSC_SIZE_T* ptrCount) const = 0;

	//! Configure the Virtual Keypad. 
	/*! Will issue the requisite commands to configure the created Virtual Keypad so it can be used. 
		This function may be called multiple times for the same Virtual Keypad to change 
		keypad's partion assignment and/or mode of operation.	*/
	/*!
		\sa enum DSC_VirtualKeypadMode_Tag
		\param numPartition The Partition System Index to which the Virtual Keypad should be assigned.
		\param flgMode The requested mode of operation for the Virtual Keypad. 
		\param ptrRequestResult Pointer to storage for the result of the operation.
	*/
	virtual IRESULT ICALL Configure(IN DSC_SYSTEM_INDEX numPartition, 
		IN DSC_VirtualKeypadMode flgMode, OUT DSC_IRequestResult** ptrRequestResult) = 0;

    //! Generate a Virtual Keypad KeyPress
    /*! Will issue the requisite commands to signal that a Virtual Keypad key has been pressed.	*/ 
    /*!	
		\sa DSC_VirtualKeypadKey_Tag
    	\param flgKey Provided key code to signal a keypress for.
		\param ptrRequestResult Pointer to storage for the result of the operation.
    */	
	virtual IRESULT ICALL KeyPress(
		IN DSC_VirtualKeypadKey flgKey, OUT DSC_IRequestResult** ptrRequestResult) = 0;
};

#else

typedef struct DSC_IVirtualKeypad_Vtbl
{
	BEGIN_INTERFACE

	IRESULT (ICALL *Query)(IN DSC_IVirtualKeypad *This, IN char const* pszInterface, OUT VOID** ptrInterface);
	IRESULT (ICALL *Acquire)(IN DSC_IVirtualKeypad *This, OUT ICOUNT* ptrCount);
	IRESULT (ICALL *Release)(IN DSC_IVirtualKeypad *This, OUT ICOUNT* ptrCount);

	IRESULT (ICALL *get_SystemIndex)(IN DSC_IVirtualKeypad *This, OUT DSC_SYSTEM_INDEX* ptrSystemIndex);
	IRESULT (ICALL *get_Partition)(IN DSC_IVirtualKeypad *This, OUT DSC_SYSTEM_INDEX* ptrPartition);
	IRESULT (ICALL *get_Mode)(IN DSC_IVirtualKeypad *This, OUT DSC_VirtualKeypadMode* ptrMode);
	IRESULT (ICALL *get_Type)(IN DSC_IVirtualKeypad *This, OUT DSC_VirtualKeypadType* ptrType);
	IRESULT (ICALL *get_Width)(IN DSC_IVirtualKeypad *This, OUT DSC_SIZE_T* ptrCount);
	IRESULT (ICALL *get_Height)(IN DSC_IVirtualKeypad *This, OUT DSC_SIZE_T* ptrCount);
	IRESULT (ICALL *Configure)(IN DSC_IVirtualKeypad *This, IN DSC_SYSTEM_INDEX numPartition, 
		IN DSC_VirtualKeypadMode flgMode, OUT DSC_IRequestResult** ptrRequestResult);
	IRESULT (ICALL *KeyPress)(IN DSC_IVirtualKeypad *This, 
		IN DSC_VirtualKeypadKey flgKey, OUT DSC_IRequestResult** ptrRequestResult);

	END_INTERFACE
} DSC_IVirtualKeypad_Vtbl;

DSC_INTERFACE DSC_IVirtualKeypad
{
	//the assumption: the compiler places pointer to VTABLE first in the class layout
 	struct DSC_IVirtualKeypad_Vtbl *ptrVtbl;
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

#endif	//_DSC_I_VIRTUAL_KEYPAD_HPP_
