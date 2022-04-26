//
// Created by loghin on 4/26/22.
//

#ifndef __CDS_COLLECTION_ABSTRACT_DELEGATE_ITERATOR_HPP__
#define __CDS_COLLECTION_ABSTRACT_DELEGATE_ITERATOR_HPP__

namespace cds {
    namespace experimental {

        template < typename T >
        class Collection < T > :: AbstractDelegateIterator {
        protected:
            constexpr AbstractDelegateIterator () noexcept = default;
        public:
            virtual ~AbstractDelegateIterator () noexcept = default;

        public:
            __CDS_cpplang_ConstexprPureAbstract virtual auto next () noexcept -> AbstractDelegateIterator & = 0;
        public:
            __CDS_cpplang_ConstexprPureAbstract virtual auto previous () noexcept -> AbstractDelegateIterator & = 0;
        public:
            __CDS_cpplang_ConstexprPureAbstract virtual auto equals ( AbstractDelegateIterator const & ) const noexcept -> bool = 0;

        public:
            virtual auto valid () const noexcept -> bool = 0;
        };

    }
}

#endif // __CDS_COLLECTION_ABSTRACT_DELEGATE_ITERATOR_HPP__
