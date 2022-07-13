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
            using Node = RBTreeNode;
            using NodePointer = Node *;
            using NodePointerRefference = NodePointer &;
            enum Colour { RED, BLACK };
        private:
            NodePointer parent { nullptr };
            NodePointer left { nullptr };
            NodePointer right { nullptr };
            Colour colour { RED };
            DataType key { 0 };
        public:
            RBTreeNode() = default;
            explicit RBTreeNode( DataType const & );
            auto getLeft () -> NodePointerRefference;
            auto getRight () -> NodePointerRefference;
            auto getParent () -> NodePointerRefference;
            auto getColour () -> Colour;
            auto getKey () -> DataType const &;
            auto setKey ( DataType const & ) -> void;
            auto setColour ( Colour ) -> void;
            auto insertLeft ( DataType const & ) -> NodePointerRefference;
            auto insertRight ( DataType const & ) -> NodePointerRefference;
            auto isRed () -> bool;
            auto isLeftChild () -> bool;

        };
    private:
        RBTreeNode * root { nullptr };
        auto leftRotate ( RBTreeNode * ) -> void;
        auto rightRotate ( RBTreeNode * ) -> void;
        auto insertFixup ( RBTreeNode * ) -> void;
        auto transplant ( RBTreeNode *, RBTreeNode * ) -> void;
        auto deleteFixup ( RBTreeNode* ) -> void;
    public:
        RBTree () = default;
        auto Insert ( DataType const & ) -> void;
        auto Delete ( DataType const & ) -> void;
        auto Find ( DataType const & ) -> RBTreeNode *;
    };
    template < typename DataType >
    RBTree < DataType > :: RBTreeNode :: RBTreeNode ( DataType const & data ) : key ( data ) { } ;

    template < typename DataType >
    auto RBTree < DataType > :: RBTreeNode :: getLeft() -> NodePointerRefference { return this->left; }

    template < typename DataType >
    auto RBTree < DataType > :: RBTreeNode :: getRight() -> NodePointerRefference { return this->right; }

    template < typename DataType >
    auto RBTree < DataType > :: RBTreeNode :: getParent() -> NodePointerRefference { return this->parent; }

    template < typename DataType >
    auto RBTree < DataType > :: RBTreeNode :: getColour() -> Colour { return this->colour; }

    template < typename DataType >
    auto RBTree < DataType > :: RBTreeNode :: getKey () -> const DataType& { return this->key; }

    template < typename DataType >
    auto RBTree < DataType > :: RBTreeNode :: setKey ( DataType const & data ) -> void { this->key = data; }

    template < typename DataType >
    auto RBTree < DataType > :: RBTreeNode :: setColour ( Colour c ) -> void { this->colour = c; }

    template < typename DataType >
    auto RBTree < DataType > :: RBTreeNode :: insertLeft ( DataType const & data ) -> NodePointerRefference {
        if ( this->left == nullptr ) {
            NodePointer x = new NodePointer ( data );
            this->left = x;
        }
    }

    template < typename DataType >
    auto RBTree < DataType > :: RBTreeNode :: insertRight ( DataType const & data ) -> NodePointerRefference {
        if ( this->right == nullptr ) {
            NodePointer x = new NodePointer ( data );
            this->right = x;
        }
    }

    template < typename DataType >
    auto RBTree < DataType > :: RBTreeNode :: isRed () -> bool {
        return this->colour == RED;
    }

    template < typename DataType >
    auto RBTree < DataType > :: RBTreeNode :: isLeftChild () -> bool {
        return ( this == this->parent->left );
    }

    template < typename DataType >
    auto RBTree < DataType > :: leftRotate ( RBTreeNode * pivot ) -> void {
        RBTreeNode * aux = pivot->getRight();
        pivot->getRight() = aux->getLeft();
        if ( aux->getLeft() != nullptr )
            aux->getLeft()->getParent() = pivot;
        aux->getParent() = pivot->getParent();
        if ( pivot->getParent() == nullptr )
            this->root = aux;
        else
            if ( pivot->isLeftChild() )
                pivot->getParent()->getLeft() = aux;
            else
                pivot->getParent()->getRight() = aux;
        aux->getLeft() = pivot;
        pivot->getParent() = aux;
    }

    template < typename DataType >
    auto RBTree < DataType > :: rightRotate ( RBTreeNode * pivot ) -> void {
        RBTreeNode * aux = pivot->getLeft();
        pivot->getLeft() = aux->getRight();
        if ( aux->getRight() != nullptr )
            aux->getRight()->getParent() = pivot;
        aux->getParent() = pivot->getParent();
        if ( pivot->getParent() != nullptr )
            this->root = aux;
        else
            if ( pivot->isLeftChild() )
                pivot->getParent()->getLeft() = aux;
            else
                pivot->getParent()->getRight() = aux;
        aux->getRight() = pivot;
        pivot->getParent() = aux;
    }

    template < typename DataType >
    auto RBTree < DataType > :: insertFixup ( RBTreeNode * newNode ) -> void {
        while ( newNode->getParent()->isRed() ) {
            if ( newNode->getParent()->isLeftChild() ) {
                RBTreeNode * aux = newNode->getParent()->getParent()->getRight();
                if ( aux != nullptr && aux->isRed() ) {
                    newNode->getParent()->setColour ( RBTreeNode :: RED );
                    aux->setColour ( RBTreeNode :: BLACK );
                    newNode->getParent()->getParent()->setColour ( RBTreeNode :: RED );
                    newNode = newNode->getParent()->getParent();
                }
                else {
                    if ( !newNode->isLeftChild () ) {
                        newNode = newNode->getParent();
                        this->leftRotate ( newNode );
                    }
                    newNode->getParent()->setColour ( RBTreeNode::BLACK );
                    newNode->getParent()->getParent()->setColour ( RBTreeNode::RED );
                    this->rightRotate ( newNode->getParent()->getParent() );
                }
            }
            else {
                RBTreeNode * aux = newNode->getParent()->getParent()->getLeft();
                if ( aux != nullptr && aux->isRed() ) {
                    newNode->getParent()->setColour ( RBTreeNode :: RED );
                    aux->setColour ( RBTreeNode :: BLACK );
                    newNode->getParent()->getParent()->setColour ( RBTreeNode :: RED );
                    newNode = newNode->getParent()->getParent();
                }
                else {
                    if ( newNode->isLeftChild () ) {
                        newNode = newNode->getParent();
                        this->rightRotate ( newNode );
                    }
                    newNode->getParent()->setColour ( RBTreeNode::BLACK );
                    newNode->getParent()->getParent()->setColour ( RBTreeNode::RED );
                    this->leftRotate ( newNode->getParent()->getParent() );
                }
            }
        }
        this->root->setColour ( RBTreeNode :: BLACK );
    }

    template < typename DataType >
    auto RBTree < DataType > :: transplant ( RBTreeNode * u, RBTreeNode * v ) -> void {
        if ( u->getParent() == nullptr )
            this->root = v;
        else
            if ( u->isLeftChild() )
                u->getParent()->getLeft() = v;
            else
                u->getParent()->getRight() = v;
        if ( v != nullptr )
            v->getParent() = u->getParent();
    }

    template < typename DataType >
    auto RBTree < DataType > :: deleteFixup ( RBTreeNode * deletedNode ) -> void {
        while ( deletedNode != this->root && !deletedNode->isRed() ) {
            if ( deletedNode->isLeftChild() ) {
                RBTreeNode * aux = deletedNode->getParent()->getRight();
                if ( aux != nullptr && aux->isRed() ) {
                    aux->setColour ( RBTreeNode :: BLACK );
                    deletedNode->getParent()->setColour ( RBTreeNode :: RED );
                    this->leftRotate ( deletedNode->getParent() );
                    aux = deletedNode->getParent()->getRight();
                }
                if ( ( aux->getLeft() == nullptr || !aux->getLeft()->isRed() ) && ( aux->getRight() == nullptr || !aux->getRight()->isRed() ) ) {
                    aux->setColour ( RBTreeNode :: RED );
                    deletedNode = deletedNode->getParent();
                }
                else {
                    if ( ( aux->getRight() == nullptr || !aux->getRight()->isRed () ) ) {
                        aux->getLeft()->setColour ( RBTreeNode::BLACK );
                        aux->setColour( RBTreeNode::RED );
                        this->rightRotate( aux );
                        aux = deletedNode->getParent()->getRight();
                    }
                    aux->setColour ( deletedNode->getParent()->getColour() );
                    deletedNode->getParent()->setColour ( RBTreeNode :: BLACK );
                    aux->getRight()->setColour ( RBTreeNode :: BLACK );
                    this->leftRotate ( deletedNode->getParent() );
                    deletedNode = this->root;
                }
            }
            else {
                RBTreeNode * aux = deletedNode->getParent()->getLeft();
                if ( aux != nullptr && aux->isRed() ) {
                    aux->setColour ( RBTreeNode :: BLACK );
                    deletedNode->getParent()->setColour ( RBTreeNode :: RED );
                    this->rightRotate ( deletedNode->getParent() );
                    aux = deletedNode->getParent()->getLeft();
                }
                if ( ( aux->getRight() == nullptr || !aux->getRight()->isRed() ) && ( aux->getLeft() == nullptr || !aux->getLeft()->isRed() ) ) {
                    aux->setColour ( RBTreeNode :: RED );
                    deletedNode = deletedNode->getParent();
                }
                else {
                    if ( ( aux->getLeft() == nullptr || !aux->getLeft ()->isRed () ) ) {
                        aux->getRight()->setColour ( RBTreeNode::BLACK );
                        aux->setColour( RBTreeNode::RED );
                        this->leftRotate( aux );
                        aux = deletedNode->getParent()->getLeft();
                    }
                    aux->setColour ( deletedNode->getParent()->getColour() );
                    deletedNode->getParent()->setColour ( RBTreeNode :: BLACK );
                    aux->getLeft()->setColour ( RBTreeNode :: BLACK );
                    this->rightRotate ( deletedNode->getParent() );
                    deletedNode = this->root;
                }
            }
        }
        deletedNode->setColour ( RBTreeNode :: BLACK );
    }

    template < typename DataType >
    auto RBTree < DataType > :: Insert ( const DataType & data ) -> void {
        RBTreeNode * x = this->root;
        if ( x == nullptr ) {
            this->root = new RBTreeNode ( data );
            this->root->setColour ( RBTreeNode :: BLACK );
            return;
        }
        RBTreeNode * y = x;
        while ( x != nullptr ) {
            y = x;
            if ( data < x->getKey() )
                x = x->getLeft();
            else
                x = x->getRight();
        }
        auto z = new RBTreeNode ( data );
        if ( data < y->getKey() )
            y->getLeft() = z;
        else
            y->getRight() = z;
        z->getParent() = y;
        this->insertFixup( z );
    }

    template < typename DataType >
    auto RBTree < DataType > :: Delete ( const DataType & data ) -> void {
        RBTreeNode * z = this->root;
        while ( z != nullptr ) {
            if ( data == z->getKey() )
                break;
            if ( data < z->getKey() )
                z = z->getLeft();
            else
                z = z->getRight();
        }
        if ( z == nullptr ) {
            throw std :: runtime_error ( "Data does not exist in RB-tree" );
        }
        RBTreeNode * y = z;
        RBTreeNode * x;
        bool isBlack = !y->isRed();
        if ( z->getLeft() == nullptr ) {
            x = z->getRight();
            this->transplant( z, z->getRight() );
        }
        else
            if ( z->getRight() == nullptr ) {
                x = z->getLeft();
                this->transplant( z, z->getLeft() );
            }
            else {
                y = z->getRight();
                while ( y->getLeft() != nullptr )
                    y = y->getLeft();
                isBlack = !y->isRed();
                x = y->getRight();
                if ( y->getParent() == z )
                    x->getParent() = y;
                else {
                    this->transplant( y, y->getRight() );
                    y->getRight() = z->getRight();
                    y->getRight()->getParent() = y;
                }
                this->transplant( z, y );
                y->getLeft() = z->getLeft();
                y->getLeft()->getParent() = y;
                y->setColour ( z->getColour() );
            }
        if ( isBlack )
            deleteFixup ( x );
    }

    template < typename DataType >
    auto RBTree < DataType > :: Find ( DataType const & data ) -> RBTreeNode * {
        RBTreeNode * x = this->root;
        while ( x != nullptr ) {
            if ( data == x->getKey() )
                return x;
            if ( data < x->getKey() )
                x = x->getLeft();
            else
                x = x->getRight();
        }
        return nullptr;
    }
}

#endif //CDS_RBTREE_H
