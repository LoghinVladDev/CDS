// NOLINT(llvm-header-guard)
// Created by loghin on 16/02/23.
//

#ifndef __CDS_STATIC_ARRAY_BASE_IMPL_HPP__ // NOLINT(llvm-header-guard, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#define __CDS_STATIC_ARRAY_BASE_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename                                                            __Element,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    Size                                                                __size,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__Element const&, __Element const&>  __equals,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __MemoryContainer   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> constexpr auto __StaticArrayBase <__Element, __size, __equals, __MemoryContainer>::__sab_size() const noexcept -> Size {
  return __size;
}


template <
    typename                                                            __Element,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    Size                                                                __size,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__Element const&, __Element const&>  __equals,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __MemoryContainer   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_cpplang_NonConstConstexprMemberFunction auto __StaticArrayBase <__Element, __size, __equals, __MemoryContainer>::__sab_get (
    Index index
) noexcept -> __Element* {
  return &this->_sab_memory._samc_data[index];
}


template <
    typename                                                            __Element,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    Size                                                                __size,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__Element const&, __Element const&>  __equals,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __MemoryContainer   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> constexpr auto __StaticArrayBase <__Element, __size, __equals, __MemoryContainer>::__sab_get (
   Index index
) const noexcept -> __Element const* {
  return &this->_sab_memory._samc_data[index];
}


template <
    typename                                                            __Element,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    Size                                                                __size,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__Element const&, __Element const&>  __equals,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __MemoryContainer   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_cpplang_NonConstConstexprMemberFunction auto __StaticArrayBase <__Element, __size, __equals, __MemoryContainer>::__sab_begin () noexcept -> __sab_Iterator {
  return __sab_Iterator (&this->_sab_memory._samc_data[0u]);
}


template <
    typename                                                            __Element,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    Size                                                                __size,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__Element const&, __Element const&>  __equals,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __MemoryContainer   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_cpplang_NonConstConstexprMemberFunction auto __StaticArrayBase <__Element, __size, __equals, __MemoryContainer>::__sab_end () noexcept -> __sab_Iterator {
  return __sab_Iterator (&this->_sab_memory._samc_data[__size]);
}


template <
    typename                                                            __Element,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    Size                                                                __size,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__Element const&, __Element const&>  __equals,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __MemoryContainer   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_cpplang_NonConstConstexprMemberFunction auto __StaticArrayBase <__Element, __size, __equals, __MemoryContainer>::__sab_rbegin () noexcept -> __sab_ReverseIterator {
  return __sab_ReverseIterator (&this->_sab_memory._samc_data[__size - 1u]);
}


template <
    typename                                                            __Element,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    Size                                                                __size,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__Element const&, __Element const&>  __equals,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __MemoryContainer   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_cpplang_NonConstConstexprMemberFunction auto __StaticArrayBase <__Element, __size, __equals, __MemoryContainer>::__sab_rend () noexcept -> __sab_ReverseIterator {
  return __sab_ReverseIterator (&this->_sab_memory._samc_data[-1]);
}


template <
    typename                                                            __Element,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    Size                                                                __size,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__Element const&, __Element const&>  __equals,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __MemoryContainer   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> constexpr auto __StaticArrayBase <__Element, __size, __equals, __MemoryContainer>::__sab_cbegin () const noexcept -> __sab_ConstIterator {
  return __sab_ConstIterator (&this->_sab_memory._samc_data[0u]);
}


template <
    typename                                                            __Element,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    Size                                                                __size,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__Element const&, __Element const&>  __equals,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __MemoryContainer   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> constexpr auto __StaticArrayBase <__Element, __size, __equals, __MemoryContainer>::__sab_cend () const noexcept -> __sab_ConstIterator {
  return __sab_ConstIterator (&this->_sab_memory._samc_data[__size]);
}


template <
    typename                                                            __Element,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    Size                                                                __size,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__Element const&, __Element const&>  __equals,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __MemoryContainer   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> constexpr auto __StaticArrayBase <__Element, __size, __equals, __MemoryContainer>::__sab_crbegin () const noexcept -> __sab_ConstReverseIterator {
  return __sab_ConstReverseIterator (&this->_sab_memory._samc_data[__size - 1u]);
}


template <
    typename                                                            __Element,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    Size                                                                __size,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__Element const&, __Element const&>  __equals,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __MemoryContainer   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> constexpr auto __StaticArrayBase <__Element, __size, __equals, __MemoryContainer>::__sab_crend () const noexcept -> __sab_ConstReverseIterator {
  return __sab_ConstReverseIterator (&this->_sab_memory._samc_data[-1u]);
}


template <
    typename                                                            __Element,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    Size                                                                __size,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__Element const&, __Element const&>  __equals,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __MemoryContainer   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_cpplang_NonConstConstexprMemberFunction auto __StaticArrayBase <__Element, __size, __equals, __MemoryContainer>::__sab_data () noexcept -> __Element* {
  return &this->_sab_memory._samc_data[0u];
}


template <
    typename                                                            __Element,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    Size                                                                __size,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__Element const&, __Element const&>  __equals,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __MemoryContainer   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> constexpr auto __StaticArrayBase <__Element, __size, __equals, __MemoryContainer>::__sab_data () const noexcept -> __Element const* {
  return &this->_sab_memory._samc_data[0u];
}


template <
    typename                                                            __Element,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    Size                                                                __size,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__Element const&, __Element const&>  __equals,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __MemoryContainer   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_cpplang_ConstexprConditioned auto __StaticArrayBase <__Element, __size, __equals, __MemoryContainer>::__sab_equals (
    __StaticArrayBase const& array
) const noexcept -> bool {
  if (this == &array) {
    return true;
  }

  for (Size index = 0u; index < __size; ++index) {
    if (!__equals (this->_sab_memory._samc_data[index], array._sab_memory._samc_data[index]) ) {
      return false;
    }
  }

  return true;
}


template <
    typename                                                            __Element,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    Size                                                                __size,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__Element const&, __Element const&>  __equals,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __MemoryContainer   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> template <typename __Comparator> __CDS_OptimalInline auto __StaticArrayBase <__Element, __size, __equals, __MemoryContainer>::__sab_sort (  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __Comparator const& comparator
) noexcept -> void {
  cds::introSort (
      &this->_sab_memory._samc_data[0u],
      &this->_sab_memory._samc_data[__size],
      comparator
  );
}
} // namespace __impl
} // namespace __hidden
} // namespace cds

#endif // __CDS_STATIC_ARRAY_BASE_IMPL_HPP__
