/* NOLINT(llvm-header-guard)
 * Created by loghin on 2/22/2023.
 */

#ifndef __CDS_QUEUE_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_QUEUE_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {

    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    constexpr Queue < __ElementType > :: Queue () noexcept = default;


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    constexpr Queue < __ElementType > :: Queue (
            Queue const & queue
    ) noexcept = default;


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    constexpr Queue < __ElementType > :: Queue (
            Queue && queue
    ) noexcept = default;


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_cpplang_ConstexprDestructor Queue < __ElementType > :: virtual ~Queue () noexcept = default;

} /* namespace cds */

#endif /* __CDS_QUEUE_IMPL_HPP__ */
