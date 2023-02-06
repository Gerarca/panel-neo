//---------------------------------------------------------------------------
//
//	DSC_IBlockCipher.hpp
//  Copyright 2017 Johnson Controls. All rights reserved.
//
//	The interface for implementing block encryption components.
//
//---------------------------------------------------------------------------

//the "#pragma once" directive (if supported by a compiler) should prevent name clashes
#pragma once

#include "DSC_IComponent.hpp"

#ifndef _DSC_I_BLOCK_CIPHER_HPP_
#define _DSC_I_BLOCK_CIPHER_HPP_

#ifdef __cplusplus
extern "C" {
#endif	//__cplusplus

//---------------------------------------------------------------------------
namespace SDK_MAJOR_NAMESPACE {
namespace SDK_MINOR_NAMESPACE {
//---------------------------------------------------------------------------

//The implementation must be thread safe.
#define NAME_DSC_IBlockCipher	"DSC_IBlockCipher"

//---------------------------------------------------------------------------

#ifndef DSC_IBlockCipher_FWD_DEFINED
#define DSC_IBlockCipher_FWD_DEFINED
typedef DSC_INTERFACE DSC_IBlockCipher DSC_IBlockCipher;
#endif

//---------------------------------------------------------------------------

#if defined(__cplusplus) && !defined(C_STYLE_INTERFACE)

/*!
	This interface is used for encrypting and decrypting data.
	There is a default AES128 EBC encryption algorithm built into the SDK. 
	This interface is provided solely for integrators that perfer to use their own 
	custom encryption. (eg. hardware encryption)
	(The implementation must be thread safe.)
*/
DSC_INTERFACE DSC_IBlockCipher : public DSC_IComponent
{
public:

	//! Get the cipher's key size.
    /*!	
     	\param result Pointer to DSC_SIZE_T member that receives the size information.
    */
	virtual IRESULT ICALL get_KeySize(OUT DSC_SIZE_T* result) = 0;

	//! Get the cipher's block size.
    /*!	
     	\param result Pointer to DSC_SIZE_T member that receives the size information.
    */
	virtual IRESULT ICALL get_BlockSize(OUT DSC_SIZE_T* result) = 0;

    //! This function is used to encrypt data.
    /*! 
		The function encrypts the data and stores it in the ouput data buffer.

		\param bufKey Pointer to the buffer containing the encryption key
     	\param numKeySize The size of the encryption key stored in the buffer
     	\param bufIV Pointer to the buffer containing the initialization vector; it may be NULL if the encryption algorithm does not require the initization vector						
     	\param numIVSize The size of the initialization vector; it may be 0 if the encryption algorithm does not require it
     	\param bufToEncrypt Pointer to the buffer containing the data to be encrypted	
     	\param numToEncryptSize the size of the data to be encrypted; the size must meet the requirements of the algorithm used
     	\param bufEncrypted Pointer to the buffer that will receive the encrypted data
     	\param numEncryptedSize The size of the buffer that will receive the encrypted data; the size must	meet the requirements of the algorithm used
     	\param ptrCount The number of bytes that were stored in the output buffer as the result of encryption
    */
	virtual IRESULT ICALL Encrypt(
		IN BYTE const* bufKey, IN DSC_SIZE_T numKeySize,
		IN BYTE const* bufIV, IN DSC_SIZE_T numIVSize, 
		IN BYTE const* bufToEncrypt, IN DSC_SIZE_T numToEncryptSize,
		IN_OUT BYTE* bufEncrypted, IN DSC_SIZE_T numEncryptedSize,
		OUT DSC_SIZE_T* ptrCount) = 0;

	//! This function is used to decrypt data.
    /*!	
		The function decrypts the data and stores it in the ouput data buffer.

		\param bufKey Pointer to the buffer containing the decryption key
     	\param numKeySize The size of the decryption key stored in the buffer
     	\param bufIV Pointer to the buffer containing the initialization vector; it may be NULL if the encryption algorithm does not require the initization vector						
     	\param numIVSize The size of the initialization vector; it may be 0 if the decryption algorithm does not require it
     	\param bufToDecrypt Pointer to the buffer containing the data to be decrypted	
     	\param numToDecryptSize the size of the data to be decrypted; the size must meet the requirements of the algorithm used
     	\param bufDecrypted Pointer to the buffer that will receive the decrypted data
     	\param numDecryptedSize The size of the buffer that will receive the decrypted data; the size must	meet the requirements of the algorithm used
     	\param ptrCount The number of bytes that were stored in the output buffer as the result of decryption
    */
	virtual IRESULT ICALL Decrypt(
		IN BYTE const* bufKey, IN DSC_SIZE_T numKeySize,
		IN BYTE const* bufIV, IN DSC_SIZE_T numIVSize, 
		IN BYTE const* bufToDecrypt, IN DSC_SIZE_T numToDecryptSize,
		IN_OUT BYTE* bufDecrypted, IN DSC_SIZE_T numDecryptedSize,
		OUT DSC_SIZE_T* ptrCount) = 0;
};

#else

typedef struct DSC_IBlockCipher_Vtbl
{
	BEGIN_INTERFACE

	IRESULT (ICALL *Query)(IN DSC_IBlockCipher *This, IN char const* pszInterface, OUT VOID** ptrInterface);
	IRESULT (ICALL *Acquire)(IN DSC_IBlockCipher *This, OUT ICOUNT* ptrCount);
	IRESULT (ICALL *Release)(IN DSC_IBlockCipher *This, OUT ICOUNT* ptrCount);

	IRESULT (ICALL *get_KeySize)(IN DSC_IBlockCipher *This, OUT DSC_SIZE_T* result);
	IRESULT (ICALL *get_BlockSize)(IN DSC_IBlockCipher *This, OUT DSC_SIZE_T* result);
	IRESULT (ICALL *Encrypt)(IN DSC_IBlockCipher *This, 
		IN BYTE const* bufKey, IN DSC_SIZE_T numKeySize,
		IN BYTE const* bufIV, IN DSC_SIZE_T numIVSize, 
		IN BYTE const* bufToEncrypt, IN DSC_SIZE_T numToEncryptSize,
		IN_OUT BYTE* bufEncrypted, IN DSC_SIZE_T numEncryptedSize,
		OUT DSC_SIZE_T* ptrCount);
	IRESULT (ICALL *Decrypt)(IN DSC_IBlockCipher *This, 
		IN BYTE const* bufKey, IN DSC_SIZE_T numKeySize,
		IN BYTE const* bufIV, IN DSC_SIZE_T numIVSize, 
		IN BYTE const* bufToDecrypt, IN DSC_SIZE_T numToDecryptSize,
		IN_OUT BYTE* bufDecrypted, IN DSC_SIZE_T numDecryptedSize,
		OUT DSC_SIZE_T* ptrCount);

	END_INTERFACE
} DSC_IBlockCipher_Vtbl;

DSC_INTERFACE DSC_IBlockCipher
{
	//the assumption: the compiler places pointer to VTABLE first in the class layout
 	struct DSC_IBlockCipher_Vtbl *ptrVtbl;
};

#endif

//---------------------------------------------------------------------------
} //SDK_MINOR_NAMESPACE
} //SDK_MAJOR_NAMESPACE
//---------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif	//__cplusplus

#endif	//_DSC_I_BLOCK_CIPHER_HPP_
