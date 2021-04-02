//
// Created by loghin on 31.03.2021.
//

#ifndef CDS_CONCEPTS_HPP
#define CDS_CONCEPTS_HPP

#if defined(__cpp_concepts)

class Object;
class String;

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

#endif

#endif //CDS_CONCEPTS_HPP