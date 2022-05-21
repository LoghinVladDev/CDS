//
// Created by uic70278 on 5/18/2022.
//

#ifndef __CDS_EX_META_TYPE_TRAITS_HPP__
#define __CDS_EX_META_TYPE_TRAITS_HPP__

#include <CDS/experimental/meta/Base>
#include <iostream>

namespace cds { // NOLINT(modernize-concat-nested-namespaces)

    template < typename K, typename V > class Pair;
    template < typename T >             class SmartPointer;
    template < typename T >             class UniquePointer;
    template < typename T >             class SharedPointer;
    template < typename T >             class ForeignPointer;
    template < typename T >             class AtomicSharedPointer;

    namespace experimental { // NOLINT(modernize-concat-nested-namespaces)

        template < typename K, typename V > class Pair;
        template < typename T >             class SmartPointer;
        template < typename T >             class UniquePointer;
        template < typename T >             class SharedPointer;
        template < typename T >             class ForeignPointer;
        template < typename T >             class AtomicSharedPointer;

        namespace meta {

            namespace impl {

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

                template < typename LeftType, typename RightType >
                struct GreaterThanPossible < LeftType, RightType, Void < decltype ( valueOf < LeftType > () > valueOf < RightType > () ) > > : TrueType {};

                template < typename LeftType, typename RightType >
                struct LessThanOrEqualToPossible < LeftType, RightType, Void < decltype ( valueOf < LeftType > () <= valueOf < RightType > () ) > > : TrueType {};

                template < typename LeftType, typename RightType >
                struct GreaterThanOrEqualToPossible < LeftType, RightType, Void < decltype ( valueOf < LeftType > () >= valueOf < RightType > () ) > > : TrueType {};

                template < typename LeftType, typename RightType >
                struct EqualToPossible < LeftType, RightType, Void < decltype ( valueOf < LeftType > () == valueOf < RightType > () ) > > : TrueType {};

                template < typename LeftType, typename RightType >
                struct NotEqualToPossible < LeftType, RightType, Void < decltype ( valueOf < LeftType > () != valueOf < RightType > () ) > > : TrueType {};

                template < typename T, typename U = void >
                struct IsPrintable : FalseType {};

                template < typename T >
                struct IsPrintable < T, Void < decltype ( std :: cout << valueOf < T > () ) > > : TrueType {};

                template < typename T >
                struct IsEnum : BoolConstant < std :: is_enum < T > :: value > {};

                template < typename T >
                struct IsUnion : BoolConstant < std :: is_union < T > :: value > {};

                template < typename T >
                struct IsClass : BoolConstant < std :: is_class < T > :: value > {};

                template < typename T >
                struct IsFunction : BoolConstant < std :: is_function < T > :: value > {};

                template < typename T >
                struct IsFundamental : BoolConstant < std :: is_fundamental < T > :: value > {};

                template < typename T >
                struct IsIntegral : BoolConstant < std :: is_integral < T > :: value > {};

                template < typename T >
                struct IsFloatingPoint : BoolConstant < std :: is_floating_point < T > :: value > {};

                template < typename T >
                struct IsArithmetic : BoolConstant < std :: is_arithmetic < T > :: value > {};

                template < typename T >
                struct IsDefaultConstructible : BoolConstant < std :: is_default_constructible < T > :: value > {};

                template < typename T >
                struct IsCopyConstructible : BoolConstant < std :: is_copy_constructible < T > :: value > {};

                template < typename T >
                struct IsMoveConstructible : BoolConstant < std :: is_move_constructible < T > :: value > {};

                template < typename T >
                struct IsCopyAssignable : BoolConstant < std :: is_copy_assignable < T > :: value > {};

                template < typename T >
                struct IsMoveAssignable : BoolConstant < std :: is_move_assignable < T > :: value > {};

                namespace baseOfImpl {
                    template < typename BaseType >                          auto conversionTest ( BaseType const volatile * ) noexcept -> TrueType;
                    template < typename >                                   auto conversionTest ( void     const volatile * ) noexcept -> FalseType;

                    template < typename, typename >                         auto testBaseOf ( ... ) -> TrueType;
                    template < typename BaseType, typename DerivedType >    auto testBaseOf ( int ) ->
                            decltype ( conversionTest < BaseType > ( addressOf < DerivedType > () ) );
                }

                template < typename BaseType, typename DerivedType >
                struct IsBaseOf : BoolConstant <
                        IsClass < BaseType > :: value && IsClass < DerivedType > :: value &&
                        decltype ( baseOfImpl :: testBaseOf < BaseType, DerivedType > (0) ) :: value
                > {};

                template < typename T, typename U = void >
                struct IsCallable {
                    constexpr static bool value = Conditional <
                            IsClass < RemoveReference < T > > :: value,
                            IsCallable < RemoveReference < T >, int >,
                            FalseType
                    > :: Type :: value;
                };

                template <> struct IsCallable < Object > : FalseType {};
                template <> struct IsCallable < String > : FalseType {};

                template < typename T, typename U, typename ... A > struct IsCallable < T ( A ... ), U > : TrueType {};
                template < typename T, typename U, typename ... A > struct IsCallable < T (*) ( A ... ), U > : TrueType {};
                template < typename T, typename U, typename ... A > struct IsCallable < T (&) ( A ... ), U > : TrueType {};
                template < typename T, typename U, typename ... A > struct IsCallable < T ( A ..., ... ), U > : TrueType {};
                template < typename T, typename U, typename ... A > struct IsCallable < T (*) ( A ..., ... ), U > : TrueType {};
                template < typename T, typename U, typename ... A > struct IsCallable < T (&) ( A ..., ... ), U > : TrueType {};
                template < typename T, typename U, typename ... A > struct IsCallable < T ( A ... ) const, U > : TrueType {};
                template < typename T, typename U, typename ... A > struct IsCallable < T ( A ... ) volatile, U > : TrueType {};
                template < typename T, typename U, typename ... A > struct IsCallable < T ( A ... ) const volatile, U > : TrueType {};
                template < typename T, typename U, typename ... A > struct IsCallable < T ( A ..., ... ) const, U > : TrueType {};
                template < typename T, typename U, typename ... A > struct IsCallable < T ( A ..., ... ) volatile, U > : TrueType {};
                template < typename T, typename U, typename ... A > struct IsCallable < T ( A ..., ... ) const volatile, U > : TrueType {};
                template < typename T, typename U, typename ... A > struct IsCallable < T ( A ... ) &, U > : TrueType {};
                template < typename T, typename U, typename ... A > struct IsCallable < T ( A ... ) const &, U > : TrueType {};
                template < typename T, typename U, typename ... A > struct IsCallable < T ( A ... ) volatile &, U > : TrueType {};
                template < typename T, typename U, typename ... A > struct IsCallable < T ( A ... ) const volatile &, U > : TrueType {};
                template < typename T, typename U, typename ... A > struct IsCallable < T ( A ..., ... ) const &, U > : TrueType {};
                template < typename T, typename U, typename ... A > struct IsCallable < T ( A ..., ... ) volatile &, U > : TrueType {};
                template < typename T, typename U, typename ... A > struct IsCallable < T ( A ..., ... ) const volatile &, U > : TrueType {};
                template < typename T, typename U, typename ... A > struct IsCallable < T ( A ... ) &&, U > : TrueType {};
                template < typename T, typename U, typename ... A > struct IsCallable < T ( A ... ) const &&, U > : TrueType {};
                template < typename T, typename U, typename ... A > struct IsCallable < T ( A ... ) volatile &&, U > : TrueType {};
                template < typename T, typename U, typename ... A > struct IsCallable < T ( A ... ) const volatile &&, U > : TrueType {};
                template < typename T, typename U, typename ... A > struct IsCallable < T ( A ..., ... ) const &&, U > : TrueType {};
                template < typename T, typename U, typename ... A > struct IsCallable < T ( A ..., ... ) volatile &&, U > : TrueType {};
                template < typename T, typename U, typename ... A > struct IsCallable < T ( A ..., ... ) const volatile &&, U > : TrueType {};

                template < typename T >
                struct IsCallable < T, int > {
                private:
                    using y = char (&)[1];
                    using n = char (&)[2];

                    struct Fallback { auto operator ()() -> void {} };
                    struct Derived : T, Fallback {};

                    template < typename U, U >
                    struct Check;

                    __CDS_WarningSuppression_NoReturnStatement_SuppressEnable
                    template<typename>
                    static auto test ( ... ) -> y {} // NOLINT(clion-misra-cpp2008-8-4-1)

                    template<typename C>
                    static auto test ( Check < auto ( Fallback :: * ) () -> void, & C :: operator () > * ) -> n {}
                    __CDS_WarningSuppression_NoReturnStatement_SuppressDisable

                public:
                    constexpr static bool value = sizeof ( test < Derived > (0) ) == sizeof (y);
                };

                template < typename T > struct TypeParseTraits { constexpr static StringLiteral name = "Undefined"; };

                template < typename T, typename = void > struct IsStaticFunction : FalseType {};
                template < typename T, typename = void > struct IsObjectFunction : FalseType {};

                template < typename T >
                struct IsStaticFunction < T > : BoolConstant < IsFunction < T > :: value && ! IsObjectFunction < T > :: value > {};

                template < typename T >
                struct IsObjectFunction < T, Void < decltype ( & T :: operator () ) > > : TrueType {};

                template < typename >               struct IsArray : FalseType {};
                template < typename T, Size size >  struct IsArray < T [size] > : TrueType {};
                template < typename T >             struct IsArray < T [] > : TrueType {};

                namespace isPointerImpl {
                    template < typename >   struct IsPointer : FalseType {};
                    template < typename T > struct IsPointer < T * > : TrueType {};
                };

                template < typename T >     struct IsPointer : isPointerImpl :: IsPointer < typename RemoveConstVolatile < T > :: Type > {};

                template < typename >       struct IsLValueReference            : FalseType {};
                template < typename T >     struct IsLValueReference < T & >    : TrueType {};

                template < typename >       struct IsRValueReference            : FalseType {};
                template < typename T >     struct IsRValueReference < T && >   : TrueType {};

                namespace isMemberPointerImpl {
                    template < typename >               struct IsMemberObjectPointer                : FalseType {};
                    template < typename T, typename C > struct IsMemberObjectPointer < T C :: * >   : BoolConstant < ! IsFunction < T > :: value > {};
                }

                template < typename T, typename = void >
                struct IsMemberObjectPointer : FalseType {};

                template < typename T > struct IsMemberObjectPointer < T > : isMemberPointerImpl :: IsMemberObjectPointer < typename RemoveConstVolatile < T > :: Type > {};
                template < typename T, typename C > struct IsMemberObjectPointer < T C :: *, C > : IsMemberObjectPointer < typename RemoveConstVolatile < T C :: * > :: Type > {};

                namespace isMemberPointerImpl {
                    template < typename >               struct IsMemberFunctionPointer              : FalseType {};
                    template < typename T, typename C > struct IsMemberFunctionPointer < T C :: * > : BoolConstant < IsFunction < T > :: value > {};
                }

                template < typename T, typename = void > struct IsMemberFunctionPointer : FalseType {};

                template < typename T > struct IsMemberFunctionPointer < T > : isMemberPointerImpl :: IsMemberFunctionPointer < typename RemoveConstVolatile < T > :: Type > {};
                template < typename T, typename C > struct IsMemberFunctionPointer < T C :: *, C > : isMemberPointerImpl :: IsMemberFunctionPointer < typename RemoveConstVolatile < T C :: * > :: Type > {};


                template < typename T >             struct IsPair                                           : FalseType {};
                template < typename K, typename V > struct IsPair < cds :: Pair < K, V > >                  : TrueType {};
                template < typename K, typename V > struct IsPair < cds :: experimental :: Pair < K, V > >  : TrueType {};

                template < typename T >             struct IsSmartPointer                                                       : FalseType {};
                template < typename T >             struct IsSmartPointer < cds :: UniquePointer < T > >                        : TrueType {};
                template < typename T >             struct IsSmartPointer < cds :: SharedPointer < T > >                        : TrueType {};
                template < typename T >             struct IsSmartPointer < cds :: ForeignPointer < T > >                       : TrueType {};
                template < typename T >             struct IsSmartPointer < cds :: AtomicSharedPointer < T > >                  : TrueType {};
                template < typename T >             struct IsSmartPointer < cds :: experimental :: UniquePointer < T > >        : TrueType {};
                template < typename T >             struct IsSmartPointer < cds :: experimental :: SharedPointer < T > >        : TrueType {};
                template < typename T >             struct IsSmartPointer < cds :: experimental :: ForeignPointer < T > >       : TrueType {};
                template < typename T >             struct IsSmartPointer < cds :: experimental :: AtomicSharedPointer < T > >  : TrueType {};

                template < typename >       struct IsConst                      : FalseType {};
                template < typename T >     struct IsConst < T const >          : TrueType {};

                template < typename >       struct IsVolatile                   : FalseType {};
                template < typename T >     struct IsVolatile < T volatile >    : TrueType {};
            }

            template < typename LeftType, typename RightType >
            constexpr auto isSame () noexcept -> bool {
                return impl :: IsSame < LeftType, RightType > :: value;
            }

            template < typename LeftType, typename RightType >
            constexpr auto lessThanPossible () noexcept -> bool {
                return impl :: LessThanPossible < LeftType, RightType > :: value;
            }

            template < typename LeftType, typename RightType >
            constexpr auto greaterThanPossible () noexcept -> bool {
                return impl :: GreaterThanPossible < LeftType, RightType > :: value;
            }

            template < typename LeftType, typename RightType >
            constexpr auto lessThanOrEqualToPossible () noexcept -> bool {
                return impl :: LessThanOrEqualToPossible < LeftType, RightType > :: value;
            }

            template < typename LeftType, typename RightType >
            constexpr auto greaterThanOrEqualToPossible () noexcept -> bool {
                return impl :: GreaterThanOrEqualToPossible < LeftType, RightType > :: value;
            }

            template < typename LeftType, typename RightType >
            constexpr auto equalToPossible () noexcept -> bool {
                return impl :: EqualToPossible < LeftType, RightType > :: value;
            }

            template < typename LeftType, typename RightType >
            constexpr auto notEqualToPossible () noexcept -> bool {
                return impl :: NotEqualToPossible < LeftType, RightType > :: value;
            }

            template < typename Type >
            constexpr auto isPrintable () noexcept -> bool {
                return impl :: IsPrintable < Type > :: value;
            }

            template < typename Type >
            constexpr auto isEnum () noexcept -> bool {
                return impl :: IsEnum < Type > :: value;
            }

            template < typename Type >
            constexpr auto isUnion () noexcept -> bool {
                return impl :: IsUnion < Type > :: value;
            }

            template < typename Type >
            constexpr auto isClass () noexcept -> bool {
                return impl :: IsClass < Type > :: value;
            }

            template < typename Type >
            constexpr auto isFunction () noexcept -> bool {
                return impl :: IsFunction < Type > :: value;
            }

            template < typename Type >
            constexpr auto isFundamental () noexcept -> bool {
                return impl :: IsFundamental < Type > :: value;
            }

            template < typename Type >
            constexpr auto isIntegral () noexcept -> bool {
                return impl :: IsIntegral < Type > :: value;
            }

            template < typename Type >
            constexpr auto isFloatingPoint () noexcept -> bool {
                return impl :: IsFloatingPoint < Type > :: value;
            }

            template < typename Type >
            constexpr auto isArithmetic () noexcept -> bool {
                return impl :: IsArithmetic < Type > :: value;
            }

            template < typename BaseType, typename DerivedType >
            constexpr auto isBaseFor () noexcept -> bool {
                return impl :: IsBaseOf < BaseType, DerivedType > :: value;
            }

            template < typename DerivedType, typename BaseType >
            constexpr auto isDerivedFrom () noexcept -> bool {
                return impl :: IsBaseOf < BaseType, DerivedType > :: value;
            }

            template < typename Type >
            constexpr auto isDefaultConstructible () noexcept -> bool {
                return impl :: IsDefaultConstructible < Type > :: value;
            }

            template < typename Type >
            constexpr auto isCopyConstructible () noexcept -> bool {
                return impl :: IsCopyConstructible < Type > :: value;
            }

            template < typename Type >
            constexpr auto isMoveConstructible () noexcept -> bool {
                return impl :: IsMoveConstructible < Type > :: value;
            }

            template < typename Type >
            constexpr auto isCopyAssignable () noexcept -> bool {
                return impl :: IsCopyAssignable < Type > :: value;
            }

            template < typename Type >
            constexpr auto isMoveAssignable () noexcept -> bool {
                return impl :: IsMoveAssignable < Type > :: value;
            }

            template < typename T >
            constexpr auto isCallable () noexcept -> bool {
                return impl :: IsCallable < T > :: value;
            }

            template < typename T >
            constexpr auto isObjectDerived () noexcept -> bool {
                return isDerivedFrom < T, Object > ();
            }

            template < typename T >
            constexpr auto isStaticFunction () noexcept -> bool {
                return impl :: IsStaticFunction < T > :: value;
            }

            template < typename T >
            constexpr auto isObjectFunction () noexcept -> bool {
                return impl :: IsObjectFunction < T > :: value;
            }

            template < typename T >
            constexpr auto isArray () noexcept -> bool {
                return impl :: IsArray < T > :: value;
            }

            template < typename T, Size size >
            constexpr auto isArray () noexcept -> bool {
                return impl :: IsArray < T [size] > :: value;
            }

            template < typename T >
            constexpr auto isBasicPointer () noexcept -> bool {
                return impl :: IsPointer < T > :: value;
            }

            template < typename T >
            constexpr auto isSmartPointer () noexcept -> bool {
                return impl :: IsSmartPointer < T > :: value;
            }

            template < typename T >
            constexpr auto isPointer () noexcept -> bool {
                return isBasicPointer < T > () || isSmartPointer < T > ();
            }

            template < typename T >
            constexpr auto isLValueReference () noexcept -> bool {
                return impl :: IsLValueReference < T > :: value;
            }

            template < typename T >
            constexpr auto isRValueReference () noexcept -> bool {
                return impl :: IsRValueReference < T > :: value;
            }

            template < typename T >
            constexpr auto isReference () noexcept -> bool {
                return impl :: IsLValueReference < T > :: value;
            }

            template < typename T >
            constexpr auto isMoveReference () noexcept -> bool {
                return impl :: IsRValueReference < T > :: value;
            }

            template < typename T >
            constexpr auto isMemberObjectPointer () noexcept -> bool {
                return impl :: IsMemberObjectPointer < T > :: value;
            }

            template < typename T >
            constexpr auto isMemberFunctionPointer () noexcept -> bool {
                return impl :: IsMemberFunctionPointer < T > :: value;
            }

            template < typename T, typename C >
            constexpr auto isMemberObjectPointer () noexcept -> bool {
                return impl :: IsMemberObjectPointer < T, C > :: value;
            }

            template < typename T, typename C >
            constexpr auto isMemberFunctionPointer () noexcept -> bool {
                return impl :: IsMemberFunctionPointer < T, C > :: value;
            }

            template < typename T >
            constexpr auto isConst () noexcept -> bool {
                return impl :: IsConst < T > :: value;
            }

            template < typename T >
            constexpr auto isVolatile () noexcept -> bool {
                return impl :: IsVolatile < T > :: value;
            }

            template < typename T >
            struct Type {

                using BaseType = T;

                using RemoveConst           = meta :: RemoveConst < T >;
                using RemoveVolatile        = meta :: RemoveVolatile < T >;
                using RemoveReference       = meta :: RemoveReference < T >;
                using RemoveConstVolatile   = meta :: RemoveConstVolatile < T >;
                using RemovePointer         = meta :: RemovePointer < T >;

                template < typename U >
                constexpr static auto isSame () noexcept -> bool {
                    return meta :: isSame < T, U > ();
                }

                constexpr static auto hasEqualTo () noexcept -> bool {
                    return meta :: equalToPossible < T, T > ();
                }

                constexpr static auto hasNotEqualTo () noexcept -> bool {
                    return meta :: notEqualToPossible < T, T > ();
                }

                constexpr static auto hasLessThan () noexcept -> bool {
                    return meta :: lessThanPossible < T, T > ();
                }

                constexpr static auto hasGreaterThan () noexcept -> bool {
                    return meta :: greaterThanPossible < T, T > ();
                }

                constexpr static auto hasLessThanOrEqual () noexcept -> bool {
                    return meta :: lessThanOrEqualToPossible < T, T > ();
                }

                constexpr static auto hasGreaterThanOrEqual () noexcept -> bool {
                    return meta :: greaterThanOrEqualToPossible < T, T > ();
                }

                constexpr static auto isPrintable () noexcept -> bool {
                    return meta :: isPrintable < T > ();
                }

                constexpr static auto isEnum () noexcept -> bool {
                    return meta :: isEnum < T > ();
                }

                constexpr static auto isClass () noexcept -> bool {
                    return meta :: isEnum < T > ();
                }

                constexpr static auto isUnion () noexcept -> bool {
                    return meta :: isUnion < T > ();
                }

                constexpr static auto isFunction () noexcept -> bool {
                    return meta :: isFunction < T > ();
                }

                constexpr static auto isStaticFunction () noexcept -> bool {
                    return meta :: isStaticFunction < T > ();
                }

                constexpr static auto isObjectFunction () noexcept -> bool {
                    return meta :: isObjectFunction < T > ();
                }

                constexpr static auto isFundamental () noexcept -> bool {
                    return meta :: isFundamental < T > ();
                }

                constexpr static auto isIntegral () noexcept -> bool {
                    return meta :: isIntegral < T > ();
                }

                constexpr static auto isArithmetic () noexcept -> bool {
                    return meta :: isArithmetic < T > ();
                }

                constexpr static auto isPrimitive () noexcept -> bool {
                    return meta :: isFundamental < T > ();
                }

                template < typename DerivedType >
                constexpr static auto isBaseFor () noexcept -> bool {
                    return meta :: isBaseFor < Type, DerivedType > ();
                }

                template < typename BaseType >
                constexpr static auto isDerivedFrom () noexcept -> bool {
                    return meta :: isDerivedFrom < Type, BaseType > ();
                }

                constexpr static auto isDefaultConstructible () noexcept -> bool {
                    return meta :: isDefaultConstructible < T > ();
                }

                constexpr static auto isCopyConstructible () noexcept -> bool {
                    return meta :: isCopyConstructible < T > ();
                }

                constexpr static auto isMoveConstructible () noexcept -> bool {
                    return meta :: isMoveConstructible < T > ();
                }

                constexpr static auto isCopyAssignable () noexcept -> bool {
                    return meta :: isCopyAssignable < T > ();
                }

                constexpr static auto isMoveAssignable () noexcept -> bool {
                    return meta :: isMoveAssignable < T > ();
                }

                constexpr static auto isCallable () noexcept -> bool {
                    return meta :: isCallable < T > ();
                }

                constexpr static auto isArray () noexcept -> bool {
                    return meta :: isArray < T > ();
                }

                template < Size size >
                constexpr static auto isArray () noexcept -> bool {
                    return meta :: isArray < T[size] > ();
                }

                constexpr static auto isPointer () noexcept -> bool {
                    return meta :: isPointer < T > ();
                }

                constexpr static auto isBasicPointer () noexcept -> bool {
                    return meta :: isBasicPointer < T > ();
                }

                constexpr static auto isSmartPointer () noexcept -> bool {
                    return meta :: isSmartPointer < T > ();
                }

                constexpr static auto isLValueReference () noexcept -> bool {
                    return meta :: isLValueReference < T > ();
                }

                constexpr static auto isRValueReference () noexcept -> bool {
                    return meta :: isRValueReference < T > ();
                }

                constexpr static auto isReference () noexcept -> bool {
                    return meta :: isReference < T > ();
                }

                constexpr static auto isMoveReference () noexcept -> bool {
                    return meta :: isMoveReference < T > ();
                }

                constexpr static auto isMemberObjectPointer () noexcept -> bool {
                    return meta :: isMemberObjectPointer < T > ();
                }

                constexpr static auto isMemberFunctionPointer () noexcept -> bool {
                    return meta :: isMemberFunctionPointer < T > ();
                }

                template < typename C >
                constexpr static auto isMemberObjectPointer () noexcept -> bool {
                    return meta :: isMemberObjectPointer < T, C > ();
                }

                template < typename C >
                constexpr static auto isMemberFunctionPointer () noexcept -> bool {
                    return meta :: isMemberFunctionPointer < T, C > ();
                }

                constexpr static auto isConst () noexcept -> bool {
                    return meta :: isConst < T > ();
                }

                constexpr static auto isVolatile () noexcept -> bool {
                    return meta :: isVolatile < T > ();
                }
            };
        }
    }
}

#define __CDS_Meta_RegisterParseType(_type) /* NOLINT(bugprone-reserved-identifier) */  \
namespace cds {                                                                         \
    namespace experimental {                                                            \
        namespace meta {                                                                \
            namespace impl {                                                            \
                template <>                                                             \
                struct TypeParseTraits < _type > {                                      \
                    constexpr static StringLiteral name = # _type;                      \
                };                                                                      \
            }                                                                           \
        }                                                                               \
    }                                                                                   \
}

#define __CDS_Meta_RegisterParseTemplateType(_type) /* NOLINT(bugprone-reserved-identifier) */  \
namespace cds {                                                                         \
    namespace experimental {                                                            \
        namespace meta {                                                                \
            namespace impl {                                                            \
                template < typename ... Types >                                         \
                struct TypeParseTraits < _type < Types ... > > {                        \
                    constexpr static StringLiteral name = # _type;                      \
                };                                                                      \
            }                                                                           \
        }                                                                               \
    }                                                                                   \
}

__CDS_Meta_RegisterParseType ( sint8 )
__CDS_Meta_RegisterParseType ( sint16 )
__CDS_Meta_RegisterParseType ( sint32 )
__CDS_Meta_RegisterParseType ( sint64 )

__CDS_Meta_RegisterParseType ( uint8 )
__CDS_Meta_RegisterParseType ( uint16 )
__CDS_Meta_RegisterParseType ( uint32 )
__CDS_Meta_RegisterParseType ( uint64 )

__CDS_Meta_RegisterParseType ( void )
__CDS_Meta_RegisterParseType ( bool )
__CDS_Meta_RegisterParseType ( float )
__CDS_Meta_RegisterParseType ( double )

#endif // __CDS_EX_META_TYPE_TRAITS_HPP__
