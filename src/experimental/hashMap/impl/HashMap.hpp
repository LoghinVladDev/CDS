//
// Created by loghin on 6/18/22.
//

#ifndef __CDS_EX_HASH_MAP_IMPL_HPP__
#define __CDS_EX_HASH_MAP_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto HashMap < __KeyType, __ValueType, __Hasher > :: updateSize (
                Size size
        ) noexcept -> void {

            this->_size                                 = size;
            this->_keySetProxy._size                    = size;
            this->_valueMutableCollectionProxy._size    = size;
            this->_entryMutableCollectionProxy._size    = size;
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto HashMap < __KeyType, __ValueType, __Hasher > :: keySetProxy () const noexcept -> AbstractKeySetProxy const & {

            return this->_keySetProxy;
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto HashMap < __KeyType, __ValueType, __Hasher > :: keySetProxy () noexcept -> AbstractKeySetProxy & {

            return this->_keySetProxy;
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto HashMap < __KeyType, __ValueType, __Hasher > :: valueCollectionProxy () const noexcept -> AbstractValueMutableCollectionProxy const & {

            return this->_valueMutableCollectionProxy;
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto HashMap < __KeyType, __ValueType, __Hasher > :: valueCollectionProxy () noexcept -> AbstractValueMutableCollectionProxy & {

            return this->_valueMutableCollectionProxy;
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto HashMap < __KeyType, __ValueType, __Hasher > :: entrySetProxy () const noexcept -> AbstractEntryMutableCollectionProxy const & {

            return this->_entryMutableCollectionProxy;
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto HashMap < __KeyType, __ValueType, __Hasher > :: entrySetProxy () noexcept -> AbstractEntryMutableCollectionProxy & {

            return this->_entryMutableCollectionProxy;
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: delegateIterator (
                DelegateIteratorRequestType requestType
        ) noexcept -> cds :: UniquePointer < DelegateIterator > {

            /// TODO : implement iterators
            return nullptr;
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: delegateConstIterator (
                DelegateIteratorRequestType requestType
        ) const noexcept -> cds :: UniquePointer < DelegateConstIterator > {

            /// TODO : implement iterators
            return nullptr;
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        constexpr HashMap < __KeyType, __ValueType, __Hasher > :: HashMap () noexcept :
                _keySetProxy ( this ),
                _valueMutableCollectionProxy ( this ),
                _entryMutableCollectionProxy ( this ) {

        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        HashMap < __KeyType, __ValueType, __Hasher > :: HashMap (
                HashMap const & map
        ) noexcept :
                Map < __KeyType, __ValueType > ( map ),
                __hidden :: __impl :: __HashTableUtils <
                        __Hasher,
                        cds :: __hidden :: __impl :: __PrimeRehashPolicy
                > ( map ),
                _keySetProxy ( this ),
                _valueMutableCollectionProxy ( this ),
                _entryMutableCollectionProxy ( this ),
                _buckets ( { nullptr, map._buckets._bucketCount } ) {

            this->_buckets._pBuckets =
                    map.empty() ?
                    nullptr     :
                    cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < BucketType > ( this->_buckets._bucketCount );

            std :: memset (
                    this->_buckets._pBuckets,
                    0U,
                    sizeof ( BucketType ) * this->_buckets._bucketCount // NOLINT(bugprone-sizeof-expression)
            );

            if ( ! map.empty() ) {
                for ( Size bucketIndex = 0ULL; bucketIndex < this->_buckets._bucketCount; ++ bucketIndex ) {

                    BucketType & currentBucket  = this->_buckets._pBuckets [ bucketIndex ];
                    DataNode   * pOtherBucket   = map._buckets._pBuckets [ bucketIndex ]._pFront;
                    DataNode   * pBack          = nullptr;

                    while ( pOtherBucket != nullptr ) {

                        DataNode * pNewNode     = Memory :: instance().create < DataNode > ();
                        pNewNode->_pNext        = nullptr;

                        pNewNode->_key.construct ( pOtherBucket->_key.data() );
                        pNewNode->_value.construct ( pOtherBucket->_value.data() );

                        if ( pBack == nullptr ) {
                            currentBucket           = pNewNode;
                        } else {
                            pBack->_pNext           = pNewNode;
                        }

                        pBack           = pNewNode;
                        pOtherBucket    = pOtherBucket->_pNext;
                    }
                }
            }
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        constexpr HashMap < __KeyType, __ValueType, __Hasher > :: HashMap (
                HashMap && map
        ) noexcept :
                Map < __KeyType, __ValueType > ( std :: move ( map ) ),
                __hidden :: __impl :: __HashTableUtils <
                        __Hasher,
                        cds :: __hidden :: __impl :: __PrimeRehashPolicy
                > ( map ),
                _keySetProxy ( this ),
                _valueMutableCollectionProxy ( this ),
                _entryMutableCollectionProxy ( this ),
                _buckets ( { cds :: exchange ( map._buckets._pBuckets, nullptr ), cds :: exchange ( map._buckets._bucketCount, 0ULL ) } ) {

        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline HashMap < __KeyType, __ValueType, __Hasher > :: HashMap (
                __Hasher const & hasher
        ) noexcept :
                __hidden :: __impl :: __HashTableUtils <
                        __Hasher,
                        cds :: __hidden :: __impl :: __PrimeRehashPolicy
                > ( hasher ),
                _keySetProxy ( this ),
                _valueMutableCollectionProxy ( this ),
                _entryMutableCollectionProxy ( this ) {

        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline HashMap < __KeyType, __ValueType, __Hasher > :: HashMap (
                InitializerList     const & initializerList
        ) noexcept :
                _keySetProxy ( this ),
                _valueMutableCollectionProxy ( this ),
                _entryMutableCollectionProxy ( this ) {

            for ( auto & entry : initializerList ) {
                this->add ( entry );
            }
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline HashMap < __KeyType, __ValueType, __Hasher > :: HashMap (
                InitializerList const & initializerList,
                __Hasher        const & hasher
        ) noexcept :
                __hidden :: __impl :: __HashTableUtils <
                        __Hasher,
                        cds :: __hidden :: __impl :: __PrimeRehashPolicy
                > ( hasher ),
                _keySetProxy ( this ),
                _valueMutableCollectionProxy ( this ),
                _entryMutableCollectionProxy ( this ) {

            for ( auto & entry : initializerList ) {
                this->add ( entry );
            }
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        HashMap < __KeyType, __ValueType, __Hasher > :: ~HashMap () noexcept {

            if ( this->_buckets._pBuckets != nullptr ) {
                for ( Size bucketIndex = 0ULL; bucketIndex < this->_buckets._bucketCount; ++ bucketIndex ) {
                    while ( this->_buckets._pBuckets [ bucketIndex ] != nullptr ) {
                        auto pCopy                                  = this->_buckets._pBuckets [ bucketIndex ];
                        this->_buckets._pBuckets [ bucketIndex ]    = this->_buckets._pBuckets [ bucketIndex ]->_pNext;

                        pCopy->_key.destruct();
                        pCopy->_value.destruct();
                        Memory :: instance().destroy ( pCopy );
                    }
                }
            }

            cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( this->_buckets._pBuckets );
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        auto HashMap < __KeyType, __ValueType, __Hasher > :: entryAt (
                KeyType const & key,
                bool          & isNew
        ) noexcept -> EntryType {

            isNew = false;
            if ( this->_buckets._pBuckets == nullptr ) {

                this->_buckets._bucketCount = this->_rehashPolicy.currentFactor();
                this->_buckets._pBuckets = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < BucketType > (
                        this->_buckets._bucketCount
                );

                (void) std :: memset (
                        this->_buckets._pBuckets,
                        0,
                        sizeof ( BucketType ) * this->_buckets._bucketCount // NOLINT(bugprone-sizeof-expression)
                );
            }

            auto hashValue  = this->_hasher ( key );
            auto & list     = this->_buckets._pBuckets [ hashValue % this->_buckets._bucketCount ];

            auto pListHead  = list;


            Size        bucketSize  = 0ULL;

            while ( pListHead != nullptr ) {
                if ( cds :: meta :: equals ( pListHead->_key.data(), key ) ) {
                    return EntryType ( pListHead->_key.data(), pListHead->_value.data() );
                }

                pListHead   = pListHead->_pNext;
                ++ bucketSize;
            }

            auto pNewNode                       = Memory :: instance().create < DataNode > ();
            pNewNode->_pNext                    = list;
            list                                = pNewNode;

            this->updateSize ( this->size() + 1ULL );

            auto entry = EntryType ( list->_key.data(), list->_value.data() );

            if ( bucketSize >= this->_rehashPolicy.loadFactor() ) {
                auto rehashData = this->_rehashPolicy.rehashRequired (
                        this->_buckets._bucketCount,
                        this->_size,
                        1ULL
                );

                if ( rehashData._required ) {
                    this->rehash (
                            rehashData._size,
                            hashValue % rehashData._size,
                            list
                    );
                }
            }

            isNew = true;

            return entry;
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        auto HashMap < __KeyType, __ValueType, __Hasher > :: rehash (
                Size                bucketCount,
                Size                hashValueOfNewNode,
                DataNode    const * pEmptyNode
        ) noexcept -> void {

            this->_buckets._pBuckets = cds :: __hidden :: __impl :: __allocation :: __reallocPrimitiveArray < BucketType > ( this->_buckets._pBuckets, bucketCount );
            std :: memset (
                    this->_buckets._pBuckets + this->_buckets._bucketCount,
                    0,
                    sizeof ( BucketType ) * ( bucketCount - this->_buckets._bucketCount ) // NOLINT(bugprone-sizeof-expression)
            );

            for ( Size bucketIndex = 0ULL; bucketIndex < this->_buckets._bucketCount; ++ bucketIndex ) {

                auto & bucket   = this->_buckets._pBuckets [ bucketIndex ];

                while ( bucket != nullptr ) {

                    Size hash;
                    if ( pEmptyNode == bucket ) {
                        hash = hashValueOfNewNode;
                    } else {
                        hash = this->_hasher ( bucket->_key.data() ) % bucketCount;
                    }

                    if ( hash != bucketIndex ) {
                        auto pToRemove  = bucket;
                        bucket          = bucket->_pNext;

                        HashMap < __KeyType, __ValueType, __Hasher > :: rehashEmplace (
                                this->_buckets._pBuckets [ hash ],
                                pToRemove
                        );
                    } else {
                        break;
                    }
                }

                auto pHead = bucket;
                while ( pHead != nullptr && pHead->_pNext != nullptr ) {

                    Size hash;
                    if ( pEmptyNode == pHead->_pNext ) {
                        hash = hashValueOfNewNode;
                    } else {
                        hash = this->_hasher ( pHead->_pNext->_key.data() ) % bucketCount;
                    }

                    if ( hash != bucketIndex ) {
                        auto pToRemove  = pHead->_pNext;
                        pHead->_pNext   = pHead->_pNext->_pNext;

                        HashMap < __KeyType, __ValueType, __Hasher > :: rehashEmplace (
                                this->_buckets._pBuckets [ hash ],
                                pToRemove
                        );
                    } else {
                        pHead = pHead->_pNext;
                    }
                }
            }

            this->_buckets._bucketCount = bucketCount;
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        auto HashMap < __KeyType, __ValueType, __Hasher > :: rehashEmplace (
                BucketType   & pBucket,
                DataNode     * pNode
        ) noexcept -> void {

            pNode->_pNext   = pBucket;
            pBucket         = pNode;
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        auto HashMap < __KeyType, __ValueType, __Hasher > :: entryAt (
                KeyType const & key,
                bool          & found
        ) const noexcept -> EntryType const {

            found = false;

            if ( this->_buckets._pBuckets == nullptr ) {
                return EntryType();
            }

            auto hashValue  = this->_hasher ( key ) % this->_buckets._bucketCount;
            auto pListHead  = this->_buckets._pBuckets [ hashValue ];

            while ( pListHead != nullptr ) {
                if ( cds :: meta :: equals ( pListHead->_key.data(), key ) ) {
                    found = true;
                    return EntryType ( pListHead->_key.data(), pListHead->_value.data() );
                }

                pListHead = pListHead->_pNext;
            }

            return EntryType();
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        auto HashMap < __KeyType, __ValueType, __Hasher > :: completeInsertion (
                EntryType * pEntry
        ) noexcept -> void {

            bool isNew;
            auto entry = this->entryAt ( pEntry->key(), isNew );

            if ( isNew ) {
                Map < __KeyType, __ValueType > :: entryMoveOrCopyKeyTo ( & entry, pEntry );
            }

            Map < __KeyType, __ValueType > :: entryMoveOrCopyValueTo ( & entry, pEntry );
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: contains (
                ElementType const & entry
        ) const noexcept -> bool {

            bool found;
            (void) this->entryAt ( entry.key(), found );
            return found;
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: containsKey (
                KeyType const & key
        ) const noexcept -> bool {

            bool found;
            (void) this->entryAt ( key, found );
            return found;
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: containsValue (
                ValueType const & value
        ) const noexcept -> bool {

            for ( Size bucketIndex = 0ULL; bucketIndex < this->_buckets._bucketCount; ++ bucketIndex ) {

                DataNode * pHead = this->_buckets._pBuckets [ bucketIndex ];
                while ( pHead != nullptr ) {

                    if ( cds :: meta :: equals ( pHead->_value.data(), value ) ) {
                        return true;
                    }

                    pHead = pHead->_pNext;
                }
            }

            return false;
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: remove (
                KeyType const & key
        ) noexcept -> bool {

            auto   hash = this->_hasher ( key ) % this->_buckets._bucketCount;
            auto & list = this->_buckets._pBuckets [ hash ];

            if ( this->empty() ) {
                return false;
            }

            if ( cds :: meta :: equals ( list->_key.data(), key ) ) {

                auto pNode  = list;
                list        = list->_pNext;

                pNode->_key.destruct();
                pNode->_value.destruct();
                Memory :: instance().destroy ( pNode );

                this->updateSize ( this->size() - 1ULL );
                return true;
            }

            auto pHead = list;
            while ( pHead->_pNext != nullptr ) {
                if ( cds :: meta :: equals ( pHead->_pNext->_key.data(), key ) ) {

                    auto pToRemove = pHead->_pNext;
                    pHead->_pNext = pHead->_pNext->_pNext;

                    pToRemove->_key.destruct();
                    pToRemove->_value.destruct();
                    Memory :: instance().destroy ( pToRemove );

                    this->updateSize ( this->size() - 1ULL );
                    return true;
                }

                pHead = pHead->_pNext;
            }

            return false;
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: remove (
                Iterator const & iterator
        ) noexcept -> bool {

            /// TODO : come back to this after iterators.
            return false;
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: remove (
                ConstIterator const & iterator
        ) noexcept -> bool {

            /// TODO : come back to this after iterators.
            return false;
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: remove (
                ReverseIterator const & iterator
        ) noexcept -> bool {

            /// TODO : come back to this after iterators.
            return false;
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: remove (
                ConstReverseIterator const & iterator
        ) noexcept -> bool {

            /// TODO : come back to this after iterators.
            return false;
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: remove (
                Iterator    const * pIterators,
                Size                iteratorCount
        ) noexcept -> Size {

            /// TODO : come back to this after iterators.
            return 0ULL;
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: remove (
                ConstIterator   const * pIterators,
                Size                    iteratorCount
        ) noexcept -> Size {

            /// TODO : come back to this after iterators.
            return 0ULL;
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: remove (
                ReverseIterator const * pIterators,
                Size                    iteratorCount
        ) noexcept -> Size {

            /// TODO : come back to this after iterators.
            return 0ULL;
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: remove (
                ConstReverseIterator    const * pIterators,
                Size                            iteratorCount
        ) noexcept -> Size {

            /// TODO : come back to this after iterators.
            return 0ULL;
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: clear () noexcept -> void {

            if ( this->_buckets._pBuckets != nullptr ) {
                for ( Size bucketIndex = 0ULL; bucketIndex < this->_buckets._bucketCount; ++ bucketIndex ) {
                    while ( this->_buckets._pBuckets [ bucketIndex ] != nullptr ) {
                        auto pCopy                                  = this->_buckets._pBuckets [ bucketIndex ];
                        this->_buckets._pBuckets [ bucketIndex ]    = this->_buckets._pBuckets [ bucketIndex ]->_pNext;

                        pCopy->_key.destruct();
                        pCopy->_value.destruct();
                        Memory :: instance().destroy ( pCopy );
                    }
                }
            }

            this->_size = 0ULL;
        }

    }
}

#endif // __CDS_EX_HASH_MAP_IMPL_HPP__
