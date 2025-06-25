//
// Created by loghin on 6/25/25.
//

#ifndef CDS_TAGS_HPP
#define CDS_TAGS_HPP

#include <cds/meta/Base>

namespace cds {
namespace meta {
struct Default {};

template <typename V, typename R> using DefaultOr = Conditional<IsSame<V, Default>, R, V>;
} // namespace meta
} // namespace cds

#endif // CDS_TAGS_HPP
