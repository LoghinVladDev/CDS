//
// Created by loghin on 6/13/22.
//

#ifndef __CDS_HASH_SET_IMPL_HPP__
#define __CDS_HASH_SET_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        auto HashSet < __ElementType, __HashCalculator > :: delegateConstIterator (
                DelegateIteratorRequestType requestType
        ) const noexcept -> cds :: UniquePointer < DelegateConstIterator > {

            switch ( requestType ) {
                case DelegateIteratorRequestType :: ForwardBegin:
                case DelegateIteratorRequestType :: BackwardBegin:
                    return Memory :: instance().create < HashSetDelegateIterator > ( this );
                case DelegateIteratorRequestType :: ForwardEnd:
                case DelegateIteratorRequestType :: BackwardEnd:
                    return Memory :: instance().create < HashSetDelegateIterator > ( nullptr );
            }

            return nullptr;
        }


        template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        constexpr HashSet < __ElementType, __HashCalculator > :: HashSet () noexcept = default;


        template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        HashSet < __ElementType, __HashCalculator > :: HashSet (
                HashSet const & set
        ) noexcept :
                HashSet (
                        set.begin(),
                        set.end()
                ) {
        }


        template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        constexpr HashSet < __ElementType, __HashCalculator > :: HashSet (
                HashSet && set
        ) noexcept :
                Set < __ElementType > ( std :: move ( set ) ),
                _listArray ( cds :: exchange ( set._listArray, nullptr ) ) {

        }


        template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        HashSet < __ElementType, __HashCalculator > :: HashSet (
                __HashCalculator const & calculator
        ) noexcept :
                _hashCalculator ( calculator ) {

        }


        template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        template < typename __IteratorType, cds :: meta :: EnableIf < cds :: meta :: isIterator < __IteratorType > () > > // NOLINT(bugprone-reserved-identifier)
        HashSet < __ElementType, __HashCalculator > :: HashSet (
                __IteratorType      const & begin,
                __IteratorType      const & end
        ) noexcept {

            for ( auto iterator = begin; iterator != end; ++ iterator ) {
                this->insert ( * iterator );
            }
        }


        template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        template < typename __IteratorType, cds :: meta :: EnableIf < cds :: meta :: isIterator < __IteratorType > () > > // NOLINT(bugprone-reserved-identifier)
        HashSet < __ElementType, __HashCalculator > :: HashSet (
                __IteratorType      const & begin,
                __IteratorType      const & end,
                __HashCalculator    const & calculator
        ) noexcept :
                _hashCalculator ( calculator ) {

            for ( auto iterator = begin; iterator != end; ++ iterator ) {
                this->insert ( * iterator );
            }
        }


        template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        HashSet < __ElementType, __HashCalculator > :: HashSet (
                InitializerList     const & initializerList
        ) noexcept :
                HashSet (
                        initializerList.begin(),
                        initializerList.end()
                ) {

        }


        template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        HashSet < __ElementType, __HashCalculator > :: HashSet (
                InitializerList     const & initializerList,
                __HashCalculator    const & calculator
        ) noexcept :
                HashSet (
                        initializerList.begin(),
                        initializerList.end(),
                        calculator
                ) {

        }


        template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        template < typename __OtherElementType, cds :: meta :: EnableIf < cds :: meta :: isConvertible < __OtherElementType, __ElementType > () > > // NOLINT(bugprone-reserved-identifier)
        HashSet < __ElementType, __HashCalculator > :: HashSet (
                Collection < __OtherElementType >   const & collection
        ) noexcept :
                HashSet (
                        collection.begin(),
                        collection.end()
                ) {

        }


        template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        template < typename __OtherElementType, cds :: meta :: EnableIf < cds :: meta :: isConvertible < __OtherElementType, __ElementType > () > > // NOLINT(bugprone-reserved-identifier)
        HashSet < __ElementType, __HashCalculator > :: HashSet (
                Collection < __OtherElementType >   const & collection,
                __HashCalculator                    const & calculator
        ) noexcept :
                HashSet (
                        collection.begin(),
                        collection.end(),
                        calculator
                ) {

        }


        template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        HashSet < __ElementType, __HashCalculator > :: ~HashSet () noexcept {

            this->HashSet :: clear();
            Memory :: instance().destroyArray ( this->_listArray );
        }


        template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto HashSet < __ElementType, __HashCalculator > :: remove (
                ConstIterator const & iterator
        ) noexcept -> bool {

            return this->remove (
                    reinterpret_cast < HashSetDelegateIterator const * > (
                            Collection < __ElementType > :: acquireDelegate ( iterator )
                    )
            );
        }


        template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto HashSet < __ElementType, __HashCalculator > :: remove (
                ConstReverseIterator const & iterator
        ) noexcept -> bool {

            return this->remove (
                    reinterpret_cast < HashSetDelegateIterator const * > (
                            Collection < __ElementType > :: acquireDelegate ( iterator )
                    )
            );
        }


        template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        auto HashSet < __ElementType, __HashCalculator > :: remove (
                HashSetDelegateIterator const * pIterator
        ) noexcept -> bool {

            auto pNode = this->_listArray [ pIterator->currentListIndex() ];

            if ( pNode == pIterator->currentNode() ) {
                this->_listArray [ pIterator->currentListIndex() ] = this->_listArray [ pIterator->currentListIndex() ]->_pNext;
                Memory :: instance().destroy ( pNode );

                return true;
            }

            while ( pNode->_pNext != nullptr ) {

                if ( pNode->_pNext == pIterator->currentNode() ) {
                    auto toRemove = pNode->_pNext;
                    pNode->_pNext = pNode->_pNext->_pNext;
                    Memory :: instance().destroy ( toRemove );

                    return true;
                }

                pNode = pNode->_pNext;
            }

            return false;
        }


        template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        auto HashSet < __ElementType, __HashCalculator > :: remove (
                ConstIterator   const * pIterators,
                Size                    iteratorCount
        ) noexcept -> Size {

            Size removedCount = 0ULL;
            for ( Size index = 0ULL; index < iteratorCount; ++ index ) {
                removedCount += static_cast < Size > ( this->remove ( pIterators [ iteratorCount ] ) );
            }

            return removedCount;
        }


        template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        auto HashSet < __ElementType, __HashCalculator > :: remove (
                ConstReverseIterator    const * pIterators,
                Size                            iteratorCount
        ) noexcept -> Size {

            Size removedCount = 0ULL;
            for ( Size index = 0ULL; index < iteratorCount; ++ index ) {
                removedCount += static_cast < Size > ( this->remove ( pIterators [ iteratorCount ] ) );
            }

            return removedCount;
        }


        template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        auto HashSet < __ElementType, __HashCalculator > :: pNewInsert (
                ElementType const & referenceElement
        ) noexcept -> ElementType * & {

            if ( this->_listArray == nullptr ) {
                this->_listArray = Memory :: instance().createArray < Node * > ( this->_hashCalculator.getBoundary() );
                (void) std :: memset ( this->_listArray, 0, sizeof ( Node * ) * this->_hashCalculator.getBoundary() );
            }

            auto   hashValue    = this->_hashCalculator ( referenceElement );
            auto & listToAddTo  = this->_listArray [ hashValue ];

            for ( Node * pHead = listToAddTo; pHead != nullptr; pHead = pHead->_pNext ) {
                if ( cds :: meta :: equals ( * pHead->_pData, referenceElement ) ) {
                    return pHead->_pData;
                }
            }

            auto pNode = Memory :: instance().create < Node > ();
            pNode->_pData = nullptr;
            pNode->_pNext = listToAddTo;
            listToAddTo   = pNode;

            ++ this->_size;
            return listToAddTo->_pData;
        }


        template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        auto HashSet < __ElementType, __HashCalculator > :: contains (
                ElementType const & element
        ) const noexcept -> bool {

            if ( this->empty() ) {
                return false;
            }

            auto hashValue    = this->_hashCalculator ( element );
            for ( auto head = this->_listArray [ hashValue ]; head != nullptr; head = head->_pNext ) {
                if ( cds :: meta :: equals ( * head->_pData, element ) ) {
                    return true;
                }
            }

            return false;
        }


        template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        auto HashSet < __ElementType, __HashCalculator > :: clear () noexcept -> void {

            if ( this->_listArray == nullptr ) {
                return;
            }

            for ( Size index = 0ULL; index < this->_hashCalculator.getBoundary(); ++ index ) {
                while ( this->_listArray [ index ] != nullptr ) {
                    auto * pHead = this->_listArray [ index ];
                    this->_listArray [ index ] = this->_listArray [ index ]->_pNext;
                    Memory :: instance().destroy ( pHead->_pData );
                    Memory :: instance().destroy (pHead );
                }
            }
        }


        template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        auto HashSet < __ElementType, __HashCalculator > :: operator == (
                HashSet const & set
        ) const noexcept -> bool {

            if ( this == & set ) {
                return true;
            }

            if ( this->size() != set.size() ) {
                return false;
            }

            for ( Size index = 0ULL; index < this->_hashCalculator.getBoundary(); ++ index ) {
                auto pThisHead  = this->_listArray [ index ];
                auto pOtherHead = set._listArray [ index ];

                while ( pThisHead != nullptr && pOtherHead != nullptr ) {
                    if ( ! cds :: meta :: equals ( * pThisHead->_pData, * pOtherHead->_pData ) ) {
                        return false;
                    }
                }

                if ( pThisHead != nullptr || pOtherHead != nullptr ) {
                    return false;
                }

                pThisHead   = pThisHead->_pNext;
                pOtherHead  = pOtherHead->_pNext;
            }

            return true;
        }


        template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto HashSet < __ElementType, __HashCalculator > :: operator != (
                HashSet const & set
        ) const noexcept -> bool {

            return ! this->operator == ( set );
        }


        template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, cds :: meta :: EnableIf < cds :: meta :: isCopyConstructible < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        auto HashSet < __ElementType, __HashCalculator > :: operator = (
                HashSet const & set
        ) noexcept -> HashSet & {

            if ( this == & set ) {
                return * this;
            }

            this->clear();
            for ( auto iterator = set.begin(), end = set.end(); iterator != end; ++ iterator ) {
                this->HashSet :: insert ( * iterator );
            }

            return * this;
        }


        template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        auto HashSet < __ElementType, __HashCalculator > :: operator = (
                HashSet && set
        ) noexcept -> HashSet & {

            if ( this == & set ) {
                return * this;
            }

            this->clear();

            this->_listArray    = cds :: exchange ( set._listArray, nullptr );
            this->_size         = cds :: exchange ( set._size, 0ULL );

            return * this;
        }


        template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        template < typename __OtherElementType, cds :: meta :: EnableIf < cds :: meta :: isConvertible < __OtherElementType, __ElementType > () > > // NOLINT(bugprone-reserved-identifier)
        auto HashSet < __ElementType, __HashCalculator > :: operator = (
                Collection < __OtherElementType > const & collection
        ) noexcept -> HashSet & {

            if ( this == & collection ) {
                return * this;
            }

            this->clear();
            for ( auto iterator = collection.begin(), end = collection.end(); iterator != end; ++ iterator ) {
                this->HashSet :: insert ( * iterator );
            }

            return * this;
        }

    }
}

#endif // __CDS_HASH_SET_IMPL_HPP__
