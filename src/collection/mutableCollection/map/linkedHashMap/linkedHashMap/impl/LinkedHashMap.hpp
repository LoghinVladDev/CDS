/*  NOLINT(llvm-header-guard)
 * Created by loghin on 09/10/22.
 */

#ifndef __CDS_LINKED_HASH_MAP_IMPL_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_LINKED_HASH_MAP_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {

    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_cpplang_ConstexprOverride auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: __iicch_obtainGenericHandler (
            __hidden :: __impl :: __IterableInternalRequestType requestType
    ) noexcept -> __GenericHandler {

        return this->__ms_handlers() [ static_cast < uint32 > ( requestType ) ];
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_cpplang_ConstexprOverride auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: __iicch_obtainGenericConstHandler (
            __hidden :: __impl :: __IterableInternalRequestType requestType
    ) const noexcept -> __GenericConstHandler {

        return this->__ms_constHandlers() [ static_cast < uint32 > ( requestType ) ];
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_OptimalInline auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: __begin (
            LinkedHashMap * pObject
    ) noexcept -> __hidden :: __impl ::__AbstractDelegateIterator < EntryType > * {

        return Memory :: instance().create < __hidden :: __impl :: __DelegateIterator < EntryType, Iterator > > (
                Iterator ( pObject->__sll_begin() )
        );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_OptimalInline auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: __end (
            LinkedHashMap * pObject
    ) noexcept -> __hidden :: __impl ::__AbstractDelegateIterator < EntryType > * {

        return Memory :: instance().create < __hidden :: __impl :: __DelegateIterator < EntryType, Iterator > > (
                Iterator ( pObject->__sll_end() )
        );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_cpplang_NonConstConstexprMemberFunction auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: __beginLocal (
            LinkedHashMap * pObject
    ) noexcept -> Iterator {

        return Iterator ( pObject->__sll_begin() );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_cpplang_NonConstConstexprMemberFunction auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: __endLocal (
            LinkedHashMap * pObject
    ) noexcept -> Iterator {

        return Iterator ( pObject->__sll_end() );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_OptimalInline auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: __cbegin (
            LinkedHashMap const * pObject
    ) noexcept -> __hidden :: __impl ::__AbstractDelegateIterator < EntryType const > * {

        return Memory :: instance().create < __hidden :: __impl :: __DelegateIterator < EntryType const, ConstIterator > > (
                ConstIterator ( pObject->__sll_cbegin() )
        );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_OptimalInline auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: __cend (
            LinkedHashMap const * pObject
    ) noexcept -> __hidden :: __impl ::__AbstractDelegateIterator < EntryType const > * {

        return Memory :: instance().create < __hidden :: __impl :: __DelegateIterator < EntryType const, ConstIterator > > (
                ConstIterator ( pObject->__sll_cend() )
        );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > constexpr auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: __cbeginLocal (
            LinkedHashMap const * pObject
    ) noexcept -> ConstIterator {

        return ConstIterator ( pObject->__sll_cbegin() );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > constexpr auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: __cendLocal (
            LinkedHashMap const * pObject
    ) noexcept -> ConstIterator {

        return ConstIterator ( pObject->__sll_cend() );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_OptimalInline auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: __newAddress (
            LinkedHashMap         * pObject,
            EntryType       const * pReferenceElement,
            bool                  * pNewElementCreated
    ) noexcept -> EntryType * {

        EntryType * pNewElement = pObject->__ht_new (
                pReferenceElement,
                pNewElementCreated
        );

        if ( * pNewElementCreated ) {
            (void) new ( pObject->__sll_newBack () ) EntryType * ( pNewElement );
        }

        return pNewElement;
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_OptimalInline auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: __remove (
            LinkedHashMap         * pObject,
            Iterator        const * pIterator
    ) noexcept -> bool {

        if (
                pIterator == nullptr ||
                ! static_cast < bool > ( * pIterator ) ||
                ( * pIterator ).iterator() == pObject->__sll_end()
        ) {
            return false;
        }

        auto const pElement = * ( * pIterator ).iterator();
        if ( pObject->__sll_removeIterator ( ( * pIterator ).iterator() ) ) {
            return pObject->__ht_remove ( pElement->key() );
        }

        return false;
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_OptimalInline auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: __removeConst (
            LinkedHashMap         * pObject,
            ConstIterator   const * pIterator
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
            return pObject->__ht_remove ( pElement->key() );
        }

        return false;
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_OptimalInline auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: __removeArray (
            LinkedHashMap             * pObject,
            Iterator    const * const * ppIterators,
            Size                        iteratorArraySize
    ) noexcept -> Size {

        auto pRemovedElementArray   = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < EntryType * > ( iteratorArraySize );
        auto pSllIteratorPtrArray   = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < typename LinkedListImplementation :: __sll_Iterator const * > ( iteratorArraySize );
        for ( Size index = 0U; index < iteratorArraySize; ++ index ) {
            pSllIteratorPtrArray [ index ] = & ( * ppIterators [index] ).iterator();
            pRemovedElementArray [ index ] = * ( * pSllIteratorPtrArray [ index ] );
        }

        Size removedCount = pObject->__sll_removeIteratorArray ( & pSllIteratorPtrArray [0ULL], iteratorArraySize );
        for ( Size index = 0ULL; index < iteratorArraySize; ++ index ) {
            pObject->__ht_remove ( pRemovedElementArray [ index ]->key() );
        }

        cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( pRemovedElementArray );
        cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( pSllIteratorPtrArray );

        return removedCount;
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_OptimalInline auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: __removeConstArray (
            LinkedHashMap                 * pObject,
            ConstIterator   const * const * ppIterators,
            Size                            iteratorArraySize
    ) noexcept -> Size {

        auto pRemovedElementArray   = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < EntryType const * > ( iteratorArraySize );
        auto pSllIteratorPtrArray   = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveArray < typename LinkedListImplementation :: __sll_ConstIterator const * > ( iteratorArraySize );
        for ( Size index = 0U; index < iteratorArraySize; ++ index ) {
            pSllIteratorPtrArray [ index ] = & ( * ppIterators [index] ).iterator();
            pRemovedElementArray [ index ] = * ( * pSllIteratorPtrArray [ index ] );
        }

        Size removedCount = pObject->__sll_removeConstIteratorArray ( & pSllIteratorPtrArray [0ULL], iteratorArraySize );
        for ( Size index = 0ULL; index < iteratorArraySize; ++ index ) {
            pObject->__ht_remove ( pRemovedElementArray [ index ]->key() );
        }

        cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( pRemovedElementArray );
        cds :: __hidden :: __impl :: __allocation :: __freePrimitiveArray ( pSllIteratorPtrArray );

        return removedCount;
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_MaybeUnused __CDS_OptimalInline auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: __find (
            LinkedHashMap         * pObject,
            __KeyType       const & element
    ) noexcept -> __hidden :: __impl :: __AbstractDelegateIterator < EntryType > * {

        if ( pObject->__ht_getConst ( element ) == nullptr ) {
            return Memory :: instance().create < __hidden :: __impl :: __DelegateIterator < EntryType, Iterator > > (
                    pObject->end()
            );
        }

        for ( auto iterator = pObject->begin(), end = pObject->end(); iterator != end; ++ iterator ) { /* NOLINT(clion-misra-cpp2008-8-0-1) */
            if ( cds :: meta :: equals ( iterator->key(), element ) ) {
                return Memory :: instance().create < __hidden :: __impl :: __DelegateIterator < EntryType, Iterator > > (
                        iterator
                );
            }
        }

        return Memory :: instance().create < __hidden :: __impl :: __DelegateIterator < EntryType, Iterator > > (
                pObject->end()
        );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_OptimalInline auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: __findConst (
            LinkedHashMap   const * pObject,
            __KeyType       const & element
    ) noexcept -> __hidden :: __impl :: __AbstractDelegateIterator < EntryType const > * {

        if ( pObject->__ht_getConst ( element ) == nullptr ) {
            return Memory :: instance().create < __hidden :: __impl :: __DelegateIterator < EntryType const, ConstIterator > > (
                    pObject->cend()
            );
        }

        for ( auto iterator = pObject->cbegin(), end = pObject->cend(); iterator != end; ++ iterator ) {  /* NOLINT(clion-misra-cpp2008-8-0-1) */
            if ( cds :: meta :: equals ( iterator->key(), element ) ) {
                return Memory :: instance().create < __hidden :: __impl :: __DelegateIterator < EntryType const, ConstIterator > > (
                        iterator
                );
            }
        }

        return Memory :: instance().create < __hidden :: __impl :: __DelegateIterator < EntryType const, ConstIterator > > (
                pObject->cend()
        );
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_cpplang_NonConstConstexprMemberFunction auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: __findLocal (
            LinkedHashMap         * pObject,
            __KeyType       const & element
    ) noexcept -> Iterator {

        if ( pObject->__ht_getConst ( element ) == nullptr ) {
            return pObject->end();
        }

        for ( auto iterator = pObject->begin(), end = pObject->end(); iterator != end; ++ iterator ) {    /* NOLINT(clion-misra-cpp2008-8-0-1) */
            if ( cds :: meta :: equals ( iterator->key(), element ) ) {
                return iterator;
            }
        }

        return pObject->end();
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_cpplang_ConstexprConditioned auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: __findConstLocal (
            LinkedHashMap   const * pObject,
            __KeyType       const & element
    ) noexcept -> ConstIterator {

        if ( pObject->__ht_getConst ( element ) == nullptr ) {
            return pObject->cend();
        }

        for ( auto iterator = pObject->cbegin(), end = pObject->cend(); iterator != end; ++ iterator ) {  /* NOLINT(clion-misra-cpp2008-8-0-1) */
            if ( cds :: meta :: equals ( iterator->key(), element ) ) {
                return iterator;
            }
        }

        return pObject->cend();
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_cpplang_ConstexprOverride auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: keys () const noexcept -> KeySetProxy const & {

        return this->_keySetProxy;
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_cpplang_ConstexprOverride auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: keys () noexcept -> KeySetProxy & {

        return this->_keySetProxy;
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_cpplang_ConstexprOverride auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: values () const noexcept -> ValueMutableCollectionProxy const & {

        return this->_valueMutableCollectionProxy;
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_cpplang_ConstexprOverride auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: values () noexcept -> ValueMutableCollectionProxy & {

        return this->_valueMutableCollectionProxy;
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_cpplang_ConstexprOverride auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: entries () const noexcept -> EntryMutableCollectionProxy const & {

        return this->_entryMutableCollectionProxy;
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_cpplang_ConstexprOverride auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: entries () noexcept -> EntryMutableCollectionProxy & {

        return this->_entryMutableCollectionProxy;
    }


    template <
            typename __KeyType,     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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
            typename __KeyType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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
        for ( auto iterator = map.cbegin(), end = map.cend(); iterator != end; ++ iterator ) {  /* NOLINT(clion-misra-cpp2008-8-0-1) */
            this->insert ( * iterator );
        }
    }


    template <
            typename __KeyType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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
            typename __KeyType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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
            typename __KeyType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > template <
            typename __IteratorType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __TElementType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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
            typename __KeyType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > template <
            typename __IteratorType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __TElementType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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
            typename __KeyType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > template <
            typename __TElementType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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
            typename __KeyType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > template <
            typename __TElementType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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
            typename __KeyType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > template < typename __IterableType >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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
            typename __KeyType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > template < typename __IterableType >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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
            typename __KeyType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: ~LinkedHashMap () noexcept {

        this->__ht_clear ();
        this->__sll_clear ();
    }


    template <
            typename __KeyType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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
        for ( auto iterator = map.cbegin(), end = map.cend(); iterator != end; ++ iterator ) {  /* NOLINT(clion-misra-cpp2008-8-0-1) */
            this->insert ( * iterator );
        }

        return * this;
    }


    template <
            typename __KeyType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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
            typename __KeyType,         /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,       /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_OptimalInline auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: operator = (
            std :: initializer_list < EntryType > const & initializerList
    ) noexcept -> LinkedHashMap & {

        this->__ht_clear ();
        this->__sll_clear ();
        for ( auto iterator = initializerList.begin(), end = initializerList.end(); iterator != end; ++ iterator ) {    /* NOLINT(clion-misra-cpp2008-8-0-1) */
            (void) this->insert ( * iterator );
        }

        return * this;
    }


    template <
            typename __KeyType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > template < typename __IterableType >  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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
        for ( auto iterator = iterable.begin(), end = iterable.end(); iterator != end; ++ iterator ) {  /* NOLINT(clion-misra-cpp2008-8-0-1) */
            this->insert ( * iterator );
        }

        return * this;
    }


    template <
            typename __KeyType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_OptimalInline auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: clear () noexcept -> void {

        this->__ht_clear();
        this->__sll_clear();
    }


    template <
            typename __KeyType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_cpplang_ConstexprOverride auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: size () const noexcept -> Size {

        return this->__ht_size();
    }


    template <
            typename __KeyType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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
            typename __KeyType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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

        return this->__ht_equals (map);
    }


    template <
            typename __KeyType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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

        return ! this->__ht_equals (map);
    }


    template <
            typename __KeyType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
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
            typename __KeyType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_cpplang_ConstexprOverride auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: containsValue (
            __ValueType const & value
    ) const noexcept -> bool {

        for ( auto iterator = this->__sll_cbegin (), end = this->__sll_cend (); iterator != end; ++ iterator ) {    /* NOLINT(clion-misra-cpp2008-8-0-1) */
            if ( cds :: meta :: equals ( ( * iterator )->value(), value ) ) {
                return true;
            }
        }

        return false;
    }


    template <
            typename __KeyType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_OptimalInline auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: entryAt (
            __KeyType const & key,
            bool            * pNewElementCreated
    ) noexcept -> EntryType * {

        EntryType * pNewElement = this->__ht_get (
                key,
                pNewElementCreated
        );

        if ( * pNewElementCreated ) {
            (void) new ( this->__sll_newBack () ) EntryType * ( pNewElement );
        }

        return pNewElement;
    }


    template <
            typename __KeyType,             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __ValueType,           /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            typename __Hasher               /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    > __CDS_cpplang_ConstexprOverride auto LinkedHashMap <
            __KeyType,
            __ValueType,
            __Hasher
    > :: entryAt (
            __KeyType const & key
    ) const noexcept -> EntryType const * {

        return this->__ht_getConst ( key );
    }

} /* namespace cds */

#endif /* __CDS_LINKED_HASH_MAP_IMPL_HPP__ */
