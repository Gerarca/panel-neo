//---------------------------------------------------------------------------
//
//	DSC_ILCDUpdateDataContainer.hpp
//
// Data container for "VirtualKeypad_LCDUpdate" General System message update.
//
//---------------------------------------------------------------------------
//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

//includes
#include "DSC_IComponent.hpp"
#include "DSC_TextAttributes.hpp"
#include "DSC_ITextString.hpp"

#ifndef _DSC_I_LCD_UPDATE_DATA_CONTAINER
#define _DSC_I_LCD_UPDATE_DATA_CONTAINER

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#define NAME_DSC_ILCDUpdateDataContainer	"DSC_ILCDUpdateDataContainer"

//---------------------------------------------------------------------------

#ifndef DSC_ILCDUpdateDataContainer_FWD_DEFINED
#define DSC_ILCDUpdateDataContainer_FWD_DEFINED
typedef DSC_INTERFACE DSC_ILCDUpdateDataContainer DSC_ILCDUpdateDataContainer;
#endif

//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

/*!
	This interface is used for providing LCD display data.
*/
DSC_INTERFACE DSC_ILCDUpdateDataContainer : public DSC_IComponent
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

    //! Get the display attributes.
    /*! This property returns the array of attributes for the entire Virtual Keypad's display.
		Each element of the display (a character, a pixe, etc.) has its own attribute information.	*/ 
    /*!	
		\sa DSC_TextAttribute_Tag
    	\param ptrAttributes Pointer to storage for the pointer to the array of attributes.
		\param ptrLength Pointer to storage for the array length information.
    */	
	virtual IRESULT ICALL get_Attributes(
		OUT DSC_TextAttribute const** ptrAttributes, OUT DSC_SIZE_T* ptrLength) const = 0;

    //! Get the horizontal position of the text string.
    /*! 	*/ 
    /*!	
    	\param ptrX Pointer to storage for the position information.
    */	
	virtual IRESULT ICALL get_HorizontalPosition(OUT DSC_SIZE_T* ptrX) const = 0;

    //! Get the vertical position of the text string.
    /*! 	*/ 
    /*!	
    	\param ptrY Pointer to storage for the position information.
    */	
	virtual IRESULT ICALL get_VerticalPosition(OUT DSC_SIZE_T* ptrY) const = 0;

    //! Get the text string being displayed.
    /*! This property is used to get the text that is being displayed at given display's position.	*/ 
    /*!	
    	\param ptrText Pointer to storage for the text string.
    */	
	virtual IRESULT ICALL get_TextString(OUT DSC_ITextString** ptrText) const = 0;
};

#else

typedef struct DSC_ILCDUpdateDataContainer_Vtbl
{
	BEGIN_INTERFACE

	IRESULT (ICALL *Query)(IN DSC_ILCDUpdateDataContainer *This, IN char const* pszInterface, OUT VOID** ptrInterface);
	IRESULT (ICALL *Acquire)(IN DSC_ILCDUpdateDataContainer *This, OUT ICOUNT* ptrCount);
	IRESULT (ICALL *Release)(IN DSC_ILCDUpdateDataContainer *This, OUT ICOUNT* ptrCount);

	IRESULT (ICALL *get_SystemIndex)(IN DSC_ILCDUpdateDataContainer *This, OUT DSC_SYSTEM_INDEX* ptrSystemIndex);
	IRESULT (ICALL *get_Partition)(IN DSC_ILCDUpdateDataContainer *This, OUT DSC_SYSTEM_INDEX* ptrPartition);
	IRESULT (ICALL *get_Attributes)(IN DSC_ILCDUpdateDataContainer *This, 
		OUT DSC_TextAttribute const** ptrAttributes, OUT DSC_SIZE_T* ptrLength);
	IRESULT (ICALL *get_HorizontalPosition)(IN DSC_ILCDUpdateDataContainer *This, OUT DSC_SIZE_T* ptrX);
	IRESULT (ICALL *get_VerticalPosition)(IN DSC_ILCDUpdateDataContainer *This, OUT DSC_SIZE_T* ptrY);
	IRESULT (ICALL *get_TextString)(IN DSC_ILCDUpdateDataContainer *This, OUT DSC_ITextString** ptrText);

	END_INTERFACE
} DSC_ILCDUpdateDataContainer_Vtbl;

DSC_INTERFACE DSC_ILCDUpdateDataContainer
{
	//the assumption: the compiler places pointer to VTABLE first in the class layout
 	struct DSC_ILCDUpdateDataContainer_Vtbl *ptrVtbl;
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

#endif	//_DSC_I_LCD_UPDATE_DATA_CONTAINER
