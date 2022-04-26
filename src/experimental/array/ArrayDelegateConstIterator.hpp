//
// Created by loghin on 4/26/22.
//

#ifndef __CDS_ARRAY_ARRAY_DELEGATE_CONST_ITERATOR_HPP__
#define __CDS_ARRAY_ARRAY_DELEGATE_CONST_ITERATOR_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
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
            __CDS_cpplang_ConstexprDestructor ~ArrayDelegateConstIterator() noexcept = default;

        public:
            __CDS_NoDiscard constexpr auto index () const noexcept -> Index;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto valid () const noexcept -> bool override;
        public:
            __CDS_cpplang_ConstexprOverride auto next () noexcept -> ArrayDelegateConstIterator & override;
        public:
            __CDS_cpplang_ConstexprOverride auto previous () noexcept -> ArrayDelegateConstIterator & override;
        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto value () const noexcept -> ElementType const & override;
        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto equals ( AbstractDelegateIterator const & ) const noexcept -> bool override;
        };

    }
}

#endif // __CDS_ARRAY_ARRAY_DELEGATE_CONST_ITERATOR_HPP__
