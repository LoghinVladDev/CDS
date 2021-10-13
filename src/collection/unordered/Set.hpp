//
// Created by loghin on 25.01.2021.
//

#ifndef CDS_SET_HPP
#define CDS_SET_HPP

#ifndef _OMIT_SEQUENCE_IMPL
#define _OMIT_SEQUENCE_IMPL // NOLINT(bugprone-reserved-identifier)

#include <CDS/UnorderedSet>
#include <CDS/OrderedSet>

#include <CDS/Sequence>

#ifndef _CDS_UNORDERED_SET_SEQUENCE_IMPL
#define _CDS_UNORDERED_SET_SEQUENCE_IMPL // NOLINT(bugprone-reserved-identifier)
template <class T>
auto UnorderedSet<T>::sequence() const noexcept -> Sequence< const UnorderedSet<T>> {
    return Sequence < typename std :: remove_reference < decltype (*this) > :: type > (*this);
}

template <class T>
auto UnorderedSet<T>::sequence() noexcept -> Sequence<UnorderedSet<T>> {
    return Sequence < typename std :: remove_reference < decltype (*this) > :: type > (*this);
}
#endif

#ifndef _CDS_ORDERED_SET_SEQUENCE_IMPL
#define _CDS_ORDERED_SET_SEQUENCE_IMPL // NOLINT(bugprone-reserved-identifier)
template <class T, class C>
#if defined(__cpp_concepts) && !defined(_MSC_VER)
requires ValidSetComparator <T, C>
#endif
auto OrderedSet<T, C>::sequence() const noexcept -> Sequence < const OrderedSet < T, C > > {
    return Sequence < typename std :: remove_reference < decltype (*this) > :: type > (*this);
}

template <class T, class C>
#if defined(__cpp_concepts) && !defined(_MSC_VER)
requires ValidSetComparator <T, C>
#endif
auto OrderedSet<T, C>::sequence() noexcept -> Sequence < OrderedSet < T, C > > {
    return Sequence < typename std :: remove_reference < decltype (*this) > :: type > (*this);
}
#endif

#undef _OMIT_SEQUENCE_IMPL
#endif


#endif //CDS_SET_HPP
