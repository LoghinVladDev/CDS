//
// Created by uic70278 on 5/18/2022.
//

#ifndef __CDS_META_TYPE_TRAITS_HPP__
#define __CDS_META_TYPE_TRAITS_HPP__

#include <CDS/meta/Base>
#include <iostream>

namespace cds { // NOLINT(modernize-concat-nested-namespaces)

    class Object;

    /**
     * @class type representing a Pair of two types.
     * @tparam __K is the type of the first pair member
     * @tparam __V is the type of the second pair member
     */
    template < typename __K, typename __V > class Pair;

    /**
     * @class abstract type representing a smart pointer to a given type
     * @tparam __T is the addressed type
     */
    template < typename __T >               class SmartPointer;

    /**
     * @class type representing an Unique Pointer ( owned by one object only ) to a given type
     * @tparam __T is the addressed type
     */
    template < typename __T >               class UniquePointer;

    /**
     * @class abstract type representing a Shared Pointer ( deleted when not owned ) to a given type
     * @tparam __T is the addressed type
     */
    template < typename __T >               class SharedPointer;

    /**
     * @class abstract type representing a Foreign Pointer ( not owned, only addressed ) to a given type
     * @tparam __T is the addressed type
     */
    template < typename __T >               class ForeignPointer;

    /**
     * @class abstract type representing a Shared Pointer ( deleted when not owned ) with atomic guarding to a given type
     * @tparam __T is the addressed type
     */
    template < typename __T >               class AtomicSharedPointer;

    namespace meta { // NOLINT(modernize-concat-nested-namespaces)

        namespace __impl {

            /**
             * @brief Meta-type implementation used to check if two given types are the same
             * @tparam __LeftType is the first type
             * @tparam __RightType is the second type
             */
            template < typename __LeftType, typename __RightType >
            struct __IsSame : __FalseType {};

            template < typename __Type >
            struct __IsSame < __Type, __Type > : __TrueType {};


            /**
             * @brief Meta-type implementation used to check if two given types can be compared by less than operator (\<)
             * @tparam __LeftType is the first type
             * @tparam __RightType is the second type
             */
            template < typename __LeftType, typename __RightType, typename = Void <> > struct __LessThanPossible : __FalseType {};

            /**
             * @brief Meta-type implementation used to check if two given types can be compared by greater than operator (\>)
             * @tparam __LeftType is the first type
             * @tparam __RightType is the second type
             */
            template < typename __LeftType, typename __RightType, typename = Void <> > struct __GreaterThanPossible : __FalseType {};

            /**
             * @brief Meta-type implementation used to check if two given types can be compared by less than or equal to operator (\<=)
             * @tparam __LeftType is the first type
             * @tparam __RightType is the second type
             */
            template < typename __LeftType, typename __RightType, typename = Void <> > struct __LessThanOrEqualToPossible : __FalseType {};

            /**
             * @brief Meta-type implementation used to check if two given types can be compared by greater than or equal to operator (\>=)
             * @tparam __LeftType is the first type
             * @tparam __RightType is the second type
             */
            template < typename __LeftType, typename __RightType, typename = Void <> > struct __GreaterThanOrEqualToPossible : __FalseType {};

            /**
             * @brief Meta-type implementation used to check if two given types can be compared by equal to operator (==)
             * @tparam __LeftType is the first type
             * @tparam __RightType is the second type
             */
            template < typename __LeftType, typename __RightType, typename = Void <> > struct __EqualToPossible : __FalseType {};

            /**
             * @brief Meta-type implementation used to check if two given types can be compared by not equal to operator (!=)
             * @tparam __LeftType is the first type
             * @tparam __RightType is the second type
             */
            template < typename __LeftType, typename __RightType, typename = Void <> > struct __NotEqualToPossible : __FalseType {};

            template < typename __Type, typename = Void <> > struct __IndirectionPossible : __FalseType {};

            template < typename __Type, typename = Void <> > struct __PrefixIncrementPossible : __FalseType {};

            template < typename __LeftType, typename __RightType >
            struct __LessThanPossible < __LeftType, __RightType, Void < decltype ( valueOf < __LeftType > () < valueOf < __RightType > () ) > > : __TrueType {};

            template < typename __LeftType, typename __RightType >
            struct __GreaterThanPossible < __LeftType, __RightType, Void < decltype ( valueOf < __LeftType > () > valueOf < __RightType > () ) > > : __TrueType {};

            template < typename __LeftType, typename __RightType >
            struct __LessThanOrEqualToPossible < __LeftType, __RightType, Void < decltype ( valueOf < __LeftType > () <= valueOf < __RightType > () ) > > : __TrueType {};

            template < typename __LeftType, typename __RightType >
            struct __GreaterThanOrEqualToPossible < __LeftType, __RightType, Void < decltype ( valueOf < __LeftType > () >= valueOf < __RightType > () ) > > : __TrueType {};

            template < typename __LeftType, typename __RightType >
            struct __EqualToPossible < __LeftType, __RightType, Void < decltype ( valueOf < __LeftType > () == valueOf < __RightType > () ) > > : __TrueType {};

            template < typename __LeftType, typename __RightType >
            struct __NotEqualToPossible < __LeftType, __RightType, Void < decltype ( valueOf < __LeftType > () != valueOf < __RightType > () ) > > : __TrueType {};

            template < typename __Type >
            struct __IndirectionPossible < __Type, Void < decltype ( * valueOf < __Type > () ) > > : __TrueType {};

            template < typename __Type >
            struct __PrefixIncrementPossible < __Type, Void < decltype ( ++ valueOf < __Type > () ) > > : __TrueType {};

            /**
             * @brief Meta-type implementation used to check if a given type is printable ( std :: ostream << type )
             * @tparam __T is the type for which printability is checked
             */
            template < typename __T, typename = void >
            struct __IsPrintable : __FalseType {};

            template < typename __T >
            struct __IsPrintable < __T, Void < decltype ( std :: cout << valueOf < __T > () ) > > : __TrueType {};

            /**
             * @brief Meta-type implementation used to check if a given type is an enum type
             * @tparam __T is the type checked
             */
            template < typename __T >
            struct __IsEnum : __BoolConstant < std :: is_enum < __T > :: value > {};

            /**
             * @brief Meta-type implementation used to check if a given type is an union type
             * @tparam __T is the type checked
             */
            template < typename __T >
            struct __IsUnion : __BoolConstant < std :: is_union < __T > :: value > {};

            /**
             * @brief Meta-type implementation used to check if a given type is a class or struct type
             * @tparam __T is the type checked
             */
            template < typename __T >
            struct __IsClass : __BoolConstant < std :: is_class < __T > :: value > {};

            /**
             * @brief Meta-type implementation used to check if a given type is a function type
             * @tparam __T is the type checked
             */
            template < typename __T >
            struct __IsFunction : __BoolConstant < std :: is_function < __T > :: value > {};

            /**
             * @brief Meta-type implementation used to check if a given type is a fundamental type ( bool, int types, float types )
             * @tparam __T is the type checked
             */
            template < typename __T >
            struct __IsFundamental : __BoolConstant < std :: is_fundamental < __T > :: value > {};

            /**
             * @brief Meta-type implementation used to check if a given type is an integral type ( bool, int types )
             * @tparam __T is the type checked
             */
            template < typename __T >
            struct __IsIntegral : __BoolConstant < std :: is_integral < __T > :: value > {};

            /**
             * @brief Meta-type implementation used to check if a given type is a floating point type ( float types )
             * @tparam __T is the type checked
             */
            template < typename __T >
            struct __IsFloatingPoint : __BoolConstant < std :: is_floating_point < __T > :: value > {};

            /**
             * @brief Meta-type implementation used to check if a given type is an arithmetic type ( int, float types )
             * @tparam __T is the type checked
             */
            template < typename __T >
            struct __IsArithmetic : __BoolConstant < std :: is_arithmetic < __T > :: value > {};

            namespace __isSignedImpl {
                template < typename __T, bool = __IsArithmetic < __T > :: value >
                struct __IsSigned : __FalseType {};

                template < typename __T >
                struct __IsSigned < __T, true > : __impl :: __BoolConstant < __T ( -1 ) < __T ( 0 ) > {};
            }

            template < typename __T >
            struct __IsSigned : __isSignedImpl :: __IsSigned < __T > :: Type {};

            /**
             * @brief Meta-type implementation used to check if a given type can be constructed without arguments ( has default constructor )
             * @tparam __T is the type checked
             */
            template < typename __T >
            struct __IsDefaultConstructible : __BoolConstant < std :: is_default_constructible < __T > :: value > {};

            /**
             * @brief Meta-type implementation used to check if a given type can be constructed by copy ( has copy constructor )
             * @tparam __T is the type checked
             */
            template < typename __T >
            struct __IsCopyConstructible : __BoolConstant < std :: is_copy_constructible < __T > :: value > {};

            /**
             * @brief Meta-type implementation used to check if a given type can be constructed by move ( has move constructor )
             * @tparam __T is the type checked
             */
            template < typename __T >
            struct __IsMoveConstructible : __BoolConstant < std :: is_move_constructible < __T > :: value > {};

            /**
             * @brief Meta-type implementation used to check if a given type can be assigned a value by copy ( has copy assignment operator )
             * @tparam __T is the type checked
             */
            template < typename __T >
            struct __IsCopyAssignable : __BoolConstant < std :: is_copy_assignable < __T > :: value > {};

            /**
             * @brief Meta-type implementation used to check if a given type can be assigned a value by move ( has move assignment operator )
             * @tparam __T is the type checked
             */
            template < typename __T >
            struct __IsMoveAssignable : __BoolConstant < std :: is_move_assignable < __T > :: value > {};

            namespace __baseOfImpl {
                template < typename __BaseType >                            auto __conversionTest ( __BaseType const volatile * ) noexcept -> __TrueType;
                template < typename >                                       auto __conversionTest ( void     const volatile *   ) noexcept -> __FalseType;

                template < typename, typename >                             auto __testBaseOf ( ... ) -> __TrueType;
                template < typename __BaseType, typename __DerivedType >    auto __testBaseOf ( int ) ->
                        decltype ( __conversionTest < __BaseType > ( addressOf < __DerivedType > () ) );
            }

            /**
             * @brief Meta-type implementation used to check if a given type is a base class of another given type
             * @tparam __BaseType is the type given as a base class
             * @tparam __DerivedType is the type given as a derived class
             */
            template < typename __BaseType, typename __DerivedType >
            struct __IsBaseOf : __BoolConstant <
                    __IsClass < __BaseType > :: value && __IsClass < __DerivedType > :: value &&
                    decltype ( __baseOfImpl :: __testBaseOf < __BaseType, __DerivedType > (0) ) :: value
            > {};

            /**
             * @brief Meta-type implementation used to check if a given type is a callable type ( function / object with operator () )
             * @tparam __T is the type checked
             */
            template < typename __T, typename = void >
            struct __IsCallable {
                /// if the given type is a class, or a class reference, use the operator() deduction implementation value. Otherwise, false,
                /// unless it is overridden by a partial template specialization
                constexpr static bool value = __Conditional <
                        __IsClass < typename __RemoveReference < __T > :: Type > :: value,
                        __IsCallable < typename __RemoveReference < __T > :: Type, int >,
                        __FalseType
                > :: Type :: value;
            };

            template < typename __T, typename __U, typename ... __A >
            struct __IsCallable < __T ( __A ... ), __U > : __TrueType {};

            template < typename __T, typename __U, typename ... __A >
            struct __IsCallable < __T (*) ( __A ... ), __U > : __TrueType {};

            template < typename __T, typename __U, typename ... __A >
            struct __IsCallable < __T (&) ( __A ... ), __U > : __TrueType {};

            template < typename __T, typename __U, typename ... __A >
            struct __IsCallable < __T ( __A ..., ... ), __U > : __TrueType {};

            template < typename __T, typename __U, typename ... __A >
            struct __IsCallable < __T (*) ( __A ..., ... ), __U > : __TrueType {};

            template < typename __T, typename __U, typename ... __A >
            struct __IsCallable < __T (&) ( __A ..., ... ), __U > : __TrueType {};

            template < typename __T, typename __U, typename ... __A >
            struct __IsCallable < __T ( __A ... ) const, __U > : __TrueType {};

            template < typename __T, typename __U, typename ... __A >
            struct __IsCallable < __T ( __A ... ) volatile, __U > : __TrueType {};

            template < typename __T, typename __U, typename ... __A >
            struct __IsCallable < __T ( __A ... ) const volatile, __U > : __TrueType {};

            template < typename __T, typename __U, typename ... __A >
            struct __IsCallable < __T ( __A ..., ... ) const, __U > : __TrueType {};

            template < typename __T, typename __U, typename ... __A >
            struct __IsCallable < __T ( __A ..., ... ) volatile, __U > : __TrueType {};

            template < typename __T, typename __U, typename ... __A >
            struct __IsCallable < __T ( __A ..., ... ) const volatile, __U > : __TrueType {};

            template < typename __T, typename __U, typename ... __A >
            struct __IsCallable < __T ( __A ... ) &, __U > : __TrueType {};

            template < typename __T, typename __U, typename ... __A >
            struct __IsCallable < __T ( __A ... ) const &, __U > : __TrueType {};

            template < typename __T, typename __U, typename ... __A >
            struct __IsCallable < __T ( __A ... ) volatile &, __U > : __TrueType {};

            template < typename __T, typename __U, typename ... __A >
            struct __IsCallable < __T ( __A ... ) const volatile &, __U > : __TrueType {};

            template < typename __T, typename __U, typename ... __A >
            struct __IsCallable < __T ( __A ..., ... ) const &, __U > : __TrueType {};

            template < typename __T, typename __U, typename ... __A >
            struct __IsCallable < __T ( __A ..., ... ) volatile &, __U > : __TrueType {};

            template < typename __T, typename __U, typename ... __A >
            struct __IsCallable < __T ( __A ..., ... ) const volatile &, __U > : __TrueType {};

            template < typename __T, typename __U, typename ... __A >
            struct __IsCallable < __T ( __A ... ) &&, __U > : __TrueType {};

            template < typename __T, typename __U, typename ... __A >
            struct __IsCallable < __T ( __A ... ) const &&, __U > : __TrueType {};

            template < typename __T, typename __U, typename ... __A >
            struct __IsCallable < __T ( __A ... ) volatile &&, __U > : __TrueType {};

            template < typename __T, typename __U, typename ... __A >
            struct __IsCallable < __T ( __A ... ) const volatile &&, __U > : __TrueType {};

            template < typename __T, typename __U, typename ... __A >
            struct __IsCallable < __T ( __A ..., ... ) const &&, __U > : __TrueType {};

            template < typename __T, typename __U, typename ... __A >
            struct __IsCallable < __T ( __A ..., ... ) volatile &&, __U > : __TrueType {};

            template < typename __T, typename __U, typename ... __A >
            struct __IsCallable < __T ( __A ..., ... ) const volatile &&, __U > : __TrueType {};


            template < typename __T >
            struct __IsCallable < __T, int > {
            private:
                using __y = char (&)[1];
                using __n = char (&)[2];

                struct __Fallback { auto operator ()() -> void {} };
                struct __Derived : __T, __Fallback {};

                template < typename __U, __U >
                struct __Check;

                __CDS_WarningSuppression_NoReturnStatement_SuppressEnable
                template < typename >
                static auto __test ( ... ) -> __y {} // NOLINT(clion-misra-cpp2008-8-4-1)

                template < typename __C >
                static auto __test ( __Check < auto ( __Fallback :: * ) () -> void, & __C :: operator () > * ) -> __n {}
                __CDS_WarningSuppression_NoReturnStatement_SuppressDisable

            public:
                constexpr static bool value = sizeof ( __test < __Derived > (0) ) == sizeof (__y);
            };

            /**
             * @brief Meta-type implementation used to obtain the type name in a StringLiteral format ( char const * )
             * @tparam __T is the type for which the name is obtained
             */
            template < typename __T > struct __TypeParseTraits { constexpr static StringLiteral name = "Undefined"; };

            /**
             * @brief Meta-type implementation used to check if a given type is a static-function type ( non-object callable )
             * @tparam __T is the type checked
             */
            template < typename __T, typename = void > struct __IsStaticFunction : __FalseType {};

            /**
             * @brief Meta-type implementation used to check if a given type is a callable object ( non-static function )
             * @tparam __T is the type checked
             */
            template < typename __T, typename = void > struct __IsObjectFunction : __FalseType {};

            template < typename __T >
            struct __IsStaticFunction < __T > : __BoolConstant < __IsFunction < __T > :: value && ! __IsObjectFunction < __T > :: value > {};

            template < typename __T >
            struct __IsObjectFunction < __T, Void < decltype ( & __T :: operator () ) > > : __TrueType {};

            /**
             * @brief Meta-type implementation used to check if a given type is an array type
             * @tparam __T is the type checked
             */
            template < typename >                   struct __IsArray                    : __FalseType {};
            template < typename __T, Size __size >  struct __IsArray < __T [__size] >   : __TrueType {};
            template < typename __T >               struct __IsArray < __T [] >         : __TrueType {};

            namespace __isPointerImpl {
                /**
                 * @brief Meta-type helper implementation used to check if a given type is a pointer type
                 * @tparam __T is the type checked
                 */
                template < typename >       struct __IsPointer : __FalseType {};
                template < typename __T >   struct __IsPointer < __T * > : __TrueType {};
            }

            /**
             * @brief Meta-type implementation used to check if a given type is a pointer type
             * @tparam __T is the type checked
             */
            template < typename __T >       struct __IsPointer : __isPointerImpl :: __IsPointer < typename __RemoveConstVolatile < __T > :: Type > {};

            /**
             * @brief Meta-type implementation used to check if a given type is a lvalue reference (&) type
             * @tparam __T is the type checked
             */
            template < typename >           struct __IsLValueReference              : __FalseType {};
            template < typename __T >       struct __IsLValueReference < __T & >    : __TrueType {};

            /**
             * @brief Meta-type implementation used to check if a given type is a rvalue reference (&&) type
             * @tparam __T is the type checked
             */
            template < typename >           struct __IsRValueReference              : __FalseType {};
            template < typename __T >       struct __IsRValueReference < __T && >   : __TrueType {};

            namespace __isMemberPointerImpl {
                /**
                 * @brief Meta-type helper implementation used to check if a given type is a member of an object
                 * @tparam __T is the type checked
                 */
                template < typename >                   struct __IsMemberObjectPointer                      : __FalseType {};
                template < typename __T, typename __C > struct __IsMemberObjectPointer < __T __C :: * >     : __BoolConstant < ! __IsFunction < __T > :: value > {};
            }

            /**
             * @brief Meta-type implementation used to check if a given type is a member of an object
             * @tparam __T is the type checked
             */
            template < typename __T, typename = void >
            struct __IsMemberObjectPointer : __FalseType {};

            template < typename __T >               struct __IsMemberObjectPointer < __T >                  : __isMemberPointerImpl :: __IsMemberObjectPointer < typename __RemoveConstVolatile < __T > :: Type > {};
            template < typename __T, typename __C > struct __IsMemberObjectPointer < __T __C :: *, __C >    : __IsMemberObjectPointer < typename __RemoveConstVolatile < __T __C :: * > :: Type > {};

            namespace __isMemberPointerImpl {
                /**
                 * @brief Meta-type helper implementation used to check if a given type is a member function of an object
                 * @tparam __T is the type checked
                 */
                template < typename >                   struct __IsMemberFunctionPointer                    : __FalseType {};
                template < typename __T, typename __C > struct __IsMemberFunctionPointer < __T __C :: * >   : __BoolConstant < __IsFunction < __T > :: value > {};
            }

            /**
             * @brief Meta-type implementation used to check if a given type is a member function of an object
             * @tparam __T is the type checked
             */
            template < typename __T, typename = void > struct __IsMemberFunctionPointer : __FalseType {};

            template < typename __T >               struct __IsMemberFunctionPointer < __T >                : __isMemberPointerImpl :: __IsMemberFunctionPointer < typename __RemoveConstVolatile < __T > :: Type > {};
            template < typename __T, typename __C > struct __IsMemberFunctionPointer < __T __C :: *, __C >  : __isMemberPointerImpl :: __IsMemberFunctionPointer < typename __RemoveConstVolatile < __T __C :: * > :: Type > {};


            /**
             * @brief Meta-type implementation used to check if a given type is a Pair type
             * @tparam __T is the type checked
             */
            template < typename __T >               struct __IsPair                                           : __FalseType {};
            template < typename __K, typename __V > struct __IsPair < cds :: Pair < __K, __V > >              : __TrueType {};


            /**
             * @brief Meta-type implementation used to check if a given type is a Smart Pointer derived-type
             * @tparam __T is the type checked
             */
            template < typename __T >               struct __IsSmartPointer                                                         : __FalseType {};
            template < typename __T >               struct __IsSmartPointer < cds :: UniquePointer < __T > >                        : __TrueType {};
            template < typename __T >               struct __IsSmartPointer < cds :: SharedPointer < __T > >                        : __TrueType {};
            template < typename __T >               struct __IsSmartPointer < cds :: ForeignPointer < __T > >                       : __TrueType {};
            template < typename __T >               struct __IsSmartPointer < cds :: AtomicSharedPointer < __T > >                  : __TrueType {};

            /**
             * @brief Meta-type implementation used to check if a given type is a const type
             * @tparam __T is the type checked
             */
            template < typename >           struct __IsConst                        : __FalseType {};
            template < typename __T >       struct __IsConst < __T const >          : __TrueType {};

            /**
             * @brief Meta-type implementation used to check if a given type is a volatile type
             * @tparam __T is the type checked
             */
            template < typename >           struct __IsVolatile                     : __FalseType {};
            template < typename __T >       struct __IsVolatile < __T volatile >    : __TrueType {};

            namespace __decayImpl {
                /**
                 * @brief Meta-type helper implementation used to obtain safe pass-by-value equivalent type of a given type
                 * @tparam __T is the type for which to obtain a pass by value
                 *
                 * This will act as a switch based on the isArray or isFunction conditions
                 * <ul>
                 *  <li> If none are satisfied, go with removal of modifiers </li>
                 *  <li> If is array, go with extent removal and addition of pointer </li>
                 *  <li> If is function, go with addition of pointer </li>
                 * </ul>
                 */
                template < typename __T, bool __isArray = __IsArray < __T > :: value, bool __isFunction = __IsFunction < __T > :: value >
                struct __Decay {};

                template < typename __T >
                struct __Decay < __T, false, false > {
                    using Type = typename __RemoveConstVolatile < __T > :: Type;
                };

                template < typename __T >
                struct __Decay < __T, true, false > {
                    using Type = typename __RemoveExtent < __T > :: Type *;
                };

                template < typename __T >
                struct __Decay < __T, false, true > {
                    using Type = typename __AddPointer < __T > :: Type *;
                };
            }

            /**
             * @brief Meta-type implementation used to obtain safe pass-by-value equivalent type of a given type
             * @tparam __T is the type for which to obtain a pass by value
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
            template < typename __T >
            struct __Decay {

            private:
                using FirstParseDecayedType = typename __RemoveReference < __T > :: Type;

            public:
                using Type = typename __decayImpl :: __Decay < FirstParseDecayedType > :: Type;
            };


            /**
             * @brief Meta-type implementation used to obtain the common, lvalue type that the given types can be converted to, if any
             * @tparam __TypePack is the pack of types to find a common type for
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
            template < typename ... __TypePack >    struct __Common;
            template <>                             struct __Common <> {};
            template < typename __T >               struct __Common < __T > : __Common < __T, __T > {};

            namespace __commonImpl {
                /**
                 * @brief Meta-type helper implementation used to obtain the common type between two types via ternary operator, if possible
                 */
                struct __CommonTest {
                    template < typename __T >   struct SuccessType { using Type = __T; };
                                                struct FailureType { };

                    template < typename __T, typename __U > using ConditionalType = decltype ( true ? valueOf < __T > () : valueOf < __U > () );
                    template < typename __T, typename __U > static SuccessType < typename __Decay < ConditionalType < __T, __U > > :: Type >                                __test ( int );
                    template < typename __T, typename __U > static SuccessType < typename __RemoveConstVolatile < ConditionalType < __T const &, __U const & > > :: Type >  __test2 ( int ); /// cpp-17?

                    template < typename, typename >         static FailureType                                                                                              __test2 ( ... );
                    template < typename __T, typename __U > static decltype ( __CommonTest :: __test2 < __T, __U > ( 0 ) )                                                  __test ( ... );
                };

                /**
                 * @brief Meta-type helper implementation used to decay the types of two given types before using the ternary helper
                 * @tparam __T1 is the type given as first type
                 * @tparam __T2 is the type given as second type
                 * @tparam __DecayedT1 is the decayed type of the first type
                 * @tparam __DecayedT2 is the decayed type of the second type
                 */
                template < typename __T1, typename __T2, typename __DecayedT1 = typename __Decay < __T1 > :: Type, typename __DecayedT2 = typename __Decay < __T2 > :: Type >
                struct __CommonDecayed {
                    using Type = __Common < __DecayedT1, __DecayedT2 >;
                };

                template < typename __T1, typename __T2 >
                struct __CommonDecayed < __T1, __T2, __T1, __T2 > : private __CommonTest {
                    using Type = decltype ( __CommonTest :: __test < __T1, __T2 > (0) );
                };

                /**
                 * @brief Meta-type helper implementation used to preserve the remaining type pack in the case of more than two types given to common
                 */
                template < typename ... >
                struct __CommonPack {};

                /**
                 * @brief Meta-type helper implementation used to apply the fold expression to reducing the two-or-more types of common by the following rule:
                 *
                 * Common \< T1, T2, T3, ... \> = Common \< Common \< T1, T2 \>, T3, ... \>
                 */
                template < typename, typename, typename = void >
                struct __CommonFold {};

                template < typename __CurrentType, typename ... __RemainingTypes >
                struct __CommonFold < __CurrentType, __CommonPack < __RemainingTypes ... >, Void < typename __CurrentType :: Type > > :
                        public meta :: __impl :: __Common < typename __CurrentType :: Type, __RemainingTypes ... > {};

                template < typename __CurrentType, typename __RemainingType >
                struct __CommonFold < __CurrentType, __RemainingType, void > {};
            }

            template < typename __T1, typename __T2 >
            struct __Common < __T1, __T2 > : public __commonImpl :: __CommonDecayed < __T1, __T2 > :: Type {};

            template < typename __T1, typename __T2, typename ... __RemainingTypes >
            struct __Common < __T1, __T2, __RemainingTypes ... > :
                    public __commonImpl :: __CommonFold < __Common < __T1, __T2 >, __commonImpl :: __CommonPack < __RemainingTypes ... > > {};

            namespace __isConvertibleImpl {
                /**
                 * @brief Meta-type helper used to check if a given type is convertible to another given type
                 * @tparam __From is the type being converted
                 * @tparam __To is the type to which the conversion is done
                 */
                template < typename __From, typename __To, bool = __IsVoid < __From > :: value || __IsFunction < __To > :: value || __IsArray < __To > :: value >
                struct __IsConvertible {
                    using Type = typename __IsVoid < __To > :: Type;
                };

                template < typename __From, typename __To >
                struct __IsConvertible < __From, __To, false > {
                private:
                    template < typename __To1 >
                    static void __metaTest ( __To1 ) noexcept;

                    template < typename __From1, typename __To1, typename = decltype ( __metaTest < __To1 > ( valueOf < __From1 > () ) ) >
                    static __TrueType __test (int);

                    template < typename, typename >
                    static __FalseType __test (...);

                public:
                    using Type = decltype ( __test < __From, __To > (0) );
                };
            }

            /**
             * @brief Meta-type implementation used to check if a given type is convertible to another given type
             * @tparam __From is the type being converted
             * @tparam __To is the type to which the conversion is done
             */
            template < typename __From, typename __To >
            struct __IsConvertible : __isConvertibleImpl :: __IsConvertible < __From, __To > :: Type {};

            template < typename __T >
            struct __MakeSigned {
                using Type = typename std :: make_signed < __T > :: type;
            };

            template < typename __T >
            struct __MakeUnsigned {
                using Type = typename std :: make_unsigned < __T > :: type;
            };
        }

        /**
         * @brief Meta-type used to obtain safe pass-by-value equivalent type of a given type
         * @tparam __T is the type for which to obtain a pass by value
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
        template < typename __T >                   using Decay     = typename __impl :: __Decay < __T > :: Type;

        /**
         * @brief Meta-type used to obtain the common, lvalue type that the given types can be converted to, if any
         * @tparam __TypePack is the pack of types to find a common type for
         *
         * @example Possible results, cpp implementation defined <br/>
         * <pre>- Common \< int, float \> = float;</pre>
         * <pre>- Common \< uint16, uint64 \> = uint64;</pre>
         * <pre>- Common \< uint16, uint64 \> = uint64;</pre>
         * <pre>- Common \< String, uint64, float \> = String;</pre>
         */
        template < typename ... __Types >           using Common        = typename __impl :: __Common < __Types ... > :: Type;

        template < typename __T >                   using MakeSigned    = typename __impl :: __MakeSigned < __T > :: Type;
        template < typename __T >                   using MakeUnsigned  = typename __impl :: __MakeUnsigned < __T > :: Type;

        /**
         * @brief Meta-function used to check if a given type is convertible to another given type
         * @tparam __From is the type being converted
         * @tparam __To is the type to which the conversion is done
         */
        template < typename __From, typename __To >
        constexpr auto isConvertible () noexcept -> bool {
            return __impl :: __IsConvertible < __From, __To > :: value;
        }

        /**
         * @brief Meta-function used to check if two given types are the same
         * @tparam __LeftType is the first type
         * @tparam __RightType is the second type
         */
        template < typename __LeftType, typename __RightType >
        constexpr auto isSame () noexcept -> bool {
            return __impl :: __IsSame < __LeftType, __RightType > :: value;
        }

        /**
         * @brief Meta-function used to check if two given types can be compared by less than operator (\<)
         * @tparam __LeftType is the first type
         * @tparam __RightType is the second type
         */
        template < typename __LeftType, typename __RightType >
        constexpr auto lessThanPossible () noexcept -> bool {
            return __impl :: __LessThanPossible < __LeftType, __RightType > :: value;
        }

        /**
         * @brief Meta-function used to check if two given types can be compared by greater than operator (\>)
         * @tparam __LeftType is the first type
         * @tparam __RightType is the second type
         */
        template < typename __LeftType, typename __RightType >
        constexpr auto greaterThanPossible () noexcept -> bool {
            return __impl :: __GreaterThanPossible < __LeftType, __RightType > :: value;
        }

        /**
         * @brief Meta-function used to check if two given types can be compared by less than or equal to operator (\<=)
         * @tparam __LeftType is the first type
         * @tparam __RightType is the second type
         */
        template < typename __LeftType, typename __RightType >
        constexpr auto lessThanOrEqualToPossible () noexcept -> bool {
            return __impl :: __LessThanOrEqualToPossible < __LeftType, __RightType > :: value;
        }

        /**
         * @brief Meta-function used to check if two given types can be compared by greater than or equal to operator (\>=)
         * @tparam __LeftType is the first type
         * @tparam __RightType is the second type
         */
        template < typename __LeftType, typename __RightType >
        constexpr auto greaterThanOrEqualToPossible () noexcept -> bool {
            return __impl :: __GreaterThanOrEqualToPossible < __LeftType, __RightType > :: value;
        }

        /**
         * @brief Meta-function used to check if two given types can be compared by equal to operator (==)
         * @tparam __LeftType is the first type
         * @tparam __RightType is the second type
         */
        template < typename __LeftType, typename __RightType >
        constexpr auto equalToPossible () noexcept -> bool {
            return __impl :: __EqualToPossible < __LeftType, __RightType > :: value;
        }

        /**
         * @brief Meta-function used to check if two given types can be compared by not equal to operator (!=)
         * @tparam __LeftType is the first type
         * @tparam __RightType is the second type
         */
        template < typename __LeftType, typename __RightType >
        constexpr auto notEqualToPossible () noexcept -> bool {
            return __impl :: __NotEqualToPossible < __LeftType, __RightType > :: value;
        }

        /**
         * @brief Meta-function used to check if a given type is printable ( std :: ostream << type )
         * @tparam __Type is the type for which printability is checked
         */
        template < typename __Type >
        constexpr auto isPrintable () noexcept -> bool {
            return __impl :: __IsPrintable < __Type > :: value;
        }

        /**
         * @brief Meta-function used to check if a given type is an enum type
         * @tparam __Type is the type checked
         */
        template < typename __Type >
        constexpr auto isEnum () noexcept -> bool {
            return __impl :: __IsEnum < __Type > :: value;
        }

        /**
         * @brief Meta-function used to check if a given type is an union type
         * @tparam __Type is the type checked
         */
        template < typename __Type >
        constexpr auto isUnion () noexcept -> bool {
            return __impl :: __IsUnion < __Type > :: value;
        }

        /**
         * @brief Meta-function used to check if a given type is a class or struct type
         * @tparam __Type is the type checked
         */
        template < typename __Type >
        constexpr auto isClass () noexcept -> bool {
            return __impl :: __IsClass < __Type > :: value;
        }

        /**
         * @brief Meta-function used to check if a given type is a function type
         * @tparam __Type is the type checked
         */
        template < typename __Type >
        constexpr auto isFunction () noexcept -> bool {
            return __impl :: __IsFunction < __Type > :: value;
        }

        /**
         * @brief Meta-function used to check if a given type is a fundamental type ( bool, int types, float types )
         * @tparam __Type is the type checked
         */
        template < typename __Type >
        constexpr auto isFundamental () noexcept -> bool {
            return __impl :: __IsFundamental < __Type > :: value;
        }

        /**
         * @brief Meta-function used to check if a given type is an integral type ( bool, int types )
         * @tparam __Type is the type checked
         */
        template < typename __Type >
        constexpr auto isIntegral () noexcept -> bool {
            return __impl :: __IsIntegral < __Type > :: value;
        }

        /**
         * @brief Meta-function used to check if a given type is a floating point type ( float types )
         * @tparam __Type is the type checked
         */
        template < typename __Type >
        constexpr auto isFloatingPoint () noexcept -> bool {
            return __impl :: __IsFloatingPoint < __Type > :: value;
        }

        /**
         * @brief Meta-function used to check if a given type is an arithmetic type ( int, float types )
         * @tparam __Type is the type checked
         */
        template < typename __Type >
        constexpr auto isArithmetic () noexcept -> bool {
            return __impl :: __IsArithmetic < __Type > :: value;
        }

        template < typename __Type >
        constexpr auto isSigned () noexcept -> bool {
            return __impl :: __IsSigned < __Type > :: value;
        }

        template < typename __Type >
        constexpr auto isUnsigned () noexcept -> bool {
            return
                    isArithmetic < __Type > () &&
                    ! isSigned < __Type > ();
        }

        /**
         * @brief Meta-function used to check if a given type is a base class of another given type
         * @tparam __BaseType is the type given as a base class
         * @tparam __DerivedType is the type given as a derived class
         */
        template < typename __BaseType, typename __DerivedType >
        constexpr auto isBaseFor () noexcept -> bool {
            return __impl :: __IsBaseOf < __BaseType, __DerivedType > :: value;
        }

        /**
         * @brief Meta-function used to check if a given type is derived from another given type
         * @tparam __DerivedType is the type given as a derived class
         * @tparam __BaseType is the type given as a base class
         */
        template < typename __DerivedType, typename __BaseType >
        constexpr auto isDerivedFrom () noexcept -> bool {
            return __impl :: __IsBaseOf < __BaseType, __DerivedType > :: value;
        }

        /**
         * @brief Meta-function used to check if a given type can be constructed without arguments ( has default constructor )
         * @tparam __Type is the type checked
         */
        template < typename __Type >
        constexpr auto isDefaultConstructible () noexcept -> bool {
            return __impl :: __IsDefaultConstructible < __Type > :: value;
        }

        /**
         * @brief Meta-function used to check if a given type can be constructed by copy ( has copy constructor )
         * @tparam __Type is the type checked
         */
        template < typename __Type >
        constexpr auto isCopyConstructible () noexcept -> bool {
            return __impl :: __IsCopyConstructible < __Type > :: value;
        }

        /**
         * @brief Meta-function used to check if a given type can be constructed by move ( has move constructor )
         * @tparam __Type is the type checked
         */
        template < typename __Type >
        constexpr auto isMoveConstructible () noexcept -> bool {
            return __impl :: __IsMoveConstructible < __Type > :: value;
        }

        /**
         * @brief Meta-function used to check if a given type can be assigned a value by copy ( has copy assignment operator )
         * @tparam __Type is the type checked
         */
        template < typename __Type >
        constexpr auto isCopyAssignable () noexcept -> bool {
            return __impl :: __IsCopyAssignable < __Type > :: value;
        }

        /**
         * @brief Meta-function used to check if a given type can be assigned a value by move ( has move assignment operator )
         * @tparam __Type is the type checked
         */
        template < typename __Type >
        constexpr auto isMoveAssignable () noexcept -> bool {
            return __impl :: __IsMoveAssignable < __Type > :: value;
        }

        /**
         * @brief Meta-function used to check if a given type is a callable type ( function / object with operator () )
         * @tparam __Type is the type checked
         */
        template < typename __Type >
        constexpr auto isCallable () noexcept -> bool {
            return __impl :: __IsCallable < __Type > :: value;
        }

        /**
         * @brief Meta-function used to check if a given type is derived from the Object base type
         * @tparam __Type is the type checked
         */
        template < typename __Type >
        constexpr auto isObjectDerived () noexcept -> bool {
            return isDerivedFrom < __Type, Object > ();
        }

        /**
         * @brief Meta-function used to check if a given type is a static-function type ( non-object callable )
         * @tparam __Type is the type checked
         */
        template < typename __Type >
        constexpr auto isStaticFunction () noexcept -> bool {
            return __impl :: __IsStaticFunction < __Type > :: value;
        }

        /**
         * @brief Meta-function used to check if a given type is a callable object ( non-static function )
         * @tparam __Type is the type checked
         */
        template < typename __Type >
        constexpr auto isObjectFunction () noexcept -> bool {
            return __impl :: __IsObjectFunction < __Type > :: value;
        }

        /**
         * @brief Meta-function used to check if a given type is an array type
         * @tparam __Type is the type checked
         */
        template < typename __Type >
        constexpr auto isArray () noexcept -> bool {
            return __impl :: __IsArray < __Type > :: value;
        }

        /**
         * @brief Meta-function used to check if a given type is a basic-pointer type = non-smart pointer type
         * @tparam __Type is the type checked
         */
        template < typename __Type >
        constexpr auto isBasicPointer () noexcept -> bool {
            return __impl :: __IsPointer < __Type > :: value;
        }

        /**
         * @brief Meta-function used to check if a given type is a smart-pointer type = derived from SmartPointer type
         * @tparam __Type is the type checked
         */
        template < typename __Type >
        constexpr auto isSmartPointer () noexcept -> bool {
            return __impl :: __IsSmartPointer < __Type > :: value;
        }

        /**
         * @brief Meta-function used to check if a given type is a basic or smart pointer type
         * @tparam __Type is the type checked
         */
        template < typename __Type >
        constexpr auto isPointer () noexcept -> bool {
            return isBasicPointer < __Type > () || isSmartPointer < __Type > ();
        }

        /**
         * @brief Meta-function used to check if a given type is a lvalue reference (&) type
         * @tparam __Type is the type checked
         */
        template < typename __Type >
        constexpr auto isLValueReference () noexcept -> bool {
            return __impl :: __IsLValueReference < __Type > :: value;
        }

        /**
         * @brief Meta-function used to check if a given type is a rvalue reference (&&) type
         * @tparam __Type is the type checked
         */
        template < typename __Type >
        constexpr auto isRValueReference () noexcept -> bool {
            return __impl :: __IsRValueReference < __Type > :: value;
        }

        /**
         * @brief Meta-function used to check if a given type is a lvalue reference (&) type
         * @tparam __Type is the type checked
         */
        template < typename __Type >
        constexpr auto isReference () noexcept -> bool {
            return __impl :: __IsLValueReference < __Type > :: value;
        }

        /**
         * @brief Meta-function used to check if a given type is a rvalue reference (&&) type
         * @tparam __Type is the type checked
         */
        template < typename __Type >
        constexpr auto isMoveReference () noexcept -> bool {
            return __impl :: __IsRValueReference < __Type > :: value;
        }

        /**
         * @brief Meta-function used to check if a given type is a member of an object
         * @tparam __T is the type checked
         */
        template < typename __T >
        constexpr auto isMemberObjectPointer () noexcept -> bool {
            return __impl :: __IsMemberObjectPointer < __T > :: value;
        }

        /**
         * @brief Meta-function used to check if a given type is a member function of an object
         * @tparam __T is the type checked
         */
        template < typename __T >
        constexpr auto isMemberFunctionPointer () noexcept -> bool {
            return __impl :: __IsMemberFunctionPointer < __T > :: value;
        }

        /**
         * @brief Meta-function used to check if a given type is a member of a given object
         * @tparam __T is the type checked
         * @tparam __C is the object of which T should be a member of
         */
        template < typename __T, typename __C >
        constexpr auto isMemberObjectPointer () noexcept -> bool {
            return __impl :: __IsMemberObjectPointer < __T, __C > :: value;
        }

        /**
         * @brief Meta-function used to check if a given type is a member function of a given object
         * @tparam __T is the type checked
         * @tparam __C is the object of which T should be a member function of
         */
        template < typename __T, typename __C >
        constexpr auto isMemberFunctionPointer () noexcept -> bool {
            return __impl :: __IsMemberFunctionPointer < __T, __C > :: value;
        }

        /**
         * @brief Meta-function used to check if a given type is a Pair type
         * @tparam __T is the type checked
         */
        template < typename __T >
        constexpr auto isPair () noexcept -> bool {
            return __impl :: __IsPair < __T > :: value;
        }

        /**
         * @brief Meta-function used to check if a given type is a const type
         * @tparam __T is the type checked
         */
        template < typename __T >
        constexpr auto isConst () noexcept -> bool {
            return __impl :: __IsConst < __T > :: value;
        }

        /**
         * @brief Meta-function used to check if a given type is a volatile type
         * @tparam __T is the type checked
         */
        template < typename __T >
        constexpr auto isVolatile () noexcept -> bool {
            return __impl :: __IsVolatile < __T > :: value;
        }

        template < typename __T >
        constexpr auto indirectionPossible () noexcept -> bool {
            return __impl :: __IndirectionPossible < __T > :: value;
        }

        template < typename __T >
        constexpr auto prefixIncrementPossible () noexcept -> bool {
            return __impl :: __PrefixIncrementPossible < __T > :: value;
        }

        template < typename __T >
        constexpr auto isIterator () noexcept -> bool {
            return
                    indirectionPossible < __T > () &&
                    prefixIncrementPossible < __T > () &&
                    notEqualToPossible < __T, __T > ();
        }

        /**
         * @brief Meta-function used to invoke the most appropriate comparison function between two values
         * @tparam __LeftType is the type to the left side of the == comparison
         * @tparam __RightType is the type to the right side of the == comparison
         *
         * @example
         * <ul>
         *      <li>If == comparison is possible, invoke ==</li>
         *      <li>If == comparison is not possible, but LeftType is ObjectDerived and RightType is ObjectDerived, invoke Object :: equals</li>
         *      <li>If == comparison is not possible and LeftType is not ObjectDerived and RightType is not ObjectDerived, invoke comparison by address</li>
         * </ul>
         */
        template < typename __LeftType, typename __RightType, EnableIf < equalToPossible < __LeftType, __RightType > () > = 0 >
        constexpr auto equals (
                __LeftType  const & left,
                __RightType const & right
        ) noexcept -> bool {

            return left == right;
        }

        template < typename __LeftType, typename __RightType, EnableIf < ! equalToPossible < __LeftType, __RightType > () && isDerivedFrom < __LeftType, Object > () && isDerivedFrom < __RightType, Object > () > = 0 >
        constexpr auto equals (
                __LeftType  const & left,
                __RightType const & right,
                int                         = 0
        ) noexcept -> bool {

            return left.equals ( right );
        }

        template < typename __LeftType, typename __RightType, EnableIf < ! equalToPossible < __LeftType, __RightType > () && ! ( isDerivedFrom < __LeftType, Object > () && isDerivedFrom < __RightType, Object > () ) > = 0 >
        constexpr auto equals (
                __LeftType  const & left,
                __RightType const & right,
                float                       = 0.0f
        ) noexcept -> bool {

            return & left == & right;
        }

        template < typename __T, meta :: EnableIf < isPrintable < __T > () > = 0 >
        constexpr auto print (
                std :: ostream        & out,
                __T             const & object
        ) noexcept -> std :: ostream & {

            return ( out << object );
        }

        template < typename __T, meta :: EnableIf < ! isPrintable < __T > () > = 0 >
        constexpr auto print (
                std :: ostream            & out,
                __T                 const & object
        ) noexcept -> std :: ostream & {

            return ( out << "Unknown@0x" << std :: hex << ( & object ) );
        }

        /**
         * @brief Meta-object helper, containing utilities for a given type. Alternative to above functions
         * @tparam __T type given for which to access meta functions
         */
        template < typename __T >
        struct Type {

            using BaseType = __T;

            using RemoveConst           = meta :: RemoveConst < __T >;
            using RemoveVolatile        = meta :: RemoveVolatile < __T >;
            using RemoveReference       = meta :: RemoveReference < __T >;
            using RemoveConstVolatile   = meta :: RemoveConstVolatile < __T >;
            using RemovePointer         = meta :: RemovePointer < __T >;

            template < typename __U >
            constexpr static auto isSame () noexcept -> bool {
                return meta :: isSame < __T, __U > ();
            }

            constexpr static auto hasEqualTo () noexcept -> bool {
                return meta :: equalToPossible < __T, __T > ();
            }

            constexpr static auto hasNotEqualTo () noexcept -> bool {
                return meta :: notEqualToPossible < __T, __T > ();
            }

            constexpr static auto hasLessThan () noexcept -> bool {
                return meta :: lessThanPossible < __T, __T > ();
            }

            constexpr static auto hasGreaterThan () noexcept -> bool {
                return meta :: greaterThanPossible < __T, __T > ();
            }

            constexpr static auto hasLessThanOrEqual () noexcept -> bool {
                return meta :: lessThanOrEqualToPossible < __T, __T > ();
            }

            constexpr static auto hasGreaterThanOrEqual () noexcept -> bool {
                return meta :: greaterThanOrEqualToPossible < __T, __T > ();
            }

            constexpr static auto isPrintable () noexcept -> bool {
                return meta :: isPrintable < __T > ();
            }

            constexpr static auto isEnum () noexcept -> bool {
                return meta :: isEnum < __T > ();
            }

            constexpr static auto isClass () noexcept -> bool {
                return meta :: isEnum < __T > ();
            }

            constexpr static auto isUnion () noexcept -> bool {
                return meta :: isUnion < __T > ();
            }

            constexpr static auto isFunction () noexcept -> bool {
                return meta :: isFunction < __T > ();
            }

            constexpr static auto isStaticFunction () noexcept -> bool {
                return meta :: isStaticFunction < __T > ();
            }

            constexpr static auto isObjectFunction () noexcept -> bool {
                return meta :: isObjectFunction < __T > ();
            }

            constexpr static auto isFundamental () noexcept -> bool {
                return meta :: isFundamental < __T > ();
            }

            constexpr static auto isIntegral () noexcept -> bool {
                return meta :: isIntegral < __T > ();
            }

            constexpr static auto isArithmetic () noexcept -> bool {
                return meta :: isArithmetic < __T > ();
            }

            constexpr static auto isPrimitive () noexcept -> bool {
                return meta :: isFundamental < __T > ();
            }

            template < typename __DerivedType >
            constexpr static auto isBaseFor () noexcept -> bool {
                return meta :: isBaseFor < __T, __DerivedType > ();
            }

            template < typename __BaseType >
            constexpr static auto isDerivedFrom () noexcept -> bool {
                return meta :: isDerivedFrom < __T, __BaseType > ();
            }

            constexpr static auto isDefaultConstructible () noexcept -> bool {
                return meta :: isDefaultConstructible < __T > ();
            }

            constexpr static auto isCopyConstructible () noexcept -> bool {
                return meta :: isCopyConstructible < __T > ();
            }

            constexpr static auto isMoveConstructible () noexcept -> bool {
                return meta :: isMoveConstructible < __T > ();
            }

            constexpr static auto isCopyAssignable () noexcept -> bool {
                return meta :: isCopyAssignable < __T > ();
            }

            constexpr static auto isMoveAssignable () noexcept -> bool {
                return meta :: isMoveAssignable < __T > ();
            }

            constexpr static auto isCallable () noexcept -> bool {
                return meta :: isCallable < __T > ();
            }

            constexpr static auto isArray () noexcept -> bool {
                return meta :: isArray < __T > ();
            }

            template < Size __size >
            constexpr static auto isArray () noexcept -> bool {
                return meta :: isArray < __T[__size] > ();
            }

            constexpr static auto isPointer () noexcept -> bool {
                return meta :: isPointer < __T > ();
            }

            constexpr static auto isBasicPointer () noexcept -> bool {
                return meta :: isBasicPointer < __T > ();
            }

            constexpr static auto isSmartPointer () noexcept -> bool {
                return meta :: isSmartPointer < __T > ();
            }

            constexpr static auto isLValueReference () noexcept -> bool {
                return meta :: isLValueReference < __T > ();
            }

            constexpr static auto isRValueReference () noexcept -> bool {
                return meta :: isRValueReference < __T > ();
            }

            constexpr static auto isReference () noexcept -> bool {
                return meta :: isReference < __T > ();
            }

            constexpr static auto isMoveReference () noexcept -> bool {
                return meta :: isMoveReference < __T > ();
            }

            constexpr static auto isMemberObjectPointer () noexcept -> bool {
                return meta :: isMemberObjectPointer < __T > ();
            }

            constexpr static auto isMemberFunctionPointer () noexcept -> bool {
                return meta :: isMemberFunctionPointer < __T > ();
            }

            template < typename __C >
            constexpr static auto isMemberObjectPointer () noexcept -> bool {
                return meta :: isMemberObjectPointer < __T, __C > ();
            }

            template < typename __C >
            constexpr static auto isMemberFunctionPointer () noexcept -> bool {
                return meta :: isMemberFunctionPointer < __T, __C > ();
            }

            constexpr static auto isConst () noexcept -> bool {
                return meta :: isConst < __T > ();
            }

            constexpr static auto isVolatile () noexcept -> bool {
                return meta :: isVolatile < __T > ();
            }
        };
    }

}

#define __CDS_Meta_RegisterParseType(_type) /* NOLINT(bugprone-reserved-identifier) */  \
namespace cds {                                                                     \
    namespace meta {                                                                \
        namespace __impl {                                                          \
            template <>                                                             \
            struct __TypeParseTraits < _type > {                                    \
                constexpr static StringLiteral name = # _type;                      \
            };                                                                      \
        }                                                                           \
    }                                                                               \
                                                                                    \
}

#define __CDS_Meta_RegisterParseTemplateType(_type) /* NOLINT(bugprone-reserved-identifier) */  \
namespace cds {                                                                     \
    namespace meta {                                                                \
        namespace __impl {                                                          \
            template < typename ... __Types >                                       \
            struct __TypeParseTraits < _type < Types ... > > {                      \
                constexpr static StringLiteral name = # _type;                      \
            };                                                                      \
        }                                                                           \
    }                                                                               \
                                                                                    \
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
