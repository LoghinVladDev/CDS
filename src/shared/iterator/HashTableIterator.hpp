//
// Created by loghin on 27/07/22.
//

#ifndef __CDS_SHARED_HASH_TABLE_ITERATOR_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_SHARED_HASH_TABLE_ITERATOR_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

#include "NodeIteratorTraits.hpp"

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
/// \brief Partial pre-Declaration of __HashTable, as it requires private values
/// \tparam __Element is the type of the node data stored in the hash table
/// \tparam __Key is the key type of the hash table
///
/// \test Suite: N/A, Group: N/A, Test Cases: N/A
/// \namespace cds::__hidden::__impl
template <
    typename __Element, // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Key,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename,
    typename,
    functional::MapperFunction <__Key const&, __Element const&>,
    functional::PredicateFunction <__Key const&, __Key const&>,
    functional::ConsumerFunction <__Element&>
> class __HashTable;            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
} // namespace __impl
} // namespace __hidden

/// \brief Hash Table Iterator, similar to Unidirectional Node Iterator, with the addition of bucket concept.
/// Used by HashMap - begin/end
/// \tparam __Element is the type of the enclosed element.
/// \implements ForwardIterator
///
/// \test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
/// \namespace cds::experimental
template <typename __Element> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class HashTableIterator : public meta::ForwardIterator {
private:
  using Traits = __hidden::__impl::__NodeIteratorTraits <
      __hidden::__impl::__UnidirectionalNode,
      __Element
  >;

  using Node = typename Traits::Node;
  using RVal = typename Traits::RVal;

public:
  /// \brief Default Constructor, constexpr
  /// \exceptsafe
  ///
  /// \test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
  /// \public
  constexpr HashTableIterator () noexcept;

  /// \brief Initialization Constructor, constexpr
  /// \param [in] pListArray : Node ptr ptr = address to a list of addresses of the buckets
  /// \param [in] bucketCount : Size = the size of the address list of buckets
  /// \exceptsafe
  ///
  /// \test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
  /// \pulbic
  __CDS_cpplang_ConstexprConditioned HashTableIterator (Node** pListArray, Size bucketCount) noexcept;

  /// \brief Initialization Constructor, constexpr
  /// \param [in] pListArray : Node ptr ptr = address to a list of addresses of the buckets
  /// \param [in] bucketCount : Size = the size of the address list of buckets
  /// \param [in] pCurrentNode : Node ptr = the address of the initial current Node
  /// \param [in] pPreviousNode : Node ptr = the address of the initial previous Node
  /// \param [in] bucketIndex : Size = index of the initial bucket Index
  /// \exceptsafe
  ///
  /// \test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
  /// \public
  constexpr HashTableIterator (
      Node**  pListArray,
      Size    bucketCount,
      Node*   pCurrentNode,
      Node*   pPreviousNode,
      Size    bucketIndex
  ) noexcept;
  
  /// \brief Copy Constructor, constexpr
  /// \param [in] iterator : HashTableIterator cref = Constant Reference to the iterator to acquire the values from
  /// \exceptsafe
  ///
  /// \test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
  /// \public
  constexpr HashTableIterator (HashTableIterator const& iterator) noexcept;

  /// \brief Move Constructor, constexpr
  /// \param [in, out] iterator : HashTableIterator mref = Move Reference to the iterator to move the values from
  /// \exceptsafe
  ///
  /// \test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
  /// \public
  constexpr HashTableIterator (HashTableIterator&& iterator) noexcept;

  /// \brief Implicit Destructor, constexpr
  /// \exceptsafe
  /// \test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
  /// \public
  ~HashTableIterator () noexcept = default;

  /// \brief Copy Operator, constexpr
  /// \param [in] iterator : HashTableIterator cref = Constant Reference to an iterator to copy the values value from
  /// \exceptsafe
  /// \return HashTableIterator ref = Reference to the modified iterator
  ///
  /// \test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
  /// \public
  __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (HashTableIterator const& iterator) noexcept -> HashTableIterator&; // NOLINT(*-copy-assignment-signature, misc-unconventional-assign-operator)

  /// \brief Move Operator, constexpr
  /// \param [in, out] iterator : HashTableIterator mref = Move Reference to an iterator to move the values value from
  /// \exceptsafe
  /// \return HashTableIterator ref = Reference to the modified iterator
  ///
  /// \test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
  /// \public
  __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (HashTableIterator&& iterator) noexcept -> HashTableIterator&;  // NOLINT(*-copy-assignment-signature, misc-unconventional-assign-operator)

  /// \brief Function used to acquire the bucket list of the iterator
  /// \exceptsafe
  /// \return Node ptr ptr = Address to the Address List
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \private
  __CDS_NoDiscard __CDS_MaybeUnused constexpr auto listArray () const noexcept -> Node**; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \brief Prefix Increment Operator. Will advance forward one position and then return
  /// \exceptsafe
  /// \return HashTableIterator ref = Reference to the modified iterator
  ///
  /// \test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
  /// \public
  __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> HashTableIterator&;

  /// \brief Postfix Increment Operator. Will return the original iterator, and then advance forward the current one
  /// \exceptsafe
  /// \return HashTableIterator = A copy of the original iterator
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \public
  __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ (int) noexcept -> HashTableIterator;

  /// \brief Function used to acquire the current value the iterator is indicating to
  /// \exceptsafe
  /// \return __Element ref = Reference to the element the address is indicating to
  ///
  /// \test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
  /// \public
  __CDS_NoDiscard constexpr auto operator* () const noexcept -> RVal&;

  /// \brief Function used to acquire the address of the value the iterator is indicating to
  /// \exceptsafe
  /// \return __Element ptr = Pointer to the element the address is indicating to
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \public
  __CDS_NoDiscard constexpr auto operator -> () const noexcept -> RVal*;

  /// \brief Inequality Comparison Operator
  /// \param [in] iterator : HashTableIterator cref = Constant Reference to another iterator to compare this one to
  /// \exceptsafe
  /// \return bool = false if iterators are indicating at the same node, with same previous, true otherwise
  ///
  /// \test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
  /// \public
  __CDS_NoDiscard constexpr auto operator != (
      HashTableIterator const& iterator
  ) const noexcept -> bool;

  /// \brief Equality Comparison Operator
  /// \param [in] iterator : HashTableIterator cref = Constant Reference to another iterator to compare this one to
  /// \exceptsafe
  /// \return bool = true if iterators are indicating at the same node, with same previous, false otherwise
  ///
  /// \test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
  /// \public
  __CDS_NoDiscard constexpr auto operator == (
      HashTableIterator const& iterator
  ) const noexcept -> bool;

  /// \brief Validity function, bool cast.
  /// \exceptsafe
  /// \return bool = true if current node is not null, false otherwise
  ///
  /// \test Suite: MCTS-00001, Group: MCTG-00050-IT, MTest Cases: All
  /// \public
  __CDS_NoDiscard __CDS_Explicit constexpr operator bool () const noexcept; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp,///-non-private-member-variables-in-classes)
  
private:
  /// \brief Pre-Declaration of __HashTable, as it requires private values
  /// \tparam __TElement is the type of the node data stored in the hash table
  /// \tparam __Key is the key type of the hash table
  /// \tparam __KeyHasher is the type of the key Hasher
  /// \tparam __RehashPolicy is the type of the Rehash Policy object
  /// \tparam __keyExtractor is the function used to extract the key value from a node element type
  /// \tparam __keyComparator is the function used to compare equality for two keys
  /// \tparam __nodeDestructor is the function used to clear a node's element type
  /// \test Not Applicable.
  /// \namespace cds::__hidden::__impl
  template <
      typename                                                      __TElement,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename                                                      __Key,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename                                                      __KeyHasher,        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename                                                      __RehashPolicy,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      functional::MapperFunction <__Key const&, __TElement const&>  __keyExtractor,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      functional::PredicateFunction <__Key const&, __Key const&>    __keyComparator,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      functional::ConsumerFunction <__TElement&>                    __nodeDestructor    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  > friend class cds::__hidden::__impl::__HashTable;                                    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  /// \brief Function used to acquire the bucket count of the bucket list
  /// \exceptsafe
  /// \return Size = the number of elements in the bucket list
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \private
  __CDS_NoDiscard __CDS_MaybeUnused constexpr auto bucketCount () const noexcept -> Size;

  /// \brief Function used to acquire the bucket index in the bucket list
  /// \exceptsafe
  /// \return Size = the index of the currently used bucket
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \private
  __CDS_NoDiscard __CDS_MaybeUnused constexpr auto bucketIndex () const noexcept -> Size;

  /// \brief Function used to acquire the address of the current node
  /// \exceptsafe
  /// \return Node ptr = Address of the current node
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \private
  __CDS_NoDiscard __CDS_MaybeUnused constexpr auto currentNode () const noexcept -> Node*;

  /// \brief Function used to acquire the address of the previous node
  /// \exceptsafe
  /// \return Node ptr = Address of the previous node
  ///
  /// \test Suite: TBA, Group: TBA, Test Cases: TBA
  /// \private
  __CDS_NoDiscard __CDS_MaybeUnused constexpr auto previousNode () const noexcept -> Node*;

  /// \brief Current Bucket Index in the Bucket Array
  /// \private
  Size        _bucketIndex    {0u};

  /// \brief Current Bucket Count, size of the Bucket Array
  /// \private
  Size        _bucketCount    {0u};

  /// \brief Address of current Node in the current bucket
  /// \private
  Node*       _pCurrentNode   {nullptr};

  /// \brief Address of previous Node in the current bucket
  /// \private
  Node*       _pPreviousNode  {nullptr};

  /// \brief Address of the Bucket List
  /// \private
  Node**      _pListArray     {nullptr};

  /// \brief Function used to advance to the next node. If next node is end of bucket list, advance to next bucket
  /// \exceptsafe
  ///
  /// \test Suite: MCTS-00001, Group: MCTG-00050-IT, Test Cases: All
  /// \private
  __CDS_cpplang_ConstexprConditioned auto advanceBucket () noexcept -> void;
};
} // namespace cds

#endif // __CDS_SHARED_HASH_TABLE_ITERATOR_HPP__
