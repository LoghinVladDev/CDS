//
// Created by loghin on 4/26/22.
//

#ifndef __CDS_COLLECTION_ABSTRACT_ITERATOR_HPP__
#define __CDS_COLLECTION_ABSTRACT_ITERATOR_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename T >
        class Collection < T > :: AbstractIterator {
        private:
            friend class Collection < T >;

        protected:
            Collection < T > const *                            _pCollection { nullptr };
            cds :: UniquePointer < AbstractDelegateIterator >   _pDelegate { nullptr };

        protected:
            constexpr AbstractIterator () noexcept = default;
        protected:
            __CDS_OptimalInline AbstractIterator ( AbstractIterator const & ) noexcept;
        protected:
            constexpr AbstractIterator ( AbstractIterator && ) noexcept;
        public:
            virtual ~AbstractIterator () noexcept = default;
        public:
            constexpr AbstractIterator (
                    Collection < T > const *,
                    cds :: UniquePointer < AbstractDelegateIterator > &&
            ) noexcept;

        public:
            __CDS_NoDiscard constexpr auto of ( Collection < T > const * ) const noexcept -> bool;

        public:
            __CDS_cpplang_ConstexprPureAbstract auto next () noexcept -> AbstractIterator &;
        public:
            __CDS_cpplang_ConstexprPureAbstract auto previous () noexcept -> AbstractIterator &;
        public:
            __CDS_NoDiscard __CDS_OptimalInline auto valid () const noexcept -> bool;
        public:
            __CDS_cpplang_ConstexprOverride auto equals ( AbstractIterator const & ) const noexcept -> bool;

        public:
            __CDS_cpplang_ConstexprOverride auto operator == ( AbstractIterator const & ) const noexcept -> bool;
        public:
            __CDS_cpplang_ConstexprOverride auto operator != ( AbstractIterator const & ) const noexcept -> bool;
        };

    }
}

#endif // __CDS_COLLECTION_ABSTRACT_ITERATOR_HPP__
