//
// Created by loghin on 24.06.2021.
//

#ifndef CDS_ENCRYPTOR_HPP
#define CDS_ENCRYPTOR_HPP

#include <CDS/crypto/CryptoOperation>

namespace cds {

    template < Size byteSize >
    class Encryptor : virtual public CryptoOperation < byteSize > { // NOLINT(clion-misra-cpp2008-10-1-1)
    public:
        using IVType = CryptoBlock < byteSize >;

    protected:
        auto run () noexcept -> Encryptor & override = 0;

        IVType _IV; // NOLINT(bugprone-reserved-identifier,clion-misra-cpp2008-11-0-1)

    public:
        inline auto encrypt () noexcept -> Encryptor & { return this->run(); }

        __CDS_NoDiscard constexpr auto IV () const noexcept -> IVType const & { return this->_IV; }
        __CDS_NoDiscard constexpr auto IV () noexcept -> IVType & { return this->_IV; }
    };

}

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace utility {

        template<Size byteSize>
        struct TypeParseTraits<Encryptor<byteSize>> {
            constexpr static StringLiteral name = "Encryptor";
        };

    }
}

#endif //CDS_ENCRYPTOR_HPP
