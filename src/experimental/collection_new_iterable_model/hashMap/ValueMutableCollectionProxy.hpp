//
// Created by loghin on 14/08/22.
//

#ifndef __CDS_EX_HASH_MAP_VALUE_MUTABLE_COLLECTION_PROXY_HPP__
#define __CDS_EX_HASH_MAP_VALUE_MUTABLE_COLLECTION_PROXY_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ServerType,                      // NOLINT(bugprone-reserved-identifier)
                        typename __KeyType,                         // NOLINT(bugprone-reserved-identifier)
                        typename __ValueType,                       // NOLINT(bugprone-reserved-identifier)
                        typename __Hasher,                          // NOLINT(bugprone-reserved-identifier)
                        typename __HashMap =                        // NOLINT(bugprone-reserved-identifier)
                                cds :: experimental :: HashMap <    // NOLINT(bugprone-reserved-identifier)
                                        __KeyType,
                                        __ValueType,
                                        __Hasher
                                >
                > using __HashMapValueProxyServer =                  // NOLINT(bugprone-reserved-identifier)
                        __MutableCollectionServer <
                                __ServerType,
                                __ValueType
                        >;


                template <
                        typename __DecoratedIteratorType,                           // NOLINT(bugprone-reserved-identifier)
                        typename __ValueAtType                                      // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __hashMapValueSetProxyIteratorDecoratorValueAt (   // NOLINT(bugprone-reserved-identifier)
                        __DecoratedIteratorType const & iterator
                ) noexcept -> __ValueAtType & {

                    return ( * iterator ).value ();
                }


                template <
                        typename __KeyType,             // NOLINT(bugprone-reserved-identifier)
                        typename __ValueType,           // NOLINT(bugprone-reserved-identifier)
                        typename __Hasher               // NOLINT(bugprone-reserved-identifier)
                > using __HashMapValueProxyIterator =   // NOLINT(bugprone-reserved-identifier)
                        ForwardIteratorGenericDecorator <
                                typename __HashMapImplementation < __KeyType, __ValueType, __Hasher > :: __ht_Iterator,
                                __ValueType,
                                & __hashMapValueSetProxyIteratorDecoratorValueAt <
                                        typename __HashMapImplementation < __KeyType, __ValueType, __Hasher > :: __ht_Iterator,
                                        __ValueType
                                >
                        >;


                template <
                        typename __KeyType,                 // NOLINT(bugprone-reserved-identifier)
                        typename __ValueType,               // NOLINT(bugprone-reserved-identifier)
                        typename __Hasher                   // NOLINT(bugprone-reserved-identifier)
                > using __HashMapValueProxyConstIterator =  // NOLINT(bugprone-reserved-identifier)
                        ForwardIteratorGenericDecorator <
                                typename __HashMapImplementation < __KeyType, __ValueType, __Hasher > :: __ht_ConstIterator,
                                __ValueType const,
                                & __hashMapValueSetProxyIteratorDecoratorValueAt <
                                        typename __HashMapImplementation < __KeyType, __ValueType, __Hasher > :: __ht_ConstIterator,
                                        __ValueType const
                                >
                        >;


                template <
                        typename __ServerType,                      // NOLINT(bugprone-reserved-identifier)
                        typename __KeyType,                         // NOLINT(bugprone-reserved-identifier)
                        typename __ValueType,                       // NOLINT(bugprone-reserved-identifier)
                        typename __Hasher,                          // NOLINT(bugprone-reserved-identifier)
                        typename __HashMap =                        // NOLINT(bugprone-reserved-identifier)
                                cds :: experimental :: HashMap <    // NOLINT(bugprone-reserved-identifier)
                                        __KeyType,
                                        __ValueType,
                                        __Hasher
                                >
                > using __HashMapValueProxyDelegateIterableServer =   // NOLINT(bugprone-reserved-identifier)
                        __DelegateIterableServer <
                                __ServerType,
                                __ValueType,
                                true,
                                false,
                                __HashMapValueProxyIterator < __KeyType, __ValueType, __Hasher >,
                                __HashMapValueProxyConstIterator < __KeyType, __ValueType, __Hasher >,
                                void,
                                void
                        >;

            }
        }

        template <
                typename __KeyType,     // NOLINT(bugprone-reserved-identifier)
                typename __ValueType,   // NOLINT(bugprone-reserved-identifier)
                typename __Hasher       // NOLINT(bugprone-reserved-identifier)
        > class HashMap <
                __KeyType,
                __ValueType,
                __Hasher
        > :: ValueMutableCollectionProxy :
                public AbstractValueMutableCollectionProxy,
                protected __hidden :: __impl :: __HashMapValueProxyServer < ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher >,
                public __hidden :: __impl :: __HashMapValueProxyDelegateIterableServer < ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher > {

        protected:  using HashMapBase   = HashMap < __KeyType, __ValueType, __Hasher >;
        protected:  using Server        = __hidden :: __impl :: __HashMapValueProxyServer < ValueMutableCollectionProxy, __KeyType, __ValueType, __Hasher >;

        protected:  using typename AbstractValueMutableCollectionProxy :: __GenericHandler;         // NOLINT(bugprone-reserved-identifier)
        protected:  using typename AbstractValueMutableCollectionProxy :: __GenericConstHandler;    // NOLINT(bugprone-reserved-identifier)

        public:     using Iterator      = __hidden :: __impl :: __HashMapValueProxyIterator < __KeyType, __ValueType, __Hasher >;
        public:     using ConstIterator = __hidden :: __impl :: __HashMapValueProxyConstIterator < __KeyType, __ValueType, __Hasher >;

        protected:  friend Server;

        protected:  using AbstractValueMutableCollectionProxy :: begin;
        protected:  using AbstractValueMutableCollectionProxy :: end;
        protected:  using AbstractValueMutableCollectionProxy :: cbegin;
        protected:  using AbstractValueMutableCollectionProxy :: cend;

        private:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __cicch_obtainGenericHandler ( // NOLINT(bugprone-reserved-identifier)
                    __hidden :: __impl :: __CollectionInternalRequestType requestType
            ) noexcept -> __GenericHandler override;

        private:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __cicch_obtainGenericConstHandler (    // NOLINT(bugprone-reserved-identifier)
                    __hidden :: __impl :: __CollectionInternalRequestType requestType
            ) const noexcept -> __GenericConstHandler override;

        public:
            __CDS_Explicit constexpr ValueMutableCollectionProxy (
                    HashMap < __KeyType, __ValueType, __Hasher > * pMap
            ) noexcept;

        public:
            auto __newAddress ( // NOLINT(bugprone-reserved-identifier)
                    __ValueType const * pReferenceValue,
                    bool              * pIsNew
            ) noexcept (false) -> __ValueType *;

        public:
            __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto begin () noexcept -> Iterator;

        public:
            __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto end () noexcept -> Iterator;

        public:
            __CDS_NoDiscard constexpr auto begin () const noexcept -> ConstIterator;

        public:
            __CDS_NoDiscard constexpr auto end () const noexcept -> ConstIterator;

        public:
            __CDS_NoDiscard constexpr auto cbegin () const noexcept -> ConstIterator;

        public:
            __CDS_NoDiscard constexpr auto cend () const noexcept -> ConstIterator;

        public:
            auto __remove ( // NOLINT(bugprone-reserved-identifier)
                    Iterator const * iterator
            ) noexcept -> bool;

        public:
            auto __removeConst (    // NOLINT(bugprone-reserved-identifier)
                    ConstIterator const * iterator
            ) noexcept -> bool;
        };

    }
}

#endif // __CDS_EX_HASH_MAP_VALUE_MUTABLE_COLLECTION_PROXY_HPP__
