/*
 * Created by loghin on 27/07/22.
 */

#ifndef __CDS_EX_SHARED_HASH_TABLE_ITERATOR_IMPL_HPP__
#define __CDS_EX_SHARED_HASH_TABLE_ITERATOR_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {

        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        __CDS_cpplang_ConstexprConditioned auto HashTableIterator < __ElementType > :: advanceBucket () noexcept -> void {

            /* If current Node is null, end of bucket list reached, reset previous node */
            if ( this->_pCurrentNode == nullptr ) {
                this->_pPreviousNode = nullptr;
            }

            /* While a non-empty list has not been reached, and we still have buckets to check */
            while ( this->_pCurrentNode == nullptr && this->_bucketIndex + 1ULL < this->_bucketCount ) {

                /* Advance the bucket index and acquire the bucket's head */
                this->_pCurrentNode = this->_pListArray [ ++ this->_bucketIndex ];
            }

            /* If last bucket has been completely parsed */
            if ( this->_bucketIndex + 1ULL == this->_bucketCount && this->_pCurrentNode == nullptr ) {

                /* Advance the index further so that no new buckets are looked into */
                ++ this->_bucketIndex;
            }
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr HashTableIterator < __ElementType > :: HashTableIterator () noexcept = default;


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        __CDS_cpplang_ConstexprConditioned HashTableIterator < __ElementType > :: HashTableIterator (
                DataNode ** pListArray,
                Size        bucketCount
        ) noexcept :
                _pListArray ( pListArray ),
                _bucketCount ( bucketCount ),
                _pCurrentNode ( pListArray == nullptr ? nullptr : pListArray [ 0ULL ] ) {

            /* Initialize iterator by copying the bucket list and size, and the initial node, if given a bucket list, based on the first bucket head */
            /* Advance the bucket, will not do anything if first bucket has nodes inside */
            this->advanceBucket();
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr HashTableIterator < __ElementType > :: HashTableIterator (
                DataNode ** pListArray,
                Size        bucketCount,
                DataNode  * pCurrentNode,
                DataNode  * pPreviousNode,
                Size        bucketIndex
        ) noexcept :
                _pListArray ( pListArray ),
                _bucketCount ( bucketCount ),
                _pCurrentNode ( pCurrentNode ),
                _pPreviousNode ( pPreviousNode ),
                _bucketIndex ( bucketIndex ) {

            /* Copy all the given data, no advancement needed is assumed, since all necessary data has been provided */
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr HashTableIterator < __ElementType > :: HashTableIterator (
                HashTableIterator const & iterator
        ) noexcept :
                _pListArray ( iterator._pListArray ),
                _bucketCount ( iterator._bucketCount ),
                _pCurrentNode ( iterator._pCurrentNode ),
                _pPreviousNode ( iterator._pPreviousNode ),
                _bucketIndex ( iterator._bucketIndex ) {

            /* copy all data from given iterator */
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr HashTableIterator < __ElementType > :: HashTableIterator (
                HashTableIterator && iterator
        ) noexcept :
                _pListArray ( cds :: exchange ( iterator._pListArray, nullptr ) ),
                _bucketCount ( cds :: exchange ( iterator._bucketCount, 0ULL ) ),
                _pCurrentNode ( cds :: exchange ( iterator._pCurrentNode, nullptr ) ),
                _pPreviousNode ( cds :: exchange ( iterator._pPreviousNode, nullptr ) ),
                _bucketIndex ( cds :: exchange ( iterator._bucketIndex, 0ULL ) ) {

            /* move all data from given iterator */
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto HashTableIterator < __ElementType > :: operator = (
                HashTableIterator const & iterator
        ) noexcept -> HashTableIterator & {

            /* if given same iterator, copy is unnecessary */
            if ( this == & iterator ) {
                return * this;
            }

            /* otherwise, copy all data from given iterator */
            this->_pListArray       = iterator._pListArray;
            this->_bucketCount      = iterator._bucketCount;
            this->_pCurrentNode     = iterator._pCurrentNode;
            this->_pPreviousNode    = iterator._pPreviousNode;
            this->_bucketIndex      = iterator._bucketIndex;

            return * this;
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto HashTableIterator < __ElementType > :: operator = (
                HashTableIterator && iterator
        ) noexcept -> HashTableIterator & {

            /* if given same iterator, move is unnecessary */
            if ( this == & iterator ) {
                return * this;
            }

            /* otherwise, move all data from given iterator */
            this->_pListArray       = cds :: exchange ( iterator._pListArray, nullptr );
            this->_bucketCount      = cds :: exchange ( iterator._bucketCount, 0ULL );
            this->_pCurrentNode     = cds :: exchange ( iterator._pCurrentNode, nullptr );
            this->_pPreviousNode    = cds :: exchange ( iterator._pPreviousNode, nullptr );
            this->_bucketIndex      = cds :: exchange ( iterator._bucketIndex, 0ULL );

            return * this;
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr auto HashTableIterator < __ElementType > :: listArray () const noexcept -> DataNode ** {

            /* return the bucket list */
            return this->_pListArray;
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr auto HashTableIterator < __ElementType > :: bucketCount () const noexcept -> Size {

            /* return the bucket list size */
            return this->_bucketCount;
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr auto HashTableIterator < __ElementType > :: bucketIndex () const noexcept -> Size {

            /* return the bucket index */
            return this->_bucketIndex;
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr auto HashTableIterator < __ElementType > :: currentNode () const noexcept -> DataNode * {

            /* return the current node */
            return this->_pCurrentNode;
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr auto HashTableIterator < __ElementType > :: previousNode () const noexcept -> DataNode * {

            /* return the previous node */
            return this->_pPreviousNode;
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto HashTableIterator < __ElementType > :: operator ++ () noexcept -> HashTableIterator & {

            /* if bucket list is completely parsed, do nothing */
            if ( this->_bucketIndex >= this->_bucketCount ) {
                return * this;
            }

            /* advance previous node to current */
            this->_pPreviousNode    = this->_pCurrentNode;
            /* advance current node to next */
            this->_pCurrentNode     = this->_pCurrentNode->_pNext;

            /* If end of bucket reached, advance to next bucket */
            if ( this->_pCurrentNode == nullptr ) {
                this->advanceBucket();
            }

            return * this;
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto HashTableIterator < __ElementType > :: operator ++ (int) noexcept -> HashTableIterator {

            /* copy, advance current, return copy */
            auto copy = * this;
            ++ ( * this );
            return copy;
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr auto HashTableIterator < __ElementType > :: operator * () const noexcept -> __ElementType & {

            /* acquire value from current node */
            return this->_pCurrentNode->_data;
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr auto HashTableIterator < __ElementType > :: operator -> () const noexcept -> __ElementType * {

            /* acquire address of element from current node */
            return & this->_pCurrentNode->_data;
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr auto HashTableIterator < __ElementType > :: operator != (
                HashTableIterator const & iterator
        ) const noexcept -> bool {

            /* iterators are not equal if not equals ( this, iterator ) */
            return ! this->operator == ( iterator );
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr auto HashTableIterator < __ElementType > :: operator == (
                HashTableIterator const & iterator
        ) const noexcept -> bool {

            /* iterators are equal if either
             *      current node values are the same and not null OR
             *      both current nodes are null and previous nodes are equal ( end of last bucket ) */
            return
                    this->_pCurrentNode     == iterator._pCurrentNode &&
                    this->_pCurrentNode     != nullptr ||
                    this->_pCurrentNode     == iterator._pCurrentNode &&
                    this->_pPreviousNode    == iterator._pPreviousNode;
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr HashTableIterator < __ElementType > :: operator bool () const noexcept {

            /* iterators valid if current node is valid */
            return this->_pCurrentNode != nullptr;
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        __CDS_cpplang_ConstexprConditioned auto HashTableConstIterator < __ElementType > :: advanceBucket () noexcept -> void {

            /* If current Node is null, end of bucket list reached, reset previous node */
            if ( this->_pCurrentNode == nullptr ) {
                this->_pPreviousNode = nullptr;
            }

            /* While a non-empty list has not been reached, and we still have buckets to check */
            while ( this->_pCurrentNode == nullptr && this->_bucketIndex + 1ULL < this->_bucketCount ) {

                /* Advance the bucket index and acquire the bucket's head */
                this->_pCurrentNode = this->_pListArray [ ++ this->_bucketIndex ];
            }

            /* If last bucket has been completely parsed */
            if ( this->_bucketIndex + 1ULL == this->_bucketCount && this->_pCurrentNode == nullptr ) {

                /* Advance the index further so that no new buckets are looked into */
                ++ this->_bucketIndex;
            }
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr HashTableConstIterator < __ElementType > :: HashTableConstIterator () noexcept = default;


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        __CDS_cpplang_ConstexprConditioned HashTableConstIterator < __ElementType > :: HashTableConstIterator (
                DataNode    const * const * pListArray,
                Size                        bucketCount
        ) noexcept :
                _pListArray ( pListArray ),
                _bucketCount ( bucketCount ),
                _pCurrentNode ( pListArray == nullptr ? nullptr : pListArray [ 0ULL ] ) {

            /* Initialize iterator by copying the bucket list and size, and the initial node, if given a bucket list, based on the first bucket head */
            /* Advance the bucket, will not do anything if first bucket has nodes inside */
            this->advanceBucket();
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        __CDS_cpplang_ConstexprConditioned HashTableConstIterator < __ElementType > :: HashTableConstIterator (
                DataNode    const * const * pListArray,
                Size                        bucketCount,
                DataNode            const * pCurrentNode,
                DataNode            const * pPreviousNode,
                Size                        bucketIndex
        ) noexcept :
                _pListArray ( pListArray ),
                _bucketCount ( bucketCount ),
                _pCurrentNode ( pCurrentNode ),
                _pPreviousNode ( pPreviousNode ),
                _bucketIndex ( bucketIndex ) {

            /* Copy all the given data, no advancement needed is assumed, since all necessary data has been provided */
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr HashTableConstIterator < __ElementType > :: HashTableConstIterator (
                HashTableConstIterator const & iterator
        ) noexcept :
                _pListArray ( iterator._pListArray ),
                _bucketCount ( iterator._bucketCount ),
                _pCurrentNode ( iterator._pCurrentNode ),
                _pPreviousNode ( iterator._pPreviousNode ),
                _bucketIndex ( iterator._bucketIndex ) {

            /* copy all data from given iterator */
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr HashTableConstIterator < __ElementType > :: HashTableConstIterator (
                HashTableConstIterator && iterator
        ) noexcept :
                _pListArray ( cds :: exchange ( iterator._pListArray, nullptr ) ),
                _bucketCount ( cds :: exchange ( iterator._bucketCount, 0ULL ) ),
                _pCurrentNode ( cds :: exchange ( iterator._pCurrentNode, nullptr ) ),
                _pPreviousNode ( cds :: exchange ( iterator._pPreviousNode, nullptr ) ),
                _bucketIndex ( cds :: exchange ( iterator._bucketIndex, 0ULL ) ) {

            /* move all data from given iterator */
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto HashTableConstIterator < __ElementType > :: operator = (
                HashTableConstIterator const & iterator
        ) noexcept -> HashTableConstIterator & {

            /* if given same iterator, copy is unnecessary */
            if ( this == & iterator ) {
                return * this;
            }

            /* otherwise, copy all data from given iterator */
            this->_pListArray       = iterator._pListArray;
            this->_bucketCount      = iterator._bucketCount;
            this->_pCurrentNode     = iterator._pCurrentNode;
            this->_pPreviousNode    = iterator._pPreviousNode;
            this->_bucketIndex      = iterator._bucketIndex;

            return * this;
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto HashTableConstIterator < __ElementType > :: operator = (
                HashTableConstIterator && iterator
        ) noexcept -> HashTableConstIterator & {

            /* if given same iterator, move is unnecessary */
            if ( this == & iterator ) {
                return * this;
            }

            /* otherwise, move all data from given iterator */
            this->_pListArray       = cds :: exchange ( iterator._pListArray, nullptr );
            this->_bucketCount      = cds :: exchange ( iterator._bucketCount, 0ULL );
            this->_pCurrentNode     = cds :: exchange ( iterator._pCurrentNode, nullptr );
            this->_pPreviousNode    = cds :: exchange ( iterator._pPreviousNode, nullptr );
            this->_bucketIndex      = cds :: exchange ( iterator._bucketIndex, 0ULL );

            return * this;
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr auto HashTableConstIterator < __ElementType > :: listArray () const noexcept -> DataNode const * const * {

            /* return the bucket list */
            return this->_pListArray;
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr auto HashTableConstIterator < __ElementType > :: bucketCount () const noexcept -> Size {

            /* return the bucket list size */
            return this->_bucketCount;
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr auto HashTableConstIterator < __ElementType > :: bucketIndex () const noexcept -> Size {

            /* return the bucket index */
            return this->_bucketIndex;
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr auto HashTableConstIterator < __ElementType > :: currentNode () const noexcept -> DataNode const * {

            /* return the current node */
            return this->_pCurrentNode;
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr auto HashTableConstIterator < __ElementType > :: previousNode () const noexcept -> DataNode const * {

            /* return the previous node */
            return this->_pPreviousNode;
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto HashTableConstIterator < __ElementType > :: operator ++ () noexcept -> HashTableConstIterator & {

            /* if bucket list is completely parsed, do nothing */
            if ( this->_bucketIndex >= this->_bucketCount ) {
                return * this;
            }

            /* advance previous node to current */
            this->_pPreviousNode    = this->_pCurrentNode;
            /* advance current node to next */
            this->_pCurrentNode     = this->_pCurrentNode->_pNext;

            /* If end of bucket reached, advance to next bucket */
            if ( this->_pCurrentNode == nullptr ) {
                this->advanceBucket();
            }

            return * this;
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto HashTableConstIterator < __ElementType > :: operator ++ (int) noexcept -> HashTableConstIterator {

            /* copy, advance current, return copy */
            auto copy = * this;
            ++ ( * this );
            return copy;
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr auto HashTableConstIterator < __ElementType > :: operator * () const noexcept -> __ElementType const & {

            /* acquire value from current node */
            return this->_pCurrentNode->_data;
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr auto HashTableConstIterator < __ElementType > :: operator -> () const noexcept -> __ElementType const * {

            /* acquire address of element from current node */
            return & this->_pCurrentNode->_data;
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr auto HashTableConstIterator < __ElementType > :: operator != (
                HashTableConstIterator const & iterator
        ) const noexcept -> bool {

            /* iterators are not equal if not equals ( this, iterator ) */
            return ! this->operator == ( iterator );
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr auto HashTableConstIterator < __ElementType > :: operator == (
                HashTableConstIterator const & iterator
        ) const noexcept -> bool {

            /* iterators are equal if either
             *      current node values are the same and not null OR
             *      both current nodes are null and previous nodes are equal ( end of last bucket ) */
            return
                    this->_pCurrentNode     == iterator._pCurrentNode &&
                    this->_pCurrentNode     != nullptr ||
                    this->_pCurrentNode     == iterator._pCurrentNode &&
                    this->_pPreviousNode    == iterator._pPreviousNode;
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr HashTableConstIterator < __ElementType > :: operator bool () const noexcept {

            /* iterators valid if current node is valid */
            return this->_pCurrentNode != nullptr;
        }

    }
}

#endif /* __CDS_EX_SHARED_HASH_TABLE_ITERATOR_IMPL_HPP__ */
