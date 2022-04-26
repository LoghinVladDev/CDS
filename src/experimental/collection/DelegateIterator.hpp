//
// Created by loghin on 4/26/22.
//

#ifndef __CDS_COLLECTION_DELEGATE_ITERATOR_HPP__
#define __CDS_COLLECTION_DELEGATE_ITERATOR_HPP__

namespace cds {
    namespace experimental {

        template < typename T >
        class Collection < T > :: DelegateIterator : public Collection < T > :: AbstractDelegateIterator {
        protected:
            constexpr DelegateIterator () noexcept = default;
        public:
            ~DelegateIterator () noexcept override = default;

        public:
            auto next () noexcept -> DelegateIterator & override = 0;
        public:
            auto previous () noexcept -> DelegateIterator & override = 0;
        public:
            virtual auto value () const noexcept -> ElementType & = 0;
        public:
            auto equals ( DelegateIterator const & ) const noexcept -> bool override = 0;
        public:
            auto copy () const noexcept -> DelegateIterator * override = 0;

        public:
            auto valid () const noexcept -> bool override = 0;
        };

    }
}

#endif // __CDS_COLLECTION_DELEGATE_ITERATOR_HPP__
