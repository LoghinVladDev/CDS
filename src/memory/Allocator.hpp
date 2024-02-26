//
// Created by loghin on 12/8/23.
//

#ifndef CDS_MEMORY_ALLOCATOR_HPP
#define CDS_MEMORY_ALLOCATOR_HPP
#pragma once

#include <cds/meta/Base>

#include <memory>

namespace cds {
template <typename... Allocs> class AllocatorSet;

namespace meta {

template <typename, typename = void> struct IsAllocator : False {};
template <typename T> struct IsAllocator<T, Void<decltype(value<T>().allocate(0))>> : True {};
template <typename, typename = void> struct IsAllocatorSet : False {};
template <typename T> struct IsAllocatorSet<T, Void<typename T::IsAllocatorSet>> : True {};

template <typename T> struct IsAllocatorOrAllocatorSet : Or<IsAllocator<T>, IsAllocatorSet<T>> {};

namespace allocatorForImpl {
class InvalidAllocator {};
template <typename T, typename A> struct AllocatorFor {};
template <typename T, typename F, typename... R> struct AllocatorFor<T, impl::Pack<F, R...>> {
  using Type = Conditional<IsSame<T, typename F::Type>, F, typename AllocatorFor<T, impl::Pack<R...>>::Type>;
};
template <typename T> struct AllocatorFor<T, impl::Pack<>> {
  using Type = InvalidAllocator;
};
} // namespace allocatorForImpl

template <typename T, typename... A> using AllocatorFor =
    typename allocatorForImpl::AllocatorFor<T, impl::Pack<A...>>::Type;
} // namespace meta

template <typename T> class Allocator : public std::allocator<T> {
public:
  using Type = T;
};

template <typename... Allocs> class AllocatorSet : public Allocs... {
public:
  using IsAllocatorSet = meta::True;

  template <typename T> CDS_ATTR(2(nodiscard, constexpr(14))) auto get() noexcept -> meta::AllocatorFor<T, Allocs...>& {
    constexpr auto requestedAllocatorExists = meta::Not<meta::IsSame<
        meta::AllocatorFor<T, Allocs...>,
        meta::allocatorForImpl::InvalidAllocator
    >>::value;
    static_assert(requestedAllocatorExists, "Allocator for requested type does not exist in AllocatorSet");
    return *static_cast<meta::AllocatorFor<T, Allocs...>*>(this);
  }
};
} // namespace cds

#endif // CDS_MEMORY_ALLOCATOR_HPP
