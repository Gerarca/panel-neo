//---------------------------------------------------------------------------
//
//	DSC_ISystemInformation.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_IComponent.hpp"
#include "DSC_ITextString.hpp"

#ifndef _DSC_I_SYSTEM_INFORMATION_HPP_
#define _DSC_I_SYSTEM_INFORMATION_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#define NAME_DSC_ISystemInformation	"DSC_ISystemInformation"

//---------------------------------------------------------------------------

#ifndef DSC_ISystemInformation_FWD_DEFINED
#define DSC_ISystemInformation_FWD_DEFINED
typedef DSC_INTERFACE DSC_ISystemInformation DSC_ISystemInformation;
#endif

//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

/*!
	This interface is used to obtain information about the panel.
*/
DSC_INTERFACE DSC_ISystemInformation : public DSC_IComponent
{
public:

	//! Get the PeerIdentifier
    /*!	Depending on the data exchange protocol the peer device can provide its Peer Identifier information. 
		(eg. for ITV2 the PeerIdentifier is the Integration ID)	*/
    /*! 
		\sa DSC_ITextString
     	\param ptrTextString Pointer to the storage for the returned DSC_ITextString interface.
    */
	virtual IRESULT ICALL get_PeerIdentifier(OUT DSC_ITextString** ptrTextString) const = 0;

	//! Get the SoftwareVersion.
    /*! Returns a string containing the software version information.    */
    /*!
		\sa DSC_ITextString
      	\param ptrTextString Pointer to storage for the result.
    */
	virtual IRESULT ICALL get_SoftwareVersion(OUT DSC_ITextString** ptrTextString) const = 0;

	//! Get the ProtocolVersion.
	/*! Returns a string containing the data exchange protocol version information.    */
	/*!
		\sa DSC_ITextString
		\param ptrTextString Pointer to storage for the result.
	*/
	virtual IRESULT ICALL get_ProtocolVersion(OUT DSC_ITextString** ptrTextString) const = 0;

	//! Get the MiscellaneousInfo.
	/*! Returns a string containing the miscellanous information.    */
	/*!
		\sa DSC_ITextString
		\param ptrTextString Pointer to storage for the result.
	*/
	virtual IRESULT ICALL get_MiscellaneousInfo(OUT DSC_ITextString** ptrTextString) const = 0;
};

#else

typedef struct DSC_ISystemInformation_Vtbl
{
	BEGIN_INTERFACE

	IRESULT (ICALL *Query)(IN DSC_ISystemInformation *This, IN char const* pszInterface, OUT VOID** ptrInterface);
	IRESULT (ICALL *Acquire)(IN DSC_ISystemInformation *This, OUT ICOUNT* ptrCount);
	IRESULT (ICALL *Release)(IN DSC_ISystemInformation *This, OUT ICOUNT* ptrCount);

	IRESULT (ICALL *get_PeerIdentifier)(IN DSC_ISystemInformation *This, OUT DSC_ITextString** ptrTextString);

	IRESULT (ICALL *get_SoftwareVersion)(IN DSC_ISystemInformation *This, OUT DSC_ITextString** ptrTextString);
	IRESULT (ICALL *get_ProtocolVersion)(IN DSC_ISystemInformation *This, OUT DSC_ITextString** ptrTextString);
	IRESULT (ICALL *get_MiscellaneousInfo)(IN DSC_ISystemInformation *This, OUT DSC_ITextString** ptrTextString);

	END_INTERFACE
} DSC_ISystemInformation_Vtbl;

DSC_INTERFACE DSC_ISystemInformation
{
	//the assumption: the compiler places pointer to VTABLE first in the class layout
 	struct DSC_ISystemInformation_Vtbl *ptrVtbl;
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

#endif	//_DSC_I_SYSTEM_CAPABILITIES_HPP_
