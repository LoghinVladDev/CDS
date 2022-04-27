//
// Created by loghin on 4/27/22.
//

#ifndef __CDS_EX_LINKED_LIST_IMPL_HPP__
#define __CDS_EX_LINKED_LIST_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename T >
        __CDS_cpplang_ConstexprOverride auto LinkedList < T > :: get ( Index index ) noexcept (false) -> ElementType & {
            if ( this->empty() ) {
                throw OutOfBoundsException(index, 0);
            }

            if ( index < 0 ) {
                index += ((-index) / this->size() + 1) * this->size();
            }

            if ( index >= static_cast<Index>(this->size()) ) {
                index = index % this->size();
            }

            auto current = 0;
            auto pHead = this->_pFront;

            while ( pHead != nullptr ) {
                if ( current == index ) {
                    return * pHead->_pData;
                }

                pHead = pHead->_pNext;
                ++ current;
            }

            throw RuntimeException ( "Unexpected Error in LinkedList :: get" );
        }

        template < typename T >
        __CDS_cpplang_ConstexprOverride auto LinkedList < T > :: get ( Index index ) const noexcept (false) -> ElementType const & {
            if ( this->empty() ) {
                throw OutOfBoundsException(index, 0);
            }

            if ( index < 0 ) {
                index += ((-index) / this->size() + 1) * this->size();
            }

            if ( index >= static_cast<Index>(this->size()) ) {
                index = index % this->size();
            }

            auto current = 0;
            auto pHead = this->_pFront;

            while ( pHead != nullptr ) {
                if ( current == index ) {
                    return * pHead->_pData;
                }

                pHead = pHead->_pNext;
                ++ current;
            }

            throw RuntimeException ( "Unexpected Error in LinkedList :: get" );
        }

        template < typename T >
        __CDS_cpplang_ConstexprOverride auto LinkedList < T > :: front () noexcept (false) -> ElementType & {
            if ( this->empty() ) {
                throw OutOfBoundsException("List is Empty");
            }

            return * this->_pFront->_pData;
        }

        template < typename T >
        __CDS_cpplang_ConstexprOverride auto LinkedList < T > :: front () const noexcept (false) -> ElementType const & {
            if ( this->empty() ) {
                throw OutOfBoundsException("List is Empty");
            }

            return * this->_pFront->_pData;
        }

        template < typename T >
        __CDS_cpplang_ConstexprOverride auto LinkedList < T > :: back () noexcept (false) -> ElementType & {
            if ( this->empty() ) {
                throw OutOfBoundsException("List is Empty");
            }

            return * this->_pBack->_pData;
        }

        template < typename T >
        __CDS_cpplang_ConstexprOverride auto LinkedList < T > :: back () const noexcept (false) -> ElementType const & {
            if ( this->empty() ) {
                throw OutOfBoundsException("List is Empty");
            }

            return * this->_pBack->_pData;
        }

        template < typename T >
        __CDS_OptimalInline auto LinkedList < T > :: equals ( Object const & object ) const noexcept -> bool {
            return this->List < T > :: equals ( object );
        }

        template < typename T >
        __CDS_OptimalInline auto LinkedList < T > :: remove ( Iterator const & iterator ) noexcept -> bool {
            if ( ! iterator.of ( this ) ) {
                return false;
            }

            return this->remove ( reinterpret_cast < LinkedListDelegateIterator const * > ( Collection < T > :: acquireDelegate ( iterator ) )->node() );
        }

        template < typename T >
        __CDS_OptimalInline auto LinkedList < T > :: remove ( ConstIterator const & iterator ) noexcept -> bool {
            if ( ! iterator.of ( this ) ) {
                return false;
            }

            return this->remove ( reinterpret_cast < LinkedListDelegateConstIterator const * > ( Collection < T > :: acquireDelegate ( iterator ) )->node() );
        }

        template < typename T >
        __CDS_OptimalInline auto LinkedList < T > :: remove ( ReverseIterator const & iterator ) noexcept -> bool {
            if ( ! iterator.of ( this ) ) {
                return false;
            }

            return this->remove ( reinterpret_cast < LinkedListDelegateIterator const * > ( Collection < T > :: acquireDelegate ( iterator ) )->node() );
        }

        template < typename T >
        __CDS_OptimalInline auto LinkedList < T > :: remove ( ConstReverseIterator const & iterator ) noexcept -> bool {
            if ( ! iterator.of ( this ) ) {
                return false;
            }

            return this->remove ( reinterpret_cast < LinkedListDelegateConstIterator const * > ( Collection < T > :: acquireDelegate ( iterator ) )->node() );
        }

        template < typename T >
        auto LinkedList < T > :: remove ( Node const * pNode ) noexcept -> bool {
            if ( pNode == nullptr ) {
                return false;
            }

            if ( pNode == this->_pFront ) {
                this->popFront();
                return true;
            }

            if ( pNode == this->_pBack ) {
                this->popBack();
                return true;
            }

            pNode->_pPrevious->_pNext = pNode->_pNext;
            pNode->_pNext->_pPrevious = pNode->_pPrevious;
            Memory :: instance ().destroy ( pNode->_pData );
            Memory :: instance ().destroy ( pNode );

            return true;
        }

        template < typename T >
        __CDS_OptimalInline auto LinkedList < T > :: pNewFront () noexcept -> ElementType * & {
            auto newNode = Memory :: instance().create < Node > ();
            newNode->_pNext     = this->_pFront;
            newNode->_pPrevious = nullptr;

            if ( this->_pFront != nullptr ) {
                this->_pFront->_pPrevious = newNode;
            }

            this->_pFront = newNode;

            if ( this->_pBack == nullptr ) {
                this->_pBack = newNode;
            }

            ++ this->_size;

            return newNode->_pData = nullptr;
        }

        template < typename T >
        __CDS_OptimalInline auto LinkedList < T > :: pNewBack () noexcept -> ElementType * & {
            auto newNode = Memory::instance().create < Node > ();
            newNode->_pNext     = nullptr;
            newNode->_pPrevious = this->_pBack;

            if ( this->_pBack != nullptr ) {
                this->_pBack->_pNext = newNode;
            }

            this->_pBack = newNode;

            if ( this->_pFront == nullptr ) {
                this->_pFront = newNode;
            }

            ++ this->_size;

            return newNode->_pData = nullptr;
        }

        template < typename T >
        __CDS_OptimalInline auto LinkedList < T > :: pNewBefore ( Iterator const & iterator ) noexcept -> ElementType * & {
            return this->pNewBefore ( reinterpret_cast < LinkedListDelegateIterator const * > ( Collection < T > :: acquireDelegate ( iterator ) )->node() );
        }

        template < typename T >
        __CDS_OptimalInline auto LinkedList < T > :: pNewAfter ( Iterator const & iterator ) noexcept -> ElementType * & {
            return this->pNewAfter ( reinterpret_cast < LinkedListDelegateIterator const * > ( Collection < T > :: acquireDelegate ( iterator ) )->node() );
        }

        template < typename T >
        __CDS_OptimalInline auto LinkedList < T > :: pNewBefore ( ConstIterator const & iterator ) noexcept -> ElementType * & {
            return this->pNewBefore ( reinterpret_cast < LinkedListDelegateConstIterator const * > ( Collection < T > :: acquireDelegate ( iterator ) )->node() );
        }

        template < typename T >
        __CDS_OptimalInline auto LinkedList < T > :: pNewAfter ( ConstIterator const & iterator ) noexcept -> ElementType * & {
            return this->pNewAfter ( reinterpret_cast < LinkedListDelegateConstIterator const * > ( Collection < T > :: acquireDelegate ( iterator ) )->node() );
        }

        template < typename T >
        __CDS_OptimalInline auto LinkedList < T > :: pNewBefore ( ReverseIterator const & iterator ) noexcept -> ElementType * & {
            return this->pNewBefore ( reinterpret_cast < LinkedListDelegateIterator const * > ( Collection < T > :: acquireDelegate ( iterator ) )->node() );
        }

        template < typename T >
        __CDS_OptimalInline auto LinkedList < T > :: pNewAfter ( ReverseIterator const & iterator ) noexcept -> ElementType * & {
            return this->pNewAfter ( reinterpret_cast < LinkedListDelegateIterator const * > ( Collection < T > :: acquireDelegate ( iterator ) )->node() );
        }

        template < typename T >
        __CDS_OptimalInline auto LinkedList < T > :: pNewBefore ( ConstReverseIterator const & iterator ) noexcept -> ElementType * & {
            return this->pNewBefore ( reinterpret_cast < LinkedListDelegateConstIterator const * > ( Collection < T > :: acquireDelegate ( iterator ) )->node() );
        }

        template < typename T >
        __CDS_OptimalInline auto LinkedList < T > :: pNewAfter ( ConstReverseIterator const & iterator ) noexcept -> ElementType * & {
            return this->pNewAfter ( reinterpret_cast < LinkedListDelegateConstIterator const * > ( Collection < T > :: acquireDelegate ( iterator ) )->node() );
        }

        template < typename T >
        LinkedList < T > :: ~LinkedList () noexcept {
            this->LinkedList < T > :: clear ();
        }

        template < typename T >
        auto LinkedList < T > :: clear () noexcept -> void {
            while ( this->_pFront != nullptr ) {
                auto current = this->_pFront;
                this->_pFront = this->_pFront->_pNext;

                Memory :: instance().destroy (current->_pData);
                Memory :: instance().destroy (current);
            }

            this->_pBack = nullptr;
            this->_size = 0;
        }

        template < typename T >
        auto LinkedList < T > :: pNewBefore ( Node const * pNode ) noexcept -> ElementType * & {
            auto pNewNode       = Memory :: instance().create < Node > ();
            auto pMutableNode   = const_cast < Node * > ( pNode );

            pNewNode->_pPrevious                = pMutableNode->_pPrevious;
            pNewNode->_pNext                    = pMutableNode;
            pMutableNode->_pPrevious->_pNext    = pNewNode;
            pMutableNode->_pPrevious            = pNewNode;

            return pNewNode->_pData = nullptr;
        }

        template < typename T >
        auto LinkedList < T > :: pNewAfter ( Node const * pNode ) noexcept -> ElementType * & {
            auto pNewNode = Memory :: instance().create < Node > ();
            auto pMutableNode   = const_cast < Node * > ( pNode );

            pNewNode->_pPrevious                = pMutableNode;
            pNewNode->_pNext                    = pMutableNode->_pNext;
            pMutableNode->_pNext->_pPrevious    = pNewNode;
            pMutableNode->_pNext                = pNewNode;

            return pNewNode->_pData = nullptr;
        }

    }
}

#endif // __CDS_EX_LINKED_LIST_IMPL_HPP__
