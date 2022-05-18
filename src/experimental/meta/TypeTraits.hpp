//
// Created by uic70278 on 5/18/2022.
//

#ifndef __CDS_EX_META_TYPE_TRAITS_HPP__
#define __CDS_EX_META_TYPE_TRAITS_HPP__

#include <CDS/experimental/meta/Base>
#include <iostream>

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental { // NOLINT(modernize-concat-nested-namespaces)
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
            }

            template < typename LeftType, typename RightType >
            constexpr static auto isSame () noexcept -> bool {
                return impl :: IsSame < LeftType, RightType > :: value;
            }

            template < typename LeftType, typename RightType >
            constexpr static auto lessThanPossible () noexcept -> bool {
                return impl :: LessThanPossible < LeftType, RightType > :: value;
            }

            template < typename LeftType, typename RightType >
            constexpr static auto greaterThanPossible () noexcept -> bool {
                return impl :: GreaterThanPossible < LeftType, RightType > :: value;
            }

            template < typename LeftType, typename RightType >
            constexpr static auto lessThanOrEqualToPossible () noexcept -> bool {
                return impl :: LessThanOrEqualToPossible < LeftType, RightType > :: value;
            }

            template < typename LeftType, typename RightType >
            constexpr static auto greaterThanOrEqualToPossible () noexcept -> bool {
                return impl :: GreaterThanOrEqualToPossible < LeftType, RightType > :: value;
            }

            template < typename LeftType, typename RightType >
            constexpr static auto equalToPossible () noexcept -> bool {
                return impl :: EqualToPossible < LeftType, RightType > :: value;
            }

            template < typename LeftType, typename RightType >
            constexpr static auto notEqualToPossible () noexcept -> bool {
                return impl :: NotEqualToPossible < LeftType, RightType > :: value;
            }

            template < typename Type >
            constexpr static auto isPrintable () noexcept -> bool {
                return impl :: IsPrintable < Type > :: value;
            }

            template < typename Type >
            constexpr static auto isEnum () noexcept -> bool {
                return impl :: IsEnum < Type > :: value;
            }

            template < typename Type >
            constexpr static auto isUnion () noexcept -> bool {
                return impl :: IsUnion < Type > :: value;
            }

            template < typename Type >
            constexpr static auto isClass () noexcept -> bool {
                return impl :: IsClass < Type > :: value;
            }

            template < typename Type >
            constexpr static auto isFunction () noexcept -> bool {
                return impl :: IsFunction < Type > :: value;
            }

            template < typename BaseType, typename DerivedType >
            constexpr static auto isBaseFor () noexcept -> bool {
                return impl :: IsBaseOf < BaseType, DerivedType > :: value;
            }

            template < typename DerivedType, typename BaseType >
            constexpr static auto isDerivedFrom () noexcept -> bool {
                return impl :: IsBaseOf < BaseType, DerivedType > :: value;
            }

            template < typename T >
            struct Type {

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

                template < typename DerivedType >
                constexpr static auto isBaseFor () noexcept -> bool {
                    return meta :: isBaseFor < Type, DerivedType > ();
                }

                template < typename BaseType >
                constexpr static auto isDerivedFrom () noexcept -> bool {
                    return meta :: isDerivedFrom < Type, BaseType > ();
                }
            };
        }
    }
}

#endif // __CDS_EX_META_TYPE_TRAITS_HPP__
