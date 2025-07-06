//
// Created by loghin on 6/25/25.
//

#if defined(CDS_FORMAT_FORMAT_HPP) && defined(CDS_DS_JSON_ARRAY_DEF_HPP) && !defined(CDS_FORMAT_JSON_ARRAY_FORMATTER_HPP)
#define CDS_FORMAT_JSON_ARRAY_FORMATTER_HPP

namespace cds {
template <typename B, typename C> struct Formatter<json::impl::JsonArrayBase<B>, C> :
    Formatter<B, C> {};

template <typename C> struct Formatter<json::impl::JsonArrayBase<meta::Default>, C> :
    Formatter<Vector<json::impl::JsonNodeBase<>>, C> {};
} // namespace cds

#endif // #if defined(CDS_FORMAT_FORMAT_HPP) && defined(CDS_DS_JSON_ARRAY_DEF_HPP) && !defined(CDS_FORMAT_JSON_ARRAY_FORMATTER_HPP)
