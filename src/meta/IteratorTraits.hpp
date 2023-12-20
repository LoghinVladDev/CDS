//
// Created by loghin on 12/8/23.
//

#ifndef CDS_META_ITERATOR_TRAITS_HPP
#define CDS_META_ITERATOR_TRAITS_HPP
#pragma once

#include <cds/meta/ObjectTraits>

namespace cds {
namespace meta {
namespace impl {
template <typename I, template <typename...> class P, typename = void> struct IteratorIsPrefixIncrementable :
    ::cds::meta::False {};

template <typename I, template <typename...> class P>
struct IteratorIsPrefixIncrementable<I, P, ::cds::meta::Void<decltype(++::cds::meta::lvalue<I>())>> :
    P<decltype(++::cds::meta::lvalue<I>())> {};

template <typename I, template <typename...> class P, typename = void> struct IteratorIsIndirectable :
    ::cds::meta::False {};

template <typename I, template <typename...> class P>
struct IteratorIsIndirectable<I, P, ::cds::meta::Void<decltype(*::cds::meta::rvalue<I>())>> :
   P<decltype(*::cds::meta::rvalue<I>())> {};

template <typename T, typename = void> struct HasIterableMemberFns : ::cds::meta::False {};
template <typename T, typename = void> struct HasConstIterableMemberFns : ::cds::meta::False {};
template <typename T, typename = void> struct HasReverseIterableMemberFns : ::cds::meta::False {};
template <typename T, typename = void> struct HasConstReverseIterableMemberFns : ::cds::meta::False {};

template <typename T>
struct HasIterableMemberFns<
    T, ::cds::meta::Void<decltype(::cds::meta::rvalue<T>().begin()), decltype(::cds::meta::rvalue<T>().end())>
> : ::cds::meta::True {
  using Iterator = decltype(::cds::meta::rvalue<T>().begin());
};

template <typename T> struct HasConstIterableMemberFns<
    T, ::cds::meta::Void<decltype(::cds::meta::rvalue<T>().cbegin()), decltype(::cds::meta::rvalue<T>().cend())>
> : ::cds::meta::True {
  using ConstIterator = decltype(::cds::meta::rvalue<T>().cbegin());
};

template <typename T> struct HasReverseIterableMemberFns<
    T, ::cds::meta::Void<decltype(::cds::meta::rvalue<T>().rbegin()), decltype(::cds::meta::rvalue<T>().rend())>
> : ::cds::meta::True {
  using ReverseIterator = decltype(::cds::meta::rvalue<T>().rbegin());
};

template <typename T> struct HasConstReverseIterableMemberFns<
    T, ::cds::meta::Void<decltype(::cds::meta::rvalue<T>().crbegin()), decltype(::cds::meta::rvalue<T>().crend())>
> : ::cds::meta::True {
  using ConstReverseIterator = decltype(::cds::meta::rvalue<T>().crbegin());
};

template <typename T> struct IsIterator : False {};
template <typename T> struct IsReverseIterator : False {};
} // namespace impl

template <typename Sentinel, typename Iterator> struct IsSentinelFor :
    ::cds::meta::IsEqCompatible<Sentinel, Iterator>::Type {};

template <typename Iterator> struct IsInputIterator : ::cds::meta::And<
    IsSentinelFor<Iterator, Iterator>,
    ::cds::meta::impl::IteratorIsPrefixIncrementable<
        Iterator, ::cds::meta::Bind<::cds::meta::IsSame, Iterator&, ::cds::meta::Ph<0>>::template Type
    >,
    ::cds::meta::impl::IteratorIsIndirectable<
        Iterator,
        ::cds::meta::Bind<::cds::meta::Unless<::cds::meta::IsSame>::Type, void, ::cds::meta::Ph<0>>::template Type
    >
> {};

template <typename Iterator> struct IsOutputIterator : ::cds::meta::And<
    IsInputIterator<Iterator>,
    ::cds::meta::impl::IteratorIsIndirectable<
        Iterator, ::cds::meta::Unless<::cds::meta::Apply<::cds::meta::IsConst, ::cds::meta::RemoveRef>::Type>::Type
    >
> {};

template <typename Iterator> struct IsForwardIterator : ::cds::meta::And<
    ::cds::meta::IsPrefixIncrementable<Iterator>,
    ::cds::meta::IsIndirectionCompatible<Iterator>,
    IsSentinelFor<Iterator, Iterator>
>{};

template <typename Iterator> struct IsBidirectionalIterator : ::cds::meta::And<
    IsForwardIterator<Iterator>,
    ::cds::meta::IsPrefixDecrementable<Iterator>
>{};

template <typename Iterator> struct IsRandomAccessIterator : ::cds::meta::And<
    IsBidirectionalIterator<Iterator>,
    ::cds::meta::IsSubscriptCompatible<Iterator>,
    ::cds::meta::IsAddCompatible<Iterator, int>,
    ::cds::meta::IsSubCompatible<Iterator, int>,
    ::cds::meta::IsSubCompatible<Iterator>
>{};

template <typename Range> struct IterableTraits {};
} // namespace meta
} // namespace cds

#endif // CDS_META_ITERATOR_TRAITS_HPP
