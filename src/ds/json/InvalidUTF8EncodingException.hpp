//
// Created by loghin on 7/21/25.
//

#ifndef CDS_DS_JSON_INVALID_UTF8_ENCODING_EXCEPTION_HPP
#define CDS_DS_JSON_INVALID_UTF8_ENCODING_EXCEPTION_HPP
#pragma once

#include <cds/String>
#include <cds/exception/RuntimeException>

namespace cds {
namespace json {
namespace impl {
class InvalidUTF8EncodingException : public RuntimeException {
public:
  InvalidUTF8EncodingException() : RuntimeException{String{"Invalid UTF-8 encoding "}} {}
};
} // namespace impl

using impl::InvalidUTF8EncodingException;
} // namespace json
} // namespace cds

#endif // #ifndef CDS_DS_JSON_INVALID_UTF8_ENCODING_EXCEPTION_HPP
