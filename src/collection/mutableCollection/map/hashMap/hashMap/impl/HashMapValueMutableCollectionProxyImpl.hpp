// NOLINT(llvm-header-guard)
// Created by loghin on 14/08/22.
//

#ifndef __CDS_HASH_MAP_VALUE_MUTABLE_COLLECTION_PROXY_IMPL_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_HASH_MAP_VALUE_MUTABLE_COLLECTION_PROXY_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

namespace cds {
template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto HashMap <__KeyType, __ValueType, __Hasher>::ValueMutableCollectionProxy::__iicch_obtainGenericHandler (
    __hidden::__impl::__IterableInternalRequestType requestType
) noexcept -> __GenericHandler {
  return __mcs_handlers() [static_cast <uint32> (requestType)];
}


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto HashMap <__KeyType, __ValueType, __Hasher>::ValueMutableCollectionProxy::__iicch_obtainGenericConstHandler (
    __hidden::__impl::__IterableInternalRequestType requestType
) const noexcept -> __GenericConstHandler {
  return __mcs_constHandlers() [static_cast <uint32> (requestType)];
}


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr HashMap <__KeyType, __ValueType, __Hasher>::ValueMutableCollectionProxy::ValueMutableCollectionProxy (
    HashMap < __KeyType, __ValueType, __Hasher >* pMap
) noexcept :
    AbstractValueMutableCollectionProxy (pMap) {

}


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprDestructor HashMap <__KeyType, __ValueType, __Hasher>::ValueMutableCollectionProxy::~ValueMutableCollectionProxy () noexcept = default;


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto HashMap <__KeyType, __ValueType, __Hasher>::ValueMutableCollectionProxy::__begin (
    ValueMutableCollectionProxy* pObject
) noexcept -> __hidden::__impl ::__AbstractDelegateIterator <__ValueType>* {
  return Memory::instance().create <__hidden::__impl::__DelegateIterator <__ValueType, Iterator>> (
      Iterator (HashMapBase::__beginLocal (pObject->template map <HashMapBase>()))
  );
}


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto HashMap <__KeyType, __ValueType, __Hasher>::ValueMutableCollectionProxy::__end (
    ValueMutableCollectionProxy* pObject
) noexcept -> __hidden::__impl ::__AbstractDelegateIterator <__ValueType>* {
  return Memory::instance().create <__hidden::__impl::__DelegateIterator <__ValueType, Iterator>> (
      Iterator (HashMapBase::__endLocal (pObject->template map <HashMapBase>()))
  );
}


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto HashMap <__KeyType, __ValueType, __Hasher>::ValueMutableCollectionProxy::__cbegin (
    ValueMutableCollectionProxy const* pObject
) noexcept -> __hidden::__impl ::__AbstractDelegateIterator <__ValueType const>* {
  return Memory::instance().create <__hidden::__impl::__DelegateIterator <__ValueType const, ConstIterator>> (
      ConstIterator (HashMapBase::__cbeginLocal (pObject->template map <HashMapBase>()))
  );
}


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto HashMap <__KeyType, __ValueType, __Hasher>::ValueMutableCollectionProxy::__cend (
    ValueMutableCollectionProxy const* pObject
) noexcept -> __hidden::__impl ::__AbstractDelegateIterator <__ValueType const>* {
  return Memory::instance().create <__hidden::__impl::__DelegateIterator <__ValueType const, ConstIterator>> (
      ConstIterator (HashMapBase::__cendLocal (pObject->template map <HashMapBase>()))
  );
}


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto HashMap <__KeyType, __ValueType, __Hasher>::ValueMutableCollectionProxy::__beginLocal (
    ValueMutableCollectionProxy* pObject
) noexcept -> Iterator {
  return Iterator (HashMapBase::__beginLocal (pObject->template map <HashMapBase>()));
}


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto HashMap <__KeyType, __ValueType, __Hasher>::ValueMutableCollectionProxy::__endLocal (
    ValueMutableCollectionProxy* pObject
) noexcept -> Iterator {
  return Iterator (HashMapBase::__endLocal (pObject->template map <HashMapBase>()));
}


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto HashMap <__KeyType, __ValueType, __Hasher>::ValueMutableCollectionProxy::__cbeginLocal (
    ValueMutableCollectionProxy const* pObject
) noexcept -> ConstIterator {
  return ConstIterator (HashMapBase::__cbeginLocal (pObject->template map <HashMapBase>()));
}


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto HashMap <__KeyType, __ValueType, __Hasher>::ValueMutableCollectionProxy::__cendLocal (
    ValueMutableCollectionProxy const* pObject
) noexcept -> ConstIterator {
  return ConstIterator (HashMapBase::__cendLocal (pObject->template map <HashMapBase>()));
}


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto HashMap <__KeyType, __ValueType, __Hasher>::ValueMutableCollectionProxy::__remove (
    ValueMutableCollectionProxy*  pObject,
    Iterator const*               pIterator
) noexcept -> bool {
  return HashMapBase::__remove (pObject->template map <HashMapBase>(), &pIterator->iterator ());
}


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto HashMap <__KeyType, __ValueType, __Hasher>::ValueMutableCollectionProxy::__removeConst (
    ValueMutableCollectionProxy*  pObject,
    ConstIterator const*          pIterator
) noexcept -> bool {
  return HashMapBase::__removeConst (pObject->template map <HashMapBase>(), &pIterator->iterator());
}


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto HashMap <__KeyType, __ValueType, __Hasher>::ValueMutableCollectionProxy::__removeArray (
    ValueMutableCollectionProxy*  pObject,
    Iterator const* const*        ppIterators,
    Size                          iteratorArrayCount
) noexcept -> Size {
  using __Alloc = __hidden::__impl::__allocation::__PrimitiveAlloc <  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename __hidden::__impl::__HashMapImplementation <__KeyType, __ValueType, __Hasher>::__ht_Iterator const*
  >;

  auto ppWrappedIteratorArray = __Alloc::__alloc (iteratorArrayCount);
  uint32 wrappedIteratorArraySize = 0u;
  for (uint32 iteratorIndex = 0u; iteratorIndex < iteratorArrayCount; ++iteratorIndex) {
    if (ppIterators [iteratorIndex] != nullptr) {                                           // NOLINT(*-bounds-pointer-arithmetic)
      ppWrappedIteratorArray [wrappedIteratorArraySize++] = &ppIterators [iteratorIndex]->iterator(); // NOLINT(*-bounds-pointer-arithmetic)
    }
  }

  auto const removedIteratorCount = HashMapBase::__removeArray (
      pObject->template map <HashMapBase> (),
      ppWrappedIteratorArray,
      wrappedIteratorArraySize
  );

  __Alloc::__free (ppWrappedIteratorArray);
  return removedIteratorCount;
}


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto HashMap <__KeyType, __ValueType, __Hasher>::ValueMutableCollectionProxy::__removeConstArray (
    ValueMutableCollectionProxy*  pObject,
    ConstIterator const* const*   ppIterators,
    Size                          iteratorArrayCount
) noexcept -> Size {
  using __Alloc = __hidden::__impl::__allocation::__PrimitiveAlloc <  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
      typename __hidden::__impl::__HashMapImplementation <__KeyType, __ValueType, __Hasher>::__ht_ConstIterator const*
  >;

  auto ppWrappedIteratorArray = __Alloc::__alloc (iteratorArrayCount);
  uint32 wrappedIteratorArraySize = 0u;
  for (uint32 iteratorIndex = 0u; iteratorIndex < iteratorArrayCount; ++iteratorIndex) {
    if (ppIterators [iteratorIndex] != nullptr) {                                           // NOLINT(*-bounds-pointer-arithmetic)
      ppWrappedIteratorArray [wrappedIteratorArraySize++] = &ppIterators [iteratorIndex]->iterator(); // NOLINT(*-bounds-pointer-arithmetic)
    }
  }

  auto const removedIteratorCount = HashMapBase::__removeConstArray (
      pObject->template map <HashMapBase>(),
      ppWrappedIteratorArray,
      wrappedIteratorArraySize
  );

  __Alloc::__free (ppWrappedIteratorArray);
  return removedIteratorCount;
}


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto HashMap <__KeyType, __ValueType, __Hasher>::ValueMutableCollectionProxy::__equals (
    ValueMutableCollectionProxy const& set
) const noexcept -> bool {
  if (this == &set) {
    return true;
  }

  if (size() != set.size()) {
    return false;
  }

  for (
      auto leftIt = begin(), rightIt = set.begin(), leftEnd = end();
      leftIt != leftEnd; ++ leftIt, ++ rightIt    // NOLINT(clion-misra-cpp2008-5-18-1)
      ) {
    if (!cds::meta::equals (*leftIt, *rightIt)) {            // NOLINT(clion-misra-cpp2008-5-3-1)
      return false;
    }
  }

  return true;
}


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto HashMap <__KeyType, __ValueType, __Hasher>::ValueMutableCollectionProxy::operator == (
    ValueMutableCollectionProxy const& set
) const noexcept -> bool {
  return __equals (set);
}


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto HashMap <__KeyType, __ValueType, __Hasher>::ValueMutableCollectionProxy::operator != (
    ValueMutableCollectionProxy const & set
) const noexcept -> bool {
  return !__equals (set); // NOLINT(clion-misra-cpp2008-5-3-1)
}

} // namespace cds

#endif // __CDS_HASH_MAP_VALUE_MUTABLE_COLLECTION_PROXY_IMPL_HPP__
