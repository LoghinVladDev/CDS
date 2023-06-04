//
// Created by stefan on 13.10.2022.
//

#ifndef __CDS_TREE_MAP_VALUE_MUTABLE_COLLECTION_PROXY_IMPL_HPP__
#define __CDS_TREE_MAP_VALUE_MUTABLE_COLLECTION_PROXY_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {

template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto TreeMap <__KeyType, __ValueType, __Comparator>::ValueMutableCollectionProxy::__iicch_obtainGenericHandler (         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __hidden::__impl::__IterableInternalRequestType requestType
) noexcept -> __GenericHandler {
  return __mcs_handlers() [static_cast <uint32> (requestType)];
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto TreeMap <__KeyType, __ValueType, __Comparator>::ValueMutableCollectionProxy::__iicch_obtainGenericConstHandler (         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __hidden::__impl::__IterableInternalRequestType requestType
) const noexcept -> __GenericConstHandler {
  return __mcs_constHandlers() [static_cast <uint32> (requestType)];
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
TreeMap <__KeyType, __ValueType, __Comparator>::ValueMutableCollectionProxy::ValueMutableCollectionProxy (
    TreeMap <__KeyType, __ValueType, __Comparator>* pMap
) noexcept : AbstractValueMutableCollectionProxy (pMap) {

}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto TreeMap <__KeyType, __ValueType, __Comparator>::ValueMutableCollectionProxy::__begin (
    ValueMutableCollectionProxy* pObject
) noexcept -> cds::__hidden::__impl::__AbstractDelegateIterator <__ValueType>* {
  return Memory::instance().create <cds::__hidden::__impl::__DelegateIterator <__ValueType, Iterator>> (
      Iterator (TreeMapBase::__beginLocal (pObject->template map <TreeMapBase>()))
  );
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto TreeMap <__KeyType, __ValueType, __Comparator>::ValueMutableCollectionProxy::__end (
    ValueMutableCollectionProxy* pObject
) noexcept -> cds::__hidden::__impl::__AbstractDelegateIterator <__ValueType>* {
  return Memory::instance().create < cds::__hidden::__impl::__DelegateIterator <__ValueType, Iterator>> (
      Iterator (TreeMapBase::__endLocal (pObject->template map <TreeMapBase>()))
  );
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto TreeMap <__KeyType, __ValueType, __Comparator>::ValueMutableCollectionProxy::__beginLocal (
    ValueMutableCollectionProxy* pObject
) noexcept -> Iterator {
  return Iterator (TreeMapBase::__beginLocal (pObject->template map <TreeMapBase>()));
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto TreeMap <__KeyType, __ValueType, __Comparator>::ValueMutableCollectionProxy::__endLocal (
    ValueMutableCollectionProxy* pObject
) noexcept -> Iterator {
  return Iterator (TreeMapBase::__endLocal (pObject->template map <TreeMapBase>()));
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto TreeMap <__KeyType, __ValueType, __Comparator>::ValueMutableCollectionProxy::__cbegin (
    ValueMutableCollectionProxy const* pObject
) noexcept -> cds::__hidden::__impl::__AbstractDelegateIterator <__ValueType const>* {
  return Memory::instance().create < cds::__hidden::__impl::__DelegateIterator <__ValueType const, ConstIterator>> (
      ConstIterator (TreeMapBase::__cbeginLocal (pObject->template map <TreeMapBase>()))
  );
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto TreeMap <__KeyType, __ValueType, __Comparator>::ValueMutableCollectionProxy::__cend (
    ValueMutableCollectionProxy const* pObject
) noexcept -> cds::__hidden::__impl::__AbstractDelegateIterator <__ValueType const>* {
  return Memory::instance().create < cds::__hidden::__impl::__DelegateIterator <__ValueType const, ConstIterator>> (
      ConstIterator (TreeMapBase::__cendLocal (pObject->template map <TreeMapBase>()))
  );
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto TreeMap <__KeyType, __ValueType, __Comparator>::ValueMutableCollectionProxy::__cbeginLocal (
    ValueMutableCollectionProxy const* pObject
) noexcept -> ConstIterator {
  return Iterator (TreeMapBase::__cbeginLocal (pObject->template map <TreeMapBase>()));
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto TreeMap <__KeyType, __ValueType, __Comparator>::ValueMutableCollectionProxy::__cendLocal (
    ValueMutableCollectionProxy const* pObject
) noexcept -> ConstIterator {
  return Iterator (TreeMapBase::__cendLocal (pObject->template map <TreeMapBase>()));
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto TreeMap <__KeyType, __ValueType, __Comparator>::ValueMutableCollectionProxy::__rbeginLocal (
    ValueMutableCollectionProxy* pObject
) noexcept -> ReverseIterator {
  return Iterator (TreeMapBase::__rbeginLocal (pObject->template map <TreeMapBase>()));
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto TreeMap <__KeyType, __ValueType, __Comparator>::ValueMutableCollectionProxy::__rendLocal (
    ValueMutableCollectionProxy* pObject
) noexcept -> ReverseIterator {
  return Iterator (TreeMapBase::__rendLocal (pObject->template map <TreeMapBase>()));
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto TreeMap <__KeyType, __ValueType, __Comparator>::ValueMutableCollectionProxy::__crbeginLocal (
    ValueMutableCollectionProxy const* pObject
) noexcept -> ConstReverseIterator {
  return Iterator (TreeMapBase::__crbeginLocal (pObject->template map <TreeMapBase>()));
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto TreeMap <__KeyType, __ValueType, __Comparator>::ValueMutableCollectionProxy::__crendLocal (
    ValueMutableCollectionProxy const* pObject
) noexcept -> ConstReverseIterator {
  return Iterator (TreeMapBase::__crendLocal (pObject->template map <TreeMapBase>()));
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto TreeMap <__KeyType, __ValueType, __Comparator>::ValueMutableCollectionProxy::__remove (
    ValueMutableCollectionProxy*  pObject,
    AbstractIterator const*       iterator
) noexcept -> bool {
  return TreeMapBase:: __remove (pObject->template map <TreeMapBase>(), &iterator->iterator());
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto TreeMap <__KeyType, __ValueType, __Comparator>::ValueMutableCollectionProxy::__removeConst (
    ValueMutableCollectionProxy* pObject,
    AbstractConstIterator const* iterator
) noexcept -> bool {
  return TreeMapBase::__removeConst (pObject->template map <TreeMapBase>(),&iterator->iterator());
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto TreeMap <__KeyType, __ValueType, __Comparator>::ValueMutableCollectionProxy::__removeArray (
    ValueMutableCollectionProxy*    pObject,
    AbstractIterator const* const*  ppIterators,
    Size                            iteratorCount
) noexcept -> Size {
  using __Alloc = __hidden::__impl::__allocation::__PrimitiveAlloc <  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename __hidden::__impl::__TreeMapImplementation <__KeyType, __ValueType, __Comparator>::__rbt_AbstractIterator const*
  >;

  auto ppWrappedIteratorArray = __Alloc::__alloc (iteratorCount);
  uint32 wrappedIteratorArraySize = 0u;
  for (auto iteratorIndex = 0u; iteratorIndex < iteratorCount; ++iteratorIndex) {
    if (ppIterators [iteratorIndex] != nullptr) {
      ppWrappedIteratorArray [wrappedIteratorArraySize++] = &ppIterators [iteratorIndex]->iterator();
    }
  }

  auto const removedIteratorCount = TreeMapBase::__removeArray (
      pObject->template map <TreeMapBase> (),
      ppWrappedIteratorArray,
      wrappedIteratorArraySize
  );

  __Alloc::__free (ppWrappedIteratorArray);
  return removedIteratorCount;
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto TreeMap <__KeyType, __ValueType, __Comparator>::ValueMutableCollectionProxy::__removeConstArray (
    ValueMutableCollectionProxy*        pObject,
    AbstractConstIterator const* const* ppIterators,
    Size                                iteratorCount
) noexcept -> Size {
  using __Alloc = __hidden::__impl::__allocation::__PrimitiveAlloc <  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename __hidden::__impl::__TreeMapImplementation <__KeyType, __ValueType, __Comparator>::__rbt_AbstractConstIterator const*
  >;

  auto ppWrappedIteratorArray = __Alloc::__alloc (iteratorCount);
  uint32 wrappedIteratorArraySize = 0u;
  for (auto iteratorIndex = 0u; iteratorIndex < iteratorCount; ++iteratorIndex) {
    if (ppIterators [iteratorIndex] != nullptr) {
      ppWrappedIteratorArray [wrappedIteratorArraySize++] = &ppIterators [iteratorIndex]->iterator();
    }
  }

  auto const removedIteratorCount = TreeMapBase::__removeConstArray (
      pObject->template map <TreeMapBase> (),
      ppWrappedIteratorArray,
      wrappedIteratorArraySize
  );

  __Alloc::__free (ppWrappedIteratorArray);
  return removedIteratorCount;
}
}

#endif // __CDS_TREE_MAP_VALUE_MUTABLE_COLLECTION_PROXY_IMPL_HPP__
