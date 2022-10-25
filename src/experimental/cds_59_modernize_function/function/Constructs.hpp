/*
 * Created by loghin on 25/10/22.
 */

#ifndef __CDS_FUNCTION_CONSTRUCTS_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_FUNCTION_CONSTRUCTS_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            using __GenericFunctionObject       = void *;       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            using __GenericConstFunctionObject  = void const *; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template < typename __ReturnType, typename ... __ArgumentTypes >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            constexpr auto __functionAdapterInvokeHelper (                      /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __GenericFunctionObject            /* function */,
                    __ArgumentTypes             && ... /* arguments */
            ) noexcept -> __ReturnType {

                /* function implementation left as dummy on purpose. clang-10, gcc-9 and gcc-10 detect this as
                 * a used function, when it is only declared for SFINAE purposes. It will still return
                 * a value acquired from an undefined function to avoid usage in compiled code. */
                return cds :: meta :: referenceOf < __ReturnType > ();
            }


            template < typename __ReturnType, typename ... __ArgumentTypes >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            constexpr auto __functionAdapterCopyHelper (                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __GenericConstFunctionObject /* function */
            ) noexcept -> __GenericFunctionObject {

                /* function implementation left as dummy on purpose. clang-10, gcc-9 and gcc-10 detect this as
                 * a used function, when it is only declared for SFINAE purposes. It will still return
                 * a value acquired from an undefined function to avoid usage in compiled code. */
                return cds :: meta :: valueOf < __GenericFunctionObject > ();
            }


            template < typename __ReturnType, typename ... __ArgumentTypes >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            constexpr auto __functionAdapterClearHelper (                       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __GenericFunctionObject /* function */
            ) noexcept -> void {

                /* function implementation left as dummy on purpose. clang-10, gcc-9 and gcc-10 detect this as
                 * a used function, when it is only declared for SFINAE purposes. It will still return
                 * a value acquired from an undefined function to avoid usage in compiled code. */
            }


            template < typename __ReturnType, typename ... __ArgumentTypes >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            constexpr auto __functionAdapterCompareHelper (                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __GenericConstFunctionObject /* leftFunction */,
                    __GenericConstFunctionObject /* rightFunction */
            ) noexcept -> bool {

                /* function implementation left as dummy on purpose. clang-10, gcc-9 and gcc-10 detect this as
                 * a used function, when it is only declared for SFINAE purposes. It will still return
                 * a value acquired from an undefined function to avoid usage in compiled code. */
                return false;
            }


            template < typename __ReturnType, typename ... __ArgumentTypes >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            using __FunctionAdapterInvoke   =                                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    decltype ( & __functionAdapterInvokeHelper < __ReturnType, __ArgumentTypes ... > );


            template < typename __ReturnType, typename ... __ArgumentTypes >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            using __FunctionAdapterCopy     =                                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    decltype ( & __functionAdapterCopyHelper < __ReturnType, __ArgumentTypes ... > );


            template < typename __ReturnType, typename ... __ArgumentTypes >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            using __FunctionAdapterClear    =                                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    decltype ( & __functionAdapterClearHelper < __ReturnType, __ArgumentTypes ... > );


            template < typename __ReturnType, typename ... __ArgumentTypes >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            using __FunctionAdapterCompare    =                                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    decltype ( & __functionAdapterCompareHelper < __ReturnType, __ArgumentTypes ... > );


            template < typename __ReturnType, typename ... __ArgumentTypes >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __FunctionAdapterGroup {                                     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                __FunctionAdapterInvoke < __ReturnType, __ArgumentTypes ... >   _invoke;
                __FunctionAdapterCopy < __ReturnType, __ArgumentTypes ... >     _copy;
                __FunctionAdapterClear < __ReturnType, __ArgumentTypes ... >    _clear;
                __FunctionAdapterCompare < __ReturnType, __ArgumentTypes ... >  _compare;
            };

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_FUNCTION_CONSTRUCTS_HPP__ */
