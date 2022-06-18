//
// Created by loghin on 6/18/22.
//

#ifndef __CDS_EX_MAP_ABSTRACT_ENTRY_SET_PROXY_HPP__
#define __CDS_EX_MAP_ABSTRACT_ENTRY_SET_PROXY_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        class Map < __KeyType, __ValueType > :: AbstractEntrySetProxy : public cds :: experimental :: Set < EntryType > {

        public:
            using EntryType = typename Map < __KeyType, __ValueType > :: EntryType;

        public:
            using typename Set < EntryType > :: ElementType;

        public:
            using typename Set < EntryType > :: ConstIterator;

        public:
            using typename Set < EntryType > :: ConstReverseIterator;

        protected:
            using typename Set < EntryType > :: InitializerList;

        protected:
            using typename Set < EntryType > :: DelegateConstIterator;

        protected:
            using typename Set < EntryType > :: AbstractIterator;

        protected:
            using typename Set < EntryType > :: AbstractDelegateIterator;

        protected:
            using typename Set < EntryType > :: DelegateIteratorRequestType;

        protected:
            auto delegateConstIterator (
                    DelegateIteratorRequestType requestType
            ) const noexcept -> cds :: UniquePointer < DelegateConstIterator > override = 0;

        private:
            Map < __KeyType, __ValueType > * _pMap;

        protected:
            constexpr AbstractEntrySetProxy (
                    Map < __KeyType, __ValueType > * pMap
            ) noexcept;

        protected:
            constexpr AbstractEntrySetProxy (
                    AbstractEntrySetProxy const & set
            ) noexcept;

        protected:
            constexpr AbstractEntrySetProxy (
                    AbstractEntrySetProxy && set
            ) noexcept;

        public:
            __CDS_cpplang_ConstexprDestructor ~AbstractEntrySetProxy() noexcept override;

        public:
            auto remove (
                    EntryType const & entry
            ) noexcept -> void;

        public:
            auto remove (
                    ConstIterator const & iterator
            ) noexcept -> bool override;

        public:
            auto remove (
                    ConstReverseIterator const & iterator
            ) noexcept -> bool override;

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

        protected:
            auto pNewInsert (
                    ElementType const & referenceElement
            ) noexcept -> ElementType * & override;

        public:
            auto contains (
                    EntryType const & element
            ) const noexcept -> bool override;

        public:
            auto clear () noexcept -> void override;
        };

    }
}

#endif // __CDS_EX_MAP_ABSTRACT_ENTRY_SET_PROXY_HPP__
