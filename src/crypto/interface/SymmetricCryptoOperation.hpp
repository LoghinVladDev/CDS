//
// Created by loghin on 24.06.2021.
//

#ifndef CDS_SYMMETRICCRYPTOOPERATION_HPP
#define CDS_SYMMETRICCRYPTOOPERATION_HPP

#include <CDS/crypto/CryptoOperation>

namespace cds {

    template < Size byteSize >
    class SymmetricCryptoOperation : virtual public CryptoOperation < byteSize > { // NOLINT(clion-misra-cpp2008-10-1-1)
    public:
        using KeyType = CryptoBlock < byteSize >;

    protected:
        KeyType _privateKey; // NOLINT(clion-misra-cpp2008-11-0-1)

    public:
        inline auto privateKey () const noexcept -> KeyType const & { return this->_privateKey; }
        inline auto privateKey () noexcept -> KeyType & { return this->_privateKey; }

    };

}


namespace cds {
    namespace utility {

        template<Size byteSize>
        struct TypeParseTraits<SymmetricCryptoOperation<byteSize>> {
            constexpr static StringLiteral name = "SymmetricCryptoOperation";
        };

    }
}

#endif //CDS_SYMMETRICCRYPTOOPERATION_HPP
