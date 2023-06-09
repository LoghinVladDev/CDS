//
// Created by Vlad-Andrei Loghin on 09.06.23.
//

#ifndef __CDS_SHARED_NODE_ITERATOR_TRAITS_HPP__
#define __CDS_SHARED_NODE_ITERATOR_TRAITS_HPP__

namespace cds {
namespace __hidden {
namespace __impl {
template <
    template <typename...> class  __NodeType,     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename                      __ElementType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    bool = cds::meta::IsConst <__ElementType>::value
> struct __NodeIteratorTraits {};                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

template <
    template <typename...> class __NodeType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ElementType                    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> struct __NodeIteratorTraits <__NodeType, __ElementType, true> {
  using Node = __NodeType <cds::meta::RemoveConst<__ElementType>>;
  using RVal = __ElementType;
};

template <
    template <typename...> class __NodeType,  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __ElementType                    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> struct __NodeIteratorTraits <__NodeType, __ElementType, false> {
  using Node = __NodeType <__ElementType>;
  using RVal = __ElementType;
};
}
}
}

#endif // __CDS_SHARED_NODE_ITERATOR_TRAITS_HPP__
