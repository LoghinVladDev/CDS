//
// Created by loghin on 18/07/22.
//

#ifndef __CDS_SHARED_NODE_ITERATOR_IMPL_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_SHARED_NODE_ITERATOR_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

namespace cds {

template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr UnidirectionalNodeIterator <__ElementType>::UnidirectionalNodeIterator () noexcept = default;


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_MaybeUnused constexpr UnidirectionalNodeIterator <__ElementType>::UnidirectionalNodeIterator (
    Node* pCurrentNode
) noexcept :
    _pCurrentNode (pCurrentNode) {
  // copy current and previous node values
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_MaybeUnused constexpr UnidirectionalNodeIterator <__ElementType>::UnidirectionalNodeIterator (
    UnidirectionalNodeIterator const& iterator
) noexcept :
    _pCurrentNode (iterator._pCurrentNode) {
  // copy current and previous node values from iterator
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_MaybeUnused constexpr UnidirectionalNodeIterator <__ElementType>::UnidirectionalNodeIterator (
    UnidirectionalNodeIterator&& iterator
) noexcept :
    _pCurrentNode (cds::exchange (iterator._pCurrentNode, nullptr)) {
  // move current and previous node values from iterator
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto UnidirectionalNodeIterator <__ElementType>::operator = (
    UnidirectionalNodeIterator const& iterator
) noexcept -> UnidirectionalNodeIterator& {
  // if given iterator is the same as current, copy unnecessary
  if (this == &iterator) {
    return *this;
  }

  // otherwise, copy current and previous node
  _pCurrentNode     = iterator._pCurrentNode;
  return *this;
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto UnidirectionalNodeIterator <__ElementType>::operator = (
    UnidirectionalNodeIterator&& iterator
) noexcept -> UnidirectionalNodeIterator& {
  // if given iterator is the same as current, move unnecessary
  if (this == &iterator) {
    return *this;
  }

  // otherwise, move current and previous node
  _pCurrentNode     = cds::exchange ( iterator._pCurrentNode, nullptr );
  return * this;
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto UnidirectionalNodeIterator <__ElementType>::operator* () const noexcept -> RVal& {
  // return reference to the element at the current node
  return _pCurrentNode->_data;
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto UnidirectionalNodeIterator <__ElementType>::operator -> () const noexcept -> RVal* {
  // return the address of the element at the current node 
  return &_pCurrentNode->_data;
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto UnidirectionalNodeIterator <__ElementType>::operator == (
    UnidirectionalNodeIterator const& iterator
) const noexcept -> bool {
  // Iterators are equal if both have current nodes valid and equal OR
  // null current nodes and equal previous nodes ( end of list or null )
  return _pCurrentNode == iterator._pCurrentNode;
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto UnidirectionalNodeIterator <__ElementType>::operator != (
    UnidirectionalNodeIterator const& iterator
) const noexcept -> bool {
  // iterators not equal when ! equals ( this, iterator ) 
  return !operator == (iterator);
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto UnidirectionalNodeIterator <__ElementType>::operator ++ () noexcept -> UnidirectionalNodeIterator & {
  // current node becomes the next 
  _pCurrentNode = _pCurrentNode == nullptr ? nullptr : _pCurrentNode->_pNext;
  return * this;
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto UnidirectionalNodeIterator <__ElementType>::operator ++ (int) noexcept -> UnidirectionalNodeIterator {
  // make a copy of this iterator, advance current one and return copy 
  auto copy = * this;
  _pCurrentNode     = _pCurrentNode == nullptr ? nullptr : _pCurrentNode->_pNext;
  return copy;
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr UnidirectionalNodeIterator <__ElementType>::operator bool () const noexcept {
  // iterator is valid if current node is not null 
  // Special case in insert before. end value potentially valid 
  return _pCurrentNode != nullptr;
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr AbstractBidirectionalNodeIterator <__ElementType>::AbstractBidirectionalNodeIterator () noexcept = default;


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr AbstractBidirectionalNodeIterator <__ElementType>::AbstractBidirectionalNodeIterator (
    Node* pPreviousNode,
    Node* pCurrentNode
) noexcept :
    _pPreviousNode (pPreviousNode),
    _pCurrentNode (pCurrentNode) {
  // copy current and previous node values 
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr AbstractBidirectionalNodeIterator <__ElementType>::AbstractBidirectionalNodeIterator (
    AbstractBidirectionalNodeIterator const& iterator
) noexcept : AbstractBidirectionalNodeIterator(iterator._pPreviousNode, iterator._pCurrentNode) {
  // copy current and previous node values from iterator 
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr AbstractBidirectionalNodeIterator <__ElementType>::AbstractBidirectionalNodeIterator (
    AbstractBidirectionalNodeIterator&& iterator
) noexcept :
    _pPreviousNode (cds::exchange (iterator._pPreviousNode, nullptr)),
    _pCurrentNode (cds::exchange (iterator._pCurrentNode, nullptr)) {
  // move current and previous node values from iterator 
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto AbstractBidirectionalNodeIterator <__ElementType>::operator * () const noexcept -> RVal& {
  // return reference to the element at the current node 
  return _pCurrentNode->_data;
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto AbstractBidirectionalNodeIterator <__ElementType>::operator -> () const noexcept -> RVal* {
  // return the address of the element at the current node 
  return & _pCurrentNode->_data;
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto AbstractBidirectionalNodeIterator <__ElementType>::operator == (
    AbstractBidirectionalNodeIterator const & iterator
) const noexcept -> bool {
  // Iterators are equal if both have current nodes valid and equal OR null current nodes and equal previous nodes ( end of list or null ) 
  return
      (_pCurrentNode     == iterator._pCurrentNode &&
      _pCurrentNode     != nullptr) ||
      (_pCurrentNode     == iterator._pCurrentNode &&
      _pPreviousNode    == iterator._pPreviousNode);
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto AbstractBidirectionalNodeIterator <__ElementType>::operator != (
    AbstractBidirectionalNodeIterator const& iterator
) const noexcept -> bool {
  // iterators not equal when ! equals (this, iterator)
  return !operator == (iterator);
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr AbstractBidirectionalNodeIterator <__ElementType>::operator bool () const noexcept {
  // iterator is valid if current node is not null. 
  // Special case in insert before. end value potentially valid 
  return _pCurrentNode != nullptr || _pPreviousNode != nullptr;
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto AbstractBidirectionalNodeIterator <__ElementType>::advanceFwd() noexcept -> void {
  // previous node becomes the current one
  _pPreviousNode    = _pCurrentNode;
  // current node becomes the next
  _pCurrentNode     = _pCurrentNode == nullptr ? nullptr : _pCurrentNode->_pNext;
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto AbstractBidirectionalNodeIterator <__ElementType>::reverseFwd() noexcept -> void {
  // current node becomes the previous one
  _pCurrentNode     = _pPreviousNode;
//   the previous node becomes the one before it, if it was valid
  _pPreviousNode    = _pCurrentNode == nullptr ? nullptr : _pCurrentNode->_pPrevious;
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto AbstractBidirectionalNodeIterator <__ElementType>::advanceBwd() noexcept -> void {
  // previous node becomes the current one
  _pPreviousNode    = _pCurrentNode;
  // current node becomes the next
  _pCurrentNode     = _pCurrentNode == nullptr ? nullptr : _pCurrentNode->_pPrevious;
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto AbstractBidirectionalNodeIterator <__ElementType>::reverseBwd() noexcept -> void {
  // current node becomes the previous one
  _pCurrentNode     = _pPreviousNode;
//   the previous node becomes the one before it, if it was valid
  _pPreviousNode    = _pCurrentNode == nullptr ? nullptr : _pCurrentNode->_pNext;
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto ForwardBidirectionalNodeIterator <__ElementType>::operator == (
    ForwardBidirectionalNodeIterator const & iterator
) const noexcept -> bool {
  return AbstractBidirectionalNodeIterator <__ElementType>::operator== (iterator);
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto ForwardBidirectionalNodeIterator <__ElementType>::operator != (
    ForwardBidirectionalNodeIterator const & iterator
) const noexcept -> bool {
  return AbstractBidirectionalNodeIterator <__ElementType>::operator!= (iterator);
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto ForwardBidirectionalNodeIterator <__ElementType>::operator ++ () noexcept -> ForwardBidirectionalNodeIterator & {
  this->advanceFwd();
  return *this;
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto ForwardBidirectionalNodeIterator <__ElementType>::operator ++ (int) noexcept -> ForwardBidirectionalNodeIterator {
  auto copy = *this;
  this->advanceFwd();
  return copy;
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto ForwardBidirectionalNodeIterator <__ElementType>::operator -- () noexcept -> ForwardBidirectionalNodeIterator & {
  this->reverseFwd();
  return *this;
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto ForwardBidirectionalNodeIterator <__ElementType>::operator -- (int) noexcept -> ForwardBidirectionalNodeIterator {
  auto copy = *this;
  this->reverseFwd();
  return copy;
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto BackwardBidirectionalNodeIterator <__ElementType>::operator == (
    BackwardBidirectionalNodeIterator const & iterator
) const noexcept -> bool {
  return AbstractBidirectionalNodeIterator <__ElementType>::operator== (iterator);
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto BackwardBidirectionalNodeIterator <__ElementType>::operator != (
    BackwardBidirectionalNodeIterator const & iterator
) const noexcept -> bool {
  return AbstractBidirectionalNodeIterator <__ElementType>::operator!= (iterator);
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto BackwardBidirectionalNodeIterator <__ElementType>::operator ++ () noexcept -> BackwardBidirectionalNodeIterator & {
  this->advanceBwd();
  return *this;
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto BackwardBidirectionalNodeIterator <__ElementType>::operator ++ (int) noexcept -> BackwardBidirectionalNodeIterator {
  auto copy = *this;
  this->advanceBwd();
  return copy;
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto BackwardBidirectionalNodeIterator <__ElementType>::operator -- () noexcept -> BackwardBidirectionalNodeIterator & {
  this->reverseBwd();
  return *this;
}


template <typename __ElementType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto BackwardBidirectionalNodeIterator <__ElementType>::operator -- (int) noexcept -> BackwardBidirectionalNodeIterator {
  auto copy = *this;
  this->reverseBwd();
  return copy;
}
} // namespace cds 

#endif // __CDS_SHARED_NODE_ITERATOR_IMPL_HPP__ 
