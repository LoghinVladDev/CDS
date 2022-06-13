//
// Created by loghin on 4/27/22.
//

#ifndef __CDS_EX_LINKED_LIST_IMPL_HPP__
#define __CDS_EX_LINKED_LIST_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto LinkedList < __ElementType > :: delegateIterator ( DelegateIteratorRequestType requestType ) noexcept -> cds :: UniquePointer < DelegateIterator > {

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

            return nullptr;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto LinkedList < __ElementType > :: delegateConstIterator ( DelegateIteratorRequestType requestType ) const noexcept -> cds :: UniquePointer < DelegateConstIterator > {

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

            return nullptr;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        LinkedList < __ElementType > :: LinkedList (
                LinkedList const & list
        ) noexcept :
                List < __ElementType > ( list.size() ) {

            bool firstNode = false;
            for ( auto iterator = list.begin(), end = list.end (); iterator != end; ++ iterator ) {

                auto newNode    = Memory :: instance().create < Node > ();
                newNode->_pData = Memory :: instance().create < __ElementType > ( * iterator );
                newNode->_pNext = nullptr;

                if ( firstNode ) {
                    this->_pFront   = newNode;
                    this->_pBack    = newNode;
                    continue;
                }

                this->_pBack->_pNext    = newNode;
                this->_pBack            = newNode;
            }
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr LinkedList < __ElementType > :: LinkedList (
                LinkedList && list
        ) noexcept :
                List < __ElementType > ( std :: move ( list ) ),
                _pFront ( cds :: exchange ( list._pFront, nullptr ) ),
                _pBack ( cds :: exchange ( list._pBack, nullptr ) ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __IteratorType, meta :: EnableIf < meta :: isIterator < __IteratorType > () > > // NOLINT(bugprone-reserved-identifier)
        LinkedList < __ElementType > :: LinkedList (
                __IteratorType const & begin,
                __IteratorType const & end
        ) noexcept {

            for ( auto iterator = begin; iterator != end; ++ iterator ) {
                this->LinkedList < __ElementType > :: pushBack ( * iterator );
            }
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        LinkedList < __ElementType > :: LinkedList (
                InitializerList const & initializerList
        ) noexcept :
                LinkedList (
                        initializerList.begin(),
                        initializerList.end()
                ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __OtherElementType, meta :: EnableIf < meta :: isConvertible < __OtherElementType, __ElementType > () > > // NOLINT(bugprone-reserved-identifier)
        LinkedList < __ElementType > :: LinkedList (
                Collection < __OtherElementType > const & collection
        ) noexcept {

            for ( auto iterator = collection.begin(), end = collection.end(); iterator != end; ++ iterator ) {
                this-> LinkedList < __ElementType > :: pushBack ( * iterator );
            }
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        LinkedList < __ElementType > :: ~LinkedList () noexcept {

            this->LinkedList < __ElementType > :: clear ();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto LinkedList < __ElementType > :: remove (
                Node const * pNode
        ) noexcept -> bool {

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


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto LinkedList < __ElementType > :: remove (
                Collection < Node const * > const & nodes
        ) noexcept -> Size {

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


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto LinkedList < __ElementType > :: removeAt (
                Index index
        ) noexcept -> bool {

            if ( index < 0 || index >= this->size() ) {
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


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto LinkedList < __ElementType > :: removeAt (
                Collection < Index > const & indices
        ) noexcept -> Size {

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


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto LinkedList < __ElementType > :: removeAt (
                std :: initializer_list < Index > const & indices
        ) noexcept -> Size {

            Node ** pToKeep         = Memory :: instance().createArray < Node * > ( this->size() );
            Node ** pToRemove       = Memory :: instance().createArray < Node * > ( indices.size() );
            Size    toKeepLength    = 0ULL;
            Size    toRemoveLength  = 0ULL;

            Index currentIndex = 0;
            for ( Node * pHead = this->_pFront; pHead != nullptr; pHead = pHead->_pNext, ++ currentIndex ) {
                if ( __hidden :: __impl :: __initializerListContains ( indices, currentIndex ) ) {
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


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto LinkedList < __ElementType > :: remove (
                Iterator const & iterator
        ) noexcept -> bool {

            if ( ! iterator.of ( this ) ) {
                return false;
            }

            return this->remove ( reinterpret_cast < LinkedListDelegateIterator const * > ( Collection < __ElementType > :: acquireDelegate ( iterator ) )->node() );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto LinkedList < __ElementType > :: remove (
                ConstIterator const & iterator
        ) noexcept -> bool {

            if ( ! iterator.of ( this ) ) {
                return false;
            }

            return this->remove ( reinterpret_cast < LinkedListDelegateConstIterator const * > ( Collection < __ElementType > :: acquireDelegate ( iterator ) )->node() );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto LinkedList < __ElementType > :: remove (
                ReverseIterator const & iterator
        ) noexcept -> bool {

            if ( ! iterator.of ( this ) ) {
                return false;
            }

            return this->remove ( reinterpret_cast < LinkedListDelegateIterator const * > ( Collection < __ElementType > :: acquireDelegate ( iterator ) )->node() );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto LinkedList < __ElementType > :: remove (
                ConstReverseIterator const & iterator
        ) noexcept -> bool {

            if ( ! iterator.of ( this ) ) {
                return false;
            }

            return this->remove ( reinterpret_cast < LinkedListDelegateConstIterator const * > ( Collection < __ElementType > :: acquireDelegate ( iterator ) )->node() );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto LinkedList < __ElementType > :: remove (
                Iterator    const * pIterators,
                Size                iteratorCount
        ) noexcept -> Size {

            LinkedList < void const * > nodes;

            for ( uint64 index = 0; index < iteratorCount; ++ index ) {
                if ( pIterators[index].of ( this ) ) {
                    auto pNode = reinterpret_cast < LinkedListDelegateIterator const * > ( Collection < __ElementType > :: acquireDelegate ( pIterators [ index ] ) )->node();
                    if ( pNode != nullptr ) {
                        nodes.pushBack ( reinterpret_cast < void const * > ( pNode ) );
                    }
                }
            }

            return this->remove ( reinterpret_cast < LinkedList < Node const * > const & > ( nodes ) );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto LinkedList < __ElementType > :: remove (
                ConstIterator   const * pIterators,
                Size                    iteratorCount
        ) noexcept -> Size {

            LinkedList < void const * > nodes;

            for ( uint64 index = 0; index < iteratorCount; ++ index ) {
                if ( pIterators[index].of ( this ) ) {
                    auto pNode = reinterpret_cast < LinkedListDelegateConstIterator const * > ( Collection < __ElementType > :: acquireDelegate ( pIterators [ index ] ) )->node();
                    if ( pNode != nullptr ) {
                        nodes.pushBack ( reinterpret_cast < void const * > ( pNode ) );
                    }
                }
            }

            return this->remove ( reinterpret_cast < LinkedList < Node const * > const & > ( nodes ) );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto LinkedList < __ElementType > :: remove (
                ReverseIterator const * pIterators,
                Size                    iteratorCount
        ) noexcept -> Size {

            LinkedList < void const * > nodes;

            for ( uint64 index = 0; index < iteratorCount; ++ index ) {
                if ( pIterators[index].of ( this ) ) {
                    auto pNode = reinterpret_cast < LinkedListDelegateIterator const * > ( Collection < __ElementType > :: acquireDelegate ( pIterators [ index ] ) )->node();
                    if ( pNode != nullptr ) {
                        nodes.pushBack ( reinterpret_cast < void const * > ( pNode ) );
                    }
                }
            }

            return this->remove ( reinterpret_cast < LinkedList < Node const * > const & > ( nodes ) );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto LinkedList < __ElementType > :: remove (
                ConstReverseIterator    const * pIterators,
                Size                            iteratorCount
        ) noexcept -> Size {

            LinkedList < void const * > nodes;

            for ( uint64 index = 0; index < iteratorCount; ++ index ) {
                if ( pIterators[index].of ( this ) ) {
                    auto pNode = reinterpret_cast < LinkedListDelegateConstIterator const * > ( Collection < __ElementType > :: acquireDelegate ( pIterators [ index ] ) )->node();
                    if ( pNode != nullptr ) {
                        nodes.pushBack ( reinterpret_cast < void const * > ( pNode ) );
                    }
                }
            }

            return this->remove ( reinterpret_cast < LinkedList < Node const * > const & > ( nodes ) );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto LinkedList < __ElementType > :: pNewBefore (
                Node const * pNode
        ) noexcept -> ElementType * & {

            auto pNewNode       = Memory :: instance().create < Node > ();
            auto pMutableNode   = const_cast < Node * > ( pNode );

            pNewNode->_pPrevious                = pMutableNode->_pPrevious;
            pNewNode->_pNext                    = pMutableNode;
            pMutableNode->_pPrevious->_pNext    = pNewNode;
            pMutableNode->_pPrevious            = pNewNode;

            ++ this->_size;
            return pNewNode->_pData = nullptr;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto LinkedList < __ElementType > :: pNewAfter (
                Node const * pNode
        ) noexcept -> ElementType * & {

            auto pNewNode = Memory :: instance().create < Node > ();
            auto pMutableNode   = const_cast < Node * > ( pNode );

            pNewNode->_pPrevious                = pMutableNode;
            pNewNode->_pNext                    = pMutableNode->_pNext;
            pMutableNode->_pNext->_pPrevious    = pNewNode;
            pMutableNode->_pNext                = pNewNode;

            ++ this->_size;
            return pNewNode->_pData = nullptr;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto LinkedList < __ElementType > :: pNewFront () noexcept -> ElementType * & {

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


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto LinkedList < __ElementType > :: pNewBack () noexcept -> ElementType * & {

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


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto LinkedList < __ElementType > :: pNewBefore (
                Iterator const & iterator
        ) noexcept -> ElementType * & {

            return this->pNewBefore ( reinterpret_cast < LinkedListDelegateIterator const * > ( Collection < __ElementType > :: acquireDelegate ( iterator ) )->node() );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto LinkedList < __ElementType > :: pNewAfter (
                Iterator const & iterator
        ) noexcept -> ElementType * & {

            return this->pNewAfter ( reinterpret_cast < LinkedListDelegateIterator const * > ( Collection < __ElementType > :: acquireDelegate ( iterator ) )->node() );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto LinkedList < __ElementType > :: pNewBefore (
                ConstIterator const & iterator
        ) noexcept -> ElementType * & {

            return this->pNewBefore ( reinterpret_cast < LinkedListDelegateConstIterator const * > ( Collection < __ElementType > :: acquireDelegate ( iterator ) )->node() );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto LinkedList < __ElementType > :: pNewAfter (
                ConstIterator const & iterator
        ) noexcept -> ElementType * & {

            return this->pNewAfter ( reinterpret_cast < LinkedListDelegateConstIterator const * > ( Collection < __ElementType > :: acquireDelegate ( iterator ) )->node() );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto LinkedList < __ElementType > :: pNewBefore (
                ReverseIterator const & iterator
        ) noexcept -> ElementType * & {

            return this->pNewAfter ( reinterpret_cast < LinkedListDelegateIterator const * > ( Collection < __ElementType > :: acquireDelegate ( iterator ) )->node() );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto LinkedList < __ElementType > :: pNewAfter (
                ReverseIterator const & iterator
        ) noexcept -> ElementType * & {

            return this->pNewBefore ( reinterpret_cast < LinkedListDelegateIterator const * > ( Collection < __ElementType > :: acquireDelegate ( iterator ) )->node() );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto LinkedList < __ElementType > :: pNewBefore (
                ConstReverseIterator const & iterator
        ) noexcept -> ElementType * & {

            return this->pNewAfter ( reinterpret_cast < LinkedListDelegateConstIterator const * > ( Collection < __ElementType > :: acquireDelegate ( iterator ) )->node() );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto LinkedList < __ElementType > :: pNewAfter (
                ConstReverseIterator const & iterator
        ) noexcept -> ElementType * & {

            return this->pNewBefore ( reinterpret_cast < LinkedListDelegateConstIterator const * > ( Collection < __ElementType > :: acquireDelegate ( iterator ) )->node() );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto LinkedList < __ElementType > :: front () noexcept (false) -> ElementType & {

            if ( this->empty() ) {
                throw OutOfBoundsException("List is Empty");
            }

            return * this->_pFront->_pData;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto LinkedList < __ElementType > :: front () const noexcept (false) -> ElementType const & {

            if ( this->empty() ) {
                throw OutOfBoundsException("List is Empty");
            }

            return * this->_pFront->_pData;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto LinkedList < __ElementType > :: back () noexcept (false) -> ElementType & {

            if ( this->empty() ) {
                throw OutOfBoundsException("List is Empty");
            }

            return * this->_pBack->_pData;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto LinkedList < __ElementType > :: back () const noexcept (false) -> ElementType const & {

            if ( this->empty() ) {
                throw OutOfBoundsException("List is Empty");
            }

            return * this->_pBack->_pData;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto LinkedList < __ElementType > :: get (
                Index index
        ) noexcept (false) -> ElementType & {

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


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto LinkedList < __ElementType > :: get (
                Index index
        ) const noexcept (false) -> ElementType const & {

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


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto LinkedList < __ElementType > :: operator == (
                LinkedList const & list
        ) const noexcept -> bool {

            if ( this == & list ) {
                return true;
            }

            if ( this->size() != list.size() ) {
                return false;
            }

            auto pThisHead  = this->_pFront;
            auto pOtherHead = list._pFront;

            while ( pThisHead != nullptr ) {

                if ( ! meta :: equals ( * pThisHead->_pData, * pOtherHead->_pData ) ) {
                    return false;
                }

                pThisHead   = pThisHead->_pNext;
                pOtherHead  = pOtherHead->_pNext;
            }

            return true;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto LinkedList < __ElementType > :: operator != (
                LinkedList const & list
        ) const noexcept -> bool {

            return ! this->operator == ( list );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto LinkedList < __ElementType > :: clear () noexcept -> void {

            while ( this->_pFront != nullptr ) {
                auto current = this->_pFront;
                this->_pFront = this->_pFront->_pNext;

                Memory :: instance().destroy (current->_pData);
                Memory :: instance().destroy (current);
            }

            this->_pBack = nullptr;
            this->_size = 0;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto LinkedList < __ElementType > :: makeUnique () noexcept -> void {

            Node * pNewHead = nullptr;
            Node * pNewLast = nullptr;
            Size newSize    = 0ULL;

            Node * pHead    = this->_pFront;

            static auto listContains = [](
                    Node              * pList,
                    ElementType const & element
            ) noexcept -> bool {
                while ( pList != nullptr ) {
                    if ( meta :: equals ( element, * pList->_pData ) ) {
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


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto LinkedList < __ElementType > :: popFront () noexcept -> void {
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


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto LinkedList < __ElementType > :: popBack () noexcept -> void {
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


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, meta :: EnableIf < meta :: isCopyConstructible < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        auto LinkedList < __ElementType > :: operator = (
                LinkedList < __ElementType > const & list
        ) noexcept -> LinkedList < __ElementType > & {

            if ( & list == this ) {
                return * this;
            }

            this-> LinkedList :: clear();
            for ( auto iterator = list.begin(), end = list.end(); iterator != end; ++ iterator ) {
                this->LinkedList :: pushBack ( * iterator );
            }

            return * this;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto LinkedList < __ElementType >:: operator = (
                LinkedList < __ElementType > && list
        ) noexcept -> LinkedList < __ElementType > & {

            if ( & list == this ) {
                return * this;
            }

            this->LinkedList :: clear();

            this->_size     = cds :: exchange ( list._size, 0ULL );
            this->_pFront   = cds :: exchange ( list._pFront, nullptr );
            this->_pBack    = cds :: exchange ( list._pBack, nullptr );

            return * this;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template < typename __OtherElementType, meta :: EnableIf < meta :: isConvertible < __OtherElementType, __ElementType > () > > // NOLINT(bugprone-reserved-identifier)
        auto LinkedList < __ElementType > :: operator = (
                Collection < __OtherElementType > const & collection
        ) noexcept -> LinkedList < __ElementType > & {

            if ( & collection == this ) {
                return * this;
            }

            this-> LinkedList :: clear();
            for ( auto iterator = collection.begin(), end = collection.end(); iterator != end; ++ iterator ) {
                this->LinkedList :: pushBack ( * iterator );
            }

            return * this;
        }

    }
}

#endif // __CDS_EX_LINKED_LIST_IMPL_HPP__
