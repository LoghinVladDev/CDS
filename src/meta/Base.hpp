/*
 * Created by loghin on 5/18/22.
 */

#ifndef __CDS_META_BASE_HPP__
#define __CDS_META_BASE_HPP__ /* NOLINT(bugprone-reserved-identifier) */

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
        template < typename __Type > auto valueOf () noexcept -> __Type; /* NOLINT(bugprone-reserved-identifier) */

        /**
         * @brief Meta-function implementation used for obtaining a pseudo-reference to a value of type T. Not to be used in actual compiled code
         * @tparam __Type is the type of the required reference
         * @return does not return anything, as implementation does not exist.
         */
        template < typename __Type > auto referenceOf () noexcept -> __Type &; /* NOLINT(bugprone-reserved-identifier) */

        /**
         * @brief Meta-function implementation used for obtaining a pseudo-pointer of type T. Not to be used in actual compiled code
         * @tparam __Type is the type of the required pointer
         * @return does not return anything, as implementation does not exist.
         */
        template < typename __Type > auto addressOf () noexcept -> __Type *; /* NOLINT(bugprone-reserved-identifier) */

        namespace __impl { /* NOLINT(bugprone-reserved-identifier) */

            /**
             * @brief Integral Constant implementation container structure
             * @tparam __IntegralType is the type of the Integral Constant
             * @tparam __value is the value of the Integral Constant
             */
            template < typename __IntegralType, __IntegralType __value >    /* NOLINT(bugprone-reserved-identifier) */
            struct __IntegralConstant {                                     /* NOLINT(bugprone-reserved-identifier) */
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
            template < bool __value >                                       /* NOLINT(bugprone-reserved-identifier) */
            using __BoolConstant = __IntegralConstant < bool, __value >;    /* NOLINT(bugprone-reserved-identifier) */

            /**
             * @brief True Bool Constant implementation container structure
             */
            using __TrueType  = __BoolConstant < true >; /* NOLINT(bugprone-reserved-identifier) */

            /**
             * @brief False Bool Constant implementation container structure
             */
            using __FalseType = __BoolConstant < false >; /* NOLINT(bugprone-reserved-identifier) */

            /**
             * @brief Meta-type implementation used to enable function declaration using sfiane based on a given condition
             * @tparam __ReplacedType is the type that is saved inside the structure if the condition is true
             */
            template < bool, typename = void >
            struct __EnableIf {};                   /* NOLINT(bugprone-reserved-identifier) */

            template < typename __ReplacedType >    /* NOLINT(bugprone-reserved-identifier) */
            struct __EnableIf < true, __ReplacedType > {
                /// on true, save type. If false, no type is saved
                using Type = __ReplacedType;
            };

            /**
             * @brief Meta-type implementation used to choose between two types based on a given condition
             * @tparam __TypeIfTrue is the type to save if condition is true
             * @tparam __TypeIfFalse is the type to save if condition is false
             */
            template < bool, typename __TypeIfTrue, typename >  /* NOLINT(bugprone-reserved-identifier) */
            struct __Conditional {                              /* NOLINT(bugprone-reserved-identifier) */
                /// by default, save the type intended for the true case
                using Type = __TypeIfTrue;
            };

            template < typename __TypeIfTrue, typename __TypeIfFalse > /* NOLINT(bugprone-reserved-identifier) */
            struct __Conditional < false, __TypeIfTrue, __TypeIfFalse > {
                /// if given condition is false, save the type intended for the false case
                using Type = __TypeIfFalse;
            };

            /**
             * @brief Meta-type implementation used to acquire the non-const type corresponding the current type
             * @tparam __T type to remove const modifier for
             */
            template < typename __T > struct __RemoveConst                                  { using Type = __T; }; /* NOLINT(bugprone-reserved-identifier) */
            template < typename __T > struct __RemoveConst < __T const >                    { using Type = __T; }; /* NOLINT(bugprone-reserved-identifier) */

            /**
             * @brief Meta-type implementation used to acquire the non-volatile type corresponding the current type
             * @tparam __T type to remove volatile modifier for
             */
            template < typename __T > struct __RemoveVolatile                               { using Type = __T; }; /* NOLINT(bugprone-reserved-identifier) */
            template < typename __T > struct __RemoveVolatile < __T volatile >              { using Type = __T; }; /* NOLINT(bugprone-reserved-identifier) */

            /**
             * @brief Meta-type implementation used to acquire the non-reference type corresponding the current type
             * @tparam __T type to remove reference for
             */
            template < typename __T > struct __RemoveReference                              { using Type = __T; }; /* NOLINT(bugprone-reserved-identifier) */
            template < typename __T > struct __RemoveReference < __T & >                    { using Type = __T; }; /* NOLINT(bugprone-reserved-identifier) */
            template < typename __T > struct __RemoveReference < __T && >                   { using Type = __T; }; /* NOLINT(bugprone-reserved-identifier) */

            /**
             * @brief Meta-type implementation used to acquire the non-const, non-volatile type corresponding the current type
             * @tparam __T type to remove const and volatile modifiers for
             */
            template < typename __T > struct __RemoveConstVolatile                          { using Type = __T; }; /* NOLINT(bugprone-reserved-identifier) */
            template < typename __T > struct __RemoveConstVolatile < __T const >            { using Type = __T; }; /* NOLINT(bugprone-reserved-identifier) */
            template < typename __T > struct __RemoveConstVolatile < __T volatile >         { using Type = __T; }; /* NOLINT(bugprone-reserved-identifier) */
            template < typename __T > struct __RemoveConstVolatile < __T const volatile >   { using Type = __T; }; /* NOLINT(bugprone-reserved-identifier) */

            namespace __removePtrImpl { /* NOLINT(bugprone-reserved-identifier) */
                /**
                 * @brief Meta-type helper used to acquire the non-pointer type corresponding the current type
                 * @tparam __T type to remove pointer for
                 */
                template < typename __T, typename >     struct __RemovePointer                { using Type = __T; }; /* NOLINT(bugprone-reserved-identifier) */
                template < typename __T, typename __U > struct __RemovePointer < __T, __U * > { using Type = __U; }; /* NOLINT(bugprone-reserved-identifier) */
            }

            /**
             * @brief Meta-type implementation used to acquire the non-pointer type corresponding the current type
             * @tparam __T type to remove pointer for
             */
            template < typename __T > struct __RemovePointer : __removePtrImpl :: __RemovePointer < __T, typename __RemoveConstVolatile < __T > :: Type > {}; /* NOLINT(bugprone-reserved-identifier) */

            /**
             * @brief Meta-type implementation used to acquire the non-array extent type corresponding the current type
             * @tparam __T type to remove the array extent ([] or [size]) for
             */
            template < typename __T >   /* NOLINT(bugprone-reserved-identifier) */
            struct __RemoveExtent {     /* NOLINT(bugprone-reserved-identifier) */
                using Type = __T;
            };

            template < typename __T, Size __size > /* NOLINT(bugprone-reserved-identifier) */
            struct __RemoveExtent < __T [__size] > {
                using Type = __T;
            };

            template < typename __T > /* NOLINT(bugprone-reserved-identifier) */
            struct __RemoveExtent < __T [] > {
                using Type = __T;
            };

            /**
             * @brief Meta-type implementation used to acquire the non-array extent type corresponding the current type, until no extent exists
             * @tparam __T type to remove all extents for - if T is T[][][], Type will be T
             */
            template < typename __T >   /* NOLINT(bugprone-reserved-identifier) */
            struct __RemoveAllExtents { /* NOLINT(bugprone-reserved-identifier) */
                using Type = __T;
            };

            template < typename __T, Size __size > /* NOLINT(bugprone-reserved-identifier) */
            struct __RemoveAllExtents < __T [__size] > {
                using Type = typename __RemoveAllExtents < __T > :: Type;
            };

            template < typename __T > /* NOLINT(bugprone-reserved-identifier) */
            struct __RemoveAllExtents < __T [] > {
                using Type = typename __RemoveAllExtents < __T > :: Type;
            };

            /**
             * @brief Meta-type used to check if a reference can be created for a given type
             * @tparam __T type to check if is referenceable
             */
            template < typename __T, typename = void > /* NOLINT(bugprone-reserved-identifier) */
            struct __IsReferenceable : __FalseType {}; /* NOLINT(bugprone-reserved-identifier) */

            template < typename __T > /* NOLINT(bugprone-reserved-identifier) */
            struct __IsReferenceable < __T, Void < __T & > > : __TrueType {};

            namespace __isVoidImpl { /* NOLINT(bugprone-reserved-identifier) */
                /**
                 * @brief Meta-type helper used to check if a given type is void
                 * @tparam __T type to check if is void
                 */
                template < typename >   struct __IsVoid           : __FalseType {}; /* NOLINT(bugprone-reserved-identifier) */
                template <>             struct __IsVoid < void >  : __TrueType {};
            }

            /**
             * @brief Meta-type implementation used to check if a given type is void
             * @tparam __T type to check if is void
             */
            template < typename __T >                                                                   /* NOLINT(bugprone-reserved-identifier) */
            struct __IsVoid : __isVoidImpl :: __IsVoid < __RemoveConstVolatile < __T > > :: Type {};    /* NOLINT(bugprone-reserved-identifier) */

            namespace __addPtrImpl { /* NOLINT(bugprone-reserved-identifier) */
                /**
                 * @brief Meta-type helper used to obtain a pointer to the given type
                 * @tparam __T type to add a pointer to
                 */
                template < typename __T, bool = __IsReferenceable < __T > :: value || __IsVoid < __T > :: value >   /* NOLINT(bugprone-reserved-identifier) */
                struct __AddPointer {                                                                               /* NOLINT(bugprone-reserved-identifier) */
                    using Type = __T;
                };

                template < typename __T > /* NOLINT(bugprone-reserved-identifier) */
                struct __AddPointer < __T, true > {
                    using Type = typename __RemoveReference < __T > :: Type *;
                };
            }

            /**
             * @brief Meta-type implementation used to obtain a pointer to the given type
             * @tparam __T type to add a pointer to
             */
            template < typename __T > struct __AddPointer : __addPtrImpl :: __AddPointer < __T, true > {}; /* NOLINT(bugprone-reserved-identifier) */

            /**
             * @brief Meta-type implementation used to obtain a const type of the given type
             * @tparam __T type to add const to
             */
            template < typename __T > struct __AddConst             { using Type = __T const; }; /* NOLINT(bugprone-reserved-identifier) */

            /**
             * @brief Meta-type implementation used to obtain a volatile type of the given type
             * @tparam __T type to add volatile to
             */
            template < typename __T > struct __AddVolatile          { using Type = __T volatile; }; /* NOLINT(bugprone-reserved-identifier) */

            /**
             * @brief Meta-type implementation used to obtain a const volatile type of the given type
             * @tparam __T type to add const and volatile to
             */
            template < typename __T > struct __AddConstVolatile     { using Type = typename __AddConst < typename __AddVolatile < __T > :: Type > :: Type; }; /* NOLINT(bugprone-reserved-identifier) */

            namespace __addReferenceImpl { /* NOLINT(bugprone-reserved-identifier) */
                /**
                 * @brief Meta-type helper used to obtain a lvalue reference (&) type of the given type
                 * @tparam __T type to add a lvalue reference to
                 */
                template < typename __T, bool = __IsReferenceable < __T > :: value >    /* NOLINT(bugprone-reserved-identifier) */
                struct __AddLValueReference                 { using Type = __T; };      /* NOLINT(bugprone-reserved-identifier) */

                template < typename __T > /* NOLINT(bugprone-reserved-identifier) */
                struct __AddLValueReference < __T, true >   { using Type = __T &; };

                /**
                 * @brief Meta-type helper used to obtain a rvalue reference (&&) type of the given type
                 * @tparam __T type to add a rvalue reference to
                 */
                template < typename __T, bool = __IsReferenceable < __T > :: value >    /* NOLINT(bugprone-reserved-identifier) */
                struct __AddRValueReference                 { using Type = __T; };      /* NOLINT(bugprone-reserved-identifier) */

                template < typename __T > /* NOLINT(bugprone-reserved-identifier) */
                struct __AddRValueReference < __T, true >   { using Type = __T &&; };
            }

            /**
             * @brief Meta-type implementation used to obtain a lvalue reference (&) type of the given type
             * @tparam __T type to add a lvalue reference to
             */
            template < typename __T > struct __AddLValueReference : __addReferenceImpl :: __AddLValueReference < __T > {}; /* NOLINT(bugprone-reserved-identifier) */

            /**
             * @brief Meta-type implementation used to obtain a rvalue reference (&&) type of the given type
             * @tparam __T type to add a rvalue reference to
             */
            template < typename __T > struct __AddRValueReference : __addReferenceImpl :: __AddRValueReference < __T > {}; /* NOLINT(bugprone-reserved-identifier) */
        }

        /**
         * @brief Meta-type used to enable function declaration using sfiane based on a given condition
         * @tparam __ReplacedType is the type that is saved inside the structure if the condition is true
         */
        template < bool __enableCondition, typename __ReplacedType = int > /* NOLINT(bugprone-reserved-identifier) */
        using EnableIf = typename __impl :: __EnableIf < __enableCondition, __ReplacedType > :: Type;

        /**
         * @brief Meta-type used to choose between two types based on a given condition
         * @tparam __TypeIfTrue is the type to save if condition is true
         * @tparam __TypeIfFalse is the type to save if condition is false
         */
        template < bool __condition, typename __TypeIfTrue, typename __TypeIfFalse > /* NOLINT(bugprone-reserved-identifier) */
        using Conditional = typename __impl :: __Conditional < __condition, __TypeIfTrue, __TypeIfFalse > :: Type;

        template < bool __condition > /* NOLINT(bugprone-reserved-identifier) */
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
        template < typename __T > using RemoveConst           = typename __impl :: __RemoveConst < __T > :: Type; /* NOLINT(bugprone-reserved-identifier) */

        /**
         * @brief Meta-type used to acquire the non-volatile type corresponding the current type
         * @tparam __T type to remove volatile modifier for
         */
        template < typename __T > using RemoveVolatile        = typename __impl :: __RemoveVolatile < __T > :: Type; /* NOLINT(bugprone-reserved-identifier) */

        /**
         * @brief Meta-type used to acquire the non-reference type corresponding the current type
         * @tparam __T type to remove reference for
         */
        template < typename __T > using RemoveReference       = typename __impl :: __RemoveReference < __T > :: Type; /* NOLINT(bugprone-reserved-identifier) */

        /**
         * @brief Meta-type used to acquire the non-const, non-volatile type corresponding the current type
         * @tparam __T type to remove const and volatile modifiers for
         */
        template < typename __T > using RemoveConstVolatile   = typename __impl :: __RemoveConstVolatile < __T > :: Type; /* NOLINT(bugprone-reserved-identifier) */

        /**
         * @brief Meta-type used to acquire the non-pointer type corresponding the current type
         * @tparam __T type to remove pointer for
         */
        template < typename __T > using RemovePointer         = typename __impl :: __RemovePointer < __T > :: Type; /* NOLINT(bugprone-reserved-identifier) */

        /**
         * @brief Meta-type used to acquire the non-array extent type corresponding the current type
         * @tparam __T type to remove the array extent ([] or [size]) for
         */
        template < typename __T > using RemoveExtent          = typename __impl :: __RemoveExtent < __T > :: Type; /* NOLINT(bugprone-reserved-identifier) */

        /**
         * @brief Meta-type used to acquire the non-array extent type corresponding the current type, until no extent exists
         * @tparam __T type to remove all extents for - if T is T[][][], Type will be T
         */
        template < typename __T > using RemoveAllExtents      = typename __impl :: __RemoveAllExtents < __T > :: Type; /* NOLINT(bugprone-reserved-identifier) */


        /**
         * @brief Meta-type used to obtain a const type of the given type
         * @tparam __T type to add const to
         */
        template < typename __T > using AddConst              = typename __impl :: __AddConst < __T > :: Type; /* NOLINT(bugprone-reserved-identifier) */

        /**
         * @brief Meta-type used to obtain a volatile type of the given type
         * @tparam __T type to add volatile to
         */
        template < typename __T > using AddVolatile           = typename __impl :: __AddVolatile < __T > :: Type; /* NOLINT(bugprone-reserved-identifier) */

        /**
         * @brief Meta-type used to obtain a lvalue reference (&) type of the given type
         * @tparam __T type to add a lvalue reference to
         */
        template < typename __T > using AddLValueReference    = typename __impl :: __AddLValueReference < __T > :: Type; /* NOLINT(bugprone-reserved-identifier) */

        /**
         * @brief Meta-type used to obtain a rvalue reference (&&) type of the given type
         * @tparam __T type to add a rvalue reference to
         */
        template < typename __T > using AddRValueReference    = typename __impl :: __AddRValueReference < __T > :: Type; /* NOLINT(bugprone-reserved-identifier) */

        /**
         * @brief Meta-type used to obtain a const volatile type of the given type
         * @tparam __T type to add const and volatile to
         */
        template < typename __T > using AddConstVolatile      = typename __impl :: __AddConstVolatile < __T > :: Type; /* NOLINT(bugprone-reserved-identifier) */

        /**
         * @brief Meta-type implementation used to obtain a pointer to the given type
         * @tparam __T type to add a pointer to
         */
        template < typename __T > using AddPointer            = typename __impl :: __AddPointer < __T > :: Type; /* NOLINT(bugprone-reserved-identifier) */

        /**
         * @brief Meta-function used to check if a given type is void
         * @tparam __T type to check if is void
         */
        template < typename __T > /* NOLINT(bugprone-reserved-identifier) */
        constexpr auto isVoid () noexcept -> bool {
            return __impl :: __IsVoid < __T > :: value;
        }

        /**
         * @brief Meta-function used to check if a given type is referenceable
         * @tparam __T type to check if is referenceable
         */
        template < typename __T > /* NOLINT(bugprone-reserved-identifier) */
        constexpr auto isReferenceable () noexcept -> bool {
            return __impl :: __IsReferenceable < __T > :: value;
        }
    }
}

#endif /* __CDS_META_BASE_HPP__ */
