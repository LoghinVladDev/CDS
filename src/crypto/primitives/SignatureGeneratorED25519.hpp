//
// Created by loghin on 24.06.2021.
//

#ifndef CDS_SIGNATUREGENERATORED25519_HPP
#define CDS_SIGNATUREGENERATORED25519_HPP

#include <CDS/crypto/SignatureVerifier>
#include <CDS/crypto/AsymmetricCryptoOperation>

#if defined(CDS_CRYPTO_OPENSSL)
#include <openssl/evp.h>
#endif

template < Size byteSize >
class SignatureGeneratorED25519 : public AsymmetricCryptoOperation < byteSize >, public SignatureVerifier < byteSize > {
    auto run () override -> SignatureGeneratorED25519 & override {

#if defined(CDS_CRYPTO_OPENSSL)


#endif

        return * this;
    }
};

#endif //CDS_SIGNATUREGENERATORED25519_HPP
