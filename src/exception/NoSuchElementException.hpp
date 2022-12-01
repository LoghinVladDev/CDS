/*
 * Created by loghin on 30/11/22.
 */

#ifndef __CDS_NO_SUCH_ELEMENT_EXCEPTION_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_NO_SUCH_ELEMENT_EXCEPTION_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/exception/RuntimeException>

namespace cds {

    class NoSuchElementException : public RuntimeException {

    public:
        NoSuchElementException () noexcept;

    public:
        NoSuchElementException (
                NoSuchElementException const & exception
        ) noexcept;

    public:
        NoSuchElementException (
                NoSuchElementException && exception
        ) noexcept;

    public:
        explicit NoSuchElementException (
                StringView message
        ) noexcept;

    public:
        ~NoSuchElementException() noexcept override = default;
    };

} /* namespace cds */

#include "exception/impl/NoSuchElementException.hpp"

__CDS_Meta_RegisterParseType(NoSuchElementException)

#endif /* __CDS_NO_SUCH_ELEMENT_EXCEPTION_HPP__ */
