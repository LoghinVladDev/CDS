//
// Created by loghin on 31.03.2021.
//

#ifndef CDS_CONCEPTS_HPP
#define CDS_CONCEPTS_HPP

#if defined(__cpp_concepts)

class Object;
class String;

#include <type_traits>
#include <concepts>

template <typename T>
concept Integral =
        std::is_integral<T>::value ||
        std::is_convertible<T, int>::value ||
        std::is_convertible<T, long long int>::value ||
        std::is_convertible<T, float>::value ||
        std::is_convertible<T, double>::value;

template < typename T >
concept Iterable = requires ( T obj ) {
    { obj.begin() } -> std::same_as < typename T::Iterator >;
    { obj.end() }   -> std::same_as < typename T::Iterator >;
};

template < typename T >
concept ConstIterable = requires ( T obj ) {
    { obj.begin() } -> std::same_as < typename T::ConstIterator >;
    { obj.end() }   -> std::same_as < typename T::ConstIterator >;
};

template < typename T >
concept ReverseIterable = requires ( T obj ) {
    { obj.rbegin() } -> std::same_as < typename T::ReverseIterator >;
    { obj.rend() }   -> std::same_as < typename T::ReverseIterator >;
};

template < typename T >
concept ConstReverseIterable = requires ( T obj ) {
    { obj.rbegin() } -> std::same_as < typename T::ConstReverseIterator >;
    { obj.rend() }   -> std::same_as < typename T::ConstReverseIterator >;
};

template < typename T >
concept ObjectDerived =
    std::is_base_of < Object, T > ::value;

template < typename T >
concept HasToString =
ObjectDerived < T >                         ||
    std::is_same < T, String >::value       ||
    std::is_same < T, const String >::value;

template <class H>
concept HashCalculatorHasBoundaryFunction = requires (H hashCalculator) {
    { hashCalculator.getBoundary() };
};

#include <std-types.h>
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

#endif

#endif //CDS_CONCEPTS_HPP
