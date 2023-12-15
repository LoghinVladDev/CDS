//
// Created by loghin on 22.01.2021.
//

#ifndef CDS_PRIMITIVE_STRING_VIEW_HPP
#define CDS_PRIMITIVE_STRING_VIEW_HPP
#pragma once

#include "string/StringViewBase.hpp"

namespace cds {
using StringView = impl::BaseStringView<char>;
} // namespace cds

#endif // CDS_PRIMITIVE_STRING_VIEW_HPP
