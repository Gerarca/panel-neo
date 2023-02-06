//---------------------------------------------------------------------------
//
//	DSC_IRepository.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_IComponent.hpp"
#include "DSC_ITextString.hpp"
#include "DSC_ISystemIndices.hpp"
#include "DSC_IAccessCode.hpp"
#include "DSC_IPartition.hpp"
#include "DSC_IZone.hpp"
#include "DSC_IVirtualZone.hpp"

#ifndef _DSC_I_REPOSITORY_HPP_
#define _DSC_I_REPOSITORY_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
namespace SECURITY_NAMESPACE {
//---------------------------------------------------------------------------

#define NAME_DSC_IRepository	"DSC_IRepository"

//---------------------------------------------------------------------------

#ifndef DSC_IRepository_FWD_DEFINED
#define DSC_IRepository_FWD_DEFINED
typedef DSC_INTERFACE DSC_IRepository DSC_IRepository;
#endif

//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

/*!
	This interface is used to access data stored in the SDK's internal repository.
*/
DSC_INTERFACE DSC_IRepository : public DSC_IComponent
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

	//-----------------------------------------------------------------------

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

	//-----------------------------------------------------------------------

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

	//-----------------------------------------------------------------------

    //! Get the NumberOfAccessCodes.
    /*! Returns the number of access code objects currently stored in the SDK. */
    /*!	
      	\param ptrCount Pointer to storage for the number of Access Codes.
    */
	virtual IRESULT ICALL get_NumberOfAccessCodes(OUT DSC_SIZE_T* ptrCount) const = 0;

    //! Get the NumberOfPartitions.
    /*! Returns the number of partition objects currently stored in the SDK. */
    /*!	
      	\param ptrCount Pointer to storage for the number of Partitions.
    */
	virtual IRESULT ICALL get_NumberOfPartitions(OUT DSC_SIZE_T* ptrCount) const = 0;

    //! Get the NumberOfZones.
    /*! Returns the number of zone objects currently stored in the SDK. */
    /*!	
      	\param ptrCount Pointer to storage for the number of Zones.
    */
	virtual IRESULT ICALL get_NumberOfZones(OUT DSC_SIZE_T* ptrCount) const = 0;

    //! Get the NumberOfVirtualZones.
    /*! Returns the number of virtual zone objects currently stored in the SDK. */
    /*!	
      	\param ptrCount Pointer to storage for the number of Virtual Zones.
    */
	virtual IRESULT ICALL get_NumberOfVirtualZones(OUT DSC_SIZE_T* ptrCount) const = 0;

	//-----------------------------------------------------------------------

    //! Get the ListOfAccessCodes.
    /*! Returns the list of system indices of all access code objects currently stored in the SDK. */
    /*!	
		\sa DSC_ISystemIndices
      	\param ptrSystemIndices Pointer to storage for the System Indices.
    */
	virtual IRESULT ICALL GetListOfAccessCodes(OUT DSC_ISystemIndices** ptrSystemIndices) = 0;

    //! Get the ListOfPartitions.
    /*! Returns the list of system indices of all partition objects currently stored in the SDK. */
    /*!	
		\sa DSC_ISystemIndices
      	\param ptrSystemIndices Pointer to storage for the System Indices.
    */
	virtual IRESULT ICALL GetListOfPartitions(OUT DSC_ISystemIndices** ptrSystemIndices) = 0;

    //! Get the ListOfZones.
    /*! Returns the list of system indices of all zone objects currently stored in the SDK. */
    /*!	
		\sa DSC_ISystemIndices
      	\param ptrSystemIndices Pointer to storage for the System Indices.
    */
	virtual IRESULT ICALL GetListOfZones(OUT DSC_ISystemIndices** ptrSystemIndices) = 0;

    //! Get the ListOfVirtualZones.
    /*! Returns the list of system indices of all virtual zone objects currently stored in the SDK. */
    /*!	
		\sa DSC_ISystemIndices
      	\param ptrSystemIndices Pointer to storage for the System Indices.
    */
	virtual IRESULT ICALL GetListOfVirtualZones(OUT DSC_ISystemIndices** ptrSystemIndices) = 0;

	//-----------------------------------------------------------------------

    //! Get AccessCodeBySystemIndex.
    /*! Retrieve a single access code interface using its system index. 
		The system index is used by the panel to enumerate its data - e.g. use 1 for access code 1. */
    /*!	
		\sa DSC_IAccessCode
      	\param numSystemIndex The system index of the access code interface you wish to get.
		\param ptrPartition Pointer to storage for the access code interface.
    */
	virtual IRESULT ICALL GetAccessCodeBySystemIndex(IN DSC_SYSTEM_INDEX numSystemIndex, OUT DSC_IAccessCode** ptrAccessCode) = 0;

    //! Get PartitionBySystemIndex.
    /*! Retrieve a single partition interface using its system index. 
		The system index is used by the panel to enumerate its data - e.g. use 4 for partition 4. */
    /*!	
		\sa DSC_IPartition
      	\param numSystemIndex The system index of the partition interface you wish to get.
		\param ptrPartition Pointer to storage for the partition interface.
    */
	virtual IRESULT ICALL GetPartitionBySystemIndex(IN DSC_SYSTEM_INDEX numSystemIndex, OUT DSC_IPartition** ptrPartition) = 0;

    //! Get ZoneBySystemIndex.
    /*! Retrieve a single zone interface using its system index. 
		The system index is used by the panel to enumerate its data - e.g. use 3 for zone 3. */
    /*!	
		\sa DSC_IZone
      	\param numSystemIndex The system index of the zone interface you wish to get.
		\param ptrPartition Pointer to storage for the zone interface.
    */
	virtual IRESULT ICALL GetZoneBySystemIndex(IN DSC_SYSTEM_INDEX numSystemIndex, OUT DSC_IZone** ptrZone) = 0;

    //! Get VirtualZoneBySystemIndex.
    /*! Retrieve a single virtual zone interface using its system index. 
		The system index is used by the panel to enumerate its data - e.g. use 3 for zone 3. */
    /*!	
		\sa DSC_IVirtualZone
      	\param numSystemIndex The system index of the virtual zone interface you wish to get.
		\param ptrPartition Pointer to storage for the virtual zone interface.
    */
	virtual IRESULT ICALL GetVirtualZoneBySystemIndex(IN DSC_SYSTEM_INDEX numSystemIndex, OUT DSC_IVirtualZone** ptrVirtualZone) = 0;

	//-----------------------------------------------------------------------

    //! Get PartitionsLinkedWithAccessCode.
    /*! Returns the list of system indices of all partitions currently stored in the SDK that are linked with given access code. */
    /*!	
		\sa DSC_ISystemIndices
		\param numAccessCodeNumber Provided system index of the access code.
      	\param ptrSystemIndices Pointer to storage for the System Indices.
    */
	virtual IRESULT ICALL GetPartitionsLinkedWithAccessCode(IN DSC_SYSTEM_INDEX numAccessCodeNumber, OUT DSC_ISystemIndices** ptrSystemIndices) = 0;

    //! Get AccessCodesLinkedWithPartition.
    /*! Returns the list of system indices of all access codes currently stored in the SDK that are linked with given partition. */
    /*!	
		\sa DSC_ISystemIndices
		\param numPartitionNumber Provided system index of the partition.
      	\param ptrSystemIndices Pointer to storage for the System Indices.
    */
	virtual IRESULT ICALL GetAccessCodesLinkedWithPartition(IN DSC_SYSTEM_INDEX numPartitionNumber, OUT DSC_ISystemIndices** ptrSystemIndices) = 0;

    //! Get PartitionsLinkedWithZone.
    /*! Returns the list of system indices of all partitions currently stored in the SDK that are linked with given zone. */
    /*!	
		\sa DSC_ISystemIndices
		\param numZoneNumber Provided system index of the zone.
      	\param ptrSystemIndices Pointer to storage for the System Indices.
    */
	virtual IRESULT ICALL GetPartitionsLinkedWithZone(IN DSC_SYSTEM_INDEX numZoneNumber, OUT DSC_ISystemIndices** ptrSystemIndices) = 0;

    //! Get ZonesLinkedWithPartition.
    /*! Returns the list of system indices of all zones currently stored in the SDK that are linked with given partition. */
    /*!	
		\sa DSC_ISystemIndices
		\param numPartitionNumber Provided system index of the partition.
      	\param ptrSystemIndices Pointer to storage for the System Indices.
    */
	virtual IRESULT ICALL GetZonesLinkedWithPartition(IN DSC_SYSTEM_INDEX numPartitionNumber, OUT DSC_ISystemIndices** ptrSystemIndices) = 0;

    //! Get VirtualZonesLinkedWithZone.
    /*! Returns the list of system indices of all virtual zones currently stored in the SDK that are linked with given zone. */
    /*!	
		\sa DSC_ISystemIndices
		\param numZoneNumber Provided system index of the zone.
      	\param ptrSystemIndices Pointer to storage for the System Indices.
    */
	virtual IRESULT ICALL GetVirtualZonesLinkedWithZone(IN DSC_SYSTEM_INDEX numZoneNumber, OUT DSC_ISystemIndices** ptrSystemIndices) = 0;

    //! Get ZonesLinkedWithVirtualZone.
    /*! Returns the list of system indices of all zones currently stored in the SDK that are linked with given virtual zone. */
    /*!	
		\sa DSC_ISystemIndices
		\param numVirtualZoneNumber Provided system index of the virtual zone.
      	\param ptrSystemIndices Pointer to storage for the System Indices.
    */
	virtual IRESULT ICALL GetZonesLinkedWithVirtualZone(IN DSC_SYSTEM_INDEX numVirtualZoneNumber, OUT DSC_ISystemIndices** ptrSystemIndices) = 0;
};

#else

typedef struct DSC_IRepository_Vtbl
{
	BEGIN_INTERFACE

	IRESULT (ICALL *Query)(IN DSC_IRepository *This, IN char const* pszInterface, OUT VOID** ptrInterface);
	IRESULT (ICALL *Acquire)(IN DSC_IRepository *This, OUT ICOUNT* ptrCount);
	IRESULT (ICALL *Release)(IN DSC_IRepository *This, OUT ICOUNT* ptrCount);

	IRESULT (ICALL *get_PeerIdentifier)(IN DSC_IRepository *This, OUT DSC_ITextString** ptrTextString);

	IRESULT (ICALL *get_SoftwareVersion)(IN DSC_IRepository *This, OUT DSC_ITextString** ptrTextString);
	IRESULT (ICALL *get_ProtocolVersion)(IN DSC_IRepository *This, OUT DSC_ITextString** ptrTextString);
	IRESULT (ICALL *get_MiscellaneousInfo)(IN DSC_IRepository *This, OUT DSC_ITextString** ptrTextString);

	IRESULT (ICALL *get_SupportedAccessCodes)(IN DSC_IRepository *This, OUT DSC_SIZE_T* ptrCount);
	IRESULT (ICALL *get_SupportedPartitions)(IN DSC_IRepository *This, OUT DSC_SIZE_T* ptrCount);
	IRESULT (ICALL *get_SupportedZones)(IN DSC_IRepository *This, OUT DSC_SIZE_T* ptrCount);
	IRESULT (ICALL *get_SupportedFOBs)(IN DSC_IRepository *This, OUT DSC_SIZE_T* ptrCount);
	IRESULT (ICALL *get_SupportedProximityTags)(IN DSC_IRepository *This, OUT DSC_SIZE_T* ptrCount);
	IRESULT (ICALL *get_SupportedCommandOutputs)(IN DSC_IRepository *This, OUT DSC_SIZE_T* ptrCount);

	IRESULT (ICALL *get_NumberOfAccessCodes)(IN DSC_IRepository *This, OUT DSC_SIZE_T* ptrCount);
	IRESULT (ICALL *get_NumberOfPartitions)(IN DSC_IRepository *This, OUT DSC_SIZE_T* ptrCount);
	IRESULT (ICALL *get_NumberOfZones)(IN DSC_IRepository *This, OUT DSC_SIZE_T* ptrCount);
	IRESULT (ICALL *get_NumberOfVirtualZones)(IN DSC_IRepository *This, OUT DSC_SIZE_T* ptrCount);

	IRESULT (ICALL *GetListOfAccessCodes)(IN DSC_IRepository *This, OUT DSC_ISystemIndices** ptrSystemIndices);
	IRESULT (ICALL *GetListOfPartitions)(IN DSC_IRepository *This, OUT DSC_ISystemIndices** ptrSystemIndices);
	IRESULT (ICALL *GetListOfZones)(IN DSC_IRepository *This, OUT DSC_ISystemIndices** ptrSystemIndices);
	IRESULT (ICALL *GetListOfVirtualZones)(IN DSC_IRepository *This, OUT DSC_ISystemIndices** ptrSystemIndices);

	IRESULT (ICALL *GetAccessCodeBySystemIndex)(IN DSC_IRepository *This, IN DSC_SYSTEM_INDEX numSystemIndex, OUT DSC_IAccessCode** ptrAccessCode);
	IRESULT (ICALL *GetPartitionBySystemIndex)(IN DSC_IRepository *This, IN DSC_SYSTEM_INDEX numSystemIndex, OUT DSC_IPartition** ptrPartition);
	IRESULT (ICALL *GetZoneBySystemIndex)(IN DSC_IRepository *This, IN DSC_SYSTEM_INDEX numSystemIndex, OUT DSC_IZone** ptrZone);
	IRESULT (ICALL *GetVirtualZoneBySystemIndex)(IN DSC_IRepository *This, IN DSC_SYSTEM_INDEX numSystemIndex, OUT DSC_IVirtualZone** ptrVirtualZone);

	IRESULT (ICALL *GetPartitionsLinkedWithAccessCode)(IN DSC_IRepository *This, IN DSC_SYSTEM_INDEX numAccessCodeNumber, OUT DSC_ISystemIndices** ptrSystemIndices);
	IRESULT (ICALL *GetAccessCodesLinkedWithPartition)(IN DSC_IRepository *This, IN DSC_SYSTEM_INDEX numPartitionNumber, OUT DSC_ISystemIndices** ptrSystemIndices);

	IRESULT (ICALL *GetPartitionsLinkedWithZone)(IN DSC_IRepository *This, IN DSC_SYSTEM_INDEX numZoneNumber, OUT DSC_ISystemIndices** ptrSystemIndices);
	IRESULT (ICALL *GetZonesLinkedWithPartition)(IN DSC_IRepository *This, IN DSC_SYSTEM_INDEX numPartitionNumber, OUT DSC_ISystemIndices** ptrSystemIndices);

	IRESULT (ICALL *GetVirtualZonesLinkedWithZone)(IN DSC_IRepository *This, IN DSC_SYSTEM_INDEX numZoneNumber, OUT DSC_ISystemIndices** ptrSystemIndices);
	IRESULT (ICALL *GetZonesLinkedWithVirtualZone)(IN DSC_IRepository *This, IN DSC_SYSTEM_INDEX numVirtualZoneNumber, OUT DSC_ISystemIndices** ptrSystemIndices);

	END_INTERFACE
} DSC_IRepository_Vtbl;

DSC_INTERFACE DSC_IRepository
{
	//the assumption: the compiler places pointer to VTABLE first in the class layout
 	struct DSC_IRepository_Vtbl *ptrVtbl;
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

#endif	//_DSC_I_REPOSITORY_HPP_
