// NOLINT(llvm-header-guard)
// Created by loghin on 16/02/23.
//

#ifndef __CDS_STATIC_ARRAY_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_STATIC_ARRAY_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

#include <CDS/Iterable>
#include <CDS/Function>
#include <CDS/meta/TypeTraits>

#include "../shared/iterator/AddressIterator.hpp"
#include "../shared/iterator/IteratorSort.hpp"

#include "../shared/iterableInternalCommunication/client/composite/ReplaceCompositeClient.hpp" // NOLINT(llvm-include-order)
#include "../shared/iterableInternalCommunication/client/composite/ReplaceOfCompositeClient.hpp"
#include "../shared/iterableInternalCommunication/client/composite/ReplaceByCompositeClient.hpp"

#include "../shared/iterableInternalCommunication/client/primitive/IndexedOperationsPrimitiveClient.hpp"

#include "../shared/iterableInternalCommunication/client/composite/IndicesCompositeClient.hpp"  // NOLINT(llvm-include-order)
#include "../shared/iterableInternalCommunication/client/composite/IndicesOfCompositeClient.hpp"
#include "../shared/iterableInternalCommunication/client/composite/IndicesByCompositeClient.hpp"

#include "../shared/iterableInternalCommunication/server/IterableServer.hpp"
#include "../shared/iterableInternalCommunication/server/IterableServerDispatcher.hpp"

#include "../shared/array/StaticArrayBase.hpp"

#include "staticArray/Constructs.hpp"

namespace cds {

template <typename __Element, Size __size>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs StaticArray :
    public Iterable <__Element>,
    protected __hidden::__impl::__StaticArrayServer <__Element, __size>,
    public __hidden::__impl::__StaticArrayImplementation <__Element, __size>,
    public __hidden::__impl::__StaticArrayDispatcher <__Element, __size>,
    public __hidden::__impl::__StaticArrayFindOfIterableClient <__Element, __size>,
    public __hidden::__impl::__StaticArrayFindOfInitializerListClient <__Element, __size>,
    public __hidden::__impl::__StaticArrayConstFindOfIterableClient <__Element, __size>,
    public __hidden::__impl::__StaticArrayConstFindOfInitializerListClient <__Element, __size>,
    public __hidden::__impl::__StaticArrayFindByClient <__Element, __size>,
    public __hidden::__impl::__StaticArrayConstFindByClient <__Element, __size>,
    public __hidden::__impl::__StaticArrayGenericStatementsClient <__Element, __size>,
    public __hidden::__impl::__StaticArrayGenericConstStatementsClient <__Element, __size>,
    public __hidden::__impl::__StaticArrayReplaceClient <__Element, __size>,
    public __hidden::__impl::__StaticArrayReplaceOfIterableClient <__Element, __size>,
    public __hidden::__impl::__StaticArrayReplaceOfInitializerListClient <__Element, __size>,
    public __hidden::__impl::__StaticArrayReplaceByClient <__Element, __size>,
    public __hidden::__impl::__StaticArrayIndexedOperationsClient <__Element, __size>,
    public __hidden::__impl::__StaticArrayIndicesClient <__Element, __size>,
    public __hidden::__impl::__StaticArrayIndicesOfIterableClient <__Element, __size>,
    public __hidden::__impl::__StaticArrayIndicesOfInitializerListClient <__Element, __size>,
    public __hidden::__impl::__StaticArrayIndicesByClient <__Element, __size>,
    public __hidden::__impl::__StaticArrayContainsOfIterableClient <__Element, __size>,
    public __hidden::__impl::__StaticArrayContainsOfInitializerListClient <__Element, __size>,
    public __hidden::__impl::__StaticArrayDelegateForwardIterableClient <__Element, __size>,
    public __hidden::__impl::__StaticArrayDelegateForwardConstIterableClient <__Element, __size>,
    public __hidden::__impl::__StaticArrayDelegateBackwardIterableClient <__Element, __size>,
    public __hidden::__impl::__StaticArrayDelegateBackwardConstIterableClient <__Element, __size> {

  static_assert (
      cds::meta::isDefaultConstructible <__Element> (),
      "Requires Default-Constructible Element Type"
  );

protected:
  using Implementation                      = __hidden::__impl::__StaticArrayImplementation <__Element, __size>;
  using Server                              = __hidden::__impl::__StaticArrayServer <__Element, __size>;

  using FindOfIterableClient                = __hidden::__impl::__StaticArrayFindOfIterableClient <__Element, __size>;
  using FindOfInitializerListClient         = __hidden::__impl::__StaticArrayFindOfInitializerListClient <__Element, __size>;
  using FindConstOfIterableClient           = __hidden::__impl::__StaticArrayConstFindOfIterableClient <__Element, __size>;
  using FindConstOfInitializerListClient    = __hidden::__impl::__StaticArrayConstFindOfInitializerListClient <__Element, __size>;
  using FindByClient                        = __hidden::__impl::__StaticArrayFindByClient <__Element, __size>;
  using FindConstByClient                   = __hidden::__impl::__StaticArrayConstFindByClient <__Element, __size>;
  using GenericStatementsClient             = __hidden::__impl::__StaticArrayGenericStatementsClient <__Element, __size>;
  using GenericConstStatementsClient        = __hidden::__impl::__StaticArrayGenericConstStatementsClient <__Element, __size>;
  using ReplaceClient                       = __hidden::__impl::__StaticArrayReplaceClient <__Element, __size>;
  using ReplaceOfIterableClient             = __hidden::__impl::__StaticArrayReplaceOfIterableClient <__Element, __size>;
  using ReplaceOfInitializerListClient      = __hidden::__impl::__StaticArrayReplaceOfInitializerListClient <__Element, __size>;
  using ReplaceByClient                     = __hidden::__impl::__StaticArrayReplaceByClient <__Element, __size>;
  using ContainsOfIterableClient            = __hidden::__impl::__StaticArrayContainsOfIterableClient <__Element, __size>;
  using ContainsOfInitializerListClient     = __hidden::__impl::__StaticArrayContainsOfInitializerListClient <__Element, __size>;
  using IndexedOperationsClient             = __hidden::__impl::__StaticArrayIndexedOperationsClient <__Element, __size>;
  using IndicesClient                       = __hidden::__impl::__StaticArrayIndicesClient <__Element, __size>;
  using IndicesOfIterableClient             = __hidden::__impl::__StaticArrayIndicesOfIterableClient <__Element, __size>;
  using IndicesOfInitializerListClient      = __hidden::__impl::__StaticArrayIndicesOfInitializerListClient <__Element, __size>;
  using IndicesByClient                     = __hidden::__impl::__StaticArrayIndicesByClient <__Element, __size>;
  using DelegateForwardIterableClient       = __hidden::__impl::__StaticArrayDelegateForwardIterableClient <__Element, __size>;
  using DelegateForwardConstIterableClient  = __hidden::__impl::__StaticArrayDelegateForwardConstIterableClient <__Element, __size>;
  using DelegateBackwardIterableClient      = __hidden::__impl::__StaticArrayDelegateBackwardIterableClient <__Element, __size>;
  using DelegateBackwardConstIterableClient = __hidden::__impl::__StaticArrayDelegateBackwardConstIterableClient <__Element, __size>;
  using IterableBase                        = Iterable <__Element>;

public:
  using ElementType = __Element;

  using typename DelegateForwardIterableClient::Iterator;
  using typename DelegateForwardConstIterableClient::ConstIterator;
  using typename DelegateBackwardIterableClient::ReverseIterator;
  using typename DelegateBackwardConstIterableClient::ConstReverseIterator;

  using DelegateForwardIterableClient::begin;
  using DelegateForwardIterableClient::end;

  using DelegateForwardConstIterableClient::begin;
  using DelegateForwardConstIterableClient::end;
  using DelegateForwardConstIterableClient::cbegin;
  using DelegateForwardConstIterableClient::cend;

  using DelegateBackwardIterableClient::rbegin;
  using DelegateBackwardIterableClient::rend;

  using DelegateBackwardConstIterableClient::rbegin;
  using DelegateBackwardConstIterableClient::rend;
  using DelegateBackwardConstIterableClient::crbegin;
  using DelegateBackwardConstIterableClient::crend;

  using FindOfIterableClient::findOf;
  using FindOfIterableClient::findFirstOf;
  using FindOfIterableClient::findLastOf;
  using FindOfIterableClient::findAllOf;
  using FindOfIterableClient::findNotOf;
  using FindOfIterableClient::findFirstNotOf;
  using FindOfIterableClient::findLastNotOf;
  using FindOfIterableClient::findAllNotOf;

  using FindOfInitializerListClient::findOf;
  using FindOfInitializerListClient::findFirstOf;
  using FindOfInitializerListClient::findLastOf;
  using FindOfInitializerListClient::findAllOf;
  using FindOfInitializerListClient::findNotOf;
  using FindOfInitializerListClient::findFirstNotOf;
  using FindOfInitializerListClient::findLastNotOf;
  using FindOfInitializerListClient::findAllNotOf;

  using FindConstOfIterableClient::findOf;
  using FindConstOfIterableClient::findFirstOf;
  using FindConstOfIterableClient::findLastOf;
  using FindConstOfIterableClient::findAllOf;
  using FindConstOfIterableClient::findNotOf;
  using FindConstOfIterableClient::findFirstNotOf;
  using FindConstOfIterableClient::findLastNotOf;
  using FindConstOfIterableClient::findAllNotOf;

  using FindConstOfInitializerListClient::findOf;
  using FindConstOfInitializerListClient::findFirstOf;
  using FindConstOfInitializerListClient::findLastOf;
  using FindConstOfInitializerListClient::findAllOf;
  using FindConstOfInitializerListClient::findNotOf;
  using FindConstOfInitializerListClient::findFirstNotOf;
  using FindConstOfInitializerListClient::findLastNotOf;
  using FindConstOfInitializerListClient::findAllNotOf;

  using FindByClient::findThat;
  using FindByClient::findFirstThat;
  using FindByClient::findLastThat;
  using FindByClient::findAllThat;

  using FindConstByClient::findThat;
  using FindConstByClient::findFirstThat;
  using FindConstByClient::findLastThat;
  using FindConstByClient::findAllThat;

  using GenericStatementsClient::forEach;
  using GenericStatementsClient::some;
  using GenericStatementsClient::atLeast;
  using GenericStatementsClient::atMost;
  using GenericStatementsClient::moreThan;
  using GenericStatementsClient::fewerThan;
  using GenericStatementsClient::count;
  using GenericStatementsClient::any;
  using GenericStatementsClient::all;
  using GenericStatementsClient::none;

  using GenericConstStatementsClient::forEach;
  using GenericConstStatementsClient::some;
  using GenericConstStatementsClient::atLeast;
  using GenericConstStatementsClient::atMost;
  using GenericConstStatementsClient::moreThan;
  using GenericConstStatementsClient::fewerThan;
  using GenericConstStatementsClient::count;
  using GenericConstStatementsClient::any;
  using GenericConstStatementsClient::all;
  using GenericConstStatementsClient::none;

  using ReplaceClient::replace;
  using ReplaceClient::replaceFirst;
  using ReplaceClient::replaceLast;
  using ReplaceClient::replaceAll;

  using ReplaceOfIterableClient::replaceOf;
  using ReplaceOfIterableClient::replaceFirstOf;
  using ReplaceOfIterableClient::replaceLastOf;
  using ReplaceOfIterableClient::replaceAllOf;
  using ReplaceOfIterableClient::replaceNotOf;
  using ReplaceOfIterableClient::replaceFirstNotOf;
  using ReplaceOfIterableClient::replaceLastNotOf;
  using ReplaceOfIterableClient::replaceAllNotOf;

  using ReplaceOfInitializerListClient::replaceOf;
  using ReplaceOfInitializerListClient::replaceFirstOf;
  using ReplaceOfInitializerListClient::replaceLastOf;
  using ReplaceOfInitializerListClient::replaceAllOf;
  using ReplaceOfInitializerListClient::replaceNotOf;
  using ReplaceOfInitializerListClient::replaceFirstNotOf;
  using ReplaceOfInitializerListClient::replaceLastNotOf;
  using ReplaceOfInitializerListClient::replaceAllNotOf;

  using ReplaceByClient::replaceThat;
  using ReplaceByClient::replaceFirstThat;
  using ReplaceByClient::replaceLastThat;
  using ReplaceByClient::replaceAllThat;
  using ReplaceByClient::replaceThatBy;
  using ReplaceByClient::replaceFirstThatBy;
  using ReplaceByClient::replaceLastThatBy;
  using ReplaceByClient::replaceAllThatBy;

  using IndexedOperationsClient::sub;

  using IndicesClient::indicesOf;
  using IndicesClient::firstIndexOf;
  using IndicesClient::lastIndexOf;
  using IndicesClient::allIndicesOf;

  using IndicesOfIterableClient::indicesOfFrom;
  using IndicesOfIterableClient::firstIndexOfFrom;
  using IndicesOfIterableClient::lastIndexOfFrom;
  using IndicesOfIterableClient::allIndicesOfFrom;
  using IndicesOfIterableClient::indicesOfNotFrom;
  using IndicesOfIterableClient::firstIndexOfNotFrom;
  using IndicesOfIterableClient::lastIndexOfNotFrom;
  using IndicesOfIterableClient::allIndicesOfNotFrom;

  using IndicesOfInitializerListClient::indicesOfFrom;
  using IndicesOfInitializerListClient::firstIndexOfFrom;
  using IndicesOfInitializerListClient::lastIndexOfFrom;
  using IndicesOfInitializerListClient::allIndicesOfFrom;
  using IndicesOfInitializerListClient::indicesOfNotFrom;
  using IndicesOfInitializerListClient::firstIndexOfNotFrom;
  using IndicesOfInitializerListClient::lastIndexOfNotFrom;
  using IndicesOfInitializerListClient::allIndicesOfNotFrom;

  using IndicesByClient::indicesOfThat;
  using IndicesByClient::firstIndexOfThat;
  using IndicesByClient::lastIndexOfThat;
  using IndicesByClient::allIndicesOfThat;

  using ContainsOfIterableClient::containsAnyOf;
  using ContainsOfIterableClient::containsAnyNotOf;
  using ContainsOfIterableClient::containsAllOf;
  using ContainsOfIterableClient::containsNoneOf;

  using ContainsOfInitializerListClient::containsAnyOf;
  using ContainsOfInitializerListClient::containsAnyNotOf;
  using ContainsOfInitializerListClient::containsAllOf;
  using ContainsOfInitializerListClient::containsNoneOf;

  constexpr StaticArray () noexcept = default;
  constexpr StaticArray (StaticArray const&) noexcept = default;
  constexpr StaticArray (StaticArray&&) noexcept = default;

  __CDS_cpplang_ConstexprConstructorNonEmptyBody StaticArray (
      std::initializer_list <__Element> const& initializerList
  ) noexcept;

  template <typename __Iterable>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_Explicit __CDS_cpplang_ConstexprConstructorNonEmptyBody StaticArray (__Iterable const& iterable) noexcept;

  constexpr ~StaticArray () noexcept override = default;

  __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (StaticArray const&) noexcept -> StaticArray& = default;
  __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (StaticArray&&) noexcept -> StaticArray& = default;
  
  __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
      std::initializer_list <__Element> const& initializerList
  ) noexcept -> StaticArray&;

  template <typename __Iterable>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
      __Iterable const& iterable
  ) noexcept -> StaticArray&;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator == (
      StaticArray const& array
  ) const noexcept -> bool;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator != (
      StaticArray const& array
  ) const noexcept -> bool;

  __CDS_NoDiscard constexpr auto size () const noexcept -> Size;
  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto front () noexcept(false) -> __Element&;
  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto back () noexcept(false) -> __Element&;
  __CDS_NoDiscard constexpr auto front () const noexcept(false) -> __Element const&;
  __CDS_NoDiscard constexpr auto back () const noexcept(false) -> __Element const&;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto get (Index index) noexcept(false) -> __Element&;
  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto get (Index index) const noexcept(false) -> __Element const&;
  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto data () noexcept -> __Element*;
  __CDS_NoDiscard constexpr auto data () const noexcept -> __Element const*;

  template <
      typename __Comparator = decltype (&cds::predicates::lessThan <__Element>)  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  > auto sort (
      __Comparator const& comparator = &cds::predicates::lessThan <__Element>
  ) noexcept -> void;

  __CDS_NoDiscard auto sequence () & noexcept -> Sequence <StaticArray <__Element, __size>>;
  __CDS_NoDiscard auto sequence () && noexcept -> Sequence <StaticArray <__Element, __size>>;
  __CDS_NoDiscard auto sequence () const& noexcept -> Sequence <StaticArray <__Element, __size> const>;
  __CDS_NoDiscard auto sequence () const&& noexcept -> Sequence <StaticArray <__Element, __size> const>;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator [] (Index index) const noexcept(false) -> ElementType const&;
  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto operator [] (Index index) noexcept(false) -> ElementType&;

  __CDS_NoDiscard auto toString () const noexcept(false) -> String override;

private:
  using typename IterableBase::__GenericHandler;        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using typename IterableBase::__GenericConstHandler;   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  friend __hidden::__impl::__IterableServer <StaticArray <__Element, __size>, __Element>;
  friend __hidden::__impl::__LocalIndexedOperationsPrimitiveClient<StaticArray, __Element>;
  friend __hidden::__impl::__LocalDelegateForwardIterablePrimitiveClient <StaticArray, typename Implementation::__sab_Iterator>;
  friend __hidden::__impl::__LocalDelegateForwardConstIterablePrimitiveClient <StaticArray, typename Implementation::__sab_ConstIterator>;
  friend __hidden::__impl::__LocalDelegateBackwardIterablePrimitiveClient <StaticArray, typename Implementation::__sab_ReverseIterator>;
  friend __hidden::__impl::__LocalDelegateBackwardConstIterablePrimitiveClient <StaticArray, typename Implementation::__sab_ConstReverseIterator>;

  using Server::__is_handlers;        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Server::__is_constHandlers;   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  using Implementation::__sab_get;    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Implementation::__sab_equals; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Implementation::__sab_size;   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Implementation::__sab_data;   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using Implementation::__sab_sort;   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __iicch_obtainGenericHandler ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __hidden::__impl::__IterableInternalRequest requestType
  ) noexcept -> __GenericHandler override;

  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __iicch_obtainGenericConstHandler ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __hidden::__impl::__IterableInternalRequest requestType
  ) const noexcept -> __GenericConstHandler override;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto circularAdjustedIndex (Index index) const noexcept -> Index;
};
} // namespace cds

#include "../shared/iterator/impl/AddressIteratorImpl.hpp"

#include "../shared/iterableInternalCommunication/client/composite/impl/ReplaceCompositeClientImpl.hpp" // NOLINT(llvm-include-order)
#include "../shared/iterableInternalCommunication/client/composite/impl/ReplaceOfCompositeClientImpl.hpp"
#include "../shared/iterableInternalCommunication/client/composite/impl/ReplaceByCompositeClientImpl.hpp"

#include "../shared/iterableInternalCommunication/client/primitive/impl/IndexedOperationsPrimitiveClientImpl.hpp"

#include "../shared/iterableInternalCommunication/client/composite/impl/IndicesCompositeClientImpl.hpp"  // NOLINT(llvm-include-order)
#include "../shared/iterableInternalCommunication/client/composite/impl/IndicesOfCompositeClientImpl.hpp"
#include "../shared/iterableInternalCommunication/client/composite/impl/IndicesByCompositeClientImpl.hpp"

#include "../shared/iterableInternalCommunication/server/impl/IterableServerImpl.hpp"
#include "../shared/iterableInternalCommunication/server/impl/IterableServerDispatcherImpl.hpp"

#include "../shared/array/impl/StaticArrayBaseImpl.hpp"

#include "staticArray/impl/StaticArray.hpp"

#endif // __CDS_STATIC_ARRAY_HPP__
