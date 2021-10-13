//
// Created by loghin on 24.06.2021.
//

#ifndef CDS_DECRYPTOR_HPP
#define CDS_DECRYPTOR_HPP

#include <CDS/crypto/CryptoOperation>

template < Size byteSize >
class Decryptor : virtual public CryptoOperation < byteSize > {
public:
    using IVType = CryptoBlock < byteSize >;

protected:
    auto run () noexcept -> Decryptor & override = 0;

    IVType _IV; // NOLINT(bugprone-reserved-identifier)

public:
    inline auto decrypt () noexcept -> Decryptor & { return this->run(); }

    [[nodiscard]] constexpr auto IV () const noexcept -> IVType const & { return this->_IV; }
    [[nodiscard]] constexpr auto IV () noexcept -> IVType & { return this->_IV; }
};

namespace Utility {
    template<Size byteSize>
    struct TypeParseTraits<Decryptor<byteSize>> {
        constexpr static StringLiteral name = "Decryptor";
    };
}

#endif //CDS_DECRYPTOR_HPP
