//
// Created by loghin on 6/18/22.
//

#ifndef __CDS_EX_HASH_MAP_IMPL_HPP__
#define __CDS_EX_HASH_MAP_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __KeyType, typename __ValueType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto HashMap < __KeyType, __ValueType, __HashCalculator > :: keySetProxy () const noexcept -> AbstractKeySetProxy const & {

            return this->_keySetProxy;
        }


        template < typename __KeyType, typename __ValueType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto HashMap < __KeyType, __ValueType, __HashCalculator > :: keySetProxy () noexcept -> AbstractKeySetProxy & {

            return this->_keySetProxy;
        }


        template < typename __KeyType, typename __ValueType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto HashMap < __KeyType, __ValueType, __HashCalculator > :: valueCollectionProxy () const noexcept -> AbstractValueMutableCollectionProxy const & {

            return this->_valueMutableCollectionProxy;
        }


        template < typename __KeyType, typename __ValueType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto HashMap < __KeyType, __ValueType, __HashCalculator > :: valueCollectionProxy () noexcept -> AbstractValueMutableCollectionProxy & {

            return this->_valueMutableCollectionProxy;
        }


        template < typename __KeyType, typename __ValueType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto HashMap < __KeyType, __ValueType, __HashCalculator > :: entrySetProxy () const noexcept -> AbstractEntryMutableCollectionProxy const & {

            return this->_entryMutableCollectionProxy;
        }


        template < typename __KeyType, typename __ValueType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto HashMap < __KeyType, __ValueType, __HashCalculator > :: entrySetProxy () noexcept -> AbstractEntryMutableCollectionProxy & {

            return this->_entryMutableCollectionProxy;
        }


        template < typename __KeyType, typename __ValueType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __HashCalculator > :: delegateIterator (
                DelegateIteratorRequestType requestType
        ) noexcept -> cds :: UniquePointer < DelegateIterator > {

            return nullptr;
        }


        template < typename __KeyType, typename __ValueType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __HashCalculator > :: delegateConstIterator (
                DelegateIteratorRequestType requestType
        ) const noexcept -> cds :: UniquePointer < DelegateConstIterator > {

            return nullptr;
        }


        template < typename __KeyType, typename __ValueType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        constexpr HashMap < __KeyType, __ValueType, __HashCalculator > :: HashMap () noexcept :
                _keySetProxy ( this ),
                _valueMutableCollectionProxy ( this ),
                _entryMutableCollectionProxy ( this ) {

        }


        template < typename __KeyType, typename __ValueType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        HashMap < __KeyType, __ValueType, __HashCalculator > :: HashMap (
                HashMap const & map
        ) noexcept :
                Map < __KeyType, __ValueType > ( map ),
                _keySetProxy ( this ),
                _valueMutableCollectionProxy ( this ),
                _entryMutableCollectionProxy ( this ) {

            this->_pBucketList =
                    map.empty() ?
                    nullptr     :
                    cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < BucketType > ( this->_hashCalculator.getBoundary() );

            if ( ! map.empty() ) {
                for ( Size bucketIndex = 0ULL; bucketIndex < this->_hashCalculator.getBoundary(); ++ bucketIndex ) {

                    BucketType & currentBucket  = this->_pBucketList [ bucketIndex ];
                    DataNode   * pOtherBucket   = map._pBucketList [ bucketIndex ]._pFront;

                    while ( pOtherBucket != nullptr ) {

                        DataNode * pNewNode     = Memory :: instance().create < DataNode > ();
                        pNewNode->_pNext        = nullptr;
                        pNewNode->_pPrevious    = currentBucket._pBack;

                        Map < __KeyType, __ValueType > :: entryCopyTo (
                                & pNewNode->_entry,
                                & pOtherBucket->_entry
                        );

                        if ( currentBucket._pBack == nullptr ) {
                            currentBucket._pFront           = pNewNode;
                        } else {
                            currentBucket._pBack->_pNext    = pNewNode;
                        }

                        currentBucket._pBack    = pNewNode;
                        pOtherBucket            = pOtherBucket->_pNext;
                    }
                }
            }
        }


        template < typename __KeyType, typename __ValueType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        constexpr HashMap < __KeyType, __ValueType, __HashCalculator > :: HashMap (
                HashMap && map
        ) noexcept :
                Map < __KeyType, __ValueType > ( map ),
                _keySetProxy ( this ),
                _valueMutableCollectionProxy ( this ),
                _entryMutableCollectionProxy ( this ),
                _pBucketList ( cds :: exchange ( map._pBucketList, nullptr ) ) {

        }


        template < typename __KeyType, typename __ValueType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline HashMap < __KeyType, __ValueType, __HashCalculator > :: HashMap (
                __HashCalculator const & hashCalculator
        ) noexcept :
                _keySetProxy ( this ),
                _valueMutableCollectionProxy ( this ),
                _entryMutableCollectionProxy ( this ),
                _hashCalculator ( hashCalculator ) {

        }


        template < typename __KeyType, typename __ValueType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline HashMap < __KeyType, __ValueType, __HashCalculator > :: HashMap (
                InitializerList     const & initializerList
        ) noexcept :
                _keySetProxy ( this ),
                _valueMutableCollectionProxy ( this ),
                _entryMutableCollectionProxy ( this ) {

            for ( auto & entry : initializerList ) {
                this->add ( entry );
            }
        }


        template < typename __KeyType, typename __ValueType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline HashMap < __KeyType, __ValueType, __HashCalculator > :: HashMap (
                InitializerList     const & initializerList,
                __HashCalculator    const & hashCalculator
        ) noexcept :
                _keySetProxy ( this ),
                _valueMutableCollectionProxy ( this ),
                _entryMutableCollectionProxy ( this ),
                _hashCalculator ( hashCalculator ) {

            for ( auto & entry : initializerList ) {
                this->add ( entry );
            }
        }


        template < typename __KeyType, typename __ValueType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        HashMap < __KeyType, __ValueType, __HashCalculator > :: ~HashMap () noexcept {

            for ( Size bucketIndex = 0ULL; bucketIndex < this->_hashCalculator.getBoundary(); ++ bucketIndex ) {
                while ( this->_pBucketList [ bucketIndex ]._pFront != nullptr ) {
                    auto pCopy                                  = this->_pBucketList [ bucketIndex ]._pFront;
                    this->_pBucketList [ bucketIndex ]._pFront  = this->_pBucketList [ bucketIndex ]._pFront->_pNext;

                    Map < __KeyType, __ValueType > :: freeEntryData ( pCopy->_entry );
                    Memory :: instance().destroy ( pCopy );
                }
            }

            cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( this->_pBucketList );
        }


        template < typename __KeyType, typename __ValueType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        auto HashMap < __KeyType, __ValueType, __HashCalculator > :: pEntryAt (
                KeyType const & key
        ) noexcept -> EntryType * {

            if ( this->_pBucketList == nullptr ) {

                this->_pBucketList = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < BucketType > (
                        this->_hashCalculator.getBoundary()
                );

                (void) std :: memset (
                        this->_pBucketList,
                        0,
                        sizeof ( BucketType ) * this->_hashCalculator.getBoundary() // NOLINT(bugprone-sizeof-expression)
                );
            }

            auto hashValue  = this->_hashCalculator ( key );
            auto pListHead  = this->_pBucketList [ hashValue ]._pFront;

            while ( pListHead != nullptr ) {
                if ( cds :: meta :: equals ( pListHead->_entry.key(), key ) ) {
                    return & pListHead->_entry;
                }

                pListHead = pListHead->_pNext;
            }

            auto pNewNode                       = Memory :: instance().create < DataNode > ();
            pNewNode->_pNext                    = this->_pBucketList [ hashValue ]._pFront;
            pNewNode->_pPrevious                = nullptr;

            if ( this->_pBucketList [ hashValue ]._pFront != nullptr ) {
                this->_pBucketList [ hashValue ]._pFront->_pPrevious    = pNewNode;
            } else {
                this->_pBucketList [ hashValue ]._pBack                 = pNewNode;
            }

            this->_pBucketList [ hashValue ]._pFront    = pNewNode;
            ++ this->_size;

            return & this->_pBucketList [ hashValue ]._pFront->_entry;
        }


        template < typename __KeyType, typename __ValueType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        auto HashMap < __KeyType, __ValueType, __HashCalculator > :: pEntryAt (
                KeyType const & key
        ) const noexcept -> EntryType const * {

            if ( this->_pBucketList == nullptr ) {
                return nullptr;
            }

            auto hashValue  = this->_hashCalculator ( key );
            auto pListHead  = this->_pBucketList [ hashValue ]._pFront;

            while ( pListHead != nullptr ) {
                if ( cds :: meta :: equals ( pListHead->_entry.key(), key ) ) {
                    return & pListHead->_entry;
                }

                pListHead = pListHead->_pNext;
            }

            return nullptr;
        }


        template < typename __KeyType, typename __ValueType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        auto HashMap < __KeyType, __ValueType, __HashCalculator > :: completeInsertion (
                EntryType * pEntry
        ) noexcept -> void {

            auto pNewEntry = this->pEntryAt ( pEntry->key() );

            if ( Map < __KeyType, __ValueType > :: entryEmpty ( pNewEntry ) ) {
                ++ this->_size;
            }

            Map < __KeyType, __ValueType > :: entryMoveOrCopyKeyTo ( pNewEntry, pEntry );
            Map < __KeyType, __ValueType > :: entryMoveOrCopyValueTo ( pNewEntry, pEntry );
        }


        template < typename __KeyType, typename __ValueType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __HashCalculator > :: contains (
                ElementType const & entry
        ) const noexcept -> bool {

            return this->pEntryAt ( entry.key() ) != nullptr;
        }


        template < typename __KeyType, typename __ValueType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __HashCalculator > :: containsKey (
                KeyType const & key
        ) const noexcept -> bool {

            return this->pEntryAt ( key ) != nullptr;
        }


        template < typename __KeyType, typename __ValueType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __HashCalculator > :: containsValue (
                ValueType const & value
        ) const noexcept -> bool {

            for ( Size bucketIndex = 0ULL; bucketIndex < this->_hashCalculator.getBoundary(); ++ bucketIndex ) {

                DataNode * pHead = this->_pBucketList [ bucketIndex ]._pFront;
                while ( pHead != nullptr ) {

                    if ( cds :: meta :: equals ( pHead->_entry.value(), value ) ) {
                        return true;
                    }

                    pHead = pHead->_pNext;
                }
            }

            return false;
        }


        template < typename __KeyType, typename __ValueType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __HashCalculator > :: remove (
                Iterator const & iterator
        ) noexcept -> bool {

            /// TODO : come back to this after iterators.
            return false;
        }


        template < typename __KeyType, typename __ValueType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __HashCalculator > :: remove (
                ConstIterator const & iterator
        ) noexcept -> bool {

            /// TODO : come back to this after iterators.
            return false;
        }


        template < typename __KeyType, typename __ValueType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __HashCalculator > :: remove (
                ReverseIterator const & iterator
        ) noexcept -> bool {

            /// TODO : come back to this after iterators.
            return false;
        }


        template < typename __KeyType, typename __ValueType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __HashCalculator > :: remove (
                ConstReverseIterator const & iterator
        ) noexcept -> bool {

            /// TODO : come back to this after iterators.
            return false;
        }


        template < typename __KeyType, typename __ValueType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __HashCalculator > :: remove (
                Iterator    const * pIterators,
                Size                iteratorCount
        ) noexcept -> Size {

            /// TODO : come back to this after iterators.
            return 0ULL;
        }


        template < typename __KeyType, typename __ValueType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __HashCalculator > :: remove (
                ConstIterator   const * pIterators,
                Size                    iteratorCount
        ) noexcept -> Size {

            /// TODO : come back to this after iterators.
            return 0ULL;
        }


        template < typename __KeyType, typename __ValueType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __HashCalculator > :: remove (
                ReverseIterator const * pIterators,
                Size                    iteratorCount
        ) noexcept -> Size {

            /// TODO : come back to this after iterators.
            return 0ULL;
        }


        template < typename __KeyType, typename __ValueType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __HashCalculator > :: remove (
                ConstReverseIterator    const * pIterators,
                Size                            iteratorCount
        ) noexcept -> Size {

            /// TODO : come back to this after iterators.
            return 0ULL;
        }


        template < typename __KeyType, typename __ValueType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __HashCalculator > :: clear () noexcept -> void {

            for ( Size bucketIndex = 0ULL; bucketIndex < this->_hashCalculator.getBoundary(); ++ bucketIndex ) {
                while ( this->_pBucketList [ bucketIndex ]._pFront != nullptr ) {
                    auto pCopy                                  = this->_pBucketList [ bucketIndex ]._pFront;
                    this->_pBucketList [ bucketIndex ]._pFront  = this->_pBucketList [ bucketIndex ]._pFront->_pNext;

                    Map < __KeyType, __ValueType > :: freeEntryData ( pCopy->_entry );
                    Memory :: instance().destroy ( pCopy );
                }
            }

            this->_size = 0ULL;
        }

    }
}

#endif // __CDS_EX_HASH_MAP_IMPL_HPP__
