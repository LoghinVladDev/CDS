//
// Created by stefan on 16.08.2022.
//

#ifndef __CDS_EX_SHARED_RED_BLACK_TREE_ITERATOR_HPP__
#define __CDS_EX_SHARED_RED_BLACK_TREE_ITERATOR_HPP__

namespace cds {                 // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {


        namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl {  // NOLINT(bugprone-reserved-identifier)
                template <
                        typename __TElementType,                                                                // NOLINT(bugprone-reserved-identifier)
                        typename __KeyType,                                                                     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ExtractorFunction < __TElementType, __KeyType > __keyExtractor,       // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __TElementType > __keyLowerComparator,           // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __TElementType > __keyEqualsComparator,          // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: DestructorFunction < __TElementType > __nodeDestructor                // NOLINT(bugprone-reserved-identifier)
                > class __RedBlackTree;                                                                         // NOLINT(bugprone-reserved-identifier)
            }
        }

        template < typename __ElementType >     // NOLINT(bugprone-reserved-identifier)
        class AbstractTreeIterator : public meta :: BidirectionalIterator {
            template <
                    typename __TElementType,                                                                // NOLINT(bugprone-reserved-identifier)
                    typename __KeyType,                                                                     // NOLINT(bugprone-reserved-identifier)
                    cds :: utility :: ExtractorFunction < __TElementType, __KeyType > __keyExtractor,       // NOLINT(bugprone-reserved-identifier)
                    cds :: utility :: ComparisonFunction < __TElementType > __keyLowerComparator,           // NOLINT(bugprone-reserved-identifier)
                    cds :: utility :: ComparisonFunction < __TElementType > __keyEqualsComparator,          // NOLINT(bugprone-reserved-identifier)
                    cds :: utility :: DestructorFunction < __TElementType > __nodeDestructor                // NOLINT(bugprone-reserved-identifier)
            > friend class cds :: experimental :: __hidden :: __impl :: __RedBlackTree;                     // NOLINT(bugprone-reserved-identifier)


            protected:
                using RBTreeNode = cds :: __hidden :: __impl :: __RedBlackTreeNode < __ElementType >;

            private:
                RBTreeNode *         _pRoot          { 0ULL };

            private:
                RBTreeNode *         _pCurrentNode  { nullptr };

            protected:
                AbstractTreeIterator() noexcept;

            protected:
                AbstractTreeIterator(
                        RBTreeNode * pRoot,
                        RBTreeNode * pCurrentNode
                ) noexcept;

            protected:
                AbstractTreeIterator(
                        AbstractTreeIterator const & iterator
                ) noexcept;

            protected:
                AbstractTreeIterator(
                        AbstractTreeIterator && iterator
                ) noexcept;

            protected:

            public:
                auto operator * () const noexcept -> __ElementType &;

            public:
                auto operator -> () const noexcept -> __ElementType *;

            public:
                auto operator == (
                        AbstractTreeIterator const & iterator
                ) const noexcept -> bool;

            public:
                auto operator != (
                        AbstractTreeIterator const & iterator
                ) const noexcept -> bool;

            public:
                __CDS_Explicit operator bool () const noexcept;

            protected:
                auto successor () noexcept -> AbstractTreeIterator &;

            protected:
                auto predecessor () noexcept -> AbstractTreeIterator &;
        };


        template < typename __ElementType >     // NOLINT(bugprone-reserved-identifier)
        class AbstractTreeConstIterator : public meta :: BidirectionalIterator {
            template <
                    typename __TElementType,                                                                // NOLINT(bugprone-reserved-identifier)
                    typename __KeyType,                                                                     // NOLINT(bugprone-reserved-identifier)
                    cds :: utility :: ExtractorFunction < __TElementType, __KeyType > __keyExtractor,       // NOLINT(bugprone-reserved-identifier)
                    cds :: utility :: ComparisonFunction < __TElementType > __keyLowerComparator,           // NOLINT(bugprone-reserved-identifier)
                    cds :: utility :: ComparisonFunction < __TElementType > __keyEqualsComparator,          // NOLINT(bugprone-reserved-identifier)
                    cds :: utility :: DestructorFunction < __TElementType > __nodeDestructor                // NOLINT(bugprone-reserved-identifier)
            > friend class cds :: experimental :: __hidden :: __impl :: __RedBlackTree;                     // NOLINT(bugprone-reserved-identifier)


        protected:
            using RBTreeNode = cds :: __hidden :: __impl :: __RedBlackTreeNode < __ElementType >;

        private:
            RBTreeNode const *         _pRoot          { 0ULL };

        private:
            RBTreeNode const *         _pCurrentNode  { nullptr };

        protected:
            AbstractTreeConstIterator() noexcept;

        protected:
            AbstractTreeConstIterator(
                    RBTreeNode const * pRoot,
                    RBTreeNode const * pCurrentNode
            ) noexcept;

        protected:
            AbstractTreeConstIterator(
                    AbstractTreeConstIterator const & iterator
            ) noexcept;

        protected:
            AbstractTreeConstIterator(
                    AbstractTreeConstIterator && iterator
            ) noexcept;

        protected:

        public:
            auto operator * () const noexcept -> __ElementType const &;

        public:
            auto operator -> () const noexcept -> __ElementType const *;

        public:
            auto operator == (
                    AbstractTreeConstIterator const & iterator
            ) const noexcept -> bool;

        public:
            auto operator != (
                    AbstractTreeConstIterator const & iterator
            ) const noexcept -> bool;

        public:
            __CDS_Explicit operator bool () const noexcept;

        protected:
            auto successor () noexcept -> AbstractTreeConstIterator &;

        protected:
            auto predecessor () noexcept -> AbstractTreeConstIterator &;
        };
        

        template < typename __ElementType >                                                             // NOLINT(bugprone-reserved-identifier)
        class RedBlackTreeForwardIterator : public AbstractTreeIterator < __ElementType > {
            template <
                    typename __TElementType,                                                            // NOLINT(bugprone-reserved-identifier)
                    typename __KeyType,                                                                 // NOLINT(bugprone-reserved-identifier)
                    cds :: utility :: ExtractorFunction < __TElementType, __KeyType > __keyExtractor,   // NOLINT(bugprone-reserved-identifier)
                    cds :: utility :: ComparisonFunction < __TElementType > __keyLowerComparator,       // NOLINT(bugprone-reserved-identifier)
                    cds :: utility :: ComparisonFunction < __TElementType > __keyEqualsComparator,      // NOLINT(bugprone-reserved-identifier)
                    cds :: utility :: DestructorFunction < __TElementType > __nodeDestructor            // NOLINT(bugprone-reserved-identifier)
            > friend class cds :: experimental :: __hidden :: __impl :: __RedBlackTree;                 // NOLINT(bugprone-reserved-identifier)

            private:
                using typename AbstractTreeIterator < __ElementType > :: RBTreeNode;

            public:
                RedBlackTreeForwardIterator () noexcept;

            public:
                RedBlackTreeForwardIterator (
                        RBTreeNode * pRoot,
                        RBTreeNode * pCurrentNode
                ) noexcept;

            public:
                RedBlackTreeForwardIterator (
                        RedBlackTreeForwardIterator const & iterator
                ) noexcept;

            public:
                RedBlackTreeForwardIterator (
                        RedBlackTreeForwardIterator && iterator
                ) noexcept;

            public:
                auto operator = (
                        RedBlackTreeForwardIterator const & iterator
                ) noexcept -> RedBlackTreeForwardIterator &;

            public:
                auto operator = (
                        RedBlackTreeForwardIterator && iterator
                ) noexcept -> RedBlackTreeForwardIterator &;

            public:
                auto operator ++ () noexcept -> RedBlackTreeForwardIterator &;

            public:
                auto operator ++ (int) noexcept -> RedBlackTreeForwardIterator;

            public:
                auto operator -- () noexcept -> RedBlackTreeForwardIterator &;

            public:
                auto operator -- (int) noexcept -> RedBlackTreeForwardIterator;

        };


        template < typename __ElementType >                                                       // NOLINT(bugprone-reserved-identifier)
        class RedBlackTreeForwardConstIterator : public AbstractTreeConstIterator < __ElementType > {    // NOLINT(bugprone-reserved-identifier)
            template <
                    typename __TElementType,                                                            // NOLINT(bugprone-reserved-identifier)
                    typename __KeyType,                                                                 // NOLINT(bugprone-reserved-identifier)
                    cds :: utility :: ExtractorFunction < __TElementType, __KeyType > __keyExtractor,   // NOLINT(bugprone-reserved-identifier)
                    cds :: utility :: ComparisonFunction < __TElementType > __keyLowerComparator,       // NOLINT(bugprone-reserved-identifier)
                    cds :: utility :: ComparisonFunction < __TElementType > __keyEqualsComparator,      // NOLINT(bugprone-reserved-identifier)
                    cds :: utility :: DestructorFunction < __TElementType > __nodeDestructor            // NOLINT(bugprone-reserved-identifier)
            > friend class cds :: experimental :: __hidden :: __impl :: __RedBlackTree;                 // NOLINT(bugprone-reserved-identifier)

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





        template < typename __ElementType >                                                             // NOLINT(bugprone-reserved-identifier)
        class RedBlackTreeBackwardIterator : public AbstractTreeIterator < __ElementType > {
            template <
                    typename __TElementType,                                                            // NOLINT(bugprone-reserved-identifier)
                    typename __KeyType,                                                                 // NOLINT(bugprone-reserved-identifier)
                    cds :: utility :: ExtractorFunction < __TElementType, __KeyType > __keyExtractor,   // NOLINT(bugprone-reserved-identifier)
                    cds :: utility :: ComparisonFunction < __TElementType > __keyLowerComparator,       // NOLINT(bugprone-reserved-identifier)
                    cds :: utility :: ComparisonFunction < __TElementType > __keyEqualsComparator,      // NOLINT(bugprone-reserved-identifier)
                    cds :: utility :: DestructorFunction < __TElementType > __nodeDestructor            // NOLINT(bugprone-reserved-identifier)
            > friend class cds :: experimental :: __hidden :: __impl :: __RedBlackTree;                 // NOLINT(bugprone-reserved-identifier)

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


        template < typename __ElementType >                                                       // NOLINT(bugprone-reserved-identifier)
        class RedBlackTreeBackwardConstIterator : public AbstractTreeConstIterator < __ElementType > {    // NOLINT(bugprone-reserved-identifier)
            template <
                    typename __TElementType,                                                            // NOLINT(bugprone-reserved-identifier)
                    typename __KeyType,                                                                 // NOLINT(bugprone-reserved-identifier)
                    cds :: utility :: ExtractorFunction < __TElementType, __KeyType > __keyExtractor,   // NOLINT(bugprone-reserved-identifier)
                    cds :: utility :: ComparisonFunction < __TElementType > __keyLowerComparator,       // NOLINT(bugprone-reserved-identifier)
                    cds :: utility :: ComparisonFunction < __TElementType > __keyEqualsComparator,      // NOLINT(bugprone-reserved-identifier)
                    cds :: utility :: DestructorFunction < __TElementType > __nodeDestructor            // NOLINT(bugprone-reserved-identifier)
            > friend class cds :: experimental :: __hidden :: __impl :: __RedBlackTree;                 // NOLINT(bugprone-reserved-identifier)

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

#endif //__CDS_EX_SHARED_RED_BLACK_TREE_ITERATOR_HPP__
