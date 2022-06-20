//
// Created by loghin on 6/18/22.
//

#ifndef __CDS_EX_MAP_ABSTRACT_KEY_SET_PROXY_IMPL_HPP__
#define __CDS_EX_MAP_ABSTRACT_KEY_SET_PROXY_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        constexpr Map < __KeyType, __ValueType > :: AbstractKeySetProxy :: AbstractKeySetProxy (
                Map < __KeyType, __ValueType > * pMap
        ) noexcept :
                Set < KeyType > ( pMap->size() ),
                _pMap ( pMap ) {

        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        constexpr Map < __KeyType, __ValueType > :: AbstractKeySetProxy :: AbstractKeySetProxy (
                AbstractKeySetProxy const & set
        ) noexcept :
                Set < KeyType > ( set ) {

        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        constexpr Map < __KeyType, __ValueType > :: AbstractKeySetProxy :: AbstractKeySetProxy (
                AbstractKeySetProxy && set
        ) noexcept :
                Set < KeyType > ( std :: move ( set ) ) {

        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprDestructor Map < __KeyType, __ValueType > :: AbstractKeySetProxy :: ~AbstractKeySetProxy() noexcept = default;


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: AbstractKeySetProxy :: remove (
                KeyType const & key
        ) noexcept -> bool {

            return this->_pMap->remove ( key );
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: AbstractKeySetProxy :: remove (
                ConstIterator const & iterator
        ) noexcept -> bool {

            /// TODO : after implementing HashMap iterator
            return false;
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: AbstractKeySetProxy :: remove (
                ConstReverseIterator const & iterator
        ) noexcept -> bool {

            /// TODO : after implementing HashMap iterator
            return false;
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: AbstractKeySetProxy :: remove (
                ConstIterator   const * pIterators,
                Size                    iteratorCount
        ) noexcept -> Size {

            /// TODO : after implementing HashMap iterator
            return 0ULL;
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: AbstractKeySetProxy :: remove (
                ConstReverseIterator    const * pIterators,
                Size                            iteratorCount
        ) noexcept -> Size {

            /// TODO : after implementing HashMap iterator
            return 0ULL;
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: AbstractKeySetProxy :: pNewInsert (
                ElementType const & referenceElement
        ) noexcept -> ElementType * & {

            static auto dummyAddress = reinterpret_cast < ElementType * > ( 0x10 );
            return dummyAddress;
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: AbstractKeySetProxy :: contains (
                KeyType const & key
        ) const noexcept -> bool {

            return this->_pMap->containsKey ( key );
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: AbstractKeySetProxy :: clear () noexcept -> void {

            this->_pMap->clear();
        }

    }
}

#endif // __CDS_EX_MAP_ABSTRACT_KEY_SET_PROXY_IMPL_HPP__
