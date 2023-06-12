//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_ITERATOR_REMOVE_PRIMITIVE_CLIENT_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_SHARED_ITERATOR_REMOVE_PRIMITIVE_CLIENT_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
/// \class pre-declaration of Abstract Delegate Wrapper Iterator, to be used by Remove Client as Abstract Iterator
template <typename>
class __AbstractDelegateWrapperIterator;    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

/// \interface Interface for creating Abstract Iterator remove requests.
///
/// \tparam __Receiver is the type of implementor class, used for static polymorphism.
/// Implementor is also required to be derived from either the Collection abstract class or
/// a class extending the __CollectionInternalCommunicationChannel class, or provide equivalent member
/// function implementations provided by the __CollectionInternalCommunicationChannel class
/// Note : This Client will request the member functions identified with:
///      __cirt_remove
///      __cirt_removeArray
///
/// \tparam __Element is the type of elements enclosed in the object
///
/// \test Suite: MCTS-00001, Group: MCTG-00350-RAIT, Test Cases: All
/// \namespace cds :: __hidden :: __impl
/// \internal library-private
template <typename __Receiver, typename __Element>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __AbstractIteratorRemovePrimitiveClient {     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
protected:
  /// \typedef internal alias representing the __Element parameter
  /// \protected
  using ElementType       = __Element;

  /// \typedef internal alias representing the iterator parameter type
  /// \protected
  using AbstractIterator          = __AbstractDelegateWrapperIterator <ElementType>;

  /// \brief Function used to create a request to remove an element indicated to by the given iterator
  /// \param [in] iterator : AbstractIterator cref = Constant Reference to the iterator to be removed
  /// \exceptsafe
  /// \return bool = true if removal was successful, false otherwise
  ///
  /// \test Suite: MCTS-00001, Group: MCTG-00350-RAIT, Test Cases: {
  ///      MCTC-00351-RAIT-removeAtFront,
  ///      MCTC-00352-RAIT-removeInBounds,
  ///      MCTC-00353-RAIT-removeAtEnd,
  ///      MCTC-00355-RAIT-removeBeforeFront,
  ///      MCTC-00356-RAIT-removeFromOther
  /// }
  ///
  /// \public
  auto remove (AbstractIterator const& iterator) noexcept(false) -> bool;

  /// \brief Function used to create a request to remove several elements indicated to by the given iterators in the array. Given Iterators in the iterator buffer MUST be ordered per forward iteration
  /// \param [in] pIterators : AbstractIterator cptr = Address to an array of constant Abstract Iterator values
  /// \param [in] iteratorCount : Size = number of values enclosed in the array given at pIterators
  /// \exceptsafe
  /// \return Size = number of elements that were removed successfully
  ///
  /// \test Suite: MCTS-00001, Group: MCTG-00400-RB, Test Cases: All
  /// \test Suite: MCTS-00001, Group: MCTG-00450-RO, Test Cases: All
  ///
  /// \protected Unused by implementor class, used by other clients. Do not inherit public
  auto removeAll (AbstractIterator const* pIterators, Size iteratorCount) noexcept(false) -> Size;
};


/// \interface Interface for creating Local Iterator remove requests. ( not through channel, through function )
///
/// \tparam __Receiver is the type of implementor class, used for static polymorphism.
/// Implementor is also required to implement an appropriate dispatcher ( __CollectionServerDispatcher or lower in hierarchy ),
/// or provide an equivalent __remove and __removeArray member function set to the one provided
/// by the dispatcher
/// \tparam __Element is the type of elements enclosed in the object
/// \tparam __Iterator is the iterator type to be expected as parameter to the functions
///
/// \test Suite: TBA, Group: TBA, Test Cases: TBA
/// \namespace cds :: __hidden :: __impl
/// \internal library-private
template <typename __Receiver, typename __Element, typename __Iterator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __LocalIteratorRemovePrimitiveClient {                            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
protected:
  /// \typedef internal alias representing the __Element const parameter
  /// \protected
  using ElementType   = __Element;

  /// \typedef internal alias representing the iterator parameter type
  /// \protected
  using Iterator              = __Iterator;

  /// \brief Function used to create a request to remove an element indicated to by the given iterator
  /// \param [in] iterator : Iterator cref = Constant Reference to the iterator to be removed
  /// \exceptsafe
  /// \return bool = true if removal was successful, false otherwise
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  ///
  /// \public
  auto remove (Iterator const& iterator) noexcept(false) -> bool;

  /// \brief Function used to create a request to remove several elements indicated to by the given iterators in the array. Given Iterators in the iterator buffer MUST be ordered per forward iteration
  /// \param [in] pIterators : Iterator cptr = Address to an array of constant Const Iterator values
  /// \param [in] iteratorCount : Size = number of values enclosed in the array given at pIterators
  /// \exceptsafe
  /// \return Size = number of elements that were removed successfully
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  ///
  /// \protected Unused by implementor class, used by other clients. Do not inherit public
  auto removeAll (Iterator const* pIterators, Size iteratorCount) noexcept(false) -> Size;
};
} // namespace __impl
} // namespace __hidden
} // namespace cds

#endif // __CDS_SHARED_ITERATOR_REMOVE_PRIMITIVE_CLIENT_HPP__
