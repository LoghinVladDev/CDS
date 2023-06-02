//
// Created by stefan on 22.07.2022.
//

#ifndef __CDS_SHARED_RED_BLACK_TREE_HPP__
#define __CDS_SHARED_RED_BLACK_TREE_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

template <
    typename                                                            __ElementType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __Comparator,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyEqualsComparator,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __RedBlackTree {                                                                        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
public:
  using __rbt_AbstractIterator        = AbstractRedBlackTreeIterator <__ElementType>;           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using __rbt_AbstractConstIterator   = AbstractRedBlackTreeConstIterator <__ElementType>;      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using __rbt_Iterator                = RedBlackTreeForwardIterator <__ElementType>;            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using __rbt_ConstIterator           = RedBlackTreeForwardConstIterator <__ElementType>;       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using __rbt_ReverseIterator         = RedBlackTreeBackwardIterator <__ElementType>;           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using __rbt_ReverseConstIterator    = RedBlackTreeBackwardConstIterator <__ElementType>;      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  template <typename __ServerType>        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  class __SetDispatcher;                  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  template <typename __ServerType>        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  class __MapDispatcher;                  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

protected:
  constexpr __RedBlackTree() noexcept = default;

  template <
      cds::functional::ConsumerFunction <__ElementType&, __ElementType const&> __copy // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  > __CDS_Implicit __RedBlackTree (__RedBlackTree const &tree) noexcept;              // NOLINT(google-explicit-constructor)

  constexpr __RedBlackTree (__RedBlackTree&& tree) noexcept;

  __CDS_NoDiscard constexpr auto __rbt_empty () const -> bool; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  __CDS_NoDiscard auto __rbt_get ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __KeyType const&  key,
      bool*             pIsNew
  ) noexcept(false) -> __ElementType*;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto __rbt_get ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __KeyType const& key
  ) const noexcept -> __ElementType const*;

  auto __rbt_remove (__KeyType const& key) noexcept -> bool;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  auto __rbt_removeIterator ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      AbstractRedBlackTreeIterator <__ElementType> const& iterator
  ) noexcept -> bool;

  auto __rbt_removeConstIterator ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      AbstractRedBlackTreeConstIterator <__ElementType> const& iterator
  ) noexcept -> bool;

  auto __rbt_removeIteratorArray ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      AbstractRedBlackTreeIterator <__ElementType> const* const*  iteratorArray,
      Size                                                        iteratorCount
  ) noexcept -> Size;

  auto __rbt_removeConstIteratorArray ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      AbstractRedBlackTreeConstIterator <__ElementType> const* const* iteratorArray,
      Size                                                            iteratorCount
  ) noexcept -> Size;

  auto __rbt_clear () noexcept -> void; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp):
  __CDS_NoDiscard constexpr auto __rbt_size () const noexcept -> Size; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto __rbt_equals (__RedBlackTree const& other) const noexcept -> bool; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  template <
      cds::functional::ConsumerFunction <__ElementType&, __ElementType const&>  __copy  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  > auto __rbt_copy (__RedBlackTree const& tree) noexcept(false) -> void;               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  template <
      cds::functional::ConsumerFunction <__ElementType&, __ElementType const&>  __copy  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  > auto __rbt_copyCleared (__RedBlackTree const& tree) noexcept(false) -> void;        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  auto __rbt_move (__RedBlackTree&& tree) noexcept -> void; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_cpplang_ConstexprConditioned auto __rbt_moveCleared (__RedBlackTree&& tree) noexcept -> void; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  auto __rbt_new (                // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __ElementType const*  pReferenceElement,
      bool*                 pIsNew
  ) noexcept(false) -> __ElementType*;

  __CDS_cpplang_ConstexprConditioned auto __rbt_findIterator (       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __KeyType const& key
  ) noexcept -> __rbt_Iterator;

  __CDS_cpplang_ConstexprConditioned auto __rbt_findIteratorConst (  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __KeyType const& key
  ) const noexcept -> __rbt_ConstIterator;

  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto __rbt_begin () noexcept -> __rbt_Iterator;         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto __rbt_end () noexcept -> __rbt_Iterator;           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto __rbt_rbegin () noexcept -> __rbt_ReverseIterator; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto __rbt_rend () noexcept -> __rbt_ReverseIterator;   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto __rbt_cbegin () const noexcept -> __rbt_ConstIterator;         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard constexpr auto __rbt_cend () const noexcept -> __rbt_ConstIterator;           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto __rbt_crbegin () const noexcept -> __rbt_ReverseConstIterator; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard constexpr auto __rbt_crend () const noexcept -> __rbt_ReverseConstIterator;   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

private:
  using __rbt_NodeType                = __RedBlackTreeNode <__ElementType>;    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using __rbt_NodeColourType          = __RedBlackTreeNodeColour;    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  template <typename> friend class AbstractRedBlackTreeIterator;
  template <typename> friend class AbstractRedBlackTreeConstIterator;

  __CDS_NoDiscard constexpr static auto __rbt_isLeftChild (      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __rbt_NodeType const* pNode,
      __rbt_NodeType const* pNodeParent
  ) noexcept -> bool;

  __CDS_NoDiscard constexpr static auto __rbt_isRightChild (     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __rbt_NodeType const* pNode,
      __rbt_NodeType const* pNodeParent
  ) noexcept -> bool;

  __CDS_NoDiscard constexpr static auto __rbt_getLeftNode (__rbt_NodeType* pNode) noexcept -> __rbt_NodeType*;     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard constexpr static auto __rbt_getRightNode (__rbt_NodeType* pNode) noexcept -> __rbt_NodeType*;    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard constexpr static auto __rbt_isNodeBlack (__rbt_NodeType const* pNode) noexcept -> bool;   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_NoDiscard constexpr static auto __rbt_isNodeRed (__rbt_NodeType const* pNode) noexcept -> bool;     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  Size              _size   {0u};
  __rbt_NodeType*   _pRoot  {nullptr};

  __CDS_NoUniqueAddress __Comparator  _keyLowerComparator;

  __CDS_NoDiscard static auto __rbt_allocateNode () noexcept(false) -> __rbt_NodeType*;          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  static auto __rbt_freeNode (__rbt_NodeType* pRemoved) noexcept -> void;         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  __CDS_cpplang_ConstexprConditioned auto __rbt_leftRotate (__rbt_NodeType* pPivot) noexcept -> void;         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_cpplang_ConstexprConditioned auto __rbt_rightRotate (__rbt_NodeType* pPivot) noexcept -> void;            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_cpplang_ConstexprConditioned auto __rbt_insertReBalance (__rbt_NodeType* pPivot) noexcept -> void;            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_cpplang_ConstexprConditioned auto __rbt_transplant (__rbt_NodeType* pRemoved, __rbt_NodeType* pMovedIn) noexcept -> void;            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __CDS_cpplang_ConstexprConditioned auto __rbt_deleteReBalance (        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __rbt_NodeType* pPivot,
      __rbt_NodeType* pPivotParent
  ) noexcept -> void;

  using __rbt_AuxiliaryLocatorFunction    = decltype (&__RedBlackTree::__rbt_getLeftNode);   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using __rbt_RotationConditionalFunction = decltype (&__RedBlackTree::__rbt_isLeftChild);   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using __rbt_RotationScenarioFunction    = decltype (&__RedBlackTree::__rbt_rightRotate);   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  template <
      typename                                                __ClassType,            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename __ClassType::__rbt_AuxiliaryLocatorFunction    __locateAuxiliary,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename __ClassType::__rbt_RotationConditionalFunction __scenarioConditional,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename __ClassType::__rbt_RotationScenarioFunction    __ifTrue,               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename __ClassType::__rbt_RotationScenarioFunction    __ifFalse               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  > __CDS_cpplang_ConstexprConditioned auto __rbt_identifyAndApplyRotationOnInsert (                                             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __rbt_NodeType*& pPivot
  ) noexcept -> void;

  template <
      typename                                                  __ClassType,                // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename __ClassType::__rbt_AuxiliaryLocatorFunction      __locateAuxiliary,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename __ClassType::__rbt_AuxiliaryLocatorFunction      __locateReverseAuxiliary,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename __ClassType::__rbt_RotationConditionalFunction   __scenarioConditional,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename __ClassType::__rbt_RotationScenarioFunction      __ifTrue,                   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename __ClassType::__rbt_RotationScenarioFunction      __ifFalse                   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  > __CDS_cpplang_ConstexprConditioned auto __rbt_identifyAndApplyRotationOnDelete (                                                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __rbt_NodeType*&  pPivot,
      __rbt_NodeType*   pPivotParent
  ) noexcept -> void;

  auto __rbt_removeAt (__rbt_NodeType* pToBeRemoved) noexcept -> bool;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  __CDS_cpplang_ConstexprConditioned auto __rbt_findNode (           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      __KeyType const &key
  ) const noexcept -> __rbt_NodeType*;
};
}
}
}

#endif // __CDS_SHARED_RED_BLACK_TREE_HPP__

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

#if defined ( __CDS_SHARED_TREE_SET_SERVER_DISPATCHER_HPP__ ) && ! defined ( __CDS_SHARED_TREE_SET_SET_SERVER_DISPATCHER_HPP__ ) && defined (__CDS_SHARED_RED_BLACK_TREE_HPP__)
#define __CDS_SHARED_TREE_SET_SET_SERVER_DISPATCHER_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

template <
    typename                                                            __ElementType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __Comparator,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyEqualsComparator,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> template <
    typename                                                            __ServerType            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __RedBlackTree <
    __ElementType, __KeyType, __Comparator,
    __keyExtractor, __keyEqualsComparator, __nodeDestructor
>::__SetDispatcher :
    public __TreeSetServerDispatcher <
        __ServerType, __RedBlackTree, __ElementType,
        AbstractRedBlackTreeConstIterator <__ElementType>,
        RedBlackTreeForwardConstIterator <__ElementType>,
        RedBlackTreeBackwardConstIterator <__ElementType>,
        &__RedBlackTree::__rbt_cbegin, &__RedBlackTree::__rbt_cend,
        &__RedBlackTree::__rbt_crbegin, &__RedBlackTree::__rbt_crend,
        &__RedBlackTree::__rbt_new,
        &__RedBlackTree::__rbt_removeConstIterator,
        &__RedBlackTree::__rbt_removeConstIteratorArray,
        &__RedBlackTree::__rbt_findIteratorConst
    > {};
#endif
} // namespace __impl
} // namespace __hidden
} // namespace cds

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#if defined ( __CDS_SHARED_TREE_MAP_SERVER_DISPATCHER_HPP__ ) && ! defined ( __CDS_SHARED_TREE_MAP_MAP_SERVER_DISPATCHER_HPP__ ) && defined ( __CDS_SHARED_RED_BLACK_TREE_HPP__ )
#define __CDS_SHARED_TREE_MAP_MAP_SERVER_DISPATCHER_HPP__   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

template <
    typename                                                            __ElementType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __Comparator,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyEqualsComparator,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> template <
    typename __ServerType                                                                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __RedBlackTree <
    __ElementType, __KeyType, __Comparator,
    __keyExtractor, __keyEqualsComparator, __nodeDestructor
>::__MapDispatcher :
    public __TreeMapServerDispatcher <
        __ServerType, __RedBlackTree, __ElementType, __KeyType,
        AbstractRedBlackTreeIterator <__ElementType>, AbstractRedBlackTreeConstIterator <__ElementType>,
        RedBlackTreeForwardIterator <__ElementType>, RedBlackTreeForwardConstIterator <__ElementType>,
        RedBlackTreeBackwardIterator <__ElementType>, RedBlackTreeBackwardConstIterator <__ElementType>,
        &__RedBlackTree::__rbt_begin, &__RedBlackTree::__rbt_end,
        &__RedBlackTree::__rbt_rbegin, &__RedBlackTree::__rbt_rend,
        &__RedBlackTree::__rbt_cbegin, &__RedBlackTree::__rbt_cend,
        &__RedBlackTree::__rbt_crbegin, &__RedBlackTree::__rbt_crend,
        &__RedBlackTree::__rbt_new,
        &__RedBlackTree::__rbt_removeIterator, &__RedBlackTree::__rbt_removeConstIterator,
        &__RedBlackTree::__rbt_removeIteratorArray, &__RedBlackTree::__rbt_removeConstIteratorArray,
        &__RedBlackTree::__rbt_findIterator, &__RedBlackTree::__rbt_findIteratorConst
    >{};
#endif
} // namespace __impl
} // namespace __hidden
} // namespace cds