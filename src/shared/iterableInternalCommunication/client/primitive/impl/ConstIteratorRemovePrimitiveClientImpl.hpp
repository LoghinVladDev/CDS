//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_CONST_ITERATOR_REMOVE_PRIMITIVE_CLIENT_IMPL_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_SHARED_CONST_ITERATOR_REMOVE_PRIMITIVE_CLIENT_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {             // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Receiver, typename __Element> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __AbstractConstIteratorRemovePrimitiveClient <__Receiver, __Element>::remove (
    AbstractConstIterator const& iterator
) noexcept(false) -> bool {
  using __ReceiverRemoveConstIteratorHandlerType  = cds::functional::PredicateFunction <__Receiver*, cds::meta::Iterator const*>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto pReceiver                                  = static_cast <__Receiver*> (this);

  // Since iterator is abstract, it is compatible with Collection Ownership -> has 'of' function. Check for ownership. If not owned, removal unsuccessful
  if (!iterator.of(pReceiver)) {
    return false;
  }

  // Acquire the member function to call from client and call it with extracted delegate as parameter, return value received from the call
  return bitCast <__ReceiverRemoveConstIteratorHandlerType> (pReceiver->__iicch_obtainGenericHandler (__IterableInternalRequest::__iir_removeConst)) (
      pReceiver, iterator._pDelegate->iterator()
  );
}


template <typename __Receiver, typename __Element> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __AbstractConstIteratorRemovePrimitiveClient <__Receiver, __Element>::removeAll (
    AbstractConstIterator const*  pIterators,
    Size                          iteratorCount
) noexcept(false) -> Size {
  using __Alloc                                       = __hidden::__impl::__allocation::__PrimitiveAlloc <cds::meta::Iterator const*>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using __ReceiverRemoveConstIteratorArrayHandlerType = cds::functional::MapperFunction <Size, __Receiver*, cds::meta::Iterator const* const*, Size>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  using __ReceiverRemoveConstIteratorHandlerType      = cds::functional::PredicateFunction <__Receiver*, cds::meta::Iterator const*>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  auto pReceiver                  = static_cast <__Receiver*> (this);
  auto genericIteratorArray       = __Alloc::__alloc (iteratorCount);
  Size genericIteratorArraySize   = 0u;
  Size removedIteratorCount       = 0u;

  try {
    for (Size index = 0u; index < iteratorCount; ++index) {
      if (!pIterators [index].of (pReceiver)) {
        continue;
      }
      genericIteratorArray [genericIteratorArraySize++] = pIterators [index]._pDelegate->iterator();
    }

    if (genericIteratorArraySize >= 2u) {
      removedIteratorCount = bitCast <__ReceiverRemoveConstIteratorArrayHandlerType> (pReceiver->__iicch_obtainGenericHandler (__IterableInternalRequest::__iir_removeConstArray)) (
          pReceiver, &genericIteratorArray [0u], genericIteratorArraySize
      );
    } else if (genericIteratorArraySize == 1u) {
      removedIteratorCount = bitCast <__ReceiverRemoveConstIteratorHandlerType> (pReceiver->__iicch_obtainGenericHandler (__IterableInternalRequest::__iir_removeConst)) (
          pReceiver, genericIteratorArray [0u]
      ) ? 1u : 0u;
    }

    __Alloc::__free (genericIteratorArray);
    return removedIteratorCount;
  } catch(...) {
    __Alloc::__free (genericIteratorArray);
    throw;
  }
}


template <typename __Receiver, typename __Element, typename __Iterator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __LocalConstIteratorRemovePrimitiveClient <__Receiver, __Element, __Iterator>::remove (
    ConstIterator const& iterator
) noexcept(false) -> bool {
  // local client, directly call the dispatcher-generated function for const removal
  return __Receiver::__removeConst (static_cast <__Receiver*> (this), &iterator);
}


template <typename __Receiver, typename __Element, typename __Iterator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __LocalConstIteratorRemovePrimitiveClient <__Receiver, __Element, __Iterator>::removeAll (
    ConstIterator const*  pIterators,
    Size                  iteratorCount
) noexcept(false) -> Size {
  using __Alloc = __hidden::__impl::__allocation::__PrimitiveAlloc <__Iterator const*>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

  auto pReceiver = static_cast <__Receiver*> (this);
  if (iteratorCount >= 2u) {
    auto pIteratorBuffer    = __Alloc::__alloc (iteratorCount);
    try {
      for (Size index = 0u; index < iteratorCount; ++index) {
        pIteratorBuffer[index] = &pIterators [index];
      }

      Size removedCount = __Receiver::__removeConstArray (pReceiver, &pIteratorBuffer [0u], iteratorCount);
      __Alloc::__free (pIteratorBuffer);
      return removedCount;
    } catch (...) {
      __Alloc::__free (pIteratorBuffer);
      throw;
    }
  } else if (iteratorCount == 1u) {
    return __Receiver::__removeConst (pReceiver, &pIterators [0u]) ? 1u : 0u;
  }

  return 0u;
}
} // namespace __impl
} // namespace __hidden
} // namespace cds

#endif // __CDS_SHARED_CONST_ITERATOR_REMOVE_PRIMITIVE_CLIENT_IMPL_HPP__
