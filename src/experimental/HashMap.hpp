//
// Created by loghin on 4/24/2022.
//

#ifndef __CDS_EX_HASH_MAP_HPP__
#define __CDS_EX_HASH_MAP_HPP__

#include <CDS/experimental/Map>
#include <CDS/Destructor>
#include <CDS/Extractor>
#include <CDS/CopyConstructor>
#include <CDS/Comparator>
#include <CDS/Hasher>
#include "../shared/rehashPolicy/rehashPolicy.hpp"
#include "shared/hash/HashTable.hpp"
#include "hashMap/HashTableConstructs.hpp"

namespace cds { // NOLINT(modernize-concat-nested-namespaces)

    template < typename __CollectionType > // NOLINT(bugprone-reserved-identifier)
    class Sequence;

    namespace experimental {

        template <
                typename __KeyType,                                                             // NOLINT(bugprone-reserved-identifier)
                typename __ValueType,                                                           // NOLINT(bugprone-reserved-identifier)
                typename __Hasher = FunctionHasher < __KeyType, & cds :: hash < __KeyType > >   // NOLINT(bugprone-reserved-identifier)
        > class HashMap :
                public Map < __KeyType, __ValueType >,
                protected __hidden :: __impl :: __HashTable <
                        __hidden :: __impl :: __HashMapDataNode < __KeyType, __ValueType >,
                        __KeyType,
                        FunctionExtractor <
                                __hidden :: __impl :: __HashMapDataNode < __KeyType, __ValueType >,
                                __KeyType,
                                & __hidden :: __impl :: __hashMapDataNodeKeyExtractor <
                                        __KeyType,
                                        __ValueType
                                >
                        >,
                        FunctionComparator < __KeyType, & cds :: meta :: equals < __KeyType > >,
                        __Hasher,
                        cds :: __hidden :: __impl :: __PrimeRehashPolicy,
                        FunctionDestructor <
                                __hidden :: __impl :: __HashMapDataNode < __KeyType, __ValueType >,
                                & __hidden :: __impl :: __hashMapDataNodeDestructor < __KeyType, __ValueType >
                        >
                > {

        protected:
            using __HashTableElementType =  // NOLINT(bugprone-reserved-identifier)
                    __hidden :: __impl :: __HashMapDataNode <
                            __KeyType,
                            __ValueType
                    >;

        protected:
            using __HashTableKeyType =  // NOLINT(bugprone-reserved-identifier)
                    __KeyType;

        protected:
            using __HashTableFunctionExtractor =    // NOLINT(bugprone-reserved-identifier)
                    FunctionExtractor <
                            __HashTableElementType,
                            __HashTableKeyType,
                            & __hidden :: __impl :: __hashMapDataNodeKeyExtractor <
                                    __KeyType,
                                    __ValueType
                            >
                    >;

        protected:
            using __HashTableFunctionComparator =   // NOLINT(bugprone-reserved-identifier)
                    FunctionComparator <
                            __KeyType,
                            & cds :: meta :: equals < __KeyType >
                    >;

        protected:
            using __HashTableHasher =   // NOLINT(bugprone-reserved-identifier)
                    __Hasher;

        protected:
            using __HashTableRehashPolicy =  // NOLINT(bugprone-reserved-identifier)
                    cds :: __hidden :: __impl :: __PrimeRehashPolicy;

        protected:
            using __HashTableFunctionDestructor = // NOLINT(bugprone-reserved-identifier)
                    FunctionDestructor <
                            __HashTableElementType,
                            & __hidden :: __impl :: __hashMapDataNodeDestructor <
                                    __KeyType,
                                    __ValueType
                            >
                    >;

        protected:
            using __HashTableFunctionCopyConstructor =  // NOLINT(bugprone-reserved-identifier)
                    FunctionCopyConstructor <
                            __HashTableElementType,
                            & __hidden :: __impl :: __hashMapDataNodeCopyConstructor <
                                    __KeyType,
                                    __ValueType
                            >
                    >;

        protected:
            using __HashTableFunctionEntryEquals =  // NOLINT(bugprone-reserved-identifier)
                    FunctionComparator <
                            __HashTableElementType,
                            & __hidden :: __impl :: __hashMapDataNodeEquals <
                                    __KeyType,
                                    __ValueType
                            >
                    >;

        public:
            using typename Map < __KeyType, __ValueType > :: ElementType;

        public:
            using typename Map < __KeyType, __ValueType > :: EntryType;

        public:
            using typename Map < __KeyType, __ValueType > :: KeyType;

        public:
            using typename Map < __KeyType, __ValueType > :: ValueType;

        protected:
            using typename Map < __KeyType, __ValueType > :: InitializerList;

        public:
            using typename Map < __KeyType, __ValueType > :: Iterator;

        public:
            using typename Map < __KeyType, __ValueType > :: ConstIterator;

        public:
            using typename Map < __KeyType, __ValueType > :: ReverseIterator;

        public:
            using typename Map < __KeyType, __ValueType > :: ConstReverseIterator;

        protected:
            using typename Map < __KeyType, __ValueType > :: AbstractDelegateIterator;

        protected:
            using typename Map < __KeyType, __ValueType > :: DelegateIterator;

        protected:
            using typename Map < __KeyType, __ValueType > :: DelegateConstIterator;

        protected:
            using typename Map < __KeyType, __ValueType > :: DelegateIteratorRequestType;

        protected:
            using typename Map < __KeyType, __ValueType > :: AbstractKeySetProxy;

        protected:
            using typename Map < __KeyType, __ValueType > :: AbstractValueMutableCollectionProxy;

        protected:
            using typename Map < __KeyType, __ValueType > :: AbstractEntryMutableCollectionProxy;

        protected:
            using typename Map < __KeyType, __ValueType > :: DefaultEntryMutableCollectionProxy;

        protected:
            class HashMapKeySetProxy;

        protected:
            class HashMapValueMutableCollectionProxy;

        private:
            friend class HashMapKeySetProxy;

        private:
            friend class HashMapValueMutableCollectionProxy;

        protected:
            class HashMapDelegateIterator;

        protected:
            class HashMapDelegateConstIterator;

        private:
            HashMapKeySetProxy                  _keySetProxy;

        private:
            HashMapValueMutableCollectionProxy  _valueMutableCollectionProxy;

        private:
            DefaultEntryMutableCollectionProxy  _entryMutableCollectionProxy;

        protected:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto keySetProxy () const noexcept -> AbstractKeySetProxy const & override;

        protected:
            __CDS_cpplang_ConstexprOverride auto keySetProxy () noexcept -> AbstractKeySetProxy & override;

        protected:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto valueCollectionProxy () const noexcept -> AbstractValueMutableCollectionProxy const & override;

        protected:
            __CDS_cpplang_ConstexprOverride auto valueCollectionProxy () noexcept -> AbstractValueMutableCollectionProxy & override;

        protected:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto entrySetProxy () const noexcept -> AbstractEntryMutableCollectionProxy const & override;

        protected:
            __CDS_cpplang_ConstexprOverride auto entrySetProxy () noexcept -> AbstractEntryMutableCollectionProxy & override;

        protected:
            auto delegateIterator (
                    DelegateIteratorRequestType requestType
            ) noexcept -> cds :: UniquePointer < DelegateIterator > override;

        protected:
            auto delegateConstIterator (
                    DelegateIteratorRequestType requestType
            ) const noexcept -> cds :: UniquePointer < DelegateConstIterator > override;

        public:
            constexpr HashMap () noexcept;

        public:
            template <
                    typename __TKeyType     = KeyType,      // NOLINT(bugprone-reserved-identifier)
                    typename __TValueType   = ValueType,    // NOLINT(bugprone-reserved-identifier)
                    cds :: meta :: EnableIf <
                            cds :: meta :: isCopyConstructible < __TKeyType > () &&
                            cds :: meta :: isCopyConstructible < __TValueType > ()
                    > = 0
            > __CDS_Implicit HashMap ( // NOLINT(google-explicit-constructor)
                    HashMap const & map
            ) noexcept;

        public:
            constexpr HashMap (
                    HashMap && map
            ) noexcept;

        public:
            __CDS_Explicit HashMap (
                    __Hasher const & hasher
            ) noexcept;

        public:
            __CDS_Implicit HashMap ( // NOLINT(google-explicit-constructor)
                    InitializerList const & initializerList
            ) noexcept;

        public:
            HashMap (
                    InitializerList const & initializerList,
                    __Hasher        const & hasher
            ) noexcept;

        public:
            template < typename __OtherElementType, typename __TElementType = ElementType, cds :: meta :: EnableIf < cds :: meta :: isConvertible < __OtherElementType, __TElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            __CDS_Explicit HashMap (
                    Collection < __OtherElementType >   const & collection
            ) noexcept;

        public:
            template < typename __OtherElementType, typename __TElementType = ElementType, cds :: meta :: EnableIf < cds :: meta :: isConvertible < __OtherElementType, __TElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            HashMap (
                    Collection < __OtherElementType >   const & collection,
                    __Hasher                            const & hasher
            ) noexcept;

        public:
            ~HashMap () noexcept override;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto size () const noexcept -> Size override;

        private:
            auto entryAt (
                    KeyType const & key,
                    bool          & isNew
            ) noexcept -> EntryType override;

        private:
            auto entryAt (
                    KeyType const & key,
                    bool          & found
            ) const noexcept -> EntryType const override;

        public:
            auto contains (
                    ElementType const & entry
            ) const noexcept -> bool override;

        public:
            auto containsKey (
                    KeyType const & key
            ) const noexcept -> bool override;

        public:
            auto containsValue (
                    ValueType const & value
            ) const noexcept -> bool override;

        public:
            auto remove (
                    KeyType const & key
            ) noexcept -> bool override;

        public:
            auto remove (
                    Iterator const & iterator
            ) noexcept -> bool override;

        public:
            auto remove (
                    ConstIterator const & iterator
            ) noexcept -> bool override;

        public:
            auto remove (
                    ReverseIterator const & iterator
            ) noexcept -> bool override;

        public:
            auto remove (
                    ConstReverseIterator const & iterator
            ) noexcept -> bool override;

        protected:
            auto remove (
                    Iterator    const * pIterators,
                    Size                iteratorCount
            ) noexcept -> Size override;

        protected:
            auto remove (
                    ConstIterator   const * pIterators,
                    Size                    iteratorCount
            ) noexcept -> Size override;

        protected:
            auto remove (
                    ReverseIterator const * pIterators,
                    Size                    iteratorCount
            ) noexcept -> Size override;

        protected:
            auto remove (
                    ConstReverseIterator    const * pIterators,
                    Size                            iteratorCount
            ) noexcept -> Size override;

        public:
            auto clear () noexcept -> void override;

        public:
            __CDS_NoDiscard auto operator == (
                    HashMap const & map
            ) const noexcept -> bool;

        public:
            __CDS_NoDiscard auto operator != (
                    HashMap const & map
            ) const noexcept -> bool;

        public:
            template < typename __VElementType = ElementType, cds :: meta :: EnableIf < cds :: meta :: isCopyConstructible < __VElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto operator = (
                    HashMap const & map
            ) noexcept -> HashMap &;

        public:
            auto operator = (
                    HashMap && map
            ) noexcept -> HashMap &;

        public:
            template < typename __OtherElementType, typename __TElementType = ElementType, cds :: meta :: EnableIf < cds :: meta :: isConvertible < __OtherElementType, __TElementType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto operator = (
                    Collection < __OtherElementType > const & collection
            ) noexcept -> HashMap &;

        public:
            auto sequence () & noexcept -> Sequence < HashMap < __KeyType, __ValueType, __Hasher > >;

        public:
            auto sequence () && noexcept -> Sequence < HashMap < __KeyType, __ValueType, __Hasher > >;

        public:
            auto sequence () const & noexcept -> Sequence < HashMap < __KeyType, __ValueType, __Hasher > const >;

        public:
            auto sequence () const && noexcept -> Sequence < HashMap < __KeyType, __ValueType, __Hasher > const >;
        };
    }
}

#include "map/AbstractProxy.hpp"

#include "hashMap/DelegateIterator.hpp"
#include "hashMap/DelegateConstIterator.hpp"
#include "hashMap/EntrySetProxy.hpp"
#include "hashMap/ValueMutableCollectionProxy.hpp"

#include "hashMap/keySet/DelegateConstIterator.hpp"

#include "hashMap/valueMutableCollection/DelegateIterator.hpp"
#include "hashMap/valueMutableCollection/DelegateConstIterator.hpp"

#include "../shared/memory/PrimitiveAllocation.hpp"
#include "shared/hash/impl/HashTable.hpp"

#include "map/impl/AbstractProxy.hpp"

#include "hashMap/impl/HashMap.hpp"
#include "hashMap/impl/DelegateIterator.hpp"
#include "hashMap/impl/DelegateConstIterator.hpp"
#include "hashMap/impl/EntrySetProxy.hpp"
#include "hashMap/impl/ValueMutableCollectionProxy.hpp"

#include "hashMap/keySet/impl/DelegateConstIterator.hpp"

#include "hashMap/valueMutableCollection/impl/DelegateIterator.hpp"
#include "hashMap/valueMutableCollection/impl/DelegateConstIterator.hpp"

#include "hashMap/CTAD.hpp"

#include "shared/hashMap/impl/HashMapSequence.hpp"


#endif // __CDS_EX_HASH_MAP_HPP__
