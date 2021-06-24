//
// Created by loghin on 24.06.2021.
//

#ifndef CDS_SIGNATUREVERIFIER_HPP
#define CDS_SIGNATUREVERIFIER_HPP


template < Size byteSize >
class SignatureVerifier : virtual public CryptoOperation < byteSize > {
protected:
    auto run () noexcept -> SignatureVerifier & override = 0;

public:
    inline auto verify () noexcept -> SignatureVerifier & { return this->run(); }
};

#endif //CDS_SIGNATUREVERIFIER_HPP
