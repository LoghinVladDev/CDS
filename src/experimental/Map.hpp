//
// Created by loghin on 4/23/2022.
//

#ifndef __CDS_EX_MAP_HPP__
#define __CDS_EX_MAP_HPP__

#include <CDS/experimental/MutableCollection>
#include <CDS/experimental/Set>

#include "map/entry/Entry.hpp"

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template <
                typename __KeyType, // NOLINT(bugprone-reserved-identifier)
                typename __ValueType // NOLINT(bugprone-reserved-identifier)
        > class Map : public MutableCollection < __hidden :: __impl :: __MapEntry < __KeyType, __ValueType > > {

        public:
            using typename MutableCollection < __hidden :: __impl :: __MapEntry < __KeyType, __ValueType > > :: ElementType;

        public:
            using EntryType = ElementType;

        public:
            using KeyType   = __KeyType;

        public:
            using ValueType = __ValueType;

        public:
            using typename MutableCollection < ElementType > :: InitializerList; /// might require replacing?

        protected:
            using typename MutableCollection < ElementType > :: AbstractIterator;

        protected:
            using typename MutableCollection < ElementType > :: Iterator;

        public:
            using typename MutableCollection < ElementType > :: ConstIterator;

        public:
            using typename MutableCollection < ElementType > :: ReverseIterator;

        public:
            using typename MutableCollection < ElementType > :: ConstReverseIterator;

        protected:
            using typename MutableCollection < ElementType > :: AbstractDelegateIterator;

        protected:
            using typename MutableCollection < ElementType > :: DelegateIterator;

        protected:
            using typename MutableCollection < ElementType > :: DelegateConstIterator;

        protected:
            using typename MutableCollection < ElementType > :: DelegateIteratorRequestType;

        protected:
            class AbstractKeySetProxy;

        protected:
            class AbstractValueMutableCollectionProxy;

        protected:
            class AbstractEntryMutableCollectionProxy;

        private:
            EntryType * _pInsertionEntry { nullptr };

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract auto keys () const noexcept -> Set < KeyType const > const &;

        public:
            __CDS_cpplang_ConstexprPureAbstract auto keys () noexcept -> Set < KeyType const > &;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract auto values () const noexcept -> MutableCollection < ValueType > const &;

        public:
            __CDS_cpplang_ConstexprPureAbstract auto values () noexcept -> MutableCollection < ValueType > &;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract auto entries () const noexcept -> MutableCollection < EntryType > const &;

        public:
            __CDS_cpplang_ConstexprPureAbstract auto entries () noexcept -> MutableCollection < EntryType > &;

        protected:
            __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract virtual auto keySetProxy () const noexcept -> AbstractKeySetProxy const & = 0;

        protected:
            __CDS_cpplang_ConstexprPureAbstract virtual auto keySetProxy () noexcept -> AbstractKeySetProxy & = 0;

        protected:
            __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract virtual auto valueCollectionProxy () const noexcept -> AbstractValueMutableCollectionProxy const & = 0;

        protected:
            __CDS_cpplang_ConstexprPureAbstract virtual auto valueCollectionProxy () noexcept -> AbstractValueMutableCollectionProxy & = 0;

        protected:
            __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract virtual auto entrySetProxy () const noexcept -> AbstractEntryMutableCollectionProxy const & = 0;

        protected:
            __CDS_cpplang_ConstexprPureAbstract virtual auto entrySetProxy () noexcept -> AbstractEntryMutableCollectionProxy & = 0;

        protected:
            auto delegateIterator (
                    DelegateIteratorRequestType requestType
            ) noexcept -> cds :: UniquePointer < DelegateIterator > override = 0;

        protected:
            auto delegateConstIterator (
                    DelegateIteratorRequestType requestType
            ) const noexcept -> cds :: UniquePointer < DelegateConstIterator > override = 0;

        public:
            constexpr Map () noexcept;

        public:
            constexpr Map (
                    Map const & map
            ) noexcept;

        public:
            constexpr Map (
                    Map && map
            ) noexcept;

        public:
            __CDS_Explicit constexpr Map (
                    Size size
            ) noexcept;

        public:
            __CDS_cpplang_ConstexprDestructor ~Map () noexcept override;

        protected:
            virtual auto entryAt (
                    KeyType const & key,
                    bool          & isNew
            ) noexcept -> EntryType = 0;

        protected:
            virtual auto entryAt (
                    KeyType const & key,
                    bool          & found
            ) const noexcept -> EntryType const = 0;

        public:
            template < typename __TValueType = ValueType, cds :: meta :: EnableIf < cds :: meta :: isDefaultConstructible < __TValueType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto get (
                    KeyType const & key
            ) noexcept -> ValueType &;

        public:
            auto at (
                    KeyType const & key
            ) noexcept (false) -> ValueType &;

        public:
            auto at (
                    KeyType const & key
            ) const noexcept (false) -> ValueType const &;

        public:
            template < typename __TValueType = ValueType, cds :: meta :: EnableIf < cds :: meta :: isDefaultConstructible < __TValueType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
            auto operator [] (
                    KeyType const & key
            ) noexcept -> ValueType &;

        public:
            auto operator [] (
                    KeyType const & key
            ) const noexcept (false) -> ValueType const &;

        private:
            auto pNewInsert (
                    ElementType const & referenceElement
            ) noexcept -> ElementType * & override;

        protected:
            virtual auto completeInsertion (
                    EntryType * pEntry
            ) noexcept -> void = 0;

        private:
            auto pNewInsertPost () noexcept -> void override;

        protected:
            static auto entryMoveOrCopyKeyTo (
                    EntryType       * pDestination,
                    EntryType       * pSource
            ) noexcept -> void;

        protected:
            static auto entryMoveOrCopyValueTo (
                    EntryType       * pDestination,
                    EntryType       * pSource
            ) noexcept -> void;

        protected:
            static auto entryCopyTo (
                    EntryType       * pDestination,
                    EntryType const * pSource
            ) noexcept -> void;

        protected:
            constexpr static auto entryEmpty (
                    EntryType const * pEntry
            ) noexcept -> bool;

        public:
            auto contains (
                    ElementType const & entry
            ) const noexcept -> bool override = 0;

        public:
            virtual auto containsKey (
                    KeyType const & key
            ) const noexcept -> bool = 0;

        public:
            virtual auto containsValue (
                    ValueType const & value
            ) const noexcept -> bool = 0;

        public:
            virtual auto remove (
                    KeyType const & key
            ) noexcept -> bool = 0;

        public:
            auto remove (
                    Iterator const & iterator
            ) noexcept -> bool override = 0;

        public:
            auto remove (
                    ConstIterator const & iterator
            ) noexcept -> bool override = 0;

        public:
            auto remove (
                    ReverseIterator const & iterator
            ) noexcept -> bool override = 0;

        public:
            auto remove (
                    ConstReverseIterator const & iterator
            ) noexcept -> bool override = 0;

        protected:
            auto remove (
                    Iterator    const * pIterators,
                    Size                iteratorCount
            ) noexcept -> Size override = 0;

        protected:
            auto remove (
                    ConstIterator   const * pIterators,
                    Size                    iteratorCount
            ) noexcept -> Size override = 0;

        protected:
            auto remove (
                    ReverseIterator const * pIterators,
                    Size                    iteratorCount
            ) noexcept -> Size override = 0;

        protected:
            auto remove (
                    ConstReverseIterator    const * pIterators,
                    Size                            iteratorCount
            ) noexcept -> Size override = 0;

        public:
            __CDS_NoDiscard auto toString () const noexcept -> String override;

        public:
            auto clear () noexcept -> void override = 0;

        public:
            template < typename __TKeyType, typename __TValueType > // NOLINT(bugprone-reserved-identifier)
            auto emplace (
                    __TKeyType      && key,
                    __TValueType    && value
            ) noexcept -> void;

        public:
            auto insert (
                    EntryType const & entry
            ) noexcept -> void;

        protected:
            static auto freeEntryData (
                    EntryType & entry
            ) noexcept -> void;

        };

    }
}

#include "map/AbstractKeySetProxy.hpp"
#include "map/AbstractValueMutableCollectionProxy.hpp"
#include "map/AbstractEntryMutableCollectionProxy.hpp"

#include "map/impl/AbstractKeySetProxy.hpp"
#include "map/impl/AbstractValueMutableCollectionProxy.hpp"
#include "map/impl/AbstractEntryMutableCollectionProxy.hpp"

#include "map/entry/impl/Entry.hpp"

#include "map/impl/Map.hpp"

#endif // __CDS_EX_MAP_HPP__
