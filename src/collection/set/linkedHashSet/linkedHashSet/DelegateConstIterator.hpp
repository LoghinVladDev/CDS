//
// Created by loghin on 6/25/22.
//

#ifndef __CDS_LINKED_HASH_SET_DELEGATE_CONST_ITERATOR_HPP__
#define __CDS_LINKED_HASH_SET_DELEGATE_CONST_ITERATOR_HPP__

namespace cds {

    template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
    class LinkedHashSet < __ElementType, __Hasher > :: LinkedHashSetDelegateConstIterator : public DelegateConstIterator {

    private:
        using SingleLinkedListConstIterator = typename LinkedHashSet < __ElementType, __Hasher > :: SingleLinkedListConstIterator;

    private:
        SingleLinkedListConstIterator _iterator;

    public:
        __CDS_Explicit constexpr LinkedHashSetDelegateConstIterator (
                SingleLinkedListConstIterator const & iterator
        ) noexcept;

    public:
        constexpr LinkedHashSetDelegateConstIterator (
                LinkedHashSetDelegateConstIterator const & iterator
        ) noexcept;

    public:
        constexpr LinkedHashSetDelegateConstIterator (
                LinkedHashSetDelegateConstIterator && iterator
        ) noexcept;

    public:
        __CDS_cpplang_ConstexprDestructor ~LinkedHashSetDelegateConstIterator() noexcept override = default;

    public:
        __CDS_NoDiscard constexpr auto valid () const noexcept -> bool override;

    public:
        __CDS_NoDiscard constexpr auto iterator () const noexcept -> SingleLinkedListConstIterator const &;

    public:
        __CDS_cpplang_ConstexprOverride auto next () noexcept -> LinkedHashSetDelegateConstIterator & override;

    public:
        __CDS_cpplang_ConstexprOverride auto previous () noexcept -> LinkedHashSetDelegateConstIterator & override;

    public:
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto value () const noexcept -> __ElementType const & override;

    public:
        __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto equals (
                AbstractDelegateIterator const & iterator
        ) const noexcept -> bool override;

    public:
        __CDS_NoDiscard auto copy () const noexcept -> LinkedHashSetDelegateConstIterator * override;
    };

}

#endif // __CDS_LINKED_HASH_SET_DELEGATE_CONST_ITERATOR_HPP__
