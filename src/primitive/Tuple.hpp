//
// Created by loghin on 5/18/22.
//

#ifndef __CDS_TUPLE_HPP__
#define __CDS_TUPLE_HPP__

#include <CDS/Object>
#include <CDS/experimental/meta/TypeTraits>

#include "tuple/TupleNode.hpp"

namespace cds { // NOLINT(modernize-concat-nested-namespaces)

    template < typename ... __TypePack > // NOLINT(bugprone-reserved-identifier)
    class Tuple : public Object {

    public:
        __CDS_NoDiscard constexpr auto size () const noexcept -> Size {
            return sizeof ... ( __TypePack );
        }

    private:
        __hidden :: __impl :: __TupleNode < 0, __TypePack ... > node;

    public:
        Tuple () noexcept = default;

    public:
        Tuple (
                Tuple const & tuple
        ) noexcept = default;

    public:
        Tuple (
                Tuple && tuple
        ) noexcept = default;

    public:
        auto operator = (
                Tuple const & tuple
        ) noexcept -> Tuple & = default;

    public:
        auto operator = (
                Tuple && tuple
        ) noexcept -> Tuple & = default;

    public:
        template <
                typename ... __ConstructorTypePack, // NOLINT(bugprone-reserved-identifier)
                meta :: EnableIf < ( sizeof ... ( __ConstructorTypePack ) == sizeof ... ( __TypePack ) && sizeof ... ( __ConstructorTypePack ) > 1 ) > = 0
        > __CDS_Implicit Tuple ( __ConstructorTypePack && ... argumentPack ) noexcept : // NOLINT(google-explicit-constructor)
                node ( std :: forward < __ConstructorTypePack > ( argumentPack ) ... ) {

        }

    public:
        template <
                typename ... __ConstructorTypePack, // NOLINT(bugprone-reserved-identifier)
                meta :: EnableIf < (
                        sizeof ... ( __ConstructorTypePack ) == sizeof ... ( __TypePack ) && sizeof ... ( __ConstructorTypePack ) == 1 &&
                        ! meta :: isSame < __ConstructorTypePack ..., Tuple > ()
                ) > = 0
        > __CDS_Implicit Tuple ( __ConstructorTypePack && ... argumentPack ) noexcept : // NOLINT(google-explicit-constructor)
                node ( std :: forward < __ConstructorTypePack > ( argumentPack ) ... ) {

        }

    public:
        template < uint32 __index > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_NonConstConstexprMemberFunction auto get () noexcept -> typename __hidden :: __impl :: __TypeAt < __index, __TypePack ... > :: Type &;

    public:
        template < uint32 __index > // NOLINT(bugprone-reserved-identifier)
        constexpr auto get () const noexcept -> typename __hidden :: __impl :: __TypeAt < __index, __TypePack ... > :: Type const &;

    public:
        auto operator == (
                Tuple const & tuple
        ) const noexcept -> bool;

    public:
        auto operator != (
                Tuple const & tuple
        ) const noexcept -> bool;

    public:
        template < uint32 __index > // NOLINT(bugprone-reserved-identifier)
        using TypeOf = typename __hidden :: __impl :: __TypeAt < __index, __TypePack ... > :: Type;

    public:
        auto toString () const noexcept -> String override;

    public:
        auto hash () const noexcept -> Index override;
    };

}

#include "tuple/impl/TupleNode.hpp"
#include "tuple/impl/Tuple.hpp"

#endif // __CDS_TUPLE_HPP__
