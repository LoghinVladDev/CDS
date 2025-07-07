//
// Created by loghin on 7/6/25.
//

#ifndef CDS_DS_JSON_OBJECT_PARSER_HPP
#define CDS_DS_JSON_OBJECT_PARSER_HPP
#pragma once

namespace cds {
namespace json {
namespace impl {
template <typename B, typename C> CDS_ATTR(2(nodiscard, constexpr(20)))
auto parseJsonObjectMember(JsonObjectBase<B>& dst, BaseStringView<C> src, JsonParseOptions const& options) noexcept
    -> Tuple<BaseStringView<C>, JsonParseError> {
  using Tok = JsonTokens<C>;

  JsonParseError err;
  JsonString key;
  cds::tie(src, err) = parseJsonString(key, src, options);
  if (err != JsonParseError::None) {
    return {src, err};
  }

  if (!src || src[0] != Tok::memberSeparator) {
    return {src, JsonParseError::ErrorObjectMemberWithoutKeyValueSeparator};
  }

  src = src.sub(1).ltrim();
  typename JsonObjectBase<B>::Value node;
  cds::tie(src, err) = parseJsonNode(node, src, options);
  if (err != JsonParseError::None) {
    return {src, err};
  }

  dst.emplace(mv(key), mv(node));
  return {src.ltrim(), JsonParseError::None};
}

template <typename B, typename C> CDS_ATTR(2(nodiscard, constexpr(20)))
auto parseJsonObject(JsonObjectBase<B>& dst, BaseStringView<C> src, JsonParseOptions const& options) noexcept
    -> Tuple<BaseStringView<C>, JsonParseError> {
  using Tok = JsonTokens<C>;

  if (src.empty() || src[0] != Tok::leftBrace) {
    return {src, JsonParseError::ErrorObjectWithoutStartingBrace};
  }

  src = src.sub(1).ltrim();
  if (src.empty()) {
    return {src, JsonParseError::ErrorObjectWithoutEndingBrace};
  }

  if (src[0] == Tok::rightBrace) {
    return {src.sub(1).ltrim(), JsonParseError::None};
  }

  JsonParseError err;
  cds::tie(src, err) = parseJsonObjectMember(dst, src, options);
  if (err != JsonParseError::None) {
    return {src, err};
  }

  while (src && src[0] != Tok::rightBrace) {
    if (src[0] != Tok::separator) {
      return {src, JsonParseError::ErrorObjectWithoutMemberSeparator};
    }

    src = src.sub(1);
    if (src.empty()) {
      break;
    }

    cds::tie(src, err) = parseJsonObjectMember(dst, src.ltrim(), options);
    if (err != JsonParseError::None) {
      return {src, err};
    }
  }

  if (!src || src[0] != Tok::rightBrace) {
    return {src, JsonParseError::ErrorObjectWithoutEndingBrace};
  }

  return {src.sub(1).ltrim(), JsonParseError::None};
}

template <typename B> CDS_ATTR(constexpr(20)) JsonObjectBase<B>::JsonObjectBase(StringView asString)
    CDS_ATTR(noexcept(false)) : JsonObjectBase{} {
  throwIfErroneous(parseJsonObject(*this, asString));
}
} // namespace impl
} // namespace json
} // namespace cds

#endif // #ifndef CDS_DS_JSON_OBJECT_PARSER_HPP
