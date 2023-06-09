//
// Created by loghin on 6/27/22.
//

#ifndef __CDS_SHARED_FIND_BY_IMMUTABLE_COMPOSITE_CLIENT_IMPL_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_SHARED_FIND_BY_IMMUTABLE_COMPOSITE_CLIENT_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

#if defined _MSC_VER
#include "../../../../../functional/FunctionalInterface.hpp"
#endif

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#if defined _MSC_VER
// Manual SFINAE for little non-compliant MSVC :)
template <
    typename                      __Iterator,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    template <typename...> class  __Collection, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                      __Predicate,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    bool = cds::meta::IsMemberFunctionPointer <__Predicate>::value
> struct __MSVC_FindThatWrapper { // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  constexpr static cds::functional::MapperFunction <
      __Collection <__Iterator>&, __Iterator const&, __Iterator const&,
      Size, __Collection <__Iterator>&, __Predicate const&
  > const __findThat = nullptr; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};

template <
    typename                      __Iterator,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    template <typename...> class  __Collection, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                      __Predicate   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> struct __MSVC_FindThatWrapper <__Iterator, __Collection, __Predicate, false> {
  constexpr static cds::functional::MapperFunction <
      __Collection <__Iterator>&, __Iterator const&, __Iterator const&,
      Size, __Collection <__Iterator>&, __Predicate const&
  > const __findThat = &__findThat <__Iterator, __Collection, __Predicate>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};


template <
    typename                      __Iterator,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    template <typename...> class  __Collection, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                      __Predicate   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> struct __MSVC_FindThatWrapper <__Iterator, __Collection, __Predicate, true> {
  constexpr static cds::functional::MapperFunction <
      __Collection <__Iterator>&, __Iterator const&, __Iterator const&,
      Size, __Collection <__Iterator>&, __Predicate const&
  > const __findThat = &__findThatMember <__Iterator, __Collection, __Predicate>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};


template <
    typename __Iterator,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Predicate, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    bool = cds::meta::IsMemberFunctionPointer <__Predicate>::value
> struct __MSVC_FindFirstThatWrapper {  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  constexpr static cds::functional::MapperFunction <
      __Iterator, __Iterator const&, __Iterator const&, __Predicate const&
  > const __findFirstThat = nullptr;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};


template <typename __Iterator, typename __Predicate>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __MSVC_FindFirstThatWrapper <__Iterator, __Predicate, false> {
  constexpr static cds::functional::MapperFunction <
      __Iterator, __Iterator const&, __Iterator const&, __Predicate const&
  > const __findFirstThat = &__findFirstThat <__Iterator, __Predicate>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};


template <typename __Iterator, typename __Predicate>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __MSVC_FindFirstThatWrapper <__Iterator, __Predicate, true> {
  constexpr static cds::functional::MapperFunction <
      __Iterator, __Iterator const&, __Iterator const&, __Predicate const&
  > const __findFirstThat = &__findFirstThatMember <__Iterator, __Predicate>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};


template <
    typename __Iterator,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Predicate, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    bool = cds::meta::IsMemberFunctionPointer <__Predicate>::value
> struct __MSVC_FindLastThatWrapper { // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  constexpr static cds::functional::MapperFunction <
      __Iterator, __Iterator const&, __Iterator const&, __Predicate const&
  > const __findLastThat = nullptr; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};


template <typename __Iterator, typename __Predicate>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __MSVC_FindLastThatWrapper <__Iterator, __Predicate, false> {
  constexpr static cds::functional::MapperFunction <
      __Iterator, __Iterator const&, __Iterator const&, __Predicate const&
  > const __findLastThat = &__findLastThat <__Iterator, __Predicate>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};


template <typename __Iterator, typename __Predicate>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __MSVC_FindLastThatWrapper <__Iterator, __Predicate, true> {
  constexpr static cds::functional::MapperFunction <
      __Iterator, __Iterator const&, __Iterator const&, __Predicate const&
  > const __findLastThat = &__findLastThatMember <__Iterator, __Predicate>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};


template <
    typename                      __Iterator,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    template <typename...> class  __Collection, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                      __Predicate,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    bool = cds::meta::IsMemberFunctionPointer <__Predicate>::value
> struct __MSVC_FindAllThatWrapper {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  constexpr static cds::functional::MapperFunction <
      __Collection <__Iterator>&, __Iterator const&, __Iterator const&,
      __Collection <__Iterator>&, __Predicate const&
  > const __findAllThat = nullptr;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};


template <
    typename                      __Iterator,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    template <typename...> class  __Collection, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                      __Predicate   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> struct __MSVC_FindAllThatWrapper <__Iterator, __Collection, __Predicate, false> {
  constexpr static cds::functional::MapperFunction <
      __Collection <__Iterator>&, __Iterator const&, __Iterator const&,
      __Collection <__Iterator>&, __Predicate const&
  > const __findAllThat = &__findAllThat <__Iterator, __Collection, __Predicate>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};


template <
    typename                      __Iterator,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    template <typename...> class  __Collection, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                      __Predicate   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> struct __MSVC_FindAllThatWrapper <__Iterator, __Collection, __Predicate, true> {
  constexpr static cds::functional::MapperFunction <
      __Collection <__Iterator>&, __Iterator const&, __Iterator const&,
      __Collection <__Iterator>&, __Predicate const&
  > const __findAllThat = &__findAllThatMember <__Iterator, __Collection, __Predicate>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};
#endif

template <typename __Iterable, typename __Element, typename __Iterator, bool __exceptCond>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <template <typename...> class __Collection, typename __Predicate>                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __FindByImmutableCompositeClient <__Iterable, __Element, __Iterator, __exceptCond>::findThat (
    Size                          count,
    __Collection <ConstIterator>& storeIn,
    __Predicate const&            predicate
) const noexcept(false) -> __Collection <ConstIterator>& {
  auto const* pIterable = static_cast <__Iterable const*> (this);
  // Call base, global implementation. Abstracts the 'is object const' requirement.
#ifdef _MSC_VER
  // Also use the MSVC dedicated manual-SFINAE wrapper due to the year being (almost)
  // 2022 and they still can't deduce whether a function is enabled or not.
  return __MSVC_FindThatWrapper <__Iterator, __Collection, __Predicate>::__findThat (
      pIterable->cbegin(), pIterable->cend(), count, storeIn, predicate
  );
#else
  return __findThat (pIterable->cbegin(), pIterable->cend(), count, storeIn, predicate);
#endif
}


template <typename __Iterable, typename __Element, typename __Iterator, bool __exceptCond>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <template <typename...> class __Collection, typename __Predicate>                  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __FindByImmutableCompositeClient <__Iterable, __Element, __Iterator, __exceptCond>::findThat (
    Size                count,
    __Predicate const&  predicate
) const noexcept(false) -> __Collection <ConstIterator> {
  __Collection <ConstIterator> foundIterators;
  auto const* pIterable = static_cast <__Iterable const*> (this);
  // Call base, global implementation. Abstracts the 'is object const' requirement.
#ifdef _MSC_VER
  // Also use the MSVC dedicated manual-SFINAE wrapper due to the year being (almost)
  // 2022 and they still can't deduce whether a function is enabled or not.
  return __MSVC_FindThatWrapper <__Iterator, __Collection, __Predicate>::__findThat (
      pIterable->cbegin(), pIterable->cend(), count, foundIterators, predicate
  );
#else
  return __findThat (pIterable->cbegin(), pIterable->cend(), count, foundIterators, predicate);
#endif
}


template <typename __Iterable, typename __Element, typename __Iterator, bool __exceptCond>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Predicate>                                                             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __FindByImmutableCompositeClient <__Iterable, __Element, __Iterator, __exceptCond>::findFirstThat (
    __Predicate const& predicate
) const noexcept (noexcept (__PredicateExceptSpecTraits <__Element const, __Predicate>::__noexceptSpec) && itNoexcept) -> ConstIterator {
  // Call base, global implementation. Abstracts the 'is object const' requirement
  auto const* pIterable = static_cast <__Iterable const*> (this);
#ifdef _MSC_VER
  // Also use the MSVC dedicated manual-SFINAE wrapper due to the year being
  // 2022 and they still can't deduce whether a function is enabled or not.
  return __MSVC_FindFirstThatWrapper <__Iterator, __Predicate>::__findFirstThat (
      pIterable->cbegin(), pIterable->cend(), predicate
  );
#else
  return __findFirstThat ( pIterable->cbegin(), pIterable->cend(), predicate);
#endif
}


template <typename __Iterable, typename __Element, typename __Iterator, bool __exceptCond>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Predicate>                                                             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __FindByImmutableCompositeClient <__Iterable, __Element, __Iterator, __exceptCond>::findLastThat (
    __Predicate const& predicate
) const noexcept (noexcept (__PredicateExceptSpecTraits <__Element const, __Predicate>::__noexceptSpec) && itNoexcept) -> ConstIterator {
  auto const* pIterable = static_cast <__Iterable const*> (this);
  // Call base, global implementation. Abstracts the 'is object const' requirement
#ifdef _MSC_VER
  // Also use the MSVC dedicated manual-SFINAE wrapper due to the year being
  // 2022 and they still can't deduce whether a function is enabled or not.
  return __MSVC_FindLastThatWrapper <__Iterator, __Predicate>::__findLastThat (
      pIterable->cbegin(), pIterable->cend(), predicate
  );
#else
  return __findLastThat (pIterable->cbegin(), pIterable->cend(), predicate);
#endif
}


template <typename __Iterable, typename __Element, typename __Iterator, bool __exceptCond>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <template <typename...> class __Collection, typename __Predicate>                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __FindByImmutableCompositeClient <__Iterable, __Element, __Iterator, __exceptCond>::findAllThat (
    __Collection <ConstIterator>& storeIn,
    __Predicate const&            predicate
) const noexcept(false) -> __Collection <ConstIterator>& {
  auto const* pIterable = static_cast <__Iterable const*> (this);
  // Call base, global implementation. Abstracts the 'is object const' requirement.
#ifdef _MSC_VER
  // Also use the MSVC dedicated manual-SFINAE wrapper due to the year being
  // 2022 and they still can't deduce whether a function is enabled or not.
  return __MSVC_FindAllThatWrapper <__Iterator, __Collection, __Predicate>::__findAllThat (
      pIterable->cbegin(), pIterable->cend(), storeIn, predicate
  );
#else
  return __findAllThat (pIterable->cbegin(), pIterable->cend(), storeIn, predicate);
#endif
}


template <typename __Iterable, typename __Element, typename __Iterator, bool __exceptCond>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <template <typename...> class __Collection, typename __Predicate>                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __FindByImmutableCompositeClient <__Iterable, __Element, __Iterator, __exceptCond>::findAllThat (
    __Predicate const& predicate
) const noexcept(false) -> __Collection <ConstIterator> {
  __Collection <ConstIterator> foundIterators;
  auto const* pIterable = static_cast <__Iterable const*> (this);
  // Call base, global implementation. Abstracts the 'is object const' requirement.
#ifdef _MSC_VER
  // Also use the MSVC dedicated manual-SFINAE wrapper due to the year being
  // 2022 and they still can't deduce whether a function is enabled or not.
  return __MSVC_FindAllThatWrapper <__Iterator, __Collection, __Predicate>::__findAllThat (
      pIterable->cbegin(), pIterable->cend(), foundIterators, predicate
  );
#else
  // Call base, global implementation. Abstracts the 'is object const' requirement
  return __findAllThat (pIterable->cbegin(), pIterable->cend(), foundIterators, predicate);
#endif
}
} // namespace __impl
} // namespace __hidden
} // namespace cds

#endif // __CDS_SHARED_FIND_BY_IMMUTABLE_COMPOSITE_CLIENT_IMPL_HPP__
