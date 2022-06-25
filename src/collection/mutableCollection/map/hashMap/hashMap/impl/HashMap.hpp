//
// Created by loghin on 6/18/22.
//

#ifndef __CDS_HASH_MAP_IMPL_HPP__
#define __CDS_HASH_MAP_IMPL_HPP__

namespace cds {

    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_ConstexprOverride auto HashMap < __KeyType, __ValueType, __Hasher > :: keySetProxy () const noexcept -> AbstractKeySetProxy const & {

        return this->_keySetProxy;
    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_ConstexprOverride auto HashMap < __KeyType, __ValueType, __Hasher > :: keySetProxy () noexcept -> AbstractKeySetProxy & {

        return this->_keySetProxy;
    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_ConstexprOverride auto HashMap < __KeyType, __ValueType, __Hasher > :: valueCollectionProxy () const noexcept -> AbstractValueMutableCollectionProxy const & {

        return this->_valueMutableCollectionProxy;
    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_ConstexprOverride auto HashMap < __KeyType, __ValueType, __Hasher > :: valueCollectionProxy () noexcept -> AbstractValueMutableCollectionProxy & {

        return this->_valueMutableCollectionProxy;
    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_ConstexprOverride auto HashMap < __KeyType, __ValueType, __Hasher > :: entrySetProxy () const noexcept -> AbstractEntryMutableCollectionProxy const & {

        return this->_entryMutableCollectionProxy;
    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_ConstexprOverride auto HashMap < __KeyType, __ValueType, __Hasher > :: entrySetProxy () noexcept -> AbstractEntryMutableCollectionProxy & {

        return this->_entryMutableCollectionProxy;
    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: delegateIterator (
            DelegateIteratorRequestType requestType
    ) noexcept -> cds :: UniquePointer < DelegateIterator > {

        switch ( requestType ) {
            case DelegateIteratorRequestType :: ForwardBegin:
            case DelegateIteratorRequestType :: BackwardBegin:
                return Memory :: instance().create < HashMapDelegateIterator > ( this->__ht_begin() );
            case DelegateIteratorRequestType :: ForwardEnd:
            case DelegateIteratorRequestType :: BackwardEnd:
                return Memory :: instance().create < HashMapDelegateIterator > ( this->__ht_end() );
        }

        return nullptr;
    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: delegateConstIterator (
            DelegateIteratorRequestType requestType
    ) const noexcept -> cds :: UniquePointer < DelegateConstIterator > {

        switch ( requestType ) {
            case DelegateIteratorRequestType :: ForwardBegin:
            case DelegateIteratorRequestType :: BackwardBegin:
                return Memory :: instance().create < HashMapDelegateConstIterator > ( this->__ht_cbegin() );
            case DelegateIteratorRequestType :: ForwardEnd:
            case DelegateIteratorRequestType :: BackwardEnd:
                return Memory :: instance().create < HashMapDelegateConstIterator > ( this->__ht_cend() );
        }

        return nullptr;
    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    constexpr HashMap < __KeyType, __ValueType, __Hasher > :: HashMap () noexcept :
            _keySetProxy ( this ),
            _valueMutableCollectionProxy ( this ),
            _entryMutableCollectionProxy ( this ) {

    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    template <
            typename __TKeyType,    // NOLINT(bugprone-reserved-identifier)
            typename __TValueType,  // NOLINT(bugprone-reserved-identifier)
            cds :: meta :: EnableIf <
                    cds :: meta :: isCopyConstructible < __TKeyType > () &&
                    cds :: meta :: isCopyConstructible < __TValueType > ()
            >
    > __CDS_OptimalInline HashMap < __KeyType, __ValueType, __Hasher > :: HashMap (
            HashMap const & map
    ) noexcept :
            Map < __KeyType, __ValueType > ( map ),
            __hidden :: __impl :: __HashTable <
                    __HashTableElementType,
                    __HashTableKeyType,
                    __HashTableFunctionExtractor,
                    __HashTableFunctionComparator,
                    __HashTableHasher,
                    __HashTableRehashPolicy,
                    __HashTableFunctionDestructor
            > ( map, __HashTableFunctionCopyConstructor () ),
            _keySetProxy ( this ),
            _valueMutableCollectionProxy ( this ),
            _entryMutableCollectionProxy ( this ) {

    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    constexpr HashMap < __KeyType, __ValueType, __Hasher > :: HashMap (
            HashMap && map
    ) noexcept :
            Map < __KeyType, __ValueType > ( std :: move ( map ) ),
            __hidden :: __impl :: __HashTable <
                    __HashTableElementType,
                    __HashTableKeyType,
                    __HashTableFunctionExtractor,
                    __HashTableFunctionComparator,
                    __HashTableHasher,
                    __HashTableRehashPolicy,
                    __HashTableFunctionDestructor
            > ( std :: move ( map ) ),
            _keySetProxy ( this ),
            _valueMutableCollectionProxy ( this ),
            _entryMutableCollectionProxy ( this ) {

    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline HashMap < __KeyType, __ValueType, __Hasher > :: HashMap (
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
            > ( hasher ),
            _keySetProxy ( this ),
            _valueMutableCollectionProxy ( this ),
            _entryMutableCollectionProxy ( this ) {

    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline HashMap < __KeyType, __ValueType, __Hasher > :: HashMap (
            InitializerList     const & initializerList
    ) noexcept :
            _keySetProxy ( this ),
            _valueMutableCollectionProxy ( this ),
            _entryMutableCollectionProxy ( this ) {

        for ( auto & entry : initializerList ) {
            this->insert ( entry );
        }
    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline HashMap < __KeyType, __ValueType, __Hasher > :: HashMap (
            InitializerList const & initializerList,
            __Hasher        const & hasher
    ) noexcept :
            __hidden :: __impl :: __HashTable <
                    __HashTableElementType,
                    __HashTableKeyType,
                    __HashTableFunctionExtractor,
                    __HashTableFunctionComparator,
                    __HashTableHasher,
                    __HashTableRehashPolicy,
                    __HashTableFunctionDestructor
            > ( hasher ),
            _keySetProxy ( this ),
            _valueMutableCollectionProxy ( this ),
            _entryMutableCollectionProxy ( this ) {

        for ( auto & entry : initializerList ) {
            this->insert ( entry );
        }
    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    template < typename __OtherElementType, typename __TElementType, cds :: meta :: EnableIf < cds :: meta :: isConvertible < __OtherElementType, __TElementType > () > > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline HashMap < __KeyType, __ValueType, __Hasher > :: HashMap (
            Collection < __OtherElementType >   const & collection
    ) noexcept :
            _keySetProxy ( this ),
            _valueMutableCollectionProxy ( this ),
            _entryMutableCollectionProxy ( this ) {

        for ( auto & entry : collection ) {
            this->insert ( entry );
        }
    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    template < typename __OtherElementType, typename __TElementType, cds :: meta :: EnableIf < cds :: meta :: isConvertible < __OtherElementType, __TElementType > () > > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline HashMap < __KeyType, __ValueType, __Hasher > :: HashMap (
            Collection < __OtherElementType >   const & collection,
            __Hasher                            const & hasher
    ) noexcept :
            __hidden :: __impl :: __HashTable <
                    __HashTableElementType,
                    __HashTableKeyType,
                    __HashTableFunctionExtractor,
                    __HashTableFunctionComparator,
                    __HashTableHasher,
                    __HashTableRehashPolicy,
                    __HashTableFunctionDestructor
            > ( hasher ),
            _keySetProxy ( this ),
            _valueMutableCollectionProxy ( this ),
            _entryMutableCollectionProxy ( this ) {

        for ( auto & entry : collection ) {
            this->insert ( entry );
        }
    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline HashMap < __KeyType, __ValueType, __Hasher > :: ~HashMap () noexcept {

        this->__ht_clear();
    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_ConstexprOverride auto HashMap < __KeyType, __ValueType, __Hasher > :: size () const noexcept -> Size {

        return this->__ht_size();
    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: entryAt (
            KeyType const & key,
            bool          & isNew
    ) noexcept -> EntryType * {

        return this->__ht_get ( key, & isNew );
    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: entryAt ( // NOLINT(readability-const-return-type)
            KeyType const & key
    ) const noexcept -> EntryType const * {

        return this->__ht_get ( key );
    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: contains (
            ElementType const & entry
    ) const noexcept -> bool {

        return this->__ht_at ( entry.key() ) != nullptr;
    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: containsKey (
            KeyType const & key
    ) const noexcept -> bool {

        return this->__ht_at ( key ) != nullptr;
    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: containsValue (
            ValueType const & value
    ) const noexcept -> bool {

        for ( auto iterator = this->__ht_cbegin(), end = this->__ht_cend(); iterator != end ; ++ iterator ) {
            if ( cds :: meta :: equals ( ( * iterator ).value(), value ) ) {
                return true;
            }
        }

        return false;
    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: remove (
            KeyType const & key
    ) noexcept -> bool {

        return this->__ht_remove ( key );
    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: remove (
            Iterator const & iterator
    ) noexcept -> bool {

        return this->__ht_remove (
                reinterpret_cast < HashMapDelegateIterator const * > (
                        HashMap :: acquireDelegate ( iterator )
                )->iterator()
        );
    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: remove (
            ConstIterator const & iterator
    ) noexcept -> bool {

        return this->__ht_remove (
                reinterpret_cast < HashMapDelegateConstIterator const * > (
                        HashMap :: acquireDelegate ( iterator )
                )->iterator()
        );
    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: remove (
            ReverseIterator const & iterator
    ) noexcept -> bool {

        return this->__ht_remove (
                reinterpret_cast < HashMapDelegateIterator const * > (
                        HashMap :: acquireDelegate ( iterator )
                )->iterator()
        );
    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: remove (
            ConstReverseIterator const & iterator
    ) noexcept -> bool {

        return this->__ht_remove (
                reinterpret_cast < HashMapDelegateConstIterator const * > (
                        HashMap :: acquireDelegate ( iterator )
                )->iterator()
        );
    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: remove (
            Iterator    const * pIterators,
            Size                iteratorCount
    ) noexcept -> Size {

        Size removedCount = 0ULL;
        for ( Size index = 0ULL; index < iteratorCount; ++ index ) {
            if ( this->remove ( pIterators [ index ] ) ) {
                ++ removedCount;
            }
        }

        return removedCount;
    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: remove (
            ConstIterator   const * pIterators,
            Size                    iteratorCount
    ) noexcept -> Size {

        Size removedCount = 0ULL;
        for ( Size index = 0ULL; index < iteratorCount; ++ index ) {
            if ( this->remove ( pIterators [ index ] ) ) {
                ++ removedCount;
            }
        }

        return removedCount;
    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: remove (
            ReverseIterator const * pIterators,
            Size                    iteratorCount
    ) noexcept -> Size {

        Size removedCount = 0ULL;
        for ( Size index = 0ULL; index < iteratorCount; ++ index ) {
            if ( this->remove ( pIterators [ index ] ) ) {
                ++ removedCount;
            }
        }

        return removedCount;
    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: remove (
            ConstReverseIterator    const * pIterators,
            Size                            iteratorCount
    ) noexcept -> Size {

        Size removedCount = 0ULL;
        for ( Size index = 0ULL; index < iteratorCount; ++ index ) {
            if ( this->remove ( pIterators [ index ] ) ) {
                ++ removedCount;
            }
        }

        return removedCount;
    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: clear () noexcept -> void {

        return this->__ht_clear();
    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: operator == (
            HashMap const & map
    ) const noexcept -> bool {

        return this->__ht_equals ( map, __HashTableFunctionEntryEquals () );
    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: operator != (
            HashMap const & map
    ) const noexcept -> bool {

        return ! this->__ht_equals ( map, __HashTableFunctionEntryEquals () );
    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    template < typename __VElementType, cds :: meta :: EnableIf < cds :: meta :: isCopyConstructible < __VElementType > () > > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: operator = (
            HashMap const & map
    ) noexcept -> HashMap & {

        if ( this == & map ) {
            return * this;
        }

        this->__ht_assign ( map, __HashTableFunctionCopyConstructor () );
        return * this;
    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: operator = (
            HashMap && map
    ) noexcept -> HashMap & {

        if ( this == & map ) {
            return * this;
        }

        this->__ht_assign ( map );
        return * this;
    }


    template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    template < typename __OtherElementType, typename __TElementType, cds :: meta :: EnableIf < cds :: meta :: isConvertible < __OtherElementType, __TElementType > () > > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: operator = (
            Collection < __OtherElementType > const & collection
    ) noexcept -> HashMap & {

        if ( this == & collection ) {
            return * this;
        }

        this->clear();
        for ( auto const & entry : collection ) {
            this->insert ( entry );
        }

        return * this;
    }

}

#endif // __CDS_HASH_MAP_IMPL_HPP__
