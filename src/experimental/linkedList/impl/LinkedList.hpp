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
            -- this->_size;

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

            ++ this->_size;
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

            ++ this->_size;
            return pNewNode->_pData = nullptr;
        }

        template < typename T >
        __CDS_OptimalInline auto LinkedList < T > :: delegateIterator ( DelegateIteratorRequestType requestType ) noexcept -> cds :: UniquePointer < DelegateIterator > {
            switch ( requestType ) {
                case DelegateIteratorRequestType :: ForwardBegin:
                    return Memory :: instance().create < LinkedListDelegateIterator > ( this->_pFront, true );
                case DelegateIteratorRequestType :: ForwardEnd:
                    return Memory :: instance().create < LinkedListDelegateIterator > ( nullptr, true );
                case DelegateIteratorRequestType :: BackwardBegin:
                    return Memory :: instance().create < LinkedListDelegateIterator > ( this->_pBack, false );
                case DelegateIteratorRequestType :: BackwardEnd:
                    return Memory :: instance().create < LinkedListDelegateIterator > ( nullptr, false );
            }
        }

        template < typename T >
        __CDS_OptimalInline auto LinkedList < T > :: delegateConstIterator ( DelegateIteratorRequestType requestType ) const noexcept -> cds :: UniquePointer < DelegateConstIterator > {
            switch ( requestType ) {
                case DelegateIteratorRequestType :: ForwardBegin:
                    return Memory :: instance().create < LinkedListDelegateConstIterator > ( this->_pFront, true );
                case DelegateIteratorRequestType :: ForwardEnd:
                    return Memory :: instance().create < LinkedListDelegateConstIterator > ( nullptr, true );
                case DelegateIteratorRequestType :: BackwardBegin:
                    return Memory :: instance().create < LinkedListDelegateConstIterator > ( this->_pBack, false );
                case DelegateIteratorRequestType :: BackwardEnd:
                    return Memory :: instance().create < LinkedListDelegateConstIterator > ( nullptr, false );
            }
        }

//        template < typename T >
//        auto LinkedList < T > :: remove ( Collection < Iterator > const & iterators ) noexcept -> Size {
//            LinkedList < void const * > nodes;
//
//            for ( auto iterator = iterators.begin(), end = iterators.end(); iterator != end; ++ iterator ) {
//                if ( iterator->of ( this ) ) {
//                    auto pNode = reinterpret_cast < LinkedListDelegateIterator const * > ( Collection < T > :: acquireDelegate ( * iterator ) )->node();
//                    if ( pNode != nullptr ) {
//                        nodes.pushBack ( reinterpret_cast < void const * > ( pNode ) );
//                    }
//                }
//            }
//
//            return this->remove ( reinterpret_cast < LinkedList < Node const * > const & > ( nodes ) );
//        }
//
//        template < typename T >
//        auto LinkedList < T > :: remove ( Collection < ConstIterator > const & iterators ) noexcept -> Size {
//            LinkedList < void const * > nodes;
//
//            for ( auto iterator = iterators.begin(), end = iterators.end(); iterator != end; ++ iterator ) {
//                if ( iterator->of ( this ) ) {
//                    auto pNode = reinterpret_cast < LinkedListDelegateConstIterator const * > ( Collection < T > :: acquireDelegate ( * iterator ) )->node();
//                    if ( pNode != nullptr ) {
//                        nodes.pushBack ( reinterpret_cast < void const * > ( pNode ) );
//                    }
//                }
//            }
//
//            return this->remove ( reinterpret_cast < LinkedList < Node const * > const & > ( nodes ) );
//        }
//
//        template < typename T >
//        auto LinkedList < T > :: remove ( Collection < ReverseIterator > const & iterators ) noexcept -> Size {
//            LinkedList < void const * > nodes;
//
//            for ( auto iterator = iterators.begin(), end = iterators.end(); iterator != end; ++ iterator ) {
//                if ( iterator->of ( this ) ) {
//                    auto pNode = reinterpret_cast < LinkedListDelegateIterator const * > ( Collection < T > :: acquireDelegate ( * iterator ) )->node();
//                    if ( pNode != nullptr ) {
//                        nodes.pushBack ( reinterpret_cast < void const * > ( pNode ) );
//                    }
//                }
//            }
//
//            return this->remove ( reinterpret_cast < LinkedList < Node const * > const & > ( nodes ) );
//        }
//
//        template < typename T >
//        auto LinkedList < T > :: remove ( Collection < ConstReverseIterator > const & iterators ) noexcept -> Size {
//            LinkedList < void const * > nodes;
//
//            for ( auto iterator = iterators.begin(), end = iterators.end(); iterator != end; ++ iterator ) {
//                if ( iterator->of ( this ) ) {
//                    auto pNode = reinterpret_cast < LinkedListDelegateConstIterator const * > ( Collection < T > :: acquireDelegate ( * iterator ) )->node();
//                    if ( pNode != nullptr ) {
//                        nodes.pushBack ( reinterpret_cast < void const * > ( pNode ) );
//                    }
//                }
//            }
//
//            return this->remove ( reinterpret_cast < LinkedList < Node const * > const & > ( nodes ) );
//        }

        template < typename T >
        auto LinkedList < T > :: remove ( Iterator const * pIterators, Size iteratorCount ) noexcept -> Size {
            LinkedList < void const * > nodes;

            for ( uint64 index = 0; index < iteratorCount; ++ index ) {
                if ( pIterators[index].of ( this ) ) {
                    auto pNode = reinterpret_cast < LinkedListDelegateIterator const * > ( Collection < T > :: acquireDelegate ( pIterators [ index ] ) )->node();
                    if ( pNode != nullptr ) {
                        nodes.pushBack ( reinterpret_cast < void const * > ( pNode ) );
                    }
                }
            }

            return this->remove ( reinterpret_cast < LinkedList < Node const * > const & > ( nodes ) );
        }

        template < typename T >
        auto LinkedList < T > :: remove ( ConstIterator const * pIterators, Size iteratorCount ) noexcept -> Size {
            LinkedList < void const * > nodes;

            for ( uint64 index = 0; index < iteratorCount; ++ index ) {
                if ( pIterators[index].of ( this ) ) {
                    auto pNode = reinterpret_cast < LinkedListDelegateConstIterator const * > ( Collection < T > :: acquireDelegate ( pIterators [ index ] ) )->node();
                    if ( pNode != nullptr ) {
                        nodes.pushBack ( reinterpret_cast < void const * > ( pNode ) );
                    }
                }
            }

            return this->remove ( reinterpret_cast < LinkedList < Node const * > const & > ( nodes ) );
        }

        template < typename T >
        auto LinkedList < T > :: remove ( ReverseIterator const * pIterators, Size iteratorCount ) noexcept -> Size {
            LinkedList < void const * > nodes;

            for ( uint64 index = 0; index < iteratorCount; ++ index ) {
                if ( pIterators[index].of ( this ) ) {
                    auto pNode = reinterpret_cast < LinkedListDelegateIterator const * > ( Collection < T > :: acquireDelegate ( pIterators [ index ] ) )->node();
                    if ( pNode != nullptr ) {
                        nodes.pushBack ( reinterpret_cast < void const * > ( pNode ) );
                    }
                }
            }

            return this->remove ( reinterpret_cast < LinkedList < Node const * > const & > ( nodes ) );
        }

        template < typename T >
        auto LinkedList < T > :: remove ( ConstReverseIterator const * pIterators, Size iteratorCount ) noexcept -> Size {
            LinkedList < void const * > nodes;

            for ( uint64 index = 0; index < iteratorCount; ++ index ) {
                if ( pIterators[index].of ( this ) ) {
                    auto pNode = reinterpret_cast < LinkedListDelegateConstIterator const * > ( Collection < T > :: acquireDelegate ( pIterators [ index ] ) )->node();
                    if ( pNode != nullptr ) {
                        nodes.pushBack ( reinterpret_cast < void const * > ( pNode ) );
                    }
                }
            }

            return this->remove ( reinterpret_cast < LinkedList < Node const * > const & > ( nodes ) );
        }

        template < typename T >
        auto LinkedList < T > :: remove ( Collection < Node const * > const & nodes ) noexcept -> Size {
            Size removedCount = 0ULL;

            while ( nodes.contains ( this->_pFront ) ) {
                auto pNode                  = this->_pFront;
                this->_pFront               = this->_pFront->_pNext;

                if ( this->_pFront != nullptr ) {
                    this->_pFront->_pPrevious = nullptr;
                } else {
                    this->_pBack = nullptr;
                }

                Memory :: instance ().destroy ( pNode->_pData );
                Memory :: instance ().destroy ( pNode );

                -- this->_size;
                ++ removedCount;
            }

            while ( nodes.contains ( this->_pBack ) ) {
                auto pNode                  = this->_pBack;
                this->_pBack                = this->_pBack->_pPrevious;

                if ( this->_pBack != nullptr ) {
                    this->_pBack->_pNext = nullptr;
                } else {
                    this->_pFront = nullptr;
                }

                Memory :: instance ().destroy ( pNode->_pData );
                Memory :: instance ().destroy ( pNode );

                -- this->_size;
                ++ removedCount;
            }

            if ( this->size() < 2 ) {
                return removedCount;
            }

            auto pNode = this->_pFront->_pNext;
            while ( pNode != nullptr && pNode->_pNext != nullptr ) {
                while ( nodes.contains ( pNode ) ) {
                    auto pNext      = pNode->_pNext;
                    auto pPrevious  = pNode->_pPrevious;

                    pNode->_pNext->_pPrevious = pPrevious;
                    pNode->_pPrevious->_pNext = pNext;

                    Memory :: instance().destroy ( pNode->_pData );
                    Memory :: instance().destroy ( pNode );

                    pNode = pNext;

                    -- this->_size;
                    ++ removedCount;
                }

                pNode = pNode->_pNext;
            }

            return removedCount;
        }

        template < typename T >
        auto LinkedList < T > :: popFront () noexcept -> void {
            if ( this->empty () ) {
                return;
            }

            this->_size --;

            auto node = this->_pFront;

            if ( this->_size == 0ULL ) {
                this->_pFront   = nullptr;
                this->_pBack    = nullptr;

                Memory :: instance().destroy ( node->_pData );
                Memory :: instance().destroy ( node );
                return;
            }

            this->_pFront = this->_pFront->_pNext;
            Memory :: instance().destroy ( node->_pData );
            Memory :: instance().destroy ( node );
            this->_pFront->_pPrevious = nullptr;
        }

        template < typename T >
        auto LinkedList < T > :: popBack () noexcept -> void {
            if ( this->empty () ) {
                return;
            }

            this->_size --;

            auto node = this->_pBack;

            if ( this->_size == 0ULL ) {
                this->_pBack = nullptr;
                this->_pFront = nullptr;

                Memory :: instance().destroy ( node->_pData );
                Memory :: instance().destroy ( node );
                return;
            }

            this->_pBack = this->_pBack->_pPrevious;
            Memory :: instance().destroy ( node->_pData );
            Memory :: instance().destroy ( node );
            this->_pBack->_pNext = nullptr;
        }

        template < typename T >
        auto LinkedList < T > :: removeAt ( Index index ) noexcept -> bool {
            if (index < 0 || index >= this->size() ) {
                return false;
            }

            if ( index == 0 ) {
                this->popFront();
                return true;
            }

            if ( index == this->size() - 1 ) {
                this->popBack();
                return true;
            }

            auto current = this->_pFront;
            Index currentIndex = 1;

            while ( current->_pNext != nullptr && currentIndex < index ) {
                current = current->_pNext;
                currentIndex ++;
            }

            auto toRemove = current->_pNext;

            current->_pNext->_pNext->_pPrevious = current;
            current->_pNext = current->_pNext->_pNext;

            Memory :: instance().destroy ( toRemove->_pData );
            Memory :: instance().destroy ( toRemove );
            -- this->_size;

            return true;
        }

        template < typename T >
        auto LinkedList < T > :: removeAt ( Collection < Index > const & indices ) noexcept -> Size {

            Node ** pToKeep         = Memory :: instance().createArray < Node * > ( this->size() );
            Node ** pToRemove       = Memory :: instance().createArray < Node * > ( indices.size() );
            Size    toKeepLength    = 0ULL;
            Size    toRemoveLength  = 0ULL;

            Index currentIndex = 0;
            for ( Node * pHead = this->_pFront; pHead != nullptr; pHead = pHead->_pNext, ++ currentIndex ) {
                if ( indices.contains ( currentIndex ) ) {
                    pToRemove [ toRemoveLength ++ ] = pHead;
                } else {
                    pToKeep [ toKeepLength ++ ] = pHead;
                }
            }

            if ( toKeepLength > 0 ) {
                pToKeep [ 0 ]->_pPrevious = nullptr;
                pToKeep [ toKeepLength - 1 ]->_pNext = nullptr;

                this->_pFront   = pToKeep [0];
                this->_pBack    = pToKeep [ toKeepLength - 1 ];
            } else {
                this->_pFront   = nullptr;
                this->_pBack    = nullptr;
            }

            for ( Index nodeIndex = 0; nodeIndex + 1 < toKeepLength; ++ nodeIndex ) {
                pToKeep [ nodeIndex ]->_pNext           = pToKeep [ nodeIndex + 1 ];
                pToKeep [ nodeIndex + 1 ]->_pPrevious   = pToKeep [ nodeIndex ];
            }

            for ( Index nodeIndex = 0; nodeIndex < toRemoveLength; ++ nodeIndex ) {
                Memory :: instance().destroy ( pToRemove [ nodeIndex ]->_pData );
                Memory :: instance().destroy ( pToRemove [ nodeIndex ] );
            }

            Memory :: instance().destroyArray( pToKeep );
            Memory :: instance().destroyArray( pToRemove );

            return toRemoveLength;
        }

        template < typename T >
        auto LinkedList < T > :: makeUnique () noexcept -> void {
            Node * pNewHead = nullptr;
            Node * pNewLast = nullptr;
            Size newSize    = 0ULL;

            Node * pHead    = this->_pFront;

            static auto listContains = [](
                    Node              * pList,
                    ElementType const & element
            ) noexcept -> bool {
                while ( pList != nullptr ) {
                    if ( Type < T > :: compare ( element, * pList->_pData ) ) {
                        return true;
                    }

                    pList = pList->_pNext;
                }

                return false;
            };

            while ( pHead != nullptr ) {
                if ( ! listContains ( pNewHead, * pHead->_pData ) ) {
                    if ( pNewHead == nullptr ) {

                        pNewHead                        = Memory :: instance().create < Node > ();

                        pNewHead->_pData                = cds :: exchange ( pHead->_pData, nullptr );
                        pNewHead->_pNext                = nullptr;
                        pNewHead->_pPrevious            = nullptr;

                        pNewLast                        = pNewHead;
                        newSize                         = 1ULL;
                    } else {

                        pNewLast->_pNext                = Memory :: instance().create < Node > ();

                        pNewLast->_pNext->_pData        = cds :: exchange ( pHead->_pData, nullptr );
                        pNewLast->_pNext->_pNext        = nullptr;
                        pNewLast->_pNext->_pPrevious    = pNewLast;
                        ++ newSize;
                    }
                }

                pHead = pHead->_pNext;
            }

            this->clear();

            this->_pFront = pNewHead;
            this->_pBack  = pNewLast;
            this->_size   = newSize;
        }

    }
}

#endif // __CDS_EX_LINKED_LIST_IMPL_HPP__
