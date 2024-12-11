//
// Created by loghin on 12/11/24.
//

#ifndef CDS_FORMAT_FORMAT_STRING_ITERATOR_HPP
#define CDS_FORMAT_FORMAT_STRING_ITERATOR_HPP
#pragma once

#include <cds/Optional>
#include <cds/StringView>
#include <cds/Union>
#include <cds/exception/FormatException>
#include <cds/iterator/Sentinel>

#include "FormatStringToken.hpp"

namespace cds {
namespace impl {
namespace fmt {
using iterator::Sentinel;

enum class FormatStringIteratorState {
  ReadingLiteral, ReadingFormat, ReadingFormatExplicitArgumentIndex, ReadLeftBrace, ReadRightBrace
};

template <typename C, typename U> class FormatStringIterator {
  using SV = BaseStringView<C, U>;
  using I = typename SV::ConstIterator;
  using T = FormatStringToken<C, U>;
  using S = FormatStringIteratorState;

  using ST = typename U::Traits;

public:
  CDS_ATTR(constexpr(14)) FormatStringIterator(I begin, I end) CDS_ATTR(noexcept(false)) : _b{begin}, _e{end} {
    acquireNextToken();
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto hasToken() const noexcept -> bool {
    return static_cast<bool>(_token);
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto operator*() const noexcept -> Union<SV, T> const& {
    assert(hasToken() && "Unexpected valueless union, previous call of acquireNextToken failed");
    return *_token;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto operator->() const noexcept -> Union<SV, T> const* {
    assert(hasToken() && "Unexpected valueless union, previous call of acquireNextToken failed");
    return &*_token;
  }

  CDS_ATTR(constexpr(14)) auto operator++() CDS_ATTR(noexcept(false)) -> FormatStringIterator& {
    acquireNextToken();
    return *this;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator==(Sentinel) const noexcept -> bool {
    return !hasToken();
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator!=(Sentinel) const noexcept -> bool {
    return hasToken();
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto usesExplicitArgumentIndexing() const noexcept -> bool {
    return _usingExplicitArgIndices;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto usesImplicitArgumentIndexing() const noexcept -> bool {
    return _usingImplicitArgIndices;
  }

private:
  CDS_ATTR(constexpr(14)) auto acquireNextToken() CDS_ATTR(noexcept(false)) -> void {
    _token = nullopt;
    Size bracketCount{1};
    Optional<Size> explicitArgumentIndex{nullopt};

    for (auto it = _b; it != _e; ++it) {
      auto const value = *it;
      switch (_state) {
        case S::ReadingLiteral: {
          if (value == static_cast<C>('{')) {
            _state = S::ReadLeftBrace;
          } else if (value == static_cast<C>('}')) {
            _state = S::ReadRightBrace;
          }
          break;
        }

        case S::ReadLeftBrace: {
          if (value == static_cast<C>('{')) {
            _state = S::ReadingLiteral;
            break;
          }
          _state = S::ReadingFormatExplicitArgumentIndex;
          _token = SV{&*_b, it - _b - 1};
          _b = it;
          return;
        }

        case S::ReadRightBrace: {
          if (value != static_cast<C>('}')) {
            throw FormatException("Right brace encountered without an open left brace");
          }

          _state = S::ReadingLiteral;
          break;
        }

        case S::ReadingFormatExplicitArgumentIndex: {
          if (ST::isDigit(value)) {
            break;
          }

          C const* afterNumber = nullptr;
          Size argIdx = 0u;
          auto readInt = U::readInt(&*_b, _e - _b, &afterNumber, &argIdx, 10);
          assert(readInt || &*_b == afterNumber && "If no number read, and something was parsed, error in 'readInt'");
          if (readInt && &*_b != afterNumber) {
            explicitArgumentIndex = argIdx;
          }
          _b = it;
          _state = S::ReadingFormat;
          CDS_ATTR(fallthrough);
        }

        case S::ReadingFormat: {
          if (value == static_cast<C>('{')) {
            ++bracketCount;
            break;
          }

          if (value == static_cast<C>(':') && bracketCount == 1) {
            _b = it + 1;
            break;
          }

          if (value != static_cast<C>('}')) {
            break;
          }

          assert(bracketCount != 0u && "Undefined behavior.");
          --bracketCount;
          if (bracketCount != 0) {
            break;
          }

          Size argumentIndex = 0u;
          if (explicitArgumentIndex) {
            argumentIndex = *explicitArgumentIndex;
            _usingExplicitArgIndices = true;
          } else {
            argumentIndex = _implicitArgIdx++;
            _usingImplicitArgIndices = true;
          }

          if (_usingImplicitArgIndices && _usingExplicitArgIndices) {
            throw FormatException("Explicit argument indexing requires all arguments to be indexed");
          }

          _token = T{SV{&*_b, it - _b}, argumentIndex};
          _state = S::ReadingLiteral;
          _b = it + 1;
          return;
        }

        default: {
          assert(false && "Unhandled 'FormatStringIteratorState'");
          unreachable();
        }
      }
    }

    if (_b != _e) {
      auto const asStr = SV{&*_b, _e - _b};
      if (asStr.length() > 0 && _state == S::ReadRightBrace && asStr.back() == static_cast<C>('}')) {
        throw FormatException("Right brace encountered without an open left brace");
      }
      _token = asStr;
      _b = _e;
    }
  }

  I _b;
  I _e;

  S _state{S::ReadingLiteral};
  Optional<Union<SV, T>> _token{};
  Size _implicitArgIdx{0u};
  bool _usingImplicitArgIndices{false};
  bool _usingExplicitArgIndices{false};
};
} // namespace fmt
} // namespace impl
} // namespace cds

#endif // #ifndef CDS_FORMAT_FORMAT_STRING_ITERATOR_HPP
