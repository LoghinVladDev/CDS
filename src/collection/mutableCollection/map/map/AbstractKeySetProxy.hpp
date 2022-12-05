/* NOLINT(llvm-header-guard)
 * Created by loghin on 14/08/22.
 */

#ifndef __CDS_MAP_ABSTRACT_KEY_SET_PROXY_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_MAP_ABSTRACT_KEY_SET_PROXY_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {

    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > class __CDS_InheritsEBOs Map <
            __KeyType,
            __ValueType
    > :: AbstractKeySetProxy :
            public cds :: Set < __KeyType const >,
            protected Map < __KeyType, __ValueType > :: AbstractMapProxy {

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using ProxyBase = Map < __KeyType, __ValueType > :: AbstractMapProxy;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using SetBase   = Set < __KeyType const >;


    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using typename SetBase :: __GenericHandler;         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        using typename SetBase :: __GenericConstHandler;    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */


    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_MaybeUnused __CDS_Explicit constexpr AbstractKeySetProxy (    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes) */
                Map < __KeyType, __ValueType > * pMap
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        AbstractKeySetProxy (
                AbstractKeySetProxy const & set
        ) noexcept = delete;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        AbstractKeySetProxy (
                AbstractKeySetProxy &&
        ) noexcept = delete;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_ConstexprDestructor ~AbstractKeySetProxy () noexcept override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                AbstractKeySetProxy const &
        ) noexcept -> AbstractKeySetProxy & = delete;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                AbstractKeySetProxy &&
        ) noexcept -> AbstractKeySetProxy & = delete;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto clear () noexcept -> void override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto remove (
                KeyType const & key
        ) noexcept -> bool override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr auto size () const noexcept -> Size override; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes) */

    protected:
        auto __newAddress ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __KeyType const * pReferenceKey,
                bool            * pIsNew
        ) noexcept (false) -> __KeyType *;
    };

} /* namespace cds */

#endif /* __CDS_MAP_ABSTRACT_KEY_SET_PROXY_HPP__ */
