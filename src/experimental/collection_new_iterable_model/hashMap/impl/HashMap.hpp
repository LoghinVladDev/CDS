/*
 * Created by loghin on 14/08/22.
 */

#ifndef __CDS_EX_HASH_MAP_IMPL_HPP__
#define __CDS_EX_HASH_MAP_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds { /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {

        template <
                typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType,   /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher       /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_cpplang_ConstexprOverride auto HashMap <
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
        > __CDS_cpplang_ConstexprOverride auto HashMap <
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
        > __CDS_cpplang_ConstexprOverride auto HashMap <
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
        > __CDS_cpplang_ConstexprOverride auto HashMap <
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
        > __CDS_cpplang_ConstexprOverride auto HashMap <
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
        > __CDS_cpplang_ConstexprOverride auto HashMap <
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
        > __CDS_cpplang_ConstexprOverride auto HashMap <
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
        > __CDS_cpplang_ConstexprOverride auto HashMap <
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
        > constexpr HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: HashMap () noexcept :
                _keySetProxy ( this ),
                _valueMutableCollectionProxy ( this ),
                _entryMutableCollectionProxy ( this ) {

        }


        template <
                typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher           /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_OptimalInline HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: HashMap (
                HashMap const & map
        ) noexcept :
                _keySetProxy ( this ),
                _valueMutableCollectionProxy ( this ),
                _entryMutableCollectionProxy ( this ),
                Implementation (
                        map,
                        & cds :: experimental :: __hidden :: __impl :: __hashMapCopyConstructor < __KeyType, __ValueType >
                ) {

        }


        template <
                typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher           /* NOLINT(bugprone-reserved-identifier) */
        > constexpr HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: HashMap (
                HashMap && map
        ) noexcept :
                _keySetProxy ( this ),
                _valueMutableCollectionProxy ( this ),
                _entryMutableCollectionProxy ( this ),
                Implementation ( std :: move ( map ) ) {

        }


        template <
                typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher           /* NOLINT(bugprone-reserved-identifier) */
        > constexpr HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: HashMap (
                __Hasher const & hasher
        ) noexcept :
                _keySetProxy ( this ),
                _valueMutableCollectionProxy ( this ),
                _entryMutableCollectionProxy ( this ),
                Implementation ( hasher ) {

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
        > __CDS_OptimalInline HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: HashMap (
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
        > __CDS_OptimalInline HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: HashMap (
                __Hasher        const & hasher,
                __IteratorType  const & begin,
                __IteratorType  const & end,
                Size                    count
        ) noexcept :
                _keySetProxy ( this ),
                _valueMutableCollectionProxy ( this ),
                _entryMutableCollectionProxy ( this ),
                Implementation ( hasher ) {

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
        > __CDS_OptimalInline HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: HashMap (
                std :: initializer_list < ElementType > const & initializerList
        ) noexcept :
                HashMap (
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
        > __CDS_OptimalInline HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: HashMap (
                __Hasher                                const & hasher,
                std :: initializer_list < ElementType > const & initializerList
        ) noexcept :
                HashMap (
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
        __CDS_OptimalInline HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: HashMap (
                __IterableType const & iterable
        ) noexcept :
                HashMap (
                        iterable.begin(),
                        iterable.end()
                ) {

        }


        template <
                typename __KeyType,             /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType,           /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher               /* NOLINT(bugprone-reserved-identifier) */
        > template < typename __IterableType >  /* NOLINT(bugprone-reserved-identifier) */
        __CDS_OptimalInline HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: HashMap (
                __Hasher        const & hasher,
                __IterableType  const & iterable
        ) noexcept :
                HashMap (
                        hasher,
                        iterable.begin(),
                        iterable.end()
                ) {

        }


        template <
                typename __KeyType,             /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType,           /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher               /* NOLINT(bugprone-reserved-identifier) */
        > HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: ~HashMap () noexcept {

            this->__ht_clear ();
        }


        template <
                typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher           /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_OptimalInline auto HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: operator = (
                HashMap const & map
        ) noexcept -> HashMap & {

            if ( this == & map ) {
                return * this;
            }

            this-> __ht_copy (
                    map,
                    & cds :: experimental :: __hidden :: __impl :: __hashMapCopyConstructor < __KeyType, __ValueType >
            );

            return * this;
        }


        template <
                typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher           /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_OptimalInline auto HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: operator = (
                HashMap && map
        ) noexcept -> HashMap & {

            if ( this == & map ) {
                return * this;
            }

            this->__ht_move ( std :: move ( map ) );
            return * this;
        }


        template <
                typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType,       /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher           /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_OptimalInline auto HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: operator = (
                std :: initializer_list < EntryType > const & initializerList
        ) noexcept -> HashMap & {

            this->__ht_clear ();
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
        __CDS_OptimalInline auto HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: operator = (
                __IterableType const & iterable
        ) noexcept -> HashMap & {

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
                typename __KeyType,             /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType,           /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher               /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_OptimalInline auto HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: clear () noexcept -> void {

            this->__ht_clear();
        }


        template <
                typename __KeyType,             /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType,           /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher               /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_cpplang_ConstexprOverride auto HashMap <
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
        > __CDS_OptimalInline auto HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: remove (
                KeyType const & key
        ) noexcept -> bool {

            return this->__ht_remove ( key );
        }


        template <
                typename __KeyType,             /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType,           /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher               /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_cpplang_ConstexprConditioned auto HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: operator == (
                HashMap const & map
        ) const noexcept -> bool {

            if ( this == & map ) {
                return true;
            }

            return this-> template __ht_equals < & __hidden :: __impl :: __hashMapEquals < __KeyType, __ValueType > > ( map );
        }


        template <
                typename __KeyType,             /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType,           /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher               /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_cpplang_ConstexprConditioned auto HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: operator != (
                HashMap const & map
        ) const noexcept -> bool {

            if ( this == & map ) {
                return false;
            }

            return ! this-> template __ht_equals < & __hidden :: __impl :: __hashMapEquals < __KeyType, __ValueType > > ( map );
        }


        template <
                typename __KeyType,             /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType,           /* NOLINT(bugprone-reserved-identifier) */
                typename __Hasher               /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_cpplang_ConstexprOverride auto HashMap <
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
        > __CDS_cpplang_ConstexprOverride auto HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: containsValue (
                __ValueType const & value
        ) const noexcept -> bool {

            for ( auto iterator = this->__ht_cbegin (), end = this->__ht_cend (); iterator != end; ++ iterator ) {
                if ( cds :: meta :: equals ( ( * iterator ).value(), value ) ) {
                    return true;
                }
            }

            return false;
        }

    }
}

#endif /* __CDS_EX_HASH_MAP_IMPL_HPP__ */
