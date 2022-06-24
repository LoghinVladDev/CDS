//
// Created by loghin on 4/26/22.
//

#ifndef __CDS_ARRAY_DELEGATE_ITERATOR_HPP__
#define __CDS_ARRAY_DELEGATE_ITERATOR_HPP__

namespace cds {

    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    class Array < __ElementType > :: ArrayDelegateIterator : public Array < __ElementType > :: DelegateIterator {

    private:
        Array < __ElementType >       * _pArray     { nullptr };

    private:
        Index                           _index      { 0 };

    private:
        bool                            _forward    { false };

    public:
        constexpr ArrayDelegateIterator (
                Array < __ElementType >   * pArray,
                Index                       index,
                bool                        forward
        ) noexcept;

    public:
        constexpr ArrayDelegateIterator (
                ArrayDelegateIterator const & iterator
        ) noexcept;

    public:
        constexpr ArrayDelegateIterator (
                ArrayDelegateIterator && iterator
        ) noexcept;

    public:
        __CDS_cpplang_ConstexprDestructor ~ArrayDelegateIterator() noexcept override = default;

    public:
        __CDS_NoDiscard constexpr auto index () const noexcept -> Index;

    public:
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto valid () const noexcept -> bool override;

    public:
        __CDS_cpplang_ConstexprOverride auto next () noexcept -> ArrayDelegateIterator & override;

    public:
        __CDS_cpplang_ConstexprOverride auto previous () noexcept -> ArrayDelegateIterator & override;

    public:
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto value () const noexcept -> __ElementType & override;

    public:
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto equals (
                AbstractDelegateIterator const & iterator
        ) const noexcept -> bool override;

    public:
        __CDS_NoDiscard auto copy () const noexcept -> ArrayDelegateIterator * override;

    };

}

#endif // __CDS_ARRAY_DELEGATE_ITERATOR_HPP__