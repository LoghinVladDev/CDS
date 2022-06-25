//
// Created by loghin on 6/22/2022.
//

#ifndef __CDS_SHARED_HASH_TABLE_ITERATOR_HPP__
#define __CDS_SHARED_HASH_TABLE_ITERATOR_HPP__

namespace cds {             // NOLINT(modernize-concat-nested-namespaces)
    namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
        namespace __impl {  // NOLINT(bugprone-reserved-identifier)

            template <
                    typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                    typename __KeyType,                 // NOLINT(bugprone-reserved-identifier)
                    typename __KeyExtractor,            // NOLINT(bugprone-reserved-identifier)
                    typename __KeyEqualsComparator,     // NOLINT(bugprone-reserved-identifier)
                    typename __KeyHasher,               // NOLINT(bugprone-reserved-identifier)
                    typename __RehashPolicy,            // NOLINT(bugprone-reserved-identifier)
                    typename __ElementTypeDestruct      // NOLINT(bugprone-reserved-identifier)
            > class __HashTable <
                    __ElementType,
                    __KeyType,
                    __KeyExtractor,
                    __KeyEqualsComparator,
                    __KeyHasher,
                    __RehashPolicy,
                    __ElementTypeDestruct
            > :: HashTableIterator {

            private:
                using HashTable = __HashTable <
                        __ElementType,
                        __KeyType,
                        __KeyExtractor,
                        __KeyEqualsComparator,
                        __KeyHasher,
                        __RehashPolicy,
                        __ElementTypeDestruct
                >;

            private:
                __CDS_cpplang_ConstexprConditioned auto advanceBucket () noexcept -> void;

            private:
                HashTable     * _pTable { nullptr };

            private:
                __DataNode    * _pCurrentNode { nullptr };

            private:
                Size            _bucketIndex { 0ULL };

            public:
                constexpr HashTableIterator () noexcept;

            public:
                __CDS_Explicit __CDS_cpplang_ConstexprConditioned HashTableIterator (
                        HashTable * pTable
                ) noexcept;

            public:
                __CDS_Explicit constexpr HashTableIterator (
                        HashTable     * pTable,
                        __DataNode    * pCurrentNode,
                        Size            bucketIndex
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
                __CDS_NoDiscard constexpr auto bucketIndex () const noexcept -> Size;

            public:
                __CDS_NoDiscard constexpr auto currentNode () const noexcept -> __DataNode *;

            public:
                __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> HashTableIterator &;

            public:
                constexpr auto operator * () const noexcept -> HashTable :: ElementType &;

            public:
                constexpr auto operator == (
                        HashTableIterator const & iterator
                ) const noexcept -> bool;

            public:
                constexpr auto operator != (
                        HashTableIterator const & iterator
                ) const noexcept -> bool;

            public:
                __CDS_NoDiscard __CDS_Explicit constexpr operator bool () const noexcept;
            };

        }
    }
}

#endif // __CDS_SHARED_HASH_TABLE_ITERATOR_HPP__
