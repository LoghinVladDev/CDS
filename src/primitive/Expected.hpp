//
// Created by loghin on 7/28/25.
//

#ifndef CDS_PRIMITIVE_EXPECTED_HPP
#define CDS_PRIMITIVE_EXPECTED_HPP
#pragma once

#include "expected/ContainingError.hpp"
#include "expected/Unexpected.hpp"
#include "expected/ExpectedValueException.hpp"
#include "expected/Expected.hpp"

namespace cds {
using impl::Expected;
using impl::ExpectedValueException;
using impl::Unexpect;
using impl::Unexpected;

using impl::unexpectedOf;
} // namespace cds

#endif // #ifndef CDS_PRIMITIVE_EXPECTED_HPP
