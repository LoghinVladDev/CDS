//
// Created by loghin on 24.06.2021.
//

#ifndef CDS_SIGNATUREGENERATOR_HPP
#define CDS_SIGNATUREGENERATOR_HPP

#include <CDS/crypto/CryptoOperation>

namespace cds {

    template < Size byteSize >
    class SignatureGenerator : virtual public CryptoOperation < byteSize > { // NOLINT(clion-misra-cpp2008-10-1-1)
    protected:
        auto run () noexcept -> SignatureGenerator & override = 0;

    public:
        inline auto sign () noexcept -> SignatureGenerator & { return this->run(); }
    };

}

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace utility {


        template<Size byteSize>
        struct TypeParseTraits<SignatureGenerator<byteSize>> {
            constexpr static StringLiteral name = "SignatureGenerator";
        };

    }
}

#endif //CDS_SIGNATUREGENERATOR_HPP
