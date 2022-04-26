//
// Created by loghin on 4/26/22.
//

#ifndef __CDS_COLLECTION_ABSTRACT_ITERATOR_HPP__
#define __CDS_COLLECTION_ABSTRACT_ITERATOR_HPP__

namespace cds {
    namespace experimental {

        template < typename T >
        class Collection < T > :: AbstractIterator {
        protected:
            ForeignPointer < Collection < T > const >   _pCollection { nullptr };
            UniquePointer < AbstractDelegateIterator >  _pDelegate { nullptr };

        protected:
            constexpr AbstractIterator () noexcept = default;
        protected:
            constexpr AbstractIterator ( AbstractIterator const & ) noexcept;
        protected:
            constexpr AbstractIterator ( AbstractIterator && ) noexcept;
        public:
            virtual ~AbstractIterator () noexcept = default;
        public:
            constexpr AbstractIterator (
                    Collection < T > const *,
                    UniquePointer < AbstractDelegateIterator > &&
            ) noexcept;

        public:
            constexpr auto of ( Collection < T > const * ) const noexcept -> bool;

        public:
            auto next () noexcept -> AbstractIterator &;
        public:
            auto previous () noexcept -> AbstractIterator &;
        public:
            auto valid () const noexcept -> bool;
        public:
            auto equals ( AbstractIterator const & ) const noexcept -> bool;

        public:
            auto operator == ( AbstractIterator const & ) const noexcept -> bool;
        public:
            auto operator != ( AbstractIterator const & ) const noexcept -> bool;
        };

    }
}

#endif // __CDS_COLLECTION_ABSTRACT_ITERATOR_HPP__
