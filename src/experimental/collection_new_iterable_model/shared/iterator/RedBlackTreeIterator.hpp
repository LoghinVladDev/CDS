/*
 * Created by stefan on 16.08.2022.
 */

#ifndef __CDS_EX_SHARED_RED_BLACK_TREE_ITERATOR_HPP__
#define __CDS_EX_SHARED_RED_BLACK_TREE_ITERATOR_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {

        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template <
                        typename __TElementType,                                                                /* NOLINT(bugprone-reserved-identifier) */
                        typename __KeyType,                                                                     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __TElementType, __KeyType >,                      /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __TElementType >,                                /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __TElementType >,                                /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __TElementType >                                 /* NOLINT(bugprone-reserved-identifier) */
                > class __RedBlackTree;                                                                         /* NOLINT(bugprone-reserved-identifier) */

            }
        }

        template < typename __ElementType >                                                                 /* NOLINT(bugprone-reserved-identifier) */
        class AbstractTreeIterator : public meta :: BidirectionalIterator {

        private:
            template <
                    typename __TElementType,                                                                /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                                                                     /* NOLINT(bugprone-reserved-identifier) */
                    cds :: utility :: ExtractorFunction < __TElementType, __KeyType >,                      /* NOLINT(bugprone-reserved-identifier) */
                    cds :: utility :: ComparisonFunction < __TElementType >,                                /* NOLINT(bugprone-reserved-identifier) */
                    cds :: utility :: ComparisonFunction < __TElementType >,                                /* NOLINT(bugprone-reserved-identifier) */
                    cds :: utility :: DestructorFunction < __TElementType >                                 /* NOLINT(bugprone-reserved-identifier) */
            > friend class cds :: experimental :: __hidden :: __impl :: __RedBlackTree;                     /* NOLINT(bugprone-reserved-identifier) */


        protected:
            using RBTreeNode = cds :: __hidden :: __impl :: __RedBlackTreeNode < __ElementType >;

        private:
            RBTreeNode *         _pRoot          { 0ULL };

        private:
            RBTreeNode *         _pCurrentNode  { nullptr };

        protected:
            constexpr AbstractTreeIterator () noexcept;

        protected:
            constexpr AbstractTreeIterator (
                    RBTreeNode * pRoot,
                    RBTreeNode * pCurrentNode
            ) noexcept;

        protected:
            constexpr AbstractTreeIterator (
                    AbstractTreeIterator const & iterator
            ) noexcept;

        protected:
            constexpr AbstractTreeIterator (
                    AbstractTreeIterator && iterator
            ) noexcept;

        protected:

        public:
            __CDS_NoDiscard constexpr auto operator * () const noexcept -> __ElementType &;

        public:
            __CDS_NoDiscard constexpr auto operator -> () const noexcept -> __ElementType *;

        public:
            __CDS_NoDiscard constexpr auto operator == (
                    AbstractTreeIterator const & iterator
            ) const noexcept -> bool;

        public:
            __CDS_NoDiscard constexpr auto operator != (
                    AbstractTreeIterator const & iterator
            ) const noexcept -> bool;

        public:
            __CDS_Explicit constexpr operator bool () const noexcept;

        protected:
            __CDS_cpplang_ConstexprConditioned auto advance () noexcept -> void;

        protected:
            __CDS_cpplang_ConstexprConditioned auto reverse () noexcept -> void;
        };


        template < typename __ElementType >     /* NOLINT(bugprone-reserved-identifier) */
        class AbstractTreeConstIterator : public meta :: BidirectionalIterator {
            template <
                    typename __TElementType,                                                                /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                                                                     /* NOLINT(bugprone-reserved-identifier) */
                    cds :: utility :: ExtractorFunction < __TElementType, __KeyType >,                      /* NOLINT(bugprone-reserved-identifier) */
                    cds :: utility :: ComparisonFunction < __TElementType >,                                /* NOLINT(bugprone-reserved-identifier) */
                    cds :: utility :: ComparisonFunction < __TElementType >,                                /* NOLINT(bugprone-reserved-identifier) */
                    cds :: utility :: DestructorFunction < __TElementType >                                 /* NOLINT(bugprone-reserved-identifier) */
            > friend class cds :: experimental :: __hidden :: __impl :: __RedBlackTree;                     /* NOLINT(bugprone-reserved-identifier) */


        protected:
            using RBTreeNode = cds :: __hidden :: __impl :: __RedBlackTreeNode < __ElementType >;

        private:
            RBTreeNode const *         _pRoot          { 0ULL };

        private:
            RBTreeNode const *         _pCurrentNode  { nullptr };

        protected:
            constexpr AbstractTreeConstIterator () noexcept;

        protected:
            constexpr AbstractTreeConstIterator (
                    RBTreeNode const * pRoot,
                    RBTreeNode const * pCurrentNode
            ) noexcept;

        protected:
            constexpr AbstractTreeConstIterator (
                    AbstractTreeConstIterator const & iterator
            ) noexcept;

        protected:
            constexpr AbstractTreeConstIterator (
                    AbstractTreeConstIterator && iterator
            ) noexcept;

        protected:

        public:
            __CDS_NoDiscard constexpr auto operator * () const noexcept -> __ElementType const &;

        public:
            __CDS_NoDiscard constexpr auto operator -> () const noexcept -> __ElementType const *;

        public:
            __CDS_NoDiscard constexpr auto operator == (
                    AbstractTreeConstIterator const & iterator
            ) const noexcept -> bool;

        public:
            __CDS_NoDiscard constexpr auto operator != (
                    AbstractTreeConstIterator const & iterator
            ) const noexcept -> bool;

        public:
            __CDS_Explicit constexpr operator bool () const noexcept;

        protected:
            auto advance () noexcept -> void;

        protected:
            auto reverse () noexcept -> void;
        };
        

        template < typename __ElementType >                                                             /* NOLINT(bugprone-reserved-identifier) */
        class RedBlackTreeForwardIterator : public AbstractTreeIterator < __ElementType > {

        private:
            template <
                    typename __TElementType,                                                            /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                                                                 /* NOLINT(bugprone-reserved-identifier) */
                    cds :: utility :: ExtractorFunction < __TElementType, __KeyType >,                  /* NOLINT(bugprone-reserved-identifier) */
                    cds :: utility :: ComparisonFunction < __TElementType >,                            /* NOLINT(bugprone-reserved-identifier) */
                    cds :: utility :: ComparisonFunction < __TElementType >,                            /* NOLINT(bugprone-reserved-identifier) */
                    cds :: utility :: DestructorFunction < __TElementType >                             /* NOLINT(bugprone-reserved-identifier) */
            > friend class cds :: experimental :: __hidden :: __impl :: __RedBlackTree;                 /* NOLINT(bugprone-reserved-identifier) */

        private:
            using typename AbstractTreeIterator < __ElementType > :: RBTreeNode;

        public:
            constexpr RedBlackTreeForwardIterator () noexcept;

        public:
            constexpr RedBlackTreeForwardIterator (
                    RBTreeNode * pRoot,
                    RBTreeNode * pCurrentNode
            ) noexcept;

        public:
            constexpr RedBlackTreeForwardIterator (
                    RedBlackTreeForwardIterator const & iterator
            ) noexcept;

        public:
            constexpr RedBlackTreeForwardIterator (
                    RedBlackTreeForwardIterator && iterator
            ) noexcept;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                    RedBlackTreeForwardIterator const & iterator
            ) noexcept -> RedBlackTreeForwardIterator &;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                    RedBlackTreeForwardIterator && iterator
            ) noexcept -> RedBlackTreeForwardIterator &;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> RedBlackTreeForwardIterator &;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ (int) noexcept -> RedBlackTreeForwardIterator;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- () noexcept -> RedBlackTreeForwardIterator &;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- (int) noexcept -> RedBlackTreeForwardIterator;

        };


        template < typename __ElementType >                                                             /* NOLINT(bugprone-reserved-identifier) */
        class RedBlackTreeForwardConstIterator : public AbstractTreeConstIterator < __ElementType > {   /* NOLINT(bugprone-reserved-identifier) */
            template <
                    typename __TElementType,                                                            /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                                                                 /* NOLINT(bugprone-reserved-identifier) */
                    cds :: utility :: ExtractorFunction < __TElementType, __KeyType >,                  /* NOLINT(bugprone-reserved-identifier) */
                    cds :: utility :: ComparisonFunction < __TElementType >,                            /* NOLINT(bugprone-reserved-identifier) */
                    cds :: utility :: ComparisonFunction < __TElementType >,                            /* NOLINT(bugprone-reserved-identifier) */
                    cds :: utility :: DestructorFunction < __TElementType >                             /* NOLINT(bugprone-reserved-identifier) */
            > friend class cds :: experimental :: __hidden :: __impl :: __RedBlackTree;                 /* NOLINT(bugprone-reserved-identifier) */

        private:
            using typename AbstractTreeConstIterator < __ElementType > :: RBTreeNode;

        public:
            RedBlackTreeForwardConstIterator () noexcept;

        public:
            RedBlackTreeForwardConstIterator (
                    RBTreeNode const * pRoot, RBTreeNode const * pCurrentNode
            ) noexcept;

        public:
            RedBlackTreeForwardConstIterator (
                    RedBlackTreeForwardConstIterator const & iterator
            ) noexcept;

        public:
            RedBlackTreeForwardConstIterator (
                    RedBlackTreeForwardConstIterator && iterator
            ) noexcept;

        public:
            auto operator = (
                    RedBlackTreeForwardConstIterator const & iterator
            ) noexcept -> RedBlackTreeForwardConstIterator &;

        public:
            auto operator = (
                    RedBlackTreeForwardConstIterator && iterator
            ) noexcept -> RedBlackTreeForwardConstIterator &;

        public:
            auto operator ++ () noexcept -> RedBlackTreeForwardConstIterator &;

        public:
            auto operator ++ (int) noexcept -> RedBlackTreeForwardConstIterator;

        public:
            auto operator -- () noexcept -> RedBlackTreeForwardConstIterator &;

        public:
            auto operator -- (int) noexcept -> RedBlackTreeForwardConstIterator;

        };





        template < typename __ElementType >                                                             /* NOLINT(bugprone-reserved-identifier) */
        class RedBlackTreeBackwardIterator : public AbstractTreeIterator < __ElementType > {
            template <
                    typename __TElementType,                                                            /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                                                                 /* NOLINT(bugprone-reserved-identifier) */
                    cds :: utility :: ExtractorFunction < __TElementType, __KeyType >,                  /* NOLINT(bugprone-reserved-identifier) */
                    cds :: utility :: ComparisonFunction < __TElementType >,                            /* NOLINT(bugprone-reserved-identifier) */
                    cds :: utility :: ComparisonFunction < __TElementType >,                            /* NOLINT(bugprone-reserved-identifier) */
                    cds :: utility :: DestructorFunction < __TElementType >                             /* NOLINT(bugprone-reserved-identifier) */
            > friend class cds :: experimental :: __hidden :: __impl :: __RedBlackTree;                 /* NOLINT(bugprone-reserved-identifier) */

        private:
            using typename AbstractTreeIterator < __ElementType > :: RBTreeNode;

        public:
            RedBlackTreeBackwardIterator () noexcept;

        public:
            RedBlackTreeBackwardIterator (
                    RBTreeNode * pRoot,
                    RBTreeNode * pCurrentNode
            ) noexcept;

        public:
            RedBlackTreeBackwardIterator (
                    RedBlackTreeBackwardIterator const & iterator
            ) noexcept;

        public:
            RedBlackTreeBackwardIterator (
                    RedBlackTreeBackwardIterator && iterator
            ) noexcept;

        public:
            auto operator = (
                    RedBlackTreeBackwardIterator const & iterator
            ) noexcept -> RedBlackTreeBackwardIterator &;

        public:
            auto operator = (
                    RedBlackTreeBackwardIterator && iterator
            ) noexcept -> RedBlackTreeBackwardIterator &;

        public:
            auto operator ++ () noexcept -> RedBlackTreeBackwardIterator &;

        public:
            auto operator ++ (int) noexcept -> RedBlackTreeBackwardIterator;

        public:
            auto operator -- () noexcept -> RedBlackTreeBackwardIterator &;

        public:
            auto operator -- (int) noexcept -> RedBlackTreeBackwardIterator;

        };


        template < typename __ElementType >                                                             /* NOLINT(bugprone-reserved-identifier) */
        class RedBlackTreeBackwardConstIterator : public AbstractTreeConstIterator < __ElementType > {  /* NOLINT(bugprone-reserved-identifier) */
            template <
                    typename __TElementType,                                                            /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                                                                 /* NOLINT(bugprone-reserved-identifier) */
                    cds :: utility :: ExtractorFunction < __TElementType, __KeyType >,                  /* NOLINT(bugprone-reserved-identifier) */
                    cds :: utility :: ComparisonFunction < __TElementType >,                            /* NOLINT(bugprone-reserved-identifier) */
                    cds :: utility :: ComparisonFunction < __TElementType >,                            /* NOLINT(bugprone-reserved-identifier) */
                    cds :: utility :: DestructorFunction < __TElementType >                             /* NOLINT(bugprone-reserved-identifier) */
            > friend class cds :: experimental :: __hidden :: __impl :: __RedBlackTree;                 /* NOLINT(bugprone-reserved-identifier) */

        private:
            using typename AbstractTreeConstIterator < __ElementType > :: RBTreeNode;

        public:
            RedBlackTreeBackwardConstIterator () noexcept;

        public:
            RedBlackTreeBackwardConstIterator (
                    RBTreeNode const * pRoot, RBTreeNode const * pCurrentNode
            ) noexcept;

        public:
            RedBlackTreeBackwardConstIterator (
                    RedBlackTreeBackwardConstIterator const & iterator
            ) noexcept;

        public:
            RedBlackTreeBackwardConstIterator (
                    RedBlackTreeBackwardConstIterator && iterator
            ) noexcept;

        public:
            auto operator = (
                    RedBlackTreeBackwardConstIterator const & iterator
            ) noexcept -> RedBlackTreeBackwardConstIterator &;

        public:
            auto operator = (
                    RedBlackTreeBackwardConstIterator && iterator
            ) noexcept -> RedBlackTreeBackwardConstIterator &;

        public:
            auto operator ++ () noexcept -> RedBlackTreeBackwardConstIterator &;

        public:
            auto operator ++ (int) noexcept -> RedBlackTreeBackwardConstIterator;

        public:
            auto operator -- () noexcept -> RedBlackTreeBackwardConstIterator &;

        public:
            auto operator -- (int) noexcept -> RedBlackTreeBackwardConstIterator;

        };
    }
}

#endif /* __CDS_EX_SHARED_RED_BLACK_TREE_ITERATOR_HPP__ */
