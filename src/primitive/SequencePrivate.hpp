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
                * ( * Type <
                        typename std :: remove_reference < C > :: type :: Iterator
                > :: unsafeAddress () )
            )
        > :: type;
    };

    template < typename C >
    constexpr auto isFlattable () noexcept -> bool {
        return std :: is_same < C, Sequence < typename ContainedType < C > :: Type > > :: value;
    }

    template < typename C >
    struct FlattenType {
        using Type = typename ContainedType < typename ContainedType < C > :: Type > :: Type;
    };

    template < typename MapperType, typename C >
    constexpr auto mapToSameType () noexcept -> bool {
        return std :: is_same <
            typename std :: remove_reference <
                decltype (
                    * Type <
                            typename std :: remove_reference < C > :: type :: Iterator
                    > :: unsafeAddress ()
                )
            > :: type,
            returnOf < MapperType >
        > :: type :: value;
    }

    template < typename TransformerType >
    struct FlatMapDeducted {
        using Type = typename std :: remove_reference <
            decltype (
                * ( * Type <
                    typename returnOf < TransformerType > :: Iterator
                > :: unsafeAddress () )
            )
        > :: type;
    };

    template < typename TransformerType >
    using FlatMapDeducedType = typename FlatMapDeducted < TransformerType > :: Type;

    template < typename C >
    constexpr auto containedTypeIsPair () noexcept -> bool {
        return isPair <
            typename std :: remove_reference <
                decltype (
                    * ( * Type <
                        typename std :: remove_reference < C > :: type :: Iterator
                    > :: unsafeAddress () )
                )
            > :: type
        > :: type :: value;
    }

//    template < typename C >
//    constexpr auto flattable () noexcept -> bool {
//
//    }

    template < typename C >
    struct ContainedTypeAsPair : pairTrait <
        typename std :: remove_reference <
            decltype (
                * ( * Type <
                    typename std :: remove_reference < C > :: type :: Iterator
                > :: unsafeAddress () )
            )
        > :: type > {

    };

    struct Windowed {

        template < typename Transformer >
        constexpr static auto isAbstract () noexcept -> bool {
            return std::is_abstract <
                typename std::remove_cv <
                    typename std::remove_reference <
                        decltype (
                            std::get < 0 > (
                                * dataTypes::unsafeAddress <
                                    argumentsOf <
                                        Transformer
                                    >
                                > ()
                            )
                        )
                    > :: type
                > :: type
            > :: type :: value;
        }

        template < typename Transformer >
        using typeIfAbstract = LinkedList <
            typename std::remove_cv <
                typename std::remove_reference <
                    decltype (
                        std::get < 0 > (
                            * dataTypes::unsafeAddress <
                                argumentsOf <
                                    Transformer
                                >
                            > ()
                        )
                    )
                >::type
            > :: type ::ElementType
        >;

        template < typename Transformer >
        using typeIfNotAbstract = typename std::remove_cv <
            typename std::remove_reference <
                decltype(
                    std::get<0>(
                        *dataTypes::unsafeAddress <
                            argumentsOf <
                                Transformer
                            >
                        >()
                    )
                )
            > :: type
        > :: type;

        template < typename ListTransformer >
        using type =
            typename std :: conditional <
                isAbstract < ListTransformer > (),
                typeIfAbstract < ListTransformer >,
                typeIfNotAbstract < ListTransformer >
            > :: type;
    };

}

#endif //CDS_SEQUENCEPRIVATE_H
