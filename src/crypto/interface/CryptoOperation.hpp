//
// Created by loghin on 24.06.2021.
//

#ifndef CDS_CRYPTOOPERATOR_HPP
#define CDS_CRYPTOOPERATOR_HPP

#include <CDS/crypto/CryptoBlock>

template < Size byteSize >
class CryptoOperation : public Object {
protected:
    CryptoBlock < byteSize > _input;
    CryptoBlock < byteSize > _output;

    CryptoOperation() noexcept = default;
    ~CryptoOperation() noexcept override = default;

public:
    [[nodiscard]] constexpr auto input () const noexcept -> CryptoBlock < byteSize > const & { return this->_input; }
    [[nodiscard]] constexpr auto input () noexcept -> CryptoBlock < byteSize > & { return this->_input; }

    [[nodiscard]] constexpr auto output () const noexcept -> CryptoBlock < byteSize > const & { return this->_output; }
    [[nodiscard]] constexpr auto output () noexcept -> CryptoBlock < byteSize > & { return this->_output; }

    virtual auto run () noexcept -> CryptoOperation & = 0;

    [[nodiscard]] auto toString () const noexcept -> String override {
        return "CryptoBlock "_s +
            "{ input = " + this->_input.toString() +
            ", output = " + this->_output.toString() +
            " }";
    }
};


#endif //CDS_CRYPTOOPERATOR_HPP
