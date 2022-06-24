//
// Created by loghin on 6/21/22.
//

#ifndef __CDS_HASH_TABLE_IMPL_HPP__
#define __CDS_HASH_TABLE_IMPL_HPP__

namespace cds {             // NOLINT(modernize-concat-nested-namespaces)
    namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
        namespace __impl {  // NOLINT(bugprone-reserved-identifier)

            template <
                    typename __ElementType,         // NOLINT(bugprone-reserved-identifier)
                    typename __KeyType,             // NOLINT(bugprone-reserved-identifier)
                    typename __KeyExtractor,        // NOLINT(bugprone-reserved-identifier)
                    typename __KeyEqualsComparator, // NOLINT(bugprone-reserved-identifier)
                    typename __KeyHasher,           // NOLINT(bugprone-reserved-identifier)
                    typename __RehashPolicy,        // NOLINT(bugprone-reserved-identifier)
                    typename __ElementTypeDestruct  // NOLINT(bugprone-reserved-identifier)
            > __CDS_cpplang_NonConstConstexprMemberFunction auto __HashTable <
                    __ElementType,
                    __KeyType,
                    __KeyExtractor,
                    __KeyEqualsComparator,
                    __KeyHasher,
                    __RehashPolicy,
                    __ElementTypeDestruct
            > :: __ht_begin () noexcept -> HashTableIterator {

                return HashTableIterator ( this );
            }


            template <
                    typename __ElementType,         // NOLINT(bugprone-reserved-identifier)
                    typename __KeyType,             // NOLINT(bugprone-reserved-identifier)
                    typename __KeyExtractor,        // NOLINT(bugprone-reserved-identifier)
                    typename __KeyEqualsComparator, // NOLINT(bugprone-reserved-identifier)
                    typename __KeyHasher,           // NOLINT(bugprone-reserved-identifier)
                    typename __RehashPolicy,        // NOLINT(bugprone-reserved-identifier)
                    typename __ElementTypeDestruct  // NOLINT(bugprone-reserved-identifier)
            > __CDS_cpplang_NonConstConstexprMemberFunction auto __HashTable <
                    __ElementType,
                    __KeyType,
                    __KeyExtractor,
                    __KeyEqualsComparator,
                    __KeyHasher,
                    __RehashPolicy,
                    __ElementTypeDestruct
            > :: __ht_end () noexcept -> HashTableIterator {

                return HashTableIterator ();
            }


            template <
                    typename __ElementType,         // NOLINT(bugprone-reserved-identifier)
                    typename __KeyType,             // NOLINT(bugprone-reserved-identifier)
                    typename __KeyExtractor,        // NOLINT(bugprone-reserved-identifier)
                    typename __KeyEqualsComparator, // NOLINT(bugprone-reserved-identifier)
                    typename __KeyHasher,           // NOLINT(bugprone-reserved-identifier)
                    typename __RehashPolicy,        // NOLINT(bugprone-reserved-identifier)
                    typename __ElementTypeDestruct  // NOLINT(bugprone-reserved-identifier)
            > constexpr auto __HashTable <
                    __ElementType,
                    __KeyType,
                    __KeyExtractor,
                    __KeyEqualsComparator,
                    __KeyHasher,
                    __RehashPolicy,
                    __ElementTypeDestruct
            > :: __ht_cbegin () const noexcept -> HashTableConstIterator {

                return HashTableConstIterator ( this );
            }


            template <
                    typename __ElementType,         // NOLINT(bugprone-reserved-identifier)
                    typename __KeyType,             // NOLINT(bugprone-reserved-identifier)
                    typename __KeyExtractor,        // NOLINT(bugprone-reserved-identifier)
                    typename __KeyEqualsComparator, // NOLINT(bugprone-reserved-identifier)
                    typename __KeyHasher,           // NOLINT(bugprone-reserved-identifier)
                    typename __RehashPolicy,        // NOLINT(bugprone-reserved-identifier)
                    typename __ElementTypeDestruct  // NOLINT(bugprone-reserved-identifier)
            > constexpr auto __HashTable <
                    __ElementType,
                    __KeyType,
                    __KeyExtractor,
                    __KeyEqualsComparator,
                    __KeyHasher,
                    __RehashPolicy,
                    __ElementTypeDestruct
            > :: __ht_cend () const noexcept -> HashTableConstIterator {

                return HashTableConstIterator ();
            }


            template <
                    typename __ElementType,         // NOLINT(bugprone-reserved-identifier)
                    typename __KeyType,             // NOLINT(bugprone-reserved-identifier)
                    typename __KeyExtractor,        // NOLINT(bugprone-reserved-identifier)
                    typename __KeyEqualsComparator, // NOLINT(bugprone-reserved-identifier)
                    typename __KeyHasher,           // NOLINT(bugprone-reserved-identifier)
                    typename __RehashPolicy,        // NOLINT(bugprone-reserved-identifier)
                    typename __ElementTypeDestruct  // NOLINT(bugprone-reserved-identifier)
            > constexpr __HashTable <
                    __ElementType,
                    __KeyType,
                    __KeyExtractor,
                    __KeyEqualsComparator,
                    __KeyHasher,
                    __RehashPolicy,
                    __ElementTypeDestruct
            > :: __HashTable () noexcept = default;


            template <
                    typename __ElementType,         // NOLINT(bugprone-reserved-identifier)
                    typename __KeyType,             // NOLINT(bugprone-reserved-identifier)
                    typename __KeyExtractor,        // NOLINT(bugprone-reserved-identifier)
                    typename __KeyEqualsComparator, // NOLINT(bugprone-reserved-identifier)
                    typename __KeyHasher,           // NOLINT(bugprone-reserved-identifier)
                    typename __RehashPolicy,        // NOLINT(bugprone-reserved-identifier)
                    typename __ElementTypeDestruct  // NOLINT(bugprone-reserved-identifier)
            >
            template < typename __EntryCopyFunction > // NOLINT(bugprone-reserved-identifier)
            __CDS_OptimalInline __HashTable <
                    __ElementType,
                    __KeyType,
                    __KeyExtractor,
                    __KeyEqualsComparator,
                    __KeyHasher,
                    __RehashPolicy,
                    __ElementTypeDestruct
            > :: __HashTable (
                    __HashTable         const & hashTable,
                    __EntryCopyFunction const & copyFunction
            ) noexcept :
                    __HashTableUtils < KeyHasher, RehashPolicy > ( hashTable ) {

                this->__ht_copyFrom (
                        hashTable,
                        copyFunction
                );
            }


            template <
                    typename __ElementType,         // NOLINT(bugprone-reserved-identifier)
                    typename __KeyType,             // NOLINT(bugprone-reserved-identifier)
                    typename __KeyExtractor,        // NOLINT(bugprone-reserved-identifier)
                    typename __KeyEqualsComparator, // NOLINT(bugprone-reserved-identifier)
                    typename __KeyHasher,           // NOLINT(bugprone-reserved-identifier)
                    typename __RehashPolicy,        // NOLINT(bugprone-reserved-identifier)
                    typename __ElementTypeDestruct  // NOLINT(bugprone-reserved-identifier)
            > constexpr __HashTable <
                    __ElementType,
                    __KeyType,
                    __KeyExtractor,
                    __KeyEqualsComparator,
                    __KeyHasher,
                    __RehashPolicy,
                    __ElementTypeDestruct
            > :: __HashTable (
                    __HashTable && hashTable
            ) noexcept :
                    __HashTableUtils < KeyHasher, RehashPolicy > ( hashTable ) {

                this->__ht_moveFrom ( std :: move ( hashTable ) );
            }


            template <
                    typename __ElementType,         // NOLINT(bugprone-reserved-identifier)
                    typename __KeyType,             // NOLINT(bugprone-reserved-identifier)
                    typename __KeyExtractor,        // NOLINT(bugprone-reserved-identifier)
                    typename __KeyEqualsComparator, // NOLINT(bugprone-reserved-identifier)
                    typename __KeyHasher,           // NOLINT(bugprone-reserved-identifier)
                    typename __RehashPolicy,        // NOLINT(bugprone-reserved-identifier)
                    typename __ElementTypeDestruct  // NOLINT(bugprone-reserved-identifier)
            > constexpr __HashTable <
                    __ElementType,
                    __KeyType,
                    __KeyExtractor,
                    __KeyEqualsComparator,
                    __KeyHasher,
                    __RehashPolicy,
                    __ElementTypeDestruct
            > :: __HashTable (
                    KeyHasher const & keyHasher
            ) noexcept :
                    __HashTableUtils < KeyHasher, RehashPolicy > ( keyHasher ) {

            }


            template <
                    typename __ElementType,         // NOLINT(bugprone-reserved-identifier)
                    typename __KeyType,             // NOLINT(bugprone-reserved-identifier)
                    typename __KeyExtractor,        // NOLINT(bugprone-reserved-identifier)
                    typename __KeyEqualsComparator, // NOLINT(bugprone-reserved-identifier)
                    typename __KeyHasher,           // NOLINT(bugprone-reserved-identifier)
                    typename __RehashPolicy,        // NOLINT(bugprone-reserved-identifier)
                    typename __ElementTypeDestruct  // NOLINT(bugprone-reserved-identifier)
            > __CDS_OptimalInline auto __HashTable <
                    __ElementType,
                    __KeyType,
                    __KeyExtractor,
                    __KeyEqualsComparator,
                    __KeyHasher,
                    __RehashPolicy,
                    __ElementTypeDestruct
            > :: __ht_allocateBuckets (
                    Size bucketCount
            ) noexcept -> void {

                this->_bucketArray._pArray = reinterpret_cast < __BucketType * > (
                        std :: memset (
                                cds :: __hidden :: __impl :: __allocation :: __reallocPrimitiveArray (
                                        this->_bucketArray._pArray,
                                        bucketCount
                                ) + this->_bucketArray._size,
                                0ULL,
                                sizeof ( __BucketType ) * ( bucketCount - this->_bucketArray._size ) // NOLINT(bugprone-sizeof-expression)
                        )
                ) - this->_bucketArray._size;

                this->_bucketArray._size = bucketCount;
            }


            template <
                    typename __ElementType,         // NOLINT(bugprone-reserved-identifier)
                    typename __KeyType,             // NOLINT(bugprone-reserved-identifier)
                    typename __KeyExtractor,        // NOLINT(bugprone-reserved-identifier)
                    typename __KeyEqualsComparator, // NOLINT(bugprone-reserved-identifier)
                    typename __KeyHasher,           // NOLINT(bugprone-reserved-identifier)
                    typename __RehashPolicy,        // NOLINT(bugprone-reserved-identifier)
                    typename __ElementTypeDestruct  // NOLINT(bugprone-reserved-identifier)
            > __CDS_OptimalInline auto __HashTable <
                    __ElementType,
                    __KeyType,
                    __KeyExtractor,
                    __KeyEqualsComparator,
                    __KeyHasher,
                    __RehashPolicy,
                    __ElementTypeDestruct
            > :: __ht_freeBuckets () noexcept -> void {

                cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray (
                        cds :: exchange (
                                this->_bucketArray._pArray,
                                nullptr
                        )
                );

                this->_bucketArray._size = 0ULL;
            }


            template <
                    typename __ElementType,         // NOLINT(bugprone-reserved-identifier)
                    typename __KeyType,             // NOLINT(bugprone-reserved-identifier)
                    typename __KeyExtractor,        // NOLINT(bugprone-reserved-identifier)
                    typename __KeyEqualsComparator, // NOLINT(bugprone-reserved-identifier)
                    typename __KeyHasher,           // NOLINT(bugprone-reserved-identifier)
                    typename __RehashPolicy,        // NOLINT(bugprone-reserved-identifier)
                    typename __ElementTypeDestruct  // NOLINT(bugprone-reserved-identifier)
            > __CDS_OptimalInline auto __HashTable <
                    __ElementType,
                    __KeyType,
                    __KeyExtractor,
                    __KeyEqualsComparator,
                    __KeyHasher,
                    __RehashPolicy,
                    __ElementTypeDestruct
            > :: __ht_allocateNode () const noexcept -> __DataNode * {

                return cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveObject < __DataNode > ();
            }


            template <
                    typename __ElementType,         // NOLINT(bugprone-reserved-identifier)
                    typename __KeyType,             // NOLINT(bugprone-reserved-identifier)
                    typename __KeyExtractor,        // NOLINT(bugprone-reserved-identifier)
                    typename __KeyEqualsComparator, // NOLINT(bugprone-reserved-identifier)
                    typename __KeyHasher,           // NOLINT(bugprone-reserved-identifier)
                    typename __RehashPolicy,        // NOLINT(bugprone-reserved-identifier)
                    typename __ElementTypeDestruct  // NOLINT(bugprone-reserved-identifier)
            > __CDS_OptimalInline auto __HashTable <
                    __ElementType,
                    __KeyType,
                    __KeyExtractor,
                    __KeyEqualsComparator,
                    __KeyHasher,
                    __RehashPolicy,
                    __ElementTypeDestruct
            > :: __ht_freeNode (
                    __DataNode * pNode
            ) const noexcept -> void {

                this->_destruct ( pNode->_data.data() );
                cds :: __hidden :: __impl :: __allocation :: __freePrimitiveObject ( pNode );
            }


            template <
                    typename __ElementType,         // NOLINT(bugprone-reserved-identifier)
                    typename __KeyType,             // NOLINT(bugprone-reserved-identifier)
                    typename __KeyExtractor,        // NOLINT(bugprone-reserved-identifier)
                    typename __KeyEqualsComparator, // NOLINT(bugprone-reserved-identifier)
                    typename __KeyHasher,           // NOLINT(bugprone-reserved-identifier)
                    typename __RehashPolicy,        // NOLINT(bugprone-reserved-identifier)
                    typename __ElementTypeDestruct  // NOLINT(bugprone-reserved-identifier)
            > __CDS_OptimalInline auto __HashTable <
                    __ElementType,
                    __KeyType,
                    __KeyExtractor,
                    __KeyEqualsComparator,
                    __KeyHasher,
                    __RehashPolicy,
                    __ElementTypeDestruct
            > :: __ht_bucket (
                    Size hash
            ) noexcept -> __BucketType & {

                return this->_bucketArray._pArray [ hash % this->_bucketArray._size ];
            }


            template <
                    typename __ElementType,         // NOLINT(bugprone-reserved-identifier)
                    typename __KeyType,             // NOLINT(bugprone-reserved-identifier)
                    typename __KeyExtractor,        // NOLINT(bugprone-reserved-identifier)
                    typename __KeyEqualsComparator, // NOLINT(bugprone-reserved-identifier)
                    typename __KeyHasher,           // NOLINT(bugprone-reserved-identifier)
                    typename __RehashPolicy,        // NOLINT(bugprone-reserved-identifier)
                    typename __ElementTypeDestruct  // NOLINT(bugprone-reserved-identifier)
            > __CDS_OptimalInline auto __HashTable <
                    __ElementType,
                    __KeyType,
                    __KeyExtractor,
                    __KeyEqualsComparator,
                    __KeyHasher,
                    __RehashPolicy,
                    __ElementTypeDestruct
            > :: __ht_bucket (
                    Size hash
            ) const noexcept -> __BucketType const & {

                return this->_bucketArray._pArray [ hash % this->_bucketArray._size ];
            }


            template <
                    typename __ElementType,         // NOLINT(bugprone-reserved-identifier)
                    typename __KeyType,             // NOLINT(bugprone-reserved-identifier)
                    typename __KeyExtractor,        // NOLINT(bugprone-reserved-identifier)
                    typename __KeyEqualsComparator, // NOLINT(bugprone-reserved-identifier)
                    typename __KeyHasher,           // NOLINT(bugprone-reserved-identifier)
                    typename __RehashPolicy,        // NOLINT(bugprone-reserved-identifier)
                    typename __ElementTypeDestruct  // NOLINT(bugprone-reserved-identifier)
            > auto __HashTable <
                    __ElementType,
                    __KeyType,
                    __KeyExtractor,
                    __KeyEqualsComparator,
                    __KeyHasher,
                    __RehashPolicy,
                    __ElementTypeDestruct
            > :: __ht_clear () noexcept -> void {

                if ( ! this->__ht_empty() ) {

                    for ( Size bucketIndex = 0ULL; bucketIndex < this->_bucketArray._size; ++ bucketIndex ) {

                        __BucketType & bucket = this->_bucketArray._pArray [ bucketIndex ];
                        while ( bucket != nullptr ) {

                            auto pCopy  = bucket;
                            bucket = bucket->_pNext;

                            this->__ht_freeNode ( pCopy );
                        }
                    }

                    this->_rehashPolicy.reset();
                    this->__ht_freeBuckets ();
                    this->_totalSize = 0ULL;
                }
            }


            template <
                    typename __ElementType,         // NOLINT(bugprone-reserved-identifier)
                    typename __KeyType,             // NOLINT(bugprone-reserved-identifier)
                    typename __KeyExtractor,        // NOLINT(bugprone-reserved-identifier)
                    typename __KeyEqualsComparator, // NOLINT(bugprone-reserved-identifier)
                    typename __KeyHasher,           // NOLINT(bugprone-reserved-identifier)
                    typename __RehashPolicy,        // NOLINT(bugprone-reserved-identifier)
                    typename __ElementTypeDestruct  // NOLINT(bugprone-reserved-identifier)
            > auto __HashTable <
                    __ElementType,
                    __KeyType,
                    __KeyExtractor,
                    __KeyEqualsComparator,
                    __KeyHasher,
                    __RehashPolicy,
                    __ElementTypeDestruct
            > :: __ht_get (
                    __KeyType    const & key,
                    bool               * pIsNew
            ) noexcept -> __ElementType * {

                if ( this->__ht_empty() ) {
                    this->__ht_allocateBuckets ( this->_rehashPolicy.currentFactor() );
                }

                auto hashValue                  = this->_hasher ( key );
                __BucketType & bucket           = this->__ht_bucket ( hashValue );
                __DataNode * pSeekAndNewNode    = bucket;
                Size bucketSize                 = 0ULL;

                while ( pSeekAndNewNode != nullptr ) {
                    if ( this->_equals ( this->_key ( pSeekAndNewNode->_data.data() ), key ) ) {
                        * pIsNew = false;
                        return & pSeekAndNewNode->_data.data();
                    }

                    pSeekAndNewNode = pSeekAndNewNode->_pNext;
                    ++ bucketSize;
                }

                pSeekAndNewNode         = this->__ht_allocateNode ();
                pSeekAndNewNode->_pNext = bucket;
                bucket                  = pSeekAndNewNode;

                ++ this->_totalSize;

                if ( bucketSize >= this->_rehashPolicy.loadFactor() ) {
                    auto rehashRequiredData = this->_rehashPolicy.rehashRequired (
                            this->_bucketArray._size,
                            this->_totalSize,
                            1ULL
                    );

                    if ( rehashRequiredData._required ) {
                        this->__ht_rehash (
                                rehashRequiredData._size,
                                hashValue,
                                pSeekAndNewNode
                        );
                    }
                }

                * pIsNew = true;
                return & pSeekAndNewNode->_data.data();
            }


            template <
                    typename __ElementType,         // NOLINT(bugprone-reserved-identifier)
                    typename __KeyType,             // NOLINT(bugprone-reserved-identifier)
                    typename __KeyExtractor,        // NOLINT(bugprone-reserved-identifier)
                    typename __KeyEqualsComparator, // NOLINT(bugprone-reserved-identifier)
                    typename __KeyHasher,           // NOLINT(bugprone-reserved-identifier)
                    typename __RehashPolicy,        // NOLINT(bugprone-reserved-identifier)
                    typename __ElementTypeDestruct  // NOLINT(bugprone-reserved-identifier)
            > auto __HashTable <
                    __ElementType,
                    __KeyType,
                    __KeyExtractor,
                    __KeyEqualsComparator,
                    __KeyHasher,
                    __RehashPolicy,
                    __ElementTypeDestruct
            > :: __ht_rehash (
                    Size                bucketCount,
                    Size                hashValueOfNewNode,
                    __DataNode  const * pNewEmptyNode
            ) noexcept -> void {

                Size            oldBucketSize = this->_bucketArray._size;
                Size            newHash;
                __DataNode    * pToMove;

                this->__ht_allocateBuckets ( bucketCount );

                for ( Size bucketIndex = 0ULL; bucketIndex < oldBucketSize; ++ bucketIndex ) {

                    /// guaranteed to be lower than newer size, so using the method
                    /// with the new greater modulus will not impact the result
                    auto & oldBucket = this->__ht_bucket ( bucketIndex );

                    while ( oldBucket != nullptr ) {

                        if ( pNewEmptyNode == oldBucket ) {
                            newHash = hashValueOfNewNode;
                        } else {
                            newHash = this->_hasher ( this->_key ( oldBucket->_data.data() ) );
                        }

                        auto & newBucket = this->__ht_bucket ( newHash );
                        if ( newBucket == oldBucket ) {
                            break;
                        }

                        pToMove     = oldBucket;
                        oldBucket   = oldBucket->_pNext;

                        __HashTable :: __ht_rehashEmplace ( & newBucket, pToMove );
                    }

                    __DataNode * pOldBucketHead = oldBucket;
                    while ( pOldBucketHead != nullptr && pOldBucketHead->_pNext != nullptr ) {


                        if ( pNewEmptyNode == pOldBucketHead->_pNext ) {
                            newHash = hashValueOfNewNode;
                        } else {
                            newHash = this->_hasher ( this->_key ( pOldBucketHead->_pNext->_data.data() ) );
                        }

                        auto & newBucket = this->__ht_bucket ( newHash );

                        if ( newBucket == oldBucket ) {
                            pOldBucketHead = pOldBucketHead->_pNext;
                            continue;
                        }

                        pToMove                 = pOldBucketHead->_pNext;
                        pOldBucketHead->_pNext  = pOldBucketHead->_pNext->_pNext;

                        __HashTable :: __ht_rehashEmplace ( & newBucket, pToMove );
                    }
                }
            }


            template <
                    typename __ElementType,         // NOLINT(bugprone-reserved-identifier)
                    typename __KeyType,             // NOLINT(bugprone-reserved-identifier)
                    typename __KeyExtractor,        // NOLINT(bugprone-reserved-identifier)
                    typename __KeyEqualsComparator, // NOLINT(bugprone-reserved-identifier)
                    typename __KeyHasher,           // NOLINT(bugprone-reserved-identifier)
                    typename __RehashPolicy,        // NOLINT(bugprone-reserved-identifier)
                    typename __ElementTypeDestruct  // NOLINT(bugprone-reserved-identifier)
            > __CDS_OptimalInline auto __HashTable <
                    __ElementType,
                    __KeyType,
                    __KeyExtractor,
                    __KeyEqualsComparator,
                    __KeyHasher,
                    __RehashPolicy,
                    __ElementTypeDestruct
            > :: __ht_rehashEmplace (
                    __BucketType * pBucket,
                    __DataNode   * pNode
            ) noexcept -> void {

                pNode->_pNext   = * pBucket;
                * pBucket       = pNode;
            }


            template <
                    typename __ElementType,         // NOLINT(bugprone-reserved-identifier)
                    typename __KeyType,             // NOLINT(bugprone-reserved-identifier)
                    typename __KeyExtractor,        // NOLINT(bugprone-reserved-identifier)
                    typename __KeyEqualsComparator, // NOLINT(bugprone-reserved-identifier)
                    typename __KeyHasher,           // NOLINT(bugprone-reserved-identifier)
                    typename __RehashPolicy,        // NOLINT(bugprone-reserved-identifier)
                    typename __ElementTypeDestruct  // NOLINT(bugprone-reserved-identifier)
            > constexpr auto __HashTable <
                    __ElementType,
                    __KeyType,
                    __KeyExtractor,
                    __KeyEqualsComparator,
                    __KeyHasher,
                    __RehashPolicy,
                    __ElementTypeDestruct
            > :: __ht_empty () const noexcept -> bool {

                return this->_bucketArray._pArray == nullptr;
            }


            template <
                    typename __ElementType,         // NOLINT(bugprone-reserved-identifier)
                    typename __KeyType,             // NOLINT(bugprone-reserved-identifier)
                    typename __KeyExtractor,        // NOLINT(bugprone-reserved-identifier)
                    typename __KeyEqualsComparator, // NOLINT(bugprone-reserved-identifier)
                    typename __KeyHasher,           // NOLINT(bugprone-reserved-identifier)
                    typename __RehashPolicy,        // NOLINT(bugprone-reserved-identifier)
                    typename __ElementTypeDestruct  // NOLINT(bugprone-reserved-identifier)
            > constexpr auto __HashTable <
                    __ElementType,
                    __KeyType,
                    __KeyExtractor,
                    __KeyEqualsComparator,
                    __KeyHasher,
                    __RehashPolicy,
                    __ElementTypeDestruct
            > :: __ht_size () const noexcept -> Size {

                return this->_totalSize;
            }


            template <
                    typename __ElementType,         // NOLINT(bugprone-reserved-identifier)
                    typename __KeyType,             // NOLINT(bugprone-reserved-identifier)
                    typename __KeyExtractor,        // NOLINT(bugprone-reserved-identifier)
                    typename __KeyEqualsComparator, // NOLINT(bugprone-reserved-identifier)
                    typename __KeyHasher,           // NOLINT(bugprone-reserved-identifier)
                    typename __RehashPolicy,        // NOLINT(bugprone-reserved-identifier)
                    typename __ElementTypeDestruct  // NOLINT(bugprone-reserved-identifier)
            > constexpr auto __HashTable <
                    __ElementType,
                    __KeyType,
                    __KeyExtractor,
                    __KeyEqualsComparator,
                    __KeyHasher,
                    __RehashPolicy,
                    __ElementTypeDestruct
            > :: __ht_bucketCount () const noexcept -> Size {

                return this->_bucketArray._size;
            }


            template <
                    typename __ElementType,         // NOLINT(bugprone-reserved-identifier)
                    typename __KeyType,             // NOLINT(bugprone-reserved-identifier)
                    typename __KeyExtractor,        // NOLINT(bugprone-reserved-identifier)
                    typename __KeyEqualsComparator, // NOLINT(bugprone-reserved-identifier)
                    typename __KeyHasher,           // NOLINT(bugprone-reserved-identifier)
                    typename __RehashPolicy,        // NOLINT(bugprone-reserved-identifier)
                    typename __ElementTypeDestruct  // NOLINT(bugprone-reserved-identifier)
            > auto __HashTable <
                    __ElementType,
                    __KeyType,
                    __KeyExtractor,
                    __KeyEqualsComparator,
                    __KeyHasher,
                    __RehashPolicy,
                    __ElementTypeDestruct
            > :: __ht_get (
                    __KeyType const & key
            ) const noexcept -> __ElementType const * {

                if ( this->__ht_empty() ) {
                    return nullptr;
                }

                auto pBucketHead = this->__ht_bucket ( this->_hasher ( key ) );
                while ( pBucketHead != nullptr ) {

                    if ( this->_equals ( this->_key ( pBucketHead->_data.data() ), key ) ) {
                        return & pBucketHead->_data.data();
                    }

                    pBucketHead = pBucketHead->_pNext;
                }

                return nullptr;
            }


            template <
                    typename __ElementType,         // NOLINT(bugprone-reserved-identifier)
                    typename __KeyType,             // NOLINT(bugprone-reserved-identifier)
                    typename __KeyExtractor,        // NOLINT(bugprone-reserved-identifier)
                    typename __KeyEqualsComparator, // NOLINT(bugprone-reserved-identifier)
                    typename __KeyHasher,           // NOLINT(bugprone-reserved-identifier)
                    typename __RehashPolicy,        // NOLINT(bugprone-reserved-identifier)
                    typename __ElementTypeDestruct  // NOLINT(bugprone-reserved-identifier)
            > __CDS_OptimalInline auto __HashTable <
                    __ElementType,
                    __KeyType,
                    __KeyExtractor,
                    __KeyEqualsComparator,
                    __KeyHasher,
                    __RehashPolicy,
                    __ElementTypeDestruct
            > :: __ht_at (
                    __KeyType const & key
            ) const noexcept -> __ElementType const * {

                return this->__ht_get ( key );
            }


            template <
                    typename __ElementType,         // NOLINT(bugprone-reserved-identifier)
                    typename __KeyType,             // NOLINT(bugprone-reserved-identifier)
                    typename __KeyExtractor,        // NOLINT(bugprone-reserved-identifier)
                    typename __KeyEqualsComparator, // NOLINT(bugprone-reserved-identifier)
                    typename __KeyHasher,           // NOLINT(bugprone-reserved-identifier)
                    typename __RehashPolicy,        // NOLINT(bugprone-reserved-identifier)
                    typename __ElementTypeDestruct  // NOLINT(bugprone-reserved-identifier)
            > __CDS_OptimalInline auto __HashTable <
                    __ElementType,
                    __KeyType,
                    __KeyExtractor,
                    __KeyEqualsComparator,
                    __KeyHasher,
                    __RehashPolicy,
                    __ElementTypeDestruct
            > :: __ht_at (
                    __KeyType const & key
            ) noexcept -> __ElementType * {

                return const_cast < __ElementType * > ( const_cast < __HashTable const * > ( this )->__ht_get ( key ) );
            }


            template <
                    typename __ElementType,         // NOLINT(bugprone-reserved-identifier)
                    typename __KeyType,             // NOLINT(bugprone-reserved-identifier)
                    typename __KeyExtractor,        // NOLINT(bugprone-reserved-identifier)
                    typename __KeyEqualsComparator, // NOLINT(bugprone-reserved-identifier)
                    typename __KeyHasher,           // NOLINT(bugprone-reserved-identifier)
                    typename __RehashPolicy,        // NOLINT(bugprone-reserved-identifier)
                    typename __ElementTypeDestruct  // NOLINT(bugprone-reserved-identifier)
            > auto __HashTable <
                    __ElementType,
                    __KeyType,
                    __KeyExtractor,
                    __KeyEqualsComparator,
                    __KeyHasher,
                    __RehashPolicy,
                    __ElementTypeDestruct
            > :: __ht_remove (
                    __KeyType const & key
            ) noexcept -> bool {

                if ( this->__ht_empty() ) {
                    return false;
                }

                __DataNode * pToRemove;
                __DataNode * pBucketHead;

                auto & bucket = this->__ht_bucket ( this->_hasher ( key ) );
                if ( this->_equals ( this->_key ( bucket->_data.data() ), key ) ) {

                    pToRemove   = bucket;
                    bucket      = bucket->_pNext;

                    this->__ht_freeNode ( pToRemove );

                    -- this->_totalSize;
                    return true;
                }

                pBucketHead = bucket;
                while ( pBucketHead->_pNext != nullptr ) {

                    if ( this->_equals ( this->_key ( pBucketHead->_pNext->_data.data() ), key ) ) {

                        pToRemove           = pBucketHead->_pNext;
                        pBucketHead->_pNext = pBucketHead->_pNext->_pNext;

                        this->__ht_freeNode ( pToRemove );

                        -- this->_totalSize;
                        return true;
                    }

                    pBucketHead = pBucketHead->_pNext;
                }

                return false;
            }


            template <
                    typename __ElementType,         // NOLINT(bugprone-reserved-identifier)
                    typename __KeyType,             // NOLINT(bugprone-reserved-identifier)
                    typename __KeyExtractor,        // NOLINT(bugprone-reserved-identifier)
                    typename __KeyEqualsComparator, // NOLINT(bugprone-reserved-identifier)
                    typename __KeyHasher,           // NOLINT(bugprone-reserved-identifier)
                    typename __RehashPolicy,        // NOLINT(bugprone-reserved-identifier)
                    typename __ElementTypeDestruct  // NOLINT(bugprone-reserved-identifier)
            > auto __HashTable <
                    __ElementType,
                    __KeyType,
                    __KeyExtractor,
                    __KeyEqualsComparator,
                    __KeyHasher,
                    __RehashPolicy,
                    __ElementTypeDestruct
            > :: __ht_remove (
                    __DataNode  const * pNode,
                    Size                bucketIndex
            ) noexcept -> bool {

                if ( bucketIndex >= this->_bucketArray._size || pNode == nullptr ) {
                    return false;
                }

                auto & bucket = this->_bucketArray._pArray [ bucketIndex ];
                if ( bucket == nullptr ) {
                    return false;
                }

                if ( bucket == pNode ) {
                    __DataNode * pCopy  = bucket;
                    bucket              = bucket->_pNext;

                    this->__ht_freeNode ( pCopy );
                    -- this->_totalSize;
                    return true;
                }

                __DataNode * pHead = bucket;
                while ( pHead->_pNext != nullptr ) {
                    if ( pNode == pHead->_pNext ) {

                        auto pToRemove  = pHead->_pNext;
                        pHead->_pNext   = pHead->_pNext->_pNext;

                        this->__ht_freeNode ( pToRemove );
                        -- this->_totalSize;
                        return true;
                    }

                    pHead = pHead->_pNext;
                }

                return false;
            }


            template <
                    typename __ElementType,         // NOLINT(bugprone-reserved-identifier)
                    typename __KeyType,             // NOLINT(bugprone-reserved-identifier)
                    typename __KeyExtractor,        // NOLINT(bugprone-reserved-identifier)
                    typename __KeyEqualsComparator, // NOLINT(bugprone-reserved-identifier)
                    typename __KeyHasher,           // NOLINT(bugprone-reserved-identifier)
                    typename __RehashPolicy,        // NOLINT(bugprone-reserved-identifier)
                    typename __ElementTypeDestruct  // NOLINT(bugprone-reserved-identifier)
            > __CDS_OptimalInline auto __HashTable <
                    __ElementType,
                    __KeyType,
                    __KeyExtractor,
                    __KeyEqualsComparator,
                    __KeyHasher,
                    __RehashPolicy,
                    __ElementTypeDestruct
            > :: __ht_remove (
                    HashTableIterator const & iterator
            ) noexcept -> bool {

                return this->__ht_remove (
                        iterator.currentNode(),
                        iterator.bucketIndex()
                );
            }


            template <
                    typename __ElementType,         // NOLINT(bugprone-reserved-identifier)
                    typename __KeyType,             // NOLINT(bugprone-reserved-identifier)
                    typename __KeyExtractor,        // NOLINT(bugprone-reserved-identifier)
                    typename __KeyEqualsComparator, // NOLINT(bugprone-reserved-identifier)
                    typename __KeyHasher,           // NOLINT(bugprone-reserved-identifier)
                    typename __RehashPolicy,        // NOLINT(bugprone-reserved-identifier)
                    typename __ElementTypeDestruct  // NOLINT(bugprone-reserved-identifier)
            > __CDS_OptimalInline auto __HashTable <
                    __ElementType,
                    __KeyType,
                    __KeyExtractor,
                    __KeyEqualsComparator,
                    __KeyHasher,
                    __RehashPolicy,
                    __ElementTypeDestruct
            > :: __ht_remove (
                    HashTableConstIterator const & iterator
            ) noexcept -> bool {

                return this->__ht_remove (
                        iterator.currentNode(),
                        iterator.bucketIndex()
                );
            }


            template <
                    typename __ElementType,         // NOLINT(bugprone-reserved-identifier)
                    typename __KeyType,             // NOLINT(bugprone-reserved-identifier)
                    typename __KeyExtractor,        // NOLINT(bugprone-reserved-identifier)
                    typename __KeyEqualsComparator, // NOLINT(bugprone-reserved-identifier)
                    typename __KeyHasher,           // NOLINT(bugprone-reserved-identifier)
                    typename __RehashPolicy,        // NOLINT(bugprone-reserved-identifier)
                    typename __ElementTypeDestruct  // NOLINT(bugprone-reserved-identifier)
            > template < typename __EntryCompareFunction > // NOLINT(bugprone-reserved-identifier)
            auto __HashTable <
                    __ElementType,
                    __KeyType,
                    __KeyExtractor,
                    __KeyEqualsComparator,
                    __KeyHasher,
                    __RehashPolicy,
                    __ElementTypeDestruct
            > :: __ht_equals (
                    __HashTable             const & table,
                    __EntryCompareFunction  const & entryCompareFunction
            ) const noexcept -> bool {

                if ( this == & table ) {
                    return true;
                }

                if ( this->__ht_empty() ) {
                    return table.__ht_empty();
                }

                if ( table.__ht_empty() || this->__ht_bucketCount () != table.__ht_bucketCount () ) {
                    return false;
                }

                for ( Size bucketIndex = 0ULL; bucketIndex < this->__ht_bucketCount(); ++ bucketIndex ) {

                    auto pThisBucketHead    = this->_bucketArray._pArray [ bucketIndex ];
                    auto pOtherBucketHead   = table._bucketArray._pArray [ bucketIndex ];

                    while ( pThisBucketHead != nullptr && pOtherBucketHead != nullptr ) {
                        if ( ! entryCompareFunction ( pThisBucketHead->_data.data(), pOtherBucketHead->_data.data() ) ) {
                            return false;
                        }
                    }

                    if ( pThisBucketHead != nullptr || pOtherBucketHead != nullptr ) {
                        return false;
                    }
                }

                return true;
            }


            template <
                    typename __ElementType,         // NOLINT(bugprone-reserved-identifier)
                    typename __KeyType,             // NOLINT(bugprone-reserved-identifier)
                    typename __KeyExtractor,        // NOLINT(bugprone-reserved-identifier)
                    typename __KeyEqualsComparator, // NOLINT(bugprone-reserved-identifier)
                    typename __KeyHasher,           // NOLINT(bugprone-reserved-identifier)
                    typename __RehashPolicy,        // NOLINT(bugprone-reserved-identifier)
                    typename __ElementTypeDestruct  // NOLINT(bugprone-reserved-identifier)
            > template < typename __EntryCopyFunction > // NOLINT(bugprone-reserved-identifier)
            auto __HashTable <
                    __ElementType,
                    __KeyType,
                    __KeyExtractor,
                    __KeyEqualsComparator,
                    __KeyHasher,
                    __RehashPolicy,
                    __ElementTypeDestruct
            > :: __ht_copyFrom (
                    __HashTable         const & table,
                    __EntryCopyFunction const & entryCopyFunction
            ) noexcept -> void {

                if ( table.__ht_empty() ) {
                    return;
                }

                this->_totalSize = table._totalSize;
                this->__ht_allocateBuckets ( table.__ht_bucketCount() );
                for ( Size bucketIndex = 0ULL; bucketIndex < table.__ht_bucketCount(); ++ bucketIndex ) {

                    auto & thisBucket   = this->__ht_bucket ( bucketIndex );
                    auto & tableBucket  = table.__ht_bucket ( bucketIndex );

                    __DataNode * pTableHead     = tableBucket;
                    __DataNode * pThisBack      = nullptr;

                    while ( pTableHead != nullptr ) {

                        auto pNewNode       = this->__ht_allocateNode ();
                        pNewNode->_pNext    = nullptr;
                        entryCopyFunction ( pNewNode->_data.data(), pTableHead->_data.data() );

                        pTableHead = pTableHead->_pNext;

                        if ( pThisBack == nullptr ) {
                            thisBucket          = pNewNode;
                        } else {
                            pThisBack->_pNext   = pNewNode;
                        }

                        pThisBack = pNewNode;
                    }
                }
            }


            template <
                    typename __ElementType,         // NOLINT(bugprone-reserved-identifier)
                    typename __KeyType,             // NOLINT(bugprone-reserved-identifier)
                    typename __KeyExtractor,        // NOLINT(bugprone-reserved-identifier)
                    typename __KeyEqualsComparator, // NOLINT(bugprone-reserved-identifier)
                    typename __KeyHasher,           // NOLINT(bugprone-reserved-identifier)
                    typename __RehashPolicy,        // NOLINT(bugprone-reserved-identifier)
                    typename __ElementTypeDestruct  // NOLINT(bugprone-reserved-identifier)
            > constexpr auto __HashTable <
                    __ElementType,
                    __KeyType,
                    __KeyExtractor,
                    __KeyEqualsComparator,
                    __KeyHasher,
                    __RehashPolicy,
                    __ElementTypeDestruct
            > :: __ht_moveFrom (
                    __HashTable && table
            ) noexcept -> void {

                this->_totalSize    = cds :: exchange ( table._totalSize, 0ULL );
                this->_bucketArray  = {
                        cds :: exchange ( table._bucketArray._pArray, nullptr ),
                        cds :: exchange ( table._bucketArray._size, 0ULL )
                };
            }


            template <
                    typename __ElementType,         // NOLINT(bugprone-reserved-identifier)
                    typename __KeyType,             // NOLINT(bugprone-reserved-identifier)
                    typename __KeyExtractor,        // NOLINT(bugprone-reserved-identifier)
                    typename __KeyEqualsComparator, // NOLINT(bugprone-reserved-identifier)
                    typename __KeyHasher,           // NOLINT(bugprone-reserved-identifier)
                    typename __RehashPolicy,        // NOLINT(bugprone-reserved-identifier)
                    typename __ElementTypeDestruct  // NOLINT(bugprone-reserved-identifier)
            > template < typename __EntryCopyFunction > // NOLINT(bugprone-reserved-identifier)
            __CDS_OptimalInline auto __HashTable <
                    __ElementType,
                    __KeyType,
                    __KeyExtractor,
                    __KeyEqualsComparator,
                    __KeyHasher,
                    __RehashPolicy,
                    __ElementTypeDestruct
            > :: __ht_assign (
                    __HashTable         const & table,
                    __EntryCopyFunction const & entryCopyFunction
            ) noexcept -> void {

                if ( this == & table ) {
                    return;
                }

                this->__ht_clear();
                this->__ht_copyFrom (
                        table,
                        entryCopyFunction
                );
            }


            template <
                    typename __ElementType,         // NOLINT(bugprone-reserved-identifier)
                    typename __KeyType,             // NOLINT(bugprone-reserved-identifier)
                    typename __KeyExtractor,        // NOLINT(bugprone-reserved-identifier)
                    typename __KeyEqualsComparator, // NOLINT(bugprone-reserved-identifier)
                    typename __KeyHasher,           // NOLINT(bugprone-reserved-identifier)
                    typename __RehashPolicy,        // NOLINT(bugprone-reserved-identifier)
                    typename __ElementTypeDestruct  // NOLINT(bugprone-reserved-identifier)
            > __CDS_OptimalInline auto __HashTable <
                    __ElementType,
                    __KeyType,
                    __KeyExtractor,
                    __KeyEqualsComparator,
                    __KeyHasher,
                    __RehashPolicy,
                    __ElementTypeDestruct
            > :: __ht_assign (
                    __HashTable && table
            ) noexcept -> void {

                if ( this == & table ) {
                    return;
                }

                this->__ht_clear();
                this->__ht_moveFrom ( std :: move ( table ) );
            }

        }
    }
}

#endif // __CDS_HASH_TABLE_IMPL_HPP__
