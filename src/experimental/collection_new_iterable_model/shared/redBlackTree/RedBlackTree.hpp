/*
 * Created by stefan on 22.07.2022.
 */

#ifndef __CDS_EX_SHARED_RED_BLACK_TREE_HPP__
#define __CDS_EX_SHARED_RED_BLACK_TREE_HPP__ /* NOLINT(bugprone-reserved-identifier) */

#include "RedBlackTreeUtils.hpp"

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(bugprone-reserved-identifier, modernize-concat-nested-namespaces) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template < typename __ElementType >                                                     /* NOLINT(bugprone-reserved-identifier) */
                using __RedBlackTreeNode = cds::__hidden::__impl::__RedBlackTreeNode < __ElementType >; /* NOLINT(bugprone-reserved-identifier) */


                template < typename __ElementType >                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                __CDS_OptimalInline auto __getLeftNode ( __RedBlackTreeNode < __ElementType > * pNode ) noexcept -> __RedBlackTreeNode < __ElementType > * {    /* NOLINT(bugprone-reserved-identifier) */
                    return pNode->_pLeft;
                }


                template < typename __ElementType >                                                                                                             /* NOLINT(bugprone-reserved-identifier) */
                __CDS_OptimalInline auto __getRightNode ( __RedBlackTreeNode < __ElementType > * pNode ) noexcept -> __RedBlackTreeNode < __ElementType > * {   /* NOLINT(bugprone-reserved-identifier) */
                    return pNode->_pRight;
                }


                template < typename __ElementType >                                                                                 /* NOLINT(bugprone-reserved-identifier) */
                __CDS_OptimalInline static auto __isLeftChild ( __RedBlackTreeNode < __ElementType > * pNode ) noexcept -> bool {   /* NOLINT(bugprone-reserved-identifier) */
                    return pNode == pNode->_pParent->_pLeft;
                }


                template < typename __ElementType >                                                                                 /* NOLINT(bugprone-reserved-identifier) */
                __CDS_OptimalInline static auto __isRightChild ( __RedBlackTreeNode < __ElementType > * pNode ) noexcept -> bool {  /* NOLINT(bugprone-reserved-identifier) */
                    return !__isLeftChild ( pNode );
                }


                template < typename __ElementType >                                                                         /* NOLINT(bugprone-reserved-identifier) */
                __CDS_OptimalInline static auto __isRed ( __RedBlackTreeNode < __ElementType > * pNode ) noexcept -> bool { /* NOLINT(bugprone-reserved-identifier) */
                    return pNode->_colour == __RedBlackTreeNode < __ElementType > :: RED;
                }


                template <
                        typename                                                            __ElementType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,              /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,         /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyLowerComparator,   /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyEqualsComparator,  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor        /* NOLINT(bugprone-reserved-identifier) */
                > class __RedBlackTree {                                                                            /* NOLINT(bugprone-reserved-identifier) */

                private:
                    using RBTreeNode                           =           __RedBlackTreeNode < __ElementType >;

                public:
                    using __rbt_AbstractIterator               =           AbstractTreeIterator < __ElementType >;                    /* NOLINT(bugprone-reserved-identifier) */

                public:
                    using __rbt_AbstractConstIterator          =           AbstractTreeConstIterator < __ElementType >;               /* NOLINT(bugprone-reserved-identifier) */

                public:
                    using __rbt_Iterator                       =           RedBlackTreeForwardIterator < __ElementType >;             /* NOLINT(bugprone-reserved-identifier) */

                public:
                    using __rbt_ConstIterator                  =           RedBlackTreeForwardConstIterator < __ElementType >;        /* NOLINT(bugprone-reserved-identifier) */

                public:
                    using __rbt_ReverseIterator                =           RedBlackTreeBackwardIterator < __ElementType >;            /* NOLINT(bugprone-reserved-identifier) */

                public:
                    using __rbt_ReverseConstIterator           =           RedBlackTreeBackwardConstIterator < __ElementType >;       /* NOLINT(bugprone-reserved-identifier) */

                public:
                    template < typename __ServerType >      /* NOLINT(bugprone-reserved-identifier) */
                    class __SetDispatcher;                  /* NOLINT(bugprone-reserved-identifier) */

                private:
                    Size            _size   { 0ULL };
                private:
                    RBTreeNode    * _pRoot  { nullptr };


                private:
                    __CDS_NoDiscard auto __rbt_allocateNode () const noexcept -> RBTreeNode *;          /* NOLINT(bugprone-reserved-identifier) */

                private:
                    auto __rbt_freeNode ( RBTreeNode * pRemoved ) noexcept -> void;         /* NOLINT(bugprone-reserved-identifier) */

                private:
                    auto __rbt_leftRotate ( RBTreeNode * pPivot ) noexcept -> void;         /* NOLINT(bugprone-reserved-identifier) */

                private:
                    auto __rbt_rightRotate ( RBTreeNode * pPivot ) noexcept -> void;            /* NOLINT(bugprone-reserved-identifier) */

                private:
                    auto __rbt_insertReBalance ( RBTreeNode * pPivot ) noexcept -> void;            /* NOLINT(bugprone-reserved-identifier) */

                private:
                    auto __rbt_transplant ( RBTreeNode * pRemoved, RBTreeNode * pMovedIn ) noexcept -> void;            /* NOLINT(bugprone-reserved-identifier) */

                private:
                    auto __rbt_deleteReBalance ( RBTreeNode * pPivot ) -> void;         /* NOLINT(bugprone-reserved-identifier) */

                private:
                    template <
                            bool rotationDecision,
                            typename __NodeType = RBTreeNode,                             /* NOLINT(bugprone-reserved-identifier) */
                            typename __ClassType = __RedBlackTree,                        /* NOLINT(bugprone-reserved-identifier) */
                            __NodeType * ( *__locateAuxiliary )( __NodeType * ) =         /* NOLINT(bugprone-reserved-identifier) */
                                    rotationDecision                            ?
                                            & __getRightNode < __ElementType >  :
                                            & __getLeftNode < __ElementType >,
                            bool ( *__ifScenario1 )( __NodeType * ) =                     /* NOLINT(bugprone-reserved-identifier) */
                                    rotationDecision                            ?
                                            &__isRightChild < __ElementType >   :
                                            &__isLeftChild < __ElementType >,
                            void ( __ClassType :: *  __rotateS1 )( __NodeType * ) =       /* NOLINT(bugprone-reserved-identifier) */
                                    rotationDecision                            ?
                                            & __ClassType :: __rbt_leftRotate   :
                                            & __ClassType :: __rbt_rightRotate,
                            void ( __ClassType :: *  __rotateS2 )( __NodeType * ) =       /* NOLINT(bugprone-reserved-identifier) */
                                    rotationDecision                            ?
                                            & __ClassType :: __rbt_rightRotate  :
                                            & __ClassType :: __rbt_leftRotate
                    > auto __identifyAndApplyRotationOnInsert (                           /* NOLINT(bugprone-reserved-identifier) */
                            RBTreeNode * pPivot
                    ) noexcept -> void;


                private:
                    template <
                            bool rotationDecision,
                            typename __NodeType = RBTreeNode,                                           /* NOLINT(bugprone-reserved-identifier) */
                            typename __ClassType = __RedBlackTree,                                      /* NOLINT(bugprone-reserved-identifier) */
                            __NodeType * ( *__locateAuxiliary )( __NodeType * ) =                       /* NOLINT(bugprone-reserved-identifier) */
                                    rotationDecision                            ?
                                            & __getRightNode < __ElementType >  :
                                            & __getLeftNode < __ElementType >,
                            __NodeType * ( *__locateReversedAuxiliary )( __NodeType * ) =               /* NOLINT(bugprone-reserved-identifier) */
                                    rotationDecision                            ?
                                            & __getRightNode < __ElementType >  :
                                            & __getLeftNode < __ElementType >,
                            bool ( *__ifScenario1 )( __NodeType * ) =                                   /* NOLINT(bugprone-reserved-identifier) */
                                    rotationDecision                            ?
                                            &__isRightChild < __ElementType >   :
                                            &__isLeftChild < __ElementType >,
                            void ( __ClassType :: *  __rotateS1 )( __NodeType * ) =                     /* NOLINT(bugprone-reserved-identifier) */
                                    rotationDecision                            ?
                                            & __ClassType :: __rbt_leftRotate   :
                                            & __ClassType :: __rbt_rightRotate,
                            void ( __ClassType :: *  __rotateS2 )( __NodeType * ) =                     /* NOLINT(bugprone-reserved-identifier) */
                                    rotationDecision                            ?
                                            & __ClassType :: __rbt_rightRotate  :
                                            & __ClassType :: __rbt_leftRotate
                    > auto __identifyAndApplyRotationOnDelete (                                         /* NOLINT(bugprone-reserved-identifier) */
                            RBTreeNode * pPivot
                    ) noexcept -> void;

                protected:
                    constexpr __RedBlackTree() noexcept = default;

                protected:
                    template <
                            cds :: utility :: CopyConstructorFunction < __ElementType > __copy /* NOLINT(bugprone-reserved-identifier) */
                    > __CDS_Implicit __RedBlackTree ( /* NOLINT(google-explicit-constructor) */
                            __RedBlackTree const & tree
                    ) noexcept;

                protected:
                    constexpr __RedBlackTree (
                            __RedBlackTree && tree
                    ) noexcept;

                protected:
                    __CDS_NoDiscard auto __rbt_empty () const -> bool; /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    __CDS_NoDiscard auto __rbt_get ( /* NOLINT(bugprone-reserved-identifier) */
                            __KeyType const & key,
                            bool * pIsNew
                    ) noexcept -> __ElementType *;

                protected:
                    __CDS_NoDiscard auto __rbt_get ( /* NOLINT(bugprone-reserved-identifier) */
                            __KeyType const & key
                    ) const noexcept -> __ElementType const *;

                private:
                    auto __rbt_removeAt ( /* NOLINT(bugprone-reserved-identifier) */
                            RBTreeNode * pToBeRemoved
                    ) noexcept -> bool;

                protected:
                    auto __rbt_remove ( /* NOLINT(bugprone-reserved-identifier) */
                            __ElementType const & key
                    ) noexcept -> bool;

                protected:
                    auto __rbt_removeIterator ( /* NOLINT(bugprone-reserved-identifier) */
                            AbstractTreeConstIterator < __ElementType > const & iterator
                    ) noexcept -> bool;

                protected:
                    auto __rbt_removeConstIteratorArray ( /* NOLINT(bugprone-reserved-identifier) */
                            AbstractTreeConstIterator < __ElementType > const * const * iteratorArray,
                            Size                                iteratorCount
                    ) noexcept -> Size;



                protected:
                    auto __rbt_clear () noexcept -> void; /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    __CDS_NoDiscard auto __rbt_size () const noexcept -> Size; /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    template <
                            cds :: utility :: CopyConstructorFunction < __ElementType > __copy  /* NOLINT(bugprone-reserved-identifier) */
                    > auto __rbt_copy (                                                         /* NOLINT(bugprone-reserved-identifier) */
                            __RedBlackTree const & tree
                    ) noexcept -> void;

                protected:
                    template <
                            cds :: utility :: CopyConstructorFunction < __ElementType > __copy  /* NOLINT(bugprone-reserved-identifier) */
                    > auto __rbt_copyCleared (                                                  /* NOLINT(bugprone-reserved-identifier) */
                            __RedBlackTree const & tree
                    ) noexcept -> void;

                protected:
                    auto __rbt_move (               /* NOLINT(bugprone-reserved-identifier) */
                            __RedBlackTree && tree
                    ) noexcept -> void;

                protected:
                    auto __rbt_moveCleared (        /* NOLINT(bugprone-reserved-identifier) */
                            __RedBlackTree && tree
                    ) noexcept -> void;

                protected:
                    auto __rbt_new (                /* NOLINT(bugprone-reserved-identifier) */
                            __ElementType const * pReferenceElement,
                            bool * pIsNew
                    ) noexcept -> __ElementType *;

                protected:
                    auto __rbt_findIteratorConst (  /* NOLINT(bugprone-reserved-identifier) */
                            __KeyType const & key
                    ) const noexcept -> __rbt_ConstIterator;

                protected:
                    __CDS_NoDiscard auto __rbt_begin () noexcept -> __rbt_Iterator;         /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    __CDS_NoDiscard auto __rbt_end () noexcept -> __rbt_Iterator;           /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    __CDS_NoDiscard auto __rbt_rbegin () noexcept -> __rbt_ReverseIterator; /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    __CDS_NoDiscard auto __rbt_rend () noexcept -> __rbt_ReverseIterator;   /* NOLINT(bugprone-reserved-identifier) */


                protected:
                    __CDS_NoDiscard auto __rbt_cbegin () const noexcept -> __rbt_ConstIterator;         /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    __CDS_NoDiscard auto __rbt_cend () const noexcept -> __rbt_ConstIterator;           /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    __CDS_NoDiscard auto __rbt_crbegin () const noexcept -> __rbt_ReverseConstIterator; /* NOLINT(bugprone-reserved-identifier) */

                protected:
                    __CDS_NoDiscard auto __rbt_crend () const noexcept -> __rbt_ReverseConstIterator;   /* NOLINT(bugprone-reserved-identifier) */

                };
            }
        }
    }
}

#endif /* __CDS_EX_SHARED_RED_BLACK_TREE_HPP__ */

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

#if defined ( __CDS_SHARED_TREE_SET_SERVER_DISPATCHER_HPP__ ) && ! defined ( __CDS_SHARED_TREE_SET_SET_SERVER_DISPATCHER_HPP__ ) && defined (__CDS_EX_SHARED_RED_BLACK_TREE_HPP__)
#define __CDS_SHARED_TREE_SET_SET_SERVER_DISPATCHER_HPP__ /* NOLINT(bugprone-reserved-identifier) */

            template <
                        typename                                                            __ElementType,             /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,                 /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,            /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyLowerComparator,      /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyEqualsComparator,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor           /* NOLINT(bugprone-reserved-identifier) */
            > template <
                    typename                                                                __ServerType               /* NOLINT(bugprone-reserved-identifier) */
            > class __RedBlackTree <
                    __ElementType,
                    __KeyType,
                    __keyExtractor,
                    __keyLowerComparator,
                    __keyEqualsComparator,
                    __nodeDestructor
            > :: __SetDispatcher :
                    public __TreeSetServerDispatcher <
                            __ServerType,
                            __RedBlackTree <
                                    __ElementType,
                                    __KeyType,
                                    __keyExtractor,
                                    __keyLowerComparator,
                                    __keyEqualsComparator,
                                    __nodeDestructor
                            >,
                            __ElementType,
                            AbstractTreeConstIterator < __ElementType >,
                            RedBlackTreeForwardConstIterator < __ElementType >,
                            RedBlackTreeBackwardConstIterator < __ElementType >,
                            & __RedBlackTree <
                                    __ElementType,
                                    __KeyType,
                                    __keyExtractor,
                                    __keyLowerComparator,
                                    __keyEqualsComparator,
                                    __nodeDestructor
                            > :: __rbt_cbegin,
                            & __RedBlackTree <
                                    __ElementType,
                                    __KeyType,
                                    __keyExtractor,
                                    __keyLowerComparator,
                                    __keyEqualsComparator,
                                    __nodeDestructor
                            > :: __rbt_cend,
                            & __RedBlackTree <
                                    __ElementType,
                                    __KeyType,
                                    __keyExtractor,
                                    __keyLowerComparator,
                                    __keyEqualsComparator,
                                    __nodeDestructor
                            > :: __rbt_crbegin,
                            & __RedBlackTree <
                                    __ElementType,
                                    __KeyType,
                                    __keyExtractor,
                                    __keyLowerComparator,
                                    __keyEqualsComparator,
                                    __nodeDestructor
                            > :: __rbt_crend,
                            & __RedBlackTree <
                                    __ElementType,
                                    __KeyType,
                                    __keyExtractor,
                                    __keyLowerComparator,
                                    __keyEqualsComparator,
                                    __nodeDestructor
                            > :: __rbt_new,
                            & __RedBlackTree <
                                    __ElementType,
                                    __KeyType,
                                    __keyExtractor,
                                    __keyLowerComparator,
                                    __keyEqualsComparator,
                                    __nodeDestructor
                            > :: __rbt_removeIterator,
                            & __RedBlackTree <
                                    __ElementType,
                                    __KeyType,
                                    __keyExtractor,
                                    __keyLowerComparator,
                                    __keyEqualsComparator,
                                    __nodeDestructor
                            > :: __rbt_removeConstIteratorArray,
                            & __RedBlackTree <
                                    __ElementType,
                                    __KeyType,
                                    __keyExtractor,
                                    __keyLowerComparator,
                                    __keyEqualsComparator,
                                    __nodeDestructor
                            > :: __rbt_findIteratorConst
                    > {};
#endif
            }
        }
    }
}