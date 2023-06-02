//
// Created by stefan on 02.07.2022.
//

#ifndef __CDS_SHARED_RED_BLACK_TREE_IMPL_HPP__
#define __CDS_SHARED_RED_BLACK_TREE_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

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
> constexpr auto __RedBlackTree <
    __ElementType, __KeyType, __Comparator,
    __keyExtractor, __keyEqualsComparator, __nodeDestructor
>::__rbt_isLeftChild (__rbt_NodeType const* pNode, __rbt_NodeType const* pNodeParent) noexcept -> bool {
  return pNodeParent == nullptr || pNodeParent->_pLeft == pNode;
}


template <
    typename                                                            __ElementType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __Comparator,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyEqualsComparator,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> constexpr auto __RedBlackTree <
    __ElementType, __KeyType, __Comparator,
    __keyExtractor, __keyEqualsComparator, __nodeDestructor
>::__rbt_isRightChild (__rbt_NodeType const* pNode, __rbt_NodeType const* pNodeParent) noexcept -> bool {
  return !__rbt_isLeftChild (pNode, pNodeParent);
}


template <
    typename                                                            __ElementType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __Comparator,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyEqualsComparator,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> constexpr auto __RedBlackTree <
    __ElementType, __KeyType, __Comparator,
    __keyExtractor, __keyEqualsComparator, __nodeDestructor
>::__rbt_getLeftNode (__rbt_NodeType* pNode) noexcept -> __rbt_NodeType* {
  return pNode->_pLeft;
}


template <
    typename                                                            __ElementType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __Comparator,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyEqualsComparator,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> constexpr auto __RedBlackTree <
    __ElementType, __KeyType, __Comparator,
    __keyExtractor, __keyEqualsComparator, __nodeDestructor
>::__rbt_getRightNode (__rbt_NodeType* pNode) noexcept -> __rbt_NodeType* {
  return pNode->_pRight;
}


template <
    typename                                                            __ElementType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __Comparator,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyEqualsComparator,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> constexpr auto __RedBlackTree <
    __ElementType, __KeyType, __Comparator,
    __keyExtractor, __keyEqualsComparator, __nodeDestructor
>::__rbt_isNodeBlack (__rbt_NodeType const* pNode) noexcept -> bool {
  return pNode == nullptr || pNode->_colour == __rbt_NodeColourType::__rbtnc_Black;
}


template <
    typename                                                            __ElementType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __Comparator,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyEqualsComparator,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> constexpr auto __RedBlackTree <
    __ElementType, __KeyType, __Comparator,
    __keyExtractor, __keyEqualsComparator, __nodeDestructor
>::__rbt_isNodeRed (__rbt_NodeType const* pNode) noexcept -> bool {
  return !__rbt_isNodeBlack (pNode);
}


template <
    typename                                                            __ElementType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __Comparator,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyEqualsComparator,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_OptimalInline auto __RedBlackTree <
    __ElementType, __KeyType, __Comparator,
    __keyExtractor, __keyEqualsComparator, __nodeDestructor
>::__rbt_allocateNode () noexcept(false) -> __rbt_NodeType* {
  using __Alloc = __allocation::__PrimitiveAlloc <__rbt_NodeType>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  auto pNode      = __Alloc::__alloc();
  pNode->_colour  = __rbt_NodeColourType::__rbtnc_Red;
  pNode->_pLeft   = pNode->_pRight = pNode->_pParent = nullptr;
  return pNode;
}


template <
    typename                                                            __ElementType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __Comparator,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyEqualsComparator,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_OptimalInline auto __RedBlackTree <
    __ElementType, __KeyType, __Comparator,
    __keyExtractor, __keyEqualsComparator, __nodeDestructor
>::__rbt_freeNode (__rbt_NodeType* pNode) noexcept -> void {
  using __Alloc = __allocation::__PrimitiveAlloc <__rbt_NodeType>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  __nodeDestructor (pNode->_data);
  __Alloc::__free (pNode);
}


template <
    typename                                                            __ElementType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __Comparator,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyEqualsComparator,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_cpplang_ConstexprConditioned auto __RedBlackTree <
    __ElementType, __KeyType, __Comparator,
    __keyExtractor, __keyEqualsComparator, __nodeDestructor
>::__rbt_leftRotate (__rbt_NodeType* pPivot) noexcept -> void {
  auto pAux       = pPivot->_pRight;
  pPivot->_pRight = pAux->_pLeft;

  if (pAux->_pLeft != nullptr) {
    pAux->_pLeft->_pParent = pPivot;
  }

  pAux->_pParent = pPivot->_pParent;
  if (pPivot->_pParent == nullptr) {
    _pRoot = pAux;
  } else if (__rbt_isLeftChild (pPivot, pPivot->_pParent)) {
    pPivot->_pParent->_pLeft = pAux;
  } else {
    pPivot->_pParent->_pRight = pAux;
  }

  pAux->_pLeft = pPivot;
  pPivot->_pParent = pAux;
}


template <
    typename                                                            __ElementType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __Comparator,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyEqualsComparator,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_cpplang_ConstexprConditioned auto __RedBlackTree <
    __ElementType, __KeyType, __Comparator,
    __keyExtractor, __keyEqualsComparator, __nodeDestructor
>::__rbt_rightRotate (__rbt_NodeType* pPivot) noexcept -> void {
  auto pAux       = pPivot->_pLeft;
  pPivot->_pLeft  = pAux->_pRight;


  if (pAux->_pRight != nullptr) {
    pAux->_pRight->_pParent = pPivot;
  }

  pAux->_pParent = pPivot->_pParent;
  if (pPivot->_pParent == nullptr) {
    _pRoot = pAux;
  } else if (__rbt_isLeftChild (pPivot, pPivot->_pParent)) {
    pPivot->_pParent->_pLeft = pAux;
  } else {
    pPivot->_pParent->_pRight = pAux;
  }

  pAux->_pRight = pPivot;
  pPivot->_pParent = pAux;
}

template <
    typename                                                            __ElementType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __Comparator,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyEqualsComparator,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_cpplang_ConstexprConditioned auto __RedBlackTree <
    __ElementType, __KeyType, __Comparator,
    __keyExtractor, __keyEqualsComparator, __nodeDestructor
>::__rbt_insertReBalance (__rbt_NodeType* pPivot) noexcept -> void {

  while (__rbt_isNodeRed (pPivot->_pParent)) {
    if (__rbt_isLeftChild (pPivot->_pParent, pPivot->_pParent->_pParent)) {
      __rbt_identifyAndApplyRotationOnInsert <
          __RedBlackTree,
          &__RedBlackTree::__rbt_getRightNode, &__RedBlackTree::__rbt_isRightChild,
          &__RedBlackTree::__rbt_leftRotate, &__RedBlackTree::__rbt_rightRotate
      > (pPivot);
    } else {
      __rbt_identifyAndApplyRotationOnInsert <
          __RedBlackTree,
          &__RedBlackTree::__rbt_getLeftNode, &__RedBlackTree::__rbt_isLeftChild,
          &__RedBlackTree::__rbt_rightRotate, &__RedBlackTree::__rbt_leftRotate
      > (pPivot);
    }
  }

  _pRoot->_colour = __rbt_NodeColourType::__rbtnc_Black;
}


template <
    typename                                                            __ElementType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __Comparator,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyEqualsComparator,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_cpplang_ConstexprConditioned auto __RedBlackTree <
    __ElementType, __KeyType, __Comparator,
    __keyExtractor, __keyEqualsComparator, __nodeDestructor
>::__rbt_transplant (__rbt_NodeType* pRemoved, __rbt_NodeType* pMovedIn) noexcept -> void {
  if (pRemoved->_pParent == nullptr) {
    _pRoot = pMovedIn;
  } else if (__rbt_isLeftChild (pRemoved, pRemoved->_pParent)) {
    pRemoved->_pParent->_pLeft = pMovedIn;
  } else {
    pRemoved->_pParent->_pRight = pMovedIn;
  }

  if (pMovedIn != nullptr) {
    pMovedIn->_pParent = pRemoved->_pParent;
  }
}


template <
    typename                                                            __ElementType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __Comparator,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyEqualsComparator,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_cpplang_ConstexprConditioned auto __RedBlackTree <
    __ElementType, __KeyType, __Comparator,
    __keyExtractor, __keyEqualsComparator, __nodeDestructor
>::__rbt_deleteReBalance (__rbt_NodeType* pPivot, __rbt_NodeType* pPivotParent) noexcept -> void {

  while (pPivot != _pRoot && __rbt_isNodeBlack (pPivot)) {
    if (__rbt_isLeftChild (pPivot, pPivotParent)) {
      __rbt_identifyAndApplyRotationOnDelete <
          __RedBlackTree,
          &__RedBlackTree::__rbt_getRightNode, &__RedBlackTree::__rbt_getLeftNode, &__RedBlackTree::__rbt_isRightChild,
          &__RedBlackTree::__rbt_leftRotate, &__RedBlackTree::__rbt_rightRotate
      > (pPivot, pPivotParent);
    } else {
      __rbt_identifyAndApplyRotationOnDelete <
          __RedBlackTree,
          &__RedBlackTree::__rbt_getLeftNode, &__RedBlackTree::__rbt_getRightNode, &__RedBlackTree::__rbt_isLeftChild,
          &__RedBlackTree::__rbt_rightRotate, &__RedBlackTree::__rbt_leftRotate
      > (pPivot, pPivotParent);
    }
  }

  if (pPivot != nullptr) {
    pPivot->_colour = __rbt_NodeColourType::__rbtnc_Black;
  }
}

template <
    typename                                                            __ElementType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __Comparator,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyEqualsComparator,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> template <
    typename                                                            __ClassType,                // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ClassType::__rbt_AuxiliaryLocatorFunction                __locateAuxiliary,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ClassType::__rbt_RotationConditionalFunction             __scenarioConditional,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ClassType::__rbt_RotationScenarioFunction                __ifTrue,                   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ClassType::__rbt_RotationScenarioFunction                __ifFalse                   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_cpplang_ConstexprConditioned auto __RedBlackTree <
    __ElementType, __KeyType, __Comparator,
    __keyExtractor, __keyEqualsComparator, __nodeDestructor
>::__rbt_identifyAndApplyRotationOnInsert (__rbt_NodeType*& pPivot) noexcept -> void {

  auto pAux = __locateAuxiliary (pPivot->_pParent->_pParent);
  if (__rbt_isNodeRed (pAux)) {
    pPivot->_pParent->_colour           = __rbt_NodeColourType::__rbtnc_Black;
    pAux->_colour                       = __rbt_NodeColourType::__rbtnc_Black;
    pPivot->_pParent->_pParent->_colour = __rbt_NodeColourType::__rbtnc_Red;
    pPivot                              = pPivot->_pParent->_pParent;
    return;
  }

  if (__scenarioConditional (pPivot, pPivot->_pParent)) {
    pPivot = pPivot->_pParent;
    (this->*__ifTrue) (pPivot);
  }

  pPivot->_pParent->_colour           = __rbt_NodeColourType::__rbtnc_Black;
  pPivot->_pParent->_pParent->_colour = __rbt_NodeColourType::__rbtnc_Red;
  (this->*__ifFalse) (pPivot->_pParent->_pParent);
}


template <
    typename                                                            __ElementType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __Comparator,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyEqualsComparator,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
>  template <
    typename                                                            __ClassType,                // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ClassType::__rbt_AuxiliaryLocatorFunction                __locateAuxiliary,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ClassType::__rbt_AuxiliaryLocatorFunction                __locateReverseAuxiliary,   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ClassType::__rbt_RotationConditionalFunction             __scenarioConditional,      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ClassType::__rbt_RotationScenarioFunction                __ifTrue,                   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ClassType::__rbt_RotationScenarioFunction                __ifFalse                   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_cpplang_ConstexprConditioned auto __RedBlackTree <
    __ElementType, __KeyType, __Comparator,
    __keyExtractor, __keyEqualsComparator, __nodeDestructor
>::__rbt_identifyAndApplyRotationOnDelete (
    __rbt_NodeType*&  pPivot,
    __rbt_NodeType*   pPivotParent
) noexcept -> void {
  auto pAux = __locateAuxiliary (pPivotParent);

  if (__rbt_isNodeRed (pAux)) {
    pAux->_colour         = __rbt_NodeColourType::__rbtnc_Black;
    pPivotParent->_colour = __rbt_NodeColourType::__rbtnc_Red;
    (this->*__ifTrue) (pPivotParent);
    pAux                  = __locateAuxiliary (pPivotParent);
  }

  if (__rbt_isNodeBlack (pAux->_pLeft) && __rbt_isNodeBlack (pAux->_pRight)) {
    pAux->_colour   = __rbt_NodeColourType::__rbtnc_Red;
    pPivot          = pPivotParent;
    return;
  }

  if (__rbt_isNodeBlack (__locateAuxiliary (pAux))) {
    __locateReverseAuxiliary (pAux)->_colour  = __rbt_NodeColourType::__rbtnc_Black;
    pAux->_colour                             = __rbt_NodeColourType::__rbtnc_Red;
    (this->*__ifFalse) (pAux);
    pAux                                      = __locateAuxiliary (pPivotParent);
  }

  pAux->_colour                     = pPivotParent->_colour;
  pPivotParent->_colour             = __rbt_NodeColourType::__rbtnc_Black;
  __locateAuxiliary (pAux)->_colour = __rbt_NodeColourType::__rbtnc_Black;
  (this->*__ifTrue) (pPivotParent);
  pPivot                            = _pRoot;
}



template <
    typename                                                                  __ElementType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                  __KeyType,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                  __Comparator,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&>       __keyExtractor,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>        __keyEqualsComparator,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                             __nodeDestructor        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> template <
    cds::functional::ConsumerFunction <__ElementType&, __ElementType const&>  __copy // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __RedBlackTree <
    __ElementType, __KeyType, __Comparator,
    __keyExtractor, __keyEqualsComparator, __nodeDestructor
>::__RedBlackTree (__RedBlackTree const& tree) noexcept {
  __rbt_copyCleared (std::move (tree));
}


template <
    typename                                                            __ElementType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __Comparator,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyEqualsComparator,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> constexpr __RedBlackTree <
    __ElementType, __KeyType, __Comparator,
    __keyExtractor, __keyEqualsComparator, __nodeDestructor
>::__RedBlackTree (__RedBlackTree&& tree) noexcept :
    _pRoot (cds::exchange (tree._pRoot, nullptr)),
    _size (cds::exchange (tree._size, 0u)) {

}


template <
    typename                                                            __ElementType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __Comparator,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyEqualsComparator,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> constexpr auto __RedBlackTree <
    __ElementType, __KeyType, __Comparator,
    __keyExtractor, __keyEqualsComparator, __nodeDestructor
>::__rbt_empty () const -> bool {
  return _pRoot == nullptr;
}


template <
    typename                                                            __ElementType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __Comparator,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyEqualsComparator,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __RedBlackTree <
    __ElementType, __KeyType, __Comparator,
    __keyExtractor, __keyEqualsComparator, __nodeDestructor
>::__rbt_get (__KeyType const& key, bool* pIsNew) noexcept(false) -> __ElementType* {

  if (__rbt_empty()) {
    _pRoot            = __rbt_allocateNode();
    _pRoot->_colour   = __rbt_NodeColourType::__rbtnc_Black;
    ++_size;
    *pIsNew = true;
    return &_pRoot->_data;
  }

  auto            pAux = _pRoot;
  __rbt_NodeType* pNewPos;
  while (pAux != nullptr) {

    pNewPos = pAux;
    if (__keyEqualsComparator (key, __keyExtractor (pAux->_data))) {
      *pIsNew = false;
      return &pAux->_data;
    }

    if (_keyLowerComparator (key, __keyExtractor (pAux->_data))) {
      pAux = pAux->_pLeft;
    } else {
      pAux = pAux->_pRight;
    }
  }

  auto pNewNode       = __rbt_allocateNode();
  pNewNode->_pParent  = pNewPos;

  if (_keyLowerComparator (key, __keyExtractor (pNewPos->_data))) {
    pNewPos->_pLeft = pNewNode;
  } else {
    pNewPos->_pRight = pNewNode;
  }

  __rbt_insertReBalance (pNewNode);
  *pIsNew = true;
  ++_size;
  return &pNewNode->_data;
}


template <
    typename                                                            __ElementType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __Comparator,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyEqualsComparator,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_cpplang_ConstexprConditioned auto __RedBlackTree <
    __ElementType, __KeyType, __Comparator,
    __keyExtractor, __keyEqualsComparator, __nodeDestructor
>::__rbt_get (__KeyType const& key) const noexcept -> __ElementType const* {
  if (__rbt_empty()) {
    return nullptr;
  }

  auto pSearch = _pRoot;
  while (pSearch != nullptr) {
    if (__keyEqualsComparator (key, __keyExtractor (pSearch->_data))) {
      return &pSearch->_data;
    }

    if (_keyLowerComparator (key, __keyExtractor (pSearch->_data))) {
      pSearch = pSearch->_pLeft;
    } else {
      pSearch = pSearch->_pRight;
    }
  }

  return nullptr;
}


template <
    typename                                                            __ElementType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __Comparator,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyEqualsComparator,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __RedBlackTree <
    __ElementType, __KeyType, __Comparator,
    __keyExtractor, __keyEqualsComparator, __nodeDestructor
>::__rbt_removeAt (__rbt_NodeType* pToBeRemoved) noexcept -> bool {
  auto            isOriginallyBlack   = __rbt_isNodeBlack (pToBeRemoved);
  __rbt_NodeType* pBalancePivot;
  __rbt_NodeType* pBalancePivotParent = nullptr;

  if (pToBeRemoved->_pLeft == nullptr) {
    pBalancePivot       = pToBeRemoved->_pRight;
    pBalancePivotParent = pToBeRemoved->_pParent;
    __rbt_transplant (pToBeRemoved, pToBeRemoved->_pRight);
  } else if (pToBeRemoved->_pRight == nullptr) {
    pBalancePivot       = pToBeRemoved->_pLeft;
    pBalancePivotParent = pToBeRemoved->_pParent;
    __rbt_transplant (pToBeRemoved, pToBeRemoved->_pLeft);
  } else {

    auto pDeletedPlaceholder = pToBeRemoved->_pRight;
    while (pDeletedPlaceholder->_pLeft != nullptr) {
      pDeletedPlaceholder = pDeletedPlaceholder->_pLeft;
    }

    isOriginallyBlack = __rbt_isNodeBlack (pDeletedPlaceholder);
    pBalancePivot = pDeletedPlaceholder->_pRight;

    if (pDeletedPlaceholder->_pParent == pToBeRemoved) {
      if (pBalancePivot == nullptr) {
        pBalancePivotParent     = pDeletedPlaceholder;
      } else {
        pBalancePivot->_pParent = pDeletedPlaceholder;
      }
    } else {
      pBalancePivotParent                     = pDeletedPlaceholder -> _pParent;
      __rbt_transplant (pDeletedPlaceholder, pDeletedPlaceholder->_pRight);
      pDeletedPlaceholder->_pRight            = pToBeRemoved->_pRight;
      pDeletedPlaceholder->_pRight->_pParent  = pDeletedPlaceholder;
    }

    __rbt_transplant (pToBeRemoved, pDeletedPlaceholder);
    pDeletedPlaceholder->_pLeft             = pToBeRemoved->_pLeft;
    pDeletedPlaceholder->_pLeft->_pParent   = pDeletedPlaceholder;
    pDeletedPlaceholder->_colour            = pToBeRemoved->_colour;
  }

  __rbt_freeNode (pToBeRemoved);
  if (isOriginallyBlack) {
    __rbt_deleteReBalance (pBalancePivot, pBalancePivotParent);
  }

  --_size;
  return true;
}


template <
    typename                                                            __ElementType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __Comparator,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyEqualsComparator,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __RedBlackTree <
    __ElementType, __KeyType, __Comparator,
    __keyExtractor, __keyEqualsComparator, __nodeDestructor
>::__rbt_remove (__KeyType const& key) noexcept -> bool {
  if (__rbt_empty()) {
    return false;
  }

  auto pToBeRemoved = _pRoot;
  while (pToBeRemoved != nullptr) {
    if (__keyEqualsComparator (key, __keyExtractor (pToBeRemoved->_data))) {
      __rbt_removeAt (pToBeRemoved);
      return true;
    }

    if (_keyLowerComparator (key, __keyExtractor (pToBeRemoved->_data))) {
      pToBeRemoved = pToBeRemoved->_pLeft;
    } else {
      pToBeRemoved = pToBeRemoved->_pRight;
    }
  }

  return false;
}


template <
    typename                                                            __ElementType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __Comparator,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyEqualsComparator,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_OptimalInline auto __RedBlackTree <
    __ElementType, __KeyType, __Comparator,
    __keyExtractor, __keyEqualsComparator, __nodeDestructor
>::__rbt_removeIterator (
    AbstractRedBlackTreeIterator <__ElementType> const& iterator
) noexcept -> bool {
  auto pToBeRemoved = iterator._pCurrentNode;
  if (pToBeRemoved == nullptr) {
    return false;
  }

  return __rbt_removeAt (pToBeRemoved);
}


template <
    typename                                                            __ElementType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __Comparator,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyEqualsComparator,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_OptimalInline auto __RedBlackTree <
    __ElementType, __KeyType, __Comparator,
    __keyExtractor, __keyEqualsComparator, __nodeDestructor
>::__rbt_removeConstIterator (
    AbstractRedBlackTreeConstIterator <__ElementType> const& iterator
) noexcept -> bool {
  auto pToBeRemoved = const_cast <__rbt_NodeType*> (iterator._pCurrentNode);
  if (pToBeRemoved == nullptr) {
    return false;
  }

  return __rbt_removeAt (pToBeRemoved);
}


template <
    typename                                                            __ElementType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __Comparator,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyEqualsComparator,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_OptimalInline auto __RedBlackTree <
    __ElementType, __KeyType, __Comparator,
    __keyExtractor, __keyEqualsComparator, __nodeDestructor
>::__rbt_removeIteratorArray (
    AbstractRedBlackTreeIterator <__ElementType> const* const*  iteratorArray,
    Size                                                        iteratorCount
) noexcept -> Size {
  Size removeCount = 0u;
  for (auto index = 0u; index < iteratorCount; ++index) {
    if (__rbt_removeIterator (*iteratorArray [index])) {
      ++removeCount;
    }
  }

  return removeCount;
}


template <
    typename                                                            __ElementType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __Comparator,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyEqualsComparator,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_OptimalInline auto __RedBlackTree <
    __ElementType, __KeyType, __Comparator,
    __keyExtractor, __keyEqualsComparator, __nodeDestructor
>::__rbt_removeConstIteratorArray (
    AbstractRedBlackTreeConstIterator <__ElementType> const* const* iteratorArray,
    Size                                                            iteratorCount
) noexcept -> Size {
  Size removeCount = 0u;
  for (auto index = 0u; index < iteratorCount; ++index) {
    if (__rbt_removeConstIterator (*iteratorArray [index])) {
      ++removeCount;
    }
  }

  return removeCount;
}


template <
    typename                                                            __ElementType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __Comparator,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyEqualsComparator,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __RedBlackTree <
    __ElementType, __KeyType, __Comparator,
    __keyExtractor, __keyEqualsComparator, __nodeDestructor
>::__rbt_clear () noexcept -> void {
  if (__rbt_empty())
    return;

  auto pCurrentNode = _pRoot;
  while (pCurrentNode != nullptr) {
    if (pCurrentNode->_pLeft != nullptr) {
      pCurrentNode = pCurrentNode->_pLeft;
    } else if (pCurrentNode->_pRight != nullptr) {
      pCurrentNode = pCurrentNode->_pRight;
    } else {

      auto pToBeDeleted   = pCurrentNode;
      pCurrentNode        = pCurrentNode->_pParent;
      if (pToBeDeleted != _pRoot) {
        if (__rbt_isLeftChild (pToBeDeleted, pToBeDeleted->_pParent)) {
          pCurrentNode->_pLeft    = nullptr;
        } else {
          pCurrentNode->_pRight   = nullptr;
        }
      }
      __rbt_freeNode (pToBeDeleted);
    }
  }

  _size = 0u;
  _pRoot = nullptr;
}


template <
    typename                                                            __ElementType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __Comparator,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyEqualsComparator,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> constexpr auto __RedBlackTree <
    __ElementType, __KeyType, __Comparator,
    __keyExtractor, __keyEqualsComparator, __nodeDestructor
>::__rbt_size () const noexcept -> Size {
  return _size;
}


template <
    typename                                                            __ElementType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __Comparator,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyEqualsComparator,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_cpplang_ConstexprConditioned auto __RedBlackTree <
    __ElementType, __KeyType, __Comparator,
    __keyExtractor, __keyEqualsComparator, __nodeDestructor
>::__rbt_equals (__RedBlackTree const& other) const noexcept -> bool {
  if (this == &other) {
    return true;
  }

  if (__rbt_empty()) {
    return other.__rbt_empty();
  }

  if (_size != other._size) {
    return false;
  }

  auto pTraversalThis  = _pRoot;
  auto pTraversalOther = other._pRoot;
  enum { _down, _upOrDown, _up } traversalDirection = _down;

  while (pTraversalThis != nullptr) {
    if (pTraversalOther == nullptr) {
      return false;
    }

    if (!__keyEqualsComparator (__keyExtractor (pTraversalThis->_data), __keyExtractor (pTraversalOther->_data))) {
      return false;
    }

    switch (traversalDirection) {
      case _down: {
        if (pTraversalThis->_pLeft != nullptr) {
          pTraversalThis  = pTraversalThis->_pLeft;
          pTraversalOther = pTraversalOther->_pLeft;
          break;
        }

        if (pTraversalOther->_pLeft != nullptr) {
          return false;
        }

        if (pTraversalThis->_pRight != nullptr) {
          pTraversalThis  = pTraversalThis->_pRight;
          pTraversalOther = pTraversalOther->_pRight;
          break;
        }

        if (pTraversalOther->_pRight != nullptr) {
          return false;
        }

        if (__rbt_isLeftChild (pTraversalThis, pTraversalThis->_pParent)) {
          traversalDirection = _upOrDown;
        } else {
          traversalDirection = _up;
        }
        break;
      }

      case _upOrDown: {
        if (pTraversalThis->_pRight != nullptr) {
          pTraversalThis     = pTraversalThis->_pRight;
          pTraversalOther    = pTraversalOther->_pRight;
          traversalDirection = _down;
          break;
        }

        if (pTraversalOther->_pRight != nullptr) {
          return false;
        }

        if (__rbt_isRightChild (pTraversalThis, pTraversalThis->_pParent)) {
          traversalDirection = _up;
        }

        pTraversalThis  = pTraversalThis->_pParent;
        pTraversalOther = pTraversalOther->_pParent;
        break;
      }
      case _up: {
        if (__rbt_isLeftChild (pTraversalThis, pTraversalThis->_pParent)) {
          traversalDirection = _upOrDown;
        }

        pTraversalThis  = pTraversalThis->_pParent;
        pTraversalOther = pTraversalOther->_pParent;
        break;
      }
    }
  }

  return true;
}



template <
    typename                                                            __ElementType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __Comparator,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyEqualsComparator,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> template <
    cds::functional::ConsumerFunction < __ElementType &, __ElementType const & >    __copy // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_OptimalInline auto __RedBlackTree <
    __ElementType, __KeyType, __Comparator,
    __keyExtractor, __keyEqualsComparator, __nodeDestructor
>:: __rbt_copy (__RedBlackTree const& tree) noexcept(false) -> void {
  if (this == &tree) {
    return;
  }

  __rbt_clear();
  __rbt_copyCleared <__copy> (tree);
}


template <
    typename                                                                  __ElementType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                  __KeyType,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                                  __Comparator,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&>       __keyExtractor,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>        __keyEqualsComparator,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                             __nodeDestructor        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> template <
    cds::functional::ConsumerFunction <__ElementType&, __ElementType const&>  __copy // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> auto __RedBlackTree <
    __ElementType, __KeyType, __Comparator,
    __keyExtractor, __keyEqualsComparator, __nodeDestructor
>:: __rbt_copyCleared (__RedBlackTree const& tree) noexcept(false) -> void {
  if (tree.__rbt_empty()) {
    return;
  }

  auto pSource      = tree._pRoot;
  auto pDestination = __rbt_allocateNode();
  _pRoot            = pDestination;
  while (pSource != nullptr) {

    if (pSource->_pLeft != nullptr && pDestination->_pLeft == nullptr) {
      pSource = pSource->_pLeft;
      pDestination->_pLeft = __RedBlackTree::__rbt_allocateNode();
      pDestination->_pLeft->_pParent = pDestination;
      pDestination = pDestination->_pLeft;
    } else if (pSource->_pRight != nullptr && pDestination->_pRight == nullptr) {
      pSource = pSource->_pRight;
      pDestination->_pRight = __RedBlackTree::__rbt_allocateNode();
      pDestination->_pRight->_pParent = pDestination;
      pDestination = pDestination->_pRight;
    } else {
      __copy (pDestination->_data, pSource->_data);
      pDestination->_colour = pSource->_colour;
      pDestination = pDestination->_pParent;
      pSource = pSource->_pParent;
    }
  }

  _size = tree._size;
}


template <
    typename                                                            __ElementType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __Comparator,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyEqualsComparator,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_OptimalInline auto __RedBlackTree <
    __ElementType, __KeyType, __Comparator,
    __keyExtractor, __keyEqualsComparator, __nodeDestructor
>::__rbt_move (__RedBlackTree&& tree) noexcept -> void {
  if (this == &tree) {
    return;
  }

  __rbt_clear();
  __rbt_moveCleared (std::move (tree));
}


template <
    typename                                                            __ElementType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __Comparator,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyEqualsComparator,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_cpplang_ConstexprConditioned auto __RedBlackTree <
    __ElementType, __KeyType, __Comparator,
    __keyExtractor, __keyEqualsComparator, __nodeDestructor
>::__rbt_moveCleared (
    __RedBlackTree&& tree
) noexcept -> void {
  _size   = cds::exchange (tree._size, 0u);
  _pRoot  = cds::exchange (tree._pRoot, nullptr);
}


template <
    typename                                                            __ElementType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __Comparator,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyEqualsComparator,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_OptimalInline auto __RedBlackTree <
    __ElementType, __KeyType, __Comparator,
    __keyExtractor, __keyEqualsComparator, __nodeDestructor
>::__rbt_new (
    __ElementType const*  pReferenceElement,
    bool*                 pIsNew
) noexcept(false) -> __ElementType* {
  return __rbt_get (__keyExtractor (*pReferenceElement), pIsNew);
}


template <
    typename                                                            __ElementType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __Comparator,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyEqualsComparator,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_cpplang_ConstexprConditioned auto __RedBlackTree <
    __ElementType, __KeyType, __Comparator,
    __keyExtractor, __keyEqualsComparator, __nodeDestructor
>::__rbt_findNode (__KeyType const& key) const noexcept -> __rbt_NodeType* {
  if (__rbt_empty()) {
    return nullptr;
  }

  auto pSearch = _pRoot;
  while (pSearch != nullptr) {
    if (__keyEqualsComparator (__keyExtractor (pSearch->_data), key)) {
      return pSearch;
    }

    if (_keyLowerComparator (key, __keyExtractor (pSearch->_data))) {
      pSearch = pSearch->_pLeft;
    } else {
      pSearch = pSearch->_pRight;
    }
  }

  return nullptr;
}


template <
    typename                                                            __ElementType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __Comparator,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyEqualsComparator,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_cpplang_ConstexprConditioned auto __RedBlackTree <
    __ElementType, __KeyType, __Comparator,
    __keyExtractor, __keyEqualsComparator, __nodeDestructor
>::__rbt_findIterator (__KeyType const& key) noexcept -> __rbt_Iterator {
  if (__rbt_empty()) {
    return __rbt_Iterator();
  }

  auto pSearch = __rbt_findNode (key);
  if ( pSearch != nullptr) {
    return __rbt_Iterator (_pRoot, pSearch);
  }

  return __rbt_Iterator();
}


template <
    typename                                                            __ElementType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __Comparator,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyEqualsComparator,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_cpplang_ConstexprConditioned auto __RedBlackTree <
    __ElementType, __KeyType, __Comparator,
    __keyExtractor, __keyEqualsComparator, __nodeDestructor
>::__rbt_findIteratorConst (
    __KeyType const& key
) const noexcept -> __rbt_ConstIterator {
  if (__rbt_empty()) {
    return __rbt_ConstIterator();
  }

  auto pSearch = __rbt_findNode (key);
  if (pSearch != nullptr) {
    return __rbt_ConstIterator (_pRoot, pSearch);
  }

  return __rbt_ConstIterator();
}


template <
    typename                                                            __ElementType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __Comparator,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyEqualsComparator,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_cpplang_ConstexprConditioned auto __RedBlackTree <
    __ElementType, __KeyType, __Comparator,
    __keyExtractor, __keyEqualsComparator, __nodeDestructor
>::__rbt_begin () noexcept -> __rbt_Iterator {
  if (__rbt_empty()) {
    return __rbt_Iterator (nullptr, nullptr);
  }

  auto pBegin = _pRoot;
  while (pBegin->_pLeft != nullptr) {
    pBegin = pBegin->_pLeft;
  }

  return __rbt_Iterator (_pRoot, pBegin);
}


template <
    typename                                                            __ElementType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __Comparator,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyEqualsComparator,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_cpplang_ConstexprConditioned auto __RedBlackTree <
    __ElementType, __KeyType, __Comparator,
    __keyExtractor, __keyEqualsComparator, __nodeDestructor
>::__rbt_end () noexcept -> __rbt_Iterator {
  return __rbt_Iterator (_pRoot, nullptr);
}


template <
    typename                                                            __ElementType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __Comparator,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyEqualsComparator,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_cpplang_ConstexprConditioned auto __RedBlackTree <
    __ElementType, __KeyType, __Comparator,
    __keyExtractor, __keyEqualsComparator, __nodeDestructor
>::__rbt_rbegin () noexcept -> __rbt_ReverseIterator {
  if (__rbt_empty()) {
    return __rbt_ReverseIterator (nullptr, nullptr);
  }

  auto prEnd = _pRoot;
  while (prEnd->_pRight != nullptr) {
    prEnd = prEnd->_pRight;
  }

  return __rbt_ReverseIterator (_pRoot, prEnd);
}


template <
    typename                                                            __ElementType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __Comparator,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyEqualsComparator,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_cpplang_ConstexprConditioned auto __RedBlackTree <
    __ElementType, __KeyType, __Comparator,
    __keyExtractor, __keyEqualsComparator, __nodeDestructor
>::__rbt_rend () noexcept -> __rbt_ReverseIterator {
  return __rbt_ReverseIterator (_pRoot, nullptr);
}


template <
    typename                                                            __ElementType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __Comparator,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyEqualsComparator,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_cpplang_ConstexprConditioned auto __RedBlackTree <
    __ElementType, __KeyType, __Comparator,
    __keyExtractor, __keyEqualsComparator, __nodeDestructor
>::__rbt_cbegin () const noexcept -> __rbt_ConstIterator {
  if (__rbt_empty()) {
    return __rbt_ConstIterator (nullptr, nullptr);
  }

  auto pcBegin = _pRoot;
  while (pcBegin->_pLeft != nullptr) {
    pcBegin = pcBegin->_pLeft;
  }

  return __rbt_ConstIterator (_pRoot, pcBegin);
}


template <
    typename                                                            __ElementType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __Comparator,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyEqualsComparator,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> constexpr auto __RedBlackTree <
    __ElementType, __KeyType, __Comparator,
    __keyExtractor, __keyEqualsComparator, __nodeDestructor
>::__rbt_cend () const noexcept -> __rbt_ConstIterator {
  return __rbt_ConstIterator (_pRoot, nullptr);
}


template <
    typename                                                            __ElementType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __Comparator,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyEqualsComparator,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> __CDS_cpplang_ConstexprConditioned auto __RedBlackTree <
    __ElementType, __KeyType, __Comparator,
    __keyExtractor, __keyEqualsComparator, __nodeDestructor
>::__rbt_crbegin () const noexcept -> __rbt_ReverseConstIterator {
  if (__rbt_empty()) {
    return __rbt_ReverseConstIterator (nullptr, nullptr);
  }

  auto pcrBegin = _pRoot;
  while (pcrBegin->_pRight != nullptr) {
    pcrBegin = pcrBegin->_pRight;
  }

  return __rbt_ReverseConstIterator (_pRoot, pcrBegin);
}


template <
    typename                                                            __ElementType,          // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __KeyType,              // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                                                            __Comparator,           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::MapperFunction <__KeyType const&, __ElementType const&> __keyExtractor,         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::PredicateFunction <__KeyType const&, __KeyType const&>  __keyEqualsComparator,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    functional::ConsumerFunction <__ElementType&>                       __nodeDestructor        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> constexpr auto __RedBlackTree <
    __ElementType, __KeyType, __Comparator,
    __keyExtractor, __keyEqualsComparator, __nodeDestructor
>::__rbt_crend () const noexcept -> __rbt_ReverseConstIterator {
  return __rbt_ReverseConstIterator (_pRoot, nullptr);
}
} // namespace __impl
} // namespace __hidden
} // namespace cds

#endif // __CDS_SHARED_RED_BLACK_TREE_IMPL_HPP__