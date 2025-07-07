//
// Created by loghin on 7/6/25.
//

#ifndef CDS_DS_JSON_ARRAY_PARSER_HPP
#define CDS_DS_JSON_ARRAY_PARSER_HPP
#pragma once

namespace cds {
namespace json {
namespace impl {
template <typename B, typename C> CDS_ATTR(2(nodiscard, constexpr(20)))
auto parseJsonArray(JsonArrayBase<B>& dst, BaseStringView<C> src, JsonParseOptions const& options) noexcept
    -> Tuple<BaseStringView<C>, JsonParseError> {
  using Tok = JsonTokens<C>;
  if (src.empty() || src[0] != Tok::leftSquareBracket) {
    return {src, JsonParseError::ErrorArrayWithoutStartingBracket};
  }

  auto afterBracket = src.sub(1).ltrim();
  if (afterBracket.empty()) {
    return {src, JsonParseError::ErrorArrayWithoutEndingBracket};
  }

  if (afterBracket[0] == Tok::rightSquareBracket) {
    return {afterBracket.sub(1).ltrim(), JsonParseError::None};
  }

  JsonParseError err;
  typename JsonArrayBase<B>::Value node;
  cds::tie(afterBracket, err) = parseJsonNode(node, afterBracket, options);
  if (err != JsonParseError::None) {
    return {afterBracket, err};
  }
  dst.emplaceBack(mv(node));
  afterBracket = afterBracket.ltrim();

  while (afterBracket && afterBracket[0] != Tok::rightSquareBracket) {
    if (afterBracket[0] != Tok::separator) {
      return {afterBracket, JsonParseError::ErrorArrayWithoutElementSeparator};
    }

    afterBracket = afterBracket.sub(1);
    if (afterBracket.empty()) {
      break;
    }

    typename JsonArrayBase<B>::Value loopNode;
    cds::tie(afterBracket, err) = parseJsonNode(loopNode, afterBracket, options);
    if (err != JsonParseError::None) {
      return {afterBracket, err};
    }
    dst.emplaceBack(mv(loopNode));
    afterBracket = afterBracket.ltrim();
  }

  if (!afterBracket || afterBracket[0] != Tok::rightSquareBracket) {
    return {afterBracket, JsonParseError::ErrorArrayWithoutEndingBracket};
  }

  return {afterBracket.sub(1).ltrim(), JsonParseError::None};
}

template <typename B> CDS_ATTR(constexpr(20)) JsonArrayBase<B>::JsonArrayBase(StringView asString)
    CDS_ATTR(noexcept(false)) : JsonArrayBase{} {
  throwIfErroneous(parseJsonArray(*this, asString));
}
} // namespace impl
} // namespace json
} // namespace cds

#endif // #ifndef CDS_DS_JSON_ARRAY_PARSER_HPP
