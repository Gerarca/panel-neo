//---------------------------------------------------------------------------
//
//	DSC_ILCDCursorDataContainer.hpp
//
// Data container for "VirtualKeypad_LCDCursor" General System message update.
//
//---------------------------------------------------------------------------
//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

//includes
#include "DSC_IComponent.hpp"
#include "DSC_CursorTypes.hpp"

#ifndef _DSC_I_LCD_CURSOR_DATA_CONTAINER
#define _DSC_I_LCD_CURSOR_DATA_CONTAINER

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#define NAME_DSC_ILCDCursorDataContainer	"DSC_ILCDCursorDataContainer"

//---------------------------------------------------------------------------

#ifndef DSC_ILCDCursorDataContainer_FWD_DEFINED
#define DSC_ILCDCursorDataContainer_FWD_DEFINED
typedef DSC_INTERFACE DSC_ILCDCursorDataContainer DSC_ILCDCursorDataContainer;
#endif

//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

/*!
	This interface is used for providing information on the current
	position of the LCD display's cursor.
*/
DSC_INTERFACE DSC_ILCDCursorDataContainer : public DSC_IComponent
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

    //! Get the cursor horizontal position.
    /*! 	*/ 
    /*!	
    	\param ptrX Pointer to storage for the position information.
    */	
	virtual IRESULT ICALL get_HorizontalPosition(OUT DSC_SIZE_T* ptrX) const = 0;

    //! Get the cursor vertical position.
    /*! 	*/ 
    /*!	
    	\param ptrY Pointer to storage for the position information.
    */	
	virtual IRESULT ICALL get_VerticalPosition(OUT DSC_SIZE_T* ptrY) const = 0;

    //! Get the cursor type information.
    /*! 	*/ 
    /*!	
		\sa DSC_CursorType_Tag
    	\param ptrCursor Pointer to storage for the type information.
    */	
	virtual IRESULT ICALL get_CursorType(OUT DSC_CursorType* ptrCursor) const = 0;
};

#else

typedef struct DSC_ILCDCursorDataContainer_Vtbl
{
	BEGIN_INTERFACE

	IRESULT (ICALL *Query)(IN DSC_ILCDCursorDataContainer *This, IN char const* pszInterface, OUT VOID** ptrInterface);
	IRESULT (ICALL *Acquire)(IN DSC_ILCDCursorDataContainer *This, OUT ICOUNT* ptrCount);
	IRESULT (ICALL *Release)(IN DSC_ILCDCursorDataContainer *This, OUT ICOUNT* ptrCount);

	IRESULT (ICALL *get_SystemIndex)(IN DSC_ILCDCursorDataContainer *This, OUT DSC_SYSTEM_INDEX* ptrSystemIndex);
	IRESULT (ICALL *get_Partition)(IN DSC_ILCDCursorDataContainer *This, OUT DSC_SYSTEM_INDEX* ptrPartition);
	IRESULT (ICALL *get_HorizontalPosition)(IN DSC_ILCDCursorDataContainer *This, OUT DSC_SIZE_T* ptrX);
	IRESULT (ICALL *get_VerticalPosition)(IN DSC_ILCDCursorDataContainer *This, OUT DSC_SIZE_T* ptrY);
	IRESULT (ICALL *get_CursorType)(IN DSC_ILCDCursorDataContainer *This, OUT DSC_CursorType* ptrCursor);

	END_INTERFACE
} DSC_ILCDCursorDataContainer_Vtbl;

DSC_INTERFACE DSC_ILCDCursorDataContainer
{
	//the assumption: the compiler places pointer to VTABLE first in the class layout
 	struct DSC_ILCDCursorDataContainer_Vtbl *ptrVtbl;
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

#endif	//_DSC_I_LCD_CURSOR_DATA_CONTAINER
