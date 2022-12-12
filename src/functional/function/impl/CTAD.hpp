/*
 * Created by loghin on 26/10/22.
 */

#ifndef __CDS_FUNCTION_CTAD_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_FUNCTION_CTAD_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#if __CDS_cpplang_CTAD_available

namespace cds {

    namespace meta {

        namespace __impl {

            template < typename = void > struct __SignatureOf {};   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template <
                    typename        __ReturnType,               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename        __ClassType,                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename    ... __ArgumentTypes             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > struct __SignatureOf <
                    __ReturnType ( __ClassType :: * ) ( __ArgumentTypes ... )
            > {
                using Type = __ReturnType ( __ArgumentTypes ... );
            };

            template <
                    typename        __ReturnType,               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename        __ClassType,                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename    ... __ArgumentTypes             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > struct __SignatureOf <
                    __ReturnType ( __ClassType :: * ) ( __ArgumentTypes ... ) const
            > {
                using Type = __ReturnType ( __ArgumentTypes ... );
            };

            template <
                    typename        __ReturnType,               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename        __ClassType,                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename    ... __ArgumentTypes             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > struct __SignatureOf <
                    __ReturnType ( __ClassType :: * ) ( __ArgumentTypes ... ) &
            > {
                using Type = __ReturnType ( __ArgumentTypes ... );
            };

            template <
                    typename        __ReturnType,               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename        __ClassType,                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename    ... __ArgumentTypes             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            > struct __SignatureOf <
                    __ReturnType ( __ClassType :: * ) ( __ArgumentTypes ... ) const & noexcept
            > {
                using Type = __ReturnType ( __ArgumentTypes ... );
            };

        } /* namespace __impl */

        template < typename __MemberFunction >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        using SignatureOf = typename __impl :: __SignatureOf < __MemberFunction > :: Type;

    } /* namespace meta */

    template < typename __ReturnType, typename ... __ArgumentTypes >                                            /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    Function ( __ReturnType (*) ( __ArgumentTypes ... ) ) -> Function < __ReturnType ( __ArgumentTypes ... ) >; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

    template < typename __Functor, typename __Signature = cds :: meta :: SignatureOf < decltype ( & __Functor :: operator () ) > >
    Function ( __Functor ) -> Function < __Signature >;

} /* namespace cds */

#endif

#endif /* __CDS_FUNCTION_CTAD_HPP__ */
