//
// Created by stefan on 02.07.2022.
//

#ifndef CDS_RBTREE_H
#define CDS_RBTREE_H
#include <CDS/Object>

namespace cds {

    template <typename DataType>
    class RBTree : public Object {

    public:
        class RBTreeNode {
        public:
            using Node =  RBTreeNode;
            using NodePointer = Node *;
            enum Colour { RED, BLACK };
        private:
            NodePointer left { nullptr };
            NodePointer right { nullptr };
            NodePointer parent { nullptr };
            DataType key = 0;
            Colour colour = BLACK;
            bool leftChild = false;
            bool leaf = true;
        public:
            RBTreeNode () = default;
            RBTreeNode ( DataType const &, Colour, bool, bool = true );
            ~RBTreeNode() = default;
            auto getLeft () -> RBTreeNode *;
            auto getRight () -> RBTreeNode *;
            auto getParent () -> RBTreeNode *;
            auto getKey () -> DataType;
            auto getColour () -> Colour;
            auto setColour ( Colour ) -> void;
            auto isLeftChild () -> bool;
            auto insertLeft ( DataType const &, Colour = RED ) -> RBTreeNode*;
            auto insertRight ( DataType const &, Colour = RED ) -> RBTreeNode*;
            auto deleteLeft () -> void;
            auto deleteRight () -> void;
        };
    private:
        RBTreeNode* root { nullptr };
        auto leftRotate ( RBTreeNode* x ) -> void {
            RBTreeNode * y = x->getRight();
            x->getRight() = y->getLeft();
            if ( y->getLeft() != nullptr )
                y->getLeft()->getParent() = x;
            y->getParent() = x->getParent();
            if ( x->getParent() == nullptr )
                this->root = y;
            else
            if ( x->isLeftChild )
                x->getParent()->getLeft() = y;
            else
                x->getParent()->getRight() = y;
            y->getLeft() = x;
            x->getParent() = y;
        }
        auto rightRotate ( RBTreeNode * x ) -> void {
            RBTreeNode* y = x->getLeft();
            x->getLeft() = y->getRight();
            if ( y->getRight() != nullptr )
                y->getRight()->getParent() = x;
            y->getParent() = x->getParent();
            if ( x->getParent() == nullptr )
                this->root = y;
            else
            if ( x->isLeftChild )
                x->getParent()->getLeft() = y;
            else
                x->getParent()->getRight() = y;
            x->getParent() = y;
            y->getRight() = x;
        }

    public:
        RBTree() = default;
        auto insert ( DataType const & value ) -> void {
            if ( this->root == nullptr ) {
                this->root = new RBTreeNode ( value, RBTreeNode :: BLACK, false, false );
            }
            RBTreeNode * y;
            RBTreeNode * x = this->root;
            while ( x != nullptr ) {
                y = x;
                if ( value < x->getKey() )
                    x = x->getLeft();
                else
                    x = x->getRight();
            }
            if ( value < y->getKey() )
                x = y->insertLeft ( value );
            else
                x = y->insertRight ( value );
            this->insertFixup ( x );
        }
        auto insertFixup ( RBTreeNode * x ) -> void {
            while ( x->getParent() != nullptr && x->getParent()->getColour() == RBTreeNode :: RED ) {
                if ( x->getParent()->isLeftChild() ) {
                    RBTreeNode* y = x->getParent()->getParent()->getRight();
                    if ( y->getColour() == RBTreeNode :: RED ) {
                        x->getParent()->setColour( RBTreeNode :: BLACK );
                        y->setColour (RBTreeNode :: BLACK );
                        x->getParent()->getParent()->setColour ( RBTreeNode :: BLACK );
                        x = x->getParent()->getParent();
                    }
                    else {
                        if ( !x->isLeftChild() ) {
                            x = x->getParent ();
                            this->leftRotate ( x );
                        }
                        x->getParent()->setColour ( RBTreeNode :: BLACK );
                        x->getParent()->getParent()->setColour ( RBTreeNode :: RED );
                        this->rightRotate ( x->getParent()->getParent() );
                    }
                }
                else {
                    RBTreeNode* y = x->getParent()->getParent()->getLeft();
                    if ( y->getColour() == RBTreeNode :: RED ) {
                        x->getParent()->setColour( RBTreeNode :: BLACK );
                        y->setColour (RBTreeNode :: BLACK );
                        x->getParent()->getParent()->setColour ( RBTreeNode :: BLACK );
                        x = x->getParent()->getParent();
                    }
                    else {
                        if ( x->isLeftChild() ) {
                            x = x->getParent ();
                            this->rigtRotate ( x );
                        }
                        x->getParent()->setColour ( RBTreeNode :: BLACK );
                        x->getParent()->getParent()->setColour ( RBTreeNode :: RED );
                        this->leftRotate ( x->getParent()->getParent() );
                    }
                }
            }
        }
    };

    template <typename DataType>
    RBTree<DataType> :: RBTreeNode :: RBTreeNode ( DataType const & key, Colour colour, bool leftChild, bool leaf ) : key ( key ), colour ( colour ), leftChild ( leftChild), leaf ( leaf ) {};

    template <typename DataType>
    auto RBTree<DataType> :: RBTreeNode :: getLeft () -> RBTreeNode* {
        return this->left;
    }

    template <typename DataType>
    auto RBTree<DataType> :: RBTreeNode :: getRight () -> RBTreeNode* {
        return this->right;
    }

    template <typename DataType>
    auto RBTree<DataType> :: RBTreeNode :: getParent () -> RBTreeNode* {
        return this->parent;
    }

    template <typename DataType>
    auto RBTree<DataType> :: RBTreeNode ::getKey () -> DataType {
        return this->key;
    }

    template <typename DataType>
    auto RBTree<DataType> :: RBTreeNode :: getColour () -> Colour {
        return this->colour;
    }

    template <typename DataType>
    auto RBTree<DataType> :: RBTreeNode :: setColour ( Colour col) -> void {
        this->colour = col;
    }

    template <typename DataType>
    auto RBTree<DataType> :: RBTreeNode :: isLeftChild () -> bool {
        return this->leftChild;
    }

    template <typename DataType>
    auto RBTree<DataType> :: RBTreeNode :: insertLeft ( DataType const & value, Colour col ) -> RBTreeNode* {
        if ( this->left == nullptr )
            this->left = new RBTreeNode ( value, col, true );
        return this->left;
    }

    template <typename DataType>
    auto RBTree<DataType> :: RBTreeNode :: insertRight ( DataType const & value, Colour col ) -> RBTreeNode* {
        if ( this->right == nullptr )
            this->right = new RBTreeNode ( value, col, false );
        return this->right;
    }

    template <typename DataType>
    auto RBTree<DataType> :: RBTreeNode :: deleteLeft () -> void {
        if ( this->left->isLeaf )
            delete this->left;
    }

    template <typename DataType>
    auto RBTree<DataType> :: RBTreeNode :: deleteRight () -> void {
        if ( this->right->isLeaf )
            delete this->right;
    }

}

#endif //CDS_RBTREE_H
