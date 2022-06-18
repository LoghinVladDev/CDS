//
// Created by loghin on 6/18/22.
//

#ifndef __CDS_EX_MAP_ABSTRACT_VALUE_COLLECTION_PROXY_HPP__
#define __CDS_EX_MAP_ABSTRACT_VALUE_COLLECTION_PROXY_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        class Map < __KeyType, __ValueType > :: AbstractValueCollectionProxy : public cds :: experimental :: Collection < ValueType > {

        public:
            using ValueType = typename Map < __KeyType, __ValueType > :: ValueType;

        public:
            using typename Collection < ValueType > :: ElementType;

        public:
            using typename Collection < ValueType > :: ConstIterator;

        public:
            using typename Collection < ValueType > :: ConstReverseIterator;

        protected:
            using typename Collection < ValueType > :: InitializerList;

        protected:
            using typename Collection < ValueType > :: DelegateConstIterator;

        protected:
            using typename Collection < ValueType > :: AbstractIterator;

        protected:
            using typename Collection < ValueType > :: AbstractDelegateIterator;

        protected:
            using typename Collection < ValueType > :: DelegateIteratorRequestType;

        protected:
            auto delegateConstIterator (
                    DelegateIteratorRequestType requestType
            ) const noexcept -> cds :: UniquePointer < DelegateConstIterator > override = 0;

        private:
            Map < __KeyType, __ValueType > * _pMap;

        protected:
            constexpr AbstractValueCollectionProxy (
                    Map < __KeyType, __ValueType > * pMap
            ) noexcept;

        protected:
            constexpr AbstractValueCollectionProxy (
                    AbstractValueCollectionProxy const & set
            ) noexcept;

        protected:
            constexpr AbstractValueCollectionProxy (
                    AbstractValueCollectionProxy && set
            ) noexcept;

        public:
            __CDS_cpplang_ConstexprDestructor ~AbstractValueCollectionProxy() noexcept override;

        public:
            auto remove (
                    ValueType const & value
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
                    ValueType const & element
            ) const noexcept -> bool override;

        public:
            auto clear () noexcept -> void override;
        };
    }
}

#endif // __CDS_EX_MAP_ABSTRACT_VALUE_COLLECTION_PROXY_HPP__
