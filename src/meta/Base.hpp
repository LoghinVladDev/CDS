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
            template < bool __value >                                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            using __BoolConstant = __IntegralConstant < bool, __value >;    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            /**
             * @brief True Bool Constant implementation container structure
             */
            using __TrueType  = __BoolConstant < true >; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            /**
             * @brief False Bool Constant implementation container structure
             */
            using __FalseType = __BoolConstant < false >; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

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
        } /* namespace __impl */

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
        using BoolConstant = __impl :: __BoolConstant < __condition >;

        /**
         * @brief True Bool Constant container structure
         */
        using FalseType = __impl :: __FalseType;

        /**
         * @brief False Bool Constant container structure
         */
        using TrueType  = __impl :: __TrueType;

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

        /**
         * @brief Meta-function used to check if a given type is referenceable
         * @tparam __T type to check if is referenceable
         */
        template < typename __T > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isReferenceable () noexcept -> bool {
            return __impl :: __IsReferenceable < __T > :: value;
        }

        /**
         * @brief Meta-function used to check if a given type is an enum type
         * @tparam __Type is the type checked
         */
        template < typename __Type > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isEnum () noexcept -> bool {
            return __impl :: __IsEnum < __Type > :: value;
        }

        /**
         * @brief Meta-function used to check if a given type is an union type
         * @tparam __Type is the type checked
         */
        template < typename __Type > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isUnion () noexcept -> bool {
            return __impl :: __IsUnion < __Type > :: value;
        }

        /**
         * @brief Meta-function used to check if a given type is a class or struct type
         * @tparam __Type is the type checked
         */
        template < typename __Type > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isClass () noexcept -> bool {
            return __impl :: __IsClass < __Type > :: value;
        }

        /**
         * @brief Meta-function used to check if a given type is a function type
         * @tparam __Type is the type checked
         */
        template < typename __Type > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isFunction () noexcept -> bool {
            return __impl :: __IsFunction < __Type > :: value;
        }

        /**
         * @brief Meta-function used to check if a given type is a fundamental type ( bool, int types, float types )
         * @tparam __Type is the type checked
         */
        template < typename __Type > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isFundamental () noexcept -> bool {
            return __impl :: __IsFundamental < __Type > :: value;
        }

        /**
         * @brief Meta-function used to check if a given type is an integral type ( bool, int types )
         * @tparam __Type is the type checked
         */
        template < typename __Type > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isIntegral () noexcept -> bool {
            return __impl :: __IsIntegral < __Type > :: value;
        }

        /**
         * @brief Meta-function used to check if a given type is a floating point type ( float types )
         * @tparam __Type is the type checked
         */
        template < typename __Type > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isFloatingPoint () noexcept -> bool {
            return __impl :: __IsFloatingPoint < __Type > :: value;
        }

        /**
         * @brief Meta-function used to check if a given type is an arithmetic type ( int, float types )
         * @tparam __Type is the type checked
         */
        template < typename __Type > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isArithmetic () noexcept -> bool {
            return __impl :: __IsArithmetic < __Type > :: value;
        }

        template < typename __Type > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isSigned () noexcept -> bool {
            return __impl :: __IsSigned < __Type > :: value;
        }

        template < typename __Type > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isUnsigned () noexcept -> bool {
            return
                    isArithmetic < __Type > () &&
                    ! isSigned < __Type > ();
        }

        /**
         * @brief Meta-function used to check if a given type is convertible to another given type
         * @tparam __From is the type being converted
         * @tparam __To is the type to which the conversion is done
         */
        template < typename __From, typename __To > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isConvertible () noexcept -> bool {
            return __impl :: __IsConvertible < __From, __To > :: value;
        }

        /**
         * @brief Meta-function used to check if two given types are the same
         * @tparam __LeftType is the first type
         * @tparam __RightType is the second type
         */
        template < typename __LeftType, typename __RightType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isSame () noexcept -> bool {
            return __impl :: __IsSame < __LeftType, __RightType > :: value;
        }

        /**
         * @brief Meta-function used to check if a given type can be constructed without arguments ( has default constructor )
         * @tparam __Type is the type checked
         */
        template < typename __Type > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isDefaultConstructible () noexcept -> bool {
            return __impl :: __IsDefaultConstructible < __Type > :: value;
        }

        /**
         * @brief Meta-function used to check if a given type can be copied trivially ( public fields, no copy operator specialization )
         * @tparam __Type is the type checked
         */
        template < typename __Type > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isTriviallyCopyable () noexcept -> bool {
            return __impl :: __IsTriviallyCopyable < __Type > :: value;
        }

        /**
         * @brief Meta-function used to check if a given type can be constructed by copy ( has copy constructor )
         * @tparam __Type is the type checked
         */
        template < typename __Type > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isCopyConstructible () noexcept -> bool {
            return __impl :: __IsCopyConstructible < __Type > :: value;
        }

        /**
         * @brief Meta-function used to check if a given type can be constructed by move ( has move constructor )
         * @tparam __Type is the type checked
         */
        template < typename __Type > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isMoveConstructible () noexcept -> bool {
            return __impl :: __IsMoveConstructible < __Type > :: value;
        }

        /**
         * @brief Meta-function used to check if a given type can be assigned a value by copy ( has copy assignment operator )
         * @tparam __Type is the type checked
         */
        template < typename __Type > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isCopyAssignable () noexcept -> bool {
            return __impl :: __IsCopyAssignable < __Type > :: value;
        }

        /**
         * @brief Meta-function used to check if a given type can be assigned a value by move ( has move assignment operator )
         * @tparam __Type is the type checked
         */
        template < typename __Type > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isMoveAssignable () noexcept -> bool {
            return __impl :: __IsMoveAssignable < __Type > :: value;
        }

        /**
         * @brief Meta-function used to check if a given type is a callable type ( function / object with operator () )
         * @tparam __Type is the type checked
         */
        template < typename __Type > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isCallable () noexcept -> bool {
            return __impl :: __IsFunction < __Type > :: value || __impl :: __IsObjectFunction < __Type > :: value;
        }

        /**
         * @brief Meta-function used to check if a given type is a static-function type ( non-object callable )
         * @tparam __Type is the type checked
         */
        template < typename __Type > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isStaticFunction () noexcept -> bool {
            return __impl :: __IsStaticFunction < __Type > :: value;
        }

        /**
         * @brief Meta-function used to check if a given type is a callable object ( non-static function )
         * @tparam __Type is the type checked
         */
        template < typename __Type > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isObjectFunction () noexcept -> bool {
            return __impl :: __IsObjectFunction < __Type > :: value;
        }

        /**
         * @brief Meta-function used to check if a given type is an array type
         * @tparam __Type is the type checked
         */
        template < typename __Type > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isArray () noexcept -> bool {
            return __impl :: __IsArray < __Type > :: value;
        }

        /**
         * @brief Meta-function used to check if a given type is a bounded array type
         * @tparam __Type is the type checked
         */
        template < typename __Type > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isBoundedArray () noexcept -> bool {
            return __impl :: __IsBoundedArray < __Type > :: value;
        }

        /**
         * @brief Meta-function used to check if a given type is an unbounded array type
         * @tparam __Type is the type checked
         */
        template < typename __Type > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isUnboundedArray () noexcept -> bool {
            return __impl :: __IsUnboundedArray < __Type > :: value;
        }

        /**
         * @brief Meta-function used to check if a given type is a basic-pointer type = non-smart pointer type
         * @tparam __Type is the type checked
         */
        template < typename __Type > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isBasicPointer () noexcept -> bool {
            return __impl :: __IsPointer < __Type > :: value;
        }

        /**
         * @brief Meta-function used to check if a given type is a lvalue reference (&) type
         * @tparam __Type is the type checked
         */
        template < typename __Type > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isLValueReference () noexcept -> bool {
            return __impl :: __IsLValueReference < __Type > :: value;
        }

        /**
         * @brief Meta-function used to check if a given type is a rvalue reference (&&) type
         * @tparam __Type is the type checked
         */
        template < typename __Type > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isRValueReference () noexcept -> bool {
            return __impl :: __IsRValueReference < __Type > :: value;
        }

        /**
         * @brief Meta-function used to check if a given type is a lvalue reference (&) type
         * @tparam __Type is the type checked
         */
        template < typename __Type > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isReference () noexcept -> bool {
            return __impl :: __IsLValueReference < __Type > :: value;
        }

        /**
         * @brief Meta-function used to check if a given type is a rvalue reference (&&) type
         * @tparam __Type is the type checked
         */
        template < typename __Type > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isMoveReference () noexcept -> bool {
            return __impl :: __IsRValueReference < __Type > :: value;
        }

        /**
         * @brief Meta-function used to check if a given type is a volatile type
         * @tparam __T is the type checked
         */
        template < typename __T > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isVolatile () noexcept -> bool {
            return __impl :: __IsVolatile < __T > :: value;
        }

        /**
         * @brief Meta-function used to check if a given type is a const type
         * @tparam __T is the type checked
         */
        template < typename __T > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isConst () noexcept -> bool {
            return __impl :: __IsConst < __T > :: value;
        }

    } /* namespace meta */
} /* namespace cds */

#endif /* __CDS_META_BASE_HPP__ */
