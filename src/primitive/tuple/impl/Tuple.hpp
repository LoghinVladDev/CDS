//
// Created by loghin on 5/23/22.
//

#ifndef __CDS_TUPLE_IMPL_HPP__
#define __CDS_TUPLE_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)

    template < typename ... __TypePack > // NOLINT(bugprone-reserved-identifier)
    template < uint32 __index > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_NonConstConstexprMemberFunction auto Tuple < __TypePack ... > :: get () noexcept -> typename __hidden :: __impl :: __TypeAt < __index, __TypePack ... > :: Type & {

        return this->node.template get < __index > ();
    }

    template < typename ... __TypePack > // NOLINT(bugprone-reserved-identifier)
    template < uint32 __index > // NOLINT(bugprone-reserved-identifier)
    constexpr auto Tuple < __TypePack ... > :: get () const noexcept -> typename __hidden :: __impl :: __TypeAt < __index, __TypePack ... > :: Type const & {

        return this->node.template get < __index > ();
    }

    template < typename ... __TypePack > // NOLINT(bugprone-reserved-identifier)
    inline auto Tuple < __TypePack ... > :: operator == (
            Tuple const & tuple
    ) const noexcept -> bool {

        return this->node == tuple.node;
    }

    template < typename ... __TypePack > // NOLINT(bugprone-reserved-identifier)
    inline auto Tuple < __TypePack ... > :: operator != (
            Tuple const & tuple
    ) const noexcept -> bool {

        return this->node != tuple.node;
    }

    template < typename ... __TypePack > // NOLINT(bugprone-reserved-identifier)
    inline auto Tuple < __TypePack ... > :: toString () const noexcept -> String {

        std :: stringstream output;
        this->node.toString ( output << "( " );
        output << " )";
        return output.str();
    }

    template < typename ... __TypePack > // NOLINT(bugprone-reserved-identifier)
    inline auto Tuple < __TypePack ... > :: hash () const noexcept -> Size {

        return this->node.hash();
    }

}

#endif // __CDS_TUPLE_IMPL_HPP__
