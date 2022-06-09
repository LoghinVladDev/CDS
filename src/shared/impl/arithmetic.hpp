//
// Created by loghin on 6/9/22.
//

#ifndef __CDS_ARITHMETIC_HPP__
#define __CDS_ARITHMETIC_HPP__

namespace cds {

    template < typename T, typename = T >
    constexpr auto convertTo ( T const & value ) noexcept -> T const & {

        return value;
    }

    template < typename T, typename U, meta :: EnableIf < ! meta :: isSame < T, U > () > = 0 >
    constexpr auto convertTo ( T const & value ) noexcept -> U {
        
        return U(value);
    }

    template < typename T >
    constexpr auto minOf ( T const & value ) noexcept -> T const & {

        return value;
    }

    template < typename T >
    constexpr auto maxOf ( T const & value ) noexcept -> T const & {

        return value;
    }

    template < typename T >
    constexpr auto minOf ( T const & left, T const & right ) noexcept -> T const & {

        return left < right ? left : right;
    }

    template < typename T >
    constexpr auto maxOf ( T const & left, T const & right ) noexcept -> T const & {

        return left > right ? left : right;
    }

    template <
            typename LeftType,
            typename RightType,
            typename Common = meta :: Common < LeftType, RightType >,
            meta :: EnableIf < ! meta :: isSame < LeftType, RightType > () > = 0
    > constexpr auto minOf ( LeftType const & left, RightType const & right ) noexcept -> Common {

        return convertTo < Common > ( left ) < convertTo < Common > ( right ) ? convertTo < Common > ( left ) : convertTo < Common > ( right );
    }

    template < typename FirstType, typename ... RemainingTypes, typename Common = meta :: Common < FirstType, RemainingTypes ... > >
    constexpr auto minOf ( FirstType const & firstArgument, RemainingTypes const & ... remainingTypes ) noexcept -> meta :: Common < FirstType, RemainingTypes ... > {

        return minOf < Common > ( firstArgument, minOf ( remainingTypes ... ) );
    }

    template <
            typename LeftType,
            typename RightType,
            typename Common = meta :: Common < LeftType, RightType >,
            meta :: EnableIf < ! meta :: isSame < LeftType, RightType > () > = 0
    > constexpr auto maxOf ( LeftType const & left, RightType const & right ) noexcept -> Common {

        return convertTo < Common > ( left ) > convertTo < Common > ( right ) ? convertTo < Common > ( left ) : convertTo < Common > ( right );
    }

    template < typename FirstType, typename ... RemainingTypes, typename Common = meta :: Common < FirstType, RemainingTypes ... > >
    constexpr auto maxOf ( FirstType const & firstArgument, RemainingTypes const & ... remainingTypes ) noexcept -> meta :: Common < FirstType, RemainingTypes ... > {

        return maxOf < Common > ( firstArgument, maxOf ( remainingTypes ... ) );
    }

}

#endif // __CDS_ARITHMETIC_HPP__
