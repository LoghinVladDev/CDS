//
// Created by stefan on 02.07.2022.
//

#ifndef __CDS_EX_SHARED_RED_BLACK_TREE_IMPL_HPP__
#define __CDS_EX_SHARED_RED_BLACK_TREE_IMPL_HPP__
#include <CDS/Comparator>
#include <CDS/Extractor>
#include <CDS/Destructor>
#include <CDS/Options>
#include <CDS/Function>
#include "../RedBlackTree.hpp"
namespace cds {                     // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {
        namespace __hidden {        // NOLINT(bugprone-reserved-identifier)
            namespace __impl {      // NOLINT(bugprone-reserved-identifier)

                template <
                        typename                                                            __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyType,                 // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,            // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyLowerComparator,      // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyEqualsComparator,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor           // NOLINT(bugprone-reserved-identifier)
                >  __CDS_OptimalInline auto __RedBlackTree <
                        __ElementType,
                        __KeyType,
                        __keyExtractor,
                        __keyLowerComparator,
                        __keyEqualsComparator,
                        __nodeDestructor
                > :: __rbt_allocateNode () noexcept -> RBTreeNode * {

                    RBTreeNode * pNode  = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveObject < RBTreeNode > ();
                    pNode->_colour      = __RedBlackTreeNode < __ElementType > :: RED;
                    pNode->_pLeft       = pNode->_pRight = pNode->_pParent = __RedBlackTree :: __endNode();
                    return pNode;
                }


                template <
                        typename                                                            __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyType,                 // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,            // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyLowerComparator,      // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyEqualsComparator,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor           // NOLINT(bugprone-reserved-identifier)
                > auto __RedBlackTree <
                        __ElementType,
                        __KeyType,
                        __keyExtractor,
                        __keyLowerComparator,
                        __keyEqualsComparator,
                        __nodeDestructor
                > :: __rbt_freeNode (
                        RBTreeNode * pRemoved
                ) noexcept -> void {

                    __nodeDestruct ( pRemoved->_data );
                    cds :: __hidden :: __impl :: __allocation :: __freePrimitiveObject ( pRemoved );
                }


                template <
                        typename                                                            __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyType,                 // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,            // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyLowerComparator,      // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyEqualsComparator,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor           // NOLINT(bugprone-reserved-identifier)
                > auto __RedBlackTree <
                        __ElementType,
                        __KeyType,
                        __keyExtractor,
                        __keyLowerComparator,
                        __keyEqualsComparator,
                        __nodeDestructor
                > :: __rbt_leftRotate (
                        RBTreeNode * pPivot
                ) noexcept -> void {

                    RBTreeNode * pAux = pPivot->_pRight;
                    pPivot->_pRight = pAux->_pLeft;

                    if ( pAux->_pLeft != __RedBlackTree :: __endNode() ) {
                        pAux->_pLeft->_pParent = pPivot;
                    }

                    pAux->_pParent = pPivot;

                    if ( pPivot->_pParent == __RedBlackTree :: __endNode() ) {
                        this->_root = pAux;
                    } else {

                        if ( __isLeftChild ( pPivot ) ) {
                            pPivot->_pParent->_pLeft = pAux;
                        } else {
                            pPivot->_pParent->_pRight = pAux;
                        }
                    }

                    pAux->_pLeft = pPivot;
                    pPivot->_pParent = pAux;
                }


                template <
                        typename                                                            __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyType,                 // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,            // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyLowerComparator,      // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyEqualsComparator,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor           // NOLINT(bugprone-reserved-identifier)
                > auto __RedBlackTree <
                        __ElementType,
                        __KeyType,
                        __keyExtractor,
                        __keyLowerComparator,
                        __keyEqualsComparator,
                        __nodeDestructor
                > :: __rbt_rightRotate (
                        RBTreeNode * pPivot
                ) noexcept -> void {

                    RBTreeNode * pAux = pPivot->_pLeft;
                    pPivot->_pLeft = pAux->_pRight;

                    if ( pAux->_pRight != __RedBlackTree :: __endNode() ) {
                        pAux->_pLeft = pPivot;
                    }

                    pAux->_pParent = pPivot->_pParent;

                    if ( pPivot->_pParent == __RedBlackTree :: __endNode() ) {
                        this->_root = pAux;
                    } else {

                        if ( __isLeftChild ( pPivot ) ) {
                            pPivot->_pParent->_pLeft = pAux;
                        } else {
                            pPivot->_pParent->_pRight = pAux;
                        }
                    }

                    pAux->_pRight = pPivot;
                    pPivot->_pParent = pAux;
                }

                template <
                        typename                                                            __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyType,                 // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,            // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyLowerComparator,      // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyEqualsComparator,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor           // NOLINT(bugprone-reserved-identifier)
                > auto __RedBlackTree <
                        __ElementType,
                        __KeyType,
                        __keyExtractor,
                        __keyLowerComparator,
                        __keyEqualsComparator,
                        __nodeDestructor
                > :: __rbt_insertReBalance (
                        RBTreeNode * pPivot
                ) noexcept -> void {

                    while ( __isRed ( pPivot->_pParent ) ) {
                        __identifyAndApplyRotationOnInsert < __isLeftChild ( pPivot ) > ( pPivot );
                    }

                    this->_root->_colour = RBTreeNode :: BLACK;
                }


                template <
                        typename                                                            __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyType,                 // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,            // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyLowerComparator,      // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyEqualsComparator,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor           // NOLINT(bugprone-reserved-identifier)
                > auto __RedBlackTree <
                        __ElementType,
                        __KeyType,
                        __keyExtractor,
                        __keyLowerComparator,
                        __keyEqualsComparator,
                        __nodeDestructor
                > :: __rbt_transplant (
                        RBTreeNode * pRemoved,
                        RBTreeNode * pMovedIn
                ) noexcept -> void {

                    if ( pRemoved->_pParent == __RedBlackTree :: __endNode() ) {
                        this->_root = pMovedIn;
                    } else {

                        if ( __isLeftChild ( pRemoved ) ) {
                            pRemoved->_pParent->_pLeft = pRemoved;
                        } else {
                            pRemoved->_pParent->_pRight = pRemoved;
                        }
                    }

                    pMovedIn->_pParent = pRemoved->_pParent;
                }


                template <
                        typename                                                            __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyType,                 // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,            // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyLowerComparator,      // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyEqualsComparator,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor           // NOLINT(bugprone-reserved-identifier)
                > auto __RedBlackTree <
                        __ElementType,
                        __KeyType,
                        __keyExtractor,
                        __keyLowerComparator,
                        __keyEqualsComparator,
                        __nodeDestructor
                > :: __rbt_deleteReBalance (
                        RBTreeNode * pPivot
                ) -> void {

                    while ( pPivot != this->_root && !__isRed (pPivot ) ) {
                        __identifyAndApplyRotationOnDelete < __isLeftChild ( pPivot ) > ( pPivot );
                    }
                }

                template <
                        typename                                                            __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyType,                 // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,            // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyLowerComparator,      // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyEqualsComparator,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor           // NOLINT(bugprone-reserved-identifier)
                > template <
                        bool rotationDecision,                                  // NOLINT(bugprone-reserved-identifier)
                        typename __NodeType,                                    // NOLINT(bugprone-reserved-identifier)
                        typename __ClassType,                                   // NOLINT(bugprone-reserved-identifier)
                        __NodeType * ( *__locateAuxiliary )( __NodeType * ),    // NOLINT(bugprone-reserved-identifier)
                        bool ( *__ifScenario1 )( __NodeType * ),                       // NOLINT(bugprone-reserved-identifier)
                        void ( __ClassType :: *  __rotateS1 )( __NodeType * ),  // NOLINT(bugprone-reserved-identifier)
                        void ( __ClassType :: *  __rotateS2 )( __NodeType * )   // NOLINT(bugprone-reserved-identifier)
                > auto __RedBlackTree <
                        __ElementType,
                        __KeyType,
                        __keyExtractor,
                        __keyLowerComparator,
                        __keyEqualsComparator,
                        __nodeDestructor
                > :: __identifyAndApplyRotationOnInsert (
                        RBTreeNode * pPivot
                ) noexcept -> void {

                    RBTreeNode * pAux = __locateAuxiliary ( pPivot->_pParent->_pParent );

                    if ( __isRed ( pAux ) ) {
                        pPivot->_pParent->_colour = RBTreeNode :: RED;
                        pAux->_colour = RBTreeNode :: BLACK;
                        pPivot->_pParent->_pParent->_colour = RBTreeNode :: RED;
                        pPivot = pPivot->_pParent->_pParent;
                    } else {

                        if ( __ifS1 ( pPivot ) ) {
                            pPivot = pPivot->_pParent;
                            ( this->*__rotateS1 )( pPivot );
                        }

                        pPivot->_pParent->_colour = RBTreeNode :: BLACK;
                        pPivot->_pParent->_pParent->_colour = RBTreeNode :: RED;
                        ( this->*__rotateS2 )( pPivot->_pParent->_pParent );
                    }
                }


                template <
                        typename                                                            __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyType,                 // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,            // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyLowerComparator,      // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyEqualsComparator,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor           // NOLINT(bugprone-reserved-identifier)
                > template <
                        bool rotationDecision,                                              // NOLINT(bugprone-reserved-identifier)
                        typename __NodeType,                                                // NOLINT(bugprone-reserved-identifier)
                        typename __ClassType,                                               // NOLINT(bugprone-reserved-identifier)
                        __NodeType * ( *__locateAuxiliary )( __NodeType * ),                // NOLINT(bugprone-reserved-identifier)
                        __NodeType * ( *__locateReversedAuxiliary )( __NodeType * ),        // NOLINT(bugprone-reserved-identifier)
                        bool ( *__ifScenario1 )( __NodeType * ),                                   // NOLINT(bugprone-reserved-identifier)
                        void ( __ClassType :: *  __rotateS1 )( __NodeType * ),              // NOLINT(bugprone-reserved-identifier)
                        void ( __ClassType :: *  __rotateS2 )( __NodeType * )               // NOLINT(bugprone-reserved-identifier)
                > auto __RedBlackTree <
                        __ElementType,
                        __KeyType,
                        __keyExtractor,
                        __keyLowerComparator,
                        __keyEqualsComparator,
                        __nodeDestructor
                > :: __identifyAndApplyRotationOnDelete (
                        RBTreeNode * pPivot
                ) noexcept -> void {

                    RBTreeNode * pAux = __locateAuxiliary ( pPivot->_pParent );

                    if ( __isRed ( pAux) ) {

                        pAux->_colour = RBTreeNode :: BLACK;
                        pPivot->_pParent->_colour = RBTreeNode :: RED;
                        ( this->*__rotateS1 )( pPivot->_pParent );
                        pAux = __locateAuxiliary ( pPivot->_pParent );
                    }

                    if ( !__isRed ( pAux->_pLeft ) && !__isRed ( pAux->_pRight ) ) {

                        pAux->_colour = RBTreeNode :: RED;
                        pPivot = pPivot->_pParent;
                    } else {

                        if ( !__isRed ( __locateAuxiliary ( pAux ) ) ) {

                            __locateReversedAuxiliary ( pAux )->_colour = RBTreeNode :: BLACK;
                            pAux->_colour = RBTreeNode :: RED;
                            ( this->*__rotateS2 )( pAux );
                            pAux = __locateAuxiliary ( pPivot->_pParent );
                        }

                        pAux->_colour = pPivot->_pParent->_colour;
                        pPivot->_pParent->_colour = RBTreeNode :: BLACK;
                        ( this->*__rotateS1 )( pPivot->_pParent );
                        pPivot = this->_root;
                    }

                    pPivot->_colour = RBTreeNode :: BLACK;
                }

                template <
                        typename                                                            __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyType,                 // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,            // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyLowerComparator,      // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyEqualsComparator,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor           // NOLINT(bugprone-reserved-identifier)
                > auto __RedBlackTree <
                        __ElementType,
                        __KeyType,
                        __keyExtractor,
                        __keyLowerComparator,
                        __keyEqualsComparator,
                        __nodeDestructor
                >  :: __rbt_empty () const -> bool {

                    return this->_root == nullptr;
                }


                template <
                        typename                                                            __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyType,                 // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,            // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyLowerComparator,      // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyEqualsComparator,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor           // NOLINT(bugprone-reserved-identifier)
                > auto __RedBlackTree <
                        __ElementType,
                        __KeyType,
                        __keyExtractor,
                        __keyLowerComparator,
                        __keyEqualsComparator,
                        __nodeDestructor
                > :: __rbt_get (
                        __KeyType const & key,
                        bool * pIsNew
                ) noexcept -> __ElementType & {

                    if ( this->__rbt_empty() ) {
                        this->_root = __rbt_allocateNode();
                        return & this->_data;
                    }

                    RBTreeNode * pAux = this->_root;
                    RBTreeNode * pNewPos;

                    while ( pAux != __RedBlackTree :: __endNode() ) {
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

                    RBTreeNode * pNewNode = __rbt_allocateNode();
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
                        typename                                                            __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyType,                 // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,            // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyLowerComparator,      // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyEqualsComparator,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor           // NOLINT(bugprone-reserved-identifier)
                > auto __RedBlackTree <
                        __ElementType,
                        __KeyType,
                        __keyExtractor,
                        __keyLowerComparator,
                        __keyEqualsComparator,
                        __nodeDestructor
                > :: __rbt_get (
                        KeyType const & key
                ) const noexcept -> ElementType const & {

                    if ( this->__rbt_empty() )
                        return nullptr;

                    RBTreeNode * pSearch = this->_root;

                    while ( pSearch != __RedBlackTree :: __endNode() ) {
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
                        typename                                                            __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyType,                 // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,            // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyLowerComparator,      // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyEqualsComparator,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor           // NOLINT(bugprone-reserved-identifier)
                > auto __RedBlackTree <
                        __ElementType,
                        __KeyType,
                        __keyExtractor,
                        __keyLowerComparator,
                        __keyEqualsComparator,
                        __nodeDestructor
                > :: __rbt_remove (
                        ElementType const & key
                ) noexcept -> void {

                    if ( this->__rbt_empty() )
                        return;

                    RBTreeNode * pToBeDeleted = this->_root;

                    while ( pToBeDeleted != __RedBlackTree :: __endNode() ) {

                        if ( __keyEqualsComparator ( key, __keyExtractor ( pToBeDeleted->_data ) ) ) {
                            bool isOriginallyBlack = __isRed ( pToBeDeleted );
                            RBTreeNode * pBalancePivot;

                            if ( pToBeDeleted->_pLeft == __RedBlackTree :: __endNode() ) {
                                pBalancePivot = pToBeDeleted->_pRight;
                                this->__rbt_transplant ( pToBeDeleted, pToBeDeleted->_pRight );
                            } else {
                                if ( pToBeDeleted->_pRight == __RedBlackTree::__endNode () ) {
                                    pBalancePivot = pToBeDeleted->_pLeft;
                                    this->__rbt_transplant ( pToBeDeleted, pToBeDeleted->_pLeft );
                                } else {
                                    RBTreeNode*pDeletedPlaceholder = pToBeDeleted->_pRight;

                                    while ( pDeletedPlaceholder->_pLeft != __RedBlackTree::__endNode () )
                                        pDeletedPlaceholder = pDeletedPlaceholder->_pLeft;

                                    isOriginallyBlack = __isRed ( pDeletedPlaceholder );
                                    pBalancePivot = pDeletedPlaceholder->_pRight;

                                    if ( pDeletedPlaceholder->_pParent == pToBeDeleted ) {
                                        pBalancePivot = pDeletedPlaceholder;
                                    } else {
                                        this->__rbt_transplant ( pDeletedPlaceholder, pDeletedPlaceholder->_pRight );
                                        pDeletedPlaceholder->_pRight = pToBeDeleted->_pRight;
                                        pDeletedPlaceholder->_pRight->_pParent = pDeletedPlaceholder;
                                    }

                                    this->__rbt_transplant ( pToBeDeleted, pDeletedPlaceholder );
                                    pDeletedPlaceholder->_pLeft = pToBeDeleted->_pLeft;
                                    pDeletedPlaceholder->_pLeft->_pParent = pDeletedPlaceholder;
                                    pDeletedPlaceholder->_colour = pToBeDeleted->_colour;
                                }
                            }

                            this->__rbt_freeNode ( pToBeDeleted );

                            if ( isOriginallyBlack )
                                this->__rbt_deleteReBalance ( pBalancePivot );

                            -- this->_size;

                            return;
                        }

                        if ( __keyLowerComparator ( key, __keyExtractor ( pToBeDeleted->_data ) ) )
                            pToBeDeleted = pToBeDeleted->_pLeft;
                        else
                            pToBeDeleted = pToBeDeleted->_pRight;
                    }
                }

                template <
                        typename                                                            __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyType,                 // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,            // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyLowerComparator,      // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyEqualsComparator,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor           // NOLINT(bugprone-reserved-identifier)
                > auto __RedBlackTree <
                        __ElementType,
                        __KeyType,
                        __keyExtractor,
                        __keyLowerComparator,
                        __keyEqualsComparator,
                        __nodeDestructor
                > :: __rbt_clear () noexcept -> void {

                    cds :: Function < void > _remove_recursively = [&] ( RBTreeNode * _pCurrNode ) {
                        if ( _pCurrNode->_pLeft != __RedBlackTree :: __endNode() )
                            _remove_recursively ( _pCurrNode->_pLeft );
                        if ( _pCurrNode->_pRight != __RedBlackTree :: __endNode() )
                            _remove_recursively ( _pCurrNode->_pRight );
                        this->__rbt_freeNode ( _pCurrNode );
                    };

                    this->_size = 0ULL;

                    _remove_recursively ( this->_root );
                }


                template <
                        typename                                                            __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyType,                 // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,            // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyLowerComparator,      // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyEqualsComparator,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor           // NOLINT(bugprone-reserved-identifier)
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
            }
        }
    }
}

#endif //__CDS_EX_SHARED_RED_BLACK_TREE_IMPL_HPP__