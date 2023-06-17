//
// Created by loghin on 09/08/22.
//

#ifndef __CDS_SHARED_DELEGATE_FIND_UNIQUE_MUTABLE_PRIMITIVE_CLIENT_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_SHARED_DELEGATE_FIND_UNIQUE_MUTABLE_PRIMITIVE_CLIENT_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
/// \interface Interface for creating Abstract Iterator find requests and creating Wrapper Iterators for received Iterators. Used when Iterable Elements are Unique
/// \tparam __Receiver is the type of implementor class, used for static polymorphism.
/// Implementor is also required to be derived from either the Map abstract class or
/// a class extending the __CollectionInternalCommunicationChannel class, or provide equivalent member
/// function implementations provided by the __CollectionInternalCommunicationChannel class
/// Note : This Client will request the member functions identified with:
///      __cirt_find
///
/// \tparam __Element is the type of elements contained into the Object
/// \tparam __Key is the type given as parameter for the element identification. In Set, this is the ElementType, while in Map, it is the KeyType of a MapEntry
/// \tparam __bidirectional is to be set 'true' if received Abstract Iterator is bi-directional. If uni-directional, set to false
///
/// \test Suite: TBA, Group: TBA, Test Cases: TBA
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <typename __Receiver, typename __Element, typename __Key, bool __bidirectional>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __FindUniqueMutablePrimitiveClient {                                                // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
public:
  /// \typedef alias for chosen Wrapper Iterator, to be used in implementor class to represent the Iterator type.
  /// \public
  using Iterator =
      cds::meta::Conditional <
          __bidirectional,
          __BidirectionalDelegateWrapperIterator <__Element>,
          __ForwardDelegateWrapperIterator <__Element>
      >;

  /// \brief Function used to obtain an iterator indicating at the value identified via the given reference key. Will acquire iterator using a __cirt_find request
  /// \param [in] key : __Key cref = Constant Reference to the value used to identify the searched value
  /// \exceptsafe
  /// \return Iterator = newly created iterator indicating at the value found via given key. If no value found, equivalent to ReceiverType::end ()
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \public
  __CDS_NoDiscard auto find (__Key const& key) noexcept(false) -> Iterator;
};


/// \interface Interface for creating Local Iterator find requests. Used when Iterable Elements are Unique
/// \tparam __Receiver is the type of implementor class, used for static polymorphism.
/// Implementor is also required to implement an appropriate dispatcher ( __MapServerDispatcher or lower in hierarchy ),
/// or provide an equivalent __findLocal member function set to the one provided
/// by the dispatcher
///
/// \tparam __Element is the type of elements contained into the Object
/// \tparam __Key is the type given as parameter for the element identification. In Map, it is the KeyType of a MapEntry
///
/// \test Suite: TBA, Group: TBA, Test Cases: TBA
/// \namespace cds::__hidden::__impl
/// \internal library-private
template <
    typename __Receiver,                    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Key,                         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __IteratorType                     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __LocalFindUniqueMutablePrimitiveClient {   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
public:
  /// \typedef alias for the __IteratorType template parameter
  /// \public
  using Iterator = __IteratorType;

  /// \brief Function used to obtain an iterator indicating at the value identified via the given reference key. Will acquire iterator using the __findLocal function
  /// \param [in] key : __Key cref = Constant Reference to the value used to identify the searched value
  /// \exceptsafe
  /// \return Iterator = newly created iterator indicating at the value found via given key. If no value found, equivalent to ReceiverType::cend ()
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \public
  __CDS_NoDiscard auto find (__Key const& key) noexcept -> Iterator;
};
} // namespace __impl
} // namespace __hidden
} // namespace cds

#endif // __CDS_SHARED_DELEGATE_FIND_UNIQUE_MUTABLE_PRIMITIVE_CLIENT_HPP__
