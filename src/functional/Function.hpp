/*
 * Created by loghin on 28.10.2021.
 */

#ifndef __CDS_FUNCTION_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_FUNCTION_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/Object>               /* NOLINT(llvm-include-order) */
#include <CDS/exception/NoSuchElementException>

#include "function/Constructs.hpp"

namespace cds {

    template < typename __Signature >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    class Function : public Object {};

    namespace meta {
        template <typename Functor, typename = void>
        struct Callable : meta::FalseType {};

        template <typename Functor>
        struct Callable <Functor, meta::Void<decltype(&Functor::operator())>> : meta::TrueType {};
    }


    template < typename __ReturnType, typename ... __ArgumentTypes >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    class Function < __ReturnType ( __ArgumentTypes ... ) > : public Object {

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        cds :: __hidden :: __impl :: __FunctionAdapterGroup < __ReturnType, __ArgumentTypes ... > const * _adapterGroup     { nullptr };

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        cds :: __hidden :: __impl :: __GenericFunctionObject                                              _functionObject   { nullptr };

    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr Function () noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_ConstexprConstructorNonEmptyBody Function (
                Function const & function
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr Function (
                Function && function
        ) noexcept;

    public:                                                                                 /* NOLINT(readability-redundant-access-specifiers) */
        template < typename __ReceivedReturnType, typename ... __ReceivedArgumentTypes >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        __CDS_Implicit __CDS_cpplang_ConstexprConstructorNonEmptyBody Function (            /* NOLINT(google-explicit-constructor, *-explicit-conversions) */
                __ReceivedReturnType ( * function ) ( __ReceivedArgumentTypes ... )
        ) noexcept;

    public:                                                                                                                 /* NOLINT(readability-redundant-access-specifiers) */
        template < typename __Functor, typename = cds :: meta :: EnableIf < meta::Callable < __Functor > :: value > >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        __CDS_Implicit __CDS_cpplang_ConstexprConstructorNonEmptyBody Function (                                            /* NOLINT(google-explicit-constructor, *-explicit-conversions) */
                __Functor const & functor
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        ~Function() noexcept override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                Function const & function
        ) noexcept -> Function &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                Function && function
        ) noexcept -> Function &;

    public:                                                                                 /* NOLINT(readability-redundant-access-specifiers) */
        template < typename __ReceivedReturnType, typename ... __ReceivedArgumentTypes >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        auto operator = (
                __ReceivedReturnType ( * function ) ( __ReceivedArgumentTypes ... )
        ) noexcept -> Function &;

    public:                                                                                                                 /* NOLINT(readability-redundant-access-specifiers) */
        template < typename __Functor, cds :: meta :: EnableIf < cds :: meta :: isObjectFunction < __Functor > () > = 0 >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        auto operator = (
                __Functor const & functor
        ) noexcept -> Function &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr auto empty () const noexcept -> bool;


    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_ConstexprConditioned auto operator () (
                __ArgumentTypes ... arguments
        ) const noexcept (false) -> __ReturnType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto toString () const noexcept -> String override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto equals (
                Object const & object
        ) const noexcept -> bool override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto hash () const noexcept -> Size override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr auto operator == (
                Function const & function
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr auto operator != (
                Function const & function
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template < typename __Functor, typename = cds :: meta :: EnableIf < meta::Callable < __Functor > :: value > >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        __CDS_NoDiscard constexpr auto operator == (
                __Functor const & functor
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template < typename __Functor, typename = cds :: meta :: EnableIf < meta::Callable < __Functor > :: value > >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        __CDS_NoDiscard constexpr auto operator != (
                __Functor const & functor
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template < typename __ReceivedReturnType, typename ... __ReceivedArgumentTypes >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        __CDS_NoDiscard constexpr auto operator == (
                __ReceivedReturnType ( * function ) ( __ReceivedArgumentTypes ... )
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template < typename __ReceivedReturnType, typename ... __ReceivedArgumentTypes >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        __CDS_NoDiscard constexpr auto operator != (
                __ReceivedReturnType ( * function ) ( __ReceivedArgumentTypes ... )
        ) const noexcept -> bool;
    };

} /* namespace cds */

#include "function/impl/Function.hpp" /* NOLINT(llvm-include-order) */
#include "function/impl/CTAD.hpp"
#include "FunctionalInterface.hpp"

#endif /* __CDS_FUNCTION_HPP__ */
