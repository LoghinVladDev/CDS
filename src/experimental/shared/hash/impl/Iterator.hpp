//
// Created by loghin on 6/22/2022.
//

#ifndef __CDS_HASH_TABLE_ITERATOR_IMPL_HPP__
#define __CDS_HASH_TABLE_ITERATOR_IMPL_HPP__

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
                > :: HashTableIterator :: HashTableIterator () noexcept = default;


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
                > :: HashTableIterator :: HashTableIterator (
                        HashTable * pTable
                ) noexcept :
                        _pTable ( pTable ) {

                    while ( this->_pCurrentNode != nullptr && this->_bucketIndex < this->_pTable->_bucketArray._size ) {
                        this->_pCurrentNode = this->_pTable->_bucketArray._pArray [ this->_bucketIndex ++ ];
                    }
                }

            }
        }
    }
}

#endif // __CDS_HASH_TABLE_ITERATOR_IMPL_HPP__
