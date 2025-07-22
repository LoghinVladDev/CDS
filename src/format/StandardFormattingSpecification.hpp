//
// Created by loghin on 12/11/24.
//

#ifndef CDS_FORMAT_STANDARD_FORMAT_SPECIFICATION_HPP
#define CDS_FORMAT_STANDARD_FORMAT_SPECIFICATION_HPP
#pragma once

#include "StandardFormattingSpecificationComponents.hpp"

#include <cds/functional/Invoke>
#include <cds/iterator/BackInserterIterator>

namespace cds {
namespace impl {
namespace fmt {
using iterator::BackInserterIterator;
using iterator::impl::BackInserterIteratorAccess;

using meta::IsSame;
using meta::IsSigned;
using meta::IsUnsigned;

namespace fn = functional;

template <typename T, typename C> struct StandardFormatter :
    FormatFillAlignComponent<C>,
    FormatNumberComponent<C>,
    FormatWidthComponent<C>,
    FormatTypeComponent<T, C> {
  using FormatFillAlignComponent<C>::parseFillAlign;
  using FormatFillAlignComponent<C>::formatFillAlign;
  using FormatFillAlignComponent<C>::fillAlignSpecification;
  using FormatNumberComponent<C>::parseNumber;
  using FormatNumberComponent<C>::numberSpecification;
  using FormatWidthComponent<C>::parseWidth;
  using FormatWidthComponent<C>::widthSpecification;
  using FormatTypeComponent<T, C>::parseType;
  using FormatTypeComponent<T, C>::typeFlags;
  using ST = StringTraits<C>;
  using SU = StringUtils<C, ST>;

  CDS_ATTR(constexpr(11)) StandardFormatter() noexcept :
      FormatTypeComponent<T, C>{DefaultTypeFormatFlags<T>::value} {}

  template <typename Ctx> CDS_ATTR(2(nodiscard, constexpr(14))) auto parse(Ctx& ctx) CDS_ATTR(noexcept(false))
      -> typename Ctx::Iterator {
    auto end = ctx.end();
    auto it = parseType(parseWidth(parseNumber(parseFillAlign(ctx.begin(), end), end), end), end);
    if (it == ctx.end()) {
      return it;
    }

    throw FormatException("Extraneous characters in format string");
  }

  template <typename T0, typename Ctx> CDS_ATTR(2(nodiscard, constexpr(20)))
  auto formatChar(T0 value, Ctx& ctx) const CDS_ATTR(noexcept(false)) -> typename Ctx::Iterator {
    auto const maybeRequestedWidth = widthSpecification.width.transform(&FormatSizeSpecification::size).getOr(nullopt);
    auto const alternate = numberSpecification.alternate;
    if (static_cast<Size>(value) >= static_cast<Size>(limits::MaxOf<C>::value)) {
      throw FormatException("Value not representable in current CharType");
    }

    if (0 != (typeFlags & FormatTypeFlagBits::Escaped)) {
      auto escaped = true;
      if (value == static_cast<C>('\t')) {
        value = static_cast<C>('t');
      } else if (value == static_cast<C>('\n')) {
        value = static_cast<C>('n');
      } else if (value == static_cast<C>('\r')) {
        value = static_cast<C>('r');
      } else if (value == static_cast<C>('\f')) {
        value = static_cast<C>('f');
      } else if (value == static_cast<C>('\'') || value == static_cast<C>('\\')) {
        // nothing changes
      } else {
        escaped = false;
      }
      // TODO: unicode
      auto const len = 1u
                       + (escaped ? 1u : 0u)
                       + (alternate ? 2u : 0u);
      return formatFillAlign(maybeRequestedWidth, ctx.out(), static_cast<C>(value), len,
          [escaped, alternate](C value0, BackInserterIterator<BaseString<C, SU>> out0) {
            if (alternate) {
              out0 = static_cast<C>('\'');
            }
            if (escaped) {
              out0 = static_cast<C>('\\');
            }
            out0 = value0;
            if (alternate) {
              out0 = static_cast<C>('\'');
            }
            return out0;
          });
    }
    auto const len = 1u + (alternate ? 2u : 0u);
    return formatFillAlign(maybeRequestedWidth, ctx.out(), static_cast<C>(value), len,
        [alternate](C value0, BackInserterIterator<BaseString<C, SU>> out0) {
          if (alternate) {
            out0 = static_cast<C>('\'');
          }
          out0 = value0;
          if (alternate) {
            out0 = static_cast<C>('\'');
          }
          return out0;
        });
  }

  template <typename Ctx, typename U = SU> CDS_ATTR(2(nodiscard, constexpr(20)))
  auto formatString(BaseStringView<C, U> value, Ctx& ctx) const CDS_ATTR(noexcept(false)) -> typename Ctx::Iterator {
    auto const maybeRequestedWidth = widthSpecification.width.transform(&FormatSizeSpecification::size).getOr(nullopt);
    auto const alternate = numberSpecification.alternate;
    if (0 != (typeFlags & FormatTypeFlagBits::Escaped)) {
      auto constexpr expectedEscapeCharsAverage = 4u;
      BaseString<C, U> escapedValue;
      if (alternate) {
        escapedValue += static_cast<C>('"');
      }
      escapedValue.reserve(value.length() + expectedEscapeCharsAverage);
      for (auto chr : value) {
        auto escaped = true;
        if (chr == static_cast<C>('\t')) {
          chr = static_cast<C>('t');
        } else if (chr == static_cast<C>('\n')) {
          chr = static_cast<C>('n');
        } else if (chr == static_cast<C>('\r')) {
          chr = static_cast<C>('r');
        } else if (chr == static_cast<C>('\f')) {
          chr = static_cast<C>('f');
        } else if (chr == static_cast<C>('"') || chr == static_cast<C>('\\')) {
          // nothing changes
        } else {
          escaped = false;
        }
        if (escaped) {
          escapedValue += static_cast<C>('\\');
        }
        // TODO: unicode
        escapedValue += chr;
      }
      if (alternate) {
        escapedValue += static_cast<C>('"');
      }
      return formatFillAlign(maybeRequestedWidth, ctx.out(), escapedValue, escapedValue.size(),
          [](BaseString<C, U> const& value0, BackInserterIterator<BaseString<C, SU>> out) {
            return out = value0;
          });
    }
    return formatFillAlign(maybeRequestedWidth, ctx.out(), value, value.length() + (alternate ? 2u : 0u),
        [alternate](BaseStringView<C, U> const& value0, BackInserterIterator<BaseString<C, SU>> out0) {
          if (alternate) {
            out0 = static_cast<C>('"');
          }
          out0 = value0;
          if (alternate) {
            out0 = static_cast<C>('"');
          }
          return out0;
        });
  }

  template <typename T0, typename Ctx, EnableIf<IsSigned<T0>> = 0> CDS_ATTR(2(nodiscard, constexpr(20)))
  auto formatInteger(T0 value, Ctx& ctx) const CDS_ATTR(noexcept(false)) -> typename Ctx::Iterator {
    using U = UnsignedEquivalent<T0>;
    auto out = ctx.out();
    auto const maybeRequestedWidth = widthSpecification.width.transform(&FormatSizeSpecification::size).getOr(nullopt);
    auto const neg = value < 0;
    auto const uns = neg ? static_cast<U>(~value) : static_cast<U>(value);
    U8 const base = 0u != (typeFlags & FormatTypeFlagBits::Decimal)
                    ? 10u : 0u != (typeFlags & FormatTypeFlagBits::Hex)
                    ? 16u : 0u != (typeFlags & FormatTypeFlagBits::Binary)
                    ? 2u : 8u;
    assert(base != 8u ? true : 0u != (typeFlags & FormatTypeFlagBits::Octal) && "Undefined behavior");
    auto const ulen = SU::intLength(uns, base);
    auto const len = ulen
                     + (!neg && numberSpecification.sign == FormatNumberSignType::Negative ? 0u : 1u)
                     + ((base == 2u || base == 16u) && numberSpecification.alternate ? 2u : 0u)
                     + (base == 8u && numberSpecification.alternate ? 1u : 0u);
    auto const leadingPotential = static_cast<SSize>(maybeRequestedWidth.getOr(0)) - len;
    auto writeIt = [this, ulen, neg, base, leadingPotential]
        (T value0, BackInserterIterator<BaseString<C, SU>> out0, bool leadingZeroes = false) {
      if (neg) {
        out0 = static_cast<C>('-');
      } else if (numberSpecification.sign == FormatNumberSignType::PositiveNegative) {
        out0 = static_cast<C>('+');
      } else if (numberSpecification.sign == FormatNumberSignType::SpaceNegative) {
        out0 = static_cast<C>(' ');
      }
      auto upper = 0 != (typeFlags & FormatTypeFlagBits::Uppercase);
      if (numberSpecification.alternate && 0 != (typeFlags & (FormatTypeFlagBits::Binary
                                                              | FormatTypeFlagBits::Octal
                                                              | FormatTypeFlagBits::Hex))) {
        if (0 != (typeFlags & FormatTypeFlagBits::Hex)) {
          out0 = static_cast<C>('0');
          out0 = upper ? static_cast<C>('X') : static_cast<C>('x');
        } else if (0 != (typeFlags & FormatTypeFlagBits::Binary)) {
          out0 = static_cast<C>('0');
          out0 = upper ? static_cast<C>('B') : static_cast<C>('b');
        } else {
          out0 = static_cast<C>('0');
        }
      }
      if (leadingZeroes && leadingPotential > 0) {
        out0 = impl::fillN(out0, static_cast<Size>(leadingPotential), static_cast<C>('0'));
      }

      auto& str = BackInserterIteratorAccess{}(out0);
      auto const oldLen = str.length();
      str.resize(str.length() + ulen, '\0');
      ignore = SU::writeInt(value0, ulen, str.data() + oldLen, base, upper);
      return out0;
    };
    if (!fillAlignSpecification.align && maybeRequestedWidth) {
      if (numberSpecification.leadingZeroes) {
        return writeIt(value, out, true);
      }
    }
    return formatFillAlign(maybeRequestedWidth, out, value, len, writeIt);
  }

  template <typename T0, typename Ctx, EnableIf<IsUnsigned<T0>> = 0> CDS_ATTR(2(nodiscard, constexpr(20)))
  auto formatInteger(T0 value, Ctx& ctx) const CDS_ATTR(noexcept(false)) -> typename Ctx::Iterator {
    auto out = ctx.out();
    auto const maybeRequestedWidth = widthSpecification.width.transform(&FormatSizeSpecification::size).getOr(nullopt);
    U8 const base = 0u != (typeFlags & FormatTypeFlagBits::Decimal)
                    ? 10u : 0u != (typeFlags & FormatTypeFlagBits::Hex)
                    ? 16u : 0u != (typeFlags & FormatTypeFlagBits::Binary)
                    ? 2u : 8u;
    assert(base != 8u ? true : 0u != (typeFlags & FormatTypeFlagBits::Octal) && "Undefined behavior");
    auto ulen = SU::intLength(value, base);
    auto len = ulen
               + (numberSpecification.sign == FormatNumberSignType::Negative ? 0u : 1u)
               + ((base == 2u || base == 16u) && numberSpecification.alternate ? 2u : 0u)
               + (base == 8u && numberSpecification.alternate ? 1u : 0u);
    auto const leadingPotential = static_cast<SSize>(maybeRequestedWidth.getOr(0)) - len;
    auto writeIt = [this, ulen, base, leadingPotential]
        (T value0, BackInserterIterator<BaseString<C, SU>> out0, bool leadingZeroes = false) {
      if (numberSpecification.sign == FormatNumberSignType::PositiveNegative) {
        out0 = static_cast<C>('+');
      } else if (numberSpecification.sign == FormatNumberSignType::SpaceNegative) {
        out0 = static_cast<C>(' ');
      }
      auto upper = 0 != (typeFlags & FormatTypeFlagBits::Uppercase);
      if (numberSpecification.alternate && 0 != (typeFlags & (FormatTypeFlagBits::Binary
                                                              | FormatTypeFlagBits::Octal
                                                              | FormatTypeFlagBits::Hex))) {
        if (0 != (typeFlags & FormatTypeFlagBits::Hex)) {
          out0 = static_cast<C>('0');
          out0 = upper ? static_cast<C>('X') : static_cast<C>('x');
        } else if (0 != (typeFlags & FormatTypeFlagBits::Binary)) {
          out0 = static_cast<C>('0');
          out0 = upper ? static_cast<C>('B') : static_cast<C>('b');
        } else {
          out0 = static_cast<C>('0');
        }
      }
      if (leadingZeroes && leadingPotential > 0) {
        out0 = impl::fillN(out0, static_cast<Size>(leadingPotential), static_cast<C>('0'));
      }
      auto& str = BackInserterIteratorAccess{}(out0);
      auto const oldLen = str.length();
      str.resize(oldLen + ulen, '\0');
      ignore = SU::writeInt(value0, ulen, str.data() + oldLen, base, upper);
      return out0;
    };
    if (!fillAlignSpecification.align && maybeRequestedWidth) {
      if (numberSpecification.leadingZeroes) {
        return writeIt(value, out, true);
      }
    }
    return formatFillAlign(maybeRequestedWidth, out, value, len, writeIt);
  }

  template <typename T0, typename Ctx> CDS_ATTR(nodiscard) auto formatPointer(T0 const* ptr, Ctx& ctx)
  const CDS_ATTR(noexcept(false)) -> typename Ctx::Iterator {
    auto const maybeRequestedWidth = widthSpecification.width.transform(&FormatSizeSpecification::size).getOr(nullopt);
    auto const reinterpretedValue = reinterpret_cast<Address>(ptr);
    auto const upper = 0 != (typeFlags & FormatTypeFlagBits::Uppercase);
    auto const length = SU::intLength(reinterpretedValue, 16);
    return formatFillAlign(
        maybeRequestedWidth, ctx.out(), reinterpretedValue, length + 2u,
        [upper, length](Address value0, BackInserterIterator<BaseString<C, SU>> out0) {
          out0 = static_cast<C>('0');
          out0 = upper ? static_cast<C>('X') : static_cast<C>('x');
          auto& str = BackInserterIteratorAccess{}(out0);
          auto const oldLen = str.length();
          str.resize(oldLen + length, '\0');
          ignore = SU::writeInt(value0, length, str.data() + oldLen, 16, upper);
          return out0;
        }
    );
  }

  template <typename T0, typename C0 = C, EnableIf<IsSame<C0, char>> = 0> CDS_ATTR(nodiscard)
  auto obtainFloatingFromOldFormat(T0 value, BaseString<C0, SU> const& formatString) const CDS_ATTR(noexcept(false))
  -> BaseString<C0, SU> {
    auto constexpr threshold = 128u;
    char smallBuf[threshold];
    auto const actualLength = static_cast<Size>(std::snprintf(smallBuf, threshold, formatString.data(), value));
    assert(actualLength < threshold && "smallBuf size too small for resulting char");
    return BaseString<C0, SU>(smallBuf, actualLength);
  }

  template <typename T0, typename C0 = C, EnableIf<IsSame<C0, wchar_t>> = 0> CDS_ATTR(nodiscard)
  auto obtainFloatingFromOldFormat(T0 value, BaseString<C0, SU> const& formatString) const CDS_ATTR(noexcept(false))
  -> BaseString<C0, SU> {
    auto constexpr threshold = 128u;
    wchar_t smallBuf[threshold];
    auto const actualLength = static_cast<Size>(std::swprintf(smallBuf, threshold, formatString.data(), value));
    assert(actualLength < threshold && "smallBuf size too small for resulting char");
    return BaseString<C0, SU>(smallBuf, actualLength);
  }

  template <typename T0, typename Ctx> CDS_ATTR(nodiscard) auto formatFloating(T0 value, Ctx& ctx)
  const CDS_ATTR(noexcept(false)) -> typename Ctx::Iterator {
    auto const maybeRequestedWidth = widthSpecification.width.transform(&FormatSizeSpecification::size).getOr(nullopt);

    BaseString<C, SU> equivalentFormatString;
    equivalentFormatString += static_cast<C>('%');
    if (numberSpecification.sign == FormatNumberSignType::PositiveNegative) {
      equivalentFormatString += static_cast<C>('+');
    } else if (numberSpecification.sign == FormatNumberSignType::SpaceNegative) {
      equivalentFormatString += static_cast<C>(' ');
    }

    if (numberSpecification.alternate) {
      equivalentFormatString += static_cast<C>('#');
    }
    if (numberSpecification.leadingZeroes) {
      equivalentFormatString += static_cast<C>('0');
    }

    auto const maybeRequestedPrecision
        = widthSpecification.precision.transform(&FormatSizeSpecification::size).getOr(nullopt);
    if (maybeRequestedPrecision) {
      equivalentFormatString += static_cast<C>('.');
      equivalentFormatString += *maybeRequestedPrecision;
    }

    if (IsSame<T, long double>::value) {
      equivalentFormatString += static_cast<C>('L');
    }

    if (typeFlags == static_cast<FormatTypeFlags>(FormatTypeFlagBits::Hex)) {
      equivalentFormatString += static_cast<C>('a');
    } else if (typeFlags == (FormatTypeFlagBits::Uppercase | FormatTypeFlagBits::Hex)) {
      equivalentFormatString += static_cast<C>('A');
    } else if (typeFlags == static_cast<FormatTypeFlags>(FormatTypeFlagBits::Scientific)) {
      equivalentFormatString += static_cast<C>('e');
    } else if (typeFlags == (FormatTypeFlagBits::Uppercase | FormatTypeFlagBits::Scientific)) {
      equivalentFormatString += static_cast<C>('E');
    } else if (typeFlags == static_cast<FormatTypeFlags>(FormatTypeFlagBits::Fixed)) {
      equivalentFormatString += static_cast<C>('f');
    } else if (typeFlags == (FormatTypeFlagBits::Uppercase | FormatTypeFlagBits::Fixed)) {
      equivalentFormatString += static_cast<C>('F');
    } else if (typeFlags == static_cast<FormatTypeFlags>(FormatTypeFlagBits::General)) {
      equivalentFormatString += static_cast<C>('g');
    } else if (typeFlags == (FormatTypeFlagBits::Uppercase | FormatTypeFlagBits::General)) {
      equivalentFormatString += static_cast<C>('G');
    } else {
      assert(false && "Unhandled typeFlag combination for given floating point type");
    }

    auto valueAsStr = obtainFloatingFromOldFormat(value, equivalentFormatString);
    return formatFillAlign(
        maybeRequestedWidth, ctx.out(), value, valueAsStr.length(),
        [&valueAsStr](T0 value0, BackInserterIterator<BaseString<C, SU>> out0) {
          ignore = value0;
          return out0 = valueAsStr;
        }
    );
  }
};
} // namespace fmt
} // namespace impl
} // namespace cds

#endif // #ifndef CDS_FORMAT_STANDARD_FORMAT_SPECIFICATION_HPP

