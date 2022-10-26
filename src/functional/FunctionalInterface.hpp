/*
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

    } /* namespace functional */
} /* namespace cds */

#if defined (__CDS_FUNCTION_HPP__)

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

#endif /* __CDS_FUNCTIONAL_INTERFACE_HPP__ */
