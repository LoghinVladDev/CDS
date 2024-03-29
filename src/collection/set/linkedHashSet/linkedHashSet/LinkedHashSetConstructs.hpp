// NOLINT(llvm-header-guard)
// Created by loghin on 02/10/22.
//

#ifndef __CDS_LINKED_HASH_SET_CONSTRUCTS_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_LINKED_HASH_SET_CONSTRUCTS_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {
template <
    typename __ElementType,                                                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Hasher = WrapperHasher <__ElementType, Hash <__ElementType>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class LinkedHashSet;

namespace __hidden {  // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
namespace __impl {    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)

template <typename __ElementType>                                                                             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto __linkedHashSetKeyExtractor (__UnidirectionalNode<__ElementType>* const& pNode) noexcept -> __ElementType const&{  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  return pNode->_data;
}


template <typename __ElementType>                                                               // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_MaybeUnused __CDS_cpplang_ConstexprNonLiteralReturn auto __linkedHashSetCopyConstructor ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __UnidirectionalNode<__ElementType>*&       destination,
    __UnidirectionalNode<__ElementType>* const& source
) noexcept -> void {
  destination = source;
}


template <typename __ElementType>                                           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprNonLiteralReturn auto __linkedHashSetDestructor (    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __UnidirectionalNode<__ElementType>*& node
) noexcept -> void {
  (void) node;
}


template <typename __ElementType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedHashSetHashTableImplementation :        // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __HashTable <
        __UnidirectionalNode<__ElementType>*, __ElementType, __Hasher,
        cds::__hidden::__impl::__PrimeRehashPolicy <uint32>, &__linkedHashSetKeyExtractor <__ElementType>,
        &cds::meta::equals <__ElementType>, &__linkedHashSetDestructor <__ElementType>
    > {};


template <typename __ElementType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedHashSetLinkedListImplementation :   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __SingleLinkedList <__ElementType, &cds::meta::equals <__ElementType>> {};


template <typename __ElementType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
using  __LinkedHashSetIterator =                      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __LinkedHashSetLinkedListImplementation <__ElementType, __Hasher>::__sll_ConstIterator;


template <typename __ElementType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedHashSetServer : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __SetServer <cds::LinkedHashSet <__ElementType, __Hasher>, __ElementType> {};


template <typename __ElementType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedHashSetRandomInsertionClient :      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRandomInsertionPrimitiveClient <
        cds::LinkedHashSet <__ElementType, __Hasher>, __ElementType, __ElementType const
    > {};


template <typename __ElementType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedHashSetIteratorRemoveClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalConstIteratorRemovePrimitiveClient <
        cds::LinkedHashSet <__ElementType, __Hasher>, __ElementType,
        __LinkedHashSetIterator <__ElementType, __Hasher>
    > {};


template <typename __ElementType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedHashSetFindOfIterableClient :   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindOfImmutableCompositeClient <
        cds::LinkedHashSet <__ElementType, __Hasher>, __ElementType,
        __LinkedHashSetIterator <__ElementType, __Hasher>, cds::Iterable <__ElementType>,
        &__iterableContains <__ElementType>, &__iterableNotContains <__ElementType>
    > {};


template <typename __ElementType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedHashSetFindOfInitializerListClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindOfImmutableCompositeClient <
        cds::LinkedHashSet <__ElementType, __Hasher>, __ElementType,
        __LinkedHashSetIterator <__ElementType, __Hasher>,
        std::initializer_list <__ElementType>,
        &__initializerListContains <__ElementType, &cds::meta::equals <__ElementType>>,
        &__initializerListNotContains <__ElementType, &cds::meta::equals <__ElementType>>
    > {};


template <typename __ElementType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedHashSetFindByClient :    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindByImmutableCompositeClient <
        cds::LinkedHashSet <__ElementType, __Hasher>, __ElementType,
        __LinkedHashSetIterator <__ElementType, __Hasher>
    > {};


template <typename __ElementType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedHashSetRemoveOfIterableClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRemoveOfCompositeClient <
        cds::LinkedHashSet <__ElementType, __Hasher>, __ElementType,
        cds::Iterable <__ElementType>, &__iterableContains <__ElementType>
    > {};


template <typename __ElementType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedHashSetRemoveOfInitializerListClient :    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRemoveOfCompositeClient <
        cds::LinkedHashSet <__ElementType, __Hasher>, __ElementType,
        std::initializer_list <__ElementType>,
        &__initializerListContains <__ElementType, &cds::meta::equals <__ElementType>>
    > {};


template <typename __ElementType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedHashSetRemoveByClient :       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRemoveByCompositeClient <cds::LinkedHashSet <__ElementType, __Hasher>, __ElementType> {};


template <typename __ElementType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedHashSetGenericStatementsClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalGenericImmutableStatementsCompositeClient <cds::LinkedHashSet <__ElementType, __Hasher>, __ElementType> {};


template <typename __ElementType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedHashSetFindUniqueClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindUniqueImmutablePrimitiveClient <
        cds::LinkedHashSet <__ElementType, __Hasher>, __ElementType,
        __LinkedHashSetIterator <__ElementType, __Hasher>
    > {};


template <typename __ElementType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedHashSetContainsOfIterableClient :   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalContainsOfCompositeClient <
        cds::LinkedHashSet <__ElementType, __Hasher>, __ElementType,
        cds::Iterable <__ElementType>, &__iterableContains <__ElementType>
    > {};


template <typename __ElementType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedHashSetContainsOfInitializerListClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalContainsOfCompositeClient <
        cds::LinkedHashSet <__ElementType, __Hasher>, __ElementType,
        std::initializer_list <__ElementType>,
        &__initializerListContains <__ElementType, &cds::meta::equals <__ElementType>>
    > {};


template <typename __ElementType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
class __CDS_InheritsEBOs __LinkedHashSetDelegateForwardConstIterableClient :   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalDelegateForwardConstIterablePrimitiveClient <
        cds::LinkedHashSet <__ElementType, __Hasher>, __LinkedHashSetIterator <__ElementType, __Hasher>
    > {};
} // namespace __impl
} // namespace __hidden
} // namespace cds

#endif // __CDS_LINKED_HASH_SET_CONSTRUCTS_HPP__
