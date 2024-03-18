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
using meta::Void;
using meta::False;
using meta::lvalue;

template <typename, template <typename...> class, typename = void> struct IteratorIsPrefixIncrementable : False {};

template <typename I, template <typename...> class P>
struct IteratorIsPrefixIncrementable<I, P, Void<decltype(++lvalue<I>())>> : P<decltype(++lvalue<I>())> {};

template <typename, template <typename...> class, typename = void> struct IteratorIsIndirectable : False {};

template <typename I, template <typename...> class P>
struct IteratorIsIndirectable<I, P, Void<decltype(*meta::rvalue<I>())>> : P<decltype(*rvalue<I>())> {};

template <typename, typename = void> struct HasIterableMemberFns : False {};
template <typename, typename = void> struct HasConstIterableMemberFns : False {};
template <typename, typename = void> struct HasReverseIterableMemberFns : False {};
template <typename, typename = void> struct HasConstReverseIterableMemberFns : False {};

template <typename T>
struct HasIterableMemberFns<T, Void<decltype(meta::rvalue<T>().begin()), decltype(meta::rvalue<T>().end())>> :
    meta::True {
  using Iterator = decltype(meta::rvalue<T>().begin());
  using Sentinel = decltype(meta::rvalue<T>().end());
};

template <typename T> struct HasConstIterableMemberFns<
    T, Void<decltype(meta::rvalue<T>().cbegin()), decltype(meta::rvalue<T>().cend())>
> : meta::True {
  using ConstIterator = decltype(meta::rvalue<T>().cbegin());
  using Sentinel = decltype(meta::rvalue<T>().cend());
};

template <typename T> struct HasReverseIterableMemberFns<
    T, Void<decltype(meta::rvalue<T>().rbegin()), decltype(meta::rvalue<T>().rend())>
> : meta::True {
  using ReverseIterator = decltype(meta::rvalue<T>().rbegin());
  using Sentinel = decltype(meta::rvalue<T>().rend());
};

template <typename T> struct HasConstReverseIterableMemberFns<
    T, Void<decltype(meta::rvalue<T>().crbegin()), decltype(meta::rvalue<T>().crend())>
> : meta::True {
  using ConstReverseIterator = decltype(meta::rvalue<T>().crbegin());
  using Sentinel = decltype(meta::rvalue<T>().crend());
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


template <template <typename...> class N, typename T, typename = typename IsConst<T>::Type>
struct NodeIteratorTraits {};

template <template <typename...> class N, typename T> struct NodeIteratorTraits<N, T, True> {
  using Node = N<RemoveConst<T>>;
  using Value = T;
};

template <template <typename...> class N, typename T> struct NodeIteratorTraits<N, T, False> {
  using Node = N<T>;
  using Value = T;
};

namespace sentinelForImpl {
template <typename T, typename = void> struct SentinelFor {
  using Type = T;
};
} // namespace sentinelForImpl

template <typename T> using SentinelFor = typename sentinelForImpl::SentinelFor<T>::Type;
} // namespace meta
} // namespace cds

#endif // CDS_META_ITERATOR_TRAITS_HPP
