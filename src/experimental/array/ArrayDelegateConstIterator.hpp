//
// Created by loghin on 4/26/22.
//

#ifndef __CDS_ARRAY_ARRAY_DELEGATE_CONST_ITERATOR_HPP__
#define __CDS_ARRAY_ARRAY_DELEGATE_CONST_ITERATOR_HPP__

namespace cds {
    namespace experimental {

        template < typename T >
        class Array < T > :: ArrayDelegateConstIterator : public Array < T > :: DelegateConstIterator {
        private:
            ForeignPointer < Array < T > const >    _pArray     { nullptr };
            Index                                   _index      { 0 };
            bool                                    _forward    { false };

        public:
            constexpr ArrayDelegateConstIterator ( Array const *, Index, bool ) noexcept;
        public:
            constexpr ArrayDelegateConstIterator ( ArrayDelegateConstIterator const & ) noexcept;
        public:
            constexpr ArrayDelegateConstIterator ( ArrayDelegateConstIterator && ) noexcept;
        public:
            constexpr ~ArrayDelegateConstIterator() noexcept;

        public:
            constexpr auto index () const noexcept -> Index;

        public:
            constexpr auto valid () const noexcept -> bool override;
        public:
            constexpr auto next () noexcept -> ArrayDelegateConstIterator & override;
        public:
            constexpr auto previous () noexcept -> ArrayDelegateConstIterator & override;
        public:
            constexpr auto value () const noexcept -> ElementType const & override;
        public:
            constexpr auto equals ( DelegateConstIterator const & ) const noexcept -> bool override;
        public:
            auto copy () const noexcept -> ArrayDelegateConstIterator * override;
        };

    }
}

#endif // __CDS_ARRAY_ARRAY_DELEGATE_CONST_ITERATOR_HPP__
