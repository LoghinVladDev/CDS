//
// Created by loghin on 4/26/22.
//

#ifndef __CDS_COLLECTION_CONST_ITERATOR_HPP__
#define __CDS_COLLECTION_CONST_ITERATOR_HPP__

namespace cds {
    namespace experimental {

        template < typename T >
        class Collection < T > :: ConstIterator : public Collection < T > :: AbstractIterator {
        public:
            constexpr ConstIterator () noexcept = default;
        public:
            __CDS_OptimalInline ConstIterator ( ConstIterator const & ) noexcept;
        public:
            constexpr ConstIterator ( ConstIterator && ) noexcept;
        public:
            constexpr ConstIterator ( Collection < T > const *, UniquePointer < DelegateConstIterator > && ) noexcept;
        public:
            ~ConstIterator () noexcept override = default;

        public:
            __CDS_OptimalInline auto operator = ( ConstIterator const & ) noexcept -> ConstIterator &;
        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator = ( ConstIterator && ) noexcept -> ConstIterator &;

        public:
            __CDS_cpplang_ConstexprPureAbstract auto operator ++ () noexcept -> ConstIterator &;
        public:
            __CDS_cpplang_ConstexprPureAbstract auto operator ++ (int) noexcept -> ConstIterator;
        public:
            __CDS_cpplang_ConstexprPureAbstract auto operator -- () noexcept -> ConstIterator &;
        public:
            __CDS_cpplang_ConstexprPureAbstract auto operator -- (int) noexcept -> ConstIterator;
        public:
            __CDS_cpplang_ConstexprPureAbstract auto operator * () const noexcept -> ElementType const &;
        public:
            __CDS_cpplang_ConstexprOverride auto operator -> () const noexcept -> ElementType const *;
        };

    }
}

#endif // __CDS_COLLECTION_CONST_ITERATOR_HPP__
