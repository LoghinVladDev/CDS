// NOLINT(llvm-header-guard) 
// Created by loghin on 16/02/23.
//

#ifndef __CDS_STATIC_ARRAY_BASE_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#define __CDS_STATIC_ARRAY_BASE_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr static auto __staticArrayMemoryContainerStackLimit (Size limit) noexcept -> bool {  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  return limit < 1024U; // NOLINT(*-magic-numbers)
}

template <
    typename  __Element,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    Size      __size,       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    bool                = __staticArrayMemoryContainerStackLimit(sizeof (__Element) * __size)
> struct __StaticArrayMemoryContainer {}; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)


template <typename __Element, Size __size>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __StaticArrayMemoryContainer <__Element, __size, true> {
  __Element _samc_data [__size]; // NOLINT(*-c-arrays)
};


template <typename __Element, Size __size>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __StaticArrayMemoryContainer <__Element, __size, false> {
  using __Alloc = __allocation::__PrimitiveAlloc<__Element>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __Element * _samc_data;     // NOLINT(misc-non-private-member-variables-in-classes)

  __CDS_cpplang_ConstexprDynamicAllocation __StaticArrayMemoryContainer () {
    _samc_data = __Alloc::__alloc(__size);
    for (Size index = 0u; index < __size; ++ index) {
      (void) new (&_samc_data [index])__Element();
    }
  }

  __CDS_cpplang_ConstexprDynamicAllocation ~__StaticArrayMemoryContainer () { // NOLINT(*-default)
    if (_samc_data == nullptr) {
      return;
    }

    for (Size index = 0u; index < __size; ++ index) {
      _samc_data [index].~__Element ();
    }
    __Alloc::__free(_samc_data);
  }

  __CDS_cpplang_ConstexprDynamicAllocation __StaticArrayMemoryContainer (
      __StaticArrayMemoryContainer const& array
  ) noexcept {
    _samc_data = __Alloc::__alloc(__size);
    for (Size index = 0u; index < __size; ++index) {
      (void) new (&_samc_data [index])__Element(array._samc_data[index]);
    }
  }

  constexpr __StaticArrayMemoryContainer (
      __StaticArrayMemoryContainer&& array
  ) noexcept {
    _samc_data = cds::exchange(array._samc_data, nullptr);
  }

  __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
      __StaticArrayMemoryContainer const& array
  ) noexcept -> __StaticArrayMemoryContainer& {
    if (this == &array) {
      return *this;
    }

    for (Size index = 0u; index < __size; ++ index) {
      _samc_data [index] = array._samc_data [index];
    }

    return *this;
  }

  __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
      __StaticArrayMemoryContainer&& array
  ) noexcept -> __StaticArrayMemoryContainer& {
    if (this == &array) {
      return *this;
    }

    _samc_data = cds::exchange(array._samc_data, nullptr);
    return *this;
  }
};


template <
    typename                                                           __Element,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    Size                                                               __size,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__Element const&, __Element const&> __equals,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                           __MemoryContainer   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __StaticArrayBase {                                                               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-member-init)
public:
  using __sab_Iterator                = ForwardAddressIterator <__Element>;     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using __sab_ConstIterator           = ForwardAddressIterator <__Element const>;   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using __sab_ReverseIterator         = BackwardAddressIterator <__Element>;        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using __sab_ConstReverseIterator    = BackwardAddressIterator <__Element const>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  template <typename __ServerType> class __Dispatcher;                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  using ElementType                   = __Element;

  constexpr ~__StaticArrayBase () noexcept = default;

protected:
  constexpr __StaticArrayBase() noexcept = default;
  __StaticArrayBase(__StaticArrayBase const&) noexcept = default;
  __StaticArrayBase(__StaticArrayBase&&) noexcept = default;

  auto operator = (__StaticArrayBase const&) noexcept -> __StaticArrayBase& = default;
  auto operator = (__StaticArrayBase&&) noexcept -> __StaticArrayBase& = default;

  __CDS_NoDiscard constexpr auto __sab_size() const noexcept -> Size;    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __sab_get(  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      Index index
  ) noexcept -> __Element*;

  __CDS_NoDiscard constexpr auto __sab_get (  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      Index index
  ) const noexcept -> __Element const*;

  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __sab_begin () noexcept -> __sab_Iterator;   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __sab_end () noexcept -> __sab_Iterator; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard constexpr auto __sab_cbegin () const noexcept -> __sab_ConstIterator;   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard constexpr auto __sab_cend () const noexcept -> __sab_ConstIterator;     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __sab_rbegin () noexcept -> __sab_ReverseIterator;   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __sab_rend () noexcept -> __sab_ReverseIterator; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard constexpr auto __sab_crbegin () const noexcept -> __sab_ConstReverseIterator;   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard constexpr auto __sab_crend () const noexcept -> __sab_ConstReverseIterator; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __sab_data () noexcept -> __Element*;   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard constexpr auto __sab_data () const noexcept -> __Element const*;   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto __sab_equals (  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __StaticArrayBase const& array
  ) const noexcept -> bool;

  template <
      typename __Comparator = decltype(&cds::predicates::lessThan<__Element>)  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  > auto __sab_sort (                                                                             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __Comparator const& comparator = &cds::predicates::lessThan <__Element>
  ) noexcept -> void;

private:
  __CDS_NoUniqueAddress __MemoryContainer _sab_memory;    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};


template <
    typename                                                           __Element,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    Size                                                               __size,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__Element const&, __Element const&> __equals,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                           __MemoryContainer   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> template <typename __ServerType> class __StaticArrayBase <                              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __Element, __size, __equals, __MemoryContainer
>::__Dispatcher :
    public __IterableServerDispatcher <
        __ServerType, __StaticArrayBase, __Element, ForwardAddressIterator <__Element const>,
        &__StaticArrayBase::__sab_cbegin, &__StaticArrayBase::__sab_cend
    > {
protected:
  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction static auto __beginLocal (
      __ServerType* pServer
  ) noexcept -> __sab_Iterator;

  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction static auto __endLocal (
      __ServerType* pServer
  ) noexcept -> __sab_Iterator;

  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction static auto __rbeginLocal (
      __ServerType* pServer
  ) noexcept -> __sab_ReverseIterator;

  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction static auto __rendLocal (
      __ServerType* pServer
  ) noexcept -> __sab_ReverseIterator;

  __CDS_NoDiscard constexpr static auto __crbeginLocal (
      __ServerType const* pServer
  ) noexcept -> __sab_ConstReverseIterator;

  __CDS_NoDiscard constexpr static auto __crendLocal (
      __ServerType const* pServer
  ) noexcept -> __sab_ConstReverseIterator;
};

} // namespace __impl
} // namespace __hidden
} // namespace cds

#endif // __CDS_STATIC_ARRAY_BASE_HPP__
