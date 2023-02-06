//---------------------------------------------------------------------------
//
//	DSC_IProgrammingDataContainer.hpp
//	Copyright 2017 Johnson Controls. All rights reserved.
//
//	Data container for "Programming" General System message update.
//
//---------------------------------------------------------------------------
//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

//includes
#include "DSC_IComponent.hpp"
#include "DSC_ProgrammingModes.hpp"
#include "DSC_ProgrammingSources.hpp"
#include "DSC_ProgrammingStates.hpp"

#ifndef _DSC_I_PROGRAMMING_DATA_CONTAINER
#define _DSC_I_PROGRAMMING_DATA_CONTAINER

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#define NAME_DSC_IProgrammingDataContainer	"DSC_IProgrammingDataContainer"

//---------------------------------------------------------------------------

#ifndef DSC_IProgrammingDataContainer_FWD_DEFINED
#define DSC_IProgrammingDataContainer_FWD_DEFINED
typedef DSC_INTERFACE DSC_IProgrammingDataContainer DSC_IProgrammingDataContainer;
#endif

//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

/*!
	This interface is used for providing programming data details.
*/
DSC_INTERFACE DSC_IProgrammingDataContainer : public DSC_IComponent
{
public:		

    //! Programming State Change Data Container - Programming Mode
    /*! This data container is presented to you whenever the Target System's programming mode change. 
    This can occur due to the SDK specifically initiating an action that requires programming level access (e.g. Change Zone Label),
    or, more importantly, whenever 'something' happens at the target outside of the SDK (e.g. via a local keypad), thus indicating to you
    that there may, or may not be changes made to the system that may or may not require a refresh of the SDK.   */
    /*!	
      	\param ptrProgrammingMode - Pointer to enum containing what mode the system has changed to (Installer, User etc);
        \sa DSC_ProgrammingMode_Tag
    */
	virtual IRESULT ICALL get_ProgrammingMode(OUT DSC_ProgrammingMode* ptrProgrammingMode) const = 0;

    //! Programming State Change Data Container - Programming State
    /*! This data container is presented to you whenever the Target System's programming mode change. 
    This can occur due to the SDK specifically initiating an action that requires programming level access (e.g. Change Zone Label),
    or, more importantly, whenever 'something' happens at the target outside of the SDK (e.g. via a local keypad), thus indicating to you
    that there may, or may not be changes made to the system that may or may not require a refresh of the SDK.   */
    /*!	
      	\param ptrProgrammingState - Pointer to enum containing what mode state system programming has changed to (Begin / End);
        \sa DSC_ProgrammingState_Tag
    */
	virtual IRESULT ICALL get_ProgrammingState(OUT DSC_ProgrammingState* ptrProgrammingState) const = 0;

    //! Programming State Change Data Container - Programming Source
    /*! This data container is presented to you whenever the Target System's programming mode change. 
    This can occur due to the SDK specifically initiating an action that requires programming level access (e.g. Change Zone Label),
    or, more importantly, whenever 'something' happens at the target outside of the SDK (e.g. via a local keypad), thus indicating to you
    that there may, or may not be changes made to the system that may or may not require a refresh of the SDK.   */
    /*!	
      	\param ptrProgrammingSource - Pointer to enum containing what the source of this state change is (e.g. local, remote, DLS);
        \sa DSC_ProgrammingSource_Tag
    */
	virtual IRESULT ICALL get_ProgrammingSource(OUT DSC_ProgrammingSource* ptrProgrammingSource) const = 0;
};

#else

typedef struct DSC_IProgrammingDataContainer_Vtbl
{
	BEGIN_INTERFACE

	IRESULT (ICALL *Query)(IN DSC_IProgrammingDataContainer *This, IN char const* pszInterface, OUT VOID** ptrInterface);
	IRESULT (ICALL *Acquire)(IN DSC_IProgrammingDataContainer *This, OUT ICOUNT* ptrCount);
	IRESULT (ICALL *Release)(IN DSC_IProgrammingDataContainer *This, OUT ICOUNT* ptrCount);

	IRESULT (ICALL *get_ProgrammingMode)(IN DSC_IProgrammingDataContainer *This, OUT DSC_ProgrammingMode* ptrProgrammingMode);
	IRESULT (ICALL *get_ProgrammingState)(IN DSC_IProgrammingDataContainer *This, OUT DSC_ProgrammingState* ptrProgrammingState);
	IRESULT (ICALL *get_ProgrammingSource)(IN DSC_IProgrammingDataContainer *This, OUT DSC_ProgrammingSource* ptrProgrammingSource);

	END_INTERFACE
} DSC_IProgrammingDataContainer_Vtbl;

DSC_INTERFACE DSC_IProgrammingDataContainer
{
	//the assumption: the compiler places pointer to VTABLE first in the class layout
 	struct DSC_IProgrammingDataContainer_Vtbl *ptrVtbl;
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

#endif	//_DSC_I_PROGRAMMING_DATA_CONTAINER
