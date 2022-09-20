/*
 * Created by stefan on 16.08.2022.
 */

#ifndef __CDS_EX_SHARED_RED_BLACK_TREE_ITERATOR_IMPL_HPP__
#define __CDS_EX_SHARED_RED_BLACK_TREE_ITERATOR_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {

        template < typename __ElementType >                                                     /* NOLINT(bugprone-reserved-identifier) */
        AbstractTreeIterator < __ElementType > :: AbstractTreeIterator () noexcept = default;   /* NOLINT(bugprone-reserved-identifier) */


        template < typename __ElementType >                                                     /* NOLINT(bugprone-reserved-identifier) */
        AbstractTreeIterator < __ElementType > :: AbstractTreeIterator (                        /* NOLINT(bugprone-reserved-identifier) */
                RBTreeNode * pRoot,
                RBTreeNode * pCurrentNode
        ) noexcept :
                _pRoot ( pRoot ),
                _pCurrentNode ( pCurrentNode ) {

        }


        template < typename __ElementType >                                                     /* NOLINT(bugprone-reserved-identifier) */
        AbstractTreeIterator < __ElementType > :: AbstractTreeIterator (                        /* NOLINT(bugprone-reserved-identifier) */
                AbstractTreeIterator const & iterator
        ) noexcept :
                _pRoot ( iterator._pRoot ),
                _pCurrentNode ( iterator._pCurrentNode ) {

        }


        template < typename __ElementType >                                 /* NOLINT(bugprone-reserved-identifier) */
        AbstractTreeIterator < __ElementType > :: AbstractTreeIterator (    /* NOLINT(bugprone-reserved-identifier) */
                AbstractTreeIterator && iterator )
        noexcept :
                _pRoot        ( cds :: exchange ( iterator._pRoot, nullptr ) ),
                _pCurrentNode ( cds :: exchange ( iterator._pCurrentNode, nullptr ) ) {

        }


        template < typename __ElementType >                             /* NOLINT(bugprone-reserved-identifier) */
        auto AbstractTreeIterator < __ElementType > :: operator * (     /* NOLINT(bugprone-reserved-identifier) */
        ) const noexcept -> __ElementType & {

            return this->_pCurrentNode->_data;
        }


        template < typename __ElementType >                             /* NOLINT(bugprone-reserved-identifier) */
        auto AbstractTreeIterator < __ElementType > :: operator -> (    /* NOLINT(bugprone-reserved-identifier) */
        ) const noexcept -> __ElementType * {

            return & this->_pCurrentNode->_data;
        }


        template < typename __ElementType >                             /* NOLINT(bugprone-reserved-identifier) */
        auto AbstractTreeIterator < __ElementType > :: operator == (    /* NOLINT(bugprone-reserved-identifier) */
                AbstractTreeIterator const & iterator
        ) const noexcept -> bool {

            return this->_pCurrentNode == iterator._pCurrentNode;
        }


        template < typename __ElementType >                             /* NOLINT(bugprone-reserved-identifier) */
        auto AbstractTreeIterator < __ElementType > :: operator != (    /* NOLINT(bugprone-reserved-identifier) */
                AbstractTreeIterator const & iterator
        ) const noexcept -> bool {

            return ! this->operator== ( iterator );
        }


        template < typename __ElementType >                                             /* NOLINT(bugprone-reserved-identifier) */
        AbstractTreeIterator < __ElementType > :: operator bool () const noexcept {     /* NOLINT(bugprone-reserved-identifier) */

            return this->_pCurrentNode != nullptr;
        }


        template < typename __ElementType >                                             /* NOLINT(bugprone-reserved-identifier) */
        auto AbstractTreeIterator < __ElementType > :: advance () noexcept -> void {    /* NOLINT(bugprone-reserved-identifier) */

            auto const pEndNode = & __hidden :: __impl :: __RedBlackTreeEndNodeContainer < __ElementType > :: __endNode.data();

            if ( this->_pCurrentNode->_pRight != pEndNode ) {
                this->_pCurrentNode = this->_pCurrentNode->_pRight;
                while ( this->_pCurrentNode->_pLeft != pEndNode ) {
                    this->_pCurrentNode = this->_pCurrentNode->_pLeft;
                }

                return;
            }

            if ( this->_pCurrentNode == this->_pRoot ) {
                this->_pCurrentNode = nullptr;
                return;
            }

            while ( this->_pCurrentNode == this->_pCurrentNode->_pParent->_pRight ) {
                this->_pCurrentNode = this->_pCurrentNode->_pParent;
                if ( this->_pCurrentNode == this->_pRoot ) {
                    this->_pCurrentNode = nullptr;
                    return;
                }
            }
            
            this->_pCurrentNode = this->_pCurrentNode->_pParent;

        }


        template < typename __ElementType >                                           /* NOLINT(bugprone-reserved-identifier) */
        auto AbstractTreeIterator < __ElementType > :: reverse () noexcept -> void {  /* NOLINT(bugprone-reserved-identifier) */

            auto const pEndNode = & __hidden :: __impl :: __RedBlackTreeEndNodeContainer < __ElementType > :: __endNode.data();

            if ( this->_pCurrentNode->_pLeft != pEndNode ) {
                this->_pCurrentNode = this->_pCurrentNode->_pLeft;
                while ( this->_pCurrentNode->_pRight != pEndNode ) {
                    this->_pCurrentNode = this->_pCurrentNode->_pRight;
                }

                return;
            }

            if ( this->_pCurrentNode == this->_pRoot ) {
                this->_pCurrentNode = nullptr;
                return;
            }

            while ( this->_pCurrentNode == this->_pCurrentNode->_pParent->_pLeft ) {
                this->_pCurrentNode = this->_pCurrentNode->_pParent;
                if ( this->_pCurrentNode == this->_pRoot ) {
                    this->_pCurrentNode = nullptr;
                    return;
                }
            }

            this->_pCurrentNode = this->_pCurrentNode->_pParent;
        }



        template < typename __ElementType >                                                                 /* NOLINT(bugprone-reserved-identifier) */
        AbstractTreeConstIterator < __ElementType > :: AbstractTreeConstIterator () noexcept = default;     /* NOLINT(bugprone-reserved-identifier) */


        template < typename __ElementType >                                                                 /* NOLINT(bugprone-reserved-identifier) */
        AbstractTreeConstIterator < __ElementType > :: AbstractTreeConstIterator (                          /* NOLINT(bugprone-reserved-identifier) */
                RBTreeNode const * pRoot,
                RBTreeNode const * pCurrentNode
        ) noexcept :
                _pRoot ( pRoot ),
                _pCurrentNode ( pCurrentNode ) {

        }


        template < typename __ElementType >                                                 /* NOLINT(bugprone-reserved-identifier) */
        AbstractTreeConstIterator < __ElementType > :: AbstractTreeConstIterator (          /* NOLINT(bugprone-reserved-identifier) */
                AbstractTreeConstIterator const & iterator
        ) noexcept :
                _pRoot ( iterator._pRoot ),
                _pCurrentNode ( iterator._pCurrentNode ) {

        }


        template < typename __ElementType >                                         /* NOLINT(bugprone-reserved-identifier) */
        AbstractTreeConstIterator < __ElementType > :: AbstractTreeConstIterator (  /* NOLINT(bugprone-reserved-identifier) */
                AbstractTreeConstIterator && iterator )
        noexcept :
                _pRoot        ( cds :: exchange ( iterator._pRoot, nullptr ) ),
                _pCurrentNode ( cds :: exchange ( iterator._pCurrentNode, nullptr ) ) {

        }


        template < typename __ElementType >                                 /* NOLINT(bugprone-reserved-identifier) */
        auto AbstractTreeConstIterator < __ElementType > :: operator * (    /* NOLINT(bugprone-reserved-identifier) */
        ) const noexcept -> __ElementType const & {

            return this->_pCurrentNode->_data;
        }


        template < typename __ElementType >                                 /* NOLINT(bugprone-reserved-identifier) */
        auto AbstractTreeConstIterator < __ElementType > :: operator -> (   /* NOLINT(bugprone-reserved-identifier) */
        ) const noexcept -> __ElementType const * {

            return & this->_pCurrentNode->_data;
        }


        template < typename __ElementType >                                 /* NOLINT(bugprone-reserved-identifier) */
        auto AbstractTreeConstIterator < __ElementType > :: operator == (   /* NOLINT(bugprone-reserved-identifier) */
                AbstractTreeConstIterator const & iterator
        ) const noexcept -> bool {

            return this->_pCurrentNode == iterator._pCurrentNode;
        }


        template < typename __ElementType >                                 /* NOLINT(bugprone-reserved-identifier) */
        auto AbstractTreeConstIterator < __ElementType > :: operator != (   /* NOLINT(bugprone-reserved-identifier) */
                AbstractTreeConstIterator const & iterator
        ) const noexcept -> bool {

            return ! this->operator== ( iterator );
        }


        template < typename __ElementType >                                                 /* NOLINT(bugprone-reserved-identifier) */
        AbstractTreeConstIterator < __ElementType > :: operator bool () const noexcept {    /* NOLINT(bugprone-reserved-identifier) */

            return this->_pCurrentNode != nullptr;
        }


        template < typename __ElementType >                                                  /* NOLINT(bugprone-reserved-identifier) */
        auto AbstractTreeConstIterator < __ElementType > :: advance () noexcept -> void {    /* NOLINT(bugprone-reserved-identifier) */

            auto const pEndNode = & __hidden :: __impl :: __RedBlackTreeEndNodeContainer < __ElementType > :: __endNode.data();

            if ( this->_pCurrentNode->_pRight != pEndNode ) {
                this->_pCurrentNode = this->_pCurrentNode->_pRight;
                while ( this->_pCurrentNode->_pLeft != pEndNode ) {
                    this->_pCurrentNode = this->_pCurrentNode->_pLeft;
                }

                return;
            }

            if ( this->_pCurrentNode == this->_pRoot ) {
                this->_pCurrentNode = nullptr;
                return;
            }

            while ( this->_pCurrentNode == this->_pCurrentNode->_pParent->_pRight ) {
                this->_pCurrentNode = this->_pCurrentNode->_pParent;
                if ( this->_pCurrentNode == this->_pRoot ) {
                    this->_pCurrentNode = nullptr;
                    return;
                }
            }

            this->_pCurrentNode = this->_pCurrentNode->_pParent;
        }


        template < typename __ElementType >                                                /* NOLINT(bugprone-reserved-identifier) */
        auto AbstractTreeConstIterator < __ElementType > :: reverse () noexcept -> void {  /* NOLINT(bugprone-reserved-identifier) */

            auto const pEndNode = & __hidden :: __impl :: __RedBlackTreeEndNodeContainer < __ElementType > :: __endNode.data();

            if ( this->_pCurrentNode->_pLeft != pEndNode ) {
                this->_pCurrentNode = this->_pCurrentNode->_pLeft;
                while ( this->_pCurrentNode->_pRight != pEndNode ) {
                    this->_pCurrentNode = this->_pCurrentNode->_pRight;
                }

                return;
            }

            if ( this->_pCurrentNode == this->_pRoot ) {
                this->_pCurrentNode = nullptr;
                return;
            }

            while ( this->_pCurrentNode == this->_pCurrentNode->_pParent->_pLeft ) {
                this->_pCurrentNode = this->_pCurrentNode->_pParent;
                if ( this->_pCurrentNode == this->_pRoot ) {
                    this->_pCurrentNode = nullptr;
                    return;
                }
            }

            this->_pCurrentNode = this->_pCurrentNode->_pParent;
        }


        template < typename __ElementType >                                                                   /* NOLINT(bugprone-reserved-identifier) */
        RedBlackTreeForwardIterator < __ElementType > :: RedBlackTreeForwardIterator () noexcept = default;   /* NOLINT(bugprone-reserved-identifier) */


        template < typename __ElementType >                                               /* NOLINT(bugprone-reserved-identifier) */
        RedBlackTreeForwardIterator < __ElementType > :: RedBlackTreeForwardIterator (    /* NOLINT(bugprone-reserved-identifier) */
                RBTreeNode  *  pRoot,
                RBTreeNode  *  pCurrentNode
        ) noexcept :
                AbstractTreeIterator < __ElementType > (
                        pRoot,
                        pCurrentNode
                ) {

        }


        template < typename __ElementType >                                             /* NOLINT(bugprone-reserved-identifier) */
        RedBlackTreeForwardIterator < __ElementType > :: RedBlackTreeForwardIterator (  /* NOLINT(bugprone-reserved-identifier) */
                const RedBlackTreeForwardIterator & iterator
        ) noexcept :
                AbstractTreeIterator < __ElementType > ( iterator ) {

        }


        template < typename __ElementType >                                             /* NOLINT(bugprone-reserved-identifier) */
        RedBlackTreeForwardIterator < __ElementType > :: RedBlackTreeForwardIterator (  /* NOLINT(bugprone-reserved-identifier) */
                RedBlackTreeForwardIterator && iterator
        ) noexcept :
                AbstractTreeIterator < __ElementType > ( std :: move ( iterator ) ) {

        }


        template < typename __ElementType >                                 /* NOLINT(bugprone-reserved-identifier) */
        auto RedBlackTreeForwardIterator < __ElementType > :: operator = (  /* NOLINT(bugprone-reserved-identifier) */
                RedBlackTreeForwardIterator const & iterator
        ) noexcept -> RedBlackTreeForwardIterator & {

            if ( this == & iterator ) {
                return * this;
            }

            this->_pRoot        = iterator._pRoot;
            this->_pCurrentNode = iterator._pCurrentNode;

            return * this;
        }


        template < typename __ElementType >                                 /* NOLINT(bugprone-reserved-identifier) */
        auto RedBlackTreeForwardIterator < __ElementType > :: operator = (  /* NOLINT(bugprone-reserved-identifier) */
                RedBlackTreeForwardIterator && iterator
        ) noexcept -> RedBlackTreeForwardIterator & {

            if ( this == & iterator ) {
                return * this;
            }

            this->_pRoot        = cds :: exchange ( iterator._pRoot, nullptr );
            this->_pCurrentNode = cds :: exchange ( iterator._pCurrentNode, nullptr );

            return * this;
        }


        template < typename __ElementType >                                 /* NOLINT(bugprone-reserved-identifier) */
        auto RedBlackTreeForwardIterator < __ElementType > :: operator ++ ( /* NOLINT(bugprone-reserved-identifier) */
        ) noexcept -> RedBlackTreeForwardIterator & {

            this->advance();
            return * this;
        }


        template < typename __ElementType >                                                                                 /* NOLINT(bugprone-reserved-identifier) */
        auto RedBlackTreeForwardIterator < __ElementType > :: operator ++ (int) noexcept -> RedBlackTreeForwardIterator {   /* NOLINT(bugprone-reserved-identifier) */

            auto copy = * this;
            ++ ( * this );
            return copy;
        }


        template < typename __ElementType >                                 /* NOLINT(bugprone-reserved-identifier) */
        auto RedBlackTreeForwardIterator < __ElementType > :: operator -- ( /* NOLINT(bugprone-reserved-identifier) */
        ) noexcept -> RedBlackTreeForwardIterator & {

            this->reverse();
            return * this;
        }


        template < typename __ElementType >                                                                                 /* NOLINT(bugprone-reserved-identifier) */
        auto RedBlackTreeForwardIterator < __ElementType > :: operator -- (int) noexcept -> RedBlackTreeForwardIterator {   /* NOLINT(bugprone-reserved-identifier) */

            auto copy = *this;
            -- ( * this );
            return copy;
        }


        template < typename __ElementType >                                                                             /* NOLINT(bugprone-reserved-identifier) */
        RedBlackTreeForwardConstIterator < __ElementType > :: RedBlackTreeForwardConstIterator () noexcept = default;   /* NOLINT(bugprone-reserved-identifier) */


        template < typename __ElementType >                                                         /* NOLINT(bugprone-reserved-identifier) */
        RedBlackTreeForwardConstIterator < __ElementType > :: RedBlackTreeForwardConstIterator (    /* NOLINT(bugprone-reserved-identifier) */
                RBTreeNode const  *  pRoot,
                RBTreeNode const  *  pCurrentNode
        ) noexcept :
                AbstractTreeConstIterator < __ElementType > (
                        pRoot,
                        pCurrentNode
                ) {

        }


        template < typename __ElementType >                                                         /* NOLINT(bugprone-reserved-identifier) */
        RedBlackTreeForwardConstIterator < __ElementType > :: RedBlackTreeForwardConstIterator (    /* NOLINT(bugprone-reserved-identifier) */
                const RedBlackTreeForwardConstIterator & iterator
        ) noexcept :
                AbstractTreeConstIterator < __ElementType > ( iterator) {

        }


        template < typename __ElementType >                                                         /* NOLINT(bugprone-reserved-identifier) */
        RedBlackTreeForwardConstIterator < __ElementType > :: RedBlackTreeForwardConstIterator (    /* NOLINT(bugprone-reserved-identifier) */
                RedBlackTreeForwardConstIterator && iterator
        ) noexcept :
                AbstractTreeConstIterator < __ElementType > ( std :: move ( iterator ) ) {

        }


        template < typename __ElementType >                                         /* NOLINT(bugprone-reserved-identifier) */
        auto RedBlackTreeForwardConstIterator < __ElementType > :: operator = (     /* NOLINT(bugprone-reserved-identifier) */
                RedBlackTreeForwardConstIterator const & iterator
        ) noexcept -> RedBlackTreeForwardConstIterator & {

            if ( this == & iterator ) {
                return * this;
            }

            this->_pRoot        = iterator._pRoot;
            this->_pCurrentNode = iterator._pCurrentNode;

            return * this;
        }


        template < typename __ElementType >                                         /* NOLINT(bugprone-reserved-identifier) */
        auto RedBlackTreeForwardConstIterator < __ElementType > :: operator = (     /* NOLINT(bugprone-reserved-identifier) */
                RedBlackTreeForwardConstIterator && iterator
        ) noexcept -> RedBlackTreeForwardConstIterator & {

            if ( this == & iterator ) {
                return * this;
            }

            this->_pRoot        = cds :: exchange ( iterator._pRoot, nullptr );
            this->_pCurrentNode = cds :: exchange ( iterator._pCurrentNode, nullptr );

            return * this;
        }


        template < typename __ElementType >                                         /* NOLINT(bugprone-reserved-identifier) */
        auto RedBlackTreeForwardConstIterator < __ElementType > :: operator ++ (    /* NOLINT(bugprone-reserved-identifier) */
        ) noexcept -> RedBlackTreeForwardConstIterator & {

            this->advance();
            return * this;
        }


        template < typename __ElementType >                                                                                             /* NOLINT(bugprone-reserved-identifier) */
        auto RedBlackTreeForwardConstIterator < __ElementType > :: operator ++ (int) noexcept -> RedBlackTreeForwardConstIterator {     /* NOLINT(bugprone-reserved-identifier) */

            auto copy = * this;
            ++ ( * this );
            return copy;
        }


        template < typename __ElementType >                                         /* NOLINT(bugprone-reserved-identifier) */
        auto RedBlackTreeForwardConstIterator < __ElementType > :: operator -- (    /* NOLINT(bugprone-reserved-identifier) */
        ) noexcept -> RedBlackTreeForwardConstIterator & {

            this->reverse();
            return * this;
        }


        template < typename __ElementType >                                                                                             /* NOLINT(bugprone-reserved-identifier) */
        auto RedBlackTreeForwardConstIterator < __ElementType > :: operator -- (int) noexcept -> RedBlackTreeForwardConstIterator {     /* NOLINT(bugprone-reserved-identifier) */

            auto copy = *this;
            -- ( * this );
            return copy;
        }


        template < typename __ElementType >                                                                     /* NOLINT(bugprone-reserved-identifier) */
        RedBlackTreeBackwardIterator < __ElementType > :: RedBlackTreeBackwardIterator () noexcept = default;   /* NOLINT(bugprone-reserved-identifier) */


        template < typename __ElementType >                                                 /* NOLINT(bugprone-reserved-identifier) */
        RedBlackTreeBackwardIterator < __ElementType > :: RedBlackTreeBackwardIterator (    /* NOLINT(bugprone-reserved-identifier) */
                RBTreeNode  *  pRoot,
                RBTreeNode  *  pCurrentNode
        ) noexcept :
                AbstractTreeIterator < __ElementType > (
                        pRoot,
                        pCurrentNode
                ) {

        }


        template < typename __ElementType >                                                 /* NOLINT(bugprone-reserved-identifier) */
        RedBlackTreeBackwardIterator < __ElementType > :: RedBlackTreeBackwardIterator (    /* NOLINT(bugprone-reserved-identifier) */
                const RedBlackTreeBackwardIterator & iterator
        ) noexcept :
                AbstractTreeIterator < __ElementType > ( iterator ) {

        }


        template < typename __ElementType >                                                 /* NOLINT(bugprone-reserved-identifier) */
        RedBlackTreeBackwardIterator < __ElementType > :: RedBlackTreeBackwardIterator (    /* NOLINT(bugprone-reserved-identifier) */
                RedBlackTreeBackwardIterator && iterator
        ) noexcept :
                AbstractTreeIterator < __ElementType > ( std :: move ( iterator ) ) {

        }


        template < typename __ElementType >                                     /* NOLINT(bugprone-reserved-identifier) */
        auto RedBlackTreeBackwardIterator < __ElementType > :: operator = (     /* NOLINT(bugprone-reserved-identifier) */
                RedBlackTreeBackwardIterator const & iterator
        ) noexcept -> RedBlackTreeBackwardIterator & {

            if ( this == & iterator ) {
                return * this;
            }

            this->_pRoot        = iterator._pRoot;
            this->_pCurrentNode = iterator._pCurrentNode;

            return * this;
        }


        template < typename __ElementType >                                     /* NOLINT(bugprone-reserved-identifier) */
        auto RedBlackTreeBackwardIterator < __ElementType > :: operator = (     /* NOLINT(bugprone-reserved-identifier) */
                RedBlackTreeBackwardIterator && iterator
        ) noexcept -> RedBlackTreeBackwardIterator & {

            if ( this == & iterator ) {
                return * this;
            }

            this->_pRoot        = cds :: exchange ( iterator._pRoot, nullptr );
            this->_pCurrentNode = cds :: exchange ( iterator._pCurrentNode, nullptr );

            return * this;
        }


        template < typename __ElementType >                                     /* NOLINT(bugprone-reserved-identifier) */
        auto RedBlackTreeBackwardIterator < __ElementType > :: operator ++ (    /* NOLINT(bugprone-reserved-identifier) */
        ) noexcept -> RedBlackTreeBackwardIterator & {

            this->reverse();
            return * this;
        }


        template < typename __ElementType >                                                                                     /* NOLINT(bugprone-reserved-identifier) */
        auto RedBlackTreeBackwardIterator < __ElementType > :: operator ++ (int) noexcept -> RedBlackTreeBackwardIterator {     /* NOLINT(bugprone-reserved-identifier) */

            auto copy = * this;
            ++ ( * this );
            return copy;
        }


        template < typename __ElementType >                                     /* NOLINT(bugprone-reserved-identifier) */
        auto RedBlackTreeBackwardIterator < __ElementType > :: operator -- (    /* NOLINT(bugprone-reserved-identifier) */
        ) noexcept -> RedBlackTreeBackwardIterator & {

            this->advance();
            return * this;
        }


        template < typename __ElementType >                                                                                     /* NOLINT(bugprone-reserved-identifier) */
        auto RedBlackTreeBackwardIterator < __ElementType > :: operator -- (int) noexcept -> RedBlackTreeBackwardIterator {     /* NOLINT(bugprone-reserved-identifier) */

            auto copy = *this;
            -- ( * this );
            return copy;
        }


        template < typename __ElementType >                                                                             /* NOLINT(bugprone-reserved-identifier) */
        RedBlackTreeBackwardConstIterator < __ElementType > :: RedBlackTreeBackwardConstIterator () noexcept = default; /* NOLINT(bugprone-reserved-identifier) */


        template < typename __ElementType >                                                         /* NOLINT(bugprone-reserved-identifier) */
        RedBlackTreeBackwardConstIterator < __ElementType > :: RedBlackTreeBackwardConstIterator (  /* NOLINT(bugprone-reserved-identifier) */
                RBTreeNode const  *  pRoot,
                RBTreeNode const  *  pCurrentNode
        ) noexcept :
                AbstractTreeConstIterator < __ElementType > (
                        pRoot,
                        pCurrentNode
                ) {

        }


        template < typename __ElementType >                                                         /* NOLINT(bugprone-reserved-identifier) */
        RedBlackTreeBackwardConstIterator < __ElementType > :: RedBlackTreeBackwardConstIterator (  /* NOLINT(bugprone-reserved-identifier) */
                const RedBlackTreeBackwardConstIterator & iterator
        ) noexcept :
                AbstractTreeConstIterator < __ElementType > ( iterator) {

        }


        template < typename __ElementType >                                                         /* NOLINT(bugprone-reserved-identifier) */
        RedBlackTreeBackwardConstIterator < __ElementType > :: RedBlackTreeBackwardConstIterator (  /* NOLINT(bugprone-reserved-identifier) */
                RedBlackTreeBackwardConstIterator && iterator
        ) noexcept :
                AbstractTreeConstIterator < __ElementType > ( std :: move ( iterator ) ) {

        }


        template < typename __ElementType >                                         /* NOLINT(bugprone-reserved-identifier) */
        auto RedBlackTreeBackwardConstIterator < __ElementType > :: operator = (    /* NOLINT(bugprone-reserved-identifier) */
                RedBlackTreeBackwardConstIterator const & iterator
        ) noexcept -> RedBlackTreeBackwardConstIterator & {

            if ( this == & iterator ) {
                return * this;
            }

            this->_pRoot        = iterator._pRoot;
            this->_pCurrentNode = iterator._pCurrentNode;

            return * this;
        }


        template < typename __ElementType >                                         /* NOLINT(bugprone-reserved-identifier) */
        auto RedBlackTreeBackwardConstIterator < __ElementType > :: operator = (    /* NOLINT(bugprone-reserved-identifier) */
                RedBlackTreeBackwardConstIterator && iterator
        ) noexcept -> RedBlackTreeBackwardConstIterator & {

            if ( this == & iterator ) {
                return * this;
            }

            this->_pRoot        = cds :: exchange ( iterator._pRoot, nullptr );
            this->_pCurrentNode = cds :: exchange ( iterator._pCurrentNode, nullptr );

            return * this;
        }


        template < typename __ElementType >                                         /* NOLINT(bugprone-reserved-identifier) */
        auto RedBlackTreeBackwardConstIterator < __ElementType > :: operator ++ (   /* NOLINT(bugprone-reserved-identifier) */
        ) noexcept -> RedBlackTreeBackwardConstIterator & {

            this->reverse();
            return * this;
        }


        template < typename __ElementType >                                                                                             /* NOLINT(bugprone-reserved-identifier) */
        auto RedBlackTreeBackwardConstIterator < __ElementType > :: operator ++ (int) noexcept -> RedBlackTreeBackwardConstIterator {   /* NOLINT(bugprone-reserved-identifier) */

            auto copy = * this;
            ++ ( * this );
            return copy;
        }


        template < typename __ElementType >                                         /* NOLINT(bugprone-reserved-identifier) */
        auto RedBlackTreeBackwardConstIterator < __ElementType > :: operator -- (   /* NOLINT(bugprone-reserved-identifier) */
        ) noexcept -> RedBlackTreeBackwardConstIterator & {

            this->advance();
            return * this;
        }


        template < typename __ElementType >                                                                                             /* NOLINT(bugprone-reserved-identifier) */
        auto RedBlackTreeBackwardConstIterator < __ElementType > :: operator -- (int) noexcept -> RedBlackTreeBackwardConstIterator {   /* NOLINT(bugprone-reserved-identifier) */

            auto copy = *this;
            -- ( * this );
            return copy;
        }
    }
}

#endif /* __CDS_EX_SHARED_RED_BLACK_TREE_ITERATOR_IMPL_HPP__ */
