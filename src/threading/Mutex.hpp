/* NOLINT(llvm-header-guard)
 * Created by loghin on 08.03.2021.
 */

#ifndef __CDS_MUTEX_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_MUTEX_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/Object>

#include "mutex/Config.hpp"

namespace cds {

    class Mutex : public Object {

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        cds :: __hidden :: __impl :: __MutexPlatformHandleType _handle;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        Mutex () noexcept;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        Mutex (
                Mutex const & /* mutex */
        ) noexcept = delete;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        Mutex (
                Mutex && mutex
        ) noexcept = delete;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        ~Mutex () noexcept override;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                Mutex const & /* mutex */
        ) noexcept -> Mutex & = delete;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                Mutex && mutex
        ) noexcept -> Mutex & = delete;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        auto lock () noexcept -> void;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto tryLock () noexcept -> bool;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        auto unlock () noexcept -> void;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto toString () const noexcept -> String override;

    public:     /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto hash () const noexcept -> Size override;
    };

} /* namespace cds */

#include "mutex/impl/Mutex.hpp"

#endif /* __CDS_MUTEX_HPP__ */
