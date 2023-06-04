//
// Created by stefan on 13.10.2022.
//

#ifndef __CDS_TREE_MAP_KEY_SET_PROXY_IMPL_HPP__
#define __CDS_TREE_MAP_KEY_SET_PROXY_IMPL_HPP__     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {
template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto TreeMap <__KeyType, __ValueType, __Comparator>::KeySetProxy::__iicch_obtainGenericHandler (         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::__hidden::__impl::__IterableInternalRequestType requestType
) noexcept -> __GenericHandler {
  return __ss_handlers() [static_cast <uint32> (requestType)];
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto TreeMap <__KeyType, __ValueType, __Comparator>::KeySetProxy::__iicch_obtainGenericConstHandler (         // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    cds::__hidden::__impl::__IterableInternalRequestType requestType
) const noexcept -> __GenericConstHandler {
  return __ss_constHandlers() [static_cast <uint32> (requestType)];
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
TreeMap <__KeyType, __ValueType, __Comparator>::KeySetProxy::KeySetProxy (
    TreeMap <__KeyType, __ValueType, __Comparator>* pMap
) noexcept : AbstractKeySetProxy (pMap) {

}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto TreeMap <__KeyType, __ValueType, __Comparator>::KeySetProxy::contains (
    __KeyType const& key
) const noexcept -> bool {
  return map()->containsKey (key);
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto TreeMap <__KeyType, __ValueType, __Comparator>::KeySetProxy::__cbegin (
    KeySetProxy const* pObject
) noexcept -> cds::__hidden::__impl::__AbstractDelegateIterator <__KeyType const>* {
  return Memory::instance().create < cds::__hidden::__impl::__DelegateIterator <__KeyType const, ConstIterator>> (
      ConstIterator (TreeMapBase::__cbeginLocal (pObject->template map <TreeMapBase>()))
  );
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto TreeMap <__KeyType, __ValueType, __Comparator>::KeySetProxy::__cend (
    KeySetProxy const* pObject
) noexcept -> cds::__hidden::__impl::__AbstractDelegateIterator <__KeyType const>* {
  return Memory::instance().create < cds::__hidden::__impl::__DelegateIterator <__KeyType const, ConstIterator>> (
      ConstIterator (TreeMapBase::__cendLocal (pObject->template map <TreeMapBase>()))
  );
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto TreeMap <__KeyType, __ValueType, __Comparator>::KeySetProxy::__cbeginLocal (
    KeySetProxy const* pObject
) noexcept -> ConstIterator {
  return ConstIterator (TreeMapBase::__cbeginLocal (pObject->template map <TreeMapBase>()));
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto TreeMap <__KeyType, __ValueType, __Comparator>::KeySetProxy::__cendLocal (
    KeySetProxy const* pObject
) noexcept -> ConstIterator {
  return ConstIterator (TreeMapBase::__cendLocal (pObject->template map <TreeMapBase>()));
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto TreeMap <__KeyType, __ValueType, __Comparator>::KeySetProxy::__crbeginLocal (
    KeySetProxy const* pObject
) noexcept -> ConstReverseIterator {
  return Iterator (TreeMapBase::__crbeginLocal (pObject->template map <TreeMapBase>()));
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto TreeMap <__KeyType, __ValueType, __Comparator>::KeySetProxy::__crendLocal (
    KeySetProxy const* pObject
) noexcept -> ConstReverseIterator {
  return Iterator (TreeMapBase::__crendLocal (pObject->template map <TreeMapBase>()));
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto TreeMap <__KeyType, __ValueType, __Comparator>::KeySetProxy::__removeConst (
    KeySetProxy*                  pObject,
    AbstractConstIterator const*  iterator
) noexcept -> bool {
  return TreeMapBase::__removeConst (pObject->template map <TreeMapBase>(), &iterator->iterator());
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto TreeMap <__KeyType, __ValueType, __Comparator>::KeySetProxy::__removeConstArray (
    KeySetProxy*                        pObject,
    AbstractConstIterator const* const* ppIterators,
    Size                                iteratorCount
) noexcept -> Size {
  using __Alloc = __hidden::__impl::__allocation::__PrimitiveAlloc <  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename __hidden::__impl::__TreeMapImplementation <__KeyType, __ValueType, __Comparator>::__rbt_AbstractConstIterator const*
  >;

  auto ppWrappedIteratorArray = __Alloc::__alloc (iteratorCount);
  uint32 wrappedIteratorArraySize = 0u;
  for (auto iteratorIndex = 0u; iteratorIndex < iteratorCount; ++iteratorIndex) {
    if ( ppIterators [iteratorIndex] != nullptr) {
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


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto TreeMap <__KeyType, __ValueType, __Comparator>::KeySetProxy::__findConst (
    KeySetProxy const*  pObject,
    __KeyType const&    key
) noexcept -> cds::__hidden::__impl::__AbstractDelegateIterator <__KeyType const>* {
  return Memory::instance().create < cds::__hidden::__impl::__DelegateIterator <__KeyType const, ConstIterator>> (
      ConstIterator (TreeMapBase::__findConstLocal (pObject->template map <TreeMapBase>(), key))
  );
}


template <typename __KeyType, typename __ValueType, typename __Comparator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto TreeMap <__KeyType, __ValueType, __Comparator>::KeySetProxy::__findConstLocal (
    KeySetProxy const*  pObject,
    __KeyType const&    key
) noexcept -> ConstIterator {
  return ConstIterator (TreeMapBase::__findConstLocal (pObject->template map <TreeMapBase>(), key));
}
}

#endif // __CDS_TREE_MAP_KEY_SET_PROXY_IMPL_HPP__
