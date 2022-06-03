//
// Created by loghin on 5/23/22.
//

#ifndef __CDS_EX_TUPLE_NODE_IMPL_HPP__
#define __CDS_EX_TUPLE_NODE_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename ... TypePack >
        class Tuple;

        namespace hidden { // NOLINT(modernize-concat-nested-namespaces)
            namespace impl {

                template < uint32 index, typename ... TypePack >
                constexpr auto TupleNode < index, TypePack ... > :: operator == (
                        TupleNode const &
                ) const noexcept -> bool {
                    return true;
                }

                template < uint32 index, typename ... TypePack >
                constexpr auto TupleNode < index, TypePack ... > :: hash () const noexcept -> Index {
                    return 0;
                }

                template < uint32 index, typename CurrentType, typename ... RemainingTypes >
                template < typename CurrentConstructorType >
                TupleNode < index, CurrentType, RemainingTypes ... > :: TupleNode (
                        CurrentConstructorType && currentArgument
                ) noexcept :
                        data ( std :: forward < CurrentConstructorType > ( currentArgument ) ) {

                }

                template < uint32 index, typename CurrentType, typename ... RemainingTypes >
                template < typename CurrentConstructorType, typename ... RemainingConstructorTypes >
                TupleNode < index, CurrentType, RemainingTypes ... > :: TupleNode (
                        CurrentConstructorType      &&      currentArgument,
                        RemainingConstructorTypes   && ...  remainingArguments
                ) noexcept :
                        TupleNode < index + 1, RemainingTypes ... > ( std :: forward < RemainingConstructorTypes > ( remainingArguments ) ... ),
                        data ( std :: forward < CurrentConstructorType > ( currentArgument ) ) {

                }

                template < uint32 index, typename CurrentType, typename ... RemainingTypes >
                template < uint32 requestedIndex, meta :: EnableIf < requestedIndex == index > >
                __CDS_cpplang_NonConstConstexprMemberFunction auto TupleNode < index, CurrentType, RemainingTypes ... > :: get () noexcept -> CurrentType & {
                    return this->data;
                }

                template < uint32 index, typename CurrentType, typename ... RemainingTypes >
                template < uint32 requestedIndex, meta :: EnableIf < requestedIndex != index > >
                __CDS_cpplang_NonConstConstexprMemberFunction auto TupleNode < index, CurrentType, RemainingTypes ... > :: get () noexcept -> typename hidden :: impl :: TypeAt < requestedIndex - index, CurrentType, RemainingTypes ... > :: Type & {
                    return this->TupleNode < index + 1, RemainingTypes ... > :: template get < requestedIndex > ();
                }

                template < uint32 index, typename CurrentType, typename ... RemainingTypes >
                template < uint32 requestedIndex, meta :: EnableIf < requestedIndex == index > >
                constexpr auto TupleNode < index, CurrentType, RemainingTypes ... > :: get () const noexcept -> CurrentType const & {
                    return this->data;
                }

                template < uint32 index, typename CurrentType, typename ... RemainingTypes >
                template < uint32 requestedIndex, meta :: EnableIf < requestedIndex != index > >
                constexpr auto TupleNode < index, CurrentType, RemainingTypes ... > :: get () const noexcept -> typename hidden :: impl :: TypeAt < requestedIndex - index, CurrentType, RemainingTypes ... > :: Type const & {
                    return this->TupleNode < index + 1, RemainingTypes ... > :: template get < requestedIndex > ();
                }

                template < uint32 index, typename CurrentType, typename ... RemainingTypes >
                auto TupleNode < index, CurrentType, RemainingTypes ... > :: operator == (
                        TupleNode const & node
                ) const noexcept -> bool {
                    return
                            this->data == node.data &&
                            this->TupleNode < index + 1, RemainingTypes ... > :: operator == ( node );
                }

                template < uint32 index, typename CurrentType, typename ... RemainingTypes >
                auto TupleNode < index, CurrentType, RemainingTypes ... > :: operator != (
                        TupleNode const & node
                ) const noexcept -> bool {
                    return
                            this->data != node.data ||
                            this->TupleNode < index + 1, RemainingTypes ... > :: operator != ( node );
                }

                template < uint32 index, typename CurrentType, typename ... RemainingTypes >
                template < uint32 size, meta :: EnableIf < size == 0 > >
                auto TupleNode < index, CurrentType, RemainingTypes ... > :: toString (
                        std :: ostream & out
                ) const noexcept -> void {
                    out << this->data;
                }

                template < uint32 index, typename CurrentType, typename ... RemainingTypes >
                template < uint32 size, meta :: EnableIf < size != 0 > >
                auto TupleNode < index, CurrentType, RemainingTypes ... > :: toString (
                        std :: ostream & out
                ) const noexcept -> void {
                    out << this->data << ", ";
                    this->TupleNode < index + 1, RemainingTypes ... > :: toString ( out );
                }

                template < uint32 index, typename CurrentType, typename ... RemainingTypes >
                auto TupleNode < index, CurrentType, RemainingTypes ... > :: hash () const noexcept -> Index {
                    return cds :: hash ( this->data ) + this->TupleNode < index + 1, RemainingTypes ... > :: hash ();
                }

            }
        }

    }
}

#endif // __CDS_EX_TUPLE_NODE_IMPL_HPP__
