//
// Created by loghin on 27/07/22.
//

#ifndef __CDS_SHARED_HASH_TABLE_ITERATOR_IMPL_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_SHARED_HASH_TABLE_ITERATOR_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
template <typename __Element> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto HashTableIterator <__Element>::advanceBucket () noexcept -> void {
  // If current Node is null, end of bucket list reached, reset previous node 
  if (_pCurrentNode == nullptr) {
    _pPreviousNode = nullptr;
  }

  // While a non-empty list has not been reached, and we still have buckets to check 
  while (_pCurrentNode == nullptr && _bucketIndex + 1u < _bucketCount) {
    // Advance the bucket index and acquire the bucket's head 
    _pCurrentNode = _pListArray [++_bucketIndex];
  }

  // If last bucket has been completely parsed 
  if (_bucketIndex + 1u == _bucketCount && _pCurrentNode == nullptr) {
    // Advance the index further so that no new buckets are looked into 
    ++_bucketIndex;
  }
}


template <typename __Element> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr HashTableIterator <__Element>::HashTableIterator () noexcept = default;


template <typename __Element> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned HashTableIterator <__Element>::HashTableIterator (
    Node**  pListArray,
    Size    bucketCount
) noexcept :
    _pListArray (pListArray),
    _bucketCount (bucketCount),
    _pCurrentNode (pListArray == nullptr ? nullptr : pListArray [0u]) {
  // Initialize iterator by copying the bucket list and size, and the initial node, if given a bucket list, based on the first bucket head 
  // Advance the bucket, will not do anything if first bucket has nodes inside 
  advanceBucket();
}


template <typename __Element> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr HashTableIterator <__Element>::HashTableIterator (
    Node**  pListArray,
    Size    bucketCount,
    Node*   pCurrentNode,
    Node*   pPreviousNode,
    Size    bucketIndex
) noexcept :
    _pListArray (pListArray),
    _bucketCount (bucketCount),
    _pCurrentNode (pCurrentNode),
    _pPreviousNode (pPreviousNode),
    _bucketIndex (bucketIndex) {
  // Copy all the given data, no advancement needed is assumed, since all necessary data has been provided 
}


template <typename __Element> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr HashTableIterator <__Element>::HashTableIterator (
    HashTableIterator const& iterator
) noexcept :
    _pListArray (iterator._pListArray),
    _bucketCount (iterator._bucketCount),
    _pCurrentNode (iterator._pCurrentNode),
    _pPreviousNode (iterator._pPreviousNode),
    _bucketIndex (iterator._bucketIndex) {
  // copy all data from given iterator 
}


template <typename __Element> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr HashTableIterator <__Element>::HashTableIterator (
    HashTableIterator&& iterator
) noexcept :
    _pListArray (cds::exchange (iterator._pListArray, nullptr)),
    _bucketCount (cds::exchange (iterator._bucketCount, 0u)),
    _pCurrentNode (cds::exchange (iterator._pCurrentNode, nullptr)),
    _pPreviousNode (cds::exchange (iterator._pPreviousNode, nullptr)),
    _bucketIndex (cds::exchange (iterator._bucketIndex, 0u)) {
  // move all data from given iterator 
}


template <typename __Element> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto HashTableIterator <__Element>::operator = (
    HashTableIterator const& iterator
) noexcept -> HashTableIterator& {
  // if given same iterator, copy is unnecessary 
  if (this == &iterator) {
    return *this;
  }

  // otherwise, copy all data from given iterator 
  _pListArray       = iterator._pListArray;
  _bucketCount      = iterator._bucketCount;
  _pCurrentNode     = iterator._pCurrentNode;
  _pPreviousNode    = iterator._pPreviousNode;
  _bucketIndex      = iterator._bucketIndex;
  return *this;
}


template <typename __Element> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto HashTableIterator <__Element>::operator = (
    HashTableIterator&& iterator
) noexcept -> HashTableIterator& {
  // if given same iterator, move is unnecessary 
  if (this == &iterator) {
    return *this;
  }

  // otherwise, move all data from given iterator 
  _pListArray       = cds::exchange (iterator._pListArray, nullptr);
  _bucketCount      = cds::exchange (iterator._bucketCount, 0u);
  _pCurrentNode     = cds::exchange (iterator._pCurrentNode, nullptr);
  _pPreviousNode    = cds::exchange (iterator._pPreviousNode, nullptr);
  _bucketIndex      = cds::exchange (iterator._bucketIndex, 0u);
  return *this;
}


template <typename __Element> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto HashTableIterator <__Element>::listArray () const noexcept -> Node** {
  // return the bucket list 
  return _pListArray;
}


template <typename __Element> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto HashTableIterator <__Element>::bucketCount () const noexcept -> Size {
  // return the bucket list size 
  return _bucketCount;
}


template <typename __Element> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto HashTableIterator <__Element>::bucketIndex () const noexcept -> Size {
  // return the bucket index 
  return _bucketIndex;
}


template <typename __Element> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto HashTableIterator <__Element>::currentNode () const noexcept -> Node* {
  // return the current node 
  return _pCurrentNode;
}


template <typename __Element> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto HashTableIterator <__Element>::previousNode () const noexcept -> Node* {
  // return the previous node 
  return _pPreviousNode;
}


template <typename __Element> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto HashTableIterator <__Element>::operator ++ () noexcept -> HashTableIterator & {
  // if bucket list is completely parsed, do nothing 
  if (_bucketIndex >= _bucketCount) {
    return *this;
  }

  // advance previous node to current 
  _pPreviousNode    = _pCurrentNode;
  // advance current node to next 
  _pCurrentNode     = _pCurrentNode->_pNext;

  // If end of bucket reached, advance to next bucket 
  if (_pCurrentNode == nullptr) {
    advanceBucket();
  }

  return *this;
}


template <typename __Element> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto HashTableIterator <__Element>::operator ++ (int) noexcept -> HashTableIterator {
  // copy, advance current, return copy 
  auto copy = *this;
  ++(*this);
  return copy;
}


template <typename __Element> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto HashTableIterator <__Element>::operator * () const noexcept -> RVal& {
  // acquire value from current node 
  return _pCurrentNode->_data;
}


template <typename __Element> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto HashTableIterator <__Element>::operator -> () const noexcept -> RVal* {
  // acquire address of element from current node 
  return &_pCurrentNode->_data;
}


template <typename __Element> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto HashTableIterator <__Element>::operator != (
    HashTableIterator const& iterator
) const noexcept -> bool {
  // iterators are not equal if not equals ( this, iterator ) 
  return !operator == (iterator);
}


template <typename __Element> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto HashTableIterator <__Element>::operator == (
    HashTableIterator const& iterator
) const noexcept -> bool {
  // iterators are equal if either
  // current node values are the same and not null OR
  // both current nodes are null and previous nodes are equal ( end of last bucket )
  return
      (_pCurrentNode     == iterator._pCurrentNode &&
      _pCurrentNode     != nullptr) ||
      (_pCurrentNode     == iterator._pCurrentNode &&
      _pPreviousNode    == iterator._pPreviousNode);
}


template <typename __Element> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr HashTableIterator <__Element>::operator bool () const noexcept {
  // iterators valid if current node is valid
  return _pCurrentNode != nullptr;
}
} // namespace cds 

#endif // __CDS_SHARED_HASH_TABLE_ITERATOR_IMPL_HPP__ 
