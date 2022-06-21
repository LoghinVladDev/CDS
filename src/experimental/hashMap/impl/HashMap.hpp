//
// Created by loghin on 6/18/22.
//

#ifndef __CDS_EX_HASH_MAP_IMPL_HPP__
#define __CDS_EX_HASH_MAP_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

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

            /// TODO : implement iterators
            return nullptr;
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: delegateConstIterator (
                DelegateIteratorRequestType requestType
        ) const noexcept -> cds :: UniquePointer < DelegateConstIterator > {

            /// TODO : implement iterators
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
                typename __TKeyType,
                typename __TValueType,
                cds :: meta :: EnableIf <
                        cds :: meta :: isCopyConstructible < __TKeyType > () &&
                        cds :: meta :: isCopyConstructible < __TValueType > ()
                >
        > HashMap < __KeyType, __ValueType, __Hasher > :: HashMap (
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
                this->add ( entry );
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
                this->add ( entry );
            }
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        HashMap < __KeyType, __ValueType, __Hasher > :: ~HashMap () noexcept {

            this->__clear();
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto HashMap < __KeyType, __ValueType, __Hasher > :: size () const noexcept -> Size {

            return this->__size();
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        auto HashMap < __KeyType, __ValueType, __Hasher > :: entryAt (
                KeyType const & key,
                bool          & isNew
        ) noexcept -> EntryType {

            auto pEntry = this->__get ( key, & isNew );
            return EntryType ( pEntry->_key.data(), pEntry->_value.data() );
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        auto HashMap < __KeyType, __ValueType, __Hasher > :: entryAt (
                KeyType const & key,
                bool          & found
        ) const noexcept -> EntryType const {

            auto pEntry = this->__get ( key );
            if ( pEntry == nullptr ) {
                found = false;
                return EntryType ();
            }

            return EntryType ( pEntry->_key.data(), pEntry->_value.data() );
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        auto HashMap < __KeyType, __ValueType, __Hasher > :: completeInsertion (
                EntryType * pEntry
        ) noexcept -> void {

            bool isNew;
            auto pNewEntry = this->__get ( pEntry->key(), & isNew );
            auto entry = EntryType (
                    pNewEntry->_key.data(),
                    pNewEntry->_value.data()
            );

            if ( isNew ) {
                Map < __KeyType, __ValueType > :: entryMoveOrCopyKeyTo ( & entry, pEntry );
            }

            Map < __KeyType, __ValueType > :: entryMoveOrCopyValueTo ( & entry, pEntry );
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: contains (
                ElementType const & entry
        ) const noexcept -> bool {

            return this->__at ( entry.key() ) != nullptr;
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: containsKey (
                KeyType const & key
        ) const noexcept -> bool {

            return this->__at ( key ) != nullptr;
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: containsValue (
                ValueType const & value
        ) const noexcept -> bool {

            /// TODO : after HashTable iteration impl.
            return false;
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: remove (
                KeyType const & key
        ) noexcept -> bool {

            return this->__remove ( key );
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: remove (
                Iterator const & iterator
        ) noexcept -> bool {

            /// TODO : come back to this after iterators.
            return false;
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: remove (
                ConstIterator const & iterator
        ) noexcept -> bool {

            /// TODO : come back to this after iterators.
            return false;
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: remove (
                ReverseIterator const & iterator
        ) noexcept -> bool {

            /// TODO : come back to this after iterators.
            return false;
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: remove (
                ConstReverseIterator const & iterator
        ) noexcept -> bool {

            /// TODO : come back to this after iterators.
            return false;
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: remove (
                Iterator    const * pIterators,
                Size                iteratorCount
        ) noexcept -> Size {

            /// TODO : come back to this after iterators.
            return 0ULL;
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: remove (
                ConstIterator   const * pIterators,
                Size                    iteratorCount
        ) noexcept -> Size {

            /// TODO : come back to this after iterators.
            return 0ULL;
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: remove (
                ReverseIterator const * pIterators,
                Size                    iteratorCount
        ) noexcept -> Size {

            /// TODO : come back to this after iterators.
            return 0ULL;
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: remove (
                ConstReverseIterator    const * pIterators,
                Size                            iteratorCount
        ) noexcept -> Size {

            /// TODO : come back to this after iterators.
            return 0ULL;
        }


        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto HashMap < __KeyType, __ValueType, __Hasher > :: clear () noexcept -> void {

            return this->__clear();
        }

    }
}

#endif // __CDS_EX_HASH_MAP_IMPL_HPP__
