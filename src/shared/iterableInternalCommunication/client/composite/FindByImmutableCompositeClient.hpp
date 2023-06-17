//
// Created by loghin on 6/27/22.
//

#ifndef __CDS_SHARED_FIND_BY_IMMUTABLE_COMPOSITE_CLIENT_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_SHARED_FIND_BY_IMMUTABLE_COMPOSITE_CLIENT_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

#include "../../../impl/functionalExceptSpecification.hpp"
#include "../../../iterator/IteratorFindStatements.hpp"         // NOLINT(llvm-include-order)
#include "../../../iterator/IteratorFindMemberStatements.hpp"

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

/// \interface Interface for calling functional find statements ( predicates as parameters, henceforth the 'find' elements 'that' are validated by a predicate )
/// on an immutable iterable type ( has 'cbegin' and 'cend' )
/// \tparam __Iterable is the type of implementor class, used for static polymorphism.
/// Implementor is also required to implement a variant of DelegateForwardConstIterablePrimitiveClient,
/// or provide a set of equivalent member functions provided by said client - 'cbegin' / 'cend'
/// \tparam __Element is the type of elements contained into the Object
/// \tparam __Iterator is the type of iterator to be returned by the functions
///
/// \test Suite: CTS-00001, Group: CTG-00600-FT, Test Cases: All
/// \test Suite: CTS-00001, Group: CTG-00650-FTMF, Test Cases: All
///
/// \namespace cds :: __hidden :: __impl
/// \internal library-private
template <typename __Iterable, typename __Element, typename __Iterator, bool __exceptCond = false>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __FindByImmutableCompositeClient {                                                            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
public:
  /// \typedef Private definition for __Iterator template parameter
  /// \private
  using ConstIterator = __Iterator;

protected:
  constexpr static bool const itNoexcept = __exceptCond;

public:
  /// \brief Function used to find the elements that are validated by a given predicate and return the iterators of the elements in a given collection, until a given limit has been reached, at which point the iteration will stop.
  /// \tparam __Collection is the type of template iterable to store the iterators in
  /// \tparam __Predicate is the type of the predicate given as a parameter, the type must be callable and compatible with the 'bool ( Decay < ElementType > )' function signature, or with the 'bool () const' member function signature.
  /// \param [in] count : Size = Maximum number of elements to find
  /// \param [out] storeIn : __Collection \< __Iterator \> cref = Constant Reference to the collection to store the iterators in
  /// \param [in] predicate : __Predicate cref = Constant Reference to callable object / member function, to be called with each element of the range as a parameter, if callable, or as an object caller, if member function
  /// \exceptsafe if __Predicate callable / member function is exceptsafe
  /// \return __Collection \< __Iterator \> ref = Reference to the updated object given in the 'storeIn' parameter
  ///
  /// \test Suite: CTS-00001, Group: CTG-00600-FT, Test Cases: {
  ///      CTC-00601-FT-findThatStoreInMatchingNone,
  ///      CTC-00602-FT-findThatStoreInMatchingOne,
  ///      CTC-00603-FT-findThatStoreInMatchingMoreLessThanLimit,
  ///      CTC-00604-FT-findThatStoreInMatchingMore,
  ///      CTC-00605-FT-findThatStoreInMatchingMoreMoreThanLimit,
  ///      CTC-00606-FT-findThatStoreInMatchingAll,
  ///      CTC-00607-FT-findThatStoreInMatchingAllAndMore
  /// }
  ///
  /// \test Suite: CTS-00001, Group: CTG-00650-FTMF, Test Cases: {
  ///      CTC-00651-FTMF-findThatStoreInMemberFunction
  /// }
  ///
  /// \public
  template <template <typename...> class __Collection, typename __Predicate>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto findThat (
      Size                          count,
      __Collection <ConstIterator>& storeIn,
      __Predicate const&            predicate
  ) const noexcept (false) -> __Collection <ConstIterator>&;

  /// \brief Function used to find the elements that are validated by a given predicate and return the iterators of the elements in a new collection, until a given limit has been reached, at which point the iteration will stop.
  /// \tparam __Collection is the type of template iterable to store the iterators in
  /// \tparam __Predicate is the type of the predicate given as a parameter, the type must be callable and compatible with the 'bool ( Decay < ElementType > )' function signature, or with the 'bool () const' member function signature.
  /// \param [in] count : Size = Maximum number of elements to find
  /// \param [in] predicate : __Predicate cref = Constant Reference to callable object / member function, to be called with each element of the range as a parameter, if callable, or as an object caller, if member function
  /// \exceptsafe if __Predicate callable / member function is exceptsafe
  /// \return __Collection \< __Iterator \> = The new collection containing the found iterators
  ///
  /// \test Suite: CTS-00001, Group: CTG-00600-FT, Test Cases: {
  ///      CTC-00608-FT-findThatReturnedMatchingNone,
  ///      CTC-00609-FT-findThatReturnedMatchingOne,
  ///      CTC-00610-FT-findThatReturnedMatchingMoreLessThanLimit,
  ///      CTC-00611-FT-findThatReturnedMatchingMore,
  ///      CTC-00612-FT-findThatReturnedMatchingMoreMoreThanLimit,
  ///      CTC-00613-FT-findThatReturnedMatchingAll,
  ///      CTC-00614-FT-findThatReturnedMatchingAllAndMore
  /// }
  ///
  /// \test Suite: CTS-00001, Group: CTG-00650-FTMF, Test Cases: {
  ///      CTC-00652-FTMF-findThatReturnedMemberFunction
  /// }
  ///
  /// \public
  template <template <typename...> class __Collection, typename __Predicate>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard auto findThat (
      Size                count,
      __Predicate const&  predicate
  ) const noexcept (false) -> __Collection <ConstIterator>;

  /// \brief Function used to find the first element validated by a given predicate and return the iterator of the element, if applicable.
  /// \tparam __Predicate is the type of the predicate given as a parameter, the type must be callable and compatible with the 'bool ( Decay < ElementType > )' function signature, or with the 'bool () const' member function signature.
  /// \param [in] predicate : __Predicate cref = Constant Reference to callable object / member function, to be called with each element of the range as a parameter, if callable, or as an object caller, if member function
  /// \exceptsafe if __Predicate callable / member function is exceptsafe
  /// \return __Iterator = The iterator of the found element, if applicable. If none found, 'cend' is returned
  ///
  /// \test Suite: CTS-00001, Group: CTG-00600-FT, Test Cases: {
  ///      CTC-00615-FT-findFirstThatMatchingNone,
  ///      CTC-00616-FT-findFirstThatMatchingOne,
  ///      CTC-00617-FT-findFirstThatMatchingMore,
  ///      CTC-00618-FT-findFirstThatMatchingAll,
  ///      CTC-00619-FT-findFirstThatMatchingAllAndMore
  /// }
  ///
  /// \test Suite: CTS-00001, Group: CTG-00650-FTMF, Test Cases: {
  ///      CTC-00653-FTMF-findFirstThatMemberFunction
  /// }
  ///
  /// \public
  template <typename __Predicate> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard auto findFirstThat (
      __Predicate const& predicate
  ) const noexcept (noexcept (__PredicateExceptSpecTraits <__Element const, __Predicate>::__noexceptSpec) && itNoexcept) -> ConstIterator;

  /// \brief Function used to find the last element validated by a given predicate and return the iterator of the element, if applicable.
  /// \tparam __Predicate is the type of the predicate given as a parameter, the type must be callable and compatible with the 'bool ( Decay < ElementType > )' function signature, or with the 'bool () const' member function signature.
  /// \param [in] predicate : __Predicate cref = Constant Reference to callable object / member function, to be called with each element of the range as a parameter, if callable, or as an object caller, if member function
  /// \exceptsafe if __Predicate callable / member function is exceptsafe
  /// \return __Iterator = The iterator of the found element, if applicable. If none found, 'cend' is returned
  ///
  /// \test Suite: CTS-00001, Group: CTG-00600-FT, Test Cases: {
  ///      CTC-00620-FT-findLastThatMatchingNone,
  ///      CTC-00621-FT-findLastThatMatchingOne,
  ///      CTC-00622-FT-findLastThatMatchingMore,
  ///      CTC-00623-FT-findLastThatMatchingAll,
  ///      CTC-00624-FT-findLastThatMatchingAllAndMore
  /// }
  ///
  /// \test Suite: CTS-00001, Group: CTG-00650-FTMF, Test Cases: {
  ///      CTC-00654-FTMF-findLastThatMemberFunction
  /// }
  ///
  /// \public
  template <typename __Predicate> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard auto findLastThat (
      __Predicate const& predicate
  ) const noexcept (noexcept (__PredicateExceptSpecTraits <__Element const, __Predicate>::__noexceptSpec) && itNoexcept) -> ConstIterator;
  
  /// \brief Function used to find all the elements that are validated by a given predicate and return the iterators of the elements in a given collection
  /// \tparam __Collection is the type of template iterable to store the iterators in
  /// \tparam __Predicate is the type of the predicate given as a parameter, the type must be callable and compatible with the 'bool ( Decay < ElementType > )' function signature, or with the 'bool () const' member function signature.
  /// \param [out] storeIn : __Collection \< __Iterator \> cref = Constant Reference to the collection to store the iterators in
  /// \param [in] predicate : __Predicate cref = Constant Reference to callable object / member function, to be called with each element of the range as a parameter, if callable, or as an object caller, if member function
  /// \exceptsafe if __Predicate callable / member function is exceptsafe
  /// \return __Collection \< __Iterator \> ref = Reference to the updated object given in the 'storeIn' parameter
  ///
  /// \test Suite: CTS-00001, Group: CTG-00600-FT, Test Cases: {
  ///      CTC-00625-FT-findAllThatStoreInMatchingNone,
  ///      CTC-00626-FT-findAllThatStoreInMatchingOne,
  ///      CTC-00627-FT-findAllThatStoreInMatchingMore,
  ///      CTC-00628-FT-findAllThatStoreInMatchingAll,
  ///      CTC-00629-FT-findAllThatStoreInMatchingAllAndMore
  /// }
  ///
  /// \test Suite: CTS-00001, Group: CTG-00650-FTMF, Test Cases: {
  ///      CTC-00655-FTMF-findAllThatStoreInMemberFunction
  /// }
  ///
  /// \public
  template <template <typename...> class __Collection, typename __Predicate>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto findAllThat (
      __Collection <ConstIterator>& storeIn,
      __Predicate const&            predicate
  ) const noexcept (false) -> __Collection <ConstIterator>&;

  /// \brief Function used to find all the elements that are validated by a given predicate and return the iterators of the elements in a new collection
  /// \tparam __Collection is the type of template iterable to store the iterators in
  /// \tparam __Predicate is the type of the predicate given as a parameter, the type must be callable and compatible with the 'bool ( Decay < ElementType > )' function signature, or with the 'bool () const' member function signature.
  /// \param [in] predicate : __Predicate cref = Constant Reference to callable object / member function, to be called with each element of the range as a parameter, if callable, or as an object caller, if member function
  /// \exceptsafe if __Predicate callable / member function is exceptsafe
  /// \return __Collection \< __Iterator \> = The new collection containing the found iterators
  ///
  /// \test Suite: CTS-00001, Group: CTG-00600-FT, Test Cases: {
  ///      CTC-00630-FT-findAllThatReturnedMatchingNone,
  ///      CTC-00631-FT-findAllThatReturnedMatchingOne,
  ///      CTC-00632-FT-findAllThatReturnedMatchingMore,
  ///      CTC-00633-FT-findAllThatReturnedMatchingAll,
  ///      CTC-00634-FT-findAllThatReturnedMatchingAllAndMore
  /// }
  ///
  /// \test Suite: CTS-00001, Group: CTG-00650-FTMF, Test Cases: {
  ///      CTC-00656-FTMF-findAllThatReturnedMemberFunction
  /// }
  ///
  /// \public
  template <template <typename...> class __Collection, typename __Predicate> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard auto findAllThat (
      __Predicate const& predicate
  ) const noexcept (false) -> __Collection <ConstIterator>;
};


/// \typedef Variant of the FindByImmutableCompositeClient, only alias due to it being a composite client
/// -> will use primitive local clients, making it a local client
/// \tparam __Iterable is the type of implementor class, used for static polymorphism.
/// Implementor is also required to implement a variant of DelegateForwardConstIterablePrimitiveClient,
/// or provide a set of equivalent member functions provided by said client - 'cbegin' / 'cend'
/// \tparam __Element is the type of elements contained into the Object
///
/// \test Suite: TBA, Group: TBA, Test Cases: TBA
///
/// \namespace cds :: __hidden :: __impl
/// \internal library-private
template <typename __Iterable, typename __Element, typename __Iterator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LocalFindByImmutableCompositeClient :        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __FindByImmutableCompositeClient <__Iterable, __Element, __Iterator, true> {};
} // namespace __impl
} // namespace __hidden
} // namespace cds

#include "../../../iterator/impl/IteratorFindStatementsImpl.hpp"        // NOLINT(llvm-include-order)
#include "../../../iterator/impl/IteratorFindMemberStatementsImpl.hpp"

#endif // __CDS_SHARED_FIND_BY_IMMUTABLE_COMPOSITE_CLIENT_HPP__
