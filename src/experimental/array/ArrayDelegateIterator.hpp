//
// Created by loghin on 4/26/22.
//

#ifndef __CDS_ARRAY_ARRAY_DELEGATE_ITERATOR_HPP__
#define __CDS_ARRAY_ARRAY_DELEGATE_ITERATOR_HPP__

namespace cds {
    namespace experimental {

        template < typename T >
        class Array < T > :: ArrayDelegateIterator : public Array < T > :: DelegateIterator {
        private:
            ForeignPointer < Array < T > >  _pArray     { nullptr };
            Index                           _index      { 0 };
            bool                            _forward    { false };

        public:
            constexpr ArrayDelegateIterator ( Array *, Index, bool ) noexcept;
        public:
            constexpr ArrayDelegateIterator ( ArrayDelegateIterator const & ) noexcept;
        public:
            constexpr ArrayDelegateIterator ( ArrayDelegateIterator && ) noexcept;
        public:
            constexpr ~ArrayDelegateIterator() noexcept;

        public:
            constexpr auto index () const noexcept -> Index;

        public:
            constexpr auto valid () const noexcept -> bool override;
        public:
            constexpr auto next () noexcept -> ArrayDelegateIterator & override;
        public:
            constexpr auto previous () noexcept -> ArrayDelegateIterator & override;
        public:
            constexpr auto value () const noexcept -> ElementType & override;
        public:
            constexpr auto equals ( DelegateIterator const & ) const noexcept -> bool override;
        public:
            auto copy () const noexcept -> ArrayDelegateIterator * override;
        };

    }
}

#endif // __CDS_ARRAY_ARRAY_DELEGATE_ITERATOR_HPP__
