//
// Created by loghin on 24.06.2021.
//

#ifndef CDS_HASHER_HPP
#define CDS_HASHER_HPP

#include <CDS/crypto/CryptoOperation>

namespace cds {

    template < Size byteSize >
    class Hasher : virtual public CryptoOperation < byteSize > { // NOLINT(clion-misra-cpp2008-10-1-1)
    protected:
        auto run () noexcept -> Hasher & override = 0;

    public:
        inline auto hash () noexcept -> Hasher & { return this->run(); }
    };

}

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace utility {

        template<Size byteSize>
        struct TypeParseTraits<Hasher<byteSize>> {
            constexpr static StringLiteral name = "Hasher";
        };

    }
}

#endif //CDS_HASHER_HPP
