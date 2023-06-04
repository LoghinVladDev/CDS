//
// Created by loghin on 17/07/22.
//

#ifndef __CDS_SHARED_NODE_ITERATOR_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_SHARED_NODE_ITERATOR_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

#include "IteratorModel.hpp"

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

/// \brief Partial Pre-Declaration of __SingleLinkedList, as it requires private values
/// \tparam __ElementType is the type of the node data stored in the hash table
///
/// \test Suite: N/A, Group: N/A, Test Cases: N/A
/// \namespace cds::__hidden::__impl
template <
    typename __ElementType, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const&, __ElementType const&>
> class __SingleLinkedList; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)


/// \brief Partial Pre-Declaration of __DoubleLinkedList, as it requires private values
/// \tparam __ElementType is the type of the node data stored in the hash table
///
/// \test Suite: N/A, Group: N/A, Test Cases: N/A
/// \namespace cds::__hidden::__impl
template <
    typename __ElementType, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__ElementType const&, __ElementType const&>
> class __DoubleLinkedList; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

template <
    template <typename...> class  __NodeType,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                      __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    bool = cds::meta::IsConst <__ElementType>::value
> struct __NodeIteratorTraits {};                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

template <
    template <typename...> class __NodeType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ElementType                    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> struct __NodeIteratorTraits <__NodeType, __ElementType, true> {
  using Node = __NodeType <cds::meta::RemoveConst<__ElementType>>;
  using RVal = __ElementType;
};

template <
    template <typename...> class __NodeType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ElementType                    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> struct __NodeIteratorTraits <__NodeType, __ElementType, false> {
  using Node = __NodeType <__ElementType>;
  using RVal = __ElementType;
};
} // namespace __impl
} // namespace __hidden


/// \brief Unidirectional Node Iterator. Parses nodes until a node is null
/// Used by LinkedHashMap - begin/end
/// \tparam __ElementType is the type of the enclosed element.
/// \implements ForwardIterator
///
/// \test Suite: TBA, Group: TBA, Test Cases: TBA
/// \namespace cds::experimental
template < typename __ElementType > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class UnidirectionalNodeIterator : public meta::ForwardIterator {
private:
  /// \typedef Alias for the Node Type.
  /// \private
  using Traits = __hidden::__impl::__NodeIteratorTraits <
      __hidden::__impl::__UnidirectionalNode,
      __ElementType
  >;

  using Node = typename Traits::Node;
  using RVal = typename Traits::RVal;

public:
  /// \typedef Alias for the __ElementType template parameter
  /// \private
  using ElementType = __ElementType;

  /// \brief Default Constructor, constexpr
  /// \exceptsafe
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \public
  constexpr UnidirectionalNodeIterator () noexcept;

  /// \brief Initialization Constructor, constexpr
  /// \param [in] pPreviousNode : DataNode ptr = address to the node previous to the node containing the current element
  /// \param [in] pCurrentNode : DataNode ptr = address of the node containing the current value
  /// \exceptsafe
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \pulbic
  __CDS_MaybeUnused constexpr UnidirectionalNodeIterator (Node* pCurrentNode) noexcept;

  /// \brief Copy Constructor, constexpr
  /// \param [in] iterator : UnidirectionalNodeIterator cref = Constant Reference to the iterator to acquire the values from
  /// \exceptsafe
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \public
  constexpr UnidirectionalNodeIterator (UnidirectionalNodeIterator const& iterator) noexcept;

  /// \brief Move Constructor, constexpr
  /// \param [in, out] iterator : UnidirectionalNodeIterator mref = Move Reference to the iterator to move the values from
  /// \exceptsafe
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \public
  constexpr UnidirectionalNodeIterator (UnidirectionalNodeIterator&& iterator) noexcept;

  /// \brief Implicit Destructor, constexpr
  /// \exceptsafe
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \public
  ~UnidirectionalNodeIterator () noexcept = default;

  /// \brief Copy Operator, constexpr
  /// \param [in] iterator : UnidirectionalNodeIterator cref = Constant Reference to an iterator to copy the values value from
  /// \exceptsafe
  /// \return UnidirectionalNodeIterator ref = Reference to the modified iterator
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \public
  __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( // NOLINT(cppcoreguidelines-c-copy-assignment-signature, misc-unconventional-assign-operator)
      UnidirectionalNodeIterator const& iterator
  ) noexcept -> UnidirectionalNodeIterator&;

  /// \brief Move Operator, constexpr
  /// \param [in, out] iterator : UnidirectionalNodeIterator mref = Move Reference to an iterator to move the values value from
  /// \exceptsafe
  /// \return UnidirectionalNodeIterator ref = Reference to the modified iterator
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \public
  __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( // NOLINT(cppcoreguidelines-c-copy-assignment-signature, misc-unconventional-assign-operator)
      UnidirectionalNodeIterator&& iterator
  ) noexcept -> UnidirectionalNodeIterator&;

  /// \brief Function used to acquire the current value the iterator is indicating to
  /// \exceptsafe
  /// \return __ElementType ref = Reference to the element the address is indicating to
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \public
  __CDS_NoDiscard constexpr auto operator* () const noexcept -> RVal&;

  /// \brief Function used to acquire the address of the value the iterator is indicating to
  /// \exceptsafe
  /// \return __ElementType ptr = Pointer to the element the address is indicating to
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \public
  __CDS_NoDiscard constexpr auto operator -> () const noexcept -> RVal*;

  /// \brief Equality Comparison Operator
  /// \param [in] iterator : UnidirectionalNodeIterator cref = Constant Reference to another iterator to compare this one to
  /// \exceptsafe
  /// \return bool = true if iterators are indicating at the same node, with same previous, false otherwise
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \public
  __CDS_NoDiscard constexpr auto operator == (
      UnidirectionalNodeIterator <__ElementType> const& iterator
  ) const noexcept -> bool;

  /// \brief Inequality Comparison Operator
  /// \param [in] iterator : UnidirectionalNodeIterator cref = Constant Reference to another iterator to compare this one to
  /// \exceptsafe
  /// \return bool = false if iterators are indicating at the same node, with same previous, true otherwise
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \public
  __CDS_NoDiscard constexpr auto operator != (
      UnidirectionalNodeIterator <__ElementType> const& iterator
  ) const noexcept -> bool;

  /// \brief Prefix Increment Operator. Will advance forward one position and then return
  /// \exceptsafe
  /// \return UnidirectionalNodeIterator ref = Reference to the modified iterator
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \public
  __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> UnidirectionalNodeIterator&;

  /// \brief Postfix Increment Operator. Will return the original iterator, and then advance forward the current one
  /// \exceptsafe
  /// \return UnidirectionalNodeIterator = A copy of the original iterator
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \public
  __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ (int) noexcept -> UnidirectionalNodeIterator;

  /// \brief Validity function, bool cast.
  /// \exceptsafe
  /// \return bool = true if current node is not null, false otherwise
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \public
  __CDS_NoDiscard __CDS_Explicit constexpr operator bool() const noexcept; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,///-non-private-member-variables-in-classes)

private:
  /// \brief Partial Pre-Declaration of __SingleLinkedList, as it requires private values
  /// \tparam __ElementType is the type of the node data stored in the hash table
  ///
  /// \test Suite: N/A, Group: N/A, Test Cases: N/A
  /// \namespace cds::__hidden::__impl
  template <
      typename __TElementType,                                    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      functional::PredicateFunction <__TElementType const&, __TElementType const&>
  > friend class cds::__hidden::__impl::__SingleLinkedList;     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \brief Address of current Node in the list
  /// \private
  Node* _pCurrentNode    {nullptr};
};


/// \brief Abstract Bidirectional Node Iterator. Parses nodes until a node is null, direction-oblivious
/// \tparam __ElementType is the type of the enclosed element.
/// \implements BidirectionalIterator
///
/// \test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
/// \namespace cds::experimental
template < typename __ElementType > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class AbstractBidirectionalNodeIterator : public meta::BidirectionalIterator {
protected:
  using Traits = __hidden::__impl::__NodeIteratorTraits <
      __hidden::__impl::__BidirectionalNode,
      __ElementType
  >;

  using Node = typename Traits::Node;
  using RVal = typename Traits::RVal;

public:
  /// \typedef Alias for the __ElementType template parameter
  /// \public
  using ElementType = __ElementType;

  /// \brief Implicit Destructor, constexpr
  /// \exceptsafe
  ///
  /// \test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
  /// \protected
  ~AbstractBidirectionalNodeIterator () noexcept = default;

  /// \brief Function used to acquire the current value the iterator is indicating to
  /// \exceptsafe
  /// \return __ElementType ref = Reference to the element the address is indicating to
  ///
  /// \test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
  /// \public
  __CDS_NoDiscard constexpr auto operator* () const noexcept -> RVal&;

  /// \brief Function used to acquire the address of the value the iterator is indicating to
  /// \exceptsafe
  /// \return __ElementType ptr = Pointer to the element the address is indicating to
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \public
  __CDS_NoDiscard constexpr auto operator -> () const noexcept -> RVal*;

  /// \brief Equality Comparison Operator
  /// \param [in] iterator : AbstractBidirectionalNodeIterator cref = Constant Reference to another iterator to compare this one to
  /// \exceptsafe
  /// \return bool = true if iterators are indicating at the same node, with same previous, false otherwise
  ///
  /// \test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
  /// \public
  __CDS_NoDiscard constexpr auto operator == (
      AbstractBidirectionalNodeIterator <__ElementType> const& iterator
  ) const noexcept -> bool;

  /// \brief Inequality Comparison Operator
  /// \param [in] iterator : AbstractBidirectionalNodeIterator cref = Constant Reference to another iterator to compare this one to
  /// \exceptsafe
  /// \return bool = false if iterators are indicating at the same node, with same previous, true otherwise
  ///
  /// \test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
  /// \public
  __CDS_NoDiscard constexpr auto operator != (
      AbstractBidirectionalNodeIterator <__ElementType> const& iterator
  ) const noexcept -> bool;

  /// \brief Validity function, bool cast.
  /// \exceptsafe
  /// \return bool = true if current node is not null, false otherwise
  ///
  /// \test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
  /// \public
  __CDS_NoDiscard __CDS_Explicit constexpr operator bool () const noexcept; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,///-non-private-member-variables-in-classes)

protected:
  /// \brief Default Constructor, constexpr
  /// \exceptsafe
  ///
  /// \test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
  /// \protected
  constexpr AbstractBidirectionalNodeIterator () noexcept;

  /// \brief Initialization Constructor, constexpr
  /// \param [in] pPreviousNode : DataNode ptr = address to the node previous to the node containing the current element
  /// \param [in] pCurrentNode : DataNode ptr = address of the node containing the current value
  /// \exceptsafe
  ///
  /// \test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
  /// \protected
  __CDS_Explicit constexpr AbstractBidirectionalNodeIterator (Node* pPreviousNode, Node* pCurrentNode) noexcept;

  /// \brief Copy Constructor, constexpr
  /// \param [in] iterator : AbstractBidirectionalNodeIterator cref = Constant Reference to the iterator to acquire the values from
  /// \exceptsafe
  ///
  /// \test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
  /// \protected
  constexpr AbstractBidirectionalNodeIterator (AbstractBidirectionalNodeIterator const& iterator) noexcept;

  /// \brief Move Constructor, constexpr
  /// \param [in, out] iterator : AbstractBidirectionalNodeIterator mref = Move Reference to the iterator to move the values from
  /// \exceptsafe
  ///
  /// \test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
  /// \protected
  constexpr AbstractBidirectionalNodeIterator (AbstractBidirectionalNodeIterator&& iterator) noexcept;

  /// \brief Implicit Assignment Copy Operator, constexpr
  /// \param [in] iterator : AbstractBidirectionalNodeIterator cref = Constant Reference to the iterator to acquire the values from
  /// \exceptsafe
  ///
  /// \test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
  /// \protected
  auto operator = (AbstractBidirectionalNodeIterator const&) noexcept -> AbstractBidirectionalNodeIterator& = default;

  /// \brief Implicit Assignment Move Operator, constexpr
  /// \param [in, out] iterator : AbstractBidirectionalNodeIterator mref = Move Reference to the iterator to move the values from
  /// \exceptsafe
  ///
  /// \test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
  /// \protected
  auto operator = (AbstractBidirectionalNodeIterator&&) noexcept -> AbstractBidirectionalNodeIterator& = default;

  __CDS_cpplang_NonConstConstexprMemberFunction auto advanceFwd() noexcept -> void;
  __CDS_cpplang_NonConstConstexprMemberFunction auto reverseFwd() noexcept -> void;
  __CDS_cpplang_NonConstConstexprMemberFunction auto advanceBwd() noexcept -> void;
  __CDS_cpplang_NonConstConstexprMemberFunction auto reverseBwd() noexcept -> void;

private:    // NOLINT(readability-redundant-access-specifiers)
  /// \brief Partial Pre-Declaration of __DoubleLinkedList, as it requires private values
  /// \tparam __ElementType is the type of the node data stored in the hash table
  /// \test Not Applicable.
  /// \namespace cds::__hidden::__impl
  template <
      typename __TElementType,                                // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      functional::PredicateFunction <__TElementType const&, __TElementType const&>
  > friend class cds::__hidden::__impl::__DoubleLinkedList; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \brief Address of current Node in the list
  /// \protected
  Node* _pCurrentNode    { nullptr }; // NOLINT(*-non-private-member-variables-in-classes)

  /// \brief Address of previous Node in the list
  /// \protected
  Node* _pPreviousNode   { nullptr }; // NOLINT(*-non-private-member-variables-in-classes)
};


/// \brief Bidirectional Forward Node Iterator. Parses nodes until a node is null, front to back, by way of next
/// Used by LinkedList - begin/end
/// \tparam __ElementType is the type of the enclosed element.
/// \extends AbstractBidirectionalNodeIterator
///
/// \test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
/// \namespace cds::experimental
template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class ForwardBidirectionalNodeIterator : public AbstractBidirectionalNodeIterator <__ElementType> {
private:
  using typename AbstractBidirectionalNodeIterator <__ElementType>::Node;

public:
  /// \typedef Alias for the __ElementType template parameter
  /// \public
  using ElementType = __ElementType;

  using AbstractBidirectionalNodeIterator <__ElementType>::AbstractBidirectionalNodeIterator;
  using AbstractBidirectionalNodeIterator <__ElementType>::operator=;

  /// \brief Implicit Destructor, constexpr
  /// \exceptsafe
  ///
  /// \test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
  /// \public
  ~ForwardBidirectionalNodeIterator () noexcept = default;

  /// \brief Equality Comparison Operator
  /// \param [in] iterator : ForwardBidirectionalNodeIterator cref = Constant Reference to another iterator to compare this one to
  /// \exceptsafe
  /// \return bool = true if iterators are indicating at the same node, with same previous, false otherwise
  ///
  /// \test Suite: MCTS-00001, MGroup: CTG-00050-IT, Test Cases: All
  /// \public
  __CDS_NoDiscard constexpr auto operator == (
      ForwardBidirectionalNodeIterator <__ElementType> const& iterator
  ) const noexcept -> bool;

  /// \brief Inequality Comparison Operator
  /// \param [in] iterator : ForwardBidirectionalNodeIterator cref = Constant Reference to another iterator to compare this one to
  /// \exceptsafe
  /// \return bool = false if iterators are indicating at the same node, with same previous, true otherwise
  ///
  /// \test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
  /// \public
  __CDS_NoDiscard constexpr auto operator != (
      ForwardBidirectionalNodeIterator <__ElementType> const& iterator
  ) const noexcept -> bool;

  /// \brief Prefix Increment Operator. Will advance forward one position and then return
  /// \exceptsafe
  /// \return ForwardBidirectionalNodeIterator ref = Reference to the modified iterator
  ///
  /// \test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
  /// \public
  __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> ForwardBidirectionalNodeIterator&;

  /// \brief Postfix Increment Operator. Will return the original iterator, and then advance forward the current one
  /// \exceptsafe
  /// \return ForwardBidirectionalNodeIterator = A copy of the original iterator
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \public
  __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ (int) noexcept -> ForwardBidirectionalNodeIterator;

  /// \brief Prefix Decrement Operator. Will advance backward one position and then return
  /// \exceptsafe
  /// \return ForwardBidirectionalNodeIterator ref = Reference to the modified iterator
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \public
  __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- () noexcept -> ForwardBidirectionalNodeIterator&;

  /// \brief Postfix Increment Operator. Will return the original iterator, and then advance backward the current one
  /// \exceptsafe
  /// \return ForwardBidirectionalNodeIterator = A copy of the original iterator
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \public
  __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- (int) noexcept -> ForwardBidirectionalNodeIterator;
};


/// \brief Bidirectional Forward Node Iterator. Parses nodes until a node is null, back to front, by way of previous
/// Used by LinkedList - rbegin/rend
/// \tparam __ElementType is the type of the enclosed element.
/// \extends AbstractBidirectionalNodeIterator
///
/// \test Suite: TBA, Group: TBA, Test Cases: TBA
/// \namespace cds::experimental
template < typename __ElementType > // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class BackwardBidirectionalNodeIterator : public AbstractBidirectionalNodeIterator <__ElementType> {
private:
  using typename AbstractBidirectionalNodeIterator <__ElementType>::Node;

public: // NOLINT(readability-redundant-access-specifiers)
  /// \typedef Alias for the __ElementType template parameter
  /// \public
  using ElementType = __ElementType;

  using AbstractBidirectionalNodeIterator <__ElementType>::AbstractBidirectionalNodeIterator;
  using AbstractBidirectionalNodeIterator <__ElementType>::operator=;

  /// \brief Implicit Destructor, constexpr
  /// \exceptsafe
  ///
  /// \test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
  /// \public
  ~BackwardBidirectionalNodeIterator () noexcept = default;

  /// \brief Equality Comparison Operator
  /// \param [in] iterator : BackwardBidirectionalNodeIterator cref = Constant Reference to another iterator to compare this one to
  /// \exceptsafe
  /// \return bool = true if iterators are indicating at the same node, with same previous, false otherwise
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \public
  __CDS_NoDiscard constexpr auto operator == (
      BackwardBidirectionalNodeIterator <__ElementType> const& iterator
  ) const noexcept -> bool;

  /// \brief Inequality Comparison Operator
  /// \param [in] iterator : BackwardBidirectionalNodeIterator cref = Constant Reference to another iterator to compare this one to
  /// \exceptsafe
  /// \return bool = false if iterators are indicating at the same node, with same previous, true otherwise
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \public
  __CDS_NoDiscard constexpr auto operator != (
      BackwardBidirectionalNodeIterator <__ElementType> const& iterator
  ) const noexcept -> bool;

  /// \brief Prefix Increment Operator. Will advance forward one position and then return
  /// \exceptsafe
  /// \return BackwardBidirectionalNodeIterator ref = Reference to the modified iterator
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \public
  __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> BackwardBidirectionalNodeIterator&;

  /// \brief Postfix Increment Operator. Will return the original iterator, and then advance forward the current one
  /// \exceptsafe
  /// \return BackwardBidirectionalNodeIterator = A copy of the original iterator
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \public
  __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ (int) noexcept -> BackwardBidirectionalNodeIterator;

  /// \brief Prefix Decrement Operator. Will advance backward one position and then return
  /// \exceptsafe
  /// \return BackwardBidirectionalNodeIterator ref = Reference to the modified iterator
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \public
  __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- () noexcept -> BackwardBidirectionalNodeIterator&;

  /// \brief Postfix Increment Operator. Will return the original iterator, and then advance backward the current one
  /// \exceptsafe
  /// \return BackwardBidirectionalNodeIterator = A copy of the original iterator
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \public
  __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- (int) noexcept -> BackwardBidirectionalNodeIterator;
};

} // namespace cds

#endif // __CDS_SHARED_NODE_ITERATOR_HPP__
