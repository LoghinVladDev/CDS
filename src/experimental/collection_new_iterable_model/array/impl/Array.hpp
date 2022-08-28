/*
 * Created by loghin on 7/2/22.
 */

#ifndef __CDS_EX_ARRAY_IMPL_HPP__
#define __CDS_EX_ARRAY_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {

        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        __CDS_cpplang_ConstexprOverride auto Array < __ElementType > :: __cicch_obtainGenericHandler (
                __hidden :: __impl :: __CollectionInternalRequestType requestType
        ) noexcept -> __GenericHandler {

            return this->__ls_handlers() [ static_cast < uint32 > ( requestType ) ];
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        __CDS_cpplang_ConstexprOverride auto Array < __ElementType > :: __cicch_obtainGenericConstHandler (
                __hidden :: __impl :: __CollectionInternalRequestType requestType
        ) const noexcept -> __GenericConstHandler {

            return this->__ls_constHandlers() [ static_cast < uint32 > ( requestType ) ];
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr Array < __ElementType > :: Array () noexcept = default;


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        __CDS_OptimalInline Array < __ElementType > :: Array (
                Array const & array
        ) noexcept :
                Implementation ( array ) {

        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr Array < __ElementType > :: Array (
                Array && array
        ) noexcept :
                Implementation ( std :: move ( array ) ) {

        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        template <
                typename __IteratorType,    /* NOLINT(bugprone-reserved-identifier) */
                typename __TElementType,    /* NOLINT(bugprone-reserved-identifier) */
                cds :: meta :: EnableIf <
                        cds :: meta :: isCopyConstructible < __TElementType > ()
                >
        > __CDS_OptimalInline Array < __ElementType > :: Array (
                __IteratorType const & begin,
                __IteratorType const & end,
                Size                   count
        ) noexcept {

            this->pushBackAllOf (
                    begin,
                    end,
                    count
            );
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        template <
                typename __TElementType,    /* NOLINT(bugprone-reserved-identifier) */
                cds :: meta :: EnableIf <
                        cds :: meta :: isCopyConstructible < __TElementType > ()
                >
        > __CDS_OptimalInline Array < __ElementType > :: Array (
                std :: initializer_list < __ElementType > const & initializerList
        ) noexcept :
                Array (
                        initializerList.begin(),
                        initializerList.end(),
                        initializerList.size()
                ) {

        }


        template < typename __ElementType >     /* NOLINT(bugprone-reserved-identifier) */
        template <
                typename __TElementType, /* NOLINT(bugprone-reserved-identifier) */
                cds :: meta :: EnableIf <
                        cds :: meta :: isDefaultConstructible < __TElementType > ()
                >
        > __CDS_OptimalInline Array < __ElementType > :: Array (
                Size size
        ) noexcept {

            this->__a_resize ( size );
        }


        template < typename __ElementType >     /* NOLINT(bugprone-reserved-identifier) */
        template <
                typename __TElementType, /* NOLINT(bugprone-reserved-identifier) */
                cds :: meta :: EnableIf <
                        cds :: meta :: isCopyConstructible < __TElementType > ()
                >
        > __CDS_OptimalInline Array < __ElementType > :: Array (
                Size                    size,
                __ElementType   const & defaultValue
        ) noexcept {

            this->__a_resize (
                    size,
                    defaultValue
            );
        }


        template < typename __ElementType >     /* NOLINT(bugprone-reserved-identifier) */
        template < typename __IterableType >    /* NOLINT(bugprone-reserved-identifier) */
        __CDS_OptimalInline Array < __ElementType > :: Array (
                __IterableType const & iterable
        ) noexcept {

            this->pushBackAllOf ( iterable );
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        Array < __ElementType > :: ~Array () noexcept {

            this->__a_clear ( true );
        }


        template < typename __ElementType >     /* NOLINT(bugprone-reserved-identifier) */
        __CDS_OptimalInline auto Array < __ElementType > :: operator = (
                Array const & array
        ) noexcept -> Array & {

            if ( this == & array ) {
                return * this;
            }

            this->__a_copy ( array );
            return * this;
        }


        template < typename __ElementType >     /* NOLINT(bugprone-reserved-identifier) */
        __CDS_OptimalInline auto Array < __ElementType > :: operator = (
                Array && array
        ) noexcept -> Array & {

            if ( this == & array ) {
                return * this;
            }

            this->__a_move ( std :: move ( array ) );
            return * this;
        }


        template < typename __ElementType >     /* NOLINT(bugprone-reserved-identifier) */
        __CDS_OptimalInline auto Array < __ElementType > :: operator = (
                std :: initializer_list < __ElementType > const & initializerList
        ) noexcept -> Array & {

            this->clear ();
            this->pushBackAllOf ( initializerList );
            return * this;
        }


        template < typename __ElementType >     /* NOLINT(bugprone-reserved-identifier) */
        template < typename __IterableType >    /* NOLINT(bugprone-reserved-identifier) */
        __CDS_OptimalInline auto Array < __ElementType > :: operator = (
                __IterableType const & iterable
        ) noexcept -> Array & {

            if ( this == & iterable ) {
                return * this;
            }

            this->clear();
            this->pushBackAllOf ( iterable );
            return * this;
        }


        template < typename __ElementType >     /* NOLINT(bugprone-reserved-identifier) */
        __CDS_OptimalInline auto Array < __ElementType > :: reserve (
                Size size
        ) noexcept -> void {

            this->__a_reserve ( size );
        }


        template < typename __ElementType >     /* NOLINT(bugprone-reserved-identifier) */
        __CDS_OptimalInline auto Array < __ElementType > :: shrink (
                Size size
        ) noexcept -> void {

            this->__a_shrink ( size );
        }


        template < typename __ElementType >     /* NOLINT(bugprone-reserved-identifier) */
        template <
                typename __TElementType, /* NOLINT(bugprone-reserved-identifier) */
                cds :: meta :: EnableIf <
                        cds :: meta :: isDefaultConstructible < __TElementType > ()
                >
        > __CDS_OptimalInline auto Array < __ElementType > :: resize (
                Size size
        ) noexcept -> void {

            this->__a_resize ( size );
        }


        template < typename __ElementType >     /* NOLINT(bugprone-reserved-identifier) */
        template <
                typename __TElementType, /* NOLINT(bugprone-reserved-identifier) */
                cds :: meta :: EnableIf <
                        cds :: meta :: isCopyConstructible < __TElementType > ()
                >
        > __CDS_OptimalInline auto Array < __ElementType > :: resize (
                Size                    size,
                __ElementType   const & defaultValue
        ) noexcept -> void {

            this->__a_resize (
                    size,
                    defaultValue
            );
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        auto Array < __ElementType > :: clear () noexcept -> void {

            this->__a_clear ( false );
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        __CDS_cpplang_ConstexprOverride auto Array < __ElementType > :: size () const noexcept -> Size {

            return this->__a_size ();
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        auto Array < __ElementType > :: popFront () noexcept -> void {

            this->__a_remove (0);
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        auto Array < __ElementType > :: popBack () noexcept -> void {

            this->__a_remove ( this->__a_size () - 1ULL );
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        __CDS_cpplang_ConstexprOverride auto Array < __ElementType > :: front () noexcept (false) -> ElementType & {

            if ( this->empty() ) {
                throw OutOfBoundsException ( "Array is Empty" );
            }

            return * this->__a_get ( 0 );
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        __CDS_cpplang_ConstexprOverride auto Array < __ElementType > :: front () const noexcept (false) -> ElementType const & {

            if ( this->empty() ) {
                throw OutOfBoundsException ( "Array is Empty" );
            }

            return * this->__a_get ( 0 );
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        __CDS_cpplang_ConstexprOverride auto Array < __ElementType > :: back () noexcept (false) -> ElementType & {

            if ( this->empty() ) {
                throw OutOfBoundsException ( "Array is Empty" );
            }

            return * this->__a_get ( this->__a_size () - 1ULL );
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        __CDS_cpplang_ConstexprOverride auto Array < __ElementType > :: back () const noexcept (false) -> ElementType const & {

            if ( this->empty() ) {
                throw OutOfBoundsException ( "Array is Empty" );
            }

            return * this->__a_get ( this->__a_size () - 1ULL );
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        __CDS_cpplang_ConstexprOverride auto Array < __ElementType > :: get (
                Index index
        ) noexcept (false) -> ElementType & {

            if ( this->empty() ) {
                throw OutOfBoundsException ( index, 0 );
            }

            return * this->__a_get ( this->circularAdjustedIndex ( index ) );
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        __CDS_cpplang_ConstexprOverride auto Array < __ElementType > :: get (
                Index index
        ) const noexcept (false) -> ElementType const & {

            if ( this->empty() ) {
                throw OutOfBoundsException ( index, 0 );
            }

            return * this->__a_get ( this->circularAdjustedIndex ( index ) );
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        auto Array < __ElementType > :: removeAt (
                Index index
        ) noexcept -> bool {

            if ( this->empty() ) {
                return false;
            }

            this->__a_remove ( this->circularAdjustedIndex ( index ) );
            return true;
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        constexpr auto Array < __ElementType > :: data () const noexcept -> __ElementType const * {

            return this->__a_data();
        }


        template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier) */
        __CDS_cpplang_NonConstConstexprMemberFunction auto Array < __ElementType > :: data () noexcept -> __ElementType * {

            return this->__a_data();
        }

    }
}

#endif /* __CDS_EX_ARRAY_IMPL_HPP__ */
