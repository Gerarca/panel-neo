//---------------------------------------------------------------------------
//
//	DSC_IRequestResult.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_IComponent.hpp"
#include "DSC_RequestResultCodes.hpp"
#include "DSC_ITextString.hpp"
#include "DSC_IDataBuffer.hpp"

#ifndef _DSC_I_REQUEST_RESULT_HPP_
#define _DSC_I_REQUEST_RESULT_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#define NAME_DSC_IRequestResult	"DSC_IRequestResult"

//---------------------------------------------------------------------------

#ifndef DSC_IRequestResult_FWD_DEFINED
#define DSC_IRequestResult_FWD_DEFINED
typedef DSC_INTERFACE DSC_IRequestResult DSC_IRequestResult;
#endif

//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

/*!
	This interface is used to obtain details about results of various
	SDK function calls.
*/
DSC_INTERFACE DSC_IRequestResult : public DSC_IComponent
{
public:
	
    //! Get ReadWriteResultCode
    /*! Returns the result code from a read or write operation. */
    /*!	
		\sa enum DSC_RequestResultCode_Tag
      	\param ptrResultCode Pointer to storage for ResultCode.
    */
	virtual IRESULT ICALL get_ReadWriteResultCode(OUT DSC_RequestResultCode* ptrResultCode) const = 0;

    //! Get ResultDescription
    /*! May contain a verbose textual description of a result code where applicable e.g. "Memory Allocation Error".     */
	/*! UTF8 Null terminated string. */
    /*!	
      	\param pszDescription Pointer to storage for a text string containing the verbose description.
    */
	virtual IRESULT ICALL get_ResultDescription(OUT DSC_ITextString** pszDescription) const = 0;

	//! Get ExtendedData
	/*! Returns the data sent/received for the read or write operation. */
	/*!
		\sa DSC_IDataBuffer
		\param ptrDataSent Pointer to storage for data sent.
		\param ptrDataReceived Pointer to storage for data received.
	*/
	virtual IRESULT ICALL get_ExtendedData(OUT DSC_IDataBuffer** ptrDataSent, 
		OUT DSC_IDataBuffer** ptrDataReceived) const = 0;
};

#else

typedef struct DSC_IRequestResult_Vtbl
{
	BEGIN_INTERFACE

	IRESULT (ICALL *Query)(IN DSC_IRequestResult *This, IN char const* pszInterface, OUT VOID** ptrInterface);
	IRESULT (ICALL *Acquire)(IN DSC_IRequestResult *This, OUT ICOUNT* ptrCount);
	IRESULT (ICALL *Release)(IN DSC_IRequestResult *This, OUT ICOUNT* ptrCount);

	IRESULT (ICALL *get_ReadWriteResultCode)(IN DSC_IRequestResult *This, 
		OUT DSC_RequestResultCode* ptrResultCode);
	IRESULT (ICALL *get_ResultDescription)(IN DSC_IRequestResult *This, 
		OUT DSC_ITextString** pszDescription);
	IRESULT (ICALL *get_ExtendedData)(IN DSC_IRequestResult *This, 
		OUT DSC_IDataBuffer** ptrDataSent, OUT DSC_IDataBuffer** ptrDataReceived);

	END_INTERFACE
} DSC_IRequestResult_Vtbl;

DSC_INTERFACE DSC_IRequestResult
{
	//the assumption: the compiler places pointer to VTABLE first in the class layout
 	struct DSC_IRequestResult_Vtbl *ptrVtbl;
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

#endif	//_DSC_I_REQUEST_RESULT_HPP_
