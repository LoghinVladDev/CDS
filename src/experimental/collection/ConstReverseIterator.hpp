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
            ConstReverseIterator ( ConstReverseIterator const & ) noexcept;
        public:
            constexpr ConstReverseIterator ( ConstReverseIterator && ) noexcept;
        public:
            constexpr ConstReverseIterator ( Collection < T > const *, UniquePointer < DelegateConstIterator > && ) noexcept;
        public:
            ~ConstReverseIterator () noexcept override = default;

        public:
            auto operator = ( ConstReverseIterator const & ) noexcept -> ConstReverseIterator &;
        public:
            auto operator = ( ConstReverseIterator && ) noexcept -> ConstReverseIterator &;

        public:
            auto operator ++ () noexcept -> ConstReverseIterator &;
        public:
            auto operator ++ (int) noexcept -> ConstReverseIterator;
        public:
            auto operator -- () noexcept -> ConstReverseIterator &;
        public:
            auto operator -- (int) noexcept -> ConstReverseIterator;
        public:
            auto operator * () const noexcept -> ElementType &;
        public:
            auto operator -> () const noexcept -> ElementType *;
        };

    }
}

#endif // __CDS_COLLECTION_CONST_REVERSE_ITERATOR_HPP__
