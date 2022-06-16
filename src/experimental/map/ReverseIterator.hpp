//
// Created by loghin on 6/16/22.
//

#ifndef __CDS_EX_MAP_REVERSE_ITERATOR_HPP__
#define __CDS_EX_MAP_REVERSE_ITERATOR_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        class Map < __KeyType, __ValueType > :: ReverseIterator : public Map < __KeyType, __ValueType > :: AbstractIterator {

        public:
            constexpr ReverseIterator () noexcept;

        public:
            ReverseIterator (
                    ReverseIterator const & iterator
            ) noexcept;

        public:
            constexpr ReverseIterator (
                    ReverseIterator && iterator
            ) noexcept;

        public:
            constexpr ReverseIterator (
                    Map < __KeyType, __ValueType >              const * pMap,
                    cds :: UniquePointer < DelegateIterator >        && pIterator
            ) noexcept;

        public:
            ~ReverseIterator () noexcept override;

        public:
            auto operator = (
                    ReverseIterator const & iterator
            ) noexcept -> ReverseIterator &;

        public:
            auto operator = (
                    ReverseIterator && iterator
            ) noexcept -> ReverseIterator &;

        public:
            __CDS_cpplang_ConstexprOverride auto operator ++ () noexcept -> ReverseIterator &;

        public:
            auto operator ++ (int) noexcept -> ReverseIterator;

        public:
            __CDS_cpplang_ConstexprOverride auto operator -- () noexcept -> ReverseIterator &;

        public:
            auto operator -- (int) noexcept -> ReverseIterator;

        public:
            __CDS_cpplang_ConstexprOverride auto operator * () const noexcept -> Map < __KeyType, __ValueType > :: EntryType &;

        public:
            __CDS_cpplang_ConstexprOverride auto operator -> () const noexcept -> Map < __KeyType, __ValueType > :: EntryType *;
        };

    }
}

#endif // __CDS_EX_MAP_REVERSE_ITERATOR_HPP__
