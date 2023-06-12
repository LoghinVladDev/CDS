// NOLINT(llvm-header-guard)
// Created by loghin on 10/08/22.
//

#ifndef __CDS_HASH_SET_CONSTRUCTS_HPP__ // NOLINT(llvm-header-guard)
#define __CDS_HASH_SET_CONSTRUCTS_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds {
template <
    typename __ElementType,                                                 // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Hasher = WrapperHasher <__ElementType, Hash <__ElementType>> // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class HashSet;

namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
namespace __impl {  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
template <typename __ElementType>                                                                       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
constexpr auto __hashSetKeyExtractor (__ElementType const&element) noexcept -> __ElementType const&{  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  return element;
}


template <typename __ElementType>                                     // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprNonLiteralReturn auto __hashSetCopyConstructor ( // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    __ElementType&       destination,
    __ElementType const& source
) noexcept -> void {
  (void) new (&destination) __ElementType (source);
}


template < typename __ElementType >                                                                           // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
__CDS_cpplang_ConstexprNonLiteralReturn auto __hashSetDestructor (__ElementType&element) noexcept -> void {  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
  element.~__ElementType();
}


template <typename __ElementType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
class __CDS_InheritsEBOs __HashSetImplementation :   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __HashTable <
        __ElementType, __ElementType, __Hasher,
        cds::__hidden::__impl::__PrimeRehashPolicy < uint32 >, &__hashSetKeyExtractor <__ElementType>,
        &cds::meta::equals <__ElementType>, &__hashSetDestructor <__ElementType>
    > {};


template <typename __ElementType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
class __CDS_InheritsEBOs __HashSetDispatcher :   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __HashSetImplementation <__ElementType, __Hasher>::template __SetDispatcher <
        HashSet <__ElementType, __Hasher>
    > {};


template <typename __ElementType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
class __CDS_InheritsEBOs __HashSetServer :       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __SetServer <cds::HashSet <__ElementType, __Hasher>, __ElementType> {};


template <typename __ElementType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
class __CDS_InheritsEBOs __HashSetRandomInsertionClient :      // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRandomInsertionPrimitiveClient <
        cds::HashSet <__ElementType, __Hasher>, __ElementType, __ElementType const
    > {};


template <typename __ElementType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
class __CDS_InheritsEBOs __HashSetIteratorRemoveClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalConstIteratorRemovePrimitiveClient <
        cds::HashSet <__ElementType, __Hasher>, __ElementType, HashTableIterator <__ElementType const>
    > {};


template <typename __ElementType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
class __CDS_InheritsEBOs __HashSetFindOfIterableClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindOfImmutableCompositeClient <
        cds::HashSet <__ElementType, __Hasher>, __ElementType,
        HashTableIterator <__ElementType const>, cds::Iterable <__ElementType>,
        &__iterableContains <__ElementType>, &__iterableNotContains <__ElementType>
    > {};


template <typename __ElementType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
class __CDS_InheritsEBOs __HashSetFindOfInitializerListClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindOfImmutableCompositeClient <
        cds::HashSet <__ElementType, __Hasher>,
        __ElementType, HashTableIterator <__ElementType const>,
        std::initializer_list <__ElementType>,
        &__initializerListContains <__ElementType, &cds::meta::equals <__ElementType>>,
        &__initializerListNotContains <__ElementType, &cds::meta::equals <__ElementType>>
    > {};


template <typename __ElementType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
class __CDS_InheritsEBOs __HashSetFindByClient :    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindByImmutableCompositeClient <
        cds::HashSet <__ElementType, __Hasher>, __ElementType, HashTableIterator <__ElementType const>
    > {};


template <
    typename __ElementType,             // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    typename __Hasher                   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
> class __CDS_InheritsEBOs __HashSetRemoveOfIterableClient :   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRemoveOfCompositeClient <
        cds::HashSet <__ElementType, __Hasher>, __ElementType,
        cds::Iterable <__ElementType>, &__iterableContains <__ElementType>
    > {};


template <typename __ElementType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
class __CDS_InheritsEBOs __HashSetRemoveOfInitializerListClient :    // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRemoveOfCompositeClient <
        cds::HashSet <__ElementType, __Hasher>, __ElementType,
        std::initializer_list <__ElementType>,
        &__initializerListContains < __ElementType, &cds::meta::equals <__ElementType> >
    > {};


template <typename __ElementType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
class __CDS_InheritsEBOs __HashSetRemoveByClient :       // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalRemoveByCompositeClient <cds::HashSet <__ElementType, __Hasher>, __ElementType> {};


template <typename __ElementType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
class __CDS_InheritsEBOs __HashSetGenericStatementsClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalGenericImmutableStatementsCompositeClient <cds::HashSet <__ElementType, __Hasher>, __ElementType> {};


template <typename __ElementType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
class __CDS_InheritsEBOs __HashSetFindUniqueClient : // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalFindUniqueImmutablePrimitiveClient <
        cds::HashSet <__ElementType, __Hasher>, __ElementType, HashTableIterator <__ElementType const>
    > {};


template <typename __ElementType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
class __CDS_InheritsEBOs __HashSetContainsOfIterableClient :   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalContainsOfCompositeClient <
        cds::HashSet < __ElementType, __Hasher >, __ElementType,
        cds::Iterable <__ElementType>, &__iterableContains <__ElementType>
    > {};


template <typename __ElementType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
class __CDS_InheritsEBOs __HashSetContainsOfInitializerListClient :  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalContainsOfCompositeClient <
        cds::HashSet < __ElementType, __Hasher >, __ElementType,
        std::initializer_list <__ElementType>,
        &__initializerListContains <__ElementType, &cds::meta::equals <__ElementType>>
    > {};


template <typename __ElementType, typename __Hasher>  // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) 
class __CDS_InheritsEBOs __HashSetDelegateForwardConstIterableClient :   // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
    public __LocalDelegateForwardConstIterablePrimitiveClient <
        cds::HashSet < __ElementType, __Hasher >,
        typename __HashSetImplementation < __ElementType, __Hasher >::__ht_ConstIterator
    > {};

} /* namespace __impl */
} /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_HASH_SET_CONSTRUCTS_HPP__ */
