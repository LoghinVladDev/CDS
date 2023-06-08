//
// Created by loghin on 6/26/22.
//

#ifndef __CDS_SHARED_DELEGATE_FORWARD_CONST_ITERABLE_PRIMITIVE_CLIENT_IMPL_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_SHARED_DELEGATE_FORWARD_CONST_ITERABLE_PRIMITIVE_CLIENT_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {             // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {    // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Receiver, typename __Element, bool __bidirectional>            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __DelegateForwardConstIterablePrimitiveClient <__Receiver, __Element, __bidirectional>::begin () const noexcept(false) -> ConstIterator {
  // begin const is cbegin
  return cbegin();
}


template <typename __Receiver, typename __Element, bool __bidirectional>            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __DelegateForwardConstIterablePrimitiveClient <__Receiver, __Element, __bidirectional>::end () const noexcept(false) -> ConstIterator {
  // end const is cend
  return cend();
}


template <typename __Receiver, typename __Element, bool __bidirectional>            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __DelegateForwardConstIterablePrimitiveClient <__Receiver, __Element, __bidirectional>::cbegin () const noexcept(false) -> ConstIterator {
  using __ReceiverBeginHandlerType    = cds::functional::MapperFunction <__AbstractDelegateIterator <__Element const>*, __Receiver const*>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto const pReceiver                = static_cast <__Receiver const*> (this);
  // Construct a ConstIterator with the current collection and the result from calling the received server member function of type __cirt_begin.
  // Member function is acquired from the Collection Communication Channel
  return ConstIterator (pReceiver, bitCast <__ReceiverBeginHandlerType> (pReceiver->__iicch_obtainGenericConstHandler (__IterableInternalRequest::__iir_begin)) (pReceiver));
}


template <typename __Receiver, typename __Element, bool __bidirectional>            // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
__CDS_OptimalInline auto __DelegateForwardConstIterablePrimitiveClient <__Receiver, __Element, __bidirectional>::cend () const noexcept(false) -> ConstIterator {
  using __ReceiverEndHandlerType  = cds::functional::MapperFunction <__AbstractDelegateIterator <__Element const>*, __Receiver const*>; // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  auto const pReceiver            = static_cast <__Receiver const*> (this);
  // Construct a ConstIterator with the current collection and the result from calling the received server member function of type __cirt_end.
  // Member function is acquired from the Collection Communication Channel
  return ConstIterator (pReceiver, bitCast <__ReceiverEndHandlerType> (pReceiver->__iicch_obtainGenericConstHandler (__IterableInternalRequest::__iir_end)) (pReceiver));
}


template <typename __Receiver, typename __ConstIterator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto __LocalDelegateForwardConstIterablePrimitiveClient <__Receiver, __ConstIterator>::begin () const noexcept -> ConstIterator {
  return __Receiver::__cbeginLocal (static_cast <__Receiver const*> (this));
}


template <typename __Receiver, typename __ConstIterator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto __LocalDelegateForwardConstIterablePrimitiveClient <__Receiver, __ConstIterator>::end () const noexcept -> ConstIterator {
  return __Receiver::__cendLocal (static_cast <__Receiver const*> (this));
}


template <typename __Receiver, typename __ConstIterator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto __LocalDelegateForwardConstIterablePrimitiveClient <__Receiver, __ConstIterator>::cbegin () const noexcept -> ConstIterator {
  return __Receiver::__cbeginLocal (static_cast <__Receiver const*> (this));
}


template <typename __Receiver, typename __ConstIterator>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto __LocalDelegateForwardConstIterablePrimitiveClient <__Receiver, __ConstIterator>::cend () const noexcept -> ConstIterator {
  return __Receiver::__cendLocal (static_cast <__Receiver const*> (this));
}
} // namespace __impl
} // namespace __hidden
} // namespace cds

#endif // __CDS_SHARED_DELEGATE_FORWARD_CONST_ITERABLE_PRIMITIVE_CLIENT_IMPL_HPP__
