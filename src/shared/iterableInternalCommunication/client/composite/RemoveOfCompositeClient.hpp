//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_REMOVE_OF_COMPOSITE_CLIENT_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_SHARED_REMOVE_OF_COMPOSITE_CLIENT_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
/// \interface Interface for calling removeOf statements - removeOf / removeFirstOf / removeLastOf / removeAllOf / removeNotOf / removeFirstNotOf / removeLastNotOf / removeAllNotOf.
/// These use the iterable / initializer_list given as predicate to determine via contains which elements to keep
/// ( hence the name - 'remove' the elements 'of' - belonging also to - given iterable / initializer_list )
/// \tparam __Iterable is the type of implementor class, used for static polymorphism. <br/>
/// Implementor is also required to implement a variant of ConstIteratorRemoveClient,
/// or provide an equivalent set of member functions 'remove' and 'removeAll' provided by the client variant. <br/>
/// Implementor is also required to implement a variant of DelegateForwardConstIterbleClient,
/// or provide an equivalent set of member functions to 'cbegin' and 'cend' provided by the client variant. <br/>
/// Implementor is also required to either be derived from the Collection abstract class
/// or provide an equivalent implementation of the member function 'size', representing the
/// number of elements in the iterable, and the distance between 'cbegin' and 'cend'
/// \tparam __Element is the type of elements contained into the object
/// \tparam __FromIterable is the type of iterable expected as parameter
/// \tparam __containsFunction is the function used to identify if the given iterable contains a given function
///
/// \test Suite: CTS-00001, Group: CTG-00450-RO, Test Cases: All
///
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <
    typename                                                                __Iterable,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __Element,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __FromIterable,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__FromIterable const&, __Element const&> __containsFunction  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __RemoveOfCompositeClient {                                                             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
protected:
  /// \brief Function used to remove the elements in the caller that are found in the given iterable parameter, until a removal limit has been reached, at which point the function will stop
  /// \param [in] count : Size = the removal limit. Once this number of elements have been removed, the iteration is stopped
  /// \param [in] from : __FromIterable cref = Constant Reference to the iterable to remove the elements found in.
  /// \exceptsafe
  /// \return Size = number of elements that were removed. If the limit has been reached, the function will return the exact value of 'count'.
  ///
  /// \test Suite: CTS-00001, Group: CTG-00450-RO, Test Cases: {
  ///      CTC-00451-RO-removeOfNoneCommon,
  ///      CTC-00452-RO-removeOfOneCommon,
  ///      CTC-00453-RO-removeOfMoreLessThanLimitCommon,
  ///      CTC-00454-RO-removeOfMoreCommon,
  ///      CTC-00455-RO-removeOfMoreMoreThanLimitCommon,
  ///      CTC-00456-RO-removeOfAllCommon,
  ///      CTC-00457-RO-removeOfAllAndMoreCommon
  /// }
  /// \public
  auto removeOf (Size count, __FromIterable const& from) noexcept(false) -> Size;

  /// \brief Function used to remove the first element in the caller that is found in the given iterable parameter.
  /// \param [in] from : __FromIterable cref = Constant Reference to the iterable to remove the first element found in.
  /// \exceptsafe
  /// \return bool = true if an element was found and removed, false otherwise
  ///
  /// \test Suite: CTS-00001, Group: CTG-00450-RO, Test Cases: {
  ///      CTC-00501-RO-removeFirstOfNoneCommon,
  ///      CTC-00502-RO-removeFirstOfOneCommon,
  ///      CTC-00503-RO-removeFirstOfMoreCommon,
  ///      CTC-00504-RO-removeFirstOfAllCommon,
  ///      CTC-00505-RO-removeFirstOfAllAndMoreCommon
  /// }
  /// \public
  auto removeFirstOf (__FromIterable const& from) noexcept(false) -> bool;

  /// \brief Function used to remove the last element in the caller that is found in the given iterable parameter.
  /// \param [in] from : __FromIterable cref = Constant Reference to the iterable to remove the last element found in.
  /// \exceptsafe
  /// \return bool = true if an element was found and removed, false otherwise
  ///
  /// \test Suite: CTS-00001, Group: CTG-00450-RO, Test Cases: {
  ///      CTC-00506-RO-removeLastOfNoneCommon,
  ///      CTC-00507-RO-removeLastOfOneCommon,
  ///      CTC-00508-RO-removeLastOfMoreCommon,
  ///      CTC-00509-RO-removeLastOfAllCommon,
  ///      CTC-00510-RO-removeLastOfAllAndMoreCommon
  /// }
  /// \public
  auto removeLastOf (__FromIterable const& from) noexcept(false) -> bool;

  /// \brief Function used to remove all the elements in the caller that are found in the given iterable parameter.
  /// \param [in] from : __FromIterable cref = Constant Reference to the iterable to remove the elements found in.
  /// \exceptsafe
  /// \return Size = the number of elements removed from the caller iterable
  ///
  /// \test Suite: CTS-00001, Group: CTG-00450-RO, Test Cases: {
  ///      CTC-00481-RO-removeAllOfNoneCommon,
  ///      CTC-00482-RO-removeAllOfOneCommon,
  ///      CTC-00483-RO-removeAllOfMoreCommon,
  ///      CTC-00484-RO-removeAllOfAllCommon,
  ///      CTC-00485-RO-removeAllOfAllAndMoreCommon
  /// }
  /// \public
  auto removeAllOf (__FromIterable const& from) noexcept(false) -> Size;

  /// \brief Function used to remove the elements in the caller that not are found in the given iterable parameter, until a removal limit has been reached, at which point the function will stop
  /// \param [in] count : Size = the removal limit. Once this number of elements have been removed, the iteration is stopped
  /// \param [in] from : __FromIterable cref = Constant Reference to the iterable to remove the elements not found in.
  /// \exceptsafe
  /// \return Size = number of elements that were removed. If the limit has been reached, the function will return the exact value of 'count'.
  ///
  /// \test Suite: CTS-00001, Group: CTG-00450-RO, Test Cases: {
  ///      CTC-00458-RO-removeNotOfNoneCommon,
  ///      CTC-00459-RO-removeNotOfOneCommon,
  ///      CTC-00460-RO-removeNotOfMoreLessThanLimitCommon,
  ///      CTC-00461-RO-removeNotOfMoreCommon,
  ///      CTC-00462-RO-removeNotOfMoreMoreThanLimitCommon,
  ///      CTC-00463-RO-removeNotOfAllCommon,
  ///      CTC-00464-RO-removeNotOfAllAndMoreCommon
  /// }
  /// \public
  auto removeNotOf (Size count, __FromIterable const& from) noexcept(false) -> Size;

  /// \brief Function used to remove the first element in the caller that is not found in the given iterable parameter.
  /// \param [in] from : __FromIterable cref = Constant Reference to the iterable to remove the first element not found in.
  /// \exceptsafe
  /// \return bool = true if an element was found and removed, false otherwise
  ///
  /// \test Suite: CTS-00001, Group: CTG-00450-RO, Test Cases: {
  ///      CTC-00511-RO-removeFirstNotOfNoneCommon,
  ///      CTC-00512-RO-removeFirstNotOfOneCommon,
  ///      CTC-00513-RO-removeFirstNotOfMoreCommon,
  ///      CTC-00514-RO-removeFirstNotOfAllCommon,
  ///      CTC-00515-RO-removeFirstNotOfAllAndMoreCommon
  /// }
  /// \public
  auto removeFirstNotOf (__FromIterable const& from) noexcept(false) -> bool;

  /// \brief Function used to remove the last element in the caller that is not found in the given iterable parameter.
  /// \param [in] from : __FromIterable cref = Constant Reference to the iterable to remove the last element not found in.
  /// \exceptsafe
  /// \return bool = true if an element was found and removed, false otherwise
  ///
  /// \test Suite: CTS-00001, Group: CTG-00450-RO, Test Cases: {
  ///      CTC-00516-RO-removeLastNotOfNoneCommon,
  ///      CTC-00517-RO-removeLastNotOfOneCommon,
  ///      CTC-00518-RO-removeLastNotOfMoreCommon,
  ///      CTC-00519-RO-removeLastNotOfAllCommon,
  ///      CTC-00520-RO-removeLastNotOfAllAndMoreCommon
  /// }
  /// \public
  auto removeLastNotOf (__FromIterable const& from) noexcept(false) -> bool;

  /// \brief Function used to remove all the elements in the caller that are not found in the given iterable parameter.
  /// \param [in] from : __FromIterable cref = Constant Reference to the iterable to remove the elements not found in.
  /// \exceptsafe
  /// \return Size = the number of elements removed from the caller iterable
  ///
  /// \test Suite: CTS-00001, Group: CTG-00450-RO, Test Cases: {
  ///      CTC-00486-RO-removeAllNotOfNoneCommon,
  ///      CTC-00487-RO-removeAllNotOfOneCommon,
  ///      CTC-00488-RO-removeAllNotOfMoreCommon,
  ///      CTC-00489-RO-removeAllNotOfAllCommon,
  ///      CTC-00490-RO-removeAllNotOfAllAndMoreCommon
  /// }
  /// \public
  auto removeAllNotOf (__FromIterable const& from) noexcept(false) -> Size;

private:
  /// \brief Function used in removeOf in the case of a self-referential remove ( removeOf with caller as parameter ).
  /// Will remove begin for count times, unless count >= size, when it will just call clear.
  /// \param [in] count : Size = the removal limit. Once this number of elements have been removed, the iteration is stopped
  /// \param [in] from : __FromIterable cref = Constant Reference to the iterable to remove the elements found in. In this call, 'from' must be 'this'
  /// \exceptsafe
  /// \return Size = number of elements that were removed. If the limit has been reached, the function will return the exact value of 'count'.
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \private
  auto __iro_selfReferentialCase_removeOf (Size count, __FromIterable const& from) noexcept(false) -> Size; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \brief Function used in removeFirstOf in the case of a self-referential remove ( removeOf with caller as parameter ).
  /// Will remove begin once.
  /// \param [in] from : __FromIterable cref = Constant Reference to the iterable to remove the elements found in. In this call, 'from' must be 'this'
  /// \exceptsafe
  /// \return bool = true if removal successful, false otherwise. Will yield 'true' if iterable is not empty
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \private
  auto __iro_selfReferentialCase_removeFirstOf (__FromIterable const& from) noexcept(false) -> bool;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \brief Function used in removeLastOf in the case of a self-referential remove ( removeOf with caller as parameter ).
  /// Will remove last element once.
  /// \param [in] from : __FromIterable cref = Constant Reference to the iterable to remove the elements found in. In this call, 'from' must be 'this'
  /// \exceptsafe
  /// \return bool = true if removal successful, false otherwise. Will yield 'true' if iterable is not empty
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \private
  auto __iro_selfReferentialCase_removeLastOf (__FromIterable const& from) noexcept(false) -> bool;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \brief Function used in removeAllOf in the case of a self-referential remove ( removeOf with caller as parameter ).
  /// Will clear the collection and return the size before clear
  /// \param [in] from : __FromIterable cref = Constant Reference to the iterable to remove the elements found in. In this call, 'from' must be 'this'
  /// \exceptsafe
  /// \return Size = number of removed elements ( equivalent to this->size() before remove )
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \private
  auto __iro_selfReferentialCase_removeAllOf (__FromIterable const& from) noexcept(false) -> Size;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \brief Function used in removeNotOf in the case of a self-referential remove ( removeOf with caller as parameter ).
  /// Will do nothing.
  /// \param [in] count : Size = the removal limit. Once this number of elements have been removed, the iteration is stopped
  /// \param [in] from : __FromIterable cref = Constant Reference to the iterable to remove the elements found in. In this call, 'from' must be 'this'
  /// \exceptsafe
  /// \return Size = always 0
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \private
  auto __iro_selfReferentialCase_removeNotOf (Size count, __FromIterable const& from) noexcept(false) -> Size;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \brief Function used in removeFirstNotOf in the case of a self-referential remove ( removeOf with caller as parameter ).
  /// Will do nothing.
  /// \param [in] from : __FromIterable cref = Constant Reference to the iterable to remove the elements found in. In this call, 'from' must be 'this'
  /// \exceptsafe
  /// \return bool = always 'false'
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \private
  auto __iro_selfReferentialCase_removeFirstNotOf (__FromIterable const& from) noexcept(false) -> bool; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \brief Function used in removeLastNotOf in the case of a self-referential remove ( removeOf with caller as parameter ).
  /// Will do nothing.
  /// \param [in] from : __FromIterable cref = Constant Reference to the iterable to remove the elements found in. In this call, 'from' must be 'this'
  /// \exceptsafe
  /// \return bool = always 'false'
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \private
  auto __iro_selfReferentialCase_removeLastNotOf (__FromIterable const& from) noexcept(false) -> bool;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \brief Function used in removeAllNotOf in the case of a self-referential remove ( removeOf with caller as parameter ).
  /// Will do nothing.
  /// \param [in] from : __FromIterable cref = Constant Reference to the iterable to remove the elements found in. In this call, 'from' must be 'this'
  /// \exceptsafe
  /// \return Size = always 0
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \private
  auto __iro_selfReferentialCase_removeAllNotOf (__FromIterable const& from) noexcept(false) -> Size; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};


/// \typedef Variant of RemoveOfCompositeClient, only alias due to it being a composite client
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
/// \tparam __FromIterable is the type of iterable expected as parameter
/// \tparam __containsFunction is the function used to identify if the given iterable contains a given function
///
/// \test Suite: TBA, Group: TBA, Test Cases: TBA
///
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <
    typename                                                                __Iterable,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __Element,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                __FromIterable,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__FromIterable const&, __Element const&> __containsFunction  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __LocalRemoveOfCompositeClient :                                     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __RemoveOfCompositeClient <__Iterable, __Element, __FromIterable, __containsFunction> {};
} // namespace __impl
} // namespace __hidden
} // namespace cds

#endif // __CDS_SHARED_REMOVE_OF_COMPOSITE_CLIENT_HPP__
