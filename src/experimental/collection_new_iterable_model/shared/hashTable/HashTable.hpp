/*
 * Created by loghin on 27/07/22.
 */

#ifndef __CDS_EX_SHARED_HASH_TABLE_HPP__
#define __CDS_EX_SHARED_HASH_TABLE_HPP__ /* NOLINT(bugprone-reserved-identifier) */

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
                > class __HashTable {                                                                           /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    using ElementType           = __ElementType;    /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    using KeyType               = __KeyType;        /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    using KeyHasher             = __KeyHasher;      /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    using RehashPolicy          = __RehashPolicy;   /* NOLINT(bugprone-reserved-identifier) */

                public:
                    using __ht_Iterator         = HashTableIterator < __ElementType >;      /* NOLINT(bugprone-reserved-identifier) */

                public:
                    using __ht_ConstIterator    = HashTableConstIterator < __ElementType >; /* NOLINT(bugprone-reserved-identifier) */

                public:
                    template < typename __ServerType >  /* NOLINT(bugprone-reserved-identifier) */
                    class __SetDispatcher;              /* NOLINT(bugprone-reserved-identifier) */

                public:
                    template < typename __ServerType >  /* NOLINT(bugprone-reserved-identifier) */
                    class __MapDispatcher;              /* NOLINT(bugprone-reserved-identifier) */

                private:
                    using __NodeType    = cds :: __hidden :: __impl :: __UnidirectionalNode < __ElementType >; /* NOLINT(bugprone-reserved-identifier) */

                private:
                    Size                                    _bucketCount    { 0ULL };

                private:
                    Size                                    _size           { 0ULL };

                private:
                    __NodeType                           ** _pBucketArray   { nullptr };

                private:
                    __CDS_NoUniqueAddress __KeyHasher       _hasher;

                private:
                    __CDS_NoUniqueAddress __RehashPolicy    _rehash;

                protected:
                    constexpr __HashTable() noexcept;

                protected:
                    __CDS_Explicit constexpr __HashTable (
                            __KeyHasher const & keyHasher
                    ) noexcept;

                protected:
                    __CDS_Explicit constexpr __HashTable (
                            __RehashPolicy const & rehashPolicy
                    ) noexcept;

                protected:
                    constexpr __HashTable (
                            __KeyHasher     const & keyHasher,
                            __RehashPolicy  const & rehashPolicy
                    ) noexcept;

                protected:
                    template <
                            typename __CopyFunction /* NOLINT(bugprone-reserved-identifier) */
                    > __CDS_Implicit __HashTable (  /* NOLINT(google-explicit-constructor) */
                            __HashTable     const & hashTable,
                            __CopyFunction  const & copyFunction
                    ) noexcept;

                protected:
                    constexpr __HashTable (
                            __HashTable && hashTable
                    ) noexcept;

                protected:
                    auto __ht_clear () noexcept -> void;    /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    __CDS_NoDiscard constexpr auto __ht_size () const noexcept -> Size;  /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    __CDS_NoDiscard constexpr auto __ht_empty () const noexcept -> bool;    /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    __CDS_NoDiscard constexpr auto __ht_bucketCount () const noexcept -> Size;  /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __ht_begin () noexcept -> __ht_Iterator; /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __ht_end () noexcept -> __ht_Iterator;   /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    __CDS_NoDiscard constexpr auto __ht_cbegin () const noexcept -> __ht_ConstIterator; /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    __CDS_NoDiscard constexpr auto __ht_cend () const noexcept -> __ht_ConstIterator;   /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    __CDS_NoDiscard auto __ht_new ( /* NOLINT(bugprone-reserved-identifier) */
                            __ElementType const * pReferenceElement,
                            bool                * pIsNew
                    ) noexcept -> __ElementType *;

                protected:
                    __CDS_NoDiscard auto __ht_get ( /* NOLINT(bugprone-reserved-identifier) */
                            __KeyType const & key,
                            bool            * pIsNew
                    ) noexcept -> __ElementType *;

                protected:
                    __CDS_NoDiscard auto __ht_getConst (    /* NOLINT(bugprone-reserved-identifier) */
                            __KeyType const & key
                    ) const noexcept -> __ElementType const *;

                protected:
                    __CDS_NoDiscard auto __ht_at (                         /* NOLINT(bugprone-reserved-identifier) */
                            __KeyType const & key
                    ) noexcept -> __ElementType *;

                protected:
                    __CDS_NoDiscard auto __ht_atConst (                         /* NOLINT(bugprone-reserved-identifier) */
                            __KeyType const & key
                    ) const noexcept -> __ElementType const *;

                private:
                    auto __ht_rehash (                     /* NOLINT(bugprone-reserved-identifier) */
                            Size                bucketCount,
                            Size                hashValueOfNewNode,
                            __NodeType  const * pNewEmptyNode
                    ) noexcept -> void;

                private:
                    static auto __ht_rehashEmplace (       /* NOLINT(bugprone-reserved-identifier) */
                            __NodeType ** pBucket,
                            __NodeType  * pNode
                    ) noexcept -> void;

                private:
                    __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto __ht_bucket (                                             /* NOLINT(bugprone-reserved-identifier) */
                            Size hash
                    ) noexcept -> __NodeType * &;

                private:
                    __CDS_NoDiscard constexpr auto __ht_bucket (                                             /* NOLINT(bugprone-reserved-identifier) */
                            Size hash
                    ) const noexcept -> __NodeType * const &;

                private:
                    auto __ht_allocateBuckets (                                    /* NOLINT(bugprone-reserved-identifier) */
                            Size bucketCount
                    ) noexcept -> void;

                private:
                    auto __ht_freeBuckets () noexcept -> void;                     /* NOLINT(bugprone-reserved-identifier) */

                private:
                    __CDS_NoDiscard auto __ht_allocateNode () const noexcept -> __NodeType *;      /* NOLINT(bugprone-reserved-identifier) */

                private:
                    auto __ht_freeNode (                                           /* NOLINT(bugprone-reserved-identifier) */
                            __NodeType * pNode
                    ) const noexcept -> void;

                protected:
                    auto __ht_remove (                                             /* NOLINT(bugprone-reserved-identifier) */
                            __KeyType const & key
                    ) noexcept -> bool;

                private:
                    auto __ht_remove (                                             /* NOLINT(bugprone-reserved-identifier) */
                            __NodeType  const * pPreviousNode,
                            __NodeType  const * pCurrentNode,
                            Size                bucketIndex
                    ) noexcept -> bool;

                protected:
                    auto __ht_removeIterator (                                             /* NOLINT(bugprone-reserved-identifier) */
                            __ht_Iterator const & iterator
                    ) noexcept -> bool;

                protected:
                    auto __ht_removeIteratorConst (                                         /* NOLINT(bugprone-reserved-identifier) */
                            __ht_ConstIterator const & iterator
                    ) noexcept -> bool;

                protected:
                    auto __ht_removeIteratorArray (                                             /* NOLINT(bugprone-reserved-identifier) */
                            __ht_Iterator   const * const * ppIterators,
                            Size                            iteratorArrayCount
                    ) noexcept -> Size;

                protected:
                    auto __ht_removeConstIteratorArray (                                         /* NOLINT(bugprone-reserved-identifier) */
                            __ht_ConstIterator  const * const * ppIterators,
                            Size                                iteratorArrayCount
                    ) noexcept -> Size;

                protected:
                    template <
                            typename __CopyFunction     /* NOLINT(bugprone-reserved-identifier) */
                    > auto __ht_copy (                  /* NOLINT(bugprone-reserved-identifier) */
                            __HashTable     const & table,
                            __CopyFunction  const & copyFunction
                    ) noexcept -> void;

                protected:
                    template <
                            typename __CopyFunction     /* NOLINT(bugprone-reserved-identifier) */
                    > auto __ht_copyCleared (           /* NOLINT(bugprone-reserved-identifier) */
                            __HashTable     const & table,
                            __CopyFunction  const & copyFunction
                    ) noexcept -> void;

                protected:
                    auto __ht_move (    /* NOLINT(bugprone-reserved-identifier) */
                            __HashTable && table
                    ) noexcept -> void;

                protected:
                    __CDS_cpplang_NonConstConstexprMemberFunction auto __ht_moveCleared (   /* NOLINT(bugprone-reserved-identifier) */
                            __HashTable && table
                    ) noexcept -> void;

                protected:
                    __CDS_NoDiscard auto __ht_findIterator ( /* NOLINT(bugprone-reserved-identifier) */
                            __KeyType const & key
                    ) noexcept -> __ht_Iterator;

                protected:
                    __CDS_NoDiscard auto __ht_findIteratorConst ( /* NOLINT(bugprone-reserved-identifier) */
                            __KeyType const & key
                    ) const noexcept -> __ht_ConstIterator;

                protected:
                    template <
                            cds :: utility :: ComparisonFunction < __ElementType > __comparator /* NOLINT(bugprone-reserved-identifier) */
                    > __CDS_NoDiscard auto __ht_equals (                                        /* NOLINT(bugprone-reserved-identifier) */
                            __HashTable const & table
                    ) const noexcept -> bool;
                };

            }
        }
    }
}

#endif /* __CDS_EX_SHARED_HASH_TABLE_HPP__ */

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

#if defined ( __CDS_SHARED_SET_SERVER_DISPATCHER_HPP__ ) && ! defined ( __CDS_SHARED_HASH_TABLE_SET_SERVER_DISPATCHER_HPP__ ) && defined (__CDS_EX_SHARED_HASH_TABLE_HPP__)
#define __CDS_SHARED_HASH_TABLE_SET_SERVER_DISPATCHER_HPP__ /* NOLINT(bugprone-reserved-identifier) */

                template <
                        typename                                                            __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyHasher,        /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __KeyType >                  __keyComparator,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename                                                            __ServerType        /* NOLINT(bugprone-reserved-identifier) */
                > class __HashTable <
                        __ElementType,
                        __KeyType,
                        __KeyHasher,
                        __RehashPolicy,
                        __keyExtractor,
                        __keyComparator,
                        __nodeDestructor
                > :: __SetDispatcher :
                        public __SetServerDispatcher <
                                __ServerType,
                                __HashTable <
                                        __ElementType,
                                        __KeyType,
                                        __KeyHasher,
                                        __RehashPolicy,
                                        __keyExtractor,
                                        __keyComparator,
                                        __nodeDestructor
                                >,
                                __ElementType,
                                HashTableConstIterator < __ElementType >,
                                HashTableConstIterator < __ElementType >,
                                & __HashTable <
                                        __ElementType,
                                        __KeyType,
                                        __KeyHasher,
                                        __RehashPolicy,
                                        __keyExtractor,
                                        __keyComparator,
                                        __nodeDestructor
                                > :: __ht_cbegin,
                                & __HashTable <
                                        __ElementType,
                                        __KeyType,
                                        __KeyHasher,
                                        __RehashPolicy,
                                        __keyExtractor,
                                        __keyComparator,
                                        __nodeDestructor
                                > :: __ht_cend,
                                & __HashTable <
                                        __ElementType,
                                        __KeyType,
                                        __KeyHasher,
                                        __RehashPolicy,
                                        __keyExtractor,
                                        __keyComparator,
                                        __nodeDestructor
                                > :: __ht_new,
                                & __HashTable <
                                        __ElementType,
                                        __KeyType,
                                        __KeyHasher,
                                        __RehashPolicy,
                                        __keyExtractor,
                                        __keyComparator,
                                        __nodeDestructor
                                > :: __ht_removeIteratorConst,
                                & __HashTable <
                                        __ElementType,
                                        __KeyType,
                                        __KeyHasher,
                                        __RehashPolicy,
                                        __keyExtractor,
                                        __keyComparator,
                                        __nodeDestructor
                                > :: __ht_removeConstIteratorArray,
                                & __HashTable <
                                        __ElementType,
                                        __KeyType,
                                        __KeyHasher,
                                        __RehashPolicy,
                                        __keyExtractor,
                                        __keyComparator,
                                        __nodeDestructor
                                > :: __ht_findIteratorConst
                        > {};

#endif


#if defined ( __CDS_SHARED_MAP_SERVER_DISPATCHER_HPP__ ) && ! defined ( __CDS_SHARED_HASH_TABLE_SERVER_DISPATCHER_HPP__ ) && defined (__CDS_EX_SHARED_HASH_TABLE_HPP__)
#define __CDS_SHARED_HASH_TABLE_SERVER_DISPATCHER_HPP__ /* NOLINT(bugprone-reserved-identifier) */

                template <
                        typename                                                            __ElementType,      /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyHasher,        /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __RehashPolicy,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __KeyType >                  __keyComparator,    /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename                                                            __ServerType        /* NOLINT(bugprone-reserved-identifier) */
                > class __HashTable <
                        __ElementType,
                        __KeyType,
                        __KeyHasher,
                        __RehashPolicy,
                        __keyExtractor,
                        __keyComparator,
                        __nodeDestructor
                > :: __MapDispatcher :
                        public __MapServerDispatcher <
                                __ServerType,
                                __HashTable <
                                        __ElementType,
                                        __KeyType,
                                        __KeyHasher,
                                        __RehashPolicy,
                                        __keyExtractor,
                                        __keyComparator,
                                        __nodeDestructor
                                >,
                                __ElementType,
                                __KeyType,
                                HashTableIterator < __ElementType >,
                                HashTableConstIterator < __ElementType >,
                                HashTableIterator < __ElementType >,
                                HashTableConstIterator < __ElementType >,
                                & __HashTable <
                                        __ElementType,
                                        __KeyType,
                                        __KeyHasher,
                                        __RehashPolicy,
                                        __keyExtractor,
                                        __keyComparator,
                                        __nodeDestructor
                                > :: __ht_begin,
                                & __HashTable <
                                        __ElementType,
                                        __KeyType,
                                        __KeyHasher,
                                        __RehashPolicy,
                                        __keyExtractor,
                                        __keyComparator,
                                        __nodeDestructor
                                > :: __ht_end,
                                & __HashTable <
                                        __ElementType,
                                        __KeyType,
                                        __KeyHasher,
                                        __RehashPolicy,
                                        __keyExtractor,
                                        __keyComparator,
                                        __nodeDestructor
                                > :: __ht_cbegin,
                                & __HashTable <
                                        __ElementType,
                                        __KeyType,
                                        __KeyHasher,
                                        __RehashPolicy,
                                        __keyExtractor,
                                        __keyComparator,
                                        __nodeDestructor
                                > :: __ht_cend,
                                & __HashTable <
                                        __ElementType,
                                        __KeyType,
                                        __KeyHasher,
                                        __RehashPolicy,
                                        __keyExtractor,
                                        __keyComparator,
                                        __nodeDestructor
                                > :: __ht_new,
                                & __HashTable <
                                        __ElementType,
                                        __KeyType,
                                        __KeyHasher,
                                        __RehashPolicy,
                                        __keyExtractor,
                                        __keyComparator,
                                        __nodeDestructor
                                > :: __ht_removeIterator,
                                & __HashTable <
                                        __ElementType,
                                        __KeyType,
                                        __KeyHasher,
                                        __RehashPolicy,
                                        __keyExtractor,
                                        __keyComparator,
                                        __nodeDestructor
                                > :: __ht_removeIteratorConst,
                                & __HashTable <
                                        __ElementType,
                                        __KeyType,
                                        __KeyHasher,
                                        __RehashPolicy,
                                        __keyExtractor,
                                        __keyComparator,
                                        __nodeDestructor
                                > :: __ht_removeIteratorArray,
                                & __HashTable <
                                        __ElementType,
                                        __KeyType,
                                        __KeyHasher,
                                        __RehashPolicy,
                                        __keyExtractor,
                                        __keyComparator,
                                        __nodeDestructor
                                > :: __ht_removeConstIteratorArray,
                                & __HashTable <
                                        __ElementType,
                                        __KeyType,
                                        __KeyHasher,
                                        __RehashPolicy,
                                        __keyExtractor,
                                        __keyComparator,
                                        __nodeDestructor
                                > :: __ht_findIterator,
                                & __HashTable <
                                        __ElementType,
                                        __KeyType,
                                        __KeyHasher,
                                        __RehashPolicy,
                                        __keyExtractor,
                                        __keyComparator,
                                        __nodeDestructor
                                > :: __ht_findIteratorConst
                        > {};

#endif

            }
        }
    }
}
