//
// Created by loghin on 6/16/22.
//

#ifndef __CDS_EX_MAP_ITERATOR_HPP__
#define __CDS_EX_MAP_ITERATOR_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        class Map < __KeyType, __ValueType > :: Iterator : public Map < __KeyType, __ValueType > :: AbstractIterator {

        public:
            constexpr Iterator () noexcept;

        public:
            Iterator (
                    Iterator const & iterator
            ) noexcept;

        public:
            constexpr Iterator (
                    Iterator && iterator
            ) noexcept;

        public:
            constexpr Iterator (
                    Map < __KeyType, __ValueType >              const * pMap,
                    cds :: UniquePointer < DelegateIterator >        && pIterator
            ) noexcept;

        public:
            ~Iterator () noexcept override;

        public:
            auto operator = (
                    Iterator const & iterator
            ) noexcept -> Iterator &;

        public:
            auto operator = (
                    Iterator && iterator
            ) noexcept -> Iterator &;

        public:
            __CDS_cpplang_ConstexprOverride auto operator ++ () noexcept -> Iterator &;

        public:
            auto operator ++ (int) noexcept -> Iterator;

        public:
            __CDS_cpplang_ConstexprOverride auto operator -- () noexcept -> Iterator &;

        public:
            auto operator -- (int) noexcept -> Iterator;

        public:
            __CDS_cpplang_ConstexprOverride auto operator * () const noexcept -> Map < __KeyType, __ValueType > :: EntryType &;

        public:
            __CDS_cpplang_ConstexprOverride auto operator -> () const noexcept -> Map < __KeyType, __ValueType > :: EntryType *;
        };

    }
}

#endif // __CDS_EX_MAP_ITERATOR_HPP__
