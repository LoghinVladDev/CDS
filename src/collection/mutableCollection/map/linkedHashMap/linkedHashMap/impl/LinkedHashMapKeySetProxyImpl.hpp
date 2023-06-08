// NOLINT(llvm-header-guard)
// Created by loghin on 09/10/22.
//

#ifndef __CDS_LINKED_HASH_MAP_KEY_SET_PROXY_IMPL_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_LINKED_HASH_MAP_KEY_SET_PROXY_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {

template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::KeySetProxy::__iicch_obtainGenericHandler (
    __hidden::__impl::__IterableInternalRequest requestType
) noexcept -> __GenericHandler {
  return __ss_handlers() [static_cast <uint32> (requestType)];
}


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::KeySetProxy::__iicch_obtainGenericConstHandler (
    __hidden::__impl::__IterableInternalRequest requestType
) const noexcept -> __GenericConstHandler {
  return __ss_constHandlers() [static_cast <uint32> (requestType)];
}


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr LinkedHashMap <__KeyType, __ValueType, __Hasher>::KeySetProxy::KeySetProxy (
    LinkedHashMap < __KeyType, __ValueType, __Hasher >* pMap
) noexcept : AbstractKeySetProxy (pMap) {

}


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprDestructor LinkedHashMap <__KeyType, __ValueType, __Hasher>::KeySetProxy::~KeySetProxy () noexcept = default;


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprOverride auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::KeySetProxy::contains (
    __KeyType const& key
) const noexcept -> bool {
  return map()->containsKey (key);
}


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::KeySetProxy::__cbeginLocal (
    KeySetProxy const* pObject
) noexcept -> ConstIterator {
  return ConstIterator (LinkedHashMapBase::__cbeginLocal (pObject->template map <LinkedHashMapBase> ()));
}


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::KeySetProxy::__cendLocal (
    KeySetProxy const* pObject
) noexcept -> ConstIterator {
  return ConstIterator (LinkedHashMapBase::__cendLocal (pObject->template map <LinkedHashMapBase> ()));
}


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::KeySetProxy::__cbegin (
    KeySetProxy const* pObject
) noexcept -> __hidden::__impl::__AbstractDelegateIterator <__KeyType const>* {
  return Memory::instance().create <__hidden::__impl::__DelegateIterator <__KeyType const, ConstIterator>> (
      ConstIterator (LinkedHashMapBase::__cbeginLocal (pObject->template map <LinkedHashMapBase> ()))
  );
}


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::KeySetProxy::__cend (
    KeySetProxy const* pObject
) noexcept -> __hidden::__impl::__AbstractDelegateIterator <__KeyType const>* {

  return Memory::instance().create <__hidden::__impl::__DelegateIterator <__KeyType const, ConstIterator>> (
      ConstIterator (LinkedHashMapBase::__cendLocal (pObject->template map <LinkedHashMapBase> ()))
  );
}


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::KeySetProxy::__removeConst (
    KeySetProxy*          pObject,
    ConstIterator const*  pIterator
) noexcept -> bool {
  return LinkedHashMapBase::__removeConst (pObject->template map <LinkedHashMapBase> (), &pIterator->iterator ());
}


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::KeySetProxy::__removeConstArray (
    KeySetProxy*                pObject,
    ConstIterator const* const* ppIterators,
    Size                        iteratorArrayCount
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


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::KeySetProxy::__findConst (
    KeySetProxy const*  pObject,
    __KeyType const&    key
) noexcept -> __hidden::__impl::__AbstractDelegateIterator <__KeyType const>* {
  return Memory::instance().create <__hidden::__impl::__DelegateIterator <__KeyType const, ConstIterator>> (
      ConstIterator (LinkedHashMapBase::__findConstLocal (pObject->template map <LinkedHashMapBase>(), key))
  );
}


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::KeySetProxy::__findConstLocal (
    KeySetProxy const*  pObject,
    __KeyType const&    key
) noexcept -> ConstIterator {
  return ConstIterator (LinkedHashMapBase::__findConstLocal (pObject->template map <LinkedHashMapBase> (), key));
}


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::KeySetProxy::__equals (
    KeySetProxy const& set
) const noexcept -> bool {
  if (this == &set) {
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


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::KeySetProxy::operator == (
    KeySetProxy const& set
) const noexcept -> bool {
  return __equals (set);
}


template <typename __KeyType, typename __ValueType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto LinkedHashMap <__KeyType, __ValueType, __Hasher>::KeySetProxy::operator != (
    KeySetProxy const& set
) const noexcept -> bool {
  return !__equals (set); // NOLINT(clion-misra-cpp2008-5-3-1)
}

} // namespace cds

#endif // __CDS_LINKED_HASH_MAP_KEY_SET_PROXY_IMPL_HPP__
