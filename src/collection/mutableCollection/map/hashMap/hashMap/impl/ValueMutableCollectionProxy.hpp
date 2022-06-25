//
// Created by loghin on 6/18/22.
//

#ifndef __CDS_HASH_MAP_VALUE_MUTABLE_COLLECTION_PROXY_IMPL_HPP__
#define __CDS_HASH_MAP_VALUE_MUTABLE_COLLECTION_PROXY_IMPL_HPP__

namespace cds {

    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    auto HashMap < __KeyType, __ValueType, __Hasher > :: HashMapValueMutableCollectionProxy :: delegateIterator (
            DelegateIteratorRequestType requestType
    ) noexcept -> cds :: UniquePointer < DelegateIterator > {

        switch ( requestType ) {
            case DelegateIteratorRequestType :: ForwardBegin:
            case DelegateIteratorRequestType :: BackwardBegin:
                return Memory :: instance().create < HashMapValueMutableCollectionProxyDelegateIterator > ( this->template map < HashMap < __KeyType, __ValueType, __Hasher > > ()->__ht_begin() );
            case DelegateIteratorRequestType :: ForwardEnd:
            case DelegateIteratorRequestType :: BackwardEnd:
                return Memory :: instance().create < HashMapValueMutableCollectionProxyDelegateIterator > ( this->template map < HashMap < __KeyType, __ValueType, __Hasher > > ()->__ht_end() );
        }

        return nullptr;
    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    auto HashMap < __KeyType, __ValueType, __Hasher > :: HashMapValueMutableCollectionProxy :: delegateConstIterator (
            DelegateIteratorRequestType requestType
    ) const noexcept -> cds :: UniquePointer < DelegateConstIterator > {

        switch ( requestType ) {
            case DelegateIteratorRequestType :: ForwardBegin:
            case DelegateIteratorRequestType :: BackwardBegin:
                return Memory :: instance().create < HashMapValueMutableCollectionProxyDelegateConstIterator > ( this->template map < HashMap < __KeyType, __ValueType, __Hasher > > ()->__ht_cbegin() );
            case DelegateIteratorRequestType :: ForwardEnd:
            case DelegateIteratorRequestType :: BackwardEnd:
                return Memory :: instance().create < HashMapValueMutableCollectionProxyDelegateConstIterator > ( this->template map < HashMap < __KeyType, __ValueType, __Hasher > > ()->__ht_cend() );
        }

        return nullptr;
    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    constexpr HashMap < __KeyType, __ValueType, __Hasher > :: HashMapValueMutableCollectionProxy :: HashMapValueMutableCollectionProxy (
            HashMap < __KeyType, __ValueType, __Hasher > * pMap
    ) noexcept :
            Map < __KeyType, __ValueType > :: AbstractValueMutableCollectionProxy ( pMap ) {

    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    constexpr HashMap < __KeyType, __ValueType, __Hasher > :: HashMapValueMutableCollectionProxy :: HashMapValueMutableCollectionProxy (
            HashMapValueMutableCollectionProxy const & collection
    ) noexcept :
            Map < __KeyType, __ValueType > :: AbstractValueMutableCollectionProxy ( collection ) {

    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    constexpr HashMap < __KeyType, __ValueType, __Hasher > :: HashMapValueMutableCollectionProxy :: HashMapValueMutableCollectionProxy (
            HashMapValueMutableCollectionProxy && collection
    ) noexcept :
            Map < __KeyType, __ValueType > :: AbstractValueMutableCollectionProxy ( std :: move ( collection ) ) {

    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_ConstexprDestructor HashMap < __KeyType, __ValueType, __Hasher > :: HashMapValueMutableCollectionProxy :: ~HashMapValueMutableCollectionProxy() noexcept = default;


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: HashMapValueMutableCollectionProxy :: remove (
            Iterator const & iterator
    ) noexcept -> bool {

        return this-> template map < HashMap < __KeyType, __ValueType, __Hasher > > ()->__ht_remove (
                reinterpret_cast < HashMapValueMutableCollectionProxyDelegateIterator const * > (
                        HashMapValueMutableCollectionProxy :: acquireDelegate ( iterator )
                )->iterator()
        );
    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: HashMapValueMutableCollectionProxy :: remove (
            ConstIterator const & iterator
    ) noexcept -> bool {

        return this-> template map < HashMap < __KeyType, __ValueType, __Hasher > > ()->__ht_remove (
                reinterpret_cast < HashMapValueMutableCollectionProxyDelegateConstIterator const * > (
                        HashMapValueMutableCollectionProxy :: acquireDelegate ( iterator )
                )->iterator()
        );
    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: HashMapValueMutableCollectionProxy :: remove (
            ReverseIterator const & iterator
    ) noexcept -> bool {

        return this-> template map < HashMap < __KeyType, __ValueType, __Hasher > > ()->__ht_remove (
                reinterpret_cast < HashMapValueMutableCollectionProxyDelegateIterator const * > (
                        HashMapValueMutableCollectionProxy :: acquireDelegate ( iterator )
                )->iterator()
        );
    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: HashMapValueMutableCollectionProxy :: remove (
            ConstReverseIterator const & iterator
    ) noexcept -> bool {

        return this-> template map < HashMap < __KeyType, __ValueType, __Hasher > > ()->__ht_remove (
                reinterpret_cast < HashMapValueMutableCollectionProxyDelegateConstIterator const * > (
                        HashMapValueMutableCollectionProxy :: acquireDelegate ( iterator )
                )->iterator()
        );
    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: HashMapValueMutableCollectionProxy :: operator == (
            HashMapValueMutableCollectionProxy const & collection
    ) const noexcept -> bool {

        return this->equals ( collection );
    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: HashMapValueMutableCollectionProxy :: operator != (
            HashMapValueMutableCollectionProxy const & collection
    ) const noexcept -> bool {

        return ! this->equals ( collection );
    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: HashMapValueMutableCollectionProxy :: size () const noexcept -> Size {

        return this-> template map < HashMap < __KeyType, __ValueType, __Hasher > > ()->__ht_size ();
    }

}

#endif // __CDS_HASH_MAP_VALUE_MUTABLE_COLLECTION_PROXY_IMPL_HPP__
