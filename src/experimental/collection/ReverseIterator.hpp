//
// Created by loghin on 4/26/22.
//

#ifndef __CDS_COLLECTION_REVERSE_ITERATOR_HPP__
#define __CDS_COLLECTION_REVERSE_ITERATOR_HPP__

namespace cds {
    namespace experimental {

        template < typename T >
        class Collection < T > :: ReverseIterator : public Collection < T > :: AbstractIterator {
        public:
            constexpr ReverseIterator () noexcept = default;
        public:
            ReverseIterator ( ReverseIterator const & ) noexcept;
        public:
            constexpr ReverseIterator ( ReverseIterator && ) noexcept;
        public:
            constexpr ReverseIterator ( Collection < T > const *, UniquePointer < DelegateIterator > && ) noexcept;
        public:
            ~ReverseIterator () noexcept override = default;

        public:
            auto operator = ( ReverseIterator const & ) noexcept -> ReverseIterator &;
        public:
            auto operator = ( ReverseIterator && ) noexcept -> ReverseIterator &;

        public:
            auto operator ++ () noexcept -> ReverseIterator &;
        public:
            auto operator ++ (int) noexcept -> ReverseIterator;
        public:
            auto operator -- () noexcept -> ReverseIterator &;
        public:
            auto operator -- (int) noexcept -> ReverseIterator;
        public:
            auto operator * () const noexcept -> ElementType &;
        public:
            auto operator -> () const noexcept -> ElementType *;
        };

    }
}

#endif // __CDS_COLLECTION_REVERSE_ITERATOR_HPP__
