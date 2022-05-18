//
// Created by uic70278 on 5/18/2022.
//

#ifndef __CDS_EX_TRAITS_HPP__
#define __CDS_EX_TRAITS_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental { // NOLINT(modernize-concat-nested-namespaces)
        namespace meta {

            template < typename ... > using Void = void;

            template < typename Type > auto valueOf () noexcept -> Type;
            template < typename Type > auto referenceOf () noexcept -> Type &;
            template < typename Type > auto addressOf () noexcept -> Type *;

            template < typename IntegralType, IntegralType _value >
            struct IntegralConstant {
                constexpr static IntegralType value = _value;
                using ValueType                     = IntegralType;
                using Type                          = IntegralConstant < IntegralType, _value >;
            };

            template < bool value >
            using BoolConstant = IntegralConstant < bool, value >;

            using TrueType  = BoolConstant < true >;
            using FalseType = BoolConstant < false >;

            template < bool, typename ReplacedType = void >
            struct EnableIf {};

            template < typename ReplacedType >
            struct EnableIf < true, ReplacedType > {
                using Type = ReplacedType;
            };

            template < bool, typename TypeIfTrue, typename TypeIfFalse >
            struct Conditional {
                using Type = TypeIfTrue;
            };

            template < typename TypeIfTrue, typename TypeIfFalse >
            struct Conditional < false, TypeIfTrue, TypeIfFalse > {
                using Type = TypeIfFalse;
            };

            template < typename LeftType, typename RightType >
            struct IsSame : FalseType {};

            template < typename Type >
            struct IsSame < Type, Type > : TrueType {};


            template < typename LeftType, typename RightType, typename = Void <> > struct LessThanPossible : FalseType {};
            template < typename LeftType, typename RightType, typename = Void <> > struct GreaterThanPossible : FalseType {};
            template < typename LeftType, typename RightType, typename = Void <> > struct LessThanOrEqualToPossible : FalseType {};
            template < typename LeftType, typename RightType, typename = Void <> > struct GreaterThanOrEqualToPossible : FalseType {};
            template < typename LeftType, typename RightType, typename = Void <> > struct EqualToPossible : FalseType {};
            template < typename LeftType, typename RightType, typename = Void <> > struct NotEqualToPossible : FalseType {};

            template < typename LeftType, typename RightType >
            struct LessThanPossible < LeftType, RightType, Void < decltype ( valueOf < LeftType > () < valueOf < RightType > () ) > > : TrueType {};
        }


        template < bool enableCondition, typename ReplacedType = int >
        using EnableIf = typename meta :: EnableIf < enableCondition, ReplacedType > :: Type;

        template < bool condition, typename TypeIfTrue, typename TypeIfFalse >
        using Conditional = typename meta :: Conditional < condition, TypeIfTrue, TypeIfFalse > :: Type;

        template < typename LeftType, typename RightType >
        using IsSame = typename meta :: IsSame < LeftType, RightType >;


        template < typename LeftType, typename RightType >
        constexpr static bool isSame = meta :: IsSame < LeftType, RightType > :: value;

        template < typename LeftType, typename RightType >
        constexpr static bool lessThanPossible = meta :: LessThanPossible < LeftType, RightType > :: value;


        template < typename _T >
        struct Type {

        };
    }
}

#endif // __CDS_EX_TRAITS_HPP__
