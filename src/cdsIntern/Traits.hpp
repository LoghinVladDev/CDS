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
//
//template < typename T >
//struct hasFirstGetter {
//private:
//    typedef char Yes[1];
//    typedef char No[2];
//
//    template < typename C > static Yes & test ( decltype ( & C ::getFirst ) );
//    template < typename C > static No & test(...);
//public:
//    enum { value = sizeof(test<T>(0)) == sizeof(Yes) };
//};
//
//template < typename T >
//struct hasSecondGetter {
//private:
//    typedef char Yes[1];
//    typedef char No[2];
//
//    template < typename C > static Yes & test ( decltype ( & C ::getSecond ) );
//    template < typename C > static No & test(...);
//public:
//    enum { value = sizeof(test<T>(0)) == sizeof(Yes) };
//};
//template < typename T >
//struct isPair {
//    constexpr static bool value = hasFirstGetter<T>::value && hasSecondGetter<T>::value;
//};

template < class T >
struct isPair : public std::false_type {};
template < class T1, class T2 >
struct isPair <Pair<T1, T2>> : public std::true_type {};

#if defined(__cpp_concepts)
template < typename T >
concept IsMappable = isPair<T>::value;
#endif
//#include <Pair.hpp>
//template < typename T >
//struct pairFirstType {
//private:
//
//};

//template < typename T >
//struct pairFirstType {
//    typename std::conditional < isPair < T >::value,
//};

#endif //CDS_TRAITS_HPP
