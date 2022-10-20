/*
 * Created by loghin on 14/08/22.
 */

#ifndef __CDS_MAP_ABSTRACT_ENTRY_MUTABLE_COLLECTION_PROXY_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_MAP_ABSTRACT_ENTRY_MUTABLE_COLLECTION_PROXY_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {

    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_MaybeUnused constexpr Map <
            __KeyType,
            __ValueType
    > :: AbstractEntryMutableCollectionProxy :: AbstractEntryMutableCollectionProxy (
            Map < __KeyType, __ValueType > * pMap
    ) noexcept :
            ProxyBase ( pMap ) {

    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_OptimalInline auto Map <
            __KeyType,
            __ValueType
    > :: AbstractEntryMutableCollectionProxy :: clear () noexcept -> void {

        this->map()->clear();
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_cpplang_ConstexprDestructor Map <
            __KeyType,
            __ValueType
    > :: AbstractEntryMutableCollectionProxy :: ~AbstractEntryMutableCollectionProxy () noexcept = default;


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_cpplang_VirtualConstexpr auto Map <
            __KeyType,
            __ValueType
    > :: AbstractEntryMutableCollectionProxy :: size () const noexcept -> Size {

        return this->map()->size();
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_OptimalInline auto Map <
            __KeyType,
            __ValueType
    > :: AbstractEntryMutableCollectionProxy :: toString () const noexcept -> String {

        return this->map()->toString();
    }

} /* namespace cds */

#endif /* __CDS_MAP_ABSTRACT_ENTRY_MUTABLE_COLLECTION_PROXY_IMPL_HPP__ */
