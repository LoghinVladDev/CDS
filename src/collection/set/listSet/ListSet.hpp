//
// Created by loghin on 6/13/22.
//

#ifndef __CDS_LIST_SET_HPP__
#define __CDS_LIST_SET_HPP__

#include <CDS/Set>
#warning ListSet has been deprecated. Use Set instead.

namespace cds { // NOLINT(modernize-concat-nested-namespaces)

    template <
            typename __ElementType // NOLINT(bugprone-reserved-identifier)
    > using ListSet __CDS_DeprecatedHint("ListSet has been deprecated. Use Set instead.") = cds :: Set < __ElementType >;

}

#endif // __CDS_LIST_SET_HPP__
