//
// Created by loghin on 6/21/22.
//

#ifndef __CDS_EX_HASH_TABLE_HPP__
#define __CDS_EX_HASH_TABLE_HPP__

#include "HashTableUtils.hpp"

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {    // NOLINT(modernize-concat-nested-namespaces)
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
                > class __HashTable :                       // NOLINT(bugprone-reserved-identifier)
                        public __HashTableUtils <
                                __KeyHasher,
                                __RehashPolicy
                        > {

                protected:
                    using ElementType           = __ElementType;            // NOLINT(bugprone-reserved-identifier)

                protected:
                    using KeyType               = __ElementType;            // NOLINT(bugprone-reserved-identifier)

                protected:
                    using KeyExtractor          = __KeyExtractor;           // NOLINT(bugprone-reserved-identifier)

                protected:
                    using KeyEqualsComparator   = __KeyEqualsComparator;    // NOLINT(bugprone-reserved-identifier)

                protected:
                    using KeyHasher             = __KeyHasher;              // NOLINT(bugprone-reserved-identifier)

                protected:
                    using RehashPolicy          = __RehashPolicy;           // NOLINT(bugprone-reserved-identifier)

                protected:
                    using ElementTypeDestruct   = __ElementTypeDestruct;    // NOLINT(bugprone-reserved-identifier)

                public:
                    using __DataType        = cds :: __hidden :: __impl :: __allocation :: __RawContainer < __ElementType >; // NOLINT(bugprone-reserved-identifier)

                private:
                    __CDS_NoUniqueAddress __KeyExtractor          _key;

                private:
                    __CDS_NoUniqueAddress __KeyEqualsComparator   _equals;

                private:
                    __CDS_NoUniqueAddress __ElementTypeDestruct   _destruct;

                private:
                    struct __DataNode {                 // NOLINT(bugprone-reserved-identifier)
                        __DataType   _data;
                        __DataNode * _pNext;
                    };

                private:
                    using __BucketType = __DataNode *;  // NOLINT(bugprone-reserved-identifier)

                private:
                    struct __BucketArrayType {          // NOLINT(bugprone-reserved-identifier)
                        __BucketType  * _pArray;
                        Size            _size;
                    };

                private:
                    __BucketArrayType   _bucketArray    { nullptr, 0ULL };

                private:
                    Size                _totalSize      { 0ULL };

                protected:
                    constexpr __HashTable () noexcept;

                protected:
                    __CDS_Explicit constexpr __HashTable (
                            __KeyHasher const & keyHasher
                    ) noexcept;

                protected:
                    template <
                            typename __EntryCopyFunction // NOLINT(bugprone-reserved-identifier)
                    > __HashTable (
                            __HashTable         const & hashTable,
                            __EntryCopyFunction const & copyFunction
                    ) noexcept;

                protected:
                    constexpr __HashTable (
                            __HashTable && hashTable
                    ) noexcept;

                protected:

                protected:
                    auto __clear () noexcept -> void;   // NOLINT(bugprone-reserved-identifier)

                protected:
                    __CDS_NoDiscard constexpr auto __empty () const noexcept -> bool;       // NOLINT(bugprone-reserved-identifier)

                protected:
                    __CDS_NoDiscard constexpr auto __size () const noexcept -> Size;        // NOLINT(bugprone-reserved-identifier)

                protected:
                    __CDS_NoDiscard constexpr auto __bucketCount () const noexcept -> Size; // NOLINT(bugprone-reserved-identifier)

                protected:
                    auto __get (                        // NOLINT(bugprone-reserved-identifier)
                            __KeyType const & key,
                            bool            * pIsNew
                    ) noexcept -> __ElementType *;

                protected:
                    auto __get (                        // NOLINT(bugprone-reserved-identifier)
                            __KeyType const & key
                    ) const noexcept -> __ElementType const *;

                protected:
                    auto __at (                         // NOLINT(bugprone-reserved-identifier)
                            __KeyType const & key
                    ) noexcept -> __ElementType *;

                protected:
                    auto __at (                         // NOLINT(bugprone-reserved-identifier)
                            __KeyType const & key
                    ) const noexcept -> __ElementType const *;

                private:
                    auto __rehash (                     // NOLINT(bugprone-reserved-identifier)
                            Size                bucketCount,
                            Size                hashValueOfNewNode,
                            __DataNode  const * pNewEmptyNode
                    ) noexcept -> void;

                private:
                    static auto __rehashEmplace (       // NOLINT(bugprone-reserved-identifier)
                            __BucketType * pBucket,
                            __DataNode   * pNode
                    ) noexcept -> void;

                private:
                    auto __bucket (                                             // NOLINT(bugprone-reserved-identifier)
                            Size hash
                    ) noexcept -> __BucketType &;

                private:
                    auto __bucket (                                             // NOLINT(bugprone-reserved-identifier)
                            Size hash
                    ) const noexcept -> __BucketType const &;

                private:
                    auto __allocateBuckets (                                    // NOLINT(bugprone-reserved-identifier)
                            Size bucketCount
                    ) noexcept -> void;

                private:
                    auto __freeBuckets () noexcept -> void;                     // NOLINT(bugprone-reserved-identifier)

                private:
                    auto __allocateNode () const noexcept -> __DataNode *;      // NOLINT(bugprone-reserved-identifier)

                private:
                    auto __freeNode (                                           // NOLINT(bugprone-reserved-identifier)
                            __DataNode * pNode
                    ) const noexcept -> void;

                protected:
                    auto __remove (                                             // NOLINT(bugprone-reserved-identifier)
                            __KeyType const & key
                    ) noexcept -> bool;
                };

            }
        }
    }
}

#endif // __CDS_EX_HASH_TABLE_HPP__
