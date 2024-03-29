//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_REMOVE_BY_COMPOSITE_CLIENT_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_SHARED_REMOVE_BY_COMPOSITE_CLIENT_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
/// \interface Interface for calling removeThat statements - removeThat / removeFirstThat / removeLastThat / removeAllThat.
/// These use the predicate given as a parameter to identify the elements via iterator to be removed
/// ( hence the name - 'remove' the elements 'that' yield true to the given predicate )
/// \tparam __Iterable is the type of implementor class, used for static polymorphism. <br/>
/// Implementor is also required to implement a variant of ConstIteratorRemoveClient,
/// or provide an equivalent set of member functions 'remove' and 'removeAll' provided by the client variant. <br/>
/// Implementor is also required to implement a variant of DelegateForwardConstIterbleClient,
/// or provide an equivalent set of member functions to 'cbegin' and 'cend' provided by the client variant. <br/>
/// Implementor is also required to either be derived from the Collection abstract class
/// or provide an equivalent implementation of the member function 'size', representing the
/// number of elements in the iterable, and the distance between 'cbegin' and 'cend'
/// \tparam __Element is the type of elements contained into the object
///
/// \test Suite: CTS-00001, Group: CTG-00400-RB, Test Cases: All
///
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <typename __Iterable, typename __Element>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __RemoveByCompositeClient {                   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
public:
  /// \typedef Alias for parameter type __Element
  /// \protected
  using ElementType = __Element const;

  /// \brief Function used to remove from the caller the elements that yield true to the given predicate, until a removal limit has been reached
  /// \tparam __Predicate is the type of the predicate callable, compatible with the signature bool ( Decay < ElementType > )
  /// \param [in] count : Size = the removal limit. Once this number of elements have been removed, the iteration is stopped
  /// \param [in] predicate : Predicate cref = Constant Reference to a predicate callable to validate the elements with
  /// \exceptsafe if predicate ( element ) is exceptsafe
  /// \return Size = number of elements that were removed. If the limit has been reached, the function will return the exact value of 'count'
  ///
  /// \test Suite: CTS-00001, Group: CTG-00400-RB, Test Cases: {
  ///      CTC-00401-RB-removeThatMatchesNone,
  ///      CTC-00402-RB-removeThatMatchesOne,
  ///      CTC-00403-RB-removeThatMatchesMoreLessThanLimit,
  ///      CTC-00404-RB-removeThatMatchesMoreExact,
  ///      CTC-00405-RB-removeThatMatchesMoreThanLimit,
  ///      CTC-00406-RB-removeThatMatchesAll
  /// }
  ///
  /// \public
  template <typename __Predicate, cds::meta::EnableIf <!cds::meta::IsMemberFunctionPointer <__Predicate, cds::meta::Decay <__Element>>::value> = 0> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto removeThat (Size count, __Predicate const& predicate) noexcept(false) -> Size;

  /// \brief Function used to remove from the caller the elements that yield true to the given predicate member function, until a removal limit has been reached
  /// \tparam __Predicate is the type of the predicate member function, compatible with the signature bool (), member function of ElementType
  /// \param [in] count : Size = the removal limit. Once this number of elements have been removed, the iteration is stopped
  /// \param [in] predicate : Predicate cref = Constant Reference to a predicate member function to validate the elements with
  /// \exceptsafe if element.predicate () is exceptsafe
  /// \return Size = number of elements that were removed. If the limit has been reached, the function will return the exact value of 'count'
  ///
  /// \test Suite: CTS-00001, Group: CTG-00400-RB, Test Cases: { CTC-00419-RB-memberRemoveThat }
  ///
  /// \public
  template <typename __Predicate, cds::meta::EnableIf <cds::meta::IsMemberFunctionPointer <__Predicate, cds::meta::Decay <__Element>>::value> = 0> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto removeThat (Size count, __Predicate const& predicate) noexcept(false) -> Size;

  /// \brief Function used to remove from the caller the first element that yields true to the given predicate
  /// \tparam __Predicate is the type of the predicate callable, compatible with the signature bool ( Decay < ElementType > )
  /// \param [in] predicate : Predicate cref = Constant Reference to a predicate callable to validate the elements with
  /// \exceptsafe if predicate ( element ) is exceptsafe
  /// \return bool = true if an element has been removed, false otherwise
  ///
  /// \test Suite: CTS-00001, Group: CTG-00400-RB, Test Cases: {
  ///      CTC-00407-RB-removeFirstThatMatchesNone,
  ///      CTC-00408-RB-removeFirstThatMatchesOne,
  ///      CTC-00409-RB-removeFirstThatMatchesMore,
  ///      CTC-00410-RB-removeFirstThatMatchesAll
  /// }
  ///
  /// \public
  template <typename __Predicate, cds::meta::EnableIf <!cds::meta::IsMemberFunctionPointer <__Predicate, cds::meta::Decay <__Element>>::value> = 0> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto removeFirstThat (__Predicate const& predicate) noexcept(false) -> bool;

  /// \brief Function used to remove from the caller the first element that yields true to the given predicate member function
  /// \tparam __Predicate is the type of the predicate member function, compatible with the signature bool (), member function of ElementType
  /// \param [in] predicate : Predicate cref = Constant Reference to a predicate member function to validate the elements with
  /// \exceptsafe if element.predicate () is exceptsafe
  /// \return bool = true if an element has been removed, false otherwise
  ///
  /// \test Suite: CTS-00001, Group: CTG-00400-RB, Test Cases: { CTC-00420-RB-memberRemoveFirstThat }
  ///
  /// \public
  template <typename __Predicate, cds::meta::EnableIf <cds::meta::IsMemberFunctionPointer <__Predicate, cds::meta::Decay <__Element>>::value> = 0> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto removeFirstThat (__Predicate const& predicate) noexcept(false) -> bool;

  /// \brief Function used to remove from the caller the last element that yields true to the given predicate
  /// \tparam __Predicate is the type of the predicate callable, compatible with the signature bool ( Decay < ElementType > )
  /// \param [in] predicate : Predicate cref = Constant Reference to a predicate callable to validate the elements with
  /// \exceptsafe if predicate ( element ) is exceptsafe
  /// \return bool = true if an element has been removed, false otherwise
  ///
  /// \test Suite: CTS-00001, Group: CTG-00400-RB, Test Cases: {
  ///      CTC-00411-RB-removeLastThatMatchesNone,
  ///      CTC-00412-RB-removeLastThatMatchesOne,
  ///      CTC-00413-RB-removeLastThatMatchesMore,
  ///      CTC-00414-RB-removeLastThatMatchesAll
  /// }
  ///
  /// \public
  template <typename __Predicate, cds::meta::EnableIf <!cds::meta::IsMemberFunctionPointer <__Predicate, cds::meta::Decay <__Element>>::value> = 0> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto removeLastThat (__Predicate const& predicate) noexcept(false) -> bool;

  /// \brief Function used to remove from the caller the last element that yields true to the given predicate member function
  /// \tparam __Predicate is the type of the predicate member function, compatible with the signature bool (), member function of ElementType
  /// \param [in] predicate : Predicate cref = Constant Reference to a predicate member function to validate the elements with
  /// \exceptsafe if element.predicate () is exceptsafe
  /// \return bool = true if an element has been removed, false otherwise
  ///
  /// \test Suite: CTS-00001, Group: CTG-00400-RB, Test Cases: { CTC-00421-RB-memberRemoveLastThat }
  ///
  /// \public
  template <typename __Predicate, cds::meta::EnableIf <cds::meta::IsMemberFunctionPointer <__Predicate, cds::meta::Decay <__Element>>::value> = 0> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto removeLastThat (__Predicate const& predicate) noexcept(false) -> bool;

  /// \brief Function used to remove from the caller all the elements that yield true to the given predicate
  /// \tparam __Predicate is the type of the predicate callable, compatible with the signature bool ( Decay < ElementType > )
  /// \param [in] predicate : Predicate cref = Constant Reference to a predicate callable to validate the elements with
  /// \exceptsafe if predicate ( element ) is exceptsafe
  /// \return Size = number of elements removed from the iterable
  ///
  /// \test Suite: CTS-00001, Group: CTG-00400-RB, Test Cases: {
  ///      CTC-00415-RB-removeAllThatMatchesNone,
  ///      CTC-00416-RB-removeAllThatMatchesOne,
  ///      CTC-00417-RB-removeAllThatMatchesMore,
  ///      CTC-00418-RB-removeAllThatMatchesAll
  /// }
  ///
  /// \public
  template <typename __Predicate, cds::meta::EnableIf <!cds::meta::IsMemberFunctionPointer <__Predicate, cds::meta::Decay <__Element>>::value> = 0> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto removeAllThat (__Predicate const& predicate) noexcept(false) -> Size;

  /// \brief Function used to remove from the caller all the element that yield true to the given predicate member function
  /// \tparam __Predicate is the type of the predicate member function, compatible with the signature bool (), member function of ElementType
  /// \param [in] predicate : Predicate cref = Constant Reference to a predicate member function to validate the elements with
  /// \exceptsafe if element.predicate () is exceptsafe
  /// \return Size = number of elements removed from the iterable
  ///
  /// \test Suite: CTS-00001, Group: CTG-00400-RB, Test Cases: { CTC-00422-RB-memberRemoveAllThat }
  ///
  /// \public
  template <typename __Predicate, cds::meta::EnableIf <cds::meta::IsMemberFunctionPointer <__Predicate, cds::meta::Decay <__Element>>::value> = 0> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto removeAllThat (__Predicate const& predicate) noexcept(false) -> Size;
};


/// \typedef Variant of RemoveByCompositeClient, only alias due to it being a composite client
/// -> will use primitive local clients, making it a local client
/// \tparam __Iterable is the type of implementor class, used for static polymorphism. <br/>
/// Implementor is also required to implement a variant of ConstIteratorRemoveClient,
/// or provide an equivalent set of member functions 'remove' and 'removeAll' provided by the client variant. <br/>
/// Implementor is also required to implement a variant of DelegateForwardConstIterbleClient,
/// or provide an equivalent set of member functions to 'cbegin' and 'cend' provided by the client variant. <br/>
/// Implementor is also required to either be derived from the Collection abstract class
/// or provide an equivalent implementation of the member function 'size', representing the
/// number of elements in the iterable, and the distance between 'cbegin' and 'cend'
/// \tparam __Element is the type of enclosed elements
///
/// \test Suite: TBA, Group: TBA, Test Cases: TBA
///
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <typename __Iterable, typename __Element>        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LocalRemoveByCompositeClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __RemoveByCompositeClient <__Iterable, __Element> {};
} // namespace __impl
} // namespace __hidden
} // namespace cds

#endif // __CDS_SHARED_REMOVE_BY_COMPOSITE_CLIENT_HPP__
