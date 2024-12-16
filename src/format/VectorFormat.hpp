//
// Created by loghin on 11/2/24.
//

#if defined(CDS_COLLECTION_VECTOR_HPP) && defined(CDS_FORMAT_RANGE_FORMATTER_HPP) \
    && !defined(CDS_FORMAT_VECTOR_FORMAT_HPP)
#define CDS_FORMAT_VECTOR_FORMAT_HPP

namespace cds {
template <typename T, typename A, typename C> struct Formatter<Vector<T, A>, C> :
    impl::fmt::RangeFormatter<meta::RemoveCVRef<T>, C>{};
} // namespace cds

#endif // #if defined(CDS_COLLECTION_VECTOR_HPP) && defined(CDS_FORMAT_RANGE_FORMATTER_HPP)
       //     && !defined(CDS_FORMAT_VECTOR_FORMAT_HPP)
