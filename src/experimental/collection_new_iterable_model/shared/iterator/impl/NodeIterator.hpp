//
// Created by loghin on 18/07/22.
//

#ifndef __CDS_SHARED_NODE_ITERATOR_IMPL_HPP__
#define __CDS_SHARED_NODE_ITERATOR_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr UnidirectionalNodeIterator < __ElementType > :: UnidirectionalNodeIterator () noexcept = default;


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr UnidirectionalNodeIterator < __ElementType > :: UnidirectionalNodeIterator (
                Node * pPreviousNode,
                Node * pCurrentNode
        ) noexcept :
                _pPreviousNode ( pPreviousNode ),
                _pCurrentNode ( pCurrentNode ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr UnidirectionalNodeIterator < __ElementType > :: UnidirectionalNodeIterator (
                UnidirectionalNodeIterator const & iterator
        ) noexcept :
                _pPreviousNode ( iterator._pPreviousNode ),
                _pCurrentNode ( iterator._pCurrentNode ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr UnidirectionalNodeIterator < __ElementType > :: UnidirectionalNodeIterator (
                UnidirectionalNodeIterator && iterator
        ) noexcept :
                _pPreviousNode ( cds :: exchange ( iterator._pPreviousNode, nullptr ) ),
                _pCurrentNode ( cds :: exchange ( iterator._pCurrentNode, nullptr ) ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto UnidirectionalNodeIterator < __ElementType > :: operator * () const noexcept -> __ElementType & {

            return this->_pCurrentNode->_data;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto UnidirectionalNodeIterator < __ElementType > :: operator -> () const noexcept -> __ElementType * {

            return & this->_pCurrentNode->_data;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto UnidirectionalNodeIterator < __ElementType > :: operator == (
                UnidirectionalNodeIterator const & iterator
        ) const noexcept -> bool {

            return
                    this->_pCurrentNode     == iterator._pCurrentNode &&
                    this->_pPreviousNode    == iterator._pPreviousNode;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto UnidirectionalNodeIterator < __ElementType > :: operator != (
                UnidirectionalNodeIterator const & iterator
        ) const noexcept -> bool {

            return
                    this->_pCurrentNode     != iterator._pCurrentNode ||
                    this->_pPreviousNode    != iterator._pPreviousNode;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto UnidirectionalNodeIterator < __ElementType > :: operator ++ () noexcept -> UnidirectionalNodeIterator & {

            this->_pPreviousNode    = this->_pCurrentNode;
            this->_pCurrentNode     = this->_pCurrentNode->_pNext;
            return * this;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto UnidirectionalNodeIterator < __ElementType > :: operator ++ (int) noexcept -> UnidirectionalNodeIterator {

            auto copy = * this;
            this->_pPreviousNode    = this->_pCurrentNode;
            this->_pCurrentNode     = this->_pCurrentNode->_pNext;
            return copy;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr UnidirectionalNodeConstIterator < __ElementType > :: UnidirectionalNodeConstIterator () noexcept = default;


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr UnidirectionalNodeConstIterator < __ElementType > :: UnidirectionalNodeConstIterator (
                Node const * pPreviousNode,
                Node const * pCurrentNode
        ) noexcept :
                _pPreviousNode ( pPreviousNode ),
                _pCurrentNode ( pCurrentNode ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr UnidirectionalNodeConstIterator < __ElementType > :: UnidirectionalNodeConstIterator (
                UnidirectionalNodeConstIterator const & iterator
        ) noexcept :
                _pPreviousNode ( iterator._pPreviousNode ),
                _pCurrentNode ( iterator._pCurrentNode ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr UnidirectionalNodeConstIterator < __ElementType > :: UnidirectionalNodeConstIterator (
                UnidirectionalNodeConstIterator && iterator
        ) noexcept :
                _pPreviousNode ( cds :: exchange ( iterator._pPreviousNode, nullptr ) ),
                _pCurrentNode ( cds :: exchange ( iterator._pCurrentNode, nullptr ) ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto UnidirectionalNodeConstIterator < __ElementType > :: operator * () const noexcept -> __ElementType const & {

            return this->_pCurrentNode->_data;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto UnidirectionalNodeConstIterator < __ElementType > :: operator -> () const noexcept -> __ElementType const * {

            return & this->_pCurrentNode->_data;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto UnidirectionalNodeConstIterator < __ElementType > :: operator == (
                UnidirectionalNodeConstIterator const & iterator
        ) const noexcept -> bool {

            return
                    this->_pCurrentNode     == iterator._pCurrentNode &&
                    this->_pPreviousNode    == iterator._pPreviousNode;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto UnidirectionalNodeConstIterator < __ElementType > :: operator != (
                UnidirectionalNodeConstIterator const & iterator
        ) const noexcept -> bool {

            return
                    this->_pCurrentNode  != iterator._pCurrentNode ||
                    this->_pPreviousNode != iterator._pPreviousNode;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto UnidirectionalNodeConstIterator < __ElementType > :: operator ++ () noexcept -> UnidirectionalNodeConstIterator & {

            this->_pPreviousNode    = this->_pCurrentNode;
            this->_pCurrentNode     = this->_pCurrentNode->_pNext;
            return * this;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto UnidirectionalNodeConstIterator < __ElementType > :: operator ++ (int) noexcept -> UnidirectionalNodeConstIterator {

            auto copy = * this;
            this->_pPreviousNode    = this->_pCurrentNode;
            this->_pCurrentNode     = this->_pCurrentNode->_pNext;
            return copy;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr AbstractBidirectionalNodeIterator < __ElementType > :: AbstractBidirectionalNodeIterator () noexcept = default;


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr AbstractBidirectionalNodeIterator < __ElementType > :: AbstractBidirectionalNodeIterator (
                Node * pPreviousNode,
                Node * pCurrentNode
        ) noexcept :
                _pPreviousNode ( pPreviousNode ),
                _pCurrentNode ( pCurrentNode ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr AbstractBidirectionalNodeIterator < __ElementType > :: AbstractBidirectionalNodeIterator (
                AbstractBidirectionalNodeIterator const & iterator
        ) noexcept :
                _pPreviousNode ( iterator._pPreviousNode ),
                _pCurrentNode ( iterator._pCurrentNode ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr AbstractBidirectionalNodeIterator < __ElementType > :: AbstractBidirectionalNodeIterator (
                AbstractBidirectionalNodeIterator && iterator
        ) noexcept :
                _pPreviousNode ( cds :: exchange ( iterator._pPreviousNode, nullptr ) ),
                _pCurrentNode ( cds :: exchange ( iterator._pCurrentNode, nullptr ) ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto AbstractBidirectionalNodeIterator < __ElementType > :: operator * () const noexcept -> __ElementType & {

            return this->_pCurrentNode->_data;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto AbstractBidirectionalNodeIterator < __ElementType > :: operator -> () const noexcept -> __ElementType * {

            return & this->_pCurrentNode->_data;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto AbstractBidirectionalNodeIterator < __ElementType > :: operator == (
                AbstractBidirectionalNodeIterator const & iterator
        ) const noexcept -> bool {

            return
                    this->_pCurrentNode     == iterator._pCurrentNode &&
                    this->_pPreviousNode    == iterator._pPreviousNode;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto AbstractBidirectionalNodeIterator < __ElementType > :: operator != (
                AbstractBidirectionalNodeIterator const & iterator
        ) const noexcept -> bool {

            return
                    this->_pCurrentNode     != iterator._pCurrentNode ||
                    this->_pPreviousNode    != iterator._pPreviousNode;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr AbstractBidirectionalNodeConstIterator < __ElementType > :: AbstractBidirectionalNodeConstIterator () noexcept = default;


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr AbstractBidirectionalNodeConstIterator < __ElementType > :: AbstractBidirectionalNodeConstIterator (
                Node const * pPreviousNode,
                Node const * pCurrentNode
        ) noexcept :
                _pPreviousNode ( pPreviousNode ),
                _pCurrentNode ( pCurrentNode ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr AbstractBidirectionalNodeConstIterator < __ElementType > :: AbstractBidirectionalNodeConstIterator (
                AbstractBidirectionalNodeConstIterator const & iterator
        ) noexcept :
                _pPreviousNode ( iterator._pPreviousNode ),
                _pCurrentNode ( iterator._pCurrentNode ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr AbstractBidirectionalNodeConstIterator < __ElementType > :: AbstractBidirectionalNodeConstIterator (
                AbstractBidirectionalNodeConstIterator && iterator
        ) noexcept :
                _pPreviousNode ( cds :: exchange ( iterator._pPreviousNode, nullptr ) ),
                _pCurrentNode ( cds :: exchange ( iterator._pCurrentNode, nullptr ) ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto AbstractBidirectionalNodeConstIterator < __ElementType > :: operator * () const noexcept -> __ElementType const & {

            return this->_pCurrentNode->_data;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto AbstractBidirectionalNodeConstIterator < __ElementType > :: operator -> () const noexcept -> __ElementType const * {

            return & this->_pCurrentNode->_data;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto AbstractBidirectionalNodeConstIterator < __ElementType > :: operator == (
                AbstractBidirectionalNodeConstIterator const & iterator
        ) const noexcept -> bool {

            return
                    this->_pCurrentNode     == iterator._pCurrentNode &&
                    this->_pPreviousNode    == iterator._pPreviousNode;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto AbstractBidirectionalNodeConstIterator < __ElementType > :: operator != (
                AbstractBidirectionalNodeConstIterator const & iterator
        ) const noexcept -> bool {

            return
                    this->_pCurrentNode     != iterator._pCurrentNode ||
                    this->_pPreviousNode    != iterator._pPreviousNode;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr ForwardBidirectionalNodeIterator < __ElementType > :: ForwardBidirectionalNodeIterator () noexcept = default;


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr ForwardBidirectionalNodeIterator < __ElementType > :: ForwardBidirectionalNodeIterator (
                Node * pPreviousNode,
                Node * pCurrentNode
        ) noexcept :
                AbstractBidirectionalNodeIterator < __ElementType > (
                        pPreviousNode,
                        pCurrentNode
                ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr ForwardBidirectionalNodeIterator < __ElementType > :: ForwardBidirectionalNodeIterator (
                ForwardBidirectionalNodeIterator const & iterator
        ) noexcept :
                AbstractBidirectionalNodeIterator < __ElementType > ( iterator._pCurrentNode ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr ForwardBidirectionalNodeIterator < __ElementType > :: ForwardBidirectionalNodeIterator (
                ForwardBidirectionalNodeIterator && iterator
        ) noexcept :
                AbstractBidirectionalNodeIterator < __ElementType > ( std :: move ( iterator ) ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto ForwardBidirectionalNodeIterator < __ElementType > :: operator == (
                ForwardBidirectionalNodeIterator const & iterator
        ) const noexcept -> bool {

            return
                    this->_pCurrentNode     == iterator._pCurrentNode &&
                    this->_pPreviousNode    == iterator._pPreviousNode;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto ForwardBidirectionalNodeIterator < __ElementType > :: operator != (
                ForwardBidirectionalNodeIterator const & iterator
        ) const noexcept -> bool {

            return
                    this->_pCurrentNode     != iterator._pCurrentNode ||
                    this->_pPreviousNode    != iterator._pPreviousNode;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto ForwardBidirectionalNodeIterator < __ElementType > :: operator ++ () noexcept -> ForwardBidirectionalNodeIterator & {

            this->_pPreviousNode    = this->_pCurrentNode;
            this->_pCurrentNode     = this->_pCurrentNode->_pNext;
            return * this;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto ForwardBidirectionalNodeIterator < __ElementType > :: operator ++ (int) noexcept -> ForwardBidirectionalNodeIterator {

            auto copy = * this;
            this->_pPreviousNode    = this->_pCurrentNode;
            this->_pCurrentNode     = this->_pCurrentNode->_pNext;
            return copy;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto ForwardBidirectionalNodeIterator < __ElementType > :: operator -- () noexcept -> ForwardBidirectionalNodeIterator & {

            this->_pCurrentNode     = this->_pPreviousNode;
            this->_pPreviousNode    = this->_pCurrentNode == nullptr ? nullptr : this->_pCurrentNode->_pPrevious;
            return * this;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto ForwardBidirectionalNodeIterator < __ElementType > :: operator -- (int) noexcept -> ForwardBidirectionalNodeIterator {

            auto copy = * this;
            this->_pCurrentNode     = this->_pPreviousNode;
            this->_pPreviousNode    = this->_pCurrentNode == nullptr ? nullptr : this->_pCurrentNode->_pPrevious;
            return copy;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr ForwardBidirectionalNodeConstIterator < __ElementType > :: ForwardBidirectionalNodeConstIterator () noexcept = default;


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr ForwardBidirectionalNodeConstIterator < __ElementType > :: ForwardBidirectionalNodeConstIterator (
                Node const * pPreviousNode,
                Node const * pCurrentNode
        ) noexcept :
                AbstractBidirectionalNodeConstIterator < __ElementType > (
                        pPreviousNode,
                        pCurrentNode
                ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr ForwardBidirectionalNodeConstIterator < __ElementType > :: ForwardBidirectionalNodeConstIterator (
                ForwardBidirectionalNodeConstIterator const & iterator
        ) noexcept :
                AbstractBidirectionalNodeConstIterator < __ElementType > ( iterator._pCurrentNode ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr ForwardBidirectionalNodeConstIterator < __ElementType > :: ForwardBidirectionalNodeConstIterator (
                ForwardBidirectionalNodeConstIterator && iterator
        ) noexcept :
                AbstractBidirectionalNodeConstIterator < __ElementType > ( std :: move ( iterator ) ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto ForwardBidirectionalNodeConstIterator < __ElementType > :: operator == (
                ForwardBidirectionalNodeConstIterator const & iterator
        ) const noexcept -> bool {

            return
                    this->_pCurrentNode     == iterator._pCurrentNode &&
                    this->_pPreviousNode    == iterator._pPreviousNode;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto ForwardBidirectionalNodeConstIterator < __ElementType > :: operator != (
                ForwardBidirectionalNodeConstIterator const & iterator
        ) const noexcept -> bool {

            return
                    this->_pCurrentNode     != iterator._pCurrentNode ||
                    this->_pPreviousNode    != iterator._pPreviousNode;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto ForwardBidirectionalNodeConstIterator < __ElementType > :: operator ++ () noexcept -> ForwardBidirectionalNodeConstIterator & {

            this->_pPreviousNode    = this->_pCurrentNode;
            this->_pCurrentNode     = this->_pCurrentNode->_pNext;
            return * this;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto ForwardBidirectionalNodeConstIterator < __ElementType > :: operator ++ (int) noexcept -> ForwardBidirectionalNodeConstIterator {

            auto copy = * this;
            this->_pPreviousNode    = this->_pCurrentNode;
            this->_pCurrentNode     = this->_pCurrentNode->_pNext;
            return copy;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto ForwardBidirectionalNodeConstIterator < __ElementType > :: operator -- () noexcept -> ForwardBidirectionalNodeConstIterator & {

            this->_pCurrentNode     = this->_pPreviousNode;
            this->_pPreviousNode    = this->_pCurrentNode == nullptr ? nullptr : this->_pCurrentNode->_pPrevious;
            return * this;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto ForwardBidirectionalNodeConstIterator < __ElementType > :: operator -- (int) noexcept -> ForwardBidirectionalNodeConstIterator {

            auto copy = * this;
            this->_pCurrentNode     = this->_pPreviousNode;
            this->_pPreviousNode    = this->_pCurrentNode == nullptr ? nullptr : this->_pCurrentNode->_pPrevious;
            return copy;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr BackwardBidirectionalNodeIterator < __ElementType > :: BackwardBidirectionalNodeIterator () noexcept = default;


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr BackwardBidirectionalNodeIterator < __ElementType > :: BackwardBidirectionalNodeIterator (
                Node * pPreviousNode,
                Node * pCurrentNode
        ) noexcept :
                AbstractBidirectionalNodeIterator < __ElementType > (
                        pPreviousNode,
                        pCurrentNode
                ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr BackwardBidirectionalNodeIterator < __ElementType > :: BackwardBidirectionalNodeIterator (
                BackwardBidirectionalNodeIterator const & iterator
        ) noexcept :
                AbstractBidirectionalNodeIterator < __ElementType > ( iterator._pCurrentNode ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr BackwardBidirectionalNodeIterator < __ElementType > :: BackwardBidirectionalNodeIterator (
                BackwardBidirectionalNodeIterator && iterator
        ) noexcept :
                AbstractBidirectionalNodeIterator < __ElementType > ( std :: move ( iterator ) ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto BackwardBidirectionalNodeIterator < __ElementType > :: operator == (
                BackwardBidirectionalNodeIterator const & iterator
        ) const noexcept -> bool {

            return
                    this->_pCurrentNode     == iterator._pCurrentNode &&
                    this->_pPreviousNode    == iterator._pPreviousNode;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto BackwardBidirectionalNodeIterator < __ElementType > :: operator != (
                BackwardBidirectionalNodeIterator const & iterator
        ) const noexcept -> bool {

            return
                    this->_pCurrentNode     != iterator._pCurrentNode ||
                    this->_pPreviousNode    != iterator._pPreviousNode;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto BackwardBidirectionalNodeIterator < __ElementType > :: operator ++ () noexcept -> BackwardBidirectionalNodeIterator & {

            this->_pPreviousNode    = this->_pCurrentNode;
            this->_pCurrentNode     = this->_pCurrentNode->_pPrevious;
            return * this;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto BackwardBidirectionalNodeIterator < __ElementType > :: operator ++ (int) noexcept -> BackwardBidirectionalNodeIterator {

            auto copy = * this;
            this->_pPreviousNode    = this->_pCurrentNode;
            this->_pCurrentNode     = this->_pCurrentNode->_pPrevious;
            return copy;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto BackwardBidirectionalNodeIterator < __ElementType > :: operator -- () noexcept -> BackwardBidirectionalNodeIterator & {

            this->_pCurrentNode     = this->_pPreviousNode;
            this->_pPreviousNode    = this->_pCurrentNode == nullptr ? nullptr : this->_pCurrentNode->_pNext;
            return * this;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto BackwardBidirectionalNodeIterator < __ElementType > :: operator -- (int) noexcept -> BackwardBidirectionalNodeIterator {

            auto copy = * this;
            this->_pCurrentNode     = this->_pPreviousNode;
            this->_pPreviousNode    = this->_pCurrentNode == nullptr ? nullptr : this->_pCurrentNode->_pNext;
            return copy;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr BackwardBidirectionalNodeConstIterator < __ElementType > :: BackwardBidirectionalNodeConstIterator () noexcept = default;


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr BackwardBidirectionalNodeConstIterator < __ElementType > :: BackwardBidirectionalNodeConstIterator (
                Node const * pPreviousNode,
                Node const * pCurrentNode
        ) noexcept :
                AbstractBidirectionalNodeConstIterator < __ElementType > (
                        pPreviousNode,
                        pCurrentNode
                ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr BackwardBidirectionalNodeConstIterator < __ElementType > :: BackwardBidirectionalNodeConstIterator (
                BackwardBidirectionalNodeConstIterator const & iterator
        ) noexcept :
                AbstractBidirectionalNodeConstIterator < __ElementType > ( iterator._pCurrentNode ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr BackwardBidirectionalNodeConstIterator < __ElementType > :: BackwardBidirectionalNodeConstIterator (
                BackwardBidirectionalNodeConstIterator && iterator
        ) noexcept :
                AbstractBidirectionalNodeConstIterator < __ElementType > ( std :: move ( iterator ) ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto BackwardBidirectionalNodeConstIterator < __ElementType > :: operator == (
                BackwardBidirectionalNodeConstIterator const & iterator
        ) const noexcept -> bool {

            return
                    this->_pCurrentNode     == iterator._pCurrentNode &&
                    this->_pPreviousNode    == iterator._pPreviousNode;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto BackwardBidirectionalNodeConstIterator < __ElementType > :: operator != (
                BackwardBidirectionalNodeConstIterator const & iterator
        ) const noexcept -> bool {

            return
                    this->_pCurrentNode     != iterator._pCurrentNode ||
                    this->_pPreviousNode    != iterator._pPreviousNode;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto BackwardBidirectionalNodeConstIterator < __ElementType > :: operator ++ () noexcept -> BackwardBidirectionalNodeConstIterator & {

            this->_pPreviousNode    = this->_pCurrentNode;
            this->_pCurrentNode     = this->_pCurrentNode->_pPrevious;
            return * this;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto BackwardBidirectionalNodeConstIterator < __ElementType > :: operator ++ (int) noexcept -> BackwardBidirectionalNodeConstIterator {

            auto copy = * this;
            this->_pPreviousNode    = this->_pCurrentNode;
            this->_pCurrentNode     = this->_pCurrentNode->_pPrevious;
            return copy;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto BackwardBidirectionalNodeConstIterator < __ElementType > :: operator -- () noexcept -> BackwardBidirectionalNodeConstIterator & {

            this->_pCurrentNode     = this->_pPreviousNode;
            this->_pPreviousNode    = this->_pCurrentNode == nullptr ? nullptr : this->_pCurrentNode->_pNext;
            return * this;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto BackwardBidirectionalNodeConstIterator < __ElementType > :: operator -- (int) noexcept -> BackwardBidirectionalNodeConstIterator {

            auto copy = * this;
            this->_pCurrentNode     = this->_pPreviousNode;
            this->_pPreviousNode    = this->_pCurrentNode == nullptr ? nullptr : this->_pCurrentNode->_pNext;
            return copy;
        }

    }
}

#endif // __CDS_SHARED_NODE_ITERATOR_IMPL_HPP__
