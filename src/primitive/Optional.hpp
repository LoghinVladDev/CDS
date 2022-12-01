/*
 * Created by loghin on 26.01.2021.
 */

#ifndef __CDS_OPTIONAL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_OPTIONAL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/memory/SharedPointer>
#include <CDS/meta/FunctionTraits>
#include <CDS/exception/NoSuchElementException>

namespace cds {

    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    class Optional : public Object {

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        SharedPointer < __ElementType > _pObject { nullptr };

    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr Optional () noexcept = default;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        Optional (
                Optional const & optional
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr Optional (
                Optional && optional
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_Implicit Optional ( /* NOLINT(*-explicit-*) */
                __ElementType const & element
        ) noexcept ( noexcept ( __ElementType ( element ) ) );

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_Implicit Optional ( /* NOLINT(*-explicit-*) */
                __ElementType && element
        ) noexcept ( noexcept ( __ElementType ( std :: move ( element ) ) ) );

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_ConstexprDestructor ~Optional () noexcept override = default;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                Optional const & optional
        ) noexcept -> Optional &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                Optional && optional
        ) noexcept -> Optional &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                __ElementType const & element
        ) noexcept ( noexcept ( __ElementType ( element ) ) ) -> Optional &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                __ElementType && element
        ) noexcept ( noexcept ( __ElementType ( std :: move ( element ) ) ) ) -> Optional &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr static auto empty () noexcept -> Optional;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard static auto of (
                __ElementType const & element
        ) noexcept ( noexcept ( __ElementType ( element ) ) ) -> Optional;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard static auto of (
                __ElementType && element
        ) noexcept ( noexcept ( __ElementType ( std :: move ( element ) ) ) ) -> Optional;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr auto isPresent () const noexcept -> bool;

    public:                                 /* NOLINT(readability-redundant-access-specifiers) */
        template < typename __Consumer >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto ifPresent (
                __Consumer const & consumer
        ) const noexcept ( noexcept ( consumer ( cds :: meta :: referenceOf < __ElementType > () ) ) ) -> void;

    public:                                 /* NOLINT(readability-redundant-access-specifiers) */
        template < typename __Predicate >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        __CDS_NoDiscard auto filter (
                __Predicate const & predicate
        ) const noexcept ( noexcept ( predicate ( cds :: meta :: referenceOf < __ElementType > () ) ) ) -> Optional < __ElementType >;

    public:                             /* NOLINT(readability-redundant-access-specifiers) */
        template < typename __Mapper >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        __CDS_NoDiscard auto map (
                __Mapper const & mapper
        ) const noexcept ( noexcept ( mapper ( cds :: meta :: referenceOf < __ElementType > () ) ) ) -> Optional < cds :: meta :: ReturnOf < __Mapper > >;

    public:                             /* NOLINT(readability-redundant-access-specifiers) */
        template < typename __Mapper >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        __CDS_NoDiscard auto flatMap (
                __Mapper const & mapper
        ) const noexcept ( noexcept ( mapper ( * this ) ) ) -> Optional < cds :: meta :: ReturnOf < __Mapper > >;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto get () const noexcept (false) -> __ElementType &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto operator * () const noexcept (false) -> __ElementType &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto operator -> () const noexcept (false) -> __ElementType *;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto orElse (
                __ElementType & element
        ) const noexcept -> __ElementType &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto orElse (
                __ElementType const & element
        ) const noexcept -> __ElementType const &;

    public:                                 /* NOLINT(readability-redundant-access-specifiers) */
        template < typename __Supplier >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        __CDS_NoDiscard auto orElseGet (
                __Supplier const & supplier
        ) const noexcept ( noexcept ( supplier () ) ) -> __ElementType;

    public:                                 /* NOLINT(readability-redundant-access-specifiers) */
        template <
                typename __Supplier,        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                cds :: meta :: EnableIf <
                        cds :: meta :: isDerivedFrom < cds :: meta :: ReturnOf < __Supplier >, std :: exception > ()
                > = 0
        > __CDS_NoDiscard auto orElseThrow (
                __Supplier const & supplier
        ) const noexcept (false) -> __ElementType &;

    public:                                     /* NOLINT(readability-redundant-access-specifiers) */
        template <
                typename __ExceptionType,       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                cds :: meta :: EnableIf <
                        cds :: meta :: isDerivedFrom < __ExceptionType, std :: exception > ()
                > = 0
        > __CDS_NoDiscard auto orElseThrow () const noexcept (false) -> __ElementType &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto equals (
                Object const & object
        ) const noexcept -> bool override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto toString () const noexcept -> String override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto hash () const noexcept -> Size override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr auto operator == (
                Optional const & optional
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr auto operator != (
                Optional const & optional
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr auto operator == (
                __ElementType const & element
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr auto operator != (
                __ElementType const & element
        ) const noexcept -> bool;
    };
    

    template < typename __ElementType, typename ... __ConstructionArguments >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_NoDiscard auto makeOptional (
            __ConstructionArguments && ... arguments
    ) noexcept ( noexcept ( __ElementType ( std :: forward < __ConstructionArguments > ( arguments ) ... ) ) ) -> Optional < __ElementType >;

} /* namespace cds */

#include "optional/impl/Optional.hpp"

#endif /* __CDS_OPTIONAL_HPP__ */
