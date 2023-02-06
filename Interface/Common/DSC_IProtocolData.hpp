//---------------------------------------------------------------------------
//
//	DSC_IProtocolData.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_IComponent.hpp"
#include "DSC_ProtocolTypes.hpp"
#include "DSC_IDataBuffer.hpp"
#include "DSC_PacketStates.hpp"

#ifndef _DSC_I_PROTOCOL_DATA_HPP_
#define _DSC_I_PROTOCOL_DATA_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
//---------------------------------------------------------------------------

#define NAME_DSC_IProtocolData	"DSC_IProtocolData"

//---------------------------------------------------------------------------

#ifndef DSC_IProtocolData_FWD_DEFINED
#define DSC_IProtocolData_FWD_DEFINED
typedef DSC_INTERFACE DSC_IProtocolData DSC_IProtocolData;
#endif

//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

/*!
	This interface is needed by the SDK engine and 
	should not be used or modified by 3rd party software.
*/
DSC_INTERFACE DSC_IProtocolData : public DSC_IComponent
{
public:

	//! This property is used to obtain the information on the communication protocol.
    /*!	
		\sa enum DSC_ProtocolType_Tag
     	\param result Pointer to DSC_ProtocolType member.
    */
	virtual IRESULT ICALL get_Protocol(OUT DSC_ProtocolType* result) const = 0;

	//! This function is used to clear all the data within the container.
    /*! 
		Normally this Interface should not be used by 3rd party developers.
    */
	virtual IRESULT ICALL Clear(VOID) = 0;

	//! This function is used to get raw data size of the command.
    /*! 
		Normally this function should not be used by 3rd party developers.

     	\param ptrSize
    */
	virtual IRESULT ICALL GetRawSize(OUT DSC_SIZE_T* ptrSize) const = 0;

	//! This function is used to get raw data bytes (serialize packet).
    /*! 
		Normally this function should not be used by 3rd party developers.

		\sa DSC_IDataBuffer
     	\param ptrData
    */
	virtual IRESULT ICALL GetRawData(OUT DSC_IDataBuffer** ptrData) const = 0;

	//! This function is used to set raw data bytes (deserialize packet).
    /*! 
		Normally this function should not be used by 3rd party developers.

     	\param bufData
     	\param numSize
    */
	virtual IRESULT ICALL SetRawData(IN BYTE const* bufData, IN DSC_SIZE_T numSize) = 0;

	//! This property is used to obtain the information on the curent state of the protocol data.
    /*!	
		\sa enum DSC_PacketState_Tag
     	\param ptrState Pointer to DSC_PacketState member.
    */
	virtual IRESULT ICALL get_DataState(OUT DSC_PacketState* ptrState) const = 0;
};

#else

typedef struct DSC_IProtocolData_Vtbl
{
	BEGIN_INTERFACE

	IRESULT (ICALL *Query)(IN DSC_IProtocolData *This, IN char const* pszInterface, OUT VOID** ptrInterface);
	IRESULT (ICALL *Acquire)(IN DSC_IProtocolData *This, OUT ICOUNT* ptrCount);
	IRESULT (ICALL *Release)(IN DSC_IProtocolData *This, OUT ICOUNT* ptrCount);

	IRESULT (ICALL *get_Protocol)(IN DSC_IProtocolData *This, OUT DSC_ProtocolType* result);
	IRESULT (ICALL *Clear)(IN DSC_IProtocolData *This);
	IRESULT (ICALL *GetRawSize)(IN DSC_IProtocolData *This, OUT DSC_SIZE_T* ptrSize);
	IRESULT (ICALL *GetRawData)(IN DSC_IProtocolData *This, OUT DSC_IDataBuffer** ptrData);
	IRESULT (ICALL *SetRawData)(IN DSC_IProtocolData *This, IN BYTE const* bufData, IN DSC_SIZE_T numSize);
	IRESULT (ICALL *get_DataState)(IN DSC_IProtocolData *This, OUT DSC_PacketState* ptrState);

	END_INTERFACE
} DSC_IProtocolData_Vtbl;

DSC_INTERFACE DSC_IProtocolData
{
	//the assumption: the compiler places pointer to VTABLE first in the class layout
 	struct DSC_IProtocolData_Vtbl *ptrVtbl;
};

#endif

//---------------------------------------------------------------------------
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_I_PROTOCOL_DATA_HPP_
