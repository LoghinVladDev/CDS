//
// Created by uic70278 on 5/18/2022.
//

#ifndef __CDS_EX_META_TYPE_TRAITS_HPP__
#define __CDS_EX_META_TYPE_TRAITS_HPP__

#include <CDS/experimental/meta/Base>
#include <iostream>

namespace cds { // NOLINT(modernize-concat-nested-namespaces)

    /**
     * @class type representing a Pair of two types.
     * @tparam K is the type of the first pair member
     * @tparam V is the type of the second pair member
     */
    template < typename K, typename V > class Pair;

    /**
     * @class abstract type representing a smart pointer to a given type
     * @tparam T is the addressed type
     */
    template < typename T >             class SmartPointer;

    /**
     * @class type representing an Unique Pointer ( owned by one object only ) to a given type
     * @tparam T is the addressed type
     */
    template < typename T >             class UniquePointer;

    /**
     * @class abstract type representing a Shared Pointer ( deleted when not owned ) to a given type
     * @tparam T is the addressed type
     */
    template < typename T >             class SharedPointer;

    /**
     * @class abstract type representing a Foreign Pointer ( not owned, only addressed ) to a given type
     * @tparam T is the addressed type
     */
    template < typename T >             class ForeignPointer;

    /**
     * @class abstract type representing a Shared Pointer ( deleted when not owned ) with atomic guarding to a given type
     * @tparam T is the addressed type
     */
    template < typename T >             class AtomicSharedPointer;

    namespace experimental { // NOLINT(modernize-concat-nested-namespaces)

        /**
         * @class type representing a Pair of two types.
         * @tparam K is the type of the first pair member
         * @tparam V is the type of the second pair member
         */
        template < typename K, typename V > class Pair;

        /**
         * @class abstract type representing a smart pointer to a given type
         * @tparam T is the addressed type
         */
        template < typename T >             class SmartPointer;

        /**
         * @class type representing an Unique Pointer ( owned by one object only ) to a given type
         * @tparam T is the addressed type
         */
        template < typename T >             class UniquePointer;

        /**
         * @class abstract type representing a Shared Pointer ( deleted when not owned ) to a given type
         * @tparam T is the addressed type
         */
        template < typename T >             class SharedPointer;

        /**
         * @class abstract type representing a Foreign Pointer ( not owned, only addressed ) to a given type
         * @tparam T is the addressed type
         */
        template < typename T >             class ForeignPointer;

        /**
         * @class abstract type representing a Shared Pointer ( deleted when not owned ) with atomic guarding to a given type
         * @tparam T is the addressed type
         */
        template < typename T >             class AtomicSharedPointer;

        namespace meta {

            namespace impl {

                /**
                 * @brief Meta-type implementation used to check if two given types are the same
                 * @tparam LeftType is the first type
                 * @tparam RightType is the second type
                 */
                template < typename LeftType, typename RightType >
                struct IsSame : FalseType {};

                template < typename Type >
                struct IsSame < Type, Type > : TrueType {};


                /**
                 * @brief Meta-type implementation used to check if two given types can be compared by less than operator (\<)
                 * @tparam LeftType is the first type
                 * @tparam RightType is the second type
                 */
                template < typename LeftType, typename RightType, typename = Void <> > struct LessThanPossible : FalseType {};

                /**
                 * @brief Meta-type implementation used to check if two given types can be compared by greater than operator (\>)
                 * @tparam LeftType is the first type
                 * @tparam RightType is the second type
                 */
                template < typename LeftType, typename RightType, typename = Void <> > struct GreaterThanPossible : FalseType {};

                /**
                 * @brief Meta-type implementation used to check if two given types can be compared by less than or equal to operator (\<=)
                 * @tparam LeftType is the first type
                 * @tparam RightType is the second type
                 */
                template < typename LeftType, typename RightType, typename = Void <> > struct LessThanOrEqualToPossible : FalseType {};

                /**
                 * @brief Meta-type implementation used to check if two given types can be compared by greater than or equal to operator (\>=)
                 * @tparam LeftType is the first type
                 * @tparam RightType is the second type
                 */
                template < typename LeftType, typename RightType, typename = Void <> > struct GreaterThanOrEqualToPossible : FalseType {};

                /**
                 * @brief Meta-type implementation used to check if two given types can be compared by equal to operator (==)
                 * @tparam LeftType is the first type
                 * @tparam RightType is the second type
                 */
                template < typename LeftType, typename RightType, typename = Void <> > struct EqualToPossible : FalseType {};

                /**
                 * @brief Meta-type implementation used to check if two given types can be compared by not equal to operator (!=)
                 * @tparam LeftType is the first type
                 * @tparam RightType is the second type
                 */
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

                /**
                 * @brief Meta-type implementation used to check if a given type is printable ( std :: ostream << type )
                 * @tparam T is the type for which printability is checked
                 */
                template < typename T, typename = void >
                struct IsPrintable : FalseType {};

                template < typename T >
                struct IsPrintable < T, Void < decltype ( std :: cout << valueOf < T > () ) > > : TrueType {};

                /**
                 * @brief Meta-type implementation used to check if a given type is an enum type
                 * @tparam T is the type checked
                 */
                template < typename T >
                struct IsEnum : BoolConstant < std :: is_enum < T > :: value > {};

                /**
                 * @brief Meta-type implementation used to check if a given type is an union type
                 * @tparam T is the type checked
                 */
                template < typename T >
                struct IsUnion : BoolConstant < std :: is_union < T > :: value > {};

                /**
                 * @brief Meta-type implementation used to check if a given type is a class or struct type
                 * @tparam T is the type checked
                 */
                template < typename T >
                struct IsClass : BoolConstant < std :: is_class < T > :: value > {};

                /**
                 * @brief Meta-type implementation used to check if a given type is a function type
                 * @tparam T is the type checked
                 */
                template < typename T >
                struct IsFunction : BoolConstant < std :: is_function < T > :: value > {};

                /**
                 * @brief Meta-type implementation used to check if a given type is a fundamental type ( bool, int types, float types )
                 * @tparam T is the type checked
                 */
                template < typename T >
                struct IsFundamental : BoolConstant < std :: is_fundamental < T > :: value > {};

                /**
                 * @brief Meta-type implementation used to check if a given type is an integral type ( bool, int types )
                 * @tparam T is the type checked
                 */
                template < typename T >
                struct IsIntegral : BoolConstant < std :: is_integral < T > :: value > {};

                /**
                 * @brief Meta-type implementation used to check if a given type is a floating point type ( float types )
                 * @tparam T is the type checked
                 */
                template < typename T >
                struct IsFloatingPoint : BoolConstant < std :: is_floating_point < T > :: value > {};

                /**
                 * @brief Meta-type implementation used to check if a given type is an arithmetic type ( int, float types )
                 * @tparam T is the type checked
                 */
                template < typename T >
                struct IsArithmetic : BoolConstant < std :: is_arithmetic < T > :: value > {};

                /**
                 * @brief Meta-type implementation used to check if a given type can be constructed without arguments ( has default constructor )
                 * @tparam T is the type checked
                 */
                template < typename T >
                struct IsDefaultConstructible : BoolConstant < std :: is_default_constructible < T > :: value > {};

                /**
                 * @brief Meta-type implementation used to check if a given type can be constructed by copy ( has copy constructor )
                 * @tparam T is the type checked
                 */
                template < typename T >
                struct IsCopyConstructible : BoolConstant < std :: is_copy_constructible < T > :: value > {};

                /**
                 * @brief Meta-type implementation used to check if a given type can be constructed by move ( has move constructor )
                 * @tparam T is the type checked
                 */
                template < typename T >
                struct IsMoveConstructible : BoolConstant < std :: is_move_constructible < T > :: value > {};

                /**
                 * @brief Meta-type implementation used to check if a given type can be assigned a value by copy ( has copy assignment operator )
                 * @tparam T is the type checked
                 */
                template < typename T >
                struct IsCopyAssignable : BoolConstant < std :: is_copy_assignable < T > :: value > {};

                /**
                 * @brief Meta-type implementation used to check if a given type can be assigned a value by move ( has move assignment operator )
                 * @tparam T is the type checked
                 */
                template < typename T >
                struct IsMoveAssignable : BoolConstant < std :: is_move_assignable < T > :: value > {};

                namespace baseOfImpl {
                    template < typename BaseType >                          auto conversionTest ( BaseType const volatile * ) noexcept -> TrueType;
                    template < typename >                                   auto conversionTest ( void     const volatile * ) noexcept -> FalseType;

                    template < typename, typename >                         auto testBaseOf ( ... ) -> TrueType;
                    template < typename BaseType, typename DerivedType >    auto testBaseOf ( int ) ->
                            decltype ( conversionTest < BaseType > ( addressOf < DerivedType > () ) );
                }

                /**
                 * @brief Meta-type implementation used to check if a given type is a base class of another given type
                 * @tparam BaseType is the type given as a base class
                 * @tparam DerivedType is the type given as a derived class
                 */
                template < typename BaseType, typename DerivedType >
                struct IsBaseOf : BoolConstant <
                        IsClass < BaseType > :: value && IsClass < DerivedType > :: value &&
                        decltype ( baseOfImpl :: testBaseOf < BaseType, DerivedType > (0) ) :: value
                > {};

                /**
                 * @brief Meta-type implementation used to check if a given type is a callable type ( function / object with operator () )
                 * @tparam T is the type checked
                 */
                template < typename T, typename = void >
                struct IsCallable {
                    /// if the given type is a class, or a class reference, use the operator() deduction implementation value. Otherwise, false,
                    /// unless it is overridden by a partial template specialization
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

                /**
                 * @brief Meta-type implementation used to obtain the type name in a StringLiteral format ( char const * )
                 * @tparam T is the type for which the name is obtained
                 */
                template < typename T > struct TypeParseTraits { constexpr static StringLiteral name = "Undefined"; };

                /**
                 * @brief Meta-type implementation used to check if a given type is a static-function type ( non-object callable )
                 * @tparam T is the type checked
                 */
                template < typename T, typename = void > struct IsStaticFunction : FalseType {};

                /**
                 * @brief Meta-type implementation used to check if a given type is a callable object ( non-static function )
                 * @tparam T is the type checked
                 */
                template < typename T, typename = void > struct IsObjectFunction : FalseType {};

                template < typename T >
                struct IsStaticFunction < T > : BoolConstant < IsFunction < T > :: value && ! IsObjectFunction < T > :: value > {};

                template < typename T >
                struct IsObjectFunction < T, Void < decltype ( & T :: operator () ) > > : TrueType {};

                /**
                 * @brief Meta-type implementation used to check if a given type is an array type
                 * @tparam T is the type checked
                 */
                template < typename >               struct IsArray : FalseType {};
                template < typename T, Size size >  struct IsArray < T [size] > : TrueType {};
                template < typename T >             struct IsArray < T [] > : TrueType {};

                namespace isPointerImpl {
                    /**
                     * @brief Meta-type helper implementation used to check if a given type is a pointer type
                     * @tparam T is the type checked
                     */
                    template < typename >   struct IsPointer : FalseType {};
                    template < typename T > struct IsPointer < T * > : TrueType {};
                }

                /**
                 * @brief Meta-type implementation used to check if a given type is a pointer type
                 * @tparam T is the type checked
                 */
                template < typename T >     struct IsPointer : isPointerImpl :: IsPointer < typename RemoveConstVolatile < T > :: Type > {};

                /**
                 * @brief Meta-type implementation used to check if a given type is a lvalue reference (&) type
                 * @tparam T is the type checked
                 */
                template < typename >       struct IsLValueReference            : FalseType {};
                template < typename T >     struct IsLValueReference < T & >    : TrueType {};

                /**
                 * @brief Meta-type implementation used to check if a given type is a rvalue reference (&&) type
                 * @tparam T is the type checked
                 */
                template < typename >       struct IsRValueReference            : FalseType {};
                template < typename T >     struct IsRValueReference < T && >   : TrueType {};

                namespace isMemberPointerImpl {
                    /**
                     * @brief Meta-type helper implementation used to check if a given type is a member of an object
                     * @tparam T is the type checked
                     */
                    template < typename >               struct IsMemberObjectPointer                : FalseType {};
                    template < typename T, typename C > struct IsMemberObjectPointer < T C :: * >   : BoolConstant < ! IsFunction < T > :: value > {};
                }

                /**
                 * @brief Meta-type implementation used to check if a given type is a member of an object
                 * @tparam T is the type checked
                 */
                template < typename T, typename = void >
                struct IsMemberObjectPointer : FalseType {};

                template < typename T > struct IsMemberObjectPointer < T > : isMemberPointerImpl :: IsMemberObjectPointer < typename RemoveConstVolatile < T > :: Type > {};
                template < typename T, typename C > struct IsMemberObjectPointer < T C :: *, C > : IsMemberObjectPointer < typename RemoveConstVolatile < T C :: * > :: Type > {};

                namespace isMemberPointerImpl {
                    /**
                     * @brief Meta-type helper implementation used to check if a given type is a member function of an object
                     * @tparam T is the type checked
                     */
                    template < typename >               struct IsMemberFunctionPointer              : FalseType {};
                    template < typename T, typename C > struct IsMemberFunctionPointer < T C :: * > : BoolConstant < IsFunction < T > :: value > {};
                }

                /**
                 * @brief Meta-type implementation used to check if a given type is a member function of an object
                 * @tparam T is the type checked
                 */
                template < typename T, typename = void > struct IsMemberFunctionPointer : FalseType {};

                template < typename T > struct IsMemberFunctionPointer < T > : isMemberPointerImpl :: IsMemberFunctionPointer < typename RemoveConstVolatile < T > :: Type > {};
                template < typename T, typename C > struct IsMemberFunctionPointer < T C :: *, C > : isMemberPointerImpl :: IsMemberFunctionPointer < typename RemoveConstVolatile < T C :: * > :: Type > {};


                /**
                 * @brief Meta-type implementation used to check if a given type is a Pair type
                 * @tparam T is the type checked
                 */
                template < typename T >             struct IsPair                                           : FalseType {};
                template < typename K, typename V > struct IsPair < cds :: Pair < K, V > >                  : TrueType {};
                template < typename K, typename V > struct IsPair < cds :: experimental :: Pair < K, V > >  : TrueType {};


                /**
                 * @brief Meta-type implementation used to check if a given type is a Smart Pointer derived-type
                 * @tparam T is the type checked
                 */
                template < typename T >             struct IsSmartPointer                                                       : FalseType {};
                template < typename T >             struct IsSmartPointer < cds :: UniquePointer < T > >                        : TrueType {};
                template < typename T >             struct IsSmartPointer < cds :: SharedPointer < T > >                        : TrueType {};
                template < typename T >             struct IsSmartPointer < cds :: ForeignPointer < T > >                       : TrueType {};
                template < typename T >             struct IsSmartPointer < cds :: AtomicSharedPointer < T > >                  : TrueType {};
                template < typename T >             struct IsSmartPointer < cds :: experimental :: UniquePointer < T > >        : TrueType {};
                template < typename T >             struct IsSmartPointer < cds :: experimental :: SharedPointer < T > >        : TrueType {};
                template < typename T >             struct IsSmartPointer < cds :: experimental :: ForeignPointer < T > >       : TrueType {};
                template < typename T >             struct IsSmartPointer < cds :: experimental :: AtomicSharedPointer < T > >  : TrueType {};

                /**
                 * @brief Meta-type implementation used to check if a given type is a const type
                 * @tparam T is the type checked
                 */
                template < typename >       struct IsConst                      : FalseType {};
                template < typename T >     struct IsConst < T const >          : TrueType {};

                /**
                 * @brief Meta-type implementation used to check if a given type is a volatile type
                 * @tparam T is the type checked
                 */
                template < typename >       struct IsVolatile                   : FalseType {};
                template < typename T >     struct IsVolatile < T volatile >    : TrueType {};

                namespace decayImpl {
                    /**
                     * @brief Meta-type helper implementation used to obtain safe pass-by-value equivalent type of a given type
                     * @tparam T is the type for which to obtain a pass by value
                     *
                     * This will act as a switch based on the isArray or isFunction conditions
                     * <ul>
                     *  <li> If none are satisfied, go with removal of modifiers </li>
                     *  <li> If is array, go with extent removal and addition of pointer </li>
                     *  <li> If is function, go with addition of pointer </li>
                     * </ul>
                     */
                    template < typename T, bool isArray = IsArray < T > :: value, bool isFunction = IsFunction < T > :: value >
                    struct Decay {};

                    template < typename T >
                    struct Decay < T, false, false > {
                        using Type = typename RemoveConstVolatile < T > :: Type;
                    };

                    template < typename T >
                    struct Decay < T, true, false > {
                        using Type = typename RemoveExtent < T > :: Type *;
                    };

                    template < typename T >
                    struct Decay < T, false, true > {
                        using Type = typename AddPointer < T > :: Type *;
                    };
                }

                /**
                 * @brief Meta-type implementation used to obtain safe pass-by-value equivalent type of a given type
                 * @tparam T is the type for which to obtain a pass by value
                 * @example decay will convert any rvalue type to a lvalue type <br/>
                 * <pre>- Decay\<int\>            = int;</pre>
                 * <pre>- Decay\<int &\>          = int;</pre>
                 * <pre>- Decay\<int &&\>         = int; </pre>
                 * <pre>- Decay\<int const &\>    = int; </pre>
                 * @example decay will convert any array with extent type to a pointer type <br/>
                 * <pre>- Decay\<int[2]\>         = int *; </pre>
                 * @example decay will convert any function signature type to a function pointer for that signature type <br/>
                 * <pre>- Decay\<int(int)\>       = int (*)(int); </pre>
                 */
                template < typename T >
                struct Decay {

                private:
                    using FirstParseDecayedType = typename RemoveReference < T > :: Type;

                public:
                    using Type = typename decayImpl :: Decay < FirstParseDecayedType > :: Type;
                };


                /**
                 * @brief Meta-type implementation used to obtain the common, lvalue type that the given types can be converted to, if any
                 * @tparam TypePack is the pack of types to find a common type for
                 *
                 * Implementation:
                 * <ul>
                 *      <li> If no types given, Common type does not exist </li>
                 *      <li> If only one type is given, Common type is the common type of itself, twice. ( will be reduced to itself ). </li>
                 *      <li> If two types are given, the Common type is the common type of the decayed types </li>
                 *      <li>
                 *          If two types are given and their decayed versions are the same as themselves, attempt to find their common
                 *          <ul>
                 *              <li> Apply them in a ternary operator, acquire the result from the expression, if any exists, and decay it. </li>
                 *          </ul>
                 *      </li>
                 *      <li> If more than two types are given, the type is the common type of the first two to their common type and the remaining types. </li>
                 * </ul>
                 */
                template < typename ... TypePack >  struct Common;
                template <>                         struct Common <> {};
                template < typename T >             struct Common < T > : Common < T, T > {};

                namespace commonImpl {
                    /**
                     * @brief Meta-type helper implementation used to obtain the common type between two types via ternary operator, if possible
                     */
                    struct CommonTest {
                        template < typename T > struct SuccessType { using Type = T; };
                                                struct FailureType { };

                        template < typename T, typename U > using ConditionalType = decltype ( true ? valueOf < T > () : valueOf < U > () );
                        template < typename T, typename U > static SuccessType < typename Decay < ConditionalType < T, U > > :: Type > test ( int );
                        template < typename T, typename U > static SuccessType < typename RemoveConstVolatile < ConditionalType < T const &, U const & > > :: Type > test2 ( int ); /// cpp-17?

                        template < typename, typename >     static FailureType test2 ( ... );
                        template < typename T, typename U > static decltype ( CommonTest :: test2 < T, U > ( 0 ) ) test ( ... );
                    };

                    /**
                     * @brief Meta-type helper implementation used to decay the types of two given types before using the ternary helper
                     * @tparam T1 is the type given as first type
                     * @tparam T2 is the type given as second type
                     * @tparam DecayedT1 is the decayed type of the first type
                     * @tparam DecayedT2 is the decayed type of the second type
                     */
                    template < typename T1, typename T2, typename DecayedT1 = typename Decay < T1 > :: Type, typename DecayedT2 = typename Decay < T2 > :: Type >
                    struct CommonDecayed {
                        using Type = Common < DecayedT1, DecayedT2 >;
                    };

                    template < typename T1, typename T2 >
                    struct CommonDecayed < T1, T2, T1, T2 > : private CommonTest {
                        using Type = decltype ( CommonTest :: test < T1, T2 > (0) );
                    };

                    /**
                     * @brief Meta-type helper implementation used to preserve the remaining type pack in the case of more than two types given to common
                     */
                    template < typename ... >
                    struct CommonPack {};

                    /**
                     * @brief Meta-type helper implementation used to apply the fold expression to reducing the two-or-more types of common by the following rule:
                     *
                     * Common \< T1, T2, T3, ... \> = Common \< Common \< T1, T2 \>, T3, ... \>
                     */
                    template < typename, typename, typename = void >
                    struct CommonFold {};

                    template < typename CurrentType, typename ... RemainingTypes >
                    struct CommonFold < CurrentType, CommonPack < RemainingTypes ... >, Void < typename CurrentType :: Type > > :
                            public meta :: impl :: Common < typename CurrentType :: Type, RemainingTypes ... > {};

                    template < typename CurrentType, typename RemainingType >
                    struct CommonFold < CurrentType, RemainingType, void > {};
                }

                template < typename T1, typename T2 >
                struct Common < T1, T2 > : public commonImpl :: CommonDecayed < T1, T2 > :: Type {};

                template < typename T1, typename T2, typename ... RemainingTypes >
                struct Common < T1, T2, RemainingTypes ... > :
                        public commonImpl :: CommonFold < Common < T1, T2 >, commonImpl :: CommonPack < RemainingTypes ... > > {};

                namespace isConvertibleImpl {
                    /**
                     * @brief Meta-type helper used to check if a given type is convertible to another given type
                     * @tparam From is the type being converted
                     * @tparam To is the type to which the conversion is done
                     */
                    template < typename From, typename To, bool = IsVoid < From > :: value || IsFunction < To > :: value || IsArray < To > :: value >
                    struct IsConvertible {
                        using Type = typename IsVoid < To > :: Type;
                    };

                    template < typename From, typename To >
                    struct IsConvertible < From, To, false > {
                    private:
                        template < typename To1 >
                        static void metaTest ( To1 ) noexcept;

                        template < typename From1, typename To1, typename = decltype ( metaTest < To1 > ( valueOf < From1 > () ) ) >
                        static TrueType test (int);

                        template < typename, typename >
                        static FalseType test (...);

                    public:
                        using Type = decltype ( test < From, To > (0) );
                    };
                }

                /**
                 * @brief Meta-type implementation used to check if a given type is convertible to another given type
                 * @tparam From is the type being converted
                 * @tparam To is the type to which the conversion is done
                 */
                template < typename From, typename To >
                struct IsConvertible : isConvertibleImpl :: IsConvertible < From, To > :: Type {};
            }

            /**
             * @brief Meta-type used to obtain safe pass-by-value equivalent type of a given type
             * @tparam T is the type for which to obtain a pass by value
             * @example decay will convert any rvalue type to a lvalue type <br/>
             * <pre>- Decay\<int\>            = int;</pre>
             * <pre>- Decay\<int &\>          = int;</pre>
             * <pre>- Decay\<int &&\>         = int; </pre>
             * <pre>- Decay\<int const &\>    = int; </pre>
             * @example decay will convert any array with extent type to a pointer type <br/>
             * <pre>- Decay\<int[2]\>         = int *; </pre>
             * @example decay will convert any function signature type to a function pointer for that signature type <br/>
             * <pre>- Decay\<int(int)\>       = int (*)(int); </pre>
             *
             * <small> It's obviously used to decay radioactive Atomic types into non-radioactive ones. </small>
             */
            template < typename T >                 using Decay     = typename impl :: Decay < T > :: Type;

            /**
             * @brief Meta-type used to obtain the common, lvalue type that the given types can be converted to, if any
             * @tparam TypePack is the pack of types to find a common type for
             *
             * @example Possible results, cpp implementation defined <br/>
             * <pre>- Common \< int, float \> = float;</pre>
             * <pre>- Common \< uint16, uint64 \> = uint64;</pre>
             * <pre>- Common \< uint16, uint64 \> = uint64;</pre>
             * <pre>- Common \< String, uint64, float \> = String;</pre>
             */
            template < typename ... Types >         using Common    = typename impl :: Common < Types ... > :: Type;

            /**
             * @brief Meta-function used to check if a given type is convertible to another given type
             * @tparam From is the type being converted
             * @tparam To is the type to which the conversion is done
             */
            template < typename From, typename To >
            constexpr auto isConvertible () noexcept -> bool {
                return impl :: IsConvertible < From, To > :: value;
            }

            /**
             * @brief Meta-function used to check if two given types are the same
             * @tparam LeftType is the first type
             * @tparam RightType is the second type
             */
            template < typename LeftType, typename RightType >
            constexpr auto isSame () noexcept -> bool {
                return impl :: IsSame < LeftType, RightType > :: value;
            }

            /**
             * @brief Meta-function used to check if two given types can be compared by less than operator (\<)
             * @tparam LeftType is the first type
             * @tparam RightType is the second type
             */
            template < typename LeftType, typename RightType >
            constexpr auto lessThanPossible () noexcept -> bool {
                return impl :: LessThanPossible < LeftType, RightType > :: value;
            }

            /**
             * @brief Meta-function used to check if two given types can be compared by greater than operator (\>)
             * @tparam LeftType is the first type
             * @tparam RightType is the second type
             */
            template < typename LeftType, typename RightType >
            constexpr auto greaterThanPossible () noexcept -> bool {
                return impl :: GreaterThanPossible < LeftType, RightType > :: value;
            }

            /**
             * @brief Meta-function used to check if two given types can be compared by less than or equal to operator (\<=)
             * @tparam LeftType is the first type
             * @tparam RightType is the second type
             */
            template < typename LeftType, typename RightType >
            constexpr auto lessThanOrEqualToPossible () noexcept -> bool {
                return impl :: LessThanOrEqualToPossible < LeftType, RightType > :: value;
            }

            /**
             * @brief Meta-function used to check if two given types can be compared by greater than or equal to operator (\>=)
             * @tparam LeftType is the first type
             * @tparam RightType is the second type
             */
            template < typename LeftType, typename RightType >
            constexpr auto greaterThanOrEqualToPossible () noexcept -> bool {
                return impl :: GreaterThanOrEqualToPossible < LeftType, RightType > :: value;
            }

            /**
             * @brief Meta-function used to check if two given types can be compared by equal to operator (==)
             * @tparam LeftType is the first type
             * @tparam RightType is the second type
             */
            template < typename LeftType, typename RightType >
            constexpr auto equalToPossible () noexcept -> bool {
                return impl :: EqualToPossible < LeftType, RightType > :: value;
            }

            /**
             * @brief Meta-function used to check if two given types can be compared by not equal to operator (!=)
             * @tparam LeftType is the first type
             * @tparam RightType is the second type
             */
            template < typename LeftType, typename RightType >
            constexpr auto notEqualToPossible () noexcept -> bool {
                return impl :: NotEqualToPossible < LeftType, RightType > :: value;
            }

            /**
             * @brief Meta-function used to check if a given type is printable ( std :: ostream << type )
             * @tparam T is the type for which printability is checked
             */
            template < typename Type >
            constexpr auto isPrintable () noexcept -> bool {
                return impl :: IsPrintable < Type > :: value;
            }

            /**
             * @brief Meta-function used to check if a given type is an enum type
             * @tparam T is the type checked
             */
            template < typename Type >
            constexpr auto isEnum () noexcept -> bool {
                return impl :: IsEnum < Type > :: value;
            }

            /**
             * @brief Meta-function used to check if a given type is an union type
             * @tparam T is the type checked
             */
            template < typename Type >
            constexpr auto isUnion () noexcept -> bool {
                return impl :: IsUnion < Type > :: value;
            }

            /**
             * @brief Meta-function used to check if a given type is a class or struct type
             * @tparam T is the type checked
             */
            template < typename Type >
            constexpr auto isClass () noexcept -> bool {
                return impl :: IsClass < Type > :: value;
            }

            /**
             * @brief Meta-function used to check if a given type is a function type
             * @tparam T is the type checked
             */
            template < typename Type >
            constexpr auto isFunction () noexcept -> bool {
                return impl :: IsFunction < Type > :: value;
            }

            /**
             * @brief Meta-function used to check if a given type is a fundamental type ( bool, int types, float types )
             * @tparam T is the type checked
             */
            template < typename Type >
            constexpr auto isFundamental () noexcept -> bool {
                return impl :: IsFundamental < Type > :: value;
            }

            /**
             * @brief Meta-function used to check if a given type is an integral type ( bool, int types )
             * @tparam T is the type checked
             */
            template < typename Type >
            constexpr auto isIntegral () noexcept -> bool {
                return impl :: IsIntegral < Type > :: value;
            }

            /**
             * @brief Meta-function used to check if a given type is a floating point type ( float types )
             * @tparam T is the type checked
             */
            template < typename Type >
            constexpr auto isFloatingPoint () noexcept -> bool {
                return impl :: IsFloatingPoint < Type > :: value;
            }

            /**
             * @brief Meta-function used to check if a given type is an arithmetic type ( int, float types )
             * @tparam T is the type checked
             */
            template < typename Type >
            constexpr auto isArithmetic () noexcept -> bool {
                return impl :: IsArithmetic < Type > :: value;
            }

            /**
             * @brief Meta-function used to check if a given type is a base class of another given type
             * @tparam BaseType is the type given as a base class
             * @tparam DerivedType is the type given as a derived class
             */
            template < typename BaseType, typename DerivedType >
            constexpr auto isBaseFor () noexcept -> bool {
                return impl :: IsBaseOf < BaseType, DerivedType > :: value;
            }

            /**
             * @brief Meta-function used to check if a given type is derived from another given type
             * @tparam DerivedType is the type given as a derived class
             * @tparam BaseType is the type given as a base class
             */
            template < typename DerivedType, typename BaseType >
            constexpr auto isDerivedFrom () noexcept -> bool {
                return impl :: IsBaseOf < BaseType, DerivedType > :: value;
            }

            /**
             * @brief Meta-function used to check if a given type can be constructed without arguments ( has default constructor )
             * @tparam T is the type checked
             */
            template < typename Type >
            constexpr auto isDefaultConstructible () noexcept -> bool {
                return impl :: IsDefaultConstructible < Type > :: value;
            }

            /**
             * @brief Meta-function used to check if a given type can be constructed by copy ( has copy constructor )
             * @tparam T is the type checked
             */
            template < typename Type >
            constexpr auto isCopyConstructible () noexcept -> bool {
                return impl :: IsCopyConstructible < Type > :: value;
            }

            /**
             * @brief Meta-function used to check if a given type can be constructed by move ( has move constructor )
             * @tparam T is the type checked
             */
            template < typename Type >
            constexpr auto isMoveConstructible () noexcept -> bool {
                return impl :: IsMoveConstructible < Type > :: value;
            }

            /**
             * @brief Meta-function used to check if a given type can be assigned a value by copy ( has copy assignment operator )
             * @tparam T is the type checked
             */
            template < typename Type >
            constexpr auto isCopyAssignable () noexcept -> bool {
                return impl :: IsCopyAssignable < Type > :: value;
            }

            /**
             * @brief Meta-function used to check if a given type can be assigned a value by move ( has move assignment operator )
             * @tparam T is the type checked
             */
            template < typename Type >
            constexpr auto isMoveAssignable () noexcept -> bool {
                return impl :: IsMoveAssignable < Type > :: value;
            }

            /**
             * @brief Meta-function used to check if a given type is a callable type ( function / object with operator () )
             * @tparam T is the type checked
             */
            template < typename T >
            constexpr auto isCallable () noexcept -> bool {
                return impl :: IsCallable < T > :: value;
            }

            /**
             * @brief Meta-function used to check if a given type is derived from the Object base type
             * @tparam T is the type checked
             */
            template < typename T >
            constexpr auto isObjectDerived () noexcept -> bool {
                return isDerivedFrom < T, Object > ();
            }

            /**
             * @brief Meta-function used to check if a given type is a static-function type ( non-object callable )
             * @tparam T is the type checked
             */
            template < typename T >
            constexpr auto isStaticFunction () noexcept -> bool {
                return impl :: IsStaticFunction < T > :: value;
            }

            /**
             * @brief Meta-function used to check if a given type is a callable object ( non-static function )
             * @tparam T is the type checked
             */
            template < typename T >
            constexpr auto isObjectFunction () noexcept -> bool {
                return impl :: IsObjectFunction < T > :: value;
            }

            /**
             * @brief Meta-function used to check if a given type is an array type
             * @tparam T is the type checked
             */
            template < typename T >
            constexpr auto isArray () noexcept -> bool {
                return impl :: IsArray < T > :: value;
            }

            /**
             * @brief Meta-function used to check if a given type is a basic-pointer type = non-smart pointer type
             * @tparam T is the type checked
             */
            template < typename T >
            constexpr auto isBasicPointer () noexcept -> bool {
                return impl :: IsPointer < T > :: value;
            }

            /**
             * @brief Meta-function used to check if a given type is a smart-pointer type = derived from SmartPointer type
             * @tparam T is the type checked
             */
            template < typename T >
            constexpr auto isSmartPointer () noexcept -> bool {
                return impl :: IsSmartPointer < T > :: value;
            }

            /**
             * @brief Meta-function used to check if a given type is a basic or smart pointer type
             * @tparam T is the type checked
             */
            template < typename T >
            constexpr auto isPointer () noexcept -> bool {
                return isBasicPointer < T > () || isSmartPointer < T > ();
            }

            /**
             * @brief Meta-function used to check if a given type is a lvalue reference (&) type
             * @tparam T is the type checked
             */
            template < typename T >
            constexpr auto isLValueReference () noexcept -> bool {
                return impl :: IsLValueReference < T > :: value;
            }

            /**
             * @brief Meta-function used to check if a given type is a rvalue reference (&&) type
             * @tparam T is the type checked
             */
            template < typename T >
            constexpr auto isRValueReference () noexcept -> bool {
                return impl :: IsRValueReference < T > :: value;
            }

            /**
             * @brief Meta-function used to check if a given type is a lvalue reference (&) type
             * @tparam T is the type checked
             */
            template < typename T >
            constexpr auto isReference () noexcept -> bool {
                return impl :: IsLValueReference < T > :: value;
            }

            /**
             * @brief Meta-function used to check if a given type is a rvalue reference (&&) type
             * @tparam T is the type checked
             */
            template < typename T >
            constexpr auto isMoveReference () noexcept -> bool {
                return impl :: IsRValueReference < T > :: value;
            }

            /**
             * @brief Meta-function used to check if a given type is a member of an object
             * @tparam T is the type checked
             */
            template < typename T >
            constexpr auto isMemberObjectPointer () noexcept -> bool {
                return impl :: IsMemberObjectPointer < T > :: value;
            }

            /**
             * @brief Meta-function used to check if a given type is a member function of an object
             * @tparam T is the type checked
             */
            template < typename T >
            constexpr auto isMemberFunctionPointer () noexcept -> bool {
                return impl :: IsMemberFunctionPointer < T > :: value;
            }

            /**
             * @brief Meta-function used to check if a given type is a member of a given object
             * @tparam T is the type checked
             * @tparam C is the object of which T should be a member of
             */
            template < typename T, typename C >
            constexpr auto isMemberObjectPointer () noexcept -> bool {
                return impl :: IsMemberObjectPointer < T, C > :: value;
            }

            /**
             * @brief Meta-function used to check if a given type is a member function of a given object
             * @tparam T is the type checked
             * @tparam C is the object of which T should be a member function of
             */
            template < typename T, typename C >
            constexpr auto isMemberFunctionPointer () noexcept -> bool {
                return impl :: IsMemberFunctionPointer < T, C > :: value;
            }

            /**
             * @brief Meta-function used to check if a given type is a Pair type
             * @tparam T is the type checked
             */
            template < typename T >
            constexpr auto isPair () noexcept -> bool {
                return impl :: IsPair < T > :: value;
            }

            /**
             * @brief Meta-function used to check if a given type is a const type
             * @tparam T is the type checked
             */
            template < typename T >
            constexpr auto isConst () noexcept -> bool {
                return impl :: IsConst < T > :: value;
            }

            /**
             * @brief Meta-function used to check if a given type is a volatile type
             * @tparam T is the type checked
             */
            template < typename T >
            constexpr auto isVolatile () noexcept -> bool {
                return impl :: IsVolatile < T > :: value;
            }

            /**
             * @brief Meta-function used to invoke the most appropriate comparison function between two values
             * @tparam LeftType is the type to the left side of the == comparison
             * @tparam RightType is the type to the right side of the == comparison
             *
             * @example
             * <ul>
             *      <li>If == comparison is possible, invoke ==</li>
             *      <li>If == comparison is not possible, but LeftType is ObjectDerived and RightType is ObjectDerived, invoke Object :: equals</li>
             *      <li>If == comparison is not possible and LeftType is not ObjectDerived and RightType is not ObjectDerived, invoke comparison by address</li>
             * </ul>
             */
            template < typename LeftType, typename RightType, EnableIf < equalToPossible < LeftType, RightType > () > = 0 >
            constexpr auto equals ( LeftType const & left, RightType const & right ) noexcept -> bool {
                return left == right;
            }

            template < typename LeftType, typename RightType, EnableIf < ! equalToPossible < LeftType, RightType > () && isDerivedFrom < LeftType, Object > () && isDerivedFrom < RightType, Object > () > = 0 >
            constexpr auto equals ( LeftType const & left, RightType const & right, int = 0 ) noexcept -> bool {
                return left.equals ( right );
            }

            template < typename LeftType, typename RightType, EnableIf < ! equalToPossible < LeftType, RightType > () && ! ( isDerivedFrom < LeftType, Object > () && isDerivedFrom < RightType, Object > () ) > = 0 >
            constexpr auto equals ( LeftType const & left, RightType const & right, float = 0.0f ) noexcept -> bool {
                return & left == & right;
            }

            /**
             * @brief Meta-object helper, containing utilities for a given type. Alternative to above functions
             * @tparam T type given for which to access meta functions
             */
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
