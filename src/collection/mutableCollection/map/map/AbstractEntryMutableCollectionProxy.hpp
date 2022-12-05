/* NOLINT(llvm-header-guard)
 * Created by loghin on 14/08/22.
 */

#ifndef __CDS_MAP_ABSTRACT_ENTRY_MUTABLE_COLLECTION_PROXY_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_MAP_ABSTRACT_ENTRY_MUTABLE_COLLECTION_PROXY_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {

    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > class __CDS_InheritsEBOs Map <
            __KeyType,
            __ValueType
    > :: AbstractEntryMutableCollectionProxy :
            public cds :: MutableCollection < EntryType >,
            protected Map < __KeyType, __ValueType > :: AbstractMapProxy {

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using ProxyBase             = Map < __KeyType, __ValueType > :: AbstractMapProxy;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using MutableCollectionBase = MutableCollection < EntryType >;


    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using typename MutableCollectionBase :: __GenericHandler;         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using typename MutableCollectionBase :: __GenericConstHandler;    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */


    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_MaybeUnused __CDS_Explicit constexpr AbstractEntryMutableCollectionProxy ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes) */
                Map < __KeyType, __ValueType > * pMap
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        AbstractEntryMutableCollectionProxy (
                AbstractEntryMutableCollectionProxy const &
        ) noexcept = delete;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        AbstractEntryMutableCollectionProxy (
                AbstractEntryMutableCollectionProxy &&
        ) noexcept = delete;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_ConstexprDestructor ~AbstractEntryMutableCollectionProxy () noexcept override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                AbstractEntryMutableCollectionProxy const &
        ) noexcept -> AbstractEntryMutableCollectionProxy & = delete;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                AbstractEntryMutableCollectionProxy &&
        ) noexcept -> AbstractEntryMutableCollectionProxy & = delete;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto clear () noexcept -> void override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto toString () const noexcept -> String override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr auto size () const noexcept -> Size override; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes) */
    };

} /* namespace cds */

#endif /* __CDS_MAP_ABSTRACT_ENTRY_MUTABLE_COLLECTION_PROXY_HPP__ */
