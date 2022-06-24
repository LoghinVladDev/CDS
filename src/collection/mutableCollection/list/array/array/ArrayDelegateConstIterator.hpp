//
// Created by loghin on 4/26/22.
//

#ifndef __CDS_ARRAY_DELEGATE_CONST_ITERATOR_HPP__
#define __CDS_ARRAY_DELEGATE_CONST_ITERATOR_HPP__

namespace cds {

    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    class Array < __ElementType > :: ArrayDelegateConstIterator : public Array < __ElementType > :: DelegateConstIterator {

    private:
        Array < __ElementType >         const * _pArray     { nullptr };

    private:
        Index                                   _index      { 0 };

    private:
        bool                                    _forward    { false };

    public:
        constexpr ArrayDelegateConstIterator (
                Array < __ElementType > const * pArray,
                Index                           index,
                bool                            forward
        ) noexcept;

    public:
        constexpr ArrayDelegateConstIterator (
                ArrayDelegateConstIterator const & iterator
        ) noexcept;

    public:
        constexpr ArrayDelegateConstIterator (
                ArrayDelegateConstIterator && iterator
        ) noexcept;

    public:
        __CDS_cpplang_ConstexprDestructor ~ArrayDelegateConstIterator() noexcept override = default;

    public:
        __CDS_NoDiscard constexpr auto index () const noexcept -> Index;

    public:
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto valid () const noexcept -> bool override;

    public:
        __CDS_cpplang_ConstexprOverride auto next () noexcept -> ArrayDelegateConstIterator & override;

    public:
        __CDS_cpplang_ConstexprOverride auto previous () noexcept -> ArrayDelegateConstIterator & override;

    public:
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto value () const noexcept -> __ElementType const & override;

    public:
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto equals (
                AbstractDelegateIterator const & iterator
        ) const noexcept -> bool override;

    public:
        __CDS_NoDiscard auto copy () const noexcept -> ArrayDelegateConstIterator * override;

    };

}

#endif // __CDS_ARRAY_DELEGATE_CONST_ITERATOR_HPP__
