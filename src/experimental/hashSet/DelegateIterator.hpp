//
// Created by loghin on 6/13/22.
//

#ifndef __CDS_EX_HASH_SET_DELEGATE_ITERATOR_HPP__
#define __CDS_EX_HASH_SET_DELEGATE_ITERATOR_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        class HashSet < __ElementType, __HashCalculator > :: HashSetDelegateIterator : public DelegateConstIterator {

        private:
            using Node = typename HashSet < __ElementType, __HashCalculator > :: Node;

        private:
            Node                                        const * _pCurrentNode { nullptr };

        private:
            Index                                               _currentListIndex { 0 };

        private:
            HashSet < __ElementType, __HashCalculator > const * _pHashSet { nullptr };

        private:
            __CDS_cpplang_ConstexprConditioned auto skipEmpty () noexcept -> void;

        public:
            __CDS_Explicit __CDS_cpplang_ConstexprConstructorNonEmptyBody HashSetDelegateIterator (
                    HashSet < __ElementType, __HashCalculator > const * pHashSet
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
            __CDS_NoDiscard constexpr auto currentListIndex () const noexcept -> Index;

        public:
            __CDS_NoDiscard constexpr auto currentNode () const noexcept -> Node const *;

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