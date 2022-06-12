//
// Created by loghin on 4/26/22.
//

#ifndef __CDS_LIST_REVERSE_ITERATOR_HPP__
#define __CDS_LIST_REVERSE_ITERATOR_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        class List < __ElementType > :: ReverseIterator : public List < __ElementType > :: AbstractIterator {

        public:
            constexpr ReverseIterator () noexcept = default;

        public:
            __CDS_OptimalInline ReverseIterator (
                    ReverseIterator const & iterator
            ) noexcept;

        public:
            constexpr ReverseIterator (
                    ReverseIterator && iterator
            ) noexcept;

        public:
            constexpr ReverseIterator (
                    List < __ElementType >                      const * pList,
                    cds :: UniquePointer < DelegateIterator >        && iterator
            ) noexcept;

        public:
            ~ReverseIterator () noexcept override = default;

        public:
            __CDS_OptimalInline auto operator = (
                    ReverseIterator const & iterator
            ) noexcept -> ReverseIterator &;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                    ReverseIterator && iterator
            ) noexcept -> ReverseIterator &;


        public:
            __CDS_cpplang_ConstexprPureAbstract auto operator ++ () noexcept -> ReverseIterator &;

        public:
            __CDS_cpplang_ConstexprPureAbstract auto operator ++ (int) noexcept -> ReverseIterator;

        public:
            __CDS_cpplang_ConstexprPureAbstract auto operator -- () noexcept -> ReverseIterator &;

        public:
            __CDS_cpplang_ConstexprPureAbstract auto operator -- (int) noexcept -> ReverseIterator;

        public:
            __CDS_cpplang_ConstexprPureAbstract auto operator * () const noexcept -> __ElementType &;

        public:
            __CDS_cpplang_ConstexprOverride auto operator -> () const noexcept -> __ElementType *;

        };

    }
}

#endif // __CDS_LIST_REVERSE_ITERATOR_HPP__
