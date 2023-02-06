//---------------------------------------------------------------------------
//
//	DSC_IAlarmTypeContainer.hpp
//
//	Data container for a table of Alarm Types.
//
//---------------------------------------------------------------------------
//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

//includes
#include "DSC_IComponent.hpp"
#include "DSC_AlarmTypes.hpp"

#ifndef _DSC_I_ALARM_TYPE_CONTAINER
#define _DSC_I_ALARM_TYPE_CONTAINER

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#define NAME_DSC_IAlarmTypeContainer	"DSC_IAlarmTypeContainer"

//---------------------------------------------------------------------------

#ifndef DSC_IAlarmTypeContainer_FWD_DEFINED
#define DSC_IAlarmTypeContainer_FWD_DEFINED
typedef DSC_INTERFACE DSC_IAlarmTypeContainer DSC_IAlarmTypeContainer;
#endif

//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

/*!
	This interface provides access to an array containing current alarm types.
*/
DSC_INTERFACE DSC_IAlarmTypeContainer : public DSC_IComponent
{
public:	

    //! Get the size of the list of alarm types
    /*! Returns the current number of alarm types     */
    /*!	
      	\param ptrLength Pointer to storage for the result
    */
	virtual IRESULT ICALL get_NumberOfAlarmTypes(OUT DSC_SIZE_T* ptrLength) const = 0;

    //! Returns an Alarm Type  
    /*! Returns the Alarm Type for the specified list index. Please note that this is not a SystemIndex! This is a 0-based offset
    to an internal list of Alarm Types.      */
    /*!	
		\sa get_NumberOfAlarmTypes
      	\param numIndex Index in the Alarm Types table to reference
		\param ptrAlarmType Pointer to storage for the result.
    */
	virtual IRESULT ICALL get_AlarmType(IN DSC_SIZE_T numIndex, OUT DSC_AlarmType* ptrAlarmType) const = 0;
};

#else

typedef struct DSC_IAlarmTypeContainer_Vtbl
{
	BEGIN_INTERFACE

	IRESULT (ICALL *Query)(IN DSC_IAlarmTypeContainer *This, IN char const* pszInterface, OUT VOID** ptrInterface);
	IRESULT (ICALL *Acquire)(IN DSC_IAlarmTypeContainer *This, OUT ICOUNT* ptrCount);
	IRESULT (ICALL *Release)(IN DSC_IAlarmTypeContainer *This, OUT ICOUNT* ptrCount);

	IRESULT (ICALL *get_NumberOfAlarmTypes)(IN DSC_IAlarmTypeContainer *This, OUT DSC_SIZE_T* ptrLength);
	IRESULT (ICALL *get_AlarmType)(IN DSC_IAlarmTypeContainer *This, IN DSC_SIZE_T numIndex, OUT DSC_AlarmType* ptrAlarmType);

	END_INTERFACE
} DSC_IAlarmTypeContainer_Vtbl;

DSC_INTERFACE DSC_IAlarmTypeContainer
{
	//the assumption: the compiler places pointer to VTABLE first in the class layout
 	struct DSC_IAlarmTypeContainer_Vtbl *ptrVtbl;
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

#endif	//_DSC_I_ALARM_TYPE_CONTAINER
