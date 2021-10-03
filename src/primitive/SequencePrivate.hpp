//
// Created by loghin on 02.10.2021.
//

#ifndef CDS_SEQUENCEPRIVATE_H
#define CDS_SEQUENCEPRIVATE_H

#include <CDS/Traits>
#include <CDS/Double>
#include <CDS/Integer>
#include <CDS/Float>
#include <CDS/Long>

namespace __CDS_Sequence { // NOLINT(bugprone-reserved-identifier)

    template < typename V, typename = void >
    struct IsArithmetic {
        static constexpr bool Value = false;
    };

    template < typename V >
    struct IsArithmetic < V > {
        static constexpr bool Value =
            std::is_arithmetic < V > :: type :: value ||
            std::is_same < V, Integer > :: value ||
            std::is_same < V, Long > :: value ||
            std::is_same < V, Float > :: value ||
            std::is_same < V, Double > :: value
        ;
    };

    template < typename C >
    struct ContainedType {
        using Type = typename std :: remove_reference <
            decltype (
                Type <
                        typename std :: remove_reference < C > :: type :: Iterator
                > :: unsafeAddress () -> value ()
            )
        > :: type;
    };

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
