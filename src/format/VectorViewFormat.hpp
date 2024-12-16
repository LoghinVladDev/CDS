//
// Created by loghin on 11/2/24.
//

#if defined(CDS_COLLECTION_VECTOR_VIEW_HPP) && defined(CDS_FORMAT_RANGE_FORMATTER_HPP) \
    && !defined(CDS_FORMAT_VECTOR_VIEW_FORMAT_HPP)
#define CDS_FORMAT_VECTOR_VIEW_FORMAT_HPP

namespace cds {
template <typename T, Size extent, typename C> struct Formatter<VectorView<T, extent>, C> :
    impl::fmt::RangeFormatter<meta::RemoveCVRef<T>, C>{};
} // namespace cds

#endif // #if defined(CDS_COLLECTION_VECTOR_VIEW_HPP) && defined(CDS_FORMAT_RANGE_FORMATTER_HPP)
       //     && !defined(CDS_FORMAT_VECTOR_VIEW_FORMAT_HPP)
