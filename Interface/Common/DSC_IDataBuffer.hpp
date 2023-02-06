//---------------------------------------------------------------------------
//
//	DSC_IDataBuffer.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//	The interface for implementing simple data buffer components.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_IComponent.hpp"

#ifndef _DSC_I_DATA_BUFFER_HPP_
#define _DSC_I_DATA_BUFFER_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
//---------------------------------------------------------------------------

//The implementation must be thread safe.
#define NAME_DSC_IDataBuffer	"DSC_IDataBuffer"

//---------------------------------------------------------------------------

#ifndef DSC_IDataBuffer_FWD_DEFINED
#define DSC_IDataBuffer_FWD_DEFINED
typedef DSC_INTERFACE DSC_IDataBuffer DSC_IDataBuffer;
#endif

//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

/*!
	This interface is used for implementing data storage objects.
*/
DSC_INTERFACE DSC_IDataBuffer : public DSC_IComponent
{
public:

	//! Gets the size of the data stored in the component.
    /*!	
     	\param ptrSize Pointer to DSC_SIZE_T that contains the number of bytes stored.
    */
	virtual IRESULT ICALL get_Size(OUT DSC_SIZE_T* ptrSize) const = 0;

	//! Gets the pointer to the data buffer within the component (read only).
    /*!	
     	\param ptrData Pointer to an array of bytes (const = readonly).
    */
	virtual IRESULT ICALL get_Data(OUT BYTE const** ptrData) const = 0;

	//! Gets the pointer to the data buffer within the component (read/write).
    /*!	
     	\param ptrData Pointer to an array of bytes NO const so Read/Write.
    */
	virtual IRESULT ICALL get_Buffer(OUT BYTE** ptrData) = 0;

	//! This function is used to create space within the data buffer component.
    /*!	
     	\param numSize The size, in bytes, to create.
    */
	virtual IRESULT ICALL Create(IN DSC_SIZE_T numSize) = 0;

	//! This function is used to delete the contents of the data buffer.
    /*! 
		The data buffer contents are deleted but the component is kept alive.
    */
	virtual IRESULT ICALL Delete(VOID) = 0;

	//! This function is used to store a copy of the data inside the component.
    /*! 
		Note the size of the internal data buffer is adjusted to match the source.

     	\param bufData The source data to be coppied.
     	\param numSize The number of bytes in bufData.
    */
	virtual IRESULT ICALL CopyData(IN BYTE const* bufData, IN DSC_SIZE_T numSize) = 0;
};

#else

typedef struct DSC_IDataBuffer_Vtbl
{
	BEGIN_INTERFACE

	IRESULT (ICALL *Query)(IN DSC_IDataBuffer *This, IN char const* pszInterface, OUT VOID** ptrInterface);
	IRESULT (ICALL *Acquire)(IN DSC_IDataBuffer *This, OUT ICOUNT* ptrCount);
	IRESULT (ICALL *Release)(IN DSC_IDataBuffer *This, OUT ICOUNT* ptrCount);

	IRESULT (ICALL *get_Size)(IN DSC_IDataBuffer *This, OUT DSC_SIZE_T* ptrSize);
	IRESULT (ICALL *get_Data)(IN DSC_IDataBuffer *This, OUT BYTE const** ptrData);
	IRESULT (ICALL *get_Buffer)(IN DSC_IDataBuffer *This, OUT BYTE** ptrData);
	IRESULT (ICALL *Create)(IN DSC_IDataBuffer *This, IN DSC_SIZE_T numSize);
	IRESULT (ICALL *Delete)(IN DSC_IDataBuffer *This);
	IRESULT (ICALL *CopyData)(IN DSC_IDataBuffer *This, IN BYTE const* bufData, IN DSC_SIZE_T numSize);

	END_INTERFACE
} DSC_IDataBuffer_Vtbl;

DSC_INTERFACE DSC_IDataBuffer
{
	//the assumption: the compiler places pointer to VTABLE first in the class layout
 	struct DSC_IDataBuffer_Vtbl *ptrVtbl;
};

#endif

//---------------------------------------------------------------------------
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_I_DATA_BUFFER_HPP_
