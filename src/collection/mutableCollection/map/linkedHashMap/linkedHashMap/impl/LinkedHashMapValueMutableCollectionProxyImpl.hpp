// NOLINT(llvm-header-guard)
// Created by loghin on 09/10/22.
//

#ifndef __CDS_LINKED_HASH_MAP_VALUE_MUTABLE_COLLECTION_PROXY_IMPL_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_LINKED_HASH_MAP_VALUE_MUTABLE_COLLECTION_PROXY_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {

template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::ValueMutableCollectionProxy::__iicch_obtainGenericHandler (
    __hidden::__impl::__IterableInternalRequestType requestType
) noexcept -> __GenericHandler {
  return __mcs_handlers() [static_cast <uint32> (requestType)];
}


template <typename __KeyType, typename __ValueType, typename __Hasher>__CDS_cpplang_ConstexprOverride auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::ValueMutableCollectionProxy::__iicch_obtainGenericConstHandler (
    __hidden::__impl::__IterableInternalRequestType requestType
) const noexcept -> __GenericConstHandler {
  return __mcs_constHandlers() [static_cast <uint32> (requestType)];
}


template <typename __KeyType, typename __ValueType, typename __Hasher>constexpr LinkedHashMap <__KeyType, __ValueType, __Hasher>::ValueMutableCollectionProxy::ValueMutableCollectionProxy (
    LinkedHashMap < __KeyType, __ValueType, __Hasher >* pMap
) noexcept : AbstractValueMutableCollectionProxy (pMap) {

}


template <typename __KeyType, typename __ValueType, typename __Hasher>__CDS_cpplang_ConstexprDestructor LinkedHashMap <__KeyType, __ValueType, __Hasher>::ValueMutableCollectionProxy::~ValueMutableCollectionProxy () noexcept = default;


template <typename __KeyType, typename __ValueType, typename __Hasher>__CDS_OptimalInline auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::ValueMutableCollectionProxy::__begin (
    ValueMutableCollectionProxy* pObject
) noexcept -> __hidden::__impl ::__AbstractDelegateIterator <__ValueType> * {
  return Memory::instance().create <__hidden::__impl::__DelegateIterator <__ValueType, Iterator>> (
      Iterator (LinkedHashMapBase::__beginLocal (pObject->template map <LinkedHashMapBase> ()))
  );
}


template <typename __KeyType, typename __ValueType, typename __Hasher>__CDS_OptimalInline auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::ValueMutableCollectionProxy::__end (
    ValueMutableCollectionProxy* pObject
) noexcept -> __hidden::__impl ::__AbstractDelegateIterator <__ValueType>* {
  return Memory::instance().create <__hidden::__impl::__DelegateIterator <__ValueType, Iterator>> (
      Iterator (LinkedHashMapBase::__endLocal (pObject->template map <LinkedHashMapBase> ()))
  );
}


template <typename __KeyType, typename __ValueType, typename __Hasher>__CDS_OptimalInline auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::ValueMutableCollectionProxy::__cbegin (
    ValueMutableCollectionProxy const* pObject
) noexcept -> __hidden::__impl ::__AbstractDelegateIterator <__ValueType const>* {
  return Memory::instance().create <__hidden::__impl::__DelegateIterator <__ValueType const, ConstIterator>> (
      ConstIterator (LinkedHashMapBase::__cbeginLocal (pObject->template map <LinkedHashMapBase> ()))
  );
}


template <typename __KeyType, typename __ValueType, typename __Hasher>__CDS_OptimalInline auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::ValueMutableCollectionProxy::__cend (
    ValueMutableCollectionProxy const* pObject
) noexcept -> __hidden::__impl ::__AbstractDelegateIterator <__ValueType const>* {
  return Memory::instance().create <__hidden::__impl::__DelegateIterator <__ValueType const, ConstIterator>> (
      ConstIterator (LinkedHashMapBase::__cendLocal (pObject->template map <LinkedHashMapBase> ()))
  );
}


template <typename __KeyType, typename __ValueType, typename __Hasher>__CDS_cpplang_NonConstConstexprMemberFunction auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::ValueMutableCollectionProxy::__beginLocal (
    ValueMutableCollectionProxy* pObject
) noexcept -> Iterator {
  return Iterator (LinkedHashMapBase::__beginLocal (pObject->template map <LinkedHashMapBase> ()));
}


template <typename __KeyType, typename __ValueType, typename __Hasher>__CDS_cpplang_NonConstConstexprMemberFunction auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::ValueMutableCollectionProxy::__endLocal (
    ValueMutableCollectionProxy* pObject
) noexcept -> Iterator {
  return Iterator (LinkedHashMapBase::__endLocal (pObject->template map <LinkedHashMapBase> ()));
}


template <typename __KeyType, typename __ValueType, typename __Hasher>constexpr auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::ValueMutableCollectionProxy::__cbeginLocal (
    ValueMutableCollectionProxy const* pObject
) noexcept -> ConstIterator {
  return ConstIterator (LinkedHashMapBase::__cbeginLocal (pObject->template map <LinkedHashMapBase> ()));
}


template <typename __KeyType, typename __ValueType, typename __Hasher>constexpr auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::ValueMutableCollectionProxy::__cendLocal (
    ValueMutableCollectionProxy const* pObject
) noexcept -> ConstIterator {
  return ConstIterator (LinkedHashMapBase::__cendLocal (pObject->template map <LinkedHashMapBase> ()));
}


template <typename __KeyType, typename __ValueType, typename __Hasher>__CDS_OptimalInline auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::ValueMutableCollectionProxy::__remove (
    ValueMutableCollectionProxy*  pObject,
    Iterator const*               pIterator
) noexcept -> bool {
  return LinkedHashMapBase::__remove (pObject->template map <LinkedHashMapBase> (), &pIterator->iterator());
}


template <typename __KeyType, typename __ValueType, typename __Hasher>__CDS_OptimalInline auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::ValueMutableCollectionProxy::__removeConst (
    ValueMutableCollectionProxy*  pObject,
    ConstIterator const*          pIterator
) noexcept -> bool {
  return LinkedHashMapBase::__removeConst (pObject->template map <LinkedHashMapBase>(), &pIterator->iterator());
}


template <typename __KeyType, typename __ValueType, typename __Hasher>__CDS_OptimalInline auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::ValueMutableCollectionProxy::__removeArray (
    ValueMutableCollectionProxy*  pObject,
    Iterator const* const*        ppIterators,
    Size                          iteratorArrayCount
) noexcept -> Size {
  using __Alloc = __hidden::__impl::__allocation::__PrimitiveAlloc <  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename __hidden::__impl::__LinkedHashMapLinkedListImplementation <__KeyType, __ValueType, __Hasher>::__sll_Iterator const*
  >;

  auto ppWrappedIteratorArray = __Alloc::__alloc (iteratorArrayCount);
  uint32 wrappedIteratorArraySize = 0u;
  for (uint32 iteratorIndex = 0u; iteratorIndex < iteratorArrayCount; ++iteratorIndex) {
    if (ppIterators [iteratorIndex] != nullptr) {                                           // NOLINT(*-bounds-pointer-arithmetic)
      ppWrappedIteratorArray [wrappedIteratorArraySize++] = &ppIterators [iteratorIndex]->iterator(); // NOLINT(*-bounds-pointer-arithmetic)
    }
  }

  auto const removedIteratorCount = LinkedHashMapBase::__removeArray (
      pObject->template map <LinkedHashMapBase> (),
      ppWrappedIteratorArray,
      wrappedIteratorArraySize
  );

  __Alloc::__free (ppWrappedIteratorArray);
  return removedIteratorCount;
}


template <typename __KeyType, typename __ValueType, typename __Hasher>__CDS_OptimalInline auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::ValueMutableCollectionProxy::__removeConstArray (
    ValueMutableCollectionProxy*  pObject,
    ConstIterator const* const*   ppIterators,
    Size                          iteratorArrayCount
) noexcept -> Size {
  using __Alloc = __hidden::__impl::__allocation::__PrimitiveAlloc <  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename __hidden::__impl::__LinkedHashMapLinkedListImplementation <__KeyType, __ValueType, __Hasher>::__sll_ConstIterator const*
  >;

  auto ppWrappedIteratorArray = __Alloc::__alloc (iteratorArrayCount);
  uint32 wrappedIteratorArraySize = 0u;
  for (uint32 iteratorIndex = 0u; iteratorIndex < iteratorArrayCount; ++iteratorIndex) {
    if (ppIterators [iteratorIndex] != nullptr) {                                           // NOLINT(*-bounds-pointer-arithmetic)
      ppWrappedIteratorArray [wrappedIteratorArraySize++] = &ppIterators [iteratorIndex]->iterator(); // NOLINT(*-bounds-pointer-arithmetic)
    }
  }

  auto const removedIteratorCount = LinkedHashMapBase::__removeConstArray (
      pObject->template map <LinkedHashMapBase> (),
      ppWrappedIteratorArray,
      wrappedIteratorArraySize
  );

  __Alloc::__free (ppWrappedIteratorArray);
  return removedIteratorCount;
}


template <typename __KeyType, typename __ValueType, typename __Hasher>auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::ValueMutableCollectionProxy::__equals (
    ValueMutableCollectionProxy const& set
) const noexcept -> bool {
  if (this == & set) {
    return true;
  }

  if (size() != set.size()) {
    return false;
  }

  for (auto leftIt = begin(), rightIt = set.begin(), leftEnd = end(); leftIt != leftEnd; ++leftIt, ++rightIt) {
    if (!cds::meta::equals (*leftIt, *rightIt)) {
      return false;
    }
  }

  return true;
}


template <typename __KeyType, typename __ValueType, typename __Hasher>__CDS_OptimalInline auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::ValueMutableCollectionProxy::operator == (
    ValueMutableCollectionProxy const& set
) const noexcept -> bool {
  return __equals (set);
}


template <typename __KeyType, typename __ValueType, typename __Hasher>__CDS_OptimalInline auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::ValueMutableCollectionProxy::operator != (
    ValueMutableCollectionProxy const& set
) const noexcept -> bool {
  return !__equals (set); // NOLINT(clion-misra-cpp2008-5-3-1)
}

} // namespace cds

#endif // __CDS_LINKED_HASH_MAP_VALUE_MUTABLE_COLLECTION_PROXY_IMPL_HPP__
