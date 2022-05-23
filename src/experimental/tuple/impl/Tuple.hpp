//
// Created by loghin on 5/23/22.
//

#ifndef __CDS_EX_TUPLE_IMPL_HPP__
#define __CDS_EX_TUPLE_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename ... TypePack >
        template < uint32 index >
        __CDS_cpplang_NonConstConstexprMemberFunction auto Tuple < TypePack ... > :: get () noexcept -> typename hidden :: impl :: TypeAt < index, TypePack ... > :: Type & {
            return this->node.template get < index > ();
        }

        template < typename ... TypePack >
        template < uint32 index >
        constexpr auto Tuple < TypePack ... > :: get () const noexcept -> typename hidden :: impl :: TypeAt < index, TypePack ... > :: Type const & {
            return this->node.template get < index > ();
        }

        template < typename ... TypePack >
        inline auto Tuple < TypePack ... > :: operator == ( Tuple const & tuple ) const noexcept -> bool {
            return this->node == tuple.node;
        }

        template < typename ... TypePack >
        inline auto Tuple < TypePack ... > :: operator != ( Tuple const & tuple ) const noexcept -> bool {
            return this->node != tuple.node;
        }

        template < typename ... TypePack >
        inline auto Tuple < TypePack ... > :: toString () const noexcept -> String {
            std :: stringstream output;
            this->node.toString ( output << "( " );
            output << " )";
            return output.str();
        }

        template < typename ... TypePack >
        inline auto Tuple < TypePack ... > :: hash () const noexcept -> Index {
            return this->node.hash();
        }

    }
}

#endif // __CDS_EX_TUPLE_IMPL_HPP__
