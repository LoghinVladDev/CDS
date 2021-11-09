//
// Created by loghin on 24.06.2021.
//

#ifndef CDS_CRYPTOOPERATOR_HPP
#define CDS_CRYPTOOPERATOR_HPP

#include <CDS/crypto/CryptoBlock>

namespace cds {

    template < Size byteSize >
    class __CDS_MaybeUnused CryptoOperation : public Object {
    protected:
        CryptoBlock < byteSize > _input;
        CryptoBlock < byteSize > _output;

        CryptoOperation() noexcept = default;
        ~CryptoOperation() noexcept override = default;

    public:
        __CDS_NoDiscard constexpr auto input () const noexcept -> CryptoBlock < byteSize > const & { return this->_input; }
        __CDS_NoDiscard constexpr auto input () noexcept -> CryptoBlock < byteSize > & { return this->_input; }

        __CDS_NoDiscard constexpr auto output () const noexcept -> CryptoBlock < byteSize > const & { return this->_output; }
        __CDS_NoDiscard constexpr auto output () noexcept -> CryptoBlock < byteSize > & { return this->_output; }

        __CDS_MaybeUnused virtual auto run () noexcept -> CryptoOperation & = 0;

        __CDS_NoDiscard auto toString () const noexcept -> String override {
            return "CryptoBlock "_s +
                "{ input = " + this->_input.toString() +
                ", output = " + this->_output.toString() +
                " }";
        }
    };

}

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace utility {

        template<Size byteSize>
        struct TypeParseTraits<CryptoOperation<byteSize>> {
            constexpr static StringLiteral name = "CryptoOperation";
        };

    }
}


#endif //CDS_CRYPTOOPERATOR_HPP
