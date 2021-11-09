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

namespace cds {

    template < Size byteSize >
    class __CDS_MaybeUnused SignatureGeneratorED25519 : public AsymmetricCryptoOperation < byteSize >, public SignatureVerifier < byteSize > {
        auto run () noexcept -> SignatureGeneratorED25519 & override {

    #if defined(CDS_CRYPTO_OPENSSL)


    #endif

            return * this;
        }
    };

}


namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace utility {

        template<Size byteSize>
        struct TypeParseTraits<SignatureGeneratorED25519<byteSize>> {
            constexpr static StringLiteral name = "SignatureGeneratorED25519";
        };

    }
}


#endif //CDS_SIGNATUREGENERATORED25519_HPP
