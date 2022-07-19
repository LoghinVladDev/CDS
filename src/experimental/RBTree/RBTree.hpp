//
// Created by stefan on 02.07.2022.
//

#ifndef CDS_RBTREE_H
#define CDS_RBTREE_H
#include <CDS/Object>
#include "./../src/shared/Node.hpp"
#include "./../src/shared/memory/PrimitiveAllocation.hpp"
namespace cds {             // NOLINT(modernize-concat-nested-namespaces)
    namespace __hidden {
        namespace __impl {

            template < typename __ElementType >     // NOLINT(bugprone-reserved-identifier)
            inline auto __getLeftNode ( __RBTreeNode < __ElementType > * pNode ) -> __RBTreeNode < __ElementType > * {      // NOLINT(bugprone-reserved-identifier)
                return pNode->_pLeft;
            }

            template < typename __ElementType >     // NOLINT(bugprone-reserved-identifier)
            inline auto __getRightNode ( __RBTreeNode < __ElementType > * pNode ) -> __RBTreeNode < __ElementType > * {     // NOLINT(bugprone-reserved-identifier)
                return pNode->_pRight;
            }

            template < typename __ElementType >     // NOLINT(bugprone-reserved-identifier)
            static auto __isLeftChild ( __RBTreeNode < __ElementType > * pNode ) -> bool {     // NOLINT(bugprone-reserved-identifier)
                return pNode->_pParent->_pLeft == pNode;
            }

            template < typename __ElementType >     // NOLINT(bugprone-reserved-identifier)
            static auto __isRightChild ( __RBTreeNode < __ElementType > * pNode ) -> bool {     // NOLINT(bugprone-reserved-identifier)
                return pNode->_pParent->_pRight == pNode;
            }

            template < typename __ElementType >     // NOLINT(bugprone-reserved-identifier)
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
            >
            class RBTree : public Object {

            private:
                using ElementType       =       __ElementType;
                using RBTreeNode        =       __RBTreeNode < __ElementType >;

            private:
                static auto pNull = __allocation :: __allocPrimitiveObject < RBTreeNode * > ();


            private:


            private:
                RBTreeNode * root { nullptr };

                auto __allocateNode ( ElementType const & ) -> RBTreeNode *;    // NOLINT(bugprone-reserved-identifier)

                auto __leftRotate ( RBTreeNode * ) -> void;                     // NOLINT(bugprone-reserved-identifier)

                auto __rightRotate ( RBTreeNode * ) -> void;                    // NOLINT(bugprone-reserved-identifier)

                auto __insertReBalance ( RBTreeNode * ) -> void;                // NOLINT(bugprone-reserved-identifier)

                auto __transplant ( RBTreeNode *, RBTreeNode * ) -> void;       // NOLINT(bugprone-reserved-identifier)

                auto __deleteReBalance ( RBTreeNode * ) -> void;                    // NOLINT(bugprone-reserved-identifier)

                template <
                        bool rotationDecision,
                        RBTreeNode * ( *__locateAuxiliary )( RBTreeNode * ) = rotationDecision ? &__getRightNode < ElementType >        // NOLINT(bugprone-reserved-identifier)
                                                                                            : &__getLeftNode < ElementType >,
                        bool ( *__ifS1 )( RBTreeNode * ) = rotationDecision ? &__isRightChild < ElementType > :                         // NOLINT(bugprone-reserved-identifier)
                                                                            &__isLeftChild < ElementType >,
                        void ( RBTree :: *  __rotateS1 )( RBTreeNode * ) = rotationDecision ? & RBTree :: __leftRotate                  // NOLINT(bugprone-reserved-identifier)
                                                                                        : & RBTree :: __rightRotate,
                        void ( RBTree :: *  __rotateS2 )( RBTreeNode * ) = rotationDecision ? & RBTree :: __rightRotate                 // NOLINT(bugprone-reserved-identifier)
                                                                                        : & RBTree :: __leftRotate
                >
                auto __identifyAndApplyRotationOnInsert (    // NOLINT(bugprone-reserved-identifier)
                        RBTreeNode * pPivot
                ) noexcept -> void;

                template <
                        bool rotationDecision,
                        RBTreeNode * ( *__locateAuxiliary )( RBTreeNode * ) = rotationDecision ? &__getRightNode < ElementType >        // NOLINT(bugprone-reserved-identifier)
                                                                                               : &__getLeftNode < ElementType >,
                        RBTreeNode * ( *__locateReversedAuxiliary )( RBTreeNode * ) = rotationDecision ? &__getLeftNode < ElementType >        // NOLINT(bugprone-reserved-identifier)
                                                                                               : &__getRightNode < ElementType >,
                        bool ( *__ifS1 )( RBTreeNode * ) = rotationDecision ? &__isRightChild < ElementType > :                         // NOLINT(bugprone-reserved-identifier)
                                                           &__isLeftChild < ElementType >,
                        void ( RBTree :: *  __rotateS1 )( RBTreeNode * ) = rotationDecision ? & RBTree :: __leftRotate                  // NOLINT(bugprone-reserved-identifier)
                                                                                            : & RBTree :: __rightRotate,
                        void ( RBTree :: *  __rotateS2 )( RBTreeNode * ) = rotationDecision ? & RBTree :: __rightRotate                 // NOLINT(bugprone-reserved-identifier)
                                                                                            : & RBTree :: __leftRotate
                >
                auto __identifyAndApplyRotationOnDelete (    // NOLINT(bugprone-reserved-identifier)
                        RBTreeNode * pPivot
                ) noexcept -> void;

            public:
                RBTree() = default;

                auto insert ( ElementType const & ) -> void;

                auto remove ( ElementType const & ) -> void;

                auto find ( ElementType const & ) -> RBTreeNode *;
            };


            template <
                    typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                    typename __KeyType,                 // NOLINT(bugprone-reserved-identifier)
                    typename __KeyExtractor,            // NOLINT(bugprone-reserved-identifier)
                    typename __KeyLowerComparator,      // NOLINT(bugprone-reserved-identifier)
                    typename __KeyEqualsComparator,     // NOLINT(bugprone-reserved-identifier)
                    typename __ElementTypeDestruct      // NOLINT(bugprone-reserved-identifier)
            >
            auto RBTree <
                    __ElementType,
                    __KeyType,
                    __KeyExtractor,
                    __KeyLowerComparator,
                    __KeyEqualsComparator,
                    __ElementTypeDestruct
            > :: __allocateNode (
                    const ElementType &
                ) -> RBTreeNode * {
                    RBTreeNode * p = __allocation :: __allocPrimitiveObject < RBTreeNode > ();
                    p->_colour = __RBTreeNode < ElementType > :: RED;
                    p->_pLeft = p->_pRight = p->_pParent = pNull;
                    return p;
            }


            template <
                    typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                    typename __KeyType,                 // NOLINT(bugprone-reserved-identifier)
                    typename __KeyExtractor,            // NOLINT(bugprone-reserved-identifier)
                    typename __KeyLowerComparator,      // NOLINT(bugprone-reserved-identifier)
                    typename __KeyEqualsComparator,     // NOLINT(bugprone-reserved-identifier)
                    typename __ElementTypeDestruct      // NOLINT(bugprone-reserved-identifier)
            >
            auto RBTree <
                    __ElementType,
                    __KeyType,
                    __KeyExtractor,
                    __KeyLowerComparator,
                    __KeyEqualsComparator,
                    __ElementTypeDestruct
            > :: __leftRotate ( RBTreeNode * pPivot ) -> void {
                RBTreeNode * pAux = pPivot->_pRight;
                pPivot->_pRight = pAux->_pLeft;
                if ( pAux->_pLeft != pNull )
                    pAux->_pLeft->_pParent = pPivot;
                pAux->_pParent = pPivot;
                if ( pPivot->_pParent == pNull )
                    this->root = pAux;
                else
                    if (__isLeftChild ( pPivot ) )
                        pPivot->_pParent->_pLeft = pAux;
                    else
                        pPivot->_pParent->_pRight = pAux;
                pAux->_pLeft = pPivot;
                pPivot->_pParent = pAux;
            }


            template <
                    typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                    typename __KeyType,                 // NOLINT(bugprone-reserved-identifier)
                    typename __KeyExtractor,            // NOLINT(bugprone-reserved-identifier)
                    typename __KeyLowerComparator,      // NOLINT(bugprone-reserved-identifier)
                    typename __KeyEqualsComparator,     // NOLINT(bugprone-reserved-identifier)
                    typename __ElementTypeDestruct      // NOLINT(bugprone-reserved-identifier)
            >
            auto RBTree <
                    __ElementType,
                    __KeyType,
                    __KeyExtractor,
                    __KeyLowerComparator,
                    __KeyEqualsComparator,
                    __ElementTypeDestruct
            > :: __rightRotate ( RBTreeNode * pPivot ) -> void {
                RBTreeNode * pAux = pPivot->_pLeft;
                pPivot->_pLeft = pAux->_pRight;
                if ( pAux->_pRight != pNull )
                    pAux->_pLeft = pPivot;
                pAux->_pParent = pPivot->_pParent;
                if ( pPivot->_pParent == pNull )
                    this->root = pAux;
                else
                    if (__isLeftChild ( pPivot ) )
                        pPivot->_pParent->_pLeft = pAux;
                    else
                        pPivot->_pParent->_pRight = pAux;
                pAux->_pRight = pPivot;
                pPivot->_pParent = pAux;
            }

            template <
                    typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                    typename __KeyType,                 // NOLINT(bugprone-reserved-identifier)
                    typename __KeyExtractor,            // NOLINT(bugprone-reserved-identifier)
                    typename __KeyLowerComparator,      // NOLINT(bugprone-reserved-identifier)
                    typename __KeyEqualsComparator,     // NOLINT(bugprone-reserved-identifier)
                    typename __ElementTypeDestruct      // NOLINT(bugprone-reserved-identifier)
            >
            auto RBTree <
                    __ElementType,
                    __KeyType,
                    __KeyExtractor,
                    __KeyLowerComparator,
                    __KeyEqualsComparator,
                    __ElementTypeDestruct
            > :: __insertReBalance ( RBTreeNode * pPivot ) -> void {
                while ( __isRed ( pPivot->_pParent ) ) {
                    __identifyAndApplyRotationOnInsert < __isLeftChild (pPivot ) > ( pPivot );
                }
                this->root->_colour = RBTreeNode :: BLACK;
            }

            template <
                    typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                    typename __KeyType,                 // NOLINT(bugprone-reserved-identifier)
                    typename __KeyExtractor,            // NOLINT(bugprone-reserved-identifier)
                    typename __KeyLowerComparator,      // NOLINT(bugprone-reserved-identifier)
                    typename __KeyEqualsComparator,     // NOLINT(bugprone-reserved-identifier)
                    typename __ElementTypeDestruct      // NOLINT(bugprone-reserved-identifier)
            >
            template <
                    bool rotationDecision,
                    typename RBTree <
                            __ElementType,
                            __KeyType,
                            __KeyExtractor,
                            __KeyLowerComparator,
                            __KeyEqualsComparator,
                            __ElementTypeDestruct
                            > :: RBTreeNode * ( *__locateAuxiliary )(       // NOLINT(bugprone-reserved-identifier)

                            typename RBTree <
                                    __ElementType,
                                    __KeyType,
                                    __KeyExtractor,
                                    __KeyLowerComparator,
                                    __KeyEqualsComparator,
                                    __ElementTypeDestruct
                            > :: RBTreeNode * ),
                    bool ( *__ifS1 )(                                       // NOLINT(bugprone-reserved-identifier)
                            typename RBTree <
                                    __ElementType,
                                    __KeyType,
                                    __KeyExtractor,
                                    __KeyLowerComparator,
                                    __KeyEqualsComparator,
                                    __ElementTypeDestruct
                            > :: RBTreeNode *),
                    void ( RBTree <
                            __ElementType,
                            __KeyType,
                            __KeyExtractor,
                            __KeyLowerComparator,
                            __KeyEqualsComparator,
                            __ElementTypeDestruct
                    > :: *  __rotateS1 )( typename RBTree <                 // NOLINT(bugprone-reserved-identifier)
                            __ElementType,
                            __KeyType,
                            __KeyExtractor,
                            __KeyLowerComparator,
                            __KeyEqualsComparator,
                            __ElementTypeDestruct
                    > :: RBTreeNode *),
                    void ( RBTree <
                            __ElementType,
                            __KeyType,
                            __KeyExtractor,
                            __KeyLowerComparator,
                            __KeyEqualsComparator,
                            __ElementTypeDestruct
                    > :: *  __rotateS2 )( typename RBTree <                 // NOLINT(bugprone-reserved-identifier)
                            __ElementType,
                            __KeyType,
                            __KeyExtractor,
                            __KeyLowerComparator,
                            __KeyEqualsComparator,
                            __ElementTypeDestruct
                    > :: RBTreeNode * )
            >
            auto RBTree <
                    __ElementType,
                    __KeyType,
                    __KeyExtractor,
                    __KeyLowerComparator,
                    __KeyEqualsComparator,
                    __ElementTypeDestruct
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
                    typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                    typename __KeyType,                 // NOLINT(bugprone-reserved-identifier)
                    typename __KeyExtractor,            // NOLINT(bugprone-reserved-identifier)
                    typename __KeyLowerComparator,      // NOLINT(bugprone-reserved-identifier)
                    typename __KeyEqualsComparator,     // NOLINT(bugprone-reserved-identifier)
                    typename __ElementTypeDestruct      // NOLINT(bugprone-reserved-identifier)
            >
            auto RBTree <
                    __ElementType,
                    __KeyType,
                    __KeyExtractor,
                    __KeyLowerComparator,
                    __KeyEqualsComparator,
                    __ElementTypeDestruct
            > :: __transplant ( RBTreeNode * pRemoved, RBTreeNode * pMovedIn ) -> void {
                if ( pRemoved->_pParent == pNull )
                    this->root = pMovedIn;
                else
                    if ( __isLeftChild ( pRemoved ) )
                        pRemoved->_pParent->_pLeft = pRemoved;
                    else
                        pRemoved->_pParent->_pRight = pRemoved;
                pMovedIn->_pParent = pRemoved->_pParent;
            }


            template <
                    typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                    typename __KeyType,                 // NOLINT(bugprone-reserved-identifier)
                    typename __KeyExtractor,            // NOLINT(bugprone-reserved-identifier)
                    typename __KeyLowerComparator,      // NOLINT(bugprone-reserved-identifier)
                    typename __KeyEqualsComparator,     // NOLINT(bugprone-reserved-identifier)
                    typename __ElementTypeDestruct      // NOLINT(bugprone-reserved-identifier)
            >
            auto RBTree <
                    __ElementType,
                    __KeyType,
                    __KeyExtractor,
                    __KeyLowerComparator,
                    __KeyEqualsComparator,
                    __ElementTypeDestruct
            > :: __deleteReBalance ( RBTreeNode * pPivot ) -> void {
                while ( pPivot != this->root && !__isRed (pPivot ) )
                    __identifyAndApplyRotationOnDelete < __isLeftChild ( pPivot ) >( pPivot );
            }


            template <
                    typename __ElementType,             // NOLINT(bugprone-reserved-identifier)
                    typename __KeyType,                 // NOLINT(bugprone-reserved-identifier)
                    typename __KeyExtractor,            // NOLINT(bugprone-reserved-identifier)
                    typename __KeyLowerComparator,      // NOLINT(bugprone-reserved-identifier)
                    typename __KeyEqualsComparator,     // NOLINT(bugprone-reserved-identifier)
                    typename __ElementTypeDestruct      // NOLINT(bugprone-reserved-identifier)
            >
            template <
                    bool rotationDecision,
                    typename RBTree <
                            __ElementType,
                            __KeyType,
                            __KeyExtractor,
                            __KeyLowerComparator,
                            __KeyEqualsComparator,
                            __ElementTypeDestruct
                    > :: RBTreeNode * ( *__locateAuxiliary )(       // NOLINT(bugprone-reserved-identifier)
                            typename RBTree <
                                    __ElementType,
                                    __KeyType,
                                    __KeyExtractor,
                                    __KeyLowerComparator,
                                    __KeyEqualsComparator,
                                    __ElementTypeDestruct
                            > :: RBTreeNode * ),
                    typename RBTree <
                            __ElementType,
                            __KeyType,
                            __KeyExtractor,
                            __KeyLowerComparator,
                            __KeyEqualsComparator,
                            __ElementTypeDestruct
                    > :: RBTreeNode * ( *__locateReversedAuxiliary )(       // NOLINT(bugprone-reserved-identifier)
                            typename RBTree <
                                    __ElementType,
                                    __KeyType,
                                    __KeyExtractor,
                                    __KeyLowerComparator,
                                    __KeyEqualsComparator,
                                    __ElementTypeDestruct
                            > :: RBTreeNode * ),
                    bool ( *__ifS1 )(                                       // NOLINT(bugprone-reserved-identifier)
                            typename RBTree <
                                    __ElementType,
                                    __KeyType,
                                    __KeyExtractor,
                                    __KeyLowerComparator,
                                    __KeyEqualsComparator,
                                    __ElementTypeDestruct
                            > :: RBTreeNode *),
                    void ( RBTree <
                            __ElementType,
                            __KeyType,
                            __KeyExtractor,
                            __KeyLowerComparator,
                            __KeyEqualsComparator,
                            __ElementTypeDestruct
                    > :: *  __rotateS1 )( typename RBTree <                 // NOLINT(bugprone-reserved-identifier)
                            __ElementType,
                            __KeyType,
                            __KeyExtractor,
                            __KeyLowerComparator,
                            __KeyEqualsComparator,
                            __ElementTypeDestruct
                    > :: RBTreeNode *),
                    void ( RBTree <
                            __ElementType,
                            __KeyType,
                            __KeyExtractor,
                            __KeyLowerComparator,
                            __KeyEqualsComparator,
                            __ElementTypeDestruct
                    > :: *  __rotateS2 )( typename RBTree <                 // NOLINT(bugprone-reserved-identifier)
                            __ElementType,
                            __KeyType,
                            __KeyExtractor,
                            __KeyLowerComparator,
                            __KeyEqualsComparator,
                            __ElementTypeDestruct
                    > :: RBTreeNode * )
            >
            auto RBTree <
                    __ElementType,
                    __KeyType,
                    __KeyExtractor,
                    __KeyLowerComparator,
                    __KeyEqualsComparator,
                    __ElementTypeDestruct
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
                }
                else {
                    if ( !__isRed ( __locateAuxiliary ( pAux ) ) ) {
                        __locateReversedAuxiliary ( pAux )->_colour = RBTreeNode :: BLACK;
                        pAux->_colour = RBTreeNode :: RED;
                        ( this->*__rotateS2 )( pAux );
                        pAux = __locateAuxiliary ( pPivot->_pParent );
                    }
                    pAux->_colour = pPivot->_pParent->_colour;
                    pPivot->_pParent->_colour = RBTreeNode :: BLACK;
                    ( this->*__rotateS1 )( pPivot->_pParent );
                    pPivot = this->root;
                }
                pPivot->_colour = RBTreeNode :: BLACK;
            }
        }
    }
}

#endif //CDS_RBTREE_H
