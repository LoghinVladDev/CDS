/*
 * Created by loghin on 10/08/22.
 */

#ifndef __CDS_HASH_SET_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_HASH_SET_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {

    template <
            typename __ElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_cpplang_ConstexprOverride auto HashSet <
            __ElementType,
            __Hasher
    > :: __iicch_obtainGenericHandler (
            __hidden :: __impl :: __IterableInternalRequestType requestType
    ) noexcept -> __GenericHandler {

        return this->__ss_handlers() [ static_cast < uint32 > ( requestType ) ];
    }


    template <
            typename __ElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_cpplang_ConstexprOverride auto HashSet <
            __ElementType,
            __Hasher
    > :: __iicch_obtainGenericConstHandler (
            __hidden :: __impl :: __IterableInternalRequestType requestType
    ) const noexcept -> __GenericConstHandler {

        return this->__ss_constHandlers() [ static_cast < uint32 > ( requestType ) ];
    }


    template <
            typename __ElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > constexpr HashSet <
            __ElementType,
            __Hasher
    > :: HashSet () noexcept = default;


    template <
            typename __ElementType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_OptimalInline HashSet <
            __ElementType,
            __Hasher
    > :: HashSet (
            HashSet const & set
    ) noexcept {

        this->__ht_copyCleared (
                set,
                & cds :: __hidden :: __impl :: __hashSetCopyConstructor < __ElementType >
        );
    }


    template <
            typename __ElementType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > constexpr HashSet <
            __ElementType,
            __Hasher
    > :: HashSet (
            HashSet && set
    ) noexcept :
            Implementation ( std :: move ( set ) ) {

    }


    template <
            typename __ElementType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > constexpr HashSet <
            __ElementType,
            __Hasher
    > :: HashSet (
            __Hasher const & hasher
    ) noexcept :
            Implementation ( hasher ) {

    }


    template <
            typename __ElementType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > template <
            typename __IteratorType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __TElementType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            cds :: meta :: EnableIf <
                    cds :: meta :: isCopyConstructible < __TElementType > ()
            >
    > __CDS_OptimalInline HashSet <
            __ElementType,
            __Hasher
    > :: HashSet (
            __IteratorType const & begin,
            __IteratorType const & end,
            Size                   count
    ) noexcept {

        (void) count;
        for ( auto iterator = begin; iterator != end; ++ iterator ) {
            this->insert ( * iterator );
        }
    }


    template <
            typename __ElementType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > template <
            typename __IteratorType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __TElementType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            cds :: meta :: EnableIf <
                    cds :: meta :: isCopyConstructible < __TElementType > ()
            >
    > __CDS_OptimalInline HashSet <
            __ElementType,
            __Hasher
    > :: HashSet (
            __Hasher        const & hasher,
            __IteratorType  const & begin,
            __IteratorType  const & end,
            Size                    count
    ) noexcept :
            Implementation ( hasher ) {

        (void) count;
        for ( auto iterator = begin; iterator != end; ++ iterator ) {
            this->insert ( iterator );
        }
    }


    template <
            typename __ElementType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > template <
            typename __TElementType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            cds :: meta :: EnableIf <
                    cds :: meta :: isCopyConstructible < __TElementType > ()
            >
    > __CDS_OptimalInline HashSet <
            __ElementType,
            __Hasher
    > :: HashSet (
            std :: initializer_list < __ElementType > const & initializerList
    ) noexcept :
            HashSet (
                    initializerList.begin (),
                    initializerList.end (),
                    initializerList.size()
            ) {

    }


    template <
            typename __ElementType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > template <
            typename __TElementType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            cds :: meta :: EnableIf <
                    cds :: meta :: isCopyConstructible < __TElementType > ()
            >
    > __CDS_OptimalInline HashSet <
            __ElementType,
            __Hasher
    > :: HashSet (
            __Hasher                                    const & hasher,
            std :: initializer_list < __ElementType >   const & initializerList
    ) noexcept :
            HashSet (
                    hasher,
                    initializerList.begin (),
                    initializerList.end (),
                    initializerList.size()
            ) {

    }


    template <
            typename __ElementType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > template < typename __IterableType >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline HashSet <
            __ElementType,
            __Hasher
    > :: HashSet (
            __IterableType const & iterable
    ) noexcept :
            HashSet (
                    iterable.begin (),
                    iterable.end ()
            ) {

    }


    template <
            typename __ElementType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > template < typename __IterableType >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline HashSet <
            __ElementType,
            __Hasher
    > :: HashSet (
            __Hasher        const & hasher,
            __IterableType  const & iterable
    ) noexcept :
            HashSet (
                    hasher,
                    iterable.begin (),
                    iterable.end ()
            ) {

    }


    template <
            typename __ElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_OptimalInline HashSet <
            __ElementType,
            __Hasher
    > :: ~HashSet () noexcept {

        this->__ht_clear ();
    }


    template <
            typename __ElementType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_OptimalInline auto HashSet <
            __ElementType,
            __Hasher
    > :: operator = (
            HashSet const & set
    ) noexcept -> HashSet & {

        if ( this == & set ) {
            return * this;
        }

        this->__ht_copy (
                set,
                & cds :: __hidden :: __impl :: __hashSetCopyConstructor < __ElementType >
        );

        return * this;
    }


    template <
            typename __ElementType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_OptimalInline auto HashSet <
            __ElementType,
            __Hasher
    > :: operator = (
            HashSet && set
    ) noexcept -> HashSet & {

        if ( this == & set ) {
            return * this;
        }

        this->__ht_move ( std :: move ( set ) );
        return * this;
    }


    template <
            typename __ElementType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_OptimalInline auto HashSet <
            __ElementType,
            __Hasher
    > :: operator = (
            std :: initializer_list < __ElementType > const & initializerList
    ) noexcept -> HashSet & {

        this->__ht_clear ();
        for ( auto iterator = initializerList.begin(), end = initializerList.end(); iterator != end; ++ iterator ) {
            (void) this->insert ( * iterator );
        }

        return * this;
    }


    template <
            typename __ElementType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > template < typename __IterableType >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto HashSet <
            __ElementType,
            __Hasher
    > :: operator = (
            __IterableType const & iterable
    ) noexcept -> HashSet & {

        if ( this == & iterable ) {
            return * this;
        }

        this->__ht_clear ();
        for ( auto iterator = iterable.begin(), end = iterable.end(); iterator != end; ++ iterator ) {
            this->insert ( * iterator );
        }

        return * this;
    }


    template <
            typename __ElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_cpplang_ConstexprOverride auto HashSet <
            __ElementType,
            __Hasher
    > :: size () const noexcept -> Size {

        return this->__ht_size ();
    }


    template <
            typename __ElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_OptimalInline auto HashSet <
            __ElementType,
            __Hasher
    > :: clear () noexcept -> void {

        return this->__ht_clear();
    }


    template <
            typename __ElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_OptimalInline auto HashSet <
            __ElementType,
            __Hasher
    > :: remove (
            __ElementType const & element
    ) noexcept -> bool {

        return this->__ht_remove ( element );
    }


    template <
            typename __ElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_cpplang_ConstexprOverride auto HashSet <
            __ElementType,
            __Hasher
    > :: contains (
            __ElementType const & element
    ) const noexcept -> bool {

        return this->__ht_getConst ( element ) != nullptr;
    }


    template <
            typename __ElementType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_cpplang_ConstexprConditioned auto HashSet <
            __ElementType,
            __Hasher
    > :: operator == (
            HashSet const & set
    ) const noexcept -> bool {

        if ( this == & set ) {
            return true;
        }

        return this-> template __ht_equals < & cds :: meta :: equals < __ElementType > > ( set );
    }


    template <
            typename __ElementType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_cpplang_ConstexprConditioned auto HashSet <
            __ElementType,
            __Hasher
    > :: operator != (
            HashSet const & set
    ) const noexcept -> bool {

        if ( this == & set ) {
            return false;
        }

        return ! this-> template __ht_equals < & cds :: meta :: equals < __ElementType > > ( set );
    }
        
} /* namespace cds */

#endif /* __CDS_HASH_SET_IMPL_HPP__ */
