//
// Created by loghin on 17/07/22.
//

#ifndef __CDS_SHARED_NODE_ITERATOR_HPP__
#define __CDS_SHARED_NODE_ITERATOR_HPP__

#include "IteratorModel.hpp"

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)

                template <
                        typename __ElementType,  // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >
                > class __SingleLinkedList;      // NOLINT(bugprone-reserved-identifier)


                template <
                        typename __ElementType,  // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >
                > class __DoubleLinkedList;      // NOLINT(bugprone-reserved-identifier)

            }
        }

        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        class UnidirectionalNodeIterator : public meta :: ForwardIterator {

        private:
            template <
                    typename _T,                                                            // NOLINT(bugprone-reserved-identifier)
                    cds :: utility :: ComparisonFunction < _T > _e
            > friend class cds :: experimental :: __hidden :: __impl :: __SingleLinkedList;  // NOLINT(bugprone-reserved-identifier)

        public:
            using ElementType = __ElementType;

        private:
            using Node = cds :: __hidden :: __impl :: __UnidirectionalNode < __ElementType >;

        private:
            Node * _pCurrentNode    { nullptr };

        private:
            Node * _pPreviousNode   { nullptr };

        public:
            constexpr UnidirectionalNodeIterator () noexcept;

        public:
            constexpr UnidirectionalNodeIterator (
                    Node * pPreviousNode,
                    Node * pCurrentNode
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
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> UnidirectionalNodeIterator &;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ (int) noexcept -> UnidirectionalNodeIterator;
        };


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        class UnidirectionalNodeConstIterator : public meta :: ForwardIterator {

        private:
            template <
                    typename _T,                                                            // NOLINT(bugprone-reserved-identifier)
                    cds :: utility :: ComparisonFunction < _T > _e
            > friend class cds :: experimental :: __hidden :: __impl :: __SingleLinkedList;  // NOLINT(bugprone-reserved-identifier)

        public:
            using ElementType = __ElementType;

        private:
            using Node = cds :: __hidden :: __impl :: __UnidirectionalNode < __ElementType >;

        private:
            Node const * _pCurrentNode    { nullptr };

        private:
            Node const * _pPreviousNode   { nullptr };

        public:
            constexpr UnidirectionalNodeConstIterator () noexcept;

        public:
            constexpr UnidirectionalNodeConstIterator (
                    Node const * pPreviousNode,
                    Node const * pCurrentNode
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
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> UnidirectionalNodeConstIterator &;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ (int) noexcept -> UnidirectionalNodeConstIterator;
        };


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        class AbstractBidirectionalNodeIterator : public meta :: BidirectionalIterator {

        private:
            template <
                    typename _T,                                                            // NOLINT(bugprone-reserved-identifier)
                    cds :: utility :: ComparisonFunction < _T > _e
            > friend class cds :: experimental :: __hidden :: __impl :: __DoubleLinkedList;  // NOLINT(bugprone-reserved-identifier)

        public:
            using ElementType = __ElementType;

        protected:
            using Node = cds :: __hidden :: __impl :: __BidirectionalNode < __ElementType >;

        protected:
            Node * _pCurrentNode    { nullptr };

        protected:
            Node * _pPreviousNode   { nullptr };

        protected:
            constexpr AbstractBidirectionalNodeIterator () noexcept;

        protected:
            __CDS_Explicit constexpr AbstractBidirectionalNodeIterator (
                    Node * pPreviousNode,
                    Node * pCurrentNode
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

        private:
            template <
                    typename _T,                                                            // NOLINT(bugprone-reserved-identifier)
                    cds :: utility :: ComparisonFunction < _T > _e
            > friend class cds :: experimental :: __hidden :: __impl :: __DoubleLinkedList;  // NOLINT(bugprone-reserved-identifier)

        public:
            using ElementType = __ElementType;

        protected:
            using Node = cds :: __hidden :: __impl :: __BidirectionalNode < __ElementType >;

        protected:
            Node const * _pCurrentNode    { nullptr };

        protected:
            Node const * _pPreviousNode   { nullptr };

        protected:
            constexpr AbstractBidirectionalNodeConstIterator () noexcept;

        protected:
            __CDS_Explicit constexpr AbstractBidirectionalNodeConstIterator (
                    Node const * pPreviousNode,
                    Node const * pCurrentNode
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
            __CDS_Explicit constexpr ForwardBidirectionalNodeIterator (
                    Node * pPreviousNode,
                    Node * pCurrentNode
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
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> ForwardBidirectionalNodeIterator &;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ (int) noexcept -> ForwardBidirectionalNodeIterator;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- () noexcept -> ForwardBidirectionalNodeIterator &;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- (int) noexcept -> ForwardBidirectionalNodeIterator;
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
            __CDS_Explicit constexpr ForwardBidirectionalNodeConstIterator (
                    Node const * pPreviousNode,
                    Node const * pCurrentNode
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
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> ForwardBidirectionalNodeConstIterator &;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ (int) noexcept -> ForwardBidirectionalNodeConstIterator;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- () noexcept -> ForwardBidirectionalNodeConstIterator &;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- (int) noexcept -> ForwardBidirectionalNodeConstIterator;
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
            __CDS_Explicit constexpr BackwardBidirectionalNodeIterator (
                    Node * pPreviousNode,
                    Node * pCurrentNode
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
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> BackwardBidirectionalNodeIterator &;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ (int) noexcept -> BackwardBidirectionalNodeIterator;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- () noexcept -> BackwardBidirectionalNodeIterator &;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- (int) noexcept -> BackwardBidirectionalNodeIterator;
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
            __CDS_Explicit constexpr BackwardBidirectionalNodeConstIterator (
                    Node const * pPreviousNode,
                    Node const * pCurrentNode
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
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> BackwardBidirectionalNodeConstIterator &;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ (int) noexcept -> BackwardBidirectionalNodeConstIterator;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- () noexcept -> BackwardBidirectionalNodeConstIterator &;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- (int) noexcept -> BackwardBidirectionalNodeConstIterator;
        };

    }
}

#endif // __CDS_SHARED_NODE_ITERATOR_HPP__
