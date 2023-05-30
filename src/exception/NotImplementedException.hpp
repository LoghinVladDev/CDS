//
// Created by loghin on 30/11/22.
//

#ifndef __CDS_NOT_IMPLEMENTED_EXCEPTION_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_NOT_IMPLEMENTED_EXCEPTION_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

#include <CDS/exception/Exception>

namespace cds {
class NotImplementedException : public Exception {
public:
  using Exception::Exception;
  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto message() const noexcept -> StringView override {
    return "Method not implemented";
  }
};

} // namespace cds

namespace cds {
namespace meta {
namespace __impl {
template<>
struct __TypeParseTraits<NotImplementedException> {
  constexpr static StringLiteral name = "NotImplementedException";
};
} // namespace __impl
} // namespace meta
} // namespace cds

#endif // __CDS_NOT_IMPLEMENTED_EXCEPTION_HPP__
