//
// Created by loghin on 5/18/22.
//

#ifndef __CDS_EX_META_FUNCTION_TRAITS_HPP__
#define __CDS_EX_META_FUNCTION_TRAITS_HPP__

namespace cds {
    namespace experimental {
        namespace meta {
            namespace impl {

                template < typename T, typename = void >
                struct FunctionTraits {

                };

                template < typename R, typename ... A >
                struct FunctionTraits < auto ( A ... ) -> R > {
                    using ReturnType = R;
                    using ClassType  = void;
                };

                template < typename R, typename ... A >
                struct FunctionTraits < auto ( * ) ( A ... ) -> R > {
                    using ReturnType = R;
                    using ClassType  = void;
                };

                template < typename R, typename C, typename ... A >
                struct FunctionTraits < auto ( C :: * ) ( A ... ) -> R > {
                    using ReturnType = R;
                    using ClassType  = C;
                };

                template < typename R, typename C, typename ... A >
                struct FunctionTraits < auto ( C :: * ) ( A ... ) const -> R > {
                    using ReturnType = R;
                    using ClassType  = C;
                };

#if __CDS_cpplang_TemplatePartialSpecNoexceptFunction_available

                template < typename R, typename ... A >
                struct FunctionTraits < auto ( A ... ) noexcept -> R > {
                    using ReturnType = R;
                    using ClassType  = void;
                };

                template < typename R, typename ... A >
                struct FunctionTraits < auto ( * ) ( A ... ) noexcept -> R > {
                    using ReturnType = R;
                    using ClassType  = void;
                };

                template < typename R, typename C, typename ... A >
                struct FunctionTraits < auto ( C :: * ) ( A ... ) noexcept -> R > {
                    using ReturnType = R;
                    using ClassType  = C;
                };

                template < typename R, typename C, typename ... A >
                struct FunctionTraits < auto ( C :: * ) ( A ... ) const noexcept -> R > {
                    using ReturnType = R;
                    using ClassType  = C;
                };

#endif

                template < typename T >
                struct FunctionTraits < T, Void < decltype ( & T :: operator () ) > > : FunctionTraits < decltype ( & T :: operator () ) > {};

            }
        }
    }
}

#endif // __CDS_EX_META_FUNCTION_TRAITS_HPP__
