//
// Created by loghin on 6/3/25.
//

#if defined(CDS_DS_SET_PROJECTION_HPP) && defined(CDS_FORMAT_RANGE_FORMATTER_HPP) \
    && !defined(CDS_FORMAT_SET_PROJECTION_FORMAT_HPP)
#define CDS_FORMAT_SET_PROJECTION_FORMAT_HPP

namespace cds {
template <typename CS, typename C, typename P, typename T> struct Formatter<SetProjection<C, P, T>, CS> :
    impl::fmt::RangeFormatter<typename T::Value, CS>{};
} // namespace cds

#endif
