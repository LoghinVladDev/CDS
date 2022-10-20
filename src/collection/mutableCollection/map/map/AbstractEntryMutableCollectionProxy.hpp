/*
 * Created by loghin on 14/08/22.
 */

#ifndef __CDS_MAP_ABSTRACT_ENTRY_MUTABLE_COLLECTION_PROXY_HPP__
#define __CDS_MAP_ABSTRACT_ENTRY_MUTABLE_COLLECTION_PROXY_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {

    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
    > class Map <
            __KeyType,
            __ValueType
    > :: AbstractEntryMutableCollectionProxy :
            public cds :: MutableCollection < EntryType >,
            protected Map < __KeyType, __ValueType > :: AbstractMapProxy {

    protected:  using ProxyBase             = Map < __KeyType, __ValueType > :: AbstractMapProxy;
    protected:  using MutableCollectionBase = MutableCollection < EntryType >;

    protected:  using typename MutableCollectionBase :: __GenericHandler;         /* NOLINT(bugprone-reserved-identifier) */
    protected:  using typename MutableCollectionBase :: __GenericConstHandler;    /* NOLINT(bugprone-reserved-identifier) */

    protected:
        __CDS_Explicit constexpr AbstractEntryMutableCollectionProxy (
                Map < __KeyType, __ValueType > * pMap
        ) noexcept;

    public:
        AbstractEntryMutableCollectionProxy (
                AbstractEntryMutableCollectionProxy const &
        ) noexcept = delete;

    public:
        AbstractEntryMutableCollectionProxy (
                AbstractEntryMutableCollectionProxy &&
        ) noexcept = delete;


    public:
        __CDS_cpplang_ConstexprDestructor ~AbstractEntryMutableCollectionProxy () noexcept override;

    public:
        auto operator = (
                AbstractEntryMutableCollectionProxy const &
        ) noexcept -> AbstractEntryMutableCollectionProxy & = delete;

    public:
        auto operator = (
                AbstractEntryMutableCollectionProxy &&
        ) noexcept -> AbstractEntryMutableCollectionProxy & = delete;

    public:
        auto clear () noexcept -> void override;

    public:
        __CDS_NoDiscard auto toString () const noexcept -> String override;

    public:
        __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr auto size () const noexcept -> Size override;
    };

}

#endif /* __CDS_MAP_ABSTRACT_ENTRY_MUTABLE_COLLECTION_PROXY_HPP__ */
