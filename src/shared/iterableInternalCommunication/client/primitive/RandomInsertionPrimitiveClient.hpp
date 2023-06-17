//
// Created by loghin on 6/28/22.
//

#ifndef __CDS_SHARED_RANDOM_INSERTION_PRIMITIVE_CLIENT_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_SHARED_RANDOM_INSERTION_PRIMITIVE_CLIENT_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace meta {
/// \struct Meta-Type used to determine if a given type has the 'size' function available. By default false
/// \tparam __Iterable is the type to be checked
/// \test Not Applicable
/// \namespace cds::__hidden::__impl::meta
/// \internal library-private
template <typename __Iterable, typename = void>           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __IterableSizeAvailable : cds::meta::FalseType {};   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

/// \struct Meta-Type used to determine if a given type has the 'size' function available. True when type can call size()
/// \tparam __Iterable is the type to be checked
/// \test Not Applicable
/// \namespace cds::__hidden::__impl::meta
/// \internal library-private
template <typename __Iterable>                                                                                                                                            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __IterableSizeAvailable <__Iterable, cds::meta::Void <decltype (cds::meta::addressOf <__Iterable>()->size())>> : cds::meta::TrueType {};    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
} // namespace meta

/// \struct Meta-Type used to determine the noexcept specification of a function calling multiple constructions of given __Element
/// \tparam __Element is the type of element constructed to check for construction noexcept specification
/// \tparam __FirstConstructedArgument is the type of parameter given to constructor
/// \test Not Applicable
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <typename __Element, typename __FirstConstructedArgument>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __ConstructExceptSpecOne {                                   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  // the value is the noexcept value of the constructor call
  constexpr static bool value = noexcept (__Element (cds::meta::valueOf <__FirstConstructedArgument>()));
};


/// \struct Meta-Type used to determine the noexcept specification of a function calling multiple constructions of given __Element
/// \tparam __Element is the type of element constructed to check for construction noexcept specification
/// \tparam __FirstConstructedArgument is the type of the first parameter given to construction
/// \tparam __RemainingConstructedArguments is the parameter type pack of the remaining parameters given to construction
/// \test Not Applicable
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <typename __Element, typename __FirstConstructedArgument, typename...__RemainingConstructedArguments>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __ConstructExceptSpecMultiple;                                                                           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)


/// \struct Meta-Type used to determine the noexcept specification of a function calling multiple constructions of given __Element
/// \tparam __Element is the type of element constructed to check for construction noexcept specification
/// \tparam __FirstConstructedArgument is the type of the first parameter given to construction
/// \test Not Applicable
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <typename __Element, typename __FirstConstructedArgument>              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __ConstructExceptSpecMultiple <__Element, __FirstConstructedArgument> : __ConstructExceptSpecOne <__Element, __FirstConstructedArgument> {};


/// \struct Meta-Type used to determine the noexcept specification of a function calling multiple constructions of given __Element
/// \tparam __Element is the type of element constructed to check for construction noexcept specification
/// \tparam __FirstConstructedArgument is the type of the first parameter given to construction
/// \tparam __RemainingConstructedArguments is the parameter type pack of the remaining parameters given to construction
/// \test Not Applicable
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <typename __Element, typename __FirstConstructedArgument, typename...__RemainingConstructedArguments>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
struct __ConstructExceptSpecMultiple : cds::meta::And <__ConstructExceptSpecOne <__Element, __FirstConstructedArgument>, __ConstructExceptSpecMultiple <__Element, __RemainingConstructedArguments...>> {};


/// \brief Function used to insert multiple elements of a parameter pack into a given accumulator value
///
/// \tparam __Accumulator is the type of value to insert the elements into
/// \tparam __Last is the type of the last value inserted into the accumulator
///
/// \param [out] pAccumulator : __Accumulator ptr = pointer to the accumulator to insert the last value into
/// \param [in] lastValue : __Last fref = Forwarding Reference to the last value to be added
/// \excetpsafe if construction of element is exceptsafe and collection supports insertion
///
/// \test Suite: CTS-00001, Group: CTG-00800-RI, Test Cases: { CTC-00804-RI-insertByPack }
/// \test Suite: MCTS-00001, Group: MCTG-00800-RI, Test Cases: { MCTC-00804-RI-insertByPack }
///
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <typename __Accumulator, typename __Last>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __expansiveInsert (__Accumulator* pAccumulator, __Last&& lastValue) noexcept(false) -> void;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)


/// \brief Function used to insert multiple elements of a parameter pack into a given accumulator value
///
/// \tparam __Accumulator is the type of value to insert the elements into
/// \tparam __First is the type of the first value in the pack inserted into the accumulator
/// \tparam __Remaining is the type pack of the remaining values in the original pack to be inserted into the accumulator
///
/// \param [out] pAccumulator : __Accumulator ptr = pointer to the accumulator to insert the last value into
/// \param [in] firstValue : __First fref = Forwarding Reference to the first value to be added
/// \param [in] remainingValues : __Remaining fref ... = Pack of Forwarding References to the remaining values from the pack to be added in subsequent calls
/// \excetpsafe if construction of element is exceptsafe and collection supports insertion
///
/// \test Suite: CTS-00001, Group: CTG-00800-RI, Test Cases: { CTC-00804-RI-insertByPack }
/// \test Suite: MCTS-00001, Group: MCTG-00800-RI, Test Cases: { MCTC-00804-RI-insertByPack }
///
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <typename __Accumulator, typename __First, typename...__Remaining>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __expansiveInsert (__Accumulator* pAccumulator, __First&& firstValue, __Remaining&&... remainingValues) noexcept(false) -> void;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)


/// \interface Interface for creating Random Insertion requests, inserting / emplacing elements without a specified location.
/// \tparam __Receiver is the type of implementor class, used for static polymorphism.
/// Implementor is required to either be derived from the Collection abstract class or a class
/// extending the __CollectionInternalCommunicationChannel class, or provide equivalent member
/// function implementations provided by the __collectionInternalCommunicationChannel class
/// Note : This Client will request the member functions identified with:
///      __cirt_newAddress
///
/// \tparam __Element is the type of elements contained into the Object
/// \tparam __Return is the type returned by the singular insertion functions
///
/// \test Suite: CTS-00001, Group: CTG-00800-RI, Test Cases: All
/// \test Suite: MCTS-00001, Group: MCTG-00800-RI, Test Cases: All
///
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __RandomInsertionPrimitiveClient {                              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
public:
  /// \typedef alias for __Element template parameter
  /// \private
  using ElementType       = __Element;

  /// \typedef alias for __Return template parameter reference
  /// \private
  using ElementReference  = __Return&;

  /// \brief Function used to create a request to insert an element into the receiver
  /// \tparam __TElementType is an alias to __Element, used to disable the function when the given type does not implement a copy constructor
  /// \param [in] element : ElementType cref = Constant Reference to the element to be inserted in the object via copy
  /// \exceptsafe if ElementType is exceptsafe copy constructible and if ReceiverType does not throw at insert request
  /// \return ElementReference = Reference to an element, new or non-replaceable, const or not, depending on use-case.
  ///
  /// \test Suite: CTS-00001, Group: CTG-00800-RI, Test Cases: {
  ///      CTC-00801-RI-insertByCopy
  /// }
  ///
  /// \test Suite: MCTS-00001, Group: MCTG-00800-RI, Test Cases: {
  ///      MCTC-00801-RI-insertByCopy
  /// }
  ///
  /// \public
  template <
      typename __TElementType = ElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value> = 0
  > auto insert (ElementType const& element) noexcept(false) -> ElementReference;

  /// \brief Function used to create a request to insert an element into the receiver
  /// \tparam __TElementType is an alias to __Element, used to disable the function when the given type does not implement a move constructor
  /// \param [in] element : ElementType mref = Move Reference to the element to be inserted in the object via move
  /// \exceptsafe if ElementType is exceptsafe move constructible and if ReceiverType does not throw at insert request
  /// \return ElementReference = Reference to an element, new or non-replaceable, const or not, depending on use-case.
  ///
  /// \test Suite: CTS-00001, Group: CTG-00800-RI, Test Cases: {
  ///      CTC-00802-RI-insertByMove
  /// }
  ///
  /// \test Suite: MCTS-00001, Group: MCTG-00800-RI, Test Cases: {
  ///      MCTC-00802-RI-insertByMove
  /// }
  ///
  /// \public
  template <
      typename __TElementType = ElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::EnableIf <cds::meta::IsMoveConstructible <__TElementType>::value> = 0
  > auto insert (ElementType&& element) noexcept(false) -> ElementReference;

  /// \deprecated 'add' function deprecated, kept for support. replaced by 'insert', same functionality
  /// \brief Function used to create a request to insert an element into the receiver.
  /// \tparam __TElementType is an alias to __Element, used to disable the function when the given type does not implement a copy constructor
  /// \param [in] element : ElementType cref = Constant Reference to the element to be inserted in the object via copy
  /// \exceptsafe if ElementType is exceptsafe copy constructible and if ReceiverType does not throw at insert request
  /// \return ElementReference = Reference to an element, new or non-replaceable, const or not, depending on use-case.
  ///
  /// \test Suite: CTS-00001, Group: CTG-00800-RI, Test Cases: {
  ///      CTC-00801-RI-insertByCopy
  /// }
  ///
  /// \test Suite: CTS-00001, Group: MCTG-00800-RI, Test Cases: {
  ///      MCTC-00801-RI-insertByCopy
  /// }
  ///
  /// \public
  template <
      typename __TElementType = ElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value> = 0
  > __CDS_DeprecatedHint ("'Collection::add' has been deprecated. Use 'Collection::insert' instead") 
  auto add (ElementType const& element) noexcept(false) -> ElementReference;

  /// \deprecated 'add' function deprecated, kept for support. replaced by 'insert', same functionality
  /// \brief Function used to create a request to insert an element into the receiver
  /// \tparam __TElementType is an alias to __Element, used to disable the function when the given type does not implement a move constructor
  /// \param [in] element : ElementType mref = Move Reference to the element to be inserted in the object via move
  /// \exceptsafe if ElementType is exceptsafe move constructible and if ReceiverType does not throw at insert request
  /// \return ElementReference = Reference to an element, new or non-replaceable, const or not, depending on use-case.
  ///
  /// \test Suite: CTS-00001, Group: CTG-00800-RI, Test Cases: {
  ///      CTC-00802-RI-insertByMove
  /// }
  ///
  /// \test Suite: MCTS-00001, Group: MCTG-00800-RI, Test Cases: {
  ///      MCTC-00802-RI-insertByMove
  /// }
  ///
  /// \public
  template <
      typename __TElementType = ElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::EnableIf <cds::meta::IsMoveConstructible <__TElementType>::value> = 0
  > __CDS_DeprecatedHint ("'Collection::add' has been deprecated. Use 'Collection::insert' instead") 
  auto add (ElementType&& element) noexcept(false) -> ElementReference;

  /// \brief Function used to create a request to emplace an element ( construct with given parameters ) into the receiver
  /// \tparam __Arguments is the type pack of the construction argument types
  /// \param [in] parameters : __Arguments fref ... = Pack of forwarding references to given parameters for element emplace construction
  /// \exceptsafe if ElementType is exceptsafe move constructible and if ReceiverType does not throw at insert request
  /// \return ElementReference = Reference to an element, new or non-replaceable, const or not, depending on use-case.
  ///
  /// \test Suite: CTS-00001, Group: CTG-00800-RI, Test Cases: {
  ///      CTC-00803-RI-insertByEmplace
  /// }
  ///
  /// \test Suite: MCTS-00001, Group: MCTG-00800-RI, Test Cases: {
  ///      MCTC-00803-RI-insertByEmplace
  /// }
  ///
  /// \public
  template <typename...__Arguments> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto emplace (__Arguments&&... parameters) noexcept(false) -> ElementReference;

  /// \brief Function used to insert multiple elements by creating multiple insert requests into the receiver
  /// \tparam __Arguments is the type pack of the values to be inserted
  /// \param [in] values : __Arguments fref ... = Pack of forwarding elements to values, each of the pack to be transformed into an Element via construction and inserted
  /// \exceptsafe if ElementType is exceptsafe constructible and if ReceiverType does not throw at insert request.
  ///
  /// \test Suite: CTS-00001, Group: CTG-00800-RI, Test Cases: {
  ///      CTC-00804-RI-insertByPack
  /// }
  ///
  /// \test Suite: MCTS-00001, Group: MCTG-00800-RI, Test Cases: {
  ///      MCTC-00804-RI-insertByPack
  /// }
  ///
  /// \public
  template <typename...__Arguments> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto insertAll (__Arguments&&... values) noexcept(false) -> void;

  /// \deprecated 'addAll' function deprecated, kept for support. replaced by 'insertAll', same functionality
  /// \brief Function used to insert multiple elements by creating multiple insert requests into the receiver
  /// \tparam __Arguments is the type pack of the values to be inserted
  /// \param [in] values : __Arguments fref ... = Pack of forwarding elements to values, each of the pack to be transformed into an Element via construction and inserted
  /// \exceptsafe if ElementType is exceptsafe constructible and if ReceiverType does not throw at insert request.
  ///
  /// \test Suite: CTS-00001, Group: CTG-00800-RI, Test Cases: {
  ///      CTC-00804-RI-insertByPack
  /// }
  ///
  /// \test Suite: MCTS-00001, Group: MCTG-00800-RI, Test Cases: {
  ///      MCTC-00804-RI-insertByPack
  /// }
  ///
  /// \public
  template <typename...__Arguments> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_DeprecatedHint ("'Collection::addAll' has been deprecated. Use 'Collection::insertAll' instead")
  auto addAll (__Arguments&&... values) noexcept(false) -> void;

  /// \brief Function used to insert multiple elements by extracting each from a given iterable and inserting each into the receiver
  /// \tparam __Iterable is the type of iterable given as parameter
  /// \param [in] iterable : __Iterable cref = Constant Reference to the iterable to extract the values from
  /// \exceptsafe if ElementType is exceptsafe constructible and if ReceiverType does not throw at insert request.
  ///
  /// \test Suite: CTS-00001, Group: CTG-00800-RI, Test Cases: {
  ///      CTC-00805-RI-insertByInsertAllIterable
  /// }
  ///
  /// \test Suite: MCTS-00001, Group: MCTG-00800-RI, Test Cases: {
  ///      MCTC-00805-RI-insertByInsertAllIterable
  /// }
  ///
  /// \public
  template <typename __Iterable> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto insertAllOf (__Iterable const& iterable) noexcept(false) -> void;

  /// \brief Function used to insert multiple elements by extracting each from a given initializer list and inserting each into the receiver
  /// \tparam __TElementType is an alias to __Element, used to disable the function when the given type does not implement a move constructor
  /// \param [in] list : std::initializer_list cref = Constant Reference to the initializer list to extract the values from
  /// \exceptsafe if ElementType is exceptsafe copy constructible and if ReceiverType does not throw at insert request.
  ///
  /// \test Suite: CTS-00001, Group: CTG-00800-RI, Test Cases: {
  ///      CTC-00805-RI-insertByInsertAllList
  /// }
  ///
  /// \test Suite: MCTS-00001, Group: MCTG-00800-RI, Test Cases: {
  ///      MCTC-00805-RI-insertByInsertAllList
  /// }
  ///
  /// \public
  template <
      typename __TElementType = __Element, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value> = 0
  > auto insertAllOf (std::initializer_list <__Element> const& list) noexcept(false) -> void;

  /// \deprecated 'addAllOf' function deprecated, kept for support. replaced by 'insertAllOf', same functionality
  /// \brief Function used to insert multiple elements by extracting each from a given iterable and inserting each into the receiver
  /// \tparam __Iterable is the type of iterable given as parameter
  /// \param [in] iterable : __Iterable cref = Constant Reference to the iterable to extract the values from
  /// \exceptsafe if ElementType is exceptsafe constructible and if ReceiverType does not throw at insert request.
  ///
  /// \test Suite: CTS-00001, Group: CTG-00800-RI, Test Cases: {
  ///      CTC-00805-RI-insertByInsertAllIterable
  /// }
  ///
  /// \test Suite: MCTS-00001, Group: MCTG-00800-RI, Test Cases: {
  ///      MCTC-00805-RI-insertByInsertAllIterable
  /// }
  ///
  /// \public
  template <typename __Iterable> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_DeprecatedHint ("'Collection::addAllOf' has been deprecated. Use 'Collection::insertAllOf' instead")
  auto addAllOf (__Iterable const& iterable) noexcept(false) -> void;

  /// \deprecated 'addAllOf' function deprecated, kept for support. replaced by 'insertAllOf', same functionality
  /// \brief Function used to insert multiple elements by extracting each from a given initializer list and inserting each into the receiver
  /// \tparam __TElementType is an alias to __Element, used to disable the function when the given type does not implement a move constructor
  /// \param [in] list : std::initializer_list cref = Constant Reference to the initializer list to extract the values from
  /// \exceptsafe if ElementType is exceptsafe copy constructible and if ReceiverType does not throw at insert request.
  ///
  /// \test Suite: CTS-00001, Group: CTG-00800-RI, Test Cases: {
  ///      CTC-00805-RI-insertByInsertAllList
  /// }
  ///
  /// \test Suite: MCTS-00001, Group: MCTG-00800-RI, Test Cases: {
  ///      MCTC-00805-RI-insertByInsertAllList
  /// }
  ///
  /// \public
  template <
      typename __TElementType = __Element, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value> = 0
  > __CDS_DeprecatedHint ("'Collection::addAllOf' has been deprecated. Use 'Collection::insertAllOf' instead")
  auto addAllOf (std::initializer_list <__Element> const& list) noexcept(false) -> void;

  /// \brief Function used to insert multiple elements by extracting each from a given iterator range and inserting each into the receiver
  /// \tparam __Iterator is the type of given iterators
  /// \param [in] begin : __Iterator cref = Constant Reference to the begin iterator of the range
  /// \param [in] end : __Iterator cref = Constant Reference to the end iterator of the range
  /// \exceptsafe if ElementType is exceptsafe constructible and if ReceiverType does not throw at insert request.
  ///
  /// \test Suite: CTS-00001, Group: CTG-00800-RI, Test Cases: {
  ///      CTC-00807-RI-insertByRange1,
  ///      CTC-00808-RI-insertByRange2,
  ///      CTC-00809-RI-insertByRange3
  /// }
  ///
  /// \test Suite: MCTS-00001, Group: MCTG-00800-RI, Test Cases: {
  ///      MCTC-00807-RI-insertByRange1,
  ///      MCTC-00808-RI-insertByRange2,
  ///      MCTC-00809-RI-insertByRange3
  /// }
  ///
  /// \public
  template <typename __Iterator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto insertAllOf (__Iterator const& begin, __Iterator const& end) noexcept(false) -> void;

  /// \deprecated 'addAllOf' function deprecated, kept for support. replaced by 'insertAllOf', same functionality
  /// \brief Function used to insert multiple elements by extracting each from a given iterator range and inserting each into the receiver
  /// \tparam __Iterator is the type of given iterators
  /// \param [in] begin : __Iterator cref = Constant Reference to the begin iterator of the range
  /// \param [in] end : __Iterator cref = Constant Reference to the end iterator of the range
  /// \exceptsafe if ElementType is exceptsafe constructible and if ReceiverType does not throw at insert request.
  ///
  /// \test Suite: CTS-00001, Group: CTG-00800-RI, Test Cases: {
  ///      CTC-00807-RI-insertByRange1,
  ///      CTC-00808-RI-insertByRange2,
  ///      CTC-00809-RI-insertByRange3
  /// }
  ///
  /// \test Suite: MCTS-00001, Group: MCTG-00800-RI, Test Cases: {
  ///      MCTC-00807-RI-insertByRange1,
  ///      MCTC-00808-RI-insertByRange2,
  ///      MCTC-00809-RI-insertByRange3
  /// }
  ///
  /// \public
  template <typename __Iterator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_DeprecatedHint ("'Collection::addAllOf' has been deprecated. Use 'Collection::insertAllOf' instead") 
  auto addAllOf (__Iterator const& begin, __Iterator const& end) noexcept(false) -> void;

private:
  /// \brief Friend declaration of the function to allow usage of insert from caller object
  /// \private
  template <typename __Accumulator, typename __Last>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  friend auto __expansiveInsert (__Accumulator* pAccumulator, __Last&& lastValue) noexcept(false) -> void; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \brief Friend declaration of the function to allow usage of insert from caller object
  /// \private
  template <typename __Accumulator, typename __First, typename...__Remaining> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  friend auto __expansiveInsert (__Accumulator* pAccumulator, __First&& firstValue, __Remaining&&... remainingValues) noexcept(false) -> void;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};


/// \interface Interface for creating Local Random Insertion requests, inserting / emplacing elements without a specified location.
/// \tparam __Receiver is the type of implementor class, used for static polymorphism.
/// Implementor is required to either implement an appropriate dispatcher ( __CollectionServerDispatcher or lower
/// in hierarchy ) or provide an equivalent __newAddress member function to the one provided by the dispatcher
///
/// \tparam __Element is the type of elements contained into the Object
/// \tparam __Return is the type returned by the singular insertion functions
///
/// \test Suite: TBA, Group: TBA, Test Cases: TBA
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <typename __Receiver, typename __Element, typename __Return> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __LocalRandomInsertionPrimitiveClient {                         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
public:
  /// \typedef alias for __Element template parameter
  /// \private
  using ElementType       = __Element;

  /// \typedef alias for __Return template parameter reference
  /// \private
  using ElementReference  = __Return&;
  
  /// \brief Function used to create a request to insert an element into the receiver
  /// \tparam __TElementType is an alias to __Element, used to disable the function when the given type does not implement a copy constructor
  /// \param [in] element : ElementType cref = Constant Reference to the element to be inserted in the object via copy
  /// \exceptsafe if ElementType is exceptsafe copy constructible and if ReceiverType does not throw at insert request
  /// \return ElementReference = Reference to an element, new or non-replaceable, const or not, depending on use-case.
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  ///
  /// \public
  template <
      typename __TElementType = ElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value> = 0
  > auto insert (ElementType const& element) noexcept(false) -> ElementReference;

  /// \brief Function used to create a request to insert an element into the receiver
  /// \tparam __TElementType is an alias to __Element, used to disable the function when the given type does not implement a move constructor
  /// \param [in] element : ElementType mref = Move Reference to the element to be inserted in the object via move
  /// \exceptsafe if ElementType is exceptsafe move constructible and if ReceiverType does not throw at insert request
  /// \return ElementReference = Reference to an element, new or non-replaceable, const or not, depending on use-case.
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  ///
  /// \public
  template <
      typename __TElementType = ElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::EnableIf <cds::meta::IsMoveConstructible <__TElementType>::value> = 0
  > auto insert (ElementType&& element) noexcept(false) -> ElementReference;

  /// \deprecated 'add' function deprecated, kept for support. replaced by 'insert', same functionality
  /// \brief Function used to create a request to insert an element into the receiver.
  /// \tparam __TElementType is an alias to __Element, used to disable the function when the given type does not implement a copy constructor
  /// \param [in] element : ElementType cref = Constant Reference to the element to be inserted in the object via copy
  /// \exceptsafe if ElementType is exceptsafe copy constructible and if ReceiverType does not throw at insert request
  /// \return ElementReference = Reference to an element, new or non-replaceable, const or not, depending on use-case.
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  ///
  /// \public
  template <
      typename __TElementType = ElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value> = 0
  > __CDS_DeprecatedHint ("'Collection::add' has been deprecated. Use 'Collection::insert' instead")
  auto add (ElementType const& element) noexcept(false) -> ElementReference;

  /// \deprecated 'add' function deprecated, kept for support. replaced by 'insert', same functionality
  /// \brief Function used to create a request to insert an element into the receiver
  /// \tparam __TElementType is an alias to __Element, used to disable the function when the given type does not implement a move constructor
  /// \param [in] element : ElementType mref = Move Reference to the element to be inserted in the object via move
  /// \exceptsafe if ElementType is exceptsafe move constructible and if ReceiverType does not throw at insert request
  /// \return ElementReference = Reference to an element, new or non-replaceable, const or not, depending on use-case.
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  ///
  /// \public
  template <
      typename __TElementType = ElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::EnableIf <cds::meta::IsMoveConstructible <__TElementType>::value> = 0
  > __CDS_DeprecatedHint ("'Collection::add' has been deprecated. Use 'Collection::insert' instead")
  auto add (ElementType&& element) noexcept(false) -> ElementReference;

  /// \brief Function used to create a request to emplace an element ( construct with given parameters ) into the receiver
  /// \tparam __Arguments is the type pack of the construction argument types
  /// \param [in] parameters : __Arguments fref ... = Pack of forwarding references to given parameters for element emplace construction
  /// \exceptsafe if ElementType is exceptsafe move constructible and if ReceiverType does not throw at insert request
  /// \return ElementReference = Reference to an element, new or non-replaceable, const or not, depending on use-case.
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  ///
  /// \public
  template <typename...__Arguments> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto emplace (__Arguments&&... parameters) noexcept(false) -> ElementReference;

  /// \brief Function used to insert multiple elements by creating multiple insert requests into the receiver
  /// \tparam __Arguments is the type pack of the values to be inserted
  /// \param [in] values : __Arguments fref ... = Pack of forwarding elements to values, each of the pack to be transformed into an Element via construction and inserted
  /// \exceptsafe if ElementType is exceptsafe constructible and if ReceiverType does not throw at insert request.
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  ///
  /// \public
  template <typename...__Arguments> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto insertAll (__Arguments&&... values) noexcept(false) -> void;

  /// \deprecated 'addAll' function deprecated, kept for support. replaced by 'insertAll', same functionality
  /// \brief Function used to insert multiple elements by creating multiple insert requests into the receiver
  /// \tparam __Arguments is the type pack of the values to be inserted
  /// \param [in] values : __Arguments fref ... = Pack of forwarding elements to values, each of the pack to be transformed into an Element via construction and inserted
  /// \exceptsafe if ElementType is exceptsafe constructible and if ReceiverType does not throw at insert request.
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  ///
  /// \public
  template <typename...__Arguments> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_DeprecatedHint ("'Collection::addAll' has been deprecated. Use 'Collection::insertAll' instead") 
  auto addAll (__Arguments&&... values) noexcept(false) -> void;

  /// \brief Function used to insert multiple elements by extracting each from a given iterable and inserting each into the receiver
  /// \tparam __Iterable is the type of iterable given as parameter
  /// \param [in] iterable : __Iterable cref = Constant Reference to the iterable to extract the values from
  /// \exceptsafe if ElementType is exceptsafe constructible and if ReceiverType does not throw at insert request.
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  ///
  /// \public
  template <typename __Iterable> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto insertAllOf (__Iterable const& iterable) noexcept(false) -> void;

  /// \brief Function used to insert multiple elements by extracting each from a given initializer list and inserting each into the receiver
  /// \tparam __TElementType is an alias to __Element, used to disable the function when the given type does not implement a move constructor
  /// \param [in] list : std::initializer_list cref = Constant Reference to the initializer list to extract the values from
  /// \exceptsafe if ElementType is exceptsafe copy constructible and if ReceiverType does not throw at insert request.
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  ///
  /// \public
  template <
      typename __TElementType = __Element, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value> = 0
  > auto insertAllOf (std::initializer_list <__Element> const& list) noexcept(false) -> void;

  /// \deprecated 'addAllOf' function deprecated, kept for support. replaced by 'insertAllOf', same functionality
  /// \brief Function used to insert multiple elements by extracting each from a given iterable and inserting each into the receiver
  /// \tparam __Iterable is the type of iterable given as parameter
  /// \param [in] iterable : __Iterable cref = Constant Reference to the iterable to extract the values from
  /// \exceptsafe if ElementType is exceptsafe constructible and if ReceiverType does not throw at insert request.
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  ///
  /// \public
  template <typename __Iterable> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_DeprecatedHint ("'Collection::addAllOf' has been deprecated. Use 'Collection::insertAllOf' instead") 
  auto addAllOf (__Iterable const& iterable) noexcept(false) -> void;

  /// \deprecated 'addAllOf' function deprecated, kept for support. replaced by 'insertAllOf', same functionality
  /// \brief Function used to insert multiple elements by extracting each from a given initializer list and inserting each into the receiver
  /// \tparam __TElementType is an alias to __Element, used to disable the function when the given type does not implement a move constructor
  /// \param [in] list : std::initializer_list cref = Constant Reference to the initializer list to extract the values from
  /// \exceptsafe if ElementType is exceptsafe copy constructible and if ReceiverType does not throw at insert request.
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  ///
  /// \public
  template <
      typename __TElementType = __Element, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value> = 0
  > __CDS_DeprecatedHint ("'Collection::addAllOf' has been deprecated. Use 'Collection::insertAllOf' instead")
  auto addAllOf (std::initializer_list <__Element> const& list) noexcept(false) -> void;

  /// \brief Function used to insert multiple elements by extracting each from a given iterator range and inserting each into the receiver
  /// \tparam __Iterator is the type of given iterators
  /// \param [in] begin : __Iterator cref = Constant Reference to the begin iterator of the range
  /// \param [in] end : __Iterator cref = Constant Reference to the end iterator of the range
  /// \exceptsafe if ElementType is exceptsafe constructible and if ReceiverType does not throw at insert request.
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  ///
  /// \public
  template <typename __Iterator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto insertAllOf (__Iterator const& begin, __Iterator const& end) noexcept(false) -> void;

  /// \deprecated 'addAllOf' function deprecated, kept for support. replaced by 'insertAllOf', same functionality
  /// \brief Function used to insert multiple elements by extracting each from a given iterator range and inserting each into the receiver
  /// \tparam __Iterator is the type of given iterators
  /// \param [in] begin : __Iterator cref = Constant Reference to the begin iterator of the range
  /// \param [in] end : __Iterator cref = Constant Reference to the end iterator of the range
  /// \exceptsafe if ElementType is exceptsafe constructible and if ReceiverType does not throw at insert request.
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  ///
  /// \public
  template <typename __Iterator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_DeprecatedHint ("'Collection::addAllOf' has been deprecated. Use 'Collection::insertAllOf' instead") 
  auto addAllOf (__Iterator const& begin, __Iterator const& end) noexcept(false) -> void;
  
private:
  /// \brief Friend declaration of the function to allow usage of insert from caller object
  /// \private
  template <typename __Accumulator, typename __Last>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  friend auto __expansiveInsert (__Accumulator* pAccumulator, __Last&& lastValue) noexcept(false) -> void;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \brief Friend declaration of the function to allow usage of insert from caller object
  /// \private
  template <typename __Accumulator, typename __First, typename...__Remaining> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  friend auto __expansiveInsert (__Accumulator* pAccumulator, __First&& firstValue, __Remaining&&... remainingValues) noexcept(false) -> void;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};
} // namespace __impl
} // namespace __hidden
} // namespace cds

#endif // __CDS_SHARED_RANDOM_INSERTION_PRIMITIVE_CLIENT_HPP__
