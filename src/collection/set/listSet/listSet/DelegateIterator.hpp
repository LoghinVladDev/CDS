//
// Created by loghin on 6/13/22.
//

#ifndef __CDS_LIST_SET_DELEGATE_ITERATOR_HPP__
#define __CDS_LIST_SET_DELEGATE_ITERATOR_HPP__

namespace cds {

    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    class ListSet < __ElementType > :: ListSetDelegateIterator : public DelegateConstIterator {

    private:
        using Node = typename ListSet < __ElementType > :: Node;

    private:
        Node                                        const * _pCurrentNode { nullptr };

    private:
        Node                                        const * _pPreviousNode { nullptr };

    public:
        __CDS_Explicit constexpr ListSetDelegateIterator (
                Node                        const * pCurrentNode,
                Node                        const * pPreviousNode
        ) noexcept;

    public:
        constexpr ListSetDelegateIterator (
                ListSetDelegateIterator const & iterator
        ) noexcept;

    public:
        constexpr ListSetDelegateIterator (
                ListSetDelegateIterator && iterator
        ) noexcept;

    public:
        __CDS_cpplang_ConstexprDestructor ~ListSetDelegateIterator() noexcept override = default;

    public:
        __CDS_NoDiscard constexpr auto valid () const noexcept -> bool override;

    public:
        __CDS_NoDiscard constexpr auto previousNode () const noexcept -> Node const *;

    public:
        __CDS_NoDiscard constexpr auto currentNode () const noexcept -> Node const *;

    public:
        __CDS_cpplang_ConstexprOverride auto next () noexcept -> ListSetDelegateIterator & override;

    public:
        __CDS_cpplang_ConstexprOverride auto previous () noexcept -> ListSetDelegateIterator & override;

    public:
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto value () const noexcept -> __ElementType const & override;

    public:
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto equals (
                AbstractDelegateIterator const & iterator
        ) const noexcept -> bool override;

    public:
        __CDS_NoDiscard auto copy () const noexcept -> ListSetDelegateIterator * override;
    };

}

#endif // __CDS_LIST_SET_DELEGATE_ITERATOR_HPP__
