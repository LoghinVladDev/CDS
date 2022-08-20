/*
 * Created by loghin on 14/08/22.
 */

#ifndef __CDS_EX_MAP_ABSTRACT_KEY_SET_PROXY_IMPL_HPP__
#define __CDS_EX_MAP_ABSTRACT_KEY_SET_PROXY_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {

        template <
                typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
        > constexpr Map <
                __KeyType,
                __ValueType
        > :: AbstractKeySetProxy :: AbstractKeySetProxy (
                Map < __KeyType, __ValueType > * pMap
        ) noexcept :
                ProxyBase ( pMap ) {

        }


        template <
                typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_cpplang_ConstexprDestructor Map <
                __KeyType,
                __ValueType
        > :: AbstractKeySetProxy :: ~AbstractKeySetProxy () noexcept = default;


        template <
                typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_OptimalInline auto Map <
                __KeyType,
                __ValueType
        > :: AbstractKeySetProxy :: clear () noexcept -> void {

            this->map()->clear();
        }


        template <
                typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_OptimalInline auto Map <
                __KeyType,
                __ValueType
        > :: AbstractKeySetProxy :: remove (
                KeyType const & key
        ) noexcept -> bool {

            return this->map()->remove(key);
        }


        template <
                typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_cpplang_VirtualConstexpr auto Map <
                __KeyType,
                __ValueType
        > :: AbstractKeySetProxy :: size () const noexcept -> Size {

            return this->map()->size();
        }


        template <
                typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_OptimalInline auto Map <
                __KeyType,
                __ValueType
        > :: AbstractKeySetProxy :: __newAddress (
                __KeyType const * pReferenceKey,
                bool            * pIsNew        /* NOLINT(readability-non-const-parameter) */
        ) noexcept (false) -> __KeyType * {

            (void) pReferenceKey;
            (void) pIsNew;

            throw cds :: UnsupportedOperationException (
                    cds :: String ( "Cannot insert a value into a Map Key Set" )
            );
        }

    }
}

#endif /* __CDS_EX_MAP_ABSTRACT_KEY_SET_PROXY_IMPL_HPP__ */
