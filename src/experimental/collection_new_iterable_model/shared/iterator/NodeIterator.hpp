//
// Created by loghin on 17/07/22.
//

#ifndef __CDS_SHARED_NODE_ITERATOR_HPP__
#define __CDS_SHARED_NODE_ITERATOR_HPP__

#include "IteratorModel.hpp"

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        class UnidirectionalNodeIterator : public meta :: ForwardIterator {

        public:
            using ElementType = __ElementType;

        private:
            using Node = cds :: __hidden :: __impl :: __UnidirectionalNode < __ElementType >;

        private:
            Node * _pCurrentNode { nullptr };

        public:
            constexpr UnidirectionalNodeIterator () noexcept;

        public:
            constexpr UnidirectionalNodeIterator (
                    Node * pNode
            ) noexcept;

        public:
            constexpr UnidirectionalNodeIterator (
                    UnidirectionalNodeIterator const & iterator
            ) noexcept;

        public:
            constexpr UnidirectionalNodeIterator (
                    UnidirectionalNodeIterator && iterator
            ) noexcept;

        public:
            __CDS_NoDiscard constexpr auto operator * () const noexcept -> __ElementType &;

        public:
            __CDS_NoDiscard constexpr auto operator -> () const noexcept -> __ElementType *;

        public:
            __CDS_NoDiscard constexpr auto operator == (
                    UnidirectionalNodeIterator < __ElementType > const & iterator
            ) const noexcept -> bool;

        public:
            __CDS_NoDiscard constexpr auto operator != (
                    UnidirectionalNodeIterator < __ElementType > const & iterator
            ) const noexcept -> bool;

        public:
            __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> UnidirectionalNodeIterator &;

        public:
            __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ (int) noexcept -> UnidirectionalNodeIterator;

        public:
            __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- () noexcept -> UnidirectionalNodeIterator &;

        public:
            __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- (int) noexcept -> UnidirectionalNodeIterator;
        };


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        class UnidirectionalNodeConstIterator : public meta :: ForwardIterator {

        public:
            using ElementType = __ElementType;

        private:
            using Node = cds :: __hidden :: __impl :: __UnidirectionalNode < __ElementType >;

        private:
            Node const * _pCurrentNode { nullptr };

        public:
            constexpr UnidirectionalNodeConstIterator () noexcept;

        public:
            constexpr UnidirectionalNodeConstIterator (
                    Node const * pNode
            ) noexcept;

        public:
            constexpr UnidirectionalNodeConstIterator (
                    UnidirectionalNodeConstIterator const & iterator
            ) noexcept;

        public:
            constexpr UnidirectionalNodeConstIterator (
                    UnidirectionalNodeConstIterator && iterator
            ) noexcept;

        public:
            __CDS_NoDiscard constexpr auto operator * () const noexcept -> __ElementType const &;

        public:
            __CDS_NoDiscard constexpr auto operator -> () const noexcept -> __ElementType const *;

        public:
            __CDS_NoDiscard constexpr auto operator == (
                    UnidirectionalNodeConstIterator < __ElementType > const & iterator
            ) const noexcept -> bool;

        public:
            __CDS_NoDiscard constexpr auto operator != (
                    UnidirectionalNodeConstIterator < __ElementType > const & iterator
            ) const noexcept -> bool;

        public:
            __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> UnidirectionalNodeConstIterator &;

        public:
            __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ (int) noexcept -> UnidirectionalNodeConstIterator;

        public:
            __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- () noexcept -> UnidirectionalNodeConstIterator &;

        public:
            __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- (int) noexcept -> UnidirectionalNodeConstIterator;
        };


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        class AbstractBidirectionalNodeIterator : public meta :: BidirectionalIterator {

        public:
            using ElementType = __ElementType;

        protected:
            using Node = cds :: __hidden :: __impl :: __BidirectionalNode < __ElementType >;

        protected:
            Node * _pCurrentNode { nullptr };

        protected:
            constexpr AbstractBidirectionalNodeIterator () noexcept;

        protected:
            constexpr AbstractBidirectionalNodeIterator (
                    Node * pNode
            ) noexcept;

        protected:
            constexpr AbstractBidirectionalNodeIterator (
                    AbstractBidirectionalNodeIterator const & iterator
            ) noexcept;

        protected:
            constexpr AbstractBidirectionalNodeIterator (
                    AbstractBidirectionalNodeIterator && iterator
            ) noexcept;

        public:
            __CDS_NoDiscard constexpr auto operator * () const noexcept -> __ElementType &;

        public:
            __CDS_NoDiscard constexpr auto operator -> () const noexcept -> __ElementType *;

        public:
            __CDS_NoDiscard constexpr auto operator == (
                    AbstractBidirectionalNodeIterator < __ElementType > const & iterator
            ) const noexcept -> bool;

        public:
            __CDS_NoDiscard constexpr auto operator != (
                    AbstractBidirectionalNodeIterator < __ElementType > const & iterator
            ) const noexcept -> bool;
        };


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        class AbstractBidirectionalNodeConstIterator : public meta :: BidirectionalIterator {

        public:
            using ElementType = __ElementType;

        protected:
            using Node = cds :: __hidden :: __impl :: __BidirectionalNode < __ElementType >;

        protected:
            Node const * _pCurrentNode { nullptr };

        protected:
            constexpr AbstractBidirectionalNodeConstIterator () noexcept;

        protected:
            constexpr AbstractBidirectionalNodeConstIterator (
                    Node const * pNode
            ) noexcept;

        protected:
            constexpr AbstractBidirectionalNodeConstIterator (
                    AbstractBidirectionalNodeConstIterator const & iterator
            ) noexcept;

        protected:
            constexpr AbstractBidirectionalNodeConstIterator (
                    AbstractBidirectionalNodeConstIterator && iterator
            ) noexcept;

        public:
            __CDS_NoDiscard constexpr auto operator * () const noexcept -> __ElementType const &;

        public:
            __CDS_NoDiscard constexpr auto operator -> () const noexcept -> __ElementType const *;

        public:
            __CDS_NoDiscard constexpr auto operator == (
                    AbstractBidirectionalNodeConstIterator < __ElementType > const & iterator
            ) const noexcept -> bool;

        public:
            __CDS_NoDiscard constexpr auto operator != (
                    AbstractBidirectionalNodeConstIterator < __ElementType > const & iterator
            ) const noexcept -> bool;
        };


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        class ForwardBidirectionalNodeIterator : public AbstractBidirectionalNodeIterator < __ElementType > {

        public:
            using ElementType = __ElementType;

        private:
            using typename AbstractBidirectionalNodeIterator < __ElementType > :: Node;

        public:
            constexpr ForwardBidirectionalNodeIterator () noexcept;

        public:
            constexpr ForwardBidirectionalNodeIterator (
                    Node * pNode
            ) noexcept;

        public:
            constexpr ForwardBidirectionalNodeIterator (
                    ForwardBidirectionalNodeIterator const & iterator
            ) noexcept;

        public:
            constexpr ForwardBidirectionalNodeIterator (
                    ForwardBidirectionalNodeIterator && iterator
            ) noexcept;

        public:
            __CDS_NoDiscard constexpr auto operator == (
                    ForwardBidirectionalNodeIterator < __ElementType > const & iterator
            ) const noexcept -> bool;

        public:
            __CDS_NoDiscard constexpr auto operator != (
                    ForwardBidirectionalNodeIterator < __ElementType > const & iterator
            ) const noexcept -> bool;

        public:
            __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> ForwardBidirectionalNodeIterator &;

        public:
            __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ (int) noexcept -> ForwardBidirectionalNodeIterator;

        public:
            __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- () noexcept -> ForwardBidirectionalNodeIterator &;

        public:
            __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- (int) noexcept -> ForwardBidirectionalNodeIterator;
        };


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        class ForwardBidirectionalNodeConstIterator : public AbstractBidirectionalNodeConstIterator < __ElementType > {

        public:
            using ElementType = __ElementType;

        private:
            using typename AbstractBidirectionalNodeConstIterator < __ElementType > :: Node;

        public:
            constexpr ForwardBidirectionalNodeConstIterator () noexcept;

        public:
            constexpr ForwardBidirectionalNodeConstIterator (
                    Node const * pNode
            ) noexcept;

        public:
            constexpr ForwardBidirectionalNodeConstIterator (
                    ForwardBidirectionalNodeConstIterator const & iterator
            ) noexcept;

        public:
            constexpr ForwardBidirectionalNodeConstIterator (
                    ForwardBidirectionalNodeConstIterator && iterator
            ) noexcept;

        public:
            __CDS_NoDiscard constexpr auto operator == (
                    ForwardBidirectionalNodeConstIterator < __ElementType > const & iterator
            ) const noexcept -> bool;

        public:
            __CDS_NoDiscard constexpr auto operator != (
                    ForwardBidirectionalNodeConstIterator < __ElementType > const & iterator
            ) const noexcept -> bool;

        public:
            __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> ForwardBidirectionalNodeConstIterator &;

        public:
            __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ (int) noexcept -> ForwardBidirectionalNodeConstIterator;

        public:
            __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- () noexcept -> ForwardBidirectionalNodeConstIterator &;

        public:
            __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- (int) noexcept -> ForwardBidirectionalNodeConstIterator;
        };


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        class BackwardBidirectionalNodeIterator : public AbstractBidirectionalNodeIterator < __ElementType > {

        public:
            using ElementType = __ElementType;

        private:
            using typename AbstractBidirectionalNodeIterator < __ElementType > :: Node;

        public:
            constexpr BackwardBidirectionalNodeIterator () noexcept;

        public:
            constexpr BackwardBidirectionalNodeIterator (
                    Node * pNode
            ) noexcept;

        public:
            constexpr BackwardBidirectionalNodeIterator (
                    BackwardBidirectionalNodeIterator const & iterator
            ) noexcept;

        public:
            constexpr BackwardBidirectionalNodeIterator (
                    BackwardBidirectionalNodeIterator && iterator
            ) noexcept;

        public:
            __CDS_NoDiscard constexpr auto operator == (
                    BackwardBidirectionalNodeIterator < __ElementType > const & iterator
            ) const noexcept -> bool;

        public:
            __CDS_NoDiscard constexpr auto operator != (
                    BackwardBidirectionalNodeIterator < __ElementType > const & iterator
            ) const noexcept -> bool;

        public:
            __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> BackwardBidirectionalNodeIterator &;

        public:
            __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ (int) noexcept -> BackwardBidirectionalNodeIterator;

        public:
            __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- () noexcept -> BackwardBidirectionalNodeIterator &;

        public:
            __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- (int) noexcept -> BackwardBidirectionalNodeIterator;
        };


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        class BackwardBidirectionalNodeConstIterator : public AbstractBidirectionalNodeConstIterator < __ElementType > {

        public:
            using ElementType = __ElementType;

        private:
            using typename AbstractBidirectionalNodeConstIterator < __ElementType > :: Node;

        public:
            constexpr BackwardBidirectionalNodeConstIterator () noexcept;

        public:
            constexpr BackwardBidirectionalNodeConstIterator (
                    Node const * pNode
            ) noexcept;

        public:
            constexpr BackwardBidirectionalNodeConstIterator (
                    BackwardBidirectionalNodeConstIterator const & iterator
            ) noexcept;

        public:
            constexpr BackwardBidirectionalNodeConstIterator (
                    BackwardBidirectionalNodeConstIterator && iterator
            ) noexcept;

        public:
            __CDS_NoDiscard constexpr auto operator == (
                    BackwardBidirectionalNodeConstIterator < __ElementType > const & iterator
            ) const noexcept -> bool;

        public:
            __CDS_NoDiscard constexpr auto operator != (
                    BackwardBidirectionalNodeConstIterator < __ElementType > const & iterator
            ) const noexcept -> bool;

        public:
            __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> BackwardBidirectionalNodeConstIterator &;

        public:
            __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ (int) noexcept -> BackwardBidirectionalNodeConstIterator;

        public:
            __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- () noexcept -> BackwardBidirectionalNodeConstIterator &;

        public:
            __CDS_NoDiscard __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- (int) noexcept -> BackwardBidirectionalNodeConstIterator;
        };

    }
}

#endif // __CDS_SHARED_NODE_ITERATOR_HPP__
