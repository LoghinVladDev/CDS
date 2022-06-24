//
// Created by loghin on 6/18/22.
//

#ifndef __CDS_HASH_MAP_KEY_SET_PROXY_IMPL_HPP__
#define __CDS_HASH_MAP_KEY_SET_PROXY_IMPL_HPP__

namespace cds {

    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    auto HashMap < __KeyType, __ValueType, __Hasher > :: HashMapKeySetProxy :: delegateConstIterator (
            DelegateIteratorRequestType requestType
    ) const noexcept -> cds :: UniquePointer < DelegateConstIterator > {

        switch ( requestType ) {
            case DelegateIteratorRequestType :: ForwardBegin:
            case DelegateIteratorRequestType :: BackwardBegin:
                return Memory :: instance().create < HashMapKeySetProxyDelegateConstIterator > ( this->template map < HashMap < __KeyType, __ValueType, __Hasher > > ()->__ht_cbegin() );
            case DelegateIteratorRequestType :: ForwardEnd:
            case DelegateIteratorRequestType :: BackwardEnd:
                return Memory :: instance().create < HashMapKeySetProxyDelegateConstIterator > ( this->template map < HashMap < __KeyType, __ValueType, __Hasher > > ()->__ht_cend() );
        }

        return nullptr;
    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    constexpr HashMap < __KeyType, __ValueType, __Hasher > :: HashMapKeySetProxy :: HashMapKeySetProxy (
            HashMap < __KeyType, __ValueType, __Hasher > * pMap
    ) noexcept :
            Map < __KeyType, __ValueType > :: AbstractKeySetProxy ( pMap ) {

    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    constexpr HashMap < __KeyType, __ValueType, __Hasher > :: HashMapKeySetProxy :: HashMapKeySetProxy (
            HashMapKeySetProxy const & keySetProxy
    ) noexcept :
            Map < __KeyType, __ValueType > :: AbstractKeySetProxy ( keySetProxy ) {

    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    constexpr HashMap < __KeyType, __ValueType, __Hasher > :: HashMapKeySetProxy :: HashMapKeySetProxy (
            HashMapKeySetProxy && keySetProxy
    ) noexcept :
            Map < __KeyType, __ValueType > :: AbstractKeySetProxy ( std :: move ( keySetProxy ) ) {

    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_ConstexprDestructor HashMap < __KeyType, __ValueType, __Hasher > :: HashMapKeySetProxy :: ~HashMapKeySetProxy() noexcept = default;


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: HashMapKeySetProxy :: remove (
            ConstIterator const & iterator
    ) noexcept -> bool {

        return this-> template map < HashMap < __KeyType, __ValueType, __Hasher > > ()->__ht_remove (
                reinterpret_cast < HashMapKeySetProxyDelegateConstIterator const * > ( HashMapKeySetProxy :: acquireDelegate ( iterator ) )->iterator()
        );
    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: HashMapKeySetProxy :: remove (
            ConstReverseIterator const & iterator
    ) noexcept -> bool {

        return this-> template map < HashMap < __KeyType, __ValueType, __Hasher > > ()->__ht_remove (
                reinterpret_cast < HashMapKeySetProxyDelegateConstIterator const * > ( HashMapKeySetProxy :: acquireDelegate ( iterator ) )->iterator()
        );
    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: HashMapKeySetProxy :: operator == (
            HashMapKeySetProxy const & set
    ) const noexcept -> bool {

        return this->equals ( set );
    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: HashMapKeySetProxy :: operator != (
            HashMapKeySetProxy const & set
    ) const noexcept -> bool {

        return ! this->equals ( set );
    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: HashMapKeySetProxy :: size () const noexcept -> Size {

        return this-> template map < HashMap < __KeyType, __ValueType, __Hasher > > ()->__ht_size ();
    }

}

#endif // __CDS_HASH_MAP_KEY_SET_PROXY_IMPL_HPP__
