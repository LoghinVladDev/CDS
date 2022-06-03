//
// Created by loghin on 4/26/22.
//

#ifndef __CDS_LIST_ITERATOR_HPP__
#define __CDS_LIST_ITERATOR_HPP__

namespace cds {
    namespace experimental {

        template < typename T >
        class List < T > :: Iterator : public List < T > :: AbstractIterator {
        public:
            constexpr Iterator () noexcept = default;
        public:
            __CDS_OptimalInline Iterator ( Iterator const & ) noexcept;
        public:
            constexpr Iterator ( Iterator && ) noexcept;
        public:
            constexpr Iterator ( List < T > const *, cds :: UniquePointer < DelegateIterator > && ) noexcept;
        public:
            ~Iterator () noexcept override = default;

        public:
            __CDS_OptimalInline auto operator = ( Iterator const & ) noexcept -> Iterator &;
        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( Iterator && ) noexcept -> Iterator &;

        public:
            __CDS_cpplang_ConstexprPureAbstract auto operator ++ () noexcept -> Iterator &;
        public:
            __CDS_cpplang_ConstexprPureAbstract auto operator ++ (int) noexcept -> Iterator;
        public:
            __CDS_cpplang_ConstexprPureAbstract auto operator -- () noexcept -> Iterator &;
        public:
            __CDS_cpplang_ConstexprPureAbstract auto operator -- (int) noexcept -> Iterator;
        public:
            __CDS_cpplang_ConstexprPureAbstract auto operator * () const noexcept -> ElementType &;
        public:
            __CDS_cpplang_ConstexprOverride auto operator -> () const noexcept -> ElementType *;
        };

    }
}

#endif // __CDS_LIST_ITERATOR_HPP__
