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

                template < typename T > struct RemoveConst                              { using Type = T; };
                template < typename T > struct RemoveConst < T const >                  { using Type = T; };

                template < typename T > struct RemoveVolatile                           { using Type = T; };
                template < typename T > struct RemoveVolatile < T volatile >            { using Type = T; };

                template < typename T > struct RemoveReference                          { using Type = T; };
                template < typename T > struct RemoveReference < T & >                  { using Type = T; };
                template < typename T > struct RemoveReference < T && >                 { using Type = T; };

                template < typename T > struct RemoveConstVolatile                      { using Type = T; };
                template < typename T > struct RemoveConstVolatile < T const >          { using Type = T; };
                template < typename T > struct RemoveConstVolatile < T volatile >       { using Type = T; };
                template < typename T > struct RemoveConstVolatile < T const volatile > { using Type = T; };

                namespace removePtrImpl {
                    template < typename T, typename > struct RemovePointer              { using Type = T; };
                    template < typename T, typename U > struct RemovePointer < T, U * > { using Type = U; };
                }

                template < typename T > struct RemovePointer : removePtrImpl :: RemovePointer < T, typename RemoveConstVolatile < T > :: Type > {};

                template < typename T >
                struct RemoveExtent {
                    using Type = T;
                };

                template < typename T, Size size >
                struct RemoveExtent < T [size] > {
                    using Type = T;
                };

                template < typename T >
                struct RemoveExtent < T [] > {
                    using Type = T;
                };

                template < typename T >
                struct RemoveAllExtents {
                    using Type = T;
                };

                template < typename T, Size size >
                struct RemoveAllExtents < T [size] > {
                    using Type = typename RemoveAllExtents < T > :: Type;
                };

                template < typename T >
                struct RemoveAllExtents < T [] > {
                    using Type = typename RemoveAllExtents < T > :: Type;
                };

                template < typename T, typename = void >
                struct IsReferenceable : FalseType {};

                template < typename T >
                struct IsReferenceable < T, Void < T & > > : TrueType {};

                namespace isVoidImpl {
                    template < typename >   struct IsVoid           : FalseType {};
                    template <>             struct IsVoid < void >  : TrueType {};
                };

                template < typename T >
                struct IsVoid : isVoidImpl :: IsVoid < RemoveConstVolatile < T > > :: Type {};

                namespace addPtrImpl {
                    template < typename T, bool = IsReferenceable < T > :: value || IsVoid < T > :: value >
                    struct AddPointer {
                        using Type = T;
                    };

                    template < typename T >
                    struct AddPointer < T, true > {
                        using Type = typename RemoveReference < T > :: Type *;
                    };
                }

                template < typename T > struct AddPointer : addPtrImpl :: AddPointer < T, true > {};

                template < typename T > struct AddConst             { using Type = T const; };
                template < typename T > struct AddVolatile          { using Type = T volatile; };
                template < typename T > struct AddConstVolatile     { using Type = typename AddConst < typename AddVolatile < T > :: Type > :: Type; };

                namespace addReferenceImpl {
                    template < typename T, bool = IsReferenceable < T > :: value >
                    struct AddLValueReference               { using Type = T; };

                    template < typename T >
                    struct AddLValueReference < T, true >   { using Type = T &; };

                    template < typename T, bool = IsReferenceable < T > :: value >
                    struct AddRValueReference               { using Type = T; };

                    template < typename T >
                    struct AddRValueReference < T, true >   { using Type = T &&; };
                }

                template < typename T > struct AddLValueReference : addReferenceImpl :: AddLValueReference < T > {};
                template < typename T > struct AddRValueReference : addReferenceImpl :: AddRValueReference < T > {};
            }

            template < bool enableCondition, typename ReplacedType = int >
            using EnableIf = typename impl :: EnableIf < enableCondition, ReplacedType > :: Type;

            template < bool condition, typename TypeIfTrue, typename TypeIfFalse >
            using Conditional = typename impl :: Conditional < condition, TypeIfTrue, TypeIfFalse > :: Type;

            using FalseType = impl :: FalseType;
            using TrueType  = impl :: TrueType;

            template < typename T > using RemoveConst           = typename impl :: RemoveConst < T > :: Type;
            template < typename T > using RemoveVolatile        = typename impl :: RemoveVolatile < T > :: Type;
            template < typename T > using RemoveReference       = typename impl :: RemoveReference < T > :: Type;
            template < typename T > using RemoveConstVolatile   = typename impl :: RemoveConstVolatile < T > :: Type;
            template < typename T > using RemovePointer         = typename impl :: RemovePointer < T > :: Type;

            template < typename T > using RemoveExtent          = typename impl :: RemoveExtent < T > :: Type;
            template < typename T > using RemoveAllExtents      = typename impl :: RemoveAllExtents < T > :: Type;


            template < typename T > using AddConst              = typename impl :: AddConst < T > :: Type;
            template < typename T > using AddVolatile           = typename impl :: AddVolatile < T > :: Type;
            template < typename T > using AddLValueReference    = typename impl :: AddLValueReference < T > :: Type;
            template < typename T > using AddRValueReference    = typename impl :: AddRValueReference < T > :: Type;
            template < typename T > using AddConstVolatile      = typename impl :: AddConstVolatile < T > :: Type;
            template < typename T > using AddPointer            = typename impl :: AddPointer < T > :: Type;

            template < typename T >
            constexpr auto isVoid () noexcept -> bool {
                return impl :: IsVoid < T > :: value;
            }

            template < typename T >
            constexpr auto isReferenceable () noexcept -> bool {
                return impl :: IsReferenceable < T > :: value;
            }
        }
    }
}

#endif // __CDS_EX_META_BASE_HPP__
