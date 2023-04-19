#include <iostream>
#include <cassert>
#include <tuple>

template <typename T>
class Tree {
private:
    struct Node {
        T       value;
        /* representation of child number */
        Node  * children    {nullptr};
        int     childCount  {0};
    };

public:
    Tree () noexcept;

    auto add_node (T const & value, Node * pParent = nullptr) noexcept -> Node *;
    auto get_node (T const & value) noexcept -> Node *;
    auto delete_node (Node const * pNode) noexcept -> void;
    auto find (bool (* pfnValidate) (T const &)) noexcept -> Node *;
    auto insert (Node * pParent, int index, Node const * pToInsert) noexcept -> Node *;
    auto sort (Node * pTargetNode, bool (* pfnSort) (T const &, T const &)) noexcept -> void;
    auto count (Node const * pTargetNode = nullptr) const noexcept -> int;


    /* can be const qualified */
    auto get_node (T const & value) const noexcept -> Node const *;
    /* as above */
    auto find (bool (* pfnCompare) (T const &, T const &)) const noexcept -> Node const *;
    /* while pfnSort can be made nullptr, if only relying on 'if pfnSort null, use <' is incorrect.
     * Given type T can have no 'operator <' overload */
    auto sort (Node * pTargetNode) noexcept -> void;
};

struct ENoLessOverload {
private:
    int x;
    int y;

public:
    ENoLessOverload (int x) : x (x) {}
};

template <typename T>
auto equal (T const & a, T const & b) {return a == b;}

template <typename T>
auto greater (T const & a, T const & b) {return a > b;}

template <typename T>
auto less (T const & a, T const & b) {return a < b;}

auto main () -> int {

    Tree <int> tree;
    auto * pAddedNode = tree.add_node(3);
    tree.add_node(5, pAddedNode);
    tree.add_node(1, pAddedNode);

    assert (tree.count() == 3);

    assert (tree.find([](int const & nValue) {return nValue == 3;}) != nullptr);
    assert (tree.find([](int const & nValue) {return nValue == 1;}) != nullptr);
    assert (tree.find([](int const & nValue) {return nValue == 5;}) != nullptr);
    assert (tree.find([](int const & nValue) {return nValue == 2;}) == nullptr);
    assert (tree.find([](int const & nValue) {return nValue == 7;}) == nullptr);
    assert (tree.find([](int const & nValue) {return nValue == 8;}) == nullptr);

    assert (tree.count(tree.find([](int const & nValue){ return nValue == 3; })) == 2);
    assert (tree.count(tree.find([](int const & nValue){ return nValue == 1; })) == 0);
    assert (tree.count(tree.find([](int const & nValue){ return nValue == 5; })) == 0);
    assert (tree.count(tree.find([](int const & nValue){ return nValue == 7; })) == 0);

    /*
     * initial tree is:
     *      3
     *    1   5
     * resulted tree should be
     *      3
     *    1   5
     *        3
     *      1   5
     * */
    tree.insert (
            tree.find([](int const & nValue) {return nValue == 5;}),
            0,
            tree.find([](int const & nValue) {return nValue == 1;})
    );

    assert (tree.count() == 6);
    assert (tree.count(tree.find([](int const & nValue) {return nValue == 3;})) == 5);
    assert (tree.count (tree.find([](int const & nValue) {return nValue == 5;})) == 3);

    tree.delete_node(tree.find([](int const &nValue) {return nValue == 5;}));
    assert (tree.count() == 2);
    assert (tree.count(tree.find([](int const & nValue) {return nValue == 3;})) == 1);

    auto * p7Node = tree.add_node (7, tree.find([](int const & nValue) {return nValue == 3;}));
    auto * p4Node = tree.add_node (4, p7Node);
    (void) tree.add_node (2, p4Node);
    auto * p10Node = tree.add_node (10, p7Node);
    (void) tree.add_node (4, p10Node);

    assert (tree.count(tree.find([](int const & nValue){return nValue == 4;})) == 1);
    tree.sort (p7Node, [](int const &a, int const& b) {return a > b;});
    /* nodes swaped, search will be different */
    assert (tree.count(tree.find([](int const & nValue){return nValue == 4;})) == 0);
    tree.sort (p7Node);
    assert (tree.count(tree.find([](int const & nValue){return nValue == 4;})) == 1);
    tree.sort (p7Node, & greater <int>);
    assert (tree.count(tree.find([](int const & nValue){return nValue == 4;})) == 0);
    tree.sort (pAddedNode, & less <int>);
    assert (tree.count(tree.find([](int const & nValue){return nValue == 4;})) == 1);


    Tree <std::tuple <std::string, int>> treeNotComparable;
    auto * pRoot = treeNotComparable.add_node (std::make_tuple ("root", 3));
    treeNotComparable.add_node (std::make_tuple ("leftLeaf", 2), pRoot);
    treeNotComparable.add_node (std::make_tuple ("rightLeaf", 1), pRoot);

    assert (treeNotComparable.find([](auto const & nValue) { return std::get <0> (nValue) == "root"; }) != nullptr);
    assert (treeNotComparable.find([](auto const & nValue) { return std::get <0> (nValue) == "Root"; }) == nullptr);
    assert (treeNotComparable.find([](auto const & nValue) { return std::get <0> (nValue) == "Root" || std::get <1> (nValue) == 2; }) != nullptr);
    assert (treeNotComparable.find([](auto const & nValue) { return std::get <0> (nValue) == "root" && std::get <1> (nValue) == 3; }) != nullptr);
    assert (treeNotComparable.find([](auto const & nValue) { return std::get <0> (nValue) == "root" && std::get <1> (nValue) == 2; }) == nullptr);
    assert (treeNotComparable.find([](auto const & nValue) { return std::get <0> (nValue) == "Root" || std::get <1> (nValue) == 4; }) == nullptr);

    assert (treeNotComparable.count() == 3);
    assert (2 == treeNotComparable.count(
            treeNotComparable.find ([](auto const & nValue) { return std::get <0> (nValue) == "root"; })
    ));
    assert (0 == treeNotComparable.count(
            treeNotComparable.find ([](auto const & nValue) { return std::get <0> (nValue) == "leftLeaf"; })
    ));
    assert (0 == treeNotComparable.count(
            treeNotComparable.find ([](auto const & nValue) { return std::get <1> (nValue) == 1; })
    ));

    return 0;
}
