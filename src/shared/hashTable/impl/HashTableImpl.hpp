//
// Created by loghin on 27/07/22.
//

#ifndef __CDS_SHARED_HASH_TABLE_IMPL_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_SHARED_HASH_TABLE_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

template <
    typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyComparator,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> constexpr __HashTable <
    __ElementType, __KeyType, __KeyHasher, __RehashPolicy,
    __keyExtractor, __keyComparator, __nodeDestructor
>::__HashTable() noexcept = default;


template <
    typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyComparator,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> constexpr __HashTable <
    __ElementType, __KeyType, __KeyHasher, __RehashPolicy,
    __keyExtractor, __keyComparator, __nodeDestructor
>::__HashTable (__KeyHasher const& keyHasher) noexcept :
    _hasher (keyHasher) {
  // only hasher received, initialize key hasher using received one
}


template <
    typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyComparator,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> constexpr __HashTable <
    __ElementType, __KeyType, __KeyHasher, __RehashPolicy,
    __keyExtractor, __keyComparator, __nodeDestructor
>::__HashTable (__RehashPolicy const& rehashPolicy) noexcept :
    _rehash (rehashPolicy) {
  // only rehash policy received, initialize rehash policy using received one
}


template <
    typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyComparator,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> constexpr __HashTable <
    __ElementType, __KeyType, __KeyHasher, __RehashPolicy,
    __keyExtractor, __keyComparator, __nodeDestructor
>::__HashTable (__KeyHasher const& keyHasher, __RehashPolicy const& rehashPolicy) noexcept :
    _hasher (keyHasher),
    _rehash (rehashPolicy) {
  // initialize key hasher and rehash policy using received ones
}


template <
    typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyComparator,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> template <
    typename                                                            __CopyFunction      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_OptimalInline __HashTable <
    __ElementType, __KeyType, __KeyHasher, __RehashPolicy,
    __keyExtractor, __keyComparator, __nodeDestructor
>::__HashTable (__HashTable const& hashTable, __CopyFunction const& copyFunction) noexcept (false) {
  // initialize by copy cleared, since hash table is at construction
  __ht_copyCleared (hashTable, copyFunction);
}


template <
    typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyComparator,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> constexpr __HashTable <
    __ElementType, __KeyType, __KeyHasher, __RehashPolicy,
    __keyExtractor, __keyComparator, __nodeDestructor
>::__HashTable (__HashTable&& hashTable) noexcept :
    _pBucketArray (cds::exchange (hashTable._pBucketArray, nullptr)),
    _bucketCount (cds::exchange (hashTable._bucketCount, 0u)),
    _size (cds::exchange (hashTable._size, 0u)),
    _rehash (std::move (hashTable._rehash)),
    _hasher (std::move (hashTable._hasher)) {

}


template <
    typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyComparator,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __HashTable <
    __ElementType, __KeyType, __KeyHasher, __RehashPolicy,
    __keyExtractor, __keyComparator, __nodeDestructor
>::__ht_clear() noexcept -> void {
  // nothing to clear
  if (_pBucketArray == nullptr) {
    return;
  }

  // parse each bucket
  for (Size bucketIndex = 0u; bucketIndex < _bucketCount; ++bucketIndex) {
    // parse the bucket node by node
    __NodeType*& bucket = _pBucketArray [bucketIndex];
    while (bucket != nullptr) {
      // acquire next and free current node
      auto pCopy = bucket;
      bucket = bucket->_pNext;
      __ht_freeNode (pCopy);
    }
  }

  // reset the rehash policy, size and free the bucket buffer
  _rehash.reset();
  __ht_freeBuckets();
  _size = 0u;
}


template <
    typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyComparator,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> constexpr auto __HashTable <
    __ElementType, __KeyType, __KeyHasher, __RehashPolicy,
    __keyExtractor, __keyComparator, __nodeDestructor
>::__ht_size () const noexcept -> Size {
  // return number of elements directly
  return _size;
}


template <
    typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyComparator,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> constexpr auto __HashTable <
    __ElementType, __KeyType, __KeyHasher, __RehashPolicy,
    __keyExtractor, __keyComparator, __nodeDestructor
>::__ht_empty () const noexcept -> bool {
  // empty if no element exists
  return _size == 0u;
}


template <
    typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyComparator,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_MaybeUnused constexpr auto __HashTable <
    __ElementType, __KeyType, __KeyHasher, __RehashPolicy,
    __keyExtractor, __keyComparator, __nodeDestructor
>::__ht_bucketCount () const noexcept -> Size {
  // return the bucket count directly
  return _bucketCount;
}


template <
    typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyComparator,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_cpplang_NonConstConstexprMemberFunction auto __HashTable <
    __ElementType, __KeyType, __KeyHasher, __RehashPolicy,
    __keyExtractor, __keyComparator, __nodeDestructor
>::__ht_begin () noexcept -> __ht_Iterator {
  // pass the bucket array and count, let the iterator find the first element
  return __ht_Iterator (_pBucketArray, _bucketCount);
}


template <
    typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyComparator,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_cpplang_NonConstConstexprMemberFunction auto __HashTable <
    __ElementType, __KeyType, __KeyHasher, __RehashPolicy,
    __keyExtractor, __keyComparator, __nodeDestructor
>::__ht_end () noexcept -> __ht_Iterator {
  // pass no array, invalid memory space
  return __ht_Iterator (nullptr, 0u);
}


template <
    typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyComparator,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> constexpr auto __HashTable <
    __ElementType, __KeyType, __KeyHasher, __RehashPolicy,
    __keyExtractor, __keyComparator, __nodeDestructor
>::__ht_cbegin () const noexcept -> __ht_ConstIterator {
  // pass the bucket array and count, let the iterator find the first element
  return __ht_ConstIterator (_pBucketArray, _bucketCount);
}


template <
    typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyComparator,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> constexpr auto __HashTable <
    __ElementType, __KeyType, __KeyHasher, __RehashPolicy,
    __keyExtractor, __keyComparator, __nodeDestructor
>::__ht_cend () const noexcept -> __ht_ConstIterator {
  // pass no array, invalid memory space
  return __ht_ConstIterator (nullptr, 0u);
}


template <
    typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyComparator,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_OptimalInline auto __HashTable <
    __ElementType, __KeyType, __KeyHasher, __RehashPolicy,
    __keyExtractor, __keyComparator, __nodeDestructor
>::__ht_new (
    __ElementType const*  pReferenceElement,
    bool*                 pNewElementCreated
) noexcept(false) -> __ElementType* {
  // acquire key from reference element and return the value from __ht_get
  return __ht_get (__keyExtractor (*pReferenceElement), pNewElementCreated);
}


template <
    typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyComparator,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __HashTable <
    __ElementType, __KeyType, __KeyHasher, __RehashPolicy,
    __keyExtractor, __keyComparator, __nodeDestructor
>::__ht_get (__KeyType const& key, bool* pIsNew) noexcept(false) -> __ElementType* {
  // if no bucket array exists
  if (_pBucketArray == nullptr) {
    // allocate the bucket array
    __ht_allocateBuckets (_rehash.currentFactor());
  }

  // obtain the hash of the key
  auto const hashValue        = _hasher (key);
  // obtain the bucket where to insert the node into
  __NodeType*& bucket         = __ht_bucket (hashValue);
  // node pointer used both to parse the current bucket and to allocate space, if no node found
  __NodeType* pSeekAndNewNode = bucket;
  // size of current bucket, to detect a potential rehash
  Size bucketSize             = 0u;

  // start looking into current bucket
  while (pSeekAndNewNode != nullptr) {
    // compare extracted node key with received key
    if (__keyComparator (__keyExtractor (pSeekAndNewNode->_data), key)) {
      // if key found, no new node created, returned address of node data
      *pIsNew = false;
      return &pSeekAndNewNode->_data;
    }
    // look forward into bucket
    pSeekAndNewNode = pSeekAndNewNode->_pNext;
    ++bucketSize;
  }

  // if flow control reaches this point, new node can be created. It will be inserted at the head
  pSeekAndNewNode         = __ht_allocateNode();
  pSeekAndNewNode->_pNext = bucket;
  bucket                  = pSeekAndNewNode;
  // increased size of table
  ++_size;

  // if, potentially, bucket exceeds load factor, check if a rehash is required with current parameters
  if (bucketSize >= _rehash.loadFactor()) {
    auto const rehashRequiredData = _rehash.rehashRequired (_bucketCount, _size, 1u);
    // if rehash is required, initiate it
    if (rehashRequiredData._required) {
      __ht_rehash (rehashRequiredData._size, hashValue, pSeekAndNewNode);
    }
  }

  // at this point, a new node was inserted, and, potentially, the table has rehashed.
  *pIsNew = true;
  // return memory space of new node data
  return &pSeekAndNewNode->_data;
}


template <
    typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyComparator,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_cpplang_ConstexprConditioned auto __HashTable <
    __ElementType, __KeyType, __KeyHasher, __RehashPolicy,
    __keyExtractor, __keyComparator, __nodeDestructor
>::__ht_getConst (__KeyType const& key) const noexcept -> __ElementType const* {
  // 0 elements -> no node
  if (__ht_empty()) {
    return nullptr;
  }

  // acquire bucket for the received key and parse it
  auto pBucketHead = __ht_bucket (_hasher (key));
  while (pBucketHead != nullptr) {
    // if key extracted from bucket node matches the key received
    if (__keyComparator (__keyExtractor (pBucketHead->_data), key)) {
      // return memory address to the node data
      return &pBucketHead->_data;
    }
    // otherwise, forward into bucket
    pBucketHead = pBucketHead->_pNext;
  }

  // bucket parsed, no node found matching the given key. No such key exists, return null
  return nullptr;
}


template <
    typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyComparator,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_MaybeUnused __CDS_OptimalInline auto __HashTable <
    __ElementType, __KeyType, __KeyHasher, __RehashPolicy,
    __keyExtractor, __keyComparator, __nodeDestructor
>::__ht_at (__KeyType const& key) noexcept -> __ElementType* {
  // 'reuse' code from __get, dirty const casts. Theoretically legal
  return const_cast <__ElementType*> (static_cast <__HashTable const*> (this)->__ht_getConst (key));
}


template <
    typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyComparator,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_MaybeUnused __CDS_OptimalInline auto __HashTable <
    __ElementType, __KeyType, __KeyHasher, __RehashPolicy,
    __keyExtractor, __keyComparator, __nodeDestructor
>::__ht_atConst (__KeyType const& key) const noexcept -> __ElementType const* {
  // at and get only differ for the non-const versions. const are the same
  return __ht_getConst (key);
}


template <
    typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyComparator,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __HashTable <
    __ElementType, __KeyType, __KeyHasher, __RehashPolicy,
    __keyExtractor, __keyComparator, __nodeDestructor
>::__ht_rehash (
    Size              bucketCount,
    Size              hashValueOfNewNode,
    __NodeType const* pNewEmptyNode
) noexcept(false) -> void {

  // store the old bucket size
  Size          oldBucketSize = _bucketCount;
  // value of computed local hashes
  Size          newHash;
  // pointer used to move nodes during rehash
  __NodeType*   pToMove;
  // re-allocate the buckets, increasing the count
  __ht_allocateBuckets (bucketCount);

  // parse each bucket
  for (Size bucketIndex = 0u; bucketIndex < oldBucketSize; ++bucketIndex) {
    // Acquire the 'old', not updated bucket
    // guaranteed to be lower than newer size, so using the method
    // with the new greater modulus will not impact the result
    auto& oldBucket = __ht_bucket (bucketIndex);

    // parse the bucket to clear nodes at the front
    while (oldBucket != nullptr) {
      // if the uninitialized node is in this bucket
      if (pNewEmptyNode == oldBucket) {
        // the 'new' hash, post rehash is the one received as parameter
        newHash = hashValueOfNewNode;
      } else {
        // otherwise, recompute the hash from the extracted key
        newHash = _hasher (__keyExtractor (oldBucket->_data));
      }

      // acquire the new bucket
      auto& newBucket = __ht_bucket (newHash);
      // if same bucket, no need to go forward, front remains in current bucket
      if (newBucket == oldBucket) {
        break;
      }

      // otherwise, prepare and move node. Advance bucket and Check next node
      pToMove     = oldBucket;
      oldBucket   = oldBucket->_pNext;
      __ht_rehashEmplace (&newBucket, pToMove);
    }

    // First node validated, start parse with lookahead
    __NodeType* pOldBucketHead = oldBucket;
    while (pOldBucketHead != nullptr && pOldBucketHead->_pNext != nullptr) {
      // same principle, if node is the uninitialized one
      if (pNewEmptyNode == pOldBucketHead->_pNext) {
        // get hash from parameter
        newHash = hashValueOfNewNode;
      } else {
        // otherwise, compute from key extracted from node
        newHash = _hasher (__keyExtractor (pOldBucketHead->_pNext->_data));
      }

      // acquire the bucket using the recomputed hash
      auto & newBucket = __ht_bucket (newHash);
      // if same bucket, node remains here. Advance and repeat
      if (newBucket == oldBucket) {
        pOldBucketHead = pOldBucketHead->_pNext;
        continue;
      }

      // otherwise, prepare and move node. Relink current list
      pToMove                 = pOldBucketHead->_pNext;
      pOldBucketHead->_pNext  = pOldBucketHead->_pNext->_pNext;

      __ht_rehashEmplace (&newBucket, pToMove);
    }
  }
}


template <
    typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyComparator,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_OptimalInline auto __HashTable <
    __ElementType, __KeyType, __KeyHasher, __RehashPolicy,
    __keyExtractor, __keyComparator, __nodeDestructor
>::__ht_rehashEmplace (__NodeType** pBucket, __NodeType* pNode) noexcept -> void {
  // emplace modifies the list, since it adds the new node as a new head
  pNode->_pNext = *pBucket;
  *pBucket      = pNode;
}


template <
    typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyComparator,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_cpplang_NonConstConstexprMemberFunction auto __HashTable <
    __ElementType, __KeyType, __KeyHasher, __RehashPolicy,
    __keyExtractor, __keyComparator, __nodeDestructor
>::__ht_bucket (Size hash) noexcept -> __NodeType*& {
  // function truncates the received hash before acquiring the bucket, applying the correct remainder class
  return _pBucketArray [hash % _bucketCount];
}


template <
    typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyComparator,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_MaybeUnused constexpr auto __HashTable <
    __ElementType, __KeyType, __KeyHasher, __RehashPolicy,
    __keyExtractor, __keyComparator, __nodeDestructor
>::__ht_bucket (Size hash) const noexcept -> __NodeType* const& {
  // function truncates the received hash before acquiring the bucket, applying the correct remainder class
  return _pBucketArray [hash % _bucketCount];
}


template <
    typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyComparator,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_OptimalInline auto __HashTable <
    __ElementType, __KeyType, __KeyHasher, __RehashPolicy,
    __keyExtractor, __keyComparator, __nodeDestructor
>::__ht_allocateBuckets (Size bucketCount) noexcept(false) -> void {
  using __Alloc = __allocation::__PrimitiveAlloc <__NodeType*>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  // reallocate the bucket array and clear the newly created buckets
  _pBucketArray = static_cast <__NodeType**> (
      std::memset (
          __Alloc::__realloc (0u, _pBucketArray, bucketCount) + _bucketCount,
          0u,
          sizeof (__NodeType*) * (bucketCount - _bucketCount)
      )
  ) - _bucketCount;

  // update stored bucket count - remainder class
  _bucketCount = bucketCount;
}


template <
    typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyComparator,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_OptimalInline auto __HashTable <
    __ElementType, __KeyType, __KeyHasher, __RehashPolicy,
    __keyExtractor, __keyComparator, __nodeDestructor
>::__ht_freeBuckets () noexcept -> void {
  using __Alloc = __allocation::__PrimitiveAlloc <__NodeType*>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  // free bucket array and clear bucket count
  __Alloc::__free (cds::exchange (_pBucketArray, nullptr));
  _bucketCount = 0u;
}


template <
    typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyComparator,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_OptimalInline auto __HashTable <
    __ElementType, __KeyType, __KeyHasher, __RehashPolicy,
    __keyExtractor, __keyComparator, __nodeDestructor
>::__ht_allocateNode () noexcept(false) -> __NodeType* {
  using __Alloc = __allocation::__PrimitiveAlloc <__NodeType>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  // wrapper for primitive allocation
  return __Alloc::__alloc();
}


template <
    typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyComparator,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_OptimalInline auto __HashTable <
    __ElementType, __KeyType, __KeyHasher, __RehashPolicy,
    __keyExtractor, __keyComparator, __nodeDestructor
>::__ht_freeNode (__NodeType* pNode) noexcept -> void {
  using __Alloc = __allocation::__PrimitiveAlloc <__NodeType>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  // call data destructor, then free primitive node
  __nodeDestructor (pNode->_data);
  __Alloc::__free (pNode);
}


template <
    typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyComparator,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __HashTable <
    __ElementType, __KeyType, __KeyHasher, __RehashPolicy,
    __keyExtractor, __keyComparator, __nodeDestructor
>::__ht_remove (__KeyType const& key) noexcept -> bool {
  return __ht_removeGetPtr(key) != nullptr;
}


template <
    typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyComparator,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __HashTable <
    __ElementType, __KeyType, __KeyHasher, __RehashPolicy,
    __keyExtractor, __keyComparator, __nodeDestructor
>::__ht_removeGetPtr (__KeyType const & key) noexcept -> __ElementType* {
  // no elements -> nothing to remove
  if ( __ht_empty() ) {
      return nullptr;
  }

  __NodeType*     pToRemove;
  __NodeType*     pBucketHead;
  __ElementType*  pOldElement;
  // acquire bucket. if key matches the front node key, remove front
  auto& bucket = __ht_bucket (_hasher (key));
  if (bucket == nullptr) {
    return nullptr;
  }

  if (__keyComparator (__keyExtractor (bucket->_data), key)) {
    pToRemove   = bucket;
    bucket      = bucket->_pNext;
    pOldElement = &pToRemove->_data;
    __ht_freeNode (pToRemove);

    // removal successful
    --_size;
    return pOldElement;
  }

  // otherwise, parse with lookahead to be able to relink list
  pBucketHead = bucket;
  while (pBucketHead->_pNext != nullptr) {
    // matching key found, remove and relink
    if (__keyComparator (__keyExtractor (pBucketHead->_pNext->_data), key)) {
      pToRemove           = pBucketHead->_pNext;
      pBucketHead->_pNext = pBucketHead->_pNext->_pNext;
      pOldElement         = &pToRemove->_data;
       __ht_freeNode (pToRemove);

      // removal successful
      --_size;
      return pOldElement;
    }

    // otherwise, keep checking bucket
    pBucketHead = pBucketHead->_pNext;
  }

  // no removal done - no matching key in nodes found - unsuccessful
  return nullptr;
}


template <
    typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyComparator,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_MaybeUnused auto __HashTable <
    __ElementType, __KeyType, __KeyHasher, __RehashPolicy,
    __keyExtractor, __keyComparator, __nodeDestructor
>::__ht_removeNode (
    __NodeType const* pPreviousNode,
    __NodeType const* pCurrentNode,
    Size              bucketIndex
) noexcept -> bool {
  // if no nodes or index out of bounds, no removal done
  if (__ht_empty() || bucketIndex >= _bucketCount) {
      return false;
  }

  // acquire bucket to compute front check
  __NodeType*& pBucket  = __ht_bucket (bucketIndex);

  // transform immutable to mutable nodes. Dirty, but not-a-const function
  auto pPreviousCasted  = const_cast <__NodeType*> (pPreviousNode);
  auto pCurrentCasted   = const_cast <__NodeType*> (pCurrentNode);

  if (pPreviousCasted == nullptr && pCurrentCasted == pBucket) {
    // if front, remove at front and advance bucket
    pBucket = pBucket->_pNext;
    __ht_freeNode (pCurrentCasted);
  } else if (pCurrentCasted != nullptr && pPreviousCasted != nullptr) {
    // otherwise, if from inside the list, remove and relink
    pPreviousCasted->_pNext = pCurrentCasted->_pNext;
    __ht_freeNode (pCurrentCasted);
  } else {
    // if neither case applies, not a correct remove
    return false;
  }

  // decrease size and return success
  --_size;
  return true;
}


template <
    typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyComparator,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_OptimalInline auto __HashTable <
    __ElementType, __KeyType, __KeyHasher, __RehashPolicy,
    __keyExtractor, __keyComparator, __nodeDestructor
>::__ht_removeIterator (__ht_Iterator const & iterator) noexcept -> bool {
  if (
      iterator._bucketIndex >= iterator._bucketCount ||
      iterator._pListArray == nullptr ||
      iterator._pCurrentNode == nullptr && iterator._pPreviousNode == nullptr
  ) {
    // if index out of bounds, or iterator list does not exist, or node values are null, cannot remove due to invalid iterator
    return false;
  }
  // otherwise, use node removal function
  return __ht_removeNode (iterator._pPreviousNode, iterator._pCurrentNode, iterator._bucketIndex);
}


template <
    typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyComparator,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_OptimalInline auto __HashTable <
    __ElementType, __KeyType, __KeyHasher, __RehashPolicy,
    __keyExtractor, __keyComparator, __nodeDestructor
>::__ht_removeIteratorConst (__ht_ConstIterator const & iterator) noexcept -> bool {
  if (
      iterator._bucketIndex >= iterator._bucketCount ||
      iterator._pListArray == nullptr ||
      iterator._pCurrentNode == nullptr && iterator._pPreviousNode == nullptr
  ) {
    // if index out of bounds, or iterator list does not exist, or node values are null, cannot remove due to invalid iterator
    return false;
  }
  // otherwise, use node removal function
  return __ht_removeNode (iterator._pPreviousNode, iterator._pCurrentNode, iterator._bucketIndex);
}


template <
    typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyComparator,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_OptimalInline auto __HashTable <
    __ElementType, __KeyType, __KeyHasher, __RehashPolicy,
    __keyExtractor, __keyComparator, __nodeDestructor
>::__ht_removeIteratorArray (
    __ht_Iterator const* const* ppIterators,
    Size                        iteratorCount
) noexcept -> Size {
  // no gain from having a special implementation. call basic iterator remove for all iterators.
  // also keep track of removed iterator count
  Size removedCount = 0u;
  for (Size index = 0u; index < iteratorCount; ++index) {
    if (__ht_removeIterator (*ppIterators [index])) {
      ++removedCount;
    }
  }
  return removedCount;
}


template <
    typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyComparator,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_OptimalInline auto __HashTable <
    __ElementType, __KeyType, __KeyHasher, __RehashPolicy,
    __keyExtractor, __keyComparator, __nodeDestructor
>::__ht_removeConstIteratorArray (
    __ht_ConstIterator const* const*  ppIterators,
    Size                              iteratorCount
) noexcept -> Size {
  // no gain from having a special implementation. call basic iterator remove for all iterators.
  // also keep track of removed iterator count
  Size removedCount = 0u;
  for (Size index = 0u; index < iteratorCount; ++index) {
    if (__ht_removeIteratorConst (*ppIterators [index])) {
      ++removedCount;
    }
  }
  return removedCount;
}


template <
    typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyComparator,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> template <
        typename                                                            __CopyFunction      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_MaybeUnused __CDS_OptimalInline auto __HashTable <
    __ElementType, __KeyType, __KeyHasher, __RehashPolicy,
    __keyExtractor, __keyComparator, __nodeDestructor
>::__ht_copy (
    __HashTable const&    table,
    __CopyFunction const& copyFunction
) noexcept(false) -> void {
  // self-check
  if (this == &table) {
    return;
  }

  // clear and call copyCleared
  __ht_clear();
  __ht_copyCleared (table, copyFunction);
}


template <
    typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyComparator,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> template <
        typename                                                            __CopyFunction      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __HashTable <
    __ElementType, __KeyType, __KeyHasher, __RehashPolicy,
    __keyExtractor, __keyComparator, __nodeDestructor
>::__ht_copyCleared (
    __HashTable const&    table,
    __CopyFunction const& copyFunction
) noexcept(false) -> void {

  // if nothing to copy, do not copy
  if (table.__ht_empty()) {
    return;
  }

  // copy size and allocate buckets
  _size = table._size;
  __ht_allocateBuckets (table._bucketCount);

  // parse each bucket from received table
  for (Size bucketIndex = 0u; bucketIndex < table._bucketCount; ++bucketIndex) {
    // acquire the bucket heads
    auto& thisBucket  = __ht_bucket (bucketIndex);
    auto& tableBucket = table.__ht_bucket (bucketIndex);

    // create parse copy for received table and back for new bucket
    __NodeType* pTableHead  = tableBucket;
    __NodeType* pThisBack   = nullptr;

    // parse to the end
    while (pTableHead != nullptr) {
      // create a new node, initialize the memory using the copy function
      auto pNewNode       = __ht_allocateNode ();
      pNewNode->_pNext    = nullptr;
      copyFunction (pNewNode->_data, pTableHead->_data);

      // advance other table bucket
      pTableHead = pTableHead->_pNext;
      // push back in new bucket. If no back, skip. otherwise, link to previous back
      if (pThisBack == nullptr) {
        thisBucket          = pNewNode;
      } else {
        pThisBack->_pNext   = pNewNode;
      }
      // store new back
      pThisBack = pNewNode;
    }
  }

  // also copy the rehash policy values.
  _rehash = table._rehash;
}


template <
    typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyComparator,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_MaybeUnused __CDS_OptimalInline auto __HashTable <
    __ElementType, __KeyType, __KeyHasher, __RehashPolicy,
    __keyExtractor, __keyComparator, __nodeDestructor
>::__ht_move (__HashTable&& table) noexcept -> void {
  // self-check
  if (this == &table) {
    return;
  }
  // clear and call moveCleared
  __ht_clear();
  __ht_moveCleared (std::move (table));
}


template <
    typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyComparator,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_cpplang_NonConstConstexprMemberFunction auto __HashTable <
    __ElementType, __KeyType, __KeyHasher, __RehashPolicy,
    __keyExtractor, __keyComparator, __nodeDestructor
>::__ht_moveCleared (__HashTable&& table) noexcept -> void {
  // acquire and release every component. Move rehash and hasher, others exchange for defaults
  _pBucketArray = cds::exchange (table._pBucketArray, nullptr);
  _bucketCount  = cds::exchange (table._bucketCount, 0u);
  _size         = cds::exchange (table._size, 0u);
  _rehash       = std::move (table._rehash);
  _hasher       = std::move (table._hasher);
}


template <
    typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyComparator,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __HashTable <
    __ElementType, __KeyType, __KeyHasher, __RehashPolicy,
    __keyExtractor, __keyComparator, __nodeDestructor
>::__ht_findIterator (__KeyType const& key) noexcept -> __ht_Iterator {
  // if no elements, return end iterator
  if (__ht_empty()) {
    return __ht_end ();
  }

  // acquire bucket index directly, used by iterator
  Size bucketIndex = _hasher (key) % _bucketCount;
  if (bucketIndex >= _bucketCount) {
    return __ht_end();
  }

  // store the previous and current values used in initialization
  __NodeType* pPrevious = nullptr;
  __NodeType* pCurrent  = _pBucketArray [bucketIndex];

  // while bucket has elements
  while (pCurrent != nullptr) {
    // compare extracted node key with received key
    if (__keyComparator (__keyExtractor (pCurrent->_data), key)) {
      // if matching, compose and return iterator
      return __ht_Iterator (
          _pBucketArray, _bucketCount,
          pCurrent, pPrevious, bucketIndex
      );
    }
    // otherwise, advance iteration
    pPrevious   = pCurrent;
    pCurrent    = pCurrent->_pNext;
  }

  // if no matching node found, return end iterator
  return __ht_end();
}


template <
    typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyComparator,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __HashTable <
    __ElementType, __KeyType, __KeyHasher, __RehashPolicy,
    __keyExtractor, __keyComparator, __nodeDestructor
>::__ht_findIteratorConst (__KeyType const& key) const noexcept -> __ht_ConstIterator {

  // if no elements, return end iterator
  if (__ht_empty()) {
    return __ht_cend ();
  }

  // acquire bucket index directly, used by iterator
  Size bucketIndex = _hasher (key) % _bucketCount;
  if (bucketIndex >= _bucketCount) {
    return __ht_cend();
  }

  // store the previous and current values used in initialization
  __NodeType const* pPrevious  = nullptr;
  __NodeType const* pCurrent   = _pBucketArray [bucketIndex];

  // while bucket has elements
  while (pCurrent != nullptr) {
    // compare extracted node key with received key
    if (__keyComparator (__keyExtractor (pCurrent->_data), key)) {
      // if matching, compose and return iterator
      return __ht_ConstIterator (
              _pBucketArray, _bucketCount,
              pCurrent, pPrevious, bucketIndex
      );
    }
    // otherwise, advance iteration
    pPrevious   = pCurrent;
    pCurrent    = pCurrent->_pNext;
  }

  // if no matching node found, return end iterator
  return __ht_cend();
}


template <
    typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyComparator,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_cpplang_ConstexprConditioned auto __HashTable <
    __ElementType, __KeyType, __KeyHasher, __RehashPolicy,
    __keyExtractor, __keyComparator, __nodeDestructor
>::__ht_equals (__HashTable const &table) const noexcept -> bool {
  // self check
  if (this == &table) {
    return true;
  }

  // if this is empty, return if other is also empty
  if (__ht_empty()) {
    return table.__ht_empty();
  }

  // if other is empty or bucket counts are different, not equal
  if (table.__ht_empty() || _bucketCount != table._bucketCount) {
    return false;
  }

  // otherwise, neither are empty, and have same bucket count. parse buckets
  for (Size bucketIndex = 0u; bucketIndex < _bucketCount; ++bucketIndex) {
    // parse buckets synchronously
    auto pThisBucketHead    = _pBucketArray [bucketIndex];
    auto pOtherBucketHead   = table._pBucketArray [bucketIndex];

    // while both have elements
    while (pThisBucketHead != nullptr && pOtherBucketHead != nullptr) {
      // if a node difference is found ( not key, element comparison )
      if (!__keyComparator (__keyExtractor (pThisBucketHead->_data), __keyExtractor (pOtherBucketHead->_data))) {
        // tables are not equal
        return false;
      }
    }

    // if any bucket still has elements, not equal buckets, not equal tables
    if (pThisBucketHead != nullptr || pOtherBucketHead != nullptr) {
      return false;
    }
  }

  // all buckets parsed and no difference found, tables are equal
  return true;
}

} // namespace __impl
} // namespace __hidden
} // namespace cds

#endif // __CDS_SHARED_HASH_TABLE_IMPL_HPP__
