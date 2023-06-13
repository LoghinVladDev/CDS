//
// Created by loghin on 30/11/22.
//

#ifndef __CDS_OUT_OF_MEMORY_EXCEPTION_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_OUT_OF_MEMORY_EXCEPTION_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

#include <CDS/exception/Exception>

namespace cds {
class OutOfMemoryException : public Exception {
public:
    OutOfMemoryException() noexcept = default;
  __CDS_Explicit OutOfMemoryException(std::bad_alloc const& stdExcept) noexcept : _pStdExcept(&stdExcept) {}

  __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto message() const noexcept -> StringView override {
    if (_pStdExcept != nullptr) {
      return _pStdExcept->what();
    }

    return "Out of Heap Memory";
  }

private:
  std::bad_alloc const* _pStdExcept {nullptr};
};
} // namespace cds

namespace cds {
namespace meta {
namespace __impl {
template<>
struct __TypeParseTraits<OutOfMemoryException> {
  constexpr static StringLiteral name = "OutOfMemoryException";
};
} // namespace __impl
} // namespace meta
} // namespace cds

#endif // __CDS_OUT_OF_MEMORY_EXCEPTION_HPP__
