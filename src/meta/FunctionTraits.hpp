//
// Created by loghin on 5/18/22.
//

#ifndef __CDS_META_FUNCTION_TRAITS_HPP__
#define __CDS_META_FUNCTION_TRAITS_HPP__

#include <CDS/meta/Base>

namespace cds {

    namespace experimental {

        /**
         * @class Type representing an element-tuple, a gathering of different value types, similar
         * to a struct with given member types in order.
         * @tparam __Pack is the types pack, representing the types of the fields of the tuple
         */
        template < typename ... __Pack >
        class Tuple;

    }

    namespace meta {
        namespace __impl {

            /**
             * @brief Meta-type implementation containing information extracted from a function's signature
             * @tparam __T is the type to extract function signature information from
             *
             * If given a valid callable object type, it will extract
             *      - ReturnType, representing the type of the returned value
             *      - ClassType, representing the type of the Class the function is a member of, if any. If not applicable, ClassType = void
             *      - ArgumentsType, representing the argument types, packed in a Tuple type
             */
            template < typename __T, typename = void >
            struct __FunctionTraits {};

            template < typename __R, typename ... __A >
            struct __FunctionTraits < auto ( __A ... ) -> __R > {
                using ReturnType    = __R;
                using ClassType     = void;
                using ArgumentsType = experimental :: Tuple < __A ... >;
            };

            template < typename __R, typename ... __A >
            struct __FunctionTraits < auto ( * ) ( __A ... ) -> __R > {
                using ReturnType = __R;
                using ClassType  = void;
                using ArgumentsType = experimental :: Tuple < __A ... >;
            };

            template < typename __R, typename __C, typename ... __A >
            struct __FunctionTraits < auto ( __C :: * ) ( __A ... ) -> __R > {
                using ReturnType = __R;
                using ClassType  = __C;
                using ArgumentsType = experimental :: Tuple < __A ... >;
            };

            template < typename __R, typename __C, typename ... __A >
            struct __FunctionTraits < auto ( __C :: * ) ( __A ... ) const -> __R > {
                using ReturnType = __R;
                using ClassType  = __C;
                using ArgumentsType = experimental :: Tuple < __A ... >;
            };

#if __CDS_cpplang_TemplatePartialSpecNoexceptFunction_available

            template < typename __R, typename ... __A >
            struct __FunctionTraits < auto ( __A ... ) noexcept -> __R > {
                using ReturnType = __R;
                using ClassType  = void;
                using ArgumentsType = experimental :: Tuple < __A ... >;
            };

            template < typename __R, typename ... __A >
            struct __FunctionTraits < auto ( * ) ( __A ... ) noexcept -> __R > {
                using ReturnType = __R;
                using ClassType  = void;
                using ArgumentsType = experimental :: Tuple < __A ... >;
            };

            template < typename __R, typename __C, typename ... __A >
            struct __FunctionTraits < auto ( __C :: * ) ( __A ... ) noexcept -> __R > {
                using ReturnType = __R;
                using ClassType  = __C;
                using ArgumentsType = experimental :: Tuple < __A ... >;
            };

            template < typename __R, typename __C, typename ... __A >
            struct __FunctionTraits < auto ( __C :: * ) ( __A ... ) const noexcept -> __R > {
                using ReturnType = __R;
                using ClassType  = __C;
                using ArgumentsType = experimental :: Tuple < __A ... >;
            };

#endif

            template < typename __T >
            struct __FunctionTraits < __T, Void < decltype ( & __T :: operator () ) > > : __FunctionTraits < decltype ( & __T :: operator () ) > {};

        }

        /**
         * @brief Meta-type containing information extracted from a function's signature
         * @tparam __T is the type to extract function signature information from
         *
         * If given a valid callable object type, it will extract
             *      - ReturnType, representing the type of the returned value
             *      - ClassType, representing the type of the Class the function is a member of, if any. If not applicable, ClassType = void
             *      - ArgumentsType, representing the argument types, packed in a Tuple type
         */
        template < typename __T >
        using FunctionTraits = __impl :: __FunctionTraits < __T >;

        /**
         * @brief Meta-type representing the type of the returned value of a function of a given type
         * @tparam __T is the type to extract the return type from
         */
        template < typename __T >
        using ReturnOf = typename FunctionTraits < __T > :: ReturnType;

        /**
         * @brief Meta-type representing the tuple of the types of the arguments of a function of a given type
         * @tparam __T is the type to extract the tuple of argument types from
         */
        template < typename __T >
        using ArgumentsOf = typename FunctionTraits < __T > :: ArgumentsType;

        /**
         * @brief Meta-type representing the type of the class a given function is the member of
         * @tparam __T is the type to extract the class type to which it is a member
         */
        template < typename __T >
        using ClassOf = typename FunctionTraits < __T > :: ClassType;
    }
}

#endif // __CDS_META_FUNCTION_TRAITS_HPP__
