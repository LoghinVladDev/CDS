/*
 * Created by loghin on 6/9/22.
 */

#ifndef __CDS_SHARED_GENERAL_PREDICATES_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_SHARED_GENERAL_PREDICATES_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/meta/TypeTraits>

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */
    namespace predicates {

        template <
                typename __LeftType,                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                typename __RightType = __LeftType,  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                meta :: EnableIf < meta :: lessThanPossible < __LeftType, __RightType > () > = 0
        > constexpr auto lessThan (
                __LeftType    const & leftValue,
                __RightType   const & rightValue
        ) noexcept ( noexcept ( leftValue < rightValue ) ) -> decltype ( leftValue < rightValue ) {

            return leftValue < rightValue;
        }


        template <
                typename __LeftType,                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                typename __RightType = __LeftType,  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                meta :: EnableIf < ! meta :: lessThanPossible < __LeftType, __RightType > () > = 0
        > constexpr auto lessThan (
                __LeftType    const & /* left */,
                __RightType   const & /* right */
        ) noexcept -> bool {

            static_assert ( meta :: lessThanPossible < __LeftType, __RightType > (), "Not possible to invoke lessThan if LeftType < RightType is not possible" );
            return false;
        }


        template <
                typename __LeftType,                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                typename __RightType = __LeftType,  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                meta :: EnableIf < meta :: greaterThanPossible < __LeftType, __RightType > () > = 0
        > constexpr auto greaterThan (
                __LeftType    const & leftValue,
                __RightType   const & rightValue
        ) noexcept ( noexcept ( leftValue > rightValue ) ) -> decltype ( leftValue > rightValue ) {

            return leftValue > rightValue;
        }


        template <
                typename __LeftType,                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                typename __RightType = __LeftType,  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                meta :: EnableIf < ! meta :: greaterThanPossible < __LeftType, __RightType > () > = 0
        > constexpr auto greaterThan (
                __LeftType    const & /* left */,
                __RightType   const & /* right */
        ) noexcept -> bool {

            static_assert ( meta :: greaterThanPossible < __LeftType, __RightType > (), "Not possible to invoke greaterThan if LeftType > RightType is not possible" );
            return false;
        }


        template <
                typename __LeftType,                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                typename __RightType = __LeftType,  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                meta :: EnableIf < meta :: lessThanOrEqualToPossible < __LeftType, __RightType > () > = 0
        > constexpr auto lessThanOrEqualTo (
                __LeftType    const & leftValue,
                __RightType   const & rightValue
        ) noexcept ( noexcept ( leftValue <= rightValue ) ) -> decltype ( leftValue <= rightValue ) {

            return leftValue <= rightValue;
        }


        template <
                typename __LeftType,                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                typename __RightType = __LeftType,  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                meta :: EnableIf < ! meta :: lessThanOrEqualToPossible < __LeftType, __RightType > () > = 0
        > constexpr auto lessThanOrEqualTo (
                __LeftType    const & /* left */,
                __RightType   const & /* right */
        ) noexcept -> bool {

            static_assert ( meta :: lessThanOrEqualToPossible < __LeftType, __RightType > (), "Not possible to invoke lessThanOrEqualTo if LeftType <= RightType is not possible" );
            return false;
        }


        template <
                typename __LeftType,                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                typename __RightType = __LeftType,  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                meta :: EnableIf < meta :: greaterThanOrEqualToPossible < __LeftType, __RightType > () > = 0
        > constexpr auto greaterThanOrEqualTo (
                __LeftType    const & leftValue,
                __RightType   const & rightValue
        ) noexcept ( noexcept ( leftValue >= rightValue ) ) -> decltype ( leftValue >= rightValue ) {

            return leftValue >= rightValue;
        }


        template <
                typename __LeftType,                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                typename __RightType = __LeftType,  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                meta :: EnableIf < ! meta :: greaterThanOrEqualToPossible < __LeftType, __RightType > () > = 0
        > constexpr auto greaterThanOrEqualTo (
                __LeftType    const & /* left */,
                __RightType   const & /* right */
        ) noexcept -> bool {

            static_assert ( meta :: greaterThanOrEqualToPossible < __LeftType, __RightType > (), "Not possible to invoke greaterThanOrEqualTo if LeftType >= RightType is not possible" );
            return false;
        }


        template <
                typename __LeftType,                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                typename __RightType = __LeftType,  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                meta :: EnableIf < meta :: equalToPossible < __LeftType, __RightType > () > = 0
        > constexpr auto equalTo (
                __LeftType    const & leftValue,
                __RightType   const & rightValue
        ) noexcept ( noexcept ( leftValue == rightValue ) ) -> decltype ( leftValue == rightValue ) {

            return leftValue == rightValue;
        }


        template <
                typename __LeftType,                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                typename __RightType = __LeftType,  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                meta :: EnableIf < ! meta :: equalToPossible < __LeftType, __RightType > () > = 0
        > constexpr auto equalTo (
                __LeftType    const & /* left */,
                __RightType   const & /* right */
        ) noexcept -> bool {

            static_assert ( meta :: equalToPossible < __LeftType, __RightType > (), "Not possible to invoke equalTo if LeftType == RightType is not possible" );
            return false;
        }


        template <
                typename __LeftType,                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                typename __RightType = __LeftType,  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                meta :: EnableIf < meta :: notEqualToPossible < __LeftType, __RightType > () > = 0
        > constexpr auto notEqualTo (
                __LeftType    const & leftValue,
                __RightType   const & rightValue
        ) noexcept ( noexcept ( leftValue != rightValue ) ) -> decltype ( leftValue != rightValue ) {

            return leftValue != rightValue;
        }


        template <
                typename __LeftType,                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                typename __RightType = __LeftType,  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                meta :: EnableIf < ! meta :: notEqualToPossible < __LeftType, __RightType > () > = 0
        > constexpr auto notEqualTo (
                __LeftType    const & /* left */,
                __RightType   const & /* right */
        ) noexcept -> bool {

            static_assert ( meta :: notEqualToPossible < __LeftType, __RightType > (), "Not possible to invoke notEqualTo if LeftType != RightType is not possible" );
            return false;
        }


        template < typename __T > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto alwaysTrue (
                __T const & /* object */
        ) noexcept -> bool {

            return true;
        }


        template < typename __T > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto alwaysFalse (
                __T const & /* object */
        ) noexcept -> bool {

            return false;
        }

    } /* namespace predicates */
} /* namespace cds */

#endif /* __CDS_SHARED_GENERAL_PREDICATES_HPP__ */
