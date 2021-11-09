//
// Created by loghin on 24.06.2021.
//

#ifndef CDS_SIGNATUREVERIFIER_HPP
#define CDS_SIGNATUREVERIFIER_HPP

namespace cds {

    template < Size byteSize >
    class SignatureVerifier : virtual public CryptoOperation < byteSize > {
    protected:
        auto run () noexcept -> SignatureVerifier & override = 0;

    public:
        inline auto verify () noexcept -> SignatureVerifier & { return this->run(); }
    };

}

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace utility {

        template<Size byteSize>
        struct TypeParseTraits<SignatureVerifier<byteSize>> {
            constexpr static StringLiteral name = "SignatureVerifier";
        };

    }
}

#endif //CDS_SIGNATUREVERIFIER_HPP
