//
// Created by loghin on 6/22/2022.
//

#ifndef __CDS_SHARED_HASH_TABLE_CONST_ITERATOR_IMPL_HPP__
#define __CDS_SHARED_HASH_TABLE_CONST_ITERATOR_IMPL_HPP__

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
            > __CDS_cpplang_ConstexprConditioned auto __HashTable <
                    __ElementType,
                    __KeyType,
                    __KeyExtractor,
                    __KeyEqualsComparator,
                    __KeyHasher,
                    __RehashPolicy,
                    __ElementTypeDestruct
            > :: HashTableConstIterator :: advanceBucket () noexcept -> void {

                while ( this->_pCurrentNode == nullptr && this->_bucketIndex + 1ULL < this->_pTable->_bucketArray._size ) {
                    this->_pCurrentNode = this->_pTable->_bucketArray._pArray [ ++ this->_bucketIndex ];
                }

                if ( this->_bucketIndex + 1ULL == this->_pTable->_bucketArray._size && this->_pCurrentNode == nullptr ) {
                    ++ this->_bucketIndex;
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
            > :: HashTableConstIterator :: HashTableConstIterator () noexcept = default;


            template <
                    typename __ElementType,         // NOLINT(bugprone-reserved-identifier)
                    typename __KeyType,             // NOLINT(bugprone-reserved-identifier)
                    typename __KeyExtractor,        // NOLINT(bugprone-reserved-identifier)
                    typename __KeyEqualsComparator, // NOLINT(bugprone-reserved-identifier)
                    typename __KeyHasher,           // NOLINT(bugprone-reserved-identifier)
                    typename __RehashPolicy,        // NOLINT(bugprone-reserved-identifier)
                    typename __ElementTypeDestruct  // NOLINT(bugprone-reserved-identifier)
            > __CDS_cpplang_ConstexprConditioned __HashTable <
                    __ElementType,
                    __KeyType,
                    __KeyExtractor,
                    __KeyEqualsComparator,
                    __KeyHasher,
                    __RehashPolicy,
                    __ElementTypeDestruct
            > :: HashTableConstIterator :: HashTableConstIterator (
                    HashTable const * pTable
            ) noexcept :
                    _pTable ( pTable ) {

                this->advanceBucket();
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
            > :: HashTableConstIterator :: HashTableConstIterator (
                    HashTable   const * pTable,
                    __DataNode  const * pCurrentNode,
                    Size                bucketIndex
            ) noexcept :
                    _pTable ( pTable ),
                    _pCurrentNode ( pCurrentNode ),
                    _bucketIndex ( bucketIndex ) {

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
            > :: HashTableConstIterator :: HashTableConstIterator (
                    HashTableConstIterator const & iterator
            ) noexcept :
                    _pTable ( iterator._pTable ),
                    _pCurrentNode ( iterator._pCurrentNode ),
                    _bucketIndex ( iterator._bucketIndex ) {

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
            > :: HashTableConstIterator :: HashTableConstIterator (
                    HashTableConstIterator && iterator
            ) noexcept :
                    _pTable ( cds :: exchange ( iterator._pTable, nullptr ) ),
                    _pCurrentNode ( cds :: exchange ( iterator._pCurrentNode, nullptr ) ),
                    _bucketIndex ( cds :: exchange ( iterator._bucketIndex, 0ULL ) ) {

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
            > :: HashTableConstIterator :: operator = (
                    HashTableConstIterator const & iterator
            ) noexcept -> HashTableConstIterator & {

                if ( this == & iterator ) {
                    return * this;
                }

                this->_pTable       = iterator._pTable;
                this->_bucketIndex  = iterator._bucketIndex;
                this->_pCurrentNode = iterator._pCurrentNode;

                return * this;
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
            > :: HashTableConstIterator :: operator = (
                    HashTableConstIterator && iterator
            ) noexcept -> HashTableConstIterator & {

                if ( this == & iterator ) {
                    return * this;
                }

                this->_pTable       = cds :: exchange ( iterator._pTable, nullptr );
                this->_bucketIndex  = cds :: exchange ( iterator._bucketIndex, 0ULL );
                this->_pCurrentNode = cds :: exchange ( iterator._pCurrentNode, nullptr );

                return * this;
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
            > :: HashTableConstIterator :: bucketIndex () const noexcept -> Size {

                return this->_bucketIndex;
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
            > :: HashTableConstIterator :: currentNode () const noexcept -> __DataNode const * {

                return this->_pCurrentNode;
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
            > :: HashTableConstIterator :: operator ++ () noexcept -> HashTableConstIterator & {

                if ( this->_bucketIndex >= this->_pTable->_bucketArray._size ) {
                    return * this;
                }

                this->_pCurrentNode = this->_pCurrentNode->_pNext;
                if ( this->_pCurrentNode == nullptr ) {
                    this->advanceBucket();
                }

                return * this;
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
            > :: HashTableConstIterator :: operator * () const noexcept -> HashTable :: ElementType const & {

                return this->_pCurrentNode->_data.data();
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
            > :: HashTableConstIterator :: operator == (
                    HashTableConstIterator const & iterator
            ) const noexcept -> bool {

                return this->_pCurrentNode == iterator._pCurrentNode;
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
            > :: HashTableConstIterator :: operator != (
                    HashTableConstIterator const & iterator
            ) const noexcept -> bool {

                return this->_pCurrentNode != iterator._pCurrentNode;
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
            > :: HashTableConstIterator :: operator bool () const noexcept {

                return this->_pCurrentNode != nullptr;
            }

        }
    }
}

#endif // __CDS_SHARED_HASH_TABLE_CONST_ITERATOR_IMPL_HPP__