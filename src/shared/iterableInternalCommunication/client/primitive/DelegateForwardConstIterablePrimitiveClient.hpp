//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_DELEGATE_FORWARD_CONST_ITERABLE_PRIMITIVE_CLIENT_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_SHARED_DELEGATE_FORWARD_CONST_ITERABLE_PRIMITIVE_CLIENT_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
/// \class pre-declaration of Bi-Directional Abstract Iterator Wrapper, to be used in Conditional
template <typename>
class __BidirectionalDelegateWrapperIterator;   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)


/// \class pre-declaration of Uni-Directional Abstract Iterator Wrapper, to be used in Conditional
template <typename>
class __ForwardDelegateWrapperIterator; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)


/// \interface Interface for creating Abstract Iterator requests and creating Wrapper Iterators for received Iterators
/// \tparam __Receiver is the type of implementor class, used for static polymorphism.
/// Implementor is also required to be derived from either the Collection abstract class or
/// a class extending the __CollectionInternalCommunicationChannel class, or provide equivalent member
/// function implementations provided by the __CollectionInternalCommunicationChannel class
/// Note : This Client will request the const member functions identified with:
///      __cirt_begin
///      __cirt_end
///
/// \tparam __Element is the type of elements contained into the Object
/// \tparam __bidirectional is to be set 'true' if received Abstract Iterator is bi-directional. If uni-directional, set to false
///
/// \test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: All
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <typename __Receiver, typename __Element, bool __bidirectional>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __DelegateForwardConstIterablePrimitiveClient {                     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
public:
  /// \typedef internal alias representing the __Element template parameter
  /// \protected
  using ElementType   = // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __Element const;

  /// \typedef alias for chosen Wrapper Iterator, to be used in implementor class to represent the ConstIterator type.
  /// \public
  using ConstIterator         =
      cds::meta::Conditional <
          __bidirectional,
          __BidirectionalDelegateWrapperIterator <ElementType>,
          __ForwardDelegateWrapperIterator <ElementType>
      >;

  /// \brief Function used to obtain the iterator at the beginning of the sequence of elements in iterable container. Will acquire iterator using a __cirt_begin request
  /// \exceptsafe
  /// \return ConstIterator = Wrapper for the received forward, immutable, begin iterator
  /// \test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: { CTC-00051-IT-range, CTC-00052-IT-begin_end,
  ///      CTC-00054-IT-e_begin_end, CTC-00056-IT-e_emptyRange }
  /// \public
  __CDS_NoDiscard auto begin () const noexcept(false) -> ConstIterator;

  /// \brief Function used to obtain the iterator at the end of the sequence of elements in iterable container. Will acquire iterator using a __cirt_end request
  /// \exceptsafe
  /// \return ConstIterator = Wrapper for the received forward, immutable, end iterator
  /// \test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: { CTC-00051-IT-range, CTC-00052-IT-begin_end,
  ///      CTC-00054-IT-e_begin_end, CTC-00056-IT-e_emptyRange }
  /// \public
  __CDS_NoDiscard auto end () const noexcept(false) -> ConstIterator;

  /// \brief Function used to obtain the iterator at the beginning of the sequence of elements in iterable container. Will acquire iterator using a __cirt_begin request
  /// \exceptsafe
  /// \return ConstIterator = Wrapper for the received forward, immutable, begin iterator
  /// \test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: { CTC-00051-IT-range, CTC-00053-IT-cbegin_cend,
  ///      CTC-00055-IT-e_cbegin_cend, CTC-00056-IT-e_emptyRange }
  /// \public
  __CDS_NoDiscard auto cbegin () const noexcept(false) -> ConstIterator;

  /// \brief Function used to obtain the iterator at the end of the sequence of elements in iterable container. Will acquire iterator using a __cirt_end request
  /// \exceptsafe
  /// \return ConstIterator = Wrapper for the received forward, immutable, end iterator
  /// \test Suite: CTS-00001, Group: CTG-00050-IT, Test Cases: { CTC-00051-IT-range, CTC-00053-IT-cbegin_cend,
  ///      CTC-00055-IT-e_cbegin_cend, CTC-00056-IT-e_emptyRange }
  /// \public
  __CDS_NoDiscard auto cend () const noexcept(false) -> ConstIterator;
};


/// \class Interface for creating Local Forward Const Iterator requests.
/// \tparam __Receiver is the type of implementor class, used for static polymorphism.
/// Implementor is also required to implement an appropriate dispatcher ( __CollectionServerDispatcher or lower in hierarchy ),
/// or provide an equivalent __cbeginLocal and __cendLocal member function set to the one provided
/// by the dispatcher
/// \tparam __ConstIterator is the type of the iterator returned by the begin / end / cbegin / cend functions
///
/// \test Suite: TBA, Group: TBA, Test Cases: TBA
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <typename __Receiver, typename __ConstIterator>    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __LocalDelegateForwardConstIterablePrimitiveClient {  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
public:
  /// \typedef alias for chosen const iterator.
  /// \public
  using ConstIterator = __ConstIterator;

  /// \brief Function used to obtain the iterator at the beginning of the sequence of elements in iterable container. Will acquire iterator using the __cbeginLocal function
  /// \exceptsafe
  /// \return ConstIterator = begin const iterator
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \public
  __CDS_NoDiscard constexpr auto begin () const noexcept -> ConstIterator;

  /// \brief Function used to obtain the iterator at the end of the sequence of elements in iterable container. Will acquire iterator using the __cendLocal function
  /// \exceptsafe
  /// \return ConstIterator = end const iterator
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \public
  __CDS_NoDiscard constexpr auto end () const noexcept -> ConstIterator;

  /// \brief Function used to obtain the iterator at the beginning of the sequence of elements in iterable container. Will acquire iterator using the __cbeginLocal function
  /// \exceptsafe
  /// \return ConstIterator = begin const iterator
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \public
  __CDS_NoDiscard constexpr auto cbegin () const noexcept -> ConstIterator;

  /// \brief Function used to obtain the iterator at the end of the sequence of elements in iterable container. Will acquire iterator using the __cendLocal function
  /// \exceptsafe
  /// \return ConstIterator = end const iterator
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \public
  __CDS_NoDiscard constexpr auto cend () const noexcept -> ConstIterator;
};

} // namespace __impl
} // namespace __hidden
} // namespace cds

#endif // __CDS_SHARED_DELEGATE_FORWARD_CONST_ITERABLE_PRIMITIVE_CLIENT_HPP__
