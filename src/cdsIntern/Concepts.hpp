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
#include <iostream>

template <typename T>
concept Integral =
        std::is_integral<T>::value ||
        std::is_convertible<T, int>::value ||
        std::is_convertible<T, long long int>::value ||
        std::is_convertible<T, float>::value ||
        std::is_convertible<T, double>::value;

template < typename T >
concept Pointer =
        std::is_pointer<T>::value;

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

template < typename T >
concept Printable = requires (T t) {
    { std::cout << t } -> std::same_as < std::ostream & >;
};

#if defined(__cpp_concepts)

template <class T>
concept Callable = std::is_invocable<T>::value;

template <typename T>
concept UniqueIdentifiableByObject = requires {
    std::is_base_of < Object, T >::value;
};

template <typename T>
concept UniqueIdentifiableByOperator = requires ( T const & a, T const & b ) {
    a == b;
};

template <typename T>
concept UniqueIdentifiable = requires ( T const & a, T const & b ) {
    UniqueIdentifiableByObject<T> || UniqueIdentifiableByOperator<T>;
};

#include <CDS/Types>
template < typename Predicate, typename T >
concept IsPredicateOver =
    std::is_invocable_r < bool, Predicate, decltype ((*dataTypes::unsafeAddress<T>())) > :: type :: value;

template < typename Action, typename T >
concept IsActionOver =
    std::is_invocable_r < void, Action, decltype ((*dataTypes::unsafeAddress<T>())) > :: type :: value;

#endif

#endif

#if !defined(REQUIRES)
    #if defined(__cpp_concepts)
        #define REQUIRES(concepts) requires concepts
    #else
        #define REQUIRES(concepts)
    #endif
#endif

#endif //CDS_CONCEPTS_HPP
