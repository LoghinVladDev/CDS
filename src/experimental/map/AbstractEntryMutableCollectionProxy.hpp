//
// Created by loghin on 6/18/22.
//

#ifndef __CDS_EX_MAP_ABSTRACT_ENTRY_MUTABLE_COLLECTION_PROXY_HPP__
#define __CDS_EX_MAP_ABSTRACT_ENTRY_MUTABLE_COLLECTION_PROXY_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        class Map < __KeyType, __ValueType > :: AbstractEntryMutableCollectionProxy :
                public cds :: experimental :: MutableCollection < EntryType >,
                protected Map < __KeyType, __ValueType > :: AbstractProxy {

        public:
            using EntryType = typename Map < __KeyType, __ValueType > :: EntryType;

        public:
            using typename MutableCollection < EntryType > :: ElementType;

        public:
            using typename MutableCollection < EntryType > :: Iterator;

        public:
            using typename MutableCollection < EntryType > :: ConstIterator;

        public:
            using typename MutableCollection < EntryType > :: ReverseIterator;

        public:
            using typename MutableCollection < EntryType > :: ConstReverseIterator;

        protected:
            using typename MutableCollection < EntryType > :: InitializerList;

        protected:
            using typename MutableCollection < EntryType > :: DelegateIterator;

        protected:
            using typename MutableCollection < EntryType > :: DelegateConstIterator;

        protected:
            using typename MutableCollection < EntryType > :: AbstractIterator;

        protected:
            using typename MutableCollection < EntryType > :: AbstractDelegateIterator;

        protected:
            using typename MutableCollection < EntryType > :: DelegateIteratorRequestType;

        protected:
            auto delegateIterator (
                    DelegateIteratorRequestType requestType
            ) noexcept -> cds :: UniquePointer < DelegateIterator > override = 0;

        protected:
            auto delegateConstIterator (
                    DelegateIteratorRequestType requestType
            ) const noexcept -> cds :: UniquePointer < DelegateConstIterator > override = 0;

        protected:
            __CDS_Explicit constexpr AbstractEntryMutableCollectionProxy (
                    Map < __KeyType, __ValueType > * pMap
            ) noexcept;

        protected:
            constexpr AbstractEntryMutableCollectionProxy (
                    AbstractEntryMutableCollectionProxy const & collection
            ) noexcept;

        protected:
            constexpr AbstractEntryMutableCollectionProxy (
                    AbstractEntryMutableCollectionProxy && collection
            ) noexcept;

        public:
            __CDS_cpplang_ConstexprDestructor ~AbstractEntryMutableCollectionProxy() noexcept override;

        public:
            auto remove (
                    EntryType const & entry
            ) noexcept -> bool;

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

        public:
            auto remove (
                    Iterator    const * pIterators,
                    Size                iteratorCount
            ) noexcept -> Size override;

        public:
            auto remove (
                    ConstIterator   const * pIterators,
                    Size                    iteratorCount
            ) noexcept -> Size override;

        public:
            auto remove (
                    ConstReverseIterator    const * pIterators,
                    Size                            iteratorCount
            ) noexcept -> Size override;

        public:
            auto remove (
                    ReverseIterator const * pIterators,
                    Size                    iteratorCount
            ) noexcept -> Size override;

        protected:
            auto pNewInsert (
                    ElementType const & referenceElement
            ) noexcept -> ElementType * override;

        public:
            auto contains (
                    EntryType const & element
            ) const noexcept -> bool override;

        public:
            auto clear () noexcept -> void override;

        public:
            __CDS_NoDiscard auto toString () const noexcept -> String override;

        public:
            __CDS_NoDiscard __CDS_cpplang_VirtualConstexpr auto size () const noexcept -> Size override = 0;
        };

    }
}

#endif // __CDS_EX_MAP_ABSTRACT_ENTRY_MUTABLE_COLLECTION_PROXY_HPP__
