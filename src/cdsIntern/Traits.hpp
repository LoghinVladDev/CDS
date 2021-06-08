//
// Created by loghin on 31.03.2021.
//

#ifndef CDS_TRAITS_HPP
#define CDS_TRAITS_HPP

#include <type_traits>
#include <utility>
#include <CDS/Pair>
#include <iostream>

template < typename T, typename U, typename = std::void_t<> > struct isComparableLess : std::false_type {};
template < typename T, typename U, typename = std::void_t<> > struct isComparableLessNoexcept : std::false_type {};
template < typename T, typename U, typename = std::void_t<> > struct isComparableEquals : std::false_type {};
template < typename T, typename U, typename = std::void_t<> > struct isComparableEqualsNoexcept : std::false_type {};

template < typename T, typename U > struct isComparableLess < T, U, std::void_t < decltype ( std::declval <T> () < std::declval <U> () ) > > : std::true_type {};
template < typename T, typename U > struct isComparableLessNoexcept < T, U, std::void_t < decltype ( std::declval <T> () < std::declval <U>() ) > > : std::bool_constant < noexcept ( std::declval <T> () < std::declval <U> () ) > { };

template < typename T, typename U > struct isComparableEquals < T, U, std::void_t < decltype ( std::declval <T> () == std::declval <U> () ) > > : std::true_type {};
template < typename T, typename U > struct isComparableEqualsNoexcept < T, U, std::void_t < decltype ( std::declval <T> () == std::declval <U>() ) > > : std::bool_constant < noexcept ( std::declval <T> () == std::declval <U> () ) > { };

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

template < typename T, typename = void >
struct functionTraits;

template < typename R, typename ... A >
struct functionTraits < R (*) (A ...) > {
    using returnType = R;
    using classType = void;
    using argsType = std::tuple < A... >;
};

template < typename R, typename C, typename ... A >
struct functionTraits < R (C::*) (A ...) > {
    using returnType = R;
    using classType = C;
    using argsType = std::tuple < A ... >;
};

template < typename R, typename C, typename ... A >
struct functionTraits < R (C::*) (A ...) const > {
    using returnType = R;
    using classType = C;
    using argsType = std::tuple < A ... >;
};

template < typename T >
struct functionTraits < T, std::void_t < decltype ( & T :: operator () ) > > :
    public functionTraits < decltype ( & T :: operator () ) > {

};

template < typename T, typename = void >
struct returnTrait;

template < typename R, typename ... A >
struct returnTrait < R (*) (A ...) > {
    using returnType = R;
};

template < typename R, typename C, typename ... A >
struct returnTrait < R (C::*) (A ...) > {
    using returnType = R;
};

template < typename R, typename C, typename ... A >
struct returnTrait < R (C::*) (A ...) const > {
    using returnType = R;
};

template < typename T >
struct returnTrait < T, std::void_t < decltype ( & T :: operator () ) > > :
    public returnTrait < decltype ( & T :: operator () ) > {

};

template < typename T >
using returnOf = typename returnTrait < T > :: returnType;

template < typename T >
using argumentsOf = typename functionTraits < T > :: argsType;

template < typename T >
using classOf = typename functionTraits < T > :: classType;

# if defined (__cpp_concepts)

template < typename T >
concept PairType = isPair < T > :: value ;

template < typename T, typename V >
concept LessComparable = isComparableLess < T, V > :: type :: value;

template < typename T >
concept TypeLessComparable = LessComparable < T, T >;

# endif

#endif //CDS_TRAITS_HPP
