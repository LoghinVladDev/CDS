//
// Created by loghin on 24.06.2021.
//

#ifndef CDS_DECRYPTOR_HPP
#define CDS_DECRYPTOR_HPP

template < Size byteSize >
class Decryptor : virtual public CryptoOperation < byteSize > {
protected:
    auto run () noexcept -> Decryptor & override = 0;

public:
    inline auto decrypt () noexcept -> Decryptor & { return this->run(); }
};

#endif //CDS_DECRYPTOR_HPP
