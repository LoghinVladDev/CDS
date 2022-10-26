/*
 * Created by loghin on 6/27/22.
 */

#ifndef __CDS_MUTABLE_COLLECTION_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_MUTABLE_COLLECTION_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */

    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    constexpr MutableCollection < __ElementType > :: MutableCollection () noexcept = default;


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    constexpr MutableCollection < __ElementType > :: MutableCollection (
            MutableCollection const & collection
    ) noexcept = default;


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    constexpr MutableCollection < __ElementType > :: MutableCollection (
            MutableCollection && collection
    ) noexcept = default;


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_cpplang_ConstexprDestructor MutableCollection < __ElementType > :: ~MutableCollection () noexcept = default;


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto MutableCollection < __ElementType > :: toString () const noexcept -> String {

        /* Default toString implementation, store 'MutableCollection at 0x....'. Use a stringstream for simplicity */
        std :: stringstream oss;
        oss << "MutableCollection at " << std :: hex << reinterpret_cast < AddressValueType const > ( this );

        /* converted to std :: string, and to cds :: String afterwards */
        return oss.str();
    }

} /* namespace cds */

#endif /* __CDS_MUTABLE_COLLECTION_IMPL_HPP__ */
