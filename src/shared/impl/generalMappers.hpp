/*
 * Created by loghin on 30/10/22.
 */

#ifndef __CDS_SHARED_GENERAL_MAPPERS_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_GENERAL_MAPPERS_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */
    namespace mappers {

        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto identity (
                __ElementType const & element
        ) noexcept -> __ElementType const & {

            return element;
        }

    } /* namespace mappers */
} /* namespace cds */

#endif /* __CDS_SHARED_GENERAL_MAPPERS_HPP__ */
