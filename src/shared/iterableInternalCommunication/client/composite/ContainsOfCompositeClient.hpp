//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_CONTAINS_OF_COMPOSITE_CLIENT_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_SHARED_CONTAINS_OF_COMPOSITE_CLIENT_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
/// \interface Interface for calling containsOf statements - contains + AnyOf / AnyNotOf / AllOf / NoneOf, with a generic parameter type ( Collection, initializer_list, etc. )
/// \tparam __Iterable is the type of implementor class, used for static polymorphism.
/// Implementor required to also be derived from the Collection abstract class, or provide an
/// equivalent 'contains' base function, as provided by the Collection class
/// \tparam __Element is the type of elements contained into the Object
/// \tparam __FromIterable is the type of the parameter given to containsOf functions
/// \tparam __contains is the function used in containsAnyNotOf to check for inclusion of element from caller to parameter
///
/// \test Suite: CTS-00001, Group: CTG-00300-CO, Test Cases: All
///
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <
    typename                                                                __Iterable,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __Element,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __FromIterable,       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__FromIterable const&, __Element const&> __contains,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    bool                                                                    __exceptCond = false  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __ContainsOfCompositeClient {                                                             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
protected:
  constexpr static bool const allNoexcept = __exceptCond;

public:
  /// \brief Function used to check if the caller iterable contains any element that matches any element from the given parameter iterable
  /// \param [in] from : __FromIterable cref = Constant Reference to an iterable to check inclusion for
  /// \exceptsafe
  /// \return bool = true if property is fulfilled, false otherwise
  ///
  /// \test Suite: CTS-00001, Group: CTG-00300-CO, Test Cases: {
  ///      CTC-00301-CO-containsAnyOfCollectionNoneCommon,
  ///      CTC-00302-CO-containsAnyOfCollectionOneCommon,
  ///      CTC-00303-CO-containsAnyOfCollectionMoreCommon,
  ///      CTC-00304-CO-containsAnyOfCollectionAllCommon,
  ///      CTC-00305-CO-containsAnyOfCollectionAllCommonAndMore
  /// }
  ///
  /// \public
  __CDS_NoDiscard auto containsAnyOf (__FromIterable const& from) const noexcept(allNoexcept) -> bool;

  /// \brief Function used to check if the caller iterable contains any element that does not match any element from the given parameter iterable
  /// \param [in] from : __FromIterable cref = Constant Reference to an iterable to check inclusion for
  /// \exceptsafe
  /// \return bool = true if property is fulfilled, false otherwise
  ///
  /// \test Suite: CTS-00001, Group: CTG-00300-CO, Test Cases: {
  ///      CTC-00311-CO-containsAnyNotOfCollectionNoneCommon,
  ///      CTC-00312-CO-containsAnyNotOfCollectionOneCommon,
  ///      CTC-00313-CO-containsAnyNotOfCollectionMoreCommon,
  ///      CTC-00314-CO-containsAnyNotOfCollectionAllCommon,
  ///      CTC-00315-CO-containsAnyNotOfCollectionAllCommonAndMore
  /// }
  ///
  /// \public
  __CDS_NoDiscard auto containsAnyNotOf (__FromIterable const& from) const noexcept(allNoexcept) -> bool;

  /// \brief Function used to check if all of the elements in the given parameter iterable match an element in the caller iterable
  /// \param [in] from : __FromIterable cref = Constant Reference to an iterable to check inclusion for
  /// \exceptsafe
  /// \return bool = true if property is fulfilled, false otherwise
  ///
  /// \test Suite: CTS-00001, Group: CTG-00300-CO, Test Cases: {
  ///      CTC-00306-CO-containsAllOfCollectionNoneCommon,
  ///      CTC-00307-CO-containsAllOfCollectionOneCommon,
  ///      CTC-00308-CO-containsAllOfCollectionMoreCommon,
  ///      CTC-00309-CO-containsAllOfCollectionAllCommon,
  ///      CTC-00310-CO-containsAllOfCollectionAllCommonAndMore
  /// }
  ///
  /// \public
  __CDS_NoDiscard auto containsAllOf (__FromIterable const& from) const noexcept(allNoexcept) -> bool;

  /// \brief Function used to check if the caller collection contains no element that matches any element from the given parameter iterable
  /// \param [in] from : __FromIterable cref = Constant Reference to an iterable to check inclusion for
  /// \exceptsafe
  /// \return bool = true if property is fulfilled, false otherwise
  ///
  /// \test Suite: CTS-00001, Group: CTG-00300-CO, Test Cases: {
  ///      CTC-00316-CO-containsNoneOfCollectionNoneCommon,
  ///      CTC-00317-CO-containsNoneOfCollectionOneCommon,
  ///      CTC-00318-CO-containsNoneOfCollectionMoreCommon,
  ///      CTC-00319-CO-containsNoneOfCollectionAllCommon,
  ///      CTC-00320-CO-containsNoneOfCollectionAllCommonAndMore
  /// }
  ///
  /// \public
  __CDS_NoDiscard auto containsNoneOf (__FromIterable const& from) const noexcept(allNoexcept) -> bool;
};


/// \typedef Variant of the ContainsOfCompositeClient, only alias due to it being a composite client
/// -> will use primitive local clients, making it a local client
/// \tparam __Iterable is the type of implementor class, used for static polymorphism.
/// Implementor required to also be derived from the Collection abstract class, or provide an
/// equivalent 'contains' base function, as provided by the Collection class
/// \tparam __Element is the type of elements contained into the Object
/// \tparam __FromIterable is the type of the parameter given to containsOf functions
/// \tparam __contains is the function used in containsAnyNotOf to check for inclusion of element from caller to parameter
///
/// \test Suite: TBA, Group: TBA, Test Cases: TBA
///
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <
    typename                                                                __Iterable,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __Element,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __FromIterable, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__FromIterable const&, __Element const&> __contains      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __LocalContainsOfCompositeClient :                               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __ContainsOfCompositeClient <__Iterable, __Element, __FromIterable, __contains, true> {};
} // namespace __impl
} // namespace __hidden 
} // namespace cds

#endif // __CDS_SHARED_CONTAINS_OF_COMPOSITE_CLIENT_HPP__
