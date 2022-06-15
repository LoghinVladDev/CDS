//
// Created by loghin on 4/23/2022.
//

#ifndef __CDS_EX_MAP_HPP__
#define __CDS_EX_MAP_HPP__

#include <CDS/experimental/Collection>

#include "map/Entry.hpp"

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template <
                typename __KeyType, // NOLINT(bugprone-reserved-identifier)
                typename __ValueType // NOLINT(bugprone-reserved-identifier)
        > class Map : public Collection < __hidden :: __impl :: __MapEntry < __KeyType, __ValueType > > {

        public:
            using typename Collection < __hidden :: __impl :: __MapEntry < __KeyType, __ValueType > > :: ElementType;

        public:
            using EntryType = ElementType;

        public:
            using KeyType   = __KeyType;

        public:
            using ValueType = __ValueType;

        public:
            using typename Collection < ElementType > :: InitializerList; /// might require replacing?

        protected:
            using typename Collection < ElementType > :: AbstractIterator;

        public:
            class Iterator;

        public:
            using typename Collection < ElementType > :: ConstIterator;

        public:
            class ReverseIterator;

        public:
            using typename Collection < ElementType > :: ConstReverseIterator;

        protected:
            using typename Collection < ElementType > :: AbstractDelegateIterator;

        protected:
            class DelegateIterator;

        protected:
            using typename Collection < ElementType > :: DelegateConstIterator;

        protected:
            using typename Collection < ElementType > :: DelegateIteratorRequestType;

        protected:
            virtual auto delegateIterator (
                    DelegateIteratorRequestType requestType
            ) noexcept -> cds :: UniquePointer < DelegateIterator > = 0;

        protected:
            auto delegateConstIterator (
                    DelegateIteratorRequestType requestType
            ) const noexcept -> cds :: UniquePointer < DelegateConstIterator > override = 0;

        public:
            auto begin () noexcept -> Iterator;

        public:
            using Collection < ElementType > :: begin;

        public:
            auto end () noexcept -> Iterator;

        public:
            using Collection < ElementType > :: end;

        public:
            auto rbegin () noexcept -> ReverseIterator;

        public:
            using Collection < ElementType > :: rbegin;

        public:
            auto rend () noexcept -> ReverseIterator;

        public:
            using Collection < ElementType > :: rend;

        public:
            using Collection < ElementType > :: cbegin;

        public:
            using Collection < ElementType > :: cend;

        public:
            using Collection < ElementType > :: crbegin;

        public:
            using Collection < ElementType > :: crend;

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

        public:
            virtual auto get (
                    KeyType const & key
            ) noexcept (false) -> ValueType & = 0;

        public:
            virtual auto get (
                    KeyType const & key
            ) const noexcept (false) -> ValueType const & = 0;

        protected:
            auto pNewInsert (
                    ElementType const & referenceElement
            ) noexcept -> ElementType * & override = 0;

        protected:
            auto pNewInsertPost () noexcept -> void override = 0;

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
                    Iterator const & iterator
            ) noexcept -> bool = 0;

        public:
            auto remove (
                    ConstIterator const & iterator
            ) noexcept -> bool override = 0;

        public:
            virtual auto remove (
                    ReverseIterator const & iterator
            ) noexcept -> bool = 0;

        public:
            auto remove (
                    ConstReverseIterator const & iterator
            ) noexcept -> bool override = 0;

        public:
            virtual auto remove (
                    Iterator    const * pIterators,
                    Size                iteratorCount
            ) noexcept -> Size = 0;

        public:
            auto remove (
                    ConstIterator   const * pIterators,
                    Size                    iteratorCount
            ) noexcept -> Size override = 0;

        public:
            virtual auto remove (
                    ReverseIterator const * pIterators,
                    Size                    iteratorCount
            ) noexcept -> Size = 0;

        public:
            auto remove (
                    ConstReverseIterator    const * pIterators,
                    Size                            iteratorCount
            ) noexcept -> Size override = 0;

        public:
            __CDS_NoDiscard auto toString () const noexcept -> String override;

        public:
            auto clear () noexcept -> void override = 0;

        public:
            template < typename __TKeyType, typename __TValueType >
            auto emplace (
                    __TKeyType      && key,
                    __TValueType    && value
            ) noexcept -> void;

        public:
            template < typename __EntryType = EntryType, cds :: meta :: EnableIf < cds :: meta :: isCopyConstructible < __EntryType > () > = 0 >
            auto insert (
                    EntryType const & entry
            ) noexcept -> void;

        public:
            template < typename __EntryType = EntryType, cds :: meta :: EnableIf < cds :: meta :: isMoveConstructible < __EntryType > () > = 0 >
            auto insert (
                    EntryType && entry
            ) noexcept -> void;

        };

    }
}

#endif // __CDS_EX_MAP_HPP__
