//
// Created by loghin on 24.06.2021.
//

#ifndef CDS_DECRYPTOR_HPP
#define CDS_DECRYPTOR_HPP

#include <CDS/crypto/CryptoOperation>

namespace cds {

    template < Size byteSize >
    class Decryptor : virtual public CryptoOperation < byteSize > { // NOLINT(clion-misra-cpp2008-10-1-1)
    public:
        using IVType = CryptoBlock < byteSize >;

    protected:
        auto run () noexcept -> Decryptor & override = 0;

        IVType _IV; // NOLINT(bugprone-reserved-identifier,clion-misra-cpp2008-11-0-1)

    public:
        inline auto decrypt () noexcept -> Decryptor & { return this->run(); }

        __CDS_NoDiscard constexpr auto IV () const noexcept -> IVType const & { return this->_IV; }
        __CDS_NoDiscard constexpr auto IV () noexcept -> IVType & { return this->_IV; }
    };

}

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace utility {

        template<Size byteSize>
        struct TypeParseTraits<Decryptor<byteSize>> {
            constexpr static StringLiteral name = "Decryptor";
        };

    }
}

#endif //CDS_DECRYPTOR_HPP
