//
// Created by loghin on 6/9/22.
//

#ifndef __CDS_GENERAL_PREDICATES_HPP__
#define __CDS_GENERAL_PREDICATES_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace predicates {

        template <
                typename __LeftType, // NOLINT(bugprone-reserved-identifier)
                typename __RightType = __LeftType, // NOLINT(bugprone-reserved-identifier)
                meta :: EnableIf < meta :: lessThanPossible < __LeftType, __RightType > () > = 0
        > constexpr auto lessThan (
                __LeftType    const & leftValue,
                __RightType   const & rightValue
        ) noexcept ( noexcept ( leftValue < rightValue ) ) -> decltype ( leftValue < rightValue ) {

            return leftValue < rightValue;
        }


        template <
                typename __LeftType, // NOLINT(bugprone-reserved-identifier)
                typename __RightType = __LeftType, // NOLINT(bugprone-reserved-identifier)
                meta :: EnableIf < ! meta :: lessThanPossible < __LeftType, __RightType > () > = 0
        > constexpr auto lessThan (
                __LeftType    const &,
                __RightType   const &
        ) noexcept -> bool {

            static_assert ( meta :: lessThanPossible < __LeftType, __RightType > (), "Not possible to invoke lessThan if LeftType < RightType is not possible" );
            return false;
        }


        template <
                typename __LeftType, // NOLINT(bugprone-reserved-identifier)
                typename __RightType = __LeftType, // NOLINT(bugprone-reserved-identifier)
                meta :: EnableIf < meta :: greaterThanPossible < __LeftType, __RightType > () > = 0
        > constexpr auto greaterThan (
                __LeftType    const & leftValue,
                __RightType   const & rightValue
        ) noexcept ( noexcept ( leftValue > rightValue ) ) -> decltype ( leftValue > rightValue ) {

            return leftValue > rightValue;
        }


        template <
                typename __LeftType, // NOLINT(bugprone-reserved-identifier)
                typename __RightType = __LeftType, // NOLINT(bugprone-reserved-identifier)
                meta :: EnableIf < ! meta :: greaterThanPossible < __LeftType, __RightType > () > = 0
        > constexpr auto greaterThan (
                __LeftType    const &,
                __RightType   const &
        ) noexcept -> bool {

            static_assert ( meta :: greaterThanPossible < __LeftType, __RightType > (), "Not possible to invoke greaterThan if LeftType > RightType is not possible" );
            return false;
        }


        template <
                typename __LeftType, // NOLINT(bugprone-reserved-identifier)
                typename __RightType = __LeftType, // NOLINT(bugprone-reserved-identifier)
                meta :: EnableIf < meta :: lessThanOrEqualToPossible < __LeftType, __RightType > () > = 0
        > constexpr auto lessThanOrEqualTo (
                __LeftType    const & leftValue,
                __RightType   const & rightValue
        ) noexcept ( noexcept ( leftValue <= rightValue ) ) -> decltype ( leftValue <= rightValue ) {

            return leftValue <= rightValue;
        }


        template <
                typename __LeftType, // NOLINT(bugprone-reserved-identifier)
                typename __RightType = __LeftType, // NOLINT(bugprone-reserved-identifier)
                meta :: EnableIf < ! meta :: lessThanOrEqualToPossible < __LeftType, __RightType > () > = 0
        > constexpr auto lessThanOrEqualTo (
                __LeftType    const &,
                __RightType   const &
        ) noexcept -> bool {

            static_assert ( meta :: lessThanOrEqualToPossible < __LeftType, __RightType > (), "Not possible to invoke lessThanOrEqualTo if LeftType <= RightType is not possible" );
            return false;
        }


        template <
                typename __LeftType,  // NOLINT(bugprone-reserved-identifier)
                typename __RightType = __LeftType, // NOLINT(bugprone-reserved-identifier)
                meta :: EnableIf < meta :: greaterThanOrEqualToPossible < __LeftType, __RightType > () > = 0
        > constexpr auto greaterThanOrEqualTo (
                __LeftType    const & leftValue,
                __RightType   const & rightValue
        ) noexcept ( noexcept ( leftValue >= rightValue ) ) -> decltype ( leftValue >= rightValue ) {

            return leftValue >= rightValue;
        }


        template <
                typename __LeftType, // NOLINT(bugprone-reserved-identifier)
                typename __RightType = __LeftType, // NOLINT(bugprone-reserved-identifier)
                meta :: EnableIf < ! meta :: greaterThanOrEqualToPossible < __LeftType, __RightType > () > = 0
        > constexpr auto greaterThanOrEqualTo (
                __LeftType    const &,
                __RightType   const &
        ) noexcept -> bool {

            static_assert ( meta :: greaterThanOrEqualToPossible < __LeftType, __RightType > (), "Not possible to invoke greaterThanOrEqualTo if LeftType >= RightType is not possible" );
            return false;
        }


        template <
                typename __LeftType,  // NOLINT(bugprone-reserved-identifier)
                typename __RightType = __LeftType, // NOLINT(bugprone-reserved-identifier)
                meta :: EnableIf < meta :: equalToPossible < __LeftType, __RightType > () > = 0
        > constexpr auto equalTo (
                __LeftType    const & leftValue,
                __RightType   const & rightValue
        ) noexcept ( noexcept ( leftValue == rightValue ) ) -> decltype ( leftValue == rightValue ) {

            return leftValue == rightValue;
        }


        template <
                typename __LeftType, // NOLINT(bugprone-reserved-identifier)
                typename __RightType = __LeftType, // NOLINT(bugprone-reserved-identifier)
                meta :: EnableIf < ! meta :: equalToPossible < __LeftType, __RightType > () > = 0
        > constexpr auto equalTo (
                __LeftType    const &,
                __RightType   const &
        ) noexcept -> bool {

            static_assert ( meta :: equalToPossible < __LeftType, __RightType > (), "Not possible to invoke equalTo if LeftType == RightType is not possible" );
            return false;
        }


        template <
                typename __LeftType, // NOLINT(bugprone-reserved-identifier)
                typename __RightType = __LeftType, // NOLINT(bugprone-reserved-identifier)
                meta :: EnableIf < meta :: notEqualToPossible < __LeftType, __RightType > () > = 0
        > constexpr auto notEqualTo (
                __LeftType    const & leftValue,
                __RightType   const & rightValue
        ) noexcept ( noexcept ( leftValue != rightValue ) ) -> decltype ( leftValue != rightValue ) {

            return leftValue != rightValue;
        }


        template <
                typename __LeftType,  // NOLINT(bugprone-reserved-identifier)
                typename __RightType = __LeftType, // NOLINT(bugprone-reserved-identifier)
                meta :: EnableIf < ! meta :: notEqualToPossible < __LeftType, __RightType > () > = 0
        > constexpr auto notEqualTo (
                __LeftType    const &,
                __RightType   const &
        ) noexcept -> bool {

            static_assert ( meta :: notEqualToPossible < __LeftType, __RightType > (), "Not possible to invoke notEqualTo if LeftType != RightType is not possible" );
            return false;
        }


        template < typename __T > // NOLINT(bugprone-reserved-identifier)
        constexpr auto alwaysTrue (
                __T const &
        ) noexcept -> bool {

            return true;
        }

        template < typename __T > // NOLINT(bugprone-reserved-identifier)
        constexpr auto alwaysFalse (
                __T const &
        ) noexcept -> bool {

            return false;
        }
    }
}

#endif // __CDS_GENERAL_PREDICATES_HPP__
