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
                        cds :: utility :: ComparisonFunction < __KeyType >,                                     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __KeyType >,                                     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __TElementType >                                 /* NOLINT(bugprone-reserved-identifier) */
                > class __RedBlackTree;                                                                         /* NOLINT(bugprone-reserved-identifier) */

            }
        }

        template < typename __ElementType >                                                                     /* NOLINT(bugprone-reserved-identifier) */
        class AbstractRedBlackTreeIterator : public cds :: meta :: BidirectionalIterator {

        private:
            template <
                    typename __TElementType,                                                                /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                                                                     /* NOLINT(bugprone-reserved-identifier) */
                    cds :: utility :: ExtractorFunction < __TElementType, __KeyType >,                      /* NOLINT(bugprone-reserved-identifier) */
                    cds :: utility :: ComparisonFunction < __KeyType >,                                     /* NOLINT(bugprone-reserved-identifier) */
                    cds :: utility :: ComparisonFunction < __KeyType >,                                     /* NOLINT(bugprone-reserved-identifier) */
                    cds :: utility :: DestructorFunction < __TElementType >                                 /* NOLINT(bugprone-reserved-identifier) */
            > friend class cds :: experimental :: __hidden :: __impl :: __RedBlackTree;                     /* NOLINT(bugprone-reserved-identifier) */


        protected:
            using RBTreeNode = cds :: __hidden :: __impl :: __RedBlackTreeNode < __ElementType >;

        private:
            RBTreeNode *         _pRoot          { 0ULL };

        private:
            RBTreeNode *         _pCurrentNode  { nullptr };

        protected:
            constexpr AbstractRedBlackTreeIterator () noexcept;

        protected:
            constexpr AbstractRedBlackTreeIterator (
                    RBTreeNode * pRoot,
                    RBTreeNode * pCurrentNode
            ) noexcept;

        protected:
            constexpr AbstractRedBlackTreeIterator (
                    AbstractRedBlackTreeIterator const & iterator
            ) noexcept;

        protected:
            constexpr AbstractRedBlackTreeIterator (
                    AbstractRedBlackTreeIterator && iterator
            ) noexcept;

        protected:

        public:
            __CDS_NoDiscard constexpr auto operator * () const noexcept -> __ElementType &;

        public:
            __CDS_NoDiscard constexpr auto operator -> () const noexcept -> __ElementType *;

        public:
            __CDS_NoDiscard constexpr auto operator == (
                    AbstractRedBlackTreeIterator const & iterator
            ) const noexcept -> bool;

        public:
            __CDS_NoDiscard constexpr auto operator != (
                    AbstractRedBlackTreeIterator const & iterator
            ) const noexcept -> bool;

        public:
            __CDS_Explicit constexpr operator bool () const noexcept;

        protected:
            __CDS_cpplang_ConstexprConditioned auto advance () noexcept -> void;

        protected:
            __CDS_cpplang_ConstexprConditioned auto reverse () noexcept -> void;
        };


        template < typename __ElementType >     /* NOLINT(bugprone-reserved-identifier) */
        class AbstractRedBlackTreeConstIterator : public meta :: BidirectionalIterator {
            template <
                    typename __TElementType,                                                                /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                                                                     /* NOLINT(bugprone-reserved-identifier) */
                    cds :: utility :: ExtractorFunction < __TElementType, __KeyType >,                      /* NOLINT(bugprone-reserved-identifier) */
                    cds :: utility :: ComparisonFunction < __KeyType >,                                     /* NOLINT(bugprone-reserved-identifier) */
                    cds :: utility :: ComparisonFunction < __KeyType >,                                     /* NOLINT(bugprone-reserved-identifier) */
                    cds :: utility :: DestructorFunction < __TElementType >                                 /* NOLINT(bugprone-reserved-identifier) */
            > friend class cds :: experimental :: __hidden :: __impl :: __RedBlackTree;                     /* NOLINT(bugprone-reserved-identifier) */


        protected:
            using RBTreeNode = cds :: __hidden :: __impl :: __RedBlackTreeNode < __ElementType >;

        private:
            RBTreeNode const *         _pRoot          { 0ULL };

        private:
            RBTreeNode const *         _pCurrentNode  { nullptr };

        protected:
            constexpr AbstractRedBlackTreeConstIterator () noexcept;

        protected:
            constexpr AbstractRedBlackTreeConstIterator (
                    RBTreeNode const * pRoot,
                    RBTreeNode const * pCurrentNode
            ) noexcept;

        protected:
            constexpr AbstractRedBlackTreeConstIterator (
                    AbstractRedBlackTreeConstIterator const & iterator
            ) noexcept;

        protected:
            constexpr AbstractRedBlackTreeConstIterator (
                    AbstractRedBlackTreeConstIterator && iterator
            ) noexcept;

        protected:

        public:
            __CDS_NoDiscard constexpr auto operator * () const noexcept -> __ElementType const &;

        public:
            __CDS_NoDiscard constexpr auto operator -> () const noexcept -> __ElementType const *;

        public:
            __CDS_NoDiscard constexpr auto operator == (
                    AbstractRedBlackTreeConstIterator const & iterator
            ) const noexcept -> bool;

        public:
            __CDS_NoDiscard constexpr auto operator != (
                    AbstractRedBlackTreeConstIterator const & iterator
            ) const noexcept -> bool;

        public:
            __CDS_Explicit constexpr operator bool () const noexcept;

        protected:
            auto advance () noexcept -> void;

        protected:
            auto reverse () noexcept -> void;
        };


        template < typename __ElementType >                                                             /* NOLINT(bugprone-reserved-identifier) */
        class RedBlackTreeForwardIterator : public AbstractRedBlackTreeIterator < __ElementType > {

        private:
            template <
                    typename __TElementType,                                                            /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                                                                 /* NOLINT(bugprone-reserved-identifier) */
                    cds :: utility :: ExtractorFunction < __TElementType, __KeyType >,                  /* NOLINT(bugprone-reserved-identifier) */
                    cds :: utility :: ComparisonFunction < __KeyType >,                                 /* NOLINT(bugprone-reserved-identifier) */
                    cds :: utility :: ComparisonFunction < __KeyType >,                                 /* NOLINT(bugprone-reserved-identifier) */
                    cds :: utility :: DestructorFunction < __TElementType >                             /* NOLINT(bugprone-reserved-identifier) */
            > friend class cds :: experimental :: __hidden :: __impl :: __RedBlackTree;                 /* NOLINT(bugprone-reserved-identifier) */

        private:
            using typename AbstractRedBlackTreeIterator < __ElementType > :: RBTreeNode;

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
        class RedBlackTreeForwardConstIterator : public AbstractRedBlackTreeConstIterator < __ElementType > {   /* NOLINT(bugprone-reserved-identifier) */
            template <
                    typename __TElementType,                                                            /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                                                                 /* NOLINT(bugprone-reserved-identifier) */
                    cds :: utility :: ExtractorFunction < __TElementType, __KeyType >,                  /* NOLINT(bugprone-reserved-identifier) */
                    cds :: utility :: ComparisonFunction < __KeyType >,                                 /* NOLINT(bugprone-reserved-identifier) */
                    cds :: utility :: ComparisonFunction < __KeyType >,                                 /* NOLINT(bugprone-reserved-identifier) */
                    cds :: utility :: DestructorFunction < __TElementType >                             /* NOLINT(bugprone-reserved-identifier) */
            > friend class cds :: experimental :: __hidden :: __impl :: __RedBlackTree;                 /* NOLINT(bugprone-reserved-identifier) */

        private:
            using typename AbstractRedBlackTreeConstIterator < __ElementType > :: RBTreeNode;

        public:
            constexpr RedBlackTreeForwardConstIterator () noexcept;

        public:
            constexpr RedBlackTreeForwardConstIterator (
                    RBTreeNode const * pRoot, RBTreeNode const * pCurrentNode
            ) noexcept;

        public:
            constexpr RedBlackTreeForwardConstIterator (
                    RedBlackTreeForwardConstIterator const & iterator
            ) noexcept;

        public:
            constexpr RedBlackTreeForwardConstIterator (
                    RedBlackTreeForwardConstIterator && iterator
            ) noexcept;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                    RedBlackTreeForwardConstIterator const & iterator
            ) noexcept -> RedBlackTreeForwardConstIterator &;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                    RedBlackTreeForwardConstIterator && iterator
            ) noexcept -> RedBlackTreeForwardConstIterator &;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> RedBlackTreeForwardConstIterator &;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ (int) noexcept -> RedBlackTreeForwardConstIterator;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- () noexcept -> RedBlackTreeForwardConstIterator &;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- (int) noexcept -> RedBlackTreeForwardConstIterator;

        };





        template < typename __ElementType >                                                             /* NOLINT(bugprone-reserved-identifier) */
        class RedBlackTreeBackwardIterator : public AbstractRedBlackTreeIterator < __ElementType > {
            template <
                    typename __TElementType,                                                            /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                                                                 /* NOLINT(bugprone-reserved-identifier) */
                    cds :: utility :: ExtractorFunction < __TElementType, __KeyType >,                  /* NOLINT(bugprone-reserved-identifier) */
                    cds :: utility :: ComparisonFunction < __KeyType >,                                 /* NOLINT(bugprone-reserved-identifier) */
                    cds :: utility :: ComparisonFunction < __KeyType >,                                 /* NOLINT(bugprone-reserved-identifier) */
                    cds :: utility :: DestructorFunction < __TElementType >                             /* NOLINT(bugprone-reserved-identifier) */
            > friend class cds :: experimental :: __hidden :: __impl :: __RedBlackTree;                 /* NOLINT(bugprone-reserved-identifier) */

        private:
            using typename AbstractRedBlackTreeIterator < __ElementType > :: RBTreeNode;

        public:
            constexpr RedBlackTreeBackwardIterator () noexcept;

        public:
            constexpr RedBlackTreeBackwardIterator (
                    RBTreeNode * pRoot,
                    RBTreeNode * pCurrentNode
            ) noexcept;

        public:
            constexpr RedBlackTreeBackwardIterator (
                    RedBlackTreeBackwardIterator const & iterator
            ) noexcept;

        public:
            constexpr RedBlackTreeBackwardIterator (
                    RedBlackTreeBackwardIterator && iterator
            ) noexcept;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                    RedBlackTreeBackwardIterator const & iterator
            ) noexcept -> RedBlackTreeBackwardIterator &;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                    RedBlackTreeBackwardIterator && iterator
            ) noexcept -> RedBlackTreeBackwardIterator &;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> RedBlackTreeBackwardIterator &;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ (int) noexcept -> RedBlackTreeBackwardIterator;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- () noexcept -> RedBlackTreeBackwardIterator &;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- (int) noexcept -> RedBlackTreeBackwardIterator;

        };


        template < typename __ElementType >                                                             /* NOLINT(bugprone-reserved-identifier) */
        class RedBlackTreeBackwardConstIterator : public AbstractRedBlackTreeConstIterator < __ElementType > {  /* NOLINT(bugprone-reserved-identifier) */
            template <
                    typename __TElementType,                                                            /* NOLINT(bugprone-reserved-identifier) */
                    typename __KeyType,                                                                 /* NOLINT(bugprone-reserved-identifier) */
                    cds :: utility :: ExtractorFunction < __TElementType, __KeyType >,                  /* NOLINT(bugprone-reserved-identifier) */
                    cds :: utility :: ComparisonFunction < __KeyType >,                                 /* NOLINT(bugprone-reserved-identifier) */
                    cds :: utility :: ComparisonFunction < __KeyType >,                                 /* NOLINT(bugprone-reserved-identifier) */
                    cds :: utility :: DestructorFunction < __TElementType >                             /* NOLINT(bugprone-reserved-identifier) */
            > friend class cds :: experimental :: __hidden :: __impl :: __RedBlackTree;                 /* NOLINT(bugprone-reserved-identifier) */

        private:
            using typename AbstractRedBlackTreeConstIterator < __ElementType > :: RBTreeNode;

        public:
            constexpr RedBlackTreeBackwardConstIterator () noexcept;

        public:
            constexpr RedBlackTreeBackwardConstIterator (
                    RBTreeNode const * pRoot, RBTreeNode const * pCurrentNode
            ) noexcept;

        public:
            constexpr RedBlackTreeBackwardConstIterator (
                    RedBlackTreeBackwardConstIterator const & iterator
            ) noexcept;

        public:
            constexpr RedBlackTreeBackwardConstIterator (
                    RedBlackTreeBackwardConstIterator && iterator
            ) noexcept;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                    RedBlackTreeBackwardConstIterator const & iterator
            ) noexcept -> RedBlackTreeBackwardConstIterator &;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator = (
                    RedBlackTreeBackwardConstIterator && iterator
            ) noexcept -> RedBlackTreeBackwardConstIterator &;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ () noexcept -> RedBlackTreeBackwardConstIterator &;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator ++ (int) noexcept -> RedBlackTreeBackwardConstIterator;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- () noexcept -> RedBlackTreeBackwardConstIterator &;

        public:
            __CDS_cpplang_NonConstConstexprMemberFunction auto operator -- (int) noexcept -> RedBlackTreeBackwardConstIterator;

        };
    }
}

#endif /* __CDS_EX_SHARED_RED_BLACK_TREE_ITERATOR_HPP__ */
