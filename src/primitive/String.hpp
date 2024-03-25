//
// Created by loghin on 22.01.2021.
//

#ifndef CDS_PRIMITIVE_STRING_HPP
#define CDS_PRIMITIVE_STRING_HPP
#pragma once

#include "string/StringBase.hpp"

namespace cds {
using String = impl::BaseString<char>;
} // namespace cds

#endif // CDS_PRIMITIVE_STRING_HPP
