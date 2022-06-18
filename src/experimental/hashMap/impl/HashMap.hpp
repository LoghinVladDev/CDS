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
        __CDS_cpplang_ConstexprOverride auto HashMap < __KeyType, __ValueType, __HashCalculator > :: valueCollectionProxy () const noexcept -> AbstractValueCollectionProxy const & {

            return this->_valueCollectionProxy;
        }


        template < typename __KeyType, typename __ValueType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto HashMap < __KeyType, __ValueType, __HashCalculator > :: valueCollectionProxy () noexcept -> AbstractValueCollectionProxy & {

            return this->_valueCollectionProxy;
        }


        template < typename __KeyType, typename __ValueType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto HashMap < __KeyType, __ValueType, __HashCalculator > :: entrySetProxy () const noexcept -> AbstractEntrySetProxy const & {

            return this->_entrySetProxy;
        }


        template < typename __KeyType, typename __ValueType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto HashMap < __KeyType, __ValueType, __HashCalculator > :: entrySetProxy () noexcept -> AbstractEntrySetProxy & {

            return this->_entrySetProxy;
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
                _valueCollectionProxy ( this ),
                _entrySetProxy ( this ) {

        }


        template < typename __KeyType, typename __ValueType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        HashMap < __KeyType, __ValueType, __HashCalculator > :: HashMap (
                HashMap const & map
        ) noexcept :
                Map < __KeyType, __ValueType > ( map ),
                _keySetProxy ( this ),
                _valueCollectionProxy ( this ),
                _entrySetProxy ( this ) {

            this->_pBucketList =
                    map.empty() ?
                    nullptr     :
                    cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < BucketType > ( this->_hashCalculator.getBoundary() );

            if ( ! map.empty() ) {
                for ( Size bucketIndex = 0ULL; bucketIndex < this->_hashCalculator.getBoundary(); ++ bucketIndex ) {

                    DataNode * & pCurrentBucket = this->_pBucketList [ bucketIndex ];
                    DataNode   * pOtherBucket   = map._pBucketList [ bucketIndex ];

                    DataNode   * pBack          = nullptr;

                    while ( pOtherBucket != nullptr ) {

                        DataNode * pNewNode = Memory :: instance().create < DataNode > ();
                        pNewNode->_pNext     = nullptr;
                        pNewNode->_pPrevious = nullptr;

                        pOtherBucket->_entry.copyInto ( pNewNode->_entry );

                        if ( pBack == nullptr ) {
                            pCurrentBucket  = pNewNode;
                        } else {
                            pBack->_pNext   = pNewNode;
                        }

                        pBack           = pNewNode;
                        pOtherBucket    = pOtherBucket->_pNext;
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
                _valueCollectionProxy ( this ),
                _entrySetProxy ( this ),
                _pBucketList ( cds :: exchange ( map._pBucketList, nullptr ) ) {

        }


        template < typename __KeyType, typename __ValueType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        HashMap < __KeyType, __ValueType, __HashCalculator > :: ~HashMap () noexcept {

            for ( Size bucketIndex = 0ULL; bucketIndex < this->_hashCalculator.getBoundary(); ++ bucketIndex ) {
                while ( this->_pBucketList [ bucketIndex ] != nullptr ) {
                    auto pCopy                          = this->_pBucketList [ bucketIndex ];
                    this->_pBucketList [ bucketIndex ]  = this->_pBucketList [ bucketIndex ]->_pNext;

                    Map < __KeyType, __ValueType > :: freeEntryData ( pCopy->_entry );
                    Memory :: instance().destroy ( pCopy );
                }
            }

            cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( this->_pBucketList );
        }

    }
}

#endif // __CDS_EX_HASH_MAP_IMPL_HPP__
