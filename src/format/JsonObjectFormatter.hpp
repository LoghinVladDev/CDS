//
// Created by loghin on 6/25/25.
//

#if defined(CDS_FORMAT_FORMAT_HPP) && defined(CDS_DS_JSON_OBJECT_DEF_HPP) && !defined(CDS_FORMAT_JSON_OBJECT_FORMATTER_HPP)
#define CDS_FORMAT_JSON_OBJECT_FORMATTER_HPP

namespace cds {
template <typename B, typename C> struct Formatter<json::impl::JsonObjectBase<B>, C> :
    Formatter<B, C> {};

template <typename C> struct Formatter<json::impl::JsonObjectBase<meta::Default>, C> :
    Formatter<LinkedHashMap<String, json::impl::JsonNodeBase<>>, C> {
  using Base = Formatter<LinkedHashMap<String, json::impl::JsonNodeBase<>>, C>;

  template <typename Ctx> CDS_ATTR(2(nodiscard, constexpr(14))) auto parse(Ctx& ctx) CDS_ATTR(noexcept(false))
      -> typename Ctx::Iterator {
    if (ctx.begin() == ctx.end() || *ctx.begin() == '}') {
      impl::BaseStringView<C> defaultFmtStr = "m:m:#?:";
      impl::fmt::FormatParseContext<C, impl::StringUtils<C, meta::StringTraits<C>>> subCtx{defaultFmtStr};
      ignore = Base::parse(subCtx);
      return ctx.begin();
    }

    return Base::parse(ctx);
  }
};
} // namespace cds

#endif // #if defined(CDS_FORMAT_FORMAT_HPP) && defined(CDS_DS_JSON_OBJECT_DEF_HPP) && !defined(CDS_FORMAT_JSON_OBJECT_FORMATTER_HPP)
