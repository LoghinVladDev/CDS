//
// Created by loghin on 4/26/22.
//

#ifndef __CDS_COLLECTION_CONST_REVERSE_ITERATOR_HPP__
#define __CDS_COLLECTION_CONST_REVERSE_ITERATOR_HPP__

namespace cds {
    namespace experimental {

        template < typename T >
        class Collection < T > :: ConstReverseIterator : public Collection < T > :: AbstractIterator {
        public:
            constexpr ConstReverseIterator () noexcept = default;
        public:
            __CDS_OptimalInline ConstReverseIterator ( ConstReverseIterator const & ) noexcept;
        public:
            constexpr ConstReverseIterator ( ConstReverseIterator && ) noexcept;
        public:
            constexpr ConstReverseIterator ( Collection < T > const *, UniquePointer < DelegateConstIterator > && ) noexcept;
        public:
            ~ConstReverseIterator () noexcept override = default;

        public:
            __CDS_OptimalInline auto operator = ( ConstReverseIterator const & ) noexcept -> ConstReverseIterator &;
        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( ConstReverseIterator && ) noexcept -> ConstReverseIterator &;

        public:
            __CDS_cpplang_ConstexprPureAbstract auto operator ++ () noexcept -> ConstReverseIterator &;
        public:
            __CDS_cpplang_ConstexprPureAbstract auto operator ++ (int) noexcept -> ConstReverseIterator;
        public:
            __CDS_cpplang_ConstexprPureAbstract auto operator -- () noexcept -> ConstReverseIterator &;
        public:
            __CDS_cpplang_ConstexprPureAbstract auto operator -- (int) noexcept -> ConstReverseIterator;
        public:
            __CDS_cpplang_ConstexprPureAbstract auto operator * () const noexcept -> ElementType const &;
        public:
            __CDS_cpplang_ConstexprOverride auto operator -> () const noexcept -> ElementType const *;
        };

    }
}

#endif // __CDS_COLLECTION_CONST_REVERSE_ITERATOR_HPP__
