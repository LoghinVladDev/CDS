//
// Created by loghin on 29.10.2021.
//

#ifndef CDS_FUNCTIONDEDUCTION_HPP
#define CDS_FUNCTIONDEDUCTION_HPP

#include <CDS/meta/FunctionTraits>

namespace cds {

    template < typename ReturnType, typename ... ArgumentTypes >
    Function ( ReturnType (*) ( ArgumentTypes ... ) ) -> Function < ReturnType ( ArgumentTypes ... ) >;

    template <
            typename Functor,
            EnableIf <
                    meta :: EnableIf < meta :: isCallable < Functor > () > &&
//                    std :: tuple_size < meta :: ArgumentsOf < Functor > > == 0 /// hard dependency on experimental :: Tuple ::
            > = 0
    >
    Function ( Functor ) -> Function <
            ReturnOf < Functor > (

            )
    >;

    template <
            typename Functor,
            EnableIf <
                    Type < Functor > :: isCallable &&
                    std :: tuple_size < ArgumentsOf < Functor > > :: value == 1
            > = 0
    >
    Function ( Functor ) -> Function <
            ReturnOf < Functor > (
                    typename std :: tuple_element < 0u, ArgumentsOf < Functor > > :: type
            )
    >;

    template <
            typename Functor,
            EnableIf <
                    Type < Functor > :: isCallable &&
                    std :: tuple_size < ArgumentsOf < Functor > > :: value == 2
            > = 0
    >
    Function ( Functor ) -> Function <
            ReturnOf < Functor > (
                    typename std :: tuple_element < 0u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 1u, ArgumentsOf < Functor > > :: type
            )
    >;

    template <
            typename Functor,
            EnableIf <
                    Type < Functor > :: isCallable &&
                    std :: tuple_size < ArgumentsOf < Functor > > :: value == 3
            > = 0
    >
    Function ( Functor ) -> Function <
            ReturnOf < Functor > (
                    typename std :: tuple_element < 0u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 1u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 2u, ArgumentsOf < Functor > > :: type
            )
    >;

    template <
            typename Functor,
            EnableIf <
                    Type < Functor > :: isCallable &&
                    std :: tuple_size < ArgumentsOf < Functor > > :: value == 4
            > = 0
    >
    Function ( Functor ) -> Function <
            ReturnOf < Functor > (
                    typename std :: tuple_element < 0u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 1u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 2u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 3u, ArgumentsOf < Functor > > :: type
            )
    >;

    template <
            typename Functor,
            EnableIf <
                    Type < Functor > :: isCallable &&
                    std :: tuple_size < ArgumentsOf < Functor > > :: value == 5
            > = 0
    >
    Function ( Functor ) -> Function <
            ReturnOf < Functor > (
                    typename std :: tuple_element < 0u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 1u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 2u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 3u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 4u, ArgumentsOf < Functor > > :: type
            )
    >;

    template <
            typename Functor,
            EnableIf <
                    Type < Functor > :: isCallable &&
                    std :: tuple_size < ArgumentsOf < Functor > > :: value == 6
            > = 0
    >
    Function ( Functor ) -> Function <
            ReturnOf < Functor > (
                    typename std :: tuple_element < 0u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 1u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 2u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 3u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 4u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 5u, ArgumentsOf < Functor > > :: type
            )
    >;

    template <
            typename Functor,
            EnableIf <
                    Type < Functor > :: isCallable &&
                    std :: tuple_size < ArgumentsOf < Functor > > :: value == 7
            > = 0
    >
    Function ( Functor ) -> Function <
            ReturnOf < Functor > (
                    typename std :: tuple_element < 0u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 1u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 2u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 3u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 4u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 5u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 6u, ArgumentsOf < Functor > > :: type
            )
    >;

    template <
            typename Functor,
            EnableIf <
                    Type < Functor > :: isCallable &&
                    std :: tuple_size < ArgumentsOf < Functor > > :: value == 8
            > = 0
    >
    Function ( Functor ) -> Function <
            ReturnOf < Functor > (
                    typename std :: tuple_element < 0u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 1u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 2u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 3u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 4u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 5u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 6u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 7u, ArgumentsOf < Functor > > :: type
            )
    >;

    template <
            typename Functor,
            EnableIf <
                    Type < Functor > :: isCallable &&
                    std :: tuple_size < ArgumentsOf < Functor > > :: value == 9
            > = 0
    >
    Function ( Functor ) -> Function <
            ReturnOf < Functor > (
                    typename std :: tuple_element < 0u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 1u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 2u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 3u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 4u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 5u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 6u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 7u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 8u, ArgumentsOf < Functor > > :: type
            )
    >;

    template <
            typename Functor,
            EnableIf <
                    Type < Functor > :: isCallable &&
                    std :: tuple_size < ArgumentsOf < Functor > > :: value == 10
            > = 0
    >
    Function ( Functor ) -> Function <
            ReturnOf < Functor > (
                    typename std :: tuple_element < 0u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 1u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 2u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 3u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 4u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 5u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 6u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 7u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 8u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 9u, ArgumentsOf < Functor > > :: type
            )
    >;

    template <
            typename Functor,
            EnableIf <
                    Type < Functor > :: isCallable &&
                    std :: tuple_size < ArgumentsOf < Functor > > :: value == 11
            > = 0
    >
    Function ( Functor ) -> Function <
            ReturnOf < Functor > (
                    typename std :: tuple_element < 0u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 1u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 2u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 3u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 4u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 5u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 6u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 7u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 8u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 9u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 10u, ArgumentsOf < Functor > > :: type
            )
    >;

    template <
            typename Functor,
            EnableIf <
                    Type < Functor > :: isCallable &&
                    std :: tuple_size < ArgumentsOf < Functor > > :: value == 12
            > = 0
    >
    Function ( Functor ) -> Function <
            ReturnOf < Functor > (
                    typename std :: tuple_element < 0u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 1u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 2u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 3u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 4u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 5u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 6u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 7u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 8u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 9u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 10u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 11u, ArgumentsOf < Functor > > :: type
            )
    >;

    template <
            typename Functor,
            EnableIf <
                    Type < Functor > :: isCallable &&
                    std :: tuple_size < ArgumentsOf < Functor > > :: value == 13
            > = 0
    >
    Function ( Functor ) -> Function <
            ReturnOf < Functor > (
                    typename std :: tuple_element < 0u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 1u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 2u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 3u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 4u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 5u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 6u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 7u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 8u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 9u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 10u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 11u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 12u, ArgumentsOf < Functor > > :: type
            )
    >;


    template <
            typename Functor,
            EnableIf <
                    Type < Functor > :: isCallable &&
                    std :: tuple_size < ArgumentsOf < Functor > > :: value == 14
            > = 0
    >
    Function ( Functor ) -> Function <
            ReturnOf < Functor > (
                    typename std :: tuple_element < 0u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 1u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 2u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 3u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 4u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 5u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 6u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 7u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 8u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 9u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 10u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 11u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 12u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 13u, ArgumentsOf < Functor > > :: type
            )
    >;

    template <
            typename Functor,
            EnableIf <
                    Type < Functor > :: isCallable &&
                    std :: tuple_size < ArgumentsOf < Functor > > :: value == 15
            > = 0
    >
    Function ( Functor ) -> Function <
            ReturnOf < Functor > (
                    typename std :: tuple_element < 0u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 1u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 2u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 3u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 4u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 5u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 6u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 7u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 8u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 9u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 10u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 11u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 12u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 13u, ArgumentsOf < Functor > > :: type,
                    typename std :: tuple_element < 14u, ArgumentsOf < Functor > > :: type
            )
    >;

}

#endif //CDS_FUNCTIONDEDUCTION_HPP
