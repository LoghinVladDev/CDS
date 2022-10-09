/*
 * Created by loghin on 18/07/22.
 */

#ifndef __CDS_SHARED_NODE_ITERATOR_IMPL_HPP__
#define __CDS_SHARED_NODE_ITERATOR_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */

    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    constexpr UnidirectionalNodeIterator < __ElementType > :: UnidirectionalNodeIterator () noexcept = default;


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    constexpr UnidirectionalNodeIterator < __ElementType > :: UnidirectionalNodeIterator (
            Node * pPreviousNode,
            Node * pCurrentNode
    ) noexcept :
            _pPreviousNode ( pPreviousNode ),
            _pCurrentNode ( pCurrentNode ) {

        /* copy current and previous node values */
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    constexpr UnidirectionalNodeIterator < __ElementType > :: UnidirectionalNodeIterator (
            UnidirectionalNodeIterator const & iterator
    ) noexcept :
            _pPreviousNode ( iterator._pPreviousNode ),
            _pCurrentNode ( iterator._pCurrentNode ) {

        /* copy current and previous node values from iterator */
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    constexpr UnidirectionalNodeIterator < __ElementType > :: UnidirectionalNodeIterator (
            UnidirectionalNodeIterator && iterator
    ) noexcept :
            _pPreviousNode ( cds :: exchange ( iterator._pPreviousNode, nullptr ) ),
            _pCurrentNode ( cds :: exchange ( iterator._pCurrentNode, nullptr ) ) {

        /* move current and previous node values from iterator */
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto UnidirectionalNodeIterator < __ElementType > :: operator = (
            UnidirectionalNodeIterator const & iterator
    ) noexcept -> UnidirectionalNodeIterator & {

        /* if given iterator is the same as current, copy unnecessary */
        if ( this == & iterator ) {
            return * this;
        }

        /* otherwise, copy current and previous node */
        this->_pCurrentNode     = iterator._pCurrentNode;
        this->_pPreviousNode    = iterator._pPreviousNode;

        return * this;
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto UnidirectionalNodeIterator < __ElementType > :: operator = (
            UnidirectionalNodeIterator && iterator
    ) noexcept -> UnidirectionalNodeIterator & {

        /* if given iterator is the same as current, move unnecessary */
        if ( this == & iterator ) {
            return * this;
        }

        /* otherwise, move current and previous node */
        this->_pCurrentNode     = cds :: exchange ( iterator._pCurrentNode, nullptr );
        this->_pPreviousNode    = cds :: exchange ( iterator._pPreviousNode, nullptr );

        return * this;
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    constexpr auto UnidirectionalNodeIterator < __ElementType > :: operator * () const noexcept -> __ElementType & {

        /* return reference to the element at the current node */
        return this->_pCurrentNode->_data;
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    constexpr auto UnidirectionalNodeIterator < __ElementType > :: operator -> () const noexcept -> __ElementType * {

        /* return the address of the element at the current node */
        return & this->_pCurrentNode->_data;
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    constexpr auto UnidirectionalNodeIterator < __ElementType > :: operator == (
            UnidirectionalNodeIterator const & iterator
    ) const noexcept -> bool {

        /* Iterators are equal if both have current nodes valid and equal OR null current nodes and equal previous nodes ( end of list or null ) */
        return
                this->_pCurrentNode     == iterator._pCurrentNode &&
                this->_pCurrentNode     != nullptr ||
                this->_pCurrentNode     == iterator._pCurrentNode &&
                this->_pPreviousNode    == iterator._pPreviousNode;
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    constexpr auto UnidirectionalNodeIterator < __ElementType > :: operator != (
            UnidirectionalNodeIterator const & iterator
    ) const noexcept -> bool {

        /* iterators not equal when ! equals ( this, iterator ) */
        return ! this->operator == ( iterator );
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto UnidirectionalNodeIterator < __ElementType > :: operator ++ () noexcept -> UnidirectionalNodeIterator & {

        /* previous node becomes the current one */
        this->_pPreviousNode    = this->_pCurrentNode;
        /* current node becomes the next */
        this->_pCurrentNode     = this->_pCurrentNode == nullptr ? nullptr : this->_pCurrentNode->_pNext;
        return * this;
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto UnidirectionalNodeIterator < __ElementType > :: operator ++ (int) noexcept -> UnidirectionalNodeIterator {

        /* make a copy of this iterator, advance current one and return copy */
        auto copy = * this;
        this->_pPreviousNode    = this->_pCurrentNode;
        this->_pCurrentNode     = this->_pCurrentNode == nullptr ? nullptr : this->_pCurrentNode->_pNext;
        return copy;
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    constexpr UnidirectionalNodeIterator < __ElementType > :: operator bool () const noexcept {

        /* iterator is valid if current node is not null */
        /* Special case in insert before. end value potentially valid */
        return this->_pCurrentNode != nullptr || this->_pPreviousNode != nullptr;
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    constexpr UnidirectionalNodeConstIterator < __ElementType > :: UnidirectionalNodeConstIterator () noexcept = default;


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    constexpr UnidirectionalNodeConstIterator < __ElementType > :: UnidirectionalNodeConstIterator (
            Node const * pPreviousNode,
            Node const * pCurrentNode
    ) noexcept :
            _pPreviousNode ( pPreviousNode ),
            _pCurrentNode ( pCurrentNode ) {

        /* copy current and previous node values */
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    constexpr UnidirectionalNodeConstIterator < __ElementType > :: UnidirectionalNodeConstIterator (
            UnidirectionalNodeConstIterator const & iterator
    ) noexcept :
            _pPreviousNode ( iterator._pPreviousNode ),
            _pCurrentNode ( iterator._pCurrentNode ) {

        /* copy current and previous node values from iterator */
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    constexpr UnidirectionalNodeConstIterator < __ElementType > :: UnidirectionalNodeConstIterator (
            UnidirectionalNodeConstIterator && iterator
    ) noexcept :
            _pPreviousNode ( cds :: exchange ( iterator._pPreviousNode, nullptr ) ),
            _pCurrentNode ( cds :: exchange ( iterator._pCurrentNode, nullptr ) ) {

        /* move current and previous node values from iterator */
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto UnidirectionalNodeConstIterator < __ElementType > :: operator = (
            UnidirectionalNodeConstIterator const & iterator
    ) noexcept -> UnidirectionalNodeConstIterator & {

        /* if given iterator is the same as current, copy unnecessary */
        if ( this == & iterator ) {
            return * this;
        }

        /* otherwise, copy current and previous node */
        this->_pCurrentNode     = iterator._pCurrentNode;
        this->_pPreviousNode    = iterator._pPreviousNode;

        return * this;
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto UnidirectionalNodeConstIterator < __ElementType > :: operator = (
            UnidirectionalNodeConstIterator && iterator
    ) noexcept -> UnidirectionalNodeConstIterator & {

        /* if given iterator is the same as current, move unnecessary */
        if ( this == & iterator ) {
            return * this;
        }

        /* otherwise, move current and previous node */
        this->_pCurrentNode     = cds :: exchange ( iterator._pCurrentNode, nullptr );
        this->_pPreviousNode    = cds :: exchange ( iterator._pPreviousNode, nullptr );

        return * this;
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    constexpr auto UnidirectionalNodeConstIterator < __ElementType > :: operator * () const noexcept -> __ElementType const & {

        /* return reference to the element at the current node */
        return this->_pCurrentNode->_data;
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    constexpr auto UnidirectionalNodeConstIterator < __ElementType > :: operator -> () const noexcept -> __ElementType const * {

        /* return the address of the element at the current node */
        return & this->_pCurrentNode->_data;
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    constexpr auto UnidirectionalNodeConstIterator < __ElementType > :: operator == (
            UnidirectionalNodeConstIterator const & iterator
    ) const noexcept -> bool {

        /* Iterators are equal if both have current nodes valid and equal OR null current nodes and equal previous nodes ( end of list or null ) */
        return
                this->_pCurrentNode     == iterator._pCurrentNode &&
                this->_pCurrentNode     != nullptr ||
                this->_pCurrentNode     == iterator._pCurrentNode &&
                this->_pPreviousNode    == iterator._pPreviousNode;
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    constexpr auto UnidirectionalNodeConstIterator < __ElementType > :: operator != (
            UnidirectionalNodeConstIterator const & iterator
    ) const noexcept -> bool {

        /* iterators not equal when ! equals ( this, iterator ) */
        return ! this->operator == ( iterator );
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto UnidirectionalNodeConstIterator < __ElementType > :: operator ++ () noexcept -> UnidirectionalNodeConstIterator & {

        /* previous node becomes the current one */
        this->_pPreviousNode    = this->_pCurrentNode;
        /* current node becomes the next */
        this->_pCurrentNode     = this->_pCurrentNode == nullptr ? nullptr : this->_pCurrentNode->_pNext;
        return * this;
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto UnidirectionalNodeConstIterator < __ElementType > :: operator ++ (int) noexcept -> UnidirectionalNodeConstIterator {

        /* make a copy of this iterator, advance current one and return copy */
        auto copy = * this;
        this->_pPreviousNode    = this->_pCurrentNode;
        this->_pCurrentNode     = this->_pCurrentNode == nullptr ? nullptr : this->_pCurrentNode->_pNext;
        return copy;
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    constexpr UnidirectionalNodeConstIterator < __ElementType > :: operator bool () const noexcept {

        /* iterator is valid if current node is not null */
        /* Special case in insert before. end value potentially valid */
        return this->_pCurrentNode != nullptr || this->_pPreviousNode != nullptr;
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    constexpr AbstractBidirectionalNodeIterator < __ElementType > :: AbstractBidirectionalNodeIterator () noexcept = default;


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    constexpr AbstractBidirectionalNodeIterator < __ElementType > :: AbstractBidirectionalNodeIterator (
            Node * pPreviousNode,
            Node * pCurrentNode
    ) noexcept :
            _pPreviousNode ( pPreviousNode ),
            _pCurrentNode ( pCurrentNode ) {

        /* copy current and previous node values */
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    constexpr AbstractBidirectionalNodeIterator < __ElementType > :: AbstractBidirectionalNodeIterator (
            AbstractBidirectionalNodeIterator const & iterator
    ) noexcept :
            _pPreviousNode ( iterator._pPreviousNode ),
            _pCurrentNode ( iterator._pCurrentNode ) {

        /* copy current and previous node values from iterator */
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    constexpr AbstractBidirectionalNodeIterator < __ElementType > :: AbstractBidirectionalNodeIterator (
            AbstractBidirectionalNodeIterator && iterator
    ) noexcept :
            _pPreviousNode ( cds :: exchange ( iterator._pPreviousNode, nullptr ) ),
            _pCurrentNode ( cds :: exchange ( iterator._pCurrentNode, nullptr ) ) {

        /* move current and previous node values from iterator */
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    constexpr auto AbstractBidirectionalNodeIterator < __ElementType > :: operator * () const noexcept -> __ElementType & {

        /* return reference to the element at the current node */
        return this->_pCurrentNode->_data;
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    constexpr auto AbstractBidirectionalNodeIterator < __ElementType > :: operator -> () const noexcept -> __ElementType * {

        /* return the address of the element at the current node */
        return & this->_pCurrentNode->_data;
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    constexpr auto AbstractBidirectionalNodeIterator < __ElementType > :: operator == (
            AbstractBidirectionalNodeIterator const & iterator
    ) const noexcept -> bool {

        /* Iterators are equal if both have current nodes valid and equal OR null current nodes and equal previous nodes ( end of list or null ) */
        return
                this->_pCurrentNode     == iterator._pCurrentNode &&
                this->_pCurrentNode     != nullptr ||
                this->_pCurrentNode     == iterator._pCurrentNode &&
                this->_pPreviousNode    == iterator._pPreviousNode;
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    constexpr auto AbstractBidirectionalNodeIterator < __ElementType > :: operator != (
            AbstractBidirectionalNodeIterator const & iterator
    ) const noexcept -> bool {

        /* iterators not equal when ! equals ( this, iterator ) */
        return ! this->operator == ( iterator );
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    constexpr AbstractBidirectionalNodeIterator < __ElementType > :: operator bool () const noexcept {

        /* iterator is valid if current node is not null. */
        /* Special case in insert before. end value potentially valid */
        return this->_pCurrentNode != nullptr || this->_pPreviousNode != nullptr;
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    constexpr AbstractBidirectionalNodeConstIterator < __ElementType > :: AbstractBidirectionalNodeConstIterator () noexcept = default;


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    constexpr AbstractBidirectionalNodeConstIterator < __ElementType > :: AbstractBidirectionalNodeConstIterator (
            Node const * pPreviousNode,
            Node const * pCurrentNode
    ) noexcept :
            _pPreviousNode ( pPreviousNode ),
            _pCurrentNode ( pCurrentNode ) {

        /* copy current and previous node values */
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    constexpr AbstractBidirectionalNodeConstIterator < __ElementType > :: AbstractBidirectionalNodeConstIterator (
            AbstractBidirectionalNodeConstIterator const & iterator
    ) noexcept :
            _pPreviousNode ( iterator._pPreviousNode ),
            _pCurrentNode ( iterator._pCurrentNode ) {

        /* copy current and previous node values from iterator */
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    constexpr AbstractBidirectionalNodeConstIterator < __ElementType > :: AbstractBidirectionalNodeConstIterator (
            AbstractBidirectionalNodeConstIterator && iterator
    ) noexcept :
            _pPreviousNode ( cds :: exchange ( iterator._pPreviousNode, nullptr ) ),
            _pCurrentNode ( cds :: exchange ( iterator._pCurrentNode, nullptr ) ) {

        /* move current and previous node values from iterator */
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    constexpr auto AbstractBidirectionalNodeConstIterator < __ElementType > :: operator * () const noexcept -> __ElementType const & {

        /* return reference to the element at the current node */
        return this->_pCurrentNode->_data;
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    constexpr auto AbstractBidirectionalNodeConstIterator < __ElementType > :: operator -> () const noexcept -> __ElementType const * {

        /* return the address of the element at the current node */
        return & this->_pCurrentNode->_data;
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    constexpr auto AbstractBidirectionalNodeConstIterator < __ElementType > :: operator == (
            AbstractBidirectionalNodeConstIterator const & iterator
    ) const noexcept -> bool {

        /* Iterators are equal if both have current nodes valid and equal OR null current nodes and equal previous nodes ( end of list or null ) */
        return
                this->_pCurrentNode     == iterator._pCurrentNode &&
                this->_pCurrentNode     != nullptr ||
                this->_pCurrentNode     == iterator._pCurrentNode &&
                this->_pPreviousNode    == iterator._pPreviousNode;
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    constexpr auto AbstractBidirectionalNodeConstIterator < __ElementType > :: operator != (
            AbstractBidirectionalNodeConstIterator const & iterator
    ) const noexcept -> bool {

        /* iterators not equal when ! equals ( this, iterator ) */
        return ! this->operator == ( iterator );
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    constexpr AbstractBidirectionalNodeConstIterator < __ElementType > :: operator bool () const noexcept {

        /* iterator is valid if current node is not null */
        /* Special case in insert before. end value potentially valid */
        return this->_pCurrentNode != nullptr || this->_pPreviousNode != nullptr;
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    constexpr ForwardBidirectionalNodeIterator < __ElementType > :: ForwardBidirectionalNodeIterator () noexcept = default;


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    constexpr ForwardBidirectionalNodeIterator < __ElementType > :: ForwardBidirectionalNodeIterator (
            Node * pPreviousNode,
            Node * pCurrentNode
    ) noexcept :
            AbstractBidirectionalNodeIterator < __ElementType > (
                    pPreviousNode,
                    pCurrentNode
            ) {

        /* pass current and previous node values to base class constructor */
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    constexpr ForwardBidirectionalNodeIterator < __ElementType > :: ForwardBidirectionalNodeIterator (
            ForwardBidirectionalNodeIterator const & iterator
    ) noexcept :
            AbstractBidirectionalNodeIterator < __ElementType > ( iterator ) {

        /* pass given iterator to base constructor to be copies */
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    constexpr ForwardBidirectionalNodeIterator < __ElementType > :: ForwardBidirectionalNodeIterator (
            ForwardBidirectionalNodeIterator && iterator
    ) noexcept :
            AbstractBidirectionalNodeIterator < __ElementType > ( std :: move ( iterator ) ) {

        /* pass given iterator to base constructor to be moved */
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto ForwardBidirectionalNodeIterator < __ElementType > :: operator = (
            ForwardBidirectionalNodeIterator const & iterator
    ) noexcept -> ForwardBidirectionalNodeIterator & {

        /* if given iterator is the same as current, copy unnecessary */
        if ( this == & iterator ) {
            return * this;
        }

        /* otherwise, copy current and previous node */
        this->_pCurrentNode     = iterator._pCurrentNode;
        this->_pPreviousNode    = iterator._pPreviousNode;

        return * this;
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto ForwardBidirectionalNodeIterator < __ElementType > :: operator = (
            ForwardBidirectionalNodeIterator && iterator
    ) noexcept -> ForwardBidirectionalNodeIterator & {

        /* if given iterator is the same as current, move unnecessary */
        if ( this == & iterator ) {
            return * this;
        }

        /* otherwise, move current and previous node */
        this->_pCurrentNode     = cds :: exchange ( iterator._pCurrentNode, nullptr );
        this->_pPreviousNode    = cds :: exchange ( iterator._pPreviousNode, nullptr );

        return * this;
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    constexpr auto ForwardBidirectionalNodeIterator < __ElementType > :: operator == (
            ForwardBidirectionalNodeIterator const & iterator
    ) const noexcept -> bool {

        /* Iterators are equal if both have current nodes valid and equal OR null current nodes and equal previous nodes ( end of list or null ) */
        return
                this->_pCurrentNode     == iterator._pCurrentNode &&
                this->_pCurrentNode     != nullptr ||
                this->_pCurrentNode     == iterator._pCurrentNode &&
                this->_pPreviousNode    == iterator._pPreviousNode;
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    constexpr auto ForwardBidirectionalNodeIterator < __ElementType > :: operator != (
            ForwardBidirectionalNodeIterator const & iterator
    ) const noexcept -> bool {

        /* iterators not equal when ! equals ( this, iterator ) */
        return ! this->operator == ( iterator );
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto ForwardBidirectionalNodeIterator < __ElementType > :: operator ++ () noexcept -> ForwardBidirectionalNodeIterator & {

        /* previous node becomes the current one */
        this->_pPreviousNode    = this->_pCurrentNode;
        /* current node becomes the next */
        this->_pCurrentNode     = this->_pCurrentNode == nullptr ? nullptr : this->_pCurrentNode->_pNext;
        return * this;
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto ForwardBidirectionalNodeIterator < __ElementType > :: operator ++ (int) noexcept -> ForwardBidirectionalNodeIterator {

        /* make a copy of this iterator, advance forward current one and return copy */
        auto copy = * this;
        this->_pPreviousNode    = this->_pCurrentNode;
        this->_pCurrentNode     = this->_pCurrentNode == nullptr ? nullptr : this->_pCurrentNode->_pNext;
        return copy;
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto ForwardBidirectionalNodeIterator < __ElementType > :: operator -- () noexcept -> ForwardBidirectionalNodeIterator & {

        /* current node becomes the previous one */
        this->_pCurrentNode     = this->_pPreviousNode;
        /* the previous node becomes the one before it, if it was valid */
        this->_pPreviousNode    = this->_pCurrentNode == nullptr ? nullptr : this->_pCurrentNode->_pPrevious;
        return * this;
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto ForwardBidirectionalNodeIterator < __ElementType > :: operator -- (int) noexcept -> ForwardBidirectionalNodeIterator {

        /* make a copy of this iterator, advance backward current one and return copy */
        auto copy = * this;
        this->_pCurrentNode     = this->_pPreviousNode;
        this->_pPreviousNode    = this->_pCurrentNode == nullptr ? nullptr : this->_pCurrentNode->_pPrevious;
        return copy;
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    constexpr ForwardBidirectionalNodeConstIterator < __ElementType > :: ForwardBidirectionalNodeConstIterator () noexcept = default;


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    constexpr ForwardBidirectionalNodeConstIterator < __ElementType > :: ForwardBidirectionalNodeConstIterator (
            Node const * pPreviousNode,
            Node const * pCurrentNode
    ) noexcept :
            AbstractBidirectionalNodeConstIterator < __ElementType > (
                    pPreviousNode,
                    pCurrentNode
            ) {

        /* pass current and previous node values to base class constructor */
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    constexpr ForwardBidirectionalNodeConstIterator < __ElementType > :: ForwardBidirectionalNodeConstIterator (
            ForwardBidirectionalNodeConstIterator const & iterator
    ) noexcept :
            AbstractBidirectionalNodeConstIterator < __ElementType > ( iterator ) {

        /* pass given iterator to base constructor to be copies */
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    constexpr ForwardBidirectionalNodeConstIterator < __ElementType > :: ForwardBidirectionalNodeConstIterator (
            ForwardBidirectionalNodeConstIterator && iterator
    ) noexcept :
            AbstractBidirectionalNodeConstIterator < __ElementType > ( std :: move ( iterator ) ) {

        /* pass given iterator to base constructor to be moved */
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto ForwardBidirectionalNodeConstIterator < __ElementType > :: operator = (
            ForwardBidirectionalNodeConstIterator const & iterator
    ) noexcept -> ForwardBidirectionalNodeConstIterator & {

        /* if given iterator is the same as current, copy unnecessary */
        if ( this == & iterator ) {
            return * this;
        }

        /* otherwise, copy current and previous node */
        this->_pCurrentNode     = iterator._pCurrentNode;
        this->_pPreviousNode    = iterator._pPreviousNode;

        return * this;
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto ForwardBidirectionalNodeConstIterator < __ElementType > :: operator = (
            ForwardBidirectionalNodeConstIterator && iterator
    ) noexcept -> ForwardBidirectionalNodeConstIterator & {

        /* if given iterator is the same as current, move unnecessary */
        if ( this == & iterator ) {
            return * this;
        }

        /* otherwise, move current and previous node */
        this->_pCurrentNode     = cds :: exchange ( iterator._pCurrentNode, nullptr );
        this->_pPreviousNode    = cds :: exchange ( iterator._pPreviousNode, nullptr );

        return * this;
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    constexpr auto ForwardBidirectionalNodeConstIterator < __ElementType > :: operator == (
            ForwardBidirectionalNodeConstIterator const & iterator
    ) const noexcept -> bool {

        /* Iterators are equal if both have current nodes valid and equal OR null current nodes and equal previous nodes ( end of list or null ) */
        return
                this->_pCurrentNode     == iterator._pCurrentNode &&
                this->_pCurrentNode     != nullptr ||
                this->_pCurrentNode     == iterator._pCurrentNode &&
                this->_pPreviousNode    == iterator._pPreviousNode;
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    constexpr auto ForwardBidirectionalNodeConstIterator < __ElementType > :: operator != (
            ForwardBidirectionalNodeConstIterator const & iterator
    ) const noexcept -> bool {

        /* iterators not equal when ! equals ( this, iterator ) */
        return ! this->operator == ( iterator );
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto ForwardBidirectionalNodeConstIterator < __ElementType > :: operator ++ () noexcept -> ForwardBidirectionalNodeConstIterator & {

        /* previous node becomes the current one */
        this->_pPreviousNode    = this->_pCurrentNode;
        /* current node becomes the next */
        this->_pCurrentNode     = this->_pCurrentNode == nullptr ? nullptr : this->_pCurrentNode->_pNext;
        return * this;
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto ForwardBidirectionalNodeConstIterator < __ElementType > :: operator ++ (int) noexcept -> ForwardBidirectionalNodeConstIterator {

        /* make a copy of this iterator, advance forward current one and return copy */
        auto copy = * this;
        this->_pPreviousNode    = this->_pCurrentNode;
        this->_pCurrentNode     = this->_pCurrentNode == nullptr ? nullptr : this->_pCurrentNode->_pNext;
        return copy;
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto ForwardBidirectionalNodeConstIterator < __ElementType > :: operator -- () noexcept -> ForwardBidirectionalNodeConstIterator & {

        /* current node becomes the previous one */
        this->_pCurrentNode     = this->_pPreviousNode;
        /* the previous node becomes the one before it, if it was valid */
        this->_pPreviousNode    = this->_pCurrentNode == nullptr ? nullptr : this->_pCurrentNode->_pPrevious;
        return * this;
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto ForwardBidirectionalNodeConstIterator < __ElementType > :: operator -- (int) noexcept -> ForwardBidirectionalNodeConstIterator {

        /* make a copy of this iterator, advance backward current one and return copy */
        auto copy = * this;
        this->_pCurrentNode     = this->_pPreviousNode;
        this->_pPreviousNode    = this->_pCurrentNode == nullptr ? nullptr : this->_pCurrentNode->_pPrevious;
        return copy;
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    constexpr BackwardBidirectionalNodeIterator < __ElementType > :: BackwardBidirectionalNodeIterator () noexcept = default;


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    constexpr BackwardBidirectionalNodeIterator < __ElementType > :: BackwardBidirectionalNodeIterator (
            Node * pPreviousNode,
            Node * pCurrentNode
    ) noexcept :
            AbstractBidirectionalNodeIterator < __ElementType > (
                    pPreviousNode,
                    pCurrentNode
            ) {

        /* pass current and previous node values to base class constructor */
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    constexpr BackwardBidirectionalNodeIterator < __ElementType > :: BackwardBidirectionalNodeIterator (
            BackwardBidirectionalNodeIterator const & iterator
    ) noexcept :
            AbstractBidirectionalNodeIterator < __ElementType > ( iterator ) {

        /* pass given iterator to base constructor to be copies */
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    constexpr BackwardBidirectionalNodeIterator < __ElementType > :: BackwardBidirectionalNodeIterator (
            BackwardBidirectionalNodeIterator && iterator
    ) noexcept :
            AbstractBidirectionalNodeIterator < __ElementType > ( std :: move ( iterator ) ) {

        /* pass given iterator to base constructor to be moved */
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto BackwardBidirectionalNodeIterator < __ElementType > :: operator = (
            BackwardBidirectionalNodeIterator const & iterator
    ) noexcept -> BackwardBidirectionalNodeIterator & {

        /* if given iterator is the same as current, copy unnecessary */
        if ( this == & iterator ) {
            return * this;
        }

        /* otherwise, copy current and previous node */
        this->_pCurrentNode     = iterator._pCurrentNode;
        this->_pPreviousNode    = iterator._pPreviousNode;

        return * this;
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto BackwardBidirectionalNodeIterator < __ElementType > :: operator = (
            BackwardBidirectionalNodeIterator && iterator
    ) noexcept -> BackwardBidirectionalNodeIterator & {

        /* if given iterator is the same as current, move unnecessary */
        if ( this == & iterator ) {
            return * this;
        }

        /* otherwise, move current and previous node */
        this->_pCurrentNode     = cds :: exchange ( iterator._pCurrentNode, nullptr );
        this->_pPreviousNode    = cds :: exchange ( iterator._pPreviousNode, nullptr );

        return * this;
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    constexpr auto BackwardBidirectionalNodeIterator < __ElementType > :: operator == (
            BackwardBidirectionalNodeIterator const & iterator
    ) const noexcept -> bool {

        /* Iterators are equal if both have current nodes valid and equal OR null current nodes and equal previous nodes ( end of list or null ) */
        return
                this->_pCurrentNode     == iterator._pCurrentNode &&
                this->_pCurrentNode     != nullptr ||
                this->_pCurrentNode     == iterator._pCurrentNode &&
                this->_pPreviousNode    == iterator._pPreviousNode;
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    constexpr auto BackwardBidirectionalNodeIterator < __ElementType > :: operator != (
            BackwardBidirectionalNodeIterator const & iterator
    ) const noexcept -> bool {

        /* iterators not equal when ! equals ( this, iterator ) */
        return ! this->operator == ( iterator );
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto BackwardBidirectionalNodeIterator < __ElementType > :: operator ++ () noexcept -> BackwardBidirectionalNodeIterator & {

        /* previous node becomes the current one */
        this->_pPreviousNode    = this->_pCurrentNode;
        /* current node becomes the previous */
        this->_pCurrentNode     = this->_pCurrentNode == nullptr ? nullptr : this->_pCurrentNode->_pPrevious;
        return * this;
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto BackwardBidirectionalNodeIterator < __ElementType > :: operator ++ (int) noexcept -> BackwardBidirectionalNodeIterator {

        /* make a copy of this iterator, advance backward current one and return copy */
        auto copy = * this;
        this->_pPreviousNode    = this->_pCurrentNode;
        this->_pCurrentNode     = this->_pCurrentNode == nullptr ? nullptr : this->_pCurrentNode->_pPrevious;
        return copy;
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto BackwardBidirectionalNodeIterator < __ElementType > :: operator -- () noexcept -> BackwardBidirectionalNodeIterator & {

        /* current node becomes the previous one */
        this->_pCurrentNode     = this->_pPreviousNode;
        /* the previous node becomes the one after it, if it was valid */
        this->_pPreviousNode    = this->_pCurrentNode == nullptr ? nullptr : this->_pCurrentNode->_pNext;
        return * this;
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto BackwardBidirectionalNodeIterator < __ElementType > :: operator -- (int) noexcept -> BackwardBidirectionalNodeIterator {

        /* make a copy of this iterator, advance forward current one and return copy */
        auto copy = * this;
        this->_pCurrentNode     = this->_pPreviousNode;
        this->_pPreviousNode    = this->_pCurrentNode == nullptr ? nullptr : this->_pCurrentNode->_pNext;
        return copy;
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    constexpr BackwardBidirectionalNodeConstIterator < __ElementType > :: BackwardBidirectionalNodeConstIterator () noexcept = default;


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    constexpr BackwardBidirectionalNodeConstIterator < __ElementType > :: BackwardBidirectionalNodeConstIterator (
            Node const * pPreviousNode,
            Node const * pCurrentNode
    ) noexcept :
            AbstractBidirectionalNodeConstIterator < __ElementType > (
                    pPreviousNode,
                    pCurrentNode
            ) {

        /* pass current and previous node values to base class constructor */
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    constexpr BackwardBidirectionalNodeConstIterator < __ElementType > :: BackwardBidirectionalNodeConstIterator (
            BackwardBidirectionalNodeConstIterator const & iterator
    ) noexcept :
            AbstractBidirectionalNodeConstIterator < __ElementType > ( iterator ) {

        /* pass given iterator to base constructor to be copies */
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    constexpr BackwardBidirectionalNodeConstIterator < __ElementType > :: BackwardBidirectionalNodeConstIterator (
            BackwardBidirectionalNodeConstIterator && iterator
    ) noexcept :
            AbstractBidirectionalNodeConstIterator < __ElementType > ( std :: move ( iterator ) ) {

        /* pass given iterator to base constructor to be moved */
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto BackwardBidirectionalNodeConstIterator < __ElementType > :: operator = (
            BackwardBidirectionalNodeConstIterator const & iterator
    ) noexcept -> BackwardBidirectionalNodeConstIterator & {

        /* if given iterator is the same as current, copy unnecessary */
        if ( this == & iterator ) {
            return * this;
        }

        /* otherwise, copy current and previous node */
        this->_pCurrentNode     = iterator._pCurrentNode;
        this->_pPreviousNode    = iterator._pPreviousNode;

        return * this;
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto BackwardBidirectionalNodeConstIterator < __ElementType > :: operator = (
            BackwardBidirectionalNodeConstIterator && iterator
    ) noexcept -> BackwardBidirectionalNodeConstIterator & {

        /* if given iterator is the same as current, move unnecessary */
        if ( this == & iterator ) {
            return * this;
        }

        /* otherwise, move current and previous node */
        this->_pCurrentNode     = cds :: exchange ( iterator._pCurrentNode, nullptr );
        this->_pPreviousNode    = cds :: exchange ( iterator._pPreviousNode, nullptr );

        return * this;
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    constexpr auto BackwardBidirectionalNodeConstIterator < __ElementType > :: operator == (
            BackwardBidirectionalNodeConstIterator const & iterator
    ) const noexcept -> bool {

        /* Iterators are equal if both have current nodes valid and equal OR null current nodes and equal previous nodes ( end of list or null ) */
        return
                this->_pCurrentNode     == iterator._pCurrentNode &&
                this->_pCurrentNode     != nullptr ||
                this->_pCurrentNode     == iterator._pCurrentNode &&
                this->_pPreviousNode    == iterator._pPreviousNode;
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    constexpr auto BackwardBidirectionalNodeConstIterator < __ElementType > :: operator != (
            BackwardBidirectionalNodeConstIterator const & iterator
    ) const noexcept -> bool {

        /* iterators not equal when ! equals ( this, iterator ) */
        return ! this->operator == ( iterator );
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto BackwardBidirectionalNodeConstIterator < __ElementType > :: operator ++ () noexcept -> BackwardBidirectionalNodeConstIterator & {

        /* previous node becomes the current one */
        this->_pPreviousNode    = this->_pCurrentNode;
        /* current node becomes the previous */
        this->_pCurrentNode     = this->_pCurrentNode == nullptr ? nullptr : this->_pCurrentNode->_pPrevious;
        return * this;
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto BackwardBidirectionalNodeConstIterator < __ElementType > :: operator ++ (int) noexcept -> BackwardBidirectionalNodeConstIterator {

        /* make a copy of this iterator, advance backward current one and return copy */
        auto copy = * this;
        this->_pPreviousNode    = this->_pCurrentNode;
        this->_pCurrentNode     = this->_pCurrentNode == nullptr ? nullptr : this->_pCurrentNode->_pPrevious;
        return copy;
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto BackwardBidirectionalNodeConstIterator < __ElementType > :: operator -- () noexcept -> BackwardBidirectionalNodeConstIterator & {

        /* current node becomes the previous one */
        this->_pCurrentNode     = this->_pPreviousNode;
        /* the previous node becomes the one after it, if it was valid */
        this->_pPreviousNode    = this->_pCurrentNode == nullptr ? nullptr : this->_pCurrentNode->_pNext;
        return * this;
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto BackwardBidirectionalNodeConstIterator < __ElementType > :: operator -- (int) noexcept -> BackwardBidirectionalNodeConstIterator {

        /* make a copy of this iterator, advance forward current one and return copy */
        auto copy = * this;
        this->_pCurrentNode     = this->_pPreviousNode;
        this->_pPreviousNode    = this->_pCurrentNode == nullptr ? nullptr : this->_pCurrentNode->_pNext;
        return copy;
    }

}

#endif /* __CDS_SHARED_NODE_ITERATOR_IMPL_HPP__ */
