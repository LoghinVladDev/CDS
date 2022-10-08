/*
 * Created by loghin on 06/10/22.
 */

#ifndef __CDS_LINKED_HASH_SET_IMPL_HPP__
#define __CDS_LINKED_HASH_SET_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {

        template <
                typename __ElementType, /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_cpplang_ConstexprOverride auto LinkedHashSet <
                __ElementType,
                __Hasher
        > :: __cicch_obtainGenericHandler (
                __hidden :: __impl :: __CollectionInternalRequestType requestType
        ) noexcept -> __GenericHandler {

            return this->__ss_handlers() [ static_cast < uint32 > ( requestType ) ];
        }


        template <
                typename __ElementType, /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_cpplang_ConstexprOverride auto LinkedHashSet <
                __ElementType,
                __Hasher
        > :: __cicch_obtainGenericConstHandler (
                __hidden :: __impl :: __CollectionInternalRequestType requestType
        ) const noexcept -> __GenericConstHandler {

            return this->__ss_constHandlers() [ static_cast < uint32 > ( requestType ) ];
        }


        template <
                typename __ElementType, /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_OptimalInline auto LinkedHashSet <
                __ElementType,
                __Hasher
        > :: __cbegin () const noexcept -> __hidden :: __impl ::__AbstractDelegateIterator < __ElementType const > * {

            return Memory :: instance().create < __hidden :: __impl :: __DelegateIterator < __ElementType const, ConstIterator > > (
                    ConstIterator ( this->__sll_cbegin() )
            );
        }


        template <
                typename __ElementType, /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_OptimalInline auto LinkedHashSet <
                __ElementType,
                __Hasher
        > :: __cend () const noexcept -> __hidden :: __impl ::__AbstractDelegateIterator < __ElementType const > * {

            return Memory :: instance().create < __hidden :: __impl :: __DelegateIterator < __ElementType const, ConstIterator > > (
                    ConstIterator ( this->__sll_cend() )
            );
        }


        template <
                typename __ElementType, /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
        > constexpr auto LinkedHashSet <
                __ElementType,
                __Hasher
        > :: __cbeginLocal () const noexcept -> ConstIterator {

            return ConstIterator ( this->__sll_cbegin() );
        }


        template <
                typename __ElementType, /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
        > constexpr auto LinkedHashSet <
                __ElementType,
                __Hasher
        > :: __cendLocal () const noexcept -> ConstIterator {

            return ConstIterator ( this->__sll_cend() );
        }


        template <
                typename __ElementType, /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_OptimalInline auto LinkedHashSet <
                __ElementType,
                __Hasher
        > :: __newAddress (
                __ElementType const * pReferenceElement,
                bool                * pNewElementCreated
        ) noexcept -> __ElementType * {

            __ElementType * pNewElement = this->__ht_new (
                    pReferenceElement,
                    pNewElementCreated
            );

            if ( * pNewElementCreated ) {
                (void) new ( this->__sll_newBack () ) __ElementType * ( pNewElement );
            }

            return pNewElement;
        }


        template <
                typename __ElementType, /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_OptimalInline auto LinkedHashSet <
                __ElementType,
                __Hasher
        > :: __removeConst (
                ConstIterator const * pIterator
        ) noexcept -> bool {

            if (
                    pIterator == nullptr ||
                    ! static_cast < bool > ( * pIterator ) ||
                    ( * pIterator ).iterator() == this->__sll_cend()
            ) {
                return false;
            }

            auto const pElement = * ( * pIterator ).iterator();
            if ( this->__sll_removeConstIterator ( ( * pIterator ).iterator() ) ) {
                return this->__ht_remove ( * pElement );
            }

            return false;
        }


        template <
                typename __ElementType, /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_OptimalInline auto LinkedHashSet <
                __ElementType,
                __Hasher
        > :: __removeConstArray (
                ConstIterator   const * const * ppIterators,
                Size                            iteratorArraySize
        ) noexcept -> Size {

            auto pRemovedElementArray   = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < __ElementType const * > ( iteratorArraySize );
            auto pSllIteratorPtrArray   = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < typename LinkedListImplementation :: __sll_ConstIterator const * > ( iteratorArraySize );
            for ( Size index = 0U; index < iteratorArraySize; ++ index ) {
                pSllIteratorPtrArray [ index ] = & ( * ppIterators [index] ).iterator();
                pRemovedElementArray [ index ] = * ( * pSllIteratorPtrArray [ index ] );
            }

            Size removedCount = this->__sll_removeConstIteratorArray ( & pSllIteratorPtrArray [0ULL], iteratorArraySize );
            for ( Size index = 0ULL; index < iteratorArraySize; ++ index ) {
                this->__ht_remove ( * pRemovedElementArray [ index ] );
            }

            cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( pRemovedElementArray );
            cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( pSllIteratorPtrArray );

            return removedCount;
        }


        template <
                typename __ElementType, /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_OptimalInline auto LinkedHashSet <
                __ElementType,
                __Hasher
        > :: __findConst (
                __ElementType const & element
        ) const noexcept -> __hidden :: __impl :: __AbstractDelegateIterator < __ElementType const > * {

            if ( this->__ht_getConst ( element ) == nullptr ) {
                return Memory :: instance().create < __hidden :: __impl :: __DelegateIterator < __ElementType const, ConstIterator > > (
                        this->end()
                );
            }

            for ( auto iterator = this->cbegin(), end = this->cend(); iterator != end; ++ iterator ) {
                if ( cds :: meta :: equals ( * iterator, element ) ) {
                    return Memory :: instance().create < __hidden :: __impl :: __DelegateIterator < __ElementType const, ConstIterator > > (
                            iterator
                    );
                }
            }

            return Memory :: instance().create < __hidden :: __impl :: __DelegateIterator < __ElementType const, ConstIterator > > (
                    this->end()
            );
        }


        template <
                typename __ElementType, /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_cpplang_NonConstConstexprMemberFunction auto LinkedHashSet <
                __ElementType,
                __Hasher
        > :: __findConstLocal (
                __ElementType const & element
        ) const noexcept -> ConstIterator {

            if ( this->__ht_getConst ( element ) == nullptr ) {
                return this->end();
            }

            for ( auto iterator = this->cbegin(), end = this->cend(); iterator != end; ++ iterator ) {
                if ( cds :: meta :: equals ( * iterator, element ) ) {
                    return iterator;
                }
            }

            return this->end();
        }


        template <
                typename __ElementType, /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
        > constexpr LinkedHashSet <
                __ElementType,
                __Hasher
        > :: LinkedHashSet () noexcept = default;


        template <
                typename __ElementType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher           /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_OptimalInline LinkedHashSet <
                __ElementType,
                __Hasher
        > :: LinkedHashSet (
                LinkedHashSet const & set
        ) noexcept {

            this->__sll_copyCleared (
                    set
            );

            this->__ht_copyCleared (
                    set,
                    & cds :: experimental :: __hidden :: __impl :: __linkedHashSetCopyConstructor < __ElementType >
            );
        }


        template <
                typename __ElementType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher           /* NOLINT(bugprone-reserved-identifier) */
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
                typename __ElementType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher           /* NOLINT(bugprone-reserved-identifier) */
        > template <
                typename __IteratorType,    /* NOLINT(bugprone-reserved-identifier) */
                typename __TElementType,    /* NOLINT(bugprone-reserved-identifier) */
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
                typename __ElementType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher           /* NOLINT(bugprone-reserved-identifier) */
        > template <
                typename __IteratorType,    /* NOLINT(bugprone-reserved-identifier) */
                typename __TElementType,    /* NOLINT(bugprone-reserved-identifier) */
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
                typename __ElementType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher           /* NOLINT(bugprone-reserved-identifier) */
        > template <
                typename __TElementType,    /* NOLINT(bugprone-reserved-identifier) */
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
                typename __ElementType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher           /* NOLINT(bugprone-reserved-identifier) */
        > template <
                typename __TElementType,    /* NOLINT(bugprone-reserved-identifier) */
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
                typename __ElementType,         /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher               /* NOLINT(bugprone-reserved-identifier) */
        > template < typename __IterableType >  /* NOLINT(bugprone-reserved-identifier) */
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
                typename __ElementType,         /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher               /* NOLINT(bugprone-reserved-identifier) */
        > template < typename __IterableType >  /* NOLINT(bugprone-reserved-identifier) */
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
                typename __ElementType, /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_OptimalInline LinkedHashSet <
                __ElementType,
                __Hasher
        > :: ~LinkedHashSet () noexcept {

            this->__ht_clear ();
            this->__sll_clear ();
        }


        template <
                typename __ElementType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher           /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_OptimalInline auto LinkedHashSet <
                __ElementType,
                __Hasher
        > :: operator = (
                LinkedHashSet const & set
        ) noexcept -> LinkedHashSet & {

            if ( this == & set ) {
                return * this;
            }

            this->__ht_copy (
                    set,
                    & cds :: experimental :: __hidden :: __impl :: __linkedHashSetCopyConstructor < __ElementType >
            );

            this->__sll_copy (
                    set,
                    & cds :: experimental :: __hidden :: __impl :: __linkedHashSetCopyConstructor < __ElementType * >
            );

            return * this;
        }


        template <
                typename __ElementType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher           /* NOLINT(bugprone-reserved-identifier) */
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
                typename __ElementType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher           /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_OptimalInline auto LinkedHashSet <
                __ElementType,
                __Hasher
        > :: operator = (
                std :: initializer_list < __ElementType > const & initializerList
        ) noexcept -> LinkedHashSet & {

            this->__ht_clear ();
            for ( auto iterator = initializerList.begin(), end = initializerList.end(); iterator != end; ++ iterator ) {
                (void) this->insert ( * iterator );
            }

            return * this;
        }


        template <
                typename __ElementType,         /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher               /* NOLINT(bugprone-reserved-identifier) */
        > template < typename __IterableType >  /* NOLINT(bugprone-reserved-identifier) */
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
            for ( auto iterator = iterable.begin(), end = iterable.end(); iterator != end; ++ iterator ) {
                this->insert ( * iterator );
            }

            return * this;
        }


        template <
                typename __ElementType, /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_cpplang_ConstexprOverride auto LinkedHashSet <
                __ElementType,
                __Hasher
        > :: size () const noexcept -> Size {

            return this->__ht_size ();
        }


        template <
                typename __ElementType, /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_OptimalInline auto LinkedHashSet <
                __ElementType,
                __Hasher
        > :: clear () noexcept -> void {

            this->__ht_clear();
            this->__sll_clear();
        }


        template <
                typename __ElementType, /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
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
                typename __ElementType, /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_cpplang_ConstexprOverride auto LinkedHashSet <
                __ElementType,
                __Hasher
        > :: contains (
                __ElementType const & element
        ) const noexcept -> bool {

            return this->__ht_getConst ( element ) != nullptr;
        }


        template <
                typename __ElementType,         /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher               /* NOLINT(bugprone-reserved-identifier) */
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
                typename __ElementType,         /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher               /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_cpplang_ConstexprConditioned auto LinkedHashSet <
                __ElementType,
                __Hasher
        > :: operator != (
                LinkedHashSet const & set
        ) const noexcept -> bool {

            if ( this == & set ) {
                return false;
            }

            return ! this-> template __ht_equals < & cds :: meta :: equals < __ElementType > > ( set );
        }

    }
}

#endif /* __CDS_LINKED_HASH_SET_IMPL_HPP__ */
