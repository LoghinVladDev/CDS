/* NOLINT(llvm-header-guard)
 * Created by loghin on 14/08/22.
 */

#ifndef __CDS_MAP_ABSTRACT_VALUE_MUTABLE_COLLECTION_PROXY_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_MAP_ABSTRACT_VALUE_MUTABLE_COLLECTION_PROXY_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {

    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > class __CDS_InheritsEBOs Map <
            __KeyType,
            __ValueType
    > :: AbstractValueMutableCollectionProxy :
            public cds :: MutableCollection < __ValueType >,
            protected Map < __KeyType, __ValueType > :: AbstractMapProxy {

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using ProxyBase             = Map < __KeyType, __ValueType > :: AbstractMapProxy;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using MutableCollectionBase = MutableCollection < __ValueType >;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using typename MutableCollectionBase :: __GenericHandler;         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using typename MutableCollectionBase :: __GenericConstHandler;    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */


    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_MaybeUnused __CDS_Explicit constexpr AbstractValueMutableCollectionProxy (    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes) */
                Map < __KeyType, __ValueType > * pMap
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        AbstractValueMutableCollectionProxy (
                AbstractValueMutableCollectionProxy const & collection
        ) noexcept = delete;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        AbstractValueMutableCollectionProxy (
                AbstractValueMutableCollectionProxy && collection
        ) noexcept = delete;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_ConstexprDestructor ~AbstractValueMutableCollectionProxy () noexcept override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                AbstractValueMutableCollectionProxy const &
        ) noexcept -> AbstractValueMutableCollectionProxy & = delete;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                AbstractValueMutableCollectionProxy &&
        ) noexcept -> AbstractValueMutableCollectionProxy & = delete;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto clear () noexcept -> void override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr auto size () const noexcept -> Size override; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes) */

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto toString () const noexcept -> String override;

    protected:
        static auto __newAddress ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                AbstractValueMutableCollectionProxy       * pObject,
                __ValueType                         const * pReferenceKey,
                bool                                      * pIsNew
        ) noexcept (false) -> __ValueType *;
    };

} /* namespace cds */

#endif /* __CDS_MAP_ABSTRACT_VALUE_MUTABLE_COLLECTION_PROXY_HPP__ */
