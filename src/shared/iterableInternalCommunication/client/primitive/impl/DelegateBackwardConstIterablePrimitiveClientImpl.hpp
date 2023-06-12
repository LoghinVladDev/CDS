//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_DELEGATE_BACKWARD_CONST_ITERABLE_PRIMITIVE_CLIENT_IMPL_HPP__ // NOLINT(llvm-header-guard) 
#define __CDS_SHARED_DELEGATE_BACKWARD_CONST_ITERABLE_PRIMITIVE_CLIENT_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {             // NOLINT(modernize-concat-nested-namespaces) 
namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
namespace __impl {  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Receiver, typename __Element, bool __bidirectional>            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __DelegateBackwardConstIterablePrimitiveClient <__Receiver, __Element, __bidirectional>::rbegin () const noexcept(false) -> ConstReverseIterator {
  return crbegin();
}


template <typename __Receiver, typename __Element, bool __bidirectional>            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __DelegateBackwardConstIterablePrimitiveClient <__Receiver, __Element, __bidirectional>::rend () const noexcept(false) -> ConstReverseIterator {
  return crend();
}


template <typename __Receiver, typename __Element, bool __bidirectional>            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __DelegateBackwardConstIterablePrimitiveClient <__Receiver, __Element, __bidirectional>::crbegin () const noexcept(false) -> ConstReverseIterator {
  using __ReceiverRBeginHandlerType   = cds::functional::MapperFunction <__AbstractDelegateIterator <__Element const>*, __Receiver const*>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto const pReceiver                = static_cast <__Receiver const*> (this);
  return ConstReverseIterator (pReceiver, bitCast <__ReceiverRBeginHandlerType> (pReceiver->__iicch_obtainGenericConstHandler (__IterableInternalRequest::__iir_rbegin)) (pReceiver));
}


template <typename __Receiver, typename __Element, bool __bidirectional>            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __DelegateBackwardConstIterablePrimitiveClient <__Receiver, __Element, __bidirectional>::crend () const noexcept(false) -> ConstReverseIterator {
  using __ReceiverREndHandlerType = cds::functional::MapperFunction <__AbstractDelegateIterator <__Element const>*, __Receiver const*>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto const pReceiver            = static_cast <__Receiver const*> (this);
  return ConstReverseIterator (pReceiver, bitCast <__ReceiverREndHandlerType> (pReceiver->__iicch_obtainGenericConstHandler (__IterableInternalRequest::__iir_rend)) (pReceiver));
}


template <typename __Receiver, typename __ConstReverseIterator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
constexpr auto __LocalDelegateBackwardConstIterablePrimitiveClient <__Receiver, __ConstReverseIterator>::rbegin () const noexcept -> ConstReverseIterator {
  return __Receiver::__crbeginLocal (static_cast <__Receiver const*> (this));
}


template <typename __Receiver, typename __ConstReverseIterator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
constexpr auto __LocalDelegateBackwardConstIterablePrimitiveClient <__Receiver, __ConstReverseIterator>::rend () const noexcept -> ConstReverseIterator {
  return __Receiver::__crendLocal (static_cast <__Receiver const*> (this));
}


template <typename __Receiver, typename __ConstReverseIterator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
constexpr auto __LocalDelegateBackwardConstIterablePrimitiveClient <__Receiver, __ConstReverseIterator>::crbegin () const noexcept -> ConstReverseIterator {
  return __Receiver::__crbeginLocal (static_cast <__Receiver const*> (this));
}


template <typename __Receiver, typename __ConstReverseIterator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
constexpr auto __LocalDelegateBackwardConstIterablePrimitiveClient <__Receiver, __ConstReverseIterator>::crend () const noexcept -> ConstReverseIterator {
  return __Receiver::__crendLocal (static_cast <__Receiver const*> (this));
}
} // namespace __impl 
} // namespace __hidden 
} // namespace cds 

#endif // __CDS_SHARED_DELEGATE_BACKWARD_CONST_ITERABLE_PRIMITIVE_CLIENT_IMPL_HPP__ 
