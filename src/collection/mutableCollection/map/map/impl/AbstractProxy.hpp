//
// Created by loghin on 6/23/22.
//

#ifndef __CDS_MAP_ABSTRACT_PROXY_IMPL_HPP__
#define __CDS_MAP_ABSTRACT_PROXY_IMPL_HPP__

namespace cds {

    template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
    constexpr Map < __KeyType, __ValueType > :: AbstractProxy :: AbstractProxy (
            Map < __KeyType, __ValueType > * pMap
    ) noexcept :
            _pMap ( pMap ) {

    }


    template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
    constexpr Map < __KeyType, __ValueType > :: AbstractProxy :: AbstractProxy (
            AbstractProxy const & proxy
    ) noexcept :
            _pMap ( proxy._pMap ) {

    }


    template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
    constexpr Map < __KeyType, __ValueType > :: AbstractProxy :: AbstractProxy (
            AbstractProxy && proxy
    ) noexcept :
            _pMap ( cds :: exchange ( proxy._pMap, nullptr ) ) {

    }


    template < typename __KeyType, typename __ValueType >   // NOLINT(bugprone-reserved-identifier)
    template < typename __DerivedType >                     // NOLINT(bugprone-reserved-identifier)
    constexpr auto Map < __KeyType, __ValueType > :: AbstractProxy :: map () const noexcept -> __DerivedType * {

        return reinterpret_cast < __DerivedType * > ( this->_pMap );
    }

}

#endif // __CDS_MAP_ABSTRACT_PROXY_IMPL_HPP__
