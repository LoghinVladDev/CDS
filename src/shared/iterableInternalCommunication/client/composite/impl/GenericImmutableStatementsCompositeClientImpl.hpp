//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_GENERIC_IMMUTABLE_STATEMENTS_COMPOSITE_CLIENT_IMPL_HPP__ // NOLINT(llvm-header-guard) 
#define __CDS_SHARED_GENERIC_IMMUTABLE_STATEMENTS_COMPOSITE_CLIENT_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

#if defined _MSC_VER
#include "../../../../../functional/FunctionalInterface.hpp"
#endif

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#ifdef _MSC_VER
// Manual SFINAE for little non-compliant MSVC :)
template <typename __Iterator, typename __Consumer, bool = cds::meta::IsMemberFunctionPointer <__Consumer>::value>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __MSVC_ForEachWrapper {  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  constexpr static cds::functional::ConsumerFunction <
      __Iterator const&, __Iterator const&, __Consumer const&
  > __forEach = nullptr;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};


template <typename __Iterator, typename __Consumer> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __MSVC_ForEachWrapper <__Iterator, __Consumer, false> {
  constexpr static cds::functional::ConsumerFunction <
      __Iterator const&, __Iterator const&, __Consumer const&
  > __forEach = &__forEach <__Iterator, __Consumer>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};


template <typename __Iterator, typename __Consumer>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __MSVC_ForEachWrapper <__Iterator, __Consumer, true> {
  constexpr static cds::functional::ConsumerFunction <
      __Iterator const&, __Iterator const&, __Consumer const&
  > __forEach = &__forEachMember <__Iterator, __Consumer>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};


template <typename __Iterator, typename __Predicate, bool = cds::meta::IsMemberFunctionPointer <__Predicate>::value>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
struct __MSVC_SomeWrapper { // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  constexpr static cds::functional::PredicateFunction <
      __Iterator const&, __Iterator const&, Size, __Predicate const&
  > __some = nullptr; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};


template <typename __Iterator, typename __Predicate>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __MSVC_SomeWrapper <__Iterator, __Predicate, false> {
  constexpr static cds::functional::PredicateFunction <
      __Iterator const&, __Iterator const&, Size, __Predicate const&
  > __some = &__some <__Iterator, __Predicate>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};


template <typename __Iterator, typename __Predicate>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __MSVC_SomeWrapper <__Iterator, __Predicate, true> {
  constexpr static cds::functional::PredicateFunction <
      __Iterator const&, __Iterator const&, Size, __Predicate const&
  > __some = &__someMember <__Iterator, __Predicate>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};


template <typename __Iterator, typename __Predicate, bool = cds::meta::IsMemberFunctionPointer <__Predicate>::value>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __MSVC_AtLeastWrapper {  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  constexpr static cds::functional::PredicateFunction <
      __Iterator const&, __Iterator const&, Size, __Predicate const&
  > __atLeast = nullptr;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};


template <typename __Iterator, typename __Predicate>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __MSVC_AtLeastWrapper <__Iterator, __Predicate, false> {
  constexpr static cds::functional::PredicateFunction <
      __Iterator const&, __Iterator const&, Size, __Predicate const&
  > __atLeast = &__atLeast <__Iterator, __Predicate>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};


template <typename __Iterator, typename __Predicate>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __MSVC_AtLeastWrapper <__Iterator, __Predicate, true> {
  constexpr static cds::functional::PredicateFunction <
      __Iterator const&, __Iterator const&, Size, __Predicate const&
  > __atLeast = &__atLeastMember <__Iterator, __Predicate>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};


template <typename __Iterator, typename __Predicate, bool = cds::meta::IsMemberFunctionPointer <__Predicate>::value>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __MSVC_AtMostWrapper { // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  constexpr static cds::functional::PredicateFunction <
      __Iterator const&, __Iterator const&, Size, __Predicate const&
  > __atMost = nullptr; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};


template <typename __Iterator, typename __Predicate>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __MSVC_AtMostWrapper <__Iterator, __Predicate, false> {
  constexpr static cds::functional::PredicateFunction <
      __Iterator const&, __Iterator const&, Size, __Predicate const&
  > __atMost = &__atMost <__Iterator, __Predicate>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};


template <typename __Iterator, typename __Predicate>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __MSVC_AtMostWrapper <__Iterator, __Predicate, true> {
  constexpr static cds::functional::PredicateFunction <
      __Iterator const&, __Iterator const&, Size, __Predicate const&
  > __atMost = &__atMostMember <__Iterator, __Predicate>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};


template <typename __Iterator, typename __Predicate, bool = cds::meta::IsMemberFunctionPointer <__Predicate>::value>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __MSVC_MoreThanWrapper { // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  constexpr static cds::functional::PredicateFunction <
      __Iterator const&, __Iterator const&, Size, __Predicate const&
  > __moreThan = nullptr; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};


template <typename __Iterator, typename __Predicate>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __MSVC_MoreThanWrapper <__Iterator, __Predicate, false> {
  constexpr static cds::functional::PredicateFunction <
      __Iterator const&, __Iterator const&, Size, __Predicate const&
  > __moreThan = &__moreThan <__Iterator, __Predicate>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};


template <typename __Iterator, typename __Predicate>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __MSVC_MoreThanWrapper <__Iterator, __Predicate, true> {
  constexpr static cds::functional::PredicateFunction <
      __Iterator const&, __Iterator const&, Size, __Predicate const&
  > __moreThan = &__moreThanMember <__Iterator, __Predicate>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};


template <typename __Iterator, typename __Predicate, bool = cds::meta::IsMemberFunctionPointer <__Predicate>::value>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __MSVC_FewerThanWrapper {  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  constexpr static cds::functional::PredicateFunction <
      __Iterator const&, __Iterator const&, Size, __Predicate const&
  > __fewerThan = nullptr;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};


template <typename __Iterator, typename __Predicate>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __MSVC_FewerThanWrapper <__Iterator, __Predicate, false> {
  constexpr static cds::functional::PredicateFunction <
      __Iterator const&, __Iterator const&, Size, __Predicate const&
  > __fewerThan = &__fewerThan <__Iterator, __Predicate>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};


template <typename __Iterator, typename __Predicate>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __MSVC_FewerThanWrapper <__Iterator, __Predicate, true> {
  constexpr static cds::functional::PredicateFunction <
      __Iterator const&, __Iterator const&, Size, __Predicate const&
  > __fewerThan = &__fewerThanMember <__Iterator, __Predicate>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};


template <typename __Iterator, typename __Predicate, bool = cds::meta::IsMemberFunctionPointer <__Predicate>::value>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __MSVC_CountWrapper {  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  constexpr static cds::functional::MapperFunction <
      Size, __Iterator const&, __Iterator const&, __Predicate const&
  > __count = nullptr;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};


template <typename __Iterator, typename __Predicate>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __MSVC_CountWrapper <__Iterator, __Predicate, false> {
  constexpr static cds::functional::MapperFunction <
      Size, __Iterator const&, __Iterator const&, __Predicate const&
  > __count = &__count <__Iterator, __Predicate>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};


template <typename __Iterator, typename __Predicate>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __MSVC_CountWrapper <__Iterator, __Predicate, true> {
  constexpr static cds::functional::MapperFunction <
      __Iterator const&, __Iterator const&, __Predicate const&
  > __count = &__countMember <__Iterator, __Predicate>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};


template <typename __Iterator, typename __Predicate, bool = cds::meta::IsMemberFunctionPointer <__Predicate>::value>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __MSVC_AnyWrapper {  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  constexpr static cds::functional::PredicateFunction <
      __Iterator const&, __Iterator const&, __Predicate const&
  > __any = nullptr;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};


template <typename __Iterator, typename __Predicate>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __MSVC_AnyWrapper <__Iterator, __Predicate, false> {
  constexpr static cds::functional::PredicateFunction <
      __Iterator const&, __Iterator const&, __Predicate const&
  > __any = &__any <__Iterator, __Predicate>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};


template <typename __Iterator, typename __Predicate>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __MSVC_AnyWrapper <__Iterator, __Predicate, true> {
  constexpr static cds::functional::PredicateFunction <
      __Iterator const&, __Iterator const&, __Predicate const&
  > __any = &__anyMember <__Iterator, __Predicate>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};


template <typename __Iterator, typename __Predicate, bool = cds::meta::IsMemberFunctionPointer <__Predicate>::value>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __MSVC_AllWrapper {  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  constexpr static cds::functional::PredicateFunction <
      __Iterator const&, __Iterator const&, __Predicate const&
  > __all = nullptr;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};


template <typename __Iterator, typename __Predicate>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __MSVC_AllWrapper <__Iterator, __Predicate, false> {
  constexpr static cds::functional::PredicateFunction <
      __Iterator const&, __Iterator const&, __Predicate const&
  > __all = &__all <__Iterator, __Predicate>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};


template <typename __Iterator, typename __Predicate>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __MSVC_AllWrapper <__Iterator, __Predicate, true> {
  constexpr static cds::functional::PredicateFunction <
      __Iterator const&, __Iterator const&, __Predicate const&
  > __all = &__allMember <__Iterator, __Predicate>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};


template <typename __Iterator, typename __Predicate, bool = cds::meta::IsMemberFunctionPointer <__Predicate>::value>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __MSVC_NoneWrapper { // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  constexpr static cds::functional::PredicateFunction <
      __Iterator const&, __Iterator const&, __Predicate const&
  > __none = nullptr; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};


template <typename __Iterator, typename __Predicate>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __MSVC_NoneWrapper <__Iterator, __Predicate, false> {
  constexpr static cds::functional::PredicateFunction <
      __Iterator const&, __Iterator const&, __Predicate const&
  > __none = &__none <__Iterator, __Predicate>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};


template <typename __Iterator, typename __Predicate>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __MSVC_NoneWrapper <__Iterator, __Predicate, true> {
  constexpr static cds::functional::PredicateFunction <
      __Iterator const&, __Iterator const&, __Predicate const&
  > __none = &__noneMember <__Iterator, __Predicate>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};
#endif

template <typename __Iterable, typename __Element, bool __exceptCond> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __Consumer> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __GenericImmutableStatementsCompositeClient <__Iterable, __Element, __exceptCond>::forEach (
    __Consumer const& consumer
) const noexcept (__ConsumerExceptSpecTraits <__Element const, __Consumer>::__noexceptSpec && itNoexcept) -> void {
  // Call base, global implementation. Abstracts the 'is object const' requirement
  auto const* pIterable = static_cast <__Iterable const*> (this);
#ifdef _MSC_VER
  using IteratorType = decltype (cds::meta::referenceOf <__Iterable const>().cbegin());
  return __MSVC_ForEachWrapper <IteratorType, __Consumer>::__forEach (
      pIterable->cbegin(), pIterable->cend(), consumer
  );
#else
  return __forEach (pIterable->cbegin(), pIterable->cend(), consumer);
#endif
}


template <typename __Iterable, typename __Element, bool __exceptCond> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __Predicate> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __GenericImmutableStatementsCompositeClient <__Iterable, __Element, __exceptCond>::some (
    Size                count,
    __Predicate const&  predicate
) const noexcept (__PredicateExceptSpecTraits <__Element const, __Predicate>::__noexceptSpec && itNoexcept) -> bool {
  // Call base, global implementation. Abstracts the 'is object const' requirement
  auto const* pIterable = static_cast <__Iterable const*> (this);
#ifdef _MSC_VER
  using IteratorType = decltype (cds::meta::referenceOf <__Iterable const>().cbegin());
  return __MSVC_SomeWrapper < IteratorType, __Predicate >::__some (
      pIterable->cbegin(), pIterable->cend(), count, predicate
  );
#else
  return __some (pIterable->cbegin(), pIterable->cend(), count, predicate);
#endif
}


template <typename __Iterable, typename __Element, bool __exceptCond> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __Predicate> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __GenericImmutableStatementsCompositeClient <__Iterable, __Element, __exceptCond>::atLeast (
    Size                count,
    __Predicate const&  predicate
) const noexcept (__PredicateExceptSpecTraits <__Element const, __Predicate>::__noexceptSpec && itNoexcept) -> bool {
  // Call base, global implementation. Abstracts the 'is object const' requirement
  auto const* pIterable = static_cast <__Iterable const*> (this);
#ifdef _MSC_VER
  using IteratorType = decltype (cds::meta::referenceOf <__Iterable const>().cbegin());
  return __MSVC_AtLeastWrapper < IteratorType, __Predicate >::__atLeast (
      pIterable->cbegin(), pIterable->cend(), count, predicate
  );
#else
  return __atLeast (pIterable->cbegin(), pIterable->cend(), count, predicate);
#endif
}


template <typename __Iterable, typename __Element, bool __exceptCond> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __Predicate> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __GenericImmutableStatementsCompositeClient <__Iterable, __Element, __exceptCond>::atMost (
    Size                count,
    __Predicate const&  predicate
) const noexcept (__PredicateExceptSpecTraits <__Element const, __Predicate>::__noexceptSpec && itNoexcept) -> bool {
  // Call base, global implementation. Abstracts the 'is object const' requirement
  auto const* pIterable = static_cast <__Iterable const*> (this);
#ifdef _MSC_VER
  using IteratorType = decltype (cds::meta::referenceOf <__Iterable const>().cbegin());
  return __MSVC_AtMostWrapper < IteratorType, __Predicate >::__atMost (
      pIterable->cbegin(), pIterable->cend(), count, predicate
  );
#else
  return __atMost (pIterable->cbegin(), pIterable->cend(), count, predicate);
#endif
}


template <typename __Iterable, typename __Element, bool __exceptCond> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __Predicate> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __GenericImmutableStatementsCompositeClient <__Iterable, __Element, __exceptCond>::moreThan (
    Size                count,
    __Predicate const&  predicate
) const noexcept (__PredicateExceptSpecTraits <__Element const, __Predicate>::__noexceptSpec && itNoexcept) -> bool {
  // Call base, global implementation. Abstracts the 'is object const' requirement
  auto const* pIterable = static_cast <__Iterable const*> (this);
#ifdef _MSC_VER
  using IteratorType = decltype (cds::meta::referenceOf <__Iterable const>().cbegin());
  return __MSVC_MoreThanWrapper < IteratorType, __Predicate >::__moreThan (
      pIterable->cbegin(), pIterable->cend(), count, predicate
  );
#else
  return __moreThan (pIterable->cbegin(), pIterable->cend(), count, predicate);
#endif
}


template <typename __Iterable, typename __Element, bool __exceptCond> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __Predicate> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __GenericImmutableStatementsCompositeClient <__Iterable, __Element, __exceptCond>::fewerThan (
    Size                count,
    __Predicate const&  predicate
) const noexcept (__PredicateExceptSpecTraits <__Element const, __Predicate>::__noexceptSpec && itNoexcept) -> bool {
  // Call base, global implementation. Abstracts the 'is object const' requirement
  auto const* pIterable = static_cast <__Iterable const*> (this);
#ifdef _MSC_VER
  using IteratorType = decltype (cds::meta::referenceOf <__Iterable const>().cbegin());
  return __MSVC_FewerThanWrapper < IteratorType, __Predicate >::__fewerThan (
      pIterable->cbegin(), pIterable->cend(), count, predicate
  );
#else
  return __fewerThan (pIterable->cbegin(), pIterable->cend(), count, predicate);
#endif
}


template <typename __Iterable, typename __Element, bool __exceptCond> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __Predicate> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __GenericImmutableStatementsCompositeClient <__Iterable, __Element, __exceptCond>::count (
    __Predicate const& predicate
) const noexcept (__PredicateExceptSpecTraits <__Element const, __Predicate>::__noexceptSpec && itNoexcept) -> Size {
  // Call base, global implementation. Abstracts the 'is object const' requirement
  auto const* pIterable = static_cast <__Iterable const*> (this);
#ifdef _MSC_VER
  using IteratorType = decltype (cds::meta::referenceOf <__Iterable const>().cbegin());
  return __MSVC_CountWrapper < IteratorType, __Predicate >::__count (
      pIterable->cbegin(), pIterable->cend(), predicate
  );
#else
  return __count (pIterable->cbegin(), pIterable->cend(), predicate);
#endif
}


template <typename __Iterable, typename __Element, bool __exceptCond> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __Predicate> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __GenericImmutableStatementsCompositeClient <__Iterable, __Element, __exceptCond>::any (
    __Predicate const& predicate
) const noexcept (__PredicateExceptSpecTraits <__Element const, __Predicate>::__noexceptSpec && itNoexcept) -> bool {
  // Call base, global implementation. Abstracts the 'is object const' requirement
  auto const* pIterable = static_cast <__Iterable const*> (this);
#ifdef _MSC_VER
  using IteratorType = decltype (cds::meta::referenceOf <__Iterable const>().cbegin());
  return __MSVC_AnyWrapper < IteratorType, __Predicate >::__any (
      pIterable->cbegin(), pIterable->cend(), predicate
  );
#else
  return __any (pIterable->cbegin(), pIterable->cend(), predicate);
#endif
}


template <typename __Iterable, typename __Element, bool __exceptCond> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __Predicate> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __GenericImmutableStatementsCompositeClient <__Iterable, __Element, __exceptCond>::all (
    __Predicate const& predicate
) const noexcept (__PredicateExceptSpecTraits <__Element const, __Predicate>::__noexceptSpec && itNoexcept) -> bool {
  // Call base, global implementation. Abstracts the 'is object const' requirement
  auto const* pIterable = static_cast <__Iterable const*> (this);
#ifdef _MSC_VER
  using IteratorType = decltype (cds::meta::referenceOf <__Iterable const>().cbegin());
  return __MSVC_AllWrapper < IteratorType, __Predicate >::__all (
      pIterable->cbegin(), pIterable->cend(), predicate
  );
#else
  return __all (pIterable->cbegin(), pIterable->cend(), predicate);
#endif
}


template <typename __Iterable, typename __Element, bool __exceptCond> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
template <typename __Predicate> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __GenericImmutableStatementsCompositeClient <__Iterable, __Element, __exceptCond>::none (
    __Predicate const& predicate
) const noexcept (__PredicateExceptSpecTraits <__Element const, __Predicate>::__noexceptSpec && itNoexcept) -> bool {
  // Call base, global implementation. Abstracts the 'is object const' requirement
  auto const* pIterable = static_cast <__Iterable const*> (this);
#ifdef _MSC_VER
  using IteratorType = decltype (cds::meta::referenceOf <__Iterable const>().cbegin());
  return __MSVC_NoneWrapper < IteratorType, __Predicate >::__none (
      pIterable->cbegin(), pIterable->cend(), predicate
  );
#else
  return __none (pIterable->cbegin(), pIterable->cend(), predicate);
#endif
}
} // namespace __impl 
} // namespace __hidden 
} // namespace cds 

#endif // __CDS_SHARED_GENERIC_IMMUTABLE_STATEMENTS_COMPOSITE_CLIENT_IMPL_HPP__ 
