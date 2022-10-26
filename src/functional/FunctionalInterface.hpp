/* NOLINT(llvm-header-guard)
 * Created by loghin on 26/10/22.
 */

#ifndef __CDS_FUNCTIONAL_INTERFACE_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_FUNCTIONAL_INTERFACE_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */
    namespace functional {

        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                template < typename ... __ConsumedTypes >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                inline auto __consumerFunctionHint (        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __ConsumedTypes && ... /* consumedValues */
                ) noexcept -> void {

                    /* function implementation left as dummy on purpose. clang-10, gcc-9 and gcc-10 detect this as
                     * a used function, when it is only declared for SFINAE purposes. It will still return
                     * a value acquired from an undefined function to avoid usage in compiled code. */
                }


                template < typename ... __TestedTypes >     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                inline auto __predicateFunctionHint (       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __TestedTypes && ... /* testedValues */
                ) noexcept -> bool {

                    /* function implementation left as dummy on purpose. clang-10, gcc-9 and gcc-10 detect this as
                     * a used function, when it is only declared for SFINAE purposes. It will still return
                     * a value acquired from an undefined function to avoid usage in compiled code. */
                    return true;
                }


                template < typename __ReturnType, typename ... __ArgumentTypes >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                inline auto __mapFunctionHint (                                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __ArgumentTypes && ... /* arguments */
                ) noexcept -> __ReturnType {

                    /* function implementation left as dummy on purpose. clang-10, gcc-9 and gcc-10 detect this as
                     * a used function, when it is only declared for SFINAE purposes. It will still return
                     * a value acquired from an undefined function to avoid usage in compiled code. */
                    return cds :: meta :: referenceOf < __ReturnType const > ();
                }


                template < typename __SuppliedType >                                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                inline auto __supplierFunctionHint () noexcept -> __SuppliedType {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                    /* function implementation left as dummy on purpose. clang-10, gcc-9 and gcc-10 detect this as
                     * a used function, when it is only declared for SFINAE purposes. It will still return
                     * a value acquired from an undefined function to avoid usage in compiled code. */
                    return cds :: meta :: referenceOf < __SuppliedType const > ();
                }

            } /* namespace __impl */
        } /* namespace __hidden */

        template < typename ... __ConsumedTypes >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        using ConsumerFunctionPointer = decltype (
                & __hidden :: __impl :: __consumerFunctionHint < __ConsumedTypes ... >
        );


        template < typename ... __TestedTypes >     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        using PredicateFunctionPointer = decltype (
                & __hidden :: __impl :: __predicateFunctionHint < __TestedTypes ... >
        );


        template < typename __ReturnType, typename ... __ArgumentTypes >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        using MapperFunction = decltype (
                & __hidden :: __impl :: __mapFunctionHint < __ReturnType, __ArgumentTypes ... >
        );


        template < typename __SuppliedType >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        using SupplierFunctionPointer = decltype (
                & __hidden :: __impl :: __supplierFunctionHint < __SuppliedType >
        );


        template < typename __ConsumerFunctionType, __ConsumerFunctionType __consumerFunction > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        struct DecoratedConsumer {};


        template < typename __PredicateFunctionType, __PredicateFunctionType __predicateFunction >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        struct DecoratedPredicate {};


        template < typename __MapperFunctionType, __MapperFunctionType __mapperFunction >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        struct DecoratedMapper {};


        template < typename __SupplierFunctionType, __SupplierFunctionType __supplierFunction > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        struct DecoratedSupplier {};


        template <
                typename                    __ConsumerFunctionType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __ConsumerFunctionType      __consumerFunction,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                typename                ... __ConsumerArgumentTypes /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        > struct DecoratedConsumer < void (*) ( __ConsumerArgumentTypes ... ), __consumerFunction > {

            __CDS_cpplang_ConstexprNonLiteralReturn auto operator () (
                    __ConsumerArgumentTypes ... arguments
            ) const noexcept ( noexcept ( __consumerFunction ( std :: forward < __ConsumerArgumentTypes > ( arguments ) ... ) ) ) -> void {

                __consumerFunction ( std :: forward < __ConsumerArgumentTypes > ( arguments ) ... );
            }
        };


        template <
                typename                    __PredicateFunctionType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __PredicateFunctionType     __predicateFunction,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                typename                ... __PredicateArgumentTypes    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        > struct DecoratedPredicate < bool (*) ( __PredicateArgumentTypes ... ), __predicateFunction > {

            __CDS_NoDiscard constexpr auto operator () (
                    __PredicateArgumentTypes ... arguments
            ) const noexcept ( noexcept ( __predicateFunction ( std :: forward < __PredicateArgumentTypes > ( arguments ) ... ) ) ) -> bool {

                return __predicateFunction ( std :: forward < __PredicateArgumentTypes > ( arguments ) ... );
            }
        };


        template <
                typename                    __MapperFunctionType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __MapperFunctionType        __mapperFunction,       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                typename                    __MapperReturnType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                typename                ... __MapperArgumentTypes   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        > struct DecoratedMapper < __MapperReturnType (*) ( __MapperArgumentTypes ... ), __mapperFunction > {

            __CDS_NoDiscard constexpr auto operator () (
                    __MapperArgumentTypes ... arguments
            ) const noexcept ( noexcept ( __mapperFunction ( std :: forward < __MapperArgumentTypes > ( arguments ) ... ) ) ) -> __MapperReturnType {

                return __mapperFunction ( std :: forward < __MapperArgumentTypes > ( arguments ) ... );
            }
        };


        template <
                typename                    __SupplierFunctionType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __SupplierFunctionType      __supplierFunction,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                typename                    __SupplierReturnType    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        > struct DecoratedSupplier < __SupplierReturnType (*) (), __supplierFunction > {

            __CDS_NoDiscard constexpr auto operator () () const noexcept ( noexcept ( __supplierFunction () ) ) -> __SupplierReturnType {

                return __supplierFunction ();
            }
        };

    } /* namespace functional */
} /* namespace cds */

#endif /* __CDS_FUNCTIONAL_INTERFACE_HPP__ */

#if defined (__CDS_FUNCTION_HPP__) && ! defined (__CDS_FUNCTION_FUNCTIONAL_INTERFACES_HPP__)
#define __CDS_FUNCTION_FUNCTIONAL_INTERFACES_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */
    namespace functional {

        template < typename ... __ConsumedTypes >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        using Consumer = cds :: Function < void ( __ConsumedTypes ... ) >;

        template < typename ... __TestedTypes >     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        using Predicate = cds :: Function < bool ( __TestedTypes ... ) >;;

        template < typename __ReturnType, typename ... __ArgumentTypes >
        using Mapper = cds :: Function < __ReturnType ( __ArgumentTypes ... ) >;

        template < typename __SuppliedType >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        using Supplier = cds :: Function < __SuppliedType () >;

    } /* namespace functional */
} /* namespace cds */

#endif
