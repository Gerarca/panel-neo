//---------------------------------------------------------------------------
//
//	DSC_IAccessCode.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_IComponent.hpp"
#include "DSC_IAccessCodeAttributes.hpp"
#include "DSC_IAccessCredentials.hpp"
#include "DSC_IRequestResult.hpp"

#ifndef _DSC_I_ACCESS_CODE_DATA_HPP_
#define _DSC_I_ACCESS_CODE_DATA_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#define NAME_DSC_IAccessCode	"DSC_IAccessCode"

//---------------------------------------------------------------------------

#ifndef DSC_IAccessCode_FWD_DEFINED
#define DSC_IAccessCode_FWD_DEFINED
typedef DSC_INTERFACE DSC_IAccessCode DSC_IAccessCode;
#endif

//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

/*!
	This interface is used for accessing user access code information.
*/
DSC_INTERFACE DSC_IAccessCode : public DSC_IComponent
{
public:

    //! Refreshes the access code data
    /*! This function will issue the requisite commands to get the Access Code information. */
    /*!	
      	\param ptrAccessCredentials Provided Credentials with appropriate permissions to read the Access Code data.
     	\param ptrRequestResult Pointer to storage for the result of the operation.
    */
	virtual IRESULT ICALL Refresh(IN DSC_IAccessCredentials* ptrAccessCredentials, 
		OUT DSC_IRequestResult** ptrRequestResult) = 0;

    //! Get the Access Code Value (i.e. digits)
    /*! UTF8 Null terminated Access code digits. */
    /*!	
      	\param ppszValue Pointer to storage for a text string containing the Access Code digits. 
    */
	virtual IRESULT ICALL get_Value(OUT DSC_ITextString** ppszValue) const = 0;

    //! Get the Access Code Label
    /*! Returns the last retrieved Label for this access code. By default this is "User x" where x is the System Index     */
	/*! UTF8 Null terminated Access code label. */
	/*!
      	\param ppszLabel Pointer to storage for a text string containing the Access Code label. 
    */
	virtual IRESULT ICALL get_Label(OUT DSC_ITextString** ppszLabel) const = 0;

    //! Get the Access Code System Index 
    /*! Gets the System Index for the Access Code as assigned by the panel.
		For example, User Code 5 would return system index 5.     */
    /*!	
      	\param ptrSystemIndex Pointer to storage for the Access Code System Index
    */
	virtual IRESULT ICALL get_SystemIndex(OUT DSC_SYSTEM_INDEX* ptrSystemIndex) const = 0;

	//! Get the Access Code Length 
	/*! Gets the length for the Access Code, as configured in the panel.
		Typical length values are 4, 6, or 8.     */
	/*!
		\param ptrAccessCodeLength Pointer to storage for the length of the Access Code
	*/
	virtual IRESULT ICALL get_AccessCodeLength(OUT DSC_SIZE_T* ptrAccessCodeLength) const = 0;

	//! Get the Access Code Attributes
	/*! Gets the attributes for the Access Code.
		Access Code Attributes are used to determine user code permissions. eg. arming, bypassing     */
	/*!
		\param ptrAttributes Pointer to storage for the attributes assigned to this Access Code
	*/
	virtual IRESULT ICALL get_Attributes(OUT DSC_IAccessCodeAttributes** ptrAttributes) = 0;

    //! Write the Access Code Label to the panel
    /*! This function will issue the requisite commands to change an Access Code Label on the panel.
		This function requires an access code with appropriate permissions to perform the operation, and may 
		not be successful depending on the Partition state. 
	*/
    /*!	
      	\param ptrAccessCredentials Provided Credentials with appropriate permissions to change the Access Code Label.
	  	\param pszAccessCodeLabel Provided UTF8 null terminated string containing Access Code Label to write.
     	\param ptrRequestResult Pointer to storage for the result of the operation.
    */
	virtual IRESULT ICALL WriteAccessCodeLabel(IN DSC_IAccessCredentials* ptrAccessCredentials, 
		IN char const* pszAccessCodeLabel, OUT DSC_IRequestResult** ptrRequestResult) = 0; 

    //! Write the Access Code Value to the panel
    /*! This function will issue the requisite commands to change an Access Code Value on the panel.
		This requires an access code with appropriate permissions to perform the operation, and may 
		not be successful depending on the Partition state.
	*/
    /*!	
      	\param ptrAccessCredentials Provided Credentials with appropriate permissions to change the Access Code Value.
		\param pszAccessCodeAsString Provided UTF8 null terminated string containing Access Code Value to write.
     	\param ptrRequestResult Pointer to storage for the result of the operation.
    */
	virtual IRESULT ICALL WriteAccessCodeValue(IN DSC_IAccessCredentials* ptrAccessCredentials, 
		IN char const* pszAccessCodeAsString, OUT DSC_IRequestResult** ptrRequestResult) = 0;
};

#else

typedef struct DSC_IAccessCode_Vtbl
{
	BEGIN_INTERFACE

	IRESULT (ICALL *Query)(IN DSC_IAccessCode *This, IN char const* pszInterface, OUT VOID** ptrInterface);
	IRESULT (ICALL *Acquire)(IN DSC_IAccessCode *This, OUT ICOUNT* ptrCount);
	IRESULT (ICALL *Release)(IN DSC_IAccessCode *This, OUT ICOUNT* ptrCount);

	IRESULT (ICALL *Refresh)(IN DSC_IAccessCode *This, 
		IN DSC_IAccessCredentials* ptrAccessCredentials, OUT DSC_IRequestResult** ptrRequestResult);
	IRESULT (ICALL *get_Value)(IN DSC_IAccessCode *This, OUT DSC_ITextString** ppszValue);
	IRESULT (ICALL *get_Label)(IN DSC_IAccessCode *This, OUT DSC_ITextString** ppszLabel);
	IRESULT (ICALL *get_SystemIndex)(IN DSC_IAccessCode *This, OUT DSC_SYSTEM_INDEX* ptrSystemIndex);
	IRESULT (ICALL *get_AccessCodeLength)(IN DSC_IAccessCode *This, OUT DSC_SIZE_T* ptrAccessCodeLength);
	IRESULT (ICALL *get_Attributes)(IN DSC_IAccessCode *This, OUT DSC_IAccessCodeAttributes** ptrAttributes);
	IRESULT (ICALL *WriteAccessCodeLabel)(IN DSC_IAccessCode *This, 
		IN DSC_IAccessCredentials* ptrAccessCredentials, 
		IN char const* pszAccessCodeLabel, OUT DSC_IRequestResult** ptrRequestResult); 
	IRESULT (ICALL *WriteAccessCodeValue)(IN DSC_IAccessCode *This, 
		IN DSC_IAccessCredentials* ptrAccessCredentials, 
		IN char const* pszAccessCodeAsString, OUT DSC_IRequestResult** ptrRequestResult);

	END_INTERFACE
} DSC_IAccessCode_Vtbl;

DSC_INTERFACE DSC_IAccessCode
{
	//the assumption: the compiler places pointer to VTABLE first in the class layout
 	struct DSC_IAccessCode_Vtbl *ptrVtbl;
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

#endif	//_DSC_I_ACCESS_CODE_DATA_HPP_
