//
// Created by loghin on 4/26/22.
//

#ifndef __CDS_MUTABLE_COLLECTION_DELEGATE_ITERATOR_HPP__
#define __CDS_MUTABLE_COLLECTION_DELEGATE_ITERATOR_HPP__

namespace cds {

    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    class MutableCollection < __ElementType > :: DelegateIterator : public MutableCollection < __ElementType > :: AbstractDelegateIterator {

    protected:
        constexpr DelegateIterator () noexcept = default;

    public:
        ~DelegateIterator () noexcept override = default;

    public:
        __CDS_cpplang_ConstexprPureAbstract auto next () noexcept -> DelegateIterator & override = 0;

    public:
        __CDS_cpplang_ConstexprPureAbstract auto previous () noexcept -> DelegateIterator & override = 0;

    public:
        __CDS_cpplang_ConstexprPureAbstract virtual auto value () const noexcept -> __ElementType & = 0;

    public:
        __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract auto equals (
                AbstractDelegateIterator const & iterator
        ) const noexcept -> bool override = 0;

    public:
        __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract auto valid () const noexcept -> bool override = 0;
    };

}

#endif // __CDS_MUTABLE_COLLECTION_DELEGATE_ITERATOR_HPP__
