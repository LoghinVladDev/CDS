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
template <typename I, template <typename...> class P, typename = void> struct IteratorIsPrefixIncrementable : False {};

template <typename I, template <typename...> class P> struct IteratorIsPrefixIncrementable<I, P, Void<decltype(++lvalue<I>())>> :
    P<decltype(++lvalue<I>())> {};

template <typename I, template <typename...> class P, typename = void> struct IteratorIsIndirectable : False {};

template <typename I, template <typename...> class P> struct IteratorIsIndirectable<I, P, Void<decltype(*value<I>())>> :
   P<decltype(*value<I>())> {};

template <typename T, typename = void> struct HasIterableMemberFns : False {};
template <typename T, typename = void> struct HasConstIterableMemberFns : False {};
template <typename T, typename = void> struct HasReverseIterableMemberFns : False {};
template <typename T, typename = void> struct HasConstReverseIterableMemberFns : False {};

template <typename T> struct HasIterableMemberFns<T, Void<decltype(value<T>().begin()), decltype(value<T>().end())>> : True {
  using Iterator = decltype(meta::value<T>().begin());
};

template <typename T> struct HasConstIterableMemberFns<T, Void<decltype(value<T>().cbegin()), decltype(value<T>().cend())>> : True {
  using ConstIterator = decltype(meta::value<T>().cbegin());
};

template <typename T> struct HasReverseIterableMemberFns<T, Void<decltype(value<T>().rbegin()), decltype(value<T>().rend())>> : True {
  using ReverseIterator = decltype(meta::value<T>().rbegin());
};

template <typename T> struct HasConstReverseIterableMemberFns<T, Void<decltype(value<T>().crbegin()), decltype(value<T>().crend())>> : True {
  using ConstReverseIterator = decltype(meta::value<T>().crbegin());
};
} // namespace impl

template <typename Sentinel, typename Iterator> struct IsSentinelFor : IsEqCompatible<Sentinel, Iterator>::Type {};

template <typename Iterator> struct IsInputIterator : And<
    IsSentinelFor<Iterator, Iterator>,
    impl::IteratorIsPrefixIncrementable<Iterator, Bind<IsSame, Iterator&, Ph<0>>::template Type>,
    impl::IteratorIsIndirectable<Iterator, Bind<Unless<IsSame>::Type, void, Ph<0>>::template Type>
> {};

template <typename Iterator> struct IsOutputIterator : And<
    IsInputIterator<Iterator>,
    impl::IteratorIsIndirectable<Iterator, Unless<Apply<IsConst, RemoveRef>::Type>::Type>
> {};

template <typename Iterator> struct IsForwardIterator : And<
    IsPrefixIncrementable<Iterator>,
    IsIndirectionCompatible<Iterator>,
    IsSentinelFor<Iterator, Iterator>
>{};

template <typename Iterator> struct IsBidirectionalIterator : And<
    IsForwardIterator<Iterator>,
    IsPrefixDecrementable<Iterator>
>{};

template <typename Iterator> struct IsRandomAccessIterator : And<
    IsBidirectionalIterator<Iterator>,
    IsSubscriptCompatible<Iterator>,
    IsAddCompatible<Iterator, int>,
    IsSubCompatible<Iterator, int>,
    IsSubCompatible<Iterator>
>{};

template <typename Range> struct IterableTraits {};
} // namespace meta
} // namespace cds

#endif // CDS_META_ITERATOR_TRAITS_HPP
