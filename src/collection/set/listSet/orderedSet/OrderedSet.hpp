/*
 * Created by loghin on 6/13/22.
 */

#ifndef __CDS_ORDERED_SET_HPP__
#define __CDS_ORDERED_SET_HPP__

#include <CDS/TreeSet>

#include "../../../../shared/impl/generalPredicates.hpp"

namespace cds {

    template <
            typename __ElementType,                                             /* NOLINT(bugprone-reserved-identifier) */
            typename __ComparatorFunction = functional :: DecoratedPredicate <  /* NOLINT(bugprone-reserved-identifier) */
                    decltype ( & predicates :: lessThan < __ElementType > ),
                    & predicates :: lessThan < __ElementType >
            >
    > using OrderedSet __CDS_DeprecatedHint("OrderedSet has been deprecated. Use TreeSet instead.") = TreeSet < __ElementType >;

}

#endif // __CDS_ORDERED_SET_HPP__
