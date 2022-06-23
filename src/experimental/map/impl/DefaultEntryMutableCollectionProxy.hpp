//
// Created by loghin on 6/18/22.
//

#ifndef __CDS_EX_HASH_MAP_ENTRY_MUTABLE_COLLECTION_PROXY_IMPL_HPP__
#define __CDS_EX_HASH_MAP_ENTRY_MUTABLE_COLLECTION_PROXY_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: DefaultEntryMutableCollectionProxy :: delegateIterator (
                DelegateIteratorRequestType requestType
        ) noexcept -> cds :: UniquePointer < DelegateIterator > {

            return this->map()->delegateIterator ( requestType );
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: DefaultEntryMutableCollectionProxy :: delegateConstIterator (
                DelegateIteratorRequestType requestType
        ) const noexcept -> cds :: UniquePointer < DelegateConstIterator > {

            return this->map()->delegateConstIterator ( requestType );
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        constexpr Map < __KeyType, __ValueType > :: DefaultEntryMutableCollectionProxy :: DefaultEntryMutableCollectionProxy (
                Map < __KeyType, __ValueType > * pMap
        ) noexcept :
                Map < __KeyType, __ValueType > :: AbstractEntryMutableCollectionProxy ( pMap ) {

        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprDestructor Map < __KeyType, __ValueType > :: DefaultEntryMutableCollectionProxy :: ~DefaultEntryMutableCollectionProxy() noexcept = default;


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: DefaultEntryMutableCollectionProxy :: remove (
                Iterator const & iterator
        ) noexcept -> bool {

            return this->map()->remove ( iterator );
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: DefaultEntryMutableCollectionProxy :: remove (
                ConstIterator const & iterator
        ) noexcept -> bool {

            return this->map()->remove ( iterator );
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: DefaultEntryMutableCollectionProxy :: remove (
                ReverseIterator const & iterator
        ) noexcept -> bool {

            return this->map()->remove ( iterator );
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: DefaultEntryMutableCollectionProxy :: remove (
                ConstReverseIterator const & iterator
        ) noexcept -> bool {

            return this->map()->remove ( iterator );
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: DefaultEntryMutableCollectionProxy :: operator == (
                DefaultEntryMutableCollectionProxy const & collection
        ) const noexcept -> bool {

            return this->equals ( collection );
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: DefaultEntryMutableCollectionProxy :: operator != (
                DefaultEntryMutableCollectionProxy const & collection
        ) const noexcept -> bool {

            return ! this->equals ( collection );
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: DefaultEntryMutableCollectionProxy :: size () const noexcept -> Size {

            return this->map()->size();
        }

    }
}

#endif // __CDS_EX_HASH_MAP_ENTRY_MUTABLE_COLLECTION_PROXY_IMPL_HPP__
