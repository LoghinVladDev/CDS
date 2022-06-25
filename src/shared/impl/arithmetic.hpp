//
// Created by loghin on 6/9/22.
//

#ifndef __CDS_SHARED_ARITHMETIC_HPP__
#define __CDS_SHARED_ARITHMETIC_HPP__

namespace cds {

    template < typename __T, typename = __T > // NOLINT(bugprone-reserved-identifier)
    constexpr auto convertTo (
            __T const & value
    ) noexcept -> __T const & {

        return value;
    }


    template < typename __T, typename __U, meta :: EnableIf < ! meta :: isSame < __T, __U > () > = 0 > // NOLINT(bugprone-reserved-identifier)
    constexpr auto convertTo (
            __T const & value
    ) noexcept -> __U {
        
        return __U(value);
    }


    template < typename __T > // NOLINT(bugprone-reserved-identifier)
    constexpr auto minOf (
            __T const & value
    ) noexcept -> __T const & {

        return value;
    }


    template < typename __T > // NOLINT(bugprone-reserved-identifier)
    constexpr auto maxOf (
            __T const & value
    ) noexcept -> __T const & {

        return value;
    }


    template < typename __T > // NOLINT(bugprone-reserved-identifier)
    constexpr auto minOf (
            __T const & left,
            __T const & right
    ) noexcept -> __T const & {

        return left < right ? left : right;
    }


    template < typename __T > // NOLINT(bugprone-reserved-identifier)
    constexpr auto maxOf (
            __T const & left,
            __T const & right
    ) noexcept -> __T const & {

        return left > right ? left : right;
    }


    template <
            typename __LeftType, // NOLINT(bugprone-reserved-identifier)
            typename __RightType, // NOLINT(bugprone-reserved-identifier)
            typename __Common = meta :: Common < __LeftType, __RightType >, // NOLINT(bugprone-reserved-identifier)
            meta :: EnableIf < ! meta :: isSame < __LeftType, __RightType > () > = 0
    > constexpr auto minOf (
            __LeftType  const & left,
            __RightType const & right
    ) noexcept -> __Common {

        return convertTo < __Common > ( left ) < convertTo < __Common > ( right ) ? convertTo < __Common > ( left ) : convertTo < __Common > ( right );
    }


    template <
            typename __FirstType,  // NOLINT(bugprone-reserved-identifier)
            typename ... __RemainingTypes, // NOLINT(bugprone-reserved-identifier)
            typename __Common = meta :: Common < __FirstType, __RemainingTypes ... > // NOLINT(bugprone-reserved-identifier)
    > constexpr auto minOf (
            __FirstType         const &     firstArgument,
            __RemainingTypes    const & ... remainingTypes
    ) noexcept -> __Common {

        return minOf < __Common > ( firstArgument, minOf ( remainingTypes ... ) );
    }


    template <
            typename __LeftType, // NOLINT(bugprone-reserved-identifier)
            typename __RightType, // NOLINT(bugprone-reserved-identifier)
            typename __Common = meta :: Common < __LeftType, __RightType >, // NOLINT(bugprone-reserved-identifier)
            meta :: EnableIf < ! meta :: isSame < __LeftType, __RightType > () > = 0
    > constexpr auto maxOf (
            __LeftType  const & left,
            __RightType const & right
    ) noexcept -> __Common {

        return convertTo < __Common > ( left ) > convertTo < __Common > ( right ) ? convertTo < __Common > ( left ) : convertTo < __Common > ( right );
    }


    template <
            typename __FirstType, // NOLINT(bugprone-reserved-identifier)
            typename ... __RemainingTypes, // NOLINT(bugprone-reserved-identifier)
            typename __Common = meta :: Common < __FirstType, __RemainingTypes ... > // NOLINT(bugprone-reserved-identifier)
    > constexpr auto maxOf (
            __FirstType         const &     firstArgument,
            __RemainingTypes    const & ... remainingTypes
    ) noexcept -> __Common {

        return maxOf < __Common > ( firstArgument, maxOf ( remainingTypes ... ) );
    }

}

#endif // __CDS_SHARED_ARITHMETIC_HPP__
