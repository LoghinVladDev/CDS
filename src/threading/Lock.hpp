/*
 * Created by loghin on 31.01.2022.
 */

#ifndef __CDS_LOCK_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_LOCK_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/Tuple>

namespace cds {

    template < typename __LockedObjectType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    class Lock : public Object {

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        __LockedObjectType & _lock; /* NOLINT(*-avoid-const-or-ref-data-members) */

    public: /* NOLINT(readability-redundant-access-specifiers) */
        Lock () noexcept = delete;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        Lock ( Lock const & ) noexcept = delete;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        Lock ( Lock && ) noexcept = delete;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_Explicit Lock ( __LockedObjectType & lock ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        ~Lock () noexcept override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = ( Lock const & ) noexcept -> Lock & = delete;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = ( Lock && ) noexcept -> Lock & = delete;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto toString () const noexcept -> String override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto hash () const noexcept -> Size override;
    };


    template < typename __LockedObjectType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    using LockGuard __CDS_DeprecatedHint("Deprecated, use cds :: Lock instead") = Lock < __LockedObjectType >;


    template < typename __LockedObjectType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    class DeferredLock : public Object {     /* NOLINT(*-special-member-functions) */

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        __LockedObjectType * pLock;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        DeferredLock () noexcept = delete;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        DeferredLock ( DeferredLock const & ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_Explicit DeferredLock ( __LockedObjectType & lock ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        ~DeferredLock () noexcept override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = ( DeferredLock const & ) noexcept -> DeferredLock &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto lock () noexcept -> void;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto tryLock () noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto unlock () noexcept -> void;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto equals (
                Object const & object
        ) const noexcept -> bool override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto toString () const noexcept -> String override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto hash () const noexcept -> Size override;
    };


    template < typename ... __LockedObjects >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    class GroupLock : public Object {

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        Tuple < __LockedObjects & ... > locks;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        GroupLock () noexcept = delete;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        GroupLock ( GroupLock const & ) noexcept = delete;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        GroupLock ( GroupLock && ) noexcept = delete;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_Explicit GroupLock ( __LockedObjects & ... lock ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        ~GroupLock () noexcept override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = ( GroupLock const & ) noexcept -> GroupLock & = delete;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = ( GroupLock && ) noexcept -> GroupLock & = delete;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto lock () noexcept -> void;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto tryLock () noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto unlock () noexcept -> void;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto equals (
                Object const & object
        ) const noexcept -> bool override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto toString () const noexcept -> String override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto hash () const noexcept -> Size override;
    };

} /* namespace cds */

#include "lock/impl/Lock.hpp"
#include "lock/impl/CTAD.hpp"

#endif /* __CDS_LOCK_HPP__ */
