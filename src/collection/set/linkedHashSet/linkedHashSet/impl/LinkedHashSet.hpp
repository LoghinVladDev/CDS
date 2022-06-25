//
// Created by loghin on 6/25/22.
//

#ifndef __CDS_LINKED_HASH_SET_IMPL_HPP__
#define __CDS_LINKED_HASH_SET_IMPL_HPP__

namespace cds {

    template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    auto LinkedHashSet < __ElementType, __Hasher > :: delegateConstIterator (
            DelegateIteratorRequestType requestType
    ) const noexcept -> cds :: UniquePointer < DelegateConstIterator > {

        switch ( requestType ) {
            case DelegateIteratorRequestType :: ForwardBegin:
            case DelegateIteratorRequestType :: BackwardBegin:
                return Memory :: instance().create < LinkedHashSetDelegateConstIterator > ( this->__sll_cbegin() );
            case DelegateIteratorRequestType :: ForwardEnd:
            case DelegateIteratorRequestType :: BackwardEnd:
                return Memory :: instance().create < LinkedHashSetDelegateConstIterator > ( this->__sll_cend() );
        }

        return nullptr;
    }


    template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    constexpr LinkedHashSet < __ElementType, __Hasher > :: LinkedHashSet () noexcept = default;
    
    
    template < typename __ElementType, typename __Hasher >  // NOLINT(bugprone-reserved-identifier)
    template <
            typename __TElementType,                                // NOLINT(bugprone-reserved-identifier)
            cds :: meta :: EnableIf <
                    cds :: meta :: isCopyConstructible < __TElementType > ()
            >
    > __CDS_OptimalInline LinkedHashSet < __ElementType, __Hasher > :: LinkedHashSet (
            LinkedHashSet const & set
    ) noexcept :
            HashSet <
                    __ElementType,
                    __Hasher
            > ( set ),
            __hidden :: __impl :: __SingleLinkedList <
                    __SingleLinkedListElementType,
                    __SingleLinkedListElementComparator,
                    __SingleLinkedListElementDestructor
            > ( set ) {
    
    }
    
    
    template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    constexpr LinkedHashSet < __ElementType, __Hasher > :: LinkedHashSet (
            LinkedHashSet && set
    ) noexcept :
            HashSet <
                    __ElementType,
                    __Hasher
            > ( std :: move ( set ) ),
            __hidden :: __impl :: __SingleLinkedList <
                    __SingleLinkedListElementType,
                    __SingleLinkedListElementComparator,
                    __SingleLinkedListElementDestructor
            > ( std :: move ( set ) ) {
    
    }
    
    
    template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline LinkedHashSet < __ElementType, __Hasher > :: LinkedHashSet (
            __Hasher const & hasher
    ) noexcept :
            HashSet <
                    __ElementType,
                    __Hasher
            > ( hasher ) {
    
    }
    
    
    template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    template < typename __IteratorType, cds :: meta :: EnableIf < cds :: meta :: isIterator < __IteratorType > () > > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline LinkedHashSet < __ElementType, __Hasher > :: LinkedHashSet (
            __IteratorType      const & begin,
            __IteratorType      const & end
    ) noexcept {
    
        for ( auto iterator = begin; iterator != end; ++ iterator ) {
            this->insert ( * iterator );
        }
    }
    
    
    template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    template < typename __IteratorType, cds :: meta :: EnableIf < cds :: meta :: isIterator < __IteratorType > () > > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline LinkedHashSet < __ElementType, __Hasher > :: LinkedHashSet (
            __IteratorType      const & begin,
            __IteratorType      const & end,
            __Hasher    const & hasher
    ) noexcept :
            HashSet <
                    __ElementType,
                    __Hasher
            > ( hasher ) {
    
        for ( auto iterator = begin; iterator != end; ++ iterator ) {
            this->insert ( * iterator );
        }
    }
    
    
    template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline LinkedHashSet < __ElementType, __Hasher > :: LinkedHashSet (
            InitializerList     const & initializerList
    ) noexcept :
            LinkedHashSet (
                    initializerList.begin(),
                    initializerList.end()
            ) {
    
    }
    
    
    template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline LinkedHashSet < __ElementType, __Hasher > :: LinkedHashSet (
            InitializerList     const & initializerList,
            __Hasher    const & hasher
    ) noexcept :
            LinkedHashSet (
                    initializerList.begin(),
                    initializerList.end(),
                    hasher
            ) {
    
    }
    
    
    template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    template < typename __OtherElementType, cds :: meta :: EnableIf < cds :: meta :: isConvertible < __OtherElementType, __ElementType > () > > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline LinkedHashSet < __ElementType, __Hasher > :: LinkedHashSet (
            Collection < __OtherElementType >   const & collection
    ) noexcept :
            LinkedHashSet (
                    collection.begin(),
                    collection.end()
            ) {
    
    }
    
    
    template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    template < typename __OtherElementType, cds :: meta :: EnableIf < cds :: meta :: isConvertible < __OtherElementType, __ElementType > () > > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline LinkedHashSet < __ElementType, __Hasher > :: LinkedHashSet (
            Collection < __OtherElementType >   const & collection,
            __Hasher                    const & hasher
    ) noexcept :
            LinkedHashSet (
                    collection.begin(),
                    collection.end(),
                    hasher
            ) {
    
    }
    
    
    template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    LinkedHashSet < __ElementType, __Hasher > :: ~LinkedHashSet () noexcept {

        this->__sll_clear();
        this->__ht_clear();
    }
    
    
    template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto LinkedHashSet < __ElementType, __Hasher > :: remove (
            ElementType const & element
    ) noexcept -> bool {

        auto htIterator = this->__ht_find ( element );

        return
                this->__sll_remove ( & ( * htIterator ) ) &&
                this->__ht_remove ( htIterator );
    }
    
    
    template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto LinkedHashSet < __ElementType, __Hasher > :: remove (
            ConstIterator const & iterator
    ) noexcept -> bool {

        auto const & rootIterator = reinterpret_cast < LinkedHashSetDelegateConstIterator const * > (
                LinkedHashSet :: acquireDelegate ( iterator )
        )->iterator();

        return
                this->__ht_remove ( * ( * rootIterator ) ) &&
                this->__sll_remove ( rootIterator );
    }
    
    
    template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto LinkedHashSet < __ElementType, __Hasher > :: remove (
            ConstReverseIterator const & iterator
    ) noexcept -> bool {

        auto const & rootIterator = reinterpret_cast < LinkedHashSetDelegateConstIterator const * > (
                LinkedHashSet :: acquireDelegate ( iterator )
        )->iterator();

        return
                this->__ht_remove ( * ( * rootIterator ) ) &&
                this->__sll_remove ( rootIterator );
    }
    
    
    template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    auto LinkedHashSet < __ElementType, __Hasher > :: pNewInsert (
            ElementType const & referenceElement
    ) noexcept -> ElementType * {
    
        bool isNew;
        auto pEntry = this->__ht_get ( referenceElement, & isNew );

        if ( isNew ) {
            new ( this->__sll_newBack() ) __ElementType * ( pEntry );
        }

        return isNew ? pEntry : nullptr;
    }
    
    
    template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    auto LinkedHashSet < __ElementType, __Hasher > :: clear () noexcept -> void {

        this->__sll_clear();
        this->__ht_clear();
    }
    
    
    template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    auto LinkedHashSet < __ElementType, __Hasher > :: operator == (
            LinkedHashSet const & set
    ) const noexcept -> bool {
    
        return this->__ht_equals ( set );
    }
    
    
    template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto LinkedHashSet < __ElementType, __Hasher > :: operator != (
            LinkedHashSet const & set
    ) const noexcept -> bool {
    
        return ! this->__ht_equals ( set );
    }
    
    
    template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    template < typename __VElementType, cds :: meta :: EnableIf < cds :: meta :: isCopyConstructible < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
    auto LinkedHashSet < __ElementType, __Hasher > :: operator = (
            LinkedHashSet const & set
    ) noexcept -> LinkedHashSet & {
    
        if ( this == & set ) {
            return * this;
        }
    
        this->clear();
        for ( auto const & entry : set ) {
            this->insert ( entry );
        }
    
        return * this;
    }
    
    
    template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    auto LinkedHashSet < __ElementType, __Hasher > :: operator = (
            LinkedHashSet && set
    ) noexcept -> LinkedHashSet & {
    
        if ( this == & set ) {
            return * this;
        }
    
        this->move ( std :: move ( set ) );
        return * this;
    }
    
    
    template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_VirtualConstexpr auto LinkedHashSet < __ElementType, __Hasher > :: move (
            HashSet < __ElementType, __Hasher > && hashSet
    ) noexcept -> LinkedHashSet & {

        this->__sll_clear();
        this->__ht_assign ( std :: move ( hashSet ) );

        for ( auto it = this->__ht_begin(), end = this->__ht_end(); it != end; ++ it ) {
            new ( this->__sll_newBack () ) __ElementType * ( & ( * it ) );
        }

        return * this;
    }
    
    
    template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    template < typename __OtherElementType, cds :: meta :: EnableIf < cds :: meta :: isConvertible < __OtherElementType, __ElementType > () > > // NOLINT(bugprone-reserved-identifier)
    auto LinkedHashSet < __ElementType, __Hasher > :: operator = (
            Collection < __OtherElementType > const & collection
    ) noexcept -> LinkedHashSet & {
    
        if ( this == & collection ) {
            return * this;
        }
    
        this->clear();
        for ( auto iterator = collection.begin(), end = collection.end(); iterator != end; ++ iterator ) {
            this->insert ( * iterator );
        }
    
        return * this;
    }

}

#endif // __CDS_LINKED_HASH_SET_IMPL_HPP__
