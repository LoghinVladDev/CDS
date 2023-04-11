/*
 * Created by loghin on 5/18/22.
 */

#ifndef __CDS_TUPLE_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_TUPLE_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <CDS/Object>
#include <CDS/meta/TypeTraits>

#include "tuple/TupleNode.hpp"

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */

    template < typename ... __TypePack > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    class Tuple : public Object {

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard constexpr auto size () const noexcept -> Size {
            return sizeof ... ( __TypePack );
        }

    private:    /* NOLINT(readability-redundant-access-specifiers) */
        __hidden :: __impl :: __TupleNode < 0, __TypePack ... > node;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        Tuple () noexcept = default;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        Tuple (
                Tuple const & tuple
        ) noexcept = default;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        Tuple (
                Tuple && tuple
        ) noexcept = default;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                Tuple const & tuple
        ) noexcept -> Tuple & = default;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator = (
                Tuple && tuple
        ) noexcept -> Tuple & = default;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template <
                typename ... __ConstructorTypePack, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                meta :: EnableIf < ( sizeof ... ( __ConstructorTypePack ) == sizeof ... ( __TypePack ) && sizeof ... ( __ConstructorTypePack ) > 1 ) > = 0
        > __CDS_Implicit Tuple ( __ConstructorTypePack && ... argumentPack ) noexcept : /* NOLINT(*-explicit-*) */
                node ( std :: forward < __ConstructorTypePack > ( argumentPack ) ... ) {

        }

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template <
                typename ... __ConstructorTypePack, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                meta :: EnableIf < (
                        sizeof ... ( __ConstructorTypePack ) == sizeof ... ( __TypePack ) && sizeof ... ( __ConstructorTypePack ) == 1 &&
                        ! meta :: isSame < __ConstructorTypePack ..., Tuple > ()
                ) > = 0
        > __CDS_Implicit Tuple ( __ConstructorTypePack && ... argumentPack ) noexcept : /* NOLINT(*-explicit-*) */
                node ( std :: forward < __ConstructorTypePack > ( argumentPack ) ... ) {

        }

    public: /* NOLINT(readability-redundant-access-specifiers) */
        ~Tuple () noexcept override = default;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template < uint32 __index > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto get () noexcept -> typename __hidden :: __impl :: __TypeAt < __index, __TypePack ... > :: Type &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template < uint32 __index > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto get () const noexcept -> typename __hidden :: __impl :: __TypeAt < __index, __TypePack ... > :: Type const &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator == (
                Tuple const & tuple
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        auto operator != (
                Tuple const & tuple
        ) const noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        template < uint32 __index > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        using TypeOf = typename __hidden :: __impl :: __TypeAt < __index, __TypePack ... > :: Type;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto toString () const noexcept -> String override;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard auto hash () const noexcept -> Size override;
    };


    template <typename ... __TypePack> /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_NoDiscard auto makeTuple (__TypePack && ... members) noexcept -> Tuple <
            meta::Decay <meta::RemoveReference <__TypePack>> ...
    >;

} /* namespace cds */

#include "tuple/impl/CTAD.hpp"
#include "tuple/impl/Tuple.hpp"
#include "tuple/impl/TupleNode.hpp"

#endif /* __CDS_TUPLE_HPP__ */
