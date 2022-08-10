//
// Created by stefan on 22.07.2022.
//

#ifndef __CDS_RBTREE_HPP__
#define __CDS_RBTREE_HPP__

#include "./../../shared/Node.hpp"
#include "./../../shared/memory/PrimitiveAllocation.hpp"
#include "./../../std-types.h"

namespace cds {     // NOLINT(modernize-concat-nested-namespaces)
    namespace __hidden {
        namespace __impl {

            template < typename __ElementType >                                                                             // NOLINT(bugprone-reserved-identifier)
            inline auto __getLeftNode ( __RBTreeNode < __ElementType > * pNode ) -> __RBTreeNode < __ElementType > *;       // NOLINT(bugprone-reserved-identifier)

            template < typename __ElementType >                                                                             // NOLINT(bugprone-reserved-identifier)
            inline auto __getRightNode ( __RBTreeNode < __ElementType > * pNode ) -> __RBTreeNode < __ElementType > *;      // NOLINT(bugprone-reserved-identifier)

            template < typename __ElementType >                                                // NOLINT(bugprone-reserved-identifier)
            static auto __isLeftChild ( __RBTreeNode < __ElementType > * pNode ) -> bool;      // NOLINT(bugprone-reserved-identifier)

            template < typename __ElementType >                                                 // NOLINT(bugprone-reserved-identifier)
            static auto __isRightChild ( __RBTreeNode < __ElementType > * pNode ) -> bool;      // NOLINT(bugprone-reserved-identifier)

            template < typename __ElementType >                                         // NOLINT(bugprone-reserved-identifier)
            static auto __isRed ( __RBTreeNode < __ElementType > * pNode ) -> bool {    // NOLINT(bugprone-reserved-identifier)
                return pNode->_colour == __RBTreeNode < __ElementType > :: RED;
            }

            template <
                    typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                    typename __KeyType,                 // NOLINT(bugprone-reserved-identifier)
                    typename __KeyExtractor,            // NOLINT(bugprone-reserved-identifier)
                    typename __KeyLowerComparator,      // NOLINT(bugprone-reserved-identifier)
                    typename __KeyEqualsComparator,     // NOLINT(bugprone-reserved-identifier)
                    typename __ElementTypeDestruct      // NOLINT(bugprone-reserved-identifier)
            > class __RBTree {                     // NOLINT(bugprone-reserved-identifier)
                protected:
                    using ElementType                   =           __ElementType;

                protected:
                    using KeyType                       =           __KeyType;

                protected:
                    using KeyExtractor                  =           __KeyExtractor;

                protected:
                    using KeyLowerComparator            =           __KeyLowerComparator;

                protected:
                    using KeyEqualsComparator           =           __KeyEqualsComparator;

                protected:
                    using ElementTypeDestruct           =           __ElementTypeDestruct;


                private:
                    __KeyExtractor          _key;

                private:
                    __KeyEqualsComparator   _equals;

                private:
                    __ElementTypeDestruct   _destruct;

                private:
                    __KeyLowerComparator    _lower;

                private:
                    using RBTreeNode        =       __RBTreeNode < __ElementType >;


                private:
                    static __allocation :: __RawContainer < RBTreeNode > const nullNodeMemory;

                private:
                    constexpr static auto __endNode () noexcept -> RBTreeNode * {        // NOLINT(bugprone-reserved-identifier)
                        return & nullNodeMemory.data();
                    }

                private:
                    Size _size { 0ULL };
                private:
                    RBTreeNode * _root { nullptr };


                private:
                    auto __rbt_allocateNode () -> RBTreeNode *;         // NOLINT(bugprone-reserved-identifier)

                private:
                    auto __rbt_freeNode ( RBTreeNode * ) -> void;                     // NOLINT(bugprone-reserved-identifier)

                private:
                    auto __rbt_leftRotate ( RBTreeNode * ) -> void;                          // NOLINT(bugprone-reserved-identifier)

                private:
                    auto __rbt_rightRotate ( RBTreeNode * ) -> void;                         // NOLINT(bugprone-reserved-identifier)

                private:
                    auto __rbt_insertReBalance ( RBTreeNode * ) -> void;                     // NOLINT(bugprone-reserved-identifier)

                private:
                    auto __rbt_transplant ( RBTreeNode *, RBTreeNode * ) -> void;            // NOLINT(bugprone-reserved-identifier)

                private:
                    auto __rbt_deleteReBalance ( RBTreeNode * ) -> void;                     // NOLINT(bugprone-reserved-identifier)

                private:
                    template <
                            bool rotationDecision,
                            typename __NodeType = RBTreeNode,                             // NOLINT(bugprone-reserved-identifier)
                            typename __ClassType = __RBTree,                              // NOLINT(bugprone-reserved-identifier)
                            __NodeType * ( *__locateAuxiliary )( __NodeType * ) =         // NOLINT(bugprone-reserved-identifier)
                            rotationDecision                    ?
                            & __getRightNode < __ElementType >    :
                            & __getLeftNode < __ElementType >,
                    bool ( *__ifS1 )( __NodeType * ) =                            // NOLINT(bugprone-reserved-identifier)
                            rotationDecision                    ?
                            &__isRightChild < __ElementType >     :
                            &__isLeftChild < __ElementType >,
                    void ( __ClassType :: *  __rotateS1 )( __NodeType * ) =       // NOLINT(bugprone-reserved-identifier)
                            rotationDecision                ?
                            & __ClassType :: __rbt_leftRotate      :
                            & __ClassType :: __rbt_rightRotate,
                    void ( __ClassType :: *  __rotateS2 )( __NodeType * ) =       // NOLINT(bugprone-reserved-identifier)
                    rotationDecision                ?
                    & __ClassType :: __rbt_rightRotate     :
                    & __ClassType :: __rbt_leftRotate
                    > auto __identifyAndApplyRotationOnInsert (                           // NOLINT(bugprone-reserved-identifier)
                            RBTreeNode * pPivot
                    ) noexcept -> void;


                private:
                    template <
                            bool rotationDecision,
                            typename __NodeType = RBTreeNode,                                     // NOLINT(bugprone-reserved-identifier)
                            typename __ClassType = __RBTree,                                      // NOLINT(bugprone-reserved-identifier)
                            __NodeType * ( *__locateAuxiliary )( __NodeType * ) =                 // NOLINT(bugprone-reserved-identifier)
                                rotationDecision                    ?
                                & __getRightNode < __ElementType >    :
                                & __getLeftNode < __ElementType >,                                // NOLINT(bugprone-reserved-identifier)
                            __NodeType * ( *__locateReversedAuxiliary )( __NodeType * ) =         // NOLINT(bugprone-reserved-identifier)
                                rotationDecision                    ?
                                & __getRightNode < __ElementType >    :
                                & __getLeftNode < __ElementType >,
                            bool ( *__ifS1 )( __NodeType * ) =                                    // NOLINT(bugprone-reserved-identifier)
                                rotationDecision                    ?
                                &__isRightChild < __ElementType >     :
                                &__isLeftChild < __ElementType >,
                            void ( __ClassType :: *  __rotateS1 )( __NodeType * ) =               // NOLINT(bugprone-reserved-identifier)
                                rotationDecision                ?
                                & __ClassType :: __rbt_leftRotate      :
                                & __ClassType :: __rbt_rightRotate,
                            void ( __ClassType :: *  __rotateS2 )( __NodeType * ) =               // NOLINT(bugprone-reserved-identifier)
                                rotationDecision                ?
                                & __ClassType :: __rbt_rightRotate     :
                                & __ClassType :: __rbt_leftRotate
                    > auto __identifyAndApplyRotationOnDelete (    // NOLINT(bugprone-reserved-identifier)
                            RBTreeNode * pPivot
                    ) noexcept -> void;

                public:
                    __RBTree() = default;

                public:
                    constexpr auto __rbt_empty () const -> bool;                            // NOLINT(bugprone-reserved-identifier)

                public:
                    auto __rbt_get ( __KeyType const &, bool * ) -> __ElementType &;        // NOLINT(bugprone-reserved-identifier)

                public:
                    auto __rbt_get ( __KeyType const & ) const -> __ElementType const &;    // NOLINT(bugprone-reserved-identifier)

                public:
                    auto __rbt_remove ( __ElementType const & ) -> void;                    // NOLINT(bugprone-reserved-identifier)

                public:
                    auto __rbt_clear () -> void;                                            // NOLINT(bugprone-reserved-identifier)

                public:
                    auto __rbt_size () -> Size;                                             // NOLINT(bugprone-reserved-identifier)
            };
        }
    }
}

#include "RBTree/impl/RBTree.hpp"

#endif //__CDS_RBTREE_HPP__
