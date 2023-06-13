//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_GENERIC_MUTABLE_STATEMENTS_COMPOSITE_CLIENT_IMPL_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_SHARED_GENERIC_MUTABLE_STATEMENTS_COMPOSITE_CLIENT_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

#ifdef _MSC_VER
#include "../GenericImmutableStatementsCompositeClient.hpp"
#include "GenericImmutableStatementsCompositeClientImpl.hpp"
#endif

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Iterable, typename __Element, bool __exceptSpec> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Consumer>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __GenericMutableStatementsCompositeClient <__Iterable, __Element, __exceptSpec>::forEach (
    __Consumer const& consumer
) noexcept (__ConsumerExceptSpecTraits <__Element, __Consumer>::__noexceptSpec && itNoexcept) -> void {
  // Call base, global implementation. Abstracts the 'is object const' requirement
  auto* pIterable = static_cast <__Iterable*> (this);
#ifdef _MSC_VER
  using IteratorType = decltype (cds::meta::referenceOf <__Iterable>().begin());
  return __MSVC_ForEachWrapper <IteratorType, __Consumer>::__forEach (
      pIterable->begin(), pIterable->end(), consumer
  );
#else
  return __forEach (pIterable->begin(), pIterable->end(), consumer);
#endif
}


template <typename __Iterable, typename __Element, bool __exceptSpec> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Predicate> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __GenericMutableStatementsCompositeClient <__Iterable, __Element, __exceptSpec>::some (
    Size                count,
    __Predicate const&  predicate
) noexcept (__PredicateExceptSpecTraits <__Element, __Predicate>::__noexceptSpec && itNoexcept) -> bool {
  // Call base, global implementation. Abstracts the 'is object const' requirement
  auto* pIterable = static_cast <__Iterable*> (this);
#ifdef _MSC_VER
  using IteratorType = decltype (cds::meta::referenceOf <__Iterable>().begin());
  return __MSVC_SomeWrapper <IteratorType, __Predicate>::__some (
      pIterable->begin(), pIterable->end(), count, predicate
  );
#else
  return __some (pIterable->begin(), pIterable->end(), count, predicate);
#endif
}


template <typename __Iterable, typename __Element, bool __exceptSpec> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Predicate> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __GenericMutableStatementsCompositeClient <__Iterable, __Element, __exceptSpec>::atLeast (
    Size                count,
    __Predicate const&  predicate
) noexcept (__PredicateExceptSpecTraits <__Element, __Predicate>::__noexceptSpec && itNoexcept) -> bool {
  // Call base, global implementation. Abstracts the 'is object const' requirement
  auto* pIterable = static_cast <__Iterable*> (this);
#ifdef _MSC_VER
  using IteratorType = decltype (cds::meta::referenceOf <__Iterable>().begin());
  return __MSVC_AtLeastWrapper <IteratorType, __Predicate>::__atLeast (
      pIterable->begin(), pIterable->end(), count, predicate
  );
#else
  return __atLeast (pIterable->begin(), pIterable->end(), count, predicate);
#endif
}


template <typename __Iterable, typename __Element, bool __exceptSpec> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Predicate> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __GenericMutableStatementsCompositeClient <__Iterable, __Element, __exceptSpec>::atMost (
    Size                count,
    __Predicate const&  predicate
) noexcept (__PredicateExceptSpecTraits <__Element, __Predicate>::__noexceptSpec && itNoexcept) -> bool {
  // Call base, global implementation. Abstracts the 'is object const' requirement
  auto* pIterable = static_cast <__Iterable*> (this);
#ifdef _MSC_VER
  using IteratorType = decltype (cds::meta::referenceOf <__Iterable>().begin());
  return __MSVC_AtMostWrapper <IteratorType, __Predicate>::__atMost (
      pIterable->begin(), pIterable->end(), count, predicate
  );
#else
  return __atMost (pIterable->begin(), pIterable->end(), count, predicate);
#endif
}


template <typename __Iterable, typename __Element, bool __exceptSpec> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Predicate> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __GenericMutableStatementsCompositeClient <__Iterable, __Element, __exceptSpec>::moreThan (
    Size                count,
    __Predicate const&  predicate
) noexcept (__PredicateExceptSpecTraits <__Element, __Predicate>::__noexceptSpec && itNoexcept) -> bool {
  // Call base, global implementation. Abstracts the 'is object const' requirement
  auto* pIterable = static_cast <__Iterable*> (this);
#ifdef _MSC_VER
  using IteratorType = decltype (cds::meta::referenceOf <__Iterable>().begin());
  return __MSVC_MoreThanWrapper <IteratorType, __Predicate>::__moreThan (
      pIterable->begin(), pIterable->end(), count, predicate
  );
#else
  return __moreThan (pIterable->begin(), pIterable->end(), count, predicate);
#endif
}


template <typename __Iterable, typename __Element, bool __exceptSpec> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Predicate> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __GenericMutableStatementsCompositeClient <__Iterable, __Element, __exceptSpec>::fewerThan (
    Size                count,
    __Predicate const&  predicate
) noexcept (__PredicateExceptSpecTraits <__Element, __Predicate>::__noexceptSpec && itNoexcept) -> bool {
  // Call base, global implementation. Abstracts the 'is object const' requirement
  auto* pIterable = static_cast <__Iterable*> (this);
#ifdef _MSC_VER
  using IteratorType = decltype (cds::meta::referenceOf <__Iterable>().begin());
  return __MSVC_FewerThanWrapper <IteratorType, __Predicate>::__fewerThan (
      pIterable->begin(), pIterable->end(), count, predicate
  );
#else
  return __fewerThan (pIterable->begin(), pIterable->end(), count, predicate);
#endif
}


template <typename __Iterable, typename __Element, bool __exceptSpec> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Predicate> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __GenericMutableStatementsCompositeClient <__Iterable, __Element, __exceptSpec>::count (
    __Predicate const& predicate
) noexcept (__PredicateExceptSpecTraits <__Element, __Predicate>::__noexceptSpec && itNoexcept) -> Size {
  // Call base, global implementation. Abstracts the 'is object const' requirement
  auto* pIterable = static_cast <__Iterable*> (this);
#ifdef _MSC_VER
  using IteratorType = decltype (cds::meta::referenceOf <__Iterable>().begin());
  return __MSVC_CountWrapper <IteratorType, __Predicate>::__count (
      pIterable->begin(), pIterable->end(), predicate
  );
#else
  return __count (pIterable->begin(), pIterable->end(), predicate);
#endif
}


template <typename __Iterable, typename __Element, bool __exceptSpec> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Predicate> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __GenericMutableStatementsCompositeClient <__Iterable, __Element, __exceptSpec>::any (
    __Predicate const& predicate
) noexcept (__PredicateExceptSpecTraits <__Element, __Predicate>::__noexceptSpec && itNoexcept) -> bool {
  // Call base, global implementation. Abstracts the 'is object const' requirement
  auto* pIterable = static_cast <__Iterable*> (this);
#ifdef _MSC_VER
  using IteratorType = decltype (cds::meta::referenceOf <__Iterable>().begin());
  return __MSVC_AnyWrapper <IteratorType, __Predicate>::__any (
      pIterable->begin(), pIterable->end(), predicate
  );
#else
  return __any (pIterable->begin(), pIterable->end(), predicate);
#endif
}


template <typename __Iterable, typename __Element, bool __exceptSpec> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Predicate> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __GenericMutableStatementsCompositeClient <__Iterable, __Element, __exceptSpec>::all (
    __Predicate const& predicate
) noexcept (__PredicateExceptSpecTraits <__Element, __Predicate>::__noexceptSpec && itNoexcept) -> bool {
  // Call base, global implementation. Abstracts the 'is object const' requirement
  auto* pIterable = static_cast <__Iterable*> (this);
#ifdef _MSC_VER
  using IteratorType = decltype (cds::meta::referenceOf <__Iterable>().begin());
  return __MSVC_AllWrapper <IteratorType, __Predicate>::__all (
      pIterable->begin(), pIterable->end(), predicate
  );
#else
  return __all (pIterable->begin(), pIterable->end(), predicate);
#endif
}


template <typename __Iterable, typename __Element, bool __exceptSpec> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Predicate> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __GenericMutableStatementsCompositeClient <__Iterable, __Element, __exceptSpec>::none (
    __Predicate const& predicate
) noexcept (__PredicateExceptSpecTraits <__Element, __Predicate>::__noexceptSpec && itNoexcept) -> bool {
  // Call base, global implementation. Abstracts the 'is object const' requirement
  auto* pIterable = static_cast <__Iterable*> (this);
#ifdef _MSC_VER
  using IteratorType = decltype (cds::meta::referenceOf <__Iterable>().begin());
  return __MSVC_NoneWrapper <IteratorType, __Predicate>::__none (
      pIterable->begin(), pIterable->end(), predicate
  );
#else
  return __none (pIterable->begin(), pIterable->end(), predicate);
#endif
}
} // namespace __impl
} // namespace __hidden
} // namespace cds

#endif // __CDS_SHARED_GENERIC_MUTABLE_STATEMENTS_COMPOSITE_CLIENT_IMPL_HPP__
