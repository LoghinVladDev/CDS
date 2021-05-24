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

namespace dataTypes {
    template<class T> static auto hash(T const &) noexcept -> Index { return 0; }
    template<> auto hash<String>(String const &o) noexcept -> Index;
    template<> auto hash<Object>(Object const &o) noexcept -> Index;
    template<> auto hash<CString>(CString const &o) noexcept -> Index { return std::strlen(o); }
    template<> auto hash<StringLiteral>(StringLiteral const &o) noexcept -> Index { return std::strlen(o); }
    template<> auto hash<uint8>(uint8 const &o) noexcept -> Index { return o; }
    template<> auto hash<uint16>(uint16 const &o) noexcept -> Index { return o; }
    template<> auto hash<uint32>(uint32 const &o) noexcept -> Index { return o; }
    template<> auto hash<uint64>(uint64 const &o) noexcept -> Index { return o; }
    template<> auto hash<sint8>(sint8 const &o) noexcept -> Index { return o; }
    template<> auto hash<sint16>(sint16 const &o) noexcept -> Index { return o; }
    template<> auto hash<sint32>(sint32 const &o) noexcept -> Index { return o; }
    template<> auto hash<sint64>(sint64 const &o) noexcept -> Index { return o; }
    template <> auto hash<float> (float const & o) noexcept -> Index { return static_cast < uint32 > ( o * 1000.0f ); }
    template <> auto hash<double> (double const & o) noexcept -> Index { return static_cast < uint64 > ( o * 100000.0 ); }

#if defined(CDS_GLM)

    template < glm::length_t l, typename T, glm::qualifier q >
    auto hash ( glm::vec < l, T , q > const & v ) noexcept -> Index {
        if constexpr ( l == 1 )         return hash (v.x);
        else if constexpr ( l == 2 )    return hash (v.x) * 100 + hash (v.y);
        else if constexpr ( l == 3 )    return hash (v.x) * 10000 + hash (v.y) * 100 + hash(v.z);
        else if constexpr ( l == 4 )    return hash (v.x) * 1000000 + hash (v.y) * 10000 + hash(v.z) * 100 + hash(v.w);
        else return 0;
    }

#endif
}

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
            return dataTypes::hash(v) % hashBoundary;
        }
    };

#if defined(CDS_EASY_HASH_DEBUG)
    template <class K> using HighCollisionDefaultHashFunction = DefaultHashFunction<K, 1>;
    template <class K> using MediumCollisionDefaultHashFunction = DefaultHashFunction<K, 2>;
    template <class K> using LowCollisionDefaultHashFunction = DefaultHashFunction<K, 3>;
#else
    template <class K> using HighCollisionDefaultHashFunction = DefaultHashFunction<K, 256>;
    template <class K> using MediumCollisionDefaultHashFunction = DefaultHashFunction<K, 4096>;
    template <class K> using LowCollisionDefaultHashFunction = DefaultHashFunction<K, 32768>;
#endif
}

#endif //CDS_TYPES_HPP
