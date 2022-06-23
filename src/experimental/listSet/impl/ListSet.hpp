//
// Created by loghin on 6/13/22.
//

#ifndef __CDS_EX_LIST_SET_IMPL_HPP__
#define __CDS_EX_LIST_SET_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto ListSet < __ElementType > :: delegateConstIterator (
                DelegateIteratorRequestType requestType
        ) const noexcept -> cds :: UniquePointer < DelegateConstIterator > {

            switch ( requestType ) {
                case DelegateIteratorRequestType :: ForwardBegin:
                case DelegateIteratorRequestType :: BackwardBegin:
                    return Memory :: instance().create < ListSetDelegateIterator > ( this->_pFront, nullptr );
                case DelegateIteratorRequestType :: ForwardEnd:
                case DelegateIteratorRequestType :: BackwardEnd:
                    return Memory :: instance().create < ListSetDelegateIterator > ( nullptr, nullptr );
            }

            return nullptr;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr ListSet < __ElementType > :: ListSet () noexcept = default;


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        ListSet < __ElementType > :: ListSet (
                ListSet const & set
        ) noexcept :
                Set < __ElementType > ( set ),
                _size ( set._size ) {

            Node * pLocalBack = nullptr;
            for ( auto pOtherHead = set._pFront; pOtherHead != nullptr; pOtherHead = pOtherHead->_pNext ) {

                auto pNewNode = Memory :: instance().create < Node > ();
                pNewNode->_pNext = nullptr;
                pNewNode->_pData = Memory :: instance().create < __ElementType > ( * pOtherHead._pData );

                if ( this->_pFront == nullptr ) {
                    this->_pFront       = pNewNode;
                    pLocalBack          = pNewNode;
                } else {
                    pLocalBack->_pNext  = pNewNode;
                    pLocalBack          = pNewNode;
                }
            }
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr ListSet < __ElementType > :: ListSet (
                ListSet && set
        ) noexcept :
                Set < __ElementType > ( std :: move ( set ) ),
                _pFront ( cds :: exchange ( set._pFront, nullptr ) ),
                _size ( cds :: exchange ( set._size, 0ULL ) ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr ListSet < __ElementType > :: ListSet (
                Size size
        ) noexcept :
                _size ( size ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto ListSet < __ElementType > :: size () const noexcept -> Size {

            return this->_size;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        ListSet < __ElementType > :: ~ListSet () noexcept {

            this-> ListSet < __ElementType > :: clear ();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto ListSet < __ElementType > :: remove (
                ListSetDelegateIterator const * pIterator
        ) noexcept -> bool {

            if ( pIterator->previousNode() == nullptr ) {
                auto pCopy      = this->_pFront;
                this->_pFront   = this->_pFront->_pNext;

                Memory :: instance().destroy ( pCopy->_pData );
                Memory :: instance().destroy ( pCopy );
                return true;
            }

            auto pPrevious      = const_cast < Node * > ( pIterator->previousNode() );
            auto pToRemove      = pPrevious->_pNext;
            pPrevious->_pNext = pPrevious->_pNext->_pNext;

            Memory :: instance().destroy ( pToRemove->_pData );
            Memory :: instance().destroy ( pToRemove );

            return true;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto ListSet < __ElementType > :: remove (
                ConstIterator const & iterator
        ) noexcept -> bool {

            return this->remove (
                    reinterpret_cast < ListSetDelegateIterator const * > (
                            Collection < __ElementType > :: acquireDelegate ( iterator )
                    )
            );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto ListSet < __ElementType > :: remove (
                ConstReverseIterator const & iterator
        ) noexcept -> bool {

            return this->remove (
                    reinterpret_cast < ListSetDelegateIterator const * > (
                            Collection < __ElementType > :: acquireDelegate ( iterator )
                    )
            );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto ListSet < __ElementType > :: remove (
                ConstIterator   const * pIterators,
                Size                    iteratorCount
        ) noexcept -> Size {

            Size removedCount = 0ULL;
            for ( Size index = 0ULL; index < iteratorCount; ++ index ) {
                removedCount += static_cast < Size > ( this->remove ( pIterators [ iteratorCount ] ) );
            }

            return removedCount;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto ListSet < __ElementType > :: remove (
                ConstReverseIterator    const * pIterators,
                Size                            iteratorCount
        ) noexcept -> Size {

            Size removedCount = 0ULL;
            for ( Size index = 0ULL; index < iteratorCount; ++ index ) {
                removedCount += static_cast < Size > ( this->remove ( pIterators [ iteratorCount ] ) );
            }

            return removedCount;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto ListSet < __ElementType > :: clear () noexcept -> void {

            while ( this->_pFront != nullptr ) {
                auto pCopy      = this->_pFront;
                this->_pFront   = this->_pFront->_pNext;

                Memory :: instance().destroy ( pCopy->_pData );
                Memory :: instance().destroy ( pCopy );
            }

            this->_size = 0ULL;
        }

    }
}

#endif // __CDS_EX_LIST_SET_IMPL_HPP__
