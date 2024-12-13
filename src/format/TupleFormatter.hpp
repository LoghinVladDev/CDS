//
// Created by loghin on 11/2/24.
//

#if defined(CDS_PRIMITIVE_TUPLE_HPP) && defined(CDS_FORMAT_TUPLE_LIKE_FORMATTER_HPP) \
    && !defined(CDS_FORMAT_TUPLE_FORMATTER_HPP)
#define CDS_FORMAT_TUPLE_FORMATTER_HPP

namespace cds {
template <typename C, typename... Ts> struct Formatter<Tuple<Ts...>, C> :
    impl::fmt::TupleLikeFormatter<C, Ts...> {};
} // namespace cds

#endif // #if defined(CDS_PRIMITIVE_TUPLE_HPP) && defined(CDS_FORMAT_TUPLE_LIKE_FORMATTER_HPP)
       //     && !defined(CDS_FORMAT_TUPLE_FORMATTER_HPP)
