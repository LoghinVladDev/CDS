//
// Created by loghin on 24.06.2021.
//

#ifndef CDS_ASYMMETRICCRYPTOOPERATION_HPP
#define CDS_ASYMMETRICCRYPTOOPERATION_HPP

#include <CDS/crypto/CryptoOperation>

namespace cds {

    template < Size byteSize >
    class AsymmetricCryptoOperation : virtual public CryptoOperation < byteSize > {
    public:
        using KeyType = CryptoBlock < byteSize >;

    protected:
        KeyType _publicKey;
        KeyType _privateKey;

    public:
        inline auto publicKey () const noexcept -> KeyType const & { return this->_publicKey; }
        inline auto publicKey () noexcept -> KeyType & { return this->_publicKey; }

        inline auto privateKey () const noexcept -> KeyType const & { return this->_privateKey; }
        inline auto privateKey () noexcept -> KeyType & { return this->_privateKey; }

    };

}

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace utility {

        template<Size byteSize>
        struct TypeParseTraits<AsymmetricCryptoOperation<byteSize>> {
            constexpr static StringLiteral name = "AsymmetricCryptoOperation";
        };

    }
}

#endif //CDS_ASYMMETRICCRYPTOOPERATION_HPP
