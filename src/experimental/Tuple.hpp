//
// Created by loghin on 5/18/22.
//

#ifndef __CDS_EX_TUPLE_HPP__
#define __CDS_EX_TUPLE_HPP__

#include <CDS/experimental/Object>
#include <CDS/experimental/meta/TypeTraits>

#include "tuple/TupleNode.hpp"

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename ... TypePack >
        class Tuple : public Object {

        private:
            hidden :: impl :: TupleNode < 0, TypePack ... > node;

        public:
            Tuple () noexcept = default;
        public:
            Tuple ( Tuple const & ) noexcept = default;
        public:
            Tuple ( Tuple && ) noexcept = default;
        public:
            auto operator = ( Tuple const & ) noexcept -> Tuple & = default;
        public:
            auto operator = ( Tuple && ) noexcept -> Tuple & = default;

        public:
            template <
                    typename ... ConstructorTypePack,
                    meta :: EnableIf < ( sizeof ... ( ConstructorTypePack ) == sizeof ... ( TypePack ) && sizeof ... ( ConstructorTypePack ) > 1 ) > = 0
            > __CDS_implicit Tuple ( ConstructorTypePack && ... argumentPack ) noexcept : // NOLINT(google-explicit-constructor)
                    node ( std :: forward < ConstructorTypePack > ( argumentPack ) ... ) {

            }

        public:
            template <
                    typename ... ConstructorTypePack,
                    meta :: EnableIf < (
                            sizeof ... ( ConstructorTypePack ) == sizeof ... ( TypePack ) && sizeof ... ( ConstructorTypePack ) == 1 &&
                            ! isSame < ConstructorTypePack ..., Tuple > ()
                    ) > = 0
            > __CDS_implicit Tuple ( ConstructorTypePack && ... argumentPack ) noexcept : // NOLINT(google-explicit-constructor)
                    node ( std :: forward < ConstructorTypePack > ( argumentPack ) ... ) {

            }

        public:
            template < uint32 index >
            __CDS_cpplang_NonConstConstexprMemberFunction auto get () noexcept -> typename hidden :: impl :: TypeAt < index, TypePack ... > :: Type &;

        public:
            template < uint32 index >
            constexpr auto get () const noexcept -> typename hidden :: impl :: TypeAt < index, TypePack ... > :: Type const &;

        public:
            auto operator == ( Tuple const & tuple ) const noexcept -> bool;
        public:
            auto operator != ( Tuple const & tuple ) const noexcept -> bool;

        public:
            template < uint32 index >
            using TypeOf = typename hidden :: impl :: TypeAt < index, TypePack ... > :: Type;

        public:
            auto toString () const noexcept -> String override;

        public:
            auto hash () const noexcept -> Index override;
        };

    }
}
#include "tuple/impl/TupleNode.hpp"
#include "tuple/impl/Tuple.hpp"

#endif // __CDS_EX_TUPLE_HPP__
