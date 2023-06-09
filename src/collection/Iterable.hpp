//
// Created by loghin on 30/10/22.
//

#ifndef __CDS_ITERABLE_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_ITERABLE_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

#include <CDS/Object>                                                                                                   // NOLINT(llvm-header-guard)
#include <CDS/FunctionalInterface>
#include <CDS/Utility>

#include "../shared/memory/PrimitiveAllocation.hpp"

#include "iterable/IterableFunctions.hpp"

#include "../shared/delegateIterator/ForwardDelegateWrapperIterator.hpp"

#include "../shared/iterableInternalCommunication/channel/IterableInternalCommunicationChannel.hpp"

#include "../shared/iterableInternalCommunication/client/primitive/DelegateForwardConstIterablePrimitiveClient.hpp"     // NOLINT(llvm-header-guard)

#include "../shared/iterableInternalCommunication/client/composite/ContainsOfCompositeClient.hpp"
#include "../shared/iterableInternalCommunication/client/composite/FindOfImmutableCompositeClient.hpp"                  // NOLINT(llvm-header-guard)
#include "../shared/iterableInternalCommunication/client/composite/FindByImmutableCompositeClient.hpp"
#include "../shared/iterableInternalCommunication/client/composite/GenericImmutableStatementsCompositeClient.hpp"

#include "iterable/IterableConstructs.hpp"

namespace cds { // NOLINT(modernize-concat-nested-namespaces)

/// \class Abstract Object representing any Iterable Sequence / immutable Container of given elements, potentially infinite
/// \tparam __ElementType is the type of elements contained into Iterable
///
/// \extends [public]            __IterableCommunicationChannel - Base class used to communicate requests from Abstract Iterable to Derived Iterables
/// \extends [public,implicit]   Object - base cds Class, inherited from __IterableCommunicationChannel
/// \extends [protected]         __IterableFunctions - container for statically stored equals function
///
/// \implements [public]         __IterableDelegateForwardConstIterableClient - Abstract Iterator Request Client - begin / end / cbegin / cend
/// \implements [public]         __IterableContainsOfIterableClient - Contains Functions for Iterable parameter Client - containsAnyOf / containsAllOf / containsAnyOf / containsAnyNotOf
/// \implements [public]         __IterableContainsOfInitializerListClient - Contains Functions for std::initializer_list parameter Client - containsAnyOf / containsAllOf / containsAnyOf / containsAnyNotOf
/// \implements [public]         __IterableFindOfIterableClient - Find Of Functions for Iterable parameter Client - findOf / findFirstOf / findLastOf / findAllOf / findNotOf / findFirstNotOf / findLastNotOf / findAllNotOf
/// \implements [public]         __IterableFindOfInitializerListClient - Find Of Functions for std::initializer_list parameter Client - findOf / findFirstOf / findLastOf / findAllOf / findNotOf / findFirstNotOf / findLastNotOf / findAllNotOf
/// \implements [public]         __IterableFindByClient - Find By Functions for Predicates Client - findThat / findFirstThat / findLastThat / findAllThat
/// \implements [public]         __IterableGenericStatementsClient - Generic Functional Statements for Predicates - forEach / some / atLeast / atMost / moreThat / fewerThan / count / any / all / none
///
/// \test Suite: CTS-00001, Group: All - requirement for running, Test Cases: All - requirement for running
/// \namespace cds
/// \public
template < typename __ElementType > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
class __CDS_InheritsEBOs Iterable : // NOLINT(*-virtual-class-destructor)
    public __hidden::__impl::__IterableCommunicationChannel <__ElementType>,
    public __hidden::__impl::__IterableDelegateForwardConstIterableClient <__ElementType>,
    public __hidden::__impl::__IterableContainsOfIterableClient <__ElementType>,
    public __hidden::__impl::__IterableContainsOfInitializerListClient <__ElementType>,
    public __hidden::__impl::__IterableFindOfIterableClient <__ElementType>,
    public __hidden::__impl::__IterableFindOfInitializerListClient <__ElementType>,
    public __hidden::__impl::__IterableFindByClient <__ElementType>,
    public __hidden::__impl::__IterableGenericStatementsClient <__ElementType>,
    protected __hidden::__impl::__IterableFunctions <__ElementType> {
protected:  /// \typedef protected alias for __IterableCommunicationChannel base interface - providing communication channel abstract functions __cicch_obtainGenericHandler / __cicch_obtainGenericConstHandler
  /// \protected
  using CommunicationChannel                  = __hidden::__impl::__IterableCommunicationChannel <__ElementType>;

  /// \typedef protected alias for __IterableDelegateForwardConstIterableClient base interface - providing begin / end / cbegin / cend for Abstract Iterators
  /// \protected
  using DelegateForwardConstIterableClient    = __hidden::__impl::__IterableDelegateForwardConstIterableClient <__ElementType>;

  /// \typedef protected alias for __IterableContainsOfIterableClient base interface - providing contains-of functions with a Iterable parameter - containsAnyOf / containsAllOf / containsAnyOf / containsAnyNotOf
  /// \protected
  using ContainsOfIterableClient              = __hidden::__impl::__IterableContainsOfIterableClient <__ElementType>;

  /// \typedef protected alias for __IterableContainsOfInitializerListClient base interface - providing contains-of functions with a std::initializer_list parameter - containsAnyOf / containsAllOf / containsAnyOf / containsAnyNotOf
  /// \protected
  using ContainsOfInitializerListClient       = __hidden::__impl::__IterableContainsOfInitializerListClient <__ElementType>;

  /// \typedef protected alias for __IterableFindOfIterableClient base interface - providing find-of functions with a Iterable parameter - findOf / findFirstOf / findLastOf / findAllOf / findNotOf / findFirstNotOf / findLastNotOf / findAllNotOf
  /// \protected
  using FindOfIterableClient                  = __hidden::__impl::__IterableFindOfIterableClient <__ElementType>;

  /// \typedef protected alias for __IterableFindOfInitializerListClient base interface - providing find-of functions with a std::initializer_list parameter - findOf / findFirstOf / findLastOf / findAllOf / findNotOf / findFirstNotOf / findLastNotOf / findAllNotOf
  /// \protected
  using FindOfInitializerListClient           = __hidden::__impl::__IterableFindOfInitializerListClient <__ElementType>;

  /// \typedef protected alias for __IterableFindByClient base interface - providing find-by-predicate functions - findThat / findFirstThat / findLastThat / findAllThat
  /// \protected
  using FindByClient                          = __hidden::__impl::__IterableFindByClient <__ElementType>;

  /// \typedef protected alias for __IterableGenericStatementsClient base interface - providing functional-predicate functions - forEach / some / atLeast / atMost / moreThat / fewerThan / count / any / all / none
  /// \protected
  using GenericStatementsClient               = __hidden::__impl::__IterableGenericStatementsClient <__ElementType>;

public:
  /// \typedef public alias for __ElementType, the type of the contained elements,
  /// publicly accessible, useful in sfinae statements - decltype ( Iterable )::ElementType
  /// \public
  using ElementType                           = __ElementType;

  /// \typedef The Const Iterator Type, imported from Abstract Forward Iterator Client
  /// \public
  using ConstIterator                         = typename DelegateForwardConstIterableClient::ConstIterator;

  /// \brief Destructor
  /// \exceptsafe
  /// \test Suite: CTS-00001, Group: All - requirement for running, Test Cases: All - requirement for running
  /// \public
  __CDS_cpplang_ConstexprDestructor ~Iterable() noexcept override;

  /// \brief Deleted Copy Assignment Operator
  /// \param [in] iterable : Iterable cref = Constant Reference to an iterable to copy data from
  /// \exceptsafe
  /// \return Iterable ref = Reference to the modified object
  ///
  /// \test N/A
  /// \public
  auto operator = (Iterable const&) noexcept -> Iterable& = delete;

  /// \brief Deleted Move Assignment Operator
  /// \param [in, out] iterable : Iterable mref = Move Reference to an iterable to move data from
  /// \exceptsafe
  /// \return Iterable ref = Reference to the modified object
  ///
  /// \test N/A
  /// \public
  auto operator = (Iterable&&) noexcept -> Iterable& = delete;
  
  /// \inherit begin function inherited from DelegateForwardConstIterableClient interface.
  /// \test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: { CTC-00051-IT-range, CTC-00052-IT-begin_end,
  ///      CTC-00054-IT-e_begin_end, CTC-00056-IT-e_emptyRange }
  /// \public
  using DelegateForwardConstIterableClient::begin;

  /// \inherit end function inherited from DelegateForwardConstIterableClient interface.
  /// \test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: { CTC-00051-IT-range, CTC-00052-IT-begin_end,
  ///      CTC-00054-IT-e_begin_end, CTC-00056-IT-e_emptyRange }
  /// \public
  using DelegateForwardConstIterableClient::end;

  /// \inherit cbegin function inherited from DelegateForwardConstIterableClient interface.
  /// \test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: { CTC-00051-IT-range, CTC-00053-IT-cbegin_cend,
  ///      CTC-00055-IT-e_cbegin_cend, CTC-00056-IT-e_emptyRange }
  /// \public
  using DelegateForwardConstIterableClient::cbegin;

  /// \inherit cend function inherited from DelegateForwardConstIterableClient interface.
  /// \test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: { CTC-00051-IT-range, CTC-00053-IT-cbegin_cend,
  ///      CTC-00055-IT-e_cbegin_cend, CTC-00056-IT-e_emptyRange }
  /// \public
  using DelegateForwardConstIterableClient::cend;

  /// \inherit forEach functional call, inherited from GenericStatementsClient interface
  /// \test Suite: CTS-00001, Group: CTG-00100-FS, Test Cases: { CTC-00139-FS-forEachCount }
  /// \test Suite: CTS-00001, Group: CTG-00200-FSMF, Test Cases: { CTC-00201-FSMF-forEach }
  /// \public
  using GenericStatementsClient::forEach;

  /// \inherit some functional call, inherited from GenericStatementsClient interface
  /// \test Suite: CTS-00001, Group: CTG-00100-FS, Test Cases: { CTC-00136-FS-someExact, CTC-00137-FS-someLessFalse, CTC-00138-someMoreFalse }
  /// \test Suite: CTS-00001, Group: CTG-00200-FSMF, Test Cases: { CTC-00202-FSMF-someEqual, CTC-00203-FSMF-someLess, CTC-00204-someMore }
  /// \public
  using GenericStatementsClient::some;

  /// \inherit atLeast functional call, inherited from GenericStatementsClient interface
  /// \test Suite: CTS-00001, Group: CTG-00100-FS, Test Cases: { CTC-00132-FS-atLeastTrue, CTC-00133-FS-atLeastCloseTrue, CTC-00134-atLeastCloseFalse, CTC-00135-atLeastFalse }
  /// \test Suite: CTS-00001, Group: CTG-00200-FSMF, Test Cases: { CTC-00205-FSMF-atLeast, CTC-00206-FSMF-atLeastLess, CTC-00207-atLeastMore }
  /// \public
  using GenericStatementsClient::atLeast;

  /// \inherit atMost functional call, inherited from GenericStatementsClient interface
  /// \test Suite: CTS-00001, Group: CTG-00100-FS, Test Cases: { CTC-00128-FS-atMostTrue, CTC-00129-FS-atMostCloseTrue, CTC-00130-atMostCloseFalse, CTC-00131-atMostFalse }
  /// \test Suite: CTS-00001, Group: CTG-00200-FSMF, Test Cases: { CTC-00208-FSMF-atMost, CTC-00209-FSMF-atMostLess, CTC-00210-atMostMore }
  /// \public
  using GenericStatementsClient::atMost;

  /// \inherit moreThan functional call, inherited from GenericStatementsClient interface
  /// \test Suite: CTS-00001, Group: CTG-00100-FS, Test Cases: { CTC-00123-FS-moreThanTrue, CTC-00124-FS-moreThanCloseTrue, CTC-00125-moreThanCloseFalse, CTC-00126-moreThanFalse, CTC-00127-moreThanCompletelyFalse }
  /// \test Suite: CTS-00001, Group: CTG-00200-FSMF, Test Cases: { CTC-00211-FSMF-moreThan, CTC-00212-FSMF-moreThanLess, CTC-00213-moreThanMore }
  /// \public
  using GenericStatementsClient::moreThan;

  /// \inherit fewerThan functional call, inherited from GenericStatementsClient interface
  /// \test Suite: CTS-00001, Group: CTG-00100-FS, Test Cases: { CTC-00118-FS-fewerThanTrue, CTC-00119-FS-fewerThanCloseTrue, CTC-00120-fewerThanCloseFalse, CTC-00121-fewerThanFalse, CTC-00122-fewerThanCompletelyFalse }
  /// \test Suite: CTS-00001, Group: CTG-00200-FSMF, Test Cases: { CTC-00214-FSMF-fewerThan, CTC-00215-FSMF-fewerThanLess, CTC-00216-fewerThanMore }
  /// \public
  using GenericStatementsClient::fewerThan;

  /// \inherit count functional call, inherited from GenericStatementsClient interface
  /// \test Suite: CTS-00001, Group: CTG-00100-FS, Test Cases: { CTC-00113-FS-countProp1, CTC-00114-FS-countProp2, CTC-00115-countProp3, CTC-00116-countProp4, CTC-00117-countPropLbd }
  /// \test Suite: CTS-00001, Group: CTG-00200-FSMF, Test Cases: { CTC-00217-FSMF-countExact }
  /// \public
  using GenericStatementsClient::count;

  /// \inherit any functional call, inherited from GenericStatementsClient interface
  /// \test Suite: CTS-00001, Group: CTG-00100-FS, Test Cases: { CTC-00101-FS-anyNone, CTC-00102-FS-anyOne, CTC-00103-anyMore, CTC-00104-anyAll }
  /// \test Suite: CTS-00001, Group: CTG-00200-FSMF, Test Cases: { CTC-00218-FSMF-anyNone, CTC-00219-FSMF-anyOne, CTC-00220-anyMore, CTC-00221-anyAll }
  /// \public
  using GenericStatementsClient::any;

  /// \inherit all functional call, inherited from GenericStatementsClient interface
  /// \test Suite: CTS-00001, Group: CTG-00100-FS, Test Cases: { CTC-00105-FS-allNone, CTC-00106-FS-allOne, CTC-00107-allMore, CTC-00108-allAll }
  /// \test Suite: CTS-00001, Group: CTG-00200-FSMF, Test Cases: { CTC-00222-FSMF-allNone, CTC-00223-FSMF-allOne, CTC-00224-allMore, CTC-00225-allAll }
  /// \public
  using GenericStatementsClient::all;

  /// \inherit none functional call, inherited from GenericStatementsClient interface
  /// \test Suite: CTS-00001, Group: CTG-00100-FS, Test Cases: { CTC-00109-FS-noneNone, CTC-00110-FS-noneOne, CTC-00111-noneMore, CTC-00112-noneAll }
  /// \test Suite: CTS-00001, Group: CTG-00200-FSMF, Test Cases: { CTC-00226-FSMF-noneNone, CTC-00227-FSMF-noneOne, CTC-00228-noneMore, CTC-00229-noneAll }
  /// \public
  using GenericStatementsClient::none;

  /// \inherit containsAnyOf ( Iterable ) call, inherited from ContainsOfIterableClient interface
  /// \test Suite: CTS-00001, Group: CTG-00300-CO, Test Cases: {
  ///      CTC-00301-CO-containsAnyOfCollectionNoneCommon [-Collection Group],
  ///      CTC-00302-CO-containsAnyOfCollectionOneCommon [-Collection Group],
  ///      CTC-00303-CO-containsAnyOfCollectionMoreCommon [-Collection Group],
  ///      CTC-00304-CO-containsAnyOfCollectionAllCommon [-Collection Group],
  ///      CTC-00305-CO-containsAnyOfCollectionAllCommonAndMore [-Collection Group]
  /// }
  /// \public
  using ContainsOfIterableClient::containsAnyOf;

  /// \inherit containsAllOf ( Iterable ) call, inherited from ContainsOfCollectionClient interface
  /// \test Suite: CTS-00001, Group: CTG-00300-CO, Test Cases: {
  ///      CTC-00306-CO-containsAllOfCollectionNoneCommon [-Collection Group],
  ///      CTC-00307-CO-containsAllOfCollectionOneCommon [-Collection Group],
  ///      CTC-00308-CO-containsAllOfCollectionMoreCommon [-Collection Group],
  ///      CTC-00309-CO-containsAllOfCollectionAllCommon [-Collection Group],
  ///      CTC-00310-CO-containsAllOfCollectionAllCommonAndMore [-Collection Group]
  /// }
  /// \public
  using ContainsOfIterableClient::containsAllOf;

  /// \inherit containsAnyNotOf ( Iterable ) call, inherited from ContainsOfCollectionClient interface
  /// \test Suite: CTS-00001, Group: CTG-00300-CO, Test Cases: {
  ///      CTC-00311-CO-containsAnyNotOfCollectionNoneCommon [-Collection Group],
  ///      CTC-00312-CO-containsAnyNotOfCollectionOneCommon [-Collection Group],
  ///      CTC-00313-CO-containsAnyNotOfCollectionMoreCommon [-Collection Group],
  ///      CTC-00314-CO-containsAnyNotOfCollectionAllCommon [-Collection Group],
  ///      CTC-00315-CO-containsAnyNotOfCollectionAllCommonAndMore [-Collection Group]
  /// }
  /// \public
  using ContainsOfIterableClient::containsAnyNotOf;

  /// \inherit containsNoneOf ( Iterable ) call, inherited from ContainsOfCollectionClient interface
  /// \test Suite: CTS-00001, Group: CTG-00300-CO, Test Cases: {
  ///      CTC-00316-CO-containsNoneOfCollectionNoneCommon [-Collection Group],
  ///      CTC-00317-CO-containsNoneOfCollectionOneCommon [-Collection Group],
  ///      CTC-00318-CO-containsNoneOfCollectionMoreCommon [-Collection Group],
  ///      CTC-00319-CO-containsNoneOfCollectionAllCommon [-Collection Group],
  ///      CTC-00320-CO-containsNoneOfCollectionAllCommonAndMore [-Collection Group]
  /// }
  /// \public
  using ContainsOfIterableClient::containsNoneOf;

  /// \inherit containsAnyOf ( std::initializer_list ) call, inherited from ContainsOfInitializerListClient interface
  /// \test Suite: CTS-00001, Group: CTG-00300-CO, Test Cases: {
  ///      CTC-00301-CO-containsAnyOfCollectionNoneCommon [-InitializerList Group],
  ///      CTC-00302-CO-containsAnyOfCollectionOneCommon [-InitializerList Group],
  ///      CTC-00303-CO-containsAnyOfCollectionMoreCommon [-InitializerList Group],
  ///      CTC-00304-CO-containsAnyOfCollectionAllCommon [-InitializerList Group],
  ///      CTC-00305-CO-containsAnyOfCollectionAllCommonAndMore [-InitializerList Group]
  /// }
  /// \public
  using ContainsOfInitializerListClient::containsAnyOf;

  /// \inherit containsAllOf ( std::initializer_list ) call, inherited from ContainsOfInitializerListClient interface
  /// \test Suite: CTS-00001, Group: CTG-00300-CO, Test Cases: {
  ///      CTC-00306-CO-containsAllOfCollectionNoneCommon [-InitializerList Group],
  ///      CTC-00307-CO-containsAllOfCollectionOneCommon [-InitializerList Group],
  ///      CTC-00308-CO-containsAllOfCollectionMoreCommon [-InitializerList Group],
  ///      CTC-00309-CO-containsAllOfCollectionAllCommon [-InitializerList Group],
  ///      CTC-00310-CO-containsAllOfCollectionAllCommonAndMore [-InitializerList Group]
  /// }
  /// \public
  using ContainsOfInitializerListClient::containsAllOf;

  /// \inherit containsAnyNotOf ( std::initializer_list ) call, inherited from ContainsOfInitializerListClient interface
  /// \test Suite: CTS-00001, Group: CTG-00300-CO, Test Cases: {
  ///      CTC-00311-CO-containsAnyNotOfCollectionNoneCommon [-InitializerList Group],
  ///      CTC-00312-CO-containsAnyNotOfCollectionOneCommon [-InitializerList Group],
  ///      CTC-00313-CO-containsAnyNotOfCollectionMoreCommon [-InitializerList Group],
  ///      CTC-00314-CO-containsAnyNotOfCollectionAllCommon [-InitializerList Group],
  ///      CTC-00315-CO-containsAnyNotOfCollectionAllCommonAndMore [-InitializerList Group]
  /// }
  /// \public
  using ContainsOfInitializerListClient::containsAnyNotOf;

  /// \inherit containsNoneOf ( std::initializer_list ) call, inherited from ContainsOfInitializerListClient interface
  /// \test Suite: CTS-00001, Group: CTG-00300-CO, Test Cases: {
  ///      CTC-00316-CO-containsNoneOfCollectionNoneCommon [-InitializerList Group],
  ///      CTC-00317-CO-containsNoneOfCollectionOneCommon [-InitializerList Group],
  ///      CTC-00318-CO-containsNoneOfCollectionMoreCommon [-InitializerList Group],
  ///      CTC-00319-CO-containsNoneOfCollectionAllCommon [-InitializerList Group],
  ///      CTC-00320-CO-containsNoneOfCollectionAllCommonAndMore [-InitializerList Group]
  /// }
  /// \public
  using ContainsOfInitializerListClient::containsNoneOf;

  /// \inherit findThat ( Predicate ) call, inherited from FindByClient interface
  /// \test Suite: CTS-00001, Group: CTG-00600-FT, Test Cases: {
  ///      CTC-00601-FT-findThatStoreInMatchingNone,
  ///      CTC-00602-FT-findThatStoreInMatchingOne,
  ///      CTC-00603-FT-findThatStoreInMatchingMoreLessThanLimit,
  ///      CTC-00604-FT-findThatStoreInMatchingMore,
  ///      CTC-00605-FT-findThatStoreInMatchingMoreMoreThanLimit,
  ///      CTC-00606-FT-findThatStoreInMatchingAll,
  ///      CTC-00607-FT-findThatStoreInMatchingAllAndMore,
  ///      CTC-00608-FT-findThatReturnedMatchingNone,
  ///      CTC-00609-FT-findThatReturnedMatchingOne,
  ///      CTC-00610-FT-findThatReturnedMatchingMoreLessThanLimit,
  ///      CTC-00611-FT-findThatReturnedMatchingMore,
  ///      CTC-00612-FT-findThatReturnedMatchingMoreMoreThanLimit,
  ///      CTC-00613-FT-findThatReturnedMatchingAll,
  ///      CTC-00614-FT-findThatReturnedMatchingAllAndMore
  /// }
  /// \test Suite: CTS-00001, Group: CTG-00650-FTMF, Test Cases: {
  ///      CTC-00651-FTMF-findThatStoreInMemberFunction,
  ///      CTC-00652-FTMF-findThatReturnedMemberFunction
  /// }
  /// \public
  using FindByClient::findThat;

  /// \inherit findFirstThat ( Predicate ) call, inherited from FindByClient interface
  /// \test Suite: CTS-00001, Group: CTG-00600-FT, Test Cases: {
  ///      CTC-00615-FT-findFirstThatMatchingNone,
  ///      CTC-00616-FT-findFirstThatMatchingOne,
  ///      CTC-00617-FT-findFirstThatMatchingMore,
  ///      CTC-00618-FT-findFirstThatMatchingAll,
  ///      CTC-00619-FT-findFirstThatMatchingAllAndMore
  /// }
  /// \test Suite: CTS-00001, Group: CTG-00650-FTMF, Test Cases: {
  ///      CTC-00653-FTMF-findFirstThatMemberFunction
  /// }
  /// \public
  using FindByClient::findFirstThat;

  /// \inherit findLastThat ( Predicate ) call, inherited from FindByClient interface
  /// \test Suite: CTS-00001, Group: CTG-00600-FT, Test Cases: {
  ///      CTC-00620-FT-findLastThatMatchingNone,
  ///      CTC-00621-FT-findLastThatMatchingOne,
  ///      CTC-00622-FT-findLastThatMatchingMore,
  ///      CTC-00623-FT-findLastThatMatchingAll,
  ///      CTC-00624-FT-findLastThatMatchingAllAndMore
  /// }
  /// \test Suite: CTS-00001, Group: CTG-00650-FTMF, Test Cases: {
  ///      CTC-00654-FTMF-findLastThatMemberFunction
  /// }
  /// \public
  using FindByClient::findLastThat;

  /// \inherit findAllThat ( Predicate ) call, inherited from FindByClient interface
  /// \test Suite: CTS-00001, Group: CTG-00600-FT, Test Cases: {
  ///      CTC-00625-FT-findAllThatStoreInMatchingNone,
  ///      CTC-00626-FT-findAllThatStoreInMatchingOne,
  ///      CTC-00627-FT-findAllThatStoreInMatchingMore,
  ///      CTC-00628-FT-findAllThatStoreInMatchingAll,
  ///      CTC-00629-FT-findAllThatStoreInMatchingAllAndMore,
  ///      CTC-00630-FT-findAllThatReturnedMatchingNone,
  ///      CTC-00631-FT-findAllThatReturnedMatchingOne,
  ///      CTC-00632-FT-findAllThatReturnedMatchingMore,
  ///      CTC-00633-FT-findAllThatReturnedMatchingAll,
  ///      CTC-00634-FT-findAllThatReturnedMatchingAllAndMore
  /// }
  /// \test Suite: CTS-00001, Group: CTG-00650-FTMF, Test Cases: {
  ///      CTC-00655-FTMF-findAllThatStoreInMemberFunction,
  ///      CTC-00656-FTMF-findAllThatReturnedMemberFunction
  /// }
  /// \public
  using FindByClient::findAllThat;

  /// \inherit findOf ( Iterable ) call, inherited from FindOfIterableClient interface
  /// \test Suite: CTS-00001, Group: CTG-00700-FO, Test Cases: {
  ///      CTC-00701-FO-findOfStoreInMatchingNone [-Collection Group],
  ///      CTC-00702-FO-findOfStoreInMatchingOne [-Collection Group],
  ///      CTC-00703-FO-findOfStoreInMatchingMoreLessThanLimit [-Collection Group],
  ///      CTC-00704-FO-findOfStoreInMatchingMore [-Collection Group],
  ///      CTC-00705-FO-findOfStoreInMatchingMoreMoreThanLimit [-Collection Group],
  ///      CTC-00706-FO-findOfStoreInMatchingAll [-Collection Group],
  ///      CTC-00707-FO-findOfStoreInMatchingAllAndMore [-Collection Group],
  ///      CTC-00708-FO-findOfReturnedMatchingNone [-Collection Group],
  ///      CTC-00709-FO-findOfReturnedMatchingOne [-Collection Group],
  ///      CTC-00710-FO-findOfReturnedMatchingMoreLessThanLimit [-Collection Group],
  ///      CTC-00711-FO-findOfReturnedMatchingMore [-Collection Group],
  ///      CTC-00712-FO-findOfReturnedMatchingMoreMoreThanLimit [-Collection Group],
  ///      CTC-00713-FO-findOfReturnedMatchingAll [-Collection Group],
  ///      CTC-00714-FO-findOfReturnedMatchingAllAndMore [-Collection Group]
  /// }
  /// \public
  using FindOfIterableClient::findOf;

  /// \inherit findFirstOf ( Iterable ) call, inherited from FindOfIterableClient interface
  /// \test Suite: CTS-00001, Group: CTG-00700-FO, Test Cases: {
  ///      CTC-00715-FO-findFirstOfMatchingNone [-Collection Group],
  ///      CTC-00716-FO-findFirstOfMatchingOne [-Collection Group],
  ///      CTC-00717-FO-findFirstOfMatchingMore [-Collection Group],
  ///      CTC-00718-FO-findFirstOfMatchingAll [-Collection Group],
  ///      CTC-00719-FO-findFirstOfMatchingAllAndMore [-Collection Group]
  /// }
  /// \public
  using FindOfIterableClient::findFirstOf;

  /// \inherit findLastOf ( Iterable ) call, inherited from FindOfIterableClient interface
  /// \test Suite: CTS-00001, Group: CTG-00700-FO, Test Cases: {
  ///      CTC-00720-FO-findLastOfMatchingNone [-Collection Group],
  ///      CTC-00721-FO-findLastOfMatchingOne [-Collection Group],
  ///      CTC-00722-FO-findLastOfMatchingMore [-Collection Group],
  ///      CTC-00723-FO-findLastOfMatchingAll [-Collection Group],
  ///      CTC-00724-FO-findLastOfMatchingAllAndMore [-Collection Group]
  /// }
  /// \public
  using FindOfIterableClient::findLastOf;

  /// \inherit findAllOf ( Iterable ) call, inherited from FindOfIterableClient interface
  /// \test Suite: CTS-00001, Group: CTG-00700-FO, Test Cases: {
  ///      CTC-00725-FO-findAllOfStoreInMatchingNone [-Collection Group],
  ///      CTC-00726-FO-findAllOfStoreInMatchingOne [-Collection Group],
  ///      CTC-00727-FO-findAllOfStoreInMatchingMore [-Collection Group],
  ///      CTC-00728-FO-findAllOfStoreInMatchingAll [-Collection Group],
  ///      CTC-00729-FO-findAllOfStoreInMatchingAllAndMore [-Collection Group],
  ///      CTC-00730-FO-findAllOfReturnedMatchingNone [-Collection Group],
  ///      CTC-00731-FO-findAllOfReturnedMatchingOne [-Collection Group],
  ///      CTC-00732-FO-findAllOfReturnedMatchingMore [-Collection Group],
  ///      CTC-00733-FO-findAllOfReturnedMatchingAll [-Collection Group],
  ///      CTC-00734-FO-findAllOfReturnedMatchingAllAndMore [-Collection Group]
  /// }
  /// \public
  using FindOfIterableClient::findAllOf;

  /// \inherit findNotOf ( Iterable ) call, inherited from FindOfIterableClient interface
  /// \test Suite: CTS-00001, Group: CTG-00700-FO, Test Cases: {
  ///      CTC-00735-FO-findNotOfStoreInMatchingNone [-Collection Group],
  ///      CTC-00736-FO-findNotOfStoreInMatchingOne [-Collection Group],
  ///      CTC-00737-FO-findNotOfStoreInMatchingMoreLessThanLimit [-Collection Group],
  ///      CTC-00738-FO-findNotOfStoreInMatchingMore [-Collection Group],
  ///      CTC-00739-FO-findNotOfStoreInMatchingMoreMoreThanLimit [-Collection Group],
  ///      CTC-00740-FO-findNotOfStoreInMatchingAll [-Collection Group],
  ///      CTC-00741-FO-findNotOfStoreInMatchingAllAndMore [-Collection Group],
  ///      CTC-00742-FO-findNotOfReturnedMatchingNone [-Collection Group],
  ///      CTC-00743-FO-findNotOfReturnedMatchingOne [-Collection Group],
  ///      CTC-00744-FO-findNotOfReturnedMatchingMoreLessThanLimit [-Collection Group],
  ///      CTC-00745-FO-findNotOfReturnedMatchingMore [-Collection Group],
  ///      CTC-00746-FO-findNotOfReturnedMatchingMoreMoreThanLimit [-Collection Group],
  ///      CTC-00747-FO-findNotOfReturnedMatchingAll [-Collection Group],
  ///      CTC-00748-FO-findNotOfReturnedMatchingAllAndMore [-Collection Group]
  /// }
  /// \public
  using FindOfIterableClient::findNotOf;

  /// \inherit findFirstNotOf ( Iterable ) call, inherited from FindOfIterableClient interface
  /// \test Suite: CTS-00001, Group: CTG-00700-FO, Test Cases: {
  ///      CTC-00749-FO-findFirstNotOfMatchingNone [-Collection Group],
  ///      CTC-00750-FO-findFirstNotOfMatchingOne [-Collection Group],
  ///      CTC-00751-FO-findFirstNotOfMatchingMore [-Collection Group],
  ///      CTC-00752-FO-findFirstNotOfMatchingAll [-Collection Group],
  ///      CTC-00753-FO-findFirstNotOfMatchingAllAndMore [-Collection Group]
  /// }
  /// \public
  using FindOfIterableClient::findFirstNotOf;

  /// \inherit findLastNotOf ( Iterable ) call, inherited from FindOfIterableClient interface
  /// \test Suite: CTS-00001, Group: CTG-00700-FO, Test Cases: {
  ///      CTC-00754-FO-findLastNotOfMatchingNone [-Collection Group],
  ///      CTC-00755-FO-findLastNotOfMatchingOne [-Collection Group],
  ///      CTC-00756-FO-findLastNotOfMatchingMore [-Collection Group],
  ///      CTC-00757-FO-findLastNotOfMatchingAll [-Collection Group],
  ///      CTC-00758-FO-findLastNotOfMatchingAllAndMore [-Collection Group]
  /// }
  /// \public
  using FindOfIterableClient::findLastNotOf;

  /// \inherit findAllNotOf ( Iterable ) call, inherited from FindOfIterableClient interface
  /// \test Suite: CTS-00001, Group: CTG-00700-FO, Test Cases: {
  ///      CTC-00759-FO-findAllNotOfStoreInMatchingNone [-Collection Group],
  ///      CTC-00760-FO-findAllNotOfStoreInMatchingOne [-Collection Group],
  ///      CTC-00761-FO-findAllNotOfStoreInMatchingMore [-Collection Group],
  ///      CTC-00762-FO-findAllNotOfStoreInMatchingAll [-Collection Group],
  ///      CTC-00763-FO-findAllNotOfStoreInMatchingAllAndMore [-Collection Group],
  ///      CTC-00764-FO-findAllNotOfReturnedMatchingNone [-Collection Group],
  ///      CTC-00765-FO-findAllNotOfReturnedMatchingOne [-Collection Group],
  ///      CTC-00766-FO-findAllNotOfReturnedMatchingMore [-Collection Group],
  ///      CTC-00767-FO-findAllNotOfReturnedMatchingAll [-Collection Group],
  ///      CTC-00768-FO-findAllNotOfReturnedMatchingAllAndMore [-Collection Group]
  /// }
  /// \public
  using FindOfIterableClient::findAllNotOf;

  /// \inherit findOf ( InitializerList ) call, inherited from FindOfInitializerListClient interface
  /// \test Suite: CTS-00001, Group: CTG-00700-FO, Test Cases: {
  ///      CTC-00701-FO-findOfStoreInMatchingNone [-InitializerList Group],
  ///      CTC-00702-FO-findOfStoreInMatchingOne [-InitializerList Group],
  ///      CTC-00703-FO-findOfStoreInMatchingMoreLessThanLimit [-InitializerList Group],
  ///      CTC-00704-FO-findOfStoreInMatchingMore [-InitializerList Group],
  ///      CTC-00705-FO-findOfStoreInMatchingMoreMoreThanLimit [-InitializerList Group],
  ///      CTC-00706-FO-findOfStoreInMatchingAll [-InitializerList Group],
  ///      CTC-00707-FO-findOfStoreInMatchingAllAndMore [-InitializerList Group],
  ///      CTC-00708-FO-findOfReturnedMatchingNone [-InitializerList Group],
  ///      CTC-00709-FO-findOfReturnedMatchingOne [-InitializerList Group],
  ///      CTC-00710-FO-findOfReturnedMatchingMoreLessThanLimit [-InitializerList Group],
  ///      CTC-00711-FO-findOfReturnedMatchingMore [-InitializerList Group],
  ///      CTC-00712-FO-findOfReturnedMatchingMoreMoreThanLimit [-InitializerList Group],
  ///      CTC-00713-FO-findOfReturnedMatchingAll [-InitializerList Group],
  ///      CTC-00714-FO-findOfReturnedMatchingAllAndMore [-InitializerList Group]
  /// }
  /// \public
  using FindOfInitializerListClient::findOf;

  /// \inherit findFirstOf ( InitializerList ) call, inherited from FindOfInitializerListClient interface
  /// \test Suite: CTS-00001, Group: CTG-00700-FO, Test Cases: {
  ///      CTC-00715-FO-findFirstOfMatchingNone [-InitializerList Group],
  ///      CTC-00716-FO-findFirstOfMatchingOne [-InitializerList Group],
  ///      CTC-00717-FO-findFirstOfMatchingMore [-InitializerList Group],
  ///      CTC-00718-FO-findFirstOfMatchingAll [-InitializerList Group],
  ///      CTC-00719-FO-findFirstOfMatchingAllAndMore [-InitializerList Group]
  /// }
  /// \public
  using FindOfInitializerListClient::findFirstOf;

  /// \inherit findLastOf ( InitializerList ) call, inherited from FindOfInitializerListClient interface
  /// \test Suite: CTS-00001, Group: CTG-00700-FO, Test Cases: {
  ///      CTC-00720-FO-findLastOfMatchingNone [-InitializerList Group],
  ///      CTC-00721-FO-findLastOfMatchingOne [-InitializerList Group],
  ///      CTC-00722-FO-findLastOfMatchingMore [-InitializerList Group],
  ///      CTC-00723-FO-findLastOfMatchingAll [-InitializerList Group],
  ///      CTC-00724-FO-findLastOfMatchingAllAndMore [-InitializerList Group]
  /// }
  /// \public
  using FindOfInitializerListClient::findLastOf;

  /// \inherit findAllOf ( InitializerList ) call, inherited from FindOfInitializerListClient interface
  /// \test Suite: CTS-00001, Group: CTG-00700-FO, Test Cases: {
  ///      CTC-00725-FO-findAllOfStoreInMatchingNone [-InitializerList Group],
  ///      CTC-00726-FO-findAllOfStoreInMatchingOne [-InitializerList Group],
  ///      CTC-00727-FO-findAllOfStoreInMatchingMore [-InitializerList Group],
  ///      CTC-00728-FO-findAllOfStoreInMatchingAll [-InitializerList Group],
  ///      CTC-00729-FO-findAllOfStoreInMatchingAllAndMore [-InitializerList Group],
  ///      CTC-00730-FO-findAllOfReturnedMatchingNone [-InitializerList Group],
  ///      CTC-00731-FO-findAllOfReturnedMatchingOne [-InitializerList Group],
  ///      CTC-00732-FO-findAllOfReturnedMatchingMore [-InitializerList Group],
  ///      CTC-00733-FO-findAllOfReturnedMatchingAll [-InitializerList Group],
  ///      CTC-00734-FO-findAllOfReturnedMatchingAllAndMore [-InitializerList Group]
  /// }
  /// \public
  using FindOfInitializerListClient::findAllOf;

  /// \inherit findNotOf ( InitializerList ) call, inherited from FindOfInitializerListClient interface
  /// \test Suite: CTS-00001, Group: CTG-00700-FO, Test Cases: {
  ///      CTC-00735-FO-findNotOfStoreInMatchingNone [-InitializerList Group],
  ///      CTC-00736-FO-findNotOfStoreInMatchingOne [-InitializerList Group],
  ///      CTC-00737-FO-findNotOfStoreInMatchingMoreLessThanLimit [-InitializerList Group],
  ///      CTC-00738-FO-findNotOfStoreInMatchingMore [-InitializerList Group],
  ///      CTC-00739-FO-findNotOfStoreInMatchingMoreMoreThanLimit [-InitializerList Group],
  ///      CTC-00740-FO-findNotOfStoreInMatchingAll [-InitializerList Group],
  ///      CTC-00741-FO-findNotOfStoreInMatchingAllAndMore [-InitializerList Group],
  ///      CTC-00742-FO-findNotOfReturnedMatchingNone [-InitializerList Group],
  ///      CTC-00743-FO-findNotOfReturnedMatchingOne [-InitializerList Group],
  ///      CTC-00744-FO-findNotOfReturnedMatchingMoreLessThanLimit [-InitializerList Group],
  ///      CTC-00745-FO-findNotOfReturnedMatchingMore [-InitializerList Group],
  ///      CTC-00746-FO-findNotOfReturnedMatchingMoreMoreThanLimit [-InitializerList Group],
  ///      CTC-00747-FO-findNotOfReturnedMatchingAll [-InitializerList Group],
  ///      CTC-00748-FO-findNotOfReturnedMatchingAllAndMore [-InitializerList Group]
  /// }
  /// \public
  using FindOfInitializerListClient::findNotOf;

  /// \inherit findFirstNotOf ( InitializerList ) call, inherited from FindOfInitializerListClient interface
  /// \test Suite: CTS-00001, Group: CTG-00700-FO, Test Cases: {
  ///      CTC-00749-FO-findFirstNotOfMatchingNone [-InitializerList Group],
  ///      CTC-00750-FO-findFirstNotOfMatchingOne [-InitializerList Group],
  ///      CTC-00751-FO-findFirstNotOfMatchingMore [-InitializerList Group],
  ///      CTC-00752-FO-findFirstNotOfMatchingAll [-InitializerList Group],
  ///      CTC-00753-FO-findFirstNotOfMatchingAllAndMore [-InitializerList Group]
  /// }
  /// \public
  using FindOfInitializerListClient::findFirstNotOf;

  /// \inherit findLastNotOf ( InitializerList ) call, inherited from FindOfInitializerListClient interface
  /// \test Suite: CTS-00001, Group: CTG-00700-FO, Test Cases: {
  ///      CTC-00754-FO-findLastNotOfMatchingNone [-InitializerList Group],
  ///      CTC-00755-FO-findLastNotOfMatchingOne [-InitializerList Group],
  ///      CTC-00756-FO-findLastNotOfMatchingMore [-InitializerList Group],
  ///      CTC-00757-FO-findLastNotOfMatchingAll [-InitializerList Group],
  ///      CTC-00758-FO-findLastNotOfMatchingAllAndMore [-InitializerList Group]
  /// }
  /// \public
  using FindOfInitializerListClient::findLastNotOf;

  /// \inherit findAllNotOf ( InitializerList ) call, inherited from FindOfInitializerListClient interface
  /// \test Suite: CTS-00001, Group: CTG-00700-FO, Test Cases: {
  ///      CTC-00759-FO-findAllNotOfStoreInMatchingNone [-InitializerList Group],
  ///      CTC-00760-FO-findAllNotOfStoreInMatchingOne [-InitializerList Group],
  ///      CTC-00761-FO-findAllNotOfStoreInMatchingMore [-InitializerList Group],
  ///      CTC-00762-FO-findAllNotOfStoreInMatchingAll [-InitializerList Group],
  ///      CTC-00763-FO-findAllNotOfStoreInMatchingAllAndMore [-InitializerList Group],
  ///      CTC-00764-FO-findAllNotOfReturnedMatchingNone [-InitializerList Group],
  ///      CTC-00765-FO-findAllNotOfReturnedMatchingOne [-InitializerList Group],
  ///      CTC-00766-FO-findAllNotOfReturnedMatchingMore [-InitializerList Group],
  ///      CTC-00767-FO-findAllNotOfReturnedMatchingAll [-InitializerList Group],
  ///      CTC-00768-FO-findAllNotOfReturnedMatchingAllAndMore [-InitializerList Group]
  /// }
  /// \public
  using FindOfInitializerListClient::findAllNotOf;

  /// \brief String conversion function, used to obtain String representation of the Iterable
  /// \exceptsafe
  /// \return String = string representation
  /// \test Suite: CTS-00001, Group: CTG-00002-MF, Test Cases: { CTC-00003-MF-toString, CTC-00010-MF-clear }
  /// \public
  __CDS_NoDiscard auto toString () const noexcept(false) -> String override;

  /// \brief Function used to check if the iterable contains the requested element.
  /// \param [in] element : ElementType cref = Constant Reference to the element to be found in the iterable
  /// \return bool = true if the element exists in the iterable, false otherwise
  /// \test Suite: CTS-00001, Group: CTG-00002-MF, Test Cases: { CTC-00007-MF-containsTrue, CTC-00008-MF-containsFalse, CTC-00010-MF-clear }
  /// \public
  __CDS_NoDiscard virtual auto contains (ElementType const& element) const noexcept -> bool;
  
protected:
  /// \typedef imported protected alias for __GenericHandler, representing a generic member function pointer, represents a function returned at a request made through the Iterable Communication Channel
  /// \protected
  using __GenericHandler                      = typename CommunicationChannel::__GenericHandler;        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \typedef imported protected alias for __GenericConstHandler, representing a generic member const-function pointer, represents a function returned at a request made through the Iterable Communication Channel
  /// \protected
  using __GenericConstHandler                 = typename CommunicationChannel::__GenericConstHandler;   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \brief Default Constructor
  /// \exceptsafe
  /// \test Suite: CTS-00001, Group: All - requirement for running, Test Cases: All - requirement for running
  /// \protected
  constexpr Iterable () noexcept;

  /// \brief Copy Constructor
  /// \param [in] iterable : Iterable cref = Constant Reference to an iterable to copy data from
  /// \exceptsafe
  /// \test Suite: CTS-00001, Group: All - requirement for running, Test Cases: All - requirement for running
  /// \protected
  constexpr Iterable (Iterable const& iterable) noexcept;

  /// \brief Move Constructor
  /// \param [in, out] iterable : Iterable mref = Move Reference to an iterable to move data from
  /// \exceptsafe
  /// \test Suite: CTS-00001, Group: All - requirement for running, Test Cases: All - requirement for running
  /// \protected
  constexpr Iterable (Iterable&& iterable) noexcept;
};
} // namespace cds

#include "iterable/impl/IterableConstructsImpl.hpp"
#include "iterable/impl/IterableFunctionsImpl.hpp"

#include "../shared/delegateIterator/impl/ForwardDelegateWrapperIterator.hpp"                                               // NOLINT(llvm-header-guard)

#include "../shared/iterableInternalCommunication/channel/impl/IterableInternalCommunicationChannelImpl.hpp"

#include "../shared/iterableInternalCommunication/client/primitive/impl/DelegateForwardConstIterablePrimitiveClientImpl.hpp"    // NOLINT(llvm-header-guard)

#include "../shared/iterableInternalCommunication/client/composite/impl/ContainsOfCompositeClientImpl.hpp"
#include "../shared/iterableInternalCommunication/client/composite/impl/FindOfImmutableCompositeClientImpl.hpp"                 // NOLINT(llvm-header-guard)
#include "../shared/iterableInternalCommunication/client/composite/impl/FindByImmutableCompositeClientImpl.hpp"
#include "../shared/iterableInternalCommunication/client/composite/impl/GenericImmutableStatementsCompositeClientImpl.hpp"

#include "iterable/impl/IterableImpl.hpp"

#endif // __CDS_ITERABLE_HPP__
