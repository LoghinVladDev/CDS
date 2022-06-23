//
// Created by loghin on 6/13/22.
//

#ifndef __CDS_HASH_SET_IMPL_HPP__
#define __CDS_HASH_SET_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        auto HashSet < __ElementType, __Hasher > :: delegateConstIterator (
                DelegateIteratorRequestType requestType
        ) const noexcept -> cds :: UniquePointer < DelegateConstIterator > {

            switch ( requestType ) {
                case DelegateIteratorRequestType :: ForwardBegin:
                case DelegateIteratorRequestType :: BackwardBegin:
                    return Memory :: instance().create < HashSetDelegateIterator > ( this->__cbegin() );
                case DelegateIteratorRequestType :: ForwardEnd:
                case DelegateIteratorRequestType :: BackwardEnd:
                    return Memory :: instance().create < HashSetDelegateIterator > ( this->__cend() );
            }

            return nullptr;
        }


        template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        constexpr HashSet < __ElementType, __Hasher > :: HashSet () noexcept = default;


        template < typename __ElementType, typename __Hasher >  // NOLINT(bugprone-reserved-identifier)
        template < 
                typename __TElementType,                                // NOLINT(bugprone-reserved-identifier)
                cds :: meta :: EnableIf < 
                        cds :: meta :: isCopyConstructible < __TElementType > ()
                >
        > __CDS_OptimalInline HashSet < __ElementType, __Hasher > :: HashSet (
                HashSet const & set
        ) noexcept :
                Set < __ElementType > ( set ),
                __hidden :: __impl :: __HashTable <
                        __HashTableElementType,
                        __HashTableKeyType,
                        __HashTableFunctionExtractor,
                        __HashTableFunctionComparator,
                        __HashTableHasher,
                        __HashTableRehashPolicy,
                        __HashTableFunctionDestructor
                > ( set, __HashTableFunctionCopyConstructor () ) {
                    
        }


        template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        constexpr HashSet < __ElementType, __Hasher > :: HashSet (
                HashSet && set
        ) noexcept :
                Set < __ElementType > ( std :: move ( set ) ),
                __hidden :: __impl :: __HashTable <
                        __HashTableElementType,
                        __HashTableKeyType,
                        __HashTableFunctionExtractor,
                        __HashTableFunctionComparator,
                        __HashTableHasher,
                        __HashTableRehashPolicy,
                        __HashTableFunctionDestructor
                > ( std :: move ( set ) ) {

        }


        template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline HashSet < __ElementType, __Hasher > :: HashSet (
                __Hasher const & hasher
        ) noexcept :
                __hidden :: __impl :: __HashTable <
                        __HashTableElementType,
                        __HashTableKeyType,
                        __HashTableFunctionExtractor,
                        __HashTableFunctionComparator,
                        __HashTableHasher,
                        __HashTableRehashPolicy,
                        __HashTableFunctionDestructor
                > ( hasher ) {

        }


        template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        template < typename __IteratorType, cds :: meta :: EnableIf < cds :: meta :: isIterator < __IteratorType > () > > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline HashSet < __ElementType, __Hasher > :: HashSet (
                __IteratorType      const & begin,
                __IteratorType      const & end
        ) noexcept {

            for ( auto iterator = begin; iterator != end; ++ iterator ) {
                this->insert ( * iterator );
            }
        }


        template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        template < typename __IteratorType, cds :: meta :: EnableIf < cds :: meta :: isIterator < __IteratorType > () > > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline HashSet < __ElementType, __Hasher > :: HashSet (
                __IteratorType      const & begin,
                __IteratorType      const & end,
                __Hasher    const & hasher
        ) noexcept :
                __hidden :: __impl :: __HashTable <
                        __HashTableElementType,
                        __HashTableKeyType,
                        __HashTableFunctionExtractor,
                        __HashTableFunctionComparator,
                        __HashTableHasher,
                        __HashTableRehashPolicy,
                        __HashTableFunctionDestructor
                > ( hasher ) {

            for ( auto iterator = begin; iterator != end; ++ iterator ) {
                this->insert ( * iterator );
            }
        }


        template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline HashSet < __ElementType, __Hasher > :: HashSet (
                InitializerList     const & initializerList
        ) noexcept :
                HashSet (
                        initializerList.begin(),
                        initializerList.end()
                ) {

        }


        template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline HashSet < __ElementType, __Hasher > :: HashSet (
                InitializerList     const & initializerList,
                __Hasher    const & hasher
        ) noexcept :
                HashSet (
                        initializerList.begin(),
                        initializerList.end(),
                        hasher
                ) {

        }


        template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        template < typename __OtherElementType, cds :: meta :: EnableIf < cds :: meta :: isConvertible < __OtherElementType, __ElementType > () > > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline HashSet < __ElementType, __Hasher > :: HashSet (
                Collection < __OtherElementType >   const & collection
        ) noexcept :
                HashSet (
                        collection.begin(),
                        collection.end()
                ) {

        }


        template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        template < typename __OtherElementType, cds :: meta :: EnableIf < cds :: meta :: isConvertible < __OtherElementType, __ElementType > () > > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline HashSet < __ElementType, __Hasher > :: HashSet (
                Collection < __OtherElementType >   const & collection,
                __Hasher                    const & hasher
        ) noexcept :
                HashSet (
                        collection.begin(),
                        collection.end(),
                        hasher
                ) {

        }


        template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        HashSet < __ElementType, __Hasher > :: ~HashSet () noexcept {

            this->__clear();
        }


        template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto HashSet < __ElementType, __Hasher > :: size () const noexcept -> Size {

            return this->__size();
        }


        template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto HashSet < __ElementType, __Hasher > :: remove (
                ElementType const & element
        ) noexcept -> bool {

            return this->__remove ( element );
        }


        template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto HashSet < __ElementType, __Hasher > :: remove (
                ConstIterator const & iterator
        ) noexcept -> bool {

            return this->__remove (
                    reinterpret_cast < HashSetDelegateIterator const * > (
                            HashSet :: acquireDelegate ( iterator )
                    )->iterator()
            );
        }


        template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto HashSet < __ElementType, __Hasher > :: remove (
                ConstReverseIterator const & iterator
        ) noexcept -> bool {

            return this->__remove (
                    reinterpret_cast < HashSetDelegateIterator const * > (
                            HashSet :: acquireDelegate ( iterator )
                    )->iterator()
            );
        }


        template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        auto HashSet < __ElementType, __Hasher > :: remove (
                ConstIterator   const * pIterators,
                Size                    iteratorCount
        ) noexcept -> Size {

            Size removedCount = 0ULL;
            for ( Size index = 0ULL; index < iteratorCount; ++ index ) {
                removedCount += static_cast < Size > ( this->remove ( pIterators [ iteratorCount ] ) );
            }

            return removedCount;
        }


        template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        auto HashSet < __ElementType, __Hasher > :: remove (
                ConstReverseIterator    const * pIterators,
                Size                            iteratorCount
        ) noexcept -> Size {

            Size removedCount = 0ULL;
            for ( Size index = 0ULL; index < iteratorCount; ++ index ) {
                removedCount += static_cast < Size > ( this->remove ( pIterators [ iteratorCount ] ) );
            }

            return removedCount;
        }


        template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        auto HashSet < __ElementType, __Hasher > :: pNewInsert (
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


        template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        auto HashSet < __ElementType, __Hasher > :: contains (
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


        template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        auto HashSet < __ElementType, __Hasher > :: clear () noexcept -> void {

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


        template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        auto HashSet < __ElementType, __Hasher > :: operator == (
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


        template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto HashSet < __ElementType, __Hasher > :: operator != (
                HashSet const & set
        ) const noexcept -> bool {

            return ! this->operator == ( set );
        }


        template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        template < typename __VElementType, cds :: meta :: EnableIf < cds :: meta :: isCopyConstructible < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
        auto HashSet < __ElementType, __Hasher > :: operator = (
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


        template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        auto HashSet < __ElementType, __Hasher > :: operator = (
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


        template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        template < typename __OtherElementType, cds :: meta :: EnableIf < cds :: meta :: isConvertible < __OtherElementType, __ElementType > () > > // NOLINT(bugprone-reserved-identifier)
        auto HashSet < __ElementType, __Hasher > :: operator = (
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
