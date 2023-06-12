//
// Created by loghin on 09/08/22.
//

#ifndef __CDS_SHARED_DELEGATE_FIND_UNIQUE_IMMUTABLE_PRIMITIVE_CLIENT_IMPL_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_SHARED_DELEGATE_FIND_UNIQUE_IMMUTABLE_PRIMITIVE_CLIENT_IMPL_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {       // NOLINT(modernize-concat-nested-namespaces)
namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __Receiver, typename __Element, typename __Key, bool __bidirectional>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __FindUniqueImmutablePrimitiveClient <__Receiver, __Element, __Key, __bidirectional>::find (
    __Key const& key
) const noexcept(false) -> ConstIterator {
  // explicit type of the handler received from the client
  using __ReceiverFindConstHandlerType    = cds::functional::MapperFunction <__AbstractDelegateIterator <__Element const>*, __Receiver const*, __Key const&>;  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  // object as the receiver type
  auto const pReceiver                    = static_cast <__Receiver const*> (this);

  // create a wrapper const iterator with the received delegate iterator from __cirt_findConst
  return ConstIterator (pReceiver, bitCast <__ReceiverFindConstHandlerType> (pReceiver->__iicch_obtainGenericConstHandler (__IterableInternalRequest::__iir_findConst)) (pReceiver, key));
}


template <typename __Receiver, typename __Key, typename __Iterator> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_OptimalInline auto __LocalFindUniqueImmutablePrimitiveClient <__Receiver, __Key, __Iterator>::find (
    __Key const& key
) const noexcept -> ConstIterator {
  // directly call the __findConstLocal function
  return __Receiver::__findConstLocal (static_cast <__Receiver const*> (this), key);
}
} // namespace __impl
} // namespace __hidden
} // namespace cds

#endif // __CDS_SHARED_DELEGATE_FIND_UNIQUE_IMMUTABLE_PRIMITIVE_CLIENT_IMPL_HPP__
