//
// Created by loghin on 5/18/22.
//

#ifndef __CDS_EX_META_BASE_HPP__
#define __CDS_EX_META_BASE_HPP__

namespace cds {
    namespace experimental {
        namespace meta {
            template < typename ... > using Void = void;

            template < typename Type > auto valueOf () noexcept -> Type;
            template < typename Type > auto referenceOf () noexcept -> Type &;
            template < typename Type > auto addressOf () noexcept -> Type *;

            namespace impl {

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
            }

            template < bool enableCondition, typename ReplacedType = int >
            using EnableIf = typename impl :: EnableIf < enableCondition, ReplacedType > :: Type;

            template < bool condition, typename TypeIfTrue, typename TypeIfFalse >
            using Conditional = typename impl :: Conditional < condition, TypeIfTrue, TypeIfFalse > :: Type;

            using FalseType = impl :: FalseType;
            using TrueType  = impl :: TrueType;
        }
    }
}

#endif // __CDS_EX_META_BASE_HPP__
