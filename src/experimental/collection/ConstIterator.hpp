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
            ConstIterator ( ConstIterator const & ) noexcept;
        public:
            constexpr ConstIterator ( ConstIterator && ) noexcept;
        public:
            constexpr ConstIterator ( Collection < T > const *, UniquePointer < DelegateConstIterator > && ) noexcept;
        public:
            ~ConstIterator () noexcept override = default;

        public:
            auto operator = ( ConstIterator const & ) noexcept -> ConstIterator &;
        public:
            auto operator = ( ConstIterator && ) noexcept -> ConstIterator &;

        public:
            auto operator ++ () noexcept -> ConstIterator &;
        public:
            auto operator ++ (int) noexcept -> ConstIterator;
        public:
            auto operator -- () noexcept -> ConstIterator &;
        public:
            auto operator -- (int) noexcept -> ConstIterator;
        public:
            auto operator * () const noexcept -> ElementType &;
        public:
            auto operator -> () const noexcept -> ElementType *;
        };

    }
}

#endif // __CDS_COLLECTION_CONST_ITERATOR_HPP__
