//---------------------------------------------------------------------------
//
//	DSC_Config.hpp
//	Copyright 2017 Johnson Controls. All rights reserved.
//
//	The file contains configuration info used during compilation.
//  This file must not be modified in any way!
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#ifndef _DSC_CONFIG_HPP_
#define _DSC_CONFIG_HPP_

//---------------------------------------------------------------------------

//platform declaration (added to the compiler's preprocessor directives)
//#define WINDOWS		//MS Windows
//#define LINUX		//Linux

//---------------------------------------------------------------------------

//compiler declaration (added to the compiler's preprocessor directives)
//#define MS_VS_COMPILER	//MS Visual Studio
//#define GCC_COMPILER	//Gnu C/C++

//compiler compliant with C++11 standard
//#define CPP_11_STANDARD

//---------------------------------------------------------------------------

//enable C-style interfaces
//#define C_STYLE_INTERFACE

//---------------------------------------------------------------------------

//SDK information
#define SDK_PRODUCT_INFO_STRING		"TSP DSC InteractiveSDK, Copyright 2017-2020 Johnson Controls. All rights reserved."
#define SDK_VERSION_INFO_STRING		"Version 2.01"
#define SDK_VERSION_INFO_VALUE		0x0201

//---------------------------------------------------------------------------

//the SDK's main/enclosing namespace (it has to be defined piece-by-piece
//on separate source lines or otherwise the VS's Intellisense gets confused) 
#define SDK_MAJOR_NAMESPACE		TSP
#define SDK_MINOR_NAMESPACE		DSC_InteractiveSDK

//the SDK's nested namespaces
#define SECURITY_NAMESPACE		Security
#define AUTOMATION_NAMESPACE	Automation

//the SDK's protocol namespaces
#define ITV2_NAMESPACE			ITV2

//---------------------------------------------------------------------------

//define enum value type (must be signed type)
#ifndef DSC_ENUM_T_DEFINED
#define DSC_ENUM_T_DEFINED
#define DSC_ENUM_T			INT32
#endif

#ifndef DSC_ENUM_T_MAX_DEFINED
#define DSC_ENUM_T_MAX_DEFINED
#define DSC_ENUM_T_MAX		INT32_MAX
#endif

//define 'size_t' type used by the interface
#ifndef DSC_SIZE_T_DEFINED
#define DSC_SIZE_T_DEFINED
#define DSC_SIZE_T			UINT32
#endif

//define 'flags' type used by the interface
#ifndef DSC_FLAGS_T_DEFINED
#define DSC_FLAGS_T_DEFINED
#define DSC_FLAGS_T			UINT32
#endif

//define product ID type used by the interface
#ifndef DSC_PRODUCT_ID_DEFINED
#define DSC_PRODUCT_ID_DEFINED
#define DSC_PRODUCT_ID		UINT16
#endif

//define invalid product ID
#define DSC_INVALID_PRODUCT_ID		static_cast<DSC_PRODUCT_ID>(0)

//define system index type used by the interface
#ifndef DSC_SYSTEM_INDEX_DEFINED
#define DSC_SYSTEM_INDEX_DEFINED
#define DSC_SYSTEM_INDEX	UINT32
#endif

//define invalid system index value
#define DSC_INVALID_SYSTEM_INDEX	static_cast<DSC_SYSTEM_INDEX>(-1)

//define error type used by the interface
#ifndef DSC_ERROR_CODE_DEFINED
#define DSC_ERROR_CODE_DEFINED
#define DSC_ERROR_CODE		UINT32
#endif

//define max label sizes
#ifndef DSC_PARTITION_LABEL_SIZE_DEFINED
#define DSC_PARTITION_LABEL_SIZE_DEFINED
#define DSC_PARTITION_LABEL_SIZE 14
#endif

#ifndef DSC_ZONE_LABEL_SIZE_DEFINED
#define DSC_ZONE_LABEL_SIZE_DEFINED
#define DSC_ZONE_LABEL_SIZE 28
#endif

#ifndef DSC_ACCESSCODE_LABEL_SIZE_DEFINED
#define DSC_ACCESSCODE_LABEL_SIZE_DEFINED
#define DSC_ACCESSCODE_LABEL_SIZE 14
#endif

//define padding character
#ifndef DSC_PADDING_CHARACTER_DEFINED
#define DSC_PADDING_CHARACTER_DEFINED
#define DSC_PADDING_CHARACTER ' '
#endif

//---------------------------------------------------------------------------

//'no debug assert' not defined?
#if !defined(NDEBUG)

//enable debugging code trace for the SDK
#define ENABLE_DEBUG_TRACE

#endif	//NDEBUG

//enable trace code for the SDK
//#define ENABLE_RELEASE_TRACE

//enable writing trace information to log file
//#define USE_FILE_TRACE_LOG

//---------------------------------------------------------------------------

//enable component's lifetime tracking
//#define TRACK_COMPOMENT_LIFETIME

//---------------------------------------------------------------------------

//enable event's lifetime tracking
//#define TRACK_EVENT_LIFETIME

//---------------------------------------------------------------------------

//disable license checking and exclude the code
//#define DISABLE_LICENSE_CHECK

//---------------------------------------------------------------------------

//'no debug assert' not defined?
#if !defined(NDEBUG)

//enable unit tests of the command objects
#define ENABLE_COMMAND_UNIT_TEST

#endif	//NDEBUG

//---------------------------------------------------------------------------
#endif	//_DSC_CONFIG_HPP_
