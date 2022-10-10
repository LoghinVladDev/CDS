/*
 * Created by loghin on 14/08/22.
 */

#ifndef __CDS_MAP_ABSTRACT_ENTRY_MUTABLE_COLLECTION_PROXY_IMPL_HPP__
#define __CDS_MAP_ABSTRACT_ENTRY_MUTABLE_COLLECTION_PROXY_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {

    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > constexpr Map <
            __KeyType,
            __ValueType
    > :: AbstractEntryMutableCollectionProxy :: AbstractEntryMutableCollectionProxy (
            Map < __KeyType, __ValueType > * pMap
    ) noexcept :
            ProxyBase ( pMap ) {

    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_OptimalInline auto Map <
            __KeyType,
            __ValueType
    > :: AbstractEntryMutableCollectionProxy :: clear () noexcept -> void {

        this->map()->clear();
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_cpplang_ConstexprDestructor Map <
            __KeyType,
            __ValueType
    > :: AbstractEntryMutableCollectionProxy :: ~AbstractEntryMutableCollectionProxy () noexcept = default;


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_cpplang_VirtualConstexpr auto Map <
            __KeyType,
            __ValueType
    > :: AbstractEntryMutableCollectionProxy :: size () const noexcept -> Size {

        return this->map()->size();
    }

}

#endif /* __CDS_MAP_ABSTRACT_ENTRY_MUTABLE_COLLECTION_PROXY_IMPL_HPP__ */
