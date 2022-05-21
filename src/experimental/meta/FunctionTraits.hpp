//
// Created by loghin on 5/18/22.
//

#ifndef __CDS_EX_META_FUNCTION_TRAITS_HPP__
#define __CDS_EX_META_FUNCTION_TRAITS_HPP__

namespace cds {
    namespace experimental {

        template < typename ... Pack >
        class Tuple;

        namespace meta {
            namespace impl {

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

            template < typename T >
            using FunctionTraits = impl :: FunctionTraits < T >;

            template < typename T >
            using ReturnOf = typename FunctionTraits < T > :: ReturnType;

            template < typename T >
            using ArgumentsOf = typename FunctionTraits < T > :: ArgumentsType;

            template < typename T >
            using ClassOf = typename FunctionTraits < T > :: ClassType;
        }
    }
}

#endif // __CDS_EX_META_FUNCTION_TRAITS_HPP__
