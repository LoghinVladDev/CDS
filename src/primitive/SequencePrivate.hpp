//
// Created by loghin on 02.10.2021.
//

#ifndef CDS_SEQUENCEPRIVATE_H
#define CDS_SEQUENCEPRIVATE_H

#include <CDS/Traits>

namespace __CDS_Sequence { // NOLINT(bugprone-reserved-identifier)

    template < typename MapperType, typename C >
    constexpr auto mapToSameType () noexcept -> bool {
        return std :: is_same <
            typename std :: remove_reference <
                decltype (
                    Type <
                            typename std :: remove_reference < C > :: type :: Iterator
                    > :: unsafeAddress () -> value ()
                )
            > :: type,
            returnOf < MapperType >
        > :: type :: value;
    }

    template < typename C >
    constexpr auto containedTypeIsPair () noexcept -> bool {
        return isPair <
            typename std :: remove_reference <
                decltype (
                    Type <
                        typename std :: remove_reference < C > :: type :: Iterator
                    > :: unsafeAddress () -> value ()
                )
            > :: type
        > :: type :: value;
    }

    template < typename C >
    struct ContainedTypeAsPair : pairTrait <
        typename std :: remove_reference <
            decltype (
                Type <
                    typename std :: remove_reference < C > :: type :: Iterator
                > :: unsafeAddress () -> value ()
            )
        > :: type > {

    };

}

#endif //CDS_SEQUENCEPRIVATE_H
