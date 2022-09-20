/*
 * Created by stefan on 02.07.2022.
 */

#ifndef __CDS_EX_SHARED_RED_BLACK_TREE_IMPL_HPP__
#define __CDS_EX_SHARED_RED_BLACK_TREE_IMPL_HPP__ /* NOLINT(bugprone-reserved-identifier) */

namespace cds {                 /* NOLINT(modernize-concat-nested-namespaces) */
    namespace experimental {    /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __hidden {    /* NOLINT(bugprone-reserved-identifier, modernize-concat-nested-namespaces) */
            namespace __impl {  /* NOLINT(bugprone-reserved-identifier) */

                template < typename __ElementType >
                cds :: __hidden :: __impl :: __allocation :: __RawContainer <
                        cds :: __hidden :: __impl :: __RedBlackTreeNode < __ElementType >
                > __RedBlackTreeEndNodeContainer < __ElementType > :: __endNode;


                template <
                        typename                                                            __ElementType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,              /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,         /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyLowerComparator,   /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyEqualsComparator,  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor        /* NOLINT(bugprone-reserved-identifier) */
                > constexpr auto __RedBlackTree <
                        __ElementType,
                        __KeyType,
                        __keyExtractor,
                        __keyLowerComparator,
                        __keyEqualsComparator,
                        __nodeDestructor
                > :: __rbt_isLeftChild (
                    __rbt_NodeType const * pNode
                ) const noexcept -> bool {

                    return pNode == pNode->_pParent->_pLeft;
                }


                template <
                        typename                                                            __ElementType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,              /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,         /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyLowerComparator,   /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyEqualsComparator,  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor        /* NOLINT(bugprone-reserved-identifier) */
                > constexpr auto __RedBlackTree <
                        __ElementType,
                        __KeyType,
                        __keyExtractor,
                        __keyLowerComparator,
                        __keyEqualsComparator,
                        __nodeDestructor
                > :: __rbt_isRightChild (
                    __rbt_NodeType const * pNode
                ) const noexcept -> bool {

                    return pNode == pNode->_pParent->_pRight;
                }


                template <
                        typename                                                            __ElementType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,              /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,         /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyLowerComparator,   /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyEqualsComparator,  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor        /* NOLINT(bugprone-reserved-identifier) */
                > constexpr auto __RedBlackTree <
                        __ElementType,
                        __KeyType,
                        __keyExtractor,
                        __keyLowerComparator,
                        __keyEqualsComparator,
                        __nodeDestructor
                > :: __rbt_getLeftNode (
                    __rbt_NodeType * pNode
                ) const noexcept -> __rbt_NodeType * {

                    return pNode->_pLeft;
                }


                template <
                        typename                                                            __ElementType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,              /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,         /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyLowerComparator,   /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyEqualsComparator,  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor        /* NOLINT(bugprone-reserved-identifier) */
                > constexpr auto __RedBlackTree <
                        __ElementType,
                        __KeyType,
                        __keyExtractor,
                        __keyLowerComparator,
                        __keyEqualsComparator,
                        __nodeDestructor
                > :: __rbt_getRightNode (
                    __rbt_NodeType * pNode
                ) const noexcept -> __rbt_NodeType * {

                    return pNode->_pRight;
                }


                template <
                        typename                                                            __ElementType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,              /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,         /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyLowerComparator,   /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyEqualsComparator,  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor        /* NOLINT(bugprone-reserved-identifier) */
                > constexpr auto __RedBlackTree <
                        __ElementType,
                        __KeyType,
                        __keyExtractor,
                        __keyLowerComparator,
                        __keyEqualsComparator,
                        __nodeDestructor
                > :: __rbt_isNodeBlack (
                    __rbt_NodeType const * pNode
                ) noexcept -> bool {

                    return pNode->_colour == __rbt_NodeColourType :: __rbtnc_Black;
                }


                template <
                        typename                                                            __ElementType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,              /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,         /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyLowerComparator,   /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyEqualsComparator,  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor        /* NOLINT(bugprone-reserved-identifier) */
                > constexpr auto __RedBlackTree <
                        __ElementType,
                        __KeyType,
                        __keyExtractor,
                        __keyLowerComparator,
                        __keyEqualsComparator,
                        __nodeDestructor
                > :: __rbt_isNodeRed (
                    __rbt_NodeType const * pNode
                ) noexcept -> bool {

                    return pNode->_colour == __rbt_NodeColourType :: __rbtnc_Red;
                }


                template <
                        typename                                                            __ElementType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,              /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,         /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyLowerComparator,   /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyEqualsComparator,  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor        /* NOLINT(bugprone-reserved-identifier) */
                > __CDS_OptimalInline auto __RedBlackTree <
                        __ElementType,
                        __KeyType,
                        __keyExtractor,
                        __keyLowerComparator,
                        __keyEqualsComparator,
                        __nodeDestructor
                > :: __rbt_endNode () noexcept -> __rbt_NodeType * {

                    return & __RedBlackTreeEndNodeContainer < __ElementType > :: __endNode.data();
                }


                template <
                        typename                                                            __ElementType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,              /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,         /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyLowerComparator,   /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyEqualsComparator,  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor        /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        cds :: utility :: CopyConstructorFunction < __ElementType > __copy                          /* NOLINT(bugprone-reserved-identifier) */
                > __RedBlackTree <
                        __ElementType,
                        __KeyType,
                        __keyExtractor,
                        __keyLowerComparator,
                        __keyEqualsComparator,
                        __nodeDestructor
                > :: __RedBlackTree (
                    __RedBlackTree const & tree
                ) noexcept {

                    this->__rbt_copyCleared ( std :: move ( tree ) );
                }


                template <
                        typename                                                            __ElementType,          /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,              /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,         /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyLowerComparator,   /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyEqualsComparator,  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor        /* NOLINT(bugprone-reserved-identifier) */
                > constexpr __RedBlackTree <
                        __ElementType,
                        __KeyType,
                        __keyExtractor,
                        __keyLowerComparator,
                        __keyEqualsComparator,
                        __nodeDestructor
                > :: __RedBlackTree (
                    __RedBlackTree && tree
                ) noexcept :
                        _pRoot ( cds :: exchange ( tree._pRoot, nullptr ) ),
                        _size ( cds :: exchange ( tree._size, 0ULL ) ) {

                }


                template <
                        typename                                                            __ElementType,             /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,                 /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,            /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyLowerComparator,      /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyEqualsComparator,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor           /* NOLINT(bugprone-reserved-identifier) */
                >  __CDS_OptimalInline auto __RedBlackTree <
                        __ElementType,
                        __KeyType,
                        __keyExtractor,
                        __keyLowerComparator,
                        __keyEqualsComparator,
                        __nodeDestructor
                > :: __rbt_allocateNode () noexcept -> __rbt_NodeType * {

                    auto pNode      = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveObject < __rbt_NodeType > ();
                    pNode->_colour  = __RedBlackTree :: __rbt_NodeColourType :: __rbtnc_Red;
                    pNode->_pLeft   = __RedBlackTree :: __rbt_endNode();
                    pNode->_pRight  = __RedBlackTree :: __rbt_endNode();
                    pNode->_pParent = __RedBlackTree :: __rbt_endNode();

                    return pNode;
                }


                template <
                        typename                                                            __ElementType,             /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,                 /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,            /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyLowerComparator,      /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyEqualsComparator,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor           /* NOLINT(bugprone-reserved-identifier) */
                > auto __RedBlackTree <
                        __ElementType,
                        __KeyType,
                        __keyExtractor,
                        __keyLowerComparator,
                        __keyEqualsComparator,
                        __nodeDestructor
                > :: __rbt_freeNode (
                        __rbt_NodeType * pNode
                ) noexcept -> void {

                    __nodeDestructor ( pNode->_data );
                    cds :: __hidden :: __impl :: __allocation :: __freePrimitiveObject ( pNode );
                }


                template <
                        typename                                                            __ElementType,             /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,                 /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,            /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyLowerComparator,      /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyEqualsComparator,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor           /* NOLINT(bugprone-reserved-identifier) */
                > auto __RedBlackTree <
                        __ElementType,
                        __KeyType,
                        __keyExtractor,
                        __keyLowerComparator,
                        __keyEqualsComparator,
                        __nodeDestructor
                > :: __rbt_leftRotate (
                        __rbt_NodeType * pPivot
                ) noexcept -> void {

                    auto pAux           = pPivot->_pRight;
                    pPivot->_pRight     = pAux->_pLeft;

                    auto const pEndNode = __RedBlackTree :: __rbt_endNode();

                    if ( pAux->_pLeft != pEndNode ) {
                        pAux->_pLeft->_pParent = pPivot;
                    }

                    pAux->_pParent = pPivot->_pParent;

                    if ( pPivot->_pParent == pEndNode ) {
                        this->_pRoot = pAux;
                    } else if ( this->__rbt_isLeftChild ( pPivot ) ) {
                        pPivot->_pParent->_pLeft = pAux;
                    } else {
                        pPivot->_pParent->_pRight = pAux;
                    }

                    pAux->_pLeft = pPivot;
                    pPivot->_pParent = pAux;
                }


                template <
                        typename                                                            __ElementType,             /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,                 /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,            /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyLowerComparator,      /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyEqualsComparator,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor           /* NOLINT(bugprone-reserved-identifier) */
                > auto __RedBlackTree <
                        __ElementType,
                        __KeyType,
                        __keyExtractor,
                        __keyLowerComparator,
                        __keyEqualsComparator,
                        __nodeDestructor
                > :: __rbt_rightRotate (
                        __rbt_NodeType * pPivot
                ) noexcept -> void {

                    auto pAux           = pPivot->_pLeft;
                    pPivot->_pLeft      = pAux->_pRight;

                    auto const pEndNode = __RedBlackTree :: __rbt_endNode();

                    if ( pAux->_pRight != pEndNode ) {
                        pAux->_pRight->_pParent = pPivot;
                    }

                    pAux->_pParent = pPivot->_pParent;

                    if ( pPivot->_pParent == pEndNode ) {
                        this->_pRoot = pAux;
                    } else if ( this->__rbt_isLeftChild ( pPivot ) ) {
                        pPivot->_pParent->_pLeft = pAux;
                    } else {
                        pPivot->_pParent->_pRight = pAux;
                    }

                    pAux->_pRight = pPivot;
                    pPivot->_pParent = pAux;
                }

                template <
                        typename                                                            __ElementType,             /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,                 /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,            /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyLowerComparator,      /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyEqualsComparator,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor           /* NOLINT(bugprone-reserved-identifier) */
                > auto __RedBlackTree <
                        __ElementType,
                        __KeyType,
                        __keyExtractor,
                        __keyLowerComparator,
                        __keyEqualsComparator,
                        __nodeDestructor
                > :: __rbt_insertReBalance (
                        __rbt_NodeType * pPivot
                ) noexcept -> void {

                    while ( __RedBlackTree :: __rbt_isNodeRed ( pPivot->_pParent ) ) {
                        if ( this->__rbt_isLeftChild ( pPivot->_pParent ) ) {
                            this->__rbt_identifyAndApplyRotationOnInsert <
                                    __RedBlackTree,
                                    & __RedBlackTree :: __rbt_getRightNode,
                                    & __RedBlackTree :: __rbt_isRightChild,
                                    & __RedBlackTree :: __rbt_leftRotate,
                                    & __RedBlackTree :: __rbt_rightRotate
                            > ( pPivot );
                        } else {
                            this->__rbt_identifyAndApplyRotationOnInsert <
                                    __RedBlackTree,
                                    & __RedBlackTree :: __rbt_getLeftNode,
                                    & __RedBlackTree :: __rbt_isLeftChild,
                                    & __RedBlackTree :: __rbt_rightRotate,
                                    & __RedBlackTree :: __rbt_leftRotate
                            > ( pPivot );
                        }
                    }

                    this->_pRoot->_colour = __RedBlackTree :: __rbt_NodeColourType :: __rbtnc_Black;
                }


                template <
                        typename                                                            __ElementType,             /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,                 /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,            /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyLowerComparator,      /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyEqualsComparator,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor           /* NOLINT(bugprone-reserved-identifier) */
                > auto __RedBlackTree <
                        __ElementType,
                        __KeyType,
                        __keyExtractor,
                        __keyLowerComparator,
                        __keyEqualsComparator,
                        __nodeDestructor
                > :: __rbt_transplant (
                        __rbt_NodeType * pRemoved,
                        __rbt_NodeType * pMovedIn
                ) noexcept -> void {

                    if ( pRemoved->_pParent == __RedBlackTree :: __rbt_endNode() ) {
                        this->_pRoot = pMovedIn;
                    } else if ( this->__rbt_isLeftChild ( pRemoved ) ) {
                        pRemoved->_pParent->_pLeft = pMovedIn;
                    } else {
                        pRemoved->_pParent->_pRight = pMovedIn;
                    }

                    pMovedIn->_pParent = pRemoved->_pParent;
                }


                template <
                        typename                                                            __ElementType,             /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,                 /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,            /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyLowerComparator,      /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyEqualsComparator,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor           /* NOLINT(bugprone-reserved-identifier) */
                > auto __RedBlackTree <
                        __ElementType,
                        __KeyType,
                        __keyExtractor,
                        __keyLowerComparator,
                        __keyEqualsComparator,
                        __nodeDestructor
                > :: __rbt_deleteReBalance (
                        __rbt_NodeType * pPivot
                ) -> void {

                    while ( pPivot != this->_pRoot && __RedBlackTree :: __rbt_isNodeBlack ( pPivot ) ) {
                        if ( this->__rbt_isLeftChild ( pPivot ) ) {
                            this->__rbt_identifyAndApplyRotationOnDelete <
                                    __RedBlackTree,
                                    & __RedBlackTree :: __rbt_getRightNode,
                                    & __RedBlackTree :: __rbt_getLeftNode,
                                    & __RedBlackTree :: __rbt_isRightChild,
                                    & __RedBlackTree :: __rbt_leftRotate,
                                    & __RedBlackTree :: __rbt_rightRotate
                            > ( pPivot );
                        } else {
                            this->__rbt_identifyAndApplyRotationOnDelete <
                                    __RedBlackTree,
                                    & __RedBlackTree :: __rbt_getLeftNode,
                                    & __RedBlackTree :: __rbt_getRightNode,
                                    & __RedBlackTree :: __rbt_isLeftChild,
                                    & __RedBlackTree :: __rbt_rightRotate,
                                    & __RedBlackTree :: __rbt_leftRotate
                            > ( pPivot );
                        }
                    }

                    pPivot->_colour = __RedBlackTree :: __rbt_NodeColourType :: __rbtnc_Black;
                }

                template <
                        typename                                                            __ElementType,              /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,                  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,             /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyLowerComparator,       /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyEqualsComparator,      /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor            /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        typename                                                            __ClassType,                /* NOLINT(bugprone-reserved-identifier) */
                        typename __ClassType :: __rbt_AuxiliaryLocatorFunction              __locateAuxiliary,          /* NOLINT(bugprone-reserved-identifier) */
                        typename __ClassType :: __rbt_RotationConditionalFunction           __scenarioConditional,      /* NOLINT(bugprone-reserved-identifier) */
                        typename __ClassType :: __rbt_RotationScenarioFunction              __ifTrue,                   /* NOLINT(bugprone-reserved-identifier) */
                        typename __ClassType :: __rbt_RotationScenarioFunction              __ifFalse                   /* NOLINT(bugprone-reserved-identifier) */
                > auto __RedBlackTree <
                        __ElementType,
                        __KeyType,
                        __keyExtractor,
                        __keyLowerComparator,
                        __keyEqualsComparator,
                        __nodeDestructor
                > :: __rbt_identifyAndApplyRotationOnInsert (
                        __rbt_NodeType * & pPivot
                ) noexcept -> void {

                    auto pAux = ( this ->* __locateAuxiliary ) ( pPivot->_pParent->_pParent );

                    if ( this->__rbt_isNodeRed ( pAux ) ) {

                        pPivot->_pParent->_colour           = __RedBlackTree :: __rbt_NodeColourType :: __rbtnc_Black;
                        pAux->_colour                       = __RedBlackTree :: __rbt_NodeColourType :: __rbtnc_Black;
                        pPivot->_pParent->_pParent->_colour = __RedBlackTree :: __rbt_NodeColourType :: __rbtnc_Red;
                        pPivot                              = pPivot->_pParent->_pParent;
                    } else {

                        if ( ( this ->* __scenarioConditional ) ( pPivot ) ) {
                            pPivot = pPivot->_pParent;
                            ( this ->* __ifTrue )( pPivot );
                        }

                        pPivot->_pParent->_colour           = __RedBlackTree :: __rbt_NodeColourType :: __rbtnc_Black;
                        pPivot->_pParent->_pParent->_colour = __RedBlackTree :: __rbt_NodeColourType :: __rbtnc_Red;
                        ( this ->* __ifFalse )( pPivot->_pParent->_pParent );
                    }
                }


                template <
                        typename                                                            __ElementType,              /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,                  /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,             /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyLowerComparator,       /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyEqualsComparator,      /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor            /* NOLINT(bugprone-reserved-identifier) */
                >  template <
                        typename                                                            __ClassType,                /* NOLINT(bugprone-reserved-identifier) */
                        typename __ClassType :: __rbt_AuxiliaryLocatorFunction              __locateAuxiliary,          /* NOLINT(bugprone-reserved-identifier) */
                        typename __ClassType :: __rbt_AuxiliaryLocatorFunction              __locateReverseAuxiliary,   /* NOLINT(bugprone-reserved-identifier) */
                        typename __ClassType :: __rbt_RotationConditionalFunction           __scenarioConditional,      /* NOLINT(bugprone-reserved-identifier) */
                        typename __ClassType :: __rbt_RotationScenarioFunction              __ifTrue,                   /* NOLINT(bugprone-reserved-identifier) */
                        typename __ClassType :: __rbt_RotationScenarioFunction              __ifFalse                   /* NOLINT(bugprone-reserved-identifier) */
                > auto __RedBlackTree <
                        __ElementType,
                        __KeyType,
                        __keyExtractor,
                        __keyLowerComparator,
                        __keyEqualsComparator,
                        __nodeDestructor
                > :: __rbt_identifyAndApplyRotationOnDelete (
                        __rbt_NodeType * & pPivot
                ) noexcept -> void {

                    auto pAux = ( this ->* __locateAuxiliary ) ( pPivot->_pParent );

                    if ( this->__rbt_isNodeRed ( pAux) ) {

                        pAux->_colour               = __RedBlackTree :: __rbt_NodeColourType :: __rbtnc_Black;
                        pPivot->_pParent->_colour   = __RedBlackTree :: __rbt_NodeColourType :: __rbtnc_Red;
                        ( this ->* __ifTrue )( pPivot->_pParent );
                        pAux                        = ( this ->* __locateAuxiliary ) ( pPivot->_pParent );
                    }

                    if ( this->__rbt_isNodeBlack ( pAux->_pLeft ) && this->__rbt_isNodeBlack ( pAux->_pRight ) ) {

                        pAux->_colour   = __RedBlackTree :: __rbt_NodeColourType :: __rbtnc_Red;
                        pPivot          = pPivot->_pParent;
                    } else {

                        if ( this->__rbt_isNodeBlack ( ( this ->* __locateAuxiliary ) ( pAux ) ) ) {

                            ( this ->* __locateReverseAuxiliary ) ( pAux )->_colour = __RedBlackTree :: __rbt_NodeColourType :: __rbtnc_Black;
                            pAux->_colour                                           = __RedBlackTree :: __rbt_NodeColourType :: __rbtnc_Red;
                            ( this ->* __ifFalse )( pAux );
                            pAux                                                    = ( this ->* __locateAuxiliary ) ( pPivot->_pParent );
                        }

                        pAux->_colour                                       = pPivot->_pParent->_colour;
                        pPivot->_pParent->_colour                           = __RedBlackTree :: __rbt_NodeColourType :: __rbtnc_Black;
                        ( this ->* __locateAuxiliary ) ( pAux )->_colour    = __RedBlackTree :: __rbt_NodeColourType :: __rbtnc_Black;
                        ( this ->* __ifTrue ) ( pPivot->_pParent );
                        pPivot                                              = this->_pRoot;
                    }

                }

                template <
                        typename                                                            __ElementType,             /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,                 /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,            /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyLowerComparator,      /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyEqualsComparator,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor           /* NOLINT(bugprone-reserved-identifier) */
                > auto __RedBlackTree <
                        __ElementType,
                        __KeyType,
                        __keyExtractor,
                        __keyLowerComparator,
                        __keyEqualsComparator,
                        __nodeDestructor
                > :: __rbt_empty () const -> bool {

                    return this->_size == 0;
                }


                template <
                        typename                                                            __ElementType,             /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,                 /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,            /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyLowerComparator,      /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyEqualsComparator,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor           /* NOLINT(bugprone-reserved-identifier) */
                > auto __RedBlackTree <
                        __ElementType,
                        __KeyType,
                        __keyExtractor,
                        __keyLowerComparator,
                        __keyEqualsComparator,
                        __nodeDestructor
                > :: __rbt_get (
                        __KeyType const &   key,
                        bool            *   pIsNew
                ) noexcept -> __ElementType * {

                    if ( this->__rbt_empty() ) {

                        this->_pRoot            = __RedBlackTree :: __rbt_allocateNode();
                        this->_pRoot->_colour   = __RedBlackTree :: __rbt_NodeColourType :: __rbtnc_Black;

                        ++ this->_size;
                        * pIsNew = true;
                        return & this->_pRoot->_data;
                    }

                    auto                pAux        = this->_pRoot;
                    __rbt_NodeType *    pNewPos;

                    auto          const pEndNode    = __RedBlackTree :: __rbt_endNode();

                    while ( pAux != pEndNode ) {
                        pNewPos = pAux;

                        if ( __keyEqualsComparator ( key, __keyExtractor ( pAux->_data ) ) ) {
                            * pIsNew = false;
                            return & pAux->_data;
                        }

                        if ( __keyLowerComparator ( key, __keyExtractor ( pAux->_data ) ) ) {
                            pAux = pAux->_pLeft;
                        } else {
                            pAux = pAux->_pRight;
                        }
                    }

                    auto pNewNode = __RedBlackTree :: __rbt_allocateNode();
                    pNewNode->_pParent = pNewPos;

                    if ( __keyLowerComparator ( key, __keyExtractor ( pNewPos->_data ) ) ) {
                        pNewPos->_pLeft = pNewNode;
                    } else {
                        pNewPos->_pRight = pNewNode;
                    }

                    this->__rbt_insertReBalance ( pNewNode );
                    * pIsNew = true;
                    ++ this->_size;

                    return & pNewNode->_data;
                }


                template <
                        typename                                                            __ElementType,             /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,                 /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,            /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyLowerComparator,      /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyEqualsComparator,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor           /* NOLINT(bugprone-reserved-identifier) */
                > auto __RedBlackTree <
                        __ElementType,
                        __KeyType,
                        __keyExtractor,
                        __keyLowerComparator,
                        __keyEqualsComparator,
                        __nodeDestructor
                > :: __rbt_get (
                        __KeyType const & key
                ) const noexcept -> __ElementType const * {

                    if ( this->__rbt_empty() ) {
                        return nullptr;
                    }

                    auto        pSearch     = this->_pRoot;
                    auto  const pEndNode    = __RedBlackTree :: __rbt_endNode();

                    while ( pSearch != pEndNode ) {
                        if ( __keyEqualsComparator ( key, __keyExtractor ( pSearch->_data ) ) ) {
                            return & pSearch->_data;
                        }

                        if ( __keyLowerComparator ( key, __keyExtractor ( pSearch->_data ) ) ) {
                            pSearch = pSearch->_pLeft;
                        } else {
                            pSearch = pSearch->_pRight;
                        }
                    }

                    return nullptr;
                }


                template <
                        typename                                                            __ElementType,             /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,                 /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,            /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyLowerComparator,      /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyEqualsComparator,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor           /* NOLINT(bugprone-reserved-identifier) */
                > auto __RedBlackTree <
                        __ElementType,
                        __KeyType,
                        __keyExtractor,
                        __keyLowerComparator,
                        __keyEqualsComparator,
                        __nodeDestructor
                > :: __rbt_removeAt (
                        __rbt_NodeType * pToBeRemoved
                ) noexcept -> bool {

                    auto          const pEndNode            = __RedBlackTree :: __rbt_endNode();
                    auto                isOriginallyBlack   = __RedBlackTree :: __rbt_isNodeBlack ( pToBeRemoved );
                    __rbt_NodeType    * pBalancePivot;

                    if ( pToBeRemoved->_pLeft == pEndNode ) {
                        pBalancePivot = pToBeRemoved->_pRight;
                        this->__rbt_transplant ( pToBeRemoved, pToBeRemoved->_pRight );
                    } else if ( pToBeRemoved->_pRight == pEndNode ) {
                            pBalancePivot = pToBeRemoved->_pLeft;
                            this->__rbt_transplant ( pToBeRemoved, pToBeRemoved->_pLeft );
                    } else {
                        auto pDeletedPlaceholder = pToBeRemoved->_pRight;

                        while ( pDeletedPlaceholder->_pLeft != pEndNode )
                            pDeletedPlaceholder = pDeletedPlaceholder->_pLeft;

                        isOriginallyBlack = __RedBlackTree :: __rbt_isNodeBlack ( pDeletedPlaceholder );
                        pBalancePivot = pDeletedPlaceholder->_pRight;

                        if ( pDeletedPlaceholder->_pParent == pToBeRemoved ) {
                            pBalancePivot->_pParent = pDeletedPlaceholder;
                        } else {
                            this->__rbt_transplant ( pDeletedPlaceholder, pDeletedPlaceholder->_pRight );
                            pDeletedPlaceholder->_pRight            = pToBeRemoved->_pRight;
                            pDeletedPlaceholder->_pRight->_pParent  = pDeletedPlaceholder;
                        }

                        this->__rbt_transplant ( pToBeRemoved, pDeletedPlaceholder );
                        pDeletedPlaceholder->_pLeft             = pToBeRemoved->_pLeft;
                        pDeletedPlaceholder->_pLeft->_pParent   = pDeletedPlaceholder;
                        pDeletedPlaceholder->_colour            = pToBeRemoved->_colour;
                    }

                    __RedBlackTree :: __rbt_freeNode ( pToBeRemoved );

                    if ( isOriginallyBlack ) {
                        this->__rbt_deleteReBalance ( pBalancePivot );
                    }

                    -- this->_size;

                    return true;
                }


                template <
                        typename                                                            __ElementType,             /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,                 /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,            /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyLowerComparator,      /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyEqualsComparator,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor           /* NOLINT(bugprone-reserved-identifier) */
                > auto __RedBlackTree <
                        __ElementType,
                        __KeyType,
                        __keyExtractor,
                        __keyLowerComparator,
                        __keyEqualsComparator,
                        __nodeDestructor
                > :: __rbt_remove (
                        __ElementType const & key
                ) noexcept -> bool {

                    if ( this->__rbt_empty() ) {
                        return false;
                    }

                    auto        pToBeRemoved    = this->_pRoot;
                    auto  const pEndNode        = __RedBlackTree :: __rbt_endNode();

                    while ( pToBeRemoved != pEndNode ) {

                        if ( __keyEqualsComparator ( key, __keyExtractor ( pToBeRemoved->_data ) ) ) {
                            this->__rbt_removeAt ( pToBeRemoved );
                            return true;
                        }

                        if ( __keyLowerComparator ( key, __keyExtractor ( pToBeRemoved->_data ) ) ) {
                            pToBeRemoved = pToBeRemoved->_pLeft;
                        } else {
                            pToBeRemoved = pToBeRemoved->_pRight;
                        }
                    }

                    return false;
                }


                template <
                        typename                                                            __ElementType,             /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,                 /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,            /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyLowerComparator,      /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyEqualsComparator,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor           /* NOLINT(bugprone-reserved-identifier) */
                > auto __RedBlackTree <
                        __ElementType,
                        __KeyType,
                        __keyExtractor,
                        __keyLowerComparator,
                        __keyEqualsComparator,
                        __nodeDestructor
                > :: __rbt_removeIterator (
                    AbstractTreeConstIterator < __ElementType > const & iterator
                ) noexcept -> bool {

                    auto pToBeRemoved = const_cast < __rbt_NodeType * > ( iterator._pCurrentNode );
                    if ( pToBeRemoved == nullptr ) {
                        return false;
                    }

                    return this->__rbt_removeAt ( pToBeRemoved );
                }


                template <
                        typename                                                            __ElementType,             /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,                 /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,            /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyLowerComparator,      /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyEqualsComparator,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor           /* NOLINT(bugprone-reserved-identifier) */
                > auto __RedBlackTree <
                        __ElementType,
                        __KeyType,
                        __keyExtractor,
                        __keyLowerComparator,
                        __keyEqualsComparator,
                        __nodeDestructor
                > :: __rbt_removeConstIteratorArray (
                        AbstractTreeConstIterator < __ElementType > const * const * iteratorArray,
                        Size                                iteratorCount
                ) noexcept -> Size {

                    Size removeCount = 0ULL;
                    for ( auto index = 0ULL; index < iteratorCount; ++ index ) {
                        if ( this->__rbt_removeIterator ( * iteratorArray [ index ] ) )
                            ++ removeCount;
                    }

                    return removeCount;
                }


                template <
                        typename                                                            __ElementType,             /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,                 /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,            /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyLowerComparator,      /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyEqualsComparator,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor           /* NOLINT(bugprone-reserved-identifier) */
                > auto __RedBlackTree <
                        __ElementType,
                        __KeyType,
                        __keyExtractor,
                        __keyLowerComparator,
                        __keyEqualsComparator,
                        __nodeDestructor
                > :: __rbt_clear () noexcept -> void {

                    if ( this->__rbt_empty() )
                        return;

                    auto  const pEndNode        = __RedBlackTree :: __rbt_endNode();
                    auto        pCurrentNode    = this->_pRoot;

                    while ( pCurrentNode != pEndNode ) {

                        if ( pCurrentNode->_pLeft != pEndNode ) {
                            pCurrentNode = pCurrentNode->_pLeft;
                        } else {

                            if ( pCurrentNode->_pRight != pEndNode ) {
                                pCurrentNode = pCurrentNode->_pRight;
                            } else {

                                auto pToBeDeleted   = pCurrentNode;
                                pCurrentNode        = pCurrentNode->_pParent;

                                if ( pToBeDeleted != this->_pRoot) {
                                    if ( this->__rbt_isLeftChild ( pToBeDeleted ) ) {
                                        pCurrentNode->_pLeft    = pEndNode;
                                    }
                                    else {
                                        pCurrentNode->_pRight   = pEndNode;
                                    }
                                }

                                __RedBlackTree :: __rbt_freeNode ( pToBeDeleted );
                            }
                        }
                    }

                    this->_size = 0ULL;
                }


                template <
                        typename                                                            __ElementType,             /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,                 /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,            /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyLowerComparator,      /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyEqualsComparator,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor           /* NOLINT(bugprone-reserved-identifier) */
                > auto __RedBlackTree <
                        __ElementType,
                        __KeyType,
                        __keyExtractor,
                        __keyLowerComparator,
                        __keyEqualsComparator,
                        __nodeDestructor
                > :: __rbt_findIteratorConst (
                        __KeyType const & key
                ) const noexcept -> __rbt_ConstIterator {

                    if ( this->__rbt_empty() ) {
                        return __rbt_ConstIterator();
                    }

                    auto        pSearch     = this->_pRoot;
                    auto  const pEndNode    = __RedBlackTree :: __rbt_endNode();

                    while ( pSearch != pEndNode ) {
                        if ( __keyEqualsComparator ( __keyExtractor ( pSearch->_data ), key ) ) {
                            return ( __rbt_ConstIterator ( this->_pRoot, pSearch ) );
                        }

                        if ( __keyLowerComparator ( __keyExtractor ( pSearch->_data ), key ) ) {
                            pSearch = pSearch->_pLeft;
                        } else {
                            pSearch = pSearch->_pRight;
                        }
                    }

                    return __rbt_ConstIterator();
                }


                template <
                        typename                                                            __ElementType,             /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,                 /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,            /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyLowerComparator,      /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyEqualsComparator,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor           /* NOLINT(bugprone-reserved-identifier) */
                > auto __RedBlackTree <
                        __ElementType,
                        __KeyType,
                        __keyExtractor,
                        __keyLowerComparator,
                        __keyEqualsComparator,
                        __nodeDestructor
                > :: __rbt_size () const noexcept -> Size {

                    return this->_size;
                }


                template <
                        typename                                                            __ElementType,             /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,                 /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,            /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyLowerComparator,      /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyEqualsComparator,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor           /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        cds :: utility :: CopyConstructorFunction < __ElementType > __copy                             /* NOLINT(bugprone-reserved-identifier) */
                > auto __RedBlackTree <
                        __ElementType,
                        __KeyType,
                        __keyExtractor,
                        __keyLowerComparator,
                        __keyEqualsComparator,
                        __nodeDestructor
                > ::  __rbt_copy (
                        const __RedBlackTree & tree
                ) noexcept -> void {

                    if ( this == & tree ) {
                        return;
                    }

                    this->__rbt_clear();
                    this->__rbt_copyCleared < __copy > ( tree );
                }


                template <
                        typename                                                            __ElementType,             /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,                 /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,            /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyLowerComparator,      /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyEqualsComparator,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor           /* NOLINT(bugprone-reserved-identifier) */
                > template <
                        cds :: utility :: CopyConstructorFunction < __ElementType > __copy                             /* NOLINT(bugprone-reserved-identifier) */
                > auto __RedBlackTree <
                        __ElementType,
                        __KeyType,
                        __keyExtractor,
                        __keyLowerComparator,
                        __keyEqualsComparator,
                        __nodeDestructor
                > ::  __rbt_copyCleared (
                        const __RedBlackTree & tree
                ) noexcept -> void {

                    if ( tree.__rbt_empty() ) {
                        return;
                    }

                    auto  const pEndNode        = __RedBlackTree :: __rbt_endNode();
                    auto        pSource         = tree._pRoot;
                    auto        pDestination    = this->_pRoot = __RedBlackTree :: __rbt_allocateNode();
                    while ( pSource != pEndNode ) {

                        if ( pSource->_pLeft != pEndNode && pDestination->_pLeft == pEndNode ) {
                            pSource = pSource->_pLeft;
                            pDestination->_pLeft = __RedBlackTree :: __rbt_allocateNode();
                            pDestination->_pLeft->_pParent = pDestination;
                            pDestination = pDestination->_pLeft;
                        }
                        else
                            if ( pSource->_pRight != pEndNode && pDestination->_pRight == pEndNode ) {
                                pSource = pSource->_pRight;
                                pDestination->_pRight = __RedBlackTree :: __rbt_allocateNode();
                                pDestination->_pRight->_pParent = pDestination;
                                pDestination = pDestination->_pRight;
                            }
                            else {
                                __copy ( pDestination->_data, pSource->_data );
                                pDestination->_colour = pSource->_colour;
                                pDestination = pDestination->_pParent;
                                pSource = pSource->_pParent;
                            }
                    }

                    this->_size = tree._size;
                }


                template <
                        typename                                                            __ElementType,             /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,                 /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,            /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyLowerComparator,      /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyEqualsComparator,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor           /* NOLINT(bugprone-reserved-identifier) */
                > auto __RedBlackTree <
                        __ElementType,
                        __KeyType,
                        __keyExtractor,
                        __keyLowerComparator,
                        __keyEqualsComparator,
                        __nodeDestructor
                > :: __rbt_move (
                        __RedBlackTree && tree
                ) noexcept -> void {

                    if ( this == & tree ) {
                        return;
                    }

                    this->__rbt_clear();
                    this->__rbt_moveCleared( std :: move ( tree ) );
                }


                template <
                        typename                                                            __ElementType,             /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,                 /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,            /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyLowerComparator,      /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyEqualsComparator,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor           /* NOLINT(bugprone-reserved-identifier) */
                > auto __RedBlackTree <
                        __ElementType,
                        __KeyType,
                        __keyExtractor,
                        __keyLowerComparator,
                        __keyEqualsComparator,
                        __nodeDestructor
                > :: __rbt_moveCleared (
                        __RedBlackTree && tree
                ) noexcept -> void {

                    this->_size = cds :: exchange ( tree._size, 0ULL );
                    this->_pRoot = cds :: exchange ( tree._pRoot, nullptr );
                }


                template <
                        typename                                                            __ElementType,             /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,                 /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,            /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyLowerComparator,      /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyEqualsComparator,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor           /* NOLINT(bugprone-reserved-identifier) */
                > auto __RedBlackTree <
                        __ElementType,
                        __KeyType,
                        __keyExtractor,
                        __keyLowerComparator,
                        __keyEqualsComparator,
                        __nodeDestructor
                > :: __rbt_new (
                        const __ElementType *   pReferenceElement,
                        bool                *   pIsNew
                ) noexcept -> __ElementType * {

                    return this->__rbt_get (
                            __keyExtractor ( * pReferenceElement ),
                            pIsNew
                    );
                }


                template <
                        typename                                                            __ElementType,             /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,                 /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,            /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyLowerComparator,      /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyEqualsComparator,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor           /* NOLINT(bugprone-reserved-identifier) */
                > auto __RedBlackTree <
                        __ElementType,
                        __KeyType,
                        __keyExtractor,
                        __keyLowerComparator,
                        __keyEqualsComparator,
                        __nodeDestructor
                > :: __rbt_begin () noexcept -> __rbt_Iterator {

                    if ( this->__rbt_empty() ) {
                        return __rbt_Iterator ( nullptr, nullptr );
                    }

                    auto        pBegin      = this->_pRoot;
                    auto  const pEndNode    = __RedBlackTree :: __rbt_endNode();

                    while ( pBegin->_pLeft != pEndNode ) {
                        pBegin = pBegin->_pLeft;
                    }

                    return __rbt_Iterator ( this->_pRoot, pBegin );
                }


                template <
                        typename                                                            __ElementType,             /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,                 /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,            /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyLowerComparator,      /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyEqualsComparator,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor           /* NOLINT(bugprone-reserved-identifier) */
                > auto __RedBlackTree <
                        __ElementType,
                        __KeyType,
                        __keyExtractor,
                        __keyLowerComparator,
                        __keyEqualsComparator,
                        __nodeDestructor
                > :: __rbt_end () noexcept -> __rbt_Iterator {

                    return __rbt_Iterator ( this->_pRoot, nullptr );
                }


                template <
                        typename                                                            __ElementType,             /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,                 /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,            /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyLowerComparator,      /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyEqualsComparator,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor           /* NOLINT(bugprone-reserved-identifier) */
                > auto __RedBlackTree <
                        __ElementType,
                        __KeyType,
                        __keyExtractor,
                        __keyLowerComparator,
                        __keyEqualsComparator,
                        __nodeDestructor
                > :: __rbt_rbegin () noexcept -> __rbt_ReverseIterator {

                    if ( this->__rbt_empty() ) {
                        return __rbt_ReverseIterator ( nullptr, nullptr );
                    }

                    auto        prEnd       = this->_pRoot;
                    auto  const pEndNode    = __RedBlackTree :: __rbt_endNode();

                    while ( prEnd->_pRight != pEndNode ) {
                        prEnd = prEnd->_pRight;
                    }

                    return __rbt_ReverseIterator ( this->_pRoot, prEnd );
                }


                template <
                        typename                                                            __ElementType,             /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,                 /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,            /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyLowerComparator,      /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyEqualsComparator,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor           /* NOLINT(bugprone-reserved-identifier) */
                > auto __RedBlackTree <
                        __ElementType,
                        __KeyType,
                        __keyExtractor,
                        __keyLowerComparator,
                        __keyEqualsComparator,
                        __nodeDestructor
                > :: __rbt_rend () noexcept -> __rbt_ReverseIterator {

                    return __rbt_ReverseIterator ( this->_pRoot, nullptr );
                }


                template <
                        typename                                                            __ElementType,             /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,                 /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,            /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyLowerComparator,      /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyEqualsComparator,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor           /* NOLINT(bugprone-reserved-identifier) */
                > auto __RedBlackTree <
                        __ElementType,
                        __KeyType,
                        __keyExtractor,
                        __keyLowerComparator,
                        __keyEqualsComparator,
                        __nodeDestructor
                > :: __rbt_cbegin () const noexcept -> __rbt_ConstIterator {

                    if ( this->__rbt_empty() ) {
                        return __rbt_ConstIterator ( nullptr, nullptr );
                    }

                    auto        pcBegin     = this->_pRoot;
                    auto  const pEndNode    = __RedBlackTree :: __rbt_endNode();

                    while ( pcBegin->_pLeft != pEndNode ) {
                        pcBegin = pcBegin->_pLeft;
                    }

                    return __rbt_ConstIterator ( this->_pRoot, pcBegin );
                }


                template <
                        typename                                                            __ElementType,             /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,                 /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,            /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyLowerComparator,      /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyEqualsComparator,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor           /* NOLINT(bugprone-reserved-identifier) */
                > auto __RedBlackTree <
                        __ElementType,
                        __KeyType,
                        __keyExtractor,
                        __keyLowerComparator,
                        __keyEqualsComparator,
                        __nodeDestructor
                > :: __rbt_cend () const noexcept -> __rbt_ConstIterator {

                    return __rbt_ConstIterator ( this->_pRoot, nullptr );
                }


                template <
                        typename                                                            __ElementType,             /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,                 /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,            /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyLowerComparator,      /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyEqualsComparator,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor           /* NOLINT(bugprone-reserved-identifier) */
                > auto __RedBlackTree <
                        __ElementType,
                        __KeyType,
                        __keyExtractor,
                        __keyLowerComparator,
                        __keyEqualsComparator,
                        __nodeDestructor
                > :: __rbt_crbegin () const noexcept -> __rbt_ReverseConstIterator {

                    if ( this->__rbt_empty() ) {
                        return __rbt_ReverseConstIterator ( nullptr, nullptr );
                    }

                    auto        pcrBegin    = this->_pRoot;
                    auto  const pEndNode    = __RedBlackTree :: __rbt_endNode();

                    while ( pcrBegin->_pRight != pEndNode ) {
                        pcrBegin = pcrBegin->_pRight;
                    }

                    return __rbt_ReverseConstIterator ( this->_pRoot, pcrBegin );
                }


                template <
                        typename                                                            __ElementType,             /* NOLINT(bugprone-reserved-identifier) */
                        typename                                                            __KeyType,                 /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,            /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyLowerComparator,      /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyEqualsComparator,     /* NOLINT(bugprone-reserved-identifier) */
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor           /* NOLINT(bugprone-reserved-identifier) */
                > auto __RedBlackTree <
                        __ElementType,
                        __KeyType,
                        __keyExtractor,
                        __keyLowerComparator,
                        __keyEqualsComparator,
                        __nodeDestructor
                > :: __rbt_crend () const noexcept -> __rbt_ReverseConstIterator {

                    return __rbt_ReverseConstIterator ( this->_pRoot, nullptr );
                }
            }
        }
    }
}

#endif /* __CDS_EX_SHARED_RED_BLACK_TREE_IMPL_HPP__ */