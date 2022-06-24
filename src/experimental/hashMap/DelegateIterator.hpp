//
// Created by loghin on 6/22/22.
//

#ifndef __CDS_HASH_MAP_DELEGATE_ITERATOR_HPP__
#define __CDS_HASH_MAP_DELEGATE_ITERATOR_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __KeyType, typename __ValueType, typename __Hasher > // NOLINT(bugprone-reserved-identifier)
        class HashMap < __KeyType, __ValueType, __Hasher > :: HashMapDelegateIterator : public DelegateIterator {

        private:
            using HashTableIterator = typename HashMap < __KeyType, __ValueType, __Hasher > :: HashTableIterator;

        private:
            HashTableIterator   _iterator;

        public:
            __CDS_Explicit constexpr HashMapDelegateIterator (
                    HashTableIterator const & iterator
            ) noexcept;

        public:
            constexpr HashMapDelegateIterator (
                    HashMapDelegateIterator const & iterator
            ) noexcept;

        public:
            constexpr HashMapDelegateIterator (
                    HashMapDelegateIterator && iterator
            ) noexcept;

        public:
            __CDS_cpplang_ConstexprDestructor ~HashMapDelegateIterator () noexcept override;

        public:
            __CDS_NoDiscard constexpr auto valid () const noexcept -> bool override;

        public:
            __CDS_NoDiscard constexpr auto iterator () const noexcept -> HashTableIterator const &;

        public:
            __CDS_cpplang_ConstexprOverride auto next () noexcept -> HashMapDelegateIterator & override;

        public:
            __CDS_cpplang_ConstexprOverride auto previous () noexcept -> HashMapDelegateIterator & override;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto value () const noexcept -> HashMap < __KeyType, __ValueType, __Hasher > :: ElementType & override;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprOverride auto equals (
                    AbstractDelegateIterator const & iterator
            ) const noexcept -> bool override;

        public:
            __CDS_NoDiscard auto copy () const noexcept -> HashMapDelegateIterator * override;
        };

    }
}

#endif // __CDS_HASH_MAP_DELEGATE_ITERATOR_HPP__
