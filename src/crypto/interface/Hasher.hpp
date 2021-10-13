//
// Created by loghin on 24.06.2021.
//

#ifndef CDS_HASHER_HPP
#define CDS_HASHER_HPP

template < Size byteSize >
class Hasher : virtual public CryptoOperation < byteSize > {
protected:
    auto run () noexcept -> Hasher & override = 0;

public:
    inline auto hash () noexcept -> Hasher & { return this->run(); }
};


namespace Utility {
    template<Size byteSize>
    struct TypeParseTraits<Hasher<byteSize>> {
        constexpr static StringLiteral name = "Hasher";
    };
}

#endif //CDS_HASHER_HPP
