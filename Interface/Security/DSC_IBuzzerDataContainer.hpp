//---------------------------------------------------------------------------
//
//	DSC_IBuzzerDataContainer.hpp
//
// Data container for "Buzzer" General System message update.
//
//---------------------------------------------------------------------------
//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

//includes
#include "DSC_IComponent.hpp"
#include "DSC_PartitionBuzzerStates.hpp"

#ifndef _DSC_I_BUZZER_DATA_CONTAINER
#define _DSC_I_BUZZER_DATA_CONTAINER

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#define NAME_DSC_IBuzzerDataContainer	"DSC_IBuzzerDataContainer"

//---------------------------------------------------------------------------

#ifndef DSC_IBuzzerDataContainer_FWD_DEFINED
#define DSC_IBuzzerDataContainer_FWD_DEFINED
typedef DSC_INTERFACE DSC_IBuzzerDataContainer DSC_IBuzzerDataContainer;
#endif

//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

/*!
	This interface is used for providing information on the buzzer state.
*/
DSC_INTERFACE DSC_IBuzzerDataContainer : public DSC_IComponent
{
public:	

    //! Get the Partition number for the partition on which the buzzer needs to sound/stop.
    /*! Gets the SystemIndex for the partition on which the buzzer needs to sound/stop. 
		Accordingly, partition = 0 indicates partition for global user interface, for example global keypad.	*/
    /*!	
    	\param ptrPartition Pointer to storage for the partition's system index.
    */	
	virtual IRESULT ICALL get_Partition(OUT DSC_SYSTEM_INDEX* ptrPartition) const = 0;

    //! Get the Buzzer State of this buzzer.
    /*! 	*/
    /*!	
		\sa DSC_PartitionBuzzerStates_Tag
    	\param ptrBuzzer Pointer to storage for the buzzer state.
    */	
	virtual IRESULT ICALL get_BuzzerState(OUT DSC_PartitionBuzzerState* ptrBuzzer) const = 0;

    //! Get the remaining buzer Duration value for the partition.
    /*! 	*/
    /*!	
    	\param ptrDuration Pointer to storage for the buzzer duration.
    */	
	virtual IRESULT ICALL get_Duration(OUT UINT32* ptrDuration) const = 0;
};

#else

typedef struct DSC_IBuzzerDataContainer_Vtbl
{
	BEGIN_INTERFACE

	IRESULT (ICALL *Query)(IN DSC_IBuzzerDataContainer *This, IN char const* pszInterface, OUT VOID** ptrInterface);
	IRESULT (ICALL *Acquire)(IN DSC_IBuzzerDataContainer *This, OUT ICOUNT* ptrCount);
	IRESULT (ICALL *Release)(IN DSC_IBuzzerDataContainer *This, OUT ICOUNT* ptrCount);

	IRESULT (ICALL *get_Partition)(IN DSC_IBuzzerDataContainer *This, OUT DSC_SYSTEM_INDEX* ptrPartition);
	IRESULT (ICALL *get_BuzzerState)(IN DSC_IBuzzerDataContainer *This, OUT DSC_PartitionBuzzerState* ptrBuzzer);
	IRESULT (ICALL *get_Duration)(IN DSC_IBuzzerDataContainer *This, OUT UINT32* ptrDuration);

	END_INTERFACE
} DSC_IBuzzerDataContainer_Vtbl;

DSC_INTERFACE DSC_IBuzzerDataContainer
{
	//the assumption: the compiler places pointer to VTABLE first in the class layout
 	struct DSC_IBuzzerDataContainer_Vtbl *ptrVtbl;
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

#endif	//_DSC_I_BUZZER_DATA_CONTAINER
