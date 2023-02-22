/*
 * Created by loghin on 11.10.2021.
 */

#ifndef __CDS_UNION_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_UNION_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/Object>               /* NOLINT(llvm-include-order) */
#include <CDS/FunctionalInterface>
#include <CDS/exception/TypeException>

#include "union/VariadicUnion.hpp"

namespace cds {

    template < typename ... __Types > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    class Union : public Object, private __hidden :: __impl :: __VariadicUnion < __Types ... > {

    public: /* NOLINT(readability-redundant-access-specifiers) */
        Union () noexcept = default;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        Union (
                Union const & /* object */
        ) noexcept = default;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        Union (
                Union && /* object */
        ) noexcept = default;

    public:                                                                     /* NOLINT(readability-redundant-access-specifiers) */
        template <
                typename __ElementType,                                         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                cds :: meta :: EnableIf <
                        ! cds :: meta :: isSame < cds :: meta :: Decay < __ElementType >, Union < __Types ... > > ()
                > = 0
        > __CDS_Implicit __CDS_cpplang_ConstexprConstructorNonEmptyBody Union ( /* NOLINT(*-explicit-*, *-forwarding-reference-overload) */
                __ElementType && value
        ) noexcept;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_ConstexprDestructor ~Union () noexcept override = default;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                Union const & /* object */
        ) noexcept -> Union & = default;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                Union && /* object */
        ) noexcept -> Union & = default;

    public:                             /* NOLINT(readability-redundant-access-specifiers) */
        template <
                typename __ElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                cds :: meta :: EnableIf <
                        ! cds :: meta :: isSame < cds :: meta :: Decay < __ElementType >, Union < __Types ... > > ()
                > = 0
        > __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                __ElementType && value
        ) noexcept -> Union &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr auto index () const noexcept -> Size;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr auto empty () const noexcept -> bool;

    public:                                                                         /* NOLINT(readability-redundant-access-specifiers) */
        template < typename __ElementType, typename ... __ConstructionArguments >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto emplace (
                __ConstructionArguments && ... arguments
        ) noexcept ( noexcept ( __ElementType ( std :: forward < __ConstructionArguments > ( arguments ) ... ) ) ) -> typename __hidden :: __impl :: __UnionPackTypeTraits < __ElementType, __Types ... > :: __DirectInitType &;

    public:                                                                                                     /* NOLINT(readability-redundant-access-specifiers) */
        template < typename __ElementType, typename __ListElementType, typename ... __ConstructionArguments >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto emplace (
                std :: initializer_list < __ListElementType > const &       list,
                __ConstructionArguments                            &&   ... arguments
        ) noexcept ( noexcept ( __ElementType ( list, std :: forward < __ConstructionArguments > ( arguments ) ... ) ) ) -> typename __hidden :: __impl :: __UnionPackTypeTraits < __ElementType, __Types ... > :: __DirectInitType &;

    public:                                                             /* NOLINT(readability-redundant-access-specifiers) */
        template < Size __index, typename ... __ConstructionArguments > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto emplace (
                __ConstructionArguments && ... arguments
        ) noexcept ( noexcept ( typename __hidden :: __impl :: __UnionPackIndexTraits < __index, __Types ... > :: __Type ( std :: forward < __ConstructionArguments > ( arguments ) ... ) ) ) -> typename __hidden :: __impl :: __UnionPackIndexTraits < __index, __Types ... > :: __Type &;

    public:                                                                                         /* NOLINT(readability-redundant-access-specifiers) */
        template < Size __index, typename __ListElementType, typename ... __ConstructionArguments > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto emplace (
                std :: initializer_list < __ListElementType > const &       list,
                __ConstructionArguments                            &&   ... arguments
        ) noexcept ( noexcept ( typename __hidden :: __impl :: __UnionPackIndexTraits < __index, __Types ... > :: __Type ( list, std :: forward < __ConstructionArguments > ( arguments ) ... ) ) ) -> typename __hidden :: __impl :: __UnionPackIndexTraits < __index, __Types ... > :: __Type &;

    public:                                 /* NOLINT(readability-redundant-access-specifiers) */
        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto get () const noexcept (false) -> typename __hidden :: __impl :: __UnionPackTypeTraits < __ElementType, __Types ... > :: __DirectInitType const &;

    public:                         /* NOLINT(readability-redundant-access-specifiers) */
        template < Size __index >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto get () const noexcept (false) -> typename __hidden :: __impl :: __UnionPackIndexTraits < __index, __Types ... > :: __Type const &;

    public:                                 /* NOLINT(readability-redundant-access-specifiers) */
        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto get () noexcept (false) -> typename __hidden :: __impl :: __UnionPackTypeTraits < __ElementType, __Types ... > :: __DirectInitType &;

    public:                         /* NOLINT(readability-redundant-access-specifiers) */
        template < Size __index >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto get () noexcept (false) -> typename __hidden :: __impl :: __UnionPackIndexTraits < __index, __Types ... > :: __Type &;

    public:                                 /* NOLINT(readability-redundant-access-specifiers) */
        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto getPointer () const noexcept -> typename __hidden :: __impl :: __UnionPackTypeTraits < __ElementType, __Types ... > :: __DirectInitType const *;

    public:                         /* NOLINT(readability-redundant-access-specifiers) */
        template < Size __index >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto getPointer () const noexcept -> typename __hidden :: __impl :: __UnionPackIndexTraits < __index, __Types ... > :: __Type const *;

    public:                                 /* NOLINT(readability-redundant-access-specifiers) */
        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto getPointer () noexcept -> typename __hidden :: __impl :: __UnionPackTypeTraits < __ElementType, __Types ... > :: __DirectInitType *;

    public:                         /* NOLINT(readability-redundant-access-specifiers) */
        template < Size __index >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto getPointer () noexcept -> typename __hidden :: __impl :: __UnionPackIndexTraits < __index, __Types ... > :: __Type *;

    public:                                 /* NOLINT(readability-redundant-access-specifiers) */
        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        __CDS_NoDiscard constexpr auto is () const noexcept -> bool;

    public:                         /* NOLINT(readability-redundant-access-specifiers) */
        template < Size __index >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        __CDS_NoDiscard constexpr auto is () const noexcept -> bool;

    public:                                                         /* NOLINT(readability-redundant-access-specifiers) */
        template < typename __ElementType, typename __Consumer >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        __CDS_cpplang_ConstexprConditioned auto ifIs (
                __Consumer const & consumer
        ) noexcept ( noexcept ( consumer ( cds :: meta :: referenceOf < typename __hidden :: __impl :: __UnionPackTypeTraits < __ElementType, __Types ... > :: __DirectInitType > () ) ) ) -> void;

    public:                                             /* NOLINT(readability-redundant-access-specifiers) */
        template < Size __index, typename __Consumer >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        __CDS_cpplang_ConstexprConditioned auto ifIs (
                __Consumer const & consumer
        ) noexcept ( noexcept ( consumer ( cds :: meta :: referenceOf < typename __hidden :: __impl :: __UnionPackIndexTraits < __index, __Types ... > :: __Type > () ) ) ) -> void;

    public:                                                         /* NOLINT(readability-redundant-access-specifiers) */
        template < typename __ElementType, typename __Consumer >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        __CDS_cpplang_ConstexprConditioned auto ifIs (
                __Consumer const & consumer
        ) const noexcept ( noexcept ( consumer ( cds :: meta :: referenceOf < typename __hidden :: __impl :: __UnionPackTypeTraits < __ElementType, __Types ... > :: __DirectInitType const > () ) ) ) -> void;

    public:                                             /* NOLINT(readability-redundant-access-specifiers) */
        template < Size __index, typename __Consumer >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        __CDS_cpplang_ConstexprConditioned auto ifIs (
                __Consumer const & consumer
        ) const noexcept ( noexcept ( consumer ( cds :: meta :: referenceOf < typename __hidden :: __impl :: __UnionPackIndexTraits < __index, __Types ... > :: __Type const > () ) ) ) -> void;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto toString () const noexcept -> String override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto hash () const noexcept -> Size override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto equals (
                Object const & object
        ) const noexcept -> bool override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr auto operator == (
                Union const & object
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr auto operator != (
                Union const & object
        ) const noexcept -> bool;

    public:                                 /* NOLINT(readability-redundant-access-specifiers) */
        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        __CDS_NoDiscard constexpr auto operator == (
                __ElementType const & object
        ) const noexcept -> bool;

    public:                                 /* NOLINT(readability-redundant-access-specifiers) */
        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        __CDS_NoDiscard constexpr auto operator != (
                __ElementType const & object
        ) const noexcept -> bool;
    };

} /* namespace cds */

#include "union/impl/Union.hpp"
#include "union/impl/VariadicUnion.hpp"

#endif /* __CDS_UNION_HPP__ */
