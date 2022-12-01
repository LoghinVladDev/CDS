/*
 * Created by loghin on 27.01.2021.
 */

#ifndef __CDS_REFERENCE_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_REFERENCE_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/meta/FunctionTraits>

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template < typename __ElementType >             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            constexpr auto __referenceImplicitCastCheck (   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __ElementType & value
            ) noexcept -> __ElementType & {

                return value;
            }


            template < typename __ElementType >             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            constexpr auto __referenceImplicitCastCheck (   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __ElementType && value
            ) noexcept -> void = delete;


            template <
                    typename __ElementType,                         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename __ReferredValueType,                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    typename = void
            > struct __ReferableTo : cds :: meta :: FalseType {};   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */


            template < typename __ElementType, typename __ReferredValueType >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __ReferableTo <                                              /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __ElementType,
                    __ReferredValueType,
                    cds :: meta :: Void <
                            decltype ( __referenceImplicitCastCheck < __ElementType > ( cds :: meta :: valueOf < __ReferredValueType > () ) )
                    >
            > : cds :: meta :: TrueType {

            };


            template < typename __ElementType, bool = cds :: meta :: isCallable < __ElementType > () >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __ReturnOfUnsafe {                                                                   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                using Type = void;
            };


            template < typename __ElementType >                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __ReturnOfUnsafe < __ElementType, true > {   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                using Type = cds :: meta :: ReturnOf < __ElementType >;
            };

        } /* namespace __impl */
    } /* namespace __hidden */

    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    class Reference : public Object {

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        __ElementType * _pObject { nullptr };

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template <
                typename __ReferredValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                cds :: meta :: EnableIf <
                        cds :: __hidden :: __impl :: __ReferableTo <
                                __ElementType,
                                __ReferredValueType
                        > :: value &&
                        ! cds :: meta :: isSame <
                                Reference,
                                cds :: meta :: RemoveConst < cds :: meta :: RemoveReference < __ElementType > >
                        > ()
                > = 0
        > __CDS_Implicit constexpr Reference ( /* NOLINT(*-explicit-*, *-forwarding-reference-overload) */
                __ReferredValueType && value
        ) noexcept ( noexcept ( cds :: __hidden :: __impl :: __referenceImplicitCastCheck < __ElementType > ( std :: forward < __ReferredValueType > ( value ) ) ) );

    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr Reference (
                Reference const & reference
        ) noexcept = default;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr Reference (
                Reference && reference
        ) noexcept = default;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_ConstexprDestructor ~Reference () noexcept = default;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                Reference const & reference
        ) noexcept -> Reference & = default;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                Reference && reference
        ) noexcept -> Reference & = default;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_Explicit constexpr operator __ElementType & () const noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr auto get () const noexcept -> __ElementType &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr auto operator -> () const noexcept -> __ElementType *;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr auto operator == (
                Reference const & reference
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr auto operator != (
                Reference const & reference
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr auto operator == (
                __ElementType const & element
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr auto operator != (
                __ElementType const & element
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto equals (
                Object const & object
        ) const noexcept -> bool override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto toString () const noexcept -> String override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto hash () const noexcept -> Size override;

    public:                                         /* NOLINT(readability-redundant-access-specifiers) */
        template < typename ... __ArgumentTypes >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto operator () (
                __ArgumentTypes && ... arguments
        ) noexcept ( noexcept (
                ( * this->_pObject ) ( std :: forward < __ArgumentTypes > ( arguments ) ... )
        ) ) -> typename __hidden :: __impl :: __ReturnOfUnsafe < __ElementType > :: Type;
    };

} /* namespace cds */

#include "reference/impl/Reference.hpp"

#endif /* __CDS_REFERENCE_HPP__ */
