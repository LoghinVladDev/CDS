//
// Created by loghin on 4/26/22.
//

#ifndef __CDS_MUTABLE_COLLECTION_ITERATOR_HPP__
#define __CDS_MUTABLE_COLLECTION_ITERATOR_HPP__

namespace cds {

    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    class MutableCollection < __ElementType > :: Iterator : public MutableCollection < __ElementType > :: AbstractIterator {

    public:
        constexpr Iterator () noexcept = default;

    public:
        Iterator (
                Iterator const & iterator
        ) noexcept;

    public:
        constexpr Iterator (
                Iterator && iterator
        ) noexcept;

    public:
        constexpr Iterator (
                MutableCollection < __ElementType >         const * pCollection,
                cds :: UniquePointer < DelegateIterator >        && pIterator
        ) noexcept;

    public:
        ~Iterator () noexcept override = default;

    public:
        auto operator = (
                Iterator const & iterator
        ) noexcept -> Iterator &;

    public:
        auto operator = (
                Iterator && iterator
        ) noexcept -> Iterator &;

    public:
        __CDS_cpplang_ConstexprOverride auto operator ++ () noexcept -> Iterator &;

    public:
        auto operator ++ (int) noexcept -> Iterator;

    public:
        __CDS_cpplang_ConstexprOverride auto operator -- () noexcept -> Iterator &;

    public:
        auto operator -- (int) noexcept -> Iterator;

    public:
        __CDS_cpplang_ConstexprOverride auto operator * () const noexcept -> __ElementType &;

    public:
        __CDS_cpplang_ConstexprOverride auto operator -> () const noexcept -> __ElementType *;

    };

}

#endif // __CDS_MUTABLE_COLLECTION_ITERATOR_HPP__
