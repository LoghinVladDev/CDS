//
// Created by loghin on 6/13/22.
//

#ifndef __CDS_HASH_SET_IMPL_HPP__
#define __CDS_HASH_SET_IMPL_HPP__

namespace cds {

    template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    auto HashSet < __ElementType, __Hasher > :: delegateConstIterator (
            DelegateIteratorRequestType requestType
    ) const noexcept -> cds :: UniquePointer < DelegateConstIterator > {

        switch ( requestType ) {
            case DelegateIteratorRequestType :: ForwardBegin:
            case DelegateIteratorRequestType :: BackwardBegin:
                return Memory :: instance().create < HashSetDelegateIterator > ( this->__ht_cbegin() );
            case DelegateIteratorRequestType :: ForwardEnd:
            case DelegateIteratorRequestType :: BackwardEnd:
                return Memory :: instance().create < HashSetDelegateIterator > ( this->__ht_cend() );
        }

        return nullptr;
    }


    template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    constexpr HashSet < __ElementType, __Hasher > :: HashSet () noexcept = default;


    template < typename __ElementType, typename __Hasher >  // NOLINT(bugprone-reserved-identifier)
    template <
            typename __TElementType,                                // NOLINT(bugprone-reserved-identifier)
            cds :: meta :: EnableIf <
                    cds :: meta :: isCopyConstructible < __TElementType > ()
            >
    > __CDS_OptimalInline HashSet < __ElementType, __Hasher > :: HashSet (
            HashSet const & set
    ) noexcept :
            Set < __ElementType > ( set ),
            __hidden :: __impl :: __HashTable <
                    __HashTableElementType,
                    __HashTableKeyType,
                    __HashTableFunctionExtractor,
                    __HashTableFunctionComparator,
                    __HashTableHasher,
                    __HashTableRehashPolicy,
                    __HashTableFunctionDestructor
            > ( set, __HashTableFunctionCopyConstructor () ) {

    }


    template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    constexpr HashSet < __ElementType, __Hasher > :: HashSet (
            HashSet && set
    ) noexcept :
            Set < __ElementType > ( std :: move ( set ) ),
            __hidden :: __impl :: __HashTable <
                    __HashTableElementType,
                    __HashTableKeyType,
                    __HashTableFunctionExtractor,
                    __HashTableFunctionComparator,
                    __HashTableHasher,
                    __HashTableRehashPolicy,
                    __HashTableFunctionDestructor
            > ( std :: move ( set ) ) {

    }


    template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline HashSet < __ElementType, __Hasher > :: HashSet (
            __Hasher const & hasher
    ) noexcept :
            __hidden :: __impl :: __HashTable <
                    __HashTableElementType,
                    __HashTableKeyType,
                    __HashTableFunctionExtractor,
                    __HashTableFunctionComparator,
                    __HashTableHasher,
                    __HashTableRehashPolicy,
                    __HashTableFunctionDestructor
            > ( hasher ) {

    }


    template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    template < typename __IteratorType, cds :: meta :: EnableIf < cds :: meta :: isIterator < __IteratorType > () > > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline HashSet < __ElementType, __Hasher > :: HashSet (
            __IteratorType      const & begin,
            __IteratorType      const & end
    ) noexcept {

        for ( auto iterator = begin; iterator != end; ++ iterator ) {
            this->insert ( * iterator );
        }
    }


    template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    template < typename __IteratorType, cds :: meta :: EnableIf < cds :: meta :: isIterator < __IteratorType > () > > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline HashSet < __ElementType, __Hasher > :: HashSet (
            __IteratorType      const & begin,
            __IteratorType      const & end,
            __Hasher    const & hasher
    ) noexcept :
            __hidden :: __impl :: __HashTable <
                    __HashTableElementType,
                    __HashTableKeyType,
                    __HashTableFunctionExtractor,
                    __HashTableFunctionComparator,
                    __HashTableHasher,
                    __HashTableRehashPolicy,
                    __HashTableFunctionDestructor
            > ( hasher ) {

        for ( auto iterator = begin; iterator != end; ++ iterator ) {
            this->insert ( * iterator );
        }
    }


    template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline HashSet < __ElementType, __Hasher > :: HashSet (
            InitializerList     const & initializerList
    ) noexcept :
            HashSet (
                    initializerList.begin(),
                    initializerList.end()
            ) {

    }


    template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline HashSet < __ElementType, __Hasher > :: HashSet (
            InitializerList     const & initializerList,
            __Hasher    const & hasher
    ) noexcept :
            HashSet (
                    initializerList.begin(),
                    initializerList.end(),
                    hasher
            ) {

    }


    template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    template < typename __OtherElementType, cds :: meta :: EnableIf < cds :: meta :: isConvertible < __OtherElementType, __ElementType > () > > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline HashSet < __ElementType, __Hasher > :: HashSet (
            Collection < __OtherElementType >   const & collection
    ) noexcept :
            HashSet (
                    collection.begin(),
                    collection.end()
            ) {

    }


    template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    template < typename __OtherElementType, cds :: meta :: EnableIf < cds :: meta :: isConvertible < __OtherElementType, __ElementType > () > > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline HashSet < __ElementType, __Hasher > :: HashSet (
            Collection < __OtherElementType >   const & collection,
            __Hasher                    const & hasher
    ) noexcept :
            HashSet (
                    collection.begin(),
                    collection.end(),
                    hasher
            ) {

    }


    template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    HashSet < __ElementType, __Hasher > :: ~HashSet () noexcept {

        this->__ht_clear();
    }


    template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_ConstexprOverride auto HashSet < __ElementType, __Hasher > :: size () const noexcept -> Size {

        return this->__ht_size();
    }


    template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto HashSet < __ElementType, __Hasher > :: remove (
            ElementType const & element
    ) noexcept -> bool {

        return this->__ht_remove ( element );
    }


    template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto HashSet < __ElementType, __Hasher > :: remove (
            ConstIterator const & iterator
    ) noexcept -> bool {

        return this->__ht_remove (
                reinterpret_cast < HashSetDelegateIterator const * > (
                        HashSet :: acquireDelegate ( iterator )
                )->iterator()
        );
    }


    template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto HashSet < __ElementType, __Hasher > :: remove (
            ConstReverseIterator const & iterator
    ) noexcept -> bool {

        return this->__ht_remove (
                reinterpret_cast < HashSetDelegateIterator const * > (
                        HashSet :: acquireDelegate ( iterator )
                )->iterator()
        );
    }


    template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    auto HashSet < __ElementType, __Hasher > :: remove (
            ConstIterator   const * pIterators,
            Size                    iteratorCount
    ) noexcept -> Size {

        Size removedCount = 0ULL;
        for ( Size index = 0ULL; index < iteratorCount; ++ index ) {
            removedCount += static_cast < Size > ( this->remove ( pIterators [ iteratorCount ] ) );
        }

        return removedCount;
    }


    template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    auto HashSet < __ElementType, __Hasher > :: remove (
            ConstReverseIterator    const * pIterators,
            Size                            iteratorCount
    ) noexcept -> Size {

        Size removedCount = 0ULL;
        for ( Size index = 0ULL; index < iteratorCount; ++ index ) {
            removedCount += static_cast < Size > ( this->remove ( pIterators [ iteratorCount ] ) );
        }

        return removedCount;
    }


    template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    auto HashSet < __ElementType, __Hasher > :: pNewInsert (
            ElementType const & referenceElement
    ) noexcept -> ElementType * {

        bool isNew;
        auto pEntry = this->__ht_get ( referenceElement, & isNew );
        return isNew ? & pEntry->data() : nullptr;
    }


    template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    auto HashSet < __ElementType, __Hasher > :: contains (
            ElementType const & element
    ) const noexcept -> bool {

        return this->__ht_get ( element ) != nullptr;
    }


    template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    auto HashSet < __ElementType, __Hasher > :: clear () noexcept -> void {

        this->__ht_clear();
    }


    template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    auto HashSet < __ElementType, __Hasher > :: operator == (
            HashSet const & set
    ) const noexcept -> bool {

        return this->__ht_equals ( set );
    }


    template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto HashSet < __ElementType, __Hasher > :: operator != (
            HashSet const & set
    ) const noexcept -> bool {

        return ! this->__ht_equals ( set );
    }


    template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    template < typename __VElementType, cds :: meta :: EnableIf < cds :: meta :: isCopyConstructible < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
    auto HashSet < __ElementType, __Hasher > :: operator = (
            HashSet const & set
    ) noexcept -> HashSet & {

        if ( this == & set ) {
            return * this;
        }

        this->__ht_assign ( set, __HashTableFunctionCopyConstructor () );
        return * this;
    }


    template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    auto HashSet < __ElementType, __Hasher > :: operator = (
            HashSet && set
    ) noexcept -> HashSet & {

        if ( this == & set ) {
            return * this;
        }

        this->__ht_assign ( std :: move ( set ) );
        return * this;
    }


    template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    template < typename __OtherElementType, cds :: meta :: EnableIf < cds :: meta :: isConvertible < __OtherElementType, __ElementType > () > > // NOLINT(bugprone-reserved-identifier)
    auto HashSet < __ElementType, __Hasher > :: operator = (
            Collection < __OtherElementType > const & collection
    ) noexcept -> HashSet & {

        if ( this == & collection ) {
            return * this;
        }

        this->__ht_clear();
        for ( auto iterator = collection.begin(), end = collection.end(); iterator != end; ++ iterator ) {
            this->insert ( * iterator );
        }

        return * this;
    }

}

#endif // __CDS_HASH_SET_IMPL_HPP__
