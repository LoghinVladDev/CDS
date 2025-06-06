//
// Created by loghin on 12/11/24.
//

#ifndef CDS_FORMAT_STANDARD_FORMAT_SPECIFICATION_COMPONENTS_HPP
#define CDS_FORMAT_STANDARD_FORMAT_SPECIFICATION_COMPONENTS_HPP
#pragma once

#include <cds/Optional>
#include <cds/String>
#include <cds/Tuple>
#include <cds/exception/FormatException>
#include <cds/functional/Invoke>
#include <cds/iterator/BackInserterIterator>

namespace cds {
namespace impl {
namespace fmt {
using iterator::BackInserterIterator;

using meta::And;
using meta::False;
using meta::IsFloating;
using meta::IsIntegral;
using meta::IsSame;
using meta::IsSigned;
using meta::IsUnsigned;
using meta::Not;
using meta::Or;
using meta::True;

namespace fn = functional;

enum class FormatAlignType : U8 {Leading, Centre, Trailing};
enum class FormatNumberSignType : U8 {PositiveNegative, Negative, SpaceNegative};
enum class FormatTypeFlagBits : U16 {
  Binary = 0x0001u,
  Character = 0x0002u,
  Decimal = 0x0004u,
  Octal = 0x0008u,
  Hex = 0x0010u,
  Uppercase = 0x0020u,
  Escaped = 0x0040u,
  Scientific = 0x0080u,
  Fixed = 0x0100u,
  General = 0x0200u,
  Pointer = 0x0400u,
  String = 0x0800u,
};

using FormatTypeFlags = U16;

template <typename C> struct FormatFillAlignSpecification {
  CDS_ATTR(constexpr(11)) FormatFillAlignSpecification(Optional<FormatAlignType> align0, C fillChar0) noexcept :
      align{align0}, fillChar{fillChar0} {}
  Optional<FormatAlignType> align;
  C fillChar;
};

struct FormatNumberSpecification {
  CDS_ATTR(2(explicit, constexpr(11))) FormatNumberSpecification(
      FormatNumberSignType sign0 = FormatNumberSignType::Negative, bool alt0 = false, bool leading0 = false
  ) noexcept : sign{sign0}, alternate{alt0}, leadingZeroes{leading0} {}
  FormatNumberSignType sign;
  bool alternate;
  bool leadingZeroes;
};

struct FormatSizeSpecification {
  CDS_ATTR(2(explicit, constexpr(11))) FormatSizeSpecification(
      Optional<Size> const& size0 = nullopt, Optional<Size> const& explicitIdx0 = nullopt
  ) noexcept : size{size0}, explicitIdx{explicitIdx0} {}
  Optional<Size> size;
  Optional<Size> explicitIdx;
};

struct FormatWidthOnlySpecification {
  CDS_ATTR(2(explicit, constexpr(11))) FormatWidthOnlySpecification(
      Optional<FormatSizeSpecification> const& width0 = nullopt
  ) noexcept : width{width0} {}
  Optional<FormatSizeSpecification> width;
};

struct FormatWidthSpecification {
  CDS_ATTR(2(explicit, constexpr(11))) FormatWidthSpecification(
      Optional<FormatSizeSpecification> const& width0 = nullopt,
      Optional<FormatSizeSpecification> const& precision0 = nullopt
  ) noexcept : width{width0}, precision{precision0} {}
  Optional<FormatSizeSpecification> width;
  Optional<FormatSizeSpecification> precision;
};

template <typename T, typename C, typename = typename And<
    Not<IsSame<T, C>>, Not<IsSame<T, bool>>,
    Or<IsSigned<T>, IsUnsigned<T>, IsFloating<T>>
>::Type> struct FormatDefaultAlign;

template <typename T, typename C> struct FormatDefaultAlign<T, C, True> {
  static constexpr FormatAlignType value = FormatAlignType::Trailing;
};

template <typename T, typename C> struct FormatDefaultAlign<T, C, False> {
  static constexpr FormatAlignType value = FormatAlignType::Leading;
};

// ODR before C++17
template <typename T, typename C> FormatAlignType const FormatDefaultAlign<T, C, True>::value;
template <typename T, typename C> FormatAlignType const FormatDefaultAlign<T, C, False>::value;

struct FormatIntegerTypeSpecification {
  template <typename C> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(Optional<C> typeChar) -> FormatTypeFlags {
    if (!typeChar) {
      return static_cast<FormatTypeFlags>(FormatTypeFlagBits::Decimal);
    }

    switch (*typeChar) {
      case static_cast<C>('b'): return static_cast<FormatTypeFlags>(FormatTypeFlagBits::Binary);
      case static_cast<C>('B'): return static_cast<FormatTypeFlags>(FormatTypeFlagBits::Binary)
                                     | static_cast<FormatTypeFlags>(FormatTypeFlagBits::Uppercase);
      case static_cast<C>('c'): return static_cast<FormatTypeFlags>(FormatTypeFlagBits::Character);
      case static_cast<C>('d'): return static_cast<FormatTypeFlags>(FormatTypeFlagBits::Decimal);
      case static_cast<C>('o'): return static_cast<FormatTypeFlags>(FormatTypeFlagBits::Octal);
      case static_cast<C>('x'): return static_cast<FormatTypeFlags>(FormatTypeFlagBits::Hex);
      case static_cast<C>('X'): return static_cast<FormatTypeFlags>(FormatTypeFlagBits::Hex)
                                     | static_cast<FormatTypeFlags>(FormatTypeFlagBits::Uppercase);
      default:
        throw FormatException("Presentation type specifier is invalid");
    }
  }
};

template <typename T, typename C, typename = typename IsIntegral<T>::Type> struct FormatIntegralTypeSpecification;
template <typename T, typename C> struct FormatIntegralTypeSpecification<T, C, True> :
    FormatIntegerTypeSpecification {};

template <typename C> struct FormatIntegralTypeSpecification<C, C, True> {
  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(Optional<C> typeChar) -> FormatTypeFlags {
    if (!typeChar) {
      return static_cast<FormatTypeFlags>(FormatTypeFlagBits::Character);
    }
    if (*typeChar == static_cast<C>('?')) {
      return static_cast<FormatTypeFlags>(FormatTypeFlagBits::Character)
             | static_cast<FormatTypeFlags>(FormatTypeFlagBits::Escaped);
    }
    return FormatIntegerTypeSpecification{}(typeChar);
  }
};

template <typename C> struct FormatIntegralTypeSpecification<bool, C, True> {
  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(Optional<C> typeChar) -> FormatTypeFlags {
    if (!typeChar || *typeChar == static_cast<C>('s')) {
      return static_cast<FormatTypeFlags>(FormatTypeFlagBits::String);
    }
    if (*typeChar == static_cast<C>('c')) {
      throw FormatException("Presentation type specifier is invalid");
    }
    return FormatIntegerTypeSpecification{}(typeChar);
  }
};

template <typename C> struct FormatStringTypeSpecification {
  constexpr auto operator()(Optional<C> typeChar) -> FormatTypeFlags {
    if (!typeChar || *typeChar == static_cast<C>('s')) {
      return static_cast<FormatTypeFlags>(FormatTypeFlagBits::String);
    }
    if (*typeChar == static_cast<C>('?')) {
      return static_cast<FormatTypeFlags>(FormatTypeFlagBits::String)
           | static_cast<FormatTypeFlags>(FormatTypeFlagBits::Escaped);
    }
    throw FormatException("Presentation type specifier is invalid");
  }
};

template <
    typename T, typename C,
    typename = typename IsIntegral<T>::Type,
    typename = typename IsFloating<T>::Type,
    typename = typename IsString<T>::Type
> struct FormatTypeSpecification;

template <typename T, typename C> struct FormatTypeSpecification<T, C, True, False, False> :
    FormatIntegralTypeSpecification<T, C> {};

template <typename T, typename C> struct FormatTypeSpecification<T, C, False, True, False> {
  constexpr auto operator()(Optional<C> typeChar) -> FormatTypeFlags {
    if (!typeChar) {
      return static_cast<FormatTypeFlags>(FormatTypeFlagBits::General);
    }

    switch (*typeChar) {
      case static_cast<C>('a'): return static_cast<FormatTypeFlags>(FormatTypeFlagBits::Hex);
      case static_cast<C>('A'): return static_cast<FormatTypeFlags>(FormatTypeFlagBits::Hex)
                                     | static_cast<FormatTypeFlags>(FormatTypeFlagBits::Uppercase);
      case static_cast<C>('e'): return static_cast<FormatTypeFlags>(FormatTypeFlagBits::Scientific);
      case static_cast<C>('E'): return static_cast<FormatTypeFlags>(FormatTypeFlagBits::Scientific)
                                     | static_cast<FormatTypeFlags>(FormatTypeFlagBits::Uppercase);
      case static_cast<C>('f'): return static_cast<FormatTypeFlags>(FormatTypeFlagBits::Fixed);
      case static_cast<C>('F'): return static_cast<FormatTypeFlags>(FormatTypeFlagBits::Fixed)
                                     | static_cast<FormatTypeFlags>(FormatTypeFlagBits::Uppercase);
      case static_cast<C>('g'): return static_cast<FormatTypeFlags>(FormatTypeFlagBits::General);
      case static_cast<C>('G'): return static_cast<FormatTypeFlags>(FormatTypeFlagBits::General)
                                     | static_cast<FormatTypeFlags>(FormatTypeFlagBits::Uppercase);
      default:
        throw FormatException("Presentation type specifier is invalid");
    }
  }
};

template <typename T, typename C> struct FormatTypeSpecification<T, C, False, False, True> : 
    FormatStringTypeSpecification<C> {};

template <typename C> struct FormatTypeSpecification<C*, C, False, False, True> : FormatStringTypeSpecification<C> {};
template <typename C> struct FormatTypeSpecification<C const*, C, False, False, True> : 
    FormatStringTypeSpecification<C> {};

template <typename T, typename C> struct FormatTypeSpecification<T*, C, False, False, False> {
  constexpr auto operator()(Optional<C> typeChar) -> FormatTypeFlags {
    if (!typeChar || *typeChar == static_cast<C>('p')) {
      return static_cast<FormatTypeFlags>(FormatTypeFlagBits::Pointer);
    }
    if (*typeChar == static_cast<C>('P')) {
      return static_cast<FormatTypeFlags>(FormatTypeFlagBits::Pointer)
           | static_cast<FormatTypeFlags>(FormatTypeFlagBits::Uppercase);
    }
    throw FormatException("Presentation type specifier is invalid");
  }
};

CDS_ATTR(2(nodiscard, constexpr(11))) auto operator|(FormatTypeFlagBits const l, FormatTypeFlagBits const r) noexcept
    -> FormatTypeFlags {
  return static_cast<FormatTypeFlags>(l) | static_cast<FormatTypeFlags>(r);
}

CDS_ATTR(2(nodiscard, constexpr(11))) auto operator|(FormatTypeFlags const l, FormatTypeFlagBits const r) noexcept
    -> FormatTypeFlags {
  return l | static_cast<FormatTypeFlags>(r);
}

CDS_ATTR(2(nodiscard, constexpr(11))) auto operator|(FormatTypeFlagBits const l, FormatTypeFlags const r) noexcept
    -> FormatTypeFlags {
  return static_cast<FormatTypeFlags>(l) | r;
}

CDS_ATTR(2(nodiscard, constexpr(11))) auto operator&(FormatTypeFlagBits const l, FormatTypeFlagBits const r) noexcept
    -> FormatTypeFlags {
  return static_cast<FormatTypeFlags>(l) & static_cast<FormatTypeFlags>(r);
}

CDS_ATTR(2(nodiscard, constexpr(11))) auto operator&(FormatTypeFlags const l, FormatTypeFlagBits const r) noexcept
    -> FormatTypeFlags {
  return l & static_cast<FormatTypeFlags>(r);
}

CDS_ATTR(2(nodiscard, constexpr(11))) auto operator&(FormatTypeFlagBits const l, FormatTypeFlags const r) noexcept
    -> FormatTypeFlags {
  return static_cast<FormatTypeFlags>(l) & r;
}

template <typename C> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator==(
    FormatFillAlignSpecification<C> const& l, FormatFillAlignSpecification<C> const& r
) noexcept -> bool {
  return l.align == r.align
      && l.fillChar == r.fillChar;
}

CDS_ATTR(2(nodiscard, constexpr(11))) auto operator==(
    FormatNumberSpecification const& l, FormatNumberSpecification const& r
) noexcept -> bool {
  return l.sign == r.sign
      && l.alternate == r.alternate
      && l.leadingZeroes == r.leadingZeroes;
}

CDS_ATTR(2(nodiscard, constexpr(11))) auto operator==(
    FormatSizeSpecification const& l, FormatSizeSpecification const& r
) noexcept -> bool {
  return l.size == r.size
      && l.explicitIdx == r.explicitIdx;
}

CDS_ATTR(2(nodiscard, constexpr(11))) auto operator==(
    FormatWidthSpecification const& l, FormatWidthSpecification const& r
) noexcept -> bool {
  return l.width == r.width
      && l.precision == r.precision;
}

template <typename C> CDS_ATTR(2(nodiscard, constexpr(11))) auto formatFillAlignSpecification(C alignChar) noexcept
    -> Optional<FormatAlignType> {
  switch (alignChar) {
    case static_cast<C>('<'): return FormatAlignType::Leading;
    case static_cast<C>('>'): return FormatAlignType::Trailing;
    case static_cast<C>('^'): return FormatAlignType::Centre;
    default:                  return nullopt;
  }
}

template <typename T, typename C> CDS_ATTR(2(nodiscard, constexpr(11)))
auto formatTypeSpecification(Optional<C> typeChar) CDS_ATTR(noexcept(false)) -> FormatTypeFlags {
  return FormatTypeSpecification<T, C>{}(typeChar);
}

template <typename /* T */, typename C, typename I, typename S> CDS_ATTR(2(nodiscard, constexpr(14)))
auto formatParseFillAlign(I it, S end) noexcept -> Tuple<I, FormatFillAlignSpecification<C>> {
  auto fillChar{static_cast<C>(' ')};
  Optional<FormatAlignType> align{nullopt};
  if (it == end) {
    return {it, FormatFillAlignSpecification<C>{align, fillChar}};
  }

  auto maybeExplicitAlign = it + 1;
  if (maybeExplicitAlign != end) {
    auto maybeAlign = formatFillAlignSpecification(*maybeExplicitAlign);
    if (maybeAlign) {
      align = *maybeAlign;
      fillChar = *it;
      it = maybeExplicitAlign + 1;
    } else {
      maybeAlign = formatFillAlignSpecification(*it);
      if (maybeAlign) {
        align = *maybeAlign;
        fillChar = static_cast<C>(' ');
        it = it + 1;
      }
    }
  }

  return {it, FormatFillAlignSpecification<C>{align, fillChar}};
}

template <typename C, typename I, typename S> CDS_ATTR(2(nodiscard, constexpr(14)))
auto formatParseNumber(I it, S end) noexcept -> Tuple<I, FormatNumberSpecification> {
  if (it == end) {
    return {it, FormatNumberSpecification{}};
  }

  auto sign = [](C signChar) {
    switch (signChar) {
      case static_cast<C>('+'): return FormatNumberSignType::PositiveNegative;
      case static_cast<C>(' '): return FormatNumberSignType::SpaceNegative;
      default:                  return FormatNumberSignType::Negative;
    }
  }(*it);

  if ((sign != FormatNumberSignType::Negative || *it == static_cast<C>('-')) && ++it == end) {
    return {it, FormatNumberSpecification{sign}};
  }

  bool alternate = *it == static_cast<C>('#');
  if (alternate && ++it == end) {
    return {it, FormatNumberSpecification{sign, alternate}};
  }

  bool leadingZeroes = *it == static_cast<C>('0');
  return {leadingZeroes ? it + 1 : it, FormatNumberSpecification{sign, alternate, leadingZeroes}};
}

template <typename C, typename I, typename S> CDS_ATTR(2(nodiscard, constexpr(14)))
auto formatParseWidthOrPrecision(I it, S end) CDS_ATTR(noexcept(false)) -> Tuple<I, Optional<FormatSizeSpecification>> {
  using T = StringTraits<C>;
  using U = StringUtils<C, T>;
  Optional<Size> size {nullopt};
  if (T::isDigit(*it)) {
    size.emplace(0);
    C const* afterNumber = nullptr;
    auto res = U::readInt(&*it, end - it, &afterNumber, &*size, 10);
    assert(res && "Unexpected failure in width int parse");
    it = it + (afterNumber - &*it);
    if (it == end) {
      return {it, optionalOf<FormatSizeSpecification>(mv(size), nullopt)};
    }
  }

  if (!size && *it != static_cast<C>('{')) {
    return {it, nullopt};
  }

  Optional<Size> sizeExplicitArgIdx = nullopt;
  if (!size) {
    ++it;
    if (it != end && *it != static_cast<C>('}')) {
      sizeExplicitArgIdx.emplace(0);
      C const* afterNumber = nullptr;
      auto res = U::readInt(&*it, end - it, &afterNumber, &*sizeExplicitArgIdx, 10);
      if (!res) {
        throw FormatException("Nested replacement field with invalid explicit argument index");
      }
      it = it + (afterNumber - &*it);
    }

    if (it == end || *it++ != static_cast<C>('}')) {
      throw FormatException("Nested replacement field in width specifier not terminated");
    }
  }

  return {it, optionalOf<FormatSizeSpecification>(mv(size), mv(sizeExplicitArgIdx))};
}

template <typename C, typename I, typename S> CDS_ATTR(2(nodiscard, constexpr(14))) 
auto formatParseWidthOnly(I it, S end) CDS_ATTR(noexcept(false)) -> Tuple<I, FormatWidthOnlySpecification> {
  if (it == end) {
    return {it, FormatWidthOnlySpecification{}};
  }

  Optional<FormatSizeSpecification> width{};
  cds::tie(it, width) = formatParseWidthOrPrecision<C>(it, end);
  return {it, FormatWidthOnlySpecification{mv(width)}};
}

template <typename C, typename I, typename S> CDS_ATTR(2(nodiscard, constexpr(14)))
auto formatParseWidth(I it, S end) CDS_ATTR(noexcept(false)) -> Tuple<I, FormatWidthSpecification> {
  if (it == end) {
    return {it, FormatWidthSpecification{}};
  }

  Optional<FormatSizeSpecification> width{};
  cds::tie(it, width) = formatParseWidthOrPrecision<C>(it, end);
  if (it == end || *it != static_cast<C>('.')) {
    return {it, FormatWidthSpecification{mv(width)}};
  }

  if (++it == end) {
    throw FormatException("Precision specification not followed by precision");
  }

  Optional<FormatSizeSpecification> precision{};
  cds::tie(it, precision) = formatParseWidthOrPrecision<C>(it, end);
  return {it, FormatWidthSpecification{mv(width), mv(precision)}};
}

template <typename T, typename C, typename I, typename S> CDS_ATTR(2(nodiscard, constexpr(14)))
auto formatParseType(I it, S end) CDS_ATTR(noexcept(false)) -> Tuple<I, FormatTypeFlags> {
  if (it == end) {
    return {it, formatTypeSpecification<T, C>(nullopt)};
  }

  auto type = formatTypeSpecification<T, C>(*it++);
  return {it, type};
}

template <typename T, typename C> struct FormatFillAlignComponent {
  template <typename I, typename S> CDS_ATTR(2(nodiscard, constexpr(14))) 
  auto parseFillAlign(I begin, S end) noexcept -> I {
    cds::tie(begin, fillAlignSpecification) = formatParseFillAlign<T, C>(begin, end);
    return begin;
  }

  template <typename T0, typename I, typename F> CDS_ATTR(2(nodiscard, constexpr(14))) auto formatFillAlign(
      Optional<Size> maybeMinWidth, I out, T0&& obj, Optional<Size> estWidth, F&& fmt) const noexcept -> I {
    if (!maybeMinWidth) {
      return fn::invoke(fwd<F>(fmt), fwd<T0>(obj), out);
    }

    auto const align = fillAlignSpecification.align.getOr(FormatDefaultAlign<RemoveCVRef<T0>, C>::value);
    auto const minWidth = *maybeMinWidth;
    if (estWidth) {
      if (*estWidth >= minWidth) {
        return fn::invoke(fwd<F>(fmt), fwd<T0>(obj), out);
      }
      auto const remaining = minWidth - *estWidth;
      if (align == FormatAlignType::Leading) {
        return fillN(fn::invoke(fwd<F>(fmt), fwd<T0>(obj), out), remaining, fillAlignSpecification.fillChar);
      }

      if (align == FormatAlignType::Trailing) {
        return fn::invoke(fwd<F>(fmt), fwd<T0>(obj), fillN(out, remaining, fillAlignSpecification.fillChar));
      }

      auto const firstHalf = remaining / 2u;
      auto const secondHalf = remaining - firstHalf;
      return impl::fillN(
          fn::invoke(fwd<F>(fmt), fwd<T0>(obj), fillN(out, firstHalf, fillAlignSpecification.fillChar)), 
          secondHalf, fillAlignSpecification.fillChar
      );
    }

    BaseString<C> asStr;
    fn::invoke(fwd<F>(fmt), fwd<T0>(obj), BackInserterIterator<BaseString<C>>{asStr});
    return formatFillAlign(maybeMinWidth, out, asStr, asStr.size(), *this);
  }

  template <typename I> CDS_ATTR(2(nodiscard, constexpr(14))) 
  auto operator()(BaseString<C> const& obj, I out) const noexcept -> I {
    return impl::copy(obj.begin(), obj.end(), out);
  }

  FormatFillAlignSpecification<C> fillAlignSpecification{FormatDefaultAlign<T, C>::value, static_cast<C>(' ')};
};

template <typename C> struct FormatNumberComponent {
  template <typename I, typename S> CDS_ATTR(2(nodiscard, constexpr(14))) 
  auto parseNumber(I begin, S end) noexcept -> I {
    cds::tie(begin, numberSpecification) = formatParseNumber<C>(begin, end);
    return begin;
  }

  FormatNumberSpecification numberSpecification{};
};

template <typename C> struct FormWidthComponent {
  template <typename I, typename S> CDS_ATTR(2(nodiscard, constexpr(14))) 
  auto parseWidth(I begin, S end) noexcept -> I {
    cds::tie(begin, widthSpecification) = formatParseWidth<C>(begin, end);
    if (widthSpecification.width && !widthSpecification.width->size && !widthSpecification.width->explicitIdx) {
      ++acceptedAutomaticArgumentCount;
    }
    if (widthSpecification.precision && !widthSpecification.precision->size 
        && !widthSpecification.precision->explicitIdx) {
      ++acceptedAutomaticArgumentCount;
    }
    return begin;
  }

  FormatWidthSpecification widthSpecification{};
  Size acceptedAutomaticArgumentCount{0u};
};

template <typename C> struct FormatWidthOnlyComponent {
  template <typename I, typename S> CDS_ATTR(2(nodiscard, constexpr(14)))
  auto parseWidth(I begin, S end) noexcept -> I {
    cds::tie(begin, widthSpecification) = formatParseWidthOnly<C>(begin, end);
    if (widthSpecification.width && !widthSpecification.width->size && !widthSpecification.width->explicitIdx) {
      ++acceptedAutomaticArgumentCount;
    }
    return begin;
  }

  FormatWidthOnlySpecification widthSpecification{};
  Size acceptedAutomaticArgumentCount{0u};
};

template <typename = void> struct DefaultTypeFormatFlagsUnspecified {
  static FormatTypeFlags constexpr value = 0u;
};

template <typename = void> struct DefaultTypeFormatFlagsIntegral {
  static FormatTypeFlags constexpr value = static_cast<FormatTypeFlags>(FormatTypeFlagBits::Decimal);
};

// ODR before C++17
template <typename T> FormatTypeFlags const DefaultTypeFormatFlagsUnspecified<T>::value;
template <typename T> FormatTypeFlags const DefaultTypeFormatFlagsIntegral<T>::value;

template <typename T, typename = typename IsIntegral<T>::Type>
struct DefaultTypeFormatFlags : DefaultTypeFormatFlagsUnspecified<>{};

template <typename T> struct DefaultTypeFormatFlags<T, typename True::Type> : DefaultTypeFormatFlagsIntegral<>{};

template <typename T, typename C> struct FormatTypeComponent {
  template <typename I, typename S> CDS_ATTR(2(nodiscard, constexpr(14)))
  auto parseType(I begin, S end) noexcept -> I {
    cds::tie(begin, typeFlags) = formatParseType<T, C>(begin, end);
    return begin;
  }

  FormatTypeFlags typeFlags{DefaultTypeFormatFlags<T>::value};
};
} // namespace fmt
} // namespace impl
} // namespace cds

#endif // #ifndef CDS_FORMAT_STANDARD_FORMAT_SPECIFICATION_COMPONENTS_HPP
