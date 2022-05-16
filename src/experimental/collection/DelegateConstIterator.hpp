//
// Created by loghin on 4/26/22.
//

#ifndef __CDS_COLLECTION_DELEGATE_CONST_ITERATOR_HPP__
#define __CDS_COLLECTION_DELEGATE_CONST_ITERATOR_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename T >
        class Collection < T > :: DelegateConstIterator : public Collection < T > :: AbstractDelegateIterator {
        protected:
            constexpr DelegateConstIterator () noexcept = default;
        public:
            ~DelegateConstIterator () noexcept override = default;

        public:
            __CDS_cpplang_ConstexprPureAbstract auto next () noexcept -> DelegateConstIterator & override = 0;
        public:
            __CDS_cpplang_ConstexprPureAbstract auto previous () noexcept -> DelegateConstIterator & override = 0;
        public:
            __CDS_cpplang_ConstexprPureAbstract virtual auto value () const noexcept -> ElementType const & = 0;
        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract auto equals ( AbstractDelegateIterator const & ) const noexcept -> bool override = 0;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprPureAbstract auto valid () const noexcept -> bool override = 0;
        };

    }
}

#endif // __CDS_COLLECTION_DELEGATE_CONST_ITERATOR_HPP__