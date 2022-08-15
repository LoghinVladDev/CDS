//
// Created by loghin on 27/07/22.
//

#ifndef __CDS_EX_SHARED_HASH_TABLE_ITERATOR_IMPL_HPP__
#define __CDS_EX_SHARED_HASH_TABLE_ITERATOR_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprConditioned auto HashTableIterator < __ElementType > :: advanceBucket () noexcept -> void {

            if ( this->_pCurrentNode == nullptr ) {
                this->_pPreviousNode = nullptr;
            }

            while ( this->_pCurrentNode == nullptr && this->_bucketIndex + 1ULL < this->_bucketCount ) {
                this->_pCurrentNode = this->_pListArray [ ++ this->_bucketIndex ];
            }

            if ( this->_bucketIndex + 1ULL == this->_bucketCount && this->_pCurrentNode == nullptr ) {
                ++ this->_bucketIndex;
            }
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr HashTableIterator < __ElementType > :: HashTableIterator () noexcept = default;


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprConditioned HashTableIterator < __ElementType > :: HashTableIterator (
                DataNode ** pListArray,
                Size        bucketCount
        ) noexcept :
                _pListArray ( pListArray ),
                _bucketCount ( bucketCount ) {

            this->advanceBucket();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
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

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr HashTableIterator < __ElementType > :: HashTableIterator (
                HashTableIterator const & iterator
        ) noexcept :
                _pListArray ( iterator._pListArray ),
                _bucketCount ( iterator._bucketCount ),
                _pCurrentNode ( iterator._pCurrentNode ),
                _pPreviousNode ( iterator._pPreviousNode ),
                _bucketIndex ( iterator._bucketIndex ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr HashTableIterator < __ElementType > :: HashTableIterator (
                HashTableIterator && iterator
        ) noexcept :
                _pListArray ( cds :: exchange ( iterator._pListArray, nullptr ) ),
                _bucketCount ( cds :: exchange ( iterator._bucketCount, 0ULL ) ),
                _pCurrentNode ( cds :: exchange ( iterator._pCurrentNode, nullptr ) ),
                _pPreviousNode ( cds :: exchange ( iterator._pPreviousNode, nullptr ) ),
                _bucketIndex ( cds :: exchange ( iterator._bucketIndex, 0ULL ) ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto HashTableIterator < __ElementType > :: operator = (
                HashTableIterator const & iterator
        ) noexcept -> HashTableIterator & {

            if ( this == & iterator ) {
                return * this;
            }

            this->_pListArray       = iterator._pListArray;
            this->_bucketCount      = iterator._bucketCount;
            this->_pCurrentNode     = iterator._pCurrentNode;
            this->_pPreviousNode    = iterator._pPreviousNode;
            this->_bucketIndex      = iterator._bucketIndex;

            return * this;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto HashTableIterator < __ElementType > :: operator = (
                HashTableIterator && iterator
        ) noexcept -> HashTableIterator & {

            if ( this == & iterator ) {
                return * this;
            }

            this->_pListArray       = cds :: exchange ( iterator._pListArray, nullptr );
            this->_bucketCount      = cds :: exchange ( iterator._bucketCount, 0ULL );
            this->_pCurrentNode     = cds :: exchange ( iterator._pCurrentNode, nullptr );
            this->_pPreviousNode    = cds :: exchange ( iterator._pPreviousNode, nullptr );
            this->_bucketIndex      = cds :: exchange ( iterator._bucketIndex, 0ULL );

            return * this;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto HashTableIterator < __ElementType > :: listArray () const noexcept -> DataNode ** {

            return this->_pListArray;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto HashTableIterator < __ElementType > :: bucketCount () const noexcept -> Size {

            return this->_bucketCount;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto HashTableIterator < __ElementType > :: bucketIndex () const noexcept -> Size {

            return this->_bucketIndex;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto HashTableIterator < __ElementType > :: currentNode () const noexcept -> DataNode * {

            return this->_pCurrentNode;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto HashTableIterator < __ElementType > :: previousNode () const noexcept -> DataNode * {

            return this->_pPreviousNode;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto HashTableIterator < __ElementType > :: operator ++ () noexcept -> HashTableIterator & {

            if ( this->_bucketIndex >= this->_bucketCount ) {
                return * this;
            }

            this->_pPreviousNode    = this->_pCurrentNode;
            this->_pCurrentNode     = this->_pCurrentNode->_pNext;

            if ( this->_pCurrentNode == nullptr ) {
                this->advanceBucket();
            }

            return * this;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto HashTableIterator < __ElementType > :: operator ++ (int) noexcept -> HashTableIterator {

            auto copy = * this;
            ++ ( * this );
            return copy;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto HashTableIterator < __ElementType > :: operator * () const noexcept -> __ElementType & {

            return this->_pCurrentNode->_data;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto HashTableIterator < __ElementType > :: operator -> () const noexcept -> __ElementType * {

            return & this->_pCurrentNode->_data;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto HashTableIterator < __ElementType > :: operator != (
                HashTableIterator const & iterator
        ) const noexcept -> bool {

            return ! this->operator == ( iterator );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto HashTableIterator < __ElementType > :: operator == (
                HashTableIterator const & iterator
        ) const noexcept -> bool {

            return
                    this->_pCurrentNode     == iterator._pCurrentNode &&
                    this->_pCurrentNode     != nullptr ||
                    this->_pCurrentNode     == iterator._pCurrentNode &&
                    this->_pPreviousNode    == iterator._pPreviousNode;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr HashTableIterator < __ElementType > :: operator bool () const noexcept {

            return this->_pCurrentNode != nullptr;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprConditioned auto HashTableConstIterator < __ElementType > :: advanceBucket () noexcept -> void {

            if ( this->_pCurrentNode == nullptr ) {
                this->_pPreviousNode = nullptr;
            }

            while ( this->_pCurrentNode == nullptr && this->_bucketIndex + 1ULL < this->_bucketCount ) {
                this->_pCurrentNode = this->_pListArray [ ++ this->_bucketIndex ];
            }

            if ( this->_bucketIndex + 1ULL == this->_bucketCount && this->_pCurrentNode == nullptr ) {
                ++ this->_bucketIndex;
            }
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr HashTableConstIterator < __ElementType > :: HashTableConstIterator () noexcept = default;


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprConditioned HashTableConstIterator < __ElementType > :: HashTableConstIterator (
                DataNode    const * const * pListArray,
                Size                        bucketCount
        ) noexcept :
                _pListArray ( pListArray ),
                _bucketCount ( bucketCount ) {

            this->advanceBucket();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr HashTableConstIterator < __ElementType > :: HashTableConstIterator (
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

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr HashTableConstIterator < __ElementType > :: HashTableConstIterator (
                HashTableConstIterator const & iterator
        ) noexcept :
                _pListArray ( iterator._pListArray ),
                _bucketCount ( iterator._bucketCount ),
                _pCurrentNode ( iterator._pCurrentNode ),
                _pPreviousNode ( iterator._pPreviousNode ),
                _bucketIndex ( iterator._bucketIndex ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr HashTableConstIterator < __ElementType > :: HashTableConstIterator (
                HashTableConstIterator && iterator
        ) noexcept :
                _pListArray ( cds :: exchange ( iterator._pListArray, nullptr ) ),
                _bucketCount ( cds :: exchange ( iterator._bucketCount, 0ULL ) ),
                _pCurrentNode ( cds :: exchange ( iterator._pCurrentNode, nullptr ) ),
                _pPreviousNode ( cds :: exchange ( iterator._pPreviousNode, nullptr ) ),
                _bucketIndex ( cds :: exchange ( iterator._bucketIndex, 0ULL ) ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto HashTableConstIterator < __ElementType > :: operator = (
                HashTableConstIterator const & iterator
        ) noexcept -> HashTableConstIterator & {

            if ( this == & iterator ) {
                return * this;
            }

            this->_pListArray       = iterator._pListArray;
            this->_bucketCount      = iterator._bucketCount;
            this->_pCurrentNode     = iterator._pCurrentNode;
            this->_pPreviousNode    = iterator._pPreviousNode;
            this->_bucketIndex      = iterator._bucketIndex;

            return * this;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto HashTableConstIterator < __ElementType > :: operator = (
                HashTableConstIterator && iterator
        ) noexcept -> HashTableConstIterator & {

            if ( this == & iterator ) {
                return * this;
            }

            this->_pListArray       = cds :: exchange ( iterator._pListArray, nullptr );
            this->_bucketCount      = cds :: exchange ( iterator._bucketCount, 0ULL );
            this->_pCurrentNode     = cds :: exchange ( iterator._pCurrentNode, nullptr );
            this->_pPreviousNode    = cds :: exchange ( iterator._pPreviousNode, nullptr );
            this->_bucketIndex      = cds :: exchange ( iterator._bucketIndex, 0ULL );

            return * this;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto HashTableConstIterator < __ElementType > :: listArray () const noexcept -> DataNode const * const * {

            return this->_pListArray;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto HashTableConstIterator < __ElementType > :: bucketCount () const noexcept -> Size {

            return this->_bucketCount;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto HashTableConstIterator < __ElementType > :: bucketIndex () const noexcept -> Size {

            return this->_bucketIndex;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto HashTableConstIterator < __ElementType > :: currentNode () const noexcept -> DataNode const * {

            return this->_pCurrentNode;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto HashTableConstIterator < __ElementType > :: previousNode () const noexcept -> DataNode const * {

            return this->_pPreviousNode;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto HashTableConstIterator < __ElementType > :: operator ++ () noexcept -> HashTableConstIterator & {

            if ( this->_bucketIndex >= this->_bucketCount ) {
                return * this;
            }

            this->_pPreviousNode    = this->_pCurrentNode;
            this->_pCurrentNode     = this->_pCurrentNode->_pNext;

            if ( this->_pCurrentNode == nullptr ) {
                this->advanceBucket();
            }

            return * this;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto HashTableConstIterator < __ElementType > :: operator ++ (int) noexcept -> HashTableConstIterator {

            auto copy = * this;
            ++ ( * this );
            return copy;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto HashTableConstIterator < __ElementType > :: operator * () const noexcept -> __ElementType const & {

            return this->_pCurrentNode->_data;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto HashTableConstIterator < __ElementType > :: operator -> () const noexcept -> __ElementType const * {

            return & this->_pCurrentNode->_data;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto HashTableConstIterator < __ElementType > :: operator != (
                HashTableConstIterator const & iterator
        ) const noexcept -> bool {

            return ! this->operator == ( iterator );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto HashTableConstIterator < __ElementType > :: operator == (
                HashTableConstIterator const & iterator
        ) const noexcept -> bool {

            return
                    this->_pCurrentNode     == iterator._pCurrentNode &&
                    this->_pCurrentNode     != nullptr ||
                    this->_pCurrentNode     == iterator._pCurrentNode &&
                    this->_pPreviousNode    == iterator._pPreviousNode;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr HashTableConstIterator < __ElementType > :: operator bool () const noexcept {

            return this->_pCurrentNode != nullptr;
        }

    }
}

#endif // __CDS_EX_SHARED_HASH_TABLE_ITERATOR_IMPL_HPP__
