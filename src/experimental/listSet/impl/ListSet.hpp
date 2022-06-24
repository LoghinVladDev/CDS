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
        __CDS_OptimalInline auto ListSet < __ElementType > :: __allocateNode () noexcept -> Node * {

            return cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveObject < Node > ();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto ListSet < __ElementType > :: __freeNode (
                Node * pNode
        ) noexcept -> void {

            pNode->_data.destruct();
            return cds :: __hidden :: __impl :: __allocation :: __freePrimitiveObject ( pNode );
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

                auto pNewNode = ListSet :: __allocateNode();
                pNewNode->_pNext = nullptr;
                pNewNode->_data.construct ( pOtherHead->_data.data() );

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

            this-> ListSet :: clear ();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto ListSet < __ElementType > :: remove (
                ListSetDelegateIterator const * pIterator
        ) noexcept -> bool {

            if ( pIterator->previousNode() == nullptr ) {
                auto pCopy      = this->_pFront;
                this->_pFront   = this->_pFront->_pNext;

                ListSet :: __freeNode ( pCopy );
                return true;
            }

            auto pPrevious      = const_cast < Node * > ( pIterator->previousNode() );
            auto pToRemove      = pPrevious->_pNext;
            pPrevious->_pNext = pPrevious->_pNext->_pNext;

            ListSet :: __freeNode ( pToRemove );
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

                ListSet :: __freeNode ( pCopy );
            }

            this->_size = 0ULL;
        }

    }
}

#endif // __CDS_EX_LIST_SET_IMPL_HPP__
