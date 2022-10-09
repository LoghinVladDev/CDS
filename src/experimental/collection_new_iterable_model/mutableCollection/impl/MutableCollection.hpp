/*
 * Created by loghin on 6/27/22.
 */

#ifndef __CDS_EX_MUTABLE_COLLECTION_IMPL_HPP__
#define __CDS_EX_MUTABLE_COLLECTION_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {

        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr MutableCollection < __ElementType > :: MutableCollection () noexcept = default;


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr MutableCollection < __ElementType > :: MutableCollection (
                MutableCollection const & collection
        ) noexcept = default;


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr MutableCollection < __ElementType > :: MutableCollection (
                MutableCollection && collection
        ) noexcept = default;


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        __CDS_cpplang_ConstexprDestructor MutableCollection < __ElementType > :: ~MutableCollection () noexcept = default;


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        __CDS_OptimalInline auto MutableCollection < __ElementType > :: toString () const noexcept -> String {

            /* Default toString implementation, store 'MutableCollection at 0x....'. Use a stringstream for simplicity */
            std :: stringstream oss;
            oss << "MutableCollection at " << std :: hex << reinterpret_cast < AddressValueType const > ( this );

            /* converted to std :: string, and to cds :: String afterwards */
            return oss.str();
        }

    }
}

#endif /* __CDS_EX_MUTABLE_COLLECTION_IMPL_HPP__ */
