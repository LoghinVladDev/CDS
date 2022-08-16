//
// Created by stefan on 22.07.2022.
//

#ifndef __CDS_EX_SHARED_RED_BLACK_TREE_HPP__
#define __CDS_EX_SHARED_RED_BLACK_TREE_HPP__


/// TODO : do not include these here, include in class using RedBlackTree
#include "../../../../shared/Node.hpp"
#include "../../../../shared/memory/PrimitiveAllocation.hpp"
#include "../../../../std-types.h"
#include <CDS/Comparator>
#include <CDS/Extractor>
#include <CDS/Destructor>
#include <CDS/Compiler>

namespace cds {                     // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {
        namespace __hidden {        // NOLINT(bugprone-reserved-identifier)
            namespace __impl {      // NOLINT(bugprone-reserved-identifier)

                /// TODO : noexcepts
                /// TODO : function for const as well ? tbd at constexpr
                /// TODO : no inlines at declaration, apply inline at definition
                /// TODO : __CDS_OptimalInline - always there, __CDS_OptionalInline - only heavy optimization ( no -OS - optimize size )
                template < typename __ElementType >                                             // NOLINT(bugprone-reserved-identifier)
                using __RedBlackTreeNode = cds::__hidden::__impl::__RedBlackTreeNode < __ElementType >;     // NOLINT(bugprone-reserved-identifier)

                template < typename __ElementType >                                                                             // NOLINT(bugprone-reserved-identifier)
                inline auto __getLeftNode ( __RedBlackTreeNode < __ElementType > * pNode ) noexcept -> __RedBlackTreeNode < __ElementType > *;       // NOLINT(bugprone-reserved-identifier)

                template < typename __ElementType >                                                                             // NOLINT(bugprone-reserved-identifier)
                inline auto __getRightNode ( __RedBlackTreeNode < __ElementType > * pNode ) noexcept -> __RedBlackTreeNode < __ElementType > *;      // NOLINT(bugprone-reserved-identifier)

                template < typename __ElementType >                                                // NOLINT(bugprone-reserved-identifier)
                static auto __isLeftChild ( __RedBlackTreeNode < __ElementType > * pNode ) noexcept -> bool;      // NOLINT(bugprone-reserved-identifier)

                template < typename __ElementType >                                                 // NOLINT(bugprone-reserved-identifier)
                static auto __isRightChild ( __RedBlackTreeNode < __ElementType > * pNode ) noexcept -> bool;      // NOLINT(bugprone-reserved-identifier)

                template < typename __ElementType >                                         // NOLINT(bugprone-reserved-identifier)
                static auto __isRed ( __RedBlackTreeNode < __ElementType > * pNode ) noexcept -> bool {    // NOLINT(bugprone-reserved-identifier)
                    return pNode->_colour == __RedBlackTreeNode < __ElementType > :: RED;
                }

                /// TODO : Perhaps __RedBlackTree ?
                /// TODO : Functions that are always the same ( __KeyEqualsComparator, __KeyExtractor ) can be made as direct functions instead of classes
                template <
                        typename                                                            __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyType,                 // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,            // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyLowerComparator,      // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyEqualsComparator,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor           // NOLINT(bugprone-reserved-identifier)
                > class __RedBlackTree {                     // NOLINT(bugprone-reserved-identifier)
                protected:
                    using ElementType                   =           __ElementType;

                protected:
                    using KeyType                       =           __KeyType;

                private:
                    using RBTreeNode                    =           __RedBlackTreeNode < __ElementType >;


                private:
                    static cds :: __hidden :: __impl :: __allocation :: __RawContainer < RBTreeNode > const nullNodeMemory;

                private:
                    constexpr static auto __endNode () noexcept -> RBTreeNode * {        // NOLINT(bugprone-reserved-identifier)
                        return & nullNodeMemory.data();
                    }

                private:
                    Size            _size { 0ULL };
                private:
                    RBTreeNode    * _root { nullptr };


                private:
                    auto __rbt_allocateNode () noexcept -> RBTreeNode *;         // NOLINT(bugprone-reserved-identifier)

                private:
                    /// TODO : parameter names
                    auto __rbt_freeNode ( RBTreeNode * pRemoved ) noexcept -> void;                     // NOLINT(bugprone-reserved-identifier)

                private:
                    auto __rbt_leftRotate ( RBTreeNode * pPivot ) noexcept -> void;                          // NOLINT(bugprone-reserved-identifier)

                private:
                    auto __rbt_rightRotate ( RBTreeNode * pPivot ) noexcept -> void;                         // NOLINT(bugprone-reserved-identifier)

                private:
                    auto __rbt_insertReBalance ( RBTreeNode * pPivot ) noexcept -> void;                     // NOLINT(bugprone-reserved-identifier)

                private:
                    auto __rbt_transplant ( RBTreeNode * pRemoved, RBTreeNode * pMovedIn ) noexcept -> void;            // NOLINT(bugprone-reserved-identifier)

                private:
                    auto __rbt_deleteReBalance ( RBTreeNode * pPivot ) -> void;                     // NOLINT(bugprone-reserved-identifier)

                private:
                    template <
                            bool rotationDecision,
                            typename __NodeType = RBTreeNode,                             // NOLINT(bugprone-reserved-identifier)
                            typename __ClassType = __RedBlackTree,                              // NOLINT(bugprone-reserved-identifier)
                            __NodeType * ( *__locateAuxiliary )( __NodeType * ) =         // NOLINT(bugprone-reserved-identifier)
                            rotationDecision                        ?
                            & __getRightNode < __ElementType >      :
                            & __getLeftNode < __ElementType >,
                            bool ( *__ifScenario1 )( __NodeType * ) =                            // NOLINT(bugprone-reserved-identifier)
                            rotationDecision                        ?
                            &__isRightChild < __ElementType >       :
                            &__isLeftChild < __ElementType >,
                            void ( __ClassType :: *  __rotateS1 )( __NodeType * ) =       // NOLINT(bugprone-reserved-identifier)
                            rotationDecision                        ?
                            & __ClassType :: __rbt_leftRotate       :
                            & __ClassType :: __rbt_rightRotate,
                            void ( __ClassType :: *  __rotateS2 )( __NodeType * ) =       // NOLINT(bugprone-reserved-identifier)
                            rotationDecision                        ?
                            & __ClassType :: __rbt_rightRotate      :
                            & __ClassType :: __rbt_leftRotate
                    > auto __identifyAndApplyRotationOnInsert (                           // NOLINT(bugprone-reserved-identifier)
                            RBTreeNode * pPivot
                    ) noexcept -> void;


                private:
                    template <
                            bool rotationDecision,
                            typename __NodeType = RBTreeNode,                                     // NOLINT(bugprone-reserved-identifier)
                            typename __ClassType = __RedBlackTree,                                      // NOLINT(bugprone-reserved-identifier)
                            __NodeType * ( *__locateAuxiliary )( __NodeType * ) =                 // NOLINT(bugprone-reserved-identifier)
                            rotationDecision                      ?
                            & __getRightNode < __ElementType >    :
                            & __getLeftNode < __ElementType >,                                // NOLINT(bugprone-reserved-identifier)
                            __NodeType * ( *__locateReversedAuxiliary )( __NodeType * ) =         // NOLINT(bugprone-reserved-identifier)
                            rotationDecision                      ?
                            & __getRightNode < __ElementType >    :
                            & __getLeftNode < __ElementType >,
                            bool ( *__ifScenario1 )( __NodeType * ) =                                    // NOLINT(bugprone-reserved-identifier)
                            rotationDecision                      ?
                            &__isRightChild < __ElementType >     :
                            &__isLeftChild < __ElementType >,
                            void ( __ClassType :: *  __rotateS1 )( __NodeType * ) =               // NOLINT(bugprone-reserved-identifier)
                            rotationDecision                      ?
                            & __ClassType :: __rbt_leftRotate     :
                            & __ClassType :: __rbt_rightRotate,
                            void ( __ClassType :: *  __rotateS2 )( __NodeType * ) =               // NOLINT(bugprone-reserved-identifier)
                            rotationDecision                      ?
                            & __ClassType :: __rbt_rightRotate    :
                            & __ClassType :: __rbt_leftRotate
                    > auto __identifyAndApplyRotationOnDelete (    // NOLINT(bugprone-reserved-identifier)
                            RBTreeNode * pPivot
                    ) noexcept -> void;

                    /// TODO : protected
                public:
                    constexpr __RedBlackTree() noexcept = default;

                public:
                    __CDS_NoDiscard auto __rbt_empty () const -> bool;                                                           // NOLINT(bugprone-reserved-identifier)

                public:
                    auto __rbt_get ( __KeyType const & key, bool * pIsNew ) noexcept -> __ElementType &;         // NOLINT(bugprone-reserved-identifier)

                public:
                    auto __rbt_get ( __KeyType const & key ) const noexcept -> __ElementType const &;                         // NOLINT(bugprone-reserved-identifier)

                public:
                    auto __rbt_remove ( __ElementType const & key ) noexcept -> void;                                         // NOLINT(bugprone-reserved-identifier)

                public:
                    auto __rbt_clear () noexcept -> void;                                                                 // NOLINT(bugprone-reserved-identifier)

                public:
                    __CDS_NoDiscard auto __rbt_size () const noexcept -> Size;                                                                  // NOLINT(bugprone-reserved-identifier)
                };
            }
        }
    }
}

#include "impl/RedBlackTree.hpp"

#endif // __CDS_EX_SHARED_RED_BLACK_TREE_HPP__