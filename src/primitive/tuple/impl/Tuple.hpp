/*
 * Created by loghin on 5/23/22.
 */

#ifndef __CDS_TUPLE_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_TUPLE_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */

    template < typename ... __TypePack > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    template < uint32 __index > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto Tuple < __TypePack ... > :: get () noexcept -> typename __hidden :: __impl :: __TypeAt < __index, __TypePack ... > :: Type & {

        return this->node.template get < __index > ();
    }

    template < typename ... __TypePack > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    template < uint32 __index > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    constexpr auto Tuple < __TypePack ... > :: get () const noexcept -> typename __hidden :: __impl :: __TypeAt < __index, __TypePack ... > :: Type const & {

        return this->node.template get < __index > ();
    }

    template < typename ... __TypePack > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    inline auto Tuple < __TypePack ... > :: operator == (
            Tuple const & tuple
    ) const noexcept -> bool {

        return this->node == tuple.node;
    }

    template < typename ... __TypePack > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    inline auto Tuple < __TypePack ... > :: operator != (
            Tuple const & tuple
    ) const noexcept -> bool {

        return this->node != tuple.node;
    }

    template < typename ... __TypePack > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    inline auto Tuple < __TypePack ... > :: toString () const noexcept -> String {

        std :: stringstream output;
        this->node.toString ( output << "( " );
        output << " )";
        return output.str();
    }


    template < typename ... __TypePack > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    inline auto Tuple < __TypePack ... > :: hash () const noexcept -> Size {

        return this->node.hash();
    }


    template <typename ... __TypePack>
    __CDS_NoDiscard inline auto makeTuple (__TypePack && ... members) noexcept -> Tuple <
            meta::Decay <meta::RemoveReference <__TypePack>> ...
    > {

        return { std::forward <__TypePack> (members) ... };
    }

} /* namespace cds */

#endif /* __CDS_TUPLE_IMPL_HPP__ */
