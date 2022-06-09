//
// Created by loghin on 29.10.2021.
//

#ifndef CDS_FUNCTIONDEDUCTION_HPP
#define CDS_FUNCTIONDEDUCTION_HPP

#include <CDS/meta/FunctionTraits>

namespace cds {
    
//    template < typename ... __ArgumentTypes >
//    __CDS_NoDiscard constexpr static auto tupleSize ( experimental :: Tuple < __ArgumentTypes ... > const & ) noexcept -> Size {
//        return 0ULL;
//    }
//
//    template < Size __index, typename ... __ArgumentTypes >
//    __CDS_NoDiscard constexpr static auto tupleElement ( Tuple < __ArgumentTypes ... > const & ) noexcept -> int {
//        return 0ULL;
//    }
//
//    template < int ... > struct seq {};
//    template < int n, int ... s > struct gens : gens < n - 1, n - 1, s ... > {};
//    template < int ... s > struct gens < 0, s ... > { using type = seq < s ... >; };
//
//    template < typename T, int index >
//    constexpr auto get ( T const & e ) -> decltype ( e.template get <index> () );

}

namespace cds {

    template < typename ReturnType, typename ... ArgumentTypes >
    Function ( ReturnType (*) ( ArgumentTypes ... ) ) -> Function < ReturnType ( ArgumentTypes ... ) >;
//
//    template < typename Functor, typename AsTuple = meta :: ArgumentsOf < Functor >, typename s = cds :: gens < meta :: valueOf < AsTuple > ().size() >, typename s2 =  meta :: EnableIf < meta :: isCallable < Functor > () > = 0 >
//    Function ( Functor ) -> Function < cds :: get <

}

//namespace cds {
//
//    template < typename ReturnType, typename ... ArgumentTypes >
//    Function ( ReturnType (*) ( ArgumentTypes ... ) ) -> Function < ReturnType ( ArgumentTypes ... ) >;
//
//    template <
//            typename Functor,
//            meta :: EnableIf <
//                    meta :: isCallable < Functor > () &&
//                    tupleSize < meta :: ArgumentsOf < Functor > > () == 0
//            > = 0
//    >
//    Function ( Functor ) -> Function <
//            meta :: ReturnOf < Functor > (
//
//            )
//    >;
//
//    template <
//            typename Functor,
//            meta :: EnableIf <
//                    meta :: isCallable < Functor > () &&
//                    tupleSize < meta :: ArgumentsOf < Functor > > () == 1
//            > = 0
//    >
//    Function ( Functor ) -> Function <
//            meta :: ReturnOf < Functor > (
//                    tupleElement < 0u, meta :: ArgumentsOf < Functor > > ()
//            )
//    >;
//
//    template <
//            typename Functor,
//            meta :: EnableIf <
//                    meta :: isCallable < Functor > () &&
//                    tupleSize < meta :: ArgumentsOf < Functor > > () == 2
//            > = 0
//    >
//    Function ( Functor ) -> Function <
//            meta :: ReturnOf < Functor > (
//                    tupleElement < 0u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 1u, meta :: ArgumentsOf < Functor > > ()
//            )
//    >;
//
//    template <
//            typename Functor,
//            meta :: EnableIf <
//                    meta :: isCallable < Functor > () &&
//                    tupleSize < meta :: ArgumentsOf < Functor > > () == 3
//            > = 0
//    >
//    Function ( Functor ) -> Function <
//            meta :: ReturnOf < Functor > (
//                    tupleElement < 0u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 1u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 2u, meta :: ArgumentsOf < Functor > > ()
//            )
//    >;
//
//    template <
//            typename Functor,
//            meta :: EnableIf <
//                    meta :: isCallable < Functor > () &&
//                    tupleSize < meta :: ArgumentsOf < Functor > > () == 4
//            > = 0
//    >
//    Function ( Functor ) -> Function <
//            meta :: ReturnOf < Functor > (
//                    tupleElement < 0u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 1u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 2u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 3u, meta :: ArgumentsOf < Functor > > ()
//            )
//    >;
//
//    template <
//            typename Functor,
//            meta :: EnableIf <
//                    meta :: isCallable < Functor > () &&
//                    tupleSize < meta :: ArgumentsOf < Functor > > () == 5
//            > = 0
//    >
//    Function ( Functor ) -> Function <
//            meta :: ReturnOf < Functor > (
//                    tupleElement < 0u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 1u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 2u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 3u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 4u, meta :: ArgumentsOf < Functor > > ()
//            )
//    >;
//
//    template <
//            typename Functor,
//            meta :: EnableIf <
//                    meta :: isCallable < Functor > () &&
//                    tupleSize < meta :: ArgumentsOf < Functor > > () == 6
//            > = 0
//    >
//    Function ( Functor ) -> Function <
//            meta :: ReturnOf < Functor > (
//                    tupleElement < 0u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 1u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 2u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 3u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 4u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 5u, meta :: ArgumentsOf < Functor > > ()
//            )
//    >;
//
//    template <
//            typename Functor,
//            meta :: EnableIf <
//                    meta :: isCallable < Functor > () &&
//                    tupleSize < meta :: ArgumentsOf < Functor > > () == 7
//            > = 0
//    >
//    Function ( Functor ) -> Function <
//            meta :: ReturnOf < Functor > (
//                    tupleElement < 0u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 1u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 2u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 3u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 4u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 5u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 6u, meta :: ArgumentsOf < Functor > > ()
//            )
//    >;
//
//    template <
//            typename Functor,
//            meta :: EnableIf <
//                    meta :: isCallable < Functor > () &&
//                    tupleSize < meta :: ArgumentsOf < Functor > > () == 8
//            > = 0
//    >
//    Function ( Functor ) -> Function <
//            meta :: ReturnOf < Functor > (
//                    tupleElement < 0u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 1u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 2u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 3u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 4u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 5u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 6u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 7u, meta :: ArgumentsOf < Functor > > ()
//            )
//    >;
//
//    template <
//            typename Functor,
//            meta :: EnableIf <
//                    meta :: isCallable < Functor > () &&
//                    tupleSize < meta :: ArgumentsOf < Functor > > () == 9
//            > = 0
//    >
//    Function ( Functor ) -> Function <
//            meta :: ReturnOf < Functor > (
//                    tupleElement < 0u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 1u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 2u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 3u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 4u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 5u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 6u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 7u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 8u, meta :: ArgumentsOf < Functor > > ()
//            )
//    >;
//
//    template <
//            typename Functor,
//            meta :: EnableIf <
//                    meta :: isCallable < Functor > () &&
//                    tupleSize < meta :: ArgumentsOf < Functor > > () == 10
//            > = 0
//    >
//    Function ( Functor ) -> Function <
//            meta :: ReturnOf < Functor > (
//                    tupleElement < 0u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 1u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 2u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 3u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 4u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 5u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 6u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 7u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 8u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 9u, meta :: ArgumentsOf < Functor > > ()
//            )
//    >;
//
//    template <
//            typename Functor,
//            meta :: EnableIf <
//                    meta :: isCallable < Functor > () &&
//                    tupleSize < meta :: ArgumentsOf < Functor > > () == 11
//            > = 0
//    >
//    Function ( Functor ) -> Function <
//            meta :: ReturnOf < Functor > (
//                    tupleElement < 0u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 1u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 2u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 3u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 4u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 5u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 6u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 7u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 8u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 9u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 10u, meta :: ArgumentsOf < Functor > > ()
//            )
//    >;
//
//    template <
//            typename Functor,
//            meta :: EnableIf <
//                    meta :: isCallable < Functor > () &&
//                    tupleSize < meta :: ArgumentsOf < Functor > > () == 12
//            > = 0
//    >
//    Function ( Functor ) -> Function <
//            meta :: ReturnOf < Functor > (
//                    tupleElement < 0u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 1u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 2u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 3u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 4u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 5u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 6u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 7u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 8u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 9u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 10u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 11u, meta :: ArgumentsOf < Functor > > ()
//            )
//    >;
//
//    template <
//            typename Functor,
//            meta :: EnableIf <
//                    meta :: isCallable < Functor > () &&
//                    tupleSize < meta :: ArgumentsOf < Functor > > () == 13
//            > = 0
//    >
//    Function ( Functor ) -> Function <
//            meta :: ReturnOf < Functor > (
//                    tupleElement < 0u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 1u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 2u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 3u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 4u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 5u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 6u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 7u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 8u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 9u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 10u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 11u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 12u, meta :: ArgumentsOf < Functor > > ()
//            )
//    >;
//
//
//    template <
//            typename Functor,
//            meta :: EnableIf <
//                    meta :: isCallable < Functor > () &&
//                    tupleSize < meta :: ArgumentsOf < Functor > > () == 14
//            > = 0
//    >
//    Function ( Functor ) -> Function <
//            meta :: ReturnOf < Functor > (
//                    tupleElement < 0u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 1u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 2u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 3u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 4u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 5u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 6u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 7u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 8u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 9u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 10u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 11u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 12u, meta :: ArgumentsOf < Functor > > (),
//                    tupleElement < 13u, meta :: ArgumentsOf < Functor > > ()
//            )
//    >;
//
//    template <
//            typename Functor,
//            meta :: EnableIf <
//                    meta :: isCallable < Functor > () &&
//                    tupleSize < meta :: ArgumentsOf < Functor > > () == 15
//            > = 0
//    >
//    Function ( Functor ) -> Function <
//            meta :: ReturnOf < Functor > (
//                    decltype ( tupleElement < 0u, meta :: ArgumentsOf < Functor > > () ),
//                    decltype ( tupleElement < 1u, meta :: ArgumentsOf < Functor > > () ),
//                    decltype ( tupleElement < 2u, meta :: ArgumentsOf < Functor > > () ),
//                    decltype ( tupleElement < 3u, meta :: ArgumentsOf < Functor > > () ),
//                    decltype ( tupleElement < 4u, meta :: ArgumentsOf < Functor > > () ),
//                    decltype ( tupleElement < 5u, meta :: ArgumentsOf < Functor > > () ),
//                    decltype ( tupleElement < 6u, meta :: ArgumentsOf < Functor > > () ),
//                    decltype ( tupleElement < 7u, meta :: ArgumentsOf < Functor > > () ),
//                    decltype ( tupleElement < 8u, meta :: ArgumentsOf < Functor > > () ),
//                    decltype ( tupleElement < 9u, meta :: ArgumentsOf < Functor > > () ),
//                    decltype ( tupleElement < 10u, meta :: ArgumentsOf < Functor > > () ),
//                    decltype ( tupleElement < 11u, meta :: ArgumentsOf < Functor > > () ),
//                    decltype ( tupleElement < 12u, meta :: ArgumentsOf < Functor > > () ),
//                    decltype ( tupleElement < 13u, meta :: ArgumentsOf < Functor > > () ),
//                    decltype ( tupleElement < 14u, meta :: ArgumentsOf < Functor > > ( ))
//            )
//    >;
//
//}

#endif //CDS_FUNCTIONDEDUCTION_HPP
