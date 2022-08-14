//
// Created by loghin on 14/08/22.
//

#ifndef __CDS_EX_HASH_MAP_KEY_SET_PROXY_IMPL_HPP__
#define __CDS_EX_HASH_MAP_KEY_SET_PROXY_IMPL_HPP__

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
        > :: KeySetProxy :: __cicch_obtainGenericHandler (
                __hidden :: __impl :: __CollectionInternalRequestType requestType
        ) noexcept -> __GenericHandler {

            return this->__ss_handlers() [ static_cast < uint32 > ( requestType ) ];
        }


        template <
                typename __KeyType,     // NOLINT(bugprone-reserved-identifier)
                typename __ValueType,   // NOLINT(bugprone-reserved-identifier)
                typename __Hasher       // NOLINT(bugprone-reserved-identifier)
        > __CDS_cpplang_ConstexprOverride auto HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: KeySetProxy :: __cicch_obtainGenericConstHandler (
                __hidden :: __impl :: __CollectionInternalRequestType requestType
        ) const noexcept -> __GenericConstHandler {

            return this->__ss_constHandlers() [ static_cast < uint32 > ( requestType ) ];
        }


        template <
                typename __KeyType,     // NOLINT(bugprone-reserved-identifier)
                typename __ValueType,   // NOLINT(bugprone-reserved-identifier)
                typename __Hasher       // NOLINT(bugprone-reserved-identifier)
        > constexpr HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: KeySetProxy :: KeySetProxy (
                HashMap < __KeyType, __ValueType, __Hasher > * pMap
        ) noexcept :
                AbstractKeySetProxy ( pMap ) {

        }


        template <
                typename __KeyType,     // NOLINT(bugprone-reserved-identifier)
                typename __ValueType,   // NOLINT(bugprone-reserved-identifier)
                typename __Hasher       // NOLINT(bugprone-reserved-identifier)
        > __CDS_OptimalInline auto HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: KeySetProxy :: __newAddress (
                __KeyType const * pReferenceKey,
                bool            * pIsNew        // NOLINT(readability-non-const-parameter)
        ) noexcept (false) -> __KeyType const * {

            (void) pReferenceKey;
            (void) pIsNew;

            throw cds :: UnsupportedOperationException (
                    cds :: String ( "Cannot insert a value into a Map Key Set" )
            );
        }


        template <
                typename __KeyType,     // NOLINT(bugprone-reserved-identifier)
                typename __ValueType,   // NOLINT(bugprone-reserved-identifier)
                typename __Hasher       // NOLINT(bugprone-reserved-identifier)
        > constexpr auto HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: KeySetProxy :: begin () const noexcept -> ConstIterator {

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
        > :: KeySetProxy :: end () const noexcept -> ConstIterator {

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
        > :: KeySetProxy :: cbegin () const noexcept -> ConstIterator {

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
        > :: KeySetProxy :: cend () const noexcept -> ConstIterator {

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
        > :: KeySetProxy :: __removeConst (
                ConstIterator const * pIterator
        ) noexcept -> bool {

            return this->template map < HashMapBase > ()->__removeConst ( & pIterator->iterator() );
        }


        template <
                typename __KeyType,     // NOLINT(bugprone-reserved-identifier)
                typename __ValueType,   // NOLINT(bugprone-reserved-identifier)
                typename __Hasher       // NOLINT(bugprone-reserved-identifier)
        > __CDS_OptimalInline auto HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: KeySetProxy :: __findConst (
                __KeyType const & key
        ) const noexcept -> ConstIterator {

            return ConstIterator ( this->template map < HashMapBase > ()->__findConst ( key ) );
        }

    }
}

#endif // __CDS_EX_HASH_MAP_KEY_SET_PROXY_IMPL_HPP__
