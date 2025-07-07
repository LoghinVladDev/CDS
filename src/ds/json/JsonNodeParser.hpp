//
// Created by loghin on 7/6/25.
//

#ifndef CDS_DS_JSON_NODE_PARSER_HPP
#define CDS_DS_JSON_NODE_PARSER_HPP
#pragma once

namespace cds {
namespace json {
namespace impl {
template <typename B, typename A, typename C> CDS_ATTR(2(nodiscard, constexpr(20)))
auto parseJsonNumber(JsonNodeBase<B, A>& dst, BaseStringView<C> src, JsonParseOptions const& options = {}) noexcept
    -> Tuple<BaseStringView<C>, JsonParseError> {
  using Tok = JsonTokens<C>;
  using T = typename BaseStringView<C>::STraits;
  using U = typename BaseStringView<C>::Utils;
  auto base = 10;
  auto afterSign = src;
  auto neg = false;
  if (!afterSign) {
    return {src, JsonParseError::ErrorNumberInvalid};
  }

  if (afterSign[0] == Tok::minus) {
    neg = true;
    afterSign = afterSign.sub(1).ltrim();
  } else if (options.readPlusSign && afterSign[0] == Tok::plus) {
    afterSign = afterSign.sub(1).ltrim();
  }

  if (!afterSign) {
    return {src, JsonParseError::ErrorNumberInvalid};
  }

  auto afterBase = afterSign;
  if (afterBase[0] == Tok::zero && afterBase.length() > 1 && options.readNonBase10Integrals) {
    if (afterBase[1] == Tok::binaryLowercase || afterBase[1] == Tok::binaryUppercase) {
      base = 2;
      afterBase = afterBase.sub(2);
    } else if (afterBase[1] == Tok::hexLowercase || afterBase[1] == Tok::hexUppercase) {
      base = 16;
      afterBase = afterBase.sub(2);
    } else if (T::isDigit(afterBase[1]) && afterBase.length() > 2 && T::isDigit(afterBase[2])) {
      base = 8;
      afterBase = afterBase.sub(1);
    }
  }

  C const* afterIntegral;
  JsonNumberIntegral integral;
  auto const hasReadIntegral = U::readInt(afterBase.data(),afterBase.length(), &afterIntegral, &integral, base);
  if (!hasReadIntegral) {
    if (afterSign[0] == Tok::dot && !options.readFloatingStartingWithFraction) {
      return {src, JsonParseError::ErrorNumberNoIntegralBeforeFraction};
    } else if (!options.readFloatingStartingWithFraction) {
      return {src, JsonParseError::ErrorNumberInvalid};
    }
  } else if (neg) {
    integral *= -1;
  }

  auto const srcAfterIntegral = BaseStringView<C>{afterIntegral, src.length() - (afterIntegral - src.data())};
  if (srcAfterIntegral.empty() || srcAfterIntegral[0] != Tok::dot) {
    dst = integral;
    return {srcAfterIntegral.ltrim(), JsonParseError::None};
  }

  if (srcAfterIntegral.length() == 1 || !T::isDigit(srcAfterIntegral[1])) {
    return {src, JsonParseError::ErrorNumberNoDigitsAfterFraction};
  }

  C* afterDouble;
  dst = std::strtod(src.data(), &afterDouble);
  auto const srcAfterDouble = BaseStringView<C>{afterDouble, src.length() - (afterDouble - src.data())};
  if (afterDouble == src.data()) {
    return {src, JsonParseError::ErrorNumberInvalid};
  }

  return {srcAfterDouble.ltrim(), JsonParseError::None};
};

template <typename B, typename A, typename C> CDS_ATTR(2(nodiscard, constexpr(20)))
auto parseJsonNode(JsonNodeBase<B, A>& dst, BaseStringView<C> src, JsonParseOptions const& options) noexcept
    -> Tuple<BaseStringView<C>, JsonParseError> {
  using Tok = JsonTokens<C>;
  using T = typename BaseStringView<C>::STraits;
  using SA = StringAbstract<>;

  src = src.ltrim();
  if (src.empty()) {
    return {src, JsonParseError::ErrorValueInvalid};
  }

  auto const current = src.front();
  switch (current) {
    case Tok::leftBrace: {
      dst = typename JsonNodeBase<B, A>::JsonObject{};
      return parseJsonObject(dst.getObject(), src, options);
    }

    case Tok::leftSquareBracket: {
      dst = typename JsonNodeBase<B, A>::JsonArray{};
      return parseJsonArray(dst.getArray(), src, options);
    }

    case Tok::stringQuote: {
      dst = JsonString{};
      return parseJsonString(dst.getString(), src, options);
    }

    default: {
      if (T::isDigit(current)
          || current == Tok::minus
          || (options.readFloatingStartingWithFraction && current == Tok::dot)
          || (options.readPlusSign && current == Tok::plus)) {
        return parseJsonNumber(dst, src, options);
      }

      if (src.startsWith(T::Constants::_true)) {
        dst = true;
        return {src.sub(SA::length(T::Constants::_true)).ltrim(), JsonParseError::None};
      }

      if (src.startsWith(T::Constants::_false)) {
        dst = false;
        return {src.sub(SA::length(T::Constants::_false)).ltrim(), JsonParseError::None};
      }

      if (src.startsWith(T::Constants::_null)) {
        dst = nullptr;
        return {src.sub(SA::length(T::Constants::_null)).ltrim(), JsonParseError::None};
      }

      return {src, JsonParseError::ErrorValueInvalid};
    }
  }
}
} // namespace impl
} // namespace json
} // namespace cds

#endif // #ifndef CDS_DS_JSON_NODE_PARSER_HPP
