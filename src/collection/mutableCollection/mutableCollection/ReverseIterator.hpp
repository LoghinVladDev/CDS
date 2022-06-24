//
// Created by loghin on 4/26/22.
//

#ifndef __CDS_MUTABLE_COLLECTION_REVERSE_ITERATOR_HPP__
#define __CDS_MUTABLE_COLLECTION_REVERSE_ITERATOR_HPP__

namespace cds {

    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    class MutableCollection < __ElementType > :: ReverseIterator : public MutableCollection < __ElementType > :: AbstractIterator {

    public:
        constexpr ReverseIterator () noexcept = default;

    public:
        __CDS_OptimalInline ReverseIterator (
                ReverseIterator const & iterator
        ) noexcept;

    public:
        constexpr ReverseIterator (
                ReverseIterator && iterator
        ) noexcept;

    public:
        constexpr ReverseIterator (
                MutableCollection < __ElementType >         const * pCollection,
                cds :: UniquePointer < DelegateIterator >        && iterator
        ) noexcept;

    public:
        ~ReverseIterator () noexcept override = default;

    public:
        auto operator = (
                ReverseIterator const & iterator
        ) noexcept -> ReverseIterator &;

    public:
        auto operator = (
                ReverseIterator && iterator
        ) noexcept -> ReverseIterator &;


    public:
        __CDS_cpplang_ConstexprOverride auto operator ++ () noexcept -> ReverseIterator &;

    public:
        auto operator ++ (int) noexcept -> ReverseIterator;

    public:
        __CDS_cpplang_ConstexprOverride auto operator -- () noexcept -> ReverseIterator &;

    public:
        auto operator -- (int) noexcept -> ReverseIterator;

    public:
        __CDS_cpplang_ConstexprOverride auto operator * () const noexcept -> __ElementType &;

    public:
        __CDS_cpplang_ConstexprOverride auto operator -> () const noexcept -> __ElementType *;

    };

}

#endif // __CDS_MUTABLE_COLLECTION_REVERSE_ITERATOR_HPP__
