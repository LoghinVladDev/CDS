// NOLINT(llvm-header-guard)
// Created by loghin on 06/10/22.
//

#ifndef __CDS_LINKED_HASH_SET_IMPL_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_LINKED_HASH_SET_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {

template <typename __ElementType, typename __Hasher> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto LinkedHashSet <__ElementType, __Hasher>::__iicch_obtainGenericHandler (
    __hidden::__impl::__IterableInternalRequestType requestType
) noexcept -> __GenericHandler {
  return __ss_handlers() [static_cast <uint32> (requestType)];
}


template <typename __ElementType, typename __Hasher> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto LinkedHashSet <__ElementType, __Hasher>::__iicch_obtainGenericConstHandler (
    __hidden::__impl::__IterableInternalRequestType requestType
) const noexcept -> __GenericConstHandler {
  return __ss_constHandlers() [static_cast <uint32> (requestType)];
}


template <typename __ElementType, typename __Hasher> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto LinkedHashSet <__ElementType, __Hasher>::__cbegin (
    LinkedHashSet const* pObject
) noexcept -> __hidden::__impl ::__AbstractDelegateIterator <__ElementType const>* {
  return Memory::instance().create <__hidden::__impl::__DelegateIterator <__ElementType const, ConstIterator>> (
      ConstIterator (pObject->__sll_cbegin())
  );
}


template <typename __ElementType, typename __Hasher> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto LinkedHashSet <__ElementType, __Hasher>::__cend (
    LinkedHashSet const *pObject
) noexcept -> __hidden::__impl ::__AbstractDelegateIterator <__ElementType const>* {
  return Memory::instance().create <__hidden::__impl::__DelegateIterator <__ElementType const, ConstIterator>> (
      ConstIterator (pObject->__sll_cend())
  );
}


template <typename __ElementType, typename __Hasher> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto LinkedHashSet <__ElementType, __Hasher>::__cbeginLocal (
    LinkedHashSet const* pObject
) noexcept -> ConstIterator {
  return ConstIterator (pObject->__sll_cbegin());
}


template <typename __ElementType, typename __Hasher> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto LinkedHashSet <__ElementType, __Hasher>::__cendLocal (
    LinkedHashSet const *pObject
) noexcept -> ConstIterator {
  return ConstIterator (pObject->__sll_cend());
}


template <typename __ElementType, typename __Hasher> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto LinkedHashSet <__ElementType, __Hasher>::__newAddress (
    LinkedHashSet*        pObject,
    __ElementType const*  pReferenceElement,
    bool*                 pNewElementCreated
) noexcept -> __ElementType* {
  auto pNewElement = pObject->__ht_new (pReferenceElement, pNewElementCreated);
  if (* pNewElementCreated) {
    (void) new (pObject->__sll_newBack()) __ElementType* (pNewElement);
  }

  return pNewElement;
}


template <typename __ElementType, typename __Hasher> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto LinkedHashSet <__ElementType, __Hasher>::__removeConst (
    LinkedHashSet*        pObject,
    ConstIterator const*  pIterator
) noexcept -> bool {
  if (
      pIterator == nullptr || !static_cast <bool> (*pIterator) ||
      (*pIterator).iterator() == pObject->__sll_cend()
  ) {
    return false;
  }

  auto const pElement = *(*pIterator).iterator();
  if (pObject->__sll_removeConstIterator ((*pIterator).iterator())) {
    return pObject->__ht_remove (*pElement);
  }

  return false;
}


template <typename __ElementType, typename __Hasher> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto LinkedHashSet <__ElementType, __Hasher>::__removeConstArray (
    LinkedHashSet*              pObject,
    ConstIterator const* const* ppIterators,
    Size                        iteratorArraySize
) noexcept -> Size {
  using __EAlloc = __hidden::__impl::__allocation::__PrimitiveAlloc <__ElementType const*>;                                               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using __SLLItAlloc = __hidden::__impl::__allocation::__PrimitiveAlloc <typename LinkedListImplementation::__sll_ConstIterator const*>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  auto pRemovedElementArray   = __EAlloc::__alloc (iteratorArraySize);
  auto pSllIteratorPtrArray   = __SLLItAlloc::__alloc (iteratorArraySize);
  for (Size index = 0u; index < iteratorArraySize; ++index) {
    pSllIteratorPtrArray [index] = &(*ppIterators [index]).iterator(); // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    pRemovedElementArray [index] = *(*pSllIteratorPtrArray [index]);
  }

  auto removedCount = pObject->__sll_removeConstIteratorArray (&pSllIteratorPtrArray [0u], iteratorArraySize);
  for (Size index = 0u; index < iteratorArraySize; ++ index ) {
    pObject->__ht_remove (*pRemovedElementArray [index]);
  }

  __EAlloc::__free (pRemovedElementArray);
  __SLLItAlloc::__free (pSllIteratorPtrArray);
  return removedCount;
}


template <typename __ElementType, typename __Hasher> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto LinkedHashSet <__ElementType, __Hasher>::__findConst (
    LinkedHashSet const* pObject,
    __ElementType const& element
) noexcept -> __hidden::__impl::__AbstractDelegateIterator <__ElementType const>* {
  using Delegate = __hidden::__impl::__DelegateIterator <__ElementType const, ConstIterator>;
  if (pObject->__ht_getConst (element) == nullptr) {
    return Memory::instance().create <Delegate> (pObject->cend());
  }

  for (auto iterator = pObject->cbegin(), end = pObject->cend(); iterator != end; ++iterator) { // NOLINT(clion-misra-cpp2008-8-0-1)
    if (cds::meta::equals (*iterator, element)) {
      return Memory::instance().create <Delegate> (iterator);
    }
  }

  return Memory::instance().create <Delegate> (pObject->cend());
}


template <typename __ElementType, typename __Hasher> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto LinkedHashSet <__ElementType, __Hasher>::__findConstLocal (
    LinkedHashSet const* pObject,
    __ElementType const& element
) noexcept -> ConstIterator {
  if (pObject->__ht_getConst (element) == nullptr) {
    return cend();
  }

  for (auto iterator = pObject->cbegin(), end = pObject->cend(); iterator != end; ++iterator) {  // NOLINT(clion-misra-cpp2008-8-0-1)
    if (cds::meta::equals (*iterator, element)) {
      return iterator;
    }
  }

  return pObject->cend();
}


template <typename __ElementType, typename __Hasher> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr LinkedHashSet <__ElementType, __Hasher>::LinkedHashSet () noexcept = default;


template <typename __ElementType, typename __Hasher> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline LinkedHashSet <__ElementType, __Hasher>::LinkedHashSet (LinkedHashSet const& set) noexcept(false) {
  // Copy of each not possible, linked list references hash table elements from other set
  for (auto iterator = set.cbegin(), end = set.cend(); iterator != end; ++iterator) {  // NOLINT(clion-misra-cpp2008-8-0-1)
    insert (*iterator);
  }
}


template <typename __ElementType, typename __Hasher> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr LinkedHashSet <__ElementType, __Hasher>::LinkedHashSet (LinkedHashSet&& set) noexcept :
    HashTableImplementation (std::move (set)),
    LinkedListImplementation (std::move (set)) {

}


template <typename __ElementType, typename __Hasher> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr LinkedHashSet <__ElementType, __Hasher>::LinkedHashSet (__Hasher const& hasher) noexcept :
    HashTableImplementation (hasher) {

}


template <typename __ElementType, typename __Hasher> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename __IteratorType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __TElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value>
> __CDS_OptimalInline LinkedHashSet <__ElementType, __Hasher>::LinkedHashSet (
    __IteratorType const& begin,
    __IteratorType const& end,
    Size                  count
) noexcept(false) {
  (void) count;
  for (auto iterator = begin; iterator != end; ++iterator) {
    insert (*iterator);
  }
}


template <typename __ElementType, typename __Hasher> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename __IteratorType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __TElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value>
> __CDS_OptimalInline LinkedHashSet <__ElementType, __Hasher>::LinkedHashSet (
    __Hasher const&       hasher,
    __IteratorType const& begin,
    __IteratorType const& end,
    Size                  count
) noexcept(false) :
    HashTableImplementation (hasher) {
  (void) count;
  for (auto iterator = begin; iterator != end; ++iterator) {
    insert (iterator);
  }
}


template <typename __ElementType, typename __Hasher> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename __TElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value>
> __CDS_OptimalInline LinkedHashSet <__ElementType, __Hasher>::LinkedHashSet (
    std::initializer_list < __ElementType > const& initializerList
) noexcept(false) :
    LinkedHashSet (initializerList.begin (), initializerList.end (), initializerList.size()) {

}


template <typename __ElementType, typename __Hasher> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <
    typename __TElementType,    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::meta::EnableIf <cds::meta::IsCopyConstructible <__TElementType>::value>
> __CDS_OptimalInline LinkedHashSet <__ElementType, __Hasher>::LinkedHashSet (
    __Hasher const&                               hasher,
    std::initializer_list <__ElementType> const&  initializerList
) noexcept(false) :
    LinkedHashSet (hasher, initializerList.begin (), initializerList.end (), initializerList.size()) {

}


template <typename __ElementType, typename __Hasher> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __IterableType>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline LinkedHashSet <__ElementType, __Hasher>::LinkedHashSet (
    __IterableType const& iterable
) noexcept(false) :
    LinkedHashSet (iterable.begin (), iterable.end ()) {

}


template <typename __ElementType, typename __Hasher> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __IterableType>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline LinkedHashSet <__ElementType, __Hasher>::LinkedHashSet (
    __Hasher const&       hasher,
    __IterableType const& iterable
) noexcept(false) :
    LinkedHashSet (hasher, iterable.begin (), iterable.end ()) {

}


template <typename __ElementType, typename __Hasher> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline LinkedHashSet <__ElementType, __Hasher>::~LinkedHashSet () noexcept {
  __ht_clear ();
  __sll_clear ();
}


template <typename __ElementType, typename __Hasher> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto LinkedHashSet <__ElementType, __Hasher>::operator = (
    LinkedHashSet const& set
) noexcept(false) -> LinkedHashSet& {
  if (this == &set) {
    return *this;
  }

  __sll_clear ();
  __ht_clear ();
  // Copy of each not possible, linked list references hash table elements from other set
  for (auto iterator = set.cbegin(), end = set.cend(); iterator != end; ++iterator) {  // NOLINT(clion-misra-cpp2008-8-0-1)
    insert (*iterator);
  }

  return *this;
}


template <typename __ElementType, typename __Hasher> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto LinkedHashSet <__ElementType, __Hasher>::operator = (
    LinkedHashSet&& set
) noexcept -> LinkedHashSet& {
  if (this == &set) {
    return *this;
  }

  __ht_move (std::move (set));
  __sll_move (std::move (set));
  return *this;
}


template <typename __ElementType, typename __Hasher> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto LinkedHashSet <__ElementType, __Hasher>::operator = (
    std::initializer_list <__ElementType> const& initializerList
) noexcept(false) -> LinkedHashSet& {
  __ht_clear ();
  __sll_clear ();
  for (auto iterator = initializerList.begin(), end = initializerList.end(); iterator != end; ++iterator) {    // NOLINT(clion-misra-cpp2008-8-0-1)
    (void) insert (*iterator);
  }

  return *this;
}


template <typename __ElementType, typename __Hasher> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __IterableType>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto LinkedHashSet <__ElementType, __Hasher>::operator = (
    __IterableType const &iterable
) noexcept(false) -> LinkedHashSet& {
  if (this == &iterable) {
    return *this;
  }

  __ht_clear ();
  __sll_clear ();
  for (auto iterator = iterable.begin(), end = iterable.end(); iterator != end; ++iterator) {  // NOLINT(clion-misra-cpp2008-8-0-1)
    insert (*iterator);
  }
  return *this;
}


template <typename __ElementType, typename __Hasher> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto LinkedHashSet <__ElementType, __Hasher>::size () const noexcept -> Size {
  return __ht_size ();
}


template <typename __ElementType, typename __Hasher> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto LinkedHashSet <__ElementType, __Hasher>::clear () noexcept -> void {
  __ht_clear();
  __sll_clear();
}


template <typename __ElementType, typename __Hasher> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto LinkedHashSet <__ElementType, __Hasher>::remove (
    __ElementType const& element
) noexcept -> bool {
  auto const pElement = __ht_removeGetPtr (element);
  return pElement != nullptr && __sll_remove (pElement);
}


template <typename __ElementType, typename __Hasher> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto LinkedHashSet <__ElementType, __Hasher>::contains (
    __ElementType const& element
) const noexcept -> bool {
  return __ht_getConst (element) != nullptr;
}


template <typename __ElementType, typename __Hasher> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto LinkedHashSet <__ElementType, __Hasher>::operator == (
    LinkedHashSet const& set
) const noexcept -> bool {
  if (this == &set) {
    return true;
  }

  return __ht_equals (set);
}


template <typename __ElementType, typename __Hasher> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprConditioned auto LinkedHashSet <__ElementType, __Hasher>::operator != (
    LinkedHashSet const& set
) const noexcept -> bool {
  if (this == &set) {
    return false;
  }

  return !__ht_equals (set); // NOLINT(clion-misra-cpp2008-5-3-1)
}

} // namespace cds

#endif // __CDS_LINKED_HASH_SET_IMPL_HPP__
