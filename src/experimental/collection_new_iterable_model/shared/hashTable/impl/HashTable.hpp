//
// Created by loghin on 27/07/22.
//

#ifndef __CDS_SHARED_HASH_TABLE_IMPL_HPP__
#define __CDS_SHARED_HASH_TABLE_IMPL_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyComparator,    // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    // NOLINT(bugprone-reserved-identifier)
                > constexpr __HashTable <
                        __ElementType,
                        __KeyType,
                        __KeyHasher,
                        __RehashPolicy,
                        __keyExtractor,
                        __keyComparator,
                        __nodeDestructor
                > :: __HashTable () noexcept = default;


                template <
                        typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyComparator,    // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    // NOLINT(bugprone-reserved-identifier)
                > constexpr __HashTable <
                        __ElementType,
                        __KeyType,
                        __KeyHasher,
                        __RehashPolicy,
                        __keyExtractor,
                        __keyComparator,
                        __nodeDestructor
                > :: __HashTable (
                        __KeyHasher const & keyHasher
                ) noexcept :
                        _hasher ( keyHasher ) {

                }


                template <
                        typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyComparator,    // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    // NOLINT(bugprone-reserved-identifier)
                > constexpr __HashTable <
                        __ElementType,
                        __KeyType,
                        __KeyHasher,
                        __RehashPolicy,
                        __keyExtractor,
                        __keyComparator,
                        __nodeDestructor
                > :: __HashTable (
                        __RehashPolicy const & rehashPolicy
                ) noexcept :
                        _rehash ( rehashPolicy ) {

                }


                template <
                        typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyComparator,    // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    // NOLINT(bugprone-reserved-identifier)
                > constexpr __HashTable <
                        __ElementType,
                        __KeyType,
                        __KeyHasher,
                        __RehashPolicy,
                        __keyExtractor,
                        __keyComparator,
                        __nodeDestructor
                > :: __HashTable (
                        __KeyHasher     const & keyHasher,
                        __RehashPolicy  const & rehashPolicy
                ) noexcept :
                        _hasher ( keyHasher ),
                        _rehash ( rehashPolicy ) {

                }


                template <
                        typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyComparator,    // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    // NOLINT(bugprone-reserved-identifier)
                > template <
                        cds :: utility :: CopyConstructorFunction < __ElementType > __copy                      // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline __HashTable <
                        __ElementType,
                        __KeyType,
                        __KeyHasher,
                        __RehashPolicy,
                        __keyExtractor,
                        __keyComparator,
                        __nodeDestructor
                > :: __HashTable (
                        __HashTable const & hashTable
                ) noexcept :
                        _rehash ( hashTable._rehash ) {

                    this->__ht_copyCleared < __copy > ( hashTable );
                }


                template <
                        typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyComparator,    // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    // NOLINT(bugprone-reserved-identifier)
                > constexpr __HashTable <
                        __ElementType,
                        __KeyType,
                        __KeyHasher,
                        __RehashPolicy,
                        __keyExtractor,
                        __keyComparator,
                        __nodeDestructor
                > :: __HashTable (
                        __HashTable && hashTable
                ) noexcept :
                        _rehash ( std :: move ( hashTable._rehash ) ) {

                    this->__ht_moveCleared ( std :: move ( hashTable ) );
                }


                template <
                        typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyComparator,    // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    // NOLINT(bugprone-reserved-identifier)
                > auto __HashTable <
                        __ElementType,
                        __KeyType,
                        __KeyHasher,
                        __RehashPolicy,
                        __keyExtractor,
                        __keyComparator,
                        __nodeDestructor
                > :: __ht_clear () noexcept -> void {

                    if ( ! this->__ht_empty () ) {

                        for ( Size bucketIndex = 0ULL; bucketIndex < this->_bucketCount; ++ bucketIndex ) {

                            __NodeType * & bucket = this->_pBucketArray [ bucketIndex ];
                            while ( bucket != nullptr ) {

                                auto pCopy = bucket;
                                bucket = bucket->_pNext;
                                this->__ht_freeNode ( pCopy );
                            }
                        }

                        this->_rehash.reset ();
                        this->__ht_freeBuckets ();
                        this->_size = 0ULL;
                    }
                }


                template <
                        typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyComparator,    // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __HashTable <
                        __ElementType,
                        __KeyType,
                        __KeyHasher,
                        __RehashPolicy,
                        __keyExtractor,
                        __keyComparator,
                        __nodeDestructor
                > :: __ht_size () const noexcept -> Size {

                    return this->_size;
                }


                template <
                        typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyComparator,    // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __HashTable <
                        __ElementType,
                        __KeyType,
                        __KeyHasher,
                        __RehashPolicy,
                        __keyExtractor,
                        __keyComparator,
                        __nodeDestructor
                > :: __ht_empty () const noexcept -> bool {

                    return this->_pBucketArray == nullptr;
                }


                template <
                        typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyComparator,    // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __HashTable <
                        __ElementType,
                        __KeyType,
                        __KeyHasher,
                        __RehashPolicy,
                        __keyExtractor,
                        __keyComparator,
                        __nodeDestructor
                > :: __ht_bucketCount () const noexcept -> Size {

                    return this->_bucketCount;
                }


                template <
                        typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyComparator,    // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    // NOLINT(bugprone-reserved-identifier)
                > __CDS_cpplang_NonConstConstexprMemberFunction auto __HashTable <
                        __ElementType,
                        __KeyType,
                        __KeyHasher,
                        __RehashPolicy,
                        __keyExtractor,
                        __keyComparator,
                        __nodeDestructor
                > :: __ht_begin () noexcept -> __ht_Iterator {

                    return __ht_Iterator (
                            this->_pBucketArray,
                            this->_bucketCount
                    );
                }


                template <
                        typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyComparator,    // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    // NOLINT(bugprone-reserved-identifier)
                > __CDS_cpplang_NonConstConstexprMemberFunction auto __HashTable <
                        __ElementType,
                        __KeyType,
                        __KeyHasher,
                        __RehashPolicy,
                        __keyExtractor,
                        __keyComparator,
                        __nodeDestructor
                > :: __ht_end () noexcept -> __ht_Iterator {

                    return __ht_Iterator (
                            nullptr,
                            0ULL
                    );
                }


                template <
                        typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyComparator,    // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __HashTable <
                        __ElementType,
                        __KeyType,
                        __KeyHasher,
                        __RehashPolicy,
                        __keyExtractor,
                        __keyComparator,
                        __nodeDestructor
                > :: __ht_cbegin () const noexcept -> __ht_ConstIterator {

                    return __ht_ConstIterator (
                            this->_pBucketArray,
                            this->_bucketCount
                    );
                }


                template <
                        typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyComparator,    // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __HashTable <
                        __ElementType,
                        __KeyType,
                        __KeyHasher,
                        __RehashPolicy,
                        __keyExtractor,
                        __keyComparator,
                        __nodeDestructor
                > :: __ht_cend () const noexcept -> __ht_ConstIterator {

                    return __ht_ConstIterator (
                            nullptr,
                            0ULL
                    );
                }


                template <
                        typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyComparator,    // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    // NOLINT(bugprone-reserved-identifier)
                > auto __HashTable <
                        __ElementType,
                        __KeyType,
                        __KeyHasher,
                        __RehashPolicy,
                        __keyExtractor,
                        __keyComparator,
                        __nodeDestructor
                > :: __ht_get (
                        __KeyType const & key,
                        bool            * pIsNew
                ) noexcept -> __ElementType * {

                    if ( this->__ht_empty() ) {
                        return this->__ht_allocateBuckets ( this->_rehash.currentFactor () );
                    }

                    auto hashValue                  = this->_hasher ( key );
                    __NodeType * & bucket           = this->__ht_bucket ( hashValue );
                    __NodeType * pSeekAndNewNode    = bucket;
                    Size bucketSize                 = 0ULL;

                    while ( pSeekAndNewNode != nullptr ) {
                        if ( __keyComparator ( __keyExtractor ( pSeekAndNewNode->_data ), key ) ) {
                            * pIsNew = false;
                            return & pSeekAndNewNode->_data;
                        }

                        pSeekAndNewNode = pSeekAndNewNode->_pNext;
                        ++ bucketSize;
                    }

                    pSeekAndNewNode         = this->__ht_allocateNode ();
                    pSeekAndNewNode->_pNext = bucket;
                    bucket                  = pSeekAndNewNode;

                    ++ this->_size;

                    if ( bucketSize >= this->_rehashPolicy.loadFactor() ) {
                        auto rehashRequiredData = this->_rehash.rehashRequired (
                                this->_bucketCount,
                                this->_size,
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
                    return & pSeekAndNewNode->_data;
                }


                template <
                        typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyComparator,    // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    // NOLINT(bugprone-reserved-identifier)
                > auto __HashTable <
                        __ElementType,
                        __KeyType,
                        __KeyHasher,
                        __RehashPolicy,
                        __keyExtractor,
                        __keyComparator,
                        __nodeDestructor
                > :: __ht_get (
                        __KeyType const & key
                ) const noexcept -> __ElementType const * {

                    if ( this->__ht_empty() ) {
                        return nullptr;
                    }

                    auto pBucketHead = this->__ht_bucket ( this->_hasher ( key ) );
                    while ( pBucketHead != nullptr ) {

                        if ( __keyComparator ( __keyExtractor ( pBucketHead->_data ), key ) ) {
                            return & pBucketHead->_data;
                        }

                        pBucketHead = pBucketHead->_pNext;
                    }

                    return nullptr;
                }


                template <
                        typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyComparator,    // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __HashTable <
                        __ElementType,
                        __KeyType,
                        __KeyHasher,
                        __RehashPolicy,
                        __keyExtractor,
                        __keyComparator,
                        __nodeDestructor
                > :: __ht_at (
                        __KeyType const & key
                ) noexcept -> __ElementType * {

                    return const_cast < __ElementType * > ( static_cast < __HashTable const * > ( this )->__ht_get ( key ) );
                }


                template <
                        typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyComparator,    // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __HashTable <
                        __ElementType,
                        __KeyType,
                        __KeyHasher,
                        __RehashPolicy,
                        __keyExtractor,
                        __keyComparator,
                        __nodeDestructor
                > :: __ht_at (
                        __KeyType const & key
                ) const noexcept -> __ElementType const * {

                    return this->__ht_get ( key );
                }


                template <
                        typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyComparator,    // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    // NOLINT(bugprone-reserved-identifier)
                > auto __HashTable <
                        __ElementType,
                        __KeyType,
                        __KeyHasher,
                        __RehashPolicy,
                        __keyExtractor,
                        __keyComparator,
                        __nodeDestructor
                > :: __ht_rehash (
                        Size                bucketCount,
                        Size                hashValueOfNewNode,
                        __NodeType  const * pNewEmptyNode
                ) noexcept -> void {

                    Size            oldBucketSize = this->_bucketCount;
                    Size            newHash;
                    __NodeType    * pToMove;

                    this->__ht_allocateBuckets ( bucketCount );

                    for ( Size bucketIndex = 0ULL; bucketIndex < oldBucketSize; ++ bucketIndex ) {

                        /// guaranteed to be lower than newer size, so using the method
                        /// with the new greater modulus will not impact the result
                        auto & oldBucket = this->__ht_bucket ( bucketIndex );

                        while ( oldBucket != nullptr ) {

                            if ( pNewEmptyNode == oldBucket ) {
                                newHash = hashValueOfNewNode;
                            } else {
                                newHash = this->_hasher ( __keyExtractor ( oldBucket->_data ) );
                            }

                            auto & newBucket = this->__ht_bucket ( newHash );
                            if ( newBucket == oldBucket ) {
                                break;
                            }

                            pToMove     = oldBucket;
                            oldBucket   = oldBucket->_pNext;

                            __HashTable :: __ht_rehashEmplace ( & newBucket, pToMove );
                        }

                        __NodeType * pOldBucketHead = oldBucket;
                        while ( pOldBucketHead != nullptr && pOldBucketHead->_pNext != nullptr ) {


                            if ( pNewEmptyNode == pOldBucketHead->_pNext ) {
                                newHash = hashValueOfNewNode;
                            } else {
                                newHash = this->_hasher ( __keyExtractor ( pOldBucketHead->_pNext->_data ) );
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
                        typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyComparator,    // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __HashTable <
                        __ElementType,
                        __KeyType,
                        __KeyHasher,
                        __RehashPolicy,
                        __keyExtractor,
                        __keyComparator,
                        __nodeDestructor
                > :: __ht_rehashEmplace (
                        __NodeType ** pBucket,
                        __NodeType  * pNode
                ) noexcept -> void {

                    pNode->_pNext   = * pBucket;
                    * pBucket       = pNode;
                }


                template <
                        typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyComparator,    // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    // NOLINT(bugprone-reserved-identifier)
                > __CDS_cpplang_NonConstConstexprMemberFunction auto __HashTable <
                        __ElementType,
                        __KeyType,
                        __KeyHasher,
                        __RehashPolicy,
                        __keyExtractor,
                        __keyComparator,
                        __nodeDestructor
                > :: __ht_bucket (
                        Size hash
                ) noexcept -> __NodeType * & {

                    return this->_pBucketArray [ hash % this->_bucketCount ];
                }


                template <
                        typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyComparator,    // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __HashTable <
                        __ElementType,
                        __KeyType,
                        __KeyHasher,
                        __RehashPolicy,
                        __keyExtractor,
                        __keyComparator,
                        __nodeDestructor
                > :: __ht_bucket (
                        Size hash
                ) const noexcept -> __NodeType * const & {

                    return this->_pBucketArray [ hash % this->_bucketCount ];
                }


                template <
                        typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyComparator,    // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __HashTable <
                        __ElementType,
                        __KeyType,
                        __KeyHasher,
                        __RehashPolicy,
                        __keyExtractor,
                        __keyComparator,
                        __nodeDestructor
                > :: __ht_allocateBuckets (
                        Size bucketCount
                ) noexcept -> void {

                    this->_pBucketArray = reinterpret_cast < __NodeType * > (
                            std :: memset (
                                    cds :: __hidden :: __impl :: __allocation :: __reallocPrimitiveArray (
                                            this->_pBucketArray,
                                            bucketCount
                                    ) + this->_bucketCount,
                                    0ULL,
                                    sizeof ( __NodeType ) * ( bucketCount - this->_bucketCount )
                            )
                    ) - this->_bucketCount;

                    this->_bucketCount = bucketCount;
                }


                template <
                        typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyComparator,    // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __HashTable <
                        __ElementType,
                        __KeyType,
                        __KeyHasher,
                        __RehashPolicy,
                        __keyExtractor,
                        __keyComparator,
                        __nodeDestructor
                > :: __ht_freeBuckets () noexcept -> void {

                    cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray (
                            cds :: exchange (
                                    this->_pBucketArray,
                                    nullptr
                            )
                    );

                    this->_bucketCount = 0ULL;
                }


                template <
                        typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyComparator,    // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __HashTable <
                        __ElementType,
                        __KeyType,
                        __KeyHasher,
                        __RehashPolicy,
                        __keyExtractor,
                        __keyComparator,
                        __nodeDestructor
                > :: __ht_allocateNode () const noexcept -> __NodeType * {

                    return cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveObject < __NodeType > ();
                }


                template <
                        typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyComparator,    // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __HashTable <
                        __ElementType,
                        __KeyType,
                        __KeyHasher,
                        __RehashPolicy,
                        __keyExtractor,
                        __keyComparator,
                        __nodeDestructor
                > :: __ht_freeNode (
                        __NodeType * pNode
                ) const noexcept -> void {

                    __nodeDestructor ( pNode->_data );
                    cds :: __hidden :: __impl :: __allocation :: __freePrimitiveObject ( pNode );
                }


                template <
                        typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyComparator,    // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    // NOLINT(bugprone-reserved-identifier)
                > auto __HashTable <
                        __ElementType,
                        __KeyType,
                        __KeyHasher,
                        __RehashPolicy,
                        __keyExtractor,
                        __keyComparator,
                        __nodeDestructor
                > :: __ht_remove (
                        __KeyType const & key
                ) noexcept -> bool {

                    if ( this->__ht_empty() ) {
                        return false;
                    }

                    __NodeType * pToRemove;
                    __NodeType * pBucketHead;

                    auto & bucket = this->__ht_bucket ( this->_hasher ( key ) );
                    if ( __keyComparator ( __keyExtractor ( bucket->_data ), key ) ) {

                        pToRemove   = bucket;
                        bucket      = bucket->_pNext;

                        this->__ht_freeNode ( pToRemove );

                        -- this->_size;
                        return true;
                    }

                    pBucketHead = bucket;
                    while ( pBucketHead->_pNext != nullptr ) {

                        if ( __keyComparator ( __keyExtractor ( pBucketHead->_pNext->_data ), key ) ) {

                            pToRemove           = pBucketHead->_pNext;
                            pBucketHead->_pNext = pBucketHead->_pNext->_pNext;

                            this->__ht_freeNode ( pToRemove );

                            -- this->_size;
                            return true;
                        }

                        pBucketHead = pBucketHead->_pNext;
                    }

                    return false;
                }


                template <
                        typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyComparator,    // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    // NOLINT(bugprone-reserved-identifier)
                > auto __HashTable <
                        __ElementType,
                        __KeyType,
                        __KeyHasher,
                        __RehashPolicy,
                        __keyExtractor,
                        __keyComparator,
                        __nodeDestructor
                > :: __ht_remove (
                        __NodeType  const * pPreviousNode,
                        __NodeType  const * pCurrentNode,
                        Size                bucketIndex
                ) noexcept -> bool {

                    if ( this->__ht_empty() ) {
                        return false;
                    }

                    __NodeType  * & pBucket         = this->__ht_bucket ( bucketIndex );
                    auto            pPreviousCasted = const_cast < __NodeType * > ( pPreviousNode );
                    auto            pCurrentCasted  = const_cast < __NodeType * > ( pCurrentNode );

                    if (
                            pPreviousCasted == nullptr &&
                            pCurrentCasted  == pBucket
                    ) {

                        pBucket = pBucket->_pNext;
                        this->__ht_freeNode ( pCurrentCasted );
                    } else if (
                            pCurrentCasted  != nullptr &&
                            pPreviousCasted != nullptr
                    ) {

                        pPreviousCasted->_pNext = pCurrentCasted->_pNext;
                        this->__ht_freeNode ( pCurrentCasted );
                    } else {

                        return false;
                    }

                    -- this->_size;
                    return true;
                }


                template <
                        typename                                                            __ElementType,      // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyComparator,    // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    // NOLINT(bugprone-reserved-identifier)
                > __CDS_OptimalInline auto __HashTable <
                        __ElementType,
                        __KeyType,
                        __KeyHasher,
                        __RehashPolicy,
                        __keyExtractor,
                        __keyComparator,
                        __nodeDestructor
                > :: __ht_remove (
                        __ht_Iterator const & iterator
                ) noexcept -> bool {

                    if (
                            this->__ht_empty() ||
                            iterator._pCurrentNode == nullptr
                    ) {
                        return false;
                    }

                    __NodeType * & pBucket = this->__ht_bucket ( bucketIndex );

                    if (
                            pPreviousNode   == nullptr &&
                            pCurrentNode    == pBucket
                    ) {

                        pBucket = pBucket->_pNext;
                        this->__ht_freeNode ( pCurrentNode );
                    } else if (
                            pCurrentNode    != nullptr &&
                            pPreviousNode   != nullptr
                    ) {

                        pPreviousNode->_pNext = pCurrentNode->_pNext;
                        this->__ht_freeNode(pCurrentNode);
                    } else {

                        return false;
                    }

                    -- this->_size;
                    return true;
                }

            }
        }
    }
}

#endif // __CDS_SHARED_HASH_TABLE_IMPL_HPP__
