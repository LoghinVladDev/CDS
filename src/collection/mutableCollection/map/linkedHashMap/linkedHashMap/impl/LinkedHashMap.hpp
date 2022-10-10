/*
 * Created by loghin on 09/10/22.
 */

#ifndef __CDS_LINKED_HASH_MAP_IMPL_HPP__
#define __CDS_LINKED_HASH_MAP_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {

    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_cpplang_ConstexprOverride auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: __cicch_obtainGenericHandler (
            __hidden :: __impl :: __CollectionInternalRequestType requestType
    ) noexcept -> __GenericHandler {

        return this->__ms_handlers() [ static_cast < uint32 > ( requestType ) ];
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_cpplang_ConstexprOverride auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: __cicch_obtainGenericConstHandler (
            __hidden :: __impl :: __CollectionInternalRequestType requestType
    ) const noexcept -> __GenericConstHandler {

        return this->__ms_constHandlers() [ static_cast < uint32 > ( requestType ) ];
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_OptimalInline auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: __begin () noexcept -> __hidden :: __impl ::__AbstractDelegateIterator < EntryType > * {

        return Memory :: instance().create < __hidden :: __impl :: __DelegateIterator < EntryType, Iterator > > (
                Iterator ( this->__sll_begin() )
        );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_OptimalInline auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: __end () noexcept -> __hidden :: __impl ::__AbstractDelegateIterator < EntryType > * {

        return Memory :: instance().create < __hidden :: __impl :: __DelegateIterator < EntryType, Iterator > > (
                Iterator ( this->__sll_end() )
        );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_cpplang_NonConstConstexprMemberFunction auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: __beginLocal () noexcept -> Iterator {

        return Iterator ( this->__sll_begin() );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_cpplang_NonConstConstexprMemberFunction auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: __endLocal () noexcept -> Iterator {

        return Iterator ( this->__sll_end() );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_OptimalInline auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: __cbegin () const noexcept -> __hidden :: __impl ::__AbstractDelegateIterator < EntryType const > * {

        return Memory :: instance().create < __hidden :: __impl :: __DelegateIterator < EntryType const, ConstIterator > > (
                ConstIterator ( this->__sll_cbegin() )
        );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_OptimalInline auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: __cend () const noexcept -> __hidden :: __impl ::__AbstractDelegateIterator < EntryType const > * {

        return Memory :: instance().create < __hidden :: __impl :: __DelegateIterator < EntryType const, ConstIterator > > (
                ConstIterator ( this->__sll_cend() )
        );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
    > constexpr auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: __cbeginLocal () const noexcept -> ConstIterator {

        return ConstIterator ( this->__sll_cbegin() );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
    > constexpr auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: __cendLocal () const noexcept -> ConstIterator {

        return ConstIterator ( this->__sll_cend() );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_OptimalInline auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: __newAddress (
            EntryType   const * pReferenceElement,
            bool              * pNewElementCreated
    ) noexcept -> EntryType * {

        EntryType * pNewElement = this->__ht_new (
                pReferenceElement,
                pNewElementCreated
        );

        if ( * pNewElementCreated ) {
            (void) new ( this->__sll_newBack () ) EntryType * ( pNewElement );
        }

        return pNewElement;
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_OptimalInline auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: __remove (
            Iterator const * pIterator
    ) noexcept -> bool {

        if (
                pIterator == nullptr ||
                ! static_cast < bool > ( * pIterator ) ||
                ( * pIterator ).iterator() == this->__sll_end()
        ) {
            return false;
        }

        auto const pElement = * ( * pIterator ).iterator();
        if ( this->__sll_removeIterator ( ( * pIterator ).iterator() ) ) {
            return this->__ht_remove ( pElement->key() );
        }

        return false;
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_OptimalInline auto LinkedHashMap <
            __KeyType,
            __ValueType,
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
            return this->__ht_remove ( pElement->key() );
        }

        return false;
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_OptimalInline auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: __removeArray (
            Iterator    const * const * ppIterators,
            Size                        iteratorArraySize
    ) noexcept -> Size {

        auto pRemovedElementArray   = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < EntryType * > ( iteratorArraySize );
        auto pSllIteratorPtrArray   = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < typename LinkedListImplementation :: __sll_Iterator const * > ( iteratorArraySize );
        for ( Size index = 0U; index < iteratorArraySize; ++ index ) {
            pSllIteratorPtrArray [ index ] = & ( * ppIterators [index] ).iterator();
            pRemovedElementArray [ index ] = * ( * pSllIteratorPtrArray [ index ] );
        }

        Size removedCount = this->__sll_removeIteratorArray ( & pSllIteratorPtrArray [0ULL], iteratorArraySize );
        for ( Size index = 0ULL; index < iteratorArraySize; ++ index ) {
            this->__ht_remove ( pRemovedElementArray [ index ]->key() );
        }

        cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( pRemovedElementArray );
        cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( pSllIteratorPtrArray );

        return removedCount;
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_OptimalInline auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: __removeConstArray (
            ConstIterator   const * const * ppIterators,
            Size                            iteratorArraySize
    ) noexcept -> Size {

        auto pRemovedElementArray   = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < EntryType const * > ( iteratorArraySize );
        auto pSllIteratorPtrArray   = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < typename LinkedListImplementation :: __sll_ConstIterator const * > ( iteratorArraySize );
        for ( Size index = 0U; index < iteratorArraySize; ++ index ) {
            pSllIteratorPtrArray [ index ] = & ( * ppIterators [index] ).iterator();
            pRemovedElementArray [ index ] = * ( * pSllIteratorPtrArray [ index ] );
        }

        Size removedCount = this->__sll_removeConstIteratorArray ( & pSllIteratorPtrArray [0ULL], iteratorArraySize );
        for ( Size index = 0ULL; index < iteratorArraySize; ++ index ) {
            this->__ht_remove ( pRemovedElementArray [ index ]->key() );
        }

        cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( pRemovedElementArray );
        cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( pSllIteratorPtrArray );

        return removedCount;
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_OptimalInline auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: __find (
            __KeyType const & element
    ) noexcept -> __hidden :: __impl :: __AbstractDelegateIterator < EntryType > * {

        if ( this->__ht_getConst ( element ) == nullptr ) {
            return Memory :: instance().create < __hidden :: __impl :: __DelegateIterator < EntryType, Iterator > > (
                    this->end()
            );
        }

        for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
            if ( cds :: meta :: equals ( iterator->key(), element ) ) {
                return Memory :: instance().create < __hidden :: __impl :: __DelegateIterator < EntryType, Iterator > > (
                        iterator
                );
            }
        }

        return Memory :: instance().create < __hidden :: __impl :: __DelegateIterator < EntryType, Iterator > > (
                this->end()
        );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_OptimalInline auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: __findConst (
            __KeyType const & element
    ) const noexcept -> __hidden :: __impl :: __AbstractDelegateIterator < EntryType const > * {

        if ( this->__ht_getConst ( element ) == nullptr ) {
            return Memory :: instance().create < __hidden :: __impl :: __DelegateIterator < EntryType const, ConstIterator > > (
                    this->cend()
            );
        }

        for ( auto iterator = this->cbegin(), end = this->cend(); iterator != end; ++ iterator ) {
            if ( cds :: meta :: equals ( iterator->key(), element ) ) {
                return Memory :: instance().create < __hidden :: __impl :: __DelegateIterator < EntryType const, ConstIterator > > (
                        iterator
                );
            }
        }

        return Memory :: instance().create < __hidden :: __impl :: __DelegateIterator < EntryType const, ConstIterator > > (
                this->cend()
        );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_cpplang_NonConstConstexprMemberFunction auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: __findLocal (
            __KeyType const & element
    ) noexcept -> Iterator {

        if ( this->__ht_getConst ( element ) == nullptr ) {
            return this->end();
        }

        for ( auto iterator = this->begin(), end = this->end(); iterator != end; ++ iterator ) {
            if ( cds :: meta :: equals ( iterator->key(), element ) ) {
                return iterator;
            }
        }

        return this->end();
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_cpplang_ConstexprConditioned auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: __findConstLocal (
            __KeyType const & element
    ) const noexcept -> ConstIterator {

        if ( this->__ht_getConst ( element ) == nullptr ) {
            return this->cend();
        }

        for ( auto iterator = this->cbegin(), end = this->cend(); iterator != end; ++ iterator ) {
            if ( cds :: meta :: equals ( iterator->key(), element ) ) {
                return iterator;
            }
        }

        return this->cend();
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_cpplang_ConstexprOverride auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: keySetProxy () const noexcept -> AbstractKeySetProxy const & {

        return this->_keySetProxy;
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_cpplang_ConstexprOverride auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: keySetProxy () noexcept -> AbstractKeySetProxy & {

        return this->_keySetProxy;
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_cpplang_ConstexprOverride auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: valueMutableCollectionProxy () const noexcept -> AbstractValueMutableCollectionProxy const & {

        return this->_valueMutableCollectionProxy;
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_cpplang_ConstexprOverride auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: valueMutableCollectionProxy () noexcept -> AbstractValueMutableCollectionProxy & {

        return this->_valueMutableCollectionProxy;
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_cpplang_ConstexprOverride auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: entryMutableCollectionProxy () const noexcept -> AbstractEntryMutableCollectionProxy const & {

        return this->_entryMutableCollectionProxy;
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_cpplang_ConstexprOverride auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: entryMutableCollectionProxy () noexcept -> AbstractEntryMutableCollectionProxy & {

        return this->_entryMutableCollectionProxy;
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
    > constexpr LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: LinkedHashMap () noexcept :
            _keySetProxy ( this ),
            _valueMutableCollectionProxy ( this ),
            _entryMutableCollectionProxy ( this ) {

    }


    template <
            typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher           /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_OptimalInline LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: LinkedHashMap (
            LinkedHashMap const & map
    ) noexcept :
            _keySetProxy ( this ),
            _valueMutableCollectionProxy ( this ),
            _entryMutableCollectionProxy ( this ) {

        /* Copy of each not possible, linked list references hash table elements from other map */
        for ( auto iterator = map.cbegin(), end = map.cend(); iterator != end; ++ iterator ) {
            this->insert ( * iterator );
        }
    }


    template <
            typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher           /* NOLINT(bugprone-reserved-identifier) */
    > constexpr LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: LinkedHashMap (
            LinkedHashMap && map
    ) noexcept :
            _keySetProxy ( this ),
            _valueMutableCollectionProxy ( this ),
            _entryMutableCollectionProxy ( this ),
            HashTableImplementation ( std :: move ( map ) ),
            LinkedListImplementation ( std :: move ( map ) ) {

    }


    template <
            typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher           /* NOLINT(bugprone-reserved-identifier) */
    > constexpr LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: LinkedHashMap (
            __Hasher const & hasher
    ) noexcept :
            _keySetProxy ( this ),
            _valueMutableCollectionProxy ( this ),
            _entryMutableCollectionProxy ( this ),
            HashTableImplementation ( hasher ) {

    }


    template <
            typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher           /* NOLINT(bugprone-reserved-identifier) */
    > template <
            typename __IteratorType,    /* NOLINT(bugprone-reserved-identifier) */
            typename __TElementType,    /* NOLINT(bugprone-reserved-identifier) */
            cds :: meta :: EnableIf <
                    cds :: meta :: isCopyConstructible < __TElementType > ()
            >
    > __CDS_OptimalInline LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: LinkedHashMap (
            __IteratorType const & begin,
            __IteratorType const & end,
            Size                   count
    ) noexcept :
            _keySetProxy ( this ),
            _valueMutableCollectionProxy ( this ),
            _entryMutableCollectionProxy ( this ) {

        (void) count;
        for ( auto iterator = begin; iterator != end; ++ iterator ) {
            (void) this->insert ( * iterator );
        }
    }


    template <
            typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher           /* NOLINT(bugprone-reserved-identifier) */
    > template <
            typename __IteratorType,    /* NOLINT(bugprone-reserved-identifier) */
            typename __TElementType,    /* NOLINT(bugprone-reserved-identifier) */
            cds :: meta :: EnableIf <
                    cds :: meta :: isCopyConstructible < __TElementType > ()
            >
    > __CDS_OptimalInline LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: LinkedHashMap (
            __Hasher        const & hasher,
            __IteratorType  const & begin,
            __IteratorType  const & end,
            Size                    count
    ) noexcept :
            _keySetProxy ( this ),
            _valueMutableCollectionProxy ( this ),
            _entryMutableCollectionProxy ( this ),
            HashTableImplementation ( hasher ) {

        (void) count;
        for ( auto iterator = begin; iterator != end; ++ iterator ) {
            (void) this->insert ( * iterator );
        }
    }


    template <
            typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher           /* NOLINT(bugprone-reserved-identifier) */
    > template <
            typename __TElementType,    /* NOLINT(bugprone-reserved-identifier) */
            cds :: meta :: EnableIf <
                    cds :: meta :: isCopyConstructible < __TElementType > ()
            >
    > __CDS_OptimalInline LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: LinkedHashMap (
            std :: initializer_list < ElementType > const & initializerList
    ) noexcept :
            LinkedHashMap (
                    initializerList.begin(),
                    initializerList.end(),
                    initializerList.size()
            ) {

    }


    template <
            typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher           /* NOLINT(bugprone-reserved-identifier) */
    > template <
            typename __TElementType,    /* NOLINT(bugprone-reserved-identifier) */
            cds :: meta :: EnableIf <
                    cds :: meta :: isCopyConstructible < __TElementType > ()
            >
    > __CDS_OptimalInline LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: LinkedHashMap (
            __Hasher                                const & hasher,
            std :: initializer_list < ElementType > const & initializerList
    ) noexcept :
            LinkedHashMap (
                    hasher,
                    initializerList.begin(),
                    initializerList.end(),
                    initializerList.size()
            ) {

    }


    template <
            typename __KeyType,             /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,           /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher               /* NOLINT(bugprone-reserved-identifier) */
    > template < typename __IterableType >  /* NOLINT(bugprone-reserved-identifier) */
    __CDS_OptimalInline LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: LinkedHashMap (
            __IterableType const & iterable
    ) noexcept :
            LinkedHashMap (
                    iterable.begin(),
                    iterable.end()
            ) {

    }


    template <
            typename __KeyType,             /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,           /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher               /* NOLINT(bugprone-reserved-identifier) */
    > template < typename __IterableType >  /* NOLINT(bugprone-reserved-identifier) */
    __CDS_OptimalInline LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: LinkedHashMap (
            __Hasher        const & hasher,
            __IterableType  const & iterable
    ) noexcept :
            LinkedHashMap (
                    hasher,
                    iterable.begin(),
                    iterable.end()
            ) {

    }


    template <
            typename __KeyType,             /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,           /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher               /* NOLINT(bugprone-reserved-identifier) */
    > LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: ~LinkedHashMap () noexcept {

        this->__ht_clear ();
        this->__sll_clear ();
    }


    template <
            typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher           /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_OptimalInline auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: operator = (
            LinkedHashMap const & map
    ) noexcept -> LinkedHashMap & {

        if ( this == & map ) {
            return * this;
        }

        this->__sll_clear ();
        this->__ht_clear ();

        /* Copy of each not possible, linked list references hash table elements from other map */
        for ( auto iterator = map.cbegin(), end = map.cend(); iterator != end; ++ iterator ) {
            this->insert ( * iterator );
        }

        return * this;
    }


    template <
            typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher           /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_OptimalInline auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: operator = (
            LinkedHashMap && map
    ) noexcept -> LinkedHashMap & {

        if ( this == & map ) {
            return * this;
        }

        this->__ht_move ( std :: move ( map ) );
        this->__sll_move ( std :: move ( map ) );
        return * this;
    }


    template <
            typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher           /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_OptimalInline auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: operator = (
            std :: initializer_list < EntryType > const & initializerList
    ) noexcept -> LinkedHashMap & {

        this->__ht_clear ();
        this->__sll_clear ();
        for ( auto iterator = initializerList.begin(), end = initializerList.end(); iterator != end; ++ iterator ) {
            (void) this->insert ( * iterator );
        }

        return * this;
    }


    template <
            typename __KeyType,             /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,           /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher               /* NOLINT(bugprone-reserved-identifier) */
    > template < typename __IterableType >  /* NOLINT(bugprone-reserved-identifier) */
    __CDS_OptimalInline auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: operator = (
            __IterableType const & iterable
    ) noexcept -> LinkedHashMap & {

        if ( this == & iterable ) {
            return * this;
        }

        this->__ht_clear ();
        this->__sll_clear ();
        for ( auto iterator = iterable.begin(), end = iterable.end(); iterator != end; ++ iterator ) {
            this->insert ( * iterator );
        }

        return * this;
    }


    template <
            typename __KeyType,             /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,           /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher               /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_OptimalInline auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: clear () noexcept -> void {

        this->__ht_clear();
        this->__sll_clear();
    }


    template <
            typename __KeyType,             /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,           /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher               /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_cpplang_ConstexprOverride auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: size () const noexcept -> Size {

        return this->__ht_size();
    }


    template <
            typename __KeyType,             /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,           /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher               /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_OptimalInline auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: remove (
            KeyType const & key
    ) noexcept -> bool {

        auto const pElement = this->__ht_removeGetPtr ( key );
        return pElement != nullptr && this->__sll_remove ( pElement );
    }


    template <
            typename __KeyType,             /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,           /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher               /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_cpplang_ConstexprConditioned auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: operator == (
            LinkedHashMap const & map
    ) const noexcept -> bool {

        if ( this == & map ) {
            return true;
        }

        return this-> template __ht_equals < & __hidden :: __impl :: __linkedHashMapEquals < __KeyType, __ValueType > > ( map );
    }


    template <
            typename __KeyType,             /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,           /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher               /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_cpplang_ConstexprConditioned auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: operator != (
            LinkedHashMap const & map
    ) const noexcept -> bool {

        if ( this == & map ) {
            return false;
        }

        return ! this-> template __ht_equals < & __hidden :: __impl :: __linkedHashMapEquals < __KeyType, __ValueType > > ( map );
    }


    template <
            typename __KeyType,             /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,           /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher               /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_cpplang_ConstexprOverride auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: containsKey (
            __KeyType const & key
    ) const noexcept -> bool {

        return this->__ht_getConst ( key ) != nullptr;
    }


    template <
            typename __KeyType,             /* NOLINT(bugprone-reserved-identifier) */
            typename __ValueType,           /* NOLINT(bugprone-reserved-identifier) */
            typename __Hasher               /* NOLINT(bugprone-reserved-identifier) */
    > __CDS_cpplang_ConstexprOverride auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: containsValue (
            __ValueType const & value
    ) const noexcept -> bool {

        for ( auto iterator = this->__sll_cbegin (), end = this->__sll_cend (); iterator != end; ++ iterator ) {
            if ( cds :: meta :: equals ( ( * iterator )->value(), value ) ) {
                return true;
            }
        }

        return false;
    }

}

#endif /* __CDS_LINKED_HASH_MAP_IMPL_HPP__ */
