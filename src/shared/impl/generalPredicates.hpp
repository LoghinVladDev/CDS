//
// Created by loghin on 6/9/22.
//

#ifndef __CDS_GENERAL_PREDICATES_HPP__
#define __CDS_GENERAL_PREDICATES_HPP__

namespace cds {
    namespace predicates {
        template < typename LeftType, typename RightType = LeftType, meta :: EnableIf < meta :: lessThanPossible < LeftType, RightType > () > = 0 >
        constexpr auto lessThan (
                LeftType    const & leftValue,
                RightType   const & rightValue
        ) noexcept ( noexcept ( leftValue < rightValue ) ) -> decltype ( leftValue < rightValue ) {

            return leftValue < rightValue;
        }

        template < typename LeftType, typename RightType = LeftType, meta :: EnableIf < ! meta :: lessThanPossible < LeftType, RightType > () > = 0 >
        constexpr auto lessThan (
                LeftType    const &,
                RightType   const &
        ) noexcept -> bool {

            static_assert ( meta :: lessThanPossible < LeftType, RightType > (), "Not possible to invoke lessThan if LeftType < RightType is not possible" );
            return false;
        }

        template < typename LeftType, typename RightType = LeftType, meta :: EnableIf < meta :: greaterThanPossible < LeftType, RightType > () > = 0 >
        constexpr auto greaterThan (
                LeftType    const & leftValue,
                RightType   const & rightValue
        ) noexcept ( noexcept ( leftValue > rightValue ) ) -> decltype ( leftValue > rightValue ) {

            return leftValue > rightValue;
        }

        template < typename LeftType, typename RightType = LeftType, meta :: EnableIf < ! meta :: greaterThanPossible < LeftType, RightType > () > = 0 >
        constexpr auto greaterThan (
                LeftType    const &,
                RightType   const &
        ) noexcept -> bool {

            static_assert ( meta :: greaterThanPossible < LeftType, RightType > (), "Not possible to invoke greaterThan if LeftType > RightType is not possible" );
            return false;
        }

        template < typename LeftType, typename RightType = LeftType, meta :: EnableIf < meta :: lessThanOrEqualToPossible < LeftType, RightType > () > = 0 >
        constexpr auto lessThanOrEqualTo (
                LeftType    const & leftValue,
                RightType   const & rightValue
        ) noexcept ( noexcept ( leftValue <= rightValue ) ) -> decltype ( leftValue <= rightValue ) {

            return leftValue <= rightValue;
        }

        template < typename LeftType, typename RightType = LeftType, meta :: EnableIf < ! meta :: lessThanOrEqualToPossible < LeftType, RightType > () > = 0 >
        constexpr auto lessThanOrEqualTo (
                LeftType    const &,
                RightType   const &
        ) noexcept -> bool {

            static_assert ( meta :: lessThanOrEqualToPossible < LeftType, RightType > (), "Not possible to invoke lessThanOrEqualTo if LeftType <= RightType is not possible" );
            return false;
        }

        template < typename LeftType, typename RightType = LeftType, meta :: EnableIf < meta :: greaterThanOrEqualToPossible < LeftType, RightType > () > = 0 >
        constexpr auto greaterThanOrEqualTo (
                LeftType    const & leftValue,
                RightType   const & rightValue
        ) noexcept ( noexcept ( leftValue >= rightValue ) ) -> decltype ( leftValue >= rightValue ) {

            return leftValue >= rightValue;
        }

        template < typename LeftType, typename RightType = LeftType, meta :: EnableIf < ! meta :: greaterThanOrEqualToPossible < LeftType, RightType > () > = 0 >
        constexpr auto greaterThanOrEqualTo (
                LeftType    const &,
                RightType   const &
        ) noexcept -> bool {

            static_assert ( meta :: greaterThanOrEqualToPossible < LeftType, RightType > (), "Not possible to invoke greaterThanOrEqualTo if LeftType >= RightType is not possible" );
            return false;
        }

        template < typename LeftType, typename RightType = LeftType, meta :: EnableIf < meta :: equalToPossible < LeftType, RightType > () > = 0 >
        constexpr auto equalTo (
                LeftType    const & leftValue,
                RightType   const & rightValue
        ) noexcept ( noexcept ( leftValue == rightValue ) ) -> decltype ( leftValue == rightValue ) {

            return leftValue == rightValue;
        }

        template < typename LeftType, typename RightType = LeftType, meta :: EnableIf < ! meta :: equalToPossible < LeftType, RightType > () > = 0 >
        constexpr auto equalTo (
                LeftType    const &,
                RightType   const &
        ) noexcept -> bool {

            static_assert ( meta :: equalToPossible < LeftType, RightType > (), "Not possible to invoke equalTo if LeftType == RightType is not possible" );
            return false;
        }

        template < typename LeftType, typename RightType = LeftType, meta :: EnableIf < meta :: notEqualToPossible < LeftType, RightType > () > = 0 >
        constexpr auto notEqualTo (
                LeftType    const & leftValue,
                RightType   const & rightValue
        ) noexcept ( noexcept ( leftValue != rightValue ) ) -> decltype ( leftValue != rightValue ) {

            return leftValue != rightValue;
        }

        template < typename LeftType, typename RightType = LeftType, meta :: EnableIf < ! meta :: notEqualToPossible < LeftType, RightType > () > = 0 >
        constexpr auto notEqualTo (
                LeftType    const &,
                RightType   const &
        ) noexcept -> bool {

            static_assert ( meta :: notEqualToPossible < LeftType, RightType > (), "Not possible to invoke notEqualTo if LeftType != RightType is not possible" );
            return false;
        }

        template < typename T >
        constexpr auto alwaysTrue (
                T const &
        ) noexcept -> bool {

            return true;
        }

        template < typename T >
        constexpr auto alwaysFalse (
                T const &
        ) noexcept -> bool {

            return false;
        }
    }
}

#endif // __CDS_GENERAL_PREDICATES_HPP__
