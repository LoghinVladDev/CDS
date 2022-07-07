//
// Created by loghin on 7/2/22.
//

#ifndef __CDS_EX_ARRAY_IMPL_HPP__
#define __CDS_EX_ARRAY_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto Array < __ElementType > :: __cicch_obtainGenericHandler (
                __hidden :: __impl :: __CollectionInternalRequestType requestType
        ) noexcept -> void ( Collection < __ElementType > :: * ) () {

            return this->__ls_handlers() [ static_cast < uint32 > ( requestType ) ];
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto Array < __ElementType > :: __cicch_obtainGenericConstHandler (
                __hidden :: __impl :: __CollectionInternalRequestType requestType
        ) const noexcept -> void ( Collection < __ElementType > :: * ) () const {

            return this->__ls_constHandlers() [ static_cast < uint32 > ( requestType ) ];
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr Array < __ElementType > :: Array () noexcept = default;


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        Array < __ElementType > :: ~Array () noexcept {

            this->__a_clear ( true );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto Array < __ElementType > :: begin () noexcept -> Iterator {

            return this->__a_begin();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto Array < __ElementType > :: end () noexcept -> Iterator {

            return this->__a_end();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto Array < __ElementType > :: begin () const noexcept -> ConstIterator {

            return this->__a_cbegin();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto Array < __ElementType > :: end () const noexcept -> ConstIterator {

            return this->__a_cend();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto Array < __ElementType > :: cbegin () const noexcept -> ConstIterator {

            return this->__a_cbegin();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto Array < __ElementType > :: cend () const noexcept -> ConstIterator {

            return this->__a_cend();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto Array < __ElementType > :: rbegin () noexcept -> ReverseIterator {

            return this->__a_rbegin();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto Array < __ElementType > :: rend () noexcept -> ReverseIterator {

            return this->__a_rend();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto Array < __ElementType > :: rbegin () const noexcept -> ConstReverseIterator {

            return this->__a_crbegin();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto Array < __ElementType > :: rend () const noexcept -> ConstReverseIterator {

            return this->__a_crend();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto Array < __ElementType > :: crbegin () const noexcept -> ConstReverseIterator {

            return this->__a_crbegin();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto Array < __ElementType > :: crend () const noexcept -> ConstReverseIterator {

            return this->__a_crend();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Array < __ElementType > :: clear () noexcept -> void {

            this->__a_clear ( false );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto Array < __ElementType > :: size () const noexcept -> Size {

            return this->__a_size ();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Array < __ElementType > :: popFront () noexcept -> void {

            this->__a_remove (0);
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Array < __ElementType > :: popBack () noexcept -> void {

            this->__a_remove ( this->__a_size () - 1ULL );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto Array < __ElementType > :: front () noexcept (false) -> ElementType & {

            if ( this->empty() ) {
                throw OutOfBoundsException ( "Array is Empty" );
            }

            return * this->__a_get ( 0 );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto Array < __ElementType > :: front () const noexcept (false) -> ElementType const & {

            if ( this->empty() ) {
                throw OutOfBoundsException ( "Array is Empty" );
            }

            return * this->__a_get ( 0 );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto Array < __ElementType > :: back () noexcept (false) -> ElementType & {

            if ( this->empty() ) {
                throw OutOfBoundsException ( "Array is Empty" );
            }

            return * this->__a_get ( this->__a_size () - 1ULL );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto Array < __ElementType > :: back () const noexcept (false) -> ElementType const & {

            if ( this->empty() ) {
                throw OutOfBoundsException ( "Array is Empty" );
            }

            return * this->__a_get ( this->__a_size () - 1ULL );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto Array < __ElementType > :: get (
                Index index
        ) noexcept (false) -> ElementType & {

            if ( this->empty() ) {
                throw OutOfBoundsException ( index, 0 );
            }

            return * this->__a_get ( this->circularAdjustedIndex ( index ) );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto Array < __ElementType > :: get (
                Index index
        ) const noexcept (false) -> ElementType const & {

            if ( this->empty() ) {
                throw OutOfBoundsException ( index, 0 );
            }

            return * this->__a_get ( this->circularAdjustedIndex ( index ) );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        auto Array < __ElementType > :: removeAt (
                Index index
        ) noexcept -> bool {

            if ( this->empty() ) {
                return false;
            }

            this->__a_remove ( this->circularAdjustedIndex ( index ) );
            return true;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Array < __ElementType > :: __newAddress (
                __ElementType const * pReferenceElement,
                bool                * pNewElementCreated
        ) noexcept -> ElementType * {
            (void) pReferenceElement;

            * pNewElementCreated = true;
            return this->__a_newBack ();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Array < __ElementType > :: __newFront () noexcept -> ElementType * {

            return this->__a_newFront ();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Array < __ElementType > :: __newBack () noexcept -> ElementType * {

            return this->__a_newBack ();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Array < __ElementType > :: __newFrontArray (
                Size            count,
                ElementType  ** ppElements
        ) noexcept -> void {

            return this->__a_newFrontArray (
                    count,
                    ppElements
            );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Array < __ElementType > :: __newBackArray (
                Size            count,
                ElementType  ** ppElements
        ) noexcept -> void {

            return this->__a_newBackArray (
                    count,
                    ppElements
            );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Array < __ElementType > :: __remove (
                __hidden :: __impl :: __DelegateIterator < __ElementType, AddressIterator < __ElementType > > const * pDelegate
        ) noexcept -> bool {

            return this->__a_remove ( pDelegate->iterator() );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Array < __ElementType > :: __removeConst (
                __hidden :: __impl :: __DelegateIterator < __ElementType const, AddressIterator < __ElementType const > > const * pDelegate
        ) noexcept -> bool {

            return this->__a_remove ( pDelegate->iterator() );
        }

    }
}

#endif // __CDS_EX_ARRAY_IMPL_HPP__
