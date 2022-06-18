//
// Created by loghin on 4/24/2022.
//

#ifndef __CDS_EX_HASH_MAP_HPP__
#define __CDS_EX_HASH_MAP_HPP__

#include <CDS/experimental/Map>
//#include "map/baseMap/BaseMap.hpp"
#include <CDS/experimental/HashSet>
#include <CDS/experimental/Array>

//#include "shared/Node.hpp"
//#include "map/entryArray/EntryArray.hpp"
//#include "map/entryArray/Associator.hpp"
//#include "hashMap/Associator.hpp"

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template <
                typename __KeyType, // NOLINT(bugprone-reserved-identifier)
                typename __ValueType, // NOLINT(bugprone-reserved-identifier)
                typename __HashCalculator = cds :: utility :: MediumCollisionDefaultHashFunction < __KeyType > // NOLINT(bugprone-reserved-identifier)
        > class HashMap : public Map < __KeyType, __ValueType > {

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
            using typename Map < __KeyType, __ValueType > :: AbstractValueCollectionProxy;

        protected:
            using typename Map < __KeyType, __ValueType > :: AbstractEntrySetProxy;

        protected:
            class HashMapKeySetProxy;

        protected:
            class HashMapValueCollectionProxy;

        protected:
            class HashMapEntrySetProxy;

        private:
            __HashCalculator            _hashCalculator;

        private:
            HashMapKeySetProxy          _keySetProxy;

        private:
            HashMapValueCollectionProxy _valueCollectionProxy;

        private:
            HashMapEntrySetProxy        _entrySetProxy;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto keySetProxy () const noexcept -> AbstractKeySetProxy const & override;

        public:
            __CDS_cpplang_ConstexprOverride auto keySetProxy () noexcept -> AbstractKeySetProxy & override;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto valueCollectionProxy () const noexcept -> AbstractValueCollectionProxy const & override;

        public:
            __CDS_cpplang_ConstexprOverride auto valueCollectionProxy () noexcept -> AbstractValueCollectionProxy & override;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto entrySetProxy () const noexcept -> AbstractEntrySetProxy const & override;

        public:
            __CDS_cpplang_ConstexprOverride auto entrySetProxy () noexcept -> AbstractEntrySetProxy & override;

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
            HashMap (
                    HashMap const & map
            ) noexcept;

        public:
            constexpr HashMap (
                    HashMap && map
            ) noexcept;

        public:
            ~HashMap () noexcept override;

        public:
            __CDS_NoDiscard auto get (
                    KeyType const & key
            ) noexcept -> ValueType & override;

        public:
            __CDS_NoDiscard auto at (
                    KeyType const & key
            ) noexcept (false) -> ValueType & override;

        public:
            __CDS_NoDiscard auto at (
                    KeyType const & key
            ) const noexcept (false) -> ValueType const & override;

        public:
            auto pNewInsert (
                    ElementType const & referenceElement
            ) noexcept -> ElementType * & override;

        public:
            auto pNewInsertPost () noexcept -> void override;

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
        };
    }
}

#include "hashMap/KeySetProxy.hpp"
#include "hashMap/ValueCollectionProxy.hpp"
#include "hashMap/EntrySetProxy.hpp"

#include "hashMap/impl/HashMap.hpp"
#include "hashMap/impl/KeySetProxy.hpp"
#include "hashMap/impl/ValueCollectionProxy.hpp"
#include "hashMap/impl/EntrySetProxy.hpp"

//#include "map/baseMap/impl/BaseMap.hpp"
//#include "map/entryArray/impl/Associator.hpp"
//#include "hashMap/impl/Associator.hpp"


#endif // __CDS_EX_HASH_MAP_HPP__
