//
// Created by loghin on 4/26/22.
//

#ifndef __CDS_LIST_REVERSE_ITERATOR_HPP__
#define __CDS_LIST_REVERSE_ITERATOR_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename T >
        class List < T > :: ReverseIterator : public List < T > :: AbstractIterator {
        public:
            constexpr ReverseIterator () noexcept = default;
        public:
            __CDS_OptimalInline ReverseIterator ( ReverseIterator const & ) noexcept;
        public:
            constexpr ReverseIterator ( ReverseIterator && ) noexcept;
        public:
            constexpr ReverseIterator ( List < T > const *, cds :: UniquePointer < DelegateIterator > && ) noexcept;
        public:
            ~ReverseIterator () noexcept override = default;

        public:
            __CDS_OptimalInline auto operator = ( ReverseIterator const & ) noexcept -> ReverseIterator &;
        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( ReverseIterator && ) noexcept -> ReverseIterator &;

        public:
            __CDS_cpplang_ConstexprPureAbstract auto operator ++ () noexcept -> ReverseIterator &;
        public:
            __CDS_cpplang_ConstexprPureAbstract auto operator ++ (int) noexcept -> ReverseIterator;
        public:
            __CDS_cpplang_ConstexprPureAbstract auto operator -- () noexcept -> ReverseIterator &;
        public:
            __CDS_cpplang_ConstexprPureAbstract auto operator -- (int) noexcept -> ReverseIterator;
        public:
            __CDS_cpplang_ConstexprPureAbstract auto operator * () const noexcept -> ElementType &;
        public:
            __CDS_cpplang_ConstexprOverride auto operator -> () const noexcept -> ElementType *;
        };

    }
}

#endif // __CDS_LIST_REVERSE_ITERATOR_HPP__
