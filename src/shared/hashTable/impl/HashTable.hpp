/*
 * Created by loghin on 27/07/22.
 */

#ifndef __CDS_SHARED_HASH_TABLE_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_HASH_TABLE_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template <
                    typename                                                                    __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyHasher,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperFunction < __KeyType const &, __ElementType const & >   __keyExtractor,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __KeyType const &, __KeyType const & >    __keyComparator,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: ConsumerFunction < __ElementType & >                          __nodeDestructor    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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
                    typename                                                                    __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyHasher,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperFunction < __KeyType const &, __ElementType const & >   __keyExtractor,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __KeyType const &, __KeyType const & >    __keyComparator,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: ConsumerFunction < __ElementType & >                          __nodeDestructor    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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

                /* only hasher received, initialize key hasher using received one */
            }


            template <
                    typename                                                                    __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyHasher,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperFunction < __KeyType const &, __ElementType const & >   __keyExtractor,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __KeyType const &, __KeyType const & >    __keyComparator,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: ConsumerFunction < __ElementType & >                          __nodeDestructor    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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

                /* only rehash policy received, initialize rehash policy using received one */
            }


            template <
                    typename                                                                    __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyHasher,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperFunction < __KeyType const &, __ElementType const & >   __keyExtractor,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __KeyType const &, __KeyType const & >    __keyComparator,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: ConsumerFunction < __ElementType & >                          __nodeDestructor    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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

                /* initialize key hasher and rehash policy using received ones */
            }


            template <
                    typename                                                                    __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyHasher,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperFunction < __KeyType const &, __ElementType const & >   __keyExtractor,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __KeyType const &, __KeyType const & >    __keyComparator,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: ConsumerFunction < __ElementType & >                          __nodeDestructor    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename                                                            __CopyFunction      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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

                /* initialize by copy cleared, since hash table is at construction */
                this->__ht_copyCleared ( hashTable, copyFunction );
            }


            template <
                    typename                                                                    __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyHasher,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperFunction < __KeyType const &, __ElementType const & >   __keyExtractor,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __KeyType const &, __KeyType const & >    __keyComparator,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: ConsumerFunction < __ElementType & >                          __nodeDestructor    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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
                    _pBucketArray ( cds :: exchange ( hashTable._pBucketArray, nullptr ) ),
                    _bucketCount ( cds :: exchange ( hashTable._bucketCount, 0ULL ) ),
                    _size ( cds :: exchange ( hashTable._size, 0ULL ) ),
                    _rehash ( std :: move ( hashTable._rehash ) ),
                    _hasher ( std :: move ( hashTable._hasher ) ) {

            }


            template <
                    typename                                                                    __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyHasher,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperFunction < __KeyType const &, __ElementType const & >   __keyExtractor,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __KeyType const &, __KeyType const & >    __keyComparator,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: ConsumerFunction < __ElementType & >                          __nodeDestructor    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > auto __HashTable <
                    __ElementType,
                    __KeyType,
                    __KeyHasher,
                    __RehashPolicy,
                    __keyExtractor,
                    __keyComparator,
                    __nodeDestructor
            > :: __ht_clear () noexcept -> void {

                /* if bucket array exists */
                if ( this->_pBucketArray != nullptr ) {

                    /* parse each bucket */
                    for ( Size bucketIndex = 0ULL; bucketIndex < this->_bucketCount; ++ bucketIndex ) {

                        /* parse the bucket node by node */
                        __NodeType * & bucket = this->_pBucketArray [ bucketIndex ];
                        while ( bucket != nullptr ) {

                            /* acquire next and free current node */
                            auto pCopy = bucket;
                            bucket = bucket->_pNext;
                            __HashTable :: __ht_freeNode ( pCopy );
                        }
                    }

                    /* reset the rehash policy, size and free the bucket buffer */
                    this->_rehash.reset ();
                    this->__ht_freeBuckets ();
                    this->_size = 0ULL;
                }
            }


            template <
                    typename                                                                    __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyHasher,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperFunction < __KeyType const &, __ElementType const & >   __keyExtractor,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __KeyType const &, __KeyType const & >    __keyComparator,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: ConsumerFunction < __ElementType & >                          __nodeDestructor    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > constexpr auto __HashTable <
                    __ElementType,
                    __KeyType,
                    __KeyHasher,
                    __RehashPolicy,
                    __keyExtractor,
                    __keyComparator,
                    __nodeDestructor
            > :: __ht_size () const noexcept -> Size {

                /* return number of elements directly */
                return this->_size;
            }


            template <
                    typename                                                                    __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyHasher,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperFunction < __KeyType const &, __ElementType const & >   __keyExtractor,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __KeyType const &, __KeyType const & >    __keyComparator,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: ConsumerFunction < __ElementType & >                          __nodeDestructor    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > constexpr auto __HashTable <
                    __ElementType,
                    __KeyType,
                    __KeyHasher,
                    __RehashPolicy,
                    __keyExtractor,
                    __keyComparator,
                    __nodeDestructor
            > :: __ht_empty () const noexcept -> bool {

                /* empty if no element exists */
                return this->_size == 0ULL;
            }


            template <
                    typename                                                                    __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyHasher,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperFunction < __KeyType const &, __ElementType const & >   __keyExtractor,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __KeyType const &, __KeyType const & >    __keyComparator,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: ConsumerFunction < __ElementType & >                          __nodeDestructor    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_MaybeUnused constexpr auto __HashTable <
                    __ElementType,
                    __KeyType,
                    __KeyHasher,
                    __RehashPolicy,
                    __keyExtractor,
                    __keyComparator,
                    __nodeDestructor
            > :: __ht_bucketCount () const noexcept -> Size {

                /* return the bucket count directly */
                return this->_bucketCount;
            }


            template <
                    typename                                                                    __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyHasher,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperFunction < __KeyType const &, __ElementType const & >   __keyExtractor,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __KeyType const &, __KeyType const & >    __keyComparator,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: ConsumerFunction < __ElementType & >                          __nodeDestructor    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_cpplang_NonConstConstexprMemberFunction auto __HashTable <
                    __ElementType,
                    __KeyType,
                    __KeyHasher,
                    __RehashPolicy,
                    __keyExtractor,
                    __keyComparator,
                    __nodeDestructor
            > :: __ht_begin () noexcept -> __ht_Iterator {

                /* pass the bucket array and count, let the iterator find the first element */
                return __ht_Iterator (
                        this->_pBucketArray,
                        this->_bucketCount
                );
            }


            template <
                    typename                                                                    __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyHasher,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperFunction < __KeyType const &, __ElementType const & >   __keyExtractor,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __KeyType const &, __KeyType const & >    __keyComparator,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: ConsumerFunction < __ElementType & >                          __nodeDestructor    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_cpplang_NonConstConstexprMemberFunction auto __HashTable <
                    __ElementType,
                    __KeyType,
                    __KeyHasher,
                    __RehashPolicy,
                    __keyExtractor,
                    __keyComparator,
                    __nodeDestructor
            > :: __ht_end () noexcept -> __ht_Iterator {

                /* pass no array, invalid memory space */
                return __ht_Iterator (
                        nullptr,
                        0ULL
                );
            }


            template <
                    typename                                                                    __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyHasher,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperFunction < __KeyType const &, __ElementType const & >   __keyExtractor,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __KeyType const &, __KeyType const & >    __keyComparator,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: ConsumerFunction < __ElementType & >                          __nodeDestructor    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > constexpr auto __HashTable <
                    __ElementType,
                    __KeyType,
                    __KeyHasher,
                    __RehashPolicy,
                    __keyExtractor,
                    __keyComparator,
                    __nodeDestructor
            > :: __ht_cbegin () const noexcept -> __ht_ConstIterator {

                /* pass the bucket array and count, let the iterator find the first element */
                return __ht_ConstIterator (
                        this->_pBucketArray,
                        this->_bucketCount
                );
            }


            template <
                    typename                                                                    __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyHasher,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperFunction < __KeyType const &, __ElementType const & >   __keyExtractor,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __KeyType const &, __KeyType const & >    __keyComparator,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: ConsumerFunction < __ElementType & >                          __nodeDestructor    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > constexpr auto __HashTable <
                    __ElementType,
                    __KeyType,
                    __KeyHasher,
                    __RehashPolicy,
                    __keyExtractor,
                    __keyComparator,
                    __nodeDestructor
            > :: __ht_cend () const noexcept -> __ht_ConstIterator {

                /* pass no array, invalid memory space */
                return __ht_ConstIterator (
                        nullptr,
                        0ULL
                );
            }


            template <
                    typename                                                                    __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyHasher,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperFunction < __KeyType const &, __ElementType const & >   __keyExtractor,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __KeyType const &, __KeyType const & >    __keyComparator,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: ConsumerFunction < __ElementType & >                          __nodeDestructor    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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
                    bool                * pNewElementCreated
            ) noexcept -> __ElementType * {

                /* acquire key from reference element and return the value from __ht_get */
                return this->__ht_get (
                        __keyExtractor ( * pReferenceElement ),
                        pNewElementCreated
                );
            }


            template <
                    typename                                                                    __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyHasher,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperFunction < __KeyType const &, __ElementType const & >   __keyExtractor,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __KeyType const &, __KeyType const & >    __keyComparator,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: ConsumerFunction < __ElementType & >                          __nodeDestructor    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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

                /* if no bucket array exists */
                if ( this->_pBucketArray == nullptr ) {
                    /* allocate the bucket array */
                    this->__ht_allocateBuckets ( this->_rehash.currentFactor () );
                }

                /* obtain the hash of the key */
                auto const hashValue            = this->_hasher ( key );

                /* obtain the bucket where to insert the node into */
                __NodeType * & bucket           = this->__ht_bucket ( hashValue );

                /* node pointer used both to parse the current bucket and to allocate space, if no node found */
                __NodeType * pSeekAndNewNode    = bucket;

                /* size of current bucket, to detect a potential rehash */
                Size bucketSize                 = 0ULL;

                /* start looking into current bucket */
                while ( pSeekAndNewNode != nullptr ) {

                    /* compare extracted node key with received key */
                    if ( __keyComparator ( __keyExtractor ( pSeekAndNewNode->_data ), key ) ) {

                        /* if key found, no new node created, returned address of node data */
                        * pIsNew = false;
                        return & pSeekAndNewNode->_data;
                    }

                    /* look forward into bucket */
                    pSeekAndNewNode = pSeekAndNewNode->_pNext;
                    ++ bucketSize;
                }

                /* if flow control reaches this point, new node can be created. It will be inserted at the head */
                pSeekAndNewNode         = __HashTable :: __ht_allocateNode ();
                pSeekAndNewNode->_pNext = bucket;
                bucket                  = pSeekAndNewNode;

                /* increased size of table */
                ++ this->_size;

                /* if, potentially, bucket exceeds load factor, check if a rehash is required with current parameters */
                if ( bucketSize >= this->_rehash.loadFactor() ) {
                    auto const rehashRequiredData = this->_rehash.rehashRequired (
                            this->_bucketCount,
                            this->_size,
                            1ULL
                    );

                    /* if rehash is required, initiate it */
                    if ( rehashRequiredData._required ) {
                        this->__ht_rehash (
                                rehashRequiredData._size,
                                hashValue,
                                pSeekAndNewNode
                        );
                    }
                }

                /* at this point, a new node was inserted, and, potentially, the table has rehashed. */
                * pIsNew = true;

                /* return memory space of new node data */
                return & pSeekAndNewNode->_data;
            }


            template <
                    typename                                                                    __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyHasher,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperFunction < __KeyType const &, __ElementType const & >   __keyExtractor,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __KeyType const &, __KeyType const & >    __keyComparator,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: ConsumerFunction < __ElementType & >                          __nodeDestructor    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_cpplang_ConstexprConditioned auto __HashTable <
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

                /* 0 elements -> no node */
                if ( this->__ht_empty() ) {
                    return nullptr;
                }

                /* acquire bucket for the received key and parse it */
                auto pBucketHead = this->__ht_bucket ( this->_hasher ( key ) );
                while ( pBucketHead != nullptr ) {

                    /* if key extracted from bucket node matches the key received */
                    if ( __keyComparator ( __keyExtractor ( pBucketHead->_data ), key ) ) {

                        /* return memory address to the node data */
                        return & pBucketHead->_data;
                    }

                    /* otherwise, forward into bucket */
                    pBucketHead = pBucketHead->_pNext;
                }

                /* bucket parsed, no node found matching the given key. No such key exists, return null */
                return nullptr;
            }


            template <
                    typename                                                                    __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyHasher,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperFunction < __KeyType const &, __ElementType const & >   __keyExtractor,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __KeyType const &, __KeyType const & >    __keyComparator,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: ConsumerFunction < __ElementType & >                          __nodeDestructor    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_MaybeUnused __CDS_OptimalInline auto __HashTable <
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

                /* 'reuse' code from __get, dirty const casts. Theoretically legal */
                return const_cast < __ElementType * > ( static_cast < __HashTable const * > ( this )->__ht_get ( key ) );
            }


            template <
                    typename                                                                    __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyHasher,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperFunction < __KeyType const &, __ElementType const & >   __keyExtractor,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __KeyType const &, __KeyType const & >    __keyComparator,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: ConsumerFunction < __ElementType & >                          __nodeDestructor    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_MaybeUnused __CDS_OptimalInline auto __HashTable <
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

                /* at and get only differ for the non-const versions. const are the same */
                return this->__ht_getConst ( key );
            }


            template <
                    typename                                                                    __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyHasher,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperFunction < __KeyType const &, __ElementType const & >   __keyExtractor,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __KeyType const &, __KeyType const & >    __keyComparator,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: ConsumerFunction < __ElementType & >                          __nodeDestructor    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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

                /* store the old bucket size */
                Size            oldBucketSize = this->_bucketCount;

                /* value of computed local hashes */
                Size            newHash;

                /* pointer used to move nodes during rehash */
                __NodeType    * pToMove;

                /* re-allocate the buckets, increasing the count */
                this->__ht_allocateBuckets ( bucketCount );

                /* parse each bucket */
                for ( Size bucketIndex = 0ULL; bucketIndex < oldBucketSize; ++ bucketIndex ) {

                    /* Acquire the 'old', not updated bucket */
                    /** guaranteed to be lower than newer size, so using the method
                      * with the new greater modulus will not impact the result */
                    auto & oldBucket = this->__ht_bucket ( bucketIndex );

                    /* parse the bucket to clear nodes at the front */
                    while ( oldBucket != nullptr ) {

                        /* if the uninitialized node is in this bucket */
                        if ( pNewEmptyNode == oldBucket ) {

                            /* the 'new' hash, post rehash is the one received as parameter */
                            newHash = hashValueOfNewNode;
                        } else {

                            /* otherwise, recompute the hash from the extracted key */
                            newHash = this->_hasher ( __keyExtractor ( oldBucket->_data ) );
                        }

                        /* acquire the new bucket */
                        auto & newBucket = this->__ht_bucket ( newHash );

                        /* if same bucket, no need to go forward, front remains in current bucket */
                        if ( newBucket == oldBucket ) {
                            break;
                        }

                        /* otherwise, prepare and move node. Advance bucket and Check next node */
                        pToMove     = oldBucket;
                        oldBucket   = oldBucket->_pNext;

                        __HashTable :: __ht_rehashEmplace ( & newBucket, pToMove );
                    }

                    /* First node validated, start parse with lookahead */
                    __NodeType * pOldBucketHead = oldBucket;
                    while ( pOldBucketHead != nullptr && pOldBucketHead->_pNext != nullptr ) {

                        /* same principle, if node is the uninitialized one */
                        if ( pNewEmptyNode == pOldBucketHead->_pNext ) {

                            /* get hash from parameter */
                            newHash = hashValueOfNewNode;
                        } else {

                            /* otherwise, compute from key extracted from node */
                            newHash = this->_hasher ( __keyExtractor ( pOldBucketHead->_pNext->_data ) );
                        }

                        /* acquire the bucket using the recomputed hash */
                        auto & newBucket = this->__ht_bucket ( newHash );

                        /* if same bucket, node remains here. Advance and repeat */
                        if ( newBucket == oldBucket ) {
                            pOldBucketHead = pOldBucketHead->_pNext;
                            continue;
                        }

                        /* otherwise, prepare and move node. Relink current list */
                        pToMove                 = pOldBucketHead->_pNext;
                        pOldBucketHead->_pNext  = pOldBucketHead->_pNext->_pNext;

                        __HashTable :: __ht_rehashEmplace ( & newBucket, pToMove );
                    }
                }
            }


            template <
                    typename                                                                    __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyHasher,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperFunction < __KeyType const &, __ElementType const & >   __keyExtractor,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __KeyType const &, __KeyType const & >    __keyComparator,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: ConsumerFunction < __ElementType & >                          __nodeDestructor    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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

                /* emplace modifies the list, since it adds the new node as a new head */
                pNode->_pNext   = * pBucket;
                * pBucket       = pNode;
            }


            template <
                    typename                                                                    __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyHasher,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperFunction < __KeyType const &, __ElementType const & >   __keyExtractor,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __KeyType const &, __KeyType const & >    __keyComparator,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: ConsumerFunction < __ElementType & >                          __nodeDestructor    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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

                /* function truncates the received hash before acquiring the bucket, applying the correct remainder class */
                return this->_pBucketArray [ hash % this->_bucketCount ];
            }


            template <
                    typename                                                                    __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyHasher,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperFunction < __KeyType const &, __ElementType const & >   __keyExtractor,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __KeyType const &, __KeyType const & >    __keyComparator,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: ConsumerFunction < __ElementType & >                          __nodeDestructor    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_MaybeUnused constexpr auto __HashTable <
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

                /* function truncates the received hash before acquiring the bucket, applying the correct remainder class */
                return this->_pBucketArray [ hash % this->_bucketCount ];
            }


            template <
                    typename                                                                    __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyHasher,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperFunction < __KeyType const &, __ElementType const & >   __keyExtractor,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __KeyType const &, __KeyType const & >    __keyComparator,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: ConsumerFunction < __ElementType & >                          __nodeDestructor    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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

                /* reallocate the bucket array and clear the newly created buckets */
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

                /* update stored bucket count - remainder class */
                this->_bucketCount = bucketCount;
            }


            template <
                    typename                                                                    __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyHasher,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperFunction < __KeyType const &, __ElementType const & >   __keyExtractor,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __KeyType const &, __KeyType const & >    __keyComparator,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: ConsumerFunction < __ElementType & >                          __nodeDestructor    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __HashTable <
                    __ElementType,
                    __KeyType,
                    __KeyHasher,
                    __RehashPolicy,
                    __keyExtractor,
                    __keyComparator,
                    __nodeDestructor
            > :: __ht_freeBuckets () noexcept -> void {

                /* free bucket array and clear bucket count */
                cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray (
                        cds :: exchange (
                                this->_pBucketArray,
                                nullptr
                        )
                );

                this->_bucketCount = 0ULL;
            }


            template <
                    typename                                                                    __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyHasher,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperFunction < __KeyType const &, __ElementType const & >   __keyExtractor,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __KeyType const &, __KeyType const & >    __keyComparator,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: ConsumerFunction < __ElementType & >                          __nodeDestructor    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_OptimalInline auto __HashTable <
                    __ElementType,
                    __KeyType,
                    __KeyHasher,
                    __RehashPolicy,
                    __keyExtractor,
                    __keyComparator,
                    __nodeDestructor
            > :: __ht_allocateNode () noexcept -> __NodeType * {

                /* wrapper for primitive allocation */
                return cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveObject < __NodeType > ();
            }


            template <
                    typename                                                                    __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyHasher,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperFunction < __KeyType const &, __ElementType const & >   __keyExtractor,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __KeyType const &, __KeyType const & >    __keyComparator,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: ConsumerFunction < __ElementType & >                          __nodeDestructor    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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
            ) noexcept -> void {

                /* call data destructor, then free primitive node */
                __nodeDestructor ( pNode->_data );
                cds :: __hidden :: __impl :: __allocation :: __freePrimitiveObject ( pNode );
            }


            template <
                    typename                                                                    __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyHasher,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperFunction < __KeyType const &, __ElementType const & >   __keyExtractor,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __KeyType const &, __KeyType const & >    __keyComparator,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: ConsumerFunction < __ElementType & >                          __nodeDestructor    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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

                /* no elements -> nothing to remove */
                if ( this->__ht_empty() ) {
                    return false;
                }

                __NodeType * pToRemove;
                __NodeType * pBucketHead;

                /* acquire bucket. if key matches the front node key, remove front */
                auto & bucket = this->__ht_bucket ( this->_hasher ( key ) );
                if ( bucket == nullptr ) {
                    return false;
                }

                if ( __keyComparator ( __keyExtractor ( bucket->_data ), key ) ) {

                    pToRemove   = bucket;
                    bucket      = bucket->_pNext;

                    __HashTable :: __ht_freeNode ( pToRemove );

                    -- this->_size;

                    /* removal successful */
                    return true;
                }

                /* otherwise, parse with lookahead to be able to relink list */
                pBucketHead = bucket;
                while ( pBucketHead->_pNext != nullptr ) {

                    /* matching key found, remove and relink */
                    if ( __keyComparator ( __keyExtractor ( pBucketHead->_pNext->_data ), key ) ) {

                        pToRemove           = pBucketHead->_pNext;
                        pBucketHead->_pNext = pBucketHead->_pNext->_pNext;

                        __HashTable :: __ht_freeNode ( pToRemove );

                        -- this->_size;

                        /* removal successful */
                        return true;
                    }

                    /* otherwise, keep checking bucket */
                    pBucketHead = pBucketHead->_pNext;
                }

                /* no removal done - no matching key in nodes found - unsuccessful */
                return false;
            }


            template <
                    typename                                                                    __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyHasher,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperFunction < __KeyType const &, __ElementType const & >   __keyExtractor,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __KeyType const &, __KeyType const & >    __keyComparator,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: ConsumerFunction < __ElementType & >                          __nodeDestructor    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > auto __HashTable <
                    __ElementType,
                    __KeyType,
                    __KeyHasher,
                    __RehashPolicy,
                    __keyExtractor,
                    __keyComparator,
                    __nodeDestructor
            > :: __ht_removeGetPtr (
                    __KeyType const & key
            ) noexcept -> __ElementType * {

                /* no elements -> nothing to remove */
                if ( this->__ht_empty() ) {
                    return nullptr;
                }

                __NodeType    * pToRemove;
                __NodeType    * pBucketHead;
                __ElementType * pOldElement;

                /* acquire bucket. if key matches the front node key, remove front */
                auto & bucket = this->__ht_bucket ( this->_hasher ( key ) );
                if ( bucket == nullptr ) {
                    return nullptr;
                }

                if ( __keyComparator ( __keyExtractor ( bucket->_data ), key ) ) {

                    pToRemove   = bucket;
                    bucket      = bucket->_pNext;
                    pOldElement = & pToRemove->_data;

                    __HashTable :: __ht_freeNode ( pToRemove );

                    -- this->_size;

                    /* removal successful */
                    return pOldElement;
                }

                /* otherwise, parse with lookahead to be able to relink list */
                pBucketHead = bucket;
                while ( pBucketHead->_pNext != nullptr ) {

                    /* matching key found, remove and relink */
                    if ( __keyComparator ( __keyExtractor ( pBucketHead->_pNext->_data ), key ) ) {

                        pToRemove           = pBucketHead->_pNext;
                        pBucketHead->_pNext = pBucketHead->_pNext->_pNext;
                        pOldElement         = & pToRemove->_data;

                        __HashTable :: __ht_freeNode ( pToRemove );

                        -- this->_size;

                        /* removal successful */
                        return pOldElement;
                    }

                    /* otherwise, keep checking bucket */
                    pBucketHead = pBucketHead->_pNext;
                }

                /* no removal done - no matching key in nodes found - unsuccessful */
                return nullptr;
            }


            template <
                    typename                                                                    __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyHasher,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperFunction < __KeyType const &, __ElementType const & >   __keyExtractor,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __KeyType const &, __KeyType const & >    __keyComparator,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: ConsumerFunction < __ElementType & >                          __nodeDestructor    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_MaybeUnused auto __HashTable <
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

                /* if no nodes or index out of bounds, no removal done */
                if ( this->__ht_empty() || bucketIndex >= this->_bucketCount ) {
                    return false;
                }

                /* acquire bucket to compute front check */
                __NodeType  * & pBucket         = this->__ht_bucket ( bucketIndex );

                /* transform immutable to mutable nodes. Dirty, but not-a-const function */
                auto            pPreviousCasted = const_cast < __NodeType * > ( pPreviousNode );
                auto            pCurrentCasted  = const_cast < __NodeType * > ( pCurrentNode );

                if ( pPreviousCasted == nullptr && pCurrentCasted == pBucket ) {

                    /* if front, remove at front and advance bucket */
                    pBucket = pBucket->_pNext;
                    __HashTable :: __ht_freeNode ( pCurrentCasted );

                } else if ( pCurrentCasted != nullptr && pPreviousCasted != nullptr ) {

                    /* otherwise, if from inside the list, remove and relink */
                    pPreviousCasted->_pNext = pCurrentCasted->_pNext;
                    __HashTable :: __ht_freeNode ( pCurrentCasted );

                } else {

                    /* if neither case applies, not a correct remove */
                    return false;
                }

                /* decrease size and return success */
                -- this->_size;
                return true;
            }


            template <
                    typename                                                                    __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyHasher,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperFunction < __KeyType const &, __ElementType const & >   __keyExtractor,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __KeyType const &, __KeyType const & >    __keyComparator,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: ConsumerFunction < __ElementType & >                          __nodeDestructor    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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
                        iterator._pCurrentNode == nullptr && iterator._pPreviousNode == nullptr
                ) {

                    /* if index out of bounds, or iterator list does not exist, or node values are null, cannot remove due to invalid iterator */
                    return false;
                }

                /* otherwise, use node removal function */
                return this->__ht_remove (
                        iterator._pPreviousNode,
                        iterator._pCurrentNode,
                        iterator._bucketIndex
                );
            }


            template <
                    typename                                                                    __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyHasher,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperFunction < __KeyType const &, __ElementType const & >   __keyExtractor,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __KeyType const &, __KeyType const & >    __keyComparator,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: ConsumerFunction < __ElementType & >                          __nodeDestructor    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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
                        iterator._pCurrentNode == nullptr && iterator._pPreviousNode == nullptr
                ) {

                    /* if index out of bounds, or iterator list does not exist, or node values are null, cannot remove due to invalid iterator */
                    return false;
                }

                /* otherwise, use node removal function */
                return this->__ht_remove (
                        iterator._pPreviousNode,
                        iterator._pCurrentNode,
                        iterator._bucketIndex
                );
            }


            template <
                    typename                                                                    __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyHasher,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperFunction < __KeyType const &, __ElementType const & >   __keyExtractor,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __KeyType const &, __KeyType const & >    __keyComparator,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: ConsumerFunction < __ElementType & >                          __nodeDestructor    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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
                    Size                            iteratorCount
            ) noexcept -> Size {

                /* no gain from having a special implementation. call basic iterator remove for all iterators. */
                /* also keep track of removed iterator count */
                Size removedCount = 0ULL;
                for ( Size index = 0ULL; index < iteratorCount; ++ index ) {

                    if ( this->__ht_removeIterator ( * ppIterators [ index ] ) ) {
                        ++ removedCount;
                    }
                }

                return removedCount;
            }


            template <
                    typename                                                                    __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyHasher,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperFunction < __KeyType const &, __ElementType const & >   __keyExtractor,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __KeyType const &, __KeyType const & >    __keyComparator,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: ConsumerFunction < __ElementType & >                          __nodeDestructor    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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
                    Size                                iteratorCount
            ) noexcept -> Size {

                /* no gain from having a special implementation. call basic iterator remove for all iterators. */
                /* also keep track of removed iterator count */
                Size removedCount = 0ULL;
                for ( Size index = 0ULL; index < iteratorCount; ++ index ) {

                    if ( this->__ht_removeIteratorConst ( * ppIterators [ index ] ) ) {
                        ++ removedCount;
                    }
                }

                return removedCount;
            }


            template <
                    typename                                                                    __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyHasher,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperFunction < __KeyType const &, __ElementType const & >   __keyExtractor,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __KeyType const &, __KeyType const & >    __keyComparator,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: ConsumerFunction < __ElementType & >                          __nodeDestructor    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename                                                            __CopyFunction      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_MaybeUnused __CDS_OptimalInline auto __HashTable <
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

                /* self-check */
                if ( this == & table ) {
                    return;
                }

                /* clear and call copyCleared */
                this->__ht_clear();
                this->__ht_copyCleared ( table, copyFunction );
            }


            template <
                    typename                                                                    __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyHasher,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperFunction < __KeyType const &, __ElementType const & >   __keyExtractor,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __KeyType const &, __KeyType const & >    __keyComparator,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: ConsumerFunction < __ElementType & >                          __nodeDestructor    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > template <
                    typename                                                            __CopyFunction      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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

                /* if nothing to copy, do not copy */
                if ( table.__ht_empty() ) {
                    return;
                }

                /* copy size and allocate buckets */
                this->_size = table._size;
                this->__ht_allocateBuckets ( table._bucketCount );

                /* parse each bucket from received table */
                for ( Size bucketIndex = 0ULL; bucketIndex < table._bucketCount; ++ bucketIndex ) {

                    /* acquire the bucket heads */
                    auto & thisBucket   = this->__ht_bucket ( bucketIndex );
                    auto & tableBucket  = table.__ht_bucket ( bucketIndex );

                    /* create parse copy for received table and back for new bucket */
                    __NodeType * pTableHead     = tableBucket;
                    __NodeType * pThisBack      = nullptr;

                    /* parse to the end */
                    while ( pTableHead != nullptr ) {

                        /* create a new node, initialize the memory using the copy function */
                        auto pNewNode       = __HashTable :: __ht_allocateNode ();
                        pNewNode->_pNext    = nullptr;
                        copyFunction ( pNewNode->_data, pTableHead->_data );

                        /* advance other table bucket */
                        pTableHead = pTableHead->_pNext;

                        /* push back in new bucket. If no back, skip. otherwise, link to previous back */
                        if ( pThisBack == nullptr ) {
                            thisBucket          = pNewNode;
                        } else {
                            pThisBack->_pNext   = pNewNode;
                        }

                        /* store new back */
                        pThisBack = pNewNode;
                    }
                }

                /* also copy the rehash policy values. */
                this->_rehash = table._rehash;
            }


            template <
                    typename                                                                    __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyHasher,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperFunction < __KeyType const &, __ElementType const & >   __keyExtractor,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __KeyType const &, __KeyType const & >    __keyComparator,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: ConsumerFunction < __ElementType & >                          __nodeDestructor    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_MaybeUnused __CDS_OptimalInline auto __HashTable <
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

                /* self-check */
                if ( this == & table ) {
                    return;
                }

                /* clear and call moveCleared */
                this->__ht_clear();
                this->__ht_moveCleared ( std :: move ( table ) );
            }


            template <
                    typename                                                                    __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyHasher,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperFunction < __KeyType const &, __ElementType const & >   __keyExtractor,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __KeyType const &, __KeyType const & >    __keyComparator,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: ConsumerFunction < __ElementType & >                          __nodeDestructor    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_cpplang_NonConstConstexprMemberFunction auto __HashTable <
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

                /* acquire and release every component. Move rehash and hasher, others exchange for defaults */
                this->_pBucketArray = cds :: exchange ( table._pBucketArray, nullptr );
                this->_bucketCount  = cds :: exchange ( table._bucketCount, 0ULL );
                this->_size         = cds :: exchange ( table._size, 0ULL );
                this->_rehash       = std :: move ( table._rehash );
                this->_hasher       = std :: move ( table._hasher );
            }


            template <
                    typename                                                                    __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyHasher,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperFunction < __KeyType const &, __ElementType const & >   __keyExtractor,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __KeyType const &, __KeyType const & >    __keyComparator,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: ConsumerFunction < __ElementType & >                          __nodeDestructor    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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

                /* if no elements, return end iterator */
                if ( this->__ht_empty() ) {
                    return this->__ht_end ();
                }

                /* acquire bucket index directly, used by iterator */
                Size bucketIndex = this->_hasher ( key ) % this->_bucketCount;

                if ( bucketIndex >= this->_bucketCount ) {
                    return this->__ht_end();
                }

                /* store the previous and current values used in initialization */
                __NodeType * pPrevious  = nullptr;
                __NodeType * pCurrent   = this->_pBucketArray [ bucketIndex ];

                /* while bucket has elements */
                while ( pCurrent != nullptr ) {

                    /* compare extracted node key with received key */
                    if ( __keyComparator ( __keyExtractor ( pCurrent->_data ), key ) ) {

                        /* if matching, compose and return iterator */
                        return __ht_Iterator (
                                this->_pBucketArray,
                                this->_bucketCount,
                                pCurrent,
                                pPrevious,
                                bucketIndex
                        );
                    }

                    /* otherwise, advance iteration */
                    pPrevious   = pCurrent;
                    pCurrent    = pCurrent->_pNext;
                }

                /* if no matching node found, return end iterator */
                return this->__ht_end ();
            }


            template <
                    typename                                                                    __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __KeyHasher,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                    __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperFunction < __KeyType const &, __ElementType const & >   __keyExtractor,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __KeyType const &, __KeyType const & >    __keyComparator,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: ConsumerFunction < __ElementType & >                          __nodeDestructor    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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

                /* if no elements, return end iterator */
                if ( this->__ht_empty() ) {
                    return this->__ht_cend ();
                }

                /* acquire bucket index directly, used by iterator */
                Size bucketIndex = this->_hasher ( key ) % this->_bucketCount;

                if ( bucketIndex >= this->_bucketCount ) {
                    return this->__ht_cend();
                }

                /* store the previous and current values used in initialization */
                __NodeType const * pPrevious  = nullptr;
                __NodeType const * pCurrent   = this->_pBucketArray [ bucketIndex ];

                /* while bucket has elements */
                while ( pCurrent != nullptr ) {

                    /* compare extracted node key with received key */
                    if ( __keyComparator ( __keyExtractor ( pCurrent->_data ), key ) ) {

                        /* if matching, compose and return iterator */
                        return __ht_ConstIterator (
                                this->_pBucketArray,
                                this->_bucketCount,
                                pCurrent,
                                pPrevious,
                                bucketIndex
                        );
                    }

                    /* otherwise, advance iteration */
                    pPrevious   = pCurrent;
                    pCurrent    = pCurrent->_pNext;
                }

                /* if no matching node found, return end iterator */
                return this->__ht_cend ();
            }


            template <
                    typename                                                                            __ElementType,      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                            __KeyType,          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                            __KeyHasher,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename                                                                            __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: MapperFunction < __KeyType const &, __ElementType const & >           __keyExtractor,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: PredicateFunction < __KeyType const &, __KeyType const & >            __keyComparator,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    functional :: ConsumerFunction < __ElementType & >                                  __nodeDestructor    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > __CDS_cpplang_ConstexprConditioned auto __HashTable <
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

                /* self check */
                if ( this == & table ) {
                    return true;
                }

                /* if this is empty, return if other is also empty */
                if ( this->__ht_empty() ) {
                    return table.__ht_empty();
                }

                /* if other is empty or bucket counts are different, not equal */
                if ( table.__ht_empty() || this->_bucketCount != table._bucketCount ) {
                    return false;
                }

                /* otherwise, neither are empty, and have same bucket count. parse buckets */
                for ( Size bucketIndex = 0ULL; bucketIndex < this->_bucketCount; ++ bucketIndex ) {

                    /* parse buckets synchronously */
                    auto pThisBucketHead    = this->_pBucketArray [ bucketIndex ];
                    auto pOtherBucketHead   = table._pBucketArray [ bucketIndex ];

                    /* while both have elements */
                    while ( pThisBucketHead != nullptr && pOtherBucketHead != nullptr ) {

                        /* if a node difference is found ( not key, element comparison ) */
                        if ( ! __keyComparator ( __keyExtractor (pThisBucketHead->_data), __keyExtractor (pOtherBucketHead->_data) ) ) {

                            /* tables are not equal */
                            return false;
                        }
                    }

                    /* if any bucket still has elements, not equal buckets, not equal tables */
                    if ( pThisBucketHead != nullptr || pOtherBucketHead != nullptr ) {
                        return false;
                    }
                }

                /* all buckets parsed and no difference found, tables are equal */
                return true;
            }

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_SHARED_HASH_TABLE_IMPL_HPP__ */
