//---------------------------------------------------------------------------
//
//	DSC_IAccessCredentials.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_IComponent.hpp"
#include "DSC_AccessCredentialsTypes.hpp"
#include "DSC_IDataBuffer.hpp"
#include "DSC_ITextString.hpp"

#ifndef _DSC_I_ACCESS_CREDENTIALS_HPP_
#define _DSC_I_ACCESS_CREDENTIALS_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

#define NAME_DSC_IAccessCredentials	"DSC_IAccessCredentials"

//---------------------------------------------------------------------------

#ifndef DSC_IAccessCredentials_FWD_DEFINED
#define DSC_IAccessCredentials_FWD_DEFINED
typedef DSC_INTERFACE DSC_IAccessCredentials DSC_IAccessCredentials;
#endif

//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

/*!
	This interface is used for storing and providing information 
	on user credentials.
*/
DSC_INTERFACE DSC_IAccessCredentials : public DSC_IComponent
{
public:

    //! Gets the access credential type
    /*! Gets the access credential type enumeration    */
    /*!
		\sa DSC_AccessCredentialsType_Tag
      	\param ptrType Pointer to storage for the Access Code Credential Type 
    */
	virtual IRESULT ICALL get_AccessCredentialsType(OUT DSC_AccessCredentialsType* ptrType) const = 0;

    //! Gets the raw data storage for the access credentials
    /*! Gets the raw data for the access credentials. This could be used to store biometric data etc beyond simple access code digits.     */
    /*!	
      	\param ptrData Pointer to storage for the result
    */
	virtual IRESULT ICALL get_AccessCredentialsBytes(OUT DSC_IDataBuffer** ptrData) const = 0;

    //! Sets the raw data storage for the access credentials
    /*! Sets the raw data for the access credentials. This could be used to store biometric data etc beyond simple access code digits.     */
    /*!	
      	\param ptrData Pointer to data to store
		\param size Length of source data 
    */
	virtual IRESULT ICALL set_AccessCredentialsBytes(IN BYTE const* ptrData, IN DSC_SIZE_T size) = 0;

    //! Gets the access credential "String" storage. 
    /*! Gets the access credential "String" storage. This is used when using access codes with a credential type of "Numeric" e.g. Access Code Digits      */
    /*!	
      	\param ptrString Pointer to null terminated string
    */
	virtual IRESULT ICALL get_AccessCredentialsString(OUT DSC_ITextString** ptrString) const = 0;

    //! Sets the access credential "String" storage. 
    /*! Sets the access credential "String" storage. This is used when using access codes with a credential type of "Numeric" e.g. Access Code Digits     */
    /*!	
      	\param ptrString Pointer to null-terminated string
    */
	virtual IRESULT ICALL set_AccessCredentialsString(IN const char* ptrString) = 0;
};

#else

typedef struct DSC_IAccessCredentials_Vtbl
{
	BEGIN_INTERFACE

	IRESULT (ICALL *Query)(IN DSC_IAccessCredentials *This, IN char const* pszInterface, OUT VOID** ptrInterface);
	IRESULT (ICALL *Acquire)(IN DSC_IAccessCredentials *This, OUT ICOUNT* ptrCount);
	IRESULT (ICALL *Release)(IN DSC_IAccessCredentials *This, OUT ICOUNT* ptrCount);

	IRESULT (ICALL *get_AccessCredentialsType)(IN DSC_IAccessCredentials *This, OUT DSC_AccessCredentialsType* ptrType);
	IRESULT (ICALL *get_AccessCredentialsBytes)(IN DSC_IAccessCredentials *This, OUT DSC_IDataBuffer** ptrData);
	IRESULT (ICALL *set_AccessCredentialsBytes)(IN DSC_IAccessCredentials *This, IN BYTE const* ptrData, IN DSC_SIZE_T size);
	IRESULT (ICALL *get_AccessCredentialsString)(IN DSC_IAccessCredentials *This, OUT DSC_ITextString** ptrString);
	IRESULT (ICALL *set_AccessCredentialsString)(IN DSC_IAccessCredentials *This, IN const char* ptrString);

	END_INTERFACE
} DSC_IAccessCredentials_Vtbl;

DSC_INTERFACE DSC_IAccessCredentials
{
	//the assumption: the compiler places pointer to VTABLE first in the class layout
 	struct DSC_IAccessCredentials_Vtbl *ptrVtbl;
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

#endif	//_DSC_I_ACCESS_CREDENTIALS_HPP_
