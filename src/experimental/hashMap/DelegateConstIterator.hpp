//
// Created by loghin on 6/22/22.
//

#ifndef __CDS_HASH_MAP_DELEGATE_CONST_ITERATOR_HPP__
#define __CDS_HASH_MAP_DELEGATE_CONST_ITERATOR_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        class HashMap < __KeyType, __ValueType, __Hasher > :: HashMapDelegateConstIterator : public DelegateConstIterator {

        private:
            using HashTableConstIterator = typename HashMap < __KeyType, __ValueType, __Hasher > :: HashTableConstIterator;

        private:
            HashTableConstIterator _iterator;

        public:
            __CDS_Explicit constexpr HashMapDelegateConstIterator (
                    HashTableConstIterator const & iterator
            ) noexcept;

        public:
            constexpr HashMapDelegateConstIterator (
                    HashMapDelegateConstIterator const & iterator
            ) noexcept;

        public:
            constexpr HashMapDelegateConstIterator (
                    HashMapDelegateConstIterator && iterator
            ) noexcept;

        public:
            __CDS_cpplang_ConstexprDestructor ~HashMapDelegateConstIterator () noexcept override;

        public:
            __CDS_NoDiscard constexpr auto valid () const noexcept -> bool override;

        public:
            __CDS_NoDiscard constexpr auto iterator () const noexcept -> HashTableConstIterator const &;

        public:
            __CDS_cpplang_ConstexprOverride auto next () noexcept -> HashMapDelegateConstIterator & override;

        public:
            __CDS_cpplang_ConstexprOverride auto previous () noexcept -> HashMapDelegateConstIterator & override;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto value () const noexcept -> HashMap < __KeyType, __ValueType, __Hasher > :: ElementType const & override;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto equals (
                    AbstractDelegateIterator const & iterator
            ) const noexcept -> bool override;

        public:
            __CDS_NoDiscard auto copy () const noexcept -> HashMapDelegateConstIterator * override;
        };

    }
}

#endif // __CDS_HASH_MAP_DELEGATE_CONST_ITERATOR_HPP__
