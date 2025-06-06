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
struct IteratorIsIndirectable<I, P, Void<decltype(*rvalue<I>())>> : P<decltype(*rvalue<I>())> {};

template <typename, typename = void> struct HasIterableMemberFns : False {};
template <typename, typename = void> struct HasConstIterableMemberFns : False {};
template <typename, typename = void> struct HasReverseIterableMemberFns : False {};
template <typename, typename = void> struct HasConstReverseIterableMemberFns : False {};
template <typename, typename = void> struct HasSizeMemberFn : False {};

template <typename T>
struct HasIterableMemberFns<T, Void<decltype(rvalue<T>().begin()), decltype(rvalue<T>().end())>> : True {
  using Iterator = decltype(rvalue<T>().begin());
  using Sentinel = decltype(rvalue<T>().end());
};

template <typename T>
struct HasConstIterableMemberFns<T, Void<decltype(rvalue<T>().cbegin()), decltype(rvalue<T>().cend())>> : True {
  using ConstIterator = decltype(rvalue<T>().cbegin());
  using Sentinel = decltype(rvalue<T>().cend());
};

template <typename T>
struct HasReverseIterableMemberFns<T, Void<decltype(rvalue<T>().rbegin()), decltype(rvalue<T>().rend())>> : True {
  using ReverseIterator = decltype(rvalue<T>().rbegin());
  using Sentinel = decltype(rvalue<T>().rend());
};

template <typename T>
struct HasConstReverseIterableMemberFns<T, Void<decltype(rvalue<T>().crbegin()), decltype(rvalue<T>().crend())>> :
    True {
  using ConstReverseIterator = decltype(rvalue<T>().crbegin());
  using Sentinel = decltype(rvalue<T>().crend());
};

template <typename T> struct HasSizeMemberFn<T, Void<decltype(rvalue<T>().size())>> : True {};

template <typename> struct IsIterator : False {};
template <typename> struct IsReverseIterator : False {};
} // namespace impl

template <typename Sentinel, typename Iterator> struct IsSentinelFor :
    IsEqCompatible<Sentinel, Iterator>::Type {};

template <typename Iterator> struct IsInputIterator : And<
    impl::IteratorIsPrefixIncrementable<Iterator, Bind<IsSame, Iterator&, Ph<0>>::template Type>,
    impl::IteratorIsIndirectable<Iterator, Bind<Unless<IsSame>::Type, void, Ph<0>>::Type>
> {};

template <typename Iterator> struct IsOutputIterator : And<
    IsInputIterator<Iterator>,
    impl::IteratorIsIndirectable<Iterator, Unless<Apply<IsConst, RemoveRef>::Type>::Type>
> {};

template <typename Iterator, typename Sentinel = Iterator> struct IsForwardIterator : And<
    IsSentinelFor<Iterator, Sentinel>,
    IsPrefixIncrementable<Iterator>,
    IsIndirectionCompatible<Iterator>
> {};

template <typename Iterator, typename Sentinel = Iterator> struct IsBidirectionalIterator : And<
    IsForwardIterator<Iterator, Sentinel>,
    IsPrefixDecrementable<Iterator>
> {};

template <typename Iterator, typename Sentinel = Iterator> struct IsRandomAccessIterator : And<
    IsBidirectionalIterator<Iterator, Sentinel>,
    IsSubscriptCompatible<Iterator>,
    IsAddCompatible<Iterator, int>,
    IsSubCompatible<Iterator, int>,
    IsSubCompatible<Iterator>
> {};

template <typename> struct IterableTraits {};

enum class IteratorType {UnknownOrSentinel, Input, Output, Forward, Bidirectional, RandomAccess};

template <typename I, typename S = I> struct IteratorTypeOf {
  static constexpr IteratorType value = IsRandomAccessIterator<I, S>::value
      ? IteratorType::RandomAccess
      : IsBidirectionalIterator<I, S>::value
      ? IteratorType::Bidirectional
      : IsForwardIterator<I, S>::value
      ? IteratorType::Forward
      : IsOutputIterator<I>::value
      ? IteratorType::Output
      : IsInputIterator<I>::value
      ? IteratorType::Input
      : IteratorType::UnknownOrSentinel;
};

// ODR before C++17
template <typename I, typename S> IteratorType const IteratorTypeOf<I, S>::value;

template <template <typename...> class, typename T, typename = typename IsConst<T>::Type>
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
