//
// Created by loghin on 4/26/22.
//

#ifndef __CDS_LIST_ITERATOR_HPP__
#define __CDS_LIST_ITERATOR_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        class List < __ElementType > :: Iterator : public List < __ElementType > :: AbstractIterator {

        public:
            constexpr Iterator () noexcept = default;

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
                    List < __ElementType >                      const * pList,
                    cds :: UniquePointer < DelegateIterator >        && pIterator
            ) noexcept;

        public:
            ~Iterator () noexcept override = default;

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
            __CDS_cpplang_ConstexprOverride auto operator * () const noexcept -> __ElementType &;

        public:
            __CDS_cpplang_ConstexprOverride auto operator -> () const noexcept -> __ElementType *;

        };

    }
}

#endif // __CDS_LIST_ITERATOR_HPP__
