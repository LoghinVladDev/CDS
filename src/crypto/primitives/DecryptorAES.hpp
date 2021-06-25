//
// Created by loghin on 24.06.2021.
//

#ifndef CDS_DECRYPTORAES_HPP
#define CDS_DECRYPTORAES_HPP

#include <CDS/crypto/Decryptor>
#include <CDS/crypto/SymmetricCryptoOperation>

#if defined(CDS_CRYPTO_OPENSSL)
#include <openssl/evp.h>
#include <openssl/conf.h>
#include <openssl/err.h>
#endif

template < Size byteSize >
class DecryptorAES : public Decryptor < byteSize >, public SymmetricCryptoOperation < byteSize > {
public:
    constexpr static auto isSizeSupported ( Size size ) noexcept -> bool {
        return size == 128 || size == 192 || size == 256;
    }

protected:
    auto run () noexcept -> DecryptorAES & override {

#if defined(CDS_CRYPTO_OPENSSL)

        static_assert ( DecryptorAES :: isSizeSupported( byteSize ), "Size not supported" );

        EVP_CIPHER_CTX * pCipherObject = EVP_CIPHER_CTX_new();

        if ( pCipherObject == nullptr ) {
            /// error handling
            return * this;
        }

        EVP_CIPHER const * pCipher;
        if constexpr ( byteSize == 128 ) {
            pCipher = EVP_aes_128_ecb();
        } else if constexpr ( byteSize == 192 ) {
            pCipher = EVP_aes_192_ecb();
        } else {
            pCipher = EVP_aes_256_ecb();
        }

        if ( 1 != EVP_DecryptInit_ex( pCipherObject, pCipher, nullptr, this->privateKey().data(), this->IV().data() ) ) {
            /// error handling
            return * this;
        }

        EVP_CIPHER_CTX_set_padding( pCipherObject, 0 );

        int length = 0;

        if ( 1 != EVP_DecryptUpdate ( pCipherObject, this->output().data(), & length, this->input().data(), byteSize ) ) {
            /// error handling
            return * this;
        }

        if ( 1 != EVP_DecryptFinal_ex ( pCipherObject, this->output().data(), & length ) ) {
            /// error handling
            return * this;
        }

        EVP_CIPHER_CTX_free( pCipherObject );

#endif

        return * this;
    }
};


#endif //CDS_DECRYPTORAES_HPP
