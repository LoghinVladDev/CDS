//
// Created by loghin on 27.01.2021.
//

#ifndef CDS_BTREE_H
#define CDS_BTREE_H

#include <CDS/Object>
#include <CDS/Optional>
#include <CDS/Reference>
#include <CDS/Range>

namespace cds {

    template <class T>
    class BTree : public Object {
    public:
        using Value                 = T;
        using ValueReference        = Value &;
        using ValueConstReference   = Value const &;
        using ValuePointer          = Value *;
        using ValueArray            = Value *;

        using TreeOrder             = Size;

        class BTreeNode final{
        public:
            using Node              = BTreeNode;
            using NodePointer       = Node *;
            using NodePointerArray  = NodePointer *;
        private:
            ValueArray          keys        {nullptr};
            TreeOrder           treeOrder;
            NodePointerArray    children    {nullptr};
            Size                keyCount;
            bool                leaf;
        public:

            BTreeNode( TreeOrder, bool ) noexcept;
            ~BTreeNode() noexcept;

            auto insert ( ValueConstReference ) noexcept -> void;
            auto split ( Index, NodePointer ) noexcept -> void;
            auto find ( ValueConstReference ) noexcept -> Optional < Node >;

            constexpr inline auto getKeys () noexcept -> ValueArray & { return keys; }
            [[nodiscard]] constexpr inline auto getOrder () const noexcept -> TreeOrder { return treeOrder; }
            constexpr inline auto getChildren () noexcept -> NodePointerArray & { return children; }
            constexpr inline auto isLeaf () noexcept -> bool { return leaf; }
            [[nodiscard]] constexpr inline auto getKeyCount () const noexcept -> Size { return keyCount; }

            inline auto makeLeaf () noexcept -> void { this->leaf = true; }
            inline auto unMakeLeaf () noexcept -> void { this->leaf = false; }

            inline auto setKeyCount (Size nCount) noexcept -> void { keyCount = nCount; }
        };

    private:
        BTreeNode * root {nullptr};
        TreeOrder   treeOrder;

    public:
        BTree () noexcept = delete;
        explicit BTree (Size tOrder) noexcept : treeOrder(tOrder), root(nullptr) {}

        inline auto find ( ValueConstReference v ) noexcept -> Optional < typename BTreeNode::Node > {
            if ( root == nullptr )
                return { };

            return root->find( v );
        }

        auto insert ( ValueConstReference v ) noexcept -> void {
            if ( root == nullptr ) {
                root = new BTreeNode ( treeOrder, true );
                root->getKeys()[0] = v;
                root->setKeyCount(1);
                return;
            }

            if (root->getKeyCount() == 2 * treeOrder - 1 ) {
                auto newNode = new BTreeNode(treeOrder, false);
                newNode->getChildren[0] = root;
                newNode->split(0, root);

                Index i = 0;
                if ( newNode->getKeys()[0] < v )
                    i++;

                newNode->getChildren()[i]->insert(v);
                root = newNode;
            } else {
                root->insert(v);
            }
        }
    };

    template <class T>
    BTree<T>::BTreeNode::BTreeNode(TreeOrder o, bool isLeaf) noexcept :
            treeOrder ( o ),
            leaf ( isLeaf ),
            keys ( new Value[2 * treeOrder - 1] ),
            children ( new NodePointer[2 * treeOrder] ),
            keyCount (0) {
        for ( auto i : Range(0, 2 * treeOrder) )
            children[i] = nullptr;
    }

    template<class T>
    BTree<T>::BTreeNode::~BTreeNode() noexcept {
        for ( auto i : Range(0, 2 * treeOrder) )
            if ( children[i] != nullptr )
                delete children[i];
        delete [] children;
        delete [] keys;
    }

    template <class T>
    auto BTree<T>::BTreeNode::find(ValueConstReference v) noexcept -> Optional < Node > {
        Index i = 0;
        while (i < keyCount && v > keys[i] )
            i++;

        if ( keys[i] == v )
            return { * this };

        if ( leaf )
            return { };

        return children[i]->find(v);
    }

    template <class T>
    auto BTree<T>::BTreeNode::insert(ValueConstReference v) noexcept -> void {
        Index i = keyCount - 1;
        if ( leaf ) {
            while ( i >= 0 && keys[i] > v ) {
                keys[i + 1] = keys[i];
                i --;
            }

            keys[i + 1] = v;
            keyCount ++;
        } else {
            while ( i >= 0 && keys[i] > v )
                i --;

            if ( children[i + 1]->getKeyCount() == 2 * treeOrder - 1 ) {
                this->split( i + 1, children[ i + 1 ] );
                if ( keys[i + 1] < v ) i++;
            }

            children[i + 1]->insert ( v );
        }
    }

    template <class T>
    auto BTree<T>::BTreeNode::split(Index i, NodePointer from) noexcept -> void {
        auto * newNode = new Node(from->treeOrder, from->isLeaf());
        newNode->setKeyCount(from->treeOrder - 1);

        for ( auto j : Range(0, treeOrder) )
            newNode->keys[j] = from->keys[j + treeOrder];
        if ( ! from->isLeaf() )
            for ( auto j : Range(0, treeOrder) )
                newNode->children[j] = from->children[j + treeOrder];

        from->setKeyCount(treeOrder - 1);
        for ( auto j : Range(keyCount, i) )
            children[j + 1] = children[j];

        children[i + 1] = newNode;

        for ( auto j : Range(keyCount - 1, i - 1) )
            keys[j + 1] = keys[j];

        keys[i] = from->keys[treeOrder - 1];
        setKeyCount( getKeyCount() + 1 );
    }

}

#endif //CDS_BTREE_H
