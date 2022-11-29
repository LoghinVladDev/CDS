/* NOLINT(llvm-header-guard)
 * Created by loghin on 14/08/22.
 */

#ifndef __CDS_MAP_ABSTRACT_MAP_PROXY_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_MAP_ABSTRACT_MAP_PROXY_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {

    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > class Map <
            __KeyType,
            __ValueType
    > :: AbstractMapProxy {

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        Map < __KeyType, __ValueType > * _pMap;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_MaybeUnused __CDS_Explicit constexpr AbstractMapProxy ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-non-private-member-variables-in-classes) */
                Map < __KeyType, __ValueType > * pMap
        ) noexcept;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        constexpr AbstractMapProxy (
                AbstractMapProxy const & proxy
        ) noexcept;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        constexpr AbstractMapProxy (
                AbstractMapProxy && proxy
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        ~AbstractMapProxy () noexcept = default;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                AbstractMapProxy const & /* proxy */
        ) noexcept -> AbstractMapProxy & = delete;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                AbstractMapProxy && /* proxy */
        ) noexcept -> AbstractMapProxy & = delete;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        template < typename __DerivedType = Map < __KeyType, __ValueType > > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        __CDS_NoDiscard auto map () noexcept -> __DerivedType *;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        template < typename __DerivedType = Map < __KeyType, __ValueType > > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        __CDS_NoDiscard auto map () const noexcept -> __DerivedType const *;

    };

} /* namespace cds */

#endif /* __CDS_MAP_ABSTRACT_MAP_PROXY_HPP__ */
