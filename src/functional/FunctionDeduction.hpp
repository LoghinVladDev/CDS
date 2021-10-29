//
// Created by loghin on 29.10.2021.
//

#ifndef CDS_FUNCTIONDEDUCTION_HPP
#define CDS_FUNCTIONDEDUCTION_HPP

template < typename ReturnType, typename ... ArgumentTypes >
Function ( ReturnType (*) ( ArgumentTypes ... ) ) -> Function < ReturnType ( ArgumentTypes ... ) >;

template <
        typename Functor,
        EnableIf <
                Type < Functor > :: isCallable &&
                std :: tuple_size < typename functionTraits < Functor > :: ArgsType > :: value == 0
        > = 0
>
Function ( Functor ) -> Function <
        typename functionTraits < Functor > :: ReturnType (

        )
>;

template <
        typename Functor,
        EnableIf <
                Type < Functor > :: isCallable &&
                std :: tuple_size < typename functionTraits < Functor > :: ArgsType > :: value == 1
        > = 0
>
Function ( Functor ) -> Function <
        typename functionTraits < Functor > :: ReturnType (
                typename std :: tuple_element < 0, typename functionTraits < Functor > :: ArgsType > :: type
        )
>;

template <
        typename Functor,
        EnableIf <
                Type < Functor > :: isCallable &&
                std :: tuple_size < typename functionTraits < Functor > :: ArgsType > :: value == 2
        > = 0
>
Function ( Functor ) -> Function <
        typename functionTraits < Functor > :: ReturnType (
                typename std :: tuple_element < 0, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 1, typename functionTraits < Functor > :: ArgsType > :: type
        )
>;

template <
        typename Functor,
        EnableIf <
                Type < Functor > :: isCallable &&
                std :: tuple_size < typename functionTraits < Functor > :: ArgsType > :: value == 3
        > = 0
>
Function ( Functor ) -> Function <
        typename functionTraits < Functor > :: ReturnType (
                typename std :: tuple_element < 0, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 1, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 2, typename functionTraits < Functor > :: ArgsType > :: type
        )
>;

template <
        typename Functor,
        EnableIf <
                Type < Functor > :: isCallable &&
                std :: tuple_size < typename functionTraits < Functor > :: ArgsType > :: value == 4
        > = 0
>
Function ( Functor ) -> Function <
        typename functionTraits < Functor > :: ReturnType (
                typename std :: tuple_element < 0, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 1, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 2, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 3, typename functionTraits < Functor > :: ArgsType > :: type
        )
>;

template <
        typename Functor,
        EnableIf <
                Type < Functor > :: isCallable &&
                std :: tuple_size < typename functionTraits < Functor > :: ArgsType > :: value == 5
        > = 0
>
Function ( Functor ) -> Function <
        typename functionTraits < Functor > :: ReturnType (
                typename std :: tuple_element < 0, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 1, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 2, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 3, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 4, typename functionTraits < Functor > :: ArgsType > :: type
        )
>;

template <
        typename Functor,
        EnableIf <
                Type < Functor > :: isCallable &&
                std :: tuple_size < typename functionTraits < Functor > :: ArgsType > :: value == 6
        > = 0
>
Function ( Functor ) -> Function <
        typename functionTraits < Functor > :: ReturnType (
                typename std :: tuple_element < 0, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 1, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 2, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 3, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 4, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 5, typename functionTraits < Functor > :: ArgsType > :: type
        )
>;

template <
        typename Functor,
        EnableIf <
                Type < Functor > :: isCallable &&
                std :: tuple_size < typename functionTraits < Functor > :: ArgsType > :: value == 7
        > = 0
>
Function ( Functor ) -> Function <
        typename functionTraits < Functor > :: ReturnType (
                typename std :: tuple_element < 0, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 1, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 2, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 3, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 4, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 5, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 6, typename functionTraits < Functor > :: ArgsType > :: type
        )
>;

template <
        typename Functor,
        EnableIf <
                Type < Functor > :: isCallable &&
                std :: tuple_size < typename functionTraits < Functor > :: ArgsType > :: value == 8
        > = 0
>
Function ( Functor ) -> Function <
        typename functionTraits < Functor > :: ReturnType (
                typename std :: tuple_element < 0, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 1, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 2, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 3, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 4, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 5, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 6, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 7, typename functionTraits < Functor > :: ArgsType > :: type
        )
>;

template <
        typename Functor,
        EnableIf <
                Type < Functor > :: isCallable &&
                std :: tuple_size < typename functionTraits < Functor > :: ArgsType > :: value == 9
        > = 0
>
Function ( Functor ) -> Function <
        typename functionTraits < Functor > :: ReturnType (
                typename std :: tuple_element < 0, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 1, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 2, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 3, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 4, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 5, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 6, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 7, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 8, typename functionTraits < Functor > :: ArgsType > :: type
        )
>;

template <
        typename Functor,
        EnableIf <
                Type < Functor > :: isCallable &&
                std :: tuple_size < typename functionTraits < Functor > :: ArgsType > :: value == 10
        > = 0
>
Function ( Functor ) -> Function <
        typename functionTraits < Functor > :: ReturnType (
                typename std :: tuple_element < 0, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 1, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 2, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 3, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 4, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 5, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 6, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 7, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 8, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 9, typename functionTraits < Functor > :: ArgsType > :: type
        )
>;

template <
        typename Functor,
        EnableIf <
                Type < Functor > :: isCallable &&
                std :: tuple_size < typename functionTraits < Functor > :: ArgsType > :: value == 11
        > = 0
>
Function ( Functor ) -> Function <
        typename functionTraits < Functor > :: ReturnType (
                typename std :: tuple_element < 0, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 1, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 2, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 3, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 4, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 5, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 6, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 7, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 8, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 9, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 10, typename functionTraits < Functor > :: ArgsType > :: type
        )
>;

template <
        typename Functor,
        EnableIf <
                Type < Functor > :: isCallable &&
                std :: tuple_size < typename functionTraits < Functor > :: ArgsType > :: value == 12
        > = 0
>
Function ( Functor ) -> Function <
        typename functionTraits < Functor > :: ReturnType (
                typename std :: tuple_element < 0, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 1, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 2, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 3, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 4, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 5, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 6, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 7, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 8, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 9, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 10, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 11, typename functionTraits < Functor > :: ArgsType > :: type
        )
>;

template <
        typename Functor,
        EnableIf <
                Type < Functor > :: isCallable &&
                std :: tuple_size < typename functionTraits < Functor > :: ArgsType > :: value == 13
        > = 0
>
Function ( Functor ) -> Function <
        typename functionTraits < Functor > :: ReturnType (
                typename std :: tuple_element < 0, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 1, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 2, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 3, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 4, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 5, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 6, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 7, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 8, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 9, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 10, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 11, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 12, typename functionTraits < Functor > :: ArgsType > :: type
        )
>;
//0x7ffd82061210 - functor
//0x562f56c298c0 - owned functor
template <
        typename Functor,
        EnableIf <
                Type < Functor > :: isCallable &&
                std :: tuple_size < typename functionTraits < Functor > :: ArgsType > :: value == 14
        > = 0
>
Function ( Functor ) -> Function <
        typename functionTraits < Functor > :: ReturnType (
                typename std :: tuple_element < 0, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 1, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 2, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 3, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 4, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 5, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 6, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 7, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 8, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 9, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 10, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 11, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 12, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 13, typename functionTraits < Functor > :: ArgsType > :: type
        )
>;

template <
        typename Functor,
        EnableIf <
                Type < Functor > :: isCallable &&
                std :: tuple_size < typename functionTraits < Functor > :: ArgsType > :: value == 15
        > = 0
>
Function ( Functor ) -> Function <
        typename functionTraits < Functor > :: ReturnType (
                typename std :: tuple_element < 0, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 1, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 2, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 3, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 4, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 5, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 6, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 7, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 8, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 9, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 10, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 11, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 12, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 13, typename functionTraits < Functor > :: ArgsType > :: type,
                typename std :: tuple_element < 14, typename functionTraits < Functor > :: ArgsType > :: type
        )
>;

#endif //CDS_FUNCTIONDEDUCTION_HPP
