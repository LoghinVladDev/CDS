/*
 * Created by loghin on 25/10/22.
 */

#ifndef __CDS_FUNCTION_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_FUNCTION_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/Object>

namespace cds {

    template < typename __ReturnType, typename ... __ArgumentTypes >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    class Function : public Object {};


    template < typename __ReturnType, typename ... __ArgumentTypes >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    class Function < __ReturnType ( __ArgumentTypes ... ) > : public Object {

    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr Function () noexcept = delete;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr Function (
                Function const & function
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr Function (
                Function && function
        ) noexcept;

    public:                                                                                 /* NOLINT(readability-redundant-access-specifiers) */
        template < typename __ReceivedReturnType, typename ... __ReceivedArgumentTypes >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        __CDS_Implicit constexpr Function (                                                 /* NOLINT(google-explicit-constructor, *-explicit-conversions) */
                __ReceivedReturnType ( * function ) ( __ReceivedArgumentTypes ... )
        ) noexcept;

    public:                                                                                                                 /* NOLINT(readability-redundant-access-specifiers) */
        template < typename __Functor, cds :: meta :: EnableIf < cds :: meta :: isObjectFunction < __Functor > () > = 0 >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        __CDS_Implicit constexpr Function (                                                                                 /* NOLINT(google-explicit-constructor, *-explicit-conversions) */
                __Functor const & functor
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        ~Function() noexcept override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                Function const & function
        ) noexcept -> Function &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                Function && function
        ) noexcept -> Function &;

    public:                                                                                 /* NOLINT(readability-redundant-access-specifiers) */
        template < typename __ReceivedReturnType, typename ... __ReceivedArgumentTypes >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                __ReceivedReturnType ( * function ) ( __ReceivedArgumentTypes ... )
        ) noexcept -> Function &;

    public:                                                                                                                 /* NOLINT(readability-redundant-access-specifiers) */
        template < typename __Functor, cds :: meta :: EnableIf < cds :: meta :: isObjectFunction < __Functor > () > = 0 >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                __Functor const & functor
        ) noexcept -> Function &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr auto operator () ( __ArgumentTypes ... ) const noexcept -> __ReturnType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto toString () const noexcept -> String override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto equals (
                Object const & object
        ) const noexcept -> bool override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto hash () const noexcept -> Size override;
    };

} /* namespace cds */

#endif /* __CDS_FUNCTION_HPP__ */
