/*
 * Created by loghin on 14/08/22.
 */

#ifndef __CDS_MAP_ABSTRACT_VALUE_MUTABLE_COLLECTION_PROXY_HPP__
#define __CDS_MAP_ABSTRACT_VALUE_MUTABLE_COLLECTION_PROXY_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {

    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > class Map <
            __KeyType,
            __ValueType
    > :: AbstractValueMutableCollectionProxy :
            public cds :: MutableCollection < __ValueType >,
            protected Map < __KeyType, __ValueType > :: AbstractMapProxy {

    protected:  using ProxyBase             = Map < __KeyType, __ValueType > :: AbstractMapProxy;
    protected:  using MutableCollectionBase = MutableCollection < __ValueType >;

    protected:  using typename MutableCollectionBase :: __GenericHandler;         /* NOLINT(bugprone-reserved-identifier) */
    protected:  using typename MutableCollectionBase :: __GenericConstHandler;    /* NOLINT(bugprone-reserved-identifier) */

    protected:
        __CDS_Explicit constexpr AbstractValueMutableCollectionProxy (
                Map < __KeyType, __ValueType > * pMap
        ) noexcept;

    public:
        AbstractValueMutableCollectionProxy (
                AbstractValueMutableCollectionProxy const & collection
        ) noexcept = delete;

    public:
        AbstractValueMutableCollectionProxy (
                AbstractValueMutableCollectionProxy && collection
        ) noexcept = delete;

    public:
        __CDS_cpplang_ConstexprDestructor ~AbstractValueMutableCollectionProxy () noexcept override;

    public:
        auto operator = (
                AbstractValueMutableCollectionProxy const &
        ) noexcept -> AbstractValueMutableCollectionProxy & = delete;

    public:
        auto operator = (
                AbstractValueMutableCollectionProxy &&
        ) noexcept -> AbstractValueMutableCollectionProxy & = delete;

    public:
        auto clear () noexcept -> void override;

    public:
        __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr auto size () const noexcept -> Size override;

    protected:
        auto __newAddress ( /* NOLINT(bugprone-reserved-identifier) */
                __ValueType const * pReferenceKey,
                bool              * pIsNew
        ) noexcept (false) -> __ValueType *;
    };

}

#endif /* __CDS_MAP_ABSTRACT_VALUE_MUTABLE_COLLECTION_PROXY_HPP__ */
