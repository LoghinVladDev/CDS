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
                > template < cds :: utility :: CopyConstructorFunction < __ElementType > __copy // NOLINT(bugprone-reserved-identifier)
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
                > :: __rbt_allocateNode () const noexcept -> RBTreeNode * {

                    RBTreeNode * pNode  = cds :: __hidden :: __impl :: __allocation :: __allocPrimitiveObject < RBTreeNode > ();
                    pNode->_colour      = __RedBlackTreeNode < __ElementType > :: RED;
                    pNode->_pLeft       = pNode->_pRight = pNode->_pParent = __endNode < __ElementType > ();
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

                    __nodeDestructor ( pRemoved->_data );
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

                    if ( pAux->_pLeft != __endNode < __ElementType > () ) {
                        pAux->_pLeft->_pParent = pPivot;
                    }

                    pAux->_pParent = pPivot;

                    if ( pPivot->_pParent == __endNode < __ElementType > () ) {
                        this->_pRoot = pAux;
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

                    if ( pAux->_pRight != __endNode < __ElementType > () ) {
                        pAux->_pLeft = pPivot;
                    }

                    pAux->_pParent = pPivot->_pParent;

                    if ( pPivot->_pParent == __endNode < __ElementType > () ) {
                        this->_pRoot = pAux;
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
                        if ( __isLeftChild ( pPivot ) )
                            __identifyAndApplyRotationOnInsert < true > ( pPivot );
                        else
                            __identifyAndApplyRotationOnInsert < false > ( pPivot );
                    }

                    this->_pRoot->_colour = RBTreeNode :: BLACK;
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

                    if ( pRemoved->_pParent == __endNode < __ElementType > () ) {
                        this->_pRoot = pMovedIn;
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
                //TODO ask about   __identifyAndApplyRotationOnDelete < __isLeftChild ( pPivot ) > ( pPivot );
                    while ( pPivot != this->_pRoot && !__isRed (pPivot ) ) {
                        if ( __isLeftChild ( pPivot ) )
                            __identifyAndApplyRotationOnDelete < true > ( pPivot );
                        else
                            __identifyAndApplyRotationOnDelete < false > ( pPivot );
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

                        if ( __ifScenario1 ( pPivot ) ) {
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
                        pPivot = this->_pRoot;
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

                    return this->_pRoot == nullptr;
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
                        __KeyType const &   key,
                        bool            *   pIsNew
                ) noexcept -> __ElementType * {

                    if ( this->__rbt_empty() ) {
                        this->_pRoot = __rbt_allocateNode();
                        return & this->_pRoot->_data;
                    }

                    RBTreeNode * pAux = this->_pRoot;
                    RBTreeNode * pNewPos;

                    while ( pAux != __endNode < __ElementType > () ) {
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
                        __KeyType const & key
                ) const noexcept -> __ElementType const & {

                    if ( this->__rbt_empty() )
                        return nullptr;

                    RBTreeNode * pSearch = this->_pRoot;

                    while ( pSearch != __endNode < __ElementType > () ) {
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
                > :: __rbt_removeAt (
                        RBTreeNode * pToBeRemoved
                ) noexcept -> bool {

                    bool isOriginallyBlack = __isRed ( pToBeRemoved );
                    RBTreeNode * pBalancePivot;

                    if ( pToBeRemoved->_pLeft == __endNode < __ElementType > () ) {
                        pBalancePivot = pToBeRemoved->_pRight;
                        this->__rbt_transplant ( pToBeRemoved, pToBeRemoved->_pRight );
                    } else {
                        if ( pToBeRemoved->_pRight == __endNode < __ElementType >  () ) {
                            pBalancePivot = pToBeRemoved->_pLeft;
                            this->__rbt_transplant ( pToBeRemoved, pToBeRemoved->_pLeft );
                        } else {
                            RBTreeNode*pDeletedPlaceholder = pToBeRemoved->_pRight;

                            while ( pDeletedPlaceholder->_pLeft != __endNode < __ElementType >  () )
                                pDeletedPlaceholder = pDeletedPlaceholder->_pLeft;

                            isOriginallyBlack = __isRed ( pDeletedPlaceholder );
                            pBalancePivot = pDeletedPlaceholder->_pRight;

                            if ( pDeletedPlaceholder->_pParent == pToBeRemoved ) {
                                pBalancePivot = pDeletedPlaceholder;
                            } else {
                                this->__rbt_transplant ( pDeletedPlaceholder, pDeletedPlaceholder->_pRight );
                                pDeletedPlaceholder->_pRight = pToBeRemoved->_pRight;
                                pDeletedPlaceholder->_pRight->_pParent = pDeletedPlaceholder;
                            }

                            this->__rbt_transplant ( pToBeRemoved, pDeletedPlaceholder );
                            pDeletedPlaceholder->_pLeft = pToBeRemoved->_pLeft;
                            pDeletedPlaceholder->_pLeft->_pParent = pDeletedPlaceholder;
                            pDeletedPlaceholder->_colour = pToBeRemoved->_colour;
                        }
                    }

                    this->__rbt_freeNode ( pToBeRemoved );

                    if ( isOriginallyBlack )
                        this->__rbt_deleteReBalance ( pBalancePivot );

                    -- this->_size;

                    return true;
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
                        __ElementType const & key
                ) noexcept -> bool {

                    if ( this->__rbt_empty() )
                        return false;

                    RBTreeNode * pToBeRemoved = this->_pRoot;

                    while ( pToBeRemoved != __endNode < __ElementType > () ) {

                        if ( __keyEqualsComparator ( key, __keyExtractor ( pToBeRemoved->_data ) ) ) {
                            this->__rbt_removeAt ( pToBeRemoved );
                            return true;
                        }

                        if ( __keyLowerComparator ( key, __keyExtractor ( pToBeRemoved->_data ) ) )
                            pToBeRemoved = pToBeRemoved->_pLeft;
                        else
                            pToBeRemoved = pToBeRemoved->_pRight;
                    }

                    return false;
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
                > :: __rbt_removeIterator (
                    AbstractTreeConstIterator < __ElementType > const & iterator
                ) noexcept -> bool {

                    auto pToBeRemoved = const_cast < RBTreeNode * > ( iterator._pCurrentNode );

                    if ( pToBeRemoved == nullptr ) {
                        return false;
                    }

                    return this->__rbt_removeAt ( pToBeRemoved );
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

                    cds :: Function < void ( RBTreeNode * ) > _remove_recursively = [&] ( RBTreeNode * _pCurrNode ) {
                        if ( _pCurrNode->_pLeft != __endNode < __ElementType > () )
                            _remove_recursively ( _pCurrNode->_pLeft );
                        if ( _pCurrNode->_pRight != __endNode < __ElementType > () )
                            _remove_recursively ( _pCurrNode->_pRight );
                        this->__rbt_freeNode ( _pCurrNode );
                    };

                    this->_size = 0ULL;

                    _remove_recursively ( this->_pRoot );
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
                > :: __rbt_findIteratorConst (
                        __KeyType const & key
                ) const noexcept -> __rbt_ConstIterator {

                    if ( this->__rbt_empty() ) {
                        return __rbt_ConstIterator();
                    }

                    auto pSearch = this->_pRoot;
                    while ( pSearch != __endNode < __ElementType > () ) {
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


                template <
                        typename                                                            __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyType,                 // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,            // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyLowerComparator,      // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyEqualsComparator,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor           // NOLINT(bugprone-reserved-identifier)
                > template <
                        cds :: utility :: CopyConstructorFunction < __ElementType > __copy                             // NOLINT(bugprone-reserved-identifier)
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

                    if ( this == &tree ) {
                        return;
                    }

                    this->__rbt_clear();
                    this->template __rbt_copyCleared < __copy > ( tree );
                }


                template <
                        typename                                                            __ElementType,             // NOLINT(bugprone-reserved-identifier)
                        typename                                                            __KeyType,                 // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ExtractorFunction < __ElementType, __KeyType >    __keyExtractor,            // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyLowerComparator,      // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: ComparisonFunction < __ElementType >              __keyEqualsComparator,     // NOLINT(bugprone-reserved-identifier)
                        cds :: utility :: DestructorFunction < __ElementType >              __nodeDestructor           // NOLINT(bugprone-reserved-identifier)
                > template <
                        cds :: utility :: CopyConstructorFunction < __ElementType > __copy                             // NOLINT(bugprone-reserved-identifier)
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

                    cds :: Function < void ( RBTreeNode *, RBTreeNode * ) > copyNodeRecursively = [ &copyNodeRecursively , this] (
                            RBTreeNode * pDestination,
                            RBTreeNode * pSource
                    ) -> void {

                        __copy ( pDestination->_data, pSource->_data );

                        if ( pSource->_pLeft != __endNode < __ElementType > () ) {
                            pDestination->_pLeft = this->__rbt_allocateNode();
                            copyNodeRecursively ( pDestination->_pLeft, pSource->_pLeft );
                        }

                        if ( pSource->_pRight != __endNode < __ElementType > () ) {
                            pDestination->_pRight = this->__rbt_allocateNode();
                            copyNodeRecursively ( pDestination->_pRight, pSource->_pRight );
                        }
                    };

                    this->_pRoot = this->__rbt_allocateNode();
                    copyNodeRecursively ( this->_pRoot, tree._pRoot );
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
                > :: __rbt_move (
                        __RedBlackTree && tree
                ) noexcept -> void {

                    if ( this == &tree ) {
                        return;
                    }

                    this->__rbt_clear();
                    this->__rbt_moveCleared( std :: move ( tree ) );
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
                > :: __rbt_moveCleared (
                        __RedBlackTree && tree
                ) noexcept -> void {

                    this->_size = cds :: exchange ( tree._size, 0ULL );
                    this->_pRoot = cds :: exchange ( tree._pRoot, nullptr );
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
                > :: __rbt_begin () noexcept -> __rbt_Iterator {

                    if ( this->_pRoot == nullptr ) {
                        return __rbt_Iterator ( nullptr, nullptr );
                    }

                    RBTreeNode * pBegin = this->_pRoot;
                    while ( pBegin->_pLeft != __endNode < __ElementType > () ) {
                        pBegin = pBegin->_pLeft;
                    }

                    return __rbt_Iterator ( this->_pRoot, pBegin );
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
                > :: __rbt_end () noexcept -> __rbt_Iterator {

                    return __rbt_Iterator ( this->_pRoot, nullptr );
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
                > :: __rbt_rbegin () noexcept -> __rbt_ReverseIterator {

                    if ( this->_pRoot == nullptr ) {
                        return __rbt_ReverseIterator ( nullptr, nullptr );
                    }

                    RBTreeNode * prEnd = this->_pRoot;
                    while ( prEnd->_pRight != __endNode < __ElementType > () ) {
                        prEnd = prEnd->_pRight;
                    }

                    return __rbt_ReverseIterator ( this->_pRoot, prEnd );
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
                > :: __rbt_rend () noexcept -> __rbt_ReverseIterator {

                    return __rbt_ReverseIterator ( this->_pRoot, nullptr );
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
                > :: __rbt_cbegin () const noexcept -> __rbt_ConstIterator {

                    if ( this->_pRoot == nullptr ) {
                        return __rbt_ConstIterator ( nullptr, nullptr );
                    }

                    RBTreeNode * pcBegin = this->_pRoot;
                    while ( pcBegin->_pLeft != __endNode < __ElementType > () ) {
                        pcBegin = pcBegin->_pLeft;
                    }

                    return __rbt_ConstIterator ( this->_pRoot, pcBegin );
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
                > :: __rbt_cend () const noexcept -> __rbt_ConstIterator {

                    return __rbt_ConstIterator ( this->_pRoot, nullptr );
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
                > :: __rbt_crbegin () const noexcept -> __rbt_ReverseConstIterator {

                    if ( this->_pRoot == nullptr ) {
                        return __rbt_ReverseConstIterator ( nullptr, nullptr );
                    }

                    RBTreeNode * pcrBegin = this->_pRoot;
                    while ( pcrBegin->_pRight != __endNode < __ElementType > () ) {
                        pcrBegin = pcrBegin->_pRight;
                    }

                    return __rbt_ReverseConstIterator ( this->_pRoot, pcrBegin );
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
                > :: __rbt_crend () const noexcept -> __rbt_ReverseConstIterator {

                    return __rbt_ReverseConstIterator ( this->_pRoot, nullptr );
                }
            }
        }
    }
}

#endif //__CDS_EX_SHARED_RED_BLACK_TREE_IMPL_HPP__