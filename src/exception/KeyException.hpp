/*
 * Created by loghin on 30/11/22.
 */

#ifndef __CDS_KEY_EXCEPTION_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_KEY_EXCEPTION_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/exception/RuntimeException>

namespace cds {

    class KeyException : public RuntimeException {

    public:
        KeyException () noexcept;

    public:
        KeyException (
                KeyException const & exception
        ) noexcept;

    public:
        KeyException (
                KeyException && exception
        ) noexcept;

    public:
        template < typename __KeyType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        explicit KeyException (
                __KeyType const & key
        ) noexcept;

    public:
        ~KeyException() noexcept override = default;
    };

} /* namespace cds */

#include "exception/impl/KeyException.hpp"

__CDS_Meta_RegisterParseType(KeyException)

#endif /* __CDS_KEY_EXCEPTION_HPP__ */
