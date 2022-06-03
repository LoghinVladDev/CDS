//
// Created by loghin on 4/26/22.
//

#ifndef __CDS_LIST_DELEGATE_ITERATOR_HPP__
#define __CDS_LIST_DELEGATE_ITERATOR_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename T >
        class List < T > :: DelegateIterator : public List < T > :: AbstractDelegateIterator {
        protected:
            constexpr DelegateIterator () noexcept = default;
        public:
            ~DelegateIterator () noexcept override = default;

        public:
            __CDS_cpplang_ConstexprPureAbstract auto next () noexcept -> DelegateIterator & override = 0;
        public:
            __CDS_cpplang_ConstexprPureAbstract auto previous () noexcept -> DelegateIterator & override = 0;
        public:
            __CDS_cpplang_ConstexprPureAbstract virtual auto value () const noexcept -> ElementType & = 0;
        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract auto equals ( AbstractDelegateIterator const & ) const noexcept -> bool override = 0;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract auto valid () const noexcept -> bool override = 0;
        };

    }
}

#endif // __CDS_LIST_DELEGATE_ITERATOR_HPP__
