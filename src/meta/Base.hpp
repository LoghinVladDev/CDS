/*
 * Created by loghin on 5/18/22.
 */

#ifndef __CDS_META_BASE_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_META_BASE_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/Types>

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */
    namespace meta {

        /**
         * @brief Meta-type implementation used for template partial-specialization generation enabling by type declaration
         *
         * @example Usage example:
         * <pre>template \< typename T, typename = Void \<\> \> struct HasValueType : FalseType {};</pre>
         * <pre>template \< typename T \> struct HasValueType \< T, Void \< typename T :: ValueType \> \> : TrueType {};</pre>
         * If given T has a public type named ValueType, HasValueType will be TrueType, otherwise, FalseType
         */
        template < typename ... > using Void = void;

        /**
         * @brief Meta-function implementation used for obtaining a pseudo-value of type T. Not to be used in actual compiled code
         * @tparam __Type is the type of the required value
         * @return does not return anything, as implementation does not exist.
         */
        template < typename __Type > auto valueOf () noexcept -> __Type; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

        /**
         * @brief Meta-function implementation used for obtaining a pseudo-reference to a value of type T. Not to be used in actual compiled code
         * @tparam __Type is the type of the required reference
         * @return does not return anything, as implementation does not exist.
         */
        template < typename __Type > auto referenceOf () noexcept -> __Type &; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

        /**
         * @brief Meta-function implementation used for obtaining a pseudo-pointer of type T. Not to be used in actual compiled code
         * @tparam __Type is the type of the required pointer
         * @return does not return anything, as implementation does not exist.
         */
        template < typename __Type > auto addressOf () noexcept -> __Type *; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

        namespace __impl { /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            /**
             * @brief Integral Constant implementation container structure
             * @tparam __IntegralType is the type of the Integral Constant
             * @tparam __value is the value of the Integral Constant
             */
            template < typename __IntegralType, __IntegralType __value >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __IntegralConstant {                                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                /// value of the integral constant
                constexpr static __IntegralType const value = __value;

                /// type of the value
                using ValueType                             = __IntegralType;

                /// type of the container structure
                using Type                                  = __IntegralConstant < __IntegralType, __value >;
            };

            /**
             * @brief Bool Constant implementation container structure
             */
            template < bool __value >                                         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __BoolConstant : __IntegralConstant < bool, __value > {};  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            /**
             * @brief True Bool Constant implementation container structure
             */
            struct __TrueType : __BoolConstant < true > {}; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            /**
             * @brief False Bool Constant implementation container structure
             */
            struct __FalseType : __BoolConstant < false > {}; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            /**
             * @brief Meta-type implementation used to enable function declaration using sfiane based on a given condition
             * @tparam __ReplacedType is the type that is saved inside the structure if the condition is true
             */
            template < bool, typename = void >
            struct __EnableIf {};                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template < typename __ReplacedType >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __EnableIf < true, __ReplacedType > {
                /// on true, save type. If false, no type is saved
                using Type = __ReplacedType;
            };

            /**
             * @brief Meta-type implementation used to choose between two types based on a given condition
             * @tparam __TypeIfTrue is the type to save if condition is true
             * @tparam __TypeIfFalse is the type to save if condition is false
             */
            template < bool, typename __TypeIfTrue, typename >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __Conditional {                              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                /// by default, save the type intended for the true case
                using Type = __TypeIfTrue;
            };

            template < typename __TypeIfTrue, typename __TypeIfFalse > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __Conditional < false, __TypeIfTrue, __TypeIfFalse > {
                /// if given condition is false, save the type intended for the false case
                using Type = __TypeIfFalse;
            };

            /**
             * @brief Meta-type implementation used to acquire the non-const type corresponding the current type
             * @tparam __T type to remove const modifier for
             */
            template < typename __T > struct __RemoveConst                                  { using Type = __T; }; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            template < typename __T > struct __RemoveConst < __T const >                    { using Type = __T; }; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            /**
             * @brief Meta-type implementation used to acquire the non-volatile type corresponding the current type
             * @tparam __T type to remove volatile modifier for
             */
            template < typename __T > struct __RemoveVolatile                               { using Type = __T; }; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            template < typename __T > struct __RemoveVolatile < __T volatile >              { using Type = __T; }; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            /**
             * @brief Meta-type implementation used to acquire the non-reference type corresponding the current type
             * @tparam __T type to remove reference for
             */
            template < typename __T > struct __RemoveReference                              { using Type = __T; }; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            template < typename __T > struct __RemoveReference < __T & >                    { using Type = __T; }; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            template < typename __T > struct __RemoveReference < __T && >                   { using Type = __T; }; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            /**
             * @brief Meta-type implementation used to acquire the non-const, non-volatile type corresponding the current type
             * @tparam __T type to remove const and volatile modifiers for
             */
            template < typename __T > struct __RemoveConstVolatile                          { using Type = __T; }; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            template < typename __T > struct __RemoveConstVolatile < __T const >            { using Type = __T; }; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            template < typename __T > struct __RemoveConstVolatile < __T volatile >         { using Type = __T; }; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            template < typename __T > struct __RemoveConstVolatile < __T const volatile >   { using Type = __T; }; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            namespace __removePtrImpl { /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                /**
                 * @brief Meta-type helper used to acquire the non-pointer type corresponding the current type
                 * @tparam __T type to remove pointer for
                 */
                template < typename __T, typename >     struct __RemovePointer                { using Type = __T; }; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                template < typename __T, typename __U > struct __RemovePointer < __T, __U * > { using Type = __U; }; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            } /* namespace __removePtrImpl */

            /**
             * @brief Meta-type implementation used to acquire the non-pointer type corresponding the current type
             * @tparam __T type to remove pointer for
             */
            template < typename __T > struct __RemovePointer : __removePtrImpl :: __RemovePointer < __T, typename __RemoveConstVolatile < __T > :: Type > {}; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            /**
             * @brief Meta-type implementation used to acquire the non-array extent type corresponding the current type
             * @tparam __T type to remove the array extent ([] or [size]) for
             */
            template < typename __T >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __RemoveExtent {     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                using Type = __T;
            };

            template < typename __T, Size __size >      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __RemoveExtent < __T [__size] > {    /* NOLINT(*-avoid-c-arrays) */
                using Type = __T;
            };

            template < typename __T >                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __RemoveExtent < __T [] > {          /* NOLINT(*-avoid-c-arrays) */
                using Type = __T;
            };

            /**
             * @brief Meta-type implementation used to acquire the non-array extent type corresponding the current type, until no extent exists
             * @tparam __T type to remove all extents for - if T is T[][][], Type will be T
             */
            template < typename __T >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __RemoveAllExtents { /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                using Type = __T;
            };

            template < typename __T, Size __size >          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __RemoveAllExtents < __T [__size] > {    /* NOLINT(*-avoid-c-arrays) */
                using Type = typename __RemoveAllExtents < __T > :: Type;
            };

            template < typename __T >                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __RemoveAllExtents < __T [] > {          /* NOLINT(*-avoid-c-arrays) */
                using Type = typename __RemoveAllExtents < __T > :: Type;
            };

            /**
             * @brief Meta-type used to check if a reference can be created for a given type
             * @tparam __T type to check if is referenceable
             */
            template < typename __T, typename = void > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __IsReferenceable : __FalseType {}; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template < typename __T > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __IsReferenceable < __T, Void < __T & > > : __TrueType {};

            namespace __isVoidImpl { /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                /**
                 * @brief Meta-type helper used to check if a given type is void
                 * @tparam __T type to check if is void
                 */
                template < typename >   struct __IsVoid           : __FalseType {}; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                template <>             struct __IsVoid < void >  : __TrueType {};
            } /* namespace __isVoidImpl */

            /**
             * @brief Meta-type implementation used to check if a given type is void
             * @tparam __T type to check if is void
             */
            template < typename __T >                                                                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __IsVoid : __isVoidImpl :: __IsVoid < __RemoveConstVolatile < __T > > :: Type {};    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            /**
             * @brief Meta-type implementation used to check if a given type is an enum type
             * @tparam __T is the type checked
             */
            template < typename __T >                                                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __IsEnum : __BoolConstant < std :: is_enum < __T > :: value > {};    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            /**
             * @brief Meta-type implementation used to check if a given type is an union type
             * @tparam __T is the type checked
             */
            template < typename __T >                                                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __IsUnion : __BoolConstant < std :: is_union < __T > :: value > {};  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            /**
             * @brief Meta-type implementation used to check if a given type is a class or struct type
             * @tparam __T is the type checked
             */
            template < typename __T >                                                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __IsClass : __BoolConstant < std :: is_class < __T > :: value > {};  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            /**
             * @brief Meta-type implementation used to check if a given type is a function type
             * @tparam __T is the type checked
             */
            template < typename __T >                                                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __IsFunction : __BoolConstant < std :: is_function < __T > :: value > {};    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            /**
             * @brief Meta-type implementation used to check if a given type is a fundamental type ( bool, int types, float types )
             * @tparam __T is the type checked
             */
            template < typename __T >                                                               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __IsFundamental : __BoolConstant < std :: is_fundamental < __T > :: value > {};  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            /**
             * @brief Meta-type implementation used to check if a given type is an integral type ( bool, int types )
             * @tparam __T is the type checked
             */
            template < typename __T >                                                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __IsIntegral : __BoolConstant < std :: is_integral < __T > :: value > {};    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            /**
             * @brief Meta-type implementation used to check if a given type is a floating point type ( float types )
             * @tparam __T is the type checked
             */
            template < typename __T >                                                                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __IsFloatingPoint : __BoolConstant < std :: is_floating_point < __T > :: value > {}; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            /**
             * @brief Meta-type implementation used to check if a given type is an arithmetic type ( int, float types )
             * @tparam __T is the type checked
             */
            template < typename __T >                                                               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __IsArithmetic : __BoolConstant < std :: is_arithmetic < __T > :: value > {};    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            namespace __isSignedImpl {                                              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                template < typename __T, bool = __IsArithmetic < __T > :: value >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                struct __IsSigned : __FalseType {};                                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                template < typename __T > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                struct __IsSigned < __T, true > : __impl :: __BoolConstant < __T ( -1 ) < __T ( 0 ) > {};
            } /* namespace __isSignedImpl */

            template < typename __T >                                               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __IsSigned : __isSignedImpl :: __IsSigned < __T > :: Type {};    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            /**
             * @brief Meta-type implementation used to check if a given type can be constructed without arguments ( has default constructor )
             * @tparam __T is the type checked
             */
            template < typename __T >                                                                                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __IsDefaultConstructible : __BoolConstant < std :: is_default_constructible < __T > :: value > {};   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            /**
             * @brief Meta-type implementation used to check if a given type can be constructed by copy ( has copy constructor )
             * @tparam __T is the type checked
             */
            template < typename __T >                                                                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __IsCopyConstructible : __BoolConstant < std :: is_copy_constructible < __T > :: value > {}; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            /**
             * @brief Meta-type implementation used to check if a given type can be copied trivially ( public fields, no copy operator specialization )
             * @tparam __T is the type checked
             */
            template < typename __T >                                                                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __IsTriviallyCopyable : __BoolConstant < std :: is_trivially_copyable < __T > :: value > {}; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            /**
             * @brief Meta-type implementation used to check if a given type can be constructed by move ( has move constructor )
             * @tparam __T is the type checked
             */
            template < typename __T >                                                                           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __IsMoveConstructible : __BoolConstant < std :: is_move_constructible < __T > :: value > {}; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            /**
             * @brief Meta-type implementation used to check if a given type can be assigned a value by copy ( has copy assignment operator )
             * @tparam __T is the type checked
             */
            template < typename __T >                                                                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __IsCopyAssignable : __BoolConstant < std :: is_copy_assignable < __T > :: value > {};   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            /**
             * @brief Meta-type implementation used to check if a given type can be assigned a value by move ( has move assignment operator )
             * @tparam __T is the type checked
             */
            template < typename __T >                                                                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __IsMoveAssignable : __BoolConstant < std :: is_move_assignable < __T > :: value > {};   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            /**
             * @brief Meta-type implementation used to check if a given type is a static-function type ( non-object callable )
             * @tparam __T is the type checked
             */
            template < typename __T, typename = void > struct __IsStaticFunction : __FalseType {}; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            /**
             * @brief Meta-type implementation used to check if a given type is a callable object ( non-static function )
             * @tparam __T is the type checked
             */
            template < typename __T, typename = void > struct __IsObjectFunction : __FalseType {}; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template < typename __T > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __IsStaticFunction < __T > : __BoolConstant < __IsFunction < __T > :: value && ! __IsObjectFunction < __T > :: value > {};

            template < typename __T > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __IsObjectFunction < __T, Void < decltype ( & __T :: operator () ) > > : __TrueType {};

            /**
             * @brief Meta-type implementation used to check if a given type is an array type
             * @tparam __T is the type checked
             */
            template < typename >                   struct __IsArray                            : __FalseType {};   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            template < typename __T, Size __size >  struct __IsArray < __T [__size] >           : __TrueType {};    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-avoid-c-arrays) */
            template < typename __T >               struct __IsArray < __T [] >                 : __TrueType {};    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-avoid-c-arrays) */

            template < typename >                   struct __IsBoundedArray                     : __FalseType {};   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            template < typename __T, Size __size >  struct __IsBoundedArray < __T [__size] >    : __TrueType {};    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-avoid-c-arrays) */

            template < typename >                   struct __IsUnboundedArray                   : __FalseType {};   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            template < typename __T >               struct __IsUnboundedArray < __T [] >        : __TrueType {};    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, *-avoid-c-arrays) */

            namespace __isPointerImpl { /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                /**
                 * @brief Meta-type helper implementation used to check if a given type is a pointer type
                 * @tparam __T is the type checked
                 */
                template < typename >       struct __IsPointer : __FalseType {};            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                template < typename __T >   struct __IsPointer < __T * > : __TrueType {};   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            } /* namespace __isPointerImpl */

            /**
             * @brief Meta-type implementation used to check if a given type is a pointer type
             * @tparam __T is the type checked
             */
            template < typename __T >       struct __IsPointer : __isPointerImpl :: __IsPointer < typename __RemoveConstVolatile < __T > :: Type > {}; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            /**
             * @brief Meta-type implementation used to check if a given type is a lvalue reference (&) type
             * @tparam __T is the type checked
             */
            template < typename >           struct __IsLValueReference              : __FalseType {};   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            template < typename __T >       struct __IsLValueReference < __T & >    : __TrueType {};    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            /**
             * @brief Meta-type implementation used to check if a given type is a rvalue reference (&&) type
             * @tparam __T is the type checked
             */
            template < typename >           struct __IsRValueReference              : __FalseType {};   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            template < typename __T >       struct __IsRValueReference < __T && >   : __TrueType {};    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            /**
             * @brief Meta-type implementation used to check if a given type is a const type
             * @tparam __T is the type checked
             */
            template < typename >           struct __IsConst                        : __FalseType {};   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            template < typename __T >       struct __IsConst < __T const >          : __TrueType {};    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            /**
             * @brief Meta-type implementation used to check if a given type is a volatile type
             * @tparam __T is the type checked
             */
            template < typename >           struct __IsVolatile                     : __FalseType {};   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            template < typename __T >       struct __IsVolatile < __T volatile >    : __TrueType {};    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            namespace __isConvertibleImpl { /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                /**
                 * @brief Meta-type helper used to check if a given type is convertible to another given type
                 * @tparam __From is the type being converted
                 * @tparam __To is the type to which the conversion is done
                 */
                template < typename __From, typename __To, bool = __IsVoid < __From > :: value || __IsFunction < __To > :: value || __IsArray < __To > :: value >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                struct __IsConvertible {                                                                                                                            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    using Type = typename __IsVoid < __To > :: Type;
                };

                template < typename __From, typename __To > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                struct __IsConvertible < __From, __To, false > {
                private:
                    template < typename __To1 >                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    static auto __metaTest ( __To1 ) noexcept -> void;  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                    template < typename __From1, typename __To1, typename = decltype ( __metaTest < __To1 > ( valueOf < __From1 > () ) ) >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    static auto __test (int) -> __TrueType;                                                                                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                    template < typename, typename >
                    static auto __test (...) -> __FalseType; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                public:
                    using Type = decltype ( __test < __From, __To > (0) );
                };
            } /* namespace __isConvertibleImpl */

            /**
             * @brief Meta-type implementation used to check if a given type is convertible to another given type
             * @tparam __From is the type being converted
             * @tparam __To is the type to which the conversion is done
             */
            template < typename __From, typename __To >                                                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __IsConvertible : __isConvertibleImpl :: __IsConvertible < __From, __To > :: Type {};    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            /**
             * @brief Meta-type implementation used to check if two given types are the same
             * @tparam __LeftType is the first type
             * @tparam __RightType is the second type
             */
            template < typename __LeftType, typename __RightType >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __IsSame : __FalseType {};                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template < typename __Type > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __IsSame < __Type, __Type > : __TrueType {};

            namespace __addPtrImpl { /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                /**
                 * @brief Meta-type helper used to obtain a pointer to the given type
                 * @tparam __T type to add a pointer to
                 */
                template < typename __T, bool = __IsReferenceable < __T > :: value || __IsVoid < __T > :: value >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                struct __AddPointer {                                                                               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    using Type = __T;
                };

                template < typename __T > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                struct __AddPointer < __T, true > {
                    using Type = typename __RemoveReference < __T > :: Type *;
                };
            } /* namespace __addPtrImpl */

            /**
             * @brief Meta-type implementation used to obtain a pointer to the given type
             * @tparam __T type to add a pointer to
             */
            template < typename __T > struct __AddPointer : __addPtrImpl :: __AddPointer < __T, true > {}; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            /**
             * @brief Meta-type implementation used to obtain a const type of the given type
             * @tparam __T type to add const to
             */
            template < typename __T > struct __AddConst             { using Type = __T const; }; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            /**
             * @brief Meta-type implementation used to obtain a volatile type of the given type
             * @tparam __T type to add volatile to
             */
            template < typename __T > struct __AddVolatile          { using Type = __T volatile; }; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            /**
             * @brief Meta-type implementation used to obtain a const volatile type of the given type
             * @tparam __T type to add const and volatile to
             */
            template < typename __T > struct __AddConstVolatile     { using Type = typename __AddConst < typename __AddVolatile < __T > :: Type > :: Type; }; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            namespace __addReferenceImpl { /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                /**
                 * @brief Meta-type helper used to obtain a lvalue reference (&) type of the given type
                 * @tparam __T type to add a lvalue reference to
                 */
                template < typename __T, bool = __IsReferenceable < __T > :: value >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                struct __AddLValueReference                 { using Type = __T; };      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                template < typename __T > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                struct __AddLValueReference < __T, true >   { using Type = __T &; };

                /**
                 * @brief Meta-type helper used to obtain a rvalue reference (&&) type of the given type
                 * @tparam __T type to add a rvalue reference to
                 */
                template < typename __T, bool = __IsReferenceable < __T > :: value >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                struct __AddRValueReference                 { using Type = __T; };      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                template < typename __T > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                struct __AddRValueReference < __T, true >   { using Type = __T &&; };
            } /* namespace __addReferenceImpl */

            /**
             * @brief Meta-type implementation used to obtain a lvalue reference (&) type of the given type
             * @tparam __T type to add a lvalue reference to
             */
            template < typename __T > struct __AddLValueReference : __addReferenceImpl :: __AddLValueReference < __T > {}; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            /**
             * @brief Meta-type implementation used to obtain a rvalue reference (&&) type of the given type
             * @tparam __T type to add a rvalue reference to
             */
            template < typename __T > struct __AddRValueReference : __addReferenceImpl :: __AddRValueReference < __T > {}; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            namespace __andImpl {                                                               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                template <typename __FirstIntegralType, typename ... __RemainingIntegralTypes>  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                struct __AndImpl : __BoolConstant <                                             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __FirstIntegralType::value && __AndImpl <__RemainingIntegralTypes...>::value
                > {};

                template <typename __IntegralType>                                              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                struct __AndImpl <__IntegralType> : __BoolConstant <__IntegralType::value> {};  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            } /* namespace __andImpl */

            namespace __orImpl {                                                                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                template <typename __FirstIntegralType, typename ... __RemainingIntegralTypes>  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                struct __OrImpl : __BoolConstant <                                              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __FirstIntegralType::value || __OrImpl <__RemainingIntegralTypes...>::value
                > {};

                template <typename __IntegralType>                                              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                struct __OrImpl <__IntegralType> : __BoolConstant <__IntegralType::value> {};   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            } /* namespace __orImpl */

            template <typename ... __IntegralTypes>                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __And : __andImpl::__AndImpl <__IntegralTypes...> {};  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template <typename ... __IntegralTypes>                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __Or : __orImpl::__OrImpl <__IntegralTypes...> {}; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template <typename __IntegralType>                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __Not : __BoolConstant <__IntegralType::value> {}; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            namespace __bindImpl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                template <template <typename...> class __BoundFormula, typename ... __BoundTParams> /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                struct __BindLeftImpl {                                                             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    template <typename ... __TParams>                                               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    using Type = __BoundFormula <__BoundTParams..., __TParams...>;                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                };

                template <template <typename...> class __BoundFormula, typename ... __BoundTParams> /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                struct __BindRightImpl {                                                            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    template <typename ... __TParams>                                               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    using Type = __BoundFormula <__TParams..., __BoundTParams...>;                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                };

                template <int __index = 0> struct __Ph {};                              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                template <typename __T> struct __IsPh : __FalseType {};                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                template <int __index> struct __IsPh <__Ph <__index>> : __TrueType {};  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                template <typename __T>                                                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                struct __GetPhIndex {                                                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    static constexpr int const index = 0u;
                };

                template <int __index>                                                  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                struct __GetPhIndex <__Ph <__index>> {
                    static constexpr int const index = __index;
                };

                template <typename...>
                struct __Pack {};       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                template <typename...>
                struct __PackPop {};    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                template <typename __FirstType, typename ... __RemainingTypes>    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                struct __PackPop <__Pack <__FirstType, __RemainingTypes...>> {    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    using Type    = __Pack <__RemainingTypes...>;
                    using Result  = __FirstType;
                };

                template <> struct __PackPop <__Pack <>> {                      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    using Type    = __Pack <>;
                    using Result  = void;
                };

                template <int __index, typename ... __Pack> struct __IndexedPackPeek {};  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                template <int __index, typename __FirstType, typename ... __RemainingTypes>     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                struct __IndexedPackPeek <__index, __Pack <__FirstType, __RemainingTypes...>> { /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    using Type    = __Pack <__FirstType, __RemainingTypes...>;
                    using Result  = typename __Conditional <
                            __index == 1,
                            __FirstType,
                            typename __IndexedPackPeek <
                                    __index - 1,
                                    __Pack <__RemainingTypes...>
                            >::Result
                    >::Type;
                };

                template <int __index> struct __IndexedPackPeek <__index, __Pack <>> {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    using Type    = __Pack <>;
                    using Result  = void;
                };

                template <typename __PhType, typename __T> struct __BoundPackPop {};                            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                template <typename __PhType, typename __FirstType, typename ... __RemainingTypes>               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                struct __BoundPackPop <__PhType, __Pack <__FirstType, __RemainingTypes...>> : __Conditional <   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __GetPhIndex <__PhType>::index == 0,
                        __PackPop <__Pack <__FirstType, __RemainingTypes...>>,
                        __IndexedPackPeek <__GetPhIndex <__PhType>::index, __Pack <__FirstType, __RemainingTypes...>>
                >::Type {};

                template <template <typename...> class __BoundFormula, typename __BoundPack, typename __ParamPack>  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                struct __BindApplyInPlace {                                                                         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                private:
                    using __NextBoundPack                     = typename __PackPop <__BoundPack>::Type;             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    using __CurrentBinding                    = typename __PackPop <__BoundPack>::Result;           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    constexpr static bool const __placeholder = __IsPh <__CurrentBinding>::value;                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    using __NextBoundParam                    = typename __Conditional <                            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                            __placeholder,
                            typename __BoundPackPop <__CurrentBinding, __ParamPack>::Result,
                            __CurrentBinding
                    >::Type;

                public:
                    template <typename ... __UnboundTParams>  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    using Type = typename __Conditional <
                            __placeholder,
                            __BindApplyInPlace <
                                    __BoundFormula,
                                    __NextBoundPack,
                                    typename __BoundPackPop <__CurrentBinding, __ParamPack>::Type
                            >,
                            __BindApplyInPlace <
                                    __BoundFormula,
                                    __NextBoundPack,
                                    __ParamPack
                            >
                    >::Type::template Type <__UnboundTParams..., __NextBoundParam>;
                };

                template <template <typename...> class __BoundFormula>              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                struct __BindApplyInPlace <__BoundFormula, __Pack <>, __Pack <>> {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    template <typename ... __UnboundTParams>                          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    using Type = __BoundFormula <__UnboundTParams...>;
                };

                template <template <typename...> class __BoundFormula, typename __UnusedParamPack>  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                struct __BindApplyInPlace <__BoundFormula, __Pack <>, __UnusedParamPack> {          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    template <typename ... __UnboundTParams>                                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    using Type = __BoundFormula <__UnboundTParams...>;
                };

                template <template <typename...> class __BoundFormula, typename __UnusedBoundPack>  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                struct __BindApplyInPlace <__BoundFormula, __UnusedBoundPack, __Pack <>> {          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    template <typename...> using Type = void;
                };

                template <template <typename...> class __BoundFormula, typename ... __BoundTParams> /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                struct __BindImpl {                                                                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    template <typename ... __UnboundTParams>                                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    using Type = typename __BindApplyInPlace <
                            __BoundFormula,
                            __Pack <__BoundTParams...>,
                            __Pack <__UnboundTParams...>
                    >::template Type <>;
                };
            } /* namespace __bindImpl */

            namespace __allAnyNoneImpl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                template <template <typename...> class __PredicateFormula, typename ... __Types>  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                struct __AllImpl {};                                                              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                template <template <typename...> class __PredicateFormula, typename ... __Types>  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                struct __AnyImpl {};                                                              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                template <template <typename...> class __PredicateFormula, typename ... __Types>  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                struct __NoneImpl : __Not <__AllImpl <__PredicateFormula, __Types...>> {};        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                template <template <typename...> class __PredicateFormula, typename __FirstType, typename ... __RemainingTypes> /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                struct __AllImpl <__PredicateFormula, __FirstType, __RemainingTypes...> : __And <                               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __PredicateFormula <__FirstType>,
                        __AllImpl <__PredicateFormula, __RemainingTypes...>
                > {};

                template <template <typename...> class __PredicateFormula, typename __FirstType, typename ... __RemainingTypes> /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                struct __AnyImpl <__PredicateFormula, __FirstType, __RemainingTypes...> : __Or <                                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __PredicateFormula <__FirstType>,
                        __AnyImpl <__PredicateFormula, __RemainingTypes...>
                > {};

                template <template <typename...> class __PredicateFormula, typename __FirstType>          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                struct __AllImpl <__PredicateFormula, __FirstType> : __PredicateFormula <__FirstType> {}; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                template <template <typename...> class __PredicateFormula, typename __FirstType>          /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                struct __AnyImpl <__PredicateFormula, __FirstType> : __PredicateFormula <__FirstType> {}; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            } /* namespace __allAnyNoneImpl */
        } /* namespace __impl */

        template <typename ... __IntegralTypes>             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        struct And : __impl::__And <__IntegralTypes...> {}; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

        template <typename ... __IntegralTypes>           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        struct Or : __impl::__Or <__IntegralTypes...> {}; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

        template <typename __IntegralType>              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        struct Not : __impl::__Not <__IntegralType> {}; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

        template <template <typename...> class __BoundFormula, typename ... __BoundTParams> /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        struct Bind : __impl::__bindImpl::__BindImpl <__BoundFormula, __BoundTParams...> {};

        template <template <typename...> class __BoundFormula, typename ... __BoundTParams> /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        struct BindLeft : __impl::__bindImpl::__BindLeftImpl <__BoundFormula, __BoundTParams...> {};

        template <template <typename...> class __BoundFormula, typename ... __BoundTParams> /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        struct BindRight : __impl::__bindImpl::__BindLeftImpl <__BoundFormula, __BoundTParams...> {};

        template <template <typename...> class __PredicateFormula, typename ... __TestedTypes>  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        struct All : __impl::__allAnyNoneImpl::__AllImpl <__PredicateFormula, __TestedTypes...> {};

        template <template <typename...> class __PredicateFormula, typename ... __TestedTypes>  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        struct Any : __impl::__allAnyNoneImpl::__AnyImpl <__PredicateFormula, __TestedTypes...> {};

        template <template <typename...> class __PredicateFormula, typename ... __TestedTypes>  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        struct None : __impl::__allAnyNoneImpl::__NoneImpl <__PredicateFormula, __TestedTypes...> {};

        template <int __index = 0>  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        using Ph = __impl::__bindImpl::__Ph <__index>;

        /**
         * @brief Meta-type used to enable function declaration using sfiane based on a given condition
         * @tparam __ReplacedType is the type that is saved inside the structure if the condition is true
         */
        template < bool __enableCondition, typename __ReplacedType = int > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        using EnableIf = typename __impl :: __EnableIf < __enableCondition, __ReplacedType > :: Type;

        /**
         * @brief Meta-type used to choose between two types based on a given condition
         * @tparam __TypeIfTrue is the type to save if condition is true
         * @tparam __TypeIfFalse is the type to save if condition is false
         */
        template < bool __condition, typename __TypeIfTrue, typename __TypeIfFalse > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        using Conditional = typename __impl :: __Conditional < __condition, __TypeIfTrue, __TypeIfFalse > :: Type;

        template < bool __condition > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        struct BoolConstant : __impl :: __BoolConstant < __condition > {};

        /**
         * @brief True Bool Constant container structure
         */
        struct FalseType : __impl :: __FalseType {};

        /**
         * @brief False Bool Constant container structure
         */
        struct TrueType : __impl :: __TrueType {};

        /**
         * @brief Meta-type used to acquire the non-const type corresponding the current type
         * @tparam __T type to remove const modifier for
         */
        template < typename __T > using RemoveConst           = typename __impl :: __RemoveConst < __T > :: Type; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

        /**
         * @brief Meta-type used to acquire the non-volatile type corresponding the current type
         * @tparam __T type to remove volatile modifier for
         */
        template < typename __T > using RemoveVolatile        = typename __impl :: __RemoveVolatile < __T > :: Type; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

        /**
         * @brief Meta-type used to acquire the non-reference type corresponding the current type
         * @tparam __T type to remove reference for
         */
        template < typename __T > using RemoveReference       = typename __impl :: __RemoveReference < __T > :: Type; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

        /**
         * @brief Meta-type used to acquire the non-const, non-volatile type corresponding the current type
         * @tparam __T type to remove const and volatile modifiers for
         */
        template < typename __T > using RemoveConstVolatile   = typename __impl :: __RemoveConstVolatile < __T > :: Type; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

        /**
         * @brief Meta-type used to acquire the non-pointer type corresponding the current type
         * @tparam __T type to remove pointer for
         */
        template < typename __T > using RemovePointer         = typename __impl :: __RemovePointer < __T > :: Type; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

        /**
         * @brief Meta-type used to acquire the non-array extent type corresponding the current type
         * @tparam __T type to remove the array extent ([] or [size]) for
         */
        template < typename __T > using RemoveExtent          = typename __impl :: __RemoveExtent < __T > :: Type; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

        /**
         * @brief Meta-type used to acquire the non-array extent type corresponding the current type, until no extent exists
         * @tparam __T type to remove all extents for - if T is T[][][], Type will be T
         */
        template < typename __T > using RemoveAllExtents      = typename __impl :: __RemoveAllExtents < __T > :: Type; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */


        /**
         * @brief Meta-type used to obtain a const type of the given type
         * @tparam __T type to add const to
         */
        template < typename __T > using AddConst              = typename __impl :: __AddConst < __T > :: Type; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

        /**
         * @brief Meta-type used to obtain a volatile type of the given type
         * @tparam __T type to add volatile to
         */
        template < typename __T > using AddVolatile           = typename __impl :: __AddVolatile < __T > :: Type; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

        /**
         * @brief Meta-type used to obtain a lvalue reference (&) type of the given type
         * @tparam __T type to add a lvalue reference to
         */
        template < typename __T > using AddLValueReference    = typename __impl :: __AddLValueReference < __T > :: Type; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

        /**
         * @brief Meta-type used to obtain a rvalue reference (&&) type of the given type
         * @tparam __T type to add a rvalue reference to
         */
        template < typename __T > using AddRValueReference    = typename __impl :: __AddRValueReference < __T > :: Type; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

        /**
         * @brief Meta-type used to obtain a const volatile type of the given type
         * @tparam __T type to add const and volatile to
         */
        template < typename __T > using AddConstVolatile      = typename __impl :: __AddConstVolatile < __T > :: Type; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

        /**
         * @brief Meta-type implementation used to obtain a pointer to the given type
         * @tparam __T type to add a pointer to
         */
        template < typename __T > using AddPointer            = typename __impl :: __AddPointer < __T > :: Type; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

        /**
         * @brief Meta-function used to check if a given type is void
         * @tparam __T type to check if is void
         */
        template < typename __T > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isVoid () noexcept -> bool {
            return __impl :: __IsVoid < __T > :: value;
        }

        template <typename __T> /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        struct IsVoid : __impl::__IsVoid <__T> {};

        /**
         * @brief Meta-function used to check if a given type is referenceable
         * @tparam __T type to check if is referenceable
         */
        template < typename __T > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isReferenceable () noexcept -> bool {
            return __impl :: __IsReferenceable < __T > :: value;
        }

        template <typename __T> /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        struct IsReferenceable : __impl::__IsReferenceable <__T> {};

        /**
         * @brief Meta-function used to check if a given type is an enum type
         * @tparam __Type is the type checked
         */
        template < typename __Type > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isEnum () noexcept -> bool {
            return __impl :: __IsEnum < __Type > :: value;
        }

        template <typename __T> /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        struct IsEnum : __impl::__IsEnum <__T> {};

        /**
         * @brief Meta-function used to check if a given type is an union type
         * @tparam __Type is the type checked
         */
        template < typename __Type > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isUnion () noexcept -> bool {
            return __impl :: __IsUnion < __Type > :: value;
        }

        template <typename __T> /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        struct IsUnion : __impl::__IsUnion <__T> {};

        /**
         * @brief Meta-function used to check if a given type is a class or struct type
         * @tparam __Type is the type checked
         */
        template < typename __Type > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isClass () noexcept -> bool {
            return __impl :: __IsClass < __Type > :: value;
        }

        template <typename __T> /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        struct IsClass : __impl::__IsClass <__T> {};

        /**
         * @brief Meta-function used to check if a given type is a function type
         * @tparam __Type is the type checked
         */
        template < typename __Type > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isFunction () noexcept -> bool {
            return __impl :: __IsFunction < __Type > :: value;
        }

        template <typename __T> /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        struct IsFunction : __impl::__IsFunction <__T> {};

        /**
         * @brief Meta-function used to check if a given type is a fundamental type ( bool, int types, float types )
         * @tparam __Type is the type checked
         */
        template < typename __Type > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isFundamental () noexcept -> bool {
            return __impl :: __IsFundamental < __Type > :: value;
        }

        template <typename __T> /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        struct IsFundamental : __impl::__IsFundamental <__T> {};

        /**
         * @brief Meta-function used to check if a given type is an integral type ( bool, int types )
         * @tparam __Type is the type checked
         */
        template < typename __Type > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isIntegral () noexcept -> bool {
            return __impl :: __IsIntegral < __Type > :: value;
        }

        template <typename __T> /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        struct IsIntegral : __impl::__IsIntegral <__T> {};

        /**
         * @brief Meta-function used to check if a given type is a floating point type ( float types )
         * @tparam __Type is the type checked
         */
        template < typename __Type > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isFloatingPoint () noexcept -> bool {
            return __impl :: __IsFloatingPoint < __Type > :: value;
        }

        template <typename __T> /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        struct IsFloatingPoint : __impl::__IsFloatingPoint <__T> {};

        /**
         * @brief Meta-function used to check if a given type is an arithmetic type ( int, float types )
         * @tparam __Type is the type checked
         */
        template < typename __Type > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isArithmetic () noexcept -> bool {
            return __impl :: __IsArithmetic < __Type > :: value;
        }

        template <typename __T> /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        struct IsArithmetic : __impl::__IsArithmetic <__T> {};

        template < typename __Type > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isSigned () noexcept -> bool {
            return __impl :: __IsSigned < __Type > :: value;
        }

        template <typename __T> /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        struct IsSigned : __impl::__IsSigned <__T> {};

        template < typename __Type > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isUnsigned () noexcept -> bool {
            return
                    isArithmetic < __Type > () &&
                    ! isSigned < __Type > ();
        }

        template <typename __T> /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        struct IsUnsigned : And <IsArithmetic <__T>, Not <IsSigned <__T>>> {};

        /**
         * @brief Meta-function used to check if a given type is convertible to another given type
         * @tparam __From is the type being converted
         * @tparam __To is the type to which the conversion is done
         */
        template < typename __From, typename __To > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isConvertible () noexcept -> bool {
            return __impl :: __IsConvertible < __From, __To > :: value;
        }

        template <typename __From, typename __To> /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        struct IsConvertible : __impl::__IsConvertible <__From, __To> {};

        /**
         * @brief Meta-function used to check if two given types are the same
         * @tparam __LeftType is the first type
         * @tparam __RightType is the second type
         */
        template < typename __LeftType, typename __RightType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isSame () noexcept -> bool {
            return __impl :: __IsSame < __LeftType, __RightType > :: value;
        }

        template <typename __LeftType, typename __RightType> /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        struct IsSame : __impl::__IsSame <__LeftType, __RightType> {};

        /**
         * @brief Meta-function used to check if a given type can be constructed without arguments ( has default constructor )
         * @tparam __Type is the type checked
         */
        template < typename __Type > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isDefaultConstructible () noexcept -> bool {
            return __impl :: __IsDefaultConstructible < __Type > :: value;
        }

        template <typename __Type> /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        struct IsDefaultConstructible : __impl::__IsDefaultConstructible <__Type> {};

        /**
         * @brief Meta-function used to check if a given type can be copied trivially ( public fields, no copy operator specialization )
         * @tparam __Type is the type checked
         */
        template < typename __Type > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isTriviallyCopyable () noexcept -> bool {
            return __impl :: __IsTriviallyCopyable < __Type > :: value;
        }

        template <typename __Type> /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        struct IsTriviallyCopyable : __impl::__IsTriviallyCopyable <__Type> {};

        /**
         * @brief Meta-function used to check if a given type can be constructed by copy ( has copy constructor )
         * @tparam __Type is the type checked
         */
        template < typename __Type > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isCopyConstructible () noexcept -> bool {
            return __impl :: __IsCopyConstructible < __Type > :: value;
        }

        template <typename __Type> /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        struct IsCopyConstructible : __impl::__IsCopyConstructible <__Type> {};

        /**
         * @brief Meta-function used to check if a given type can be constructed by move ( has move constructor )
         * @tparam __Type is the type checked
         */
        template < typename __Type > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isMoveConstructible () noexcept -> bool {
            return __impl :: __IsMoveConstructible < __Type > :: value;
        }

        template <typename __Type> /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        struct IsMoveConstructible : __impl::__IsMoveConstructible <__Type> {};

        /**
         * @brief Meta-function used to check if a given type can be assigned a value by copy ( has copy assignment operator )
         * @tparam __Type is the type checked
         */
        template < typename __Type > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isCopyAssignable () noexcept -> bool {
            return __impl :: __IsCopyAssignable < __Type > :: value;
        }

        template <typename __Type> /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        struct IsCopyAssignable : __impl::__IsCopyAssignable <__Type> {};

        /**
         * @brief Meta-function used to check if a given type can be assigned a value by move ( has move assignment operator )
         * @tparam __Type is the type checked
         */
        template < typename __Type > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isMoveAssignable () noexcept -> bool {
            return __impl :: __IsMoveAssignable < __Type > :: value;
        }

        template <typename __Type> /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        struct IsMoveAssignable : __impl::__IsMoveAssignable <__Type> {};

        /**
         * @brief Meta-function used to check if a given type is a callable type ( function / object with operator () )
         * @tparam __Type is the type checked
         */
        template < typename __Type > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isCallable () noexcept -> bool {
            return __impl :: __IsFunction < __Type > :: value || __impl :: __IsObjectFunction < __Type > :: value;
        }

        template <typename __Type> /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        struct IsCallable : Or <__impl::__IsFunction <__Type>, __impl::__IsObjectFunction <__Type>> {};

        /**
         * @brief Meta-function used to check if a given type is a static-function type ( non-object callable )
         * @tparam __Type is the type checked
         */
        template < typename __Type > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isStaticFunction () noexcept -> bool {
            return __impl :: __IsStaticFunction < __Type > :: value;
        }

        template <typename __Type> /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        struct IsStaticFunction : __impl::__IsStaticFunction <__Type> {};

        /**
         * @brief Meta-function used to check if a given type is a callable object ( non-static function )
         * @tparam __Type is the type checked
         */
        template < typename __Type > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isObjectFunction () noexcept -> bool {
            return __impl :: __IsObjectFunction < __Type > :: value;
        }

        template <typename __Type> /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        struct IsObjectFunction : __impl::__IsObjectFunction <__Type> {};

        /**
         * @brief Meta-function used to check if a given type is an array type
         * @tparam __Type is the type checked
         */
        template < typename __Type > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isArray () noexcept -> bool {
            return __impl :: __IsArray < __Type > :: value;
        }

        template <typename __Type> /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        struct IsArray : __impl::__IsArray <__Type> {};

        /**
         * @brief Meta-function used to check if a given type is a bounded array type
         * @tparam __Type is the type checked
         */
        template < typename __Type > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isBoundedArray () noexcept -> bool {
            return __impl :: __IsBoundedArray < __Type > :: value;
        }

        template <typename __Type> /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        struct IsBoundedArray : __impl::__IsBoundedArray <__Type> {};

        /**
         * @brief Meta-function used to check if a given type is an unbounded array type
         * @tparam __Type is the type checked
         */
        template < typename __Type > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isUnboundedArray () noexcept -> bool {
            return __impl :: __IsUnboundedArray < __Type > :: value;
        }

        template <typename __Type> /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        struct IsUnboundedArray : __impl::__IsUnboundedArray <__Type> {};

        /**
         * @brief Meta-function used to check if a given type is a basic-pointer type = non-smart pointer type
         * @tparam __Type is the type checked
         */
        template < typename __Type > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isBasicPointer () noexcept -> bool {
            return __impl :: __IsPointer < __Type > :: value;
        }

        template <typename __Type> /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        struct IsBasicPointer : __impl::__IsPointer <__Type> {};

        /**
         * @brief Meta-function used to check if a given type is a lvalue reference (&) type
         * @tparam __Type is the type checked
         */
        template < typename __Type > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isLValueReference () noexcept -> bool {
            return __impl :: __IsLValueReference < __Type > :: value;
        }

        template <typename __Type> /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        struct IsLValueReference : __impl::__IsLValueReference <__Type> {};

        /**
         * @brief Meta-function used to check if a given type is a rvalue reference (&&) type
         * @tparam __Type is the type checked
         */
        template < typename __Type > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isRValueReference () noexcept -> bool {
            return __impl :: __IsRValueReference < __Type > :: value;
        }

        template <typename __Type> /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        struct IsRValueReference : __impl::__IsRValueReference <__Type> {};

        /**
         * @brief Meta-function used to check if a given type is a lvalue reference (&) type
         * @tparam __Type is the type checked
         */
        template < typename __Type > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isReference () noexcept -> bool {
            return __impl :: __IsLValueReference < __Type > :: value;
        }

        template <typename __Type> /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        struct IsReference : IsLValueReference <__Type> {};

        /**
         * @brief Meta-function used to check if a given type is a rvalue reference (&&) type
         * @tparam __Type is the type checked
         */
        template < typename __Type > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isMoveReference () noexcept -> bool {
            return __impl :: __IsRValueReference < __Type > :: value;
        }

        template <typename __Type> /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        struct IsMoveReference : IsRValueReference <__Type> {};

        /**
         * @brief Meta-function used to check if a given type is a volatile type
         * @tparam __T is the type checked
         */
        template < typename __T > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isVolatile () noexcept -> bool {
            return __impl :: __IsVolatile < __T > :: value;
        }

        template <typename __Type> /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        struct IsVolatile : __impl::__IsVolatile <__Type> {};

        /**
         * @brief Meta-function used to check if a given type is a const type
         * @tparam __T is the type checked
         */
        template < typename __T > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isConst () noexcept -> bool {
            return __impl :: __IsConst < __T > :: value;
        }

        template <typename __Type> /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        struct IsConst : __impl::__IsConst <__Type> {};

    } /* namespace meta */
} /* namespace cds */

#endif /* __CDS_META_BASE_HPP__ */
