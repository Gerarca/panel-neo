//---------------------------------------------------------------------------
//
//	DSC_ISystemCapabilities.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_IComponent.hpp"
#include "DSC_ITextString.hpp"

#ifndef _DSC_I_SYSTEM_CAPABILITIES_HPP_
#define _DSC_I_SYSTEM_CAPABILITIES_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#define NAME_DSC_ISystemCapabilities	"DSC_ISystemCapabilities"

//---------------------------------------------------------------------------

#ifndef DSC_ISystemCapabilities_FWD_DEFINED
#define DSC_ISystemCapabilities_FWD_DEFINED
typedef DSC_INTERFACE DSC_ISystemCapabilities DSC_ISystemCapabilities;
#endif

//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

/*!
	This interface is used to obtain information about the system capabilities of the panel.
*/
DSC_INTERFACE DSC_ISystemCapabilities : public DSC_IComponent
{
public:

	//! Get the PeerIdentifier
     /*! Depending on the data exchange protocol the peer device can provide its Peer Identifier information. 
		(eg. for ITV2 the PeerIdentifier is the Integration ID)	*/
    /*! 
		\sa DSC_ITextString
     	\param ptrTextString Pointer to the storage for the returned DSC_ITextString interface.
    */
	virtual IRESULT ICALL get_PeerIdentifier(OUT DSC_ITextString** ptrTextString) const = 0;

    //! Get the SupportedAccessCodes.
    /*! Returns the number of access codes supported by the panel. 
		(The access codes are numbered starting with system index 1.)    */
    /*!	
      	\param ptrCount Pointer to storage for the number of supported Access Codes.
    */
	virtual IRESULT ICALL get_SupportedAccessCodes(OUT DSC_SIZE_T* ptrCount) const = 0;

    //! Get the SupportedPartitions.
    /*! Returns the number of partitions supported by the panel. 
		(The partitions are numbered starting with system index 1.)    */
    /*!	
      	\param ptrCount Pointer to storage for the number of supported Partitions.
    */
	virtual IRESULT ICALL get_SupportedPartitions(OUT DSC_SIZE_T* ptrCount) const = 0;

    //! Get the SupportedZones.
    /*! Returns the number of zones supported by the panel. 
		(The zones are numbered starting with system index 1.)    */
    /*!	
      	\param ptrCount Pointer to storage for the number of supported Zones.
    */
	virtual IRESULT ICALL get_SupportedZones(OUT DSC_SIZE_T* ptrCount) const = 0;

	//! Get the SupportedFOBs.
    /*! Returns the number of FOBs supported by the panel. 
		(The FOBs are numbered starting with system index 1.)    */
    /*!	
      	\param ptrCount Pointer to storage for the number of supported FOBs.
    */
	virtual IRESULT ICALL get_SupportedFOBs(OUT DSC_SIZE_T* ptrCount) const = 0;

	//! Get the SupportedProximityTags.
    /*! Returns the number of proximity tags supported by the panel. 
		(The proximity tags are numbered starting with system index 1.)    */
    /*!	
      	\param ptrCount Pointer to storage for the number of supported Proximity Tags.
    */
	virtual IRESULT ICALL get_SupportedProximityTags(OUT DSC_SIZE_T* ptrCount) const = 0;

	//! Get the SupportedCommandOutputs.
    /*! Returns the number of command outputs supported by the panel. 
		(The command outputs are numbered starting with system index 1.)    */
    /*!	
      	\param ptrCount Pointer to storage for the number of supported Command Outputs.
    */
	virtual IRESULT ICALL get_SupportedCommandOutputs(OUT DSC_SIZE_T* ptrCount) const = 0;
};

#else

typedef struct DSC_ISystemCapabilities_Vtbl
{
	BEGIN_INTERFACE

	IRESULT (ICALL *Query)(IN DSC_ISystemCapabilities *This, IN char const* pszInterface, OUT VOID** ptrInterface);
	IRESULT (ICALL *Acquire)(IN DSC_ISystemCapabilities *This, OUT ICOUNT* ptrCount);
	IRESULT (ICALL *Release)(IN DSC_ISystemCapabilities *This, OUT ICOUNT* ptrCount);

	IRESULT (ICALL *get_PeerIdentifier)(IN DSC_ISystemCapabilities *This, OUT DSC_ITextString** ptrTextString);

	IRESULT (ICALL *get_SupportedAccessCodes)(IN DSC_ISystemCapabilities *This, OUT DSC_SIZE_T* ptrCount);
	IRESULT (ICALL *get_SupportedPartitions)(IN DSC_ISystemCapabilities *This, OUT DSC_SIZE_T* ptrCount);
	IRESULT (ICALL *get_SupportedZones)(IN DSC_ISystemCapabilities *This, OUT DSC_SIZE_T* ptrCount);
	IRESULT (ICALL *get_SupportedFOBs)(IN DSC_ISystemCapabilities *This, OUT DSC_SIZE_T* ptrCount);
	IRESULT (ICALL *get_SupportedProximityTags)(IN DSC_ISystemCapabilities *This, OUT DSC_SIZE_T* ptrCount);
	IRESULT (ICALL *get_SupportedCommandOutputs)(IN DSC_ISystemCapabilities *This, OUT DSC_SIZE_T* ptrCount);

	END_INTERFACE
} DSC_ISystemCapabilities_Vtbl;

DSC_INTERFACE DSC_ISystemCapabilities
{
	//the assumption: the compiler places pointer to VTABLE first in the class layout
 	struct DSC_ISystemCapabilities_Vtbl *ptrVtbl;
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
