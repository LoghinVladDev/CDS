//
// Created by loghin on 6/17/22.
//

#ifndef __CDS_MAP_DELEGATE_ITERATOR_HPP__
#define __CDS_MAP_DELEGATE_ITERATOR_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        class Map < __KeyType, __ValueType > :: DelegateIterator : public Map < __KeyType, __ValueType > :: AbstractDelegateIterator {

        protected:
            constexpr DelegateIterator () noexcept = default;

        public:
            ~DelegateIterator () noexcept override = default;

        public:
            __CDS_cpplang_ConstexprPureAbstract auto next () noexcept -> DelegateIterator & override = 0;

        public:
            __CDS_cpplang_ConstexprPureAbstract auto previous () noexcept -> DelegateIterator & override = 0;

        public:
            __CDS_cpplang_ConstexprPureAbstract virtual auto value () const noexcept -> Map < __KeyType, __ValueType > :: EntryType & = 0;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract auto equals (
                    AbstractDelegateIterator const & iterator
            ) const noexcept -> bool override = 0;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract auto valid () const noexcept -> bool override = 0;
        };

    }
}

#endif // __CDS_MAP_DELEGATE_ITERATOR_HPP__
