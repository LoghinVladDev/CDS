//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_DELEGATE_BACKWARD_ITERABLE_PRIMITIVE_CLIENT_IMPL_HPP__ // NOLINT(llvm-header-guard) 
#define __CDS_SHARED_DELEGATE_BACKWARD_ITERABLE_PRIMITIVE_CLIENT_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {             // NOLINT(modernize-concat-nested-namespaces) 
namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
namespace __impl {  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Receiver, typename __Element, bool __bidirectional>            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __DelegateBackwardIterablePrimitiveClient <__Receiver, __Element, __bidirectional>::rbegin () noexcept(false) -> ReverseIterator {
  using __ReceiverRBeginHandlerType   = cds::functional::MapperFunction <__AbstractDelegateIterator <__Element>*, __Receiver*>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto pReceiver                      = static_cast <__Receiver*> (this);
  return ReverseIterator (pReceiver, bitCast <__ReceiverRBeginHandlerType> (pReceiver->__iicch_obtainGenericHandler (__IterableInternalRequest::__iir_rbegin)) (pReceiver));
}


template <typename __Receiver, typename __Element, bool __bidirectional>            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __DelegateBackwardIterablePrimitiveClient <__Receiver, __Element, __bidirectional>::rend () noexcept(false) -> ReverseIterator {
  using __ReceiverREndHandlerType = cds::functional::MapperFunction <__AbstractDelegateIterator <__Element>*, __Receiver*>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto pReceiver                  = static_cast <__Receiver*> (this);
  return ReverseIterator (pReceiver, bitCast <__ReceiverREndHandlerType> (pReceiver->__iicch_obtainGenericHandler (__IterableInternalRequest::__iir_rend)) (pReceiver));
}


template <typename __Receiver, typename __ReverseIterator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto __LocalDelegateBackwardIterablePrimitiveClient <__Receiver, __ReverseIterator>::rbegin () noexcept -> ReverseIterator {
  return __Receiver::__rbeginLocal (static_cast <__Receiver*> (this));
}


template <typename __Receiver, typename __ReverseIterator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_NonConstConstexprMemberFunction auto __LocalDelegateBackwardIterablePrimitiveClient <__Receiver, __ReverseIterator>::rend () noexcept -> ReverseIterator {
  return __Receiver::__rendLocal (static_cast <__Receiver*> (this));
}
} // namespace __impl 
} // namespace __hidden 
} // namespace cds 

#endif // __CDS_SHARED_DELEGATE_BACKWARD_ITERABLE_PRIMITIVE_CLIENT_IMPL_HPP__ 
