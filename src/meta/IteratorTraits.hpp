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
template <typename, template <typename...> class, typename = void> struct IteratorIsPrefixIncrementable :
    meta::False {};

template <typename I, template <typename...> class P>
struct IteratorIsPrefixIncrementable<I, P, Void<decltype(++meta::lvalue<I>())>> : P<decltype(++meta::lvalue<I>())> {};

template <typename, template <typename...> class, typename = void> struct IteratorIsIndirectable : meta::False {};

template <typename I, template <typename...> class P>
struct IteratorIsIndirectable<I, P, Void<decltype(*meta::rvalue<I>())>> : P<decltype(*meta::rvalue<I>())> {};

template <typename, typename = void> struct HasIterableMemberFns : meta::False {};
template <typename, typename = void> struct HasConstIterableMemberFns : meta::False {};
template <typename, typename = void> struct HasReverseIterableMemberFns : meta::False {};
template <typename, typename = void> struct HasConstReverseIterableMemberFns : meta::False {};

template <typename T>
struct HasIterableMemberFns<T, Void<decltype(meta::rvalue<T>().begin()), decltype(meta::rvalue<T>().end())>> :
    meta::True {
  using Iterator = decltype(meta::rvalue<T>().begin());
};

template <typename T> struct HasConstIterableMemberFns<
    T, Void<decltype(meta::rvalue<T>().cbegin()), decltype(meta::rvalue<T>().cend())>
> : meta::True {
  using ConstIterator = decltype(meta::rvalue<T>().cbegin());
};

template <typename T> struct HasReverseIterableMemberFns<
    T, Void<decltype(meta::rvalue<T>().rbegin()), decltype(meta::rvalue<T>().rend())>
> : meta::True {
  using ReverseIterator = decltype(meta::rvalue<T>().rbegin());
};

template <typename T> struct HasConstReverseIterableMemberFns<
    T, Void<decltype(meta::rvalue<T>().crbegin()), decltype(meta::rvalue<T>().crend())>
> : meta::True {
  using ConstReverseIterator = decltype(meta::rvalue<T>().crbegin());
};

template <typename> struct IsIterator : False {};
template <typename> struct IsReverseIterator : False {};
} // namespace impl

template <typename Sentinel, typename Iterator> struct IsSentinelFor :
    IsEqCompatible<Sentinel, Iterator>::Type {};

template <typename Iterator> struct IsInputIterator : And<
    IsSentinelFor<Iterator, Iterator>,
    impl::IteratorIsPrefixIncrementable<Iterator, Bind<IsSame, Iterator&, Ph<0>>::template Type>,
    impl::IteratorIsIndirectable<Iterator, Bind<Unless<IsSame>::Type, void, Ph<0>>::Type>
> {};

template <typename Iterator> struct IsOutputIterator : And<
    IsInputIterator<Iterator>,
    impl::IteratorIsIndirectable<Iterator, Unless<Apply<IsConst, RemoveRef>::Type>::Type>
> {};

template <typename Iterator> struct IsForwardIterator : And<
    IsPrefixIncrementable<Iterator>,
    IsIndirectionCompatible<Iterator>,
    IsSentinelFor<Iterator, Iterator>
> {};

template <typename Iterator> struct IsBidirectionalIterator : And<
    IsForwardIterator<Iterator>,
    IsPrefixDecrementable<Iterator>
> {};

template <typename Iterator> struct IsRandomAccessIterator : And<
    IsBidirectionalIterator<Iterator>,
    IsSubscriptCompatible<Iterator>,
    IsAddCompatible<Iterator, int>,
    IsSubCompatible<Iterator, int>,
    IsSubCompatible<Iterator>
> {};

template <typename> struct IterableTraits {};
} // namespace meta
} // namespace cds

#endif // CDS_META_ITERATOR_TRAITS_HPP
