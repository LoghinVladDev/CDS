//
// Created by stefan on 26.09.2022.
//

#ifndef __CDS_EX_TREE_MAP_IMPL_HPP__
#define __CDS_EX_TREE_MAP_IMPL_HPP__    /* NOLINT(bugprone-reserved-identifier) */

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {

        template <
                typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_cpplang_ConstexprOverride auto TreeMap <
                __KeyType,
                __ValueType
        > :: __cicch_obtainGenericHandler (         /* NOLINT(bugprone-reserved-identifier) */
                cds :: __hidden :: __impl :: __CollectionInternalRequestType requestType
        ) noexcept -> __GenericHandler {

            return this->__ms_handlers() [ static_cast < uint32 > ( requestType ) ];
        }

        template <
                typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_cpplang_ConstexprOverride auto TreeMap <
                __KeyType,
                __ValueType
        > :: __cicch_obtainGenericConstHandler (         /* NOLINT(bugprone-reserved-identifier) */
                cds :: __hidden :: __impl :: __CollectionInternalRequestType requestType
        ) const noexcept -> __GenericConstHandler {

            return this->__ms_constHandlers() [ static_cast < uint32 > ( requestType ) ];
        }


        template <
                typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_cpplang_ConstexprOverride auto TreeMap <
                __KeyType,
                __ValueType
        > :: keys () const noexcept -> KeySetProxy const & {

            return this->_keySetProxy;
        }


        template <
                typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_cpplang_ConstexprOverride auto TreeMap <
                __KeyType,
                __ValueType
        > :: keys () noexcept -> KeySetProxy & {

            return this->_keySetProxy;
        }


        template <
                typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_cpplang_ConstexprOverride auto TreeMap <
                __KeyType,
                __ValueType
        > :: values () const noexcept -> ValueMutableCollectionProxy const & {

            return this->_valueMutableCollectionProxy;
        }


        template <
                typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_cpplang_ConstexprOverride auto TreeMap <
                __KeyType,
                __ValueType
        > :: values () noexcept -> ValueMutableCollectionProxy & {

            return this->_valueMutableCollectionProxy;
        }


        template <
                typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_cpplang_ConstexprOverride auto TreeMap <
                __KeyType,
                __ValueType
        > :: entries () const noexcept -> EntryMutableCollectionProxy const & {

            return this->_entryMutableCollectionProxy;
        }


        template <
                typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_cpplang_ConstexprOverride auto TreeMap <
                __KeyType,
                __ValueType
        > :: entries () noexcept -> EntryMutableCollectionProxy & {

            return this->_entryMutableCollectionProxy;
        }


        template <
                typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
        > constexpr TreeMap <
                __KeyType,
                __ValueType
        > :: TreeMap () noexcept :
                _keySetProxy ( this ),
                _valueMutableCollectionProxy ( this ),
                _entryMutableCollectionProxy ( this ) {

        }


        template <
                typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
        > TreeMap <
                __KeyType,
                __ValueType
        > :: TreeMap (
                TreeMap const & map
        ) noexcept :
                _keySetProxy ( this ),
                _valueMutableCollectionProxy ( this ),
                _entryMutableCollectionProxy ( this ) {

            this-> template __rbt_copyCleared < & __hidden :: __impl :: __treeMapCopyConstructor < __KeyType, __ValueType > > ( map );
        }


        template <
                typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
        > constexpr TreeMap <
                __KeyType,
                __ValueType
        > :: TreeMap (
                TreeMap && map
        ) noexcept :
                _keySetProxy ( this ),
                _valueMutableCollectionProxy ( this ),
                _entryMutableCollectionProxy ( this ),
                Implementation ( std :: move ( map ) ) {

        }


        template <
                typename __KeyType,     /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType    /* NOLINT(bugprone-reserved-identifier) */
        > template <
                typename __TElementType,        /* NOLINT(bugprone-reserved-identifier) */
                typename __IteratorType,        /* NOLINT(bugprone-reserved-identifier) */
                cds :: meta :: EnableIf <
                        cds :: meta :: isCopyConstructible < __TElementType > ()
                >
        > TreeMap <
                __KeyType,
                __ValueType
        > :: TreeMap (
                __IteratorType const & begin,
                __IteratorType const & end,
                Size                   count
        ) noexcept :
                _keySetProxy ( this ),
                _valueMutableCollectionProxy ( this ),
                _entryMutableCollectionProxy ( this ) {

                (void) count;
                for ( auto iterator = begin; iterator != end; ++ iterator ) {
                    this->insert ( * iterator );
                }
        }


        template <
                typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType        /* NOLINT(bugprone-reserved-identifier) */
        > template <
                typename __TElementType,    /* NOLINT(bugprone-reserved-identifier) */
                cds :: meta :: EnableIf <
                        cds :: meta :: isCopyConstructible < __TElementType > ()
                >
        > __CDS_OptimalInline TreeMap <
                __KeyType,
                __ValueType
        > :: TreeMap (
                std :: initializer_list < __ElementType > const & initializer_list
        ) noexcept :
                TreeMap (
                        initializer_list.begin(),
                        initializer_list.end(),
                        initializer_list.size()
                ) {

        }


        template <
                typename __KeyType,             /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType            /* NOLINT(bugprone-reserved-identifier) */
        > template < typename __IterableType >  /* NOLINT(bugprone-reserved-identifier) */
        __CDS_OptimalInline TreeMap <
                __KeyType,
                __ValueType
        > :: TreeMap (
                __IterableType const & iterable
        ) noexcept :
                TreeMap (
                        iterable.begin(),
                        iterable.end()
                ) {

        }


        template <
                typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType        /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_cpplang_ConstexprOverride auto TreeMap <
                __KeyType,
                __ValueType
        > :: size () const noexcept -> Size {

            return this->__rbt_size();
        }


        template <
                typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType        /* NOLINT(bugprone-reserved-identifier) */
        > auto TreeMap <
                __KeyType,
                __ValueType
        > :: clear () noexcept -> void {

            this->__rbt_clear();
        }


        template <
                typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType        /* NOLINT(bugprone-reserved-identifier) */
        > auto TreeMap <
                __KeyType,
                __ValueType
        > :: remove (
                __KeyType const & key
        ) noexcept -> bool {

            this->__rbt_remove ( key );
        }


        template <
                typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType        /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_cpplang_VirtualConstexpr auto TreeMap <
                __KeyType,
                __ValueType
        > :: containsKey (
                __KeyType const & key
        ) const noexcept -> bool {

            return this->__rbt_get ( key ) != nullptr;
        }


        template <
                typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType        /* NOLINT(bugprone-reserved-identifier) */
        > __CDS_cpplang_VirtualConstexpr auto TreeMap <
                __KeyType,
                __ValueType
        > :: containsValue (
                __ValueType const & value
        ) const noexcept -> bool {

            for ( auto it = this->__rbt_cbegin(); it != this->__rbt_cend(); ++ it ) {
                if ( cds :: meta :: equals ( ( * it ).value(), value ) == true )
                    return true;
            }

            return false;
        }


        template <
                typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType        /* NOLINT(bugprone-reserved-identifier) */
        > auto TreeMap <
                __KeyType,
                __ValueType
        > :: entryAt (
                __KeyType const & key,
                bool            * pNewElementCreated
        ) noexcept -> EntryType * {

            return this->__rbt_get ( key, pNewElementCreated );
        }


        template <
                typename __KeyType,         /* NOLINT(bugprone-reserved-identifier) */
                typename __ValueType        /* NOLINT(bugprone-reserved-identifier) */
        > auto TreeMap <
                __KeyType,
                __ValueType
        > :: entryAt (
                __KeyType const & key
        ) const noexcept -> EntryType const * {

            return this->__rbt_get ( key );
        }
    }
}
#endif //__CDS_EX_TREE_MAP_IMPL_HPP__
