//
// Created by loghin on 24.06.2021.
//

#ifndef CDS_SYMMETRICCRYPTOOPERATION_HPP
#define CDS_SYMMETRICCRYPTOOPERATION_HPP

#include <CDS/crypto/CryptoOperation>

template < Size byteSize >
class SymmetricCryptoOperation : virtual public CryptoOperation < byteSize > {
public:
    using KeyType = CryptoBlock < byteSize >;

protected:
    KeyType _privateKey;

public:
    inline auto privateKey () const noexcept -> KeyType const & { return this->_privateKey; }
    inline auto privateKey () noexcept -> KeyType & { return this->_privateKey; }

};

#endif //CDS_SYMMETRICCRYPTOOPERATION_HPP
