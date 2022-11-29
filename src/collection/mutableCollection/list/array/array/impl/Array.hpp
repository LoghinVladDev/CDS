/* NOLINT(llvm-header-guard)
 * Created by loghin on 7/2/22.
 */

#ifndef __CDS_ARRAY_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_ARRAY_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {

    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_cpplang_ConstexprOverride auto Array < __ElementType > :: __cicch_obtainGenericHandler (
            __hidden :: __impl :: __CollectionInternalRequestType requestType
    ) noexcept -> __GenericHandler {

        return this->__ls_handlers() [ static_cast < uint32 > ( requestType ) ];
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_cpplang_ConstexprOverride auto Array < __ElementType > :: __cicch_obtainGenericConstHandler (
            __hidden :: __impl :: __CollectionInternalRequestType requestType
    ) const noexcept -> __GenericConstHandler {

        return this->__ls_constHandlers() [ static_cast < uint32 > ( requestType ) ];
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline Array < __ElementType > :: Array (
            Array const & array
    ) noexcept :
            Implementation ( array ) {

    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    constexpr Array < __ElementType > :: Array (
            Array && array
    ) noexcept :
            Implementation ( std :: move ( array ) ) {

    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    template <
            typename __IteratorType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __TElementType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    template <
            typename __TElementType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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


    template < typename __ElementType >     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    template <
            typename __TElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            cds :: meta :: EnableIf <
                    cds :: meta :: isDefaultConstructible < __TElementType > ()
            >
    > __CDS_OptimalInline Array < __ElementType > :: Array (
            Size size
    ) noexcept {

        this->__ab_resize ( size );
    }


    template < typename __ElementType >     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    template <
            typename __TElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            cds :: meta :: EnableIf <
                    cds :: meta :: isCopyConstructible < __TElementType > ()
            >
    > __CDS_OptimalInline Array < __ElementType > :: Array (
            Size                    size,
            __ElementType   const & defaultValue
    ) noexcept {

        this->__ab_resize (
                size,
                defaultValue
        );
    }


    template < typename __ElementType >     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    template < typename __IterableType >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline Array < __ElementType > :: Array (
            __IterableType const & iterable
    ) noexcept {

        this->pushBackAllOf ( iterable );
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    Array < __ElementType > :: ~Array () noexcept {

        this->__ab_clear ( true );
    }


    template < typename __ElementType >     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto Array < __ElementType > :: operator = (
            Array const & array
    ) noexcept -> Array & {

        if ( this == & array ) {
            return * this;
        }

        this->__ab_copy ( array );
        return * this;
    }


    template < typename __ElementType >     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto Array < __ElementType > :: operator = (
            Array && array
    ) noexcept -> Array & {

        if ( this == & array ) {
            return * this;
        }

        this->__ab_move ( std :: move ( array ) );
        return * this;
    }


    template < typename __ElementType >     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto Array < __ElementType > :: operator = (
            std :: initializer_list < __ElementType > const & initializerList
    ) noexcept -> Array & {

        this->clear ();
        this->pushBackAllOf ( initializerList );
        return * this;
    }


    template < typename __ElementType >     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    template < typename __IterableType >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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


    template < typename __ElementType >     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_cpplang_ConstexprConditioned auto Array < __ElementType > :: operator == (
            Array const & array
    ) const noexcept -> bool {

        if ( this == & array ) {
            return true;
        }

        return this->__ab_equals ( array );
    }


    template < typename __ElementType >     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_cpplang_ConstexprConditioned auto Array < __ElementType > :: operator != (
            Array const & array
    ) const noexcept -> bool {

        if ( this == & array ) {
            return false;
        }

        return ! this->__ab_equals ( array ); /* NOLINT(clion-misra-cpp2008-5-3-1) */
    }


    template < typename __ElementType >     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto Array < __ElementType > :: reserve (
            Size size
    ) noexcept -> void {

        this->__ab_reserve ( size );
    }


    template < typename __ElementType >     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto Array < __ElementType > :: shrink (
            Size size
    ) noexcept -> void {

        this->__ab_shrink ( size );
    }


    template < typename __ElementType >     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    template <
            typename __TElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            cds :: meta :: EnableIf <
                    cds :: meta :: isDefaultConstructible < __TElementType > ()
            >
    > __CDS_OptimalInline auto Array < __ElementType > :: resize (
            Size size
    ) noexcept -> void {

        this->__ab_resize ( size );
    }


    template < typename __ElementType >     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    template <
            typename __TElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            cds :: meta :: EnableIf <
                    cds :: meta :: isCopyConstructible < __TElementType > ()
            >
    > __CDS_OptimalInline auto Array < __ElementType > :: resize (
            Size                    size,
            __ElementType   const & defaultValue
    ) noexcept -> void {

        this->__ab_resize (
                size,
                defaultValue
        );
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    auto Array < __ElementType > :: clear () noexcept -> void {

        this->__ab_clear ( false );
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_cpplang_ConstexprOverride auto Array < __ElementType > :: size () const noexcept -> Size {

        return this->__ab_size ();
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    auto Array < __ElementType > :: popFront () noexcept -> void {

        this->__ab_remove (0);
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    auto Array < __ElementType > :: popBack () noexcept -> void {

        this->__ab_remove ( this->__ab_size () - 1ULL );
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_cpplang_ConstexprOverride auto Array < __ElementType > :: front () noexcept (false) -> ElementType & {

        if ( this->empty() ) {
            throw OutOfBoundsException ( "Array is Empty" );
        }

        return * this->__ab_get ( 0 );
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_cpplang_ConstexprOverride auto Array < __ElementType > :: front () const noexcept (false) -> ElementType const & {

        if ( this->empty() ) {
            throw OutOfBoundsException ( "Array is Empty" );
        }

        return * this->__ab_get ( 0 );
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_cpplang_ConstexprOverride auto Array < __ElementType > :: back () noexcept (false) -> ElementType & {

        if ( this->empty() ) {
            throw OutOfBoundsException ( "Array is Empty" );
        }

        return * this->__ab_get ( this->__ab_size () - 1ULL );
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_cpplang_ConstexprOverride auto Array < __ElementType > :: back () const noexcept (false) -> ElementType const & {

        if ( this->empty() ) {
            throw OutOfBoundsException ( "Array is Empty" );
        }

        return * this->__ab_get ( this->__ab_size () - 1ULL );
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_cpplang_ConstexprOverride auto Array < __ElementType > :: get (
            Index index
    ) noexcept (false) -> ElementType & {

        if ( this->empty() ) {
            throw OutOfBoundsException ( index, 0 );
        }

        return * this->__ab_get ( this->circularAdjustedIndex ( index ) );
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_cpplang_ConstexprOverride auto Array < __ElementType > :: get (
            Index index
    ) const noexcept (false) -> ElementType const & {

        if ( this->empty() ) {
            throw OutOfBoundsException ( index, 0 );
        }

        return * this->__ab_get ( this->circularAdjustedIndex ( index ) );
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    auto Array < __ElementType > :: removeAt (
            Index index
    ) noexcept -> bool {

        if ( this->empty() ) {
            return false;
        }

        this->__ab_remove ( this->circularAdjustedIndex ( index ) );
        return true;
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    constexpr auto Array < __ElementType > :: data () const noexcept -> __ElementType const * {

        return this->__ab_data();
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_cpplang_NonConstConstexprMemberFunction auto Array < __ElementType > :: data () noexcept -> __ElementType * {

        return this->__ab_data();
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto Array < __ElementType > :: sort (
            cds :: Function < auto ( __ElementType const &, __ElementType const & ) -> bool > const & comparator
    ) noexcept -> void {

        return this->template sort < decltype ( comparator ) > ( comparator );
    }


    template < typename __ElementType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    template < typename __Comparator >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto Array < __ElementType > :: sort (
            __Comparator const & comparator
    ) noexcept -> void {

        return this->__ab_sort ( comparator );
    }

} /* namespace cds */

#endif /* __CDS_ARRAY_IMPL_HPP__ */
