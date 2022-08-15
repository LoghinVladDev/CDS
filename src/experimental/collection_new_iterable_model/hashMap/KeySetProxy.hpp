//
// Created by loghin on 14/08/22.
//

#ifndef __CDS_EX_HASH_MAP_KEY_SET_PROXY_HPP__
#define __CDS_EX_HASH_MAP_KEY_SET_PROXY_HPP__

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
                > using __HashMapKeyProxyServer =                   // NOLINT(bugprone-reserved-identifier)
                        __SetServer <
                                __ServerType,
                                __KeyType const
                        >;


                template <
                        typename __DecoratedIteratorType,                       // NOLINT(bugprone-reserved-identifier)
                        typename __ValueAtType                                  // NOLINT(bugprone-reserved-identifier)
                > constexpr auto __hashMapKeySetProxyIteratorDecoratorValueAt ( // NOLINT(bugprone-reserved-identifier)
                        __DecoratedIteratorType const & iterator
                ) noexcept -> __ValueAtType & {

                    return ( * iterator ).key ();
                }


                template <
                        typename __KeyType,                 // NOLINT(bugprone-reserved-identifier)
                        typename __ValueType,               // NOLINT(bugprone-reserved-identifier)
                        typename __Hasher                   // NOLINT(bugprone-reserved-identifier)
                > using __HashMapKeyProxyConstIterator =    // NOLINT(bugprone-reserved-identifier)
                        ForwardIteratorGenericDecorator <
                                typename __HashMapImplementation < __KeyType, __ValueType, __Hasher > :: __ht_ConstIterator,
                                __KeyType const,
                                & __hashMapKeySetProxyIteratorDecoratorValueAt <
                                        typename __HashMapImplementation < __KeyType, __ValueType, __Hasher > :: __ht_ConstIterator,
                                        __KeyType const
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
                > using __HashMapKeyProxyDelegateIterableServer =   // NOLINT(bugprone-reserved-identifier)
                        __DelegateIterableServer <
                                __ServerType,
                                __KeyType const,
                                false,
                                false,
                                void,
                                __HashMapKeyProxyConstIterator < __KeyType, __ValueType, __Hasher >,
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
        > :: KeySetProxy :
                public AbstractKeySetProxy,
                protected __hidden :: __impl :: __HashMapKeyProxyServer < KeySetProxy, __KeyType, __ValueType, __Hasher >,
                public __hidden :: __impl :: __HashMapKeyProxyDelegateIterableServer < KeySetProxy, __KeyType, __ValueType, __Hasher > {

        protected:  using HashMapBase   = HashMap < __KeyType, __ValueType, __Hasher >;
        protected:  using Server        = __hidden :: __impl :: __HashMapKeyProxyServer < KeySetProxy, __KeyType, __ValueType, __Hasher >;

        protected:  using typename AbstractKeySetProxy :: __GenericHandler;         // NOLINT(bugprone-reserved-identifier)
        protected:  using typename AbstractKeySetProxy :: __GenericConstHandler;    // NOLINT(bugprone-reserved-identifier)

        public:     using ConstIterator = __hidden :: __impl :: __HashMapKeyProxyConstIterator < __KeyType, __ValueType, __Hasher >;

        protected:  friend Server;

        protected:  using AbstractKeySetProxy :: begin;
        protected:  using AbstractKeySetProxy :: end;
        protected:  using AbstractKeySetProxy :: cbegin;
        protected:  using AbstractKeySetProxy :: cend;

        private:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __cicch_obtainGenericHandler ( // NOLINT(bugprone-reserved-identifier)
                    __hidden :: __impl :: __CollectionInternalRequestType requestType
            ) noexcept -> __GenericHandler override;

        private:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto __cicch_obtainGenericConstHandler (    // NOLINT(bugprone-reserved-identifier)
                    __hidden :: __impl :: __CollectionInternalRequestType requestType
            ) const noexcept -> __GenericConstHandler override;

        public:
            __CDS_Explicit constexpr KeySetProxy (
                    HashMap < __KeyType, __ValueType, __Hasher > * pMap
            ) noexcept;

        public:
            KeySetProxy (
                    KeySetProxy const &
            ) noexcept = delete;

        public:
            KeySetProxy (
                    KeySetProxy &&
            ) noexcept = delete;

        public:
            __CDS_cpplang_ConstexprDestructor ~KeySetProxy() noexcept override;

        public:
            auto operator = (
                    KeySetProxy const &
            ) noexcept -> KeySetProxy & = delete;

        public:
            auto operator = (
                    KeySetProxy &&
            ) noexcept -> KeySetProxy & = delete;

        public:
            __CDS_NoDiscard constexpr auto begin () const noexcept -> ConstIterator;

        public:
            __CDS_NoDiscard constexpr auto end () const noexcept -> ConstIterator;

        public:
            __CDS_NoDiscard constexpr auto cbegin () const noexcept -> ConstIterator;

        public:
            __CDS_NoDiscard constexpr auto cend () const noexcept -> ConstIterator;

        protected:
            auto __removeConst (    // NOLINT(bugprone-reserved-identifier)
                    ConstIterator const * pIterator
            ) noexcept -> bool;

        protected:
            auto __findConst (    // NOLINT(bugprone-reserved-identifier)
                    __KeyType const & key
            ) const noexcept -> ConstIterator;

        private:
            __CDS_NoDiscard auto __equals ( // NOLINT(bugprone-reserved-identifier)
                    KeySetProxy const & set
            ) const noexcept -> bool;

        public:
            __CDS_NoDiscard auto operator == (
                    KeySetProxy const & set
            ) const noexcept -> bool;

        public:
            __CDS_NoDiscard auto operator != (
                    KeySetProxy const & set
            ) const noexcept -> bool;
        };

    }
}

#endif // __CDS_EX_HASH_MAP_KEY_SET_PROXY_HPP__
