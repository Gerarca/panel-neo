//---------------------------------------------------------------------------
//
//	DSC_ICommandOutputDataContainer.hpp
//
// Data container for "CommandOutput" General System message update.
//
//---------------------------------------------------------------------------
//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

//includes
#include "DSC_IComponent.hpp"
#include "DSC_ISystemIndices.hpp"
#include "DSC_CommandOutputReportingStates.hpp"

#ifndef _DSC_I_COMMAND_OUTPUT_DATA_CONTAINER
#define _DSC_I_COMMAND_OUTPUT_DATA_CONTAINER

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#define NAME_DSC_ICommandOutputDataContainer	"DSC_ICommandOutputDataContainer"

//---------------------------------------------------------------------------

#ifndef DSC_ICommandOutputDataContainer_FWD_DEFINED
#define DSC_ICommandOutputDataContainer_FWD_DEFINED
typedef DSC_INTERFACE DSC_ICommandOutputDataContainer DSC_ICommandOutputDataContainer;
#endif

//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

/*!
	This interface is used for providing information on command outputs
	in the system.
*/
DSC_INTERFACE DSC_ICommandOutputDataContainer : public DSC_IComponent
{
public:	

    //! Get the partitions of the Command Output.
    /*!	
    	\param ptrPartitions Pointer to storage for the command output partitions.
    */	
	virtual IRESULT ICALL get_CommandOutputPartitions(OUT DSC_ISystemIndices** ptrPartitions) const = 0;

    //! Get the output number of the Command Output.
    /*!	
    	\param ptrOutputNumber Pointer to storage for the command output number.
    */	
	virtual IRESULT ICALL get_CommandOutputNumber(OUT DSC_SYSTEM_INDEX* ptrOutputNumber) const = 0;

    //! Get the status of the Command Output.
    /*! 	*/ 
    /*!	
		\sa DSC_CommandOutputStatus_Tag
    	\param ptrOutputStatus Pointer to storage for the command output status.
    */	
	virtual IRESULT ICALL get_CommandOutputState(OUT DSC_CommandOutputReportingState* ptrOutputState) const = 0;
};

#else

typedef struct DSC_ICommandOutputDataContainer_Vtbl
{
	BEGIN_INTERFACE

	IRESULT (ICALL *Query)(IN DSC_ICommandOutputDataContainer *This, IN char const* pszInterface, OUT VOID** ptrInterface);
	IRESULT (ICALL *Acquire)(IN DSC_ICommandOutputDataContainer *This, OUT ICOUNT* ptrCount);
	IRESULT (ICALL *Release)(IN DSC_ICommandOutputDataContainer *This, OUT ICOUNT* ptrCount);

	IRESULT (ICALL *get_CommandOutputPartitions(IN DSC_ICommandOutputDataContainer *This, OUT DSC_ISystemIndices** ptrPartitions);
	IRESULT (ICALL *get_CommandOutputNumber)(IN DSC_ICommandOutputDataContainer *This, OUT DSC_SYSTEM_INDEX* ptrOutputNumber);
	IRESULT (ICALL *get_CommandOutputState)(IN DSC_ICommandOutputDataContainer *This, OUT DSC_CommandOutputReportingState* ptrOutputState);

	END_INTERFACE
} DSC_ICommandOutputDataContainer_Vtbl;

DSC_INTERFACE DSC_ICommandOutputDataContainer
{
	//the assumption: the compiler places pointer to VTABLE first in the class layout
 	struct DSC_ICommandOutputDataContainer_Vtbl *ptrVtbl;
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

#endif	//_DSC_I_COMMAND_OUTPUT_DATA_CONTAINER
