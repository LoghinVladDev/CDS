//
// Created by stefan on 16.08.2022.
//

#ifndef __CDS_EX_SHARED_RED_BLACK_TREE_ITERATOR_IMPL_HPP__
#define __CDS_EX_SHARED_RED_BLACK_TREE_ITERATOR_IMPL_HPP__
#include "../RedBlackTreeIterator.h"
namespace cds {
    namespace experimental {

        template < typename __ElementType >
        RedBlackTreeIterator < __ElementType > :: RedBlackTreeIterator () noexcept = default;


        template < typename __ElementType >
        RedBlackTreeIterator < __ElementType > :: RedBlackTreeIterator (
                RBTreeNode  *  pRoot,
                RBTreeNode  *  pCurrentNode
        ) noexcept :
            _pRoot        ( pRoot ),
            _pCurrentNode ( pCurrentNode ) {

        }


        template < typename __ElementType >
        RedBlackTreeIterator < __ElementType > :: RedBlackTreeIterator (
                const RedBlackTreeIterator & iterator
        ) noexcept :
            _pRoot        ( iterator._pRoot ),
            _pCurrentNode ( iterator._pCurrentNode) {

        }


        template < typename __ElementType >
        RedBlackTreeIterator < __ElementType > :: RedBlackTreeIterator (
                RedBlackTreeIterator && iterator
        ) noexcept :
            _pRoot        ( cds :: exchange ( iterator._pRoot, nullptr ) ),
            _pCurrentNode ( cds :: exchange ( iterator._pCurrentNode, nullptr ) ) {

        }


        template < typename __ElementType >
        auto RedBlackTreeIterator < __ElementType > :: operator = (
                RedBlackTreeIterator const & iterator
        ) noexcept -> RedBlackTreeIterator & {

            if ( this == & iterator ) {
                return * this;
            }

            this->_pRoot        = iterator._pRoot;
            this->_pCurrentNode = iterator._pCurrentNode;

            return * this;
        }


        template < typename __ElementType >
        auto RedBlackTreeIterator < __ElementType > :: operator = (
                RedBlackTreeIterator && iterator
        ) noexcept -> RedBlackTreeIterator & {

            if ( this == & iterator )
                return * this;

            this->_pRoot        = cds :: exchange ( iterator._pRoot, nullptr );
            this->_pCurrentNode = cds :: exchange ( iterator._pCurrentNode, nullptr );

            return * this;
        }


        template < typename __ElementType >
        auto RedBlackTreeIterator < __ElementType > :: operator ++ (
        ) noexcept -> RedBlackTreeIterator & {

            if ( this->_pCurrentNode->_pRight != __hidden :: __impl :: __endNode < __ElementType > () ) {
                this->_pCurrentNode = this->_pCurrentNode->_pRight;
                while ( this->_pCurrentNode->_pLeft != __endNode < __ElementType > () ) {
                    this->_pCurrentNode = this->_pCurrentNode->_pLeft;
                }
                return * this;
            }

            if ( this->_pCurrentNode == this->_pRoot )
                return nullptr;

            while ( this->_pCurrentNode == this->_pCurrentNode->_pParent->_pRight ) {
                this->_pCurrentNode = this->_pCurrentNode->_pParent;
                if ( this->_pCurrentNode == this->_pRoot )
                    return nullptr;
            }
            this->_pCurrentNode = this->_pCurrentNode->_pParent;

            return * this;
        }


        template < typename __ElementType >
        auto RedBlackTreeIterator < __ElementType > :: operator ++ (int) noexcept -> RedBlackTreeIterator {

            auto copy = * this;
            ++ ( * this );
            return copy;
        }


        template < typename __ElementType >
        auto RedBlackTreeIterator < __ElementType > :: operator -- (
        ) noexcept -> RedBlackTreeIterator & {

            if ( this->_pCurrentNode->_pLeft != __hidden :: __impl :: __endNode < __ElementType > () ) {
                this->_pCurrentNode = this->_pCurrentNode->_pLeft;
                while ( this->_pCurrentNode->_pRight != __endNode < __ElementType > () ) {
                    this->_pCurrentNode = this->_pCurrentNode->_pRight;
                }
                return * this;
            }

            if ( this->_pCurrentNode == this->_pRoot )
                return nullptr;

            while ( this->_pCurrentNode == this->_pCurrentNode->_pParent->_pLeft ) {
                this->_pCurrentNode = this->_pCurrentNode->_pParent;
                if ( this->_pCurrentNode == this->_pRoot )
                    return nullptr;
            }
            this->_pCurrentNode = this->_pCurrentNode->_pParent;

            return * this;
        }


        template < typename __ElementType >
        auto RedBlackTreeIterator < __ElementType > :: operator -- (int) noexcept -> RedBlackTreeIterator {

            auto copy = *this;
            -- ( * this );
            return copy;
        }


        template < typename __ElementType >
        auto RedBlackTreeIterator < __ElementType > :: operator * (
        ) const noexcept -> __ElementType & {

            return this->_pCurrentNode->_data;
        }


        template < typename __ElementType >
        auto RedBlackTreeIterator < __ElementType > :: operator -> (
        ) const noexcept -> __ElementType * {

            return & this->_pCurrentNode->_data;
        }


        template < typename __ElementType >
        auto RedBlackTreeIterator < __ElementType > :: operator == (
                RedBlackTreeIterator const & iterator
        ) const noexcept -> bool {

            return this->_pCurrentNode == iterator._pCurrentNode;
        }


        template < typename __ElementType >
        auto RedBlackTreeIterator < __ElementType > :: operator != (
                RedBlackTreeIterator const & iterator
        ) const noexcept -> bool {

            return ! this->operator== ( iterator );
        }


        template < typename __ElementType >
        RedBlackTreeIterator < __ElementType > :: operator bool () const noexcept {

            return this->_pCurrentNode != nullptr;
        }





        template < typename __ElementType >
        RedBlackTreeConstIterator < __ElementType > :: RedBlackTreeConstIterator () noexcept = default;


        template < typename __ElementType >
        RedBlackTreeConstIterator < __ElementType > :: RedBlackTreeConstIterator (
                RBTreeNode const  *  pRoot,
                RBTreeNode const  *  pCurrentNode
        ) noexcept :
                _pRoot        ( pRoot ),
                _pCurrentNode ( pCurrentNode ) {

        }


        template < typename __ElementType >
        RedBlackTreeConstIterator < __ElementType > :: RedBlackTreeConstIterator (
                const RedBlackTreeConstIterator & iterator
        ) noexcept :
                _pRoot        ( iterator._pRoot ),
                _pCurrentNode ( iterator._pCurrentNode) {

        }


        template < typename __ElementType >
        RedBlackTreeConstIterator < __ElementType > :: RedBlackTreeConstIterator (
                RedBlackTreeConstIterator && iterator
        ) noexcept :
                _pRoot        ( cds :: exchange ( iterator._pRoot, nullptr ) ),
                _pCurrentNode ( cds :: exchange ( iterator._pCurrentNode, nullptr ) ) {

        }


        template < typename __ElementType >
        auto RedBlackTreeConstIterator < __ElementType > :: operator = (
                RedBlackTreeConstIterator const & iterator
        ) noexcept -> RedBlackTreeConstIterator & {

            if ( this == & iterator ) {
                return * this;
            }

            this->_pRoot        = iterator._pRoot;
            this->_pCurrentNode = iterator._pCurrentNode;

            return * this;
        }


        template < typename __ElementType >
        auto RedBlackTreeConstIterator < __ElementType > :: operator = (
                RedBlackTreeConstIterator && iterator
        ) noexcept -> RedBlackTreeConstIterator & {

            if ( this == & iterator )
                return * this;

            this->_pRoot        = cds :: exchange ( iterator._pRoot, nullptr );
            this->_pCurrentNode = cds :: exchange ( iterator._pCurrentNode, nullptr );

            return * this;
        }


        template < typename __ElementType >
        auto RedBlackTreeConstIterator < __ElementType > :: operator ++ (
        ) noexcept -> RedBlackTreeConstIterator & {

            if ( this->_pCurrentNode->_pRight != __hidden :: __impl :: __endNode < __ElementType > () ) {
                this->_pCurrentNode = this->_pCurrentNode->_pRight;
                while ( this->_pCurrentNode->_pLeft != __endNode < __ElementType > () ) {
                    this->_pCurrentNode = this->_pCurrentNode->_pLeft;
                }
                return * this;
            }

            if ( this->_pCurrentNode == this->_pRoot )
                return nullptr;

            while ( this->_pCurrentNode == this->_pCurrentNode->_pParent->_pRight ) {
                this->_pCurrentNode = this->_pCurrentNode->_pParent;
                if ( this->_pCurrentNode == this->_pRoot )
                    return nullptr;
            }
            this->_pCurrentNode = this->_pCurrentNode->_pParent;

            return * this;
        }


        template < typename __ElementType >
        auto RedBlackTreeConstIterator < __ElementType > :: operator ++ (int) noexcept -> RedBlackTreeConstIterator {

            auto copy = * this;
            ++ ( * this );
            return copy;
        }


        template < typename __ElementType >
        auto RedBlackTreeConstIterator < __ElementType > :: operator -- (
        ) noexcept -> RedBlackTreeConstIterator & {

            if ( this->_pCurrentNode->_pLeft != __hidden :: __impl :: __endNode < __ElementType > () ) {
                this->_pCurrentNode = this->_pCurrentNode->_pLeft;
                while ( this->_pCurrentNode->_pRight != __endNode < __ElementType > () ) {
                    this->_pCurrentNode = this->_pCurrentNode->_pRight;
                }
                return * this;
            }

            if ( this->_pCurrentNode == this->_pRoot )
                return nullptr;

            while ( this->_pCurrentNode == this->_pCurrentNode->_pParent->_pLeft ) {
                this->_pCurrentNode = this->_pCurrentNode->_pParent;
                if ( this->_pCurrentNode == this->_pRoot )
                    return nullptr;
            }
            this->_pCurrentNode = this->_pCurrentNode->_pParent;

            return * this;
        }


        template < typename __ElementType >
        auto RedBlackTreeConstIterator < __ElementType > :: operator -- (int) noexcept -> RedBlackTreeConstIterator {

            auto copy = *this;
            -- ( * this );
            return copy;
        }


        template < typename __ElementType >
        auto RedBlackTreeConstIterator < __ElementType > :: operator * (
        ) const noexcept -> __ElementType const & {

            return this->_pCurrentNode->_data;
        }


        template < typename __ElementType >
        auto RedBlackTreeConstIterator < __ElementType > :: operator -> (
        ) const noexcept -> __ElementType const * {

            return & this->_pCurrentNode->_data;
        }


        template < typename __ElementType >
        auto RedBlackTreeConstIterator < __ElementType > :: operator == (
                RedBlackTreeConstIterator const & iterator
        ) const noexcept -> bool {

            return this->_pCurrentNode == iterator._pCurrentNode;
        }


        template < typename __ElementType >
        auto RedBlackTreeConstIterator < __ElementType > :: operator != (
                RedBlackTreeConstIterator const & iterator
        ) const noexcept -> bool {

            return ! this->operator== ( iterator );
        }


        template < typename __ElementType >
        RedBlackTreeConstIterator < __ElementType > :: operator bool () const noexcept {

            return this->_pCurrentNode != nullptr;
        }
    }
}

#endif //__CDS_EX_SHARED_RED_BLACK_TREE_ITERATOR_IMPL_HPP__
