//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_DELEGATE_FORWARD_ITERABLE_PRIMITIVE_CLIENT_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_SHARED_DELEGATE_FORWARD_ITERABLE_PRIMITIVE_CLIENT_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
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
/// Note : This Client will request the member functions identified with:
///      __cirt_begin
///      __cirt_end
///
/// \tparam __Element is the type of elements contained into the Object
/// \tparam __bidirectional is to be set 'true' if received Abstract Iterator is bi-directional. If uni-directional, set to false
///
/// \test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <typename __Receiver, typename __Element, bool __bidirectional>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __DelegateForwardIterablePrimitiveClient {                          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
public:
  /// \typedef internal alias representing the __Element template parameter
  /// \protected
  using ElementType    = __Element;

  /// \typedef alias for chosen Wrapper Iterator, to be used in implementor class to represent the Iterator type.
  /// \public
  using Iterator              = // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      cds::meta::Conditional <
          __bidirectional,
          __BidirectionalDelegateWrapperIterator <ElementType>,
          __ForwardDelegateWrapperIterator <ElementType>
      >;

  /// \brief Function used to obtain the iterator at the beginning of the sequence of elements in iterable container. Will acquire iterator using a __cirt_begin request
  /// \exceptsafe
  /// \return Iterator = Wrapper for the received forward, mutable, begin iterator
  ///
  /// \test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: {
  ///      MCTC-00051-IT-range,
  ///      MCTC-00052-IT-begin_end,
  ///      MCTC-00054-IT-e_begin_end,
  ///      MCTC-00056-IT-e_emptyRange,
  ///      MCTC-00058-IT-mutabilityRange,
  ///      MCTC-00059-IT-mutabilityIteration
  /// }
  ///
  /// \public
  __CDS_NoDiscard auto begin () noexcept(false) -> Iterator;

  /// \brief Function used to obtain the iterator at the end of the sequence of elements in iterable container. Will acquire iterator using a __cirt_end request
  /// \exceptsafe
  /// \return Iterator = Wrapper for the received forward, mutable, end iterator
  ///
  /// \test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: {
  ///      MCTC-00051-IT-range,
  ///      MCTC-00052-IT-begin_end,
  ///      MCTC-00054-IT-e_begin_end,
  ///      MCTC-00056-IT-e_emptyRange,
  ///      MCTC-00058-IT-mutabilityRange,
  ///      MCTC-00059-IT-mutabilityIteration
  /// }
  ///
  /// \public
  __CDS_NoDiscard auto end () noexcept(false) -> Iterator;
};


/// \class Interface for creating Local Forward Iterator requests.
/// \tparam __Receiver is the type of implementor class, used for static polymorphism.
/// Implementor is also required to implement an appropriate dispatcher ( __MutableCollectionServerDispatcher or lower in hierarchy ),
/// or provide an equivalent __beginLocal and __endLocal member function set to the one provided
/// by the dispatcher
/// \tparam __Iterator is the type of the iterator returned by the begin / end functions
///
/// \test Suite: TBA, Group: TBA, Test Cases: TBA
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <typename __Receiver, typename __Iterator>   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __LocalDelegateForwardIterablePrimitiveClient { // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,///-member-init)
public:
  /// \typedef alias for chosen iterator.
  /// \public
  using Iterator = __Iterator;

  /// \brief Function used to obtain the iterator at the beginning of the sequence of elements in iterable container. Will acquire iterator using the __beginLocal function
  /// \exceptsafe
  /// \return Iterator = begin iterator
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \public
  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto begin () noexcept -> Iterator;   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \brief Function used to obtain the iterator at the end of the sequence of elements in iterable container. Will acquire iterator using the __endLocal function
  /// \exceptsafe
  /// \return Iterator = end iterator
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \public
  __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto end () noexcept -> Iterator; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
};
} // namespace __impl 
} // namespace __hidden
} // namespace cds

#endif // __CDS_SHARED_DELEGATE_FORWARD_ITERABLE_PRIMITIVE_CLIENT_HPP__
