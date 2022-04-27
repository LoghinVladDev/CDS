//
// Created by loghin on 4/26/22.
//

#ifndef __CDS_ARRAY_ARRAY_DELEGATE_ITERATOR_HPP__
#define __CDS_ARRAY_ARRAY_DELEGATE_ITERATOR_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename T >
        class Array < T > :: ArrayDelegateIterator : public Array < T > :: DelegateIterator {
        private:
            ForeignPointer < Array < T > >  _pArray     { nullptr };
        private:
            Index                           _index      { 0 };
        private:
            bool                            _forward    { false };

        public:
            constexpr ArrayDelegateIterator ( Array *, Index, bool ) noexcept;
        public:
            constexpr ArrayDelegateIterator ( ArrayDelegateIterator const & ) noexcept;
        public:
            constexpr ArrayDelegateIterator ( ArrayDelegateIterator && ) noexcept;
        public:
            __CDS_cpplang_ConstexprDestructor ~ArrayDelegateIterator() noexcept = default;

        public:
            __CDS_NoDiscard constexpr auto index () const noexcept -> Index;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto valid () const noexcept -> bool override;
        public:
            __CDS_cpplang_ConstexprOverride auto next () noexcept -> ArrayDelegateIterator & override;
        public:
            __CDS_cpplang_ConstexprOverride auto previous () noexcept -> ArrayDelegateIterator & override;
        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto value () const noexcept -> ElementType & override;
        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto equals ( AbstractDelegateIterator const & ) const noexcept -> bool override;
        };

    }
}

#endif // __CDS_ARRAY_ARRAY_DELEGATE_ITERATOR_HPP__
