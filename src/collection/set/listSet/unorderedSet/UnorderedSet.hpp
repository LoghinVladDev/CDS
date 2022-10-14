/*
 * Created by loghin on 6/13/22.
 */

#ifndef __CDS_UNORDERED_SET_HPP__
#define __CDS_UNORDERED_SET_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/HashSet>
#warning UnorderedSet has been deprecated. Use HashSet instead.

namespace cds {

    template <
            typename __ElementType  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > using UnorderedSet = cds :: HashSet < __ElementType >;

}

#endif /* __CDS_UNORDERED_SET_HPP__ */
