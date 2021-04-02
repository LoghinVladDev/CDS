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

#endif //CDS_TRAITS_HPP
