/*
 * Created by loghin on 27/07/22.
 */

#ifndef __CDS_EX_SHARED_HASH_TABLE_IMPL_HPP__
#define __CDS_EX_SHARED_HASH_TABLE_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template <
                        typename                                                            __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyHasher,        /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __KeyType >                  __keyComparator,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    /* NOLINT(bugprone-reserved-identifier) */
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
                        typename                                                            __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyHasher,        /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __KeyType >                  __keyComparator,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    /* NOLINT(bugprone-reserved-identifier) */
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
                        typename                                                            __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyHasher,        /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __KeyType >                  __keyComparator,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    /* NOLINT(bugprone-reserved-identifier) */
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
                        typename                                                            __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyHasher,        /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __KeyType >                  __keyComparator,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    /* NOLINT(bugprone-reserved-identifier) */
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
                        typename                                                            __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyHasher,        /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __KeyType >                  __keyComparator,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename                                                            __CopyFunction      /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline __HashTable <
                        __ElementType,
                        __KeyType,
                        __KeyHasher,
                        __RehashPolicy,
                        __keyExtractor,
                        __keyComparator,
                        __nodeDestructor
                > :: __HashTable (
                        __HashTable     const & hashTable,
                        __CopyFunction  const & copyFunction
                ) noexcept {

                    this->__ht_copyCleared ( hashTable, copyFunction );
                }


                template <
                        typename                                                            __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyHasher,        /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __KeyType >                  __keyComparator,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    /* NOLINT(bugprone-reserved-identifier) */
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
                ) noexcept {

                    this->__ht_moveCleared ( std :: move ( hashTable ) );
                }


                template <
                        typename                                                            __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyHasher,        /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __KeyType >                  __keyComparator,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    /* NOLINT(bugprone-reserved-identifier) */
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
                        typename                                                            __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyHasher,        /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __KeyType >                  __keyComparator,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    /* NOLINT(bugprone-reserved-identifier) */
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
                        typename                                                            __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyHasher,        /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __KeyType >                  __keyComparator,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    /* NOLINT(bugprone-reserved-identifier) */
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
                        typename                                                            __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyHasher,        /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __KeyType >                  __keyComparator,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    /* NOLINT(bugprone-reserved-identifier) */
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
                        typename                                                            __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyHasher,        /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __KeyType >                  __keyComparator,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    /* NOLINT(bugprone-reserved-identifier) */
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
                        typename                                                            __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyHasher,        /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __KeyType >                  __keyComparator,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    /* NOLINT(bugprone-reserved-identifier) */
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
                        typename                                                            __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyHasher,        /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __KeyType >                  __keyComparator,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    /* NOLINT(bugprone-reserved-identifier) */
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
                        typename                                                            __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyHasher,        /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __KeyType >                  __keyComparator,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    /* NOLINT(bugprone-reserved-identifier) */
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
                        typename                                                            __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyHasher,        /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __KeyType >                  __keyComparator,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __HashTable <
                        __ElementType,
                        __KeyType,
                        __KeyHasher,
                        __RehashPolicy,
                        __keyExtractor,
                        __keyComparator,
                        __nodeDestructor
                > :: __ht_new (
                        __ElementType const * pReferenceElement,
                        bool                * pIsNew
                ) noexcept -> __ElementType * {

                    return this->__ht_get (
                            __keyExtractor ( * pReferenceElement ),
                            pIsNew
                    );
                }


                template <
                        typename                                                            __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyHasher,        /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __KeyType >                  __keyComparator,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    /* NOLINT(bugprone-reserved-identifier) */
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
                        this->__ht_allocateBuckets ( this->_rehash.currentFactor () );
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

                    if ( bucketSize >= this->_rehash.loadFactor() ) {
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
                        typename                                                            __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyHasher,        /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __KeyType >                  __keyComparator,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    /* NOLINT(bugprone-reserved-identifier) */
                > auto __HashTable <
                        __ElementType,
                        __KeyType,
                        __KeyHasher,
                        __RehashPolicy,
                        __keyExtractor,
                        __keyComparator,
                        __nodeDestructor
                > :: __ht_getConst (
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
                        typename                                                            __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyHasher,        /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __KeyType >                  __keyComparator,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    /* NOLINT(bugprone-reserved-identifier) */
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
                        typename                                                            __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyHasher,        /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __KeyType >                  __keyComparator,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __HashTable <
                        __ElementType,
                        __KeyType,
                        __KeyHasher,
                        __RehashPolicy,
                        __keyExtractor,
                        __keyComparator,
                        __nodeDestructor
                > :: __ht_atConst (
                        __KeyType const & key
                ) const noexcept -> __ElementType const * {

                    return this->__ht_get ( key );
                }


                template <
                        typename                                                            __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyHasher,        /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __KeyType >                  __keyComparator,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    /* NOLINT(bugprone-reserved-identifier) */
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

                        /** guaranteed to be lower than newer size, so using the method
                          * with the new greater modulus will not impact the result */
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
                        typename                                                            __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyHasher,        /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __KeyType >                  __keyComparator,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    /* NOLINT(bugprone-reserved-identifier) */
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
                        typename                                                            __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyHasher,        /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __KeyType >                  __keyComparator,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    /* NOLINT(bugprone-reserved-identifier) */
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
                        typename                                                            __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyHasher,        /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __KeyType >                  __keyComparator,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    /* NOLINT(bugprone-reserved-identifier) */
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
                        typename                                                            __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyHasher,        /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __KeyType >                  __keyComparator,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    /* NOLINT(bugprone-reserved-identifier) */
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

                    this->_pBucketArray = reinterpret_cast < __NodeType ** > (
                            std :: memset (
                                    cds :: __hidden :: __impl :: __allocation :: __reallocPrimitiveArray (
                                            this->_pBucketArray,
                                            bucketCount
                                    ) + this->_bucketCount,
                                    0ULL,
                                    sizeof ( __NodeType * ) * ( bucketCount - this->_bucketCount )
                            )
                    ) - this->_bucketCount;

                    this->_bucketCount = bucketCount;
                }


                template <
                        typename                                                            __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyHasher,        /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __KeyType >                  __keyComparator,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    /* NOLINT(bugprone-reserved-identifier) */
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
                        typename                                                            __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyHasher,        /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __KeyType >                  __keyComparator,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    /* NOLINT(bugprone-reserved-identifier) */
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
                        typename                                                            __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyHasher,        /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __KeyType >                  __keyComparator,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    /* NOLINT(bugprone-reserved-identifier) */
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
                        typename                                                            __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyHasher,        /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __KeyType >                  __keyComparator,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    /* NOLINT(bugprone-reserved-identifier) */
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
                        typename                                                            __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyHasher,        /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __KeyType >                  __keyComparator,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    /* NOLINT(bugprone-reserved-identifier) */
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

                    if ( this->__ht_empty() || bucketIndex >= this->_bucketCount ) {
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
                        typename                                                            __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyHasher,        /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __KeyType >                  __keyComparator,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __HashTable <
                        __ElementType,
                        __KeyType,
                        __KeyHasher,
                        __RehashPolicy,
                        __keyExtractor,
                        __keyComparator,
                        __nodeDestructor
                > :: __ht_removeIterator (
                        __ht_Iterator const & iterator
                ) noexcept -> bool {

                    if (
                            iterator._bucketIndex >= iterator._bucketCount ||
                            iterator._pListArray == nullptr ||
                            iterator._pCurrentNode == nullptr && iterator._pPreviousNode
                    ) {

                        return false;
                    }

                    return this->__ht_remove (
                            iterator._pPreviousNode,
                            iterator._pCurrentNode,
                            iterator._bucketIndex
                    );
                }


                template <
                        typename                                                            __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyHasher,        /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __KeyType >                  __keyComparator,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __HashTable <
                        __ElementType,
                        __KeyType,
                        __KeyHasher,
                        __RehashPolicy,
                        __keyExtractor,
                        __keyComparator,
                        __nodeDestructor
                > :: __ht_removeIteratorConst (
                        __ht_ConstIterator const & iterator
                ) noexcept -> bool {

                    if (
                            iterator._bucketIndex >= iterator._bucketCount ||
                            iterator._pListArray == nullptr ||
                            iterator._pCurrentNode == nullptr && iterator._pPreviousNode
                    ) {

                        return false;
                    }

                    return this->__ht_remove (
                            iterator._pPreviousNode,
                            iterator._pCurrentNode,
                            iterator._bucketIndex
                    );
                }


                template <
                        typename                                                            __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyHasher,        /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __KeyType >                  __keyComparator,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __HashTable <
                        __ElementType,
                        __KeyType,
                        __KeyHasher,
                        __RehashPolicy,
                        __keyExtractor,
                        __keyComparator,
                        __nodeDestructor
                > :: __ht_removeIteratorArray (
                        __ht_Iterator   const * const * ppIterators,
                        Size                            iteratorArrayCount
                ) noexcept -> Size {

                    Size removedCount = 0ULL;
                    for ( Size index = 0ULL; index < iteratorArrayCount; ++ index ) {

                        if ( ppIterators [ index ] == nullptr ) {
                            continue;
                        }

                        if ( this->__ht_removeIterator ( * ppIterators [ index ] ) ) {
                            ++ removedCount;
                        }
                    }

                    return removedCount;
                }


                template <
                        typename                                                            __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyHasher,        /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __KeyType >                  __keyComparator,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __HashTable <
                        __ElementType,
                        __KeyType,
                        __KeyHasher,
                        __RehashPolicy,
                        __keyExtractor,
                        __keyComparator,
                        __nodeDestructor
                > :: __ht_removeConstIteratorArray (
                        __ht_ConstIterator  const * const * ppIterators,
                        Size                                iteratorArrayCount
                ) noexcept -> Size {

                    Size removedCount = 0ULL;
                    for ( Size index = 0ULL; index < iteratorArrayCount; ++ index ) {

                        if ( ppIterators [ index ] == nullptr ) {
                            continue;
                        }

                        if ( this->__ht_removeIteratorConst ( * ppIterators [ index ] ) ) {
                            ++ removedCount;
                        }
                    }

                    return removedCount;
                }


                template <
                        typename                                                            __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyHasher,        /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __KeyType >                  __keyComparator,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename                                                            __CopyFunction      /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __HashTable <
                        __ElementType,
                        __KeyType,
                        __KeyHasher,
                        __RehashPolicy,
                        __keyExtractor,
                        __keyComparator,
                        __nodeDestructor
                > :: __ht_copy (
                        __HashTable     const & table,
                        __CopyFunction  const & copyFunction
                ) noexcept -> void {

                    if ( this == & table ) {
                        return;
                    }

                    this->__ht_clear();
                    this->__ht_copyCleared ( table, copyFunction );
                }


                template <
                        typename                                                            __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyHasher,        /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __KeyType >                  __keyComparator,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename                                                            __CopyFunction      /* NOLINT(bugprone-reserved-identifier) */
                > auto __HashTable <
                        __ElementType,
                        __KeyType,
                        __KeyHasher,
                        __RehashPolicy,
                        __keyExtractor,
                        __keyComparator,
                        __nodeDestructor
                > :: __ht_copyCleared (
                        __HashTable     const & table,
                        __CopyFunction  const & copyFunction
                ) noexcept -> void {

                    if ( table.__ht_empty() ) {
                        return;
                    }

                    this->_size = table._size;
                    this->__ht_allocateBuckets ( table._bucketCount );
                    for ( Size bucketIndex = 0ULL; bucketIndex < table._bucketCount; ++ bucketIndex ) {

                        auto & thisBucket   = this->__ht_bucket ( bucketIndex );
                        auto & tableBucket  = table.__ht_bucket ( bucketIndex );

                        __NodeType * pTableHead     = tableBucket;
                        __NodeType * pThisBack      = nullptr;

                        while ( pTableHead != nullptr ) {

                            auto pNewNode       = this->__ht_allocateNode ();
                            pNewNode->_pNext    = nullptr;
                            copyFunction ( pNewNode->_data, pTableHead->_data );

                            pTableHead = pTableHead->_pNext;

                            if ( pThisBack == nullptr ) {
                                thisBucket          = pNewNode;
                            } else {
                                pThisBack->_pNext   = pNewNode;
                            }

                            pThisBack = pNewNode;
                        }
                    }

                    this->_rehash = table._rehash;
                }


                template <
                        typename                                                            __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyHasher,        /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __KeyType >                  __keyComparator,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __HashTable <
                        __ElementType,
                        __KeyType,
                        __KeyHasher,
                        __RehashPolicy,
                        __keyExtractor,
                        __keyComparator,
                        __nodeDestructor
                > :: __ht_move (
                        __HashTable && table
                ) noexcept -> void {

                    if ( this == & table ) {
                        return;
                    }

                    this->__ht_clear();
                    this->__ht_moveCleared ( std :: move ( table ) );
                }


                template <
                        typename                                                            __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyHasher,        /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __KeyType >                  __keyComparator,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    /* NOLINT(bugprone-reserved-identifier) */
                > constexpr auto __HashTable <
                        __ElementType,
                        __KeyType,
                        __KeyHasher,
                        __RehashPolicy,
                        __keyExtractor,
                        __keyComparator,
                        __nodeDestructor
                > :: __ht_moveCleared (
                        __HashTable && table
                ) noexcept -> void {

                    this->_pBucketArray = cds :: exchange ( table._pBucketArray, nullptr );
                    this->_bucketCount  = cds :: exchange ( table._bucketCount, 0ULL );
                    this->_size         = cds :: exchange ( table._size, 0ULL );
                    this->_rehash       = std :: move ( table._rehash );
                    this->_hasher       = std :: move ( table._hasher );
                }


                template <
                        typename                                                            __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyHasher,        /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __KeyType >                  __keyComparator,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    /* NOLINT(bugprone-reserved-identifier) */
                > auto __HashTable <
                        __ElementType,
                        __KeyType,
                        __KeyHasher,
                        __RehashPolicy,
                        __keyExtractor,
                        __keyComparator,
                        __nodeDestructor
                > :: __ht_findIterator (
                        __KeyType const & key
                ) noexcept -> __ht_Iterator {

                    if ( this->__ht_empty() ) {
                        return __ht_Iterator ();
                    }

                    Size bucketIndex = this->_hasher ( key ) % this->_bucketCount;

                    __NodeType * pPrevious  = nullptr;
                    __NodeType * pCurrent   = this->_pBucketArray [ bucketIndex ];

                    while ( pCurrent != nullptr ) {

                        if ( __keyComparator ( __keyExtractor ( pCurrent->_data ), key ) ) {
                            return __ht_Iterator (
                                    this->_pBucketArray,
                                    this->_bucketCount,
                                    pCurrent,
                                    pPrevious,
                                    bucketIndex
                            );
                        }

                        pPrevious   = pCurrent;
                        pCurrent    = pCurrent->_pNext;
                    }

                    return __ht_Iterator ();
                }


                template <
                        typename                                                            __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyHasher,        /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __KeyType >                  __keyComparator,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    /* NOLINT(bugprone-reserved-identifier) */
                > auto __HashTable <
                        __ElementType,
                        __KeyType,
                        __KeyHasher,
                        __RehashPolicy,
                        __keyExtractor,
                        __keyComparator,
                        __nodeDestructor
                > :: __ht_findIteratorConst (
                        __KeyType const & key
                ) const noexcept -> __ht_ConstIterator {

                    if ( this->__ht_empty() ) {
                        return __ht_ConstIterator ();
                    }

                    Size bucketIndex = this->_hasher ( key ) % this->_bucketCount;

                    __NodeType const * pPrevious  = nullptr;
                    __NodeType const * pCurrent   = this->_pBucketArray [ bucketIndex ];

                    while ( pCurrent != nullptr ) {

                        if ( __keyComparator ( __keyExtractor ( pCurrent->_data ), key ) ) {
                            return __ht_ConstIterator (
                                    this->_pBucketArray,
                                    this->_bucketCount,
                                    pCurrent,
                                    pPrevious,
                                    bucketIndex
                            );
                        }

                        pPrevious   = pCurrent;
                        pCurrent    = pCurrent->_pNext;
                    }

                    return __ht_ConstIterator ();
                }


                template <
                        typename                                                            __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyHasher,        /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __KeyType >                  __keyComparator,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        cds :: utility :: ComparisonFunction < __ElementType >              __comparator        /* NOLINT(bugprone-reserved-identifier) */
                > auto __HashTable <
                        __ElementType,
                        __KeyType,
                        __KeyHasher,
                        __RehashPolicy,
                        __keyExtractor,
                        __keyComparator,
                        __nodeDestructor
                > :: __ht_equals (
                        __HashTable const & table
                ) const noexcept -> bool {

                    if ( this == & table ) {
                        return true;
                    }

                    if ( this->__ht_empty() ) {
                        return table.__ht_empty();
                    }

                    if ( table.__ht_empty() || this->_bucketCount != table._bucketCount ) {
                        return false;
                    }

                    for ( Size bucketIndex = 0ULL; bucketIndex < this->_bucketCount; ++ bucketIndex ) {

                        auto pThisBucketHead    = this->_pBucketArray [ bucketIndex ];
                        auto pOtherBucketHead   = table._pBucketArray [ bucketIndex ];

                        while ( pThisBucketHead != nullptr && pOtherBucketHead != nullptr ) {
                            if ( ! __comparator ( pThisBucketHead->_data, pOtherBucketHead->_data ) ) {
                                return false;
                            }
                        }

                        if ( pThisBucketHead != nullptr || pOtherBucketHead != nullptr ) {
                            return false;
                        }
                    }

                    return true;
                }

            }
        }
    }
}

#endif /* __CDS_EX_SHARED_HASH_TABLE_IMPL_HPP__ */
