//---------------------------------------------------------------------------
//
//	DSC_IBase.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//	The base interface implementation.
//	Common stuff for all interfaces
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_Types.hpp"

#ifndef _DSC_IBASE_HPP_
#define _DSC_IBASE_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
//---------------------------------------------------------------------------

//this macro is used to define interface
#ifndef DSC_INTERFACE

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

#define DSC_INTERFACE class

#else	//defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

#define DSC_INTERFACE struct

#ifndef BEGIN_INTERFACE
#define BEGIN_INTERFACE
#endif

#ifndef END_INTERFACE
#define END_INTERFACE
#endif

#endif	//defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

#endif	//DSC_INTERFACE

//---------------------------------------------------------------------------

//input parameter designation
#ifndef IN
#define IN
#endif

//output parameter designation
#ifndef OUT
#define OUT
#endif

//bidirectional parmater designation
#ifndef IN_OUT
#define IN_OUT
#endif

//argument passed by value
#ifndef BYVAL
#define BYVAL
#endif

//argument passed by reference
#ifndef BYREF
#define BYREF
#endif

//---------------------------------------------------------------------------

//This data type is used by all methods to return execution status.
//The 32 bits are used as follows:
//bit	0x80000000	indicates failure when set or success otherwise
//bits	0x7FFF0000	indicate category of the status
//bits	0x0000FFFF	indicate the status code
//The category 0x0000 is a special category. It contains generic
//status codes defined in this header file. This category should
//never be used to define custom statuses.
#define IRESULT		UINT32

//This macro defines the standard calling convention for interface methods.
#if defined(MS_VS_COMPILER)
	#define ICALL		__stdcall
#elif defined(GCC_COMPILER)
	#if defined(i386) || defined(__i386) || defined(__i386__)
		#define ICALL	__attribute__((stdcall))
	#elif defined(__amd64__) || defined(__amd64)
		#define ICALL
	#elif defined(__x86_64__) || defined(__x86_64)
		#define ICALL
	#elif defined(__arm__) || defined(__thumb__)
		#define ICALL
	#elif defined(__aarch64__)
		#define ICALL
	#else
		#error "Unknown target architecture!"
	#endif
#else
	#error "Undefined compiler information!"
#endif	//MS_VS_COMPILER

#define ICOUNT		UINT32

//-------------------------------------------------------------------------

//The masks used when determining the status of the operation.
#define IRESULT_FAILURE_MASK	0x80000000
#define IRESULT_CATEGORY_MASK	0x7FFF0000
#define IRESULT_STATUS_MASK		0x0000FFFF

//Macros used to extract the status parts.
#define IRESULT_FAILURE(Expr)		((0 != ((Expr) & (IRESULT_FAILURE_MASK))) ? TRUE : FALSE)
#define IRESULT_CATEGORY(Expr)		(((Expr) & (IRESULT_CATEGORY_MASK)) >> 16)
#define IRESULT_STATUS(Expr)		((Expr) & (IRESULT_STATUS_MASK))

//-------------------------------------------------------------------------

//Macros defining different categories.
#define IRESULT_CATEGORY_SDK		0
#define IRESULT_CATEGORY_TARGET		1

//-------------------------------------------------------------------------

/*!
	The SDK uses a number of codes to describe the results of SDK function calls.
*/
enum DSC_ResultCode_Tag {
	//This values of this enum are available in 
	//all name spaces and in both C and C++ code.

	IRESULT_S_OK					= 0x00000000,	/**< The operation has succeeded. */
	IRESULT_S_TRUE					= 0x00000001,	/**< The operation has succeeded and the result value is 'TRUE' */
	IRESULT_S_FALSE					= 0x00000002,	/**< The operation has succeeded and the result value is 'FALSE' */
	IRESULT_S_NULL					= 0x00000003,	/**< The operation has succeeded and the result value is 'NULL' */

	IRESULT_E_FAILURE				= 0x80000000,	/**< The operation has failed (general error). */
	IRESULT_E_TIMEOUT				= 0x80000001,	/**< The operation has timed out. */
	IRESULT_E_NOT_IMPLEMENTED		= 0x80000002,	/**< The function is not implemented. */
	IRESULT_E_MEMORY_ALLOC			= 0x80000003,	/**< Internal memory allocation error. */
	IRESULT_E_SMALL_BUFFER			= 0x80000004,	/**< The buffer provided for the output data is too small. */
	IRESULT_E_BAD_ARGUMENTS			= 0x80000005,	/**< Bad function call call arguments (a NULL pointer, etc.). */
	IRESULT_E_NOT_AVAILABLE			= 0x80000006,	/**< The property value or the function result is not available. */
	IRESULT_E_UNKNOWN_VALUE			= 0x80000007,	/**< The property value or the function argument is unknown. */
	IRESULT_E_INVALID_VALUE			= 0x80000008,	/**< The property value or the function argument is invalid (wrong in a given context). */
	IRESULT_E_INDEX_OUT_OF_RANGE	= 0x80000009,	/**< The data array index is out of range. */
	IRESULT_E_MISSING_DATA			= 0x8000000A,	/**< The required data is missing. */
	IRESULT_E_MISSING_LICENSE		= 0x8000000B,	/**< Missing required feature license (feature disabled). */
	IRESULT_E_MISSING_SESSION		= 0x8000000C,	/**< Data exchange session has not been established. */
	IRESULT_E_INVALID_INSTANCE		= 0x8000000D,	/**< The current instance of the interface is no longer valid. Please re-request the interface again. */

	IRESULT_E_TARGET_FAILURE		= 0x80010000,	/**< The operation has failed on the target device. */
	IRESULT_E_TARGET_TIMEOUT		= 0x80010001	/**< The operation has timed out on the target device. */

};

//-------------------------------------------------------------------------

//Macros used to facilitate building appropriate status result and make
//the source code more readable.
#define IRESULT_CREATE(Failure, Category, Status)		\
	((0 != (Failure))? (IRESULT_FAILURE_MASK) : 0) |	\
	(((Category) << 16) & (IRESULT_CATEGORY_MASK)) |	\
	((Status) & (IRESULT_STATUS_MASK))

//Macros used to test the results of interface calls (use directly in code - do not compare against TRUE/FALSE).
#define IS_SUCCESS(Expr)		(FALSE == IRESULT_FAILURE(Expr))
#define IS_FAILURE(Expr)		(FALSE != IRESULT_FAILURE(Expr))

//Macros used to differentiate the SDK internal vs target statuses (use directly in code - do not compare against TRUE/FALSE).
#define IS_CATEGORY_SDK(Expr)		((IRESULT_CATEGORY_SDK) == IRESULT_CATEGORY(Expr))
#define IS_CATEGORY_TARGET(Expr)	((IRESULT_CATEGORY_TARGET) == IRESULT_CATEGORY(Expr))

//---------------------------------------------------------------------------
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_IBASE_HPP_
