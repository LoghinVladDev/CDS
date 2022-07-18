//
// Created by loghin on 17/07/22.
//

#ifndef __CDS_EX_LINKED_LIST_IMPL_HPP__
#define __CDS_EX_LINKED_LIST_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto LinkedList < __ElementType > :: __cicch_obtainGenericHandler (
                __hidden :: __impl :: __CollectionInternalRequestType requestType
        ) noexcept -> void ( Collection < __ElementType > :: * ) () {

            return this->__ls_handlers() [ static_cast < uint32 > ( requestType ) ];
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto LinkedList < __ElementType > :: __cicch_obtainGenericConstHandler (
                __hidden :: __impl :: __CollectionInternalRequestType requestType
        ) const noexcept -> void ( Collection < __ElementType > :: * ) () const {

            return this->__ls_constHandlers() [ static_cast < uint32 > ( requestType ) ];
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr LinkedList < __ElementType > :: LinkedList () noexcept = default;


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template <
                typename __TElementType,    // NOLINT(bugprone-reserved-identifier)
                cds :: meta :: EnableIf <
                        cds :: meta :: isCopyConstructible < __TElementType > ()
                >
        > __CDS_OptimalInline LinkedList < __ElementType > :: LinkedList (
                LinkedList const & list
        ) noexcept :
                Implementation ( list ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr LinkedList < __ElementType > :: LinkedList (
                LinkedList && list
        ) noexcept :
                Implementation ( std :: move ( list ) ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template <
                typename __IteratorType,    // NOLINT(bugprone-reserved-identifier)
                typename __TElementType,    // NOLINT(bugprone-reserved-identifier)
                cds :: meta :: EnableIf <
                        cds :: meta :: isCopyConstructible < __TElementType > ()
                >
        > __CDS_OptimalInline LinkedList < __ElementType > :: LinkedList (
                __IteratorType const & begin,
                __IteratorType const & end
        ) noexcept {

            this->pushBackAllOf (
                    begin,
                    end
            );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        template <
                typename __TElementType,    // NOLINT(bugprone-reserved-identifier)
                cds :: meta :: EnableIf <
                        cds :: meta :: isCopyConstructible < __TElementType > ()
                >
        > __CDS_OptimalInline LinkedList < __ElementType > :: LinkedList (
                std :: initializer_list < __ElementType > const & initializerList
        ) noexcept :
                LinkedList (
                        initializerList.begin(),
                        initializerList.end()
                ) {

        }


        template < typename __ElementType >     // NOLINT(bugprone-reserved-identifier)
        template <
                typename __OtherElementType,    // NOLINT(bugprone-reserved-identifier)
                cds :: meta :: EnableIf <
                        cds :: meta :: isConvertible < __OtherElementType, __ElementType > ()
                >
        > __CDS_OptimalInline LinkedList < __ElementType > :: LinkedList (
                Collection < __OtherElementType > const & collection
        ) noexcept :
                LinkedList (
                        collection.begin(),
                        collection.end()
                ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        LinkedList < __ElementType > :: ~LinkedList () noexcept {

            this->__dll_clear ();
        }


        template < typename __ElementType >     // NOLINT(bugprone-reserved-identifier)
        template <
                typename __TElementType, // NOLINT(bugprone-reserved-identifier)
                cds :: meta :: EnableIf <
                        cds :: meta :: isCopyConstructible < __TElementType > ()
                >
        > __CDS_OptimalInline auto LinkedList < __ElementType > :: operator = (
                LinkedList const & list
        ) noexcept -> LinkedList & {

            if ( this == & list ) {
                return * this;
            }

            this->__dll_copy ( list );
            return * this;
        }


        template < typename __ElementType >     // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto LinkedList < __ElementType > :: operator = (
                LinkedList && list
        ) noexcept -> LinkedList & {

            if ( this == & list ) {
                return * this;
            }

            this->__dll_move ( std :: move ( list ) );
            return * this;
        }


        template < typename __ElementType >     // NOLINT(bugprone-reserved-identifier)
        template <
                typename __OtherElementType, // NOLINT(bugprone-reserved-identifier)
                cds :: meta :: EnableIf <
                        cds :: meta :: isConvertible < __OtherElementType, __ElementType > ()
                >
        > __CDS_OptimalInline auto LinkedList < __ElementType > :: operator = (
                Collection < __OtherElementType > const & collection
        ) noexcept -> LinkedList & {

            if ( this == & collection ) {
                return * this;
            }

            this->clear();
            this->pushBackAllOf ( collection );
            return * this;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto LinkedList < __ElementType > :: begin () noexcept -> Iterator {

            return this->__dll_begin();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto LinkedList < __ElementType > :: end () noexcept -> Iterator {

            return this->__dll_end();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto LinkedList < __ElementType > :: begin () const noexcept -> ConstIterator {

            return this->__dll_cbegin();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto LinkedList < __ElementType > :: end () const noexcept -> ConstIterator {

            return this->__dll_cend();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto LinkedList < __ElementType > :: cbegin () const noexcept -> ConstIterator {

            return this->__dll_cbegin();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto LinkedList < __ElementType > :: cend () const noexcept -> ConstIterator {

            return this->__dll_cend();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto LinkedList < __ElementType > :: rbegin () noexcept -> ReverseIterator {

            return this->__dll_rbegin();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto LinkedList < __ElementType > :: rend () noexcept -> ReverseIterator {

            return this->__dll_rend();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto LinkedList < __ElementType > :: rbegin () const noexcept -> ConstReverseIterator {

            return this->__dll_crbegin();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto LinkedList < __ElementType > :: rend () const noexcept -> ConstReverseIterator {

            return this->__dll_crend();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto LinkedList < __ElementType > :: crbegin () const noexcept -> ConstReverseIterator {

            return this->__dll_crbegin();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto LinkedList < __ElementType > :: crend () const noexcept -> ConstReverseIterator {

            return this->__dll_crend();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto LinkedList < __ElementType > :: clear () noexcept -> void {

            this->__dll_clear ();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto LinkedList < __ElementType > :: size () const noexcept -> Size {

            return this->__dll_size ();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto LinkedList < __ElementType > :: popFront () noexcept -> void {

            this->__dll_removeFront ();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto LinkedList < __ElementType > :: popBack () noexcept -> void {

            this->__dll_removeBack ();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto LinkedList < __ElementType > :: front () noexcept (false) -> ElementType & {

            if ( this->empty() ) {
                throw OutOfBoundsException ( "List is Empty" );
            }

            return * this->__dll_front ();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto LinkedList < __ElementType > :: front () const noexcept (false) -> ElementType const & {

            if ( this->empty() ) {
                throw OutOfBoundsException ( "List is Empty" );
            }

            return * this->__dll_front ();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto LinkedList < __ElementType > :: back () noexcept (false) -> ElementType & {

            if ( this->empty() ) {
                throw OutOfBoundsException ( "List is Empty" );
            }

            return * this->__dll_back ();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto LinkedList < __ElementType > :: back () const noexcept (false) -> ElementType const & {

            if ( this->empty() ) {
                throw OutOfBoundsException ( "List is Empty" );
            }

            return * this->__dll_back();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto LinkedList < __ElementType > :: get (
                Index index
        ) noexcept (false) -> ElementType & {

            if ( this->empty() ) {
                throw OutOfBoundsException ( index, 0 );
            }

            return * this->__dll_get ( this->circularAdjustedIndex ( index ) );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto LinkedList < __ElementType > :: get (
                Index index
        ) const noexcept (false) -> ElementType const & {

            if ( this->empty() ) {
                throw OutOfBoundsException ( index, 0 );
            }

            return * this->__dll_get ( this->circularAdjustedIndex ( index ) );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto LinkedList < __ElementType > :: removeAt (
                Index index
        ) noexcept -> bool {

            if ( this->empty() ) {
                return false;
            }

            this->__dll_removeAt ( this->circularAdjustedIndex ( index ) );
            return true;
        }

    }
}

#endif // __CDS_EX_LINKED_LIST_IMPL_HPP__
