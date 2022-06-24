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
                AbstractProxy ( pMap ) {

        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        constexpr Map < __KeyType, __ValueType > :: AbstractKeySetProxy :: AbstractKeySetProxy (
                AbstractKeySetProxy const & set
        ) noexcept :
                AbstractProxy ( set ),
                Set < KeyType > ( set ) {

        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        constexpr Map < __KeyType, __ValueType > :: AbstractKeySetProxy :: AbstractKeySetProxy (
                AbstractKeySetProxy && set
        ) noexcept :
                AbstractProxy ( std :: move ( set ) ),
                Set < KeyType > ( std :: move ( set ) ) {

        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprDestructor Map < __KeyType, __ValueType > :: AbstractKeySetProxy :: ~AbstractKeySetProxy() noexcept = default;


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: AbstractKeySetProxy :: remove (
                KeyType const & key
        ) noexcept -> bool {

            return this->map()->remove ( key );
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: AbstractKeySetProxy :: remove (
                ConstIterator   const * pIterators,
                Size                    iteratorCount
        ) noexcept -> Size {

            Size removedCount = 0ULL;
            for ( Size index = 0ULL; index < iteratorCount; ++ index ) {
                if ( this->remove ( pIterators [ index ] ) ) {
                    ++ removedCount;
                }
            }

            return removedCount;
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: AbstractKeySetProxy :: remove (
                ConstReverseIterator    const * pIterators,
                Size                            iteratorCount
        ) noexcept -> Size {

            Size removedCount = 0ULL;
            for ( Size index = 0ULL; index < iteratorCount; ++ index ) {
                if ( this->remove ( pIterators [ index ] ) ) {
                    ++ removedCount;
                }
            }

            return removedCount;
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: AbstractKeySetProxy :: pNewInsert (
                ElementType const & referenceElement
        ) noexcept -> ElementType * {

            return nullptr;
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: AbstractKeySetProxy :: contains (
                KeyType const & key
        ) const noexcept -> bool {

            return this->map()->containsKey ( key );
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: AbstractKeySetProxy :: clear () noexcept -> void {

            this->map()->clear();
        }

    }
}

#endif // __CDS_EX_MAP_ABSTRACT_KEY_SET_PROXY_IMPL_HPP__
