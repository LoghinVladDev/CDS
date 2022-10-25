/*
 * Created by loghin on 07.03.2021.
 */

#ifndef __CDS_THREAD_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_THREAD_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/Object>

#include "thread/Config.hpp"

namespace cds {

    class Thread : public Object { /* NOLINT(*-member-init) */

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        cds :: __hidden :: __impl :: __ThreadPlatformHandleType _handle;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        Thread () noexcept = default; /* NOLINT(*-member-init) */

    public: /* NOLINT(readability-redundant-access-specifiers) */
        Thread (
                Thread const & /* thread */
        ) noexcept = delete;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        Thread (
                Thread && thread
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        ~Thread () noexcept override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                Thread const & /* thread */
        ) noexcept -> Thread & = delete;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                Thread && thread
        ) noexcept -> Thread & = delete;

    protected:  /* NOLINT(readability-redundant-access-specifiers) */
        virtual auto run () noexcept (false) -> void = 0;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        static auto launch (
                void * pArgument
        ) noexcept (false) -> cds :: __hidden :: __impl :: __ThreadPlatformFunctionReturnType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard static auto hardwareConcurrency () noexcept -> Size;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto start () noexcept -> void;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto kill () noexcept -> void;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto join () noexcept -> void;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard static auto currentThreadID () noexcept -> cds :: __hidden :: __impl :: __ThreadPlatformIdType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto toString () const noexcept -> String override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto equals (
                Object const & object
        ) const noexcept -> bool override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto hash () const noexcept -> Size override;
    };


    template < typename __ThreadFunction >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    class Runnable : public Thread {

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        __ThreadFunction _function;

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        auto run () noexcept (false) -> void override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        Runnable () noexcept = delete;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        Runnable (
                Runnable const & /* runnable */
        ) noexcept = delete;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        Runnable (
                Runnable && runnable
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_Implicit Runnable ( /* NOLINT(google-explicit-constructor, *-explicit-conversions) */
                __ThreadFunction threadFunction
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        ~Runnable () noexcept override = default;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                Runnable const & /* runnable */
        ) noexcept -> Runnable & = delete;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                Runnable && /* runnable */
        ) noexcept -> Runnable & = delete;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto toString () const noexcept -> String override;
    };

} /* namespace cds */

#include "thread/impl/Thread.hpp" /* NOLINT(llvm-include-order) */
#include "thread/impl/CTAD.hpp"

#endif /* __CDS_THREAD_HPP__ */
