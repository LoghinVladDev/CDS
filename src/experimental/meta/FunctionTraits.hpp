//
// Created by loghin on 5/18/22.
//

#ifndef __CDS_EX_META_FUNCTION_TRAITS_HPP__
#define __CDS_EX_META_FUNCTION_TRAITS_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        /**
         * @class Type representing an element-tuple, a gathering of different value types, similar
         * to a struct with given member types in order.
         * @tparam Pack is the types pack, representing the types of the fields of the tuple
         */
        template < typename ... Pack >
        class Tuple;

        namespace meta {
            namespace impl {

                /**
                 * @brief Meta-type implementation containing information extracted from a function's signature
                 * @tparam T is the type to extract function signature information from
                 *
                 * If given a valid callable object type, it will extract
                 *      - ReturnType, representing the type of the returned value
                 *      - ClassType, representing the type of the Class the function is a member of, if any. If not applicable, ClassType = void
                 *      - ArgumentsType, representing the argument types, packed in a Tuple type
                 */
                template < typename T, typename = void >
                struct FunctionTraits {

                };

                template < typename R, typename ... A >
                struct FunctionTraits < auto ( A ... ) -> R > {
                    using ReturnType    = R;
                    using ClassType     = void;
                    using ArgumentsType = Tuple < A ... >;
                };

                template < typename R, typename ... A >
                struct FunctionTraits < auto ( * ) ( A ... ) -> R > {
                    using ReturnType = R;
                    using ClassType  = void;
                    using ArgumentsType = Tuple < A ... >;
                };

                template < typename R, typename C, typename ... A >
                struct FunctionTraits < auto ( C :: * ) ( A ... ) -> R > {
                    using ReturnType = R;
                    using ClassType  = C;
                    using ArgumentsType = Tuple < A ... >;
                };

                template < typename R, typename C, typename ... A >
                struct FunctionTraits < auto ( C :: * ) ( A ... ) const -> R > {
                    using ReturnType = R;
                    using ClassType  = C;
                    using ArgumentsType = Tuple < A ... >;
                };

#if __CDS_cpplang_TemplatePartialSpecNoexceptFunction_available

                template < typename R, typename ... A >
                struct FunctionTraits < auto ( A ... ) noexcept -> R > {
                    using ReturnType = R;
                    using ClassType  = void;
                    using ArgumentsType = Tuple < A ... >;
                };

                template < typename R, typename ... A >
                struct FunctionTraits < auto ( * ) ( A ... ) noexcept -> R > {
                    using ReturnType = R;
                    using ClassType  = void;
                    using ArgumentsType = Tuple < A ... >;
                };

                template < typename R, typename C, typename ... A >
                struct FunctionTraits < auto ( C :: * ) ( A ... ) noexcept -> R > {
                    using ReturnType = R;
                    using ClassType  = C;
                    using ArgumentsType = Tuple < A ... >;
                };

                template < typename R, typename C, typename ... A >
                struct FunctionTraits < auto ( C :: * ) ( A ... ) const noexcept -> R > {
                    using ReturnType = R;
                    using ClassType  = C;
                    using ArgumentsType = Tuple < A ... >;
                };

#endif

                template < typename T >
                struct FunctionTraits < T, Void < decltype ( & T :: operator () ) > > : FunctionTraits < decltype ( & T :: operator () ) > {};

            }

            /**
             * @brief Meta-type containing information extracted from a function's signature
             * @tparam T is the type to extract function signature information from
             *
             * If given a valid callable object type, it will extract
                 *      - ReturnType, representing the type of the returned value
                 *      - ClassType, representing the type of the Class the function is a member of, if any. If not applicable, ClassType = void
                 *      - ArgumentsType, representing the argument types, packed in a Tuple type
             */
            template < typename T >
            using FunctionTraits = impl :: FunctionTraits < T >;

            /**
             * @brief Meta-type representing the type of the returned value of a function of a given type
             * @tparam T is the type to extract the return type from
             */
            template < typename T >
            using ReturnOf = typename FunctionTraits < T > :: ReturnType;

            /**
             * @brief Meta-type representing the tuple of the types of the arguments of a function of a given type
             * @tparam T is the type to extract the tuple of argument types from
             */
            template < typename T >
            using ArgumentsOf = typename FunctionTraits < T > :: ArgumentsType;

            /**
             * @brief Meta-type representing the type of the class a given function is the member of
             * @tparam T is the type to extract the class type to which it is a member
             */
            template < typename T >
            using ClassOf = typename FunctionTraits < T > :: ClassType;
        }
    }
}

#endif // __CDS_EX_META_FUNCTION_TRAITS_HPP__
