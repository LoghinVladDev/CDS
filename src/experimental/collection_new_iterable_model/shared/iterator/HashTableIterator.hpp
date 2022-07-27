//
// Created by loghin on 27/07/22.
//

#ifndef __CDS_SHARED_HASH_TABLE_ITERATOR_HPP__
#define __CDS_SHARED_HASH_TABLE_ITERATOR_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ElementType,                                             // NOLINT(bugprone-reserved-identifier)
                        typename __KeyType,                                                 // NOLINT(bugprone-reserved-identifier)
                        typename,
                        typename,
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >,
                        cds :: utility :: ComparisonFunction < __ElementType >,
                        cds :: utility :: DestructorFunction < __ElementType >
                > class __HashTable;                                                        // NOLINT(bugprone-reserved-identifier)

            }
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        class HashTableIterator : public meta :: ForwardIterator {

        private:
            template <
                    typename                                                            __TElementType,     // NOLINT(bugprone-reserved-identifier)
                    typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier)
                    typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier)
                    typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier)
                    cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     // NOLINT(bugprone-reserved-identifier)
                    cds :: utility :: ComparisonFunction < __ElementType >              __keyComparator,    // NOLINT(bugprone-reserved-identifier)
                    cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    // NOLINT(bugprone-reserved-identifier)
            > friend class cds :: experimental :: __hidden :: __impl :: __HashTable;                        // NOLINT(bugprone-reserved-identifier)

        private:
            using DataNode = cds :: __hidden :: __impl :: __UnidirectionalNode < __ElementType >;

        private:
            Size        _bucketIndex    { 0ULL };

        private:
            Size        _bucketCount    { 0ULL };

        private:
            DataNode  * _pCurrentNode   { nullptr };

        private:
            DataNode  * _pPreviousNode  { nullptr };

        private:
            DataNode ** _pListArray     { nullptr };

        public:
            constexpr HashTableIterator () noexcept;

        public:
            __CDS_cpplang_ConstexprConditioned HashTableIterator (
                    DataNode ** pListArray,
                    Size        bucketCount
            ) noexcept;

        public:
            __CDS_cpplang_ConstexprConditioned HashTableIterator (
                    DataNode ** pListArray,
                    Size        bucketCount,
                    DataNode  * pCurrentNode,
                    DataNode  * pPreviousNode,
                    Size        bucketIndex
            ) noexcept;

        public:
            constexpr HashTableIterator (
                    HashTableIterator const & iterator
            ) noexcept;

        public:
            constexpr HashTableIterator (
                    HashTableIterator && iterator
            ) noexcept;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                    HashTableIterator const & iterator
            ) noexcept -> HashTableIterator &;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                    HashTableIterator && iterator
            ) noexcept -> HashTableIterator &;

        public:
            __CDS_NoDiscard constexpr auto listArray () const noexcept -> DataNode **;

        public:
            __CDS_NoDiscard constexpr auto bucketCount () const noexcept -> Size;

        public:
            __CDS_NoDiscard constexpr auto bucketIndex () const noexcept -> Size;

        public:
            __CDS_NoDiscard constexpr auto currentNode () const noexcept -> DataNode *;

        public:
            __CDS_NoDiscard constexpr auto previousNode () const noexcept -> DataNode *;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> HashTableIterator &;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ (int) noexcept -> HashTableIterator;

        public:
            __CDS_NoDiscard constexpr auto operator * () const noexcept -> __ElementType &;

        public:
            __CDS_NoDiscard constexpr auto operator -> () const noexcept -> __ElementType *;

        public:
            __CDS_NoDiscard constexpr auto operator != (
                    HashTableIterator const & iterator
            ) const noexcept -> bool;

        public:
            __CDS_NoDiscard constexpr auto operator == (
                    HashTableIterator const & iterator
            ) const noexcept -> bool;

        public:
            __CDS_NoDiscard __CDS_Explicit constexpr operator bool () const noexcept;
        };


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        class HashTableConstIterator : public meta :: ForwardIterator {

        private:
            template <
                    typename                                                            __TElementType,     // NOLINT(bugprone-reserved-identifier)
                    typename                                                            __KeyType,          // NOLINT(bugprone-reserved-identifier)
                    typename                                                            __KeyHasher,        // NOLINT(bugprone-reserved-identifier)
                    typename                                                            __RehashPolicy,     // NOLINT(bugprone-reserved-identifier)
                    cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,     // NOLINT(bugprone-reserved-identifier)
                    cds :: utility :: ComparisonFunction < __ElementType >              __keyComparator,    // NOLINT(bugprone-reserved-identifier)
                    cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor    // NOLINT(bugprone-reserved-identifier)
            > friend class cds :: experimental :: __hidden :: __impl :: __HashTable;                        // NOLINT(bugprone-reserved-identifier)

        private:
            using DataNode = cds :: __hidden :: __impl :: __UnidirectionalNode < __ElementType >;

        private:
            Size                        _bucketIndex    { 0ULL };

        private:
            Size                        _bucketCount    { 0ULL };

        private:
            DataNode            const * _pCurrentNode   { nullptr };

        private:
            DataNode            const * _pPreviousNode  { nullptr };

        private:
            DataNode    const * const * _pListArray     { nullptr };

        public:
            constexpr HashTableConstIterator () noexcept;

        public:
            __CDS_cpplang_ConstexprConditioned HashTableConstIterator (
                    DataNode    const * const * pListArray,
                    Size                        bucketCount
            ) noexcept;

        public:
            __CDS_cpplang_ConstexprConditioned HashTableConstIterator (
                    DataNode    const * const * pListArray,
                    Size                        bucketCount,
                    DataNode            const * pCurrentNode,
                    DataNode            const * pPreviousNode,
                    Size                        bucketIndex
            ) noexcept;

        public:
            constexpr HashTableConstIterator (
                    HashTableConstIterator const & iterator
            ) noexcept;

        public:
            constexpr HashTableConstIterator (
                    HashTableConstIterator && iterator
            ) noexcept;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                    HashTableConstIterator const & iterator
            ) noexcept -> HashTableConstIterator &;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                    HashTableConstIterator && iterator
            ) noexcept -> HashTableConstIterator &;

        public:
            __CDS_NoDiscard constexpr auto listArray () const noexcept -> DataNode const * const *;

        public:
            __CDS_NoDiscard constexpr auto bucketCount () const noexcept -> Size;

        public:
            __CDS_NoDiscard constexpr auto bucketIndex () const noexcept -> Size;

        public:
            __CDS_NoDiscard constexpr auto currentNode () const noexcept -> DataNode const *;

        public:
            __CDS_NoDiscard constexpr auto previousNode () const noexcept -> DataNode const *;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> HashTableConstIterator &;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ (int) noexcept -> HashTableConstIterator;

        public:
            __CDS_NoDiscard constexpr auto operator * () const noexcept -> __ElementType &;

        public:
            __CDS_NoDiscard constexpr auto operator -> () const noexcept -> __ElementType *;

        public:
            __CDS_NoDiscard constexpr auto operator != (
                    HashTableConstIterator const & iterator
            ) const noexcept -> bool;

        public:
            __CDS_NoDiscard constexpr auto operator == (
                    HashTableConstIterator const & iterator
            ) const noexcept -> bool;

        public:
            __CDS_NoDiscard __CDS_Explicit constexpr operator bool () const noexcept;
        };

    }
}

#endif // __CDS_SHARED_HASH_TABLE_ITERATOR_HPP__
