/* NOLINT(llvm-header-guard)
 * Created by loghin on 06/10/22.
 */

#ifndef __CDS_LINKED_HASH_SET_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_LINKED_HASH_SET_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {

    template <
            typename __ElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_cpplang_ConstexprOverride auto LinkedHashSet <
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
    > __CDS_cpplang_ConstexprOverride auto LinkedHashSet <
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
    > __CDS_OptimalInline auto LinkedHashSet <
            __ElementType,
            __Hasher
    > :: __cbegin (
            LinkedHashSet const * pObject
    ) noexcept -> __hidden :: __impl ::__AbstractDelegateIterator < __ElementType const > * {

        return Memory :: instance().create < __hidden :: __impl :: __DelegateIterator < __ElementType const, ConstIterator > > (
                ConstIterator ( pObject->__sll_cbegin() )
        );
    }


    template <
            typename __ElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_OptimalInline auto LinkedHashSet <
            __ElementType,
            __Hasher
    > :: __cend (
            LinkedHashSet const * pObject
    ) noexcept -> __hidden :: __impl ::__AbstractDelegateIterator < __ElementType const > * {

        return Memory :: instance().create < __hidden :: __impl :: __DelegateIterator < __ElementType const, ConstIterator > > (
                ConstIterator ( pObject->__sll_cend() )
        );
    }


    template <
            typename __ElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > constexpr auto LinkedHashSet <
            __ElementType,
            __Hasher
    > :: __cbeginLocal (
            LinkedHashSet const * pObject
    ) noexcept -> ConstIterator {

        return ConstIterator ( pObject->__sll_cbegin() );
    }


    template <
            typename __ElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > constexpr auto LinkedHashSet <
            __ElementType,
            __Hasher
    > :: __cendLocal (
            LinkedHashSet const * pObject
    ) noexcept -> ConstIterator {

        return ConstIterator ( pObject->__sll_cend() );
    }


    template <
            typename __ElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_OptimalInline auto LinkedHashSet <
            __ElementType,
            __Hasher
    > :: __newAddress (
            LinkedHashSet       * pObject,
            __ElementType const * pReferenceElement,
            bool                * pNewElementCreated
    ) noexcept -> __ElementType * {

        __ElementType * pNewElement = pObject->__ht_new (
                pReferenceElement,
                pNewElementCreated
        );

        if ( * pNewElementCreated ) {
            (void) new ( pObject->__sll_newBack () ) __ElementType * ( pNewElement );
        }

        return pNewElement;
    }


    template <
            typename __ElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_OptimalInline auto LinkedHashSet <
            __ElementType,
            __Hasher
    > :: __removeConst (
            LinkedHashSet       * pObject,
            ConstIterator const * pIterator
    ) noexcept -> bool {

        if (
                pIterator == nullptr ||
                ! static_cast < bool > ( * pIterator ) ||
                ( * pIterator ).iterator() == pObject->__sll_cend()
        ) {
            return false;
        }

        auto const pElement = * ( * pIterator ).iterator();
        if ( pObject->__sll_removeConstIterator ( ( * pIterator ).iterator() ) ) {
            return pObject->__ht_remove ( * pElement );
        }

        return false;
    }


    template <
            typename __ElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_OptimalInline auto LinkedHashSet <
            __ElementType,
            __Hasher
    > :: __removeConstArray (
            LinkedHashSet                 * pObject,
            ConstIterator   const * const * ppIterators,
            Size                            iteratorArraySize
    ) noexcept -> Size {

        auto pRemovedElementArray   = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType const * > ( iteratorArraySize );
        auto pSllIteratorPtrArray   = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < typename LinkedListImplementation :: __sll_ConstIterator const * > ( iteratorArraySize );
        for ( Size index = 0U; index < iteratorArraySize; ++ index ) {
            pSllIteratorPtrArray [ index ] = & ( * ppIterators [index] ).iterator(); /* NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic) */
            pRemovedElementArray [ index ] = * ( * pSllIteratorPtrArray [ index ] );
        }

        Size removedCount = pObject->__sll_removeConstIteratorArray ( & pSllIteratorPtrArray [0ULL], iteratorArraySize );
        for ( Size index = 0ULL; index < iteratorArraySize; ++ index ) {
            pObject->__ht_remove ( * pRemovedElementArray [ index ] );
        }

        cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( pRemovedElementArray );
        cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( pSllIteratorPtrArray );

        return removedCount;
    }


    template <
            typename __ElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_OptimalInline auto LinkedHashSet <
            __ElementType,
            __Hasher
    > :: __findConst (
            LinkedHashSet const * pObject,
            __ElementType const & element
    ) noexcept -> __hidden :: __impl :: __AbstractDelegateIterator < __ElementType const > * {

        if ( pObject->__ht_getConst ( element ) == nullptr ) {
            return Memory :: instance().create < __hidden :: __impl :: __DelegateIterator < __ElementType const, ConstIterator > > (
                    pObject->cend()
            );
        }

        for ( auto iterator = pObject->cbegin(), end = pObject->cend(); iterator != end; ++ iterator ) { /* NOLINT(clion-misra-cpp2008-8-0-1) */
            if ( cds :: meta :: equals ( * iterator, element ) ) {
                return Memory :: instance().create < __hidden :: __impl :: __DelegateIterator < __ElementType const, ConstIterator > > (
                        iterator
                );
            }
        }

        return Memory :: instance().create < __hidden :: __impl :: __DelegateIterator < __ElementType const, ConstIterator > > (
                pObject->cend()
        );
    }


    template <
            typename __ElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_cpplang_NonConstConstexprMemberFunction auto LinkedHashSet <
            __ElementType,
            __Hasher
    > :: __findConstLocal (
            LinkedHashSet const * pObject,
            __ElementType const & element
    ) noexcept -> ConstIterator {

        if ( pObject->__ht_getConst ( element ) == nullptr ) {
            return this->cend();
        }

        for ( auto iterator = pObject->cbegin(), end = pObject->cend(); iterator != end; ++ iterator ) {  /* NOLINT(clion-misra-cpp2008-8-0-1) */
            if ( cds :: meta :: equals ( * iterator, element ) ) {
                return iterator;
            }
        }

        return pObject->cend();
    }


    template <
            typename __ElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > constexpr LinkedHashSet <
            __ElementType,
            __Hasher
    > :: LinkedHashSet () noexcept = default;


    template <
            typename __ElementType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_OptimalInline LinkedHashSet <
            __ElementType,
            __Hasher
    > :: LinkedHashSet (
            LinkedHashSet const & set
    ) noexcept {

        /* Copy of each not possible, linked list references hash table elements from other set */
        for ( auto iterator = set.cbegin(), end = set.cend(); iterator != end; ++ iterator ) {  /* NOLINT(clion-misra-cpp2008-8-0-1) */
            this->insert ( * iterator );
        }
    }


    template <
            typename __ElementType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > constexpr LinkedHashSet <
            __ElementType,
            __Hasher
    > :: LinkedHashSet (
            LinkedHashSet && set
    ) noexcept :
            HashTableImplementation ( std :: move ( set ) ),
            LinkedListImplementation ( std :: move ( set ) ) {

    }


    template <
            typename __ElementType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > constexpr LinkedHashSet <
            __ElementType,
            __Hasher
    > :: LinkedHashSet (
            __Hasher const & hasher
    ) noexcept :
            HashTableImplementation ( hasher ) {

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
    > __CDS_OptimalInline LinkedHashSet <
            __ElementType,
            __Hasher
    > :: LinkedHashSet (
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
    > __CDS_OptimalInline LinkedHashSet <
            __ElementType,
            __Hasher
    > :: LinkedHashSet (
            __Hasher        const & hasher,
            __IteratorType  const & begin,
            __IteratorType  const & end,
            Size                    count
    ) noexcept :
            HashTableImplementation ( hasher ) {

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
    > __CDS_OptimalInline LinkedHashSet <
            __ElementType,
            __Hasher
    > :: LinkedHashSet (
            std :: initializer_list < __ElementType > const & initializerList
    ) noexcept :
            LinkedHashSet (
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
    > __CDS_OptimalInline LinkedHashSet <
            __ElementType,
            __Hasher
    > :: LinkedHashSet (
            __Hasher                                    const & hasher,
            std :: initializer_list < __ElementType >   const & initializerList
    ) noexcept :
            LinkedHashSet (
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
    __CDS_OptimalInline LinkedHashSet <
            __ElementType,
            __Hasher
    > :: LinkedHashSet (
            __IterableType const & iterable
    ) noexcept :
            LinkedHashSet (
                    iterable.begin (),
                    iterable.end ()
            ) {

    }


    template <
            typename __ElementType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > template < typename __IterableType >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline LinkedHashSet <
            __ElementType,
            __Hasher
    > :: LinkedHashSet (
            __Hasher        const & hasher,
            __IterableType  const & iterable
    ) noexcept :
            LinkedHashSet (
                    hasher,
                    iterable.begin (),
                    iterable.end ()
            ) {

    }


    template <
            typename __ElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_OptimalInline LinkedHashSet <
            __ElementType,
            __Hasher
    > :: ~LinkedHashSet () noexcept {

        this->__ht_clear ();
        this->__sll_clear ();
    }


    template <
            typename __ElementType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_OptimalInline auto LinkedHashSet <
            __ElementType,
            __Hasher
    > :: operator = (
            LinkedHashSet const & set
    ) noexcept -> LinkedHashSet & {

        if ( this == & set ) {
            return * this;
        }

        this->__sll_clear ();
        this->__ht_clear ();

        /* Copy of each not possible, linked list references hash table elements from other set */
        for ( auto iterator = set.cbegin(), end = set.cend(); iterator != end; ++ iterator ) {  /* NOLINT(clion-misra-cpp2008-8-0-1) */
            this->insert ( * iterator );
        }

        return * this;
    }


    template <
            typename __ElementType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_OptimalInline auto LinkedHashSet <
            __ElementType,
            __Hasher
    > :: operator = (
            LinkedHashSet && set
    ) noexcept -> LinkedHashSet & {

        if ( this == & set ) {
            return * this;
        }

        this->__ht_move ( std :: move ( set ) );
        this->__sll_move ( std :: move ( set ) );
        return * this;
    }


    template <
            typename __ElementType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_OptimalInline auto LinkedHashSet <
            __ElementType,
            __Hasher
    > :: operator = (
            std :: initializer_list < __ElementType > const & initializerList
    ) noexcept -> LinkedHashSet & {

        this->__ht_clear ();
        this->__sll_clear ();
        for ( auto iterator = initializerList.begin(), end = initializerList.end(); iterator != end; ++ iterator ) {    /* NOLINT(clion-misra-cpp2008-8-0-1) */
            (void) this->insert ( * iterator );
        }

        return * this;
    }


    template <
            typename __ElementType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > template < typename __IterableType >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    __CDS_OptimalInline auto LinkedHashSet <
            __ElementType,
            __Hasher
    > :: operator = (
            __IterableType const & iterable
    ) noexcept -> LinkedHashSet & {

        if ( this == & iterable ) {
            return * this;
        }

        this->__ht_clear ();
        this->__sll_clear ();
        for ( auto iterator = iterable.begin(), end = iterable.end(); iterator != end; ++ iterator ) {  /* NOLINT(clion-misra-cpp2008-8-0-1) */
            this->insert ( * iterator );
        }

        return * this;
    }


    template <
            typename __ElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_cpplang_ConstexprOverride auto LinkedHashSet <
            __ElementType,
            __Hasher
    > :: size () const noexcept -> Size {

        return this->__ht_size ();
    }


    template <
            typename __ElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_OptimalInline auto LinkedHashSet <
            __ElementType,
            __Hasher
    > :: clear () noexcept -> void {

        this->__ht_clear();
        this->__sll_clear();
    }


    template <
            typename __ElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_OptimalInline auto LinkedHashSet <
            __ElementType,
            __Hasher
    > :: remove (
            __ElementType const & element
    ) noexcept -> bool {

        auto const pElement = this->__ht_removeGetPtr ( element );
        return pElement != nullptr && this->__sll_remove ( pElement );
    }


    template <
            typename __ElementType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_cpplang_ConstexprOverride auto LinkedHashSet <
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
    > __CDS_cpplang_ConstexprConditioned auto LinkedHashSet <
            __ElementType,
            __Hasher
    > :: operator == (
            LinkedHashSet const & set
    ) const noexcept -> bool {

        if ( this == & set ) {
            return true;
        }

        return this-> template __ht_equals < & cds :: meta :: equals < __ElementType > > ( set );
    }


    template <
            typename __ElementType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_cpplang_ConstexprConditioned auto LinkedHashSet <
            __ElementType,
            __Hasher
    > :: operator != (
            LinkedHashSet const & set
    ) const noexcept -> bool {

        if ( this == & set ) {
            return false;
        }

        return ! this-> template __ht_equals < & cds :: meta :: equals < __ElementType > > ( set ); /* NOLINT(clion-misra-cpp2008-5-3-1) */
    }

} /* namespace cds */

#endif /* __CDS_LINKED_HASH_SET_IMPL_HPP__ */
