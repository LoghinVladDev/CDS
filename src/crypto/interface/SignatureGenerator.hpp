//
// Created by loghin on 24.06.2021.
//

#ifndef CDS_SIGNATUREGENERATOR_HPP
#define CDS_SIGNATUREGENERATOR_HPP

template < Size byteSize >
class SignatureGenerator : virtual public CryptoOperation < byteSize > {
protected:
    auto run () noexcept -> SignatureGenerator & override = 0;

public:
    inline auto sign () noexcept -> SignatureGenerator & { return this->run(); }
};


#endif //CDS_SIGNATUREGENERATOR_HPP
