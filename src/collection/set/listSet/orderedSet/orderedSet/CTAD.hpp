//
// Created by loghin on 6/15/22.
//

#ifndef __CDS_ORDERED_SET_CTAD_HPP__
#define __CDS_ORDERED_SET_CTAD_HPP__

#if __CDS_cpplang_CTAD_available

namespace cds {

    template <
            typename __ElementType, // NOLINT(bugprone-reserved-identifier)
            typename __ComparatorFunction = FunctionComparator < __ElementType, & predicates :: lessThan < __ElementType > > // NOLINT(bugprone-reserved-identifier)
    > OrderedSet (
            std :: initializer_list < __ElementType >
    ) -> OrderedSet < __ElementType, __ComparatorFunction >;

}

#endif

#endif // __CDS_ORDERED_SET_CTAD_HPP__
