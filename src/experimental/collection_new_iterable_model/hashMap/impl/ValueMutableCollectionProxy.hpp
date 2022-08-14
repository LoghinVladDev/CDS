//
// Created by loghin on 14/08/22.
//

#ifndef __CDS_EX_HASH_MAP_VALUE_MUTABLE_COLLECTION_PROXY_IMPL_HPP__
#define __CDS_EX_HASH_MAP_VALUE_MUTABLE_COLLECTION_PROXY_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template <
                typename __KeyType,     // NOLINT(bugprone-reserved-identifier)
                typename __ValueType,   // NOLINT(bugprone-reserved-identifier)
                typename __Hasher       // NOLINT(bugprone-reserved-identifier)
        > __CDS_cpplang_ConstexprOverride auto HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: ValueMutableCollectionProxy :: __cicch_obtainGenericHandler (
                __hidden :: __impl :: __CollectionInternalRequestType requestType
        ) noexcept -> __GenericHandler {

            return this->__mcs_handlers() [ static_cast < uint32 > ( requestType ) ];
        }


        template <
                typename __KeyType,     // NOLINT(bugprone-reserved-identifier)
                typename __ValueType,   // NOLINT(bugprone-reserved-identifier)
                typename __Hasher       // NOLINT(bugprone-reserved-identifier)
        > __CDS_cpplang_ConstexprOverride auto HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: ValueMutableCollectionProxy :: __cicch_obtainGenericConstHandler (
                __hidden :: __impl :: __CollectionInternalRequestType requestType
        ) const noexcept -> __GenericConstHandler {

            return this->__mcs_constHandlers() [ static_cast < uint32 > ( requestType ) ];
        }


        template <
                typename __KeyType,     // NOLINT(bugprone-reserved-identifier)
                typename __ValueType,   // NOLINT(bugprone-reserved-identifier)
                typename __Hasher       // NOLINT(bugprone-reserved-identifier)
        > constexpr HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: ValueMutableCollectionProxy :: ValueMutableCollectionProxy (
                HashMap < __KeyType, __ValueType, __Hasher > * pMap
        ) noexcept :
                AbstractValueMutableCollectionProxy ( pMap ) {
                    
        }


        template <
                typename __KeyType,     // NOLINT(bugprone-reserved-identifier)
                typename __ValueType,   // NOLINT(bugprone-reserved-identifier)
                typename __Hasher       // NOLINT(bugprone-reserved-identifier)
        > __CDS_OptimalInline auto HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: ValueMutableCollectionProxy :: __newAddress (
                __ValueType const * pReferenceValue,
                bool              * pIsNew          // NOLINT(readability-non-const-parameter)
        ) noexcept (false) -> __ValueType * {

            (void) pReferenceValue;
            (void) pIsNew;

            throw cds :: UnsupportedOperationException (
                    cds :: String ( "Cannot insert a value into a Map Value Mutable Collection" )
            );
        }


        template <
                typename __KeyType,     // NOLINT(bugprone-reserved-identifier)
                typename __ValueType,   // NOLINT(bugprone-reserved-identifier)
                typename __Hasher       // NOLINT(bugprone-reserved-identifier)
        > __CDS_cpplang_NonConstConstexprMemberFunction auto HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: ValueMutableCollectionProxy :: begin () noexcept -> Iterator {

            return Iterator ( this->template map < HashMapBase > ()->begin() );
        }


        template <
                typename __KeyType,     // NOLINT(bugprone-reserved-identifier)
                typename __ValueType,   // NOLINT(bugprone-reserved-identifier)
                typename __Hasher       // NOLINT(bugprone-reserved-identifier)
        > __CDS_cpplang_NonConstConstexprMemberFunction auto HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: ValueMutableCollectionProxy :: end () noexcept -> Iterator {

            return Iterator ( this->template map < HashMapBase > ()->end() );
        }


        template <
                typename __KeyType,     // NOLINT(bugprone-reserved-identifier)
                typename __ValueType,   // NOLINT(bugprone-reserved-identifier)
                typename __Hasher       // NOLINT(bugprone-reserved-identifier)
        > constexpr auto HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: ValueMutableCollectionProxy :: begin () const noexcept -> ConstIterator {

            return ConstIterator ( this->template map < HashMapBase > ()->begin() );
        }


        template <
                typename __KeyType,     // NOLINT(bugprone-reserved-identifier)
                typename __ValueType,   // NOLINT(bugprone-reserved-identifier)
                typename __Hasher       // NOLINT(bugprone-reserved-identifier)
        > constexpr auto HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: ValueMutableCollectionProxy :: end () const noexcept -> ConstIterator {

            return ConstIterator ( this->template map < HashMapBase > ()->end() );
        }


        template <
                typename __KeyType,     // NOLINT(bugprone-reserved-identifier)
                typename __ValueType,   // NOLINT(bugprone-reserved-identifier)
                typename __Hasher       // NOLINT(bugprone-reserved-identifier)
        > constexpr auto HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: ValueMutableCollectionProxy :: cbegin () const noexcept -> ConstIterator {

            return ConstIterator ( this->template map < HashMapBase > ()->cbegin() );
        }


        template <
                typename __KeyType,     // NOLINT(bugprone-reserved-identifier)
                typename __ValueType,   // NOLINT(bugprone-reserved-identifier)
                typename __Hasher       // NOLINT(bugprone-reserved-identifier)
        > constexpr auto HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: ValueMutableCollectionProxy :: cend () const noexcept -> ConstIterator {

            return ConstIterator ( this->template map < HashMapBase > ()->cend() );
        }


        template <
                typename __KeyType,     // NOLINT(bugprone-reserved-identifier)
                typename __ValueType,   // NOLINT(bugprone-reserved-identifier)
                typename __Hasher       // NOLINT(bugprone-reserved-identifier)
        > __CDS_OptimalInline auto HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: ValueMutableCollectionProxy :: __remove (
                Iterator const * pIterator
        ) noexcept -> bool {

            return this->template map < HashMapBase > ()->__remove ( & pIterator->iterator() );
        }


        template <
                typename __KeyType,     // NOLINT(bugprone-reserved-identifier)
                typename __ValueType,   // NOLINT(bugprone-reserved-identifier)
                typename __Hasher       // NOLINT(bugprone-reserved-identifier)
        > __CDS_OptimalInline auto HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: ValueMutableCollectionProxy :: __removeConst (
                ConstIterator const * pIterator
        ) noexcept -> bool {

            return this->template map < HashMapBase > ()->__removeConst ( & pIterator->iterator() );
        }

    }
}

#endif // __CDS_EX_HASH_MAP_VALUE_MUTABLE_COLLECTION_PROXY_IMPL_HPP__
