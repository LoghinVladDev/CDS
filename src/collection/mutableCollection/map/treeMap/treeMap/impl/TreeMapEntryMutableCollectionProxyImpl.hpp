//
// Created by stefan on 13.10.2022.
//

#ifndef __CDS_TREE_MAP_ENTRY_MUTABLE_COLLECTION_PROXY_IMPL_HPP__
#define __CDS_TREE_MAP_ENTRY_MUTABLE_COLLECTION_PROXY_IMPL_HPP__     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

namespace cds {
template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto TreeMap <__KeyType, __ValueType, __Comparator>::EntryMutableCollectionProxy::__iicch_obtainGenericHandler (         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::__hidden::__impl::__IterableInternalRequest requestType
) noexcept -> __GenericHandler {
  return __mcs_handlers() [ static_cast <uint32> (requestType)];
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto TreeMap <__KeyType, __ValueType, __Comparator>::EntryMutableCollectionProxy::__iicch_obtainGenericConstHandler (         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::__hidden::__impl::__IterableInternalRequest requestType
) const noexcept -> __GenericConstHandler {
  return __mcs_constHandlers() [static_cast <uint32> (requestType)];
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
TreeMap <__KeyType, __ValueType, __Comparator>::EntryMutableCollectionProxy::EntryMutableCollectionProxy (
    TreeMap <__KeyType, __ValueType, __Comparator>* pMap
) noexcept : AbstractEntryMutableCollectionProxy (pMap) {

}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto TreeMap <__KeyType, __ValueType, __Comparator>::EntryMutableCollectionProxy::__newAddress (
    EntryMutableCollectionProxy*  pObject,
    EntryType const*              pReferenceElement,
    bool*                         pIsNew
) noexcept -> EntryType* {
  return pObject->template map <TreeMapBase>()->__rbt_new (pReferenceElement, pIsNew);
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto TreeMap <__KeyType, __ValueType, __Comparator>::EntryMutableCollectionProxy::__begin (
    EntryMutableCollectionProxy* pObject
) noexcept -> cds::__hidden::__impl::__AbstractDelegateIterator <EntryType>* {
  return TreeMapBase::__begin (pObject->template map <TreeMapBase>());
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto TreeMap <__KeyType, __ValueType, __Comparator>::EntryMutableCollectionProxy::__end (
    EntryMutableCollectionProxy* pObject
) noexcept -> cds::__hidden::__impl::__AbstractDelegateIterator <EntryType>* {

  return TreeMapBase::__end (pObject->template map <TreeMapBase>());
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto TreeMap <__KeyType, __ValueType, __Comparator>::EntryMutableCollectionProxy::__beginLocal (
    EntryMutableCollectionProxy* pObject
) noexcept -> Iterator {
  return TreeMapBase::__beginLocal (pObject->template map <TreeMapBase>());
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto TreeMap <__KeyType, __ValueType, __Comparator>::EntryMutableCollectionProxy::__endLocal (
    EntryMutableCollectionProxy* pObject
) noexcept -> Iterator {
  return TreeMapBase::__endLocal (pObject->template map <TreeMapBase>());
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto TreeMap <__KeyType, __ValueType, __Comparator>::EntryMutableCollectionProxy::__cbegin (
    EntryMutableCollectionProxy const* pObject
) noexcept -> cds::__hidden::__impl::__AbstractDelegateIterator <EntryType const>* {
  return TreeMapBase::__cbegin (pObject->template map <TreeMapBase>());
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto TreeMap <__KeyType, __ValueType, __Comparator>::EntryMutableCollectionProxy::__cend (
    EntryMutableCollectionProxy const* pObject
) noexcept -> cds::__hidden::__impl::__AbstractDelegateIterator <EntryType const>* {
  return TreeMapBase::__cend (pObject->template map <TreeMapBase>());
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto TreeMap <__KeyType, __ValueType, __Comparator>::EntryMutableCollectionProxy::__cbeginLocal (
    EntryMutableCollectionProxy const* pObject
) noexcept -> ConstIterator {
  return TreeMapBase::__cbeginLocal (pObject->template map <TreeMapBase>());
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto TreeMap <__KeyType, __ValueType, __Comparator>::EntryMutableCollectionProxy::__cendLocal (
    EntryMutableCollectionProxy const* pObject
) noexcept -> ConstIterator {
  return TreeMapBase::__cendLocal (pObject->template map <TreeMapBase>());
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto TreeMap <__KeyType, __ValueType, __Comparator>::EntryMutableCollectionProxy::__rbeginLocal (
    EntryMutableCollectionProxy* pObject
) noexcept -> ReverseIterator {
  return TreeMapBase::__rbeginLocal (pObject->template map <TreeMapBase>());
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto TreeMap <__KeyType, __ValueType, __Comparator>::EntryMutableCollectionProxy::__rendLocal (
    EntryMutableCollectionProxy* pObject
) noexcept -> ReverseIterator {

  return TreeMapBase::__rendLocal (pObject->template map <TreeMapBase>());
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto TreeMap <__KeyType, __ValueType, __Comparator>::EntryMutableCollectionProxy::__crbeginLocal (
    EntryMutableCollectionProxy const* pObject
) noexcept -> ConstReverseIterator {
  return TreeMapBase::__crbeginLocal (pObject->template map <TreeMapBase>());
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto TreeMap <__KeyType, __ValueType, __Comparator>::EntryMutableCollectionProxy::__crendLocal (
    EntryMutableCollectionProxy const* pObject
) noexcept -> ConstReverseIterator {

  return TreeMapBase::__crendLocal (pObject->template map <TreeMapBase>());
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto TreeMap <__KeyType, __ValueType, __Comparator>::EntryMutableCollectionProxy::__remove (
    EntryMutableCollectionProxy*  pObject,
    AbstractIterator const*       iterator
) noexcept -> bool {
  return TreeMapBase::__remove (pObject->template map <TreeMapBase>(), iterator);
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto TreeMap <__KeyType, __ValueType, __Comparator>::EntryMutableCollectionProxy::__removeConst (
    EntryMutableCollectionProxy* pObject,
    AbstractConstIterator const* iterator
) noexcept -> bool {
  return TreeMapBase::__removeConst (pObject->template map <TreeMapBase>(), iterator);
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto TreeMap <__KeyType, __ValueType, __Comparator>::EntryMutableCollectionProxy::__removeArray (
    EntryMutableCollectionProxy*    pObject,
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
      ppWrappedIteratorArray [wrappedIteratorArraySize++] = ppIterators [iteratorIndex];
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
__CDS_OptimalInline auto TreeMap <__KeyType, __ValueType, __Comparator>::EntryMutableCollectionProxy::__removeConstArray (
    EntryMutableCollectionProxy*        pObject,
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
      ppWrappedIteratorArray [wrappedIteratorArraySize++] = ppIterators [iteratorIndex];
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
} // namespace cds

#endif // __CDS_TREE_MAP_ENTRY_MUTABLE_COLLECTION_PROXY_IMPL_HPP__
