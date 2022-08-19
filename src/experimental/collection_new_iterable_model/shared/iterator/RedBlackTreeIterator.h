//
// Created by stefan on 16.08.2022.
//

#ifndef __CDS_EX_SHARED_RED_BLACK_TREE_ITERATOR_HPP__
#define __CDS_EX_SHARED_RED_BLACK_TREE_ITERATOR_HPP__

#include "IteratorModel.hpp"
#include <CDS/Comparator>
#include <CDS/Extractor>
#include <CDS/Destructor>
#include <CDS/Compiler>
#include <CDS/CopyConstructor>
#include <CDS/Options>
#include "../redBlackTree/RedBlackTree.hpp"
#include "../../../../shared/Node.hpp"
namespace cds {
    namespace experimental {


        template < typename __ElementType >
        class RedBlackTreeIterator : public meta :: BidirectionalIterator {
            template <
                    typename __TElementType,
                    typename __KeyType,
                    cds :: utility :: ExtractorFunction < __TElementType, __KeyType > __keyExtractor,
                    cds :: utility :: ComparisonFunction < __TElementType > __keyLowerComparator,
                    cds :: utility :: ComparisonFunction < __TElementType > __keyEqualsComparator,
                    cds :: utility :: DestructorFunction < __TElementType > __nodeDestructor
            > friend class cds :: experimental :: __hidden :: __impl :: __RedBlackTree;

            private:
                using RBTreeNode = cds :: __hidden :: __impl :: __RedBlackTreeNode < __ElementType >;



            private:
                RBTreeNode *         _pRoot          { 0ULL };

            private:
                RBTreeNode *         _pCurrentNode  { nullptr };

            public:
                RedBlackTreeIterator () noexcept;

            public:
                RedBlackTreeIterator (
                        RBTreeNode * pRoot, RBTreeNode * pCurrentNode
                ) noexcept;

            public:
                RedBlackTreeIterator (
                        RedBlackTreeIterator const & iterator
                ) noexcept;

            public:
                RedBlackTreeIterator (
                        RedBlackTreeIterator && iterator
                ) noexcept;

            public:
                auto operator = (
                        RedBlackTreeIterator const & iterator
                ) noexcept -> RedBlackTreeIterator &;

            public:
                auto operator = (
                        RedBlackTreeIterator && iterator
                ) noexcept -> RedBlackTreeIterator &;

            public:
                auto operator ++ () noexcept -> RedBlackTreeIterator &;

            public:
                auto operator ++ (int) noexcept -> RedBlackTreeIterator;

            public:
                auto operator -- () noexcept -> RedBlackTreeIterator &;

            public:
                auto operator -- (int) noexcept -> RedBlackTreeIterator;

            public:
                auto operator * () const noexcept -> __ElementType &;

            public:
                auto operator -> () const noexcept -> __ElementType *;

            public:
                auto operator == (
                        RedBlackTreeIterator const & iterator
                ) const noexcept -> bool;

            public:
                auto operator != (
                        RedBlackTreeIterator const & iterator
                ) const noexcept -> bool;

            public:
                operator bool () const noexcept;

        };


        template < typename __ElementType >
        class RedBlackTreeConstIterator : public meta :: BidirectionalIterator {
            template <
                    typename __TElementType,
                    typename __KeyType,
                    cds :: utility :: ExtractorFunction < __TElementType, __KeyType > __keyExtractor,
                    cds :: utility :: ComparisonFunction < __TElementType > __keyLowerComparator,
                    cds :: utility :: ComparisonFunction < __TElementType > __keyEqualsComparator,
                    cds :: utility :: DestructorFunction < __TElementType > __nodeDestructor
            > friend class cds :: experimental :: __hidden :: __impl :: __RedBlackTree;

        private:
            using RBTreeNode = cds :: __hidden :: __impl :: __RedBlackTreeNode < __ElementType >;

        private:
            RBTreeNode const *         _pRoot          { 0ULL };

        private:
            RBTreeNode const *         _pCurrentNode  { nullptr };

        public:
            RedBlackTreeConstIterator () noexcept;

        public:
            RedBlackTreeConstIterator (
                    RBTreeNode const * pRoot, RBTreeNode const * pCurrentNode
            ) noexcept;

        public:
            RedBlackTreeConstIterator (
                    RedBlackTreeConstIterator const & iterator
            ) noexcept;

        public:
            RedBlackTreeConstIterator (
                    RedBlackTreeConstIterator && iterator
            ) noexcept;

        public:
            auto operator = (
                    RedBlackTreeConstIterator const & iterator
            ) noexcept -> RedBlackTreeConstIterator &;

        public:
            auto operator = (
                    RedBlackTreeConstIterator && iterator
            ) noexcept -> RedBlackTreeConstIterator &;

        public:
            auto operator ++ () noexcept -> RedBlackTreeConstIterator &;

        public:
            auto operator ++ (int) noexcept -> RedBlackTreeConstIterator;

        public:
            auto operator -- () noexcept -> RedBlackTreeConstIterator &;

        public:
            auto operator -- (int) noexcept -> RedBlackTreeConstIterator;

        public:
            auto operator * () const noexcept -> __ElementType const &;

        public:
            auto operator -> () const noexcept -> __ElementType const *;

        public:
            auto operator == (
                    RedBlackTreeConstIterator const & iterator
            ) const noexcept -> bool;

        public:
            auto operator != (
                    RedBlackTreeConstIterator const & iterator
            ) const noexcept -> bool;

        public:
            operator bool () const noexcept;

        };
    }
}

#endif //__CDS_EX_SHARED_RED_BLACK_TREE_ITERATOR_HPP__
