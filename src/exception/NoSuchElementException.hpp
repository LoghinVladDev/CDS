//
// Created by loghin on 6/23/24.
//

#ifndef CDS_NO_SUCH_ELEMENT_EXCEPTION_HPP
#define CDS_NO_SUCH_ELEMENT_EXCEPTION_HPP
#pragma once

#include <cds/exception/RuntimeException>

namespace cds {
class NoSuchElementException : public RuntimeException {
  using String = impl::BaseString<char>;
  using StringView = impl::BaseStringView<char>;
public:
  using RuntimeException::RuntimeException;
  NoSuchElementException() : RuntimeException("No such element exists") {}
};
} // namespace cds

#endif // CDS_NO_SUCH_ELEMENT_EXCEPTION_HPP
