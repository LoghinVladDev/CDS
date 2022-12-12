/*
 * Created by loghin on 30/11/22.
 */

#ifndef __CDS_NOT_IMPLEMENTED_EXCEPTION_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_NOT_IMPLEMENTED_EXCEPTION_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/exception/Exception>

namespace cds {

    class NotImplementedException : public Exception {

    public:
        NotImplementedException () noexcept;

    public:
        NotImplementedException (
                NotImplementedException const & exception
        ) noexcept;

    public:
        NotImplementedException (
                NotImplementedException && exception
        ) noexcept;

    public:
        explicit NotImplementedException (
                StringView message
        ) noexcept;

    public:
        ~NotImplementedException() noexcept override = default;
    };

} /* namespace cds */

#include "exception/impl/NotImplementedException.hpp"

__CDS_Meta_RegisterParseType(NotImplementedException)

#endif /* __CDS_NOT_IMPLEMENTED_EXCEPTION_HPP__ */
