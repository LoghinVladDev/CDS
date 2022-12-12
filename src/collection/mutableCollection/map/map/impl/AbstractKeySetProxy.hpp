/* NOLINT(llvm-header-guard)
 * Created by loghin on 14/08/22.
 */

#ifndef __CDS_MAP_ABSTRACT_KEY_SET_PROXY_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_MAP_ABSTRACT_KEY_SET_PROXY_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {

    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_MaybeUnused constexpr Map <
            __KeyType,
            __ValueType
    > :: AbstractKeySetProxy :: AbstractKeySetProxy (
            Map < __KeyType, __ValueType > * pMap
    ) noexcept :
            ProxyBase ( pMap ) {

    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_cpplang_ConstexprDestructor Map <
            __KeyType,
            __ValueType
    > :: AbstractKeySetProxy :: ~AbstractKeySetProxy () noexcept = default;


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_OptimalInline auto Map <
            __KeyType,
            __ValueType
    > :: AbstractKeySetProxy :: clear () noexcept -> void {

        this->map()->clear();
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_OptimalInline auto Map <
            __KeyType,
            __ValueType
    > :: AbstractKeySetProxy :: remove (
            KeyType const & key
    ) noexcept -> bool {

        return this->map()->remove(key);
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_cpplang_VirtualConstexpr auto Map <
            __KeyType,
            __ValueType
    > :: AbstractKeySetProxy :: size () const noexcept -> Size {

        return this->map()->size();
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_OptimalInline auto Map <
            __KeyType,
            __ValueType
    > :: AbstractKeySetProxy :: __newAddress (
            AbstractKeySetProxy       * pObject,        /* NOLINT(readability-non-const-parameter) */
            __KeyType           const * pReferenceKey,
            bool                      * pIsNew          /* NOLINT(readability-non-const-parameter) */
    ) noexcept (false) -> __KeyType * {

        (void) pReferenceKey;
        (void) pIsNew;
        (void) pObject;

        throw cds :: UnsupportedOperationException (
                cds :: String ( "Cannot insert a value into a Map Key Set" )
        );
    }

} /* namespace cds */

#endif /* __CDS_MAP_ABSTRACT_KEY_SET_PROXY_IMPL_HPP__ */
