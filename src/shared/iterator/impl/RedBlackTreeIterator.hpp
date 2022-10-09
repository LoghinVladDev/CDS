/*
 * Created by stefan on 16.08.2022.
 */

#ifndef __CDS_SHARED_RED_BLACK_TREE_ITERATOR_IMPL_HPP__
#define __CDS_SHARED_RED_BLACK_TREE_ITERATOR_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */

    template < typename __ElementType >                                                                             /* NOLINT(bugprone-reserved-identifier) */
    constexpr AbstractRedBlackTreeIterator < __ElementType > :: AbstractRedBlackTreeIterator () noexcept = default; /* NOLINT(bugprone-reserved-identifier) */


    template < typename __ElementType >                                                         /* NOLINT(bugprone-reserved-identifier) */
    constexpr AbstractRedBlackTreeIterator < __ElementType > :: AbstractRedBlackTreeIterator (  /* NOLINT(bugprone-reserved-identifier) */
            RBTreeNode * pRoot,
            RBTreeNode * pCurrentNode
    ) noexcept :
            _pRoot ( pRoot ),
            _pCurrentNode ( pCurrentNode ) {

    }


    template < typename __ElementType >                                                         /* NOLINT(bugprone-reserved-identifier) */
    constexpr AbstractRedBlackTreeIterator < __ElementType > :: AbstractRedBlackTreeIterator (  /* NOLINT(bugprone-reserved-identifier) */
            AbstractRedBlackTreeIterator const & iterator
    ) noexcept :
            _pRoot ( iterator._pRoot ),
            _pCurrentNode ( iterator._pCurrentNode ) {

    }


    template < typename __ElementType >                                                         /* NOLINT(bugprone-reserved-identifier) */
    constexpr AbstractRedBlackTreeIterator < __ElementType > :: AbstractRedBlackTreeIterator (  /* NOLINT(bugprone-reserved-identifier) */
            AbstractRedBlackTreeIterator && iterator )
    noexcept :
            _pRoot        ( cds :: exchange ( iterator._pRoot, nullptr ) ),
            _pCurrentNode ( cds :: exchange ( iterator._pCurrentNode, nullptr ) ) {

    }


    template < typename __ElementType >                                                                                 /* NOLINT(bugprone-reserved-identifier) */
    constexpr auto AbstractRedBlackTreeIterator < __ElementType > :: operator * () const noexcept -> __ElementType & {  /* NOLINT(bugprone-reserved-identifier) */

        return this->_pCurrentNode->_data;
    }


    template < typename __ElementType >                                                                                 /* NOLINT(bugprone-reserved-identifier) */
    constexpr auto AbstractRedBlackTreeIterator < __ElementType > :: operator -> () const noexcept -> __ElementType * { /* NOLINT(bugprone-reserved-identifier) */

        return & this->_pCurrentNode->_data;
    }


    template < typename __ElementType >                                             /* NOLINT(bugprone-reserved-identifier) */
    constexpr auto AbstractRedBlackTreeIterator < __ElementType > :: operator == (  /* NOLINT(bugprone-reserved-identifier) */
            AbstractRedBlackTreeIterator const & iterator
    ) const noexcept -> bool {

        return this->_pCurrentNode == iterator._pCurrentNode;
    }


    template < typename __ElementType >                                             /* NOLINT(bugprone-reserved-identifier) */
    constexpr auto AbstractRedBlackTreeIterator < __ElementType > :: operator != (  /* NOLINT(bugprone-reserved-identifier) */
            AbstractRedBlackTreeIterator const & iterator
    ) const noexcept -> bool {

        return ! this->operator== ( iterator );
    }


    template < typename __ElementType >                                                             /* NOLINT(bugprone-reserved-identifier) */
    constexpr AbstractRedBlackTreeIterator < __ElementType > :: operator bool () const noexcept {   /* NOLINT(bugprone-reserved-identifier) */

        return this->_pCurrentNode != nullptr;
    }


    template < typename __ElementType >                                                                                     /* NOLINT(bugprone-reserved-identifier) */
    __CDS_cpplang_ConstexprConditioned auto AbstractRedBlackTreeIterator < __ElementType > :: advance () noexcept -> void { /* NOLINT(bugprone-reserved-identifier) */


        if ( this->_pCurrentNode->_pRight != nullptr ) {
            this->_pCurrentNode = this->_pCurrentNode->_pRight;
            while ( this->_pCurrentNode->_pLeft != nullptr ) {
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


    template < typename __ElementType >                                                                                     /* NOLINT(bugprone-reserved-identifier) */
    __CDS_cpplang_ConstexprConditioned auto AbstractRedBlackTreeIterator < __ElementType > :: reverse () noexcept -> void { /* NOLINT(bugprone-reserved-identifier) */

        if ( this->_pCurrentNode->_pLeft != nullptr ) {
            this->_pCurrentNode = this->_pCurrentNode->_pLeft;
            while ( this->_pCurrentNode->_pRight != nullptr ) {
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



    template < typename __ElementType >                                                                                         /* NOLINT(bugprone-reserved-identifier) */
    constexpr AbstractRedBlackTreeConstIterator < __ElementType > :: AbstractRedBlackTreeConstIterator () noexcept = default;   /* NOLINT(bugprone-reserved-identifier) */


    template < typename __ElementType >                                                                     /* NOLINT(bugprone-reserved-identifier) */
    constexpr AbstractRedBlackTreeConstIterator < __ElementType > :: AbstractRedBlackTreeConstIterator (    /* NOLINT(bugprone-reserved-identifier) */
            RBTreeNode const * pRoot,
            RBTreeNode const * pCurrentNode
    ) noexcept :
            _pRoot ( pRoot ),
            _pCurrentNode ( pCurrentNode ) {

    }


    template < typename __ElementType >                                                                     /* NOLINT(bugprone-reserved-identifier) */
    constexpr AbstractRedBlackTreeConstIterator < __ElementType > :: AbstractRedBlackTreeConstIterator (    /* NOLINT(bugprone-reserved-identifier) */
            AbstractRedBlackTreeConstIterator const & iterator
    ) noexcept :
            _pRoot ( iterator._pRoot ),
            _pCurrentNode ( iterator._pCurrentNode ) {

    }


    template < typename __ElementType >                                                                     /* NOLINT(bugprone-reserved-identifier) */
    constexpr AbstractRedBlackTreeConstIterator < __ElementType > :: AbstractRedBlackTreeConstIterator (    /* NOLINT(bugprone-reserved-identifier) */
            AbstractRedBlackTreeConstIterator && iterator )
    noexcept :
            _pRoot        ( cds :: exchange ( iterator._pRoot, nullptr ) ),
            _pCurrentNode ( cds :: exchange ( iterator._pCurrentNode, nullptr ) ) {

    }


    template < typename __ElementType >                                                 /* NOLINT(bugprone-reserved-identifier) */
    constexpr auto AbstractRedBlackTreeConstIterator < __ElementType > :: operator * (  /* NOLINT(bugprone-reserved-identifier) */
    ) const noexcept -> __ElementType const & {

        return this->_pCurrentNode->_data;
    }


    template < typename __ElementType >                                                 /* NOLINT(bugprone-reserved-identifier) */
    constexpr auto AbstractRedBlackTreeConstIterator < __ElementType > :: operator -> ( /* NOLINT(bugprone-reserved-identifier) */
    ) const noexcept -> __ElementType const * {

        return & this->_pCurrentNode->_data;
    }


    template < typename __ElementType >                                                 /* NOLINT(bugprone-reserved-identifier) */
    constexpr auto AbstractRedBlackTreeConstIterator < __ElementType > :: operator == ( /* NOLINT(bugprone-reserved-identifier) */
            AbstractRedBlackTreeConstIterator const & iterator
    ) const noexcept -> bool {

        return this->_pCurrentNode == iterator._pCurrentNode;
    }


    template < typename __ElementType >                                                 /* NOLINT(bugprone-reserved-identifier) */
    constexpr auto AbstractRedBlackTreeConstIterator < __ElementType > :: operator != ( /* NOLINT(bugprone-reserved-identifier) */
            AbstractRedBlackTreeConstIterator const & iterator
    ) const noexcept -> bool {

        return ! this->operator== ( iterator );
    }


    template < typename __ElementType >                                                                 /* NOLINT(bugprone-reserved-identifier) */
    constexpr AbstractRedBlackTreeConstIterator < __ElementType > :: operator bool () const noexcept {  /* NOLINT(bugprone-reserved-identifier) */

        return this->_pCurrentNode != nullptr;
    }


    template < typename __ElementType >                                                         /* NOLINT(bugprone-reserved-identifier) */
    auto AbstractRedBlackTreeConstIterator < __ElementType > :: advance () noexcept -> void {   /* NOLINT(bugprone-reserved-identifier) */

        if ( this->_pCurrentNode->_pRight != nullptr ) {
            this->_pCurrentNode = this->_pCurrentNode->_pRight;
            while ( this->_pCurrentNode->_pLeft != nullptr ) {
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


    template < typename __ElementType >                                                         /* NOLINT(bugprone-reserved-identifier) */
    auto AbstractRedBlackTreeConstIterator < __ElementType > :: reverse () noexcept -> void {   /* NOLINT(bugprone-reserved-identifier) */

        if ( this->_pCurrentNode->_pLeft != nullptr ) {
            this->_pCurrentNode = this->_pCurrentNode->_pLeft;
            while ( this->_pCurrentNode->_pRight != nullptr ) {
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


    template < typename __ElementType >                                                                             /* NOLINT(bugprone-reserved-identifier) */
    constexpr RedBlackTreeForwardIterator < __ElementType > :: RedBlackTreeForwardIterator () noexcept = default;   /* NOLINT(bugprone-reserved-identifier) */


    template < typename __ElementType >                                                         /* NOLINT(bugprone-reserved-identifier) */
    constexpr RedBlackTreeForwardIterator < __ElementType > :: RedBlackTreeForwardIterator (    /* NOLINT(bugprone-reserved-identifier) */
            RBTreeNode  *  pRoot,
            RBTreeNode  *  pCurrentNode
    ) noexcept :
            AbstractRedBlackTreeIterator < __ElementType > (
                    pRoot,
                    pCurrentNode
            ) {

    }


    template < typename __ElementType >                                                         /* NOLINT(bugprone-reserved-identifier) */
    constexpr RedBlackTreeForwardIterator < __ElementType > :: RedBlackTreeForwardIterator (    /* NOLINT(bugprone-reserved-identifier) */
            const RedBlackTreeForwardIterator & iterator
    ) noexcept :
            AbstractRedBlackTreeIterator < __ElementType > ( iterator ) {

    }


    template < typename __ElementType >                                                         /* NOLINT(bugprone-reserved-identifier) */
    constexpr RedBlackTreeForwardIterator < __ElementType > :: RedBlackTreeForwardIterator (    /* NOLINT(bugprone-reserved-identifier) */
            RedBlackTreeForwardIterator && iterator
    ) noexcept :
            AbstractRedBlackTreeIterator < __ElementType > ( std :: move ( iterator ) ) {

    }


    template < typename __ElementType >                                                                                 /* NOLINT(bugprone-reserved-identifier) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto RedBlackTreeForwardIterator < __ElementType > :: operator = (    /* NOLINT(bugprone-reserved-identifier) */
            RedBlackTreeForwardIterator const & iterator
    ) noexcept -> RedBlackTreeForwardIterator & {

        if ( this == & iterator ) {
            return * this;
        }

        this->_pRoot        = iterator._pRoot;
        this->_pCurrentNode = iterator._pCurrentNode;

        return * this;
    }


    template < typename __ElementType >                                                                                 /* NOLINT(bugprone-reserved-identifier) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto RedBlackTreeForwardIterator < __ElementType > :: operator = (    /* NOLINT(bugprone-reserved-identifier) */
            RedBlackTreeForwardIterator && iterator
    ) noexcept -> RedBlackTreeForwardIterator & {

        if ( this == & iterator ) {
            return * this;
        }

        this->_pRoot        = cds :: exchange ( iterator._pRoot, nullptr );
        this->_pCurrentNode = cds :: exchange ( iterator._pCurrentNode, nullptr );

        return * this;
    }


    template < typename __ElementType >                                                                                 /* NOLINT(bugprone-reserved-identifier) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto RedBlackTreeForwardIterator < __ElementType > :: operator ++ (   /* NOLINT(bugprone-reserved-identifier) */
    ) noexcept -> RedBlackTreeForwardIterator & {

        this->advance();
        return * this;
    }


    template < typename __ElementType >                                                                                                                                 /* NOLINT(bugprone-reserved-identifier) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto RedBlackTreeForwardIterator < __ElementType > :: operator ++ (int) noexcept -> RedBlackTreeForwardIterator {     /* NOLINT(bugprone-reserved-identifier) */

        auto copy = * this;
        ++ ( * this );
        return copy;
    }


    template < typename __ElementType >                                                                                 /* NOLINT(bugprone-reserved-identifier) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto RedBlackTreeForwardIterator < __ElementType > :: operator -- (   /* NOLINT(bugprone-reserved-identifier) */
    ) noexcept -> RedBlackTreeForwardIterator & {

        this->reverse();
        return * this;
    }


    template < typename __ElementType >                                                                                                                                 /* NOLINT(bugprone-reserved-identifier) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto RedBlackTreeForwardIterator < __ElementType > :: operator -- (int) noexcept -> RedBlackTreeForwardIterator {     /* NOLINT(bugprone-reserved-identifier) */

        auto copy = *this;
        -- ( * this );
        return copy;
    }


    template < typename __ElementType >                                                                                         /* NOLINT(bugprone-reserved-identifier) */
    constexpr RedBlackTreeForwardConstIterator < __ElementType > :: RedBlackTreeForwardConstIterator () noexcept = default;     /* NOLINT(bugprone-reserved-identifier) */


    template < typename __ElementType >                                                                     /* NOLINT(bugprone-reserved-identifier) */
    constexpr RedBlackTreeForwardConstIterator < __ElementType > :: RedBlackTreeForwardConstIterator (      /* NOLINT(bugprone-reserved-identifier) */
            RBTreeNode const  *  pRoot,
            RBTreeNode const  *  pCurrentNode
    ) noexcept :
            AbstractRedBlackTreeConstIterator < __ElementType > (
                    pRoot,
                    pCurrentNode
            ) {

    }


    template < typename __ElementType >                                                                     /* NOLINT(bugprone-reserved-identifier) */
    constexpr RedBlackTreeForwardConstIterator < __ElementType > :: RedBlackTreeForwardConstIterator (      /* NOLINT(bugprone-reserved-identifier) */
            const RedBlackTreeForwardConstIterator & iterator
    ) noexcept :
            AbstractRedBlackTreeConstIterator < __ElementType > ( iterator) {

    }


    template < typename __ElementType >                                                                     /* NOLINT(bugprone-reserved-identifier) */
    constexpr RedBlackTreeForwardConstIterator < __ElementType > :: RedBlackTreeForwardConstIterator (      /* NOLINT(bugprone-reserved-identifier) */
            RedBlackTreeForwardConstIterator && iterator
    ) noexcept :
            AbstractRedBlackTreeConstIterator < __ElementType > ( std :: move ( iterator ) ) {

    }


    template < typename __ElementType >                                                                                         /* NOLINT(bugprone-reserved-identifier) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto RedBlackTreeForwardConstIterator < __ElementType > :: operator = (       /* NOLINT(bugprone-reserved-identifier) */
            RedBlackTreeForwardConstIterator const & iterator
    ) noexcept -> RedBlackTreeForwardConstIterator & {

        if ( this == & iterator ) {
            return * this;
        }

        this->_pRoot        = iterator._pRoot;
        this->_pCurrentNode = iterator._pCurrentNode;

        return * this;
    }


    template < typename __ElementType >                                                                                         /* NOLINT(bugprone-reserved-identifier) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto RedBlackTreeForwardConstIterator < __ElementType > :: operator = (       /* NOLINT(bugprone-reserved-identifier) */
            RedBlackTreeForwardConstIterator && iterator
    ) noexcept -> RedBlackTreeForwardConstIterator & {

        if ( this == & iterator ) {
            return * this;
        }

        this->_pRoot        = cds :: exchange ( iterator._pRoot, nullptr );
        this->_pCurrentNode = cds :: exchange ( iterator._pCurrentNode, nullptr );

        return * this;
    }


    template < typename __ElementType >                                                                                         /* NOLINT(bugprone-reserved-identifier) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto RedBlackTreeForwardConstIterator < __ElementType > :: operator ++ (      /* NOLINT(bugprone-reserved-identifier) */
    ) noexcept -> RedBlackTreeForwardConstIterator & {

        this->advance();
        return * this;
    }


    template < typename __ElementType >                                                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto RedBlackTreeForwardConstIterator < __ElementType > :: operator ++ (int) noexcept -> RedBlackTreeForwardConstIterator {       /* NOLINT(bugprone-reserved-identifier) */

        auto copy = * this;
        ++ ( * this );
        return copy;
    }


    template < typename __ElementType >                                                                                         /* NOLINT(bugprone-reserved-identifier) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto RedBlackTreeForwardConstIterator < __ElementType > :: operator -- (      /* NOLINT(bugprone-reserved-identifier) */
    ) noexcept -> RedBlackTreeForwardConstIterator & {

        this->reverse();
        return * this;
    }


    template < typename __ElementType >                                                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto RedBlackTreeForwardConstIterator < __ElementType > :: operator -- (int) noexcept -> RedBlackTreeForwardConstIterator {       /* NOLINT(bugprone-reserved-identifier) */

        auto copy = *this;
        -- ( * this );
        return copy;
    }


    template < typename __ElementType >                                                                                 /* NOLINT(bugprone-reserved-identifier) */
    constexpr RedBlackTreeBackwardIterator < __ElementType > :: RedBlackTreeBackwardIterator () noexcept = default;     /* NOLINT(bugprone-reserved-identifier) */


    template < typename __ElementType >                                                             /* NOLINT(bugprone-reserved-identifier) */
    constexpr RedBlackTreeBackwardIterator < __ElementType > :: RedBlackTreeBackwardIterator (      /* NOLINT(bugprone-reserved-identifier) */
            RBTreeNode  *  pRoot,
            RBTreeNode  *  pCurrentNode
    ) noexcept :
            AbstractRedBlackTreeIterator < __ElementType > (
                    pRoot,
                    pCurrentNode
            ) {

    }


    template < typename __ElementType >                                                             /* NOLINT(bugprone-reserved-identifier) */
    constexpr RedBlackTreeBackwardIterator < __ElementType > :: RedBlackTreeBackwardIterator (      /* NOLINT(bugprone-reserved-identifier) */
            const RedBlackTreeBackwardIterator & iterator
    ) noexcept :
            AbstractRedBlackTreeIterator < __ElementType > ( iterator ) {

    }


    template < typename __ElementType >                                                             /* NOLINT(bugprone-reserved-identifier) */
    constexpr RedBlackTreeBackwardIterator < __ElementType > :: RedBlackTreeBackwardIterator (      /* NOLINT(bugprone-reserved-identifier) */
            RedBlackTreeBackwardIterator && iterator
    ) noexcept :
            AbstractRedBlackTreeIterator < __ElementType > ( std :: move ( iterator ) ) {

    }


    template < typename __ElementType >                                                                                     /* NOLINT(bugprone-reserved-identifier) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto RedBlackTreeBackwardIterator < __ElementType > :: operator = (       /* NOLINT(bugprone-reserved-identifier) */
            RedBlackTreeBackwardIterator const & iterator
    ) noexcept -> RedBlackTreeBackwardIterator & {

        if ( this == & iterator ) {
            return * this;
        }

        this->_pRoot        = iterator._pRoot;
        this->_pCurrentNode = iterator._pCurrentNode;

        return * this;
    }


    template < typename __ElementType >                                                                                     /* NOLINT(bugprone-reserved-identifier) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto RedBlackTreeBackwardIterator < __ElementType > :: operator = (       /* NOLINT(bugprone-reserved-identifier) */
            RedBlackTreeBackwardIterator && iterator
    ) noexcept -> RedBlackTreeBackwardIterator & {

        if ( this == & iterator ) {
            return * this;
        }

        this->_pRoot        = cds :: exchange ( iterator._pRoot, nullptr );
        this->_pCurrentNode = cds :: exchange ( iterator._pCurrentNode, nullptr );

        return * this;
    }


    template < typename __ElementType >                                                                                     /* NOLINT(bugprone-reserved-identifier) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto RedBlackTreeBackwardIterator < __ElementType > :: operator ++ (      /* NOLINT(bugprone-reserved-identifier) */
    ) noexcept -> RedBlackTreeBackwardIterator & {

        this->reverse();
        return * this;
    }


    template < typename __ElementType >                                                                                                                                     /* NOLINT(bugprone-reserved-identifier) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto RedBlackTreeBackwardIterator < __ElementType > :: operator ++ (int) noexcept -> RedBlackTreeBackwardIterator {       /* NOLINT(bugprone-reserved-identifier) */

        auto copy = * this;
        ++ ( * this );
        return copy;
    }


    template < typename __ElementType >                                                                                     /* NOLINT(bugprone-reserved-identifier) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto RedBlackTreeBackwardIterator < __ElementType > :: operator -- (      /* NOLINT(bugprone-reserved-identifier) */
    ) noexcept -> RedBlackTreeBackwardIterator & {

        this->advance();
        return * this;
    }


    template < typename __ElementType >                                                                                                                                     /* NOLINT(bugprone-reserved-identifier) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto RedBlackTreeBackwardIterator < __ElementType > :: operator -- (int) noexcept -> RedBlackTreeBackwardIterator {       /* NOLINT(bugprone-reserved-identifier) */

        auto copy = *this;
        -- ( * this );
        return copy;
    }


    template < typename __ElementType >                                                                                         /* NOLINT(bugprone-reserved-identifier) */
    constexpr RedBlackTreeBackwardConstIterator < __ElementType > :: RedBlackTreeBackwardConstIterator () noexcept = default;   /* NOLINT(bugprone-reserved-identifier) */


    template < typename __ElementType >                                                                     /* NOLINT(bugprone-reserved-identifier) */
    constexpr RedBlackTreeBackwardConstIterator < __ElementType > :: RedBlackTreeBackwardConstIterator (    /* NOLINT(bugprone-reserved-identifier) */
            RBTreeNode const  *  pRoot,
            RBTreeNode const  *  pCurrentNode
    ) noexcept :
            AbstractRedBlackTreeConstIterator < __ElementType > (
                    pRoot,
                    pCurrentNode
            ) {

    }


    template < typename __ElementType >                                                                     /* NOLINT(bugprone-reserved-identifier) */
    constexpr RedBlackTreeBackwardConstIterator < __ElementType > :: RedBlackTreeBackwardConstIterator (    /* NOLINT(bugprone-reserved-identifier) */
            const RedBlackTreeBackwardConstIterator & iterator
    ) noexcept :
            AbstractRedBlackTreeConstIterator < __ElementType > ( iterator) {

    }


    template < typename __ElementType >                                                                     /* NOLINT(bugprone-reserved-identifier) */
    constexpr RedBlackTreeBackwardConstIterator < __ElementType > :: RedBlackTreeBackwardConstIterator (    /* NOLINT(bugprone-reserved-identifier) */
            RedBlackTreeBackwardConstIterator && iterator
    ) noexcept :
            AbstractRedBlackTreeConstIterator < __ElementType > ( std :: move ( iterator ) ) {

    }


    template < typename __ElementType >                                                                                         /* NOLINT(bugprone-reserved-identifier) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto RedBlackTreeBackwardConstIterator < __ElementType > :: operator = (      /* NOLINT(bugprone-reserved-identifier) */
            RedBlackTreeBackwardConstIterator const & iterator
    ) noexcept -> RedBlackTreeBackwardConstIterator & {

        if ( this == & iterator ) {
            return * this;
        }

        this->_pRoot        = iterator._pRoot;
        this->_pCurrentNode = iterator._pCurrentNode;

        return * this;
    }


    template < typename __ElementType >                                                                                     /* NOLINT(bugprone-reserved-identifier) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto RedBlackTreeBackwardConstIterator < __ElementType > :: operator = (  /* NOLINT(bugprone-reserved-identifier) */
            RedBlackTreeBackwardConstIterator && iterator
    ) noexcept -> RedBlackTreeBackwardConstIterator & {

        if ( this == & iterator ) {
            return * this;
        }

        this->_pRoot        = cds :: exchange ( iterator._pRoot, nullptr );
        this->_pCurrentNode = cds :: exchange ( iterator._pCurrentNode, nullptr );

        return * this;
    }


    template < typename __ElementType >                                                                                         /* NOLINT(bugprone-reserved-identifier) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto RedBlackTreeBackwardConstIterator < __ElementType > :: operator ++ (     /* NOLINT(bugprone-reserved-identifier) */
    ) noexcept -> RedBlackTreeBackwardConstIterator & {

        this->reverse();
        return * this;
    }


    template < typename __ElementType >                                                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto RedBlackTreeBackwardConstIterator < __ElementType > :: operator ++ (int) noexcept -> RedBlackTreeBackwardConstIterator {     /* NOLINT(bugprone-reserved-identifier) */

        auto copy = * this;
        ++ ( * this );
        return copy;
    }


    template < typename __ElementType >                                                                                         /* NOLINT(bugprone-reserved-identifier) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto RedBlackTreeBackwardConstIterator < __ElementType > :: operator -- (     /* NOLINT(bugprone-reserved-identifier) */
    ) noexcept -> RedBlackTreeBackwardConstIterator & {

        this->advance();
        return * this;
    }


    template < typename __ElementType >                                                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto RedBlackTreeBackwardConstIterator < __ElementType > :: operator -- (int) noexcept -> RedBlackTreeBackwardConstIterator {     /* NOLINT(bugprone-reserved-identifier) */

        auto copy = *this;
        -- ( * this );
        return copy;
    }
}

#endif /* __CDS_SHARED_RED_BLACK_TREE_ITERATOR_IMPL_HPP__ */
