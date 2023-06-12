//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_DELEGATE_FORWARD_ITERABLE_PRIMITIVE_CLIENT_IMPL_HPP__ // NOLINT(llvm-header-guard) 
#define __CDS_SHARED_DELEGATE_FORWARD_ITERABLE_PRIMITIVE_CLIENT_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
#pragma once

namespace cds {             // NOLINT(modernize-concat-nested-namespaces) 
namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
namespace __impl {  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Receiver, typename __Element, bool __bidirectional>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
auto __DelegateForwardIterablePrimitiveClient <__Receiver, __Element, __bidirectional>::begin () noexcept(false) -> Iterator {
  using __ReceiverBeginHandlerType    = cds::functional::MapperFunction <__AbstractDelegateIterator <__Element>*, __Receiver*>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto pReceiver                      = static_cast <__Receiver*> (this);
  return Iterator (pReceiver, bitCast <__ReceiverBeginHandlerType> (pReceiver->__iicch_obtainGenericHandler (__IterableInternalRequest::__iir_begin)) (pReceiver));
}


template <typename __Receiver, typename __Element, bool __bidirectional>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
auto __DelegateForwardIterablePrimitiveClient <__Receiver, __Element, __bidirectional>::end () noexcept(false) -> Iterator {
  using __ReceiverEndHandlerType  = cds::functional::MapperFunction <__AbstractDelegateIterator <__Element>*, __Receiver*>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto pReceiver                  = static_cast <__Receiver*> (this);
  return Iterator (pReceiver, bitCast <__ReceiverEndHandlerType> (pReceiver->__iicch_obtainGenericHandler (__IterableInternalRequest::__iir_end)) (pReceiver));
}


template <typename __Receiver, typename __IteratorType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto __LocalDelegateForwardIterablePrimitiveClient <__Receiver, __IteratorType>::begin () noexcept -> Iterator {
  return __Receiver::__beginLocal (static_cast <__Receiver*> (this));
}


template <typename __Receiver, typename __IteratorType> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto __LocalDelegateForwardIterablePrimitiveClient <__Receiver, __IteratorType>::end () noexcept -> Iterator {
  return __Receiver::__endLocal (static_cast <__Receiver*> (this));
}
} // namespace __impl 
} // namespace __hidden 
} // namespace cds 

#endif // __CDS_SHARED_DELEGATE_FORWARD_ITERABLE_PRIMITIVE_CLIENT_IMPL_HPP__ 
