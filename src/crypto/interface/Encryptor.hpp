//
// Created by loghin on 24.06.2021.
//

#ifndef CDS_ENCRYPTOR_HPP
#define CDS_ENCRYPTOR_HPP

#include <CDS/crypto/CryptoOperation>

template < Size byteSize >
class Encryptor : virtual public CryptoOperation < byteSize > {
protected:
    auto run () noexcept -> Encryptor & override = 0;

public:
    inline auto encrypt () noexcept -> Encryptor & { return this->run(); }
};

#endif //CDS_ENCRYPTOR_HPP
