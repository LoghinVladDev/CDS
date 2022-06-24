//
// Created by loghin on 6/22/2022.
//

#ifndef __CDS_HASH_TABLE_CONST_ITERATOR_HPP__
#define __CDS_HASH_TABLE_CONST_ITERATOR_HPP__

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
            > :: HashTableConstIterator {

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
                HashTable   const * _pTable { nullptr };

            private:
                __DataNode  const * _pCurrentNode { nullptr };

            private:
                Size                _bucketIndex { 0ULL };

            public:
                __CDS_cpplang_ConstexprConditioned HashTableConstIterator () noexcept;

            public:
                __CDS_Explicit constexpr HashTableConstIterator (
                        HashTable const * pTable
                ) noexcept;

            public:
                __CDS_cpplang_ConstexprConditioned HashTableConstIterator (
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
                __CDS_NoDiscard constexpr auto bucketIndex () const noexcept -> Size;

            public:
                __CDS_NoDiscard constexpr auto currentNode () const noexcept -> __DataNode const *;

            public:
                __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> HashTableConstIterator &;

            public:
                constexpr auto operator * () const noexcept -> HashTable :: ElementType const &;

            public:
                constexpr auto operator == (
                        HashTableConstIterator const & iterator
                ) const noexcept -> bool;

            public:
                constexpr auto operator != (
                        HashTableConstIterator const & iterator
                ) const noexcept -> bool;

            public:
                __CDS_NoDiscard __CDS_Explicit constexpr operator bool () const noexcept;
            };

        }
    }
}

#endif // __CDS_HASH_TABLE_CONST_ITERATOR_HPP__
