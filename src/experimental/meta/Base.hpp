//
// Created by loghin on 5/18/22.
//

#ifndef __CDS_EX_META_BASE_HPP__
#define __CDS_EX_META_BASE_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental { // NOLINT(modernize-concat-nested-namespaces)
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
             * @tparam Type is the type of the required value
             * @return does not return anything, as implementation does not exist.
             */
            template < typename Type > auto valueOf () noexcept -> Type;

            /**
             * @brief Meta-function implementation used for obtaining a pseudo-reference to a value of type T. Not to be used in actual compiled code
             * @tparam Type is the type of the required reference
             * @return does not return anything, as implementation does not exist.
             */
            template < typename Type > auto referenceOf () noexcept -> Type &;

            /**
             * @brief Meta-function implementation used for obtaining a pseudo-pointer of type T. Not to be used in actual compiled code
             * @tparam Type is the type of the required pointer
             * @return does not return anything, as implementation does not exist.
             */
            template < typename Type > auto addressOf () noexcept -> Type *;

            namespace impl {

                /**
                 * @brief Integral Constant implementation container structure
                 * @tparam IntegralType is the type of the Integral Constant
                 * @tparam _value is the value of the Integral Constant
                 */
                template < typename IntegralType, IntegralType _value >
                struct IntegralConstant {
                    /// value of the integral constant
                    constexpr static IntegralType value = _value;

                    /// type of the value
                    using ValueType                     = IntegralType;

                    /// type of the container structure
                    using Type                          = IntegralConstant < IntegralType, _value >;
                };

                /**
                 * @brief Bool Constant implementation container structure
                 */
                template < bool value >
                using BoolConstant = IntegralConstant < bool, value >;

                /**
                 * @brief True Bool Constant implementation container structure
                 */
                using TrueType  = BoolConstant < true >;

                /**
                 * @brief False Bool Constant implementation container structure
                 */
                using FalseType = BoolConstant < false >;

                /**
                 * @brief Meta-type implementation used to enable function declaration using sfiane based on a given condition
                 * @tparam ReplacedType is the type that is saved inside the structure if the condition is true
                 */
                template < bool, typename ReplacedType = void >
                struct EnableIf {};

                template < typename ReplacedType >
                struct EnableIf < true, ReplacedType > {
                    /// on true, save type. If false, no type is saved
                    using Type = ReplacedType;
                };

                /**
                 * @brief Meta-type implementation used to choose between two types based on a given condition
                 * @tparam TypeIfTrue is the type to save if condition is true
                 * @tparam TypeIfFalse is the type to save if condition is false
                 */
                template < bool, typename TypeIfTrue, typename TypeIfFalse >
                struct Conditional {
                    /// by default, save the type intended for the true case
                    using Type = TypeIfTrue;
                };

                template < typename TypeIfTrue, typename TypeIfFalse >
                struct Conditional < false, TypeIfTrue, TypeIfFalse > {
                    /// if given condition is false, save the type intended for the false case
                    using Type = TypeIfFalse;
                };

                /**
                 * @brief Meta-type implementation used to acquire the non-const type corresponding the current type
                 * @tparam T type to remove const modifier for
                 */
                template < typename T > struct RemoveConst                              { using Type = T; };
                template < typename T > struct RemoveConst < T const >                  { using Type = T; };

                /**
                 * @brief Meta-type implementation used to acquire the non-volatile type corresponding the current type
                 * @tparam T type to remove volatile modifier for
                 */
                template < typename T > struct RemoveVolatile                           { using Type = T; };
                template < typename T > struct RemoveVolatile < T volatile >            { using Type = T; };

                /**
                 * @brief Meta-type implementation used to acquire the non-reference type corresponding the current type
                 * @tparam T type to remove reference for
                 */
                template < typename T > struct RemoveReference                          { using Type = T; };
                template < typename T > struct RemoveReference < T & >                  { using Type = T; };
                template < typename T > struct RemoveReference < T && >                 { using Type = T; };

                /**
                 * @brief Meta-type implementation used to acquire the non-const, non-volatile type corresponding the current type
                 * @tparam T type to remove const and volatile modifiers for
                 */
                template < typename T > struct RemoveConstVolatile                      { using Type = T; };
                template < typename T > struct RemoveConstVolatile < T const >          { using Type = T; };
                template < typename T > struct RemoveConstVolatile < T volatile >       { using Type = T; };
                template < typename T > struct RemoveConstVolatile < T const volatile > { using Type = T; };

                namespace removePtrImpl {
                    /**
                     * @brief Meta-type helper used to acquire the non-pointer type corresponding the current type
                     * @tparam T type to remove pointer for
                     */
                    template < typename T, typename > struct RemovePointer              { using Type = T; };
                    template < typename T, typename U > struct RemovePointer < T, U * > { using Type = U; };
                }

                /**
                 * @brief Meta-type implementation used to acquire the non-pointer type corresponding the current type
                 * @tparam T type to remove pointer for
                 */
                template < typename T > struct RemovePointer : removePtrImpl :: RemovePointer < T, typename RemoveConstVolatile < T > :: Type > {};

                /**
                 * @brief Meta-type implementation used to acquire the non-array extent type corresponding the current type
                 * @tparam T type to remove the array extent ([] or [size]) for
                 */
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

                /**
                 * @brief Meta-type implementation used to acquire the non-array extent type corresponding the current type, until no extent exists
                 * @tparam T type to remove all extents for - if T is T[][][], Type will be T
                 */
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

                /**
                 * @brief Meta-type used to check if a reference can be created for a given type
                 * @tparam T type to check if is referenceable
                 */
                template < typename T, typename = void >
                struct IsReferenceable : FalseType {};

                template < typename T >
                struct IsReferenceable < T, Void < T & > > : TrueType {};

                namespace isVoidImpl {
                    /**
                     * @brief Meta-type helper used to check if a given type is void
                     * @tparam T type to check if is void
                     */
                    template < typename >   struct IsVoid           : FalseType {};
                    template <>             struct IsVoid < void >  : TrueType {};
                }

                /**
                 * @brief Meta-type implementation used to check if a given type is void
                 * @tparam T type to check if is void
                 */
                template < typename T >
                struct IsVoid : isVoidImpl :: IsVoid < RemoveConstVolatile < T > > :: Type {};

                namespace addPtrImpl {
                    /**
                     * @brief Meta-type helper used to obtain a pointer to the given type
                     * @tparam T type to add a pointer to
                     */
                    template < typename T, bool = IsReferenceable < T > :: value || IsVoid < T > :: value >
                    struct AddPointer {
                        using Type = T;
                    };

                    template < typename T >
                    struct AddPointer < T, true > {
                        using Type = typename RemoveReference < T > :: Type *;
                    };
                }

                /**
                 * @brief Meta-type implementation used to obtain a pointer to the given type
                 * @tparam T type to add a pointer to
                 */
                template < typename T > struct AddPointer : addPtrImpl :: AddPointer < T, true > {};

                /**
                 * @brief Meta-type implementation used to obtain a const type of the given type
                 * @tparam T type to add const to
                 */
                template < typename T > struct AddConst             { using Type = T const; };

                /**
                 * @brief Meta-type implementation used to obtain a volatile type of the given type
                 * @tparam T type to add volatile to
                 */
                template < typename T > struct AddVolatile          { using Type = T volatile; };

                /**
                 * @brief Meta-type implementation used to obtain a const volatile type of the given type
                 * @tparam T type to add const and volatile to
                 */
                template < typename T > struct AddConstVolatile     { using Type = typename AddConst < typename AddVolatile < T > :: Type > :: Type; };

                namespace addReferenceImpl {
                    /**
                     * @brief Meta-type helper used to obtain a lvalue reference (&) type of the given type
                     * @tparam T type to add a lvalue reference to
                     */
                    template < typename T, bool = IsReferenceable < T > :: value >
                    struct AddLValueReference               { using Type = T; };

                    template < typename T >
                    struct AddLValueReference < T, true >   { using Type = T &; };

                    /**
                     * @brief Meta-type helper used to obtain a rvalue reference (&&) type of the given type
                     * @tparam T type to add a rvalue reference to
                     */
                    template < typename T, bool = IsReferenceable < T > :: value >
                    struct AddRValueReference               { using Type = T; };

                    template < typename T >
                    struct AddRValueReference < T, true >   { using Type = T &&; };
                }

                /**
                 * @brief Meta-type implementation used to obtain a lvalue reference (&) type of the given type
                 * @tparam T type to add a lvalue reference to
                 */
                template < typename T > struct AddLValueReference : addReferenceImpl :: AddLValueReference < T > {};

                /**
                 * @brief Meta-type implementation used to obtain a rvalue reference (&&) type of the given type
                 * @tparam T type to add a rvalue reference to
                 */
                template < typename T > struct AddRValueReference : addReferenceImpl :: AddRValueReference < T > {};
            }

            /**
             * @brief Meta-type used to enable function declaration using sfiane based on a given condition
             * @tparam ReplacedType is the type that is saved inside the structure if the condition is true
             */
            template < bool enableCondition, typename ReplacedType = int >
            using EnableIf = typename impl :: EnableIf < enableCondition, ReplacedType > :: Type;

            /**
             * @brief Meta-type used to choose between two types based on a given condition
             * @tparam TypeIfTrue is the type to save if condition is true
             * @tparam TypeIfFalse is the type to save if condition is false
             */
            template < bool condition, typename TypeIfTrue, typename TypeIfFalse >
            using Conditional = typename impl :: Conditional < condition, TypeIfTrue, TypeIfFalse > :: Type;

            /**
             * @brief True Bool Constant container structure
             */
            using FalseType = impl :: FalseType;

            /**
             * @brief False Bool Constant container structure
             */
            using TrueType  = impl :: TrueType;

            /**
             * @brief Meta-type used to acquire the non-const type corresponding the current type
             * @tparam T type to remove const modifier for
             */
            template < typename T > using RemoveConst           = typename impl :: RemoveConst < T > :: Type;

            /**
             * @brief Meta-type used to acquire the non-volatile type corresponding the current type
             * @tparam T type to remove volatile modifier for
             */
            template < typename T > using RemoveVolatile        = typename impl :: RemoveVolatile < T > :: Type;

            /**
             * @brief Meta-type used to acquire the non-reference type corresponding the current type
             * @tparam T type to remove reference for
             */
            template < typename T > using RemoveReference       = typename impl :: RemoveReference < T > :: Type;

            /**
             * @brief Meta-type used to acquire the non-const, non-volatile type corresponding the current type
             * @tparam T type to remove const and volatile modifiers for
             */
            template < typename T > using RemoveConstVolatile   = typename impl :: RemoveConstVolatile < T > :: Type;

            /**
             * @brief Meta-type used to acquire the non-pointer type corresponding the current type
             * @tparam T type to remove pointer for
             */
            template < typename T > using RemovePointer         = typename impl :: RemovePointer < T > :: Type;

            /**
             * @brief Meta-type used to acquire the non-array extent type corresponding the current type
             * @tparam T type to remove the array extent ([] or [size]) for
             */
            template < typename T > using RemoveExtent          = typename impl :: RemoveExtent < T > :: Type;

            /**
             * @brief Meta-type used to acquire the non-array extent type corresponding the current type, until no extent exists
             * @tparam T type to remove all extents for - if T is T[][][], Type will be T
             */
            template < typename T > using RemoveAllExtents      = typename impl :: RemoveAllExtents < T > :: Type;


            /**
             * @brief Meta-type used to obtain a const type of the given type
             * @tparam T type to add const to
             */
            template < typename T > using AddConst              = typename impl :: AddConst < T > :: Type;

            /**
             * @brief Meta-type used to obtain a volatile type of the given type
             * @tparam T type to add volatile to
             */
            template < typename T > using AddVolatile           = typename impl :: AddVolatile < T > :: Type;

            /**
             * @brief Meta-type used to obtain a lvalue reference (&) type of the given type
             * @tparam T type to add a lvalue reference to
             */
            template < typename T > using AddLValueReference    = typename impl :: AddLValueReference < T > :: Type;

            /**
             * @brief Meta-type used to obtain a rvalue reference (&&) type of the given type
             * @tparam T type to add a rvalue reference to
             */
            template < typename T > using AddRValueReference    = typename impl :: AddRValueReference < T > :: Type;

            /**
             * @brief Meta-type used to obtain a const volatile type of the given type
             * @tparam T type to add const and volatile to
             */
            template < typename T > using AddConstVolatile      = typename impl :: AddConstVolatile < T > :: Type;

            /**
             * @brief Meta-type implementation used to obtain a pointer to the given type
             * @tparam T type to add a pointer to
             */
            template < typename T > using AddPointer            = typename impl :: AddPointer < T > :: Type;

            /**
             * @brief Meta-function used to check if a given type is void
             * @tparam T type to check if is void
             */
            template < typename T >
            constexpr auto isVoid () noexcept -> bool {
                return impl :: IsVoid < T > :: value;
            }

            /**
             * @brief Meta-function used to check if a given type is referenceable
             * @tparam T type to check if is referenceable
             */
            template < typename T >
            constexpr auto isReferenceable () noexcept -> bool {
                return impl :: IsReferenceable < T > :: value;
            }
        }
    }
}

#endif // __CDS_EX_META_BASE_HPP__
