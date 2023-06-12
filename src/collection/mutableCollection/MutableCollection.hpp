// NOLINT(llvm-header-guard)
// Created by loghin on 6/20/22.
//

#ifndef __CDS_MUTABLE_COLLECTION_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_MUTABLE_COLLECTION_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

#include <CDS/Collection>

#include "../../shared/iterableInternalCommunication/client/primitive/DelegateForwardIterablePrimitiveClient.hpp"
#include "../../shared/iterableInternalCommunication/client/primitive/IteratorRemovePrimitiveClient.hpp"

#include "../../shared/iterableInternalCommunication/client/composite/GenericMutableStatementsCompositeClient.hpp" // NOLINT(llvm-include-order)
#include "../../shared/iterableInternalCommunication/client/composite/FindOfMutableCompositeClient.hpp"
#include "../../shared/iterableInternalCommunication/client/composite/FindByMutableCompositeClient.hpp"

#include "mutableCollection/MutableCollectionConstructs.hpp"

namespace cds { // NOLINT(modernize-concat-nested-namespaces)

/// \class Abstract Object representing any Iterable Container of given elements, mutable via iteration
/// \tparam __ElementType is the type of elements contained into Collection
///
/// \extends [public]            Collection - Base Collection Class, inheriting properties - Immutable Iterable Container
///
/// \implements [public]         __MutableCollectionDelegateForwardIterableClient - Abstract Mutable Iterator Request Client - begin / end
/// \implements [public]         __MutableCollectionIteratorRemoveClient - Abstract Mutable Iterator Remove Client - remove
/// \implements [public]         __MutableCollectionRandomInsertionClient - Insertion without specified position Client - <strike>add</strike> / <strike>addAll</strike> / <strike>addAllOf</strike> / insert / insertAll / insertAllOf / emplace
/// \implements [public]         __MutableCollectionFindOfIterableClient - Find Of Functions for Collection parameter Client - findOf / findFirstOf / findLastOf / findAllOf / findNotOf / findFirstNotOf / findLastNotOf / findAllNotOf
/// \implements [public]         __MutableCollectionFindOfInitializerListClient - Find Of Functions for std::initializer_list parameter Client - findOf / findFirstOf / findLastOf / findAllOf / findNotOf / findFirstNotOf / findLastNotOf / findAllNotOf
/// \implements [public]         __MutableCollectionFindByClient - Find By Functions for Predicates Client - findThat / findFirstThat / findLastThat / findAllThat
/// \implements [public]         __MutableCollectionGenericStatementsClient - Generic Mutable Functional Statements for Predicates - forEach / some / atLeast / atMost / moreThat / fewerThan / count / any / all / none
///
/// \test Suite: CTS-00001, Group: All - requirement for running, Test Cases: All - requirement for running
/// \test Suite: MCTS-00001, Group: All - requirement for running, Test Cases: All - requirement for running
/// \namespace cds
/// \public
template <typename __ElementType>             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs MutableCollection :  // NOLINT(*-virtual-class-destructor)
    public Collection <__ElementType>,
    public __hidden::__impl::__MutableCollectionDelegateForwardIterableClient <__ElementType>,
    public __hidden::__impl::__MutableCollectionIteratorRemoveClient <__ElementType>,
    public __hidden::__impl::__MutableCollectionRandomInsertionClient <__ElementType>,
    public __hidden::__impl::__MutableCollectionFindOfIterableClient <__ElementType>,
    public __hidden::__impl::__MutableCollectionFindOfInitializerListClient <__ElementType>,
    public __hidden::__impl::__MutableCollectionFindByClient <__ElementType>,
    public __hidden::__impl::__MutableCollectionGenericStatementsClient <__ElementType> {
protected:
  /// \typedef protected alias for Collection \< __ElementType \> base extended class - providing immutable iterable properties
  /// \protected
  using CollectionBase                    = Collection <__ElementType>;

  /// \typedef protected alias for __MutableCollectionDelegateForwardIterableClient base interface - providing begin / end for Abstract Mutable Iterators
  /// \protected
  using DelegateForwardIterableClient     = __hidden::__impl::__MutableCollectionDelegateForwardIterableClient <__ElementType>;

  /// \typedef protected alias for __MutableCollectionIteratorRemoveClient base interface - providing remove for Abstract Mutable Iterators
  /// \protected
  using IteratorRemoveClient              = __hidden::__impl::__MutableCollectionIteratorRemoveClient <__ElementType>;

  /// \typedef protected alias for __MutableCollectionRandomInsertionClient base interface - providing insertion functions - <strike>add</strike> / <strike>addAll</strike> / <strike>addAllOf</strike> / insert / insertAll / insertAllOf / emplace
  /// \protected
  using RandomInsertionClient             = __hidden::__impl::__MutableCollectionRandomInsertionClient <__ElementType>;

  /// \typedef protected alias for __MutableCollectionFindOfIterableClient base interface - providing find-of functions with a Collection parameter - findOf / findFirstOf / findLastOf / findAllOf / findNotOf / findFirstNotOf / findLastNotOf / findAllNotOf
  /// \protected
  using FindOfIterableClient              = __hidden::__impl::__MutableCollectionFindOfIterableClient <__ElementType>;

  /// \typedef protected alias for __MutableCollectionFindOfInitializerListClient base interface - providing find-of functions with a std::initializer_list parameter - findOf / findFirstOf / findLastOf / findAllOf / findNotOf / findFirstNotOf / findLastNotOf / findAllNotOf
  /// \protected
  using FindOfInitializerListClient       = __hidden::__impl::__MutableCollectionFindOfInitializerListClient <__ElementType>;

  /// \typedef protected alias for __MutableCollectionFindByClient base interface - providing find-by-predicate functions - findThat / findFirstThat / findLastThat / findAllThat
  /// \protected
  using FindByClient                      = __hidden::__impl::__MutableCollectionFindByClient <__ElementType>;

  /// \typedef protected alias for __MutableCollectionGenericStatementsClient base interface - providing functional-predicate functions - forEach / some / atLeast / atMost / moreThat / fewerThan / count / any / all / none
  /// \protected
  using GenericStatementsClient           = __hidden::__impl::__MutableCollectionGenericStatementsClient <__ElementType>;

  /// \typedef imported protected alias for __GenericHandler, representing a generic member function pointer, represents a function returned at a request made through the Collection Communication Channel
  /// \protected
  using typename CollectionBase::__GenericHandler;        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \typedef imported protected alias for __GenericConstHandler, representing a generic member const-function pointer, represents a function returned at a request made through the Collection Communication Channel
  /// \protected
  using typename CollectionBase::__GenericConstHandler;   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

public:
  /// \typedef public alias for __ElementType, the type of the contained elements,
  /// publicly accessible, useful in sfinae statements - decltype ( MutableCollection )::ElementType
  /// \public
  using ElementType                       = __ElementType;

  /// \typedef The Mutable Iterator Type, imported from Abstract Forward Iterator Client
  /// \public
  using typename DelegateForwardIterableClient::Iterator;

  /// \brief Destructor
  /// \exceptsafe
  /// \test Suite: MCTS-00001, Group: All - requirement for running, Test Cases: All - requirement for running
  /// \public
  __CDS_cpplang_ConstexprDestructor ~MutableCollection () noexcept override;
  
  /// \brief Deleted Copy Assignment Operator
  /// \param [in] collection : MutableCollection cref = Constant Reference to a collection to copy data from
  /// \exceptsafe
  /// \return MutableCollection ref = Reference to the modified object
  ///
  /// \test N/A
  /// \public
  auto operator = (MutableCollection const&) noexcept -> MutableCollection & = delete;

  /// \brief Deleted Move Assignment Operator
  /// \param [in, out] collection : MutableCollection mref = Move Reference to a collection to move data from
  /// \exceptsafe
  /// \return MutableCollection ref = Reference to the modified object
  ///
  /// \test N/A
  /// \public
  auto operator = (MutableCollection&&) noexcept -> MutableCollection & = delete;

  /// \inherit begin function inherited from Collection base class. Forward Const Iterator begin function
  /// \test Not Applicable, import of tested functionality.
  /// \public
  using CollectionBase::begin;

  /// \inherit begin function inherited from Collection base class. Forward Const Iterator end function
  /// \test Not Applicable, import of tested functionality.
  /// \public
  using CollectionBase::end;

  /// \inherit begin function inherited from Collection. Forward Const Iterator begin function
  /// \test Not Applicable, import of tested functionality.
  /// \public
  using CollectionBase::cbegin;

  /// \inherit begin function inherited from Collection. Forward Const Iterator end function
  /// \test Not Applicable, import of tested functionality.
  /// \public
  using CollectionBase::cend;

  /// \inherit begin function inherited from DelegateForwardIterableClient interface.
  /// \test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: {
  ///      MCTC-00051-IT-range,
  ///      MCTC-00052-IT-begin_end,
  ///      MCTC-00054-IT-e_begin_end,
  ///      MCTC-00056-IT-e_emptyRange,
  ///      MCTC-00058-IT-mutabilityRange,
  ///      MCTC-00059-IT-mutabilityIteration
  /// }
  /// \public
  using DelegateForwardIterableClient::begin;

  /// \inherit end function inherited from DelegateForwardIterableClient interface.
  /// \test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: {
  ///      MCTC-00051-IT-range,
  ///      MCTC-00052-IT-begin_end,
  ///      MCTC-00054-IT-e_begin_end,
  ///      MCTC-00056-IT-e_emptyRange,
  ///      MCTC-00058-IT-mutabilityRange,
  ///      MCTC-00059-IT-mutabilityIteration
  /// }
  /// \public
  using DelegateForwardIterableClient::end;

  /// \inherit remove ( ConstIterator ) call, inherited from Collection base class
  /// \test Not Applicable, import of tested functionality.
  /// \public
  using CollectionBase::remove;

  /// \inherit remove ( Iterator ) call, inherited from IteratorPrimitiveClient interface
  /// \test Suite: MCTS-00001, Group: MCTG-00350-RAIT, Test Cases: {
  ///      MCTC-00351-RAIT-removeAtFront,
  ///      MCTC-00352-RAIT-removeInBounds,
  ///      MCTC-00353-RAIT-removeAtEnd,
  ///      MCTC-00355-RAIT-removeBeforeFront,
  ///      MCTC-00356-RAIT-removeFromOther
  /// }
  /// \public
  using IteratorRemoveClient::remove;

  /// \inherit forEach immutable functional call, inherited from Collection base class
  /// \test Not Applicable, import of tested functionality.
  /// \public
  using CollectionBase::forEach;

  /// \inherit some immutable functional call, inherited from Collection base class
  /// \test Not Applicable, import of tested functionality.
  /// \public
  using CollectionBase::some;

  /// \inherit atLeast immutable functional call, inherited from Collection base class
  /// \test Not Applicable, import of tested functionality.
  /// \public
  using CollectionBase::atLeast;

  /// \inherit atMost immutable functional call, inherited from Collection base class
  /// \test Not Applicable, import of tested functionality.
  /// \public
  using CollectionBase::atMost;

  /// \inherit moreThan immutable functional call, inherited from Collection base class
  /// \test Not Applicable, import of tested functionality.
  /// \public
  using CollectionBase::moreThan;

  /// \inherit fewerThan immutable functional call, inherited from Collection base class
  /// \test Not Applicable, import of tested functionality.
  /// \public
  using CollectionBase::fewerThan;

  /// \inherit count immutable functional call, inherited from Collection base class
  /// \test Not Applicable, import of tested functionality.
  /// \public
  using CollectionBase::count;

  /// \inherit any immutable functional call, inherited from Collection base class
  /// \test Not Applicable, import of tested functionality.
  /// \public
  using CollectionBase::any;

  /// \inherit all immutable functional call, inherited from Collection base class
  /// \test Not Applicable, import of tested functionality.
  /// \public
  using CollectionBase::all;

  /// \inherit none immutable functional call, inherited from Collection base class
  /// \test Not Applicable, import of tested functionality.
  /// \public
  using CollectionBase::none;


  /// \inherit forEach mutable functional call, inherited from GenericStatementsClient interface
  /// \test Suite: MCTS-00001, Group: MCTG-00100-FS, Test Cases: {
  ///      MCTC-00139-FS-forEachCount,
  ///      MCTC-00140-FS-forEachMutability,
  ///      MCTC-00141-FS-forEachMemberFnMutability
  /// }
  /// \test Suite: MCTS-00001, Group: MCTG-00200-FSMF, Test Cases: { MCTC-00201-FSMF-forEach }
  /// \public
  using GenericStatementsClient::forEach;

  /// \inherit some mutable functional call, inherited from GenericStatementsClient interface
  /// \test Suite: MCTS-00001, Group: MCTG-00100-FS, Test Cases: { MCTC-00136-FS-someExact, MCTC-00137-FS-someLessFalse, MCTC-00138-someMoreFalse }
  /// \test Suite: MCTS-00001, Group: MCTG-00200-FSMF, Test Cases: { MCTC-00202-FSMF-someEqual, MCTC-00203-FSMF-someLess, MCTC-00204-someMore }
  /// \public
  using GenericStatementsClient::some;

  /// \inherit atLeast mutable functional call, inherited from GenericStatementsClient interface
  /// \test Suite: MCTS-00001, Group: MCTG-00100-FS, Test Cases: { MCTC-00132-FS-atLeastTrue, MCTC-00133-FS-atLeastCloseTrue, MCTC-00134-atLeastCloseFalse, MCTC-00135-atLeastFalse }
  /// \test Suite: MCTS-00001, Group: MCTG-00200-FSMF, Test Cases: { MCTC-00205-FSMF-atLeast, MCTC-00206-FSMF-atLeastLess, MCTC-00207-atLeastMore }
  /// \public
  using GenericStatementsClient::atLeast;

  /// \inherit atMost mutable functional call, inherited from GenericStatementsClient interface
  /// \test Suite: MCTS-00001, Group: MCTG-00100-FS, Test Cases: { MCTC-00128-FS-atMostTrue, MCTC-00129-FS-atMostCloseTrue, MCTC-00130-atMostCloseFalse, MCTC-00131-atMostFalse }
  /// \test Suite: MCTS-00001, Group: MCTG-00200-FSMF, Test Cases: { MCTC-00208-FSMF-atMost, MCTC-00209-FSMF-atMostLess, MCTC-00210-atMostMore }
  /// \public
  using GenericStatementsClient::atMost;

  /// \inherit moreThan mutable functional call, inherited from GenericStatementsClient interface
  /// \test Suite: MCTS-00001, Group: MCTG-00100-FS, Test Cases: { MCTC-00123-FS-moreThanTrue, MCTC-00124-FS-moreThanCloseTrue, MCTC-00125-moreThanCloseFalse, MCTC-00126-moreThanFalse, MCTC-00127-moreThanCompletelyFalse }
  /// \test Suite: MCTS-00001, Group: MCTG-00200-FSMF, Test Cases: { MCTC-00211-FSMF-moreThan, MCTC-00212-FSMF-moreThanLess, MCTC-00213-moreThanMore }
  /// \public
  using GenericStatementsClient::moreThan;

  /// \inherit fewerThan mutable functional call, inherited from GenericStatementsClient interface
  /// \test Suite: MCTS-00001, Group: MCTG-00100-FS, Test Cases: { MCTC-00118-FS-fewerThanTrue, MCTC-00119-FS-fewerThanCloseTrue, MCTC-00120-fewerThanCloseFalse, MCTC-00121-fewerThanFalse, MCTC-00122-fewerThanCompletelyFalse }
  /// \test Suite: MCTS-00001, Group: MCTG-00200-FSMF, Test Cases: { MCTC-00214-FSMF-fewerThan, MCTC-00215-FSMF-fewerThanLess, MCTC-00216-fewerThanMore }
  /// \public
  using GenericStatementsClient::fewerThan;

  /// \inherit count mutable functional call, inherited from GenericStatementsClient interface
  /// \test Suite: MCTS-00001, Group: MCTG-00100-FS, Test Cases: { MCTC-00113-FS-countProp1, MCTC-00114-FS-countProp2, MCTC-00115-countProp3, MCTC-00116-countProp4, MCTC-00117-countPropLbd }
  /// \test Suite: MCTS-00001, Group: MCTG-00200-FSMF, Test Cases: { MCTC-00217-FSMF-countExact }
  /// \public
  using GenericStatementsClient::count;

  /// \inherit any mutable functional call, inherited from GenericStatementsClient interface
  /// \test Suite: MCTS-00001, Group: MCTG-00100-FS, Test Cases: { MCTC-00101-FS-anyNone, MCTC-00102-FS-anyOne, MCTC-00103-anyMore, MCTC-00104-anyAll }
  /// \test Suite: MCTS-00001, Group: MCTG-00200-FSMF, Test Cases: { MCTC-00218-FSMF-anyNone, MCTC-00219-FSMF-anyOne, MCTC-00220-anyMore, MCTC-00221-anyAll }
  /// \public
  using GenericStatementsClient::any;

  /// \inherit all mutable functional call, inherited from GenericStatementsClient interface
  /// \test Suite: MCTS-00001, Group: MCTG-00100-FS, Test Cases: { MCTC-00105-FS-allNone, MCTC-00106-FS-allOne, MCTC-00107-allMore, MCTC-00108-allAll }
  /// \test Suite: MCTS-00001, Group: MCTG-00200-FSMF, Test Cases: { MCTC-00222-FSMF-allNone, MCTC-00223-FSMF-allOne, MCTC-00224-allMore, MCTC-00225-allAll }
  /// \public
  using GenericStatementsClient::all;

  /// \inherit none mutable functional call, inherited from GenericStatementsClient interface
  /// \test Suite: MCTS-00001, Group: MCTG-00100-FS, Test Cases: { MCTC-00109-FS-noneNone, MCTC-00110-FS-noneOne, MCTC-00111-noneMore, MCTC-00112-noneAll }
  /// \test Suite: MCTS-00001, Group: MCTG-00200-FSMF, Test Cases: { MCTC-00226-FSMF-noneNone, MCTC-00227-FSMF-noneOne, MCTC-00228-noneMore, MCTC-00229-noneAll }
  /// \public
  using GenericStatementsClient::none;

  /// \inherit findOf ( Collection ) Const Iterator, inherited from Collection base class
  /// \test Not Applicable, import of tested functionality.
  /// \public
  using CollectionBase::findOf;

  /// \inherit findFirstOf ( Collection ) Const Iterator, inherited from Collection base class
  /// \test Not Applicable, import of tested functionality.
  /// \public
  using CollectionBase::findFirstOf;

  /// \inherit findLastOf ( Collection ) Const Iterator, inherited from Collection base class
  /// \test Not Applicable, import of tested functionality.
  /// \public
  using CollectionBase::findLastOf;

  /// \inherit findAllOf ( Collection ) Const Iterator, inherited from Collection base class
  /// \test Not Applicable, import of tested functionality.
  /// \public
  using CollectionBase::findAllOf;

  /// \inherit findNotOf ( Collection ) Const Iterator, inherited from Collection base class
  /// \test Not Applicable, import of tested functionality.
  /// \public
  using CollectionBase::findNotOf;

  /// \inherit findFirstNotOf ( Collection ) Const Iterator, inherited from Collection base class
  /// \test Not Applicable, import of tested functionality.
  /// \public
  using CollectionBase::findFirstNotOf;

  /// \inherit findLastNotOf ( Collection ) Const Iterator, inherited from Collection base class
  /// \test Not Applicable, import of tested functionality.
  /// \public
  using CollectionBase::findLastNotOf;

  /// \inherit findAllNotOf ( Collection ) Const Iterator, inherited from Collection base class
  /// \test Not Applicable, import of tested functionality.
  /// \public
  using CollectionBase::findAllNotOf;


  /// \inherit findOf ( Collection ) call, returning mutable iterators, inherited from FindOfIterableClient interface
  /// \test Suite: MCTS-00001, Group: MCTG-00700-FO, Test Cases: {
  ///      MCTC-00701-FO-findOfStoreInMatchingNone [-Collection Group],
  ///      MCTC-00702-FO-findOfStoreInMatchingOne [-Collection Group],
  ///      MCTC-00703-FO-findOfStoreInMatchingMoreLessThanLimit [-Collection Group],
  ///      MCTC-00704-FO-findOfStoreInMatchingMore [-Collection Group],
  ///      MCTC-00705-FO-findOfStoreInMatchingMoreMoreThanLimit [-Collection Group],
  ///      MCTC-00706-FO-findOfStoreInMatchingAll [-Collection Group],
  ///      MCTC-00707-FO-findOfStoreInMatchingAllAndMore [-Collection Group],
  ///      MCTC-00708-FO-findOfReturnedMatchingNone [-Collection Group],
  ///      MCTC-00709-FO-findOfReturnedMatchingOne [-Collection Group],
  ///      MCTC-00710-FO-findOfReturnedMatchingMoreLessThanLimit [-Collection Group],
  ///      MCTC-00711-FO-findOfReturnedMatchingMore [-Collection Group],
  ///      MCTC-00712-FO-findOfReturnedMatchingMoreMoreThanLimit [-Collection Group],
  ///      MCTC-00713-FO-findOfReturnedMatchingAll [-Collection Group],
  ///      MCTC-00714-FO-findOfReturnedMatchingAllAndMore [-Collection Group]
  /// }
  /// \public
  using FindOfIterableClient::findOf;

  /// \inherit findFirstOf ( Collection ) call, returning mutable iterators, inherited from FindOfIterableClient interface
  /// \test Suite: MCTS-00001, Group: MCTG-00700-FO, Test Cases: {
  ///      MCTC-00715-FO-findFirstOfMatchingNone [-Collection Group],
  ///      MCTC-00716-FO-findFirstOfMatchingOne [-Collection Group],
  ///      MCTC-00717-FO-findFirstOfMatchingMore [-Collection Group],
  ///      MCTC-00718-FO-findFirstOfMatchingAll [-Collection Group],
  ///      MCTC-00719-FO-findFirstOfMatchingAllAndMore [-Collection Group]
  /// }
  /// \public
  using FindOfIterableClient::findFirstOf;

  /// \inherit findLastOf ( Collection ) call, returning mutable iterators, inherited from FindOfIterableClient interface
  /// \test Suite: MCTS-00001, Group: MCTG-00700-FO, Test Cases: {
  ///      MCTC-00720-FO-findLastOfMatchingNone [-Collection Group],
  ///      MCTC-00721-FO-findLastOfMatchingOne [-Collection Group],
  ///      MCTC-00722-FO-findLastOfMatchingMore [-Collection Group],
  ///      MCTC-00723-FO-findLastOfMatchingAll [-Collection Group],
  ///      MCTC-00724-FO-findLastOfMatchingAllAndMore [-Collection Group]
  /// }
  /// \public
  using FindOfIterableClient::findLastOf;

  /// \inherit findAllOf ( Collection ) call, returning mutable iterators, inherited from FindOfIterableClient interface
  /// \test Suite: MCTS-00001, Group: MCTG-00700-FO, Test Cases: {
  ///      MCTC-00725-FO-findAllOfStoreInMatchingNone [-Collection Group],
  ///      MCTC-00726-FO-findAllOfStoreInMatchingOne [-Collection Group],
  ///      MCTC-00727-FO-findAllOfStoreInMatchingMore [-Collection Group],
  ///      MCTC-00728-FO-findAllOfStoreInMatchingAll [-Collection Group],
  ///      MCTC-00729-FO-findAllOfStoreInMatchingAllAndMore [-Collection Group],
  ///      MCTC-00730-FO-findAllOfReturnedMatchingNone [-Collection Group],
  ///      MCTC-00731-FO-findAllOfReturnedMatchingOne [-Collection Group],
  ///      MCTC-00732-FO-findAllOfReturnedMatchingMore [-Collection Group],
  ///      MCTC-00733-FO-findAllOfReturnedMatchingAll [-Collection Group],
  ///      MCTC-00734-FO-findAllOfReturnedMatchingAllAndMore [-Collection Group]
  /// }
  /// \public
  using FindOfIterableClient::findAllOf;

  /// \inherit findNotOf ( Collection ) call, returning mutable iterators, inherited from FindOfIterableClient interface
  /// \test Suite: MCTS-00001, Group: MCTG-00700-FO, Test Cases: {
  ///      MCTC-00735-FO-findNotOfStoreInMatchingNone [-Collection Group],
  ///      MCTC-00736-FO-findNotOfStoreInMatchingOne [-Collection Group],
  ///      MCTC-00737-FO-findNotOfStoreInMatchingMoreLessThanLimit [-Collection Group],
  ///      MCTC-00738-FO-findNotOfStoreInMatchingMore [-Collection Group],
  ///      MCTC-00739-FO-findNotOfStoreInMatchingMoreMoreThanLimit [-Collection Group],
  ///      MCTC-00740-FO-findNotOfStoreInMatchingAll [-Collection Group],
  ///      MCTC-00741-FO-findNotOfStoreInMatchingAllAndMore [-Collection Group],
  ///      MCTC-00742-FO-findNotOfReturnedMatchingNone [-Collection Group],
  ///      MCTC-00743-FO-findNotOfReturnedMatchingOne [-Collection Group],
  ///      MCTC-00744-FO-findNotOfReturnedMatchingMoreLessThanLimit [-Collection Group],
  ///      MCTC-00745-FO-findNotOfReturnedMatchingMore [-Collection Group],
  ///      MCTC-00746-FO-findNotOfReturnedMatchingMoreMoreThanLimit [-Collection Group],
  ///      MCTC-00747-FO-findNotOfReturnedMatchingAll [-Collection Group],
  ///      MCTC-00748-FO-findNotOfReturnedMatchingAllAndMore [-Collection Group]
  /// }
  /// \public
  using FindOfIterableClient::findNotOf;

  /// \inherit findFirstNotOf ( Collection ) call, returning mutable iterators, inherited from FindOfIterableClient interface
  /// \test Suite: MCTS-00001, Group: MCTG-00700-FO, Test Cases: {
  ///      MCTC-00749-FO-findFirstNotOfMatchingNone [-Collection Group],
  ///      MCTC-00750-FO-findFirstNotOfMatchingOne [-Collection Group],
  ///      MCTC-00751-FO-findFirstNotOfMatchingMore [-Collection Group],
  ///      MCTC-00752-FO-findFirstNotOfMatchingAll [-Collection Group],
  ///      MCTC-00753-FO-findFirstNotOfMatchingAllAndMore [-Collection Group]
  /// }
  /// \public
  using FindOfIterableClient::findFirstNotOf;

  /// \inherit findLastNotOf ( Collection ) call, returning mutable iterators, inherited from FindOfIterableClient interface
  /// \test Suite: MCTS-00001, Group: MCTG-00700-FO, Test Cases: {
  ///      MCTC-00754-FO-findLastNotOfMatchingNone [-Collection Group],
  ///      MCTC-00755-FO-findLastNotOfMatchingOne [-Collection Group],
  ///      MCTC-00756-FO-findLastNotOfMatchingMore [-Collection Group],
  ///      MCTC-00757-FO-findLastNotOfMatchingAll [-Collection Group],
  ///      MCTC-00758-FO-findLastNotOfMatchingAllAndMore [-Collection Group]
  /// }
  /// \public
  using FindOfIterableClient::findLastNotOf;

  /// \inherit findAllNotOf ( Collection ) call, returning mutable iterators, inherited from FindOfIterableClient interface
  /// \test Suite: MCTS-00001, Group: MCTG-00700-FO, Test Cases: {
  ///      MCTC-00759-FO-findAllNotOfStoreInMatchingNone [-Collection Group],
  ///      MCTC-00760-FO-findAllNotOfStoreInMatchingOne [-Collection Group],
  ///      MCTC-00761-FO-findAllNotOfStoreInMatchingMore [-Collection Group],
  ///      MCTC-00762-FO-findAllNotOfStoreInMatchingAll [-Collection Group],
  ///      MCTC-00763-FO-findAllNotOfStoreInMatchingAllAndMore [-Collection Group],
  ///      MCTC-00764-FO-findAllNotOfReturnedMatchingNone [-Collection Group],
  ///      MCTC-00765-FO-findAllNotOfReturnedMatchingOne [-Collection Group],
  ///      MCTC-00766-FO-findAllNotOfReturnedMatchingMore [-Collection Group],
  ///      MCTC-00767-FO-findAllNotOfReturnedMatchingAll [-Collection Group],
  ///      MCTC-00768-FO-findAllNotOfReturnedMatchingAllAndMore [-Collection Group]
  /// }
  /// \public
  using FindOfIterableClient::findAllNotOf;


  /// \inherit findOf ( InitializerList ) call, returning mutable iterators, inherited from FindOfInitializerListClient interface
  /// \test Suite: MCTS-00001, Group: MCTG-00700-FO, Test Cases: {
  ///      MCTC-00701-FO-findOfStoreInMatchingNone [-InitializerList Group],
  ///      MCTC-00702-FO-findOfStoreInMatchingOne [-InitializerList Group],
  ///      MCTC-00703-FO-findOfStoreInMatchingMoreLessThanLimit [-InitializerList Group],
  ///      MCTC-00704-FO-findOfStoreInMatchingMore [-InitializerList Group],
  ///      MCTC-00705-FO-findOfStoreInMatchingMoreMoreThanLimit [-InitializerList Group],
  ///      MCTC-00706-FO-findOfStoreInMatchingAll [-InitializerList Group],
  ///      MCTC-00707-FO-findOfStoreInMatchingAllAndMore [-InitializerList Group],
  ///      MCTC-00708-FO-findOfReturnedMatchingNone [-InitializerList Group],
  ///      MCTC-00709-FO-findOfReturnedMatchingOne [-InitializerList Group],
  ///      MCTC-00710-FO-findOfReturnedMatchingMoreLessThanLimit [-InitializerList Group],
  ///      MCTC-00711-FO-findOfReturnedMatchingMore [-InitializerList Group],
  ///      MCTC-00712-FO-findOfReturnedMatchingMoreMoreThanLimit [-InitializerList Group],
  ///      MCTC-00713-FO-findOfReturnedMatchingAll [-InitializerList Group],
  ///      MCTC-00714-FO-findOfReturnedMatchingAllAndMore [-InitializerList Group]
  /// }
  /// \public
  using FindOfInitializerListClient::findOf;

  /// \inherit findFirstOf ( InitializerList ) call, returning mutable iterators, inherited from FindOfInitializerListClient interface
  /// \test Suite: MCTS-00001, Group: MCTG-00700-FO, Test Cases: {
  ///      MCTC-00715-FO-findFirstOfMatchingNone [-InitializerList Group],
  ///      MCTC-00716-FO-findFirstOfMatchingOne [-InitializerList Group],
  ///      MCTC-00717-FO-findFirstOfMatchingMore [-InitializerList Group],
  ///      MCTC-00718-FO-findFirstOfMatchingAll [-InitializerList Group],
  ///      MCTC-00719-FO-findFirstOfMatchingAllAndMore [-InitializerList Group]
  /// }
  /// \public
  using FindOfInitializerListClient::findFirstOf;

  /// \inherit findLastOf ( InitializerList ) call, returning mutable iterators, inherited from FindOfInitializerListClient interface
  /// \test Suite: MCTS-00001, Group: MCTG-00700-FO, Test Cases: {
  ///      MCTC-00720-FO-findLastOfMatchingNone [-InitializerList Group],
  ///      MCTC-00721-FO-findLastOfMatchingOne [-InitializerList Group],
  ///      MCTC-00722-FO-findLastOfMatchingMore [-InitializerList Group],
  ///      MCTC-00723-FO-findLastOfMatchingAll [-InitializerList Group],
  ///      MCTC-00724-FO-findLastOfMatchingAllAndMore [-InitializerList Group]
  /// }
  /// \public
  using FindOfInitializerListClient::findLastOf;

  /// \inherit findAllOf ( InitializerList ) call, returning mutable iterators, inherited from FindOfInitializerListClient interface
  /// \test Suite: MCTS-00001, Group: MCTG-00700-FO, Test Cases: {
  ///      MCTC-00725-FO-findAllOfStoreInMatchingNone [-InitializerList Group],
  ///      MCTC-00726-FO-findAllOfStoreInMatchingOne [-InitializerList Group],
  ///      MCTC-00727-FO-findAllOfStoreInMatchingMore [-InitializerList Group],
  ///      MCTC-00728-FO-findAllOfStoreInMatchingAll [-InitializerList Group],
  ///      MCTC-00729-FO-findAllOfStoreInMatchingAllAndMore [-InitializerList Group],
  ///      MCTC-00730-FO-findAllOfReturnedMatchingNone [-InitializerList Group],
  ///      MCTC-00731-FO-findAllOfReturnedMatchingOne [-InitializerList Group],
  ///      MCTC-00732-FO-findAllOfReturnedMatchingMore [-InitializerList Group],
  ///      MCTC-00733-FO-findAllOfReturnedMatchingAll [-InitializerList Group],
  ///      MCTC-00734-FO-findAllOfReturnedMatchingAllAndMore [-InitializerList Group]
  /// }
  /// \public
  using FindOfInitializerListClient::findAllOf;

  /// \inherit findNotOf ( InitializerList ) call, returning mutable iterators, inherited from FindOfInitializerListClient interface
  /// \test Suite: MCTS-00001, Group: MCTG-00700-FO, Test Cases: {
  ///      MCTC-00735-FO-findNotOfStoreInMatchingNone [-InitializerList Group],
  ///      MCTC-00736-FO-findNotOfStoreInMatchingOne [-InitializerList Group],
  ///      MCTC-00737-FO-findNotOfStoreInMatchingMoreLessThanLimit [-InitializerList Group],
  ///      MCTC-00738-FO-findNotOfStoreInMatchingMore [-InitializerList Group],
  ///      MCTC-00739-FO-findNotOfStoreInMatchingMoreMoreThanLimit [-InitializerList Group],
  ///      MCTC-00740-FO-findNotOfStoreInMatchingAll [-InitializerList Group],
  ///      MCTC-00741-FO-findNotOfStoreInMatchingAllAndMore [-InitializerList Group],
  ///      MCTC-00742-FO-findNotOfReturnedMatchingNone [-InitializerList Group],
  ///      MCTC-00743-FO-findNotOfReturnedMatchingOne [-InitializerList Group],
  ///      MCTC-00744-FO-findNotOfReturnedMatchingMoreLessThanLimit [-InitializerList Group],
  ///      MCTC-00745-FO-findNotOfReturnedMatchingMore [-InitializerList Group],
  ///      MCTC-00746-FO-findNotOfReturnedMatchingMoreMoreThanLimit [-InitializerList Group],
  ///      MCTC-00747-FO-findNotOfReturnedMatchingAll [-InitializerList Group],
  ///      MCTC-00748-FO-findNotOfReturnedMatchingAllAndMore [-InitializerList Group]
  /// }
  /// \public
  using FindOfInitializerListClient::findNotOf;

  /// \inherit findFirstNotOf ( InitializerList ) call, returning mutable iterators, inherited from FindOfInitializerListClient interface
  /// \test Suite: MCTS-00001, Group: MCTG-00700-FO, Test Cases: {
  ///      MCTC-00749-FO-findFirstNotOfMatchingNone [-InitializerList Group],
  ///      MCTC-00750-FO-findFirstNotOfMatchingOne [-InitializerList Group],
  ///      MCTC-00751-FO-findFirstNotOfMatchingMore [-InitializerList Group],
  ///      MCTC-00752-FO-findFirstNotOfMatchingAll [-InitializerList Group],
  ///      MCTC-00753-FO-findFirstNotOfMatchingAllAndMore [-InitializerList Group]
  /// }
  /// \public
  using FindOfInitializerListClient::findFirstNotOf;

  /// \inherit findLastNotOf ( InitializerList ) call, returning mutable iterators, inherited from FindOfInitializerListClient interface
  /// \test Suite: MCTS-00001, Group: MCTG-00700-FO, Test Cases: {
  ///      MCTC-00754-FO-findLastNotOfMatchingNone [-InitializerList Group],
  ///      MCTC-00755-FO-findLastNotOfMatchingOne [-InitializerList Group],
  ///      MCTC-00756-FO-findLastNotOfMatchingMore [-InitializerList Group],
  ///      MCTC-00757-FO-findLastNotOfMatchingAll [-InitializerList Group],
  ///      MCTC-00758-FO-findLastNotOfMatchingAllAndMore [-InitializerList Group]
  /// }
  /// \public
  using FindOfInitializerListClient::findLastNotOf;

  /// \inherit findAllNotOf ( InitializerList ) call, returning mutable iterators, inherited from FindOfInitializerListClient interface
  /// \test Suite: MCTS-00001, Group: MCTG-00700-FO, Test Cases: {
  ///      MCTC-00759-FO-findAllNotOfStoreInMatchingNone [-InitializerList Group],
  ///      MCTC-00760-FO-findAllNotOfStoreInMatchingOne [-InitializerList Group],
  ///      MCTC-00761-FO-findAllNotOfStoreInMatchingMore [-InitializerList Group],
  ///      MCTC-00762-FO-findAllNotOfStoreInMatchingAll [-InitializerList Group],
  ///      MCTC-00763-FO-findAllNotOfStoreInMatchingAllAndMore [-InitializerList Group],
  ///      MCTC-00764-FO-findAllNotOfReturnedMatchingNone [-InitializerList Group],
  ///      MCTC-00765-FO-findAllNotOfReturnedMatchingOne [-InitializerList Group],
  ///      MCTC-00766-FO-findAllNotOfReturnedMatchingMore [-InitializerList Group],
  ///      MCTC-00767-FO-findAllNotOfReturnedMatchingAll [-InitializerList Group],
  ///      MCTC-00768-FO-findAllNotOfReturnedMatchingAllAndMore [-InitializerList Group]
  /// }
  /// \public
  using FindOfInitializerListClient::findAllNotOf;


  /// \inherit findThat ( Predicate ) returning Const Iterators, inherited from Collection base class
  /// \test Not Applicable, import of tested functionality.
  /// \public
  using CollectionBase::findThat;

  /// \inherit findFirstThat ( Predicate ) returning Const Iterators, inherited from Collection base class
  /// \test Not Applicable, import of tested functionality.
  /// \public
  using CollectionBase::findFirstThat;

  /// \inherit findLastThat ( Predicate ) returning Const Iterators, inherited from Collection base class
  /// \test Not Applicable, import of tested functionality.
  /// \public
  using CollectionBase::findLastThat;

  /// \inherit findAllThat ( Predicate ) returning Const Iterators, inherited from Collection base class
  /// \test Not Applicable, import of tested functionality.
  /// \public
  using CollectionBase::findAllThat;


  /// \inherit findThat ( Predicate ) call, returning mutable iterators, inherited from FindByClient interface
  /// \test Suite: MCTS-00001, Group: MCTG-00600-FT, Test Cases: {
  ///      MCTC-00601-FT-findThatStoreInMatchingNone,
  ///      MCTC-00602-FT-findThatStoreInMatchingOne,
  ///      MCTC-00603-FT-findThatStoreInMatchingMoreLessThanLimit,
  ///      MCTC-00604-FT-findThatStoreInMatchingMore,
  ///      MCTC-00605-FT-findThatStoreInMatchingMoreMoreThanLimit,
  ///      MCTC-00606-FT-findThatStoreInMatchingAll,
  ///      MCTC-00607-FT-findThatStoreInMatchingAllAndMore,
  ///      MCTC-00608-FT-findThatReturnedMatchingNone,
  ///      MCTC-00609-FT-findThatReturnedMatchingOne,
  ///      MCTC-00610-FT-findThatReturnedMatchingMoreLessThanLimit,
  ///      MCTC-00611-FT-findThatReturnedMatchingMore,
  ///      MCTC-00612-FT-findThatReturnedMatchingMoreMoreThanLimit,
  ///      MCTC-00613-FT-findThatReturnedMatchingAll,
  ///      MCTC-00614-FT-findThatReturnedMatchingAllAndMore
  /// }
  /// \test Suite: MCTS-00001, Group: MCTG-00650-FTMF, Test Cases: {
  ///      MCTC-00651-FTMF-findThatStoreInMemberFunction,
  ///      MCTC-00652-FTMF-findThatReturnedMemberFunction
  /// }
  /// \public
  using FindByClient::findThat;

  /// \inherit findFirstThat ( Predicate ) call, returning mutable iterators, inherited from FindByClient interface
  /// \test Suite: MCTS-00001, Group: MCTG-00600-FT, Test Cases: {
  ///      MCTC-00615-FT-findFirstThatMatchingNone,
  ///      MCTC-00616-FT-findFirstThatMatchingOne,
  ///      MCTC-00617-FT-findFirstThatMatchingMore,
  ///      MCTC-00618-FT-findFirstThatMatchingAll,
  ///      MCTC-00619-FT-findFirstThatMatchingAllAndMore
  /// }
  /// \test Suite: MCTS-00001, Group: MCTG-00650-FTMF, Test Cases: {
  ///      MCTC-00653-FTMF-findFirstThatMemberFunction
  /// }
  /// \public
  using FindByClient::findFirstThat;

  /// \inherit findLastThat ( Predicate ) call, returning mutable iterators, inherited from FindByClient interface
  /// \test Suite: MCTS-00001, Group: MCTG-00600-FT, Test Cases: {
  ///      MCTC-00620-FT-findLastThatMatchingNone,
  ///      MCTC-00621-FT-findLastThatMatchingOne,
  ///      MCTC-00622-FT-findLastThatMatchingMore,
  ///      MCTC-00623-FT-findLastThatMatchingAll,
  ///      MCTC-00624-FT-findLastThatMatchingAllAndMore
  /// }
  /// \test Suite: MCTS-00001, Group: MCTG-00650-FTMF, Test Cases: {
  ///      MCTC-00654-FTMF-findLastThatMemberFunction
  /// }
  /// \public
  using FindByClient::findLastThat;

  /// \inherit findAllThat ( Predicate ) call, returning mutable iterators, inherited from FindByClient interface
  /// \test Suite: MCTS-00001, Group: MCTG-00600-FT, Test Cases: {
  ///      MCTC-00625-FT-findAllThatStoreInMatchingNone,
  ///      MCTC-00626-FT-findAllThatStoreInMatchingOne,
  ///      MCTC-00627-FT-findAllThatStoreInMatchingMore,
  ///      MCTC-00628-FT-findAllThatStoreInMatchingAll,
  ///      MCTC-00629-FT-findAllThatStoreInMatchingAllAndMore,
  ///      MCTC-00630-FT-findAllThatReturnedMatchingNone,
  ///      MCTC-00631-FT-findAllThatReturnedMatchingOne,
  ///      MCTC-00632-FT-findAllThatReturnedMatchingMore,
  ///      MCTC-00633-FT-findAllThatReturnedMatchingAll,
  ///      MCTC-00634-FT-findAllThatReturnedMatchingAllAndMore
  /// }
  /// \test Suite: MCTS-00001, Group: MCTG-00650-FTMF, Test Cases: {
  ///      MCTC-00655-FTMF-findAllThatStoreInMemberFunction,
  ///      MCTC-00656-FTMF-findAllThatReturnedMemberFunction
  /// }
  /// \public
  using FindByClient::findAllThat;

  /// \inherit insert ( copy / move ) call, inherited from RandomInsertionClient interface
  /// \test Suite: MCTS-00001, Group: MCTG-00800-RI, Test Cases: {
  ///      MCTC-00801-RI-insertByCopy,
  ///      MCTC-00802-RI-insertByMove
  /// }
  /// \public
  using RandomInsertionClient::insert;

  /// \inherit insertAll ( pack ) call, inherited from RandomInsertionClient interface
  /// \test Suite: MCTS-00001, Group: MCTG-00800-RI, Test Cases: {
  ///      MCTC-00804-RI-insertByPack
  /// }
  /// \public
  using RandomInsertionClient::insertAll;

  /// \inherit insertAllOf ( begin + end / iterable / initializer_list ) call, inherited from RandomInsertionClient interface
  /// \test Suite: MCTS-00001, Group: MCTG-00800-RI, Test Cases: {
  ///      MCTC-00805-RI-insertByInsertAllIterable,
  ///      MCTC-00806-RI-insertByInsertAllList,
  ///      MCTC-00807-RI-insertByRange1,
  ///      MCTC-00808-RI-insertByRange2,
  ///      MCTC-00809-RI-insertByRange3
  /// }
  /// \public
  using RandomInsertionClient::insertAllOf;

  /// \inherit add ( copy / move ) call, inherited from RandomInsertionClient interface
  /// \deprecated 'MutableCollection::add' has been deprecated. Use 'MutableCollection::insert' instead
  /// \test Not Applicable
  /// \public
  using RandomInsertionClient::add;

  /// \inherit addAll ( pack ) call, inherited from RandomInsertionClient interface
  /// \deprecated 'MutableCollection::addAll' has been deprecated. Use 'MutableCollection::insertAll' instead
  /// \test Not Applicable
  /// \public
  using RandomInsertionClient::addAll;

  /// \inherit addAllOf ( begin + end / iterable / initializer_list ) call, inherited from RandomInsertionClient interface
  /// \deprecated 'MutableCollection::addAllOf' has been deprecated. Use 'MutableCollection::insertAllOf' instead
  /// \test Not Applicable
  /// \public
  using RandomInsertionClient::addAllOf;

  /// \inherit emplace ( forwarded arguments ) call, inherited from RandomInsertionClient interface
  /// \test Suite: MCTS-00001, Group: MCTG-00800-RI, Test Cases: {
  ///      MCTC-00803-RI-insertByEmplace
  /// }
  /// \public
  using RandomInsertionClient::emplace;

  /// \brief String conversion function, used to obtain String representation of the Collection
  /// \exceptsafe
  /// \return String = string representation
  /// \test Suite: MCTS-00001, Group: MCTG-00002-MF, Test Cases: { MCTC-00003-MF-toString, MCTC-00004-MF-clear }
  /// \public
  __CDS_NoDiscard auto toString () const noexcept(false) -> String override;

  /// \brief Function used to clear the collection, removing all elements from it
  /// \exceptsafe
  /// \test Suite: MCTS-00001, Group: MCTG-00002-MF, Test Cases: { MCTC-00004-MF-clear }
  /// \public
  auto clear () noexcept -> void override = 0;

protected:
  /// \brief Default Constructor
  /// \exceptsafe
  /// \test Suite: MCTS-00001, Group: All - requirement for running, Test Cases: All - requirement for running
  /// \protected
  constexpr MutableCollection () noexcept;

  /// \brief Copy Constructor
  /// \param [in] collection : MutableCollection cref = Constant Reference to a mutable collection to copy data from
  /// \exceptsafe
  /// \test Suite: MCTS-00001, Group: All - requirement for running, Test Cases: All - requirement for running
  /// \protected
  constexpr MutableCollection (MutableCollection const& collection) noexcept;

  /// \brief Move Constructor
  /// \param [in] collection : MutableCollection mref = Move Reference to a mutable collection to acquire and release the data from
  /// \exceptsafe
  /// \test Suite: MCTS-00001, Group: All - requirement for running, Test Cases: All - requirement for running
  /// \protected
  constexpr MutableCollection (MutableCollection&& collection) noexcept;
};

} // namespace cds

#include "mutableCollection/impl/MutableCollectionImpl.hpp"

#include "../../shared/iterableInternalCommunication/client/primitive/impl/DelegateForwardIterablePrimitiveClientImpl.hpp"
#include "../../shared/iterableInternalCommunication/client/primitive/impl/IteratorRemovePrimitiveClientImpl.hpp"

#include "../../shared/iterableInternalCommunication/client/composite/impl/GenericMutableStatementsCompositeClientImpl.hpp" // NOLINT(llvm-include-order)
#include "../../shared/iterableInternalCommunication/client/composite/impl/FindOfMutableCompositeClientImpl.hpp"
#include "../../shared/iterableInternalCommunication/client/composite/impl/FindByMutableCompositeClientImpl.hpp"

#endif // __CDS_MUTABLE_COLLECTION_HPP__
