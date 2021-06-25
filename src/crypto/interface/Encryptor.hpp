//
// Created by loghin on 24.06.2021.
//

#ifndef CDS_ENCRYPTOR_HPP
#define CDS_ENCRYPTOR_HPP

#include <CDS/crypto/CryptoOperation>

template < Size byteSize >
class Encryptor : virtual public CryptoOperation < byteSize > {
public:
    using IVType = CryptoBlock < byteSize >;

protected:
    auto run () noexcept -> Encryptor & override = 0;

    IVType _IV; // NOLINT(bugprone-reserved-identifier)

public:
    inline auto encrypt () noexcept -> Encryptor & { return this->run(); }

    [[nodiscard]] constexpr auto IV () const noexcept -> IVType const & { return this->_IV; }
    [[nodiscard]] constexpr auto IV () noexcept -> IVType & { return this->_IV; }
};

#endif //CDS_ENCRYPTOR_HPP
