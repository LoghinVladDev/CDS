//
// Created by vladl on 4/7/2021.
//

#ifndef CDS_TYPES_HPP
#define CDS_TYPES_HPP

#if defined(__cpp_concepts)
template <class H>
concept HashCalculatorHasBoundaryFunction = requires (H hashCalculator) {
    { hashCalculator.getBoundary() };
};
#endif

#include "../std-types.h"
class Object;
class String;

#include <cstring>
template <class T> static auto hash (T const &) noexcept -> Index { return 0; }
template <> auto hash<String> (String const & o) noexcept -> Index;
template <> auto hash<Object> (Object const & o) noexcept -> Index;
template <> auto hash<CString> (CString const & o)noexcept -> Index { return std::strlen(o); }
template <> auto hash<StringLiteral> (StringLiteral const & o)noexcept -> Index { return std::strlen(o); }
template <> auto hash<CDS_uint8> (CDS_uint8 const & o)noexcept -> Index { return o; }
template <> auto hash<CDS_uint16> (CDS_uint16 const & o)noexcept -> Index { return o; }
template <> auto hash<CDS_uint32> (CDS_uint32 const & o)noexcept -> Index { return o; }
template <> auto hash<CDS_uint64> (CDS_uint64 const & o)noexcept -> Index { return o; }
template <> auto hash<CDS_sint8> (CDS_sint8 const & o)noexcept -> Index { return o; }
template <> auto hash<CDS_sint16> (CDS_sint16 const & o)noexcept -> Index { return o; }
template <> auto hash<CDS_sint32> (CDS_sint32 const & o)noexcept -> Index { return o; }
template <> auto hash<CDS_sint64> (CDS_sint64 const & o)noexcept -> Index { return o; }

template <typename K, Size hashBoundary>
class HashCalculator {
public:
    using Value                 = K;
    using ValueConstReference   = Value const &;

    using HashValue             = Index;

    virtual auto operator ()(ValueConstReference) const noexcept -> HashValue = 0;

#if __cpp_constexpr >= 201907
    [[nodiscard]] virtual constexpr inline auto getBoundary () const noexcept -> Size { return hashBoundary; }
#else
    [[nodiscard]] virtual inline auto getBoundary () const noexcept -> Size { return hashBoundary; }
#endif
};

namespace dataTypes {
    template <class K, Size hashBoundary>
    class DefaultHashFunction : public HashCalculator<K, hashBoundary> {
    public:
        using AddressValue = std::size_t;

        auto operator ()(typename HashCalculator<K, hashBoundary>::ValueConstReference v) const noexcept -> typename HashCalculator<K, hashBoundary>::HashValue {
            return hash(v) % hashBoundary;
        }
    };

    template <class K> using HighCollisionDefaultHashFunction = DefaultHashFunction<K, 256>;
    template <class K> using MediumCollisionDefaultHashFunction = DefaultHashFunction<K, 4096>;
    template <class K> using LowCollisionDefaultHashFunction = DefaultHashFunction<K, 32768>;
}

#endif //CDS_TYPES_HPP
