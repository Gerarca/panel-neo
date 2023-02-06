//---------------------------------------------------------------------------
//
//	DSC_IDataStore.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//	The interface for implementing data stores. The data being exchanged 
//	uses text strings to provide required flexibility. This interface is 
//	_NOT_ intended for exchanging large amounts of data.
//
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
/*	The format of the string parmeters as well as the response
	uses name-value pairs separated by the semicolon ";". The
	example: "name_1 = value_1; name_2 = value_2".

	The <name> must be one word or multiple words and/or special 
	chars enclosed by quotes ("..."). The text enclosed	in quotes 
	may include special characters but not quote chars.

	The <value> may be one word, multiple words enclosed by 
	quotes ("..."), or an <array>. The text enclosed in quotes 
	may include special characters but not quote chars.

	The <array> consists of a list of <list_value> enclosed by 
	square brackets ([...]) and separated by the coma char ",".

	The <list_value> may be one word or multiple words enclosed 
	by quotes ("..."). The text enclosed in quotes may include 
	special characters but not quote chars. The <list_value>
	must not be another <array_of_values> - the array nesting 
	is _NOT_ supported.

	The special characters mentioned above that may be used within
	quoted name or value are: ";", "=", "[", "]", ",". Nested quotes 
	are not supported.

	Check the file "DSC_Parameters.hpp" for the information on
	all the parameter names that the SDK currently uses. Make
	sure to use the parameter QUERY_CATEGORY to determine the
	subject of a given query. 
	
	An example of a well-formatted string is as follows: 
	“Category=ITV2; ITV2_Identifier = \”12345\”; ITV2_IntegrationID=\”456789\”; AccessCode=\”0987654\””
*/
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_IComponent.hpp"
#include "DSC_ITextString.hpp"

#ifndef _DSC_I_DATA_STORE_HPP_
#define _DSC_I_DATA_STORE_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
//---------------------------------------------------------------------------

//The implementation must be thread safe.
#define NAME_DSC_IDataStore		"DSC_IDataStore"

//---------------------------------------------------------------------------

#ifndef DSC_IDataStore_FWD_DEFINED
#define DSC_IDataStore_FWD_DEFINED
typedef DSC_INTERFACE DSC_IDataStore DSC_IDataStore;
#endif

//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

/*!
	This interface provides basic database functionality. The SDK queries
	external database for any kind of information it needs to perform its
	function. Also some of the SDK objects implement this interface to allow
	queries. (The implementation must be thread safe.)
*/
DSC_INTERFACE DSC_IDataStore : public DSC_IComponent
{
public:

	//! This function is used to fetch data based on the requested parameters.
    /*! 
		See Parameters.hpp for default "Keys" used by the IDataStore. 
		The function returns the text string containing the result of the query.

		\sa DSC_ITextString
		\param pszParams The string containing the data selection parameters. (UTF-8)
     	\param ptrResult Pointer to the component containing the result string.
    */
	virtual IRESULT ICALL SelectData(
		IN char const* pszParams, OUT DSC_ITextString** ptrResult) const = 0;

	//! This function is used to insert data into the data store.
    /*! 
		See Parameters.hpp for default "Keys" used by the IDataStore. 
		The function returns the number of records affected.

		\param pszParams The string containing the data to insert. (UTF-8)
     	\param ptrResult Pointer to a variable that will receive the number of the records affected.
    */
	virtual IRESULT ICALL InsertData(
		IN char const* pszParams, OUT DSC_SIZE_T* ptrResult) = 0;

	//! This function is used to update data within the data store.
    /*! 
		See Parameters.hpp for default "Keys" used by the IDataStore. 
		The function returns the number of records affected.

		\param pszParams The string containing the updated data. (UTF-8)
     	\param ptrResult Pointer to a variable that will receive the number of the records affected.
    */
	virtual IRESULT ICALL UpdateData(
		IN char const* pszParams, OUT DSC_SIZE_T* ptrResult) = 0;

	//! This function is used to delete data from the data store.
    /*! 
		See Parameters.hpp for default "Keys" used by the IDataStore. 
		The function returns the number of records affected.

		\param pszParams The string containing the selection parameters. (UTF-8)
     	\param ptrResult Pointer to a variable that will receive the number of the records affected.
    */
	virtual IRESULT ICALL DeleteData(
		IN char const* pszParams, OUT DSC_SIZE_T* ptrResult) = 0;
};

#else

typedef struct DSC_IDataStore_Vtbl
{
	BEGIN_INTERFACE

	IRESULT (ICALL *Query)(IN DSC_IDataStore *This, IN char const* pszInterface, OUT VOID** ptrInterface);
	IRESULT (ICALL *Acquire)(IN DSC_IDataStore *This, OUT ICOUNT* ptrCount);
	IRESULT (ICALL *Release)(IN DSC_IDataStore *This, OUT ICOUNT* ptrCount);

	IRESULT (ICALL *SelectData)(IN DSC_IDataStore *This, 
		IN char const* pszParams, OUT DSC_ITextString** ptrResult);
	IRESULT (ICALL *InsertData)(IN DSC_IDataStore *This, 
		IN char const* pszParams, OUT DSC_SIZE_T* ptrResult);
	IRESULT (ICALL *UpdateData)(IN DSC_IDataStore *This, 
		IN char const* pszParams, OUT DSC_SIZE_T* ptrResult);
	IRESULT (ICALL *DeleteData)(IN DSC_IDataStore *This, 
		IN char const* pszParams, OUT DSC_SIZE_T* ptrResult);

	END_INTERFACE
} DSC_IDataStore_Vtbl;

DSC_INTERFACE DSC_IDataStore
{
	//the assumption: the compiler places pointer to VTABLE first in the class layout
 	struct DSC_IDataStore_Vtbl *ptrVtbl;
};

#endif

//---------------------------------------------------------------------------
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_I_DATA_STORE_HPP_
