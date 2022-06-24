//
// Created by loghin on 6/13/22.
//

#ifndef __CDS_EX_HASH_SET_DELEGATE_ITERATOR_HPP__
#define __CDS_EX_HASH_SET_DELEGATE_ITERATOR_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __ElementType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        class HashSet < __ElementType, __Hasher > :: HashSetDelegateIterator : public DelegateConstIterator {

        private:
            using HashTableConstIterator = typename HashSet < __ElementType, __Hasher > :: HashTableConstIterator;

        private:
            HashTableConstIterator _iterator;

        public:
            __CDS_Explicit constexpr HashSetDelegateIterator (
                    HashTableConstIterator const & iterator
            ) noexcept;

        public:
            constexpr HashSetDelegateIterator (
                    HashSetDelegateIterator const & iterator
            ) noexcept;

        public:
            constexpr HashSetDelegateIterator (
                    HashSetDelegateIterator && iterator
            ) noexcept;

        public:
            __CDS_cpplang_ConstexprDestructor ~HashSetDelegateIterator() noexcept override = default;

        public:
            __CDS_NoDiscard constexpr auto valid () const noexcept -> bool override;

        public:
            __CDS_NoDiscard constexpr auto iterator () const noexcept -> HashTableConstIterator const &;

        public:
            __CDS_cpplang_ConstexprOverride auto next () noexcept -> HashSetDelegateIterator & override;

        public:
            __CDS_cpplang_ConstexprOverride auto previous () noexcept -> HashSetDelegateIterator & override;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto value () const noexcept -> __ElementType const & override;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto equals (
                    AbstractDelegateIterator const & iterator
            ) const noexcept -> bool override;

        public:
            __CDS_NoDiscard auto copy () const noexcept -> HashSetDelegateIterator * override;
        };

    }
}

#endif // __CDS_EX_HASH_SET_DELEGATE_ITERATOR_HPP__
