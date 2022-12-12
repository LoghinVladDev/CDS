/* 
 * Created by loghin on 5/23/22.
 */

#ifndef __CDS_TUPLE_NODE_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_TUPLE_NODE_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */

    template < typename ... __TypePack > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    class Tuple;

    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */


            template < uint32 __index, typename ... __TypePack > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            constexpr auto __TupleNode < __index, __TypePack ... > :: operator == (
                    __TupleNode const &
            ) const noexcept -> bool {

                return true;
            }


            template < uint32 __index, typename ... __TypePack > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            constexpr auto __TupleNode < __index, __TypePack ... > :: hash () const noexcept -> Index {

                return 0;
            }


            template < uint32 __index, typename __CurrentType, typename ... __RemainingTypes > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            template < typename __CurrentConstructorType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __TupleNode < __index, __CurrentType, __RemainingTypes ... > :: __TupleNode (
                    __CurrentConstructorType && currentArgument
            ) noexcept :
                    data ( std :: forward < __CurrentConstructorType > ( currentArgument ) ) {

            }


            template < uint32 __index, typename __CurrentType, typename ... __RemainingTypes > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            template < typename __CurrentConstructorType, typename ... __RemainingConstructorTypes > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __TupleNode < __index, __CurrentType, __RemainingTypes ... > :: __TupleNode (
                    __CurrentConstructorType      &&      currentArgument,
                    __RemainingConstructorTypes   && ...  remainingArguments
            ) noexcept :
                    __TupleNode < __index + 1U, __RemainingTypes ... > ( std :: forward < __RemainingConstructorTypes > ( remainingArguments ) ... ),
                    data ( std :: forward < __CurrentConstructorType > ( currentArgument ) ) {

            }


            template < uint32 __index, typename __CurrentType, typename ... __RemainingTypes > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            template < uint32 __requestedIndex, cds :: meta :: EnableIf < __requestedIndex == __index > > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_cpplang_NonConstConstexprMemberFunction auto __TupleNode < __index, __CurrentType, __RemainingTypes ... > :: get () noexcept -> __CurrentType & {

                return this->data;
            }


            template < uint32 __index, typename __CurrentType, typename ... __RemainingTypes > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            template < uint32 __requestedIndex, cds :: meta :: EnableIf < __requestedIndex != __index > > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            __CDS_cpplang_NonConstConstexprMemberFunction auto __TupleNode < __index, __CurrentType, __RemainingTypes ... > :: get () noexcept -> typename __hidden :: __impl :: __TypeAt < __requestedIndex - __index, __CurrentType, __RemainingTypes ... > :: Type & {

                return this-> __TupleNode < __index + 1, __RemainingTypes ... > :: template get < __requestedIndex > ();
            }


            template < uint32 __index, typename __CurrentType, typename ... __RemainingTypes > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            template < uint32 __requestedIndex, cds :: meta :: EnableIf < __requestedIndex == __index > > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            constexpr auto __TupleNode < __index, __CurrentType, __RemainingTypes ... > :: get () const noexcept -> __CurrentType const & {

                return this->data;
            }


            template < uint32 __index, typename __CurrentType, typename ... __RemainingTypes > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            template < uint32 __requestedIndex, cds :: meta :: EnableIf < __requestedIndex != __index > > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            constexpr auto __TupleNode < __index, __CurrentType, __RemainingTypes ... > :: get () const noexcept -> typename __hidden :: __impl :: __TypeAt < __requestedIndex - __index, __CurrentType, __RemainingTypes ... > :: Type const & {

                return this-> __TupleNode < __index + 1U, __RemainingTypes ... > :: template get < __requestedIndex > ();
            }


            template < uint32 __index, typename __CurrentType, typename ... __RemainingTypes > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            auto __TupleNode < __index, __CurrentType, __RemainingTypes ... > :: operator == (
                    __TupleNode const & node
            ) const noexcept -> bool {

                return
                        this->data == node.data &&
                        this-> __TupleNode < __index + 1, __RemainingTypes ... > :: operator == ( node );
            }


            template < uint32 __index, typename __CurrentType, typename ... __RemainingTypes > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            auto __TupleNode < __index, __CurrentType, __RemainingTypes ... > :: operator != (
                    __TupleNode const & node
            ) const noexcept -> bool {

                return
                        this->data != node.data ||
                        this-> __TupleNode < __index + 1U, __RemainingTypes ... > :: operator != ( node );
            }


            template < uint32 __index, typename __CurrentType, typename ... __RemainingTypes > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            template < uint32 __size, cds :: meta :: EnableIf < __size == 0 > > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            auto __TupleNode < __index, __CurrentType, __RemainingTypes ... > :: toString (
                    std :: ostream & out
            ) const noexcept -> void {

                out << this->data;
            }


            template < uint32 __index, typename __CurrentType, typename ... __RemainingTypes > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            template < uint32 __size, cds :: meta :: EnableIf < __size != 0 > > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            auto __TupleNode < __index, __CurrentType, __RemainingTypes ... > :: toString (
                    std :: ostream & out
            ) const noexcept -> void {

                out << this->data << ", ";
                this-> __TupleNode < __index + 1U, __RemainingTypes ... > :: toString ( out );
            }


            template < uint32 __index, typename __CurrentType, typename ... __RemainingTypes > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            auto __TupleNode < __index, __CurrentType, __RemainingTypes ... > :: hash () const noexcept -> Index {

                return cds :: hash ( this->data ) + this-> __TupleNode < __index + 1U, __RemainingTypes ... > :: hash ();
            }

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_TUPLE_NODE_IMPL_HPP__ */
