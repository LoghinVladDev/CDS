/*
 * Created by loghin on 11/29/2022.
 */

#ifndef __CDS_TUPLE_CTAD_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_TUPLE_CTAD_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#if __CDS_cpplang_CTAD_available

namespace cds {

    template < typename ... __Types > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    Tuple (
            __Types ...
    ) -> Tuple < __Types ... >;

} /* namespace cds */

#endif

#endif /* __CDS_TUPLE_CTAD_HPP__ */
