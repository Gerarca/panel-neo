//---------------------------------------------------------------------------
//
//	DSC_Types.hpp
//	Copyright 2017 Johnson Controls. All rights reserved.
//
//	Definitions of data types used thorough the SDK.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

//---------------------------------------------------------------------------

#include "DSC_Config.hpp"

#if defined(WINDOWS)

//exclude some non-essential headers
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <stdint.h>

#elif defined(LINUX)

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <pthread.h>

#else
#error "Undefined platform information!"
#endif

#ifndef _DSC_TYPES_HPP_
#define _DSC_TYPES_HPP_

//---------------------------------------------------------------------------

#ifndef VOID
#define VOID void
#endif	//VOID

#ifndef NULL
#ifdef __cplusplus

#ifdef CPP_11_STANDARD
#define NULL nullptr
#else
#define NULL 0
#endif	//CPP_11_STANDARD

#else	//C language

#define NULL ((VOID*)0)

#endif	//__cplusplus
#endif	//NULL

//*******************************************************
//The C/C++ statndard does not guarantee the sizes of
//various data types so it is necessary to define the
//base well-sized data types based on compilers being
//used.
//*******************************************************

#ifndef INT8_DEFINED
typedef int8_t INT8;
#define INT8_DEFINED
#endif	//INT8_DEFINED

#ifndef INT16_DEFINED
typedef int16_t INT16;
#define INT16_DEFINED
#endif	//INT16_DEFINED

////there is no such data type available
//#ifndef INT24_DEFINED
//typedef int24_t INT24;
//#define INT24_DEFINED
//#endif	//INT24_DEFINED

#ifndef INT32_DEFINED
typedef int32_t INT32;
#define INT32_DEFINED
#endif	//INT32_DEFINED

#ifndef UINT8_DEFINED
typedef uint8_t UINT8;
#define UINT8_DEFINED
#endif	//UINT8_DEFINED

#ifndef UINT16_DEFINED
typedef uint16_t UINT16;
#define UINT16_DEFINED
#endif	//UINT16_DEFINED

////there is no such data type available
//#ifndef UINT24_DEFINED
//typedef uint24_t UINT24;
//#define UINT24_DEFINED
//#endif	//UINT24_DEFINED

#ifndef UINT32_DEFINED
typedef uint32_t UINT32;
#define UINT32_DEFINED
#endif	//UINT32_DEFINED

//*******************************************************

#ifndef INT8_SIZE
#define INT8_SIZE   1
#endif	//INT8_SIZE

#ifndef INT8_BITS
#define INT8_BITS   8
#endif	//INT8_BITS

#ifndef INT8_MASK
#define INT8_MASK	0xFF
#endif	//INT8_MASK

#ifndef INT8_MIN
#define INT8_MIN    (-128)
#endif	//INT8_MIN

#ifndef INT8_MAX
#define INT8_MAX    127
#endif	//INT8_MAX

#ifndef INT8_MSB
#define INT8_MSB	0x80
#endif	//INT8_MSB

//*******************************************************

#ifndef INT16_SIZE
#define INT16_SIZE	2
#endif	//INT16_SIZE

#ifndef INT16_BITS
#define INT16_BITS  16
#endif	//INT16_BITS

#ifndef INT16_MASK
#define INT16_MASK	0xFFFF
#endif	//INT16_MASK

#ifndef INT16_MIN
#define INT16_MIN   (-32768)
#endif	//INT16_MIN

#ifndef INT16_MAX
#define INT16_MAX   32767
#endif	//INT16_MAX

#ifndef INT16_MSB
#define INT16_MSB	0x8000
#endif	//INT16_MSB

//*******************************************************

#ifndef INT24_SIZE
#define INT24_SIZE	3
#endif	//INT24_SIZE

#ifndef INT24_BITS
#define INT24_BITS	24
#endif	//INT24_BITS

#ifndef INT24_MASK
#define INT24_MASK	0xFFFFFF
#endif	//INT24_MASK

#ifndef INT24_MIN
#define INT24_MIN   (-8388608)
#endif	//INT24_MIN

#ifndef INT24_MAX
#define INT24_MAX	8388607
#endif	//INT24_MAX

#ifndef INT24_MSB
#define INT24_MSB	0x800000
#endif	//INT24_MSB

//*******************************************************

#ifndef INT32_SIZE
#define INT32_SIZE	4
#endif	//INT32_SIZE

#ifndef INT32_BITS
#define INT32_BITS  32
#endif	//INT32_BITS

#ifndef INT32_MASK
#define INT32_MASK	0xFFFFFFFF
#endif	//INT32_MASK

#ifndef INT32_MIN
#define INT32_MIN   (-2147483648)
#endif	//INT32_MIN

#ifndef INT32_MAX
#define INT32_MAX   2147483647
#endif	//INT32_MAX

#ifndef INT32_MSB
#define INT32_MSB	0x80000000
#endif	//INT32_MSB

//*******************************************************

#ifndef UINT8_SIZE
#define UINT8_SIZE	1
#endif	//UINT8_SIZE

#ifndef UINT8_BITS
#define UINT8_BITS  8
#endif	//UINT8_BITS

#ifndef UINT8_MASK
#define UINT8_MASK	0xFF
#endif	//UINT8_MASK

#ifndef UINT8_MIN
#define UINT8_MIN   0
#endif	//UINT8_MIN

#ifndef UINT8_MAX
#define UINT8_MAX   255
#endif	//UINT8_MAX

#ifndef UINT8_MSB
#define UINT8_MSB	0x80
#endif	//UINT8_MSB

//*******************************************************

#ifndef UINT16_SIZE
#define UINT16_SIZE	2
#endif	//UINT16_SIZE

#ifndef UINT16_BITS
#define UINT16_BITS 16
#endif	//UINT16_BITS

#ifndef UINT16_MASK
#define UINT16_MASK	0xFFFF
#endif	//UINT16_MASK

#ifndef UINT16_MIN
#define UINT16_MIN  0
#endif	//UINT16_MIN

#ifndef UINT16_MAX
#define UINT16_MAX  65535
#endif	//UINT16_MAX

#ifndef UINT16_MSB
#define UINT16_MSB	0x8000
#endif	//UINT16_MSB

//*******************************************************

#ifndef UINT24_SIZE
#define UINT24_SIZE	3
#endif	//UINT24_SIZE

#ifndef UINT24_BITS
#define UINT24_BITS	24
#endif	//UINT24_BITS

#ifndef UINT24_MASK
#define UINT24_MASK	0xFFFFFF
#endif	//UINT24_MASK

#ifndef UINT24_MIN
#define UINT24_MIN	0
#endif	//UINT24_MIN

#ifndef UINT24_MAX
#define UINT24_MAX	16777216
#endif	//UINT24_MAX

#ifndef UINT24_MSB
#define UINT24_MSB	0x800000
#endif	//UINT24_MSB

//*******************************************************

#ifndef UINT32_SIZE
#define UINT32_SIZE	4
#endif	//UINT32_SIZE

#ifndef UINT32_BITS
#define UINT32_BITS 32
#endif	//UINT32_BITS

#ifndef UINT32_MASK
#define UINT32_MASK	0xFFFFFFFF
#endif	//UINT32_MASK

#ifndef UINT32_MIN
#define UINT32_MIN  0
#endif	//UINT32_MIN

#ifndef UINT32_MAX
#define UINT32_MAX	4294967295
#endif	//UINT32_MAX

#ifndef UINT32_MSB
#define UINT32_MSB	0x80000000
#endif	//UINT32_MSB

//*******************************************************

#ifndef BOOL_DEFINED
typedef INT32 BOOL;
#define BOOL_DEFINED
#endif	//BOOL_DEFINED

#ifndef FALSE
//the FALSE value must always be 0!
#define FALSE 0
#endif	//FALSE

#ifndef TRUE
//#define TRUE (!FALSE)
#define TRUE (~FALSE)
#endif	//TRUE

#ifndef FALSE_STRING
#define FALSE_STRING	"FALSE"
#endif	//FALSE_STRING

#ifndef TRUE_STRING
#define TRUE_STRING		"TRUE"
#endif	//TRUE_STRING

//*******************************************************

#ifndef BYTE_DEFINED
typedef UINT8 BYTE;
#define BYTE_DEFINED
#endif	//BYTE_DEFINED

#ifndef BYTE_SIZE
#define BYTE_SIZE	UINT8_SIZE
#endif	//BYTE_SIZE

#ifndef BYTE_BITS
#define BYTE_BITS	UINT8_BITS
#endif	//BYTE_BITS

#ifndef BYTE_MASK
#define BYTE_MASK	UINT8_MASK
#endif	//BYTE_MASK

#ifndef BYTE_MIN
#define BYTE_MIN	UINT8_MIN
#endif	//BYTE_MIN

#ifndef BYTE_MAX
#define BYTE_MAX	UINT8_MAX
#endif	//BYTE_MAX

#ifndef BYTE_MSB
#define BYTE_MSB	UINT8_MSB
#endif	//BYTE_MSB

//*******************************************************

#ifndef NIBBLE_BITS
#define NIBBLE_BITS		4
#endif	//NIBBLE_BITS

#ifndef NIBBLE_MASK
#define NIBBLE_MASK		0xF
#endif	//NIBBLE_MASK

#ifndef NIBBLE_MIN
#define NIBBLE_MIN		0
#endif	//NIBBLE_MIN

#ifndef NIBBLE_MAX
#define NIBBLE_MAX		15
#endif	//NIBBLE_MAX

//*******************************************************

//for use with the sizeof()
#ifndef SIZE_T_DEFINED
#if defined(WINDOWS)

#ifndef _SIZE_T_DEFINED
#ifdef _WIN64
typedef unsigned __int64 size_t;
#else
typedef unsigned int     size_t;
#endif	//_WIN64
#endif	//_SIZE_T_DEFINED

#elif defined(LINUX)

// size_t is defined in stddef.h for linux

#else
#error "Undefined platform information!"
#endif

#define SIZE_T_DEFINED
#endif	//SIZE_T_DEFINED

//Notice: the assumption is that 'size_t' is always
//'unsigned'. If this was to change, the source code
//may be affected because it implicitly assumes that
//values of 'size_t' type are always >= 0.

//*******************************************************

//auxiliary macros
#define MIN_VALUE(x, y)	(((x) <= (y))? (x) : (y))
#define MAX_VALUE(x, y)	(((x) >= (y))? (x) : (y))

//general purpose negative value ("invalid index", "invalid length", etc.)
#define NEGATIVE_VALUE	(-1)	//must be less than 0!

//the possible results of comparison
#define IS_GREATER	1		//must be positive!
#define IS_LESSER	(-1)	//must be negative!
#define IS_EQUAL	0		//must be zero!

//bit flags operations
//#define SET_FLAGS(data, flags)			((data) |= (flags))
#define SET_FLAGS(data, flags, type)	((data) = (type)((data) | (flags)))

//#define CLR_FLAGS(data, flags)			((data) &= ~(flags))
#define CLR_FLAGS(data, flags, type)	((data) = (type)((data) & ~(flags)))

//#define XOR_FLAGS(data, flags)			((data) ^= (flags))
#define XOR_FLAGS(data, flags, type)	((data) = (type)((data) ^ (flags)))

//#define GET_FLAGS(data, flags)			((data) & (flags))
#define GET_FLAGS(data, flags, type)	(type)((data) & (flags))

#define TEST_FLAGS(data, flags)			(((flags) == ((data) & (flags))) ? TRUE : FALSE)

#define ZERO_FLAGS(data)				((data) = 0)

//---------------------------------------------------------------------------

#endif	//_DSC_TYPES_HPP_
