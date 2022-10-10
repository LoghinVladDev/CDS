/*
 * Created by loghin on 6/26/22.
 */

#ifndef __CDS_EX_SHARED_ADDRESS_ITERATOR_HPP__
#define __CDS_EX_SHARED_ADDRESS_ITERATOR_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#warning No longer an experimental feature. Use the non-experimental header.
#include "../../../../shared/iterator/AddressIterator.hpp"

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {

        template < typename __ElementType >                                                             /* NOLINT(bugprone-reserved-identifier) */
        using AbstractAddressIterator   __CDS_DeprecatedHint("No longer an experimental feature.") =    /* NOLINT(bugprone-reserved-identifier) */
                cds :: AbstractAddressIterator < __ElementType >;

        template < typename __ElementType >                                                             /* NOLINT(bugprone-reserved-identifier) */
        using ForwardAddressIterator    __CDS_DeprecatedHint("No longer an experimental feature.") =    /* NOLINT(bugprone-reserved-identifier) */
                cds :: ForwardAddressIterator < __ElementType >;

        template < typename __ElementType >                                                             /* NOLINT(bugprone-reserved-identifier) */
        using BackwardAddressIterator   __CDS_DeprecatedHint("No longer an experimental feature.") =    /* NOLINT(bugprone-reserved-identifier) */
                cds :: BackwardAddressIterator < __ElementType >;

        template < typename __ElementType, bool __reverse = false >                                     /* NOLINT(bugprone-reserved-identifier) */
        using AddressIterator           __CDS_DeprecatedHint("No longer an experimental feature.") =    /* NOLINT(bugprone-reserved-identifier) */
                cds :: AddressIterator < __ElementType, __reverse >;

    }
}

#endif /* __CDS_EX_SHARED_ADDRESS_ITERATOR_HPP__ */
