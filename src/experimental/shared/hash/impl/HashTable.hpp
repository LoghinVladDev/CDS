//
// Created by loghin on 6/21/22.
//

#ifndef __CDS_EX_HASH_TABLE_IMPL_HPP__
#define __CDS_EX_HASH_TABLE_IMPL_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
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
                __HashTable <
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
                        _totalSize ( hashTable._totalSize ),
                        __HashTableUtils < KeyHasher, RehashPolicy > ( hashTable ) {

                    if ( hashTable.__empty() ) {
                        return;
                    }

                    this->__allocateBuckets ( hashTable.__bucketCount() );
                    for ( Size bucketIndex = 0ULL; bucketIndex < hashTable.__bucketCount(); ++ bucketIndex ) {

                        auto & thisBucket   = this->__bucket ( bucketIndex );
                        auto & tableBucket  = hashTable.__bucket ( bucketIndex );

                        __DataNode * pTableHead     = tableBucket;
                        __DataNode * pThisBack      = nullptr;

                        while ( pTableHead != nullptr ) {

                            auto pNewNode       = this->__allocateNode ();
                            pNewNode->_pNext    = nullptr;
                            copyFunction ( pNewNode->_data.data(), pTableHead->_data.data() );

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
                        __HashTableUtils < KeyHasher, RehashPolicy > ( hashTable ),
                        _totalSize ( cds :: exchange ( hashTable._totalSize, 0ULL ) ),
                        _bucketArray ( {
                            cds :: exchange ( hashTable._bucketArray._pArray, nullptr ),
                            cds :: exchange ( hashTable._bucketArray._size, 0ULL )
                        } ) {

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
                > :: __allocateBuckets (
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
                > :: __freeBuckets () noexcept -> void {

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
                > :: __allocateNode () const noexcept -> __DataNode * {

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
                > :: __freeNode (
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
                > :: __bucket (
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
                > :: __bucket (
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
                > :: __clear () noexcept -> void {

                    if ( ! this->__empty() ) {

                        for ( Size bucketIndex = 0ULL; bucketIndex < this->_bucketArray._size; ++ bucketIndex ) {

                            __BucketType & bucket = this->_bucketArray._pArray [ bucketIndex ];
                            while ( bucket != nullptr ) {

                                auto pCopy  = bucket;
                                bucket = bucket->_pNext;

                                this->__freeNode ( pCopy );
                            }
                        }

                        this->_rehashPolicy.reset();
                        this->__freeBuckets ();
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
                > :: __get (
                        __KeyType    const & key,
                        bool               * pIsNew
                ) noexcept -> __ElementType * {

                    if ( this->__empty() ) {
                        this->__allocateBuckets ( this->_rehashPolicy.currentFactor() );
                    }

                    auto hashValue                  = this->_hasher ( key );
                    __BucketType & bucket           = this->__bucket ( hashValue );
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

                    pSeekAndNewNode         = this->__allocateNode ();
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
                            this->__rehash (
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
                > :: __rehash (
                        Size                bucketCount,
                        Size                hashValueOfNewNode,
                        __DataNode  const * pNewEmptyNode
                ) noexcept -> void {

                    Size            oldBucketSize = this->_bucketArray._size;
                    Size            newHash;
                    __DataNode    * pToMove;

                    this->__allocateBuckets ( bucketCount );

                    for ( Size bucketIndex = 0ULL; bucketIndex < oldBucketSize; ++ bucketIndex ) {

                        /// guaranteed to be lower than newer size, so using the method
                        /// with the new greater modulus will not impact the result
                        auto & oldBucket = this->__bucket ( bucketIndex );

                        while ( oldBucket != nullptr ) {

                            if ( pNewEmptyNode == oldBucket ) {
                                newHash = hashValueOfNewNode;
                            } else {
                                newHash = this->_hasher ( this->_key ( oldBucket->_data.data() ) );
                            }

                            auto & newBucket = this->__bucket ( newHash );
                            if ( newBucket == oldBucket ) {
                                break;
                            }

                            pToMove     = oldBucket;
                            oldBucket   = oldBucket->_pNext;

                            __HashTable :: __rehashEmplace ( & newBucket, pToMove );
                        }

                        __DataNode * pOldBucketHead = oldBucket;
                        while ( pOldBucketHead != nullptr && pOldBucketHead->_pNext != nullptr ) {


                            if ( pNewEmptyNode == pOldBucketHead->_pNext ) {
                                newHash = hashValueOfNewNode;
                            } else {
                                newHash = this->_hasher ( this->_key ( pOldBucketHead->_pNext->_data.data() ) );
                            }

                            auto & newBucket = this->__bucket ( newHash );

                            if ( newBucket == oldBucket ) {
                                pOldBucketHead = pOldBucketHead->_pNext;
                                continue;
                            }

                            pToMove                 = pOldBucketHead->_pNext;
                            pOldBucketHead->_pNext  = pOldBucketHead->_pNext->_pNext;

                            __HashTable :: __rehashEmplace ( & newBucket, pToMove );
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
                > :: __rehashEmplace (
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
                > :: __empty () const noexcept -> bool {

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
                > :: __size () const noexcept -> Size {

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
                > :: __bucketCount () const noexcept -> Size {

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
                > :: __get (
                        __KeyType const & key
                ) const noexcept -> __ElementType const * {

                    if ( this->__empty() ) {
                        return nullptr;
                    }

                    auto pBucketHead = this->__bucket ( this->_hasher ( key ) );
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
                > auto __HashTable <
                        __ElementType,
                        __KeyType,
                        __KeyExtractor,
                        __KeyEqualsComparator,
                        __KeyHasher,
                        __RehashPolicy,
                        __ElementTypeDestruct
                > :: __at (
                        __KeyType const & key
                ) const noexcept -> __ElementType const * {

                    return this->__get ( key );
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
                > :: __at (
                        __KeyType const & key
                ) noexcept -> __ElementType * {

                    return const_cast < __ElementType * > ( const_cast < __HashTable const * > ( this )->__get ( key ) );
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
                > :: __remove (
                        __KeyType const & key
                ) noexcept -> bool {

                    if ( this->__empty() ) {
                        return false;
                    }

                    __DataNode * pToRemove;
                    __DataNode * pBucketHead;

                    auto & bucket = this->__bucket ( this->_hasher ( key ) );

                    if ( this->_equals ( this->_key ( bucket->_data.data() ), key ) ) {

                        pToRemove   = bucket;
                        bucket      = bucket->_pNext;

                        this->__freeNode ( pBucketHead );

                        -- this->_totalSize;
                        return true;
                    }

                    pBucketHead = bucket;
                    while ( pBucketHead->_pNext != nullptr ) {

                        if ( this->_equals ( this->_key ( pBucketHead->_pNext->_data.data() ), key ) ) {

                            pToRemove           = pBucketHead->_pNext;
                            pBucketHead->_pNext = pBucketHead->_pNext->_pNext;

                            this->__freeNode ( pBucketHead );

                            -- this->_totalSize;
                            return true;
                        }

                        pBucketHead = pBucketHead->_pNext;
                    }

                    return false;
                }

            }
        }
    }
}

#endif // __CDS_EX_HASH_TABLE_IMPL_HPP__
