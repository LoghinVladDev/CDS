/*
 * Created by loghin on 25/10/22.
 */

#ifndef __CDS_FUNCTION_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_FUNCTION_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */

    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template < typename __Signature, typename __FunctionSignature > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __FunctionAdapter {};                                    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template < typename __Signature, typename __Functor >           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __FunctorAdapter;                                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */


            template < typename __FunctionSignature, typename __ReturnType, typename ... __ArgumentTypes >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __FunctionAdapter < __ReturnType ( __ArgumentTypes ... ), __FunctionSignature > {        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                constexpr static auto __invoke (                                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __GenericFunctionObject        function,
                        __ArgumentTypes         && ... arguments
                ) noexcept (false) -> __ReturnType {

                    return reinterpret_cast < cds :: meta :: Decay < __FunctionSignature > > ( function ) (
                            std :: forward < __ArgumentTypes > ( arguments ) ...
                    );
                }


                constexpr static auto __copy ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __GenericConstFunctionObject function
                ) noexcept -> __GenericFunctionObject {

                    return const_cast < __GenericFunctionObject > ( function );
                }


                __CDS_cpplang_ConstexprNonLiteralReturn static auto __clear ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __GenericFunctionObject /* function */
                ) noexcept -> void {

                    /* do nothing */
                }


                constexpr static auto __compare (                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __GenericConstFunctionObject leftFunction,  /* NOLINT(bugprone-easily-swappable-parameters) */
                        __GenericConstFunctionObject rightFunction  /* NOLINT(bugprone-easily-swappable-parameters) */
                ) noexcept -> bool {

                    return leftFunction == rightFunction;
                }


                static auto __adapterGroup () noexcept -> __FunctionAdapterGroup < __ReturnType, __ArgumentTypes ... > const * { /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                    static __FunctionAdapterGroup < __ReturnType, __ArgumentTypes ... > const adapterGroup = {
                            & __FunctionAdapter :: __invoke,
                            & __FunctionAdapter :: __copy,
                            & __FunctionAdapter :: __clear,
                            & __FunctionAdapter :: __compare
                    };

                    return & adapterGroup;
                }
            };


            template < typename __Functor, typename __ReturnType, typename ... __ArgumentTypes >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __FunctorAdapter < __ReturnType ( __ArgumentTypes ... ), __Functor > {           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                inline static auto __invoke ( /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __GenericFunctionObject        function,
                        __ArgumentTypes         && ... arguments
                ) noexcept (false) -> __ReturnType {

                    static auto const pMemberCallOperator = & __Functor :: operator ();
                    return
                            ( ( static_cast < __Functor * > ( function ) ) ->* pMemberCallOperator ) (
                                    std :: forward < __ArgumentTypes > ( arguments ) ...
                            );
                }


                __CDS_OptimalInline static auto __copy (                                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __GenericConstFunctionObject function
                ) noexcept -> __GenericFunctionObject {

                    return reinterpret_cast < __GenericFunctionObject > (                       /* NOLINT(cppcoreguidelines-owning-memory) */
                            new __Functor (
                                    * static_cast < __Functor const * > ( function )
                            )
                    );
                }


                __CDS_OptimalInline static auto __clear (                                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __GenericFunctionObject function
                ) noexcept -> void {

                    delete static_cast < __Functor * > ( function );
                }


                __CDS_OptimalInline static auto __compare (         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                        __GenericConstFunctionObject leftFunction,  /* NOLINT(bugprone-easily-swappable-parameters) */
                        __GenericConstFunctionObject rightFunction  /* NOLINT(bugprone-easily-swappable-parameters) */
                ) noexcept -> bool {

                    return std :: memcmp (
                            leftFunction,
                            rightFunction,
                            sizeof ( __Functor )
                    ) == 0;
                }


                inline static auto __adapterGroup () noexcept -> __FunctionAdapterGroup < __ReturnType, __ArgumentTypes ... > const * { /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                    static __FunctionAdapterGroup < __ReturnType, __ArgumentTypes ... > const adapterGroup = {
                            & __FunctorAdapter :: __invoke,
                            & __FunctorAdapter :: __copy,
                            & __FunctorAdapter :: __clear,
                            & __FunctorAdapter :: __compare
                    };

                    return & adapterGroup;
                }
            };


            template < typename ... __NoTypes, cds :: meta :: EnableIf < sizeof ... (__NoTypes) == 0 > = 0 >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            inline auto __functionToStringTypeReduce () noexcept -> String {                                    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                return "";
            }


            template < typename __LastType >                                    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            inline auto __functionToStringTypeReduce () noexcept -> String {    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                return cds :: meta :: Type < __LastType > :: name ();
            }


            template < typename __FirstType, typename ... __RemainingTypes, cds :: meta :: EnableIf < sizeof ... (__RemainingTypes) >= 1 > = 0 >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            inline auto __functionToStringTypeReduce () noexcept -> String {                                                                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

                return String ( cds :: meta :: Type < __FirstType > :: name () ) + ", " + __functionToStringTypeReduce < __RemainingTypes ... > ();
            }

        } /* namespace __impl */
    } /* namespace __hidden */

    template < typename __ReturnType, typename ... __ArgumentTypes >
    constexpr Function < __ReturnType ( __ArgumentTypes ... ) > :: Function () noexcept = default;


    template < typename __ReturnType, typename ... __ArgumentTypes >
    __CDS_cpplang_ConstexprConstructorNonEmptyBody Function < __ReturnType ( __ArgumentTypes ... ) > :: Function (
            Function const & function
    ) noexcept :
            _adapterGroup ( function._adapterGroup ) {

        if ( this->_adapterGroup != nullptr ) {
            this->_functionObject = this->_adapterGroup->_copy ( function._functionObject );
        }
    }


    template < typename __ReturnType, typename ... __ArgumentTypes >
    constexpr Function < __ReturnType ( __ArgumentTypes ... ) > :: Function (
            Function && function
    ) noexcept :
            _adapterGroup ( cds :: exchange ( function._adapterGroup, nullptr ) ),
            _functionObject ( cds :: exchange ( function._functionObject, nullptr ) ) {

    }


    template < typename __ReturnType, typename ... __ArgumentTypes >
    template < typename __ReceivedReturnType, typename ... __ReceivedArgumentTypes >
    __CDS_cpplang_ConstexprConstructorNonEmptyBody Function < __ReturnType ( __ArgumentTypes ... ) > :: Function (
            __ReceivedReturnType ( * function ) ( __ReceivedArgumentTypes ... )
    ) noexcept :
            _functionObject ( reinterpret_cast < __hidden :: __impl :: __GenericFunctionObject > ( function ) ) {

        this->_adapterGroup = cds :: __hidden :: __impl :: __FunctionAdapter <
                __ReturnType ( __ArgumentTypes ... ),
                __ReceivedReturnType ( __ReceivedArgumentTypes ... )
        > :: __adapterGroup ();
    }


    template < typename __ReturnType, typename ... __ArgumentTypes >
    template < typename __Functor, cds :: meta :: EnableIf < cds :: meta :: isObjectFunction < __Functor > () > >
    __CDS_cpplang_ConstexprConstructorNonEmptyBody Function < __ReturnType ( __ArgumentTypes ... ) > :: Function (
            __Functor const & functor
    ) noexcept {

        this->_adapterGroup = cds :: __hidden :: __impl :: __FunctorAdapter <
                __ReturnType ( __ArgumentTypes ... ),
                __Functor
        > :: __adapterGroup ();

        this->_functionObject = this->_adapterGroup->_copy ( & functor );
    }


    template < typename __ReturnType, typename ... __ArgumentTypes >
    Function < __ReturnType ( __ArgumentTypes ... ) > :: ~Function () noexcept {

        if ( this->_adapterGroup != nullptr ) {
            this->_adapterGroup->_clear ( this->_functionObject );
        }
    }


    template < typename __ReturnType, typename ... __ArgumentTypes >
    auto Function < __ReturnType ( __ArgumentTypes ... ) > :: operator = (
            Function const & function
    ) noexcept -> Function & {

        if ( this == & function || this->_functionObject == function._functionObject ) {
            return true;
        }

        if ( this->_adapterGroup != nullptr ) {
            this->_adapterGroup->_clear ( this->_functionObject );
        }

        this->_adapterGroup = function._adapterGroup;
        if ( this->_adapterGroup != nullptr ) {
            this->_functionObject = this->_adapterGroup->_copy ( function._functionObject );
        }

        return * this;
    }


    template < typename __ReturnType, typename ... __ArgumentTypes >
    auto Function < __ReturnType ( __ArgumentTypes ... ) > :: operator = (
            Function && function
    ) noexcept -> Function & {

        if ( this == & function || this->_functionObject == function._functionObject ) {
            return true;
        }

        if ( this->_adapterGroup != nullptr ) {
            this->_adapterGroup->_clear ( this->_functionObject );
        }

        this->_adapterGroup     = cds :: exchange ( function._adapterGroup, nullptr );
        this->_functionObject   = cds :: exchange ( function._functionObject, nullptr );

        return * this;
    }


    template < typename __ReturnType, typename ... __ArgumentTypes >
    template < typename __ReceivedReturnType, typename ... __ReceivedArgumentTypes >
    auto Function < __ReturnType ( __ArgumentTypes ... ) > :: operator = (
            __ReceivedReturnType ( * function ) ( __ReceivedArgumentTypes ... )
    ) noexcept -> Function & {

        if ( this->_functionObject == function ) {
            return true;
        }

        if ( this->_adapterGroup != nullptr ) {
            this->_adapterGroup->_clear ( this->_functionObject );
        }

        this->_functionObject   = reinterpret_cast < __hidden :: __impl :: __GenericFunctionObject > ( function );
        this->_adapterGroup     = cds :: __hidden :: __impl :: __FunctionAdapter <
                __ReturnType ( __ArgumentTypes ... ),
                __ReceivedReturnType ( __ReceivedArgumentTypes ... )
        > :: __adapterGroup ();

        return * this;
    }


    template < typename __ReturnType, typename ... __ArgumentTypes >
    template < typename __Functor, cds :: meta :: EnableIf < cds :: meta :: isObjectFunction < __Functor > () > >
    auto Function < __ReturnType ( __ArgumentTypes ... ) > :: operator = (
            __Functor const & functor
    ) noexcept -> Function & {

        if ( this->_functionObject == & functor ) {
            return true;
        }

        if ( this->_adapterGroup != nullptr ) {
            this->_adapterGroup->_clear ( this->_functionObject );
        }

        this->_adapterGroup     = cds :: __hidden :: __impl :: __FunctorAdapter <
                __ReturnType ( __ArgumentTypes ... ),
                __Functor
        > :: __adapterGroup ();
        this->_functionObject   = this->_adapterGroup->_copy ( & functor );

        return * this;
    }


    template < typename __ReturnType, typename ... __ArgumentTypes >
    constexpr auto Function < __ReturnType ( __ArgumentTypes ... ) > :: empty () const noexcept -> bool {

        return this->_functionObject == nullptr;
    }


    template < typename __ReturnType, typename ... __ArgumentTypes >
    __CDS_cpplang_ConstexprConditioned auto Function < __ReturnType ( __ArgumentTypes ... ) > :: operator () (
            __ArgumentTypes ... arguments
    ) const noexcept (false) -> __ReturnType {

        if ( this->_functionObject == nullptr ) {
            throw NullPointerException ("Invalid Function Call. No Handle Assigned");
        }

        return this->_adapterGroup->_invoke (
                this->_functionObject,
                std :: forward < __ArgumentTypes > ( arguments ) ...
        );
    }


    template < typename __ReturnType, typename ... __ArgumentTypes >
    __CDS_OptimalInline auto Function < __ReturnType ( __ArgumentTypes ... ) > :: toString () const noexcept -> String {

        std :: stringstream oss;

        oss
                << "Function " << meta :: Type < __ReturnType > :: name () << " ( "
                << cds :: __hidden :: __impl :: __functionToStringTypeReduce < __ArgumentTypes ... > ()
                << " ) at " << std :: hex << reinterpret_cast < AddressValueType > ( this->_functionObject )
                << std :: dec;

        return oss.str();
    }


    template < typename __ReturnType, typename ... __ArgumentTypes >
    __CDS_OptimalInline auto Function < __ReturnType ( __ArgumentTypes ... ) > :: equals (
            Object const & object
    ) const noexcept -> bool {

        if ( this == & object ) {
            return true;
        }

        auto pFunction = dynamic_cast < decltype (this) > ( & object );
        if ( pFunction == nullptr ) {
            return false;
        }

        return
                this->_adapterGroup == pFunction->_adapterGroup &&
                this->_adapterGroup->_compare ( this->_functionObject, pFunction->_functionObject );
    }


    template < typename __ReturnType, typename ... __ArgumentTypes >
    __CDS_OptimalInline auto Function < __ReturnType ( __ArgumentTypes ... ) > :: hash () const noexcept -> Size {

        return reinterpret_cast < Size > ( this->_adapterGroup );
    }

} /* namespace cds */

#endif /* __CDS_FUNCTION_IMPL_HPP__ */
