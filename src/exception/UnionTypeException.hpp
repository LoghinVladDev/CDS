//
// Created by loghin on 6/17/24.
//

#ifndef CDS_TYPE_EXCEPTION_HPP
#define CDS_TYPE_EXCEPTION_HPP

#include <cds/exception/RuntimeException>

namespace cds {
class UnionTypeException : public RuntimeException {
  using String = impl::BaseString<char>;
  using StringView = impl::BaseStringView<char>;
public:
  using RuntimeException::RuntimeException;
  UnionTypeException() noexcept = delete;
  explicit UnionTypeException(String message) noexcept : RuntimeException{cds::move(message)} {}
  template <typename From, typename To> static auto of() noexcept -> UnionTypeException {
    auto message = impl::BaseString<char>();
    message.reserve(128u);
    return UnionTypeException {
        cds::move(message)
        + "Union Type Exception: '"
        + StringView{meta::TypeInfo<To>::name}
        + "' is not the active Union member. Actual: '"
        + StringView{meta::TypeInfo<From>::name}
        + "'"
    };
  }
};
} // namespace cds

#endif // #ifndef CDS_TYPE_EXCEPTION_HPP
