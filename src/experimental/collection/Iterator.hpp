//
// Created by loghin on 4/26/22.
//

#ifndef __CDS_COLLECTION_ITERATOR_HPP__
#define __CDS_COLLECTION_ITERATOR_HPP__

namespace cds {
    namespace experimental {

        template < typename T >
        class Collection < T > :: Iterator : public Collection < T > :: AbstractIterator {
        public:
            constexpr Iterator () noexcept = default;
        public:
            Iterator ( Iterator const & ) noexcept;
        public:
            constexpr Iterator ( Iterator && ) noexcept;
        public:
            constexpr Iterator ( Collection < T > const *, UniquePointer < DelegateIterator > && ) noexcept;
        public:
            ~Iterator () noexcept override = default;

        public:
            auto operator = ( Iterator const & ) noexcept -> Iterator &;
        public:
            auto operator = ( Iterator && ) noexcept -> Iterator &;

        public:
            auto operator ++ () noexcept -> Iterator &;
        public:
            auto operator ++ (int) noexcept -> Iterator;
        public:
            auto operator -- () noexcept -> Iterator &;
        public:
            auto operator -- (int) noexcept -> Iterator;
        public:
            auto operator * () const noexcept -> ElementType &;
        public:
            auto operator -> () const noexcept -> ElementType *;
        };

    }
}

#endif // __CDS_COLLECTION_ITERATOR_HPP__
