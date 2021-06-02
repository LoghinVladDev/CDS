//
// Created by loghin on 31.03.2021.
//

#ifndef CDS_TRAITS_HPP
#define CDS_TRAITS_HPP

#include <type_traits>
#include <utility>

template < typename T, typename U, typename = std::void_t<> > struct isComparableLess : std::false_type {};
template < typename T, typename U, typename = std::void_t<> > struct isComparableLessNoexcept : std::false_type {};

template < typename T, typename U > struct isComparableLess < T, U, std::void_t < decltype ( std::declval <T> () < std::declval <U> () ) > > : std::true_type {};
template < typename T, typename U > struct isComparableLessNoexcept < T, U, std::void_t < decltype ( std::declval <T> () < std::declval <U>() ) > > : std::bool_constant < noexcept ( std::declval <T> () < std::declval <U> () ) > { };

template < class T >
struct isPair : public std::false_type {};
template < class T1, class T2 >
struct isPair <Pair<T1, T2>> : public std::true_type {};

#if defined(__cpp_concepts)
template < typename T >
concept IsMappable = isPair<T>::value;
#endif


template < typename T, typename U = void >
struct isPrintable : std::false_type {};

template < typename T >
struct isPrintable <
        T,
        std::enable_if_t <
                std::is_same < decltype (std::cout << std::declval<T>()), std::ostream & >::value
        >
> : std::true_type { };

template < typename D, typename B >
using isDerivedFrom = std::is_base_of < B, D >;

template < typename B, typename D >
using isBaseOf = std::is_base_of < B, D >;

template < typename D >
using isObjectDerived = isDerivedFrom < D, Object >;

#endif //CDS_TRAITS_HPP
